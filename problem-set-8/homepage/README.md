# CS50X – Problem Set 8: Homepage

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to design and build a personal, multi-page **homepage** from scratch using **HTML, CSS, and JavaScript**, integrating the **Bootstrap** front-end framework for styling and layout. Unlike earlier, more prescriptive problem sets, this task was intentionally open-ended: the content, structure, and design were entirely up to the student, so long as a specific set of technical requirements around structure, styling, and interactivity were met.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- structuring a multi-page website using semantic HTML, with consistent navigation linking every page to every other page,
- using a broad, varied set of HTML tags to represent different kinds of content meaningfully,
- writing and organizing custom CSS in a separate stylesheet, using a mix of tag, class, and ID selectors,
- integrating a third-party front-end framework (**Bootstrap**) via CDN links to speed up and improve the site's visual design,
- adding interactivity to a webpage using JavaScript, beyond the event-handling techniques introduced in the earlier "Trivia" exercise,
- designing a site with **responsive design** in mind, ensuring it looks reasonable on both desktop and mobile viewports,
- validating HTML markup for correctness using an external markup validation service,
- documenting technical choices clearly in a plain-text specification file,
- the tools provided by CS50 for submitting the solution (`submit50`), given that this problem, like "Trivia," has no automated `check50` due to the personalized nature of the content.

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/8/homepage.zip
   ```
2. Extracted the downloaded archive to create a folder called `homepage`:
   ```bash
   unzip homepage.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm homepage.zip
   ```
4. Navigated into the `homepage` folder:
   ```bash
   cd homepage
   ```
5. Reviewed the provided starter files (`index.html` and `styles.css`) before planning the site's overall structure and content.
6. Planned out at least four distinct HTML pages centered around a personal theme (introducing myself, a hobby, and other interests), ensuring `index.html` served as the site's main landing page.
7. Built out each page's markup, deliberately using a varied set of HTML tags (well beyond `<html>`, `<head>`, `<body>`, and `<title>`) to represent content meaningfully, such as navigation, headings, lists, images, and forms.
8. Added a consistent navigation menu across every page, ensuring that any page could be reached from any other page via one or more hyperlinks.
9. Integrated Bootstrap into each page's `<head>` by including its CDN-hosted CSS and JavaScript files, and applied one or more Bootstrap components (such as a navbar, cards, or a carousel) to improve the site's visual polish.
10. Linked a custom stylesheet, `styles.css`, below the Bootstrap CSS link, and wrote at least five distinct CSS selectors (tag, class, and ID selectors) covering at least five different CSS properties, taking care to let styles cascade from parent elements where appropriate rather than repeating declarations unnecessarily.
11. Added one or more JavaScript-driven interactive features (such as a button-triggered alert, a recurring visual effect, or dynamic form behavior) to make the site more engaging.
12. Started a local development server to preview the site while working on it:
    ```bash
    http-server
    ```
13. Used Chrome DevTools' device toolbar (`Ctrl+Shift+M` / `Cmd+Shift+M`) to test and adjust the site's appearance on simulated mobile viewports, in addition to testing on a standard desktop browser window.
14. Validated the HTML on every page using the W3C Markup Validation Service, correcting any warnings or errors that were flagged.
15. Documented the ten HTML tags and five CSS properties used, along with a brief description of how JavaScript and Bootstrap were incorporated, in `specification.txt`.
16. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/homepage
    ```

## 💻 Site Structure

The site was organized into (at minimum) four interlinked pages, each reachable from a shared navigation menu:

```
homepage/
├── about.html           (personal introduction)
├── contact.html          (a contact or "get in touch" page, e.g., using a form)
├── hobbies.html          (a favorite hobby or extracurricular)
├── index.html          (main landing page)
├── specification.txt      (list of HTML tags, CSS properties, and JS/Bootstrap notes)
└── styles.css            (custom stylesheet)
```

