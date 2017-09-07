/********************************************************************************
	Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      wt_windows_config.c
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

// USER START (Optionally insert additional includes)
// USER END
#include "wt_bsp.h" 
#include "DIALOG.h"
#include "wt_task_gui.h"
#include "main.h"
#include "tools.h"


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0        			(GUI_ID_USER + 0x02)
#define ID_BUTTON_OK    			(GUI_ID_USER + 0x03)
#define ID_BUTTON_EXIT    			(GUI_ID_USER + 0x04)
#define ID_BUTTON_DEFAULT    		(GUI_ID_USER + 0x05)
#define ID_MULTIPAGE                (GUI_ID_USER + 0x0A)

//系统设置
#define ID_SLIDER_LIGHT    			(GUI_ID_USER + 0x10)
#define ID_TEXT_LIGHT    			(GUI_ID_USER + 0x11)
#define ID_TEXT_AUDIO    			(GUI_ID_USER + 0x12)
#define ID_SLIDER_AUDIO    			(GUI_ID_USER + 0x13)
#define ID_TEXT_AUDIOOK     		(GUI_ID_USER + 0x14)
#define ID_TEXT_AUDIONG     		(GUI_ID_USER + 0x15)
#define ID_DROPDOWN_AUDIOOK 	    (GUI_ID_USER + 0x16)
#define ID_DROPDOWN_AUDIONG 	    (GUI_ID_USER + 0x17)
#define ID_TEXT_PRINT		        (GUI_ID_USER + 0x18)
#define ID_DROPDOWN_PRINT           (GUI_ID_USER + 0x19)
#define ID_TEXT_PRINTMODE    		(GUI_ID_USER + 0x1A)
#define ID_DROPDOWN_PRINTMODE       (GUI_ID_USER + 0x1B)

#define ID_TEXT_DEVID               (GUI_ID_USER + 0x1C)
#define ID_EDIT_DEVID               (GUI_ID_USER + 0x1D)
#define ID_TEXT_TESTWAIT            (GUI_ID_USER + 0x1E)
#define ID_DROPDOWN_TESTWAIT        (GUI_ID_USER + 0x1F)
#define ID_TEXT_SERNUM              (GUI_ID_USER + 0x20)
#define ID_EDIT_SERNUM              (GUI_ID_USER + 0x21)
#define ID_TEXT_IMSTEXT             (GUI_ID_USER + 0x22)
#define ID_DROPDOWN_IMS             (GUI_ID_USER + 0x23)

//时间设置
#define ID_TEXT_DATE           	    (GUI_ID_USER + 0x24)
#define ID_TEXT_TIME           	    (GUI_ID_USER + 0x25)
#define ID_EDIT_YEAR                (GUI_ID_USER + 0x30)
#define ID_TEXT_YEAR                (GUI_ID_USER + 0x31)
#define ID_TEXT_MONTH               (GUI_ID_USER + 0x32)
#define ID_EDIT_MONTH               (GUI_ID_USER + 0x33)
#define ID_TEXT_DAY           	    (GUI_ID_USER + 0x34)
#define ID_EDIT_DAY           	    (GUI_ID_USER + 0x35)
#define ID_EDIT_HOUR                (GUI_ID_USER + 0x36)
#define ID_TEXT_HOUR                (GUI_ID_USER + 0x37)
#define ID_TEXT_MINUTE              (GUI_ID_USER + 0x38)
#define ID_EDIT_MINUTE              (GUI_ID_USER + 0x39)
#define ID_TEXT_SECOND              (GUI_ID_USER + 0x3A)
#define ID_EDIT_SECOND              (GUI_ID_USER + 0x3B)

//通信设置
#define ID_TEXT_NETWORK             (GUI_ID_USER + 0x40)
#define ID_EDIT_NETWORK             (GUI_ID_USER + 0x41)
#define ID_TEXT_SECKEY              (GUI_ID_USER + 0x42)
#define ID_EDIT_SECKEY              (GUI_ID_USER + 0x43)
#define ID_TEXT_IPADDR              (GUI_ID_USER + 0x55)
#define ID_EDIT_IPADDR              (GUI_ID_USER + 0x45)
#define ID_TEXT_MACADDR             (GUI_ID_USER + 0x46)
#define ID_EDIT_MACADDR             (GUI_ID_USER + 0x47)
#define ID_TEXT_SERVERADDR          (GUI_ID_USER + 0x48)
#define ID_EDIT_SERVERADDR1         (GUI_ID_USER + 0x49)
#define ID_TEXT_SERVERADDR1         (GUI_ID_USER + 0x4A)
#define ID_EDIT_SERVERADDR2         (GUI_ID_USER + 0x4B)
#define ID_TEXT_SERVERADDR2         (GUI_ID_USER + 0x4C)
#define ID_EDIT_SERVERADDR3         (GUI_ID_USER + 0x4D)
#define ID_TEXT_SERVERADDR3         (GUI_ID_USER + 0x4E)
#define ID_EDIT_SERVERADDR4         (GUI_ID_USER + 0x4F)
#define ID_TEXT_TCPPORT             (GUI_ID_USER + 0x50)
#define ID_EDIT_TCPPORT             (GUI_ID_USER + 0x51)

//调试设置
#define ID_TEXT_SIGNAL    			(GUI_ID_USER + 0x52)
#define ID_DROPDOWN_SIGNAL          (GUI_ID_USER + 0x53)
#define ID_TEXT_INFRARED    		(GUI_ID_USER + 0x54)
#define ID_TEXT_REALY1              (GUI_ID_USER + 0x55)
#define ID_TEXT_REALY2              (GUI_ID_USER + 0x56)
#define ID_TEXT_REALY3              (GUI_ID_USER + 0x57)
#define ID_TEXT_INFRARED_ST    	    (GUI_ID_USER + 0x58)
#define ID_TEXT_REALY1_ST           (GUI_ID_USER + 0x59)
#define ID_TEXT_REALY2_ST           (GUI_ID_USER + 0x5A)
#define ID_TEXT_REALY3_ST           (GUI_ID_USER + 0x5B)

//高级设置
#define ID_TEXT_TESTMODE            (GUI_ID_USER + 0x60)
#define ID_DROPDOWN_TESTMODE        (GUI_ID_USER + 0x61)
#define ID_TEXT_TESTRULE     		(GUI_ID_USER + 0x62)
#define ID_DROPDOWN_TESTRULE 	    (GUI_ID_USER + 0x63)
#define ID_TEXT_WTLIMIT    			(GUI_ID_USER + 0x64)
#define ID_DROPDOWN_WTLIMIT    	    (GUI_ID_USER + 0x65)
#define ID_TEXT_CAPTIAL    			(GUI_ID_USER + 0x66)
#define ID_DROPDOWN_CAPTIAL         (GUI_ID_USER + 0x67)
#define ID_TEXT_PRINTSERV     	    (GUI_ID_USER + 0x68)
#define ID_DROPDOWN_PRINTSERV 	    (GUI_ID_USER + 0x69)
#define ID_TEXT_PASSWD     			(GUI_ID_USER + 0x6A)
#define ID_EDIT_PASSWD 	    		(GUI_ID_USER + 0x6B)
#define ID_TEXT_LOOPNUM     		(GUI_ID_USER + 0x6C)
#define ID_EDIT_LOOPNUM 	    	(GUI_ID_USER + 0x6D)
// USER START (Optionally insert additional defines)
// USER END

extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_wheel;  //wujun added
extern void WT_TestFolder_Init(void);
extern uint8_t WT_Config_Read(void);
extern uint8_t WT_Config_Save(void);
extern uint8_t WT_Config_Restore(void);
extern WM_HWIN Create_PasswdDlgWindow(WM_HWIN hWin_para);
extern void WT_UART_COM1_Init(void);
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos);
void set_systemtime(uint8_t sec,uint8_t min, uint8_t hour, uint8_t day, uint8_t month,uint16_t year);
static void get_systime(uint8_t *sec,uint8_t *min, uint8_t *hour, uint8_t *day, uint8_t *month,uint16_t *year);
extern uint8_t WT_Printcfg_Clear(void);
void System_Setting_Init(WM_MESSAGE * pMsg);
void Commu_Setting_Init(WM_MESSAGE * pMsg);
void Advance_Setting_Init(WM_MESSAGE * pMsg);
void Time_Setting_Init(WM_MESSAGE * pMsg);



extern uint32_t wheel_value;
//static uint32_t tmpwheel;
static WM_HWIN hDialog_comm;
static WM_HWIN hDialog_advance;
static WM_HWIN hDialog_system;
static WM_HWIN hDialog_time;
static WM_HWIN hDialog_signal;
static int cursorindex=0;
uint16_t print_sn = 0;



K_ModuleItem_Typedef  wt_setting =
{	
	5,
	"设置",
	&bm_ICO_wheel,	
	//&CreateSystemInfo,
	Startup,
	0,
};

/*********************************************************************
*
*       _aDialog
*
* Purpose
*   Dialog resource using a WINDOW widget
*/
static const GUI_WIDGET_CREATE_INFO _aDialog[] = 
{
  
  { WINDOW_CreateIndirect, "System", ID_WINDOW_0, 0, 0, 480, 222, 0, 0x0, 0 },
  { MULTIPAGE_CreateIndirect, "Multipage", ID_MULTIPAGE, 0, 0, 480, 190, 0, 0x0, 0 },  
	{ BUTTON_CreateIndirect, "<短按>保存", ID_BUTTON_OK, 100, 195, 80, 25, 0, 0x0, 0 },  
  { BUTTON_CreateIndirect, "<长按>默认值", ID_BUTTON_DEFAULT, 195, 195, 90, 25, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "退出设置", ID_BUTTON_EXIT, 300, 195, 80, 25, 0, 0x0, 0 },
};

