#include "stdio.h"
#include "app\app.h"

int main(void){
    appInit();

    while(1){
        appRun();
    }

    appStop();
    return 0;
}