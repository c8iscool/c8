import os
import string

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# makes sure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
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
    return render_template("index.html")

@app.route("/footprint", methods=["GET", "POST"])
@login_required
def footprint():
    if request.method == "GET":
        rows = db.execute("SELECT date, SUM(milesTraveled), SUM(meatEaten), SUM(Total) FROM footprints WHERE user_id = :user_id GROUP BY date", user_id = session["user_id"])

    items = []
    for row in rows:
        if row["SUM(Total)"]>0:
            items.append(row)
    tot = range(len(rows))

    return render_template("footprint.html", rows=rows, tot=tot)

@app.route("/scoreboard", methods=["GET", "POST"])
@login_required
def scoreboard():
    if request.method == "GET":
        names = db.execute("SELECT * FROM users")
        total = db.execute("SELECT * FROM footprints ORDER BY Total DESC")

    tot = range(len(names))

    return render_template("scoreboard.html", names=names, total=total, tot=tot)

@app.route("/input", methods=["GET", "POST"])
@login_required
def input():
    if request.method == "POST":
        if not request.form.get("activity"):
            return apology("invalid activity", 400)
        elif not request.form.get("amount"):
            return apology("invalid amount", 400)

        #allows user to input their activity with how much they consumed
        user_id = session["user_id"]
        activity = str(request.form.get("activity")).lower()
        amount = float(request.form.get("amount"))

        #calculates carbon footprint
        Total = 0.0
        airMiles = 0.00
        meatEaten = 0.00
        carMiles = 0.00
        emissionTransport = 0.00
        emissionMeat = 0.00

        if activity == "car":
            Total += float(0.411*(amount))
            emissionTransport += float(0.411*amount)
            carMiles = amount
        if activity == "air":
            Total += float(24.04*amount)
            emissionTransport += float(24.04*amount)
            airMiles = amount
        if activity == "beef":
            Total += float(13.3*amount)
            emissionMeat += float(13.3*amount)
            meatEaten += amount
        if activity == "cheese":
            Total += float(13.5*amount)
            emissionMeat += float(13.5*amount)
            meatEaten += amount
        if activity == "lamb":
            Total += 39.2*amount
            emissionMeat += 39.2*amount
            meatEaten += amount

        milesTraveled = carMiles + airMiles

        rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=user_id)

        #puts into table
        db.execute("INSERT INTO footprints (user_id, emissionTransport, emissionMeat, meatEaten, milesTraveled, Total) VALUES (:user_id, :emissionTransport, :emissionMeat, :meatEaten, :milesTraveled, :Total)",
                   user_id=user_id, emissionTransport=emissionTransport, emissionMeat=emissionMeat, meatEaten=meatEaten, milesTraveled=milesTraveled, Total=Total)
        db.execute("UPDATE users SET emission = :emission WHERE id=:user_id", emission=Total, user_id=user_id)
        return render_template("input.html")

    else:
        return render_template("input.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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


@app.route("/cost", methods=["GET", "POST"])
@login_required
def cost():
    if request.method == "POST":

        #checks what interactions have occurred
        if not request.form.get("activity"):
            return apology("missing activity", 400)

        activity = str(request.form.get("activity"))
        cost = 0
        unit = 0
        name = activity
        if name == "cheese":
            cost = 13.5
            unit = "kilogram"
        if name == "car":
            cost = 0.411
            unit = "mile"
        if name == "air":
            cost = 24.04
        if name == "beef":
            cost = 27
            unit = "kilogram"
        if name == "lamb":
            cost = 39.2
            unit = "kilogram"

        return render_template("actcost.html", name=name, cost=cost, unit=unit)

    else:
        return render_template("cost.html")

@app.route("/improve")
@login_required
def improve():
    return render_template("improve.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must re-type username", 403)

        # makes sure a password was submitted
        if not request.form.get("password"):
            return apology("must re-type password", 403)
            if len("password")<8:
                return apology("password must be at least 8 characters", 403)

        if not request.form.get("confirmation"):
            return apology("must re-type password", 403)

        if request.form.get("confirmation") != request.form.get("password"):
            return apology("Passwords did not match", 403)

        else:
            username = request.form.get("username")
            password = generate_password_hash(request.form.get("password"))
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username= username, hash = password)
        return redirect("/")
        # Redirect user to home page

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)