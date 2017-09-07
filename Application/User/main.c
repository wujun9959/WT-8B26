/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    26-February-2014
  * @brief   This file provides main program functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "wt_bsp.h" 
#include "k_log.h"  

//#include "k_calibration.h"
//#include "wt_bsp_storage.h" 
#include "k_mem.h" 
#include "wt_task_gui.h"
#include "wt_bsp_sd.h"
#include "wt_task_wiretest.h"
#include "wt_task_wirestudy.h"
#include "wt_task_wireselfcheck.h"
#include "wt_task_wirefindpoint.h"
#include "wt_bsp_print.h"
#include "verision.h"


extern void wt_StartUp(void);
extern void wt_Logo_StartUp(void);
extern void Menu_NextICO(void);
extern void Menu_OpenLinkICO(void);
extern uint8_t WT_Config_Read(void);
extern uint8_t flag_heartbeat;
extern uint8_t gwifi_stat;
extern uint8_t gwifi_connect;

/** @defgroup MAIN_Private_FunctionPrototypes
* @{
*/ 
static void SystemClock_Config(void);
static void StartThread(void const * argument);
static void TimerCallback(void const *n);
static void WifiCallback(void const *n);

/* Private_Variables */
WT_TesterStatusTypedef TesterStatus;
volatile uint32_t ulHighFrequencyTimerTicks = 0UL;
extern void freertos_debug_timer_init(void);
extern uint8_t taskinfo_printf(char* pData, uint16_t length);
extern uint8_t com2_printf(char* pData, uint16_t length);

/* Allocate the memory for the heap of FreeRTOS. */
#define BaseRAMCCM  0x10000000
#if( configAPPLICATION_ALLOCATED_HEAP == 1 )
  #if   (defined ( __CC_ARM ))
  uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__(( at(BaseRAMCCM) ));
  #elif (defined (__ICCARM__))
  uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] @BaseRAMCCM;
  #elif defined   (  __GNUC__  )
  uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__((section(".ExtRAMData")));
  #endif
#endif

  
/** @defgroup MAIN_Private_Functions
* @{
*/ 
SystemSettingsTypeDef 	settings;
//osMessageQId 						WireTestEvent;
//osMessageQId 						WireStudyEvent;
//osMessageQId 						WireSelfCheckEvent;
//osMessageQId 						WireFindPointEvent;
//osMessageQId 						UartCOM1Event;
//osMessageQId 						UartCOM2Event;
//osMessageQId 						UartAudioEvent;
//osMessageQId 						Uart24GHzEvent;
//osMessageQId 						UartInfrEvent;
WT_ConfigTypedef				WT_Config;

/**
* @brief  Main program
* @param  None
* @retval int
*/
int main(void)
{
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
  */
	
	//__set_MSP(0x08000000);
	//NVIC_SetVectorTable(0x08000000,0x200);
	
  HAL_Init();
 
  /* Configure the system clock @ 168 Mhz */
  SystemClock_Config();
  
  /* Initialize Joystick, Touch screen and Leds */
  k_BspInit();
    
  freertos_debug_timer_init();
  
  /*Initialize memory pools */
  my_mem_init(SRAMIN);
  my_mem_init(SDRAM);

  /* read wire harness tester config */
  //internal RTC backup data RTC_ReadBackupRegister(RTC_BKP_DR1)
  WT_Config_Read();
  
  /* Create Start task */
  osThreadDef(Kernel_Thread, StartThread, osPriorityHigh, 0, 2 * configMINIMAL_STACK_SIZE);
  osThreadCreate (osThread(Kernel_Thread), NULL);
  
  /* Start scheduler */
  osKernelStart ();

  /* We should never get here as control is now taken by the scheduler */
  for( ;; );
}

