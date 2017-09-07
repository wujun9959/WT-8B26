/********************************************************************************
	Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      wt_windows_find.c
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
#include "wt_task_wirefindpoint.h"
#include "tools.h"
#include "main.h" 



/*********************************************************************
*
*       Defines
*
**********************************************************************
*/



// USER START (Optionally insert additional defines)
// USER END
#define ID_WINDOW_0    			(GUI_ID_USER + 0x00)
#define ID_IMAGE_0    			(GUI_ID_USER + 0x01)
#define ID_IMAGE_1    			(GUI_ID_USER + 0x02)
#define ID_IMAGE_2    			(GUI_ID_USER + 0x03)
#define ID_IMAGE_3    			(GUI_ID_USER + 0x04)
#define ID_TEXT_0    			(GUI_ID_USER + 0x05)
#define ID_TEXT_1    			(GUI_ID_USER + 0x06)
#define ID_TEXT_2    			(GUI_ID_USER + 0x07)
#define ID_TEXT_3    			(GUI_ID_USER + 0x08)
#define ID_TEXT_4    			(GUI_ID_USER + 0x0A)
#define ID_TEXT_5    			(GUI_ID_USER + 0x0B)
#define ID_BUTTON_OK    		(GUI_ID_USER + 0x0C)
#define ID_BUTTON_CANCEL	 	(GUI_ID_USER + 0x0D)
#define ID_MULTIEDIT	    	(GUI_ID_USER + 0x0E)
#define ID_TEXT_NODES    		(GUI_ID_USER + 0x0F)

extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ_Song_32;

extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_find;  //wujun added
extern GUI_CONST_STORAGE GUI_BITMAP bm_board_160x40;
extern GUI_CONST_STORAGE GUI_BITMAP bm_board_null_160x40;
//extern char *itoa(int num, char *str, int radix);
//extern uint32_t wheel_value;
//void showHz32( WM_HWIN hItem);
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos);
static char points[256];
//static char hz32[]  = {"\x82\x82\x70\xb9\x65\x70\xe6\x95\xb0\xef\xbc\x9a"};
//static char hz32[]  = {"\xe8\x8a\x82\xe7\x82\xb9\xe6\x95\xb0\xef\xbc\x9a"};

