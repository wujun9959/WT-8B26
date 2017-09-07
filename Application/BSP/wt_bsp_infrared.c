/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_bsp_infrared.c
  * @author  LZY wu jun
  * @version V1.0.0
  * @date    2014-03-30
  * @brief   This file provides the INFRARED functions
  ******************************************************************************
  */

#define WT_BSP_INFRARED_GLOBALS

/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_infrared.h"
#include "cmsis_os.h"
#include "main.h"
#include "wt_bsp_usart.h"


extern HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status, uint32_t Timeout);

static void UART_Infr_Buffer_RxClear(void);
static uint8_t WT_UART_Infr_WrBuf(uint8_t* pData, uint8_t length);

static void WT_UART_Infr_Rx_IT(uint8_t dat);
static void UartInfr_RX_Process(void);
//void UartInfr_Send_StartPrint_Cmd(void);

//static uint8_t is_send_command_ok = 0;
static uint8_t Is_UART_Infra_Rx_Come = 0; //0-未收到数据 1-收到数据包

/**
  * @brief  wire self check task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void UARTINFRThread(void const * argument)
{
	osEvent event;
	uint16_t cnt;
	
	BSP_INFRARED_Init();	//Init
	UART_Infr_Buffer_RxClear();
	UART_Infr_Switch = 0;
	
  for( ;; )
  {
    event = osMessageGet(UartInfrEvent, osWaitForever );
    
    if( event.status == osEventMessage )
    {
      switch(event.value.v)
      {
				case UartInfr_RX_Event:
					UartInfr_RX_Process();
					break;
				
				case UartInfr_TX_Event://测试OK，发送红外信号
					cnt = 10000;
					UART_Infr_Switch = 0;//0-start infrared 1-stop infrared
				  while(cnt--)
					{
						UartInfr_Send_StartInfr_Cmd();
						
						if(UART_Infr_Switch == 1 || Is_UART_Infra_Rx_Come == 1) break;
						osDelay(100);
					}
					break;
				case UartInfr_TX_STOP_Event:
					UART_Infr_Switch = 1;
					break;
				
				default:
					break;
      }
    }
		else	//error
		{
			osDelay(1000);
		}
  }
}


/**
  * @brief  Configures INFRARED GPIO.
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
//void BSP_INFRARED_Init(void)
//{
//  GPIO_InitTypeDef  GPIO_InitStruct;
//  
//  /* Enable the GPIO_INFRARED Clock */
//  INFRARED_GPIO_CLK_ENABLE();

//  /* Configure the GPIO_INFRARED pin */
//  GPIO_InitStruct.Pin = IO_INFRARED_TX_PIN;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
//  HAL_GPIO_Init(INFRARED_PORT, &GPIO_InitStruct);

//	Infra_PWM_OFF();
//}


/**
  * @brief  WT_UART_Audio_Init
  * @param  None
  * @retval None
  */
void BSP_INFRARED_Init(void)
{
	//GPIO_InitTypeDef  GPIO_InitStruct;
	//uint32_t i;
	
	/* USART configuration */
  /* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle_Infr.Instance        = UART_Infr;
  UartHandle_Infr.Init.BaudRate   = 9600;
  UartHandle_Infr.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle_Infr.Init.StopBits   = UART_STOPBITS_1;
  UartHandle_Infr.Init.Parity     = UART_PARITY_NONE;
  UartHandle_Infr.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle_Infr.Init.Mode       = UART_MODE_TX_RX;
  HAL_UART_Init(&UartHandle_Infr);
		
}


/**
  * @brief  This function handles UART interrupt request.
  * @param  huart: UART handle
  * @retval None
  */
void WT_UART_Infr_IRQHandler(UART_HandleTypeDef *huart)
{
  uint32_t tmp1 = 0, tmp2 = 0;

  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_PE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_PE);  
  /* UART parity error interrupt occurred ------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_PE);
    
    huart->ErrorCode |= HAL_UART_ERROR_PE;
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_FE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR);
  /* UART frame error interrupt occurred -------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);
    
    huart->ErrorCode |= HAL_UART_ERROR_FE;
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_NE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR);
  /* UART noise error interrupt occurred -------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_NE);
    
    huart->ErrorCode |= HAL_UART_ERROR_NE;
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_ORE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR);
  /* UART Over-Run interrupt occurred ----------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_ORE);
    
    huart->ErrorCode |= HAL_UART_ERROR_ORE;
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_RXNE);
  /* UART in mode Receiver ---------------------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
		WT_UART_Infr_Rx_IT((uint8_t)(huart->Instance->DR & (uint8_t)0x00FF));	//cndz, 20140723
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_TC);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_TC);
  /* UART in mode Transmitter ------------------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    //UART_Transmit_IT(huart);
  }
  
  if(huart->ErrorCode != HAL_UART_ERROR_NONE)
  {
    /* Set the UART state ready to be able to start again the process */
    huart->State = HAL_UART_STATE_READY;
    
    HAL_UART_ErrorCallback(huart);
  }  
}

/**
  * @brief  UART_Infr_Buffer_RxClear
  * @param  None
  * @retval None
  */
static void UART_Infr_Buffer_RxClear(void)
{
	uint32_t i;
	
	for(i=0;i<UART_Infr_RX_Bufer_Length;i++) UART_Infr_Buffer_Rx[i]=0;
	UART_Infr_Cnt_Buffer_Rx = 0;
//	Is_UART_Infr_Rx_Come = 0;
}

