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
#include "board.h"
#include "debug.h"


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