//系统设置标签
static const GUI_WIDGET_CREATE_INFO _aDialogSystemSettings[] = {
  { WINDOW_CreateIndirect, "System Settings", 0, 0, 0, 480, 222, FRAMEWIN_CF_MOVEABLE },
	{ TEXT_CreateIndirect, "亮度", ID_TEXT_LIGHT, 20, 10, 40, 20, 0, 0x0, 0 },
	{ SLIDER_CreateIndirect, "Slider-light", ID_SLIDER_LIGHT, 80, 10, 130, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "音量", ID_TEXT_AUDIO, 20, 40, 40, 20, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "Slider-audio", ID_SLIDER_AUDIO, 80, 40, 130, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "声音(OK)", ID_TEXT_AUDIOOK, 20, 70, 60, 20, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "dropdown-audiook", ID_DROPDOWN_AUDIOOK, 80, 70, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "声音(NG)", ID_TEXT_AUDIONG, 20, 100, 60, 20, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "dropdown-audiong", ID_DROPDOWN_AUDIONG, 80, 100, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "IMS连接", ID_TEXT_IMSTEXT, 20, 130, 60, 20, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "dropdown-ims", ID_DROPDOWN_IMS, 80, 130, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "本地打印", ID_TEXT_PRINT, 240, 10, 60, 20, 0, 0x0, 0 },
	{ DROPDOWN_CreateIndirect, "dropdown-lang", ID_DROPDOWN_PRINT, 300, 10, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "打印模式", ID_TEXT_PRINTMODE, 240, 40, 60, 20, 0, 0x0, 0 },
	{ DROPDOWN_CreateIndirect, "print-mode", ID_DROPDOWN_PRINTMODE, 300, 40, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "设备编号", ID_TEXT_DEVID, 240, 70, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Device-num", ID_EDIT_DEVID, 300, 70, 80, 25, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "测试时间", ID_TEXT_TESTWAIT, 240, 100, 80, 20, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "dropdown-time", ID_DROPDOWN_TESTWAIT, 300, 100, 80, 25, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "打印号", ID_TEXT_SERNUM, 240, 130, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "serial-num", ID_EDIT_SERNUM, 300, 130, 80, 25, 0, 0x64, 0 },

};

//时间设置标签
static const GUI_WIDGET_CREATE_INFO _aDialogTimeSettings[] = {
  { WINDOW_CreateIndirect, "Time Settings", 0, 0, 0, 480, 222, FRAMEWIN_CF_MOVEABLE },
	{ TEXT_CreateIndirect, "当前日期:", ID_TEXT_DATE, 20, 30, 70, 20, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "Edit-year", ID_EDIT_YEAR, 95, 30, 50, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "年", ID_TEXT_YEAR, 150, 30, 20, 20, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "Edit-month", ID_EDIT_MONTH, 170, 30, 30, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "月", ID_TEXT_MONTH, 200, 30, 20, 20, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "Edit-day", ID_EDIT_DAY, 220, 30, 30, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "日", ID_TEXT_DAY, 250, 30, 20, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "当前时间:", ID_TEXT_TIME, 20, 75, 70, 20, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "Edit-hour", ID_EDIT_HOUR, 95, 75, 50, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "时", ID_TEXT_HOUR, 150, 75, 20, 20, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "Edit-minute", ID_EDIT_MINUTE, 170, 75, 30, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "分", ID_TEXT_MINUTE, 200, 75, 20, 20, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "Edit-second", ID_EDIT_SECOND, 220, 75, 30, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "秒", ID_TEXT_SECOND, 250, 75, 20, 20, 0, 0x0, 0 },

};

//通信设置标签
static const GUI_WIDGET_CREATE_INFO _aDialogCommunitSettings[] = {
  { WINDOW_CreateIndirect, "Communication Settings", 0, 0, 0, 480, 222, FRAMEWIN_CF_MOVEABLE },  
	{ TEXT_CreateIndirect, "网络名称", ID_TEXT_NETWORK, 20, 10, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "network", ID_EDIT_NETWORK, 100, 10, 140, 25, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "密钥", ID_TEXT_SECKEY, 20, 40, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "password", ID_EDIT_SECKEY, 100, 40, 140, 25, 0, 0x64, 0 }, 
  { TEXT_CreateIndirect, "服务器地址", ID_TEXT_SERVERADDR, 20, 70, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Serv-IP", ID_EDIT_SERVERADDR1, 100, 70, 40, 25, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, ".", ID_TEXT_SERVERADDR1, 140, 70, 5, 25, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "Serv-IP", ID_EDIT_SERVERADDR2, 145, 70, 40, 25, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, ".", ID_TEXT_SERVERADDR2, 185, 70, 5, 25, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "Serv-IP", ID_EDIT_SERVERADDR3, 190, 70, 40, 25, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, ".", ID_TEXT_SERVERADDR3, 230, 70, 5, 25, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "Serv-IP", ID_EDIT_SERVERADDR4, 235, 70, 40, 25, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "端口号", ID_TEXT_TCPPORT, 20, 100, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Tcp-Port", ID_EDIT_TCPPORT, 100, 100, 80, 25, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "IP地址", ID_TEXT_IPADDR, 260, 10, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "IP-address", ID_EDIT_IPADDR, 330, 10, 110, 25, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "MAC地址", ID_TEXT_MACADDR, 260, 40, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "MAC-address", ID_EDIT_MACADDR, 330, 40, 110, 25, 0, 0x64, 0 },
  
  { TEXT_CreateIndirect, "打印服务器", ID_TEXT_LOOPNUM, 260, 100, 80, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "loop-num", ID_EDIT_LOOPNUM, 330, 100, 80, 25, 0, 0x64, 0 },
};

//高级设置标签
static const GUI_WIDGET_CREATE_INFO _aDialogAdvanceSettings[] = {
  { WINDOW_CreateIndirect, "Advance Settings", 0, 0, 0, 480, 222, FRAMEWIN_CF_MOVEABLE },  
	{ TEXT_CreateIndirect, "测试模式", ID_TEXT_TESTMODE, 20, 30, 82, 20, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "TestMode", ID_DROPDOWN_TESTMODE, 100, 30, 80, 20, 0, 0x64, 0 }, 
	{ TEXT_CreateIndirect, "导通阈值", ID_TEXT_WTLIMIT, 20, 70, 80, 20, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Edit-wtlimit", ID_DROPDOWN_WTLIMIT, 100, 70, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "打印服务器", ID_TEXT_PRINTSERV, 20, 110, 82, 20, 0, 0x0, 0 }, 
  { DROPDOWN_CreateIndirect, "Edit-printserv", ID_DROPDOWN_PRINTSERV, 100, 110, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "测试规则", ID_TEXT_TESTRULE, 240, 30, 80, 20, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Edit-testrule", ID_DROPDOWN_TESTRULE, 300, 30, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "电容阈值", ID_TEXT_CAPTIAL, 240, 70, 80, 20, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Edit-captial", ID_DROPDOWN_CAPTIAL, 300, 70, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "密码", ID_TEXT_PASSWD, 240, 110, 40, 20, 0, 0x0, 0 },
	{ EDIT_CreateIndirect, "dropdown-lang", ID_EDIT_PASSWD, 300, 110, 80, 20, 0, 0x0, 0 },

};

//调试设置标签
static const GUI_WIDGET_CREATE_INFO _aDialogDebugSettings[] = {
  { WINDOW_CreateIndirect, "Advance Settings", 0, 0, 0, 480, 222, FRAMEWIN_CF_MOVEABLE },  
	{ TEXT_CreateIndirect, "信号源", ID_TEXT_SIGNAL, 20, 30, 82, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "infrared", ID_TEXT_INFRARED, 240, 30, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "", ID_TEXT_INFRARED_ST, 320, 30, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "DIO_IN1", ID_TEXT_REALY1, 240, 60, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "", ID_TEXT_REALY1_ST, 320, 60, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "DIO_IN2", ID_TEXT_REALY2, 240, 90, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "", ID_TEXT_REALY2_ST, 320, 90, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "DIO_IN3", ID_TEXT_REALY3, 240, 120, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "", ID_TEXT_REALY3_ST, 320, 120, 80, 20, 0, 0x0, 0 },
	
  { DROPDOWN_CreateIndirect, "dropdown-signal", ID_DROPDOWN_SIGNAL, 100, 30, 100, 20, 0, 0x64, 0 }, 
};


/**
  * @brief  callback for System Settings
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */

static void _cbSystemSettings(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  
  hItem = pMsg->hWin;
  uint8_t sel=0;
	//int32_t tmp_val=0;
	WINDOW_SetBkColor(hItem, 0x00FFFFFF);
	int cursorpos=0;
	int index=0;
	
	//WT_Config_Read();//读取配置参数
	
    switch (pMsg->MsgId) {
    
    case WM_INIT_DIALOG:   
        System_Setting_Init(pMsg);
        Wheel_Encoder_Write(0);
        break;
	case MY_MESSAGE_WHEEL://处理滚轮事件
        hItem = WM_GetFocussedWindow();
        if(hItem == WM_GetDialogItem(pMsg->hWin, ID_SLIDER_LIGHT))//改变亮度
        {
            sel=SLIDER_GetValue(hItem);
            if(1 == KeyLed_State.rotate)
            {
                if(sel<10) 
                {
                    SLIDER_Inc(hItem);
                    LCD_BackLight_SetPWM(sel+1);
                }
                else
                {
                    SLIDER_SetValue(hItem,10);
                    LCD_BackLight_SetPWM(10);
                }
                //tmpwheel=KeyLed_State.wheel;
            }
            else if(2 == KeyLed_State.rotate)
            {
                if(sel>0) 
                {
                    SLIDER_Dec(hItem);
                    LCD_BackLight_SetPWM(sel-1);
                }
                else
                {
                    SLIDER_SetValue(hItem,0);
                    LCD_BackLight_SetPWM(0);
                }
                //tmpwheel=KeyLed_State.wheel;
            }
        }
        else if(hItem == WM_GetDialogItem(pMsg->hWin, ID_SLIDER_AUDIO))//改变音量
        {
            sel=SLIDER_GetValue(hItem);
            if(1 == KeyLed_State.rotate)
            {
                if(sel<10) 
                {
                    SLIDER_Inc(hItem);
                    WT_Config.AudioVolume = sel+1;
                    osMessagePut(UartAudioEvent, UartAudio_VOLUME_Event, 0);	//调节音量
                }
                else
                {
                    SLIDER_SetValue(hItem,10);
                    WT_Config.AudioVolume = 10;
                    osMessagePut(UartAudioEvent, UartAudio_VOLUME_Event, 0);	//调节音量
                }
                //tmpwheel=KeyLed_State.wheel;
            }
            else if(2 == KeyLed_State.rotate)
            {
                if(sel>0) 
                {
                    SLIDER_Dec(hItem);
                    WT_Config.AudioVolume = sel - 1;
                    osMessagePut(UartAudioEvent, UartAudio_VOLUME_Event, 0);	//调节音量
                }
                else
                {
                    SLIDER_SetValue(hItem,0);
                    WT_Config.AudioVolume = 0;
                    osMessagePut(UartAudioEvent, UartAudio_VOLUME_Event, 0);	//调节音量
                }
                //tmpwheel=KeyLed_State.wheel;
            }
        }
        else if(hItem == WM_GetDialogItem(pMsg->hWin, ID_EDIT_DEVID))//输入设备编号
        {		
            EDIT_SetCursorAtChar(hItem,cursorindex);
            index = Get_InputNum_Index(Wheel_Encoder_Read());
            if(cursorindex==EDIT_GetCursorCharPos(hItem))
            {
                EDIT_AddKey(hItem,GUI_KEY_DELETE);
                EDIT_AddKey(hItem,Get_InputNum(index));
                cursorpos=EDIT_GetCursorCharPos(hItem);
                if(cursorindex == 2) EDIT_SetSel(hItem,cursorpos,cursorpos);
                else EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
            }				
        }
//			else if(hItem == WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TESTWAIT))//输入版本号
//			{		
//				EDIT_SetCursorAtChar(hItem,cursorindex);
//				index = Get_InputNum_Index(KeyLed_State.wheel);
//				if(cursorindex==EDIT_GetCursorCharPos(hItem))
//				{
//					EDIT_AddKey(hItem,GUI_KEY_DELETE);
//					EDIT_AddKey(hItem,Get_InputNum(index));
//					cursorpos=EDIT_GetCursorCharPos(hItem);
//					if(cursorindex == 2) EDIT_SetSel(hItem,cursorpos,cursorpos);
//					else EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
//				}				
//				
//			}		
        else if(hItem == WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERNUM))//输入打印序列号
        {
            EDIT_SetCursorAtChar(hItem,cursorindex);
            index = Get_InputNum_Index(Wheel_Encoder_Read());
            if(cursorindex==EDIT_GetCursorCharPos(hItem))
            {
                EDIT_AddKey(hItem,GUI_KEY_DELETE);
                EDIT_AddKey(hItem,Get_InputNum(index));
                cursorpos=EDIT_GetCursorCharPos(hItem);
                if(cursorindex == 3) EDIT_SetSel(hItem,cursorpos,cursorpos);
                else EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
            }
            
        }
        
		break;
	case	MY_MESSAGE_DOWN://处理向下按钮事件
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_PRINT);
		if(WM_HasFocus(hItem))//选择是否本地打印
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<1)
			{
				DROPDOWN_IncSel(hItem);
			}					
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,0);		
			}						
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_LIGHT);
		if(WM_HasFocus(hItem))//调节亮度
		{
			sel=SLIDER_GetValue(hItem);
			if(sel<10)
			{
				SLIDER_Inc(hItem);
				LCD_BackLight_SetPWM(sel+1);
			}					
			else //sel>=10 
			{
				SLIDER_SetValue(hItem,10);
				LCD_BackLight_SetPWM(10);
			}	
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_AUDIO);
		if(WM_HasFocus(hItem))//调节音量
		{
			sel=SLIDER_GetValue(hItem);
			sel++;
			if(sel > 10) 
			{
				sel=0;
			}
			SLIDER_SetValue(hItem,sel);
			WT_Config.AudioVolume = sel;
			osMessagePut(UartAudioEvent, UartAudio_VOLUME_Event, 0);	//调节音量
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_AUDIOOK);
		if(WM_HasFocus(hItem))//选择OK声音文件
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<3)
			{
				DROPDOWN_IncSel(hItem);
				WT_Config.AudioOK = DROPDOWN_GetSel(hItem);
				osMessagePut(UartAudioEvent, UartAudioOK_REPEAT_TX_Event, 0);	//播放声音
			}					
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,0);		
				WT_Config.AudioOK = 0;
				osMessagePut(UartAudioEvent, UartAudioOK_REPEAT_TX_Event, 0);	//播放声音
			}						
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_AUDIONG);
		if(WM_HasFocus(hItem))//选择NG声音文件
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<3)
			{
				DROPDOWN_IncSel(hItem);
				WT_Config.AudioNG = DROPDOWN_GetSel(hItem)+4;
				osMessagePut(UartAudioEvent, UartAudioNG_TX_Event, 0);	//播放声音
			}					
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,0);		
				WT_Config.AudioNG = 4;
				osMessagePut(UartAudioEvent, UartAudioNG_TX_Event, 0);	//播放声音
			}						
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_IMS);
		if(WM_HasFocus(hItem))//选择IMS连接选项
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<1)
			{
				DROPDOWN_IncSel(hItem);
			}					
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,0);		
			}						
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_PRINTMODE);
		if(WM_HasFocus(hItem))//选择打印模式
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<1)
			{
				DROPDOWN_IncSel(hItem);
			}					
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,0);		
			}						
		}
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_DEVID);//修改设备编号
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == 2)
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TESTWAIT);//选择等待时间
		if(WM_HasFocus(hItem))
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<5)
			{
				DROPDOWN_IncSel(hItem);
				WT_Config.Test_Wait = DROPDOWN_GetSel(hItem)+6;
			}					
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,0);		
				WT_Config.Test_Wait = 6;
			}						
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERNUM);//修改流水号
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == 3)
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		
		break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/**
  * @brief  callback for Time Settings
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */

