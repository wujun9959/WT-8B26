/********************************************************************************
	Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      wt_uart_24GHz.c
  Author: wujun      Version:  2.0      Date: 2016.7.28
  Description:    WT-8A46 2.4G function
                  
  Others:          

	Function List:  
    1. ....
  History:        
    1. Date:
       Author:
       Modification:
    2. ...

******************************************************************************/

/* Define ------------------------------------------------------------------*/
#define  WT_UART_24GHZ_GLOBALS


/* Includes ------------------------------------------------------------------*/
#include "k_bsp.h"
#include "main.h"
#include "verision.h"
#include "wt_task_wiretest.h"
#include "tools.h"
//#pragma diag_suppress 870 



static void WT_UART_24GHz_Rx_IT(uint8_t dat);
static void WT_UART_24GHz_Rx_Finish(void);
static uint8_t WT_UART_24GHz_Cnfig(void);
static uint8_t WT_UART_24GHz_Reset(void);
static void Uart24G_RX_Process(void);
static void Commu_RX_Process(void);
static void Wificfg_RX_Process(void);
static void WifiReset_RX_Process(void);

static void Uart24GHz_IMSTEST_Require(void);
static void Uart24GHz_IMSREPAIR_Require(void);	
static void Uart24GHz_IMSTESTOK_Reply(void);	
static void Uart24GHz_IMSREPAIROK_Reply(void);
static void Uart24GHz_IMSTESTNG_Reply(void);	
static void Uart24GHz_IMSREPAIRNG_Reply(void);
static void Uart24GHz_IMSPRINTOK_Report(void);
static void Uart24GHz_IMSPRINTNG_Report(void);
static void Uart24GHz_BoardID_Report(void);

static uint16_t last_rec;
static uint8_t ok_cnt;
static uint8_t cfg_ok_cnt = 0;
static uint8_t reset_mode=0;
static uint8_t config_mode=0;
extern uint8_t gwifi_stat;//0-not connect  1-connect
uint8_t flag_heartbeat = 0;
uint8_t gwifi_connect = 0;
uint8_t flag_userid = 0;//0-not test  1-ok  2-ng
static uint8_t wificfg_mode = 0; // 0-正常数据收发 1-配置wifi 2-wifi reset 

uint8_t UART_24GHz_Buffer_Rx[UART_24GHz_RX_Bufer_Length];
uint8_t task_mode=0; //0-测试模式  1-维修模式
uint8_t test_permit = 0;//0-不允许测试 1-允许测试

//void Create_PPID(char *PPID);
static void Uart24GHz_IMSID_Report(void);

extern char repair_PPID[30];
extern char printing_PPID[30];
extern char print_PPID[30];
//extern char product_info[45]; 

extern uint8_t NG_point1;
extern uint8_t NG_point2;
extern uint8_t NG_type; //0-断路  1-错位  2-短路
extern uint8_t NG_points[8];
extern char memberID[15]; //员工工号
extern char boardID[15]; //测试板卡ID

extern void set_systemtime(uint8_t sec,uint8_t min, uint8_t hour, uint8_t day, uint8_t month,uint16_t year);
extern char *itoa(int num, char *str, int radix);
extern void wt_SetText_Menu(const char * pTitle); 
extern void wt_SetText_Status(const char * pTitle); 

#define TIME_OUT  500