Each page included, in its `<head>`, the Bootstrap CSS and JavaScript CDN links, followed by a link to the custom `styles.css` stylesheet:

```html
<!-- Bootstrap CSS -->
<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/css/bootstrap.min.css"
    integrity="sha384-TX8t27EcRE3e/ihU7zmQxVncDAy5uIKz4rEkgIXeMed4M0jlfIDPvg6uqKI2xXr2" crossorigin="anonymous" />
<!-- Custom CSS -->
<link href="styles.css" rel="stylesheet" />

<!-- Bootstrap JS + dependencies -->
<script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"
    integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/js/bootstrap.bundle.min.js"
    integrity="sha384-ho+j7jyWK8fNQe+A12Hb8AhRq26LrZ/JpcUGGOn+Y7RsweNrtN/tE3MoK7ZeZDyx" crossorigin="anonymous"></script>
```

## 📄 `specification.txt` Structure

The `specification.txt` file listed the technical elements used across the site, following a structure similar to the below:

```
HTML tags used:
1. <nav>
2. <ul> / <li>
3. <img>
4. <section>
5. <form>
6. <label>
7. <input>
8. <footer>
9. <blockquote>
10. <figure> / <figcaption>

CSS properties used:
1. color
2. font-size
3. margin
4. padding
5. background-color

JavaScript: [brief, one-sentence description of the interactive feature implemented]
Bootstrap: [brief, one-sentence description of which Bootstrap component(s) were used]
```

## 📤 Expected Output

Running `http-server` and opening the provided link in a browser displays a personal, multi-page website with consistent navigation between all pages, Bootstrap-enhanced styling, custom CSS applied on top, and at least one interactive JavaScript feature. The layout adapts sensibly when viewed on both desktop and simulated mobile screen sizes.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Multi-Page Site Architecture** – I learned how to structure a website as multiple interlinked HTML pages rather than a single file, and how to design a consistent navigation system so that every page remains reachable from every other page.
- **Meaningful Use of HTML Tags** – I practiced choosing HTML tags based on the semantic meaning of the content they represent (e.g., `<nav>` for navigation, `<figure>` for images with captions, `<form>` for user input) rather than relying on generic containers for everything.
- **Organizing and Scoping CSS** – I gained experience writing CSS across multiple selector types (tag, class, and ID selectors), and learned to take advantage of the "cascading" nature of CSS to apply shared styles at a higher level rather than repeating declarations across individual elements.
- **Integrating a Third-Party Framework** – I learned how to incorporate an external front-end framework (Bootstrap) into a project via CDN links, and how to combine framework-provided styling with my own custom CSS without conflicts, adding polished, pre-built components with relatively little custom code.
- **Client-Side Interactivity Beyond Basic Events** – I extended my JavaScript skills beyond simple click-based feedback (as in the "Trivia" exercise) to implement a feature suited to a general-purpose website, reinforcing how JavaScript can be used to enhance, rather than replace, a page's core HTML content.
- **Responsive Design Considerations** – I practiced testing and adjusting a site's layout for both desktop and mobile viewports using browser developer tools, gaining an appreciation for how a design decision that looks fine on a large screen may need adjustment for smaller ones.
- **HTML Validation** – I learned to use the W3C Markup Validation Service to catch structural or syntactic issues in my HTML that might not be visually obvious but could cause problems for browsers, assistive technologies, or search engines.
- **Working Without Automated Grading** – Since this problem had no `check50` tests, I practiced self-assessing my work against a written specification, paying close attention to details like tag variety, selector count, and code cleanliness that automated tools might not catch, and manually validating my HTML and testing interactivity end to end.
- **Technical Documentation** – I practiced clearly and concisely documenting the technical choices behind my implementation in `specification.txt`, a skill relevant to writing documentation, READMEs, or design notes in real-world software projects.
- **Submitting Work** – I learned how to properly submit a completed, multi-file front-end project using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 8: Homepage](https://cs50.harvard.edu/x/psets/8/homepage/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
