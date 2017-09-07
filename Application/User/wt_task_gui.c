/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_task_gui.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-7-2
  * @brief   This file provides the startup functions
  ******************************************************************************
  */

#define WT_WINDOWS_GUI_GLOBALS



/* Includes ------------------------------------------------------------------*/
//#include "k_mem.h" 
//#include "wt_bsp.h" 
//#include "k_log.h"    
//#include "k_calibration.h"    
//#include "wt_bsp_storage.h"

#include "main.h" 
#include "k_module.h"
#include "wt_task_gui.h"
#include "wt_windows_menu.h"
#include "k_rtc.h"
#include "wt_bsp_storage.h"
#include "cpu_utils.h"
#include "wt_task_wireselfcheck.h"
#include "wt_bsp_file.h"
#include "tools.h"


/* External variables --------------------------------------------------------*/
extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_study;
extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_test;
extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_edit;
extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_setting;
extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_Info;
extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_book;
extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_smail;
extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_wheel;

extern K_ModuleItem_Typedef  wt_test;
extern K_ModuleItem_Typedef  wt_info;
extern K_ModuleItem_Typedef wt_setting;
extern K_ModuleItem_Typedef wt_study;
extern K_ModuleItem_Typedef wt_self;
extern K_ModuleItem_Typedef wt_edit;
extern K_ModuleItem_Typedef wt_find;
//extern K_ModuleItem_Typedef wt_debug;
extern K_ModuleItem_Typedef wt_print;

/* External variables --------------------------------------------------------*/
extern GUI_CONST_STORAGE GUI_BITMAP bm_BackGround480x272A;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmLZYLogo40x20;
extern GUI_CONST_STORAGE GUI_BITMAP bmusbdisk;
extern GUI_CONST_STORAGE GUI_BITMAP bmmicrosd;
extern GUI_CONST_STORAGE U8 _acImage_LZYLogo40x20[2454];
extern GUI_CONST_STORAGE GUI_BITMAP bmwifi;

/* External functions --------------------------------------------------------*/
extern void wt_StartUp(void);
extern void Menu_NextICO(void);
extern void Menu_OpenLinkICO(void);

uint8_t gwifi_stat = 0;//0:not connect 1:connect
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define ID_WINDOW_Title		(GUI_ID_USER + 0x01)
#define ID_TITLE_TEXT_0   (GUI_ID_USER + 0x02)
#define ID_TITLE_TEXT_1   (GUI_ID_USER + 0x03)
#define ID_TITLE_IMAGE_0  (GUI_ID_USER + 0x04)

#define ID_TIMER_TIME  		(GUI_ID_USER + 0x10)
#define ID_ICONVIEW_MENU  (GUI_ID_USER + 0x11)


/* Private macros ------------------------------------------------------------*/
/*********************************************************************
*
*       _aDialogCreate - Title
*/
static const GUI_WIDGET_CREATE_INFO _aTitleDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", 	ID_WINDOW_Title, 0, 0, 480, 25, 0, 0x0, 0 },
	{ IMAGE_CreateIndirect, "Image", 		ID_TITLE_IMAGE_0, 2, 2, 40, 20, 0, IMAGE_CF_AUTOSIZE, 0 },
  { TEXT_CreateIndirect, "Text", 			ID_TITLE_TEXT_0, 60, 0, 330, 25, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", 			ID_TITLE_TEXT_1, 380, 0, 100, 25, 0, 0x0, 0 },
};



/* Private variables ---------------------------------------------------------*/
static WM_HWIN hWin_Title = 0;
static WM_HWIN hWin_Statue = 0;
//static SystemSettingsTypeDef    settings;
static uint8_t StatusText[50];
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


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
													 

/**
  * @brief  set the GUI profile
  * @param  None.
  * @retval None.
  */
