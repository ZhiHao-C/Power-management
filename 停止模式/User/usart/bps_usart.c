#include "bps_usart.h"
#include <stdio.h>



static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}







void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USARTx, &USART_InitStructure);

	// 串口中断优先级配置
	NVIC_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}

//发送一个字节
void USART_Sendbyte(USART_TypeDef* USARTx,uint8_t Data)
{
	USART_SendData(USARTx,Data);
	while (!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));//判断发送数据寄存器是否将数据发送到发送移位寄存器
}
//发送两个字节
void USART_Send_twobyte(USART_TypeDef* USARTx,uint16_t Data)
{
	uint8_t temp_h,temp_l;
	temp_h=Data>>8;
	temp_l=Data;
	USART_SendData(USARTx,temp_h);
	while (!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));
	USART_SendData(USARTx,temp_l);
	while (!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));
}
//发送一个数组
void USART_Sendarr(USART_TypeDef* USARTx,uint8_t*arr,uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++)
	{
		USART_SendData(USARTx,arr[i]);
		while (!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));
	}
}
//发送一个字符串（可以是中文）
void USART_Sendstr(USART_TypeDef* USARTx,uint8_t *str)
{
	while ((*str)!=0)
	{
		USART_SendData(USARTx,*str);
		str++;
		while (!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));
	}
}

int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}

