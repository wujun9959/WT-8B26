/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_bsp_spi_flash.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2016-08-09
  * @brief   support FM25VF10 & W25Q128FV.
  ******************************************************************************
  */

#define WT_BSP_SPI_FLASH_GLOBALS

/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_spi_flash.h"
#include <string.h>


static SPI_HandleTypeDef SpiHandle;
uint32_t SpixTimeout = sFLASH_SPI_TIMEOUT_MAX; /*<! Value of Timeout when SPI communication fails */  
SFLASH_T sflash;



static void sFLASH_Wait_Busy(void);


static void SPI6_MspInit(SPI_HandleTypeDef *hspi);
static void SPI6_Init(void);
static void SPI6_Error(void);
static uint8_t SPI6_WriteRead(uint8_t Byte);
static uint8_t sFLASH_ReadSR(void);
//static void sFLASH_Write_SR(uint8_t sr);
static uint16_t sFLASH_ReadID(void);
static void sFLASH_ReadInfo(void);
static void sFLASH_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
static void sFLASH_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);


/**
  * @brief  SPI6 MSP Init.
  * @param  hspi: SPI handle
  * @retval None
  */
static void SPI6_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable SPIx clock  */
  sFLASH_SPI_CLK_ENABLE();
	
  /* Enable DISCOVERY_SPI GPIO clock */
  sFLASH_SPI_GPIO_CLK_ENABLE();
	sFLASH_SPI_NSS_GPIO_CLK_ENABLE();
	
  /* configure SPI NSS Pin */
  sFLASH_SPI_NSS_H();
  GPIO_InitStructure.Pin    = sFLASH_SPI_NSS_PIN;
  GPIO_InitStructure.Mode   = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull   = GPIO_PULLUP;
  GPIO_InitStructure.Speed  = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(sFLASH_SPI_NSS_PORT, &GPIO_InitStructure);   
  
  /* configure SPI SCK, MOSI and MISO */    
  GPIO_InitStructure.Pin    = (sFLASH_SPI_MISO_PIN | sFLASH_SPI_SCK_PIN | sFLASH_SPI_MOSI_PIN);
  GPIO_InitStructure.Mode   = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull   = GPIO_PULLDOWN;
  GPIO_InitStructure.Speed  = GPIO_SPEED_MEDIUM;
  GPIO_InitStructure.Alternate = sFLASH_SPI_AF;
  HAL_GPIO_Init(sFLASH_SPI_PORT, &GPIO_InitStructure);      
}

/**
  * @brief  SPI6 Bus initialization
  * @param  None
  * @retval None
  */
static void SPI6_Init(void)
{
  if(HAL_SPI_GetState(&SpiHandle) == HAL_SPI_STATE_RESET)
  {
    /* SPI Config */
    SpiHandle.Instance = sFLASH_SPI;
    /* SPI6 baudrate is set to 42 MHz (PCLK2/SPI_BaudRatePrescaler = 84/2 = 42 MHz) 
       to verify these constraints:
       - sFLASH SPI interface max baudrate is 104MHz
       - PCLK2 frequency is set to 84 MHz 
       - SPI6 can communicate at up to 45 Mbits/s
    */  
    SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    SpiHandle.Init.Direction      = SPI_DIRECTION_2LINES;
    SpiHandle.Init.CLKPhase       = SPI_PHASE_1EDGE;
    SpiHandle.Init.CLKPolarity    = SPI_POLARITY_LOW;
    SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    SpiHandle.Init.CRCPolynomial  = 7;
    SpiHandle.Init.DataSize       = SPI_DATASIZE_8BIT;
    SpiHandle.Init.FirstBit       = SPI_FIRSTBIT_MSB;
    SpiHandle.Init.NSS            = SPI_NSS_SOFT;
    SpiHandle.Init.TIMode         = SPI_TIMODE_DISABLED;
    SpiHandle.Init.Mode           = SPI_MODE_MASTER;
  
    SPI6_MspInit(&SpiHandle);
    HAL_SPI_Init(&SpiHandle);
		
		
		/* Chip Select */
		sFLASH_SPI_NSS_H();
		CLK_Delay(10);
  }
}

