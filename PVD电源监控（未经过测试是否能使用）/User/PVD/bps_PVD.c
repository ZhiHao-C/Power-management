#include "bps_PVD.h"


static void NVIC_Config(void)//该函数只有在这个文件内容才能被调用其他文件调用不了
{
	NVIC_InitTypeDef NVIC_InitStruct;//设置变量
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//分组为组1（主优先级为1bit 次优先级为3bit）
	NVIC_InitStruct.NVIC_IRQChannel=PVD_IRQn;//设置引脚来源
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI_PVD_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	//打开电源管理时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	//配置中断优先级
	NVIC_Config();
	
	
	//初始化EXTI包括选择模式 触发方式 引脚
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO,ENABLE);//打开AFIO时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_DeInit();//恢复默认状态
	EXTI_InitStruct.EXTI_Line=EXTI_Line16;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	
	//配置PVD级别PWR_PVDLevel_2V6 (PVD检测电压的阈值为2.6V，VDD电压低于2.6V时产生PVD中断)
	PWR_PVDLevelConfig(PWR_PVDLevel_2V6);
	PWR_PVDCmd(ENABLE);
}
