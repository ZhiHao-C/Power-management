#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_exti.h"
#include "bps_usart.h"
#include <stdio.h>
void delay_ms(int n)//延时函数
{
	int i;
	while (n--)
	{
		for(i=0;i<5520;i++);
	}
}



int main()
{
	LED_G_GPIO_Config();
	led(off);
	EXTI_KEY1_Config();
	USART_Config();
	printf("准备进入睡眠模式\n");
	delay_ms(110);
	__WFI();
	printf("唤醒STM32\n");
	led(on);
	while(1)
	{
		printf("准备循环进入睡眠模式\n");
		led(off);
		delay_ms(3000);
		__WFI();
		printf("唤醒STM32\n");
		led(on);
		delay_ms(3000);
	}
}



void EXTI0_IRQHandler ()//EXTI0中断函数名称（在startup查询）
{
	if(EXTI_GetFlagStatus(EXTI_Line0)==1)
	{
		printf("检测到KEY1按下准备唤醒STM32\n");
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}
	


//接收触发中断函数
void DEBUG_USART_IRQHandler(void)
{
	uint8_t temp;
	if((USART1->SR&0x20)==0x20)
	{
		temp=USART_ReceiveData(USART1);
		USART_SendData(USART1,temp);
		while (!USART_GetFlagStatus(USART1,USART_FLAG_TXE));
	}
}
