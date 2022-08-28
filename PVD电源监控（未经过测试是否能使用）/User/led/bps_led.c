#include "bps_led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin=LED_G_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin=LED_B_GPIO_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin=LED_R_GPIO_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
	GPIO_SetBits(LED_G_GPIO_PORT, LED_B_GPIO_PIN);
	GPIO_SetBits(LED_G_GPIO_PORT, LED_R_GPIO_PIN);
}



