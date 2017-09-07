/*
******************************************************************************
* @progect LZY Wire Cube Tester
* @file    wt_uart_COM2.c
* @author  wujun
* @version V1.0.0
* @date    2015-03-23
* @brief   ...
******************************************************************************
*/

/* Define ------------------------------------------------------------------*/
#define  WT_UART_COM2_GLOBALS


/* Includes ------------------------------------------------------------------*/
#include "k_bsp.h"
#include "main.h"


/* Private functions ---------------------------------------------------------*/
static void WT_UART_COM2_Rx_IT(uint8_t dat);
static void UART_COM2_Buffer_RxClear(void);
static void UartCOM2_RX_Process(void);

static uint16_t last_rec;
char repair_PPID[30];  //维修PPID
char print_PPID[30];   //接收到的PPID
char printing_PPID[30]; //实际打印打印PPID
//char product_info[45]; //产品信息
char memberID[15]; //员工工号
char boardID[15]; //导通板编码

uint8_t repairmode_flag = 0;//0-not repair  1-repair mode
uint8_t UserID_flag = 0;//0-测试版信息  1-员工工号
uint8_t UART_COM2_Buffer_Rx[UART_COM2_RX_Bufer_Length];
uint8_t UART_COM2_Cnt_Buffer_Rx;
//uint8_t reportID_flag = 0;
//static uint8_t  IsNewStatus =0;
/**
  * @brief  wire self check task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void UARTCOM2Thread(void const * argument)
{
//	uint8_t i;
//	static uint8_t last_stat = 0;//
//	uint8_t curr_stat = 0;//
	osEvent event;
	
	WT_UART_COM2_Init();	//Init
	UART_COM2_Buffer_RxClear();
	
	
  for( ;; )
  {
		//clear message
		while(1)
		{
			event = osMessageGet( UartCOM2Event, 0);
			if(event.status != osEventMessage) break;
		}
		//wait new message
    event = osMessageGet(UartCOM2Event, osWaitForever );
    
    if( event.status == osEventMessage )
    {
      switch(event.value.v)
      {
				case UartCOM2_RX_Event:
					UartCOM2_RX_Process();
					break;
				
				case UartCOM2_TX_Event:		
//					UartCOM2_Send_StartPrint_Cmd();		
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
  * @brief  WT_UART_COM2_Init
  * @param  None
  * @retval None
  */
void WT_UART_COM2_Init(void)
{
	uint32_t i;
	
	for(i=0;i<UART_COM2_RX_Bufer_Length;i++) UART_COM2_Buffer_Rx[i]=0;
	UART_COM2_Cnt_Buffer_Rx = 0;

  UartHandle_COM2.Instance        = UART_COM2;
  UartHandle_COM2.Init.BaudRate   = 115200;
  UartHandle_COM2.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle_COM2.Init.StopBits   = UART_STOPBITS_1;
  UartHandle_COM2.Init.Parity     = UART_PARITY_NONE;
  UartHandle_COM2.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle_COM2.Init.Mode       = UART_MODE_TX_RX;
  HAL_UART_Init(&UartHandle_COM2);	
}


/**
  * @brief  This function handles UART interrupt request.
  * @param  huart: UART handle
  * @retval None
  */
void WT_UART_COM2_IRQHandler(UART_HandleTypeDef *huart)
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
    //UART_Receive_IT(huart);
		WT_UART_COM2_Rx_IT((uint8_t)(huart->Instance->DR & (uint8_t)0x00FF));	//cndz, 20140723
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
  * @brief  UART_COM2_Buffer_RxClear
  * @param  None
  * @retval None
  */
static void UART_COM2_Buffer_RxClear(void)
{
	uint32_t i;
	
	for(i=0;i<UART_COM2_RX_Bufer_Length;i++) UART_COM2_Buffer_Rx[i]=0;
	UART_COM2_Cnt_Buffer_Rx = 0;
//	Is_UART_COM2_Rx_Come = 0;
}

/**
  * @brief  WT_UART_COM2_Rx
  * @param  uint8_t dat
  * @retval None
  */
uint8_t WT_UART_COM2_WrBuf(uint8_t* pData, uint8_t length)
{
	while(length--)
	{
		if(UART_WaitOnFlagUntilTimeout(&UartHandle_COM2, UART_FLAG_TXE, RESET, 100) != HAL_OK)
		{
			return 1;
		}
		UartHandle_COM2.Instance->DR = (*pData++ & (uint8_t)0xFF);
	}
	
	if(UART_WaitOnFlagUntilTimeout(&UartHandle_COM2, UART_FLAG_TXE, RESET, 100) != HAL_OK)
	{
		return 1;
	}
	
	return 0;
}

