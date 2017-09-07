/********************************************************************************
	Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      wt_windows_menu.c
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


/* Includes ------------------------------------------------------------------*/
#include "wt_bsp.h" 
#include "DIALOG.h"
#include "dialog.h"
#include "messagebox.h"
#include "cpu_utils.h"
#include "wt_task_gui.h"
#include "wt_task_wirefindpoint.h"
#include "main.h" 



#define ID_ICONVIEW_MENU  (GUI_ID_USER + 0x02)

static ICONVIEW_Handle hIcon = 0;

/*********************************************************************
*
*       _cbBk
*/
static void _cbBk(WM_MESSAGE * pMsg) {
//  
//  MENU_MSG_DATA* pData;
//  uint32_t NCode, Id;
//  static uint8_t sel = 0;
//  
  switch (pMsg->MsgId) 
  {

		case WM_PAINT:
			GUI_SetBkColor(GUI_TRANSPARENT);
			GUI_Clear();
			if(hIcon)
			{
				WM_BringToBottom(hIcon);
			}
			break;
		default:
			WM_DefaultProc(pMsg);
  }
}

/**
  * @brief  Initializes the menu.
  * @param  None.
  * @retval None.
  */
void k_InitMenu(void) 
{
  uint8_t i = 0;
	char temp[50];

  //GUI_SetLayerVisEx (0, 1);
  GUI_SelectLayer(1);
  GUI_Clear();
  WM_SetCallback(WM_HBKWIN, _cbBk);
  
	if(hIcon == 0)
	{
		hIcon = ICONVIEW_CreateEx(0, 
                                    25, 
                                    LCD_GetXSize(), 
                                    LCD_GetYSize()- 50, 
                                    WM_HBKWIN, 
                                    WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_BGND ,
                                    ICONVIEW_CF_AUTOSCROLLBAR_V,
                                    ID_ICONVIEW_MENU, 
                                    115, 
                                    90);
		
		//ICONVIEW_SetFont(hIcon, &GUI_Font13B_ASCII);
		ICONVIEW_SetFont(hIcon, &GUI_FontHZ16);
		
		ICONVIEW_SetBkColor(hIcon, ICONVIEW_CI_SEL, GUI_LIGHTBLUE |GUI_TRANSPARENT);
		
		ICONVIEW_SetSpace(hIcon, GUI_COORD_Y, 10);
		
		ICONVIEW_SetFrame(hIcon, GUI_COORD_Y, 10);
			
		for (i = 0; i < k_ModuleGetNumber(); i++)
		{
			ICONVIEW_AddBitmapItem(hIcon,module_prop[i].module->icon, (char *)module_prop[i].module->name);
		}
	}
	else
	{
		WM_ShowWindow(hIcon);
	}
	WM_SetFocus(hIcon);
	//update title & menu
	strcpy(temp, DEF_WT_NAME);
	strcat(temp, " ");
	strcat(temp, DEF_WT_MODEL);
	wt_SetText_Title(temp);
	wt_SetText_Menu("主菜单");
}


/**
  * @brief  goto next menu.
  * @param  None.
  * @retval None.
  */
static void Menu_NextICO(void) 
{
	static int id;
	id=ICONVIEW_GetSel(hIcon);
	id++;
	
	if(id > (ICONVIEW_GetNumItems(hIcon)-1)) id=0;
	ICONVIEW_SetSel(hIcon, id);
	//wheel_value=KeyLed_State.wheel;
	switch(id)
	{
		case 0:
			wt_SetText_Status("运行线束检测程序"); 	
			break;
		case 1:
			wt_SetText_Status("自动学习测试规则"); 
			break;
		case 2:
			wt_SetText_Status("运行自动找点程序"); 
			break;
		case 3:
			wt_SetText_Status("编辑测试规则文件"); 
			break;
		case 4:
			wt_SetText_Status("运行设备自检程序"); 
			break;
		case 5:
			wt_SetText_Status("进入系统设置菜单"); 
			break;
		case 6:
			wt_SetText_Status("显示系统信息");
			break;
		case 7:
			wt_SetText_Status("系统打印");
			break;
		default:
			wt_SetText_Status("");
			break;
	}
}

