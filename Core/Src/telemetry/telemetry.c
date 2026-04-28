#include "stdio.h"
#include "telemetry\telemetry.h"
#include "mavlink\common\mavlink.h"
#include "system\systemState.h"
#include "comm\pSerial.h"

mavlink_message_t msg;
uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

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
    writeData(buffer, len);
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
    writeData(buffer, len);
}

void telemetrySendBatteryStatus(void){
    BatState_t *batState = batStateGet();

    mavlink_msg_battery_status_pack(sysId, cmpId, &msg,
                                    batState->id, batState->batFunc, batState->batType,
                                    batState->batTemp, batState->voltages, batState->cBat,
                                    batState->cConsumed, batState->eConsumed,
                                    batState->batRmn, 0, 0, batState->voltagesExt, 0, 0);

    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    writeData(buffer, len);
}