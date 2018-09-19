import DAN

ServerIP = 'https://DomainName'   #=None:AutoSearch, or ='IP':Connect to this IP
Comm_interval = 15 # unit:second

def profile_init():
    DAN.profile['dm_name']='Model2'
    DAN.profile['d_name']= 'Set2' #DAN.profile['dm_name']+'.'+DAN.get_mac_addr()[-4:]

def odf():  # int only
    return []

def idf():
    return [
       ('Bugs', int),
       ('Moisture1', float),
       ('pH1', float),
       ('UV1', float),
       ('UV2', float),
    ]
