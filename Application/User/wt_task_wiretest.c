/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_task_wiretest.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-8-5
  * @brief   This file provides the wire test functions
  ******************************************************************************
  */

#define WT_WINDOWS_WIRETEST_GLOBALS



/* Includes ------------------------------------------------------------------*/
#include "wt_task_wiretest.h"
#include "main.h"
#include "wt_ad_app.h"
#include "wt_bsp.h" 
 

/* External variables --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
													 
extern uint8_t test_permit;//0-不允许测试 1-允许测试
extern uint8_t repairmode_flag;//0-not repair  1-repair mode
extern uint8_t task_mode; //0-测试模式  1-维修模式
extern uint8_t gwifi_stat;//0-not connect  1-connect
extern uint32_t test_totaltime ;
/**
  * @brief  WIRETEST task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void WIRETESTThread(void const * argument)
{
	osEvent event;
    uint8_t res;
	uint8_t res_wait;
//	uint8_t res_last;
	uint32_t i;
//	uint8_t test_okcnt;
	uint8_t requir_cnt;
	
	//Init 	
	WT_Config.TestMode = 0;	//0-自动模式，1-手动模式，2-定时模式
	TestFile->number_point = 0;	//端口数量
	TestFile->number_line = 0;		//通道数量
	TestFile->test_num = 0;//测试总数
//	test_okcnt = 0;
	requir_cnt = 0;
	
    for( ;; )
    {
		TestFile->task_status = 0;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error
		while(1)
		{
			event = osMessageGet( WireTestEvent, 0);
			if(event.status != osEventMessage) break;
		}
		//wait new message
		event = osMessageGet( WireTestEvent, osWaitForever );
        TestFile->command=1;
        if( event.status == osEventMessage )
        {
          switch(event.value.v)
          {
				case WIRETEST_START_EVENT:
					// check Test file
					if((TestFolder->status != 1) || (TestFile->file_status != 1))	//init error
					{
						if(WT_StoreFiles_Init() != 0) break;
					}
					requir_cnt = 0;	
					
					switch(WT_Config.TestMode)	//0-自动模式，1-手动模式，2-定时模式
					{
						case 0:	//自动模式
							for(;;)
							{
								test_start:
								if(test_permit != 1 && WT_Config.IMS_Mode == 0)//IMS测试模式
								{
									if(task_mode == 1)//0-not repair  1-repair mode
									{
										osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSREPAIR_Event, 0);	//发送维修请求信息
									}
									else
                                    {
                                        if(PrintFile->print_status == 2)
                                        {
                                            osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSTEST_Event, 0);//发送测试请求信息
                                            for(i=0;i<30;i++)
                                            {
                                                if(test_permit == 1) 
                                                {
                                                   break;
                                                }
                                                osDelay(100);
                                                
                                            }
                                        }
                                        else
                                        {
                                            osDelay(1500);
                                        }
                                        
                                        
                                    }
									
									
                                    requir_cnt ++;
                                    if(requir_cnt > 4 && task_mode !=1 && PrintFile->print_status == 4 )//打印出错，不要死等
                                    {
                                        TestFile->task_status = 0;
                                        PrintFile->print_status = 2;//print OK,便于下一次请求
										requir_cnt = 0;
										break;
                                    }

									if(requir_cnt > 6 && task_mode !=1 )//重复6次请求，如果没有回应，退出测试模式,重新连接IMS服务器,维修模式下不用发送请求信息
									{
                                        TestFile->task_status = 0;
                                        PrintFile->print_status = 2;//print OK,便于下一次请求
										requir_cnt = 0;
										break;
									}
									goto test_start;
								}
								requir_cnt = 0;	
                                PrintFile->print_status = 0;
                                //wt_SetText_Menu("IMS测试");
								TestFile->task_status = 1;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error
                                test_permit = 0;
                                
								res = WireTest_Process();	//0:ok, 1:file errror, 2:test error, 3-user cancel; 
								if(res == 0)
								{
//									test_okcnt++;
//									if(test_okcnt < 2 && WT_Config.TestRule == 1) goto test_start;  ////0-循环检测  1-单次检测 
//									else test_okcnt=0;
										
									TestFile->task_status = 3;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error
									//LED4_OFF();
									LED4_ON_G();
									
									//测试成功发送红外信号，本地打印不发送红外信号
//									if(WT_Config.Print == 0) { osMessagePut(UartInfrEvent, UartInfr_TX_Event, 0);}
									//IMS模式下，wifi发送测试结果
									if(WT_Config.IMS_Mode == 0 && gwifi_stat == 1) { osMessagePut(Uart24GHzEvent, Uart24GHZ_TXOK_Event, 0);	}	
									//喇叭发音
									osMessagePut(UartAudioEvent, UartAudioOK_TX_Event, 0);
									//本地测试模式，发送打印消息
									if(WT_Config.Print == 1 && WT_Config.IMS_Mode == 1) osMessagePut(UartCOM1Event, UartCOM1_TX_Event, 0);//本地打印
									
									TestFile->test_num++;
									TestFile->task_status = 4;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error
									test_permit = 0;
									res_wait = WireTest_WaitForNext();	//0:all remove, 1:file error, 3-user cancel; 
									if(res_wait != 0) 
									{
										TestFile->task_status = 2;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error
										osMessagePut(UartAudioEvent, UartAudioSTOP_TX_Event, 0);
										if(res_wait == 3)//user cancel 清除标志位
										{
											for(i=0; i<TestFile->item_total; i++)
											TestFile->test_item[i].result = 0;
											TestFile->test_ErrFlag = 0;	//for max error ID??0-no error, 1-error detect and retest
										}
										break;
									}
									else//all remove 清除标志位
									{
										for(i=0; i<TestFile->item_total; i++)
										TestFile->test_item[i].result = 0;
										TestFile->test_ErrFlag = 0;	//for max error ID，0-no error, 1-error detect and retest
                                        test_totaltime++;
//										//IMS模式下，请求新一轮测试
//										if(task_mode == 1 && WT_Config.IMS_Mode == 0)//0-not repair  1-repair mode
//										{
//											osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSREPAIR_Event, 0);	//发送维修请求信息
//										}
//										else if(task_mode == 0 && WT_Config.IMS_Mode == 0) 
//										{
//											osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSTEST_Event, 0);//发送测试请求信息
//										}

									}
									
								}
								else if(res == 3)//user cancel
								{
										LED4_OFF();
										osMessagePut(UartAudioEvent, UartAudioSTOP_TX_Event, 0);
										break;
								}
								else//res !=0  0:ok, 1:file errror, 2:test error, 3-user cancel; 					
								{			
									TestFile->task_status = 2;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error								
									test_totaltime++;
                  test_permit = 0;
									//IMS模式下，wifi发送测试结果			
									if(WT_Config.IMS_Mode == 0) { osMessagePut(Uart24GHzEvent, Uart24GHZ_TXNG_Event, 0);	}	
									//osMessagePut(Uart24GHzEvent, Uart24GHZ_TXNG_Event, 0);	//wifi发送测试结果
									osMessagePut(UartAudioEvent, UartAudioNG_TX_Event, 0);
									//if(WT_Config.Print == 1 ) osMessagePut(UartCOM1Event, UartCOM1_TXNG_Event, 0);//本地打印NG标签
									
									res_wait = WireTest_WaitForNext();	//0:all remove, 1:file error, 3-user cancel; 
									
									if(res_wait != 0) 
									{
										TestFile->task_status = 2;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error
										osMessagePut(UartAudioEvent, UartAudioSTOP_TX_Event, 0);
										if(res_wait == 3)//user cancel 清除标志位
										{
											osMessagePut(UartAudioEvent, UartAudioSTOP_TX_Event, 0);
											LED4_OFF();
										}
									}
									else//all remove 清除标志位
									{
										osMessagePut(UartAudioEvent, UartAudioSTOP_TX_Event, 0);
										LED4_OFF();
										//break;
//										//请求新一轮测试,维修模式下测试结束后不会自动发送测试请求
//										if(task_mode == 0 && WT_Config.IMS_Mode == 0)//0-not repair  1-repair mode
//										{
//											osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSTEST_Event, 0);//发送新一轮测试请求信息										
//										}
										//else osMessagePut(Uart24GHzEvent, Uart24GHZ_IMSREPAIR_Event, 0);	//发送维修请求信息

									}
								}
							}
							break;
						
						case 1:	//手动模式
							TestFile->task_status = 1;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error
							res = WireTest_Process();	//0:ok, 1:file errror, 2:test error, 3-user cancel; 
							if(res == 0)
							{
								TestFile->task_status = 3;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error
								LED4_OFF();
								//BSP_UartAudioOK_BeepOn(2);
								osMessagePut(UartAudioEvent, UartAudioOK_TX_Event, 0);
								TestFile->test_num++;
							}
							else					
							{
								TestFile->task_status = 2;	//0-waiting, 1-testing, 2-test error, 3-test ok, 4-waiting remove wire, 5-testing & Z error
								LED4_ON_RG();
							}
							break;
						
						default:
							break;						
					}
					break;
				
				default:
					break;
      }
    }
  }
}

