#include "hal.h"
#include "board.h"

// Sets wtimer descriptor to call 'handler' in/at 'time' (depends on 'relative')
// 'handler' is optional, if NULL, old one is used
void ScheduleTask(struct wtimer_desc __xdata *desc, wtimer_desc_handler_t handler, uint8_t relative, uint32_t time)
{
    wtimer0_remove(desc);
    desc->time = time;
    if(relative)    desc->time += wtimer0_curtime();
    if(handler)     desc->handler = handler;
    wtimer0_addabsolute(desc);
}

__idata __no_init uint8_t message @ (0xFF);

void HAL_RebootToBootloader()
{
    message = 0xB1;
    PCON |= 0x10;
}

void UART_Init()
{
    // Init pins
    PIN_SET_INPUT(UART_RX_DIR, UART_RX_PIN); // UART RX
    UART_RX = HIGH;

    PIN_SET_OUTPUT(UART_TX_DIR, UART_TX_PIN); // UART TX
    UART_TX_PORT = LOW;

    PALTA |= 0x20; // Alternative function
    PINSEL |= 0x02;

    // Init UART
    uart_timer0_baud(CLKSRC_FRCOSC, 115200, 20000000);//115200
    uart1_init(0,8,1);
    EIE_5 = 1;//enable uart interrupt
    EIP_5 = 1;//hi priority
    // bug fix
    uart1_rxcount();
    uart_timer0_baud(CLKSRC_FRCOSC, 115200, 20000000);//115200
}

uint8_t GetVoltageOrTemp(uint8_t val)
{
    uint8_t i = 0;
    uint32_t   VDDIOAVER = 0;
    uint32_t   TEMPERAVER = 0;
    uint8_t    res;

    EA = 0;
    ADCCLKSRC = 0x30;
    ADCCH1CONFIG = 0xD9;    //VddIO
    ADCCH2CONFIG = 0xD8;    //Temperature
    do
    {
        ADCCONV = 0x01;
        while(ADCCLKSRC&0x80);
        VDDIOAVER += ADCCH1VAL0;
        VDDIOAVER += (((uint16_t)ADCCH1VAL1)<<8);
        TEMPERAVER += ADCCH2VAL0;
        TEMPERAVER += (((uint16_t)ADCCH2VAL1)<<8);
    }
    while(++i);
    EA = 1;
    if(val)
    {
        res = (((VDDIOAVER>>8)*1000)>>16) - 450;
    }
    else res = TEMPERAVER>>16;

    return res;
}

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