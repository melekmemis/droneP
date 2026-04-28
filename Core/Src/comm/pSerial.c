#include "comm\pSerial.h"

HANDLE hSerial;
DWORD written;
DWORD bytesRead;

void activatePort(void){
    hSerial = CreateFile("COM7", GENERIC_WRITE, 0,
                         NULL, OPEN_EXISTING, 0, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Port acilamadi\n");
    }

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);

    GetCommState(hSerial, &dcb);
    dcb.BaudRate = CBR_57600;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    SetCommState(hSerial, &dcb);
}

uint16_t writeData(uint8_t *buffer, uint16_t len){
    WriteFile(hSerial, buffer, len, &written, NULL);
    printf("Data gonderildi: %lu byte\n", written);
    return written;
}

uint16_t readFile(uint8_t *buffer, uint16_t maxLen){
    ReadFile(hSerial, buffer, maxLen, &bytesRead, NULL);
    printf("Bytes alındı: %lu byte\n", maxLen);
    return bytesRead;
}

void closePort(void){
    CloseHandle(hSerial);
}