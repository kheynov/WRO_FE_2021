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