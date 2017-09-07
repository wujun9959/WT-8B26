/*
******************************************************************************
* @progect LZY Wire Cube Tester
* @file    wt_uart_COM1.c
* @author  LZY Zhang Manxin
* @version V1.0.0
* @date    2014-12-09
* @brief   ...
******************************************************************************
*/

/* Define ------------------------------------------------------------------*/
#define  WT_UART_COM1_GLOBALS


/* Includes ------------------------------------------------------------------*/
#include "k_bsp.h"
#include "main.h"
#include "tools.h"


/* Private functions ---------------------------------------------------------*/
static void WT_UART_COM1_Rx_IT(uint8_t dat);
static void WT_UART_COM1_Rx_Finish(void);
static void UART_COM1_Buffer_RxClear(void);
static void UartCOM1_RX_Process(void);
static void UartCOM1_Serial_print(void);
static void UartCOM1_Parallel_print(void);
//static void UartCOM1_Send_StopPrint_Cmd(void);
static void UartCOM1_Send_StartPrint_Cmd(void);
//extern void get_system_time(char * date ,char * time);
uint8_t UART_COM1_Buffer_Rx[UART_COM1_RX_Bufer_Length];
uint8_t UART_COM1_Cnt_Buffer_Rx;
//print for tesla
static void UartCOM1_PrintOk(void);
//static void UartCOM1_PrintNG(void);
//static void Update_Print_Tesla(void);
extern uint8_t task_mode; //0-测试模式  1-维修模式
extern char printing_PPID[30];//打印PPID
//extern char product_info[45]; //产品信息
//static uint8_t print_echo;
static uint8_t print_type = 0; // 1-打印ok标签 2-打印NG标签

//print info for samsung
extern void get_system_time(char * date ,char * time);
extern void get_system_date(uint8_t * day ,uint8_t * month, uint16_t * year);
extern void get_teststart_time(char * date ,char * time);
extern void get_teststop_time(char * date ,char * time);
extern char str_mode[20];
static void Update_Print_Samsung(void);
static void Update_Print_Midea(void);
static void Update_Print_IMS(void);

static char stryear[21] = {'R','T','W','X','Y','L','M','Q','S','Z','B','C','D','F','G','H','J','K','M','N'};
static char strmonth[12] = {'1','2','3','4','5','6','7','8','9','A','B','C'};
static char strday[31] = {'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','J','K','L','M','N','P','R','S','T','V','W','X','Y','Z'};
//print info for midea
static char print_ID[78] = "23DA9600482VB96QH6M0001QRCNL01T00101/20160621132015/20160621132016/A094-OK--/";

								
/**
  * @brief  wire self check task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void UARTCOM1Thread(void const * argument)
{
	osEvent event;
	
	WT_UART_COM1_Init();	//Init
	UART_COM1_Buffer_RxClear();

  for( ;; )
  {
		//clear message
		while(1)
		{
			event = osMessageGet( UartCOM1Event, 0);
			if(event.status != osEventMessage) break;
		}
		//wait new message
    event = osMessageGet(UartCOM1Event, osWaitForever );
    
    if( event.status == osEventMessage )
    {
      switch(event.value.v)
      {
				case UartCOM1_RX_Event:
					UartCOM1_RX_Process();//接收打印机反馈信息
					break;
				
				case UartCOM1_TX_Event:	
                    print_type = 1;
					if(WT_Config.Print_Mode == 0)//并口打印
					{						
						//UartCOM1_Send_StartPrint_Cmd();	
                        UartCOM1_Parallel_print();                        
					}
					else  //串口打印
					{

                        UartCOM1_Serial_print();

					}	                    
					break;
				case UartCOM1_TXNG_Event:
                    print_type = 2;
					if(task_mode == 1) break;//维修模式不用打印标签
					//print_mode = 1;//0-print ok  1-print NG
					//UartCOM1_PrintNG();//测试NG也要打印标签
                    UartCOM1_Serial_print();
					break;
				default:
					break;
      }
    }
		else	//error
		{
			osDelay(500);
		}
  }
}


/**
  * @brief  WT_UART_COM1_Init
  * @param  None
  * @retval None
  */
