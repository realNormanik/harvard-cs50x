# CS50X – Problem Set 8: Trivia

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It marks the introduction of **HTML, CSS, and JavaScript** in the course. The goal was to build an interactive trivia webpage consisting of two parts: a **multiple-choice question** with several button-based answer choices, and a **free-response question** answered via a text input field. Using JavaScript, the page provides immediate visual feedback: buttons and input fields turn green with a "Correct!" message when the right answer is given, or red with an "Incorrect" message otherwise.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- structuring a webpage using semantic HTML elements (headings, buttons, input fields, and paragraphs),
- linking an external CSS stylesheet to control a page's visual appearance,
- writing client-side JavaScript to make a webpage interactive and responsive to user actions,
- selecting DOM elements using `document.querySelector` and `document.querySelectorAll`,
- attaching event listeners to respond to user interactions such as button clicks,
- dynamically modifying an element's styling (e.g., `style.backgroundColor`) and content (`innerHTML`) in response to events,
- distinguishing between different approaches to handling events in JavaScript (attaching listeners programmatically versus using inline `onclick` attributes),
- running and testing a webpage locally using a simple HTTP server,
- the tools provided by CS50 for submitting the solution (`submit50`), given that this problem has no automated `check50` due to variation in each student's chosen questions.

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2025/fall/psets/8/trivia.zip
   ```
2. Extracted the downloaded archive to create a folder called `trivia`:
   ```bash
   unzip trivia.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm trivia.zip
   ```
4. Navigated into the `trivia` folder:
   ```bash
   cd trivia
   ```
5. Reviewed the provided starter files (`index.html` and `styles.css`) to understand the existing page structure before adding content.
6. Added a multiple-choice trivia question beneath "Part 1" in `index.html`, using an `h3` heading for the question text and a set of `button` elements (with at least three choices, exactly one correct) for the possible answers.
7. Added a free-response trivia question beneath "Part 2" in `index.html`, using an `h3` heading for the question text, an `input` field for the user's typed response, and a `button` to confirm the answer.
8. Implemented JavaScript logic to handle the multiple-choice question, using `document.querySelectorAll` to select all "correct" and "incorrect" buttons, and attaching a `click` event listener to each that updates the button's background color and displays "Correct!" or "Incorrect" feedback text accordingly.
9. Implemented JavaScript logic to handle the free-response question, attaching a `click` event listener to the confirmation button that compares the input field's value against the expected answer, then updates the input field's background color and displays the appropriate feedback text.
10. Wrapped the JavaScript logic in a `DOMContentLoaded` event listener to ensure the script only ran once the page's HTML had fully loaded.
11. Started a local development server to preview and test the page:
    ```bash
    http-server
    ```
12. Manually tested both questions with correct and incorrect responses, confirming the buttons and input field changed color appropriately and that the correct feedback text appeared beneath each question.
13. Optionally adjusted `styles.css` to customize the page's appearance.
14. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/trivia
    ```

## 💻 Program Code

