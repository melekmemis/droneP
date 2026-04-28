#include "app\app.h"
#include "comm\pSerial.h"
#include "telemetry\telemetry.h"
#include "system\scheduler.h"
#include "system\systemState.h"

void appInit(void){
    activatePort();
    telemetryInit(1, 2);
    systemStateInit();
}

void appRun(void){
    telemetrySendHeartbeat();
    telemetrySendSysStatus();
    Sleep(1000);
}

void appStop(void){
    closePort();
}