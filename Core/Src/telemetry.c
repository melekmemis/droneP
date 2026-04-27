#include "windows.h"
#include "stdio.h"
#include "mavlink\common\mavlink.h"

int main(void){
    HANDLE hSerial;

    hSerial = CreateFile("COM7",
                         GENERIC_WRITE,
                         0,
                         NULL,
                         OPEN_EXISTING,
                         0,
                         NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Port acilamadi\n");
        return -1;
    }
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Serial port acilamadi\n");
        return 1;
    }

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);

    GetCommState(hSerial, &dcb);
    dcb.BaudRate = CBR_57600;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    SetCommState(hSerial, &dcb);

    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    uint8_t system_id = 1;
    uint8_t component_id = 1;

    mavlink_msg_heartbeat_pack(
        system_id,
        component_id,
        &msg,
        MAV_TYPE_QUADROTOR,
        MAV_AUTOPILOT_GENERIC,
        MAV_MODE_MANUAL_ARMED,
        0,
        MAV_STATE_ACTIVE
    );

    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

    DWORD written;
    WriteFile(hSerial, buffer, len, &written, NULL);

    printf("Heartbeat gonderildi: %lu byte\n", written);
    Sleep(1000);

    CloseHandle(hSerial);
    return 0;
}