/*
*********************************************************************************************************
*  函数名: vTaskTaskUserIF
*  功能说明: 接口消息处理
*  形参: pvParameters 在创建该任务时传递的形参
*  返回值: 无
* 优先级: 1 (数值越小优先级越低,这个和uCOS 相反)
*********************************************************************************************************
*/
static void vTaskTaskUserIF(void const * argument)
{
//    uint8_t ucKeyCode;
    uint8_t pcWriteBuffer[500];
	char s[500];
	uint16_t len=0;

    while(1)
    {

			
//        vTaskList((char *)&pcWriteBuffer);
//		taskinfo_printf((char *)pcWriteBuffer,len);
			

        len = sprintf(s,"=================================================\r\n");
				com2_printf(s,len);
			
        len = sprintf(s,"任务名 任务状态 优先级 剩余栈 任务序号\r\n");
				com2_printf(s,len);
			
        vTaskList((char *)&pcWriteBuffer);
        len = sprintf(s,"%s\r\n", pcWriteBuffer);
				com2_printf(s,len);
			
        len = sprintf(s,"\r\n 任务名 运行计数 使用率\r\n");
				com2_printf(s,len);
			
        vTaskGetRunTimeStats((char *)&pcWriteBuffer);
        len = sprintf(s,"%s\r\n", pcWriteBuffer);
				com2_printf(s,len);
			
			
        vTaskDelay(10000);
    }
}

/**
  * @brief  Start task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
static void StartThread(void const * argument)
{
  //osTimerId wifi_timer;
	
    /* Initialize GUI */
    GUI_Init();
    LISTVIEW_SetDefaultGridColor(GUI_GRAY);
    LCD_BackLight_SetPWM(WT_Config.BackLight);
    WM_MULTIBUF_Enable(1);
    GUI_SelectLayer(1);
    //GUI_UC_SetEncodeUTF8();

    // malloc ram for large file
    TestFolder  = mymalloc(SDRAM, sizeof(WT_TestFolderTypedef));
    TestFile    = mymalloc(SDRAM, sizeof(WT_TestFileTypedef));
    StudyFile   = mymalloc(SDRAM, sizeof(WT_StudyFileTypedef));
    //StudyFolder =mymalloc(SDRAM, sizeof(WT_StudyFolderTypedef));
    PrintFolder = mymalloc(SDRAM, sizeof(WT_PrintFolderTypedef));
    PrintFile   = mymalloc(SDRAM, sizeof(WT_PrintFileTypedef));
    PrintConfig = mymalloc(SDRAM, sizeof(WT_PrintConfigTypedef));
    FileStream  = mymalloc(SDRAM, sizeof(WT_StudyFileStreamTypedef));

    /* Initialize RTC */
    k_CalendarBkupInit();

    /* Initialize Storage Units */
    k_StorageInit();
  WT_StoreFiles_Init();
  //WT_TestFile_Init();
    WT_StudyFiles_Init();
    WT_PrintConfig_Init();

    /* Create GUI task */
    osThreadDef(GUI_Thread, GUIThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE * 9);	//8*128*4 bytes
    osThreadCreate (osThread(GUI_Thread), NULL);

    /* Create WireTest task */
    osThreadDef(WireTest_Thread, WIRETESTThread, osPriorityNormal, 0, 2 * configMINIMAL_STACK_SIZE);	//2*128*4 bytes
    osThreadCreate (osThread(WireTest_Thread), NULL);

    /* Create Auto Study task */
  osThreadDef(WireStudy_Thread, WIRESTUDYThread, osPriorityNormal, 0, 2 * configMINIMAL_STACK_SIZE);	//2*128*4 bytes
  osThreadCreate (osThread(WireStudy_Thread), NULL);

    /* Create Self Check task */
    osThreadDef(WireSelfCheck_Thread, WIRESELFCHECKThread, osPriorityNormal, 0, 3 * configMINIMAL_STACK_SIZE);	//3*128*4 bytes
    osThreadCreate (osThread(WireSelfCheck_Thread), NULL);

		/* Create Find Point Check task */
		osThreadDef(WireFindPoint_Thread, WIREFINDPOINTThread, osPriorityNormal, 0, 2 * configMINIMAL_STACK_SIZE);	//2*128*4 bytes
		osThreadCreate (osThread(WireFindPoint_Thread), NULL);

    /* Create KEY_LED task */
    osThreadDef(KEY_LED_Thread, TimerCallback, osPriorityLow, 0, 1 * configMINIMAL_STACK_SIZE);	//1*128*4 bytes
    osThreadCreate (osThread(KEY_LED_Thread), NULL);

    /* Create Uart_COM1 task */
    osThreadDef(UART_COM1_Thread, UARTCOM1Thread, osPriorityHigh, 0, 2 * configMINIMAL_STACK_SIZE);	//2*128*4 bytes
    osThreadCreate (osThread(UART_COM1_Thread), NULL);

    /* Create Uart_INFR task === 已取消，不再使用 === */
		//osThreadDef(UART_INFR_Thread, UARTINFRThread, osPriorityAboveNormal, 0, 2 * configMINIMAL_STACK_SIZE);	//2*128*4 bytes
		//osThreadCreate (osThread(UART_INFR_Thread), NULL);

    /* Create Uart_24GHZ task */
    osThreadDef(UART_24GHZ_Thread, UART24GHZThread, osPriorityHigh, 0, 4 * configMINIMAL_STACK_SIZE);	//2*128*4 bytes
    osThreadCreate (osThread(UART_24GHZ_Thread), NULL);

	/* Create Uart_COM2 task */
    osThreadDef(UART_COM2_Thread, UARTCOM2Thread, osPriorityAboveNormal, 0, 1 * configMINIMAL_STACK_SIZE);	//1*128*4 bytes
    osThreadCreate (osThread(UART_COM2_Thread), NULL);
	
    #ifdef TASKOUTPUT
		/* Create UserIF task */
    osThreadDef(UserIF_Thread, vTaskTaskUserIF, osPriorityAboveNormal, 0, 3 * configMINIMAL_STACK_SIZE);	//3*128*4 bytes
    osThreadCreate (osThread(UserIF_Thread), NULL);
    #endif
    /* Create wifi connect task */
    osThreadDef(WIFI_Thread, WifiCallback, osPriorityHigh, 0, 1*configMINIMAL_STACK_SIZE );	//1*128*4 bytes
    osThreadCreate (osThread(WIFI_Thread), NULL);

    /* Create Uart_Audio task */
    osThreadDef(UART_Audio_Thread, UARTAudioThread, osPriorityAboveNormal, 0, 1 * configMINIMAL_STACK_SIZE);	//1*128*4 bytes
    osThreadCreate (osThread(UART_Audio_Thread), NULL);
	
    /* Create Test Message Queue */
    osMessageQDef(osqueue_test, 1, uint16_t);
    WireTestEvent = osMessageCreate (osMessageQ(osqueue_test), NULL);

    /* Create auto study Message Queue */
    osMessageQDef(osqueue_study, 1, uint16_t);
    WireStudyEvent = osMessageCreate (osMessageQ(osqueue_study), NULL);

    /* Create Self check Message Queue */
    osMessageQDef(osqueue_selfcheck, 1, uint16_t);
    WireSelfCheckEvent = osMessageCreate (osMessageQ(osqueue_selfcheck), NULL);

    /* Create find point Message Queue */
    osMessageQDef(osqueue_findpoint, 1, uint16_t);
    WireFindPointEvent = osMessageCreate (osMessageQ(osqueue_findpoint), NULL);

    /* Create Uart COM1 Message Queue */
    osMessageQDef(osqueue_uart_com1, 1, uint16_t);
    UartCOM1Event = osMessageCreate (osMessageQ(osqueue_uart_com1), NULL);

    /* Create Uart INFR Message Queue */
