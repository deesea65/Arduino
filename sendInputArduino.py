
import serial
from time import sleep

ser = serial.Serial('/dev/ttyACM0', 9600)

#  change this to get keyboard input of number

print "Sending 3"
ser.write('3')
sleep(3)
print "sending 5"
ser.write('5')





