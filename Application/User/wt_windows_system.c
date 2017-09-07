/********************************************************************************
	Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      wt_windows_system.c
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

#include "DIALOG.h"
#include "wt_bsp.h"
#include "wt_task_gui.h"
#include "wt_task_wireselfcheck.h"
#include "main.h"
#include "tools.h"
#include "verision.h"


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define ID_WINDOW_0             (GUI_ID_USER + 0x00)
//#define ID_LISTVIEW_0         (GUI_ID_USER + 0x01)
#define ID_TEXT_COPYRIGHT       (GUI_ID_USER + 0x11)
#define ID_TEXT_SOFTWRE         (GUI_ID_USER + 0x15)
#define ID_TEXT_HARDWARE        (GUI_ID_USER + 0x16)
#define ID_TEXT_WEBSITE         (GUI_ID_USER + 0x17)
#define ID_TEXT_MAC             (GUI_ID_USER + 0x18)
#define ID_TEXT_TUNNEL          (GUI_ID_USER + 0x19)
#define ID_TEXT_MACVAL          (GUI_ID_USER + 0x1A)
#define ID_TEXT_TUNEVAL         (GUI_ID_USER + 0x1B)
#define ID_TEXT_ADDR            (GUI_ID_USER + 0x1C)
#define ID_TEXT_ADDRVAL         (GUI_ID_USER + 0x1D)
#define ID_TEXT_BOARD           (GUI_ID_USER + 0x1E)
#define ID_TEXT_BOARDSTAT       (GUI_ID_USER + 0x1F)
#define ID_TEXT_TRANSMIT        (GUI_ID_USER + 0x20)
#define ID_TEXT_TRANSMITSTAT    (GUI_ID_USER + 0x21)

extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_Info;  //wujun added
extern GUI_CONST_STORAGE GUI_BITMAP bm_logo_lzy115x84;

extern uint32_t wheel_value;
extern uint8_t WT_Config_Read(void);



static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos);
//static uint32_t items_show;
void show_item_LOG(WT_LogFileTypedef logInfo[],int16_t index,WM_HWIN hItem);
void update_item_LOG(int16_t index,WM_HWIN hItem);

K_ModuleItem_Typedef  wt_info =
{	
	6,
	"信息",
	&bm_ICO_Info,	
	//&CreateSystemInfo,
	Startup,
	0,
};


#define ID_IMAGE_0     			(GUI_ID_USER + 0x10)
#define ID_TEXT_0     			(GUI_ID_USER + 0x11)
#define ID_MULTIEDIT_0     	    (GUI_ID_USER + 0x12)
#define ID_BUTTON_0     		(GUI_ID_USER + 0x13)
#define ID_TEXT_1 				(GUI_ID_USER + 0x15)
#define ID_TEXT_2 				(GUI_ID_USER + 0x16)

//#define ID_TEXT_BOARD           (GUI_ID_USER + 0x04)
#define ID_LISTVIEW_0     	    (GUI_ID_USER + 0x05)
#define ID_LISTVIEW_1     	    (GUI_ID_USER + 0x0C)
#define ID_MULTIPAGE            (GUI_ID_USER + 0x0A)
#define ID_IMAGE_LOGO           (GUI_ID_USER + 0x0B)    

WM_HWIN hWindowLog;
WM_HWIN hWindowTask;
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
  { MULTIPAGE_CreateIndirect, "Multipage", ID_MULTIPAGE, 0, 0, 480, 222, 0, 0x0, 0 },  
};

static const GUI_WIDGET_CREATE_INFO _aDialogSystemInformation[] = {
  { WINDOW_CreateIndirect, "System Information", 0, 0,   0, 480, 222, FRAMEWIN_CF_MOVEABLE },
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_0, 18, 0, 115, 84, 0, 0, 0 },
  { TEXT_CreateIndirect, "soft-verion", ID_TEXT_SOFTWRE, 18, 100, 200, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "copyright", ID_TEXT_COPYRIGHT, 18, 125, 210, 35, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "website", ID_TEXT_WEBSITE, 18, 150, 200, 20, 0, 0x64, 0 },
	
  { TEXT_CreateIndirect, "hardware ver", ID_TEXT_HARDWARE, 260, 20, 200, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "MAC", ID_TEXT_MAC, 260, 45, 58, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "MAC val", ID_TEXT_MACVAL, 325, 45, 120, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Tunnel", ID_TEXT_TUNNEL, 260, 70, 58, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Tunnel val", ID_TEXT_TUNEVAL, 325, 70, 60, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Addr", ID_TEXT_ADDR, 260, 95, 58, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Addr val", ID_TEXT_ADDRVAL, 325, 95, 120, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "board", ID_TEXT_BOARD, 260, 120, 58, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "board stat", ID_TEXT_BOARDSTAT, 325, 120, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Transmit", ID_TEXT_TRANSMIT, 260, 145, 58, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "transmmit stat", ID_TEXT_TRANSMITSTAT, 325, 145, 80, 20, 0, 0x0, 0 },

};

static const GUI_WIDGET_CREATE_INFO _aDialogLogInfo[] = {
  { WINDOW_CreateIndirect, "LogInfo", 0, 0, 0, 480, 222, FRAMEWIN_CF_MOVEABLE },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 0, 0, 480, 200, 0, 0x0, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogTaskInfo[] = {
  { WINDOW_CreateIndirect, "TaskInfo", 0, 0, 0, 480, 222, FRAMEWIN_CF_MOVEABLE },
  { MULTIEDIT_CreateIndirect, "MultiEidittask", ID_MULTIEDIT_0, 0, 0, 240, 200, 0, 0x0, 0 },
};


/**
  * @brief  callback for System Information
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */
static void _cbSystemInformation(WM_MESSAGE * pMsg) 
{
    WM_HWIN hItem;
    char num[3];
    char str[40];
    char softver[20];
    char ip[20];

    WT_Config_Read();

    WINDOW_SetBkColor(pMsg->hWin, 0x00FFFFFF);
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:

    hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
    //pData = _GetImageById(ID_IMAGE_0_IMAGE_0, &FileSize);
    //IMAGE_SetBMP(hItem, pData, FileSize);
    IMAGE_SetBitmap(hItem, &bm_logo_lzy115x84);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_COPYRIGHT);
    TEXT_SetFont(hItem,&GUI_FontHZ12);
    TEXT_SetText(hItem, "版权所有(C)路之遥科技有限公司");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SOFTWRE);
    TEXT_SetFont(hItem,&GUI_FontHZ12);
    memset(str,0,sizeof(str));
    strcpy(str,"软件版本：");

    sprintf(softver,"%d.%d.%d",DEF_WT_VERSION_MAIN, DEF_WT_VERSION_SUB1, DEF_WT_VERSION_SUB2);

    strcat(str,softver);
    TEXT_SetText(hItem, str);
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_HARDWARE);
    TEXT_SetFont(hItem,&GUI_FontHZ12);
	TEXT_SetText(hItem, "硬件版本：STM32F429 V2.0");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_WEBSITE);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    TEXT_SetText(hItem, "http://www.lzy.cn");
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MAC);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    TEXT_SetText(hItem, "MAC地址：");
    
    memset(str,0,40);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MACVAL);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    sprintf(str,"%02x:%02x:%02x:%02x:%02x:%02x",WT_Config.MAC_Addr[0],WT_Config.MAC_Addr[1],WT_Config.MAC_Addr[2],WT_Config.MAC_Addr[3],WT_Config.MAC_Addr[4],WT_Config.MAC_Addr[5]);
    TEXT_SetText(hItem, str);

    memset(ip,0,20);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_ADDR);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    TEXT_SetText(hItem, "无线地址：");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_ADDRVAL);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    sprintf(ip,"%d.%d.%d.%d",WT_Config.IP_Addr[0],WT_Config.IP_Addr[1],WT_Config.IP_Addr[2],WT_Config.IP_Addr[3]);
    TEXT_SetText(hItem, ip);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TUNNEL);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    TEXT_SetText(hItem, "无线通道：");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TUNEVAL);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    TEXT_SetText(hItem, "2.4G");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_BOARD);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    TEXT_SetText(hItem, "板卡数量：");
		
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_BOARDSTAT);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    TEXT_SetText(hItem,itoa(SelfCheckItem.port_board_number,num,10)); 
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TRANSMIT);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    TEXT_SetText(hItem, "通信状态：");
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TRANSMITSTAT);
    TEXT_SetFont(hItem, &GUI_FontHZ12);
    TEXT_SetText(hItem, "OK");
    
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}


