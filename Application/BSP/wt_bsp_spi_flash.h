/**
  ******************************************************************************
  * @file    wt_bsp_spi_flash.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2016-8-9
  * @brief   This file contains all the functions prototypes for the E2PROM driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_BSP_SPI_FLASH_H
#define __WT_BSP_SPI_FLASH_H
   

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_common.h"
#include "wt_bsp_define.h"

#define sFLASH_SPI                          		SPI6
#define sFLASH_SPI_CLK_ENABLE()             		__SPI6_CLK_ENABLE()
   
#define sFLASH_SPI_MISO_PIN                    GPIO_PIN_12
#define sFLASH_SPI_SCK_PIN                     GPIO_PIN_13
#define sFLASH_SPI_MOSI_PIN                    GPIO_PIN_14
#define sFLASH_SPI_AF                       		GPIO_AF5_SPI6
#define sFLASH_SPI_PORT                        GPIOG
#define sFLASH_SPI_GPIO_CLK_ENABLE()           __GPIOG_CLK_ENABLE()  
#define sFLASH_SPI_GPIO_CLK_DISABLE()          __GPIOG_CLK_DISABLE()

#define sFLASH_SPI_NSS_PIN                     GPIO_PIN_15
#define sFLASH_SPI_NSS_PORT                    GPIOA
#define sFLASH_SPI_NSS_GPIO_CLK_ENABLE()       __GPIOA_CLK_ENABLE()  
#define sFLASH_SPI_NSS_GPIO_CLK_DISABLE()      __GPIOA_CLK_DISABLE()

#define sFLASH_SPI_NSS_L()     HAL_GPIO_WritePin(sFLASH_SPI_NSS_PORT, sFLASH_SPI_NSS_PIN, GPIO_PIN_RESET)
#define sFLASH_SPI_NSS_H()    HAL_GPIO_WritePin(sFLASH_SPI_NSS_PORT, sFLASH_SPI_NSS_PIN, GPIO_PIN_SET)
   
/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define sFLASH_SPI_TIMEOUT_MAX              ((uint32_t)0x1000)



//W25X系列/Q系列芯片列表	   
//W25Q80  ID  0XEF13
//W25Q16  ID  0XEF14
//W25Q32  ID  0XEF15
//W25Q64  ID  0XEF16	
//W25Q128 ID  0XEF17	
#define sFLASH_W25Q80_ID 	0XEF13 	
#define sFLASH_W25Q16_ID 	0XEF14
#define sFLASH_W25Q32_ID 	0XEF15
#define sFLASH_W25Q64_ID 	0XEF16
#define sFLASH_W25Q128_ID	0XEF17


/* W25Q SPI Flash supported commands */ 
#define sFLASH_CMD_WriteEnable		  0x06 
#define sFLASH_CMD_WriteDisable		  0x04 
#define sFLASH_CMD_ReadStatusReg	  0x05 
#define sFLASH_CMD_WriteStatusReg	  0x01 
#define sFLASH_CMD_ReadData			    0x03 
#define sFLASH_CMD_FastReadData		  0x0B 
#define sFLASH_CMD_FastReadDual		  0x3B 
#define sFLASH_CMD_PageProgram		  0x02 
#define sFLASH_CMD_BlockErase		  	0xD8 
#define sFLASH_CMD_SectorErase	  	0x20 
#define sFLASH_CMD_ChipErase		  	0xC7 
#define sFLASH_CMD_PowerDown		  	0xB9 
#define sFLASH_CMD_ReleasePowerDown 0xAB 
#define sFLASH_CMD_DeviceID			    0xAB
#define sFLASH_CMD_ManufactDeviceID 0x90
#define sFLASH_CMD_JedecDeviceID	  0x9F 


#define sFLASH_USE_MALLOC       0 

#define sFLASH_ADDR_FONT        0xD00000


typedef struct
{
	uint32_t ChipID;		  /* 芯片ID */
	char ChipName[16];		/* 芯片型号字符串，主要用于显示 */
	uint32_t TotalSize;		/* 总容量 */
	uint16_t PageSize;		/* 页面大小 */
}SFLASH_T;
extern SFLASH_T sflash;


void      sFLASH_Init(void);
void      sFLASH_Write_Enable(void);  		//写使能 
void      sFLASH_Write_Disable(void);		//写保护
void      sFLASH_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //读取flash
void      sFLASH_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//写入flash
void      sFLASH_Erase_Chip(void);    	  	//整片擦除
void      sFLASH_Erase_Sector(uint32_t Dst_Addr);	//扇区擦除
void      sFLASH_PowerDown(void);        	//进入掉电模式
void      sFLASH_WAKEUP(void);				//唤醒



#ifdef __cplusplus
}
#endif
#endif /* __WT_BSP_sFLASH_SPI_H */

     
/************************ (C) COPYRIGHT CNDZ *****END OF FILE****/
