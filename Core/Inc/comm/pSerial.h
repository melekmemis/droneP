#include <stdint.h>
#include "windows.h"
#include "stdio.h"

#ifndef PSERIAL_H
#define PSERIAL_H

void activatePort(void);
uint16_t writeData(uint8_t *buffer, uint16_t len);
uint16_t readData(uint8_t *buffer, uint16_t maxLen);
void closePort(void);

#endif