/**
  * @brief  goto forward menu.
  * @param  None.
  * @retval None.
  */
static void Menu_ForwardICO(void) 
{
	static int id;
	id = ICONVIEW_GetSel(hIcon);
	id--;
	if(id <0) id=ICONVIEW_GetNumItems(hIcon)-1;
	ICONVIEW_SetSel(hIcon, id);
	//wheel_value=KeyLed_State.wheel;
	switch(id)
	{
		case 0:
			wt_SetText_Status("运行线束检测程序"); 	
			break;
		case 1:
			wt_SetText_Status("自动学习测试规则"); 
			break;
		case 2:
			wt_SetText_Status("运行自动找点程序"); 
			break;
		case 3:
			wt_SetText_Status("编辑测试规则文件"); 
			break;
		case 4:
			wt_SetText_Status("运行设备自检程序"); 
			break;
		case 5:
			wt_SetText_Status("进入系统设置菜单"); 
			break;
		case 6:
			wt_SetText_Status("显示系统信息");
			break;
		case 7:
			wt_SetText_Status("运行打印程序");
			break;
		default:
			wt_SetText_Status("");
			break;
	}
}


/**
  * @brief  Open the ICO Item.
  * @param  None.
  * @retval None.
  */
void WT_Windows_Menu(uint32_t *ID_Select)
{
    //uint32_t wheel_value=0;
    uint8_t buf8=0;
    char temp[50];
    /* Show the main menu */
    k_InitMenu();
 
  /* Gui background Task */
  while(1)
  {
		//key detect
        //KeyLed_State.wheel = Wheel_Encoder_Read();
        BSP_Update_Wheel();
		if(BSP_GetKEY_State(KeyUp) == 1)
		{
			while(BSP_GetKEY_State(KeyUp) == 1)
			{			
				osDelay(10); 
			}
			Menu_ForwardICO();

		}
		
		if(BSP_GetKEY_State(KeyDown) == 1)
		{
			while(BSP_GetKEY_State(KeyDown) == 1)
			{
				osDelay(10); 
			}
			Menu_NextICO();
		}
		
		if(BSP_GetKEY_State(KeyOK) == 1 || BSP_GetKEY_State(KeyWheel)==1 )
		{
			while(BSP_GetKEY_State(KeyOK) == 1 || BSP_GetKEY_State(KeyWheel)==1)
			{
				osDelay(10); 
			}

			*ID_Select = ICONVIEW_GetSel(hIcon);
			//WM_DeleteWindow(hIcon);
			WM_HideWindow(hIcon);
			Number_Windos = 1;
			return;
		}
        if(1 == KeyLed_State.rotate)// 顺时针旋转
		{
            Menu_NextICO();
            osDelay(100); 
		}
        if(2 == KeyLed_State.rotate)//逆时针旋转
        {
            Menu_ForwardICO();
            osDelay(100); 
        }
		if(BSP_GetLock_State() == 1 && WT_Config.Lockstat == 0xFE)
		{
			buf8 = 10;
			while(BSP_GetLock_State() == 1)
			{
				osDelay(20);
				buf8--;
				if(buf8 == 0) break;
			}
			wt_SetText_Title("设备锁定，请解锁！");
		}
		if(BSP_GetLock_State() == 0)
		{
			buf8 = 10;
			while(BSP_GetLock_State() == 1)
			{
				osDelay(20);
				buf8--;
				if(buf8 == 0) break;
			}
			WT_Config.Lockstat = 0;
			strcpy(temp, DEF_WT_NAME);
			strcat(temp, " ");
			strcat(temp, DEF_WT_MODEL);
			wt_SetText_Title(temp);
		}

		//delay
		osDelay(100); 
		GUI_Exec();
	}
}

