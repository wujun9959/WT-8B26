/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_bsp_storage.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-06-28
  * @brief   This file provides the E2PROM functions
  ******************************************************************************
  */

#define WT_BSP_STORAGE_GLOBALS

/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_storage.h"





/** @defgroup STMPE811_Private_Variables
  * @{
  */ 

/* Touch screen driver structure initialization */  
E2PROM_DrvTypeDef AT24C02_drv = 
{
  AT24C02_Init,
};




/**
  * @brief  Initialize the AT24C02 and configure the needed hardware resources
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void AT24C02_Init(void)
{
//	uint32_t res;
//	uint32_t i;
//	uint8_t buf_tx[10] = {0};
//	uint8_t buf_rx[100] = {0};
//	
//	
//	/* Initialize IO BUS layer */
//	EEPROM_IO_Init(); 
//	
//	
//	
//	res =  EEPROM_IO_IsDeviceReady(FM24C64_I2C_ADDRESS, 1);
//	if(res == HAL_OK)
//	{
//		
//		IOE_ReadMultiple(FM24C64_I2C_ADDRESS, 0, buf_rx, 12);
//		for(i=0;i<6;i++)
//		{
//			buf_tx[i] = i+1;
//			buf_rx[i] = 0;
//		}
//		
//		//res = EEPROM_IO_WriteData(AT24C02_Addr,0, buf_tx, 6);
//		//res = EEPROM_IO_ReadData(AT24C02_Addr, 0, buf_rx, 1);
//		
//		//test ok
//		//IOE_Write(AT24C02_Addr, 0, 55);
//		//buf_rx[0] = IOE_Read(AT24C02_Addr, 0);

//		//test,20140630,ok
//		IOE_WriteMultiple(AT24C02_Addr, 0, buf_tx, 6);
//		IOE_ReadMultiple(AT24C02_Addr, 0, buf_rx, 6);
//	}
//	
//   E2PROM_Drv = &AT24C02_drv;
}

//void WT_Test(void)
//{
//	AT24C02_Init();
//	
//}
