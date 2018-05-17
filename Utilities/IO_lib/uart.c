#include "main.h" // Is dit de bedoeling?

/**************************************************************************************/

void RCC_Configuration(void)
{
	/* --------------------------- System Clocks Configuration -----------------*/
	/* USART2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* DMA1 clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
}

/**************************************************************************************/



void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*-------------------------- GPIO Configuration ----------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);   // USART2_TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);  // USART2_RX

}

/**************************************************************************************/

void USART2_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;

	/* USARTx configuration ------------------------------------------------------*/
	/* USARTx configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);

	USART_Cmd(USART2, ENABLE);
}

/**************************************************************************************/


void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Enable the USART2 TX DMA Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART2 RX DMA Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**************************************************************************************/


void DMA_Configuration(void)
{
	DMA_InitTypeDef  DMA_InitStructure;

	// USART2_TX DMA Channel 5, DMA1, Stream6

	DMA_DeInit(DMA1_Stream6);

	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // Transmit
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&DMA_TX_Buffer;
	DMA_InitStructure.DMA_BufferSize = DMA_TX_BUFFER_SIZE;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA1_Stream6, &DMA_InitStructure);

	/* Enable the USART Tx DMA request */
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);

	/* Enable DMA Stream Transfer Complete interrupt */
	DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);

	/* Enable the DMA TX Stream */
	DMA_Cmd(DMA1_Stream6, ENABLE);

	// USART2_RX DMA Channel 5, DMA1, Stream5

	DMA_DeInit(DMA1_Stream5);

	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Receive
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&DMA_RX_Buffer;
	DMA_InitStructure.DMA_BufferSize = DMA_RX_BUFFER_SIZE;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA1_Stream5, &DMA_InitStructure);

	/* Enable the USART Rx DMA request */
	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);

	/* Enable DMA Stream Transfer Complete interrupt */
	DMA_ITConfig(DMA1_Stream5, DMA_IT_TC, ENABLE);

	/* Enable the DMA RX Stream */
	DMA_Cmd(DMA1_Stream5, ENABLE);
}

/**************************************************************************************/


void DMA1_Stream6_IRQHandler(void) // USART2_TX
{

	/* Test on DMA Stream Transfer Complete interrupt */
	if (DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6))
	{
		/* Clear DMA Stream Transfer Complete interrupt pending bit */
		DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);
//	    memset(DMA_TX_Buffer, 0, sizeof DMA_TX_Buffer);
	}

    if (USART2->SR & USART_FLAG_IDLE) {         /* We want IDLE flag only */
        /* This part is important */
        /* Clear IDLE flag by reading status register first */
        /* And follow by reading data register */
        volatile uint32_t tmp;                  /* Must be volatile to prevent optimizations */
        tmp = USART2->SR;                       /* Read status register */
        tmp = USART2->DR;                       /* Read data register */
        (void)tmp;                              /* Prevent compiler warnings */
	    DMA1_Stream6->CR &= ~DMA_SxCR_EN;       /* Disabling DMA will force transfer complete interrupt if enabled */
    }



}

/**************************************************************************************/

void DMA1_Stream5_IRQHandler(void) // USART2_RX
{
	/* Test on DMA Stream Transfer Complete interrupt */
	if (DMA_GetITStatus(DMA1_Stream5, DMA_IT_TCIF5))
	{
		/* Clear DMA Stream Transfer Complete interrupt pending bit */
		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);
	}
}



/**************************************************************************************/


void UART_printf( char *put )
/* UART printf
 * This function translates a string with variables to a string and puts in on the UART
 */
{

    /* Prepare DMA for next transfer */
    /* Important! DMA stream won't start if all flags are not cleared first */
    DMA1->HIFCR = DMA_FLAG_DMEIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_HTIF5 | DMA_FLAG_TCIF5 | DMA_FLAG_TEIF5;
    DMA1_Stream5->M0AR = (uint32_t)DMA_RX_Buffer;   /* Set memory address for DMA again */
    DMA1_Stream5->NDTR = DMA_RX_BUFFER_SIZE;    /* Set number of bytes to receive */
    DMA1_Stream5->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
	memcpy(DMA_TX_Buffer, put, strlen(put)+1);

	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
}

