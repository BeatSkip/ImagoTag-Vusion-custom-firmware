/*************************************
 * 
 *        89c52 sdcc blink demo
 * 
 * CPU: 89C52
 * FREQ: 12MHz
 * PIN: P00
 * 
 * ***********************************
*/
#include <ax8052.h>
#include <libmf.h>
#include <libmftypes.h>
#include <libmfuart.h>
#include <libmfuart0.h>
#include <libmfflash.h>
#include <libmfwtimer.h>
#include "board.h"
#include "debug.h"

void sleep(void)
{
    // désactivation des GPIO
    DIRA = 0;
    PORTA = -1;

    // event A sur timer A
    WTIRQEN=1;

    WTCFGB=0x7; // disable
    WTCFGA=(SLEEP_TIME<<3) | 1; // LPOSC

    enter_sleep();
}

void init(void)
{
    DPS = 0;
    wtimer0_setclksrc(CLKSRC_LPOSC, 1);
    wtimer1_setclksrc(CLKSRC_FRCOSC, 7);

    // Disable PORTC
    DIRC = 0;
    PORTC = -1;


    DIRA = 0x07; // A0,A1,A2 en sortie
    PORTA = -1; // reset

    DIRB=0x03;
    PORTB = 0xFC;

    // Allumer toutes les LEDs au démarrage
    if(PCON == 0)
    {
        LED_GREEN = LED_ON;
        for(int i=0; i<5; i++)
        {
            delay(-1);
        }
    }
    LED_GREEN = LED_OFF;


    ANALOGA = 0x10; // A5 analog input

    MISCCTRL |= 0x02;

    EIE = 0x00;
    E2IE = 0x00;
    IE = 0x00;
    GPIOENABLE = 1;

    // rapatrier les données de calibration usine
    flash_apply_calibration();

    CLKCON = 0x00;

    wtimer_init_deepsleep();

    // Enable interrupts
    EA = 1;

    PCON = 0x01;

    // use calibration data
    ADCTUNE1 = 0x06;
    ADCTUNE0 = 0x01;

    //ADC System clock, prescaler +1
    // 0b  x   0000 110
    ADCCLKSRC = 0x06;


    // Disable ADC channels 1,2,3
    ADCCH1CONFIG = 0xFF;
    ADCCH2CONFIG = 0xFF;
    ADCCH3CONFIG = 0xFF;

    // ADC5 single ended
    ADCCH0CONFIG = 0xCD;

    ADCCONV = 0x07;
}


static void pwrmgmt_irq(void) __interrupt(INT_POWERMGMT)
{
    uint8_t pc = PCON;

    if (!(pc & 0x80))
        return;

    GPIOENABLE = 0;
    IE = EIE = E2IE = 0;

    for (;;)
        PCON |= 0x01;
}

void main()
{
    board_init();
    uart_timer0_baud(CLKSRC_XOSC, 115200, 26000000);
    uart0_init(0, 8, 1);
    write_banner();
    while (1)
    {
        PIN_SET_LOW(LEDR_PORT, LEDR_PIN);
        delay(250000);
        PIN_SET_HIGH(LEDR_PORT, LEDR_PIN);
        delay(250000);
    }
}

