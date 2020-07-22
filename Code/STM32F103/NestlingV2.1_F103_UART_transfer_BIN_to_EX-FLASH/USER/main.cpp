
#include "main.h"
#include "../BSP/delay/delay.h"
#include "../BSP/usart/usart.h"
#include "../BSP/TIM/myTIM.h"
#include "../BSP/LED/LED.h"
#include "../bsp/transfer_BIN_to_EX_FLASH/transfer_BIN_to_EX_FLASH.h"
#include "../bsp/w25qxx/w25qxx.h" 
#include <stdio.h>

//以下表示地址为W25QXX的第一个区块的第0个扇区
#define W25QXX_STORAGE_Block	1
#define W25QXX_STORAGE_Sector	0
u32 W25QXX_StorageAddress = W25QXX_STORAGE_Block * 4 * 1024 * 16 + 4 * 1024 * W25QXX_STORAGE_Sector;	//要烧录的具体地址
u32 mybytesStored = 0;	//已经储存的字节
u8 buf[72];
int main()
{

	SystemInit();	//晶振时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//4位抢占优先级
	DelayInit();	//延时函数初始化
	LED_init();
	//usart1_init(115200);
	usart1_init(230400);
	TIM2_Int_Init(10 - 1, 7200 - 1); //1MS
	W25QXX_Init();
	std::printf("NestlingV2.1_Demo\r\n");
	
	
//	std::printf("FLASH ID:%X\r\n", W25QXX_ReadID());
//	for(u8 j = 0; j < 200; j++)
//	{
//	
//		std::printf("-----[%d]-----: \r\n", j);
//		W25QXX_Read(buf, W25QXX_StorageAddress + 5827 * 72 + mybytesStored, 72);
//		mybytesStored += 72;
//		for(u8 i = 0; i < 72; i++){
//			std::printf("%02X ", buf[i]);
//		}
//		std::printf("\r\n");
//	}


	while(1){
		TBEF_mainFun();
		
		
	}
	return 0;
}