/**
  * @brief  wire self check task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void UART24GHZThread(void const * argument)
{
	osEvent event;
	uint16_t i;
	static uint16_t cnt=0;
	
	WT_UART_24GHz_Init();	//Init
	
//	UART_24GHz_Buffer_RxClear();
//	osDelay(6000);
//	WT_UART_24GHz_Cnfig();	//config
//	osDelay(1000);
	
	
  for( ;; )
  {
    //clear message
    while(1)
    {
        event = osMessageGet( Uart24GHzEvent, 0);
        if(event.status != osEventMessage) break;
    }
    event = osMessageGet(Uart24GHzEvent, osWaitForever );
	//	event = osMessageGet(Uart24GHzEvent, 10000 );
		
    if( event.status == osEventMessage )
    {
      switch(event.value.v)
      {
				case Uart24GHZ_RX_Event:
					Uart24G_RX_Process();
					break;		
				case Uart24GHZ_TXOK_Event://测试结果反馈
					//Uart24GHz_UploadTestRes();
					if(task_mode == 0)//0-测试模式 1-维修模式
					{
						Uart24GHz_IMSTESTOK_Reply();	
					}
					else Uart24GHz_IMSREPAIROK_Reply();	
					break;
				case Uart24GHZ_TXNG_Event://测试结果反馈
					//Uart24GHz_UploadTestRes();
					if(task_mode == 0)//0-测试模式 1-维修模式
					{
						Uart24GHz_IMSTESTNG_Reply();	
					}
					else Uart24GHz_IMSREPAIRNG_Reply();	
					break;
				case Uart24GHZ_CONF_Event:
					BSP_UartNRF_PowerOFF();
					osDelay(2000);
					BSP_UartNRF_PowerON();
					osDelay(3000);
					UART_24GHz_Buffer_RxClear();
					WT_UART_24GHz_Cnfig();	//config
				  if(gwifi_stat == 1) wt_SetText_Status("网络连接OK");
					break;
				case Uart24GHZ_IMSTEST_Event://同IMS Server通信，请求测试
					Uart24GHz_IMSTEST_Require();	
					break;
				case Uart24GHZ_IMSREPAIR_Event://同IMS Server通信，维修测试请求
					Uart24GHz_IMSREPAIR_Require();						
					break;
				case Uart24GHZ_IMSPRINTOK_REPORT_Event:
					Uart24GHz_IMSPRINTOK_Report();						
					break;
				case Uart24GHZ_IMSPRINTNG_REPORT_Event:
					Uart24GHz_IMSPRINTNG_Report();						
					break;
				case Uart24GHZ_IMSID_REPORT_Event://发送员工工号
					Uart24GHz_IMSID_Report();						
					break;
                case Uart24GHZ_BOARDID_REPORT_Event://发送板卡ID
					Uart24GHz_BoardID_Report();						
					break;
                case Uart24GHZ_IMSHEATBEAT_Event:
                    Uart24G_HeartBeat();
                    break;
                case Uart24GHZ_WIFIRESET_Event:
					//BSP_UartNRF_PowerOFF();
                    RST_WIFI_OFF();
					osDelay(2000);
//					WT_UART_24GHz_Init();
                    //BSP_UartNRF_PowerON();
                    RST_WIFI_ON();
					osDelay(4000);
					UART_24GHz_Buffer_RxClear();
					WT_UART_24GHz_Reset();	//config
                    
					break;
				default:
					break;
      }
    }
		else if( event.status == osEventTimeout )//超时重新连接
		{
			last_rec = UART_24GHz_Cnt_Buffer_Rx;
			for(i=0;i<30;i++)
			{
				osDelay(3);
				if(last_rec == UART_24GHz_Cnt_Buffer_Rx ) break;
				else last_rec = UART_24GHz_Cnt_Buffer_Rx;
			}	
			
			if(UART_24GHz_Cnt_Buffer_Rx == 0)
			{
				cnt++;
				//BSP_UartNRF_PowerOFF();
				osDelay(2000);
				WT_UART_24GHz_Init();
				osDelay(1500);
				UART_24GHz_Buffer_RxClear();
				WT_UART_24GHz_Cnfig();	//config
			}
			UART_24GHz_Cnt_Buffer_Rx = 0;
		}
		else	//error
		{
			osDelay(1000);
		}
  }
}


/**
  * @brief  WT_UART_24GHz_Init
  * @param  None
  * @retval None
  */
void WT_UART_24GHz_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	uint32_t i;
	
	for(i=0;i<UART_24GHz_RX_Bufer_Length;i++) UART_24GHz_Buffer_Rx[i]=0;
	UART_24GHz_Cnt_Buffer_Rx = 0;
	Is_UART_24GHz_Rx_Come = 0;
	
    UartHandle_24GHz.Instance        = UART_24GHz;
    UartHandle_24GHz.Init.BaudRate   = 115200;
    UartHandle_24GHz.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle_24GHz.Init.StopBits   = UART_STOPBITS_1;
    UartHandle_24GHz.Init.Parity     = UART_PARITY_NONE;
    UartHandle_24GHz.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle_24GHz.Init.Mode       = UART_MODE_TX_RX;
    HAL_UART_Init(&UartHandle_24GHz);

    /* Enable the PowerSW_WireLess_PIN Clock */
    PowerSW_GPIO_CLK_ENABLE();

    /* Configure the PowerSW_WireLess_PIN  */
    GPIO_InitStruct.Pin = PowerSW_WireLess_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(PowerSW_PORT, &GPIO_InitStruct);
	BSP_UartNRF_PowerON();
    
    /* Enable the RSTWIFI_PIN Clock */
    RST_WIFI_GPIO_CLK_ENABLE();

    /* Configure the RSTWIFI_PIN  */
    GPIO_InitStruct.Pin = RST_WIFI_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(RST_WIFI_PORT, &GPIO_InitStruct);
	RST_WIFI_ON();
}


/**
  * @brief  This function handles UART interrupt request.
  * @param  huart: UART handle
  * @retval None
  */
void WT_UART_24GHz_IRQHandler(UART_HandleTypeDef *huart)
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
		WT_UART_24GHz_Rx_IT((uint8_t)(huart->Instance->DR & (uint8_t)0x00FF));	//cndz, 20140723
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE);
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    
	WT_UART_24GHz_Rx_Finish();	//wujun, 20170316
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
  * @brief  WT_UART_24GHz_Rx
  * @param  uint8_t dat
  * @retval None
  */
static void WT_UART_24GHz_Rx_IT(uint8_t dat)
{
	/* receiver data */
	UART_24GHz_Buffer_Rx[UART_24GHz_Cnt_Buffer_Rx] = dat;
	if(UART_24GHz_Cnt_Buffer_Rx < (UART_24GHz_RX_Bufer_Length-2)) UART_24GHz_Cnt_Buffer_Rx++;

//	if(UART_24GHz_Cnt_Buffer_Rx >=3 )
//	{
//		//Is_UART_COM2_Rx_Come = 1;
//		osMessagePut(Uart24GHzEvent, Uart24GHZ_RX_Event, 0);	//收到数据帧
//		//UartCOM2_RX_Process();
//	}

}