//    osMessageQDef(osqueue_uart_infr, 1, uint16_t);
//    UartInfrEvent = osMessageCreate (osMessageQ(osqueue_uart_infr), NULL);

    /* Create Uart COM2 Message Queue */
    osMessageQDef(osqueue_uart_com2, 1, uint16_t);
    UartCOM2Event = osMessageCreate (osMessageQ(osqueue_uart_com2), NULL);

    /* Create Uart 24G Message Queue */
    osMessageQDef(osqueue_uart_24G, 1, uint16_t);
    Uart24GHzEvent = osMessageCreate (osMessageQ(osqueue_uart_24G), NULL);

    /* Create Uart Audio Message Queue */
    osMessageQDef(osqueue_uart_aduio, 1, uint16_t);
    UartAudioEvent = osMessageCreate (osMessageQ(osqueue_uart_aduio), NULL);
	
//  /* Create Touch screen Timer */
//  osTimerDef(TS_Timer, TimerCallback);
//  lcd_timer =  osTimerCreate(osTimer(TS_Timer), osTimerPeriodic, (void *)0);
//  osTimerStart(lcd_timer, 20);	/* Start the TS Timer */
  
//    disp_task_stat_info();
    for( ;; )
    {
        LED_RUN_ON;   
//		LED1_ON_G();
        osDelay(500);
        
        LED_RUN_OFF;   
//		LED1_OFF();
        osDelay(500);	
    }
}



/**
  * @brief  Timer callbacsk 
  * @param  n: Timer index 
  * @retval None
  */
