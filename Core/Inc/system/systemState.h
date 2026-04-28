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

DroneState_t* systemStateGet(void);
void systemStateInit(void);

#endif