/**
  * @brief  UART_24GHz_Buffer_RxClear
  * @param  None
  * @retval None
  */
static void UART_24GHz_Buffer_RxClear(void)
{
	uint32_t i;
	
	for(i=0;i<UART_24GHz_RX_Bufer_Length;i++) UART_24GHz_Buffer_Rx[i]=0;
	UART_24GHz_Cnt_Buffer_Rx = 0;
	Is_UART_24GHz_Rx_Come = 0;
}

/**
  * @brief  WT_UART_24GHz_Rx
  * @param  uint8_t dat
  * @retval None
  */
uint8_t WT_UART_24GHz_WrBuf(uint8_t* pData, uint8_t length)
{
	while(length--)
	{
		if(UART_WaitOnFlagUntilTimeout(&UartHandle_24GHz, UART_FLAG_TXE, RESET, 100) != HAL_OK)
		{
			return 1;
		}
		UartHandle_24GHz.Instance->DR = (*pData++ & (uint8_t)0xFF);
	}
	
	//if(UART_WaitOnFlagUntilTimeout(&UartHandle_24GHz, UART_FLAG_TXE, RESET, 100) != HAL_OK)
	if(UART_WaitOnFlagUntilTimeout(&UartHandle_24GHz, UART_FLAG_TXE, RESET, 100) != HAL_OK)
	{
		return 1;
	}
	
	return 0;
}


static void WT_GetIP(char *buff)
{
	char * ptr;	
	uint8_t index = 0;
	strtok(buff,",");	
		index=0;
		while(1)
		{
			ptr=strtok(NULL,".,\"");
			if(ptr == 0) break;
			switch(index)
			{
				case 0:
					index++;
					WT_Config.IP_Addr[0]= atoi(ptr);
					break;
				case 1:
					index++;
					WT_Config.IP_Addr[1]= atoi(ptr);
					break;
				case 2:
					index++;
					WT_Config.IP_Addr[2]= atoi(ptr);
					break;
				case 3:
					index++;
					WT_Config.IP_Addr[3]= atoi(ptr);
					break;
				default:
					break;
			}
		}
}

static void WT_GetMAC(char *buff)
{
	uint8_t i=0;
	char ptr[2];
	for(i=0;i<6;i++)
	{
		strncpy(ptr,&buff[4+i*2],2);
		WT_Config.MAC_Addr[i]=strtol(ptr,NULL,16);
	}
	
}

static uint16_t WT_GetSockID(char *buff)
{
	uint16_t sockid=0;
	char ptr[8];
    if(strlen(buff) < 5) return 1;
	strcpy(ptr,&buff[4]);
	sockid = atoi(ptr);
	return sockid;
}

static uint8_t WT_UART_24GHz_Cnfig(void)
{
	char cmd[50];
	
	gwifi_stat = 0;//0-not connect  1-connect
    gwifi_connect = 0;
	cfg_ok_cnt = 0;
	memset(cmd,0,50);

	sprintf(cmd,"AT+SSID=\"%s\"\r\n",(char *)WT_Config.NetWork);
	
	WT_UART_24GHz_WrBuf((uint8_t *)cmd, strlen(cmd));	
    wificfg_mode = 1; // 0-正常数据收发 1-配置wifi 2-wifi reset 
	return 0;
}


/**
  * @brief  Wifi模块重连
  * @param  None
  * @retval None
  */
static uint8_t WT_UART_24GHz_Reset(void)
{
	gwifi_stat = 0;//0-not connect  1-connect
    gwifi_connect = 0;
    ok_cnt = 0;
    
    WT_UART_24GHz_WrBuf((uint8_t *)"AT+WJOIN\r\n", 10);
    wificfg_mode = 2; // 0-正常数据收发 1-配置wifi 2-wifi reset 
    return 0;
}


/**
  * @brief  Uart24G_RX_Process
  * @param  None
  * @retval None
  */
static void Uart24G_RX_Process(void)
{
//	uint16_t i;
   
    switch(wificfg_mode)// 0-正常数据收发 1-配置wifi 2-wifi reset 
    {
        case 0:
            Commu_RX_Process();
            break;
        case 1:
            Wificfg_RX_Process();
            break;
        case 2:
            WifiReset_RX_Process();
            break;
        default:
            break;
    }
        
   
		
	UART_24GHz_Buffer_RxClear();


}

/**
  * @brief  Uart24GHz_HeatBeat
  * @param  None
  * @retval None
  */
static void Uart24G_HeartBeat(void)
{
	uint16_t i;
	uint16_t j=0;
	char  TxBuffer[20];
    char  Ipaddr[15];
	
    memset(TxBuffer,0,20);
	//return data to PC
	/****** 帧头 ****************************************************/
	TxBuffer[j++] = '0';	//Logo
	TxBuffer[j++] = '7';
	TxBuffer[j++] = '&';
    sprintf(Ipaddr,"%d.%d.%d.%d",WT_Config.IP_Addr[0],WT_Config.IP_Addr[1],WT_Config.IP_Addr[2],WT_Config.IP_Addr[3]);
    for(i=0;i<strlen(Ipaddr);i++)
    {
        TxBuffer[j++] = Ipaddr[i];
    }
    TxBuffer[j++] = '@';
    
	/****** Send ***********************************************************/
	WT_UART_24GHz_WrBuf((uint8_t *)TxBuffer, strlen(TxBuffer));
    flag_heartbeat = 0;
}