```html
<!DOCTYPE html>

<html lang="en">
<head>
    <meta charset="UTF-8" />
    <title>Trivia!</title>
    <link href="styles.css" rel="stylesheet" />
    <script>
        document.addEventListener("DOMContentLoaded", () => {
            // Support for multiple choice questions
            const buttons = document.querySelectorAll(".multiple-choice button");
            buttons.forEach(button => {
                button.addEventListener("click", () => {
                    // Reset colors and feedback
                    buttons.forEach(btn => btn.style.backgroundColor = "");
                    const feedback = button.parentElement.querySelector(".feedback");
                    feedback.textContent = "";

                    // We color and show feedback depending on the answer
                    if (button.classList.contains("correct")) {
                        button.style.backgroundColor = "green";
                        feedback.textContent = "Correct!";
                    } else {
                        button.style.backgroundColor = "red";
                        feedback.textContent = "Incorrect";
                    };
                });
            });

            // Handling an open-ended question
            const checkBtn = document.querySelector("#check-answer");
            checkBtn.addEventListener("click", () => {
                const input = document.querySelector("#free-response-input");
                const feedback = input.parentElement.querySelector(".feedback");
                const answer = input.value.trim().toLowerCase();

                if (answer === "switzerland") {
                    input.style.backgroundColor = "green";
                    feedback.textContent = "Correct!";
                } else {
                    input.style.backgroundColor = "red";
                    feedback.textContent = "Incorrect";
                };
            });
        });
    </script>
</head>
<body>
    <h1>Trivia!</h1>

    <section class="multiple-choice">
        <h2>Part 1: Multiple Choice</h2>
        <hr>
        <h3>What is the approximate ratio of people to sheep in New Zealand?</h3>
        <button class="incorrect">6 people per 1 sheep</button>
        <button class="incorrect">3 people per 1 sheep</button>
        <button class="incorrect">1 person per 1 sheep</button>
        <button class="incorrect">1 person per 3 sheep</button>
        <button class="correct">1 person per 6 sheep</button>
        <p class="feedback"></p>
    </section>

    <section class="free-response">
        <h2>Part 2: Free Response</h2>
        <hr>
        <h3>In which country is it illegal to own only one guinea pig, as a lone guinea pig might get lonely?</h3>
        <input type="text" id="free-response-input" />
        <button id="check-answer">Check Answer</button>
        <p class="feedback"></p>
    </section>
</body>
</html>
```

## 📤 Expected Output

After opening the page in a browser, the user can click any multiple-choice button to receive immediate feedback: the selected button turns green with "Correct!" displayed if it was the right answer, or red with "Incorrect" displayed otherwise. Similarly, typing an answer into the free-response field and clicking "Check Answer" turns the input field green with "Correct!" if the typed answer matches, or red with "Incorrect" otherwise.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Building a Webpage with HTML** – I learned how to structure interactive content using semantic elements such as `h3` headings, `button` elements, and `input` fields, and how to organize related content within `div` containers.
- **Selecting Elements with the DOM API** – I practiced using `document.querySelectorAll` to select every element matching a given class (e.g., all `.correct` or `.incorrect` buttons) and looping over the resulting collection to attach behavior to each one individually.
- **Event-Driven Programming in JavaScript** – I gained hands-on experience with event-driven programming, attaching `click` event listeners to respond to user interactions rather than running code in a fixed, linear sequence, a significant shift from the procedural C and Python programs written in earlier problem sets.
- **Manipulating the DOM Dynamically** – I learned how to change an element's appearance and content at runtime using JavaScript, specifically by setting `style.backgroundColor` to update a button's or input field's color and `innerHTML` to insert feedback text into the page.
- **Ensuring the DOM Is Ready** – I understood the purpose of wrapping JavaScript logic in a `DOMContentLoaded` event listener, ensuring that scripts attempting to select and modify page elements only run after those elements actually exist in the DOM.
- **Navigating Parent-Child Relationships** – I practiced using `parentElement` combined with `querySelector` to locate a related element (the feedback paragraph) relative to the element that triggered an event, rather than relying on globally unique IDs for every piece of feedback text.
- **Comparing Event-Handling Approaches** – I compared two different ways of wiring up interactivity — attaching event listeners programmatically in JavaScript versus using inline `onclick` HTML attributes — and considered the trade-offs in readability, separation of concerns, and maintainability between the two approaches.
- **Local Development Workflow** – I learned how to use a simple local HTTP server (`http-server`) to preview and test a static webpage in a browser, a common step in front-end web development before deploying a page more broadly.
- **Manual, Interactive Testing** – Since this problem had no automated `check50` correctness checks, I practiced thorough manual testing, deliberately trying both correct and incorrect answers for every question to confirm the page behaved as expected in every case.
- **Submitting Work** – I learned how to properly submit a completed front-end assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 8: Trivia](https://cs50.harvard.edu/x/psets/8/trivia/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
