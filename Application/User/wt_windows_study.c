/********************************************************************************
	Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      wt_windows_study.c
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
#include "tools.h"
#include "main.h"


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0     	(GUI_ID_USER + 0x00)
#define ID_LISTVIEW_0       (GUI_ID_USER + 0x01)
//#define ID_BUTTON_0       (GUI_ID_USER + 0x03)
#define ID_BUTTON_OK     	(GUI_ID_USER + 0x03)
#define ID_BUTTON_CANCEL    (GUI_ID_USER + 0x04)
#define ID_PROGBAR0			(GUI_ID_USER + 0x05)



// USER START (Optionally insert additional defines)
// USER END

extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_study; 
extern WM_HWIN Create_StudySaveDlgWindow( WM_HWIN hWin_para);
extern WM_HWIN Create_StudyDlgWindow( WM_HWIN hWin_para);
extern WM_HWIN CreateWarningBox(WM_HWIN hWin_para);


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
#define DEF_LENGTH_ITEM_STUDY	256
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos);
void Save_studyfile( WM_HWIN hWindow);

static WM_HWIN hWindow;
static uint8_t win_stat=1;//0--close window  1--not close window
//extern uint32_t wheel_value;
static char studyinfo[50];
static uint16_t items_study_index[DEF_LENGTH_ITEM_STUDY];
static uint32_t items_study_show;
static uint16_t listview_FirstItem = 0;
static uint8_t study_stat=0;//0-not sutdy  1- study ok
static uint8_t study_stat_last=0;//0-not sutdy  1- study ok
static uint8_t  IsNewState =0;

void update_table_study(void);
void update_item_study(int16_t *index);

//void get_items_studyindex(uint16_t (* items_studyindex)[DEF_LENGTH_ITEM_STUDY]);
void get_items_studyindex(uint16_t items_studyindex[DEF_LENGTH_ITEM_STUDY]);
uint32_t get_items_studyshow(void);

extern void  Wheel_Encoder_clear(void);

K_ModuleItem_Typedef  wt_study =
{	
	0,
	"自学习",
	&bm_ICO_study,	
	//&CreateSystemInfo,
	Startup,
	0,
};

extern char *itoa(int num, char *str, int radix);

// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 480, 222, 0, 0x0, 0 },
	{ LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 0, 0, 480, 204, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "保存", ID_BUTTON_OK, 150, 202, 80, 20, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "退出", ID_BUTTON_CANCEL, 250, 202, 80, 20, 0, 0x0, 0 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
	HEADER_Handle hHeader;
	char portnum[3];
  // USER START (Optionally insert additional variables)
  // USER END
//	if(SelfCheckItem.port_board_number<=0)
//	{
//		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
//		TEXT_SetBkColor(hItem, GUI_LIGHTGRAY);
//	}
//	else 
//	{
//		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
//		TEXT_SetBkColor(hItem, GUI_GREEN);
//	}

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
        Wheel_Encoder_Clear();
        hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
		hHeader = LISTVIEW_GetHeader(hItem);
		HEADER_SetFont(hHeader,&GUI_FontHZ12);
		HEADER_SetHeight(hHeader,20);
        LISTVIEW_AddColumn(hItem, 60, "序号", GUI_TA_HCENTER | GUI_TA_VCENTER);
        LISTVIEW_AddColumn(hItem, 80, "测试类型", GUI_TA_HCENTER | GUI_TA_VCENTER);
        LISTVIEW_AddColumn(hItem, 80, "节点", GUI_TA_HCENTER | GUI_TA_VCENTER);
        LISTVIEW_AddColumn(hItem, 80, "节点", GUI_TA_HCENTER | GUI_TA_VCENTER);
        LISTVIEW_AddColumn(hItem, 180, "测试参数", GUI_TA_HCENTER | GUI_TA_VCENTER);
        //LISTVIEW_SetAutoScrollV(hItem, 1);
		LISTVIEW_SetGridVis(hItem,1);
		LISTVIEW_SetDefaultGridColor(GUI_GRAY);
        LISTVIEW_SetRowHeight(hItem, 20);
		LISTVIEW_EnableSort(hItem);
		LISTVIEW_SetFont(hItem, &GUI_FontHZ16);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_OK);
		BUTTON_SetFont(hItem,&GUI_FontHZ12);
		BUTTON_SetSkinClassic(hItem);
		BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_GREEN);
		BUTTON_SetFocussable(hItem,0);//不接收焦点
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_CANCEL);
		BUTTON_SetFont(hItem,&GUI_FontHZ12);
		BUTTON_SetSkinClassic(hItem);
		BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_RED);
		BUTTON_SetFocussable(hItem,0);//不接收焦点
		
//		if(SelfCheckItem.port_board_number<=0)
//		{
//			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
//			TEXT_SetBkColor(hItem, GUI_LIGHTGRAY);
//		}
//		else 
//		{
//			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
//			TEXT_SetBkColor(hItem, GUI_GREEN);
//		}

    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case MY_MESSAGE_BUTTONOK:
		wt_SetText_Status("自学习完成");
		strcpy(studyinfo,(char *)"线束：自学习  点位：");
		strcat(studyinfo,itoa(StudyFile->number_point,portnum,10));
		strcat(studyinfo,"，");
		strcat(studyinfo,(char *)"回路：");
		strcat(studyinfo,itoa(StudyFile->number_line,portnum,10));
		wt_SetText_Title(studyinfo);
		wt_SetText_Menu(wt_study.name);
		KeyLed_State.wheel=0;
		study_stat=1;
//		update_table_study();
		break;
	case MY_MESSAGE_BUTTONCANCEL:
		//Listview_study();
		study_stat=0;
//		update_item_study();
		KeyLed_State.wheel=0;
		break;
	case MY_MESSAGE_OK:
		GUI_EndDialog(pMsg->hWin,0);
		win_stat=0;//0--close window  1--not close window
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
*       Createlearning
*/
//WM_HWIN CreateSystemInfo(void);
//WM_HWIN CreateSystemInfo(void) {
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos)
{
 // WM_HWIN hWindow;
  WM_HWIN hItem;
	WM_HWIN hDialog;
	WM_HWIN hWarningbox;
	WM_MESSAGE Msg;
	WM_HWIN hParent;
//	uint32_t i;
//	int32_t wheel_stat=0;
	KeyLed_State.wheel=0;
	uint8_t buf8=0;
	listview_FirstItem = 0;
	
	int32_t  number_wheel = KeyLed_State.wheel;
	int16_t  index_item = 0;
	
	wt_SetText_Title("");
	wt_SetText_Menu(wt_study.name);
	wt_SetText_Status("准备自学习");
	
    hWindow = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, hWin, xpos, ypos);
	
	//创建自学习选择对话框
	loop: hDialog=Create_StudyDlgWindow(hWindow);
	
	while (WM_IsWindow(hDialog))
	{
        
        if(BSP_GetKEY_State(KeyOK) == 1 )//wujun added 
		{

			Msg.MsgId = MY_MESSAGE_OK;
			Msg.hWinSrc = hWindow;
			hItem=WM_GetFocussedWindow();
			hParent=hDialog;
			//WM_SendMessage(hParent,&Msg);
			while(BSP_GetKEY_State(KeyOK) == 1)
			{
				osDelay(100);
			}
			WM_SendMessage(hParent,&Msg);
			
		}
		if(BSP_GetKEY_State(KeyCancle) == 1 )//wujun added 
		{
			Msg.MsgId = MY_MESSAGE_CANCEL;
			Msg.hWinSrc = hWindow;
			hItem=WM_GetFocussedWindow();
			//hParent=WM_GetParent(hItem);
			hParent=hDialog;
			//WM_SendMessage(hParent,&Msg);
			while(BSP_GetKEY_State(KeyCancle) == 1)
			{
				osDelay(100);
			}

			WM_SendMessage(hParent,&Msg);

		}
//		if(KeyLed_State.wheel!=number_wheel)//处理滚轮事件
//		{
//			Msg.MsgId = MY_MESSAGE_WHEEL;
//			hItem=WM_GetFocussedWindow();
//			hParent=WM_GetParent(hItem);
//			WM_SendMessage(hParent,&Msg);
//			number_wheel=KeyLed_State.wheel;
//			GUI_Delay(100);
//		}
  
		GUI_Delay(100);
   }
	
	hItem = WM_GetDialogItem(hWindow, ID_LISTVIEW_0);
	WM_SetFocus(hItem);
	 
	while(1)
    {
		BSP_Update_Wheel();
        //update status
		if(study_stat != study_stat_last)
		{
			IsNewState = 1;
			study_stat_last = study_stat;
		}
		//key detect
		//向下选择条目
		if(BSP_GetKEY_State(KeyDown) == 1)
		{
			hItem = WM_GetDialogItem(hWindow, ID_LISTVIEW_0);
			buf8 = 5;
			while(BSP_GetKEY_State(KeyDown) == 1)
			{
				osDelay(20);
				buf8--;
				if(buf8 == 0) break;
			}
			index_item++;
		}
		//向上选择条目
		if(BSP_GetKEY_State(KeyUp) == 1)
		{
			buf8 = 5;
			while(BSP_GetKEY_State(KeyUp) == 1)
			{
				osDelay(20);
				buf8--;
				if(buf8 == 0) break;
			}
			index_item--;
		}
//		if(KeyLed_State.wheel!=number_wheel)//处理滚轮事件
//		{
//			index_item += KeyLed_State.wheel - number_wheel;
//			number_wheel = KeyLed_State.wheel;
//		}
        if(1 == KeyLed_State.rotate || 2 == KeyLed_State.rotate )
        {
            index_item += (Wheel_Encoder_Read() - number_wheel);
            osDelay(100);
            number_wheel = Wheel_Encoder_Read();      
        }			
		//保存学习文件或重新自学习
		if(BSP_GetKEY_State(KeyOK) == 1 )
		{
			while(BSP_GetKEY_State(KeyOK) == 1)
			{
				osDelay(10);
			}
			if(StudyFile->item_total>0)
			{
				KeyLed_State.wheel=0;
				Save_studyfile(hWindow);//打开文件保存路径对话框
				win_stat = 0;
				goto closewindow;
			}
			else
			{
				goto loop;
			}
		}
		//关闭测试程序
		if(BSP_GetKEY_State(KeyCancle) == 1  )
		{
			//弹出告警对话框
			while(BSP_GetKEY_State(KeyCancle) == 1)
			{
				osDelay(10);
			}
			hWarningbox = CreateWarningBox(hWindow);			
			//WM_BringToTop(hWarningbox);
			//WM_SetFocus(hWarningbox);
			GUI_Exec();
			win_stat=1;
			while(WM_IsWindow(hWarningbox))
			{
				if(BSP_GetKEY_State(KeyOK) == 1 )//确定关闭
				{
					while(BSP_GetKEY_State(KeyOK) == 1)
					{
						osDelay(10);
					}
					
					Msg.MsgId = MY_MESSAGE_OK;
					Msg.hWinSrc = hWindow;
					hItem=WM_GetFocussedWindow();
					//hParent=WM_GetParent(hItem);
					hParent=hWarningbox;
					WM_SendMessage(hParent,&Msg);
					closewindow:
					KeyLed_State.wheel=0;
					//wheel_value=0;
					StudyFile->item_total=0;
					study_stat=0;
					study_stat_last=0;				
					if(win_stat != 1  )////0--close window  1--not close window
					{						
						GUI_EndDialog(hWindow,0);
						Number_Windos = 0;
						return;
					}
					
				}
				if(BSP_GetKEY_State(KeyCancle) == 1 )//取消关闭
				{
					while(BSP_GetKEY_State(KeyCancle) == 1)
					{
						osDelay(10);
					}
					GUI_EndDialog(hWarningbox,0);
					GUI_Exec();
				}
				osDelay(10);
			}		
			
			osDelay(30);
		}
		
		if(StudyFile->item_total<=0)
		{			
			hItem = WM_GetDialogItem(hWindow, ID_BUTTON_OK);
			BUTTON_SetText(hItem,(char *)"自学习");
		}
		else
		{
			hItem = WM_GetDialogItem(hWindow, ID_BUTTON_OK);
			BUTTON_SetText(hItem,(char *)"保存");
		}
		
		if(study_stat == 1)
		{
			study_stat = 0;
			update_table_study();
		} 
		
		update_item_study(&index_item);
		//delay
		osDelay(30); 
		GUI_Exec();
	}
}