/**
* @brief   同IMS服务器通信，设备调用程序，将程序名及设备ID反馈IMS，案例： 03&7999191 &DTJ00001@
  * @param  None
  * @retval None
  */
static void Uart24GHz_IMSTEST_Require(void)
{
	uint16_t i=0;
	uint16_t j=0;
	uint8_t  TxBuffer[30];
	uint8_t  filename[30];
    char  strnum[5];
    uint8_t  dev_id[5];
	memset(TxBuffer,0,30);
	memset(filename,0,30);
    memset(strnum,0,5);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	//Logo
	TxBuffer[i++] = '3';
	TxBuffer[i++] = '&';
	
	if(strlen((char *)TestFile->FileName)>0)
    {
		strncpy((char *)filename,(char *)TestFile->FileName,strlen((char *)TestFile->FileName)-4);
		for(j=0;j<strlen((char *)filename);j++)
		{
			TxBuffer[i++] = filename[j];
		}
        TxBuffer[i++] = '&';//结束符

	}
    TxBuffer[i++] = 'D';	//Logo
	TxBuffer[i++] = 'T';
	TxBuffer[i++] = 'J';
    TxBuffer[i++] = '-';
    //????
    sprintf((char *)dev_id,"%03d",WT_Config.Dev_ID);
	//????ID
	for(j=0;j<3;j++)
	{
		TxBuffer[i++] = dev_id[j];
	}
    TxBuffer[i++] = '@';//???
    WT_UART_24GHz_WrBuf(TxBuffer, i);


}

/**
* @brief   同IMS服务器通信，测试调用程序，扫描 PPID ，并将程序名以及 PPID 反馈给 IMS ，案例：02&C0021512190002&82342313
  * @param  None
  * @retval None
  */
static void Uart24GHz_IMSREPAIR_Require(void)
{
	uint16_t i=0;
	uint16_t j=0;
	uint8_t  TxBuffer[60];
	uint8_t  filename[30];
//    uint8_t  strnum[5];
    uint8_t  dev_id[5];
//	uint8_t  TxCnt = 0;
//	memset(TxBuffer,0,60);
	memset(filename,0,30);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	//Logo
	TxBuffer[i++] = '2';	//Logo
	TxBuffer[i++] = '&';
	
	//PPID
	for(j=0;j<strlen(repair_PPID);j++)
	{
		TxBuffer[i++] = repair_PPID[j];
	}
	
	TxBuffer[i++] = '&';
	//设备编号
    sprintf((char *)dev_id,"%03d",WT_Config.Dev_ID);
	//替换设备ID
	for(j=0;j<3;j++)
	{
		TxBuffer[i++] = dev_id[j];
	}
	
	TxBuffer[i++] = '@';//结束符
	/****** Send ***********************************************************/
	WT_UART_24GHz_WrBuf(TxBuffer, i);
	
}


/**
* @brief   测试OK结果反馈
  *发送数据包格式：01&Y@
  * @param  None
  * @retval None
  */
static void Uart24GHz_IMSTESTOK_Reply(void)
{
	uint16_t i=0;
	uint16_t j=0;
	uint8_t  TxBuffer[60];
	uint8_t  filename[30];
//    char  strnum[5];
	memset(TxBuffer,0,60);
	memset(filename,0,30);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	
	TxBuffer[i++] = '1';	
	TxBuffer[i++] = '&';
	//测试结果
	TxBuffer[i++] = 'Y';
    TxBuffer[i++] = '&';
	//PPID
	//Create_PPID((char *)PPID);
	for(j=0;j<strlen(print_PPID);j++)
	{
		TxBuffer[i++] = print_PPID[j];
	}
    TxBuffer[i++] = '@';//结束符
	/****** Send ***********************************************************/
	WT_UART_24GHz_WrBuf(TxBuffer, i);
}

/**
* @brief   测试NG结果反馈
  *发送数据包格式：01&N&错误点位（英文逗号区分不同点位）@
  * @param  None
  * @retval None
  */
static void Uart24GHz_IMSTESTNG_Reply(void)
{
	uint16_t i=0;
	uint16_t j=0;
	uint8_t  TxBuffer[50];
	uint8_t  filename[30];
//    char  strnum[5];
	memset(TxBuffer,0,50);
	memset(filename,0,30);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	//Logo
	TxBuffer[i++] = '1';	//Logo
	TxBuffer[i++] = '&';
	//测试结果
    TxBuffer[i++] = 'N';
    TxBuffer[i++] = '&';
	//PPID
	for(j=0;j<strlen(print_PPID);j++)
	{
		TxBuffer[i++] = print_PPID[j];
	}

	TxBuffer[i++] = '&';
	//错误类型
	TxBuffer[i++] = '&';
	TxBuffer[i++] = NG_type;
	//错误点位
	TxBuffer[i++] = '&';
	for(j=0;j<strlen((char *)NG_points);j++)
	{
		TxBuffer[i++] = NG_points[j];
	}

    TxBuffer[i++] = '@';//结束符
//	TxBuffer[i++] = NG_point1;
//	TxBuffer[i++] = NG_point2;
	/****** Send ***********************************************************/
	WT_UART_24GHz_WrBuf(TxBuffer, i);
}