static void _cbTimeSettings(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  //uint32_t year=0;
	int32_t tmp_val=0;
  hItem = pMsg->hWin;
	WINDOW_SetBkColor(hItem, 0x00FFFFFF);
	
  uint16_t year;

	
  switch (pMsg->MsgId) {
    
  case WM_INIT_DIALOG:
  	Time_Setting_Init(pMsg);
    Wheel_Encoder_Write(0);
    break;
	case	MY_MESSAGE_WHEEL://处理滚轮事件
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_YEAR);
		if(WM_HasFocus(hItem))//改变年
		{
			year=EDIT_GetValue(hItem);
			if(1 == KeyLed_State.rotate)
			{
				EDIT_SetValue(hItem,year+1);
				//tmpwheel=KeyLed_State.wheel;
			}
			else if(2 == KeyLed_State.rotate)
			{
				EDIT_SetValue(hItem,year-1);
				//tmpwheel=KeyLed_State.wheel;
			}
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MONTH);
		if(WM_HasFocus(hItem))//改变月
		{
			tmp_val = EDIT_GetValue(hItem);
			if(1 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val + 1;
				if(tmp_val >12) tmp_val = tmp_val - 12;
				EDIT_SetValue(hItem,tmp_val+1);
				//tmpwheel=KeyLed_State.wheel;
			}
			else if(2 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val - 1;			
				if(tmp_val <= 0) tmp_val = tmp_val + 12;
				EDIT_SetValue(hItem,tmp_val);
				//tmpwheel=KeyLed_State.wheel;
			}
			EDIT_SetValue(hItem,tmp_val);
			//EDIT_SetValue(hItem,KeyLed_State.wheel);	
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_DAY);
		if(WM_HasFocus(hItem))//改变日
		{
			tmp_val = EDIT_GetValue(hItem);
			if(1 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val + 1;
				if(tmp_val >31) tmp_val = tmp_val - 31;
				EDIT_SetValue(hItem,tmp_val+1);
				//tmpwheel=KeyLed_State.wheel;
			}
			else if(2 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val - 1;			
				if(tmp_val <= 0) tmp_val = tmp_val + 31;
				EDIT_SetValue(hItem,tmp_val);
				//tmpwheel=KeyLed_State.wheel;
			}
			EDIT_SetValue(hItem,tmp_val);
			//EDIT_SetValue(hItem,KeyLed_State.wheel);	
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_HOUR);
		if(WM_HasFocus(hItem))//改变时
		{
			tmp_val = EDIT_GetValue(hItem);
			if(1 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val + 1;
				if(tmp_val >23) tmp_val = tmp_val - 24;
				EDIT_SetValue(hItem,tmp_val);
				//tmpwheel=KeyLed_State.wheel;
			}
			else if(2 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val - 1;			
				if(tmp_val < 0) tmp_val = tmp_val + 24;
				EDIT_SetValue(hItem,tmp_val);
				//tmpwheel=KeyLed_State.wheel;
			}
			EDIT_SetValue(hItem,tmp_val);
			//EDIT_SetValue(hItem,KeyLed_State.wheel);	
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MINUTE);
		if(WM_HasFocus(hItem))//改变分
		{
			tmp_val = EDIT_GetValue(hItem);
			if(1 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val + 1;
				if(tmp_val >59) tmp_val = tmp_val - 60;
				EDIT_SetValue(hItem,tmp_val);
				//tmpwheel=KeyLed_State.wheel;
			}
			else if(2 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val - 1;			
				if(tmp_val < 0) tmp_val = tmp_val + 60;
				EDIT_SetValue(hItem,tmp_val);
				//tmpwheel=KeyLed_State.wheel;
			}
			EDIT_SetValue(hItem,tmp_val);
			//EDIT_SetValue(hItem,KeyLed_State.wheel);	
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SECOND);
		if(WM_HasFocus(hItem))//改变秒
		{
			tmp_val = EDIT_GetValue(hItem);
			if(1 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val + 1;
				if(tmp_val >59) tmp_val = tmp_val - 60;
				EDIT_SetValue(hItem,tmp_val);
				//tmpwheel=KeyLed_State.wheel;
			}
			else if(2 == KeyLed_State.rotate)
			{
				tmp_val = tmp_val - 1;			
				if(tmp_val < 0) tmp_val = tmp_val + 60;
				EDIT_SetValue(hItem,tmp_val);
				//tmpwheel=KeyLed_State.wheel;
			}
			EDIT_SetValue(hItem,tmp_val);
			//EDIT_SetValue(hItem,KeyLed_State.wheel);	
		}
		break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/**
  * @brief  callback for Communit Settings
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */

static void _cbCommunitSettings(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;

	int cursorpos=0;
	int index=0;
  
  hItem = pMsg->hWin;
	WINDOW_SetBkColor(hItem, 0x00FFFFFF);
	
  switch (pMsg->MsgId) {   
  case WM_INIT_DIALOG:     
    Commu_Setting_Init(pMsg);
    Wheel_Encoder_Write(0);
    break;
	case	MY_MESSAGE_WHEEL://处理滚轮事件
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_NETWORK);
		
		if(WM_HasFocus(hItem))//输入网络名称
		{
			EDIT_SetCursorAtChar(hItem,cursorindex);
			index = Get_InputChar_Index(Wheel_Encoder_Read());
			if(cursorindex==EDIT_GetCursorCharPos(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_DELETE);
				EDIT_AddKey(hItem,Get_InputChar(index));
				cursorpos=EDIT_GetCursorCharPos(hItem);
				EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
			}	
		}

		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SECKEY);
		if(WM_HasFocus(hItem))//输入秘钥
		{
			EDIT_SetCursorAtChar(hItem,cursorindex);
			index = Get_InputChar_Index(Wheel_Encoder_Read());
			if(cursorindex==EDIT_GetCursorCharPos(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_DELETE);
				EDIT_AddKey(hItem,Get_InputChar(index));
				cursorpos=EDIT_GetCursorCharPos(hItem);
				EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
			}	
		}
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR1);
		if(WM_HasFocus(hItem))//输入服务器地址
		{
			EDIT_SetCursorAtChar(hItem,cursorindex);
			index = Get_InputNum_Index(Wheel_Encoder_Read());
			if(cursorindex==EDIT_GetCursorCharPos(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_DELETE);
				EDIT_AddKey(hItem,Get_InputNum(index));
				cursorpos=EDIT_GetCursorCharPos(hItem);
				if(cursorindex == 2) EDIT_SetSel(hItem,cursorpos,cursorpos);
				else EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
			}
			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR2);
		if(WM_HasFocus(hItem))//输入服务器地址
		{
			EDIT_SetCursorAtChar(hItem,cursorindex);
			index = Get_InputNum_Index(Wheel_Encoder_Read());
			if(cursorindex==EDIT_GetCursorCharPos(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_DELETE);
				EDIT_AddKey(hItem,Get_InputNum(index));
				cursorpos=EDIT_GetCursorCharPos(hItem);
				if(cursorindex == 2) EDIT_SetSel(hItem,cursorpos,cursorpos);
				else EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR3);
		if(WM_HasFocus(hItem))//输入服务器地址
		{
			EDIT_SetCursorAtChar(hItem,cursorindex);
			index = Get_InputNum_Index(Wheel_Encoder_Read());
			if(cursorindex==EDIT_GetCursorCharPos(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_DELETE);
				EDIT_AddKey(hItem,Get_InputNum(index));
				cursorpos=EDIT_GetCursorCharPos(hItem);
				if(cursorindex == 2) EDIT_SetSel(hItem,cursorpos,cursorpos);
				else EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR4);
		if(WM_HasFocus(hItem))//输入服务器地址
		{
			EDIT_SetCursorAtChar(hItem,cursorindex);
			index = Get_InputNum_Index(Wheel_Encoder_Read());
			if(cursorindex==EDIT_GetCursorCharPos(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_DELETE);
				EDIT_AddKey(hItem,Get_InputNum(index));
				cursorpos=EDIT_GetCursorCharPos(hItem);
				if(cursorindex == 2) EDIT_SetSel(hItem,cursorpos,cursorpos);
				else EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_TCPPORT);
		if(WM_HasFocus(hItem))//输入端口号
		{
			EDIT_SetCursorAtChar(hItem,cursorindex);
			index = Get_InputNum_Index(Wheel_Encoder_Read());
			if(cursorindex==EDIT_GetCursorCharPos(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_DELETE);
				EDIT_AddKey(hItem,Get_InputNum(index));
				cursorpos=EDIT_GetCursorCharPos(hItem);
				if(cursorindex == 3) EDIT_SetSel(hItem,cursorpos,cursorpos);
				else EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
			}
			
		}
        hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOOPNUM);
		if(WM_HasFocus(hItem))//输入流水线编号
		{
			EDIT_SetCursorAtChar(hItem,cursorindex);
			index = Get_InputNum_Index(Wheel_Encoder_Read());
			if(cursorindex==EDIT_GetCursorCharPos(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_DELETE);
				EDIT_AddKey(hItem,Get_InputNum(index));
				cursorpos=EDIT_GetCursorCharPos(hItem);
				if(cursorindex == 2) EDIT_SetSel(hItem,cursorpos,cursorpos);
				else EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
			}
			
		}
	
		break;
	case MY_MESSAGE_DOWN://向右移动光标
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SECKEY);//修改密钥
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == EDIT_GetNumChars(hItem) )
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_NETWORK);//修改网络名称
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == EDIT_GetNumChars(hItem) )
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR1);//修改服务器地址
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == 2)
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR2);//修改服务器地址
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == 2)
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR3);//修改服务器地址
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == 2)
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR4);//修改服务器地址
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == 2)
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_TCPPORT);//修改端口号
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == 3)
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOOPNUM);//修改流水线编号
		if(WM_HasFocus(hItem))	
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			if(cursorpos == 2)
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			else
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}			
		}
		break;
  default:
    WM_DefaultProc(pMsg);
  }
}






