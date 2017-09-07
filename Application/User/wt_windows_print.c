/*
******************************************************************************
* @progect LZY Wire Cube Tester
* @file    wt_windows_print.c
* @author  wujun
* @version V1.0.0
* @date    2015-03-23
* @brief   ...
******************************************************************************
*/


// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "wt_bsp.h"
#include "wt_task_gui.h"
#include "wt_uart_COM1.h"
#include "main.h"
#include "tools.h"
#include "wt_bsp_print.h"



/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
// USER START (Optionally insert additional defines)
// USER END
#define ID_WINDOW_0    			(GUI_ID_USER + 0x00)
#define ID_LISTBOX_0    		(GUI_ID_USER + 0x01)
#define ID_TEXT_FILE_LIST       (GUI_ID_USER + 0x02)
#define ID_TEXT_PRINT_STAT	    (GUI_ID_USER + 0x03)
#define ID_BUTTON_OK    		(GUI_ID_USER + 0x04)
#define ID_BUTTON_CANCEL	 	(GUI_ID_USER + 0x05)
#define ID_DROPDOWN_0    		(GUI_ID_USER + 0x06)
#define ID_IMAGE_0    			(GUI_ID_USER + 0x07)
#define ID_TEXT_MODE_SEL  	    (GUI_ID_USER + 0x08)
#define ID_EDIT_MODE  	        (GUI_ID_USER + 0x09)
#define ID_TEXT_WARN  	        (GUI_ID_USER + 0x0A)


extern GUI_CONST_STORAGE GUI_BITMAP bm_ICO_print; 
extern uint32_t wheel_value;
extern GUI_CONST_STORAGE GUI_BITMAP bmbm_test_run;
extern GUI_CONST_STORAGE GUI_BITMAP bmbm_test_ok;
extern GUI_CONST_STORAGE GUI_BITMAP bmbm_test_fail;

extern void UartInfr_Send_StartPrint_Cmd(void);

char str_mode[20];
void Init_Dialog(WM_MESSAGE * pMsg);

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static int cursorindex=0;

// USER START (Optionally insert additional static data)
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos);
static uint8_t  IsNewStatus =0;
														

K_ModuleItem_Typedef  wt_print =
{	
	7,
	"打印",
	&bm_ICO_print,	
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
    { TEXT_CreateIndirect, "filelist", ID_TEXT_FILE_LIST, 20, 10, 120, 20, 0, 0x64, 0 },
    { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 120,  10,  80,  20, 0, 0x0, 0 },
    { LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_0, 20, 30, 200, 120, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "mode", ID_TEXT_MODE_SEL, 	10, 165, 35, 20, 0, 0x64, 0 },
    { EDIT_CreateIndirect, "Edit-mode", ID_EDIT_MODE, 45, 158, 190, 30, 0, 0x64, 0 },
    { IMAGE_CreateIndirect, "Image", ID_IMAGE_0, 262, 45, 190, 140, 0, 0, 0 }, 
    { TEXT_CreateIndirect, "print_stat", ID_TEXT_PRINT_STAT, 320, 20, 100, 20, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "warning", ID_TEXT_WARN, 20, 200, 120, 20, 0, 0x64, 0 },
    { BUTTON_CreateIndirect, "start", ID_BUTTON_OK, 150, 200, 80, 20, 0, 0, 0 },
    { BUTTON_CreateIndirect, "exit", ID_BUTTON_CANCEL, 250, 200, 80, 20, 0, 0, 0 },
};

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	
	GUI_SetPenSize(8);
	WINDOW_SetBkColor(pMsg->hWin, 0x00FFFFFF);
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
		Init_Dialog(pMsg);
        Wheel_Encoder_Clear();    
        break;
	case WM_PAINT://绘制边框
		GUI_SetColor(GUI_DARKGRAY);
		GUI_SetPenSize(4);
		GUI_DrawRoundedFrame(2, 2, 240, 195, 0, 4);
		GUI_DrawRoundedFrame(2, 2, 478, 195, 0, 4);
		GUI_SetColor(GUI_BLUE);
		GUI_DrawLine(262, 185, 451, 185);	
        break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

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
	WM_HWIN hItem_mode;

