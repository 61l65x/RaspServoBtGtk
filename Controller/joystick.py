from time import sleep
import RPi.GPIO as GPIO

# Set up BCM GPIO numbering.
GPIO.setmode(GPIO.BCM)
# Set up input pins.
SENSOR_1_INPUT = 22
SENSOR_2_INPUT = 23
GPIO.setup(SENSOR_1_INPUT, GPIO.IN)
GPIO.setup(SENSOR_2_INPUT, GPIO.IN)

# Initiate the loop.
while True:
    # Get signals from Arduino as digital input values.
    SENSOR_1_VALUE = GPIO.input(SENSOR_1_INPUT)
    SENSOR_2_VALUE = GPIO.input(SENSOR_2_INPUT)
    
    # Print values.
    print(SENSOR_1_VALUE)
    print(SENSOR_2_VALUE)
    
    # Define conditions:
    # ...
    # ...
    # ...
        
    sleep(1)