/**
  * @brief  callback for Advance Settings
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */

static void _cbAdvanceSettings(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  uint8_t sel=0;
  int index=0;
	int cursorpos=0;
	uint8_t NumChars=0;
	
  hItem = pMsg->hWin;
	WINDOW_SetBkColor(hItem, 0x00FFFFFF);
	//WT_Config_Read();//读取配置参数
	
  switch (pMsg->MsgId) {
    
  case WM_INIT_DIALOG:
 		Advance_Setting_Init(pMsg);	
    break;
	case	MY_MESSAGE_WHEEL://处理滚轮事件
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_PASSWD);
		if(WM_HasFocus(hItem))//改变字符值
		{
			EDIT_SetCursorAtChar(hItem,cursorindex);
			index = Get_InputChar_Index(KeyLed_State.wheel);
			if(cursorindex==EDIT_GetCursorCharPos(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_DELETE);
				EDIT_AddKey(hItem,Get_InputChar(index));
				cursorpos=EDIT_GetCursorCharPos(hItem);
				EDIT_SetSel(hItem,cursorpos-1,cursorpos-1);
			}	
		}
		break;
	case	MY_MESSAGE_DOWN://处理向下按钮事件
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TESTMODE);
		if(WM_HasFocus(hItem))//选择测试模式
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<2)
			{
				DROPDOWN_IncSel(hItem);
			}					
			else //sel>=2 
			{
				DROPDOWN_SetSel(hItem,0);		
			}						
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_WTLIMIT);
		if(WM_HasFocus(hItem))//选择导通阈值
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<2)
			{
				DROPDOWN_IncSel(hItem);
			}
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,0);		
			}						
		}
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_PRINTSERV);
		if(WM_HasFocus(hItem))//选择是否为打印服务器
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<1)
			{
				DROPDOWN_IncSel(hItem);
			}
			else //sel>=2 
			{
				DROPDOWN_SetSel(hItem,0);		
			}				
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TESTRULE);
		if(WM_HasFocus(hItem))//选择测试模式
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<1)
			{
				DROPDOWN_IncSel(hItem);
			}
			else //sel>=2 
			{
				DROPDOWN_SetSel(hItem,0);		
			}				
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_CAPTIAL);
		if(WM_HasFocus(hItem))//选择电容阈值
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<3)
			{
				DROPDOWN_IncSel(hItem);
			}
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,0);		
			}						
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_PASSWD);
		if(WM_HasFocus(hItem))//移动光标
		{
			cursorpos=EDIT_GetCursorCharPos(hItem);
			NumChars = EDIT_GetNumChars(hItem);
			if(cursorpos <= (NumChars-1) )
			{
				EDIT_SetCursorAtChar(hItem,cursorpos+1);
				EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
			if(cursorpos == NumChars )
			{
				EDIT_SetCursorAtChar(hItem,0);
				EDIT_SetSel(hItem,0,0);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
		}
		break;
  default:
    WM_DefaultProc(pMsg);
  }
}


/**
  * @brief  callback for Debug Settings
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */

