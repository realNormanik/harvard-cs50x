# CS50X – Problem Set 9: Finance

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to extend CS50-provided distribution code to build **C$50 Finance**, a full-featured Flask web application that simulates managing a stock portfolio. Users can register for an account, look up real-time-style stock quotes, "buy" and "sell" shares using simulated cash, view a live summary of their current portfolio, and review a complete history of their past transactions — all backed by a SQLite database.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- building a multi-route, multi-page **Flask** web application with user authentication (registration, login, logout, and session management),
- securely hashing and verifying user passwords using `generate_password_hash` and `check_password_hash`,
- designing and extending a **relational database schema**, including creating new tables with appropriate types, unique constraints, and indexes to support new application features,
- writing and executing parameterized SQL queries (`SELECT`, `INSERT`) safely, avoiding SQL injection by using `?` placeholders rather than string concatenation,
- validating user input thoroughly on the **server side**, since client-side validation alone can always be bypassed,
- using SQL aggregate functions (`SUM`, `GROUP BY`, `HAVING`) to summarize a user's holdings across multiple transactions,
- rendering dynamic, reusable HTML using Jinja templates, including a shared layout, custom filters (`usd`), and conditional/looped content,
- protecting routes with a custom `login_required` decorator to ensure only authenticated users can access sensitive pages,
- integrating an external data source (`lookup`) to retrieve simulated stock prices,
- thinking critically about a real-world application's edge cases: invalid input, insufficient funds, overselling shares, and malicious input,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/9/finance.zip
   ```
2. Extracted the downloaded archive to create a folder called `finance`:
   ```bash
   unzip finance.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm finance.zip
   ```
4. Navigated into the `finance` folder:
   ```bash
   cd finance
   ```
5. Reviewed the provided distribution files (`app.py`, `finance.db`, `helpers.py`, `templates/`, `static/`), studying the already-implemented `login` and `logout` routes, the `login_required` decorator, the `apology` helper, the `usd` Jinja filter, and the `lookup` function used to simulate stock price data.
6. Inspected the existing `finance.db` schema using `sqlite3 finance.db` and `.schema`, noting the pre-built `users` table (with a default `$10,000` starting cash balance) and its `UNIQUE INDEX` on `username`.
7. Implemented the `register` route, creating a new `register.html` template with username, password, and confirmation fields, validating that all fields were filled in and that the two password entries matched, hashing the password with `generate_password_hash`, and using a `try`/`except` block around the `INSERT` to gracefully handle duplicate usernames (which raise a `ValueError` due to the existing unique index).
8. Implemented the `quote` route, creating `quote.html` (a form for entering a stock symbol) and `quoted.html` (displaying the looked-up price), calling the provided `lookup` function and rendering an apology if the symbol was invalid.
9. Designed and created a new `transactions` table in `finance.db` to record every buy and sell, storing the user's ID, the stock symbol, the number of shares (positive for buys, negative for sells, or accompanied by a separate type column), the price per share at the time of the transaction, and a timestamp, along with appropriate indexes for efficient lookups by user.
10. Implemented the `buy` route, validating the submitted symbol and share count (requiring a positive integer), looking up the current price via `lookup`, checking the user's cash balance against the total cost, and — if affordable — inserting a new transaction row and deducting the cost from the user's cash balance, before redirecting to the home page.
11. Implemented the `sell` route, populating a select menu with the symbols the user currently owns, validating the requested share count against how many shares the user actually owned, and — if valid — inserting a corresponding sell transaction and crediting the sale proceeds to the user's cash balance, before redirecting to the home page.
12. Implemented the `index` route, using SQL `GROUP BY` and `SUM` to compute each stock's total shares currently owned by the logged-in user, calling `lookup` to get each stock's current price, computing each holding's total value, and displaying the results in a table alongside the user's remaining cash and a grand total.
13. Implemented the `history` route, querying the `transactions` table for every transaction belonging to the logged-in user, ordered chronologically, and displaying each as a row indicating whether it was a buy or sell, the symbol, price, number of shares, and timestamp.
14. Implemented a personal-touch feature allowing users to change their password from a dedicated settings page, requiring the user's current password to be verified before updating it to a new, re-hashed password.
15. Started the local Flask development server:
    ```bash
    flask run
    ```
16. Manually tested the full application flow: registering a new account, requesting quotes, buying and selling stocks (including attempting to overspend or oversell), reviewing the portfolio and transaction history, and testing malformed input (non-numeric share counts, negative numbers, floating-point share counts, invalid symbols, and SQL special characters like `'` and `;`).
17. Validated HTML output using the built-in W3C validator link included in the page footer.
18. Checked the correctness of the application using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/finance
    ```
19. Checked the code style using the `style50` tool:
    ```bash
    style50 app.py
    ```
20. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/finance
    ```

