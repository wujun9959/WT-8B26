/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_bsp_print.c
  * @author  LZY wujun
  * @version V1.0.0
  * @date    2016-08-18
  * @brief   This file provides the Print functions
  ******************************************************************************
	
	Flash中打印信息位置分配表
	地址：   存储内容                长度
	100 ：打印文件长度                 2
	102 ：线束型号                     20
	122 ：打印文件内容  
  800 ：线束型号信息                 16*30	
	1300：保存的线束型号个数           1
  */

#define WT_BSP_PRINT_GLOBALS

/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_print.h"
#include "wt_bsp.h"
#include "k_mem.h"
#include "k_storage.h"
#include "tools.h"


extern char str_mode[20];

#define IO_MAXSIZE  200

static void StrReplace(char* strSrc, char* strFind, char* strReplace,int src_len);

/**
  * @brief  初始化打印目录，获取打印文件信息
  * @param  None
  * @retval None
	* //0-not init, 1-inited, 2-no files, 3-hardware error, 4-no folder
  */
void WT_PrintFolder_Init(void)
{
	FRESULT res;
  FILINFO fno;
  DIR dir;
  char *fn,*p;
  uint8_t i=0;
	uint8_t buf8;

	// Init
	PrintFolder->number_TotalFile = 0;
	PrintFolder->number_CurrentFile = 0;
	
	PrintFolder->status = 0;	
	
	PrintFile->print_status = 0;
	PrintFile->sum_str = 0;
	PrintFile->number_Cmdline = 0;
	memset(PrintFile->PrintFilestr,0,PRINTCONFIG_MAX);
	
	// Check USB
	if(k_StorageGetStatus(USB_DISK_UNIT) == 0 && store_dev == 0 )	//no usb
	{
		PrintFolder->status = 3;	//0-not init, 1-inited, 2-no files, 3-hardware error, 4-no folder
		return;
	}
	// Check SD
	if(k_StorageGetStatus(MSD_DISK_UNIT) == 0 && store_dev == 1 )	//no sd
	{
		PrintFolder->status = 3;	//0-not init, 1-inited, 2-no files, 3-hardware error, 4-no folder
		return;
	}
	
	if(store_dev == 2) return;
	
#if _USE_LFN
  static char lfn[_MAX_LFN];
  fno.lfname = lfn;
  fno.lfsize = sizeof(lfn);
#endif
	
	if(store_dev==0) //usb
  res = f_opendir(&dir, path_printfile);
	if(store_dev==1) //sd
	res = f_opendir(&dir, path_printfile_sd);
	//res = f_opendir(&dir, "1:/LZY_WireTester/Test Files");
  if (res == FR_OK)
  {
    
    while (i < WT_Number_PrintFiles_MAX)
    {
      res = f_readdir(&dir, &fno);
      
      if (res != FR_OK || fno.fname[0] == 0)
      {
        break;
      }
      if (fno.fname[0] == '.')
      {
        continue;
      }
			
#if _USE_LFN
      fn = *fno.lfname ? fno.lfname : fno.fname;
#else
      fn = fno.fname;
#endif
			p = fn;
			while(*p) p++;
			buf8 = p - fn;
			if(buf8 > WT_FILE_NAME_SIZE+4) continue;
			if((fn[buf8-4] != '.') || (fn[buf8-3] != 'p') || (fn[buf8-2] != 'r') || (fn[buf8-1] != 'n'))
			{
				continue;
			}
			strncpy((char *)PrintFolder->FilesName[i], (char *)fn, buf8+1);
			i++;
		}
		
		if(i==0)	PrintFolder->status = 2;	//0-not init, 1-inited, 2-no files, 3-hardware error, 4-no folder
		else			
		{
			PrintFolder->status = 1;	//0-not init, 1-inited, 2-no files, 3-hardware error, 4-no folder
			PrintFolder->number_TotalFile = i;
		}
	}
	else
	{
		PrintFolder->status = 4;	//0-not init, 1-inited, 2-no files, 3-hardware error, 4-no folder
	}
}

/**
  * @brief  读取打印文件
  * @param  None
  * @retval None
	* //0-not init, 1-inited, 2-no files, 3-hardware error, 4-no folder
  */
