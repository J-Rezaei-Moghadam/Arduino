import serial
import keyboard
data = serial.Serial('com4',9600)
while 1:
        if(data.inWating()>0):
            input_data = data.readline()
            print (input_data)
            input_data = str(input_data)
            if "Play/Pause" in input_data:
                keyboard.press_and_release('space')
            elif "Forward" in input_data:
                keyboard.press_and_release('ctrl+right')
