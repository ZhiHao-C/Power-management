#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_PVD.h"
void delay_ms(int n)//ÑÓÊ±º¯Êý
{
	int i;
	while (n--)
	{
		for(i=0;i<5520;i++);
	}
}



int main()
{
	LED_GPIO_Config();
	EXTI_PVD_Config();
	led_R(off);
	led_G(on);
	while(1)
	{}
}


void PVD_IRQHandler(void)
{
	
	led_G(off);
	led_R(on);
	
	EXTI_ClearFlag(EXTI_Line16);
}

	
