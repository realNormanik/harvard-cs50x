"use client";
import { useTheme } from "context/theme-context";

import Sun from "styles/icons/sun";
import Moon from "styles/icons/moon";

export default function ThemeButton() {
  // Destructure dark mode state and setter function from theme context
  const { isDarkMode, setIsDarkMode } = useTheme();

  return (
    <div className="u15 gap-2 text-center align-middle">
      <label className="relative inline-block w-20 h-10 scale-[1.2] hover:scale-[1.3] transition-transform duration-200 cursor-pointer">
        <input
          type="checkbox"
          checked={isDarkMode}
          className="peer opacity-0 w-0 h-0"
          onChange={() => setIsDarkMode(!isDarkMode)}
        />

        <span className="
          absolute inset-0 rounded-[34px]
          bg-gradient-to-br from-[#f1c40f] to-[#f39c12]
          shadow-[0_0_15px_rgba(241,196,15,0.5)]
          transition-all duration-[400ms]
          overflow-hidden

          peer-checked:from-[#2c3e50] peer-checked:to-[#34495e]
          peer-checked:shadow-[0_0_15px_rgba(44,62,80,0.5)]

          before:absolute before:content-['☀️']
          before:h-8 before:w-8 before:left-[1px] before:bottom-[2px]
          before:bg-white before:rounded-full
          before:flex before:items-center before:justify-center
          before:text-[18px]
          before:shadow-[0_0_10px_rgba(0,0,0,0.1)]
          before:z-[2]
          before:transition-all before:duration-[400ms]

          peer-checked:before:translate-x-10
          peer-checked:before:content-['🌚']
          peer-checked:before:left-[6px]

          peer-checked:[&_.cloud]:opacity-0
          peer-checked:[&_.cloud]:-translate-y-5
        ">
          <div className="absolute w-full h-full overflow-hidden pointer-events-none">
            <svg
              viewBox="0 0 100 100"
              className="absolute top-[10px] left-[10px] w-5 h-5 fill-white/80 drop-shadow-[0_2px_3px_rgba(0,0,0,0.1)] transition-all duration-[400ms] animate-[float-cloud-1_8s_infinite_linear] motion-reduce:animate-none"
            >
              <path
                d="M30,45 Q35,25 50,25 Q65,25 70,45 Q80,45 85,50 Q90,55 85,60 Q80,65 75,60 Q65,60 60,65 Q55,70 50,65 Q45,70 40,65 Q35,60 25,60 Q20,65 15,60 Q10,55 15,50 Q20,45 30,45"
              />
            </svg>

            <svg
              viewBox="0 0 100 100"
              className="absolute top-[15px] left-10 scale-[0.8] w-5 h-5 fill-white/80 drop-shadow-[0_2px_3px_rgba(0,0,0,0.1)] transition-all duration-[400ms] animate-[float-cloud-2_12s_infinite_linear] motion-reduce:animate-none"
            >
              <path
                d="M30,45 Q35,25 50,25 Q65,25 70,45 Q80,45 85,50 Q90,55 85,60 Q80,65 75,60 Q65,60 60,65 Q55,70 50,65 Q45,70 40,65 Q35,60 25,60 Q20,65 15,60 Q10,55 15,50 Q20,45 30,45"
              />
            </svg>
          </div>
        </span>
      </label>
    </div>
  );
};