# Proizvoljno smo odredili "auth" datoteku koja će nam sadržavati 
# one stranice gdje korisnik unosi neke svoje podatke
# (autentificira se)

from flask import Blueprint, render_template, request

auth = Blueprint('auth', __name__)

@auth.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
    return render_template("login.html")

@auth.route('/sign_up', methods=['GET', 'POST'])
def sign_up():
    if request.method == 'POST':
        email = request.form.get('email')
        first_name = request.form.get('first_name')
        last_name = request.form.get('last_name')
        password1 = request.form.get('password1')
        password2 = request.form.get('password2')
        print(email, first_name, last_name, password1, password2)
    return render_template("sign_up.html")
