import Lock from "styles/icons/lock";
import GithubIcon from "styles/icons/github";

export default function Footer() {
  return (
    <footer className="u1 align-center mb-4 md:mx-qp mx-2 border-t-2 border-t-third">
      <h4>Your secure messenger for creating one-time encrypted messages.</h4>
      <Lock />

      <aside className="github">
        <div className="z-2 fixed w-50 h-50 right-0 bottom-0 overflow-hidden after:content-[''] after:block after:absolute after:left-0 after:right-0 after:bottom-0 after:z-0 after:border-t-[12.5rem] after:border-t-transparent after:border-l-[12.5rem] after:border-l-transparent after:border-b-[12.5rem] after:border-b-[#343535]">
          <div className="u17 z-1 w-full h-full top-0 right-0 absolute justify-end -rotate-(--ff)">
            <a
              target="_blank"
              rel="noreferrer"
              aria-label="github-repo"
              href="https://github.com/realNormanik/harvard-cs50x/tree/main/problem-set-10/final-project"
              className="u17 focus:text-g-100 hover:text-[#a6a6a6] text-white text-base font-mono no-underline px-6 pt-[.1875rem] pb-6 m-0 -mb-5 transition-colors duration-[150ms] ease-[cubic-bezier(1,-.115,.975,.855)]"
            >
              <p className="text-current font-normal text-base mt-4 mb-4">View on GitHub</p>

              <GithubIcon />
            </a>
          </div>
        </div>
      </aside>
    </footer>
  );
};