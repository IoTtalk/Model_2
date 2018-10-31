import DAN

ServerIP = 'https://DomainName'  #or 'http://IP:9999'
Comm_interval = 15 # unit:second

def profile_init():
    DAN.profile['dm_name']='Model2'
    DAN.profile['d_name']= 'SetX'

def odf():  # int only
    return []

def idf():
    return [
       ('Bugs', int),
       ('Moisture1', float),
       ('SoilEC-I', float),
       ('SoilTemp-I', float),
       ('UV1', float),
       ('UV2', float),
       ('pH1', float),
    ]
