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

void SYSCLKConfig_STOP(void)
{
  /* After wake-up from STOP reconfigure the system clock */
  /* 使能 HSE */
  RCC_HSEConfig(RCC_HSE_ON);
  
  /* 等待 HSE 准备就绪 */
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
  {
  }
  
  /* 使能 PLL */ 
  RCC_PLLCmd(ENABLE);
  
  /* 等待 PLL 准备就绪 */
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {
  }
  
  /* 选择PLL作为系统时钟源 */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  /* 等待PLL被选择为系统时钟源 */
  while (RCC_GetSYSCLKSource() != 0x08)
  {
  }
}


uint8_t KEY2_LongPress(void)
{
	uint16_t count=0;
	while(1)
	{
		delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==1)
		{
			count++;
			if(count>=1000)
			{
				return 1;
			}
		}
		else
		{
			count=0;
			return 0;
		}
		
	}
	
	
}

int main()
{
	KEY2_GPIO_Config();
	LED_G_GPIO_Config();
	led(on);
	EXTI_KEY1_Config();//可以不需要这条
	USART_Config();
	/* 使能电源管理单元的时钟,必须要使能时钟才能进入待机模式 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR , ENABLE);
	printf("长按 KEY2 1秒进入待机模式\n");
	while(1)
	{
		if(KEY2_LongPress()==1)
		{
			printf("准备进入待机模式\n");
			printf("按下KEY1唤醒stm32\n");
			delay_ms(110);
			PWR_WakeUpPinCmd(ENABLE);
			PWR_EnterSTANDBYMode();//进入待机模式
			//通过 WKUP 引脚的上升沿，RTC 闹钟、唤醒、入侵、时间戳事件或NRST 引脚外部复位及 IWDG 复位唤醒。
			//这里KEY1按键PA0也是WKUP引脚
		}
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
