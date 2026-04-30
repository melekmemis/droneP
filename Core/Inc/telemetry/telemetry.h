#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "stdio.h"
#include <stdint.h>

void telemetryInit(uint8_t systemId, uint8_t componentId);

void telemetrySendHeartbeat(void);
void telemetrySendSysStatus(void);
void telemetrySendBatteryStatus(void);
void telemetrySendAttitude(void);
void telemetrySendGpsRaw(void);
void telemetryUpdate(uint32_t now);

void telemetryRecv(void);

#endif