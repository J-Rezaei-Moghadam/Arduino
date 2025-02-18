import serial
import time

ArduinoData=serial.Serial('com4',9600)
print (ArduinoData.readline())

while 1:
    var=5
    if (var=='1'):
        ArduinoData.write('1')
        print("LED is ON")
        time.sleep(1)
    elif (var=='0'):
        ArduinoData.write('0')
        print("LED is OFF")
        time.sleep(1)

    else:
        print("Error: The number must be 0 or 1")
        time.sleep(1)
        
            
    