void WT_UART_COM1_Init(void)
{
	uint32_t i;
	
	for(i=0;i<UART_COM1_RX_Bufer_Length;i++) UART_COM1_Buffer_Rx[i]=0;
	UART_COM1_Cnt_Buffer_Rx = 0;

  UartHandle_COM1.Instance        = UART_COM1;
  UartHandle_COM1.Init.BaudRate   = 9600;
  UartHandle_COM1.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle_COM1.Init.StopBits   = UART_STOPBITS_1;
  UartHandle_COM1.Init.Parity     = UART_PARITY_NONE;
  UartHandle_COM1.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle_COM1.Init.Mode       = UART_MODE_TX_RX;
  HAL_UART_Init(&UartHandle_COM1);	
}


/**
  * @brief  This function handles UART interrupt request.
  * @param  huart: UART handle
  * @retval None
  */
void WT_UART_COM1_IRQHandler(UART_HandleTypeDef *huart)
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
		WT_UART_COM1_Rx_IT((uint8_t)(huart->Instance->DR & (uint8_t)0x00FF));	//cndz, 20140723
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE);
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    
	WT_UART_COM1_Rx_Finish();	//wujun, 20170316
    __HAL_UART_CLEAR_IDLEFLAG(huart);
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
  * @brief  UART_COM1_Buffer_RxClear
  * @param  None
  * @retval None
  */
static void UART_COM1_Buffer_RxClear(void)
{
	uint32_t i;
	
	for(i=0;i<UART_COM1_RX_Bufer_Length;i++) UART_COM1_Buffer_Rx[i]=0;
	UART_COM1_Cnt_Buffer_Rx = 0;
//	Is_UART_COM1_Rx_Come = 0;
}

/**
  * @brief  WT_UART_COM1_Rx
  * @param  uint8_t dat
  * @retval None
  */
uint8_t WT_UART_COM1_WrBuf(uint8_t* pData, uint16_t length)
{
	while(length--)
	{
		if(UART_WaitOnFlagUntilTimeout(&UartHandle_COM1, UART_FLAG_TXE, RESET, 100) != HAL_OK)
		{
			return 1;
		}
		UartHandle_COM1.Instance->DR = (*pData++ & (uint8_t)0xFF);
	}
	
	if(UART_WaitOnFlagUntilTimeout(&UartHandle_COM1, UART_FLAG_TXE, RESET, 100) != HAL_OK)
	{
		return 1;
	}
	
	return 0;
}

/**************************************************/
/*** Aplication ***********************************/
/**************************************************/

/**
  * @brief  WT_UART_COM1_Rx_IT
  * @param  uint8_t dat
  * @retval None
  */
static void WT_UART_COM1_Rx_IT(uint8_t dat)
{
//	uint8_t buf8=0;
	
	/* receiver data */
	UART_COM1_Buffer_Rx[UART_COM1_Cnt_Buffer_Rx] = dat;
	if(UART_COM1_Cnt_Buffer_Rx < (UART_COM1_RX_Bufer_Length-2)) UART_COM1_Cnt_Buffer_Rx++;
    
   
	

//	//检测桢头标志
//	if(UART_COM1_Cnt_Buffer_Rx >= 2)//第一个06表示打印机收到指令，第二个06表示打印完成
//	{
//		//osMessagePut(UartCOM1Event, UartCOM1_RX_Event, 10);	//收到数据帧
//		if(UART_COM1_Buffer_Rx[0] == 0x06 && UART_COM1_Buffer_Rx[1] == 0x06)
//		{
//            
//            if(1 == print_type)
//            {
//                osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSPRINTOK_REPORT_Event, 0);	//wifi发送打印OK确认信息
//            }
//            else if(2 == print_type)
//            {                
//                osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSPRINTNG_REPORT_Event, 0);	//wifi发送打印NG确认信息
//            }

//		}
//		else
//		{
//			PrintFile.print_status = 4;//0-stop 1-wait, 2-print ok, 3-print run, 4-print error
//		}
//       
//		UART_COM1_Buffer_RxClear();
//	}

}