static void wt_SetGuiProfile(void) 
{
 
  settings.d32 = k_BkupRestoreParameter(CALIBRATION_GENERAL_SETTINGS_BKP);

  if(settings.b.disable_flex_skin == 0)
  {
    FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);  
    PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
    SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
    BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    
    FRAMEWIN_SetDefaultTextColor(0, GUI_DARKGRAY);
    FRAMEWIN_SetDefaultTextColor(1, GUI_DARKGRAY);      
  }
  else
  {
    FRAMEWIN_SetDefaultTextColor(0, GUI_WHITE);
    FRAMEWIN_SetDefaultTextColor(1, GUI_WHITE);   
  }

  FRAMEWIN_SetDefaultFont(GUI_FONT_10_ASCII);

  FRAMEWIN_SetDefaultClientColor(GUI_LIGHTGRAY | 0x20F50000);  
  FRAMEWIN_SetDefaultTitleHeight(15);
  
  TREEVIEW_SetDefaultBkColor(TREEVIEW_CI_SEL, GUI_LIGHTGRAY | 0x20E50000);
  TREEVIEW_SetDefaultBkColor(TREEVIEW_CI_UNSEL, GUI_LIGHTGRAY | 0x20E50000);
  TREEVIEW_SetDefaultTextColor(TREEVIEW_CI_SEL, GUI_BLUE);
  
  WINDOW_SetDefaultBkColor(GUI_LIGHTGRAY | 0x20E50000);
  MULTIPAGE_SetDefaultBkColor(GUI_LIGHTGRAY | 0x20E50000, 0);
  MULTIPAGE_SetDefaultBkColor(GUI_LIGHTGRAY | 0x20E50000, 1);    
  MULTIPAGE_SetDefaultFont(GUI_FONT_10_ASCII); 
  CHECKBOX_SetDefaultBkColor(GUI_LIGHTGRAY | 0x20E50000);
  
  CALENDAR_SetDefaultSize(CALENDAR_SI_HEADER, 20 );
  CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_X, 25 );
  CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_Y, 21 ); 
  
  MULTIPAGE_SetDefaultBkColor (GUI_WHITE, 1);
    
  SPINBOX_SetDefaultButtonSize(15);
  LISTVIEW_SetDefaultGridColor(GUI_WHITE);
  SCROLLBAR_SetDefaultWidth(16);

  HEADER_SetDefaultBkColor(0x00C5903E);
  HEADER_SetDefaultTextColor(GUI_WHITE);
  SCROLLBAR_SetDefaultColor(GUI_LIGHTGRAY | 0x20F50000, SCROLLBAR_CI_THUMB);  
  SCROLLBAR_SetDefaultColor(GUI_LIGHTGRAY | 0x20F50000, SCROLLBAR_CI_SHAFT);  
  SCROLLBAR_SetDefaultColor(GUI_LIGHTGRAY | 0x20F50000, SCROLLBAR_CI_ARROW);    
  CHOOSEFILE_SetDelim('/');
}