/**
  * @brief  WT_UART_Infr_Rx
  * @param  uint8_t dat
  * @retval None
  */
uint8_t WT_UART_Infr_WrBuf(uint8_t* pData, uint8_t length)
{
	while(length--)
	{
		if(UART_WaitOnFlagUntilTimeout(&UartHandle_Infr, UART_FLAG_TXE, RESET, 100) != HAL_OK)
		{
			return 1;
		}
		UartHandle_Infr.Instance->DR = (*pData++ & (uint8_t)0xFF);
	}
	
	if(UART_WaitOnFlagUntilTimeout(&UartHandle_Infr, UART_FLAG_TXE, RESET, 100) != HAL_OK)
	{
		return 1;
	}
	
	return 0;
}


/**************************************************/
/*** Aplication ***********************************/
/**************************************************/

/**
  * @brief  WT_UART_Infr_Rx_IT
  * @param  uint8_t dat
  * @retval None
  */
static void WT_UART_Infr_Rx_IT(uint8_t dat)
{
//	uint8_t buf8=0;
	
	/* receiver data */
	UART_Infr_Buffer_Rx[UART_Infr_Cnt_Buffer_Rx] = dat;
	if(UART_Infr_Cnt_Buffer_Rx < (UART_Infr_RX_Bufer_Length-2)) UART_Infr_Cnt_Buffer_Rx++;
	
	//??????
	if(UART_Infr_Cnt_Buffer_Rx == 1)
	{
		if(UART_Infr_Buffer_Rx[0] != 0x8E ) 
		{
			UART_Infr_Buffer_RxClear();
			return;
		}
	}
	else //wait frame end
	{
		if(UART_Infr_Cnt_Buffer_Rx >= 5)
		{
			Is_UART_Infra_Rx_Come = 1;
			osMessagePut(UartInfrEvent, UartInfr_RX_Event, 0);	//?????
			//UartCOM2_RX_Process();
		}
	}

}


/**
  * @brief  UartInfr_Send_StartPrint_Cmd
  * @param  None
  * @retval None
  */
void UartInfr_Send_StartInfr_Cmd(void)
{
	uint16_t i;
	uint16_t j=0;
	uint8_t  TxBuffer[5];
	
	
	//send data to PC
	/****** ?? ****************************************************/
	TxBuffer[j++] = 0x8E;
	TxBuffer[j++] = 0x00;	//0-start  1-stop
	TxBuffer[j++] = 0xFF;//??????
	
	/****** CRC-16 ?? ****************************************************/
	i = Data_CRC16_MOSBUS(TxBuffer, 3); //???CRC-16
	TxBuffer[j++] = (i>>8)&0xFF; //CRC-16H
	TxBuffer[j++] = i&0xFF; //CRC-16L

	/****** Send ***********************************************************/
	WT_UART_Infr_WrBuf(TxBuffer, 5);
}

/**
  * @brief  UartInfr_Send_StopInfr_Cmd
  * @param  None
  * @retval None
  */
static void UartInfr_Send_StopInfr_Cmd(void)
{
	uint16_t i;
	uint16_t j=0;
	uint8_t  TxBuffer[5];

	
	//send data to PC
	/****** ?? ****************************************************/
	TxBuffer[j++] = 0x8E;
	TxBuffer[j++] = 0x01;	//0x00-start,0x01-stop
	TxBuffer[j++] = 0xFF;//??????
	
	/****** CRC-16 ?? ****************************************************/
	i = Data_CRC16_MOSBUS(TxBuffer, TxBuffer[1]-2); //???CRC-16
	TxBuffer[j++] = (i>>8)&0xFF; //CRC-16H
	TxBuffer[j++] = i&0xFF; //CRC-16L

	/****** Send ***********************************************************/
	WT_UART_Infr_WrBuf(TxBuffer, 5);
}

/**
  * @brief  UartInfr_Send_StopInfr_Confirm
  * @param  None
  * @retval None
  */
static void UartInfr_Send_StopInfr_Confirm(void)
{
	uint16_t i;
	uint16_t j=0;
	uint8_t  TxBuffer[5];

	
	//send data to PC
	/****** ?? ****************************************************/
	TxBuffer[j++] = 0x8E;
	TxBuffer[j++] = 0x01;	//0x00-start,0x01-stop
	TxBuffer[j++] = 0x00;//??????
	
	/****** CRC-16 ?? ****************************************************/
	i = Data_CRC16_MOSBUS(TxBuffer, TxBuffer[1]-2); //???CRC-16
	TxBuffer[j++] = (i>>8)&0xFF; //CRC-16H
	TxBuffer[j++] = i&0xFF; //CRC-16L

	/****** Send ***********************************************************/
	WT_UART_Infr_WrBuf(TxBuffer, 5);
}




/**
  * @brief  UartInfr_RX_Process
  * @param  None
  * @retval None
  */
static void UartInfr_RX_Process(void)
{
//	static uint16_t cmdline;
	
	//Process
	switch(UART_Infr_Buffer_Rx[1])
	{
		case 0x00:	//发送红外信号
			UartInfr_Send_StopInfr_Cmd();
		  Is_UART_Infra_Rx_Come = 0;
			break;
		case 0x01:	//停止发送红外信号
			UART_Infr_Switch = 1;
		  Is_UART_Infra_Rx_Come = 0;
			UartInfr_Send_StopInfr_Confirm();
			break;

		
		default:
			break;
	}
	
	// clear rx buffer
	UART_Infr_Buffer_RxClear();
}