/**
  * @brief  SPIx error treatment function.
  * @param  None
  * @retval None
  */
static void SPI6_Error(void)
{
  /* De-initialize the SPI communication BUS */
  HAL_SPI_DeInit(&SpiHandle);
  
  /* Re- Initialize the SPI communication BUS */
  SPI6_Init();
}

/**
  * @brief  Sends a Byte through the SPI interface and return the Byte received 
  *         from the SPI bus.
  * @param  Byte: Byte send.
  * @retval The received byte value
  */
static uint8_t SPI6_WriteRead(uint8_t Byte)
{
  uint8_t receivedbyte = 0;
  
  /* Send a Byte through the SPI peripheral */
  /* Read byte from the SPI bus */
  if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t*) &Byte, (uint8_t*) &receivedbyte, 1, SpixTimeout) != HAL_OK)
  {
    SPI6_Error();
  }
  
  return receivedbyte;
}

//---------------------------------------------------------------------------
//读取sFLASH的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
static uint8_t sFLASH_ReadSR(void)
{  
  uint8_t byte=0;   
  sFLASH_SPI_NSS_L();                  //使能器件   
  SPI6_WriteRead(sFLASH_CMD_ReadStatusReg); //发送读取状态寄存器命令    
  byte=SPI6_WriteRead(0X00);          //读取一个字节  
  sFLASH_SPI_NSS_H();                  //取消片选     
  return byte;   
} 
//写sFLASH状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
//static void sFLASH_Write_SR(uint8_t sr)
//{   
//  sFLASH_SPI_NSS_L();                    //使能器件   
//  SPI6_WriteRead(sFLASH_CMD_WriteStatusReg);  //发送写取状态寄存器命令    
//  SPI6_WriteRead(sr);              	    //写入一个字节  
//  sFLASH_SPI_NSS_H();                    //取消片选     	      
//}   
//sFLASH写使能	
//将WEL置位   
void sFLASH_Write_Enable(void)   
{
  sFLASH_SPI_NSS_L();                  //使能器件   
  SPI6_WriteRead(sFLASH_CMD_WriteEnable);   //发送写使能  
  sFLASH_SPI_NSS_H();                  //取消片选     	      
} 
//sFLASH写禁止	
//将WEL清零  
void sFLASH_Write_Disable(void)   
{  
  sFLASH_SPI_NSS_L();                    //使能器件   
  SPI6_WriteRead(sFLASH_CMD_WriteDisable);  //发送写禁止指令    
  sFLASH_SPI_NSS_H();                    //取消片选     	      
} 
//读取芯片ID
//返回值如下:				   
//0XEF13,表示芯片型号为W25Q80  
//0XEF14,表示芯片型号为W25Q16    
//0XEF15,表示芯片型号为W25Q32  
//0XEF16,表示芯片型号为W25Q64 
//0XEF17,表示芯片型号为W25Q128 	  
static uint16_t sFLASH_ReadID(void)
{
	uint16_t Temp = 0;

  /* Chip Select */
	sFLASH_SPI_NSS_L();
  
  /* Send Command & Address of the indexed register */
	SPI6_WriteRead(sFLASH_CMD_ManufactDeviceID);
  
  /* Receive the data that will be read from the device (MSB First) */
  /* Send dummy byte (0x00) to generate the SPI clock to GYRO (Slave device) */
	Temp|=SPI6_WriteRead(0x00)<<8; 
	Temp|=SPI6_WriteRead(0x00);
  
  /* Chip Disable */
	sFLASH_SPI_NSS_H();
  
	return Temp;
}   	
//	函 数 名: sFLASH_ReadInfo
//	功能说明: 读取器件ID,并填充器件参数
//  形    参:  无
//	返 回 值: 无
static void sFLASH_ReadInfo(void)
{
	/* 自动识别串行Flash型号 */
	{
		sflash.ChipID = sFLASH_ReadID();	/* 芯片ID */

		switch (sflash.ChipID)
		{
			case sFLASH_W25Q80_ID:
				strcpy(sflash.ChipName, "W25Q80");
				sflash.TotalSize = 1 * 1024 * 1024;	/* 总容量 = 1M */
				sflash.PageSize = 4 * 1024;			    /* 页面大小 = 4K */
				break;

			case sFLASH_W25Q32_ID:
				strcpy(sflash.ChipName, "W25Q32");
				sflash.TotalSize = 4 * 1024 * 1024;	/* 总容量 = 4M */
				sflash.PageSize = 4 * 1024;			    /* 页面大小 = 4K */
				break;

			case sFLASH_W25Q64_ID:
				strcpy(sflash.ChipName, "W25Q64");
				sflash.TotalSize = 8 * 1024 * 1024;	/* 总容量 = 8M */
				sflash.PageSize = 4 * 1024;			    /* 页面大小 = 4K */
				break;
      
      case sFLASH_W25Q128_ID:
				strcpy(sflash.ChipName, "W25Q128");
				sflash.TotalSize = 16 * 1024 * 1024;	/* 总容量 = 16M */
				sflash.PageSize = 4 * 1024;			    /* 页面大小 = 4K */
				break;

			default:
				strcpy(sflash.ChipName, "Unknow Flash");
				sflash.TotalSize = 2 * 1024 * 1024;
				sflash.PageSize = 4 * 1024;
				break;
		}
	}
}

