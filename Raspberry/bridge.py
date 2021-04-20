# DEVICE_ID table:
# 0x01 | servo-motor
# 0x02 | drive motor
# 0x0A | left range sensor
# 0x0B | right range sensor

# scheme of data for sending to controller:
# 1 byte - DEVICE_ID
# 2 byte - DATA (if requied)

# scheme of data for getting from controller:
# 2 byte - DATA (if requied)

import smbus
import time

address = 0x04
servo = 0x01
drive_motor = 0x02
left_sensor = 0x0A
right_sensor = 0x0B

bus = smbus.SMBus(1)

def get_sensor_state(port):
    time.sleep(0.005)
    bus.write_byte(address, port)
    bus.write_byte(address, 0)
    time.sleep(0.01)
    return bus.read_byte(address)

def set_servo_angle(angle):
    bus.write_byte(address, servo)
    bus.write_byte(address, angle)

def set_motor_power(speed):
    bus.write_byte(address, drive_motor)
    bus.write_byte(address, speed)

def close():
    bus.close()