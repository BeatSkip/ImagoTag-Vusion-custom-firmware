
#include "nfc_fm11nt081d.h"


/* #define LOG_TAG_CONST       NORM */
#define LOG_TAG             "[fm11nt08]"
#include "debug.h"


/********************************************************/
#if(TCFG_FM11NT081D_USER_IIC_TYPE)
#define iic_init(iic)                       hw_iic_init(iic)
#define iic_uninit(iic)                     hw_iic_uninit(iic)
#define iic_start(iic)                      hw_iic_start(iic)
#define iic_stop(iic)                       hw_iic_stop(iic)
#define iic_tx_byte(iic, byte)              hw_iic_tx_byte(iic, byte)
#define iic_rx_byte(iic, ack)               hw_iic_rx_byte(iic, ack)
#define iic_read_buf(iic, buf, len)         hw_iic_read_buf(iic, buf, len)
#define iic_write_buf(iic, buf, len)        hw_iic_write_buf(iic, buf, len)
#define iic_suspend(iic)                    hw_iic_suspend(iic)
#define iic_resume(iic)                     hw_iic_resume(iic)
#else
#define iic_init(iic)                       soft_iic_init(iic)
#define iic_uninit(iic)                     soft_iic_uninit(iic)
#define iic_start(iic)                      soft_iic_start(iic)
#define iic_stop(iic)                       soft_iic_stop(iic)
#define iic_tx_byte(iic, byte)              soft_iic_tx_byte(iic, byte)
#define iic_rx_byte(iic, ack)               soft_iic_rx_byte(iic, ack)
#define iic_read_buf(iic, buf, len)         soft_iic_read_buf(iic, buf, len)
#define iic_write_buf(iic, buf, len)        soft_iic_write_buf(iic, buf, len)
#define iic_suspend(iic)                    soft_iic_suspend(iic)
#define iic_resume(iic)                     soft_iic_resume(iic)
#endif

struct fm11nt081d_platform_data *fm11nt081d_info;
/* extern void delay(unsigned int cnt); */
void delay_12us(u32 us)
{
    u32 mips = (clk_get("sys") / 1000000);
    /* log_info("sys:%d000000",mips); */
    while (us--) {
        for (int i = 0; i < mips; i++) {
            asm("nop");
        }
    }
}

static bool fm11nt08_read_buf(u16 reg, u8 *rbuf, u8 len)
{
    iic_start(fm11nt081d_info->hdl);
    if (0 == iic_tx_byte(fm11nt081d_info->hdl, FM11NT081D_WADDR)) {
        iic_stop(fm11nt081d_info->hdl);
        log_error("fm11nt081d read fail1!\n");
        return false;
    }
    /* os_time_dly(fm11nt081d_info->iic_delay); */
    /* delay(fm11nt081d_info->iic_delay); */
    delay_2ms(fm11nt081d_info->iic_delay);
    if (0 == iic_tx_byte(fm11nt081d_info->hdl, (u8)(reg >> 8))) {
        iic_stop(fm11nt081d_info->hdl);
        log_error("fm11nt081d read fail21!\n");
        return false;
    }
    delay_2ms(fm11nt081d_info->iic_delay);
    if (0 == iic_tx_byte(fm11nt081d_info->hdl, (u8)reg)) {
        iic_stop(fm11nt081d_info->hdl);
        log_error("fm11nt081d read fail22!\n");
        return false;
    }
    delay_2ms(fm11nt081d_info->iic_delay);
    iic_start(fm11nt081d_info->hdl);
    if (0 == iic_tx_byte(fm11nt081d_info->hdl, FM11NT081D_RADDR)) {
        iic_stop(fm11nt081d_info->hdl);
        log_error("fm11nt081d read fail3!\n");
        return false;
    }
    /* for (u8 i = 0; i < len - 1; i++) {	 */
    /* 	rbuf[i] = iic_rx_byte(fm11nt081d_info->hdl, 1); */
    /* 	delay(fm11nt081d_info->iic_delay); */
    /* } */
    /* rbuf[len - 1] = iic_rx_byte(fm11nt081d_info->hdl, 0); */
    iic_read_buf(fm11nt081d_info->hdl, rbuf, len);
    iic_stop(fm11nt081d_info->hdl);
    return true;
}