static void _cbDebugSettings(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  uint8_t sel=0;
	
  hItem = pMsg->hWin;
	WINDOW_SetBkColor(hItem, 0x00FFFFFF);
	//WT_Config_Read();//读取配置参数
	
  switch (pMsg->MsgId) {
    
  case WM_INIT_DIALOG:
 		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SIGNAL);
		TEXT_SetText(hItem, "信号源:");
        TEXT_SetFont(hItem, &GUI_FontHZ16);
        TEXT_SetTextColor(hItem,GUI_BLUE);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_SIGNAL);
        DROPDOWN_SetFont(hItem,GUI_FONT_16_1);
        DROPDOWN_AddString(hItem, "Infr_On");	
        DROPDOWN_AddString(hItem, "Infr_Off");	
        DROPDOWN_AddString(hItem, "Relay1_On");	
        DROPDOWN_AddString(hItem, "Relay1_Off");	
        DROPDOWN_AddString(hItem, "Relay2_On");	
        DROPDOWN_AddString(hItem, "Relay2_Off");	
        DROPDOWN_AddString(hItem, "Relay3_On");	
        DROPDOWN_AddString(hItem, "Relay3_Off");	
        DROPDOWN_SetSel(hItem,0);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFRARED);
		TEXT_SetText(hItem, "Infrared:");
        TEXT_SetFont(hItem, &GUI_FontHZ16);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY1);
        TEXT_SetText(hItem, "DIO_IN1:");
        TEXT_SetFont(hItem, &GUI_FontHZ16);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY2);
        TEXT_SetText(hItem, "DIO_IN2:");
        TEXT_SetFont(hItem, &GUI_FontHZ16);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY3);
        TEXT_SetText(hItem, "DIO_IN3:");
        TEXT_SetFont(hItem, &GUI_FontHZ16);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFRARED_ST);
		TEXT_SetBkColor(hItem,GUI_GRAY);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY1_ST);
		TEXT_SetBkColor(hItem,GUI_GRAY);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY2_ST);
		TEXT_SetBkColor(hItem,GUI_GRAY);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY3_ST);
		TEXT_SetBkColor(hItem,GUI_GRAY);
		
		
		//AD_Update_SourceAddr(AD_SourceAddr_U45V,AD_SourceAddr_GND);

    break;
		case	MY_MESSAGE_DOWN://处理向下按钮事件
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_SIGNAL);
		if(WM_HasFocus(hItem))//选择测试模式
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<7)
			{
				DROPDOWN_IncSel(hItem);
			}					
			else //sel>=5 
			{
				DROPDOWN_SetSel(hItem,0);		
			}										
		}
		sel=DROPDOWN_GetSel(hItem);
		
		
		switch (sel)
		{
//			case 0:   Infra_PWM_ON(); break;
//			case 1:   Infra_PWM_OFF(); break;
			case 0:   osMessagePut(UartInfrEvent, UartInfr_TX_Event, 0); break;
			case 1:   osMessagePut(UartInfrEvent, UartInfr_TX_STOP_Event, 0); break;		
			case 2:   IO_State.output = IO_State.output | (1<<0); break;
			case 3:   IO_State.output = IO_State.output & (0<<0); break;
			case 4:   IO_State.output = IO_State.output | (1<<1); break;
			case 5:   IO_State.output = IO_State.output & (0<<1); break;
			case 6:   IO_State.output = IO_State.output | (1<<2); break;
			case 7:   IO_State.output = IO_State.output & (0<<2); break;
			default:  break;
		}
		
		if((IO_State.input & (1<<3)) !=0 )
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFRARED_ST);
			TEXT_SetBkColor(hItem,GUI_GREEN);
		}
		else
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFRARED_ST);
			TEXT_SetBkColor(hItem,GUI_GRAY);
		}
		if((IO_State.input & (1<<0)) !=0 )
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY1_ST);
			TEXT_SetBkColor(hItem,GUI_GREEN);
		}
		else
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY1_ST);
			TEXT_SetBkColor(hItem,GUI_GRAY);
		}
		if((IO_State.input & (1<<1)) !=0 )
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY2_ST);
			TEXT_SetBkColor(hItem,GUI_GREEN);
		}
		else
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY2_ST);
			TEXT_SetBkColor(hItem,GUI_GRAY);
		}
		if((IO_State.input & (1<<2)) !=0 )
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY3_ST);
			TEXT_SetBkColor(hItem,GUI_GREEN);
		}
		else
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALY3_ST);
			TEXT_SetBkColor(hItem,GUI_GRAY);
		}
		break;
		
		default:
    WM_DefaultProc(pMsg);
  }
}

/**
  * @brief  Callback routine of the dialog
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:

    /* Initialization of 'System Information'  */
    hItem = pMsg->hWin;   
    WINDOW_SetBkColor(hItem, 0x00FFFFFF);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIPAGE);
    
		MULTIPAGE_SetFont(hItem,&GUI_FontHZ16);
   /* Create and attache the MULTIPAGE dialog windows */
		hDialog_system = GUI_CreateDialogBox(_aDialogSystemSettings, 
                                  GUI_COUNTOF(_aDialogSystemSettings), 
                                  &_cbSystemSettings, WM_UNATTACHED, 0, 0); 
    MULTIPAGE_AddPage(hItem, hDialog_system, "系统设置");	
	
		hDialog_time = GUI_CreateDialogBox(_aDialogTimeSettings, 
                                  GUI_COUNTOF(_aDialogTimeSettings), 
                                  &_cbTimeSettings, WM_UNATTACHED, 0, 0); 
    MULTIPAGE_AddPage(hItem, hDialog_time, "时间设置");
	
		hDialog_comm = GUI_CreateDialogBox(_aDialogCommunitSettings, 
                                  GUI_COUNTOF(_aDialogCommunitSettings), 
                                  &_cbCommunitSettings, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hItem, hDialog_comm, "通信设置");
		
		hDialog_signal = GUI_CreateDialogBox(_aDialogDebugSettings, 
                                  GUI_COUNTOF(_aDialogDebugSettings), 
                                  &_cbDebugSettings, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hItem, hDialog_signal, "调试设置");
		
		hDialog_advance = GUI_CreateDialogBox(_aDialogAdvanceSettings, 
                                  GUI_COUNTOF(_aDialogAdvanceSettings), 
                                  &_cbAdvanceSettings, WM_UNATTACHED, 0, 0); 
    MULTIPAGE_AddPage(hItem, hDialog_advance, "高级设置");
		
    MULTIPAGE_SelectPage(hItem, 0);  
		MULTIPAGE_SetBkColor(hItem, 0x00FFFFFF,MULTIPAGE_CI_ENABLED);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_OK);
		BUTTON_SetFont(hItem,&GUI_FontHZ12);
		BUTTON_SetSkinClassic(hItem);
		BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_GREEN);
		BUTTON_SetFocussable(hItem,0);//不接收焦点
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DEFAULT);
		BUTTON_SetFont(hItem,&GUI_FontHZ12);
		BUTTON_SetSkinClassic(hItem);
		BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_GREEN);
		BUTTON_SetFocussable(hItem,0);//不接收焦点
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_EXIT);
		BUTTON_SetFont(hItem,&GUI_FontHZ12);
		BUTTON_SetSkinClassic(hItem);
		BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_RED);
		BUTTON_SetFocussable(hItem,0);//不接收焦点
		
    break;
   
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}


