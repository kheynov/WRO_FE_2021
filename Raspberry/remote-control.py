import eventlet
import socketio
import json
import bridge

sio = socketio.Server()
app = socketio.WSGIApp(sio, static_files={
    '/': 'index.html'
})

@sio.on('inputs')
def inputs(sid, data):
    e = json.loads(data)
    print(e)

    if e['dir'] == 'forward':
        if e['state'] == True:
            bridge.set_motor_power(100)
        if e['state'] == False:
            bridge.set_motor_power(0)

    if e['dir'] == 'left':
        if e['state'] == True:
            bridge.set_servo_angle(0)
        if e['state'] == False:
            bridge.set_motor_power(45)

    if e['dir'] == 'right':
        if e['state'] == True:
            bridge.set_servo_angle(90)
        if e['state'] == False:
            bridge.set_motor_power(45)


if __name__ == '__main__':
    eventlet.wsgi.server(eventlet.listen(('', 5000)), app)