static bool fm11nt08_write_buf(u16 reg, u8 *wbuf, u8 len)
{
    u8 ret;
    iic_start(fm11nt081d_info->hdl);
    if (0 == iic_tx_byte(fm11nt081d_info->hdl, FM11NT081D_WADDR)) {
        iic_stop(fm11nt081d_info->hdl);
        log_error("fm11nt081d write fail1!\n");
        return false;
    }
    delay_2ms(fm11nt081d_info->iic_delay);
    if (0 == iic_tx_byte(fm11nt081d_info->hdl, (u8)(reg >> 8))) {
        iic_stop(fm11nt081d_info->hdl);
        log_error("fm11nt081d write fail21!\n");
        return false;
    }
    delay_2ms(fm11nt081d_info->iic_delay);
    if (0 == iic_tx_byte(fm11nt081d_info->hdl, (u8)reg)) {
        iic_stop(fm11nt081d_info->hdl);
        log_error("fm11nt081d write fail22!\n");
        return false;
    }
    delay_2ms(fm11nt081d_info->iic_delay);
    /* for (u8 i = 0; i < len - 1; i++) {	 */
    /* 	if(0==iic_tx_byte(fm11nt081d_info->hdl, wbuf[i])){ */
    /* 		iic_stop(fm11nt081d_info->hdl); */
    /* 		log_error("fm11nt081d write fail2!\n"); */
    /* 		return false; */
    /* 	} */
    /* 	delay(fm11nt081d_info->iic_delay); */
    /* } */
    /* if (0 == iic_tx_byte(fm11nt081d_info->hdl, wbuf[len-1])) {	 */
    /* 	iic_stop(fm11nt081d_info->hdl); */
    /* 	log_error("fm11nt081d write fail3!\n"); */
    /* 	return false; */
    /* } */
    ret = iic_write_buf(fm11nt081d_info->hdl, wbuf, len);
    if (ret < len) {
        log_error("fm11nt081d write fail3!\n");
        iic_stop(fm11nt081d_info->hdl);
        return false;
    }
    iic_stop(fm11nt081d_info->hdl);
    return true;
}

void fm11nt08_cs_on()
{
    gpio_write(fm11nt081d_info->csn_port_io, 0);
    delay_12us(10);//abort 100us
}
void fm11nt08_cs_off()
{
    gpio_write(fm11nt081d_info->csn_port_io, 1);
}
/*********************************************************************************************************
 * ** 函数名称:	FM11NT08_WriteReg
 * ** 函数功能:	写11NC08寄存器
 * ** 输入参数:    reg:寄存器地址
 * ** 				val:写入的参数
 * ** 返回值:      无
 * *********************************************************************************************************/
void fm11nt08_writereg(u8 reg, u8 val)
{
    u16 reg_temp;
    u8 val_temp = val;
    fm11nt08_cs_on();
    reg_temp = (0xff << 8) | (reg | 0xf0);
    fm11nt08_write_buf(reg_temp, &val_temp, 1);
    fm11nt08_cs_off();
}
/*********************************************************************************************************
 * ** 函数名称:	FM11NT08_ReadReg
 * ** 函数功能:	读寄存器值
 * ** 输入参数:    reg:寄存器地址
 * ** 返回值:      val,读出的寄存器值
 * *********************************************************************************************************/
u8 fm11nt08_readreg(u8 reg)
{
    u16 reg_temp;
    u8 val;
    fm11nt08_cs_on();
    reg_temp = (0xff << 8) | (reg | 0xf0);
    fm11nt08_read_buf(reg_temp, &val, 1);
    fm11nt08_cs_off();
    return val;
}
/*********************************************************************************************************
 * ** 函数名称:	FM11NT08_WriteFIFO
 * ** 函数功能:	写FIFO
 * ** 输入参数:    ilen:写数据长度(<=32 fifo空间)
 * ** 					*ibuf:写的数据
 * ** 返回值:      无
 * *********************************************************************************************************/
