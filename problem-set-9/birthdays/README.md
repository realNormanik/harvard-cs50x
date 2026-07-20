# CS50X – Problem Set 9: Birthdays

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It marks the introduction of **Flask**, a Python web framework, combined with a **SQLite** database to build a full, dynamic web application. The goal was to extend CS50-provided distribution code to build a web application that lets users keep track of friends' birthdays: the homepage displays every stored birthday in a table, and a form allows users to submit a new name, month, and day, which is then saved to the database and immediately reflected on the page.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- setting up and running a basic **Flask** web application, including routing and handling both `GET` and `POST` requests on the same route,
- connecting to and querying a **SQLite** database from within a Python web application using the `cs50` library's `SQL` class,
- rendering dynamic HTML content using **Jinja templating**, including looping over Python data structures directly within an HTML template,
- building an HTML `<form>` to collect user input, and correctly configuring its `action` and `method` attributes to submit data via `POST`,
- reading submitted form data in Flask using `request.form.get`,
- performing **server-side validation** of user input (checking for missing values, invalid types, and out-of-range values) before inserting data into a database,
- using parameterized SQL queries (with `?` placeholders) to safely insert user-submitted data and help prevent SQL injection,
- redirecting the browser back to a route after processing a form submission, to avoid duplicate submissions on page refresh,
- the tools provided by CS50 for manually testing a Flask application, as well as submitting the solution (`submit50`), given that this problem has no automated `check50`.

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/9/birthdays.zip
   ```
2. Extracted the downloaded archive to create a folder called `birthdays`:
   ```bash
   unzip birthdays.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm birthdays.zip
   ```
4. Navigated into the `birthdays` folder:
   ```bash
   cd birthdays
   ```
5. Reviewed the provided distribution files (`app.py`, `birthdays.db`, `static/styles.css`, `templates/index.html`), understanding the existing Flask route structure, the pre-populated SQLite database and its `birthdays` table (with `id`, `name`, `month`, and `day` columns), and the two `TODO` markers left to complete.
6. Implemented the `GET` request handling in `app.py`, querying the database for all rows in the `birthdays` table with `SELECT * FROM birthdays`, and passing the resulting list of dictionaries to `index.html` via `render_template`.
7. Implemented the birthday table rendering in `index.html`, using a Jinja `{% for %}` loop to iterate over the `birthdays` variable and render each entry as a table row with the person's name and their month/day birthday.
8. Added an HTML `<form>` to `index.html`, with input fields for a name, a birthday month, and a birthday day, using appropriate `type`, `placeholder`, `min`, and `max` attributes for basic client-side validation, and configured the form's `action="/"` and `method="post"` attributes.
9. Implemented the `POST` request handling in `app.py`, reading the submitted `name`, `month`, and `day` values with `request.form.get`, and adding server-side validation to check for missing values, non-numeric `month`/`day` values (using a `try`/`except` around `int()`), and out-of-range values (month outside 1–12, day outside 1–31), redirecting back to `/` if any check failed.
10. Completed the `POST` handler by inserting the validated data into the database using a parameterized `INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)` query, then redirecting the user back to `/` so the updated birthday list would be displayed via a fresh `GET` request.
11. Started the local Flask development server:
    ```bash
    flask run
    ```
12. Manually tested the application by submitting several new birthdays through the form, confirming they appeared correctly in the table, and testing edge cases such as submitting an empty field, a non-numeric month/day, and an out-of-range value to confirm the server-side validation correctly rejected them.
13. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/birthdays
    ```

## 💻 Program Code

The distribution code provided the overall Flask application skeleton, the database connection setup, and the base HTML template. My work focused on completing the two `TODO` sections in `app.py` and adding the missing form and rendering logic in `index.html`:

**`app.py`**
```python
from cs50 import SQL
from flask import Flask, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Access form data
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Basic validation
        if not name or not month or not day:
            return redirect("/")

        try:
            month = int(month)
            day = int(day)
        except ValueError:
            return redirect("/")

        if month < 1 or month > 12 or day < 1 or day > 31:
            return redirect("/")

        # Insert the user's entry into the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:
        # Query for all birthday entries
        birthdays = db.execute("SELECT * FROM birthdays")

        # Display the entries in the database on index.html
        return render_template("index.html", birthdays=birthdays)
```

