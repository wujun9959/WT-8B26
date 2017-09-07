/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_task_wireselfcheck.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-8-5
  * @brief   This file provides the wire test functions
  ******************************************************************************
  */

#define WT_WINDOWS_WIRESELFCHECK_GLOBALS



/* Includes ------------------------------------------------------------------*/
#include "wt_task_wireselfcheck.h"
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
static uint8_t WireSelfCheck_Process(void);


/**
  * @brief  wire self check task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void WIRESELFCHECKThread(void const * argument)
{
	osEvent event;
  uint8_t res;
	uint32_t i;
	
	//init the value
	SelfCheckItem.i2c_e2prom = 0;
	for(i=0;i<3;i++) SelfCheckItem.spi_flash[i] = 0;
	SelfCheckItem.sdram = 0;
	SelfCheckItem.sd_card = 0;
	SelfCheckItem.usb_disc = 0;
	SelfCheckItem.wireless = 0;
	SelfCheckItem.port_board_number = 0;
	SelfCheckItem.board_state = 0;
	for(i=0;i<4;i++) 
	{
		SelfCheckItem.port_board[i][0]=0;
		SelfCheckItem.port_board[i][1]=0;
		SelfCheckItem.port_board[i][2]=0;
	}
	SelfCheckItem.state = 0;	//0:waiting, 1:testing
	
  for( ;; )
  {
    event = osMessageGet( WireSelfCheckEvent, osWaitForever );
    
    if( event.status == osEventMessage )
    {
      switch(event.value.v)
      {
				case WIRESELFCHECK_START_EVENT:
					// start self check
					SelfCheckItem.state = 1;	//0:waiting, 1:testing
					res = WireSelfCheck_Process();	//0:ok, 1:error,
					SelfCheckItem.state = 0;	//0:waiting, 1:testing
					if(res == 0)
					{
						LED4_OFF();
					}
					else
					{
						//LED4_ON_R();
					}
					break;
				
				default:
					break;
      }
    }
  }
}

/**
  * @brief  WireSelfCheck_Process
  * @param  None
  * @retval None
  */
