#include "bps_exti.h"


static void NVIC_Config(void)//�ú���ֻ��������ļ����ݲ��ܱ����������ļ����ò���
{
	NVIC_InitTypeDef NVIC_InitStruct;//���ñ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//����Ϊ��1�������ȼ�Ϊ1bit �����ȼ�Ϊ3bit��
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;//����������Դ
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI_KEY1_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//�����ж����ȼ�
	NVIC_Config();
	
	//��ʼ��ʹ��GPIOA PA0Ϊ����״̬
	RCC_APB2PeriphClockCmd(KEY1_INT_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin=KEY1_INT_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY1_INT_PORT, &GPIO_InitStruct);
	//��ʼ��EXTI����ѡ��ģʽ ������ʽ ����
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO,ENABLE);//��AFIOʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_DeInit();//�ָ�Ĭ��״̬
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}
void KEY2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//��ʼ��ʹ��GPIOC PB0Ϊ����״̬
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}