//	int32_t wheel_stat=0;
	uint8_t res=0;
	uint8_t sel;
	uint8_t items;
	int32_t i;
	uint8_t print_stat = 0;//0-no change  1-changed 
	int cursorpos=0;
	int index=0;
	uint8_t NumChars=0;
	
	static uint8_t last_stat = 0;//
	uint8_t curr_stat = 0;//
	char file_name[20];//文件名称
	char mode_name[20];//型号名称
	
  uint16_t keywheelcnt = 0;

	wt_SetText_Title("");
	wt_SetText_Menu(wt_print.name);
	
	hWindow = GUI_CreateDialogBox(_aDialog, GUI_COUNTOF(_aDialog), _cbDialog, hWin, xpos, ypos);
	memset(file_name,0,20);
	memset(mode_name,0,20);
	
	loop1:
	while(1)
    {
		BSP_Update_Wheel();
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
			PrintFile->print_status = 0;
			return;
		}
		if(BSP_GetKEY_State(KeyOK) == 1)
		{
			while(BSP_GetKEY_State(KeyOK) == 1)
			{
				osDelay(10);
			}
			memset(str_mode,0,20);
			hItem = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
			EDIT_GetText(hItem,str_mode,20);
			if(strlen(str_mode)==0)//线束型号输入检测
			{
				hItem = WM_GetDialogItem(hWindow, ID_TEXT_WARN);
				WM_ShowWindow(hItem);
				GUI_Exec();
				goto loop1;
			}
			else
			{
				hItem = WM_GetDialogItem(hWindow, ID_TEXT_WARN);
				WM_HideWindow(hItem);
			}
			
			hItem = WM_GetDialogItem(hWindow, ID_LISTBOX_0);
			//if(LISTBOX_GetNumItems(hItem) ==0 ) 	goto loop1;;
			if(store_dev ==2 ) //如果SD卡或U盘中没有文件，选择从Flash中读取打印文件
			{
				WT_PrintFileInfo_ReadFlash();//读取Flash中打印文件数据
				osDelay(50);
				memset(str_mode,0,20);
				hItem = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
				EDIT_GetText(hItem,str_mode,20);
				//保存型号信息
				WT_PrintModeName_Init(str_mode);
				goto print_start;
			}
			
			PrintFolder->number_CurrentFile=LISTBOX_GetSel(hItem);
			//打开U盘或SD卡中的prn文件
			res=WT_PrintFiles_Init((char *)PrintFolder->FilesName[LISTBOX_GetSel(hItem)],str_mode);//0-not init, 1-inited, 2-no files, 3-hardware error, 4-no folder
			if(res == 1)
			{
				WT_PrintFileInfo_Write2Flash();//保存打印文件信息
				
				WT_PrintModeName_Init(str_mode);
				print_start:
				//osMessagePut(UartCOM2Event, UartCOM2_TX_Event, 0);//开始打印
				hItem = WM_GetDialogItem(hWindow, ID_TEXT_PRINT_STAT);
				WM_ShowWindow(hItem);
				hItem = WM_GetDialogItem(hWindow, ID_IMAGE_0);
				WM_ShowWindow(hItem);
				hItem = WM_GetDialogItem(hWindow, ID_BUTTON_OK);
				BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_GRAY);
				PrintFile->print_status = 1;
				print_stat = 1;		
			}
			else
			{
				PrintFile->print_status = 4;//0-stop 1-wait, 2-print ok, 3-print run, 4-print error
				goto loop1;
			}

		}
		if(BSP_GetKEY_State(KeyDown) == 1)
		{
			while(BSP_GetKEY_State(KeyDown) == 1)
			{
				osDelay(10);
			}
			
			hItem = WM_GetDialogItem(hWindow, ID_LISTBOX_0);
			if(WM_HasFocus(hItem))
			{
				LISTBOX_IncSel(hItem);
				osDelay(20);
				if(LISTBOX_GetNumItems(hItem) > 0)
				{
					LISTBOX_GetItemText(hItem,LISTBOX_GetSel(hItem),file_name,20);
					memset(mode_name,0,20);
					if(store_dev == 2) strcpy(mode_name,file_name);//flash中保存的文件名没有.wtr
					else strncpy(mode_name,file_name,strlen(file_name)-4);
					//根据文件名更新线束型号
					hItem_mode = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
					EDIT_SetText(hItem_mode, mode_name);
				}		

			}

			
			hItem = WM_GetDialogItem(hWindow, ID_DROPDOWN_0);
			if(WM_HasFocus(hItem))
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

				store_dev=DROPDOWN_GetSel(hItem);
				if(store_dev == 2)//flash
				{
					WT_ModeName_read();
					hItem = WM_GetDialogItem(hWindow, ID_LISTBOX_0);
					items = LISTBOX_GetNumItems(hItem);
					for(i=0;i<items;i++)
					{
						LISTBOX_DeleteItem(hItem,0);
					}
					for(i=0;i<PrintConfig->max_index;i++)
					{
						LISTBOX_AddString(hItem, (char *)PrintConfig->print_item[i].mode_name);
					}
					
					LISTBOX_SetSel(hItem,0);
					//根据文件名更新线束型号
					hItem_mode = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
					EDIT_SetText(hItem_mode, (char *)PrintConfig->print_item[0].mode_name);
				}
				else 
				{
					WT_PrintFolder_Init();
					hItem = WM_GetDialogItem(hWindow, ID_LISTBOX_0);
					items = LISTBOX_GetNumItems(hItem);
					for(i=0;i<items;i++)
					{
						LISTBOX_DeleteItem(hItem,0);
					}
					for(i=0;i<PrintFolder->number_TotalFile;i++)
					{
						LISTBOX_AddString(hItem, (char *)PrintFolder->FilesName[i]);
					}
					if(PrintFolder->number_TotalFile >=1) 
					{
						LISTBOX_SetSel(hItem,0);
						//根据文件名更新线束型号
						memset(mode_name,0,20);
						LISTBOX_GetItemText(hItem,LISTBOX_GetSel(hItem),file_name,20);
						strncpy(mode_name,file_name,strlen(file_name)-4);
						hItem_mode = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
						EDIT_SetText(hItem_mode, mode_name);
					}
		
					//GUI_Exec();
					//if(PrintFolder->number_TotalFile ==0) LISTBOX_DeleteItem(hItem,0);
				}
			}	
			//输入下一个字符
			hItem = WM_GetDialogItem(hWindow, ID_EDIT_MODE);	
			if(WM_HasFocus(hItem))
			{			
				cursorpos=EDIT_GetCursorCharPos(hItem);
				NumChars = EDIT_GetNumChars(hItem);
				if(cursorpos <= (NumChars-1) )
				{
					EDIT_SetCursorAtChar(hItem,cursorpos+1);
					EDIT_SetSel(hItem,cursorpos+1,cursorpos+1);
					cursorindex=EDIT_GetCursorCharPos(hItem);
				}
			}
		}
		if(BSP_GetKEY_State(KeyUp) == 1)
		{
			while(BSP_GetKEY_State(KeyUp) == 1)
			{
				osDelay(10);
			}
			
			hItem = WM_GetDialogItem(hWindow, ID_LISTBOX_0);
			if(WM_HasFocus(hItem))
			{
				LISTBOX_DecSel(hItem);
				osDelay(20);
				if(LISTBOX_GetNumItems(hItem) > 0)
				{
					LISTBOX_GetItemText(hItem,LISTBOX_GetSel(hItem),file_name,20);
					memset(mode_name,0,20);
					if(store_dev == 2) strcpy(mode_name,file_name);//flash中保存的文件名没有.wtr
					else strncpy(mode_name,file_name,strlen(file_name)-4);
					//根据文件名更新线束型号
					hItem_mode = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
					EDIT_SetText(hItem_mode, mode_name);  
				}					
			}
			
			hItem = WM_GetDialogItem(hWindow, ID_DROPDOWN_0);
			if(WM_HasFocus(hItem))
			{
				sel=DROPDOWN_GetSel(hItem);
				if(sel>0)
				{
					DROPDOWN_DecSel(hItem);
				}					
				else //sel>=1 
				{
					DROPDOWN_SetSel(hItem,2);		
				}	

				store_dev=DROPDOWN_GetSel(hItem);
				if(store_dev == 2)//flash
				{	
					WT_ModeName_read();//读取Flash中的型号名称
					hItem = WM_GetDialogItem(hWindow, ID_LISTBOX_0);
					items = LISTBOX_GetNumItems(hItem);
					for(i=0;i<items;i++)
					{
						LISTBOX_DeleteItem(hItem,0);
					}
					for(i=0;i<PrintConfig->max_index;i++)
					{
						LISTBOX_AddString(hItem, (char *)PrintConfig->print_item[i].mode_name);
					}
					
					LISTBOX_SetSel(hItem,0);
					//根据文件名更新线束型号
					hItem_mode = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
					EDIT_SetText(hItem_mode, (char *)PrintConfig->print_item[0].mode_name);
				}
				else 
				{
					WT_PrintFolder_Init();
					hItem = WM_GetDialogItem(hWindow, ID_LISTBOX_0);
					items = LISTBOX_GetNumItems(hItem);
					for(i=0;i<items;i++)
					{
						LISTBOX_DeleteItem(hItem,0);
					}
					for(i=0;i<PrintFolder->number_TotalFile;i++)
					{
						LISTBOX_AddString(hItem, (char *)PrintFolder->FilesName[i]);
					}
					if(PrintFolder->number_TotalFile >=1) 
					{
						LISTBOX_SetSel(hItem,0);
						//根据文件名更新线束型号
						memset(mode_name,0,20);
						LISTBOX_GetItemText(hItem,LISTBOX_GetSel(hItem),file_name,20);
						strncpy(mode_name,file_name,strlen(file_name)-4);
						hItem_mode = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
						EDIT_SetText(hItem_mode, mode_name);
					}
				}
			}
			
			//删除字符
			hItem = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
			if(WM_HasFocus(hItem))
			{
				EDIT_AddKey(hItem,GUI_KEY_BACKSPACE);
				cursorindex=EDIT_GetCursorCharPos(hItem);
			}
		}
        if(1 == KeyLed_State.rotate)// 顺时针旋转,向下选择条目
		{
            hItem = WM_GetDialogItem(hWindow, ID_LISTBOX_0);
            if(WM_HasFocus(hItem))
            {
                LISTBOX_IncSel(hItem);
                osDelay(20);
                if(LISTBOX_GetNumItems(hItem) > 0)
                {
                    LISTBOX_GetItemText(hItem,LISTBOX_GetSel(hItem),file_name,20);
                    memset(mode_name,0,20);
                    if(store_dev == 2) strcpy(mode_name,file_name);//flash中保存的文件名没有.wtr
                    else strncpy(mode_name,file_name,strlen(file_name)-4);
                    //根据文件名更新线束型号
                    hItem_mode = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
                    EDIT_SetText(hItem_mode, mode_name);  
                }					
            }
            //输入线束型号
			hItem = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
			if(WM_HasFocus(hItem))
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
				GUI_Exec();
			}
            //osDelay(100); 
		}
        if(2 == KeyLed_State.rotate)//逆时针旋转,向上选择条目
        {
            hItem = WM_GetDialogItem(hWindow, ID_LISTBOX_0);
            if(WM_HasFocus(hItem))
            {
                LISTBOX_DecSel(hItem);
                osDelay(20);
                if(LISTBOX_GetNumItems(hItem) > 0)
                {
                    LISTBOX_GetItemText(hItem,LISTBOX_GetSel(hItem),file_name,20);
                    memset(mode_name,0,20);
                    if(store_dev == 2) strcpy(mode_name,file_name);//flash中保存的文件名没有.wtr
                    else strncpy(mode_name,file_name,strlen(file_name)-4);
                    //根据文件名更新线束型号
                    hItem_mode = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
                    EDIT_SetText(hItem_mode, mode_name);  
                }					
            }
            //输入线束型号
			hItem = WM_GetDialogItem(hWindow, ID_EDIT_MODE);
			if(WM_HasFocus(hItem))
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
				GUI_Exec();
			}
            //osDelay(100); 
        }
		if(BSP_GetKEY_State(KeyWheel) == 1)
		{
			while(BSP_GetKEY_State(KeyWheel) == 1)
			{
				osDelay(10);
				keywheelcnt++;
			}		
			if(keywheelcnt > 500)//按住按钮键5秒，清除Flash中的型号信息
			{
				WT_ModeName_Clear();
				keywheelcnt=0;
			}
			GUI_SendKeyMsg(GUI_KEY_TAB, 1);//改变输入焦点			
		}
		if(BSP_GetInput_State(0) == 1)//DIN1输入检测，引脚1，4
		{
			for(i=0;i<3;i++)
			{
				osDelay(10);
				BSP_Update_Input();
				if(BSP_GetInput_State(0) == 0) 
				{
					curr_stat = 0;
					break;
				}
			}
			if(i >= 3) curr_stat = 1;
			if(last_stat != curr_stat) 
			{
				IsNewStatus = 1;
				last_stat = curr_stat;
			}
			if(IsNewStatus != 0 && curr_stat != 0 && PrintFile->print_status == 1) 
			{
				osMessagePut(UartCOM1Event, UartCOM1_TX_Event, 0);
				IsNewStatus = 0;
			}
		}
		if(BSP_GetInput_State(0) == 0)//DIN1输入
		{
			for(i=0;i<3;i++)
			{
				osDelay(10);
				BSP_Update_Input();
				if(BSP_GetInput_State(0) == 1) 
				{
					curr_stat = 1;
					break;
				}
			}
			if(i >= 3) curr_stat = 0;
			if(last_stat != curr_stat) 
			{
				IsNewStatus = 1;
				last_stat = curr_stat;
			}
		}
	
		switch(PrintFile->print_status)//0-stop 1-wait, 2-print ok, 3-print run, 4-print error
		{
			case 0x00:
				hItem = WM_GetDialogItem(hWindow, ID_TEXT_PRINT_STAT);
				TEXT_SetText(hItem, "选择打印文件");
				GUI_Exec();
				if(print_stat == 1)
				{
					hItem = WM_GetDialogItem(hWindow, ID_IMAGE_0);
					IMAGE_SetBitmap(hItem, &bmbm_test_run);
					print_stat = 0;
				}
				break;
			case 0x01:
				hItem = WM_GetDialogItem(hWindow, ID_TEXT_PRINT_STAT);
				TEXT_SetText(hItem, "等待打印");
				if(print_stat == 1)
				{
					hItem = WM_GetDialogItem(hWindow, ID_IMAGE_0);
					IMAGE_SetBitmap(hItem, &bmbm_test_run);
					print_stat = 0;
				}
				break;
			case 0x02:
				hItem = WM_GetDialogItem(hWindow, ID_TEXT_PRINT_STAT);
				TEXT_SetText(hItem, "打印完成");
				hItem = WM_GetDialogItem(hWindow, ID_IMAGE_0);
				IMAGE_SetBitmap(hItem, &bmbm_test_ok);
				GUI_Exec();
				//计数牌+1
				IO_State.output = IO_State.output | (1<<0);//继电器输出高电平
				osDelay(1000);
				IO_State.output = IO_State.output & (0<<0);//继电器输出低电平
				PrintFile->print_status = 1;
				print_stat = 1;
				break;
			case 0x03:
				hItem = WM_GetDialogItem(hWindow, ID_TEXT_PRINT_STAT);
				TEXT_SetText(hItem, "正在打印");
				hItem = WM_GetDialogItem(hWindow, ID_IMAGE_0);
				IMAGE_SetBitmap(hItem, &bmbm_test_run);
				break;
			case 0x04:
				hItem = WM_GetDialogItem(hWindow, ID_TEXT_PRINT_STAT);
				TEXT_SetText(hItem, "打印错误");
				hItem = WM_GetDialogItem(hWindow, ID_IMAGE_0);
				IMAGE_SetBitmap(hItem, &bmbm_test_fail);
				break;
			default:
			break;
		}

		//delay
		osDelay(30); 
		GUI_Exec();
	}
}