/**
  * @brief  Update_Print_Serialnum
		更新打印文件序列号。直接在字符串中替换，避免每次读取文件再替换关键字
  * @param  None
  * @retval None
  */
static void Update_Print_Data()
{
	uint8_t i;
	char sn_sort[5];

	memset(sn_sort,0,5);
	
	for(i=0;i<5;i++)
	{
		sn_sort[i] = printing_PPID[19+i];
	}
	WT_Config.Print_SN = atoi(sn_sort);
	
	//Product_info替换
//	for(i=0;i<15;i++)
//	{
//		PrintFile.PrintFilestr[69+i] = product_info[i];
//		PrintFile.PrintFilestr[107+i] = product_info[15+i];
//		PrintFile.PrintFilestr[145+i] = product_info[30+i];
//	}
	
	//TPN内容替换
	for(i=0;i<12;i++)
	{
		PrintFile->PrintFilestr[190+i] = printing_PPID[1+i];
	}
	//TSN内容替换
	for(i=0;i<10;i++)
	{
		PrintFile->PrintFilestr[232+i] = printing_PPID[14+i];
	}

	//二维码PPID变量替换
	for(i=0;i<25;i++)
	{
		PrintFile->PrintFilestr[263+i] = printing_PPID[i];
	}

}

///**
//  * @brief  Update_Print_Serialnum
//		更新打印文件序列号。直接在字符串中替换，避免每次读取文件再替换关键字
//		流水号变为6位，第一位固定为8或6.==>8代表正常生产良品；6代表不良品需返修
//  * @param  None
//  * @retval None
//  */
//static void Update_Print_DataNG()
//{
//	uint8_t i;
//	char sn_sort[5];

//	memset(sn_sort,0,5);
//	
//	printing_PPID[18] = '6';
//	
//	for(i=0;i<5;i++)
//	{
//		sn_sort[i] = printing_PPID[19+i];
//	}
//	WT_Config.Print_SN = atoi(sn_sort);
//	
//	//Product_info替换
////	for(i=0;i<15;i++)
////	{
////		PrintFile.PrintFilestr[69+i] = product_info[i];
////		PrintFile.PrintFilestr[107+i] = product_info[15+i];
////		PrintFile.PrintFilestr[145+i] = product_info[30+i];
////	}
//	
//	//TPN内容替换
//	for(i=0;i<12;i++)
//	{
//		PrintFile->PrintFilestr[190+i] = printing_PPID[1+i];
//	}
//	//TSN内容替换
//	for(i=0;i<10;i++)
//	{
//		PrintFile->PrintFilestr[232+i] = printing_PPID[14+i];
//	}

//	//二维码PPID变量替换
//	for(i=0;i<25;i++)
//	{
//		PrintFile->PrintFilestr[263+i] = printing_PPID[i];
//	}

//}


/**
  * @brief  接收打印机反馈信息
  * @param  None
  * @retval None
  If an error occurs the printer will send a NACK(15H), followed by the error number to the host.
  If no error, the printer will echo an ACK(06H)
  */
static void UartCOM1_RX_Process(void)
{
  
    //检测桢头标志
    if(UART_COM1_Cnt_Buffer_Rx >= 2)//第一个06表示打印机收到指令，第二个06表示打印完成
    {
        //osMessagePut(UartCOM1Event, UartCOM1_RX_Event, 10);	//收到数据帧
        if(UART_COM1_Buffer_Rx[0] == 0x06 && UART_COM1_Buffer_Rx[1] == 0x06)
        {
            
            if(1 == print_type)
            {
                osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSPRINTOK_REPORT_Event, 0);	//wifi发送打印OK确认信息
            }
            else if(2 == print_type)
            {                
                osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSPRINTNG_REPORT_Event, 0);	//wifi发送打印NG确认信息
            }

        }
        else
        {
            PrintFile->print_status = 4;//0-stop 1-wait, 2-print ok, 3-print run, 4-print error
        }
       
        UART_COM1_Buffer_RxClear();
    } 
	
}