/**
  * @brief  callback for LogInfo
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */

static void _cbLogInfo(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
	HEADER_Handle hHeader;
  uint32_t tmp = 0;
	uint8_t num = 0;
  WT_LogFileTypedef logInfo[20];
	
  hItem = pMsg->hWin;
	
  WINDOW_SetBkColor(hItem, 0x00FFFFFF);
  switch (pMsg->MsgId) {
    
  case WM_INIT_DIALOG:    

    /* LogInfo */

    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
    hWindowLog = hItem;
    hHeader = LISTVIEW_GetHeader(hItem);
    HEADER_SetFont(hHeader,&GUI_FontHZ12);
    HEADER_SetHeight(hHeader,20);
    LISTVIEW_AddColumn(hItem, 120, "线束名称", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 60, "测试总数", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 60, "良品数", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 60, "不良数", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 70,"错误类型", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 110, "日期", GUI_TA_HCENTER | GUI_TA_VCENTER);

    LISTVIEW_SetGridVis(hItem,1);
    LISTVIEW_SetDefaultGridColor(GUI_GRAY);
    LISTVIEW_SetRowHeight(hItem, 25);
    LISTVIEW_EnableSort(hItem);
    LISTVIEW_SetFont(hItem, &GUI_FontHZ16);
	
    WT_LogFiles_Read(logInfo,&num);
		//items_show = num;
		show_item_LOG(logInfo,num,hItem);
    break;
    
  case WM_DELETE:  
    /* Save Setting before delete settings frame */
    
    tmp = k_BkupRestoreParameter(CALIBRATION_GENERAL_SETTINGS_BKP);
	
    /* check if new settings have to be saved */
    if(settings.d32 != tmp)
    {
      k_BkupSaveParameter(CALIBRATION_GENERAL_SETTINGS_BKP, settings.d32); 
    }
    break;    
    
  default:
    WM_DefaultProc(pMsg);
  }
}