/**
  * @brief  Callback routine of desktop window title.
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbTitle(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
//	const void * pData;
//  U32          FileSize;

  switch (pMsg->MsgId) 
  {
		case WM_INIT_DIALOG:
			//
			// Initialization of 'Window'
			//
			hItem = pMsg->hWin;
			//WINDOW_SetBkColor(hItem, 0x00303030);
			WINDOW_SetBkColor(hItem, GUI_DARKGRAY);
			//
			// Initialization of 'Image'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TITLE_IMAGE_0);
//			FileSize = sizeof(_acImage_LZYLogo40x20);
//			pData = (const void *)_acImage_LZYLogo40x20;
//			IMAGE_SetBMP(hItem, pData, FileSize);
			IMAGE_SetBitmap(hItem, &bmbmLZYLogo40x20);
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TITLE_TEXT_0);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, &GUI_FontHZ16);
			TEXT_SetTextColor(hItem, GUI_WHITE);
//			strcpy(temp, DEF_WT_NAME);
//			strcat(temp, " ");
//			strcat(temp, DEF_WT_MODEL);
//			TEXT_SetText(hItem, temp);
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TITLE_TEXT_1);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			//GUI_UC_SetEncodeUTF8();
			TEXT_SetFont(hItem, &GUI_FontHZ16);
			//TEXT_SetBkColor(hItem, GUI_DARKBLUE);
			TEXT_SetTextColor(hItem, GUI_WHITE);
			//TEXT_SetText(hItem, "主菜单");
			break;
			
		default:
			WM_DefaultProc(pMsg);
			break;
  }
}

/**
  * @brief  Callback routine of desktop window status.
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbStatus(WM_MESSAGE * pMsg) {
  int xSize, ySize;
  static uint8_t TempStr[50];
  static WM_HTIMER hTimerTime;
	//uint8_t res = 0;
  //static WM_HTIMER hSpriteTime;  

  RTC_TimeTypeDef   RTC_Time;
  RTC_DateTypeDef   RTC_DateStructure;
  uint8_t sec, min, hour, day, month;
  uint16_t year;
  WM_HWIN hWin;
	uint16_t PosDisplay;

  hWin = pMsg->hWin;
  switch (pMsg->MsgId) 
  {
  case WM_CREATE:
    hTimerTime = WM_CreateTimer(hWin, ID_TIMER_TIME, 1000, 0);
    break;
    
  case WM_DELETE:
    WM_DeleteTimer(hTimerTime);
    break;
    
  case WM_TIMER:
    if( WM_GetTimerId(pMsg->Data.v) == ID_TIMER_TIME)
    {
      WM_InvalidateWindow(hWin);
      WM_RestartTimer(pMsg->Data.v, 1000);
    }
    break;
    
  case WM_PAINT:
    xSize = WM_GetWindowSizeX(hWin);
    ySize = WM_GetWindowSizeY(hWin);
		PosDisplay = xSize;
    
		/* Draw background */
		//GUI_SetColor(0x808080);
    //GUI_SetColor(0x742E1B);
		GUI_SetColor(0x000000);
		GUI_FillRect(0, 0, xSize - 1, ySize - 1);
    
		// status
		GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringAt( (char *)StatusText, 4, 4);
	
    /* Draw time & Date */
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(GUI_FONT_13B_ASCII);
    //time
    k_GetTime(&RTC_Time);
    sec    =  RTC_Time.Seconds;
    min    =  RTC_Time.Minutes;
    hour   =  RTC_Time.Hours;
    sprintf((char *)TempStr, "%02d:%02d:%02d", hour , min, sec);
    //sprintf((char *)TempStr, "%02d:%02d", hour , min);
		PosDisplay-=60;
		GUI_DispStringAt((char *)TempStr, PosDisplay, 0);
		//date
    k_GetDate(&RTC_DateStructure);
    year =  RTC_DateStructure.Year + RTCTIME_YEAR;
    month =  RTC_DateStructure.Month;
    day =  RTC_DateStructure.Date;
    if((day > 0) && (day <= 31) && (month > 0)&& (month <= 12) && (year >= 1900))
    {
      sprintf((char *)TempStr, "%04d/%s/%02d", year, strMonth[month-1], day);
    }
    else
    {
      sprintf((char *)TempStr, "2017/01/01");
    }
		PosDisplay-=10;
    GUI_DispStringAt((char *)TempStr, PosDisplay, 11);
    
    /* USB */
    if(k_StorageGetStatus(USB_DISK_UNIT))
    {
       PosDisplay-=35;
       GUI_DrawBitmap(&bmusbdisk, PosDisplay, 3);
    }
		
		/* MSD */
    if(k_StorageGetStatus(MSD_DISK_UNIT))
    {
      PosDisplay-=35; 
			GUI_DrawBitmap(&bmmicrosd, PosDisplay, 3);
    }   
		/* WIFI */
    if(gwifi_stat == 1)
    {
      PosDisplay-=35; 
			GUI_DrawBitmap(&bmwifi, PosDisplay, 3);
    }	
		/* CPU */
    sprintf((char *)TempStr, "%d %%", osGetCPUUsage());
    if(osGetCPUUsage() > 95 )
    {
      /* waiting for user input when using dialog box*/
      sprintf((char *)TempStr, "95 %%");
    }   
    PosDisplay-=35;
    GUI_DispStringAt( (char *)TempStr, PosDisplay, 6);
		
//		if(WT_Config.Print == 1 && PrintFile->print_status == 4)//本地打印Yes  //print_status 0-stop 1-wait, 2-print ok, 3-print run, 4-print error
//		{
////			WT_PrintFolder_Init();
////			res=WT_PrintFiles_Init((char *)PrintFolder->FilesName[WT_Config.Print_ID]);//0-not init, 1-inited, 2-no files, 3-hardware error, 4-no folder
////			if(res != 1) wt_SetText_Status("打印文件错误");
//			wt_SetText_Status("打印文件错误");
//		}	
    break;
    
  default:
    WM_DefaultProc(pMsg);
  }
}

/**
  * @brief  wt_SetText_Title
  * @param  
  * @retval None
  */
void wt_SetText_Title(const char * pTitle) 
{
	TEXT_Handle hText;

  if (WM_IsVisible(hWin_Title)) {
		hText = WM_GetDialogItem(hWin_Title, ID_TITLE_TEXT_0);
    TEXT_SetText(hText, pTitle);
  }
}

/**
  * @brief  wt_SetText_Menu
  * @param  
  * @retval None
  */