/**
  * @brief  UartCOM1_PrintOk
  * @param  None
  * @retval None
  */
static void UartCOM1_PrintOk(void)
{
//	Update_Print_Date();
//	Update_Print_Serialnum();
	if(WT_Config.IMS_Mode == 0)//本地测试不用替换标签内容
	{
		Update_Print_Data();
	}
	
  //PrintFile.sum_str = strlen((char *)PrintFile.PrintFilestr);
	PrintFile->sum_str = 295;
	/****** Send ***********************************************************/
	WT_UART_COM1_WrBuf(PrintFile->PrintFilestr, PrintFile->sum_str);
//	WT_Config_Serial_Num_Save();//保存打印流水号
	osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSPRINTOK_REPORT_Event, 0);	//wifi发送打印确认信息	
}

///**
//  * @brief  UartCOM1_PrintNG
//  * @param  None
//  * @retval None
//  */
//static void UartCOM1_PrintNG(void)
//{
////	Update_Print_Date();
////	Update_Print_Serialnum();
//	Update_Print_DataNG();
//  PrintFile->sum_str = 295;
//	/****** Send ***********************************************************/
//	WT_UART_COM1_WrBuf(PrintFile->PrintFilestr, PrintFile->sum_str);
////	WT_Config_Serial_Num_Save();//保存打印流水号
//	osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSPRINTNG_REPORT_Event, 0);	//wifi发送打印确认信息	
//}

/**
  * @brief  Update PrintInfo for Media
  * @param  None
  * @retval None
  */
static void Update_Print_Midea()
{
	uint16_t i;
	char date_replace[20];
	char time_replace[20];
	uint8_t day,month;
	uint16_t year;

	uint8_t serial_num[5];
	uint8_t dev_id[5];
//	uint8_t str_ver[3];

	uint16_t printsn = 0;
	
	memset(date_replace,0,20);
	memset(time_replace,0,20);
	get_system_time(date_replace,time_replace);
	get_system_date(&day,&month,&year);
	
	//替换日期
	for(i=0;i<8;i++)
	{
		PrintFile->PrintFilestr[63+i] = date_replace[i];
	}
	//替换时间
	for(i=0;i<8;i++)
	{
		PrintFile->PrintFilestr[76+i] = time_replace[i];
	}

	//替换型号
	if(strlen(str_mode) <= 10)//短型号
	{
		for(i=0;i<10;i++)
		{
			PrintFile->PrintFilestr[139+i] = str_mode[i];
		}
	}
	else
	{
		for(i=0;i<14;i++)
		{
			PrintFile->PrintFilestr[139+i] = str_mode[i];
		}
	}
	
	//流水号
  printsn = WT_PrintSN_Read();
	if(0 == printsn || printsn > 9999) printsn =1;
	//sprintf((char *)serial_num,"%04d",PrintConfig.print_item[index].serial_num);
	sprintf((char *)serial_num,"%04d",printsn);
	//替换流水号
	for(i=0;i<4;i++)
	{
		PrintFile->PrintFilestr[71+i] = serial_num[i];
	}
	//设备编号
	sprintf((char *)dev_id,"%03d",WT_Config.Dev_ID);
	//替换设备ID
	for(i=0;i<3;i++)
	{
		PrintFile->PrintFilestr[112+i] = dev_id[i];
	}
//	//替换软件版本
//	sprintf((char *)str_ver,"%02d",WT_Config.Dev_Version);
//	for(i=0;i<2;i++)
//	{
//		PrintFile.PrintFilestr[158+i] = str_ver[i];
//	}
	
}

/**
  * @brief  Update Printinfo for samsung
  * @param  None
  * @retval None
  */
