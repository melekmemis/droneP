#include "system/systemState.h"
#include "mavlink/common/mavlink.h"

static DroneState_t state;

DroneState_t* systemStateGet(void)
{
    return &state;
}

void systemStateInit(void)
{
    state.sensorsPresent =
        MAV_SYS_STATUS_SENSOR_3D_GYRO |
        MAV_SYS_STATUS_SENSOR_3D_ACCEL |
        MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE;

    state.sensorsEnabled = state.sensorsPresent;
    state.sensorsHealth  = state.sensorsPresent;
    state.load = 25;
    state.vBat = 12000;
    state.cBat = 100;
    state.batPrst = 80;
    state.dropRateC0mm = 0;
    state.errComm = 0;
    state.erCnt1 = 0;
    state.erCnt2 = 0;
    state.erCnt3 = 0;
    state.erCnt4 = 0;
}