/*
 * 用于测试pt_thread封装的测试文件
 *
 *                      Author: 权勋（KarsusNeko	karsus@msn.cn）
 */

/* headers -------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "stdio.h"
#include "pt_thread.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u32 ticks = 0;

pt_thread_info	thread_info1;
pt_thread_info	thread_info2;
/* Private function prototypes -----------------------------------------------*/ 
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void Systick_Configuration(void);
void USART_Configuration(void);
/* Private functions ---------------------------------------------------------*/

/*
 * 线程作用：打印>>>>>>>>>，并在等待20个tick之后，再次打印<<<<<<<<<，之后再
 *           等待20个tick。如此循环
 */
static int
protothread1(struct pt *pt)
{
	PT_BEGIN(pt);
	while(1)
	{
		printf("\r\n>>>>>>>>>>>>\r\n");
		timer_set(&((container_of(pt, pt_thread_info, pt))->timer), 20);
		PT_WAIT_UNTIL(pt, timer_expired(&((container_of(pt, pt_thread_info, pt))->timer)));
		printf("\r\n<<<<<<<<<<<<\r\n");
		timer_set(&((container_of(pt, pt_thread_info, pt))->timer), 20);
		PT_WAIT_UNTIL(pt, timer_expired(&((container_of(pt, pt_thread_info, pt))->timer)));
	}
	PT_END(pt);
}

/*
 * 作用：打印-------后等待10个tick，如此循环
 */
static int
protothread2(struct pt *pt)
{
	PT_BEGIN(pt);
	while(1)
	{
		printf("\r\n------------\r\n");
		timer_set(&((container_of(pt, pt_thread_info, pt))->timer), 10);
		PT_WAIT_UNTIL(pt, timer_expired(&((container_of(pt, pt_thread_info, pt))->timer)));
	}
	PT_END(pt);
}

int main(void)
{
	RCC_Configuration();
	NVIC_Configuration();
	GPIO_Configuration();
	Systick_Configuration();
	USART_Configuration();

	pt_thread_init(&thread_info1, &(thread_info1.pt_thread));
	pt_thread_init(&thread_info2, &(thread_info1.pt_thread));

	PT_INIT(&(thread_info1.pt));
	PT_INIT(&(thread_info2.pt));

	while(1)
	{
		protothread1(&(thread_info1.pt));
		protothread2(&(thread_info2.pt));
	}
}

void RCC_Configuration(void)
{
    ErrorStatus HSEStartUpStatus;
    
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if(HSEStartUpStatus == SUCCESS)
    {
    	RCC_HCLKConfig(RCC_SYSCLK_Div1);
    	RCC_PCLK2Config(RCC_HCLK_Div1); 
    	RCC_PCLK1Config(RCC_HCLK_Div2);
    	FLASH_SetLatency(FLASH_Latency_2);
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    	RCC_PLLCmd(ENABLE);
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    	while(RCC_GetSYSCLKSource() != 0x08);
    }
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
						|  RCC_APB2Periph_GPIOC
						|  RCC_APB2Periph_USART1, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate 			  = 115200;
	USART_InitStructure.USART_WordLength		  = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 			  = USART_StopBits_1;
	USART_InitStructure.USART_Parity 			  = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 				  = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);
}
 
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

#ifdef	VECT_TAB_RAM
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel			  = USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd		  = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}  

void Systick_Configuration(void)
{
    SysTick_CounterCmd(SysTick_Counter_Disable);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    SysTick_CounterCmd(SysTick_Counter_Clear);
    SysTick_SetReload(9000 * 50);
	
	NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 1, 0);	
	
	SysTick_CounterCmd(SysTick_Counter_Enable);
	SysTick_ITConfig(ENABLE);		
}

int fputc(int ch, FILE* f)
{
	USART_SendData(USART1, (u8)ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);

	return ch;
}