uint8_t WT_PrintFiles_Init(char * filename, char * wire_mode)
{
FRESULT res;
	FIL file;
	char str[100];
	char vendor[20];
	uint32_t br =0;
	uint8_t  read_delay = 0;
	char *str_div1 = "$Y.m.d$";
	char *str_div2 = "@h:m:s@";
//	char *str_div3 = "@model@";
	char date_replace[20];
	char time_replace[20];
	
	memset(date_replace,0,20);
	memset(time_replace,0,20);
	memset(vendor,0,20);
	
	WT_PrintConfig_Init();
	
	if(k_StorageGetStatus(USB_DISK_UNIT) || k_StorageGetStatus(MSD_DISK_UNIT))
	{
		if(store_dev == 0) strcpy (str,(char *)path_printfile);
		if(store_dev == 1) strcpy (str,(char *)path_printfile_sd);

		strcat (str,"/");
		strcat (str,filename);
		
		// open file
		res = f_open(&file, str, FA_OPEN_EXISTING | FA_READ);
		if (res == FR_OK)
		{		
			f_gets(vendor, sizeof vendor, &file);//读取第一行厂商信息
			if(!strcmp(vendor,"#MIDEA\n"))
			{
				PrintFile->vendor = MIDEA;
				res = f_lseek(&file, strlen(vendor)+1);
			}
			else if(!strcmp(vendor,"#SAMSUNG\n"))
			{
				PrintFile->vendor = SAMSUNG;
				res = f_lseek(&file, strlen(vendor)+1);
			}
			else if(!strcmp(vendor,"#TESLA\n"))
			{
				PrintFile->vendor = TESLA;
				res = f_lseek(&file, strlen(vendor)+1);
			}
            else if(!strcmp(vendor,"#IMS\n"))
			{
				PrintFile->vendor = IMS;
				res = f_lseek(&file, strlen(vendor)+1);
			}
			else 
			{
				PrintFile->vendor = MIDEA;	
				f_lseek(&file,0);
			}				
			if(res != FR_OK) return 0;
			PrintFile->sum_str = f_size(&file);
			while(1)
		  {
				res=f_read(&file,PrintFile->PrintFilestr,PrintFile->sum_str,&br);
				if(res == FR_OK)
				{
					get_system_time(date_replace,time_replace);
					StrReplace((char *)PrintFile->PrintFilestr,str_div1,date_replace,PrintFile->sum_str);
					StrReplace((char *)PrintFile->PrintFilestr,str_div2,time_replace,PrintFile->sum_str);
//					StrReplace((char *)PrintFile->PrintFilestr,str_div3,wire_mode,PrintFile->sum_str);
					PrintFile->sum_str = strlen((char *)PrintFile->PrintFilestr);
					break;
				}
				else read_delay++;
				if(read_delay > 5) return 2;
		  } 

			PrintFile->number_Cmdline = PrintFile->sum_str/IO_MAXSIZE +1;
			f_close(&file);
			return 1;	//0:not init, 1: init ok, 2: hardware error, 3-no this file
		}
		else	
		{
			f_close(&file);
			return 3;	//0:not init, 1: init ok, 2: hardware error, 3-no this file
		}
		
	}
	else
	{
		f_close(&file);
		return 2;	//0:not init, 1: init ok, 2: hardware error, 3-no this file
	}
}



/**
  * @brief  将打印文件信息存到Flash
  * @param  None
  * @retval 0-ok, 1-hardware error, 2-file operate error, 
  */
uint8_t WT_PrintFileInfo_Write2Flash (void)
{
//	char line[IO_MAXSIZE];
//	uint32_t i=0;
	uint16_t len=0;
	uint8_t length[2];
	
	len = PrintFile->sum_str;
	length[0] = len >> 8;
	length[1] = len & 0xFF;
	sFLASH_Write(length,100,2);//头两个字节保存字节长度
	osDelay(10);
	sFLASH_Write((uint8_t *)str_mode,102,20);//20个字节保存线束型?
	osDelay(10);
    length[0] = PrintFile->vendor;
	length[1] = PrintFile->vendor;
	sFLASH_Write(length,122,1);//1?????????
	osDelay(20);
	sFLASH_Write((uint8_t *)PrintFile->PrintFilestr,123,PrintFile->sum_str);
//	for(i=0;i<len;i++)
//	{
//			memset(line,0,IO_MAXSIZE);
//			strcpy(line,(char *)PrintFile->PrintFilestr+i*IO_MAXSIZE);
//			sFLASH_Write((uint8_t *)line,(122+i*IO_MAXSIZE),IO_MAXSIZE);
//	}
	return 0;

}