static void Update_Print_Samsung(void)
{
	uint16_t i;
	char date_replace[20];
	char start_time[20];
	char stop_time[20];
	char test_date[20];
	char str_devid[4];
	char mode_replace[20];
	uint8_t serial_num[5];
	uint8_t mode_len;//线束型号长度
	
	uint8_t day,month;
	uint16_t year;

	uint16_t printsn = 0;
	
	memset(date_replace,0,20);
	memset(start_time,0,20);
	memset(stop_time,0,20);
	memset(test_date,0,20);
	memset(str_devid,0,4);
	memset(serial_num,0,5);
	memset(mode_replace,' ',18);
	
	get_system_time_samsung(date_replace,start_time);
	get_teststart_time(test_date,start_time);
	get_teststop_time(test_date,stop_time);
	get_system_date(&day,&month,&year);

  mode_len = strlen(str_mode);
	strncpy(mode_replace,str_mode,mode_len);
	
	//替换时间
	for(i=0;i<10;i++)
	{
		PrintFile->PrintFilestr[142+i] = date_replace[i];
	}

	//替换型号
	for(i=0;i<10;i++)
	{
		PrintFile->PrintFilestr[109+i] = mode_replace[i];//style1

	}
	
	//替换二维码信息
	for(i=0;i<10;i++)
	{
		print_ID[2+i] = mode_replace[i];
	}
	print_ID[16] = stryear[year-2001];
	print_ID[17] = strmonth[month-1];
	print_ID[18] = strday[day-1];
	
	//流水号
  printsn = WT_PrintSN_Read();
	if(0 == printsn || printsn > 9999) printsn =1;
	//sprintf((char *)serial_num,"%04d",PrintConfig.print_item[index].serial_num);
	sprintf((char *)serial_num,"%04d",printsn);
	//替换流水号
	for(i=0;i<4;i++)
	{
		print_ID[19+i] = serial_num[i];
	}
	//设备编号
	sprintf(str_devid, "%03d", WT_Config.Dev_ID);
	for(i=0;i<3;i++)
	{
		print_ID[31+i] = str_devid[i];
	}
	//print_ID[33] = WT_Config.Dev_ID + 48;//简单将1转换为'1'
	
	//开始测试时间
	for(i=0;i<8;i++)
	{
		print_ID[37 + i] = test_date[i];
	}
	for(i=0;i<6;i++)
	{
		print_ID[45 + i] = start_time[i];
	}
	
	//结束测试时间
	for(i=0;i<8;i++)
	{
		print_ID[52 + i] = test_date[i];
	}
	for(i=0;i<6;i++)
	{
		print_ID[60 + i] = stop_time[i];
	}
	
	for(i=0;i<77;i++)
	{
		PrintFile->PrintFilestr[170+i] = print_ID[i];
	}
	
	if(PrintFile->sum_str > 320)//大标签
	{
		for(i=0;i<4;i++)
		{
			PrintFile->PrintFilestr[270+i] = mode_replace[i];
		}
		
		for(i=0;i<6;i++)
		{
			PrintFile->PrintFilestr[275+i] = mode_replace[i+4];
		}
	}
	
}

/**
  * @brief  Update PrintInfo for IMS
  * @param  None
  * @retval None
  */
