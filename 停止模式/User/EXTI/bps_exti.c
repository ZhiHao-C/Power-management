#include "bps_exti.h"


static void NVIC_Config(void)//该函数只有在这个文件内容才能被调用其他文件调用不了
{
	NVIC_InitTypeDef NVIC_InitStruct;//设置变量
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//分组为组1（主优先级为1bit 次优先级为3bit）
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;//设置引脚来源
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI_KEY1_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//配置中断优先级
	NVIC_Config();
	
	//初始化使得GPIOA PB0为输入状态
	RCC_APB2PeriphClockCmd(KEY1_INT_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin=KEY1_INT_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY1_INT_PORT, &GPIO_InitStruct);
	//初始化EXTI包括选择模式 触发方式 引脚
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO,ENABLE);//打开AFIO时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_DeInit();//恢复默认状态
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}
