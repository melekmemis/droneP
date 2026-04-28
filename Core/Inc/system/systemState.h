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

DroneState_t* systemStateGet(void);
BatState_t* batStateGet(void);
void systemStateInit(void);

#endif