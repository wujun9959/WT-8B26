/********************************************************************************
  Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      tools.c
  Author: wujun      Version:  2.0      Date: 2016.7.28
  Description:    WT-8A46 Tool function
                  
  Others:          

  Function List:  
    1. ....
  History:        
    1. Date:
       Author:
       Modification:
    2. ...
    
******************************************************************************/

#include  "tools.h"
#include  "k_bsp.h"
#include  "FreeRTOS.h"
#include  "task.h"

static uint8_t strMonth[][12] = {"01",
                           "02",
                           "03",
                           "04",
                           "05",
                           "06",
                           "07",
                           "08",
                           "09",
                           "10",
                           "11",
                           "12"};

static char input_num[10]={'0','1','2','3','4','5','6','7','8','9'};

static char input_char[66]={'1','2','3','4','5','6','7','8','9','0',
														'a','b','c','d','e','f','g','h','i','j',
														'k','l','m','n','o','p','q','r','s','t',
														'u','v','w','x','y','z','A','B','C','D',
														'E','F','G','H','I','J','K','L','M','N',
														'O','P','Q','R','S','T','U','V','W','X',
														'Y','Z','\0','-','_','@'};


/**
  * @brief  converter num to str.
  * @param  num(1-256)
  * @retval None
  */
void num_converter(uint16_t num, char * str)
{
	char tmp_str[20];
	memset(tmp_str,0,20);
	if(num <=64) sprintf(tmp_str,"A%d",num);
	else if(num >64 && num <=128) sprintf(tmp_str,"B%d",num-64);
	else if(num >128 && num <=192) sprintf(tmp_str,"C%d",num-128);
	else if(num >192 && num <=256) sprintf(tmp_str,"D%d",num-192);
	else sprintf(tmp_str,"E%d",num);
	strcpy(str,tmp_str);
	
}

/**
  * @brief  get_systemtime
  * @param  time
  * @retval None
  */
void get_systemtime(char *time)
{
	uint8_t TempStr[50];
	//uint8_t datestr[50];
	uint8_t timestr[20];
	
	RTC_TimeTypeDef   RTC_Time;
  RTC_DateTypeDef   RTC_DateStructure;
  //uint8_t /*sec,*/ min, hour, day, month;
	uint8_t sec,min, hour, day, month;
  uint16_t year;
	//time
	k_GetTime(&RTC_Time);
	sec    =  RTC_Time.Seconds;
	min    =  RTC_Time.Minutes;
	hour   =  RTC_Time.Hours;
	sprintf((char *)timestr, "%02d-%02d-%02d", hour , min, sec);
	//sprintf((char *)timestr, "%02d:%02d", hour , min);
	//date
	k_GetDate(&RTC_DateStructure);
	year =  RTC_DateStructure.Year + RTCTIME_YEAR;
	month =  RTC_DateStructure.Month;
	day =  RTC_DateStructure.Date;
	if((day > 0) && (day <= 31) && (month > 0)&& (month <= 12) && (year >= 1900))
	{
		sprintf((char *)TempStr, "%04d-%s-%02d_", year, strMonth[month-1], day);
	}
	else
	{
		sprintf((char *)TempStr, "2017-01-01_");
	}
	strcat((char*)TempStr,(char*)timestr);
	//strcat((char*)TempStr,".log");
	strcpy(time,(char*)TempStr);
}

/**
  * @brief  get_system_time
  * @param  date time
  * @retval None
  */
void get_system_time(char * date ,char * time)
{
	uint8_t TempStr[50];
	//uint8_t datestr[50];
	uint8_t timestr[20];
	
	RTC_TimeTypeDef   RTC_Time;
  RTC_DateTypeDef   RTC_DateStructure;
  //uint8_t /*sec,*/ min, hour, day, month;
	uint8_t sec,min, hour, day, month;
  uint16_t year;
	//time
	k_GetTime(&RTC_Time);
	sec    =  RTC_Time.Seconds;
	min    =  RTC_Time.Minutes;
	hour   =  RTC_Time.Hours;
	sprintf((char *)timestr, "%02d:%02d:%02d", hour , min, sec);
	//sprintf((char *)timestr, "%02d:%02d", hour , min);
	//date
	k_GetDate(&RTC_DateStructure);
	year =  RTC_DateStructure.Year + RTCTIME_YEAR;
	month =  RTC_DateStructure.Month;
	day =  RTC_DateStructure.Date;
	if((day > 0) && (day <= 31) && (month > 0)&& (month <= 12) && (year >= 1900))
	{
		sprintf((char *)TempStr, "%04d%s%02d", year, strMonth[month-1], day);
	}
	else
	{
		sprintf((char *)TempStr, "20160101_");
	}
	//strcat((char*)TempStr,(char*)timestr);
	//strcat((char*)TempStr,".log");
	strcpy(time,(char*)timestr);
	strcpy(date,(char*)TempStr);
}