//保存学习文件，打开保存路径对话框
void Save_studyfile( WM_HWIN hWindow)
{
    WM_HWIN hItem;
	WM_HWIN hDialog;
	WM_MESSAGE Msg;
	WM_HWIN hParent;
	uint32_t i=0;
//	uint32_t wheel_stat=0;
//    int32_t  number_wheel = KeyLed_State.wheel;
//	int16_t  index_item = 0;
	
	wt_SetText_Status("保存自学习文件");

	hDialog=Create_StudySaveDlgWindow(hWindow);
	while(WM_IsWindow(hDialog))
	{
		BSP_Update_Wheel();
        if(BSP_GetKEY_State(KeyOK) == 1)//wujun added 
		{
			i=0;
			Msg.MsgId = MY_MESSAGE_OK;
			hItem=WM_GetFocussedWindow();
			//hParent=WM_GetParent(hItem);
			hParent=hDialog;
			while(BSP_GetKEY_State(KeyOK) == 1)
			{
				i++;
				osDelay(100);
			}
			if(i < 20)
			{
				WM_SendMessage(hParent,&Msg);	
				osDelay(100);					
			}
			hItem = WM_GetDialogItem(hWindow, ID_LISTVIEW_0);
			WM_SetFocus(hItem);
		}
		//取消并关闭窗口
		if(BSP_GetKEY_State(KeyCancle) == 1 )
		{
			i=0;
			while(BSP_GetKEY_State(KeyCancle) == 1)
			{
				i++;
				osDelay(100);
			}
			if(i < 20)
			{
				GUI_EndDialog(hDialog,0);
				GUI_Exec();
			}
			//hItem = WM_GetDialogItem(hWindow, ID_LISTVIEW_0);
			//WM_SetFocus(hItem);
		}
		if(BSP_GetKEY_State(KeyUp) == 1 )//wujun added 
		{
			i=0;
			Msg.MsgId = MY_MESSAGE_UP;
			hItem=WM_GetFocussedWindow();
			hParent=WM_GetParent(hItem);
			//WM_SendMessage(hParent,&Msg);
			
			while(BSP_GetKEY_State(KeyUp) == 1)
			{
				i++;
				osDelay(100);
			}
			if(i < 20)
			{
				WM_SendMessage(hParent,&Msg);
				GUI_Delay(300);
			}
		}
		if(BSP_GetKEY_State(KeyDown) == 1 )//wujun added 
		{
			i=0;
			Msg.MsgId = MY_MESSAGE_DOWN;
			hItem=WM_GetFocussedWindow();
			hParent=WM_GetParent(hItem);
			//WM_SendMessage(hParent,&Msg);
			
			while(BSP_GetKEY_State(KeyDown) == 1)
			{
				i++;
				osDelay(300);
			}
			if(i < 20)
			{
				WM_SendMessage(hParent,&Msg);
				GUI_Delay(100);
			}
		}
//		if(KeyLed_State.wheel!=wheel_stat)//处理滚轮事件
//		{
//			Msg.MsgId = MY_MESSAGE_WHEEL;
//			hItem=WM_GetFocussedWindow();
//			hParent=WM_GetParent(hItem);
//			WM_SendMessage(hParent,&Msg);
//			wheel_stat=KeyLed_State.wheel;
//		}
        if(1 == KeyLed_State.rotate || 2 == KeyLed_State.rotate )
        {
            Msg.MsgId = MY_MESSAGE_WHEEL;
            hItem=WM_GetFocussedWindow();
            hParent=WM_GetParent(hItem);
            WM_SendMessage(hParent,&Msg);   
        }	
		//wheel按键删除字符
		if(BSP_GetKEY_State(KeyWheel) == 1 )
		{
			i=0;
			Msg.MsgId = MY_MESSAGE_BUTTONDELETE;
			Msg.hWinSrc = hWindow;
			hItem=WM_GetFocussedWindow();
			hParent=WM_GetParent(hItem);
			//WM_SendMessage(hParent,&Msg);
			while(BSP_GetKEY_State(KeyWheel) == 1)
			{
				i++;
				osDelay(100);
			}
			if(i < 12)
			{
				WM_SendMessage(hParent,&Msg);
				//osDelay(100);
			}
			else
			{
				Msg.MsgId = MY_MESSAGE_CLICK;
				Msg.hWinSrc = hWindow;
				hItem=WM_GetFocussedWindow();
				hParent=WM_GetParent(hItem);
				WM_SendMessage(hParent,&Msg);
			}
		}	
		GUI_Delay(100);			
	}
}