#define SelfCheck_BufferLen		10
static uint8_t WireSelfCheck_Process(void)
{
//	DIR dir;
	uint8_t  res = 0, flag;
	uint8_t  buf8[SelfCheck_BufferLen];
//	uint32_t buf32;
	uint32_t i;
	uint8_t  temp[SelfCheck_BufferLen];
	
	//-----------------------------------------------
	// test i2c e2prom - FM24C64
	// Size    = 0x2000(64K bit)
	// AddrMAX = 0x1FFF;
	// state - 0:not init, 1:ok, 2:error,
	//-----------------------------------------------
	res = BSP_EEPROM_Init();
	if(res == 0)	//init ok
	{
		// back data
		for(i=0;i<SelfCheck_BufferLen;i++) temp[i] = 0;
		res = BSP_EEPROM_ReadBuffer(temp, 0x2000 - SelfCheck_BufferLen, SelfCheck_BufferLen);
		if(res != 0)	//read buffer error
		{
			SelfCheckItem.i2c_e2prom = 2;
			goto end_i2c_e2prom;
		}
		
		// write data
		for(i=0;i<SelfCheck_BufferLen;i++) buf8[i] = i + '0';
		res = BSP_EEPROM_WriteBuffer(buf8, 0x2000 - SelfCheck_BufferLen, SelfCheck_BufferLen);
		if(res != 0) //write buffer error
		{
			SelfCheckItem.i2c_e2prom = 2;
			goto end_i2c_e2prom;
		}
		
		// read data
		for(i=0;i<SelfCheck_BufferLen;i++) buf8[i] = 0;
		res = BSP_EEPROM_ReadBuffer(buf8, 0x2000 - SelfCheck_BufferLen, SelfCheck_BufferLen);
		if(res != 0)	//read buffer error
		{
			SelfCheckItem.i2c_e2prom = 2;
			goto end_i2c_e2prom;
		}
		
		// check data
		flag = 0;
		for(i=0;i<SelfCheck_BufferLen;i++)
		{
			if(buf8[i] != i + '0')	//data error
			{
				flag = 1;
				break;
			}
		}
		if(flag == 1) //read buffer error
		{
			SelfCheckItem.i2c_e2prom = 2;
			goto end_i2c_e2prom;
		}
		
		// restore data
		res = BSP_EEPROM_WriteBuffer(temp, 0x2000 - SelfCheck_BufferLen, SelfCheck_BufferLen);
		if(res != 0)	// restore data error
		{
			SelfCheckItem.i2c_e2prom = 2;
			goto end_i2c_e2prom;
		}
		
		// pass
		SelfCheckItem.i2c_e2prom = 1;
	}
	else	//init error
	{
		SelfCheckItem.i2c_e2prom = 2;
	}
	end_i2c_e2prom:
		
	
	//-----------------------------------------------
	// test SPI flash - FM25V10
	// Size    = 0x20000(1M bit)
	// AddrMAX = 0x1FFFF;
	// state - 0:not init, 1:ok, 2:error,
	//-----------------------------------------------
	
    //此处进行flash自检，会导致发送自学习消息后，系统死机
//	//Init
//	sFLASH_Init();
//	
//	// back data
//	for(i=0;i<SelfCheck_BufferLen;i++) temp[i] = 0;
//	sFLASH_Read(temp, 0x20000 - SelfCheck_BufferLen, SelfCheck_BufferLen);
//	
//	//write
//	for(i=0;i<SelfCheck_BufferLen;i++) buf8[i] = i + '0';
//	sFLASH_Write(buf8, 0x20000 - SelfCheck_BufferLen, SelfCheck_BufferLen);
//	//read
//	for(i=0;i<SelfCheck_BufferLen;i++) buf8[i] = 0;
//	sFLASH_Read(buf8, 0x20000 - SelfCheck_BufferLen, SelfCheck_BufferLen);
//	//check the data
//	flag = 0;
//	for(i=0;i<SelfCheck_BufferLen;i++)
//	{
//		if(buf8[i] != i + '0')	//data error
//		{
//			flag = 1;
//			break;
//		}
//	}
//	if(flag == 0)	//write & read ok
//	{
//		if(sflash.ChipID == sFLASH_W25Q128_ID)	//read id ok
//		{
//			SelfCheckItem.spi_flash[0] = 1;
//			SelfCheckItem.spi_flash[1] = (uint8_t)(sflash.ChipID >> 8);
//			SelfCheckItem.spi_flash[2] = (uint8_t)(sflash.ChipID >> 0);
//			
//			//restore data
//			sFLASH_Write(temp, 0x20000 - SelfCheck_BufferLen, SelfCheck_BufferLen);
//		}
//		else
//		{
//			SelfCheckItem.spi_flash[0] = 2;
//		}
//	}
//	else	//write & read error
//	{
//		SelfCheckItem.spi_flash[0] = 2;
//	}

	
	//-----------------------------------------------
	// test SDRAM
	// Size    = 0xD080_0000(64M bit)
	// AddrMAX = 0xD07F_FFFF
	// state - 0:not init, 1:ok, 2:error,
	//-----------------------------------------------
	//protect data & write data
	for(i=0;i<SelfCheck_BufferLen;i++)
	{
		buf8[i] = *(uint8_t*)(0xD0800000 - SelfCheck_BufferLen + i);
		*(uint8_t*)(0xD0800000 - SelfCheck_BufferLen + i) = i + '0';
	}
	//check the data
	flag = 0;
	for(i=0;i<SelfCheck_BufferLen;i++)
	{
		if(*(uint8_t*)(0xD0800000 - SelfCheck_BufferLen + i) != i + '0')	//data error
		{
			flag = 1;
			break;
		}
	}
	if(flag == 0)	//write & read ok
	{
		SelfCheckItem.sdram = 1;
		//restore data
		for(i=0;i<SelfCheck_BufferLen;i++)
		{
			*(uint8_t*)(0xD0800000 - SelfCheck_BufferLen + i) = buf8[i];
		}
	}
	else	//write & read error
	{
		SelfCheckItem.sdram = 2;
	}

	
	//-----------------------------------------------
	// test SD card
	// state - 0:not init, 1:ok, 2:error, 3:not connect
	//-----------------------------------------------
	if(k_StorageGetStatus(MSD_DISK_UNIT) == 0)	//no sd card 
	{
		SelfCheckItem.sd_card = 3;
	}
	else	//sd card insert
	{
		store_dev = 1;
//        res = f_opendir(&dir, "1:/");
//		if(res == 0)
//		{
//			SelfCheckItem.sd_card = 1;
//			store_dev = 1;
//		}
//		else
//		{
//			SelfCheckItem.sd_card = 2;
//		}
	}

	
	//-----------------------------------------------
	// test USB disc
	// state - 0:not init, 1:ok, 2:error, 3:not connect
	//-----------------------------------------------
	if(k_StorageGetStatus(USB_DISK_UNIT) == 0)	//no usb
	{
		SelfCheckItem.usb_disc = 3;
	}
	else
	{
//		res = f_opendir(&dir, "0:/");
//		if(res == 0)
//		{
//			SelfCheckItem.usb_disc = 1;
//		}
//		else
//		{
//			SelfCheckItem.usb_disc = 2;
//		}

			SelfCheckItem.usb_disc = 1;
			store_dev = 0;
	}
	
	
	//-----------------------------------------------
	// test wireless model
	//-----------------------------------------------
	SelfCheckItem.wireless = 0;
	
	//-----------------------------------------------
	// test port switch board
	// NumberMAX = 4;
	// state - 	//byte0, 	0:not init, 1:ok, 2:error, 3:not connect
							//byte1, 	FW Vision;
							//byte2,  Voltage 15V * 10
	//port_board_number;	//0-4
	//-----------------------------------------------
	flag = 0;
	BSP_AD_Init();
	//PortBoard_Read_BoardInfo(&buf32);

	for(i=0;i<4;i++)
	{
		if(AD_State.PortBoard_Connected & (1 << i))
		{
			SelfCheckItem.port_board[i][0] = 1;								//byte0, 	0:not init, 1:ok, 2:error, 3:not connect
			SelfCheckItem.port_board[i][1] = 1;	//byte1, 	FW Vision;
			SelfCheckItem.port_board[i][2] = 150;							//byte2,  Voltage 15V * 10
			flag++; 
		}
		else
		{
			SelfCheckItem.port_board[i][0] = 3;	//byte0, 	0:not init, 1:ok, 2:error, 3:not connect
			SelfCheckItem.port_board[i][1] = 0;	//byte1, 	FW Vision;
			SelfCheckItem.port_board[i][2] = 0;	//byte2,  Voltage 15V * 10
		}
	}
	SelfCheckItem.port_board_number = flag;
    
    BSP_DA_Init();
	// return
	return res;
}


/**
  * @brief  WT_Test
  * @param  None
  * @retval None
  */
//void WT_Test(void)
//{
//	static uint16_t i=0;
//	
//	i++;
//	osMessagePut (WireSelfCheckEvent, WIRESELFCHECK_START_EVENT, 0);
//}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
