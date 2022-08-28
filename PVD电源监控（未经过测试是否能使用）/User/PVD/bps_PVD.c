#include "bps_PVD.h"


static void NVIC_Config(void)//�ú���ֻ��������ļ����ݲ��ܱ����������ļ����ò���
{
	NVIC_InitTypeDef NVIC_InitStruct;//���ñ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//����Ϊ��1�������ȼ�Ϊ1bit �����ȼ�Ϊ3bit��
	NVIC_InitStruct.NVIC_IRQChannel=PVD_IRQn;//����������Դ
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI_PVD_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	//�򿪵�Դ����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	//�����ж����ȼ�
	NVIC_Config();
	
	
	//��ʼ��EXTI����ѡ��ģʽ ������ʽ ����
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO,ENABLE);//��AFIOʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_DeInit();//�ָ�Ĭ��״̬
	EXTI_InitStruct.EXTI_Line=EXTI_Line16;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	
	//����PVD����PWR_PVDLevel_2V6 (PVD����ѹ����ֵΪ2.6V��VDD��ѹ����2.6Vʱ����PVD�ж�)
	PWR_PVDLevelConfig(PWR_PVDLevel_2V6);
	PWR_PVDCmd(ENABLE);
}
