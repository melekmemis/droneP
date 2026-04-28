#include "system/systemState.h"
#include "mavlink/common/mavlink.h"

void systemStateInit(void){
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

    batState.id = 0;
    batState.batFunc = 0;
    batState.batType = 1;
    batState.batTemp = 1816;
    batState.voltages[0] = 3462;
    batState.voltages[1] = 3865;
    batState.voltages[2] = 3683;
    batState.voltages[3] = 3245;
    batState.voltages[4] = 0;
    batState.voltages[5] = 0;
    batState.voltages[6] = 0;
    batState.voltages[7] = 0;
    batState.voltages[8] = 0;
    batState.voltages[9] = 0;
    batState.cBat = 120;
    batState.cConsumed = -1;
    batState.eConsumed = -1;
    batState.batRmn = 86;
}

DroneState_t* systemStateGet(void){ return &state; }
BatState_t* batStateGet(void){ return &batState; }