/**
  * @brief  callback for TaskInfo
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */

static void _cbTaskInfo(WM_MESSAGE * pMsg) {
    WM_HWIN hItem;

	char s[500];
    hItem = pMsg->hWin;

    WINDOW_SetBkColor(hItem, 0x00FFFFFF);
    switch (pMsg->MsgId) {

    case WM_INIT_DIALOG:    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
    hWindowTask = hItem;

    MULTIEDIT_SetFont(hItem,&GUI_FontHZ12);
    MULTIEDIT_EnableBlink(hItem,2000,1);
    MULTIEDIT_SetBufferSize(hItem,500);

    //sprintf(s,"=================================================\n");    	
    sprintf(s,"任务名 任务状态 优先级 剩余栈 任务序号\n");
    MULTIEDIT_SetText(hWindowTask,s);
    MULTIEDIT_SetCursorOffset(hWindowTask,100);
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
  WM_HWIN hItem, hDialog;
  
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:

    /* Initialization of 'System Information'  */
    hItem = pMsg->hWin;
		//FRAMEWIN_AddCloseButton(hItem, FRAMEWIN_BUTTON_RIGHT, 0);    
    
    /* Initialization of 'Image' */
    //hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_INFO);
    //IMAGE_SetBitmap(hItem, &bminfo);
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIPAGE);
    
		MULTIPAGE_SetFont(hItem,&GUI_FontHZ16);
   /* Create and attache the MULTIPAGE dialog windows */
    hDialog = GUI_CreateDialogBox(_aDialogSystemInformation, 
                                  GUI_COUNTOF(_aDialogSystemInformation), 
                                  &_cbSystemInformation, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hItem, hDialog, "系统信息");
    
    hDialog = GUI_CreateDialogBox(_aDialogLogInfo, 
                                  GUI_COUNTOF(_aDialogLogInfo), 
                                  &_cbLogInfo, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hItem, hDialog, "日志信息");
    
    hDialog = GUI_CreateDialogBox(_aDialogTaskInfo, 
                                  GUI_COUNTOF(_aDialogTaskInfo), 
                                  &_cbTaskInfo, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hItem, hDialog, "任务信息");

    
    MULTIPAGE_SelectPage(hItem, 0);  
    
    break;
   
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
//WM_HWIN CreateSystemInfo(void);
//WM_HWIN CreateSystemInfo(void) {
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos)
{
  WM_HWIN hWindow;
  WM_HWIN hItem;
	uint32_t i;
	uint32_t index=0;
//	int16_t  index_item = 0;
//	int32_t  number_wheel = KeyLed_State.wheel;
	wt_SetText_Title("");
	wt_SetText_Menu(wt_info.name);
	
  hWindow = GUI_CreateDialogBox(_aDialog, GUI_COUNTOF(_aDialog), _cbDialog, hWin, xpos, ypos);
	hItem = WM_GetDialogItem(hWin, ID_MULTIPAGE);
	MULTIPAGE_SetDefaultFont(&GUI_FontHZ16);
	while(1)
  {
		//key detect
		BSP_Update_Wheel();
		
		if(BSP_GetKEY_State(KeyCancle) == 1)
		{
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
			//snapshot();
			hItem = WM_GetDialogItem(hWin, ID_MULTIPAGE);
			index++;			
			if(index==3)
			{
				index=0;
			}
			MULTIPAGE_SelectPage(hItem,index);
		}
//		if(KeyLed_State.wheel != number_wheel)//滚轮
//		{
//			index_item += KeyLed_State.wheel - number_wheel;
//			number_wheel = KeyLed_State.wheel;
//			update_item_LOG(index_item,hWindowLog);
//		}	
		if(1 == KeyLed_State.rotate)// 顺时针旋转,向下选择条目
		{
			hItem = WM_GetDialogItem(hWin, ID_LISTVIEW_0);	
			LISTVIEW_IncSel(hItem);
		}
		if(2 == KeyLed_State.rotate)// 顺时针旋转,向下选择条目
		{
			hItem = WM_GetDialogItem(hWin, ID_LISTVIEW_0);
				LISTVIEW_DecSel(hItem);
		}
		if(BSP_GetKEY_State(KeyOK) == 1)
		{
			i=0;
			while(BSP_GetKEY_State(KeyOK) == 1)
			{
				i++;
				osDelay(100);
			}
			if(i > 40)	//短按保存，小于5秒
			{
				//清除日志
				hItem = WM_GetDialogItem(hWin, ID_LISTVIEW_0);
				WT_LogFiles_Clear();
				LISTVIEW_DeleteAllRows(hItem);
			}
		}

		//delay
		osDelay(30); 
		GUI_Exec();
	}
}