//更新WRDC类型结构体,显示自学习条目
void update_table_study(void)
{
	uint32_t i;
	uint32_t buf32;
	
	for(i=0;i<DEF_LENGTH_ITEM_STUDY;i++) items_study_index[i]=0;
	
	//过滤断路条目
	buf32 = 0;
	for(i=0;i<StudyFile->item_total;i++)
	{
		if(StudyFile->study_item[i].type=='Z')
		{
			continue;
		}
		else 
		{
			if(buf32 < DEF_LENGTH_ITEM_STUDY) items_study_index[buf32]=i;
			buf32++;
		}
	}
	items_study_show = buf32;
}

//更新WRDC显示
void update_item_study(int16_t *index)
{
	WM_HWIN  hItem;
	uint8_t  buf8;
	uint16_t buf16;
	uint16_t i;
	static uint32_t items_study_show_last=0;

	const char * pText[2][5];
	char id[5];
	char p1[5];
	char p2[5];
	char param[20];
	
	hItem = WM_GetDialogItem(hWindow, ID_LISTVIEW_0);
	if(items_study_show <= 0) 
	{
		*index=0;
		//delete items
		while(1)
		{
			buf8 = LISTVIEW_GetNumRows(hItem);
			if(buf8 != 0) LISTVIEW_DeleteRow(hItem,0);
			else break;
		}
		return;
	}
	// check index
	if(*index < 0) *index=0;
	
	else if(*index >= items_study_show) *index = items_study_show-1;
	
	
	//更新整个控件
	if(IsNewState != 0 || items_study_show_last != items_study_show)
	{
		IsNewState = 0;
		items_study_show_last = items_study_show;
		while(1)
		{
			buf8 = LISTVIEW_GetNumRows(hItem);
			if(buf8 != 0) LISTVIEW_DeleteRow(hItem,0);
			else break;
		}
		
		if(items_study_show > 9) 	buf8 = 9;
		else								buf8 = items_study_show;
		for(i=0;i<buf8;i++)
		{
			buf16 = i;
			itoa(buf16+1,id,10);
			pText[0][0]=id;

			//itoa(StudyFile->study_item[items_study_index[buf16]].p1,p1,10);
			num_converter(StudyFile->study_item[items_study_index[buf16]].p1,p1);
			pText[0][2]=p1;
			//itoa(StudyFile->study_item[items_study_index[buf16]].p2,p2,10);
			num_converter(StudyFile->study_item[items_study_index[buf16]].p2,p2);
			pText[0][3]=p2;

			if(StudyFile->study_item[items_study_index[buf16]].type=='W')
			{
				pText[0][1]="导通";
				//sprintf(param,"RGB=%d%d%d",StudyFile->study_item[items_study_index[buf16]].param1,StudyFile->study_item[items_study_index[buf16]].param2,StudyFile->study_item[items_study_index[buf16]].param3);
                sprintf(param,"RGB=%d%d%d",0,0,0);
            }
			else if(StudyFile->study_item[items_study_index[buf16]].type=='D')
			{
				pText[0][1]="二极管";
				sprintf(param,"V=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='C')
			{
				pText[0][1]="电容";
				sprintf(param,"C=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='R')
			{
				pText[0][1]="电阻";
				sprintf(param,"R=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='Z')
			{
				pText[0][1]="断路";
				sprintf(param,"Z=%d",StudyFile->study_item[items_study_index[buf16]].param2);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='K')
			{
				pText[0][1]="开关";
				sprintf(param,"K=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else
			{
				pText[0][1]="错误";
				sprintf(param,"自学习文件错误");
			}
			pText[0][4]=param;
			
			LISTVIEW_AddRow(hItem,pText[0]);
		}
		LISTVIEW_SetSel(hItem,0);
	}
	if(*index < listview_FirstItem)	//显示上移
	{
		//delete item
		buf8 = listview_FirstItem - *index;
		if(buf8 > 9) buf8=9;
		for(i=0;i<buf8;i++) LISTVIEW_DeleteRow(hItem,8-i);
		
		if(listview_FirstItem > buf8)  listview_FirstItem -= buf8;
		else															listview_FirstItem = 0;

		//add item
		for(i=0;i<buf8;i++)
		{
			//buf16 = *index + buf8 - 1 - i;
			if(buf16 >= DEF_LENGTH_ITEM_STUDY) 	buf16 = DEF_LENGTH_ITEM_STUDY - 1;
			else 										buf16 = *index + buf8 - 1 - i;
			itoa(buf16+1,id,10);
			pText[0][0]=id;

			//itoa(StudyFile->study_item[items_study_index[buf16]].p1,p1,10);
			num_converter(StudyFile->study_item[items_study_index[buf16]].p1,p1);
			pText[0][2]=p1;
			//itoa(StudyFile->study_item[items_study_index[buf16]].p2,p2,10);
			num_converter(StudyFile->study_item[items_study_index[buf16]].p2,p2);
			pText[0][3]=p2;

			if(StudyFile->study_item[items_study_index[buf16]].type=='W')
			{
				pText[0][1]="导通";
				//sprintf(param,"RGB=%d%d%d",StudyFile->study_item[items_study_index[buf16]].param1,StudyFile->study_item[items_study_index[buf16]].param2,StudyFile->study_item[items_study_index[buf16]].param3);
                sprintf(param,"RGB=%d%d%d",0,0,0);
            }
			else if(StudyFile->study_item[items_study_index[buf16]].type=='D')
			{
				pText[0][1]="二极管";
				sprintf(param,"V=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='C')
			{
				pText[0][1]="电容";
				sprintf(param,"C=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='R')
			{
				pText[0][1]="电阻";
				sprintf(param,"R=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='Z')
			{
				pText[0][1]="断路";
				sprintf(param,"Z=%d",StudyFile->study_item[items_study_index[buf16]].param2);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='K')
			{
				pText[0][1]="开关";
				sprintf(param,"K=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else
			{
				pText[0][1]="错误";
				sprintf(param,"自学习文件错误");
			}

			pText[0][4]=param;
			
			LISTVIEW_InsertRow(hItem, 0, pText[0]);
		}
		LISTVIEW_SetSel(hItem,0);
	}
	else if(*index > listview_FirstItem +8)	//显示下移
	{
		//delete item
		buf8 = *index - listview_FirstItem - 8;
		if(buf8 > 9) buf8=9;
		for(i=0;i<buf8;i++) LISTVIEW_DeleteRow(hItem,0);
		listview_FirstItem += buf8;

		//add item
		for(i=0;i<buf8;i++)
		{
			//buf16 = *index - buf8 + 1 + i;
			if(buf16 >= DEF_LENGTH_ITEM_STUDY) 	buf16 = DEF_LENGTH_ITEM_STUDY - 1;
			else 										buf16 = *index - buf8 + 1 + i;
			itoa(buf16+1,id,10);
			pText[1][0]=id;

			//itoa(StudyFile->study_item[items_study_index[buf16]].p1,p1,10);
			num_converter(StudyFile->study_item[items_study_index[buf16]].p1,p1);
			pText[1][2]=p1;
			//itoa(StudyFile->study_item[items_study_index[buf16]].p2,p2,10);
			num_converter(StudyFile->study_item[items_study_index[buf16]].p2,p2);
			pText[1][3]=p2;

			if(StudyFile->study_item[items_study_index[buf16]].type=='W')
			{
				pText[1][1]="导通";
				//sprintf(param,"RGB=%d%d%d",StudyFile->study_item[items_study_index[buf16]].param1,StudyFile->study_item[items_study_index[buf16]].param2,StudyFile->study_item[items_study_index[buf16]].param3);
                sprintf(param,"RGB=%d%d%d",0,0,0);
            }
			else if(StudyFile->study_item[items_study_index[buf16]].type=='D')
			{
				pText[1][1]="二极管";
				sprintf(param,"V=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='C')
			{
				pText[1][1]="电容";
				sprintf(param,"C=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='R')
			{
				pText[1][1]="电阻";
				sprintf(param,"R=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='Z')
			{
				pText[1][1]="断路";
				sprintf(param,"Z=%d",StudyFile->study_item[items_study_index[buf16]].param2);
			}
			else if(StudyFile->study_item[items_study_index[buf16]].type=='K')
			{
				pText[1][1]="开关";
				sprintf(param,"K=%d",StudyFile->study_item[items_study_index[buf16]].param1);
			}
			else
			{
				pText[1][1]="错误";
				sprintf(param,"自学习文件错误");
			}
			pText[1][4]=param;
			
			LISTVIEW_AddRow(hItem,pText[1]);
		}
		LISTVIEW_SetSel(hItem,9);
	}
	else	//修改指针
	{
		LISTVIEW_SetSel(hItem,(*index - listview_FirstItem));
	}

}

void get_items_studyindex(uint16_t items_studyindex[DEF_LENGTH_ITEM_STUDY])
{
	uint32_t i=0;
	for(i=0; i < DEF_LENGTH_ITEM_STUDY;i++)
	{
		items_studyindex[i] = items_study_index[i];
	}
}

uint32_t get_items_studyshow(void)
{
	return items_study_show;
}


// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
