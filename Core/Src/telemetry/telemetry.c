#include "stdio.h"
#include "telemetry\telemetry.h"
#include "mavlink\common\mavlink.h"
#include "system\systemState.h"
#include "comm\pSerial.h"

#include <stdint.h>
#include "windows.h"

mavlink_message_t msg;
mavlink_status_t status;

uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
uint8_t buffRcv[MAVLINK_MAX_PACKET_LEN];

uint8_t sysId = 0;
uint8_t cmpId = 0;

void telemetryInit(uint8_t systemId, uint8_t componentId){
    sysId = systemId;
    cmpId = componentId;
}

void telemetrySendHeartbeat(void){

    mavlink_msg_heartbeat_pack(sysId, cmpId, &msg,
                               MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC,
                               MAV_MODE_MANUAL_ARMED, 0, MAV_STATE_ACTIVE);

    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    uint16_t writtenD = writeData(buffer, len);
    printf("Data gonderildi: %lu byte\n", writtenD);
}

void telemetrySendSysStatus(void){
    DroneState_t *state = systemStateGet();

    mavlink_msg_sys_status_pack(sysId, cmpId, &msg,
                                state->sensorsPresent, state->sensorsEnabled,
                                state->sensorsHealth, state->load, state->vBat, state->cBat,
                                state->batPrst, state->dropRateC0mm, state->errComm,
                                state->erCnt1, state->erCnt2, state->erCnt3, state->erCnt4,
                                0, 0, 0);

    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    uint16_t writtenD = writeData(buffer, len);
    printf("Data gonderildi: %lu byte\n", writtenD);
}

void telemetrySendBatteryStatus(void){
    BatState_t *batState = batStateGet();

    mavlink_msg_battery_status_pack(sysId, cmpId, &msg,
                                    batState->id, batState->batFunc, batState->batType,
                                    batState->batTemp, batState->voltages, batState->cBat,
                                    batState->cConsumed, batState->eConsumed,
                                    batState->batRmn, 0, 0, batState->voltagesExt, 0, 0);

    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    uint16_t writtenD = writeData(buffer, len);
    printf("Data gonderildi: %lu byte\n", writtenD);
}

void telemetrySendAttitude(void){
    SensorState_t *sensorState = sensorStateGet();

    mavlink_msg_attitude_pack(sysId, cmpId, &msg,
                              sensorState->timeBootMs,
                              sensorState->roll, sensorState->pitch, sensorState->yaw,
                              sensorState->rollspeed, sensorState->pitchspeed, sensorState->yawspeed);
    
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    uint16_t writtenD = writeData(buffer, len);
    printf("Data gonderildi: %lu byte\n", writtenD);
}

void telemetrySendGpsRaw(void){
    GpsState_t *gpsState = gpsStateGet();

    mavlink_msg_gps_raw_int_pack(sysId, cmpId, &msg,
                               gpsState->timeUsec, gpsState->fixType,
                               gpsState->lat, gpsState->lon, gpsState->alt,
                               gpsState->eph, gpsState->epv, gpsState->vel, gpsState->cog,
                               gpsState->satellitesVisible, gpsState->altEllipsoid,
                               gpsState->hAcc, gpsState->vAcc, gpsState->velAcc,
                               gpsState->hdgAcc, gpsState->yaw);

    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    uint16_t writtenD = writeData(buffer, len);
    printf("Data gonderildi: %lu byte\n", writtenD);
}

void telemetryRecv(void){
    uint16_t receivedD = readData(buffRcv, 48);
    uint16_t writtenD;

    for (int i = 0; i < receivedD; i++)
    {
        if (mavlink_parse_char(MAVLINK_COMM_0, buffRcv[i], &msg, &status))
        {
            printf("Mesaj geldi: %d\n", msg.msgid);

            if (msg.msgid == MAVLINK_MSG_ID_PARAM_REQUEST_LIST)
            {
                printf("PARAM_REQUEST_LIST alındı\n");

                mavlink_message_t param_msg;
                uint8_t tx_buffer[MAVLINK_MAX_PACKET_LEN];
                uint16_t tx_len;

                // TEST_PARAM
                mavlink_msg_param_value_pack(
                    1, 2,
                    &param_msg,
                    "TEST_PARAM",
                    123.0f,
                    MAV_PARAM_TYPE_REAL32,
                    2,
                    0
                );

                tx_len = mavlink_msg_to_send_buffer(tx_buffer, &param_msg);
                writtenD = writeData(tx_buffer, tx_len);
                printf("Params gonderildi: %lu byte\n", writtenD);

                // SYSID_THISMAV
                mavlink_msg_param_value_pack(
                    1, 2,
                    &param_msg,
                    "SYSID_THISMAV",
                    1.0f,
                    MAV_PARAM_TYPE_REAL32,
                    2,
                    1
                );

                tx_len = mavlink_msg_to_send_buffer(tx_buffer, &param_msg);
                writtenD = writeData(tx_buffer, tx_len);
                printf("Params gonderildi: %lu byte\n", writtenD);
            }
        }
    }
}