/**
* @brief   维修结果反馈
  * @param  None
  * @retval None
  */
static void Uart24GHz_IMSREPAIROK_Reply(void)
{
	uint16_t i=0;
	uint16_t j=0;
	uint8_t  TxBuffer[50];
	memset(TxBuffer,0,50);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	//Logo
	TxBuffer[i++] = '2';	//Logo
	TxBuffer[i++] = '&';
	
	//PPID
	for(j=0;j<strlen(repair_PPID);j++)
	{
		TxBuffer[i++] = repair_PPID[j];
	}
	
	TxBuffer[i++] = '&';
	//测试结果

	TxBuffer[i++] = 'Y';
    TxBuffer[i++] = '@';//结束符
	/****** Send ***********************************************************/
	//WT_UART_24GHz_WrBuf(TxBuffer, strlen((char *)TxBuffer));
	WT_UART_24GHz_WrBuf(TxBuffer, i);
}

/**
* @brief   维修结果反馈
  * @param  None
  * @retval None
  */
static void Uart24GHz_IMSREPAIRNG_Reply(void)
{
	uint16_t i=0;
	uint16_t j=0;
	uint8_t  TxBuffer[50];
	memset(TxBuffer,0,50);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	//Logo
	TxBuffer[i++] = '2';	//Logo
	TxBuffer[i++] = '&';
	
	//PPID
	for(j=0;j<strlen(repair_PPID);j++)
	{
		TxBuffer[i++] = repair_PPID[j];
	}
	
	TxBuffer[i++] = '&';
	//测试结果

	TxBuffer[i++] = 'N';

    TxBuffer[i++] = '@';//结束符
	/****** Send ***********************************************************/
	//WT_UART_24GHz_WrBuf(TxBuffer, strlen((char *)TxBuffer));
	WT_UART_24GHz_WrBuf(TxBuffer, i);
}

/**
* @brief   打印OK确认回复
  * @param  None
  * @retval None
  */
static void Uart24GHz_IMSPRINTOK_Report(void)
{
	uint8_t i=0;
	uint8_t j=0;
	uint8_t  TxBuffer[40];
	memset(TxBuffer,0,40);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	//Logo
	TxBuffer[i++] = '5';	//Logo
	TxBuffer[i++] = '&';
	TxBuffer[i++] = 'Y';
	TxBuffer[i++] = '&';
	for(j=0;j<strlen(printing_PPID);j++)
	{
		TxBuffer[i++] = printing_PPID[j];
	}

    TxBuffer[i++] = '@';//结束符
	/****** Send ***********************************************************/
	WT_UART_24GHz_WrBuf(TxBuffer, i);
    PrintFile->print_status = 2;//0-stop 1-wait, 2-print ok, 3-print run, 4-print error
}

/**
* @brief   打印NG确认回复
  * @param  None
  * @retval None
  */
static void Uart24GHz_IMSPRINTNG_Report(void)
{
	uint8_t i=0;
	uint8_t j=0;
	uint8_t  TxBuffer[40];
	memset(TxBuffer,0,40);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	//Logo
	TxBuffer[i++] = '5';	//Logo
	TxBuffer[i++] = '&';
	TxBuffer[i++] = 'N';
	TxBuffer[i++] = '&';
	for(j=0;j<strlen(printing_PPID);j++)
	{
		TxBuffer[i++] = printing_PPID[j];
	}
	//错误类型
	TxBuffer[i++] = '&';
	TxBuffer[i++] = NG_type;
	//错误点位
	TxBuffer[i++] = '&';
	for(j=0;j<strlen((char *)NG_points);j++)
	{
		TxBuffer[i++] = NG_points[j];
	}
    TxBuffer[i++] = '@';//结束符
	/****** Send ***********************************************************/
	WT_UART_24GHz_WrBuf(TxBuffer, i);
    PrintFile->print_status = 2;//0-stop 1-wait, 2-print ok, 3-print run, 4-print error
}

/**
* @brief   提交员工工号
  * @param  None
  * @retval None
  */
static void Uart24GHz_IMSID_Report(void)
{
	uint8_t i=0;
	uint8_t j=0;
	uint8_t  TxBuffer[15];
	memset(TxBuffer,0,15);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	//Logo
	TxBuffer[i++] = '6';	//Logo
	TxBuffer[i++] = '&';
	for(j=0;j<strlen(memberID);j++)
	{
		TxBuffer[i++] = memberID[j];
	}
    
    TxBuffer[i++] = '@';//结束符
	/****** Send ***********************************************************/
	WT_UART_24GHz_WrBuf(TxBuffer, i);
}

