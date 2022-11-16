
# User Configuration Global variables:

# For testing purposes, where no real serial device is plugged in, set to False; set to True to actually communicate
# over a plugged-in serial device.
REAL_SERIAL = True
LOGGING_ON = True # for logging data to a file
#LOGGING_ON = False
LOG_FOLDER = './logs/'
EXIT_COMMAND = "exit" # Command to exit this program
# Default serial settings used when not specified at the command line:
port = 'COM4'
baudrate = 115200