/**
  * @brief  get_system_time
  * @param  date time
  * @retval None
  */
void get_system_time_samsung(char * date ,char * time)
{
	uint8_t TempStr[50];
	//uint8_t datestr[50];
	uint8_t timestr[20];
	
	RTC_TimeTypeDef   RTC_Time;
  RTC_DateTypeDef   RTC_DateStructure;
  //uint8_t /*sec,*/ min, hour, day, month;
	uint8_t sec,min, hour, day, month;
  uint16_t year;
	//time
	k_GetTime(&RTC_Time);
	sec    =  RTC_Time.Seconds;
	min    =  RTC_Time.Minutes;
	hour   =  RTC_Time.Hours;
	sprintf((char *)timestr, "%02d:%02d:%02d", hour , min, sec);
	//sprintf((char *)timestr, "%02d:%02d", hour , min);
	//date
	k_GetDate(&RTC_DateStructure);
	year =  RTC_DateStructure.Year + RTCTIME_YEAR;
	month =  RTC_DateStructure.Month;
	day =  RTC_DateStructure.Date;
	if((day > 0) && (day <= 31) && (month > 0)&& (month <= 12) && (year >= 1900))
	{
		sprintf((char *)TempStr, "%04d.%s.%02d", year, strMonth[month-1], day);
	}
	else
	{
		sprintf((char *)TempStr, "20160101_");
	}
	//strcat((char*)TempStr,(char*)timestr);
	//strcat((char*)TempStr,".log");
	strcpy(time,(char*)timestr);
	strcpy(date,(char*)TempStr);
}

/**
  * @brief  get_system_date
  * @param  day month year
  * @retval None
  */
void get_system_date(uint8_t * day ,uint8_t * month, uint16_t * year)
{
  RTC_DateTypeDef   RTC_DateStructure;

	//date
	k_GetDate(&RTC_DateStructure);
	*year =  RTC_DateStructure.Year + RTCTIME_YEAR;
	*month =  RTC_DateStructure.Month;
	*day =  RTC_DateStructure.Date;

}

/**
  * @brief  获得测试开始时间
  * @param  day month year
  * @retval None
  */
void get_teststart_time(char * date ,char * time)
{
	uint8_t TempStr[50];
	//uint8_t datestr[50];
	uint8_t timestr[20];
	
	RTC_TimeTypeDef   RTC_Time;
  RTC_DateTypeDef   RTC_DateStructure;

	uint8_t sec,min, hour, day, month;
  uint16_t year;
	//time
	k_GetTime(&RTC_Time);
	sec    =  RTC_Time.Seconds;
	min    =  RTC_Time.Minutes;
	hour   =  RTC_Time.Hours;
	
	if(sec >= 1 && sec <= 60)
	{
		sec = sec -1;
	}
	else
	{
		sec = 59;
		min = min - 1;
	}
	
	sprintf((char *)timestr, "%02d%02d%02d", hour , min, sec);

	//date
	k_GetDate(&RTC_DateStructure);
	year =  RTC_DateStructure.Year + RTCTIME_YEAR;
	month =  RTC_DateStructure.Month;
	day =  RTC_DateStructure.Date;
	if((day > 0) && (day <= 31) && (month > 0)&& (month <= 12) && (year >= 1900))
	{
		sprintf((char *)TempStr, "%04d%s%02d", year, strMonth[month-1], day);
	}
	else
	{
		sprintf((char *)TempStr, "20160101");
	}

	strcpy(time,(char*)timestr);
	strcpy(date,(char*)TempStr);
}

/**
  * @brief  获得测试结束时间
  * @param  day month year
  * @retval None
  */
void get_teststop_time(char * date ,char * time)
{
	uint8_t TempStr[50];
	//uint8_t datestr[50];
	uint8_t timestr[20];
	
	RTC_TimeTypeDef   RTC_Time;
  RTC_DateTypeDef   RTC_DateStructure;

	uint8_t sec,min, hour, day, month;
  uint16_t year;
	//time
	k_GetTime(&RTC_Time);
	sec    =  RTC_Time.Seconds;
	min    =  RTC_Time.Minutes;
	hour   =  RTC_Time.Hours;
	sprintf((char *)timestr, "%02d%02d%02d", hour , min, sec);

	//date
	k_GetDate(&RTC_DateStructure);
	year =  RTC_DateStructure.Year + RTCTIME_YEAR;
	month =  RTC_DateStructure.Month;
	day =  RTC_DateStructure.Date;
	if((day > 0) && (day <= 31) && (month > 0)&& (month <= 12) && (year >= 1900))
	{
		sprintf((char *)TempStr, "%04d%s%02d", year, strMonth[month-1], day);
	}
	else
	{
		sprintf((char *)TempStr, "20170101");
	}

	strcpy(time,(char*)timestr);
	strcpy(date,(char*)TempStr);
}


