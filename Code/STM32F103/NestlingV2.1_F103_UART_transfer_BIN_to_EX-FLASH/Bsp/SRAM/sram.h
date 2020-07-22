#ifndef __SRAM_H
#define __SRAM_H															    
#include "sys.h" 

/*A地址信号线*/    
#define FSMC_A0_GPIO_PORT        GPIOF
#define FSMC_A0_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A0_GPIO_PIN         GPIO_Pin_0

#define FSMC_A1_GPIO_PORT        GPIOF
#define FSMC_A1_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A1_GPIO_PIN         GPIO_Pin_1

#define FSMC_A2_GPIO_PORT        GPIOF
#define FSMC_A2_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A2_GPIO_PIN         GPIO_Pin_2

#define FSMC_A3_GPIO_PORT        GPIOF
#define FSMC_A3_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A3_GPIO_PIN         GPIO_Pin_3

#define FSMC_A4_GPIO_PORT        GPIOF
#define FSMC_A4_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A4_GPIO_PIN         GPIO_Pin_4

#define FSMC_A5_GPIO_PORT        GPIOF
#define FSMC_A5_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A5_GPIO_PIN         GPIO_Pin_5

#define FSMC_A6_GPIO_PORT        GPIOF
#define FSMC_A6_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A6_GPIO_PIN         GPIO_Pin_12

#define FSMC_A7_GPIO_PORT        GPIOF
#define FSMC_A7_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A7_GPIO_PIN         GPIO_Pin_13

#define FSMC_A8_GPIO_PORT        GPIOF
#define FSMC_A8_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A8_GPIO_PIN         GPIO_Pin_14

#define FSMC_A9_GPIO_PORT        GPIOF
#define FSMC_A9_GPIO_CLK         RCC_APB2Periph_GPIOF
#define FSMC_A9_GPIO_PIN         GPIO_Pin_15

#define FSMC_A10_GPIO_PORT        GPIOG
#define FSMC_A10_GPIO_CLK         RCC_APB2Periph_GPIOG
#define FSMC_A10_GPIO_PIN         GPIO_Pin_0

#define FSMC_A11_GPIO_PORT        GPIOG
#define FSMC_A11_GPIO_CLK         RCC_APB2Periph_GPIOG
#define FSMC_A11_GPIO_PIN         GPIO_Pin_1

#define FSMC_A12_GPIO_PORT        GPIOG
#define FSMC_A12_GPIO_CLK         RCC_APB2Periph_GPIOG
#define FSMC_A12_GPIO_PIN         GPIO_Pin_2

#define FSMC_A13_GPIO_PORT        GPIOG
#define FSMC_A13_GPIO_CLK         RCC_APB2Periph_GPIOG
#define FSMC_A13_GPIO_PIN         GPIO_Pin_3

#define FSMC_A14_GPIO_PORT        GPIOG
#define FSMC_A14_GPIO_CLK         RCC_APB2Periph_GPIOG
#define FSMC_A14_GPIO_PIN         GPIO_Pin_4

#define FSMC_A15_GPIO_PORT        GPIOG
#define FSMC_A15_GPIO_CLK         RCC_APB2Periph_GPIOG
#define FSMC_A15_GPIO_PIN         GPIO_Pin_5

#define FSMC_A16_GPIO_PORT        GPIOD
#define FSMC_A16_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_A16_GPIO_PIN         GPIO_Pin_11

#define FSMC_A17_GPIO_PORT        GPIOD
#define FSMC_A17_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_A17_GPIO_PIN         GPIO_Pin_12

#define FSMC_A18_GPIO_PORT        GPIOD
#define FSMC_A18_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_A18_GPIO_PIN         GPIO_Pin_13

/*D 数据信号线*/
#define FSMC_D0_GPIO_PORT        GPIOD
#define FSMC_D0_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D0_GPIO_PIN         GPIO_Pin_14

#define FSMC_D1_GPIO_PORT        GPIOD
#define FSMC_D1_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D1_GPIO_PIN         GPIO_Pin_15

#define FSMC_D2_GPIO_PORT        GPIOD
#define FSMC_D2_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D2_GPIO_PIN         GPIO_Pin_0

#define FSMC_D3_GPIO_PORT        GPIOD
#define FSMC_D3_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D3_GPIO_PIN         GPIO_Pin_1

#define FSMC_D4_GPIO_PORT        GPIOE
#define FSMC_D4_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D4_GPIO_PIN         GPIO_Pin_7

#define FSMC_D5_GPIO_PORT        GPIOE
#define FSMC_D5_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D5_GPIO_PIN         GPIO_Pin_8

#define FSMC_D6_GPIO_PORT        GPIOE
#define FSMC_D6_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D6_GPIO_PIN         GPIO_Pin_9

#define FSMC_D7_GPIO_PORT        GPIOE
#define FSMC_D7_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D7_GPIO_PIN         GPIO_Pin_10

#define FSMC_D8_GPIO_PORT        GPIOE
#define FSMC_D8_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D8_GPIO_PIN         GPIO_Pin_11

#define FSMC_D9_GPIO_PORT        GPIOE
#define FSMC_D9_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D9_GPIO_PIN         GPIO_Pin_12

#define FSMC_D10_GPIO_PORT        GPIOE
#define FSMC_D10_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D10_GPIO_PIN         GPIO_Pin_13

#define FSMC_D11_GPIO_PORT        GPIOE
#define FSMC_D11_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D11_GPIO_PIN         GPIO_Pin_14

#define FSMC_D12_GPIO_PORT        GPIOE
#define FSMC_D12_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D12_GPIO_PIN         GPIO_Pin_15

#define FSMC_D13_GPIO_PORT        GPIOD
#define FSMC_D13_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D13_GPIO_PIN         GPIO_Pin_8

#define FSMC_D14_GPIO_PORT        GPIOD
#define FSMC_D14_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D14_GPIO_PIN         GPIO_Pin_9

#define FSMC_D15_GPIO_PORT        GPIOD
#define FSMC_D15_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D15_GPIO_PIN         GPIO_Pin_10

/*控制信号线*/  
/*CS片选*/
/*NE3 ,对应的基地址0x68000000*/
#define FSMC_CS_GPIO_PORT        GPIOG
#define FSMC_CS_GPIO_CLK         RCC_APB2Periph_GPIOG
#define FSMC_CS_GPIO_PIN         GPIO_Pin_10

/*WE写使能*/
#define FSMC_WE_GPIO_PORT        GPIOD
#define FSMC_WE_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_WE_GPIO_PIN         GPIO_Pin_5

/*OE读使能*/
#define FSMC_OE_GPIO_PORT        GPIOD
#define FSMC_OE_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_OE_GPIO_PIN         GPIO_Pin_4


/*UB数据掩码*/
#define FSMC_UDQM_GPIO_PORT        GPIOE
#define FSMC_UDQM_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_UDQM_GPIO_PIN         GPIO_Pin_1

/*LB数据掩码*/
#define FSMC_LDQM_GPIO_PORT        GPIOE
#define FSMC_LDQM_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_LDQM_GPIO_PIN         GPIO_Pin_0


											  
void FSMC_SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 NumHalfwordToWrite);
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 NumHalfwordToRead);


void fsmc_sram_test_write(u8 data,u32 addr);
u8 fsmc_sram_test_read(u32 addr);

#endif

