import serial
import time
from pymavlink import mavutil
import threading

running = True

port_send = 'COM7'
mav = mavutil.mavlink.MAVLink(None)
ser_out = serial.Serial(port_send, 57600)

def keyboard_listener():
    global running
    while True:
        cmd = input().strip()  # test için
        if cmd == "q":
            running = False
            print("Reciever node is stoped")
            ser_out.close()
            break

threading.Thread(target=keyboard_listener, daemon=True).start()

while running:
    print("Sender node is running")
    mav.srcSystem = 1
    mav.srcComponent = 2
    
    msgHeartbeat = mavutil.mavlink.MAVLink_heartbeat_message(
        type=mavutil.mavlink.MAV_TYPE_QUADROTOR,
        autopilot=mavutil.mavlink.MAV_AUTOPILOT_ARDUPILOTMEGA,
        base_mode=0,
        custom_mode=0,
        system_status=mavutil.mavlink.MAV_STATE_STANDBY, # Eksik olan 1. parametre
        mavlink_version=3                                 # Eksik olan 2. parametre
    )

    packet = msgHeartbeat.pack(mav)
    print(f"Sending packet to {port_send}...")
    ser_out.write(packet)
    
    present = mavutil.mavlink.MAV_SYS_STATUS_SENSOR_3D_GYRO
    present |= mavutil.mavlink.MAV_SYS_STATUS_SENSOR_3D_ACCEL
    present |= mavutil.mavlink.MAV_SYS_STATUS_SENSOR_GPS
    enabled = present
    health = present

    msgSysStat = mavutil.mavlink.MAVLink_sys_status_message(
        onboard_control_sensors_present = present,
        onboard_control_sensors_enabled = enabled,
        onboard_control_sensors_health = health,
        load = 26, # %0.1 - 26 = %2.6
        voltage_battery = 23462, # mV
        current_battery = 180, # cA => 120cA = 1.2A
        battery_remaining = 89, # %, -1 is unknown
        drop_rate_comm = 0, # %
        errors_comm = 0,
        errors_count1 = 0,
        errors_count2 = 0,
        errors_count3 = 0,
        errors_count4 = 0,
    )

    packet = msgSysStat.pack(mav)
    print(f"Sending packet to {port_send}...")
    ser_out.write(packet)

    msgBat1Stat = mavutil.mavlink.MAVLink_battery_status_message(
        current_consumed = -1,
        energy_consumed = -1,
        temperature = 1624,
        voltages = [23462, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        current_battery = 180,
        id = 0,
        battery_function = mavutil.mavlink.MAV_BATTERY_FUNCTION_AVIONICS,
        type = mavutil.mavlink.MAV_BATTERY_TYPE_LIPO,
        battery_remaining = 89
    )
    
    packet = msgBat1Stat.pack(mav)
    print(f"Sending packet to {port_send}...")
    ser_out.write(packet)

    msgBat2Stat = mavutil.mavlink.MAVLink_battery_status_message(
        current_consumed = -1,
        energy_consumed = -1,
        temperature = 1816,
        voltages = [3462, 3865, 3683, 3245, 0, 0, 0, 0, 0, 0],
        current_battery = 120,
        id = 1,
        battery_function = mavutil.mavlink.MAV_BATTERY_FUNCTION_AVIONICS,
        type = mavutil.mavlink.MAV_BATTERY_TYPE_LIPO,
        battery_remaining = 86
    )
    
    packet = msgBat2Stat.pack(mav)
    print(f"Sending packet to {port_send}...")
    ser_out.write(packet)

    params = {
        "SYSID_THISMAV": 1,
        "TEST_PARAM": 123,
    }

    if ser_out.in_waiting > 0:
        data = ser_out.read(ser_out.in_waiting)
        print(f"Received {len(data)} bytes from {port_send} data is {data}")
        for b in data:
            msg = mav.parse_char(bytes([b]))
            if msg:
                print(msg.get_type())
        
                if msg.get_type() == "PARAM_REQUEST_LIST":
                    msg = mav.param_value_encode(
                        b"TEST_PARAM",
                        123.0,
                        mavutil.mavlink.MAV_PARAM_TYPE_REAL32,
                        2,
                        0
                    )
                    packet = msg.pack(mav)

                    msg1 = mav.param_value_encode(
                        b"SYSID_THISMAV",
                        1.0,
                        mavutil.mavlink.MAV_PARAM_TYPE_REAL32,
                        2,
                        1
                    )
                    packet1 = msg1.pack(mav)
    
                    print(f"Sending packet to {port_send}...")
                    ser_out.write(packet)
                    ser_out.write(packet1)

    time.sleep(0.5)

if __name__ == "__main__":
    keyboard_listener()