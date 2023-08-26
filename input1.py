import serial
from time import sleep

#
#get input from user and send to arduino
#
#ser = ""

def setup_serial():
    #ser = serial.Serial('/dev/ttyACM0', 9600)
    print "setting up serial comms"


def get_temp():
    print "request temperature"
    ser.write('temp,,') # what is the terminator char for a string
    # request a temperature reading from arduino
    # read reply from arduino
    # display result
    sleep(1)
    result = ser.readline()
    print result



def get_light():
    print "send light command"
    #ser.write('light,on,1')
    # need to determine which light function is required
    # which light and on or off
    # send full string to arduino
    light_no = raw_input("which light ?")
    status = raw_input("on or off ?")
    print "sending: light,", light_no,",",status
    cmd = "light,%s,%s" % (status, light_no)
    ser.write(cmd)

def get_photo():
    print "send photosensor command"
    # send full string to arduino
    cmd = "photo,,"
    ser.write(cmd)
    sleep(1)
    result = ser.readline()
    print result

        
def cmd_exit():
    print "quitting"
    exit()

def cmd_help():
    for i in sorted(takeaction.keys()):
        print i




def errhandler():
    print "input not recognised"
    cmd_help()


takeaction = {
    "temp"  : get_temp,
    "light" : get_light,
    "exit"  : cmd_exit,
    "help"  : cmd_help,
    "photo" : get_photo
    }

setup_serial()
ser = serial.Serial('/dev/ttyACM0', 9600)
print "setting up serial comms"

while 1: 
    cmd_text = raw_input(" Enter a command ")
    takeaction.get(cmd_text, errhandler)()
    #process input