void fm11nt08_writefifo(u8 *wbuf, u32 len)
{
    u16 reg_temp;
    fm11nt08_cs_on();
    reg_temp = 0xfff0;
    fm11nt08_write_buf(reg_temp, wbuf, len);
    fm11nt08_cs_off();
}
/*********************************************************************************************************
 * ** 函数名称:	ReadFIFO
 * ** 函数功能:	发送NAK帧
 * ** 输入参数:    *ilen:待读取的数据长度
 * ** 输出参数:    *rbuf:读取的数据
 * ** 返回值:      读取的数据长度
 * *********************************************************************************************************/
void fm11nt08_readfifo(u8 *rbuf, u32 len)
{
    u16 reg_temp;
    fm11nt08_cs_on();
    reg_temp = 0xfff0;
    fm11nt08_read_buf(reg_temp, rbuf, len);
    fm11nt08_cs_off();
}
/*********************************************************************************************************
 * ** 函数名称:	FM11NT08_WriteE2
 * ** 函数功能:	写E2数据
 * ** 输入参数:    adr:E2地址
 * ** 				len:写入的数据长度(<=16)
 * ** 				*ibuf:写入的数据
 * ** 返回值:      无
 * *********************************************************************************************************/
void fm11nt08_writeE2(u8 *addr, u8 *wbuf, u32 len)
{
    u16 reg_temp;
    fm11nt08_cs_on();
    reg_temp = ((addr[0] & 0x03) << 8) | addr[1];
    fm11nt08_write_buf(reg_temp, wbuf, len);
    fm11nt08_cs_off();
}
/*********************************************************************************************************
 * ** 函数名称:	FM11NT08_ReadE2
 * ** 函数功能:	读取的E2数据
 * ** 输入参数:    adr:E2地址
 * ** 				len:读取的数据长度
 * ** 				*rbuf:读取的数据
 * ** 返回值:      无
 * *********************************************************************************************************/
void fm11nt08_readE2(u8 *addr, u8 *rbuf, u32 len)
{
    u16 reg_temp;
    fm11nt08_cs_on();
    reg_temp = ((addr[0] & 0x03) << 8) | addr[1];
    fm11nt08_read_buf(reg_temp, rbuf, len);
    fm11nt08_cs_off();
}

unsigned char irq_rxdone = 0;
unsigned char irq_txdone = 0;
unsigned char irq_data_in = 0;

unsigned char rfLen = 0;
unsigned char rfBuf[255];
unsigned char FlagFirstFrame = OFF;
unsigned char FlagErrIrq = OFF;
unsigned char CID;
unsigned char FSDI;
unsigned char block_num;
/*********************************************
 * ** 函数名称:	FM11NT08_RFDataTx
 * ** 函数功能:	RF数据回发
 * ** 输入参数:    ilen:回发数据长度
 * ** 				*ibuf:回发的数据
 * ** 输出参数:    无
 * ** 返回值:      无
 * *******************************************/
void fm11nt08_RFDataTx(u8 *ibuf, u32 ilen)
{
    u32 slen, cnt;
    u8 *sbuf;

    slen = ilen;
    sbuf = ibuf;
    cnt = 0;
    if (slen <= 32) {
        fm11nt08_writefifo(sbuf, slen);		//write fifo	长度小于等于32，全部发送
        slen = 0;
    } else {
        fm11nt08_writefifo(sbuf, 32);		//write fifo	长度大于32，先发送32字节

        slen -= 32;		//待发长度－32
        sbuf += 32;		//待发数据指针+32
    }

    fm11nt08_writereg(RF_TXEN, 0x55);	//写0x55时触发非接触口回发数据

    while (slen > 0) {
        if ((fm11nt08_readreg(FIFO_WORDCNT) & 0x3F) <= 8) {
            if (slen <= 24) {
                fm11nt08_writefifo(sbuf, slen);			//write fifo	先发24字节进fifo
                slen = 0;
            } else {
                fm11nt08_writefifo(sbuf, 24);			//write fifo	先发24字节进fifo

                slen -= 24; 	//待发长度－24
                sbuf += 24; 	//待发数据指针+24
            }
        }

        fm11nt08_writereg(RF_TXEN, 0x55);	//写0x55时触发非接触口回发数据
    }
    //while(fm11nt08_ChkIrqInfo(FIFO_IRQ_EMPTY,FIFO_IRQ)==OFF);
    //fm11nt08_readreg(MAIN_IRQ);

    //while((fm11nt08_readreg(FIFO_WORDCNT) & 0x3F )> 0);	//等待发送完成标志位置起
    irq_txdone = 0;
}

