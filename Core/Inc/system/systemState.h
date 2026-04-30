#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <stdint.h>

typedef struct {
uint32_t sensorsPresent;
uint32_t sensorsEnabled;
uint32_t sensorsHealth;
uint16_t load;
uint16_t vBat;
uint16_t cBat;
int8_t batPrst;
uint16_t dropRateC0mm;
uint16_t errComm;
uint16_t erCnt1;
uint16_t erCnt2;
uint16_t erCnt3;
uint16_t erCnt4;
} DroneState_t;
static DroneState_t state;

typedef struct {
uint8_t id;
uint8_t batFunc;
uint8_t batType;
int16_t batTemp;
uint16_t voltages[10];
int16_t cBat;
int32_t cConsumed;
int32_t eConsumed;
int8_t batRmn;
uint16_t voltagesExt[10];
} BatState_t;
static BatState_t batState;

typedef struct {
uint32_t timeBootMs;
float roll;
float pitch;
float yaw;
float rollspeed;
float pitchspeed;
float yawspeed;
} SensorState_t;
static SensorState_t sensorState;

typedef struct {
uint64_t timeUsec;
uint8_t fixType;
int32_t lat;
int32_t lon;
int32_t alt;
uint16_t eph; 
uint16_t epv;
uint16_t vel;
uint16_t cog;
uint8_t satellitesVisible;
int32_t altEllipsoid;
uint32_t hAcc;
uint32_t vAcc;
uint32_t velAcc;
uint32_t hdgAcc;
uint16_t yaw;
} GpsState_t;
static GpsState_t gpsState;

DroneState_t* systemStateGet(void);
BatState_t* batStateGet(void);
SensorState_t* sensorStateGet(void);
GpsState_t* gpsStateGet(void);
void systemStateInit(void);

#endif