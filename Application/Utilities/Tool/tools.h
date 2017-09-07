/********************************************************************************
  Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      tools.h
  Author: wujun      Version:  2.0      Date: 2016.7.28
  Description:    WT-8A46 main function
                  
  Others:          

  Function List:  
    1. ....
  History:        
    1. Date:
       Author:
       Modification:
    2. ...

******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __UTILITY_TOOL_H__
#define  __UTILITY_TOOL_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <stdint.h>
     
#define RTCTIME_YEAR    2017

void num_converter(uint16_t num, char * str);
void get_systemtime(char *time);
void get_system_time(char * date ,char * time);
void get_system_time_samsung(char * date ,char * time);
void get_system_date(uint8_t * day ,uint8_t * month, uint16_t * year);
void get_teststart_time(char * date ,char * time);
void get_teststop_time(char * date ,char * time);
char *itoa(int num, char *str, int radix);
int add(int n);

int Get_InputNum_Index(int32_t wheel);
int Get_InputChar_Index(int32_t wheel);
char Get_InputNum(int32_t index);
char Get_InputChar(int32_t index);
	 
void snapshot(void);
	 
#ifdef __cplusplus
}
#endif

#endif /* __UTILITY_TOOL_H__ */