/*******************************************
 ** 函数名称:	FM11NT08_RFDataRx
 ** 函数功能:	写FIFO
 ** 输入参数:    rbuf:读取数据
 ** 输出参数:    无
 ** 返回值:      读取的数据长度
 ******************************************/
unsigned int fm11nt08_RFDataRx(unsigned char *rbuf)
{
    u8 rlen, irq_main;
    rlen = 0;
    bit_clr_ie(IRQ_PORT_IDX);
    while (1) {
        //		Delay_100us(10);
        rlen = fm11nt08_readreg(FIFO_WORDCNT) & 0x3F;
        if (rlen > 8) {
            fm11nt08_readfifo(rfBuf + rfLen, rlen);
            rfLen += rlen;
        }
        irq_main = fm11nt08_readreg(MAIN_IRQ);
        if (irq_main & MAIN_IRQ_RX_DONE) {
            break;
        }
        if (irq_main & MAIN_IRQ_AUX) {
            FlagErrIrq = ON;
            fm11nt08_readreg(AUX_IRQ);
        }
    }
    //	while(irq_rxdone == 0);
    irq_rxdone = 0;
    //	rlen=rfLen;
    //while((irq_rxdone == 0)&&(FlagErrIrq == OFF));
    //	irq_rxdone = 0;
    /*
    	if(FlagErrIrq == ON)
    	{
    	FlagErrIrq = OFF;
    	return 0;
    	}
    	*/
    rlen = fm11nt08_readreg(FIFO_WORDCNT) & 0x3F;	//接收完全之后，查fifo有多少字节
    fm11nt08_readfifo(rfBuf + rfLen, rlen);		//读最后的数据
    rfLen += rlen;
    rlen = rfLen;

    if (rlen <= 2)	{
        return 0;
    }
    rlen -= 2;	//2字节crc校验
    bit_set_ie(IRQ_PORT_IDX);
    return rlen;
}

void fm11nt08_Clearfifo(void)
{
    fm11nt08_writereg(FIFO_FLUSH, 0xFF);		//清fifo寄存器
}


/*********************************************************************************************************
 * ** 函数名称:	FM11NT08_GetStatus
 * ** 函数功能:	读FM11NT08 status
 * ** 输入参数:    无
 * ** 输出参数:    无
 * ** 返回值:      sta 状态值
 * *********************************************************************************************************/
unsigned char fm11nt08_GetStatus(void)
{
    unsigned char sta;
    sta = fm11nt08_readreg(RF_STATUS);
    sta = (sta & 0xE0) >> 5;		//高3bit
    return sta;
}
/*********************************************************************************************************
 * ** 函数名称:	FM11NT08_ChkIrqInfo
 * ** 函数功能:	读FM11NT08 中断状态
 * ** 输入参数:    irq:中断位置
 * **					reg:mian/fifo/aux
 * ** 输出参数:    无
 * ** 返回值:      sta:ON/OFF
 * *********************************************************************************************************/
unsigned char fm11nt08_ChkIrqInfo(u8 irq, u8 reg)
{
    unsigned char ret;
    ret = fm11nt08_readreg(reg);
    if (ret & irq) {
        return ON;		//标志起来置ON
    } else {
        return OFF;
    }
}

