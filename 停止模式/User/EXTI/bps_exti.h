#ifndef __BPS_EXTI_H__
#define __BPS_EXTI_H__

#include "stm32f10x.h" 

#define KEY1_INT_PIN          GPIO_Pin_0
#define KEY1_INT_PORT         GPIOA
#define KEY1_INT_CLK          RCC_APB2Periph_GPIOA
void EXTI_KEY1_Config(void);
#endif