static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos)
{
  WM_HWIN hWindow;
	WM_HWIN hItem;
	WM_HWIN hItem_slider_light;
	WM_HWIN hItem_slider_audio;
	WM_HWIN hItem_audiook;
	WM_HWIN hItem_audiong;
	WM_HWIN hItem_Print;
	WM_HWIN hItem_Testmode;
	WM_HWIN hItem_wtlimit;
	WM_HWIN hItem_printserv;
	WM_HWIN hItem_caplimit;
	WM_HWIN hDialog;
	
	WM_HWIN hItem_network;
	WM_HWIN hItem_seckey;
	WM_HWIN hItem_serv_ip1,hItem_serv_ip2,hItem_serv_ip3,hItem_serv_ip4;
	WM_HWIN hItem_tcpport;
	WM_HWIN hItem_devid;
	WM_HWIN hItem_testwait;
	WM_HWIN hItem_imsmode;
	WM_HWIN hParent;
	WM_MESSAGE Msg;
	
	WM_HWIN hItem_year;
	WM_HWIN hItem_month;
	WM_HWIN hItem_day;
	WM_HWIN hItem_hour;
	WM_HWIN hItem_min;
	WM_HWIN hItem_sec;
	
	WM_HWIN hItem_passwd;
	WM_HWIN hItem_Testrule;
	WM_HWIN hItem_printmode;
	WM_HWIN hItem_printsn;
    WM_HWIN hItem_loopnum;

	uint32_t i;
	uint32_t index=0;
	uint8_t buf8;
	//uint32_t focus;
//	uint32_t wheel_stat=0;
//	KeyLed_State.wheel=0;
	
	uint8_t sec,min,hour,day,month;
	uint16_t year;
	uint8_t res;
//	uint16_t buf16=0;
	
//	char mac[10];
	wt_SetText_Title("");
	wt_SetText_Menu(wt_setting.name);
	wt_SetText_Status("设置系统参数");
	
	WT_Config_Read();//读取配置参数
	
  hWindow = GUI_CreateDialogBox(_aDialog, GUI_COUNTOF(_aDialog), _cbDialog, hWin, xpos, ypos);
	hItem = WM_GetDialogItem(hWin, ID_MULTIPAGE);

	hItem_slider_light = WM_GetDialogItem(hWin,ID_SLIDER_LIGHT);
	hItem_slider_audio = WM_GetDialogItem(hWin,ID_SLIDER_AUDIO);
	hItem_Print = WM_GetDialogItem(hWin,ID_DROPDOWN_PRINT);
	hItem_Testmode = WM_GetDialogItem(hWin,ID_DROPDOWN_TESTMODE);
	hItem_wtlimit = WM_GetDialogItem(hWin,ID_DROPDOWN_WTLIMIT);
	hItem_printserv = WM_GetDialogItem(hWin,ID_DROPDOWN_PRINTSERV);
	hItem_caplimit = WM_GetDialogItem(hWin,ID_DROPDOWN_CAPTIAL);
	
	hItem_network = WM_GetDialogItem(hWin,ID_EDIT_NETWORK);
	hItem_seckey = WM_GetDialogItem(hWin,ID_EDIT_SECKEY);
	hItem_serv_ip1 = WM_GetDialogItem(hWin,ID_EDIT_SERVERADDR1);
	hItem_serv_ip2 = WM_GetDialogItem(hWin,ID_EDIT_SERVERADDR2);
	hItem_serv_ip3 = WM_GetDialogItem(hWin,ID_EDIT_SERVERADDR3);
	hItem_serv_ip4 = WM_GetDialogItem(hWin,ID_EDIT_SERVERADDR4);
	hItem_tcpport = WM_GetDialogItem(hWin,ID_EDIT_TCPPORT);
	hItem_devid = WM_GetDialogItem(hWin,ID_EDIT_DEVID);
	hItem_testwait = WM_GetDialogItem(hWin,ID_DROPDOWN_TESTWAIT);
	hItem_imsmode = WM_GetDialogItem(hWin,ID_DROPDOWN_IMS);
	
	hItem_audiook = WM_GetDialogItem(hWin,ID_DROPDOWN_AUDIOOK);
	hItem_audiong = WM_GetDialogItem(hWin,ID_DROPDOWN_AUDIONG);
	
	hItem_year = WM_GetDialogItem(hWin,ID_EDIT_YEAR);
	hItem_month = WM_GetDialogItem(hWin,ID_EDIT_MONTH);
	hItem_day = WM_GetDialogItem(hWin,ID_EDIT_DAY);
	hItem_hour = WM_GetDialogItem(hWin,ID_EDIT_HOUR);
	hItem_min = WM_GetDialogItem(hWin,ID_EDIT_MINUTE);
	hItem_sec = WM_GetDialogItem(hWin,ID_EDIT_SECOND);
	
	hItem_passwd = WM_GetDialogItem(hWin,ID_EDIT_PASSWD);
	hItem_Testrule = WM_GetDialogItem(hWin,ID_DROPDOWN_TESTRULE);
	hItem_printmode = WM_GetDialogItem(hWin,ID_DROPDOWN_PRINTMODE);
	hItem_printsn = WM_GetDialogItem(hWin,ID_EDIT_SERNUM);
    
    hItem_loopnum = WM_GetDialogItem(hWin,ID_EDIT_LOOPNUM);
	 
	goto normal_loop;
	passwd_auth:
	//创建密码输入对话框
		hDialog= Create_PasswdDlgWindow(hWindow);
		GUI_Exec();
		while (WM_IsWindow(hDialog))
		{
			BSP_Update_Wheel();
            if(BSP_GetKEY_State(KeyOK) == 1 )//wujun added 
			{
				while(BSP_GetKEY_State(KeyOK) == 1)
				{
					osDelay(10);
				}
				Msg.MsgId = MY_MESSAGE_OK;
				Msg.hWinSrc=hWindow;
				hItem=WM_GetFocussedWindow();
				hParent=WM_GetParent(hItem);
				WM_SendMessage(hParent,&Msg);
				buf8 = 0;
				hItem=WM_GetFocussedWindow();

			}
			if(BSP_GetKEY_State(KeyCancle) == 1 ) 
			{
				while(BSP_GetKEY_State(KeyCancle) == 1)
				{
					osDelay(10);
				}
				Msg.MsgId = MY_MESSAGE_CANCEL;
				Msg.hWinSrc=hWindow;
				hItem=WM_GetFocussedWindow();
				hParent=WM_GetParent(hItem);
				WM_SendMessage(hParent,&Msg);	
				buf8 = 2;
			}
			if(BSP_GetKEY_State(KeyWheel) == 1 )//删除字符
			{
				while(BSP_GetKEY_State(KeyWheel) == 1)
				{
					osDelay(10);
				}
				Msg.MsgId = MY_MESSAGE_BUTTONDELETE;
				hItem=WM_GetFocussedWindow();
				hParent=hDialog;
				WM_SendMessage(hParent,&Msg);
			}
		
			if(BSP_GetKEY_State(KeyDown) == 1)
			{
				buf8 = 10;
				while(BSP_GetKEY_State(KeyDown) == 1)
				{
					osDelay(20);
					buf8--;
					if(buf8 == 0) break;
				}
				Msg.MsgId = MY_MESSAGE_DOWN;
				hItem=WM_GetFocussedWindow();
				hParent=WM_GetParent(hItem);
				WM_SendMessage(hParent,&Msg);
			}
			
			if(BSP_GetKEY_State(KeyUp) == 1)
			{
				buf8 = 10;
				while(BSP_GetKEY_State(KeyUp) == 1)
				{
					osDelay(20);
					buf8--;
					if(buf8 == 0) break;
				}
				Msg.MsgId = MY_MESSAGE_UP;
				WM_SendMessage(hDialog,&Msg);
			}
//			if(KeyLed_State.wheel!=wheel_stat)//处理滚轮事件
//			{
//				Msg.MsgId = MY_MESSAGE_WHEEL;
//				hItem=WM_GetFocussedWindow();
//				hParent=WM_GetParent(hItem);
//				WM_SendMessage(hParent,&Msg);
//				wheel_stat=KeyLed_State.wheel;
//			}
            if(1 == KeyLed_State.rotate || 2 == KeyLed_State.rotate)
            {
                Msg.MsgId = MY_MESSAGE_WHEEL;
				hItem=WM_GetFocussedWindow();
				hParent=WM_GetParent(hItem);
				WM_SendMessage(hParent,&Msg);
//				wheel_stat=KeyLed_State.wheel;
                osDelay(100); 
            }
			GUI_Delay(20);
		 }
		// close config dialog
		if(buf8 != 0) 
		{
			// close dialog
			//wheel_value=0;
			KeyLed_State.wheel=0;
			GUI_EndDialog(hWindow,0);
			GUI_Exec();
			//win_stat=0;	
			Number_Windos = 0;
			return;
		}
		if(WM_IsWindow(hDialog) == 0) 
		{
			WM_SetFocus(hDialog_advance);
		}
	
	normal_loop:
	while(1)
    {
		BSP_Update_Wheel();
        //key detect
		if(BSP_GetKEY_State(KeyDown) == 1)
		{
			while(BSP_GetKEY_State(KeyDown) == 1)
			{
				osDelay(10);
			}
			
			Msg.MsgId = MY_MESSAGE_DOWN;
			hItem=WM_GetFocussedWindow();
			hParent=WM_GetParent(hItem);
			WM_SendMessage(hParent,&Msg);
			
		}
		if(BSP_GetKEY_State(KeyUp) == 1)//改变输入焦点
		{
			while(BSP_GetKEY_State(KeyUp) == 1)
			{
				osDelay(10);
			}
			GUI_SendKeyMsg(GUI_KEY_TAB, 1);
			if(WM_HasFocus(hItem_audiook)) 
			{
				osMessagePut(UartAudioEvent, UartAudioOK_REPEAT_TX_Event, 0);	//播放OK声音
			}
			else if(WM_HasFocus(hItem_audiong)) 
			{
				osMessagePut(UartAudioEvent, UartAudioNG_TX_Event, 0);	//播放NG声音
			}
			else osMessagePut(UartAudioEvent, UartAudioSTOP_TX_Event, 0);	//关闭声音
			
			//KeyLed_State.wheel=0;
            Wheel_Encoder_Write(0);//wheel值清零
			cursorindex = 0;
//			wheel_stat=0;
		}
		//保存配置
		if(BSP_GetKEY_State(KeyOK) == 1)
		{
			i=0;
			while(BSP_GetKEY_State(KeyOK) == 1)
			{
				i++;
				osDelay(100);
			}
			if(i < 50)	//短按保存，小于5秒
			{
				hItem=WM_GetFocussedWindow();
				hParent=WM_GetParent(hItem);
				if(hParent==hDialog_comm)//保存通信设置
				{
					EDIT_GetText(hItem_network,(char *)WT_Config.NetWork,14);
					EDIT_GetText(hItem_seckey,(char *)WT_Config.SecKey,14);
					WT_Config.Server_IP[0] = EDIT_GetValue(hItem_serv_ip1);
					WT_Config.Server_IP[1] = EDIT_GetValue(hItem_serv_ip2);
					WT_Config.Server_IP[2] = EDIT_GetValue(hItem_serv_ip3);
					WT_Config.Server_IP[3] = EDIT_GetValue(hItem_serv_ip4);
					WT_Config.TCP_Port = EDIT_GetValue(hItem_tcpport);
                    WT_Config.Loop_Num = EDIT_GetValue(hItem_loopnum);
					osMessagePut(Uart24GHzEvent, Uart24GHZ_CONF_Event, 0);
				}
				else if(hParent==hDialog_advance)//保存高级设置
				{
					WT_Config.TestMode = DROPDOWN_GetSel(hItem_Testmode);
					WT_Config.Mode_TestW = DROPDOWN_GetSel(hItem_wtlimit);
					WT_Config.PrintServ = DROPDOWN_GetSel(hItem_printserv);
					WT_Config.TestRule = DROPDOWN_GetSel(hItem_Testrule);
					WT_Config.Mode_TestCap = DROPDOWN_GetSel(hItem_caplimit);
					EDIT_GetText(hItem_passwd,(char *)WT_Config.Passwd,7);
				}
				else if(hParent==hDialog_system)//保存系统设置
				{
					WT_Config.BackLight = SLIDER_GetValue(hItem_slider_light);
					WT_Config.AudioVolume = SLIDER_GetValue(hItem_slider_audio);
					WT_Config.AudioOK = DROPDOWN_GetSel(hItem_audiook);
					WT_Config.AudioNG = DROPDOWN_GetSel(hItem_audiong)+4;
					WT_Config.Print = DROPDOWN_GetSel(hItem_Print);	
					WT_Config.Print_Mode = DROPDOWN_GetSel(hItem_printmode);
					WT_Config.Dev_ID = EDIT_GetValue(hItem_devid);
					WT_Config.Test_Wait = DROPDOWN_GetSel(hItem_testwait);
					WT_Config.Print_SN = EDIT_GetValue(hItem_printsn);
					WT_Config.IMS_Mode = DROPDOWN_GetSel(hItem_imsmode);
					print_sn = EDIT_GetValue(hItem_printsn);
					WT_PrintSN_Write(print_sn);
					
				}
				else if(hParent==hDialog_time)//保存时间设置
				{
					sec=EDIT_GetValue(hItem_sec);
					min=EDIT_GetValue(hItem_min);
					hour=EDIT_GetValue(hItem_hour);
					day=EDIT_GetValue(hItem_day);
					month=EDIT_GetValue(hItem_month);
					year=EDIT_GetValue(hItem_year)-RTCTIME_YEAR;
					WT_Config.InfoRTC[0]=sec;
					set_systemtime(sec,min,hour,day,month,year);
				}				
				res = WT_Config_Save();
				if(res == 0) //ok
				{
					wt_SetText_Status("保存参数成功");
				}
				else //error
				{
					wt_SetText_Status("保存参数失败");
				}
			}	
			else//长按恢复默认值
			{
				wt_SetText_Status("恢复默认设置");
				LoadFontLib();
				res=WT_Config_Restore();
				if(res==0)//0-ok, 1-error
				{
					 EDIT_SetText(hItem_network,(const char *)WT_Config.NetWork);
					 EDIT_SetText(hItem_seckey,(const char *)WT_Config.SecKey);
					 EDIT_SetValue(hItem_serv_ip1,WT_Config.Server_IP[0]);
					 EDIT_SetValue(hItem_serv_ip2,WT_Config.Server_IP[1]);
					 EDIT_SetValue(hItem_serv_ip3,WT_Config.Server_IP[2]);
					 EDIT_SetValue(hItem_serv_ip4,WT_Config.Server_IP[3]);
					 EDIT_SetValue(hItem_tcpport,WT_Config.TCP_Port);
					 EDIT_SetValue(hItem_devid,WT_Config.Dev_ID);
                     EDIT_SetValue(hItem_loopnum,WT_Config.Loop_Num);
					 
					 DROPDOWN_SetSel(hItem_Testmode,WT_Config.TestMode);
					 DROPDOWN_SetSel(hItem_wtlimit,WT_Config.Mode_TestW);
					 DROPDOWN_SetSel(hItem_printserv,WT_Config.PrintServ);
					 DROPDOWN_SetSel(hItem_caplimit,WT_Config.Mode_TestCap);
					 SLIDER_SetValue(hItem_slider_light,WT_Config.BackLight);
					 SLIDER_SetValue(hItem_slider_audio,WT_Config.AudioVolume);
					 DROPDOWN_SetSel(hItem_Print,WT_Config.Print);
					 DROPDOWN_SetSel(hItem_testwait,WT_Config.Test_Wait);
					 DROPDOWN_SetSel(hItem_printmode,WT_Config.IMS_Mode);
					 DROPDOWN_SetSel(hItem_audiook,WT_Config.AudioOK);
					 DROPDOWN_SetSel(hItem_audiong,WT_Config.AudioNG-4);
					 EDIT_SetValue(hItem_sec,WT_Config.InfoRTC[5]);
					 EDIT_SetValue(hItem_min,WT_Config.InfoRTC[4]);
					 EDIT_SetValue(hItem_hour,WT_Config.InfoRTC[3]);
					 EDIT_SetValue(hItem_day,WT_Config.InfoRTC[2]);
					 EDIT_SetValue(hItem_month,WT_Config.InfoRTC[1]);
					 EDIT_SetValue(hItem_year,WT_Config.InfoRTC[0]+2000);
					 sec=EDIT_GetValue(hItem_sec);
					 min=EDIT_GetValue(hItem_min);
					 hour=EDIT_GetValue(hItem_hour);
					 day=EDIT_GetValue(hItem_day);
					 month=EDIT_GetValue(hItem_month);
					 year=EDIT_GetValue(hItem_year)-RTCTIME_YEAR;
					 set_systemtime(sec,min,hour,day,month,year);
					 EDIT_SetText(hItem_passwd,(const char *)WT_Config.Passwd);
					 DROPDOWN_SetSel(hItem_Testrule,WT_Config.TestRule);
					 DROPDOWN_SetSel(hItem_printmode,WT_Config.Print_Mode);
					 EDIT_SetValue(hItem_printsn,0);
				}
				//WT_Printcfg_Clear();//清除打印配置文件
			}				
		}
		if(BSP_GetKEY_State(KeyCancle) == 1)//关闭窗口
		{
			while(BSP_GetKEY_State(KeyCancle) == 1)
			{
				osDelay(10);
			}
			osMessagePut(UartAudioEvent, UartAudioSTOP_TX_Event, 0);	//关闭声音
			GUI_EndDialog(hWindow,0);
			KeyLed_State.wheel=0;
			//wheel_value=0;
			Number_Windos = 0;
			return;
		}
		//切换标签
		if(BSP_GetKEY_State(KeyWheel) == 1)
		{
			while(BSP_GetKEY_State(KeyWheel) == 1)
			{
				osDelay(10);
			}

			hItem = WM_GetDialogItem(hWin, ID_MULTIPAGE);
			osMessagePut(UartAudioEvent, UartAudioSTOP_TX_Event, 0);	//关闭声音
			index++;			
			if(index==5)
			{
				index=0;
			}
			MULTIPAGE_SelectPage(hItem,index);
			
			hItem=WM_GetFocussedWindow();
			hParent=WM_GetParent(hItem);
			if(hParent==hDialog_advance)//系统设置
			{
				goto passwd_auth;
			}
		}
//		if(KeyLed_State.wheel!=wheel_stat)//处理滚轮事件
//		{
//			Msg.MsgId = MY_MESSAGE_WHEEL;
//			hItem=WM_GetFocussedWindow();
//			hParent=WM_GetParent(hItem);
//			WM_SendMessage(hParent,&Msg);
//			wheel_stat=KeyLed_State.wheel;
//			GUI_Delay(100);
//		}
        if(1 == KeyLed_State.rotate || 2 == KeyLed_State.rotate)//处理滚轮事件
        {
            Msg.MsgId = MY_MESSAGE_WHEEL;
            hItem=WM_GetFocussedWindow();
            hParent=WM_GetParent(hItem);
            WM_SendMessage(hParent,&Msg);
//            wheel_stat=KeyLed_State.wheel;
            osDelay(100); 
        }

		//AD_ReadValue(10*1000, &buf16);
		
		//delay
		osDelay(30); 
		GUI_Exec();
	}
}

