#ifndef __NFC_FM11NT081D_H__
#define __NFC_FM11NT081D_H__

#define TCFG_FM11NT081D_USER_IIC_TYPE 1


#define FM11NT081D_RADDR        0xaf
#define FM11NT081D_WADDR        0xae

#define ON        		1
#define OFF		       	0

#define FUNC_RATS		0
#define FUNC_PPSS 		1
#define FUNC_I_BLOCK 	2
#define FUNC_R_BLOCK 	3
#define FUNC_S_BLOCK	4
#define FUNC_PDTP		5

///// Register addresses (SPI) and related definitions
#define FIFO_ACCESS     0x00    // Memory location for MCU FIFO access and SPI FIFO operation instructions
#define FIFO_FLUSH      0x01    // Clear/flush FIFO buffer contents
#define FIFO_WORDCNT    0x02    // Register for MCU to check remaining FIFO capacity
#define RF_STATUS       0x03    // Contactless interface operating status
#define RF_TXEN         0x04    // FIFO Access Control Unit
#define RF_BAUD         0x05    // Contactless communication baud rate selection
#define RF_RATS         0x06    // RATS (Request for Answer To Select) data received during contactless communication
#define MAIN_IRQ        0x07    // Main interrupt flag register
#define FIFO_IRQ        0x08    // FIFO interrupt flag register
#define AUX_IRQ         0x09    // Auxiliary interrupt flag register
#define MAIN_IRQ_MASK   0x0A    // Main interrupt mask register
#define FIFO_IRQ_MASK   0x0B    // FIFO interrupt mask register
#define AUX_IRQ_MASK    0x0C    // Auxiliary interrupt mask register
#define NFC_CFG         0x0D    // NFC configuration register
#define REGU_CFG        0x0E    // Voltage regulator configuration register

//#define REG_RANGE    REGU_CFG    // Valid register address range
#define CS_DELAY          1000
#define MAIN_IRQ_RF_PWON  0x80
#define MAIN_IRQ_ACTIVE   0x40
#define MAIN_IRQ_RX_START 0x20
#define MAIN_IRQ_RX_DONE  0x10
#define MAIN_IRQ_TX_DONE  0x08
#define MAIN_IRQ_ARBIT    0x04
#define MAIN_IRQ_FIFO     0x02
#define MAIN_IRQ_AUX      0x01

#define FIFO_IRQ_WL      0x08
#define FIFO_IRQ_OVFLOW  0x04
#define FIFO_IRQ_FULL    0x02
#define FIFO_IRQ_EMPTY   0x01

#define TYPE_IRQ_MAIN 0
#define TYPE_IRQ_FIFO 1
#define TYPE_IRQ_AUX  2

//iic mode: transmission speed: standard-mode (100kbps), fast-mode (400kbps), fast-mode plus (1mbps)
//spi mode: frequency <= 5MHz. Timing: default CPOL=0, CPHA=1; can be modified to CPOL=1, CPHA=1 (not introduced in the data)
struct fm11nt081d_platform_data {
    u8 comms;//0:IIC,  1:SPI
    u8 csn_port_io;//模块上电
    u8 fd_port_io;//field detect
    u8 hdl;//iic_hdl  or spi_hdl
    u8 iic_delay; //This delay does not affect the clock frequency of iic, but the delay between 2Byte data. Unit: ms
};


//iic
bool fm11nt08_init(void *priv);
void fm11nt08_writereg(u8 reg, u8 val);
u8 fm11nt08_readreg(u8 reg);
void fm11nt08_writefifo(u8 *wbuf, u32 len);
void fm11nt08_readfifo(u8 *rbuf, u32 len);
void fm11nt08_writeE2(u8 *addr, u8 *wbuf, u32 len);
void fm11nt08_readE2(u8 *addr, u8 *rbuf, u32 len);
void fm11nt08_RFDataTx(u8 *ibuf, u32 ilen);
unsigned int fm11nt08_RFDataRx(unsigned char *rbuf);
void fm11nt08_Clearfifo(void);
unsigned char fm11nt08_GetStatus(void);
unsigned char fm11nt08_ChkIrqInfo(u8 irq, u8 reg);
unsigned char fm11nt08_fifo_func(unsigned char ibuf);
void fm11nt08_SetRatsCfg(unsigned char rats);

//spi

#endif