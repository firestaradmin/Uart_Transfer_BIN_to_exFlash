/************************************************************************************
*  Copyright (c), 2020, LXG.
*
* FileName		:
* Author		:firestaradmin
* Version		:1.0
* Date			:2020.7.21
* Description	:串口接收BIN文件数据烧录至外部储存器
* History		:
*
*
*************************************************************************************
帧协议格式:
		Byte0	Byte1	Byte2		Byte3		Byte4		Byte5	…		last but two Byte	last but one Byte	Last Byte
		0xC5	0x5C	XX			XX			XX			XX		XX		XX					0x5C				0xC5
		帧头	帧头	命令		长度高字节	长度低字节	数据	数据	BCC校验码			帧尾				帧尾
		
		如发送数据：C5 5C 00 00 04 22 33 44 FF AE 5C C5
		BCC = 除了帧头帧尾和bcc本身的异或
		BCC = 00 ^ 00 ^ 04 ^ 22 ^ 33 ^ 44 ^ FF = AE

命令:	0x00	0x01			0x02			0xFF
备注:	数据	数据传输开始	数据传输结束	应答

*************************************************************************************/


#include "stm32f10x.h"
#include "../bsp/transfer_BIN_to_EX_FLASH/transfer_BIN_to_EX_FLASH.h"
#include "../bsp/w25qxx/w25qxx.h" 
#include "../BSP/usart/usart.h"

static u32 bytesStored = 0;	//已经储存的字节
static u32 stroage_StartAddress = 0;	//片外储存的起始地址
static u8 transfer_started_flag = 0;	//是否已经开始传输数据标志

static u8 TBEF_recvBuf[1000];	//接受buf，最大单次传输字节数应不大于buf大小-8
static u16 TBEF_recvBuf_tail = 0;
u8 TBEF_uart_recv_finish = 0, TBEF_uart_recving_flag = 0, TBEF_uart_recv_tim_cnt = 0;


//用户回调函数，此处修改需要烧录的函数
void TBEF_data_CallBack(u8 *dataBuf, u16 len)
{
	//根据需求修改此处
	W25QXX_Write(dataBuf, stroage_StartAddress + bytesStored, len);//写入flash
	
	bytesStored += len;
}

//串口处理函数，在串口中断中调用，将接收到的字节传入data
void TBEF_uart_receive_process(u8 data)
{  	
	if(TBEF_uart_recv_finish == 0){
		TBEF_recvBuf[TBEF_recvBuf_tail++] = data;		// 存入缓存数组
		TBEF_uart_recving_flag = 1;                     // 串口 接收标志
		TBEF_uart_recv_tim_cnt = 0;	                    // 串口接收定时器计数清零	
	}
	if(TBEF_recvBuf_tail >= sizeof(TBEF_recvBuf))
	{
		 TBEF_recvBuf_tail = 0;                               	// 防止数据量过大
	}		
	
}

//定时器处理函数，在定时器中断中调用，1Ms一次
void TBEF_tim_process(void)		//1MS调用一次
{
	/* 串口接收完成判断处理 */
	if(TBEF_uart_recving_flag)                        	// 如果 usart接收数据标志为1
	{
		TBEF_uart_recv_tim_cnt++;             // usart 接收计数	
		if(TBEF_uart_recv_tim_cnt > 10)       // 当超过 3 ms 未接收到数据，则认为数据接收完成。
		{
			TBEF_uart_recv_finish = 1;
			TBEF_uart_recving_flag = 0;
			TBEF_uart_recv_tim_cnt = 0;
		}
	}
	
}

//在主函数中调用，需要一直循环调用，此函数为阻塞函数
void TBEF_mainFun(void)
{
	u8 ret = TBEF_frameVerify();
	if(ret)
		TBEF_Err_Processing(ret);
	else
		TBEF_CMD_Precesing();
	
	TBEF_SendACK(ret);
	TBEF_recvBuf_tail = 0;
	TBEF_uart_recv_finish = 0;
}

