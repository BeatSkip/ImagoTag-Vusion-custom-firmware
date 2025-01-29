#ifndef SLEEP_H_INCLUDED
#define SLEEP_H_INCLUDED


#include <ax8052.h>
#include <libmftypes.h>


void goToSleepMode(void);

uint8_t isWakeUpStart(void);

#endif // SLEEP_H_INCLUDED