/*********************************************************************************************************
 * ** 函数名称:	FM11NT08_FIFO_func
 * ** 函数功能:	判断FIFO数据的功能
 * ** 输入参数:    ibuf
 * ** 输出参数:    无
 * ** 返回值:      协议模式
 * *********************************************************************************************************/
unsigned char fm11nt08_fifo_func(unsigned char ibuf)
{
    if (ibuf == 0xE0) {		//Rats指令
        return FUNC_RATS;
    }
    if ((ibuf & 0xF0) == 0xD0) {	//pps指令
        return  FUNC_PPSS;
    }
    if ((ibuf & 0xE2) == 0x02) {	//I_BLOCK指令
        return  FUNC_I_BLOCK;
    }
    if ((ibuf & 0xE6) == 0xA2) {	//R_BLOCK指令
        return  FUNC_R_BLOCK;
    }
    if ((ibuf & 0xC7) == 0xC2) {	//S_BLOCK指令
        return  FUNC_S_BLOCK;
    }
    if (ibuf == 0x80) {		//处理0x80开头的指令,PDTP协议
        return  FUNC_PDTP;
    }
    return 0xFF;
}

void fm11nt08_SetRatsCfg(unsigned char rats)
{
    u8 temp;
    CID = rats & 0x0F;
    temp = (rats >> 4) & 0x0F;
    if (temp < 5) {
        FSDI = 8 * (temp + 2);
    } else if ((temp >= 5) && (temp <= 7)) {
        FSDI = 32 * (temp - 3);
    } else {
        FSDI = 255;
    }

    FSDI -= 2;	//减去2字节EDC
    block_num = 0x01;	//初始为1，调用前，一直为上一帧的块号
}
void port_irq_fm11nt08(void)//FM175XX IRQ中断
{
    u8 irq_main;
    u8 irq_fifo;
    u8 rx_len = 0;
    log_info("nfc irq");
    irq_main = fm11nt08_readreg(MAIN_IRQ);

    if (irq_main & MAIN_IRQ_RF_PWON) {
        /* log_info("port  irq rf_pwon"); */
        fm11nt08_Clearfifo();
        return;
    }

    if (irq_main & MAIN_IRQ_RX_START) {
        rfLen = 0;
        irq_rxdone = 0;
        irq_data_in = 1;
        /* log_info("port  irq rx_start"); */
        return;
    }
    if (irq_main & MAIN_IRQ_TX_DONE) {
        irq_txdone = 1;
        /* log_info("port  irq tx_done"); */
        return;
    }
    /* if(reg_data & MAIN_IRQ_ACTIVE)FlagFirstFrame = ON; */
}
/*********************************************************************************************************
 ** 函数名称:	FM11NT08_Init
 ** 函数功能:	Fm11NT08的spi口初始化程序
 ** 输入参数:    无
 ** 输出参数:    无
 ** 返回值:      无
 *********************************************************************************************************/
bool fm11nt08_init(void *priv)
{
    if (priv == NULL) {
        log_info("fm11nt081d init fail(no priv)\n");
        return false;
    }
    fm11nt081d_info = (struct fm11nt081d_platform_data *)priv;

    gpio_write(fm11nt081d_info->csn_port_io, 1);
    gpio_set_direction(fm11nt081d_info->csn_port_io, 0);
    gpio_set_die(fm11nt081d_info->csn_port_io, 1);
    port_wkup_interrupt_init(fm11nt081d_info->fd_port_io, 1, port_irq_fm11nt08);//下沿触发
    u8 reg_data;
    /* delay_2ms(100);//100ms */

    fm11nt08_writereg(MAIN_IRQ_MASK, 0x54);	//MAIN中断配置;接收开始中断
    reg_data = fm11nt08_readreg(MAIN_IRQ_MASK);
    log_info("-> MAIN_IRQ_MASK = %x", reg_data);

    fm11nt08_writereg(FIFO_IRQ_MASK, 0x07);	//FIFO中断配置
    reg_data = fm11nt08_readreg(FIFO_IRQ_MASK);
    log_info("-> FIFO_IRQ_MASK = %x", reg_data);

    fm11nt08_writereg(NFC_CFG, 0x03);	//写NFC配置字(默认支持-4)
    reg_data = fm11nt08_readreg(NFC_CFG);
    log_info("-> NFC_CFG = %x", reg_data);

    fm11nt08_Clearfifo();
    log_info("clear fm fifo");
    //	RFpdtpReady = OFF;
    //	RFapduReady = OFF;
    //	RFdataLen = 0;
    //	CTdataLen = 0;
    //	CTdataIndex = 0;
    //
    //	memset(RFdataBuf,0,BUF_LENTH);
    //	memset(CTdataBuf,0,BUF_LENTH);
    return true;
}





