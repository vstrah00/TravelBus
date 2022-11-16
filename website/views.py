# Proizvoljno smo odredili "views" datoteku koja će nam sadržavati 
# one stranice sa kojima korisnik ne interaktira

from flask import Blueprint, render_template

views = Blueprint('views', __name__)

# Ovdje povezujemo početnu(home) stranicu sa html kodom koji smo odredili za nju
# pomoću naredbe render_template()
@views.route('/')
def home():
    return render_template("home.html")