void TBEF_CMD_Precesing(void)
{
	u8 cmd = TBEF_recvBuf[2];
	
	if(cmd == 0x00)
	{
		u16 length = TBEF_recvBuf[3] * 0xFF + TBEF_recvBuf[4];;
		TBEF_data_CallBack(TBEF_recvBuf + 5, length);
		
	}
	else if(cmd == 0x01)
	{
		transfer_started_flag = 1;
		bytesStored = 0;
		stroage_StartAddress = (uint32_t)TBEF_recvBuf[5] * 0x1000000 + (uint32_t)TBEF_recvBuf[6] * 0x10000 + (uint32_t)TBEF_recvBuf[7] * 0x100 + (uint32_t)TBEF_recvBuf[8] ; 
		//stroage_StartAddress = ((uint32_t)TBEF_recvBuf[5] << 24) & ((uint32_t)TBEF_recvBuf[6] << 16) & ((uint32_t)TBEF_recvBuf[7] << 8) & (uint32_t)TBEF_recvBuf[8];
	}
	else if(cmd == 0x02)
	{
		transfer_started_flag = 0;
	}else {
		//TODO:
	}
}

void TBEF_Err_Processing(u8 err)
{
	switch(err){
		case 0:	/* no err */
			
			break;
		case 1:
			UartSendStr(USART1, (u8*)"Frame Head err!\r\n");
			break;
		case 2:
			UartSendStr(USART1, (u8*)"Frame Tail err!\r\n");
			break;
		case 3:
			UartSendStr(USART1, (u8*)"BCC err!\r\n");
			break;
		default:
			UartSendStr(USART1, (u8*)"Unknow err!\r\n");
	};
}
	
u8 TBEF_frameVerify(void)
{
	u16 length = 0;
	u8 bcc = 0x00;
	while(TBEF_uart_recv_finish != 1);	//wait receive finish
	
	
	if(TBEF_recvBuf[0] != 0xC5)
		return 1;	//帧头错误
	if(TBEF_recvBuf[1] != 0x5C)
		return 1;	//帧头错误
	length = (u16)TBEF_recvBuf[3] * 0xFF + (u16)TBEF_recvBuf[4];
	
	for(u16 i = 2; i < 5 + length; i ++){
		bcc ^= TBEF_recvBuf[i];
	}
	
	if(bcc != TBEF_recvBuf[5 + length])
		return 2;	//bcc校验码错误
	
	if(TBEF_recvBuf[6 + length] != 0x5C)
		return 3;	//帧尾错误
	if(TBEF_recvBuf[7 + length] != 0xC5)
		return 3;	//帧尾错误
	
	return 0;
	
}

//如：C5 5C FF 00 01 00 FE 5C C5	表示没有错误
void TBEF_SendACK(u8 ERROR)
{
	u8 sendBuf[9] = {0xC5, 0x5C, 0x00, 0x00, 0x01, ERROR, 0x00, 0x5C, 0xC5};
	sendBuf[2] = TBEF_recvBuf[2];
	sendBuf[6] = sendBuf[2] ^ sendBuf[3] ^ sendBuf[4] ^ sendBuf[5] ; 
	
	UartSendMultByte(USART1, sendBuf, 9);
}

void TBEF_clearRecvBuf(void)
{
	while(TBEF_recvBuf_tail--)
	{
		TBEF_recvBuf[TBEF_recvBuf_tail] = 0;
	}
	
}




/*
//W25Q64
//容量为8M字节,共有128个Block,2048个Sector 
//4Kbytes为一个Sector
//16个扇区为1个Block

//以下表示地址为W25QXX的第一个区块的第0个扇区的第0个地址
#define W25QXX_STORAGE_Block	1
#define W25QXX_STORAGE_Sector	0
#define W25QXX_STORAGE_Sector_OFFSET	0
//static u32 TBEF_W25QXX_StorageAddress = W25QXX_STORAGE_Block * 4 * 1024 * 16 + 4 * 1024 * W25QXX_STORAGE_Sector + W25QXX_STORAGE_Sector_OFFSET;	//要烧录的具体地址
*/