//系统设置初始化
void System_Setting_Init(WM_MESSAGE * pMsg)
{
    WM_HWIN hItem;
    //亮度
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_LIGHT);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_LIGHT);
    SLIDER_SetRange(hItem, 0, 10);
    SLIDER_SetNumTicks(hItem, 11);
    SLIDER_SetValue(hItem,WT_Config.BackLight);
    // Initialization of 'Light'
    //音量
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_AUDIO);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_AUDIO);
    SLIDER_SetRange(hItem, 0, 10);
    SLIDER_SetNumTicks(hItem, 11);
    SLIDER_SetValue(hItem,WT_Config.AudioVolume);
    GUI_SetColor(GUI_BLACK);

    //声音OK
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_AUDIOOK);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_AUDIOOK);
    DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "OK-1");
    DROPDOWN_AddString(hItem, "OK-2");
    DROPDOWN_AddString(hItem, "OK-3");
    DROPDOWN_AddString(hItem, "OK-4");

    DROPDOWN_SetSel(hItem,WT_Config.AudioOK);
    GUI_SetColor(GUI_BLACK);

    //声音NG
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_AUDIONG);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_AUDIONG);
    DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "NG-1");
    DROPDOWN_AddString(hItem, "NG-2");
    DROPDOWN_AddString(hItem, "NG-3");
    DROPDOWN_AddString(hItem, "NG-4");
    if((WT_Config.AudioNG-4)>0)
    DROPDOWN_SetSel(hItem,WT_Config.AudioNG-4);
    else DROPDOWN_SetSel(hItem,0);
    GUI_SetColor(GUI_BLACK);

    //本地打印
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_PRINT);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_PRINT);
    DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "否");
    DROPDOWN_AddString(hItem, "是");
    DROPDOWN_SetSel(hItem,WT_Config.Print);	

    //打印方式
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_PRINTMODE);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_PRINTMODE);
    DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "并口打印");
    DROPDOWN_AddString(hItem, "串口打印");
    DROPDOWN_SetSel(hItem,WT_Config.Print_Mode);	

    // 设备编号
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_DEVID);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_DEVID);    
    //EDIT_SetTextMode(hItem);
    EDIT_SetDecMode(hItem, 1, 1,999, 0, 0);
    EDIT_SetValue(hItem, WT_Config.Dev_ID);
		EDIT_SetFont(hItem,GUI_FONT_20_1);
		// 测试等待时间
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TESTWAIT);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TESTWAIT);
    DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "30s");
    DROPDOWN_AddString(hItem, "60s");
    DROPDOWN_AddString(hItem, "120s");
    DROPDOWN_AddString(hItem, "200s");
    DROPDOWN_AddString(hItem, "300s");
    DROPDOWN_AddString(hItem, "1000s");
    DROPDOWN_SetSel(hItem,WT_Config.Test_Wait);	

    //流水号
    print_sn = WT_PrintSN_Read();
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SERNUM);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERNUM);    
    EDIT_SetDecMode(hItem, 1, 1,9999, 0, 0);
    EDIT_SetValue(hItem,print_sn);
    EDIT_SetFont(hItem,GUI_FONT_20_1);
		//IMS连接
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_IMSTEXT);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_IMS);
		DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "是");
    DROPDOWN_AddString(hItem, "否");
		DROPDOWN_SetSel(hItem,WT_Config.IMS_Mode);	
}

