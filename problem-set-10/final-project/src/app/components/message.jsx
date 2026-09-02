"use client";
import { useRouter, useSearchParams } from "next/navigation";
import { useEffect, useState, useRef } from "react";
import Script from "next/script";

import { decryptMessage } from "../utils";
import { createApolloClient } from "client/client";
import { DELETE_MESSAGE, VERIFY_PASSWORD } from "client/mutations";
import { useTheme } from "context/theme-context";
import { GET_MESSAGE } from "client/query";

import Loader from "./loader";

export default function Message() {
  const router = useRouter();
  const { isDarkMode } = useTheme();

  const [error, setError] = useState("");
  const [message, setMessage] = useState("");
  const [loading, setLoading] = useState(false);
  const [deleting, setDeleting] = useState(false);
  const [turnstileToken, setTurnstileToken] = useState(null);
  const [decryptedId, setDecryptedId] = useState(null);

  const [passwordRequired, setPasswordRequired] = useState(false);
  const [passwordInput, setPasswordInput] = useState("");
  const [passwordError, setPasswordError] = useState("");
  const [verifyingPassword, setVerifyingPassword] = useState(false);
  const [encryptedMessageData, setEncryptedMessageData] = useState(null);

  const passwordSectionRef = useRef(null);

  const searchParams = useSearchParams();

  // ID from URL
  const encryptedId = searchParams.get("id");

  // Turnstile callback
  useEffect(() => {
    window.javascriptCallback = function (token) {
      setTurnstileToken(token);
    };
  }, []);

  // The ID from the URL is already a plain KV ID.
  // It does NOT need to be decrypted or verified as a JWT.
  useEffect(() => {
    if (encryptedId) {
      setDecryptedId(encryptedId);
    } else {
      setError("Message ID not found.");
    }
  }, [encryptedId]);

  // Automatic scroll to password form
  useEffect(() => {
    if (passwordRequired && passwordSectionRef.current) {
      setTimeout(() => {
        const targetElement = passwordSectionRef.current;

        const targetPosition =
          targetElement.getBoundingClientRect().top +
          window.pageYOffset -
          window.innerHeight / 2 +
          targetElement.offsetHeight / 2;

        window.scrollTo({
          top: targetPosition,
          behavior: "smooth",
        });

        setTimeout(() => {
          const passwordInput =
            passwordSectionRef.current.querySelector("#password");

          if (passwordInput) {
            passwordInput.focus();
          }
        }, 800);
      }, 200);
    }
  }, [passwordRequired]);

  // Fetch message
  useEffect(() => {
    if (!turnstileToken || !decryptedId) {
      return;
    }

    if (turnstileToken === "error") {
      setError("Turnstile verification failed.");
      setLoading(false);
      return;
    }

    const fetchMessage = async () => {
      setLoading(true);
      setError("");
      setPasswordError("");

      try {
        const client = createApolloClient(turnstileToken);

        const { data } = await client.query({
          query: GET_MESSAGE,
          variables: {
            id: decryptedId,
          },
        });

        const encryptedContent = data?.getMessage?.message;

        if (!encryptedContent) {
          setError("Message not found.");
          return;
        }

        try {
          const decryptedContent = await decryptMessage(encryptedContent);

          if (
            typeof decryptedContent === "object" &&
            decryptedContent !== null &&
            decryptedContent.password &&
            decryptedContent.password.trim() !== ""
          ) {
            setPasswordRequired(true);
            setEncryptedMessageData(decryptedContent);
          } else if (typeof decryptedContent === "string") {
            setMessage(decryptedContent);
          } else if (
            typeof decryptedContent === "object" &&
            decryptedContent !== null
          ) {
            setMessage(
              decryptedContent.message ||
                JSON.stringify(decryptedContent)
            );
          } else {
            setError("Invalid message content.");
          };
        } catch (decryptError) {
          setError(
            "Error decrypting content: " + decryptError.message
          );
        };
      } catch (err) {
        setError(
          err.message || "Error fetching message."
        );
      } finally {
        setLoading(false);
      };
    };

    fetchMessage();
  }, [turnstileToken, decryptedId]);

  // Verify password
  const handlePasswordSubmit = async (e) => {
    e.preventDefault();

    if (!passwordInput || !encryptedMessageData) {
      return;
    };

    setVerifyingPassword(true);
    setPasswordError("");

    try {
      const client = createApolloClient(turnstileToken);

      const { data } = await client.mutate({
        mutation: VERIFY_PASSWORD,
        variables: {
          id: decryptedId,
          password: passwordInput,
        },
      });

      if (
        data?.verifyPassword?.message === "Password correct"
      ) {
        setMessage(encryptedMessageData.message);
        setPasswordRequired(false);
        setPasswordInput("");
      } else {
        setPasswordError(
          "Incorrect password. Please try again."
        );
      };
    } catch (err) {
      setPasswordError(
        "Error verifying password: " + err.message
      );
    } finally {
      setVerifyingPassword(false);
    };
  };

  // Delete message
  const handleDelete = async () => {
    if (!turnstileToken || !decryptedId) {
      return;
    };

    setDeleting(true);
    setError("");

    try {
      const client = createApolloClient(turnstileToken);

      await client.mutate({
        mutation: DELETE_MESSAGE,
        variables: {
          id: decryptedId,
        },
      });

      setMessage("The note has been deleted.");
      setPasswordRequired(false);
    } catch (err) {
      setError(
        err.message || "Error deleting message."
      );
    } finally {
      setDeleting(false);
    };
  };

  const TURNSTILE_SITE_KEY = process.env.NEXT_PUBLIC_SITE_KEY;

  return (
    <div>
      <Script src="https://challenges.cloudflare.com/turnstile/v0/api.js" />

      <div className="h-15 flex items-center justify-between">
        <h2>Notate</h2>
      </div>

      <div>
        <div className="notebook">
          <div className="top-0 h-full left-13 absolute border-1 border-(--color-r-100)" />

          <textarea
            readOnly
            name="message"
            value={passwordRequired ? "" : message}
            placeholder={loading ? "Loading..." : passwordRequired ? "Enter password to view message" : "No message"}
          />
        </div>

        <div className="mb-6 grid md:flex md:h-15 space-x-4 items-center md:justify-between">
          <button
            className="u11 bg-third text-white"
            onClick={handleDelete}
            disabled={
              loading ||
              deleting ||
              passwordRequired
            }
          >
            {loading || deleting ? (
              <Loader />
            ) : (
              "Delete note"
            )}
          </button>

          <div className="justify-center flex">
            <div
              className="cf-turnstile"
              data-sitekey={TURNSTILE_SITE_KEY}
              data-callback="javascriptCallback"
              data-theme={isDarkMode ? "dark" : "light"}
            />
          </div>

          <div className="md:w-40 md:h-15">
            <button
              className="u11 text-third"
              type="button"
              onClick={() => router.push("/")}
            >
              New notate
            </button>
          </div>
        </div>

        {(error || passwordError) && (
          <div className="mb-6 text-sm text-r">
            <strong>
              Error: {error || passwordError}
            </strong>
          </div>
        )}

        {/* Password form */}
        <section
          ref={passwordSectionRef}
          className={
            passwordRequired
              ? "opacity-100"
              : "mb-0 p-0 max-h-0 opacity-0"
          }
        >
          <form
            onSubmit={handlePasswordSubmit}
            className="space-y-4"
          >
            <div>
              <label htmlFor="password">
                <h4>
                  This message is password protected
                </h4>

                <span>Enter password:</span>

                <input
                  type="password"
                  id="password"
                  value={passwordInput}
                  onChange={(e) =>
                    setPasswordInput(e.target.value)
                  }
                  placeholder="Password..."
                  disabled={verifyingPassword}
                  className={
                    passwordError
                      ? "border-(--color-r-100)"
                      : ""
                  }
                />
              </label>
            </div>

            <div className="p-2">
              <button
                className="w-full py-2 px-4 bg-third text-white"
                type="submit"
                disabled={
                  verifyingPassword ||
                  !passwordInput
                }
              >
                {verifyingPassword ? (
                  <Loader />
                ) : (
                  "Verify password"
                )}
              </button>
            </div>
          </form>
        </section>
      </div>
    </div>
  );
};
