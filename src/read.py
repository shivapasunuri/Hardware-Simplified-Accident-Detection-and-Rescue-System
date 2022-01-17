from serial.serialwin32 import Serial
from twilio.rest import Client
import serial
import time
import sconf

fromnum = sconf.fromnum
tonum = sconf.tonum
account_sid = sconf.account_sid
auth_token = sconf.auth_token
client = Client(account_sid, auth_token)
arduino = serial.Serial('COM4', 9600)
time.sleep(0.2)
while True:
    for i in range(1):
        b = arduino.readline()
        string_n = b.decode()
        coors = string_n.rstrip()
        print(coors)
        message = client.messages.create(
            from_=fromnum, to=tonum,
            body="Emergency!! Possible Accident Detected at location below"
        )
        message = client.messages.create(
            from_=fromnum, to=tonum,
            body=coors
        )
        time.sleep(3)

arduino.close()