//时间设置初始化
void Time_Setting_Init(WM_MESSAGE * pMsg)
{
    WM_HWIN hItem;
    uint8_t sec,min, hour, day, month;
    uint16_t year;
    //WT_Config_Read();//读取配置参数
    get_systime(&sec,&min,&hour,&day,&month,&year);
    //日期设置
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_DATE);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ16);

    //Initialization of 'Edit-year'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_YEAR);
    EDIT_SetDecMode(hItem, 2017, 1970,9999, 0, 0);
    EDIT_SetValue(hItem,year);
    EDIT_SetFont(hItem,&GUI_FontHZ16);
    //EDIT_SetText(hItem, "2017");
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_YEAR);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ16);
    //Initialization of 'Edit-month'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MONTH);
    EDIT_SetDecMode(hItem, 1, 1,12, 0, 0);
    EDIT_SetValue(hItem,month);
    EDIT_SetFont(hItem,&GUI_FontHZ16);
    //EDIT_SetText(hItem, "1");
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MONTH);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ16);
    //Initialization of 'Edit-day'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_DAY);
    EDIT_SetDecMode(hItem, 1, 1,31, 0, 0);
    EDIT_SetValue(hItem,day);
    EDIT_SetFont(hItem,&GUI_FontHZ16);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_DAY);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ16);
    //时间设置
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TIME);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ16);
    //Initialization of 'Edit-hour'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_HOUR);
    EDIT_SetDecMode(hItem, 12, 0,23, 0, 0);
    EDIT_SetValue(hItem,hour);
    EDIT_SetFont(hItem,&GUI_FontHZ16);
    //EDIT_SetText(hItem, "12");
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_HOUR);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ16);
    //Initialization of 'Edit-minute'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MINUTE);
    EDIT_SetDecMode(hItem, 0, 0,59, 0, 0);
    EDIT_SetValue(hItem,min);
    EDIT_SetFont(hItem,&GUI_FontHZ16);
    //EDIT_SetText(hItem, "00");
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MINUTE);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ16);
    //Initialization of 'Edit-second'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SECOND);
    EDIT_SetDecMode(hItem, 0, 0,59, 0, 0);
    EDIT_SetValue(hItem,sec);
    EDIT_SetFont(hItem,&GUI_FontHZ16);
    //EDIT_SetText(hItem, "00");
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SECOND);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ16);
}

//通信设置初始化
void Commu_Setting_Init(WM_MESSAGE * pMsg)
{
    char mac[20];
    char ipaddr[10];
    WM_HWIN hItem;
    // 网络名称
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_NETWORK);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_NETWORK);

    EDIT_EnableBlink(hItem, 600, 1);
    EDIT_SetFont(hItem,GUI_FONT_24_1);
    EDIT_SetText(hItem, (const char *)WT_Config.NetWork);
    // 秘钥
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SECKEY);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SECKEY);
    EDIT_SetText(hItem, (const char *)WT_Config.SecKey);
    EDIT_SetFont(hItem,GUI_FONT_24_1);
    EDIT_EnableBlink(hItem, 600, 1);
    // 服务器地址
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SERVERADDR);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SERVERADDR1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_BOTTOM);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SERVERADDR2);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_BOTTOM);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SERVERADDR3);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_BOTTOM);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR1);
    EDIT_SetFont(hItem,GUI_FONT_20_1);
    EDIT_SetDecMode(hItem, 192, 0,254, 0, 0);
    EDIT_SetValue(hItem, WT_Config.Server_IP[0]);
    EDIT_EnableBlink(hItem, 600, 1);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR2);
    EDIT_SetFont(hItem,GUI_FONT_20_1);
    EDIT_SetDecMode(hItem, 168, 0,254, 0, 0);
    EDIT_SetValue(hItem, WT_Config.Server_IP[1]);
    EDIT_EnableBlink(hItem, 600, 1);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR3);
    EDIT_SetFont(hItem,GUI_FONT_20_1);
    EDIT_SetDecMode(hItem, 1, 0,254, 0, 0);
    EDIT_SetValue(hItem, WT_Config.Server_IP[2]);
    EDIT_EnableBlink(hItem, 600, 1);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SERVERADDR4);
    EDIT_SetFont(hItem,GUI_FONT_20_1);
    EDIT_SetDecMode(hItem, 100, 0,254, 0, 0);
    EDIT_SetValue(hItem, WT_Config.Server_IP[3]);
    EDIT_EnableBlink(hItem, 600, 1);
    // 端口号
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TCPPORT);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_TCPPORT);    
    EDIT_SetDecMode(hItem, 1000, 1000,8000, 0, 0);
    EDIT_SetValue(hItem,WT_Config.TCP_Port);
    EDIT_SetFont(hItem,GUI_FONT_20_1);


    // IP地址
    sprintf(ipaddr,"%d.%d.%d.%d",WT_Config.IP_Addr[0],WT_Config.IP_Addr[1],WT_Config.IP_Addr[2],WT_Config.IP_Addr[3]);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_IPADDR);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_IPADDR);    
    EDIT_SetTextMode(hItem);
    EDIT_SetText(hItem, ipaddr);
    EDIT_SetFocussable(hItem,0);
    EDIT_SetFont(hItem,GUI_FONT_16B_1);

    // MAC地址
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MACADDR);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MACADDR);    
    EDIT_SetTextMode(hItem);

    sprintf(mac,"%02x:%02x:%02x:%02x:%02x:%02x",WT_Config.MAC_Addr[0],WT_Config.MAC_Addr[1],WT_Config.MAC_Addr[2],WT_Config.MAC_Addr[3],\
            WT_Config.MAC_Addr[4],WT_Config.MAC_Addr[5]);
    EDIT_SetText(hItem, mac);
    EDIT_SetFocussable(hItem,0);
		EDIT_SetFont(hItem,GUI_FONT_13B_1);
        // 流水号
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_LOOPNUM);
        TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		TEXT_SetFont(hItem,&GUI_FontHZ12);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOOPNUM);    
		EDIT_SetDecMode(hItem, 0, 0,255, 0, 0);
        EDIT_SetValue(hItem,WT_Config.Loop_Num);
		EDIT_SetFont(hItem,GUI_FONT_20_1);
}

//高级设置初始化
void Advance_Setting_Init(WM_MESSAGE * pMsg)
{
    WM_HWIN hItem;
    //测试模式
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TESTMODE);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TESTMODE);
    DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "自动");
    DROPDOWN_AddString(hItem, "手动");
    DROPDOWN_AddString(hItem, "定时");	
    DROPDOWN_SetSel(hItem,WT_Config.TestMode);	
    //
    // 导通阈值
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_WTLIMIT);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_WTLIMIT);
    DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "365Ω");
    DROPDOWN_AddString(hItem, "1KΩ");
    DROPDOWN_AddString(hItem, "10KΩ");
    DROPDOWN_SetSel(hItem,WT_Config.Mode_TestW);	
		//
	  // 选择是否为打印服务器
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_PRINTSERV);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_PRINTSERV);
		DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
		DROPDOWN_AddString(hItem, "是");
        DROPDOWN_AddString(hItem, "否");
		//DROPDOWN_SetSel(hItem,WT_Config.StudyOptimizingMode);	
		DROPDOWN_SetSel(hItem,WT_Config.PrintServ);	

    // 电容阈值
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CAPTIAL);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_CAPTIAL);
    DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "0.1uF");
    DROPDOWN_AddString(hItem, "0.47uF");
    DROPDOWN_AddString(hItem, "1.0uF");
    DROPDOWN_AddString(hItem, "2.0uF");
    DROPDOWN_SetSel(hItem,WT_Config.Mode_TestCap);	//电容阈值, 0:0.1uF, 1:0.47uF, 2:1.0uF, 3:4.7uF; 
    //密码
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_PASSWD);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_PASSWD);
    EDIT_SetText(hItem, (const char *)WT_Config.Passwd);
    EDIT_SetCursorAtChar(hItem,0);
    //EDIT_SetFont(hItem,&GUI_FontHZ12);

    //测试规则
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TESTRULE);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,&GUI_FontHZ12);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TESTRULE);
    DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "循环检测");
    DROPDOWN_AddString(hItem, "单次检测");
    DROPDOWN_SetSel(hItem,WT_Config.TestRule);

}




//设置时间
void set_systemtime(uint8_t sec,uint8_t min, uint8_t hour, uint8_t day, uint8_t month,uint16_t year)
{
    RTC_TimeTypeDef   RTC_Time;
    RTC_DateTypeDef   RTC_DateStructure;

    //time 
    RTC_Time.Seconds = sec;
    RTC_Time.Minutes = min;
    RTC_Time.Hours = hour;
    k_SetTime(&RTC_Time);

    //date 
    RTC_DateStructure.Year = year;
    RTC_DateStructure.Month = month;
    RTC_DateStructure.Date = day;
    k_SetDate(&RTC_DateStructure);
}

//获取时间
static void get_systime(uint8_t *sec,uint8_t *min, uint8_t *hour, uint8_t *day, uint8_t *month,uint16_t *year)
{
    RTC_TimeTypeDef   RTC_Time;
    RTC_DateTypeDef   RTC_DateStructure;

    k_GetTime(&RTC_Time);
    *sec    =  RTC_Time.Seconds;
    *min    =  RTC_Time.Minutes;
    *hour   =  RTC_Time.Hours;

    k_GetDate(&RTC_DateStructure);
    *year =  RTC_DateStructure.Year + RTCTIME_YEAR;
    *month =  RTC_DateStructure.Month;
    *day =  RTC_DateStructure.Date;
}

/*************************** End of file ****************************/