#define TIMES_KEY_LED		10
static void TimerCallback(void const *n)
{  
	uint8_t cnt = 0;
//    uint16_t cnt_wifiwait = 0;
//    uint16_t cnt_heatbeat = 0;
//    uint16_t cnt_reconnect = 0;

	
	while(1)
	{
		BSP_Update_KEY_LED();	//read 595 Key
		BSP_Update_Input();		//read Din
		
		// 1S for update Input & Output
		cnt++;
		if(cnt > (1000 / TIMES_KEY_LED))
		{
			cnt = 0;
			BSP_Update_Output();	//update output
		}
//        //wifi heatbeat
//        if(gwifi_connect == 1)
//        {
//            cnt_heatbeat++;

//            if(cnt_heatbeat > (5000 / TIMES_KEY_LED))//10s for wifi heatbeat
//            {
//                cnt_heatbeat = 0;  
//                osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSHEATBEAT_Event, 0);	//wifi heatbeat
//            }
//  
//            //2s for wifi heatbeat
//            if(flag_wifi == 0 )
//            {
//                cnt_wifiwait++;
//            }
//            else if(flag_wifi == 1 )
//            {
//                cnt_wifiwait = 0;
//                gwifi_stat = 1;
//                
//            }
//            if(cnt_wifiwait > (3000 / TIMES_KEY_LED) )//3s内没有收到心跳报文
//            {
//                gwifi_stat = 0;   
//              
//            }
//        }
//        
//        if( 1 == gwifi_stat )
//        {
//            WT_Config.IMS_Mode = 0;//IMS连接可用状态下自动切换为IMS测试模式
//        }
//        else
//        {
//            WT_Config.IMS_Mode = 1;//IMS连接断开状态下自动切换为本地测试模式
//            cnt_reconnect++;
//            if(cnt_reconnect > (10000 / TIMES_KEY_LED))//每隔10秒自动重连wifi
//            {
//                cnt_reconnect = 0;
//                osMessagePut(Uart24GHzEvent, Uart24GHZ_CONF_Event, 0); //Wifi模块复位    
//            }
//        }
  
		//os delay
		osDelay(TIMES_KEY_LED);
	}
}

/**
  * @brief  Wifi Timer callbacsk 
  * @param  n: Timer index 
  * @retval None
  */
static void WifiCallback(void const *n)
{  
    uint16_t i = 0;
    static uint8_t reconnect = 0;
    flag_heartbeat = 0;

    while(1)
	{
        
        if(gwifi_connect == 1)//wifi为连接状态
        {
            //flag_heartbeat = 0;
            if(WT_Config.IMS_Mode == 0 && flag_heartbeat == 0)
            {
                osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSHEATBEAT_Event, 0);	//wifi heatbeat
            }

            for(i=0;i<100;i++) 
            {
                if(flag_heartbeat == 1) //收到心跳报文
                {
                    break;
                }
                osDelay(30);
            }
            
            if(flag_heartbeat == 1 )
            {
                gwifi_stat = 1;//显示wifi图标
                flag_heartbeat = 0;
                
            }
            else//3s内没有收到心跳报文
            {
                reconnect++;                         
            }
            
            if(reconnect == 2)
            {
                gwifi_stat = 0; //隐藏wifi图标 
                gwifi_connect = 0; 
                reconnect = 0;       
                flag_heartbeat = 0;                    
            }
        }
        else
        {
           if(WT_Config.IMS_Mode == 0)
           {
                osMessagePut(Uart24GHzEvent, Uart24GHZ_WIFIRESET_Event, 0); //Wifi模块复位
                for(i=0;i<400;i++) //Wifi模块复位，等待9秒
                {
                    if(gwifi_connect == 1) //联网成功
                    {
                        break;
                    }
                    osDelay(30);
                }
            }
              
        }
        
//        if( 1 == gwifi_stat )
//        {
//            WT_Config.IMS_Mode = 0;//IMS连接可用状态下自动切换为IMS测试模式
//        }
//        else
//        {
//            WT_Config.IMS_Mode = 1;//IMS连接断开状态下自动切换为本地测试模式
//        }
  
		//os delay
		osDelay(5000);
	}

}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable Power Control clock */
  __PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		ulHighFrequencyTimerTicks++;
}

#ifdef USE_FULL_ASSERT
/**
* @brief  assert_failed
*         Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  File: pointer to the source file name
* @param  Line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line
  number,ex: printf("Wrong parameters value: file %s on line %d\r\n", 
  file, line) */
  
  /* Infinite loop */
  while (1)
  {}
}

#endif