//等待空闲
static void sFLASH_Wait_Busy(void)   
{   
	while((sFLASH_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}
//进入掉电模式
void sFLASH_PowerDown(void)   
{ 
  sFLASH_SPI_NSS_L();                            //使能器件   
  SPI6_WriteRead(sFLASH_CMD_PowerDown);     //发送掉电命令  
  sFLASH_SPI_NSS_H();                            //取消片选     	      
  CLK_Delay(10);                            //等待TPD  
}
//唤醒
void sFLASH_WAKEUP(void)   
{  
  sFLASH_SPI_NSS_L();                            	//使能器件   
  SPI6_WriteRead(sFLASH_CMD_ReleasePowerDown);	//  send sFLASH_CMD_PowerDown command 0xAB    
  sFLASH_SPI_NSS_H();                            	//取消片选     	      
  CLK_Delay(10);                               	//等待TRES1
}
//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void sFLASH_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{ 
  /* Chip Select */
	sFLASH_SPI_NSS_L();
	
  /* Send Command & Address of the indexed register */
  SPI6_WriteRead(sFLASH_CMD_ReadData);
  SPI6_WriteRead((uint8_t)((ReadAddr)>>16)); //发送24bit地址    
  SPI6_WriteRead((uint8_t)((ReadAddr)>>8));   
  SPI6_WriteRead((uint8_t)ReadAddr);
  
  /* Receive the data that will be read from the device (MSB First) */
  while(NumByteToRead > 0x00)
  {
    /* Send dummy byte (0x00) to generate the SPI clock to GYRO (Slave device) */
    *pBuffer = SPI6_WriteRead(0x00);
    NumByteToRead--;
    pBuffer++;
  }
	
	/* Chip Disable */
	sFLASH_SPI_NSS_H();
}  
//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
static void sFLASH_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
  /* Write Enable */
  sFLASH_Write_Enable();
  
  /* Chip Select */
  sFLASH_SPI_NSS_L();                            //使能器件   
  
  /* Send Command & Address of the indexed register */
  SPI6_WriteRead(sFLASH_CMD_PageProgram);      //发送写页命令   
  SPI6_WriteRead((uint8_t)((WriteAddr)>>16)); //发送24bit地址    
  SPI6_WriteRead((uint8_t)((WriteAddr)>>8));   
  SPI6_WriteRead((uint8_t)WriteAddr);
  
  /* Send the data that will be written into the device (MSB First) */
  while(NumByteToWrite > 0x00)
  {
    SPI6_WriteRead(*pBuffer);
    NumByteToWrite--;
    pBuffer++;
  }
  /* Chip Select */
  sFLASH_SPI_NSS_H();                 			//取消片选 
  
  sFLASH_Wait_Busy();						//等待写入结束
} 
//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
static void sFLASH_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{ 			 		 
  uint16_t pageremain;	   
  pageremain=256-WriteAddr%256; //单页剩余的字节数		 	    
  if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
  while(1)
  {	   
    sFLASH_Write_Page(pBuffer,WriteAddr,pageremain);
    if(NumByteToWrite==pageremain) break;//写入结束了
    else //NumByteToWrite>pageremain
    {
      pBuffer+=pageremain;
      WriteAddr+=pageremain;	

      NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
      if(NumByteToWrite>256)pageremain=256; //一次可以写入256个字节
      else pageremain=NumByteToWrite; 	  //不够256个字节了
    }
  }
} 
//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)						
//NumByteToWrite:要写入的字节数(最大65535) 
void sFLASH_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    
	uint8_t * sFLASH_BUF;	
