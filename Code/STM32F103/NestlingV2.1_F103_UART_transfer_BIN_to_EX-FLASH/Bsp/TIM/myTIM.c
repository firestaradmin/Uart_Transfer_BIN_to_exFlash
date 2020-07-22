#include "../BSP/TIM/myTIM.h"
#include "../BSP/LED/LED.h"
#include "../bsp/transfer_BIN_to_EX_FLASH/transfer_BIN_to_EX_FLASH.h"



//通用定时器初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM中断,允许更新中断
 
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;  //先占优先级
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
 
 
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}

#ifdef __cplusplus
extern "C"{
#endif


	
//定时器中断服务程序
void TIM2_IRQHandler(void)   //TIM中断 	TIM2_Int_Init(10 - 1, 7200 - 1); //1MS
{
	static u16 tim_cnt = 0;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
			
			
			tim_cnt++;
			if(tim_cnt >= 500)
			{
				LED_TOGGLE();
				tim_cnt = 0;
			}
			
			TBEF_tim_process();
		}
}


#ifdef __cplusplus
}
#endif





