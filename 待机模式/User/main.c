#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_exti.h"
#include "bps_usart.h"
#include <stdio.h>
void delay_ms(int n)//��ʱ����
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
  /* ʹ�� HSE */
  RCC_HSEConfig(RCC_HSE_ON);
  
  /* �ȴ� HSE ׼������ */
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
  {
  }
  
  /* ʹ�� PLL */ 
  RCC_PLLCmd(ENABLE);
  
  /* �ȴ� PLL ׼������ */
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {
  }
  
  /* ѡ��PLL��Ϊϵͳʱ��Դ */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  /* �ȴ�PLL��ѡ��Ϊϵͳʱ��Դ */
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
	EXTI_KEY1_Config();//���Բ���Ҫ����
	USART_Config();
	/* ʹ�ܵ�Դ����Ԫ��ʱ��,����Ҫʹ��ʱ�Ӳ��ܽ������ģʽ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR , ENABLE);
	printf("���� KEY2 1��������ģʽ\n");
	while(1)
	{
		if(KEY2_LongPress()==1)
		{
			printf("׼���������ģʽ\n");
			printf("����KEY1����stm32\n");
			delay_ms(110);
			PWR_WakeUpPinCmd(ENABLE);
			PWR_EnterSTANDBYMode();//�������ģʽ
			//ͨ�� WKUP ���ŵ������أ�RTC ���ӡ����ѡ����֡�ʱ����¼���NRST �����ⲿ��λ�� IWDG ��λ���ѡ�
			//����KEY1����PA0Ҳ��WKUP����
		}
	}
}



void EXTI0_IRQHandler ()//EXTI0�жϺ������ƣ���startup��ѯ��
{
	if(EXTI_GetFlagStatus(EXTI_Line0)==1)
	{
		printf("��⵽KEY1����׼������STM32\n");
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}
	


//���մ����жϺ���
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
