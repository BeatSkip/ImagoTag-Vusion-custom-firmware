#ifndef HAL_H
#define HAL_H

#include <ax8052f143.h>
#include <libmftypes.h>
#include <libmfwtimer.h>
#include <libmfuart.h>
#include <libmfuart1.h>

//Choose LOWFREQ_QUARZ or LOWFREQ_RC as source for RTC clock
//#define LOWFREQ_QUARZ
#define LOWFREQ_QUARZ

#define HIGH (1)
#define LOW (0)

#define BIT(x)  (1<<(x))
#define SET(p,x)    do{(p) |= (x);}while(0)
#define CLEAR(p,x)  do{(p) &= ~(x);}while(0)

#define PIN_SET_INPUT(p,x)  CLEAR(p, (BIT(x)))
#define PIN_SET_OUTPUT(p,x) SET(p, (BIT(x)))
#define PIN_SET_LOW(p,x)    CLEAR(p, (BIT(x)))
#define PIN_SET_HIGH(p,x)   SET(p, (BIT(x)))

#ifdef LOWFREQ_QUARZ
#define SECONDS(x) ((uint32_t)(x) * 8192)
#elif defined LOWFREQ_RC
#define SECONDS(x) ((uint32_t)(x) * 640)
#endif // LOWFREQ_QUARZ
#define MILLISECONDS(x) (SECONDS(x) / 1000)

#define ABSOLUTE    0
#define RELATIVE    1

#define NAIVE_MEMCPY(x,y,n) for(int i=0;i<(n);i++){x[i]=y[i];}

#define RemoveEvent(x)  wtimer0_remove(x)

void ScheduleTask(struct wtimer_desc __xdata *desc, wtimer_desc_handler_t handler, uint8_t relative, uint32_t time);
void UART_Init();

uint8_t GetVoltageOrTemp(uint8_t val);
int my_sprintf(char __generic *buf, char __generic *fmt, ...);

void board_init(void);

#endif // HAL_H