#if sFLASH_USE_MALLOC==0 
  uint8_t sFLASH_BUFFER[4096];		 
#endif
  
#if	sFLASH_USE_MALLOC==1	//动态内存管理
	sFLASH_BUF=mymalloc(SRAMIN,4096);//申请内存
#else
  sFLASH_BUF=sFLASH_BUFFER; 
#endif     
 	secpos=WriteAddr/4096;//扇区地址  
	secoff=WriteAddr%4096;//在扇区内的偏移
	secremain=4096-secoff;//扇区剩余空间大小   
 	//printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//测试用
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//不大于4096个字节
	while(1) 
	{	
		sFLASH_Read(sFLASH_BUF,secpos*4096,4096);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(sFLASH_BUF[secoff+i]!=0XFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			sFLASH_Erase_Sector(secpos);	//擦除这个扇区
			for(i=0;i<secremain;i++)	  	//复制
			{
				sFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			sFLASH_Write_NoCheck(sFLASH_BUF,secpos*4096,4096);//写入整个扇区  

		}else sFLASH_Write_NoCheck(pBuffer,WriteAddr,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumByteToWrite==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;//扇区地址增1
			secoff=0;//偏移位置为0 	 

		   	pBuffer+=secremain;  //指针偏移
			WriteAddr+=secremain;//写地址偏移	   
		   	NumByteToWrite-=secremain;				//字节数递减
			if(NumByteToWrite>4096)secremain=4096;	//下一个扇区还是写不完
			else secremain=NumByteToWrite;			//下一个扇区可以写完了
		}	 
	};	
#if	sFLASH_USE_MALLOC==1		 
	myfree(SRAMIN,sFLASH_BUF);	//释放内存
#endif	
}
//擦除整个芯片		  
//等待时间超长...
void sFLASH_Erase_Chip(void)   
{                                   
  sFLASH_Write_Enable();                  //SET WEL 
  sFLASH_Wait_Busy();   
  sFLASH_SPI_NSS_L();                            //使能器件   
  SPI6_WriteRead(sFLASH_CMD_ChipErase);		//发送片擦除命令  
  sFLASH_SPI_NSS_H();                            //取消片选     	      
  sFLASH_Wait_Busy();   				   	//等待芯片擦除结束
}   
//擦除一个扇区
//Dst_Addr:扇区地址 根据实际容量设置
//擦除一个山区的最少时间:150ms
void sFLASH_Erase_Sector(uint32_t Dst_Addr)   
{  
	//监视falsh擦除情况,测试用   
  //printf("fe:%x\r\n",Dst_Addr);	  
  Dst_Addr*=4096;
  sFLASH_Write_Enable();                  //SET WEL 	 
  sFLASH_Wait_Busy();   
  sFLASH_SPI_NSS_L();                            //使能器件   
  SPI6_WriteRead(sFLASH_CMD_SectorErase);  	//发送扇区擦除指令 
  SPI6_WriteRead((uint8_t)((Dst_Addr)>>16));  //发送24bit地址    
  SPI6_WriteRead((uint8_t)((Dst_Addr)>>8));   
  SPI6_WriteRead((uint8_t)Dst_Addr);  
  sFLASH_SPI_NSS_H();                       		//取消片选     	      
  sFLASH_Wait_Busy();   				   	//等待擦除完成
}  
//初始化SPI FLASH的IO口
void sFLASH_Init(void)
{
  SPI6_Init();  //SPI Init
	sFLASH_ReadInfo();  /* 自动识别芯片型号 */
}





/************************ (C) COPYRIGHT CNDZ *****END OF FILE****/