void Init_Dialog(WM_MESSAGE * pMsg)
{
	WM_HWIN hItem;
	WM_HWIN hItem_mode;
	char file_name[20];//文件名称
	char mode_name[20];//型号名称
	memset(file_name,0,20);
	memset(mode_name,0,20);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
	DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
	//if(k_StorageGetStatus(USB_DISK_UNIT) != 0)
	DROPDOWN_AddString(hItem, "U盘");
	//if(k_StorageGetStatus(MSD_DISK_UNIT) != 0)
	DROPDOWN_AddString(hItem, "SD卡");
	DROPDOWN_AddString(hItem, "Flash");
	if(k_StorageGetStatus(MSD_DISK_UNIT) != 0) DROPDOWN_SetSel(hItem,1);
	else DROPDOWN_SetSel(hItem,0);
	store_dev=DROPDOWN_GetSel(hItem);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_FILE_LIST);
	TEXT_SetFont(hItem,&GUI_FontHZ16);
	TEXT_SetText(hItem, "打印文件:");  	
	WT_PrintFolder_Init();
	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
	for(int i=0;i<PrintFolder->number_TotalFile;i++)
	{
		LISTBOX_AddString(hItem, (char *)PrintFolder->FilesName[i]);
	}
	LISTBOX_SetFont(hItem,GUI_FONT_20_1);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_PRINT_STAT);
	TEXT_SetText(hItem, "选择打印文件");
	TEXT_SetFont(hItem, &GUI_FontHZ16);
	TEXT_SetTextColor(hItem,GUI_BLUE);
	//WM_HideWindow(hItem);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
	IMAGE_SetBitmap(hItem, &bmbm_test_run);
	//		FileSize = sizeof(bmbm_test_run);
	//		pData = (const void *)&bmbm_test_run;
	//		IMAGE_SetBMP(hItem, pData, FileSize);
	//WM_HideWindow(hItem);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MODE_SEL);
	TEXT_SetFont(hItem,&GUI_FontHZ16);
	TEXT_SetText(hItem, "型号:");  	


	hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MODE);
	EDIT_SetFont(hItem,GUI_FONT_24B_1);
	EDIT_SetMaxLen(hItem, 50);
	EDIT_EnableBlink(hItem, 600, 1);
	EDIT_SetInsertMode(hItem,1);	
	if(strlen(str_mode) == 0)
	{
		if(LISTBOX_GetNumItems(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0)) > 0)
		{
			LISTBOX_GetItemText(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0),0,file_name,20);
			memset(mode_name,0,20);
			if(store_dev == 2) strcpy(mode_name,file_name);//flash中保存的文件名没有.wtr
			else strncpy(mode_name,file_name,strlen(file_name)-4);
			//根据文件名更新线束型号
			hItem_mode = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MODE);
			EDIT_SetText(hItem_mode, mode_name);  
		}		
		//EDIT_SetText(hItem, "8001018049");  	
	}
	else 
	{
		WT_PrintFileInfo_ReadFlash();
		EDIT_SetText(hItem, str_mode);
	}
	cursorindex=EDIT_GetCursorCharPos(hItem);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_WARN);
	TEXT_SetText(hItem, "请输入线束型号");
	TEXT_SetFont(hItem, &GUI_FontHZ16);
	TEXT_SetTextColor(hItem,GUI_RED);
	WM_HideWindow(hItem);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_OK);
	BUTTON_SetFont(hItem,&GUI_FontHZ12);
	BUTTON_SetText(hItem, "开始");
	BUTTON_SetSkinClassic(hItem);
	BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_GREEN);
	BUTTON_SetFocussable(hItem,0);//不接收焦点

	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_CANCEL);
	BUTTON_SetFont(hItem,&GUI_FontHZ12);
	BUTTON_SetText(hItem, "关闭");
	BUTTON_SetSkinClassic(hItem);
	BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_RED);
	BUTTON_SetFocussable(hItem,0);//不接收焦点
}