void wt_SetText_Menu(const char * pMenu) 
{
	TEXT_Handle hText;

  if (WM_IsVisible(hWin_Title)) {
    hText = WM_GetDialogItem(hWin_Title, ID_TITLE_TEXT_1);
    TEXT_SetText(hText, pMenu);
  }
}

/**
  * @brief  wt_SetText_Status
  * @param  
  * @retval None
  */
void wt_SetText_Status(const char * pStatus) 
{
	uint32_t len;
	uint32_t i;
	
	len = strlen(pStatus);
	if(len > 49) len = 49;
	for(i=0;i<len;i++) StatusText[i]=pStatus[i];
	StatusText[len]=0;
	//刷新显示
	WM_InvalidateWindow(hWin_Statue);
}

/**
  * @brief  wt_InitBackGround
  * @param  
  * @retval None
  */
void wt_InitBackGround(void)
{
//	uint32_t i = 0;
  
	sprintf((char *)StatusText, "就绪...");
	
	GUI_SelectLayer(0);
	GUI_SetLayerVisEx (0, 0);
    GUI_DrawBitmap(&bm_BackGround480x272A, 0,0);  

    GUI_SetLayerVisEx (0, 1);//设置层0可见
    GUI_SelectLayer(1);
    GUI_SetBkColor(GUI_TRANSPARENT);//设置层1为透明
    GUI_Clear();
	
	// creat title
	hWin_Title = GUI_CreateDialogBox(_aTitleDialogCreate, GUI_COUNTOF(_aTitleDialogCreate), _cbTitle, WM_HBKWIN, 0, 0);

	//creat status
	hWin_Statue = WM_CreateWindowAsChild(0,LCD_GetYSize()-25,LCD_GetXSize(), 25, WM_HBKWIN, WM_CF_SHOW | WM_CF_HASTRANS , _cbStatus, 0);
}


/**
  * @brief  GUI task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void GUIThread(void const * argument)
{
	static uint32_t WinNumberICO;

	TesterStatus.mode = 0;
	TesterStatus.error = 0;
	
	// wait for others task init
  wt_StartUp();	
	
	// self check
	osMessagePut(WireSelfCheckEvent, WIRESELFCHECK_START_EVENT, 0);//开始自检
	
	/* Add Modules*/
  k_ModuleInit();
	k_ModuleAdd(&wt_test);
	k_ModuleAdd(&wt_study);
	k_ModuleAdd(&wt_find);
	k_ModuleAdd(&wt_edit);
	k_ModuleAdd(&wt_self);
	k_ModuleAdd(&wt_setting);
	k_ModuleAdd(&wt_info);
	k_ModuleAdd(&wt_print);

	/* Set General Graphical proprieties */
  wt_SetGuiProfile();
    
//  if(k_CalibrationIsDone() == 0)
//  {
//    GUI_SelectLayer(1);
//    k_CalibrationInit();
//    GUI_SelectLayer(0);
//  }
	settings.d32 = k_BkupRestoreParameter(CALIBRATION_GENERAL_SETTINGS_BKP);
  
	Number_Windos = 0;	//当前显示窗口编号
	WinNumberICO = 1;
	
	// Init Back Ground & Patch the bug of Listview Grid
	wt_InitBackGround();
	LISTVIEW_SetDefaultGridColor(GUI_GRAY);
  
  /* Gui background Task */
  while(1)
  {
		// show the windows
    switch(Number_Windos)
		{
			case 0:
				TesterStatus.mode = 0;
				WT_Windows_Menu(&WinNumberICO);
				break;
			
			case 1:
				// update Tester_Status
//				switch (WinNumberICO)
//				{
//					//0：待机状态；1：正常运行测试程序；2：正在运行自学习程序；
//					//3：正在运行找点程序；4：正在运行自检程序；5：正在运行调试程序；
//					case 0:
//						TesterStatus.mode = 1;
//						break;
//					case 1:
//						TesterStatus.mode = 2;
//						break;
//					case 2:
//						TesterStatus.mode = 3;
//						break;
//					case 4:
//						TesterStatus.mode = 4;
//						break;
//					case 7:
//						TesterStatus.mode = 5;
//						break;
//					default:
//						TesterStatus.mode = 0;
//						break;
//				}
				module_prop[WinNumberICO].module->startup(WM_HBKWIN, 0, 25);
				
				break;
			
			default:
				Number_Windos = 0;	//显示menu
				break;	
		}
		// system delay
		GUI_Exec();
		osDelay(30); 
	}
}


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