/**
  * @brief  读取Flash中的打印文件信息
  * @param  None
  * @retval 0-ok, 1-hardware error, 2-file operate error, 
  */
uint8_t WT_PrintFileInfo_ReadFlash(void)
{
	//uint32_t i=0;
	uint16_t len=0;
	//uint8_t line[IO_MAXSIZE];
	uint8_t tmp[2];
    uint8_t vendor[2];
	
	WT_PrintConfig_Init();
	
	sFLASH_Read(tmp,100,2);
	sFLASH_Read((uint8_t *)str_mode,102,20);
	len = (tmp[0] << 8 ) + tmp[1];
	PrintFile->sum_str = len;
    
    sFLASH_Read(vendor,122,1);//1个字节保存厂商信息
	PrintFile->vendor = (PRINTVENDOR)vendor[0];
	
//	for(i=0;i<len;i++)
//	{
//		sFLASH_Read(line,122+i*IO_MAXSIZE,IO_MAXSIZE);
//		if(i==0)
//		strcpy((char *)PrintFile->PrintFilestr,(char *)line);
//		else
//		strcat((char *)PrintFile->PrintFilestr,(char *)line);
//	}
//	
//	PrintFile->sum_str = strlen((char *)PrintFile->PrintFilestr);
//	PrintFile->number_Cmdline = PrintFile->sum_str/IO_MAXSIZE +1;

	sFLASH_Read((uint8_t *)PrintFile->PrintFilestr,123,PrintFile->sum_str);
	PrintFile->number_Cmdline = PrintFile->sum_str/IO_MAXSIZE +1;
	return 0;
}

/**
  * @brief  初始化打印配置信息
  * @param  None
  * @retval None
	* //1-not init, 0-inited
  */
uint8_t WT_PrintConfig_Init(void)
{
	PrintFile->number_Cmdline = 0;
	PrintFile->print_status = 0;
	PrintFile->sum_str = 0;
	memset(PrintFile->PrintFilestr,0,PRINTCONFIG_MAX);
	return 0;
}


/**
  * @brief  清空Flash中的线束型号信息
  * @param  None
  * @retval 0-ok, 1-operate error
  */
uint8_t WT_ModeName_Clear(void)
{
	uint32_t i=0;
	uint8_t data[100];
	memset(data,0,100);
	for(i=0;i<6;i++)
	{
		sFLASH_Write(data,800+i*100,100);
		osDelay(10);
	}
	return 0;
}


/**
  * @brief  将线束型号信息写入Flash
  * @param  None
  * @retval 0-ok, 1-hardware error, 2-file operate error, 
  */
uint8_t WT_ModeName_Write(void)
{
	uint32_t i=0;
	uint8_t buff[500];
	memset(buff,0,500);
	

	for(i=0;i<PrintConfig->max_index;i++)
	{
		strcpy((char *)(buff+16*i),(char *)PrintConfig->print_item[i].mode_name);
		//CLK_Delay(500);	
	}
	sFLASH_Write(buff,800,500);
	osDelay(20);
	sFLASH_Write(&PrintConfig->max_index,1300,1);
	osDelay(20);
	return 0;
	
}

/**
  * @brief  从Flash读取线束型号信息
  * @param  None
  * @retval 0-ok, 1-hardware error, 2-file operate error, 
  */
