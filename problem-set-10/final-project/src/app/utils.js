import { jwtVerify } from "jose";

export async function decryptMessage(encryptedMessage) {
  try {
    const secret = new TextEncoder().encode(process.env.NEXT_PUBLIC_JWT_SECRET);
    const { payload } = await jwtVerify(encryptedMessage, secret);

    return payload;
  } catch (error) {
    console.error("Message decryption error:", error);
    throw new Error("Invalid message token");
  };
};