K_ModuleItem_Typedef  wt_find =
{	
	4,
	"找点",
	&bm_ICO_find,	
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
static const GUI_WIDGET_CREATE_INFO _aDialog[] = {
    { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 480, 222, 0, 0x0, 0 },
    { IMAGE_CreateIndirect, "Image1", ID_IMAGE_0, 10, 10, 160, 40, 0, 0, 0 },
    { IMAGE_CreateIndirect, "Image2", ID_IMAGE_1, 10, 55, 160, 40, 0, 0, 0 },
    { IMAGE_CreateIndirect, "Image3", ID_IMAGE_2, 10, 100, 160, 40, 0, 0, 0 },
    { IMAGE_CreateIndirect, "Image4", ID_IMAGE_3, 10, 145, 160, 40, 0, 0, 0 },
    { TEXT_CreateIndirect, "board1", ID_TEXT_0, 176, 20, 80, 20, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "board2", ID_TEXT_1, 176, 70, 80, 20, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "board3", ID_TEXT_2, 176, 115, 80, 20, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "board4", ID_TEXT_3, 176, 160, 80, 20, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "Port_index", ID_TEXT_4, 260, 85, 200, 60, 0, 0x64, 0 },
    { MULTIEDIT_CreateIndirect, "Port_index", ID_MULTIEDIT, 245, 65, 220, 120, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "nodeinfo", ID_TEXT_5, 270, 20, 150, 40, 0, 0, 0 },
    { TEXT_CreateIndirect, "nodes", ID_TEXT_NODES, 400, 10, 70, 40, 0, 0, 0 },
    { BUTTON_CreateIndirect, "start", ID_BUTTON_OK, 150, 200, 80, 20, 0, 0, 0 },
    { BUTTON_CreateIndirect, "exit", ID_BUTTON_CANCEL, 250, 200, 80, 20, 0, 0, 0 },
};

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {

    WM_HWIN      hItem;
    uint32_t i;

    GUI_SetPenSize(8);
    WINDOW_SetBkColor(pMsg->hWin, 0x00FFFFFF);
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
		if(SelfCheckItem.port_board_number == 0)
		{
			osMessagePut(WireSelfCheckEvent, WIRESELFCHECK_START_EVENT, 0);//开始自检
			i=100;
			while(i--)
			{
				osDelay(10);
				if(SelfCheckItem.state == 0) break;
			}
		}
		if(SelfCheckItem.port_board_number == 0)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_1);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_2);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_3);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
		}
		else if(SelfCheckItem.port_board_number == 1)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_1);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_2);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_3);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
		}
		else if(SelfCheckItem.port_board_number == 2)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_1);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_2);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_3);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
		}
		else if(SelfCheckItem.port_board_number == 3)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_1);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_2);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_3);
			IMAGE_SetBitmap(hItem, &bm_board_null_160x40);
		}
		else
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_1);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_2);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_3);
			IMAGE_SetBitmap(hItem, &bm_board_160x40);
		}

    //
    // Initialization of 'board1'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetText(hItem, "A1 - A64");
    TEXT_SetFont(hItem, GUI_FONT_16B_1);
    //
    // Initialization of 'board2'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetText(hItem, "B1 - B64");
    TEXT_SetFont(hItem, GUI_FONT_16B_1);
    //
    // Initialization of 'board3'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetText(hItem, "C1 - C64");
    TEXT_SetFont(hItem, GUI_FONT_16B_1);
    //
    // Initialization of 'board4'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetText(hItem, "D1 - D64");
    TEXT_SetFont(hItem, GUI_FONT_16B_1);
    //
    // Initialization of 'Port_index'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT);
    MULTIEDIT_SetText(hItem, " ");
    MULTIEDIT_SetFont(hItem, GUI_FONT_24_1);
    MULTIEDIT_SetTextAlign(hItem, GUI_TA_HCENTER);
    TEXT_SetTextColor(hItem,GUI_RED);
    MULTIEDIT_SetAutoScrollV(hItem,1);
    MULTIEDIT_SetWrapWord(hItem);
    MULTIEDIT_SetFocussable(hItem,1);
    WM_HideWindow(hItem);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetText(hItem, " ");
    TEXT_SetFont(hItem, &GUI_FontHZ_Song_48);
    TEXT_SetTextColor(hItem,GUI_RED);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Image'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetText(hItem, "节点数:");
    TEXT_SetFont(hItem, &GUI_FontHZ24);
    TEXT_SetTextColor(hItem,GUI_BLUE);
    //TEXT_SetText(hItem, hz32);
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_NODES);
    TEXT_SetText(hItem, "");
    TEXT_SetFont(hItem, &GUI_FontHZ_Song_48);
    TEXT_SetTextColor(hItem,GUI_BLUE);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_OK);
    BUTTON_SetFont(hItem,&GUI_FontHZ12);
    BUTTON_SetText(hItem, "开始");
    BUTTON_SetSkinClassic(hItem);
    BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_GRAY);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_CANCEL);
    BUTTON_SetFont(hItem,&GUI_FontHZ12);
    BUTTON_SetText(hItem, "关闭");
    BUTTON_SetSkinClassic(hItem);
    BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_RED);
    break;
	case WM_PAINT://绘制边框
		GUI_SetColor(GUI_DARKGRAY);
		GUI_SetPenSize(8);
		GUI_DrawRoundedFrame(2, 2, 240, 195, 0, 4);
		GUI_DrawRoundedFrame(2, 2, 478, 195, 0, 4);
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
	char tmp[6];
	char Items_count[20];
	char p1[6];
	char p2[6];

	wt_SetText_Title("");
	wt_SetText_Menu(wt_find.name);
	
		
  hWindow = GUI_CreateDialogBox(_aDialog, GUI_COUNTOF(_aDialog), _cbDialog, hWin, xpos, ypos);
	
	FindPoint.command = 1;
	if(FindPoint.task_status == 0)	//0-waiting, 1-finding
	osMessagePut(WireFindPointEvent, WIREFINDPOINT_START_EVENT, 0);//开始找点
	else
	FindPoint.command = 2;	//0-no operate, 1-start, 2-cancel

	memset(p1,0,6);
	memset(p2,0,6);
	while(1)
  {
		//key detect
		if(BSP_GetKEY_State(KeyCancle) == 1)
		{	
			while(BSP_GetKEY_State(KeyCancle) == 1)
			{
				osDelay(10);
			}
			GUI_EndDialog(hWindow,0);
			KeyLed_State.wheel=0;
			//wheel_value=0;
			Number_Windos = 0;
			FindPoint.command = 2;
			return;
		}
		if(BSP_GetKEY_State(KeyOK) == 1)
		{
				while(BSP_GetKEY_State(KeyOK) == 1)
				{
					osDelay(10);
				}

		}
		if(FindPoint.Items_count > 0 && FindPoint.task_status==1 )
		//if(FindPoint.Items_count > 0 )
		{		
			memset(points,0,256);
			for(i=0;i<FindPoint.Items_count;i++)
			{
				memset(tmp,0,6);
				if(FindPoint.Items_count == 1) 
				{
					num_converter(FindPoint.Items_Point[i]+1,p1);
					sprintf(tmp,"%s",p1);
				}
				else
				{
					if(i== FindPoint.Items_count-1 ) 
					{
						num_converter(FindPoint.Items_Point[i]+1,p1);
						sprintf(tmp,"%s",p1);
					}
					else 
					{
						num_converter(FindPoint.Items_Point[i]+1,p2);
						sprintf(tmp,"%s-",p2);
					}
				}
				strcat(points,tmp);
			}
			if(FindPoint.Items_count < 3)
			{
				hItem = WM_GetDialogItem(hWin, ID_TEXT_4);
				TEXT_SetText(hItem, points);
				hItem = WM_GetDialogItem(hWin, ID_MULTIEDIT);
				WM_HideWindow(hItem);
			}
			else
			{
				hItem = WM_GetDialogItem(hWin, ID_MULTIEDIT);
				MULTIEDIT_SetText(hItem, points);
				MULTIEDIT_AddKey(hItem,GUI_KEY_END);
				WM_ShowWindow(hItem);
			}

			
			sprintf(Items_count,"%d",FindPoint.Items_count);
			hItem = WM_GetDialogItem(hWin, ID_TEXT_NODES);
			TEXT_SetText(hItem, Items_count);
			osDelay(100); 
		}
		//delay
		osDelay(30); 
		GUI_Exec();
	}
}