/**
  * @brief  int to array
  * @param  
  * @retval None
  */
char *itoa(int num, char *str, int radix)   
{
    char  string[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char* ptr = str;
    int i;
    int j;
		
		if(num==0) 
		{
			strcpy(str,"0");
			return str;
		}

    while (num)
    {
        *ptr++  = string[num % radix];
        num    /= radix;

        if (num < radix)
        {
            *ptr++  = string[num];
            *ptr    = '\0';
            break;
        }
    }

    j = ptr - str - 1;

    for (i = 0; i < (ptr - str) / 2; i++)
    {
        int temp = str[i];
        str[i]   = str[j];
        str[j--] = temp;
    }

    return str;
}

//获得数字索引
int Get_InputNum_Index(int32_t wheel)
{
	int index = 0;
	if(wheel >= 10 && wheel <20) index = wheel-10;
	else if(wheel >= 20 && wheel <30) index = wheel-20;
	else if(wheel >= 30) index = 9;
	else if(wheel < 0 && wheel >= -10) index = wheel+10;
	else if(wheel < -10 && wheel >= -20) index = wheel+20;
	else if(wheel < -20) index = 0;
	else index = wheel;
	return index;
}

//获得字符索引
int Get_InputChar_Index(int32_t wheel)
{
	int index = 0;
	if(wheel >= 66 && wheel < 132) index = wheel-66;
	else if(wheel >= 132 && wheel < 198) index = wheel-132;
	else if(wheel >= 198 && wheel < 264) index = wheel-198;
    else if(wheel >= 264) index = 65;
	else if(wheel < 0 && wheel >= -66) index = wheel+66;
	else if(wheel < -66 && wheel >= -132) index = wheel+132;
    else if(wheel < -132 && wheel >= -198) index = wheel+198;
	else if(wheel < -198) index=0;
	else index = wheel;
	return index;
}

//根据索引获得数字
char Get_InputNum(int32_t index)
{
	if(index >= 0 && index < 10)
	{		
		return input_num[index];
	}
	else
	{
		return input_num[0];
	}
}

//根据索引获得字符
char Get_InputChar(int32_t index)
{
	if(index >= 0 && index < 66)
	{		
		return input_char[index];
	}
	else
	{
		return input_char[0];
	}
}

//累加函数
int add(int n)
{
	int i,sum=0;
	for(i=1;i<n;i++)
		sum+=i;
	return sum;
}

static void _WriteByte2File(U8 Data, void * p)
{
        UINT nWrite = 0;
         
        f_write((FIL *)p, (TCHAR *)&Data, 1, &nWrite);
}


void emWin_CreateBMPPicture(uint8_t * FileName, int x0, int y0, int xSize, int ySize)
{
		static FIL hFile;
//		GUI_COLOR forecolor, backcolor;

//		forecolor = GUI_GetColor();  //??????
//		backcolor = GUI_GetBkColor();  //??????
		//
		//创建一个文件
		//
		f_open(&hFile, (const TCHAR *)FileName, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
		GUI_BMP_SerializeEx(_WriteByte2File, x0, y0, xSize, ySize, &hFile);
		f_close(&hFile);  //写完关闭文件
		 
//		GUI_SetColor(forecolor);  //??????
//		GUI_SetBkColor(backcolor);  //??????
}

//屏幕截图
uint8_t		Pic_Name = 0;
void snapshot(void)
{
	
	char buf[100];
	FRESULT result;
//	FIL			 file;
	sprintf(buf,"0:/PicSave/%d.bmp",Pic_Name);
	result = f_mkdir("0:/PicSave");
	if(result != FR_OK) return;
	//result = f_open(&file,buf, FA_WRITE|FA_CREATE_ALWAYS);
	emWin_CreateBMPPicture((uint8_t *)buf, 0, 0, 480, 272);  //??
	//result = f_close(&file);
	Pic_Name++; 		
}

void disp_task_stat_info(void)
{
     char *buf = NULL;
     
     buf = malloc(1024);
     if(NULL == buf)
      return; 

     osThreadList((uint8_t *)buf);

     //TLS_DBGPRT_INFO("\n%s",buf);
     free(buf);
     buf = NULL;
}