**`templates/index.html`** (relevant excerpt)
```html
<!DOCTYPE html>

<html lang="en">
    <head>
        <link href="https://fonts.googleapis.com/css2?family=Montserrat:wght@500&display=swap" rel="stylesheet">
        <link href="/static/styles.css" rel="stylesheet">
        <title>Birthdays</title>
    </head>
    <body>
        <div class="header">
            <h1>Birthdays</h1>
        </div>
        <div class="container">
            <div class="section">

                <h2>Add a Birthday</h2>
                <form action="/" method="post">
                    <input name="name" placeholder="Name" type="text" required>
                    <input name="month" placeholder="Month" type="number" min="1" max="12" required>
                    <input name="day" placeholder="Day" type="number" min="1" max="31" required>
                    <input type="submit" value="Add Birthday">
                </form>
            </div>

            <div class="section">

                <h2>All Birthdays</h2>
                <table>
                    <thead>
                        <tr>
                            <th>Name</th>
                            <th>Birthday</th>
                        </tr>
                    </thead>
                    <tbody>
                        <table>
                            <tr>
                                <th>Name</th>
                                <th>Birthday</th>
                            </tr>

                            {% for birthday in birthdays %}

                            <tr>
                                <td>{{ birthday.name }}</td>
                                <td>{{ birthday.month }}/{{ birthday.day }}</td>
                            </tr>

                            {% endfor %}
                        </table>
                    </tbody>
                </table>
            </div>
        </div>
    </body>
</html>
```

## 📤 Expected Output

Running `flask run` and opening the application in a browser displays a table of all birthdays currently stored in `birthdays.db`, along with a form to add a new birthday. Submitting the form with a valid name, month, and day inserts a new row into the database and immediately shows the updated list, including the newly added entry.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Building a Flask Web Application** – I gained hands-on experience with Flask's routing system, learning how a single route (`/`) can handle both `GET` and `POST` requests differently depending on `request.method`, a pattern common to many simple web forms.
- **Server-Side Rendering with Jinja** – I learned how to use Jinja templating within an HTML file to loop over server-side data (`{% for birthday in birthdays %}`) and interpolate values (`{{ birthday.name }}`), dynamically generating HTML content based on data retrieved from a database.
- **Connecting a Web App to a Database** – I practiced using the `cs50` library's `SQL` class to execute queries against a SQLite database directly from Python code running inside a Flask route, bridging the web-application layer with persistent data storage.
- **Handling and Validating Form Data** – I learned how to read submitted form fields using `request.form.get`, and practiced layering multiple validation checks (presence, type conversion, and range checking) before trusting user input enough to insert it into a database.
- **Parameterized Queries** – I reinforced the importance of using parameterized SQL queries with `?` placeholders (rather than directly formatting user input into a query string) as a safeguard against SQL injection, a critical security practice when handling any form of user-submitted data.
- **The Post/Redirect/Get Pattern** – I learned why redirecting back to `/` after processing a `POST` request (rather than directly rendering a response) is good practice, since it prevents the browser from re-submitting the same form data if the user refreshes the page.
- **Designing Usable Forms** – I practiced adding thoughtful touches to a form beyond the bare minimum, such as `placeholder` text and `min`/`max` attributes on numeric fields, to guide users toward providing valid input before the request even reaches the server.
- **Separating Client-Side and Server-Side Validation** – I gained an appreciation for why both client-side validation (HTML attributes like `min`/`max`) and server-side validation (Python checks in `app.py`) are necessary together, since client-side checks can be bypassed but still improve the everyday user experience.
- **Manual, End-to-End Testing** – Since this problem had no automated `check50` tests, I practiced thorough manual testing of the full request/response cycle, submitting both valid and deliberately invalid data to confirm the application behaved correctly and safely in every case.
- **Submitting Work** – I learned how to properly submit a completed, multi-file Flask application using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 9: Birthdays](https://cs50.harvard.edu/x/psets/9/birthdays/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
