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

#define UART_RX PORTB_4
#define UART_TX PORTB_5
#define UART_PORT PORTB
#define UART_DIR DIRB

//FLASH MEMORY & SPI
#define CS_FLASH PORTC_0
#define CS_FLASH_DIR DIRC
#define CS_FLASH_PORT PORTC

#define CS_NFC PORTB_1
#define CS_NFC_DIR DIRB
#define CS_NFC_PORT PORTB

#define CS_EPD PORTA_1
#define CS_EPD_DIR DIRA
#define CS_EPD_PORT PORTA

#define SPI_SCK PORTC_1
#define SPI_MISO PORTC_3
#define SPI_MOSI PORTC_2

#define SPI_PORT PORTC
#define SPI_DIR DIRC

#define NFC_FD PORTB_3
#define NFC_FD_DIR DIRB
#define NFC_FD_PORT PORTB

#define EPD_DC PORTA_0
#define EPD_DC_DIR DIRA
#define EPD_DC_PORT PORTA

#define EPD_RST PORTB_5
#define EPD_RST_DIR DIRB
#define EPD_RST_PORT PORTB

#define EPD_BUSY PORTB_2
#define EPD_BUSY_DIR DIRB
#define EPD_BUSY_PORT PORTB





#endif // BOARD_HEADER_H