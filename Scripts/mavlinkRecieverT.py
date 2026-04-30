import serial
import time
from pymavlink import mavutil
import threading

running = True
started = True
port_recv = 'COM8'
mav = mavutil.mavlink.MAVLink(None)
ser_in = serial.Serial(port_recv, 57600)
heartbeatD = []

def keyboard_listener():
    global running
    while True:
        cmd = input().strip()  # test için
        if cmd == "q":
            running = False
            print("Reciever node is stoped")
            ser_in.close()
            break

threading.Thread(target=keyboard_listener, daemon=True).start()

while running:
    if started:
        print("Reciever node is running")
        started = False
    
    time.sleep(0.5)
    if ser_in.in_waiting > 0:
        data = ser_in.read(ser_in.in_waiting)
        print(f"Received {len(data)} bytes from {port_recv} data is {data}")
        for b in data:
            msg = mav.parse_char(bytes([b]))
            if msg:
                sysId = msg.get_srcSystem()
                compId = msg.get_srcComponent()
                print(f"sysId: {sysId}, compId: {compId}")
                msgId = msg.get_msgId()
                # print(f"message Id: {msgId}")
                gyroP = 0; accelP = 0; magnP = 0; absPrsP = 0; diffPrsP = 0; gpsP = 0
                match msgId:
                    case 0:
                        print(f"Mesaj yakalandı: {msg.get_type()}, ID: {msgId}")
                        heartbeatD = msg.to_dict()
                        print(f"Mesaj içeriği: {heartbeatD}") #heartbeatD['type']
                    case 1:
                        print(f"Mesaj yakalandı: {msg.get_type()}, ID: {msgId}")
                        sysStatD = msg.to_dict()
                        print(f"Mesaj içeriği: {sysStatD}")
                        print(f"voltage: {sysStatD['voltage_battery']/1000}V")
                        if sysStatD['onboard_control_sensors_present'] & 1:
                            gyroP = 1
                        if sysStatD['onboard_control_sensors_present'] & 2:
                            accelP = 1
                        if sysStatD['onboard_control_sensors_present'] & 4:
                            magnP = 1
                        if sysStatD['onboard_control_sensors_present'] & 8:
                            absPrsP = 1
                        if sysStatD['onboard_control_sensors_present'] & 16:
                            diffPrsP = 1
                        if sysStatD['onboard_control_sensors_present'] & 32:
                            gpsP = 1
                        print(f"Sensors Present: Gyro: {gyroP}, Accel: {accelP}, Magn: {magnP}, Abs Press: {absPrsP}, Diff Press: {diffPrsP}, GPS: {gpsP}")
                    case 147:
                        print(f"Mesaj yakalandı: {msg.get_type()}, ID: {msgId}")
                        batStatD = msg.to_dict()
                        print(f"Mesaj içeriği: {batStatD}")
                    case 30:
                        print(f"Mesaj yakalandı: {msg.get_type()}, ID: {msgId}")
                        attitudeD = msg.to_dict()
                        print(f"Mesaj içeriği: {attitudeD}")
                    case 24:
                        print(f"Mesaj yakalandı: {msg.get_type()}, ID: {msgId}")
                        gpsStatD = msg.to_dict()
                        print(f"Mesaj içeriği: {gpsStatD}")
                    

if __name__ == "__main__":
    keyboard_listener()