static void Update_Print_IMS()
{
	uint16_t i;
	char date_replace[20];
	char time_replace[20];
	uint8_t day,month;
	uint16_t year;

//	uint8_t serial_num[5];
	uint8_t dev_id[5];

	uint8_t ppidnum = 0;
	
	memset(date_replace,0,20);
	memset(time_replace,0,20);
	get_system_time(date_replace,time_replace);
	get_system_date(&day,&month,&year);
	
    
	//替换日期
	for(i=0;i<8;i++)
	{
		PrintFile->PrintFilestr[191+i] = date_replace[i];
	}
	//替换时间
	for(i=0;i<8;i++)
	{
		PrintFile->PrintFilestr[200+i] = time_replace[i];
	}
    
    //替换PPID
	for(i=0;i<strlen(printing_PPID);i++)
	{
		PrintFile->PrintFilestr[144+i] = printing_PPID[i];
	}
    //设备编号
	sprintf((char *)dev_id,"%03d",WT_Config.Dev_ID);
	//替换设备ID
	for(i=0;i<3;i++)
	{
		PrintFile->PrintFilestr[117+i] = dev_id[i];
	}
    //替换二维码内容，如果二维码内容比模板内容短，需要将末尾内容一并替换
    for(i=0;i<strlen(printing_PPID);i++)
	{
        PrintFile->PrintFilestr[261+i] = printing_PPID[i];
	}
    for(i=0;i<strlen(printing_PPID);i++)
	{
        PrintFile->PrintFilestr[261+i] = printing_PPID[i];
	}
    ppidnum = strlen(printing_PPID);
    
    PrintFile->PrintFilestr[261+ppidnum] = 0x22;
    PrintFile->PrintFilestr[261+ppidnum+1] = 0x0D;
    PrintFile->PrintFilestr[261+ppidnum+2] = 0x0A;
    PrintFile->PrintFilestr[261+ppidnum+3] = 0x50;
    PrintFile->PrintFilestr[261+ppidnum+4] = 0x31;
    PrintFile->PrintFilestr[261+ppidnum+5] = 0x0D;
    PrintFile->PrintFilestr[261+ppidnum+6] = 0x0A;

	//替换型号
//	if(strlen(str_mode) <= 10)//短型号
//	{
//		for(i=0;i<10;i++)
//		{
//			PrintFile.PrintFilestr[114+i] = str_mode[i];
//		}
//	}
//	else
//	{
//		for(i=0;i<14;i++)
//		{
//			PrintFile.PrintFilestr[114+i] = str_mode[i];
//		}
//	}
	
//	//流水号
//    printsn = WT_PrintSN_Read();
//	if(0 == printsn || printsn > 9999) printsn =1;
//	//sprintf((char *)serial_num,"%04d",PrintConfig.print_item[index].serial_num);
//	sprintf((char *)serial_num,"%04d",printsn);
//	//替换流水号
//	for(i=0;i<3;i++)
//	{
//		if(WT_Config.IMS_Mode == 0) PrintFile.PrintFilestr[195+i] = printing_PPID[ (strlen(printing_PPID) -4) + i];
//        else PrintFile.PrintFilestr[195+i] = serial_num[i];
//	}
	

    //WT_UART_COM1_WrBuf(PrintFile.PrintFilestr, PrintFile.sum_str);	
    WT_UART_COM1_WrBuf(PrintFile->PrintFilestr, 261+ppidnum+7);

}

/**
  * @brief  UartCOM1_Serial_print
  * @param  None
  * @retval None
  */
static void UartCOM1_Serial_print(void)
{
	uint16_t printsn;

	if(PrintFile->vendor == MIDEA)
	{
		Update_Print_Midea();
	}
	else if(PrintFile->vendor == SAMSUNG)
	{
		Update_Print_Samsung();
	}
	else if(PrintFile->vendor == TESLA)
	{
		if(task_mode == 0)//0-测试模式  1-维修模式
		UartCOM1_PrintOk();//维修模式不用打印标签	
	}
    else if(PrintFile->vendor == IMS)
	{
		Update_Print_IMS();
	}
	else
	{
		Update_Print_Midea();
	}
	//PrintConfig.print_item[index].serial_num++;
	/****** Send ***********************************************************/
	if(PrintFile->vendor != TESLA && PrintFile->vendor != IMS)
	{
		WT_UART_COM1_WrBuf(PrintFile->PrintFilestr, PrintFile->sum_str);
		//WT_Printcfg_Write();
		printsn = WT_PrintSN_Read();
		if(printsn >= 9999) printsn = 0;
		printsn++;
		WT_PrintSN_Write(printsn);
	}
}

/**
  * @brief  UartCOM1_Parallel_print
  * @param  None
  * @retval None
  */
static void UartCOM1_Parallel_print(void)
{
	UartCOM1_Send_StartPrint_Cmd();		
}

/**
  * @brief  UartCOM1_Send_StartPrint_Cmd
  * @param  None
  * @retval None
  */