/********************************test*********************************/
#if 1
//iic模式:传输速度：standard-mode(100kbps)、fast-mode(400kbps)、fast-mode plus(1mbps)
struct fm11nt081d_platform_data fm11nt081d_test_data = {
    .comms = 0,  //0:IIC,  1:SPI
    .hdl = 0,    //iic_hdl  or spi_hdl
    .csn_port_io = IO_PORTC_02,
    .fd_port_io = IO_PORTC_03,
    .iic_delay = 0 //这个延时并非影响iic的时钟频率，而是2Byte数据之间的延时
};
void fm11nt081d_test_main()
{
    u8 reg_data;
    log_info("----------FM11NT081D test---------\n");
#if(TCFG_FM11NT081D_USER_IIC_TYPE)
    log_info("-------hw_iic-------\n");
#else
    log_info("-------soft_iic-------\n");
#endif
    iic_init(fm11nt081d_test_data.hdl);
    fm11nt08_init(&fm11nt081d_test_data);
    u32 eeprom_addr = 0;
    u8 buff[16] = {0x05, 0x72, 0x01, 0x57, 0xf7, 0x60, 0x02, 0x00, 0x00, 0x00, 0xa2, 0xb2, 0x00, 0x00, 0x00, 0x00};
    u8 adr[2] = {0x03, 0x10};
    log_info("write fm ee");
    wdt_clear();
    for (u8 i = 0; i < 4; i++) {
        fm11nt08_writeE2(adr, buff + i * 4, 4);
        log_info("write fm ee:%d", i);
        delay_2ms(3);//110ms
        adr[1] += 4;
    }
    delay_2ms(110);//110ms
    wdt_clear();
    for (u16 i = 0; i < 0x7a; i++) {
        eeprom_addr = i * 8;
        adr[1] = eeprom_addr & 0xFF;	//LSB
        adr[0] = (eeprom_addr & 0xFF00) >> 8; //MSB
        fm11nt08_readE2(adr, buff, 8);
        log_info("read eeprom:%d", i * 2);
        log_info_hexdump(buff, 8);
        delay_2ms(2);//110ms
    }
    while (1) {
        if (irq_data_in) {
            //		   reg_data = fm11nt08_readreg(MAIN_IRQ);
            //			Uart_Send_Msg("-> MAIN_IRQ = ");
            //			Uart_Send_Hex(&reg_data,1);
            //			Uart_Send_Msg("\r\n");

            log_info("-> irq_data_in ");
            rfLen = fm11nt08_RFDataRx(rfBuf);		//读取rf数据(一帧)
            if (rfLen > 0) {
                if (FlagFirstFrame == ON) {
                    fm11nt08_SetRatsCfg(fm11nt08_readreg(RF_RATS));	//第一帧配置rats信息
                    FlagFirstFrame = OFF;
                }

                reg_data = fm11nt08_readreg(RF_BAUD);
                log_info("-> RF_BAUD = %x", reg_data);
                log_info("-> FM11NT08_RFDataRx = ");
                log_info_hexdump(rfBuf, rfLen);

                fm11nt08_RFDataTx(rfBuf, rfLen);
            }
            irq_data_in = 0;
        }
        delay_2ms(2);//110ms
        wdt_clear();
    }

    iic_uninit(fm11nt081d_test_data.hdl);
}


#endif