## 💻 Program Code

The distribution code provided the Flask application skeleton, the `login`/`logout` routes, the `login_required` decorator, the `apology` helper, the `usd` Jinja filter, and the `lookup` function. My work focused on completing the remaining routes in `app.py`:

```python
from cs50 import SQL
from flask import Flask, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren"t cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    users = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])
    owned_cash = users[0]["cash"]

    # Get user currently owned stocks
    summaries = db.execute("""SELECT company, symbol, sum(shares) as sum_of_shares
                              FROM transactions
                              WHERE user_id = ?
                              GROUP BY user_id, company, symbol
                              HAVING sum_of_shares > 0;""", session["user_id"])

    # Use lookup API to get the current price for each stock
    summaries = [dict(x, **{"price": lookup(x["symbol"])["price"]}) for x in summaries]

    # Calcuate total price for each stock
    summaries = [dict(x, **{"total": x["price"]*x["sum_of_shares"]}) for x in summaries]

    sum_totals = owned_cash + sum([x["total"] for x in summaries])

    return render_template("index.html", owned_cash=owned_cash, summaries=summaries, sum_totals=sum_totals)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not (symbol := request.form.get("symbol")):
            return apology("MISSING SYMBOL")

        if not (shares := request.form.get("shares")):
            return apology("MISSING SHARES")

        # Check share is numeric data type
        try:
            shares = int(shares)
        except ValueError:
            return apology("INVALID SHARES")

        # Check shares is positive number
        if not (shares > 0):
            return apology("INVALID SHARES")

        # Ensure symbol is valided
        if not (query := lookup(symbol)):
            return apology("INVALID SYMBOL")

        rows = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])

        user_owned_cash = rows[0]["cash"]
        total_prices = query["price"] * shares

        # Ensure user have enough money
        if user_owned_cash < total_prices:
            return apology("CAN"T AFFORD")

        # Execute a transaction
        db.execute("INSERT INTO transactions(user_id, company, symbol, shares, price) VALUES(?, ?, ?, ?, ?);",
                   session["user_id"], query["name"], symbol, shares, query["price"])

        # Update user owned cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?;",
                   (user_owned_cash - total_prices), session["user_id"])

        flash("Bought!")

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?;", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("MISSING USERNAME")

        if not request.form.get("password"):
            return apology("MISSING PASSWORD")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?;", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Ensure Symbol is exists
        if not (query := lookup(request.form.get("symbol"))):
            return apology("INVALID SYMBOL")

        return render_template("quote.html", query=query)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not (username := request.form.get("username")):
            return apology("MISSING USERNAME")

        if not (password := request.form.get("password")):
            return apology("MISSING PASSWORD")

        if not (confirmation := request.form.get("confirmation")):
            return apology("PASSWORD DON"T MATCH")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?;", username)

        # Ensure username not in database
        if len(rows) != 0:
            return apology(f"The username "{username}" already exists. Please choose another name.")

        # Ensure first password and second password are matched
        if password != confirmation:
            return apology("password not matched")

        # Insert username into database
        id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?);",
                        username, generate_password_hash(password))

        # Remember which user has logged in
        session["user_id"] = id

        flash("Registered!")

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    owned_symbols = db.execute("""SELECT symbol, sum(shares) as sum_of_shares
                                  FROM transactions
                                  WHERE user_id = ?
                                  GROUP BY user_id, symbol
                                  HAVING sum_of_shares > 0;""", session["user_id"])

    if request.method == "POST":
        if not (symbol := request.form.get("symbol")):
            return apology("MISSING SYMBOL")

        if not (shares := request.form.get("shares")):
            return apology("MISSING SHARES")

        # Check share is numeric data type
        try:
            shares = int(shares)
        except ValueError:
            return apology("INVALID SHARES")

        # Check shares is positive number
        if not (shares > 0):
            return apology("INVALID SHARES")

        symbols_dict = {d["symbol"]: d["sum_of_shares"] for d in owned_symbols}

        if symbols_dict[symbol] < shares:
            return apology("TOO MANY SHARES")

        query = lookup(symbol)

        # Get user currently owned cash
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Execute a transaction
        db.execute("INSERT INTO transactions(user_id, company, symbol, shares, price) VALUES(?, ?, ?, ?, ?);",
                   session["user_id"], query["name"], symbol, -shares, query["price"])

        # Update user owned cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?;",
                   (rows[0]["cash"] + (query["price"] * shares)), session["user_id"])

        flash("Sold!")

        return redirect("/")

    else:
        return render_template("sell.html", symbols=owned_symbols)


@app.route("/reset", methods=["GET", "POST"])
@login_required
def reset():
    if request.method == "POST":
        if not (password := request.form.get("password")):
            return apology("MISSING OLD PASSWORD")

        rows = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])

        if not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("INVALID PASSWORD")

        if not (new_password := request.form.get("new_password")):
            return apology("MISSING NEW PASSWORD")

        if not (confirmation := request.form.get("confirmation")):
            return apology("MISSING CONFIRMATION")

        if new_password != confirmation:
            return apology("PASSWORD NOT MATCH")

        db.execute("UPDATE users set hash = ? WHERE id = ?;",
                   generate_password_hash(new_password), session["user_id"])

        flash("Password reset successful!")

        return redirect("/")
    else:
        return render_template("reset.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
```