static void UartCOM1_Send_StartPrint_Cmd(void)
{
	uint16_t i;
	uint16_t j=0;
	uint8_t  TxBuffer[7];
	uint16_t sendbytes=0;
	
	sendbytes = (PrintFile->sum_str/100) + 1;
	
	//send data to PC
	/****** 帧头 ****************************************************/
	TxBuffer[j++] = 0x7e;
	TxBuffer[j++] = 0x07;	//帧长度
	TxBuffer[j++] = 0x01;	//功能，开始发送打印内容命令
	TxBuffer[j++] = (sendbytes>>8)&0xFF;//打印内容行数
	TxBuffer[j++] = sendbytes & 0xFF;
	
	/****** CRC-16 校验 ****************************************************/
	i = Data_CRC16_MOSBUS(TxBuffer, TxBuffer[1]-2); //计算出CRC-16
	TxBuffer[j++] = (i>>8)&0xFF; //CRC-16H
	TxBuffer[j++] = i&0xFF; //CRC-16L

	/****** Send ***********************************************************/
	WT_UART_COM1_WrBuf(TxBuffer, TxBuffer[1]);
	if(PrintFile->vendor == MIDEA)
	{
		Update_Print_Midea();
	}
	else if(PrintFile->vendor == SAMSUNG)
	{
		Update_Print_Samsung();
	}
	else
	{
		Update_Print_Midea();
	}
}

///**
//  * @brief  UartCOM1_Send_Print_Cmd
//  * @param  None
//  * @retval None
//  */
//static void UartCOM1_Send_Print_Cmd(uint16_t cmd_line)
//{
//	uint16_t i;
//	uint16_t j=0;
//	uint8_t TxBuffer[108];
//	uint16_t line=0;
//	uint16_t frame_num = 0;
//	
//	memset(TxBuffer,0,100);
//	frame_num = cmd_line + 1;

//	//send data to Printer
//	/****** 帧头 ****************************************************/
//	TxBuffer[j++] = 0x7e;
//	TxBuffer[j++] = 108;	//帧长度
//	TxBuffer[j++] = 0x02;	//功能，发送打印内容命令
//	TxBuffer[j++] = (frame_num>>8)&0xFF; //帧号
//	TxBuffer[j++] = (frame_num)&0xFF;    //帧号
//	TxBuffer[j++] = 100;//打印行字符串长度

//	for(i=0;i<100;i++)
//	{
//		line = 100*cmd_line +i;
//		if(line < PrintFile->sum_str)
//		{
//			TxBuffer[j++] = PrintFile->PrintFilestr[line];
//		}
//		else TxBuffer[j++] = 0;
//		
//	}
//	
//	/****** CRC-16 校验 ****************************************************/
//	i = Data_CRC16_MOSBUS(TxBuffer, TxBuffer[1]-2); //计算出CRC-16
//	TxBuffer[106] = (i>>8)&0xFF; //CRC-16H
//	TxBuffer[107] = i&0xFF; //CRC-16L

//	/****** Send ***********************************************************/
//	WT_UART_COM1_WrBuf(TxBuffer, TxBuffer[1]);
//}

///**
//  * @brief  UartCOM1_Send_Print_Cmd
//  * @param  None
//  * @retval None
//  */
//static void UartCOM1_Send_StopPrint_Cmd()
//{
//	uint16_t i;
//	uint16_t j=0;
//	uint8_t  TxBuffer[6];
//	
//	//send data to PC
//	/****** 帧头 ****************************************************/
//	TxBuffer[j++] = 0x7e;
//	TxBuffer[j++] = 0x06;	//帧长度
//	TxBuffer[j++] = 0x03;	//功能，结束发送打印内容命令
//	TxBuffer[j++] = 0x5A; //发送文件结束

//	/****** CRC-16 校验 ****************************************************/
//	i = Data_CRC16_MOSBUS(TxBuffer, TxBuffer[1]-2); //计算出CRC-16
//	TxBuffer[j++] = (i>>8)&0xFF; //CRC-16H
//	TxBuffer[j++] = i&0xFF; //CRC-16L

//	/****** Send ***********************************************************/
//	WT_UART_COM1_WrBuf(TxBuffer, TxBuffer[1]);
//}

static void WT_UART_COM1_Rx_Finish(void)
{
    osMessagePut(UartCOM1Event, UartCOM1_RX_Event, 0);	//数据帧接收完成
}
