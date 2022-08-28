#ifndef __BPS_LED_H__
#define __BPS_LED_H__

#include "stm32f10x.h" 



#define LED_G_GPIO_PIN        GPIO_Pin_0
#define LED_B_GPIO_PIN        GPIO_Pin_1
#define LED_R_GPIO_PIN        GPIO_Pin_5
#define LED_G_GPIO_PORT       GPIOB
#define LED_G_GPIO_CLK        RCC_APB2Periph_GPIOB


#define on     1
#define off    0
#define led(a)         if(a)\
                             {GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);}\
											 else\
                             {GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);} 





void LED_G_GPIO_Config(void);
void LED_B_GPIO_Config(void);
void LED_R_GPIO_Config(void);

#endif