/**************************************************/
/*** Aplication ***********************************/
/**************************************************/

/**
  * @brief  WT_UART_COM2_Rx_IT
  * @param  uint8_t dat
  * @retval None
  */
static void WT_UART_COM2_Rx_IT(uint8_t dat)
{
//	uint8_t buf8=0;
	
	/* receiver data */
	UART_COM2_Buffer_Rx[UART_COM2_Cnt_Buffer_Rx] = dat;
	if(UART_COM2_Cnt_Buffer_Rx < (UART_COM2_RX_Bufer_Length-2)) UART_COM2_Cnt_Buffer_Rx++;
	
//	//检测桢头标志
//	if(UART_COM2_Cnt_Buffer_Rx == 1)
//	{
//		if(UART_COM2_Buffer_Rx[0] != 0x7e ) 
//		{
//			UART_COM2_Buffer_RxClear();
//			return;
//		}
//	}
//	else if(UART_COM2_Cnt_Buffer_Rx <= 4) //通信地址、帧格式
//	{
//		//Byte[1] -	帧长度
//		//Byte[2]	-	功能
//		//Byte[3]	-	参数
//		//Byte[4]	-	累加和
//		if(UART_COM2_Cnt_Buffer_Rx == 2)
//		{
//			if((UART_COM2_Buffer_Rx[1] < 4) |													//长度太短
//				 (UART_COM2_Buffer_Rx[1] > UART_COM2_RX_Bufer_Length))	//长度太长
//			{
//				UART_COM2_Buffer_RxClear();
//				return;
//			}
//		}
//	}
//	else //wait frame end
//	{
		if(UART_COM2_Cnt_Buffer_Rx >= 2)
		{
			//Is_UART_COM2_Rx_Come = 1;
			osMessagePut(UartCOM2Event, UartCOM2_RX_Event, 0);	//收到数据帧
			//UartCOM2_RX_Process();
		}
//	}
}

uint8_t com2_printf(char* pData, uint16_t length)
{
	while(length--)
	{
		if(UART_WaitOnFlagUntilTimeout(&UartHandle_COM2, UART_FLAG_TXE, RESET, 100) != HAL_OK)
		{
			return 1;
		}
		UartHandle_COM2.Instance->DR = (*pData++ & (uint8_t)0xFF);
	}
	
	if(UART_WaitOnFlagUntilTimeout(&UartHandle_COM2, UART_FLAG_TXE, RESET, 100) != HAL_OK)
	{
		return 1;
	}
	
	return 0;
}

/**
  * @brief  UartCOM2_RX_Process
  * @param  None
  * @retval None
  */
static void UartCOM2_RX_Process(void)
{
	uint16_t i;

	last_rec = UART_COM2_Cnt_Buffer_Rx;

	
	for(i=0;i<50;i++)
	{
		osDelay(30);
		if(last_rec == UART_COM2_Cnt_Buffer_Rx) break;
		else last_rec = UART_COM2_Cnt_Buffer_Rx;
	}
	if(i < 50) 
	{
		last_rec =0 ;
		if(UART_COM2_Cnt_Buffer_Rx <= 15 )//员工ID/导通板编码
		{
			
			//reportID_flag = 1;
            if(0 == UserID_flag)//0-测试版信息  1-员工工号
            {
                strcpy(boardID,(char *)UART_COM2_Buffer_Rx);
                UserID_flag = 1;
                osMessagePut(Uart24GHzEvent, Uart24GHZ_BOARDID_REPORT_Event, 0);//向IMS服务器发送测试板信息
            }
            else
            {
                strcpy(memberID,(char *)UART_COM2_Buffer_Rx);
                osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSID_REPORT_Event, 0);	//向IMS服务器发送员工ID
            }
		}
    else
		{
			strcpy(repair_PPID,(char *)UART_COM2_Buffer_Rx);
			//osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSREPAIR_Event, 0);	//发送维修信息
			repairmode_flag = 1;//0-not repair  1-repair mode	
		}
		UART_COM2_Buffer_RxClear();

	}
	else UART_COM2_Buffer_RxClear();
}