/**
* @brief   提交测试板ID  :09&DTB001@
  * @param  None
  * @retval None
  */
static void Uart24GHz_BoardID_Report(void)
{
	uint8_t i=0;
	uint8_t j=0;
	uint8_t  TxBuffer[15];
	memset(TxBuffer,0,15);
	
	/****** 帧头 ****************************************************/
	TxBuffer[i++] = '0';	//
	TxBuffer[i++] = '9';	//
	TxBuffer[i++] = '&';
	for(j=0;j<strlen(boardID);j++)
	{
		TxBuffer[i++] = boardID[j];
	}
    
    TxBuffer[i++] = '@';//结束符
	/****** Send ***********************************************************/
	WT_UART_24GHz_WrBuf(TxBuffer, i);
}

static void WT_UART_24GHz_Rx_Finish(void)
{
   osMessagePut(Uart24GHzEvent, Uart24GHZ_RX_Event, 0);	//收到数据帧   
}

/**
* @brief   通信协议数据收发
  * @param  None
  * @retval None
  */
static void Commu_RX_Process(void)
{
     uint8_t index;
//    uint8_t rxbuf_len = 0;
    char *ptr;
    
    if(	UART_24GHz_Buffer_Rx[0] == '0' && UART_24GHz_Buffer_Rx[1] == '3' && UART_24GHz_Buffer_Rx[2] == '&'  )//01代表OK,02代表NG
    {
        task_mode	= 0;//0-测试模式 1-维修模式
        flag_heartbeat = 1;
        if(UART_24GHz_Buffer_Rx[3] == 'Y')//符合要求，开始测试
        {
            test_permit = 1; //0-不允许测试 1-允许测试
            memset(print_PPID,0,30);
            //获取PPID   3&Y&P1065835-00-C:SA15L0000001
            strtok((char *)UART_24GHz_Buffer_Rx,"&@");
            index=0;
            while(1)
            {
                ptr=strtok(NULL,"&@");
                if(ptr == 0) break;
                
                switch(index)
                {
                    case 0:
                        index++;
                        break;
                    case 1:
                        strcpy(print_PPID,ptr);
                        index++;
                        break;

                    default:
                        break;
                }
            }
        }
        else
        {
            wt_SetText_Status("程序名错误");
            test_permit = 0; //0-不允许测试 1-允许测试
        }
    }
    else if(UART_24GHz_Buffer_Rx[0] == '0' && UART_24GHz_Buffer_Rx[1] == '2' && UART_24GHz_Buffer_Rx[2] == '&')
    {
        task_mode	= 1;//0-测试模式 1-维修模式
        flag_heartbeat = 1;
        if(UART_24GHz_Buffer_Rx[3] == 'Y')//维修结果反馈
        {
            //osMessagePut(WireTestEvent, WIRETEST_START_EVENT, 0);//开始测试
            test_permit = 1; //0-不允许测试 1-允许测试
        }
        else
        {
            wt_SetText_Status("程序名错误");
            test_permit = 0; //0-不允许测试 1-允许测试
        }
    }
    else if(UART_24GHz_Buffer_Rx[0] == '0' && UART_24GHz_Buffer_Rx[1] == '4' && UART_24GHz_Buffer_Rx[2] == '&' )
    {
        memset(printing_PPID,0,30);
        flag_heartbeat = 1;

        //获取PPID   3&Y&P1065835-00-C:SA15L0000001
        strtok((char *)UART_24GHz_Buffer_Rx,"&@");
        index=0;
        while(1)
        {
            ptr=strtok(NULL,"&@");
            if(ptr == 0) break;
            
            switch(index)
            {
                case 0:
                    index++;
                    break;
                case 1:
                    strcpy(printing_PPID,ptr);
                    index++;
                    break;
                default:
                    break;
            }
        }
        if(UART_24GHz_Buffer_Rx[3] == 'Y')
        {
            if(WT_Config.Print == 1 ) osMessagePut(UartCOM1Event, UartCOM1_TX_Event, 0);//本地打印OK标签
        }
        else 
        {
            if(WT_Config.Print == 1 ) osMessagePut(UartCOM1Event, UartCOM1_TXNG_Event, 0);//本地打印NG标签
        }
    }
    else if(	(UART_24GHz_Buffer_Rx[0] == '+') && (UART_24GHz_Buffer_Rx[1] == 'O') && (UART_24GHz_Buffer_Rx[2] == 'K') 
           && UART_24GHz_Buffer_Rx[7] == '0' && UART_24GHz_Buffer_Rx[8] == '3' && UART_24GHz_Buffer_Rx[9] == '&' )
    {
        if( UART_24GHz_Buffer_Rx[10] == 'Y')
        {
            test_permit = 1; //0-不允许测试 1-允许测试
            flag_heartbeat = 1;
            memset(print_PPID,0,30);
            //获取PPID   3&Y&P1065835-00-C:SA15L0000001
            strtok((char *)UART_24GHz_Buffer_Rx,"&@");
            index=0;
            while(1)
            {
                ptr=strtok(NULL,"&@");
                if(ptr == 0) break;
                
                switch(index)
                {
                    case 0:
                        index++;
                        break;
                    case 1:
                        strcpy(print_PPID,ptr);
                        index++;
                        break;
                    default:
                        break;
                }
            }
        }
        else
        {
            wt_SetText_Status("程序名错误");
            test_permit = 0; //0-不允许测试 1-允许测试
        }
    }
    else if( (UART_24GHz_Buffer_Rx[0] == '0') && (UART_24GHz_Buffer_Rx[1] == '7') && (UART_24GHz_Buffer_Rx[2] == '&'))//心跳报文回复
    {
        flag_heartbeat = 1;
    }
    else if( (UART_24GHz_Buffer_Rx[0] == '+') && (UART_24GHz_Buffer_Rx[1] == 'O') && (UART_24GHz_Buffer_Rx[2] == 'K') 
           && UART_24GHz_Buffer_Rx[7] == '0' && UART_24GHz_Buffer_Rx[8] == '7' && UART_24GHz_Buffer_Rx[9] == '&' )
    {
        flag_heartbeat = 1;
    }
    else if( UART_24GHz_Buffer_Rx[7] == '0' && UART_24GHz_Buffer_Rx[8] == '7' && UART_24GHz_Buffer_Rx[9] == '&' )
    {
        flag_heartbeat = 1;
    }
    else if( (UART_24GHz_Buffer_Rx[0] == '0') && (UART_24GHz_Buffer_Rx[1] == '6') && (UART_24GHz_Buffer_Rx[2] == '&'))//用户ID回复
    {
        flag_heartbeat = 1;
        if( UART_24GHz_Buffer_Rx[3] == 'Y')
        flag_userid = 1;//0-not test  1-ok  2-ng
        else
        flag_userid = 2;  
    }
    else if( (UART_24GHz_Buffer_Rx[0] == '+') && (UART_24GHz_Buffer_Rx[1] == 'O') && (UART_24GHz_Buffer_Rx[2] == 'K') 
           && UART_24GHz_Buffer_Rx[7] == '0' && UART_24GHz_Buffer_Rx[8] == '6' && UART_24GHz_Buffer_Rx[9] == '&' )
    {
        flag_heartbeat = 1;
        if( UART_24GHz_Buffer_Rx[10] == 'Y')
        flag_userid = 1;//0-not test  1-ok  2-ng
        else
        flag_userid = 2;  
    }
    else
    {
        flag_heartbeat = 1; 
    }
}