//LOG显示
void show_item_LOG(WT_LogFileTypedef logInfo[],int16_t index,WM_HWIN hItem)
{
	const char * pText[2][6];
	char total[5];
	char oknum[5];
	char errnum[5];
	char errtype[10];
	for(int i = 0;i< index ;i++)
	{
		pText[0][0] = (char * )logInfo[i].wireMode;
		itoa(logInfo[i].test_total,total,10);
		pText[0][1] = total;
		itoa(logInfo[i].ok_num,oknum,10);
		pText[0][2] = oknum;
		itoa(logInfo[i].err_num,errnum,10);
		pText[0][3] = errnum;
		itoa(logInfo[i].err_type,errtype,10);
		if(logInfo[i].err_num > 0) pText[0][4] = "错位";
		else pText[0][4] = " ";
		pText[0][5] = (char * )logInfo[i].test_time;
		LISTVIEW_AddRow(hItem,pText[0]);
	}
}

//更新LOG显示
void update_item_LOG(int16_t index,WM_HWIN hItem)
{
	if(index > LISTVIEW_GetSel(hItem))
	{
		//for(int i = 0; i<index;i++)	
		LISTVIEW_IncSel(hItem);
	}
	else if(index < LISTVIEW_GetSel(hItem))
	{
		LISTVIEW_DecSel(hItem);
	}
}

//更新任务显示
uint8_t taskinfo_printf(char* pData, uint16_t length)
{
    //MULTIEDIT_AddText(hWindowTask," ");
    MULTIEDIT_SetCursorOffset(hWindowTask,100);
    MULTIEDIT_AddText(hWindowTask,pData);
	return 0;
}

