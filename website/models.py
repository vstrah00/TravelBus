from . import db
from flask_login import UserMixin
from sqlalchemy.sql import func

class User(db.Model):
    id=db.Column(db.Integer, primary_key=True)
    first_name=db.Column(db.String(50))
    last_name=db.Column(db.String(50))
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(50))
    is_admin = db.Column(db.Boolean)
    creation_date = db.Column(db.DateTime(timezone=True), default = func.now()) 

#model entiteta: prijevozna kompanija
class Transport_company(db.Model):                      
    id=db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True)
    phone_number = db.Column(db.String(50))
    trips = db.relationship('Trip')                     #povezuje prijevoznu kompaniju sa njenim vožnjama(cijelom listom)

 #model entiteta: vožnja(trip)
class Trip(db.Model):                             
    id=db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(50))
    is_admin = db.Column(db.Boolean)
    creation_date = db.Column(db.DateTime(timezone=True), default = func.now()) 
    id_trip=db.Column(db.Integer, db.ForeignKey('transport_company.id'))            #kaže koja kompanija organizira vožnju
