#include "sleep.h"

// Endormis l'appareil
void goToSleepMode(void)
{
    ADCCLKSRC = 0x7; //disable adc

    // event A sur timer A
    WTIRQEN=1;

    // 3min10
    //WTCFGA=0x11;

    // 1min35
    //WTCFGA=0x9;

    // 45s
    WTCFGA=0x01;

    WTCNTA=0;
    WTCNTB=0;


    enter_sleep();
}

// indique s'il s'agit d'une mise sous tension et non d'un réveil
uint8_t isWakeUpStart(void)
{
    uint8_t result;
    result = PCON & 0x40;
    return result;
}