uint8_t WT_ModeName_read(void)
{
	uint32_t i=0;
	//PrintConfig结构体初始化
	for(i=0;i<30;i++)
	{
		memset(PrintConfig->print_item[i].mode_name,0,16);
	}
	PrintConfig->max_index = 0;
	
	sFLASH_Read(&PrintConfig->max_index,1300,1);
	osDelay(20);
	if(PrintConfig->max_index >= 30) PrintConfig->max_index = 0;

	for(i=0;i<PrintConfig->max_index;i++)
	{
		sFLASH_Read((uint8_t *)PrintConfig->print_item[i].mode_name,(800+i*16),16);
		osDelay(20);
		//CLK_Delay(500);
	}

	return 0;
	
}

/**
  * @brief  初始化线束型号信息
  * @param  None
  * @retval 0-ok, 1-hardware error, 2-file operate error, 
  */
uint8_t WT_PrintModeName_Init(char * filename)
{
	uint8_t i = 0;
	uint8_t max_index = 0;
	uint8_t cnt = 0;

	if(!WT_ModeName_read())//读取线束型号信息
	{
		if(PrintConfig->max_index == 0)//没有打印配置信息
		{
			//添加打印信息
			strcpy((char *)PrintConfig->print_item[0].mode_name,filename);
			PrintConfig->max_index = 1;
			WT_ModeName_Write();
		}
		else
		{
			for(i=0;i<30;i++)
			{
				if(!strcmp(filename,(char *)PrintConfig->print_item[i].mode_name))//文件名相同
				{
					cnt++;
					break;
				}
			}
			if(cnt == 0)//没有同名文件
			{
				max_index = PrintConfig->max_index;
				if(max_index < 30)
				{
					strcpy((char *)PrintConfig->print_item[max_index].mode_name,filename);		
					PrintConfig->max_index = max_index+1;		
					WT_ModeName_Write();				
				}
				else
				{
					for(i=0;i<30;i++)
					{
						memset(PrintConfig->print_item[i].mode_name,0,16);
					}
					PrintConfig->max_index = 0;
				}
			}
		}
		
		return 0;
	}
	else
	{
		return 1;
	}
		
}

/**
  * @brief  获取打印流水号
  * @param  None
  * @retval printsn 
  */
uint16_t WT_PrintSN_Read(void)
{
//	uint16_t printsn = 0;
//	WT_Config_PrintSN_Read();
//	printsn = WT_Config.Print_SN;
//	return printsn;
    uint16_t printsn = 0;
	printsn = k_BkupRestoreParameter(CALIBRATION_VIDEOPLAYER_SETTING_BKP);
	return printsn;
	
}

/**
  * @brief  保存打印流水号到铁电
  * @param  None
  * @retval 0-ok, 1-hardware error, 2-file operate error, 
  */
uint8_t WT_PrintSN_Write(uint16_t printsn)
{
//	WT_Config.Print_SN = printsn;
//	WT_Config_PrintSN_Save();
    k_BkupSaveParameter(CALIBRATION_VIDEOPLAYER_SETTING_BKP,printsn);
	return 0;
}


/**
  * @brief  字符串中子字符串的替换
  * @param  None
  * @retval None
  */
static void StrReplace(char* strSrc, char* strFind, char* strReplace,int src_len)
{
  int len=0;
  int temp_len = 0;
  unsigned int find_len = 0;
  int lastLen = 0;
  find_len = strlen(strFind);

  while (len < src_len)
  {
    if (*strSrc == *strFind)
    {
      if (strncmp(strSrc, strFind, find_len) == 0)
      {
        char* q = strSrc+find_len;
        char* p = q;//p,q均指向剩余字符串的首地址
        char* repl = strReplace;
       
				lastLen = src_len - len;
        char* temp = (char *)malloc(lastLen+1);//临时开辟一段内存保存剩下的字符串，防止内存覆盖
        for (int k = 0; k < lastLen; k++)
        {
          *(temp+k) = *(p+k);
        }
        *(temp+lastLen) = '\0';
        while (*repl != '\0')
        {
          *strSrc++ = *repl++;
        }
        p = strSrc;
        char* pTemp = temp;//回收动态开辟内存
				temp_len = 0;
        while (temp_len < lastLen+1)
        {
          *p++ = *pTemp++;
					temp_len ++;
        }
        free(temp);
        *p = '\0';
      }
      else
        strSrc++;
    }
    else
      strSrc++;
		len++;
  }
}