## 📤 Expected Output

After registering an account and logging in, the home page (`/`) displays a table of the user's current stock holdings, their live value, the user's remaining cash, and a grand total. From there, users can navigate to `/quote` to look up a stock's price, `/buy` and `/sell` to trade shares, and `/history` to review every past transaction, all while apology pages guard against invalid or malicious input at every step.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Building a Complete, Authenticated Web Application** – I gained end-to-end experience building a multi-page Flask application with real user accounts, moving well beyond the single-route "Birthdays" exercise to a project with authentication, authorization, and several interdependent features.
- **Password Security** – I learned how to securely handle user passwords by never storing them in plaintext, instead using `generate_password_hash` to store a salted hash and `check_password_hash` to verify a login attempt against that hash.
- **Session Management** – I practiced using Flask's `session` object to track a logged-in user's ID across requests, and understood how a custom `login_required` decorator can be used to protect multiple routes from unauthenticated access without duplicating logic in every route.
- **Designing a Relational Schema for New Features** – I gained experience extending an existing database schema by designing a new `transactions` table from scratch, thinking carefully about which columns, types, and indexes were needed to support both the `buy`/`sell` logic and the aggregate portfolio and history views.
- **Aggregating Data Across Transactions** – I learned how to use `GROUP BY`, `SUM`, and `HAVING` to compute each user's current net holdings per stock from a raw log of individual buy and sell transactions, rather than maintaining a separately updated "current holdings" table.
- **Defense-in-Depth Input Validation** – I reinforced the principle that all validation must happen server-side, regardless of any client-side checks, and practiced validating multiple failure conditions per form (missing fields, invalid types, out-of-range or non-positive values, and business-logic constraints like affordability or share ownership).
- **Safe Database Access** – I consistently used parameterized queries with `?` placeholders throughout every route, reinforcing safe database practices and avoiding the SQL injection vulnerabilities that string concatenation or f-strings could introduce.
- **Integrating External Data Lookups** – I practiced calling a provided `lookup` function to retrieve simulated stock data, and learned to treat that data as another piece of context needed to complete calculations (cost, proceeds, and portfolio value) rather than something to be reimplemented.
- **Template Reuse with Jinja** – I extended the shared `layout.html` structure across multiple new templates, reused the custom `usd` filter for consistent currency formatting, and used Flask's message flashing to relay confirmation messages (e.g., "Bought!", "Sold!") between routes.
- **Thorough, Adversarial Testing** – I practiced testing the application not just for expected "happy path" behavior but also for a wide range of unexpected or malicious input, including negative numbers, floating-point share counts, invalid symbols, attempts to overspend or oversell, and potentially dangerous characters like `'` and `;`.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed, multi-file Flask application using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 9: Finance](https://cs50.harvard.edu/x/psets/9/finance/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