/**
* @brief   配置wifi数据收发
  * @param  None
  * @retval None
  */
static void Wificfg_RX_Process(void)
{
	//uint16_t i;
	//uint8_t mode=0;
	uint16_t sock_Id=0;
	char buff[30];
    char cmd[50];
	
	//char res[20];
	char serv_ip[20];
	
	//memset(res,0,20);
    memset(cmd,0,50);
	memset(serv_ip,0,20);
	
	
    memset(buff,0,30);
    strncpy(buff,(char *)UART_24GHz_Buffer_Rx,30);

    //接收完成，成功、失败
    if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==0) 
    {
        config_mode=1;
        cfg_ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==1) 
    {
        config_mode=2;
        cfg_ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==2) 
    {
        config_mode=3;
        cfg_ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==3) 
    {
        config_mode=4;
        cfg_ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==4) 
    {
        config_mode=5;
        cfg_ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==5) 
    {
        WT_GetIP(buff);
        config_mode=6;
        //WT_Config_Ipaddr_Save();//防止重复写入导致存储坏掉
        cfg_ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==6) 
    {
        WT_GetMAC(buff);
        config_mode=7;
        //WT_Config_MAC_Save();
        cfg_ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==7) 
    {
        sock_Id = WT_GetSockID(buff);
        config_mode=8;
        cfg_ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==8) 
    {
        config_mode=9;
        cfg_ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && cfg_ok_cnt==9) 
    {
        cfg_ok_cnt=0;
        config_mode = 0;
        //return 0;
    }
    else config_mode=10;

    //clear rx buffer
    UART_24GHz_Buffer_RxClear();

    //send new command
    switch(config_mode)
    {					
        case 1:	//配置KEY
            memset(cmd,0,50);
            sprintf(cmd,"AT+KEY=1,0,\"%s\"\r\n",(char *)WT_Config.SecKey);
            WT_UART_24GHz_WrBuf((uint8_t *)cmd, strlen(cmd));
            break;
        case 2:	//KEY OK
            WT_UART_24GHz_WrBuf((uint8_t *)"AT+PMTF\r\n", 9);
            //osDelay(TIME_OUT);
            break;
        case 3:	//write flash OK
            WT_UART_24GHz_WrBuf((uint8_t *)"AT+Z\r\n", 6);
//            osDelay(TIME_OUT);
            break;
        case 4:	//reboot OK
            osDelay(1000);
            WT_UART_24GHz_WrBuf((uint8_t *)"AT+WJOIN\r\n", 10);
            break;
        case 5:	//查询IP
            osDelay(TIME_OUT);
            WT_UART_24GHz_WrBuf((uint8_t *)"AT+LKSTT=?\r\n", 12);
            break;
        case 6:	//查询MAC
            WT_UART_24GHz_WrBuf((uint8_t *)"AT+QMAC=?\r\n", 11);
//            osDelay(TIME_OUT);
            break;
        case 7:	//join OK
            memset(cmd,0,50);
            sprintf(serv_ip,"%d.%d.%d.%d",WT_Config.Server_IP[0],WT_Config.Server_IP[1],WT_Config.Server_IP[2],WT_Config.Server_IP[3]);
            sprintf(cmd,"AT+SKCT=0,0,%s,%d,%d\r\n",serv_ip,WT_Config.TCP_Port,WT_Config.TCP_Port+WT_Config.Dev_ID);
            WT_UART_24GHz_WrBuf((uint8_t *)cmd, strlen(cmd));
 //           osDelay(TIME_OUT);
            break;
        case 8:	//设置系统默认发送的socket
            memset(cmd,0,50);			
            sprintf(cmd,"AT+SKSDF=%d\r\n",sock_Id);
            WT_UART_24GHz_WrBuf((uint8_t *)cmd, strlen(cmd));
//            osDelay(TIME_OUT);
            break;
        case 9:	//设置透传模式
            WT_UART_24GHz_WrBuf((uint8_t *)"AT+ENTM\r\n", 9);
            gwifi_stat = 1;
            gwifi_connect = 1;
            wificfg_mode = 0; // 0-正常数据收发 1-配置wifi 2-wifi reset 
            //flag_wifi = 1;
            //WT_UART_24GHz_WrBuf((uint8_t *)"AT+SKSTT=1\r\n", 12);
            break;
        default:	
            cfg_ok_cnt = 0;	
            config_mode = 0;     
            break;
    }
}
    /**
* @brief  wifi reset数据收发
  * @param  None
  * @retval None
  */
