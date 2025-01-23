#ifndef BOARD_HEADER_H
#define BOARD_HEADER_H

/*************************************
 * 
 *        SES-Imagotag Board Header
 * 
 * CPU: AX8052
 * FREQ: 26MHz
 * 
 * ***********************************
*/

#include <ax8052.h>
#include <libmftypes.h>

//Board constants
#define SYSCLK 26000000UL  // 26Mhz system clock

//MACROS
#define HIGH (1)
#define LOW (0)

#define BIT(x)  (1<<(x))
#define SET(p,x)    do{(p) |= (x);}while(0)
#define CLEAR(p,x)  do{(p) &= ~(x);}while(0)

#define PIN_SET_INPUT(p,x)  CLEAR(p, (BIT(x)))
#define PIN_SET_OUTPUT(p,x) SET(p, (BIT(x)))
#define PIN_SET_LOW(p,x)    CLEAR(p, (BIT(x)))
#define PIN_SET_HIGH(p,x)   SET(p, (BIT(x)))

//PINS

#define LEDW PORTB_0
#define LEDB PORTB_7
#define LEDG PORTB_6
#define LEDR PORTC_4

#define LEDW_PORT PORTB
#define LEDB_PORT PORTB
#define LEDG_PORT PORTB
#define LEDR_PORT PORTC

#define LEDW_DIR DIRB
#define LEDB_DIR DIRB
#define LEDG_DIR DIRB
#define LEDR_DIR DIRC

#define LEDW_PIN 0
#define LEDB_PIN 7
#define LEDG_PIN 6
#define LEDR_PIN 4



void board_init(void);


void board_init(void)
{
    // Set LED pins as output
    PIN_SET_OUTPUT(LEDW_DIR, LEDW_PIN);
    PIN_SET_OUTPUT(LEDR_DIR, LEDR_PIN);
    PIN_SET_OUTPUT(LEDG_DIR, LEDG_PIN);
    PIN_SET_OUTPUT(LEDB_DIR, LEDB_PIN);  

    PIN_SET_LOW(LEDW_PORT, LEDW_PIN);
    PIN_SET_LOW(LEDR_PORT, LEDR_PIN);
    PIN_SET_LOW(LEDG_PORT, LEDG_PIN);
    PIN_SET_LOW(LEDB_PORT, LEDB_PIN);  
}

#endif // BOARD_HEADER_H