static void WifiReset_RX_Process(void)
{
    //uint16_t i;
	//uint8_t mode=0;
	uint16_t sock_Id=0;
	char buff[30];
	char cmd[50];
	char serv_ip[20];
	
	memset(cmd,0,50);
	memset(serv_ip,0,20);	
    memset(buff,0,30);
    strncpy(buff,(char *)UART_24GHz_Buffer_Rx,30);
    
    //接收完成，成功、失败
    if(strncmp(buff,"+OK",3)==0 && ok_cnt==0) //join ok
    {
        reset_mode=1;
        ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && ok_cnt==1) 
    {
        WT_GetIP(buff);
        reset_mode=2;
        ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && ok_cnt==2) 
    {
        WT_GetMAC(buff);
        reset_mode=3;
        ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && ok_cnt==3) 
    {					
        
        sock_Id = WT_GetSockID(buff);
        reset_mode=4;
        ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && ok_cnt==4) 
    {				
        
        reset_mode=5;
        ok_cnt++;
    }
    else if(strncmp(buff,"+OK",3)==0 && ok_cnt==5) 
    {
        ok_cnt=0;
        //return 0;
    }
    else reset_mode=10;
    
    //clear rx buffer
    UART_24GHz_Buffer_RxClear();
    
    //send new command
    switch(reset_mode)
    {					
        
        case 1:	//查询IP
            osDelay(TIME_OUT);
            WT_UART_24GHz_WrBuf((uint8_t *)"AT+LKSTT=?\r\n", 12);
            break;
        case 2:	//查询MAC
            WT_UART_24GHz_WrBuf((uint8_t *)"AT+QMAC=?\r\n", 11);
            //osDelay(TIME_OUT);
            break;
        case 3:	//建立TCP连接
            memset(cmd,0,50);
            sprintf(serv_ip,"%d.%d.%d.%d",WT_Config.Server_IP[0],WT_Config.Server_IP[1],WT_Config.Server_IP[2],WT_Config.Server_IP[3]);
            sprintf(cmd,"AT+SKCT=0,0,%s,%d,%d\r\n",serv_ip,WT_Config.TCP_Port,WT_Config.TCP_Port+WT_Config.Dev_ID);
            WT_UART_24GHz_WrBuf((uint8_t *)cmd, strlen(cmd));
            //osDelay(TIME_OUT);
            break;
        case 4:	//设置系统默认发送的socket
            memset(cmd,0,50);			
            sprintf(cmd,"AT+SKSDF=%d\r\n",sock_Id);
            WT_UART_24GHz_WrBuf((uint8_t *)cmd, strlen(cmd));
            //osDelay(TIME_OUT);
            break;
        case 5:	//设置透传模式
            WT_UART_24GHz_WrBuf((uint8_t *)"AT+ENTM\r\n", 9);
            gwifi_stat = 1;
            gwifi_connect = 1;
            wificfg_mode = 0; // 0-正常数据收发 1-配置wifi 2-wifi reset 
            if(gwifi_stat == 1) wt_SetText_Status("网络连接OK");
            //flag_wifi = 1;
            //WT_UART_24GHz_WrBuf((uint8_t *)"AT+SKSTT=1\r\n", 12);
            break;
        case 10: //重新连接
            ok_cnt = 0;
            reset_mode = 0;
            //return 0;//退出连接状态
            break;
        default:	
            ok_cnt = 0;	
            reset_mode = 0;       
            break;
    }
    //osDelay(50);

}
