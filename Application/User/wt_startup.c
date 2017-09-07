/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_startup.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-06-12
  * @brief   This file provides the startup functions
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dialog.h"
#include "tools.h"

/** @addtogroup CORE
  * @{
  */

/** @defgroup KERNEL_STARTUP
  * @brief Kernel startup routines 
  * @{
  */

extern GUI_CONST_STORAGE GUI_BITMAP bm_wt_startupA;


/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t idx = 0;


static GUI_CONST_STORAGE unsigned short _acBlue6[] = {
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};

GUI_CONST_STORAGE GUI_BITMAP bmBlue6 = {
  6, // xSize
  6, // ySize
  12, // BytesPerLine
  16, // BitsPerPixel
  (unsigned char *)_acBlue6,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP565
};


static GUI_CONST_STORAGE unsigned short _acBlue10[] = {
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};

GUI_CONST_STORAGE GUI_BITMAP bmBlue10 = {
  10, // xSize
  10, // ySize
  20, // BytesPerLine
  16, // BitsPerPixel
  (unsigned char *)_acBlue10,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP565
};

/* Private function prototypes -----------------------------------------------*/
static void BackGroundCallback(WM_MESSAGE * pMsg) ;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Backbground callbacsk
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */

static void BackGroundCallback(WM_MESSAGE * pMsg) 
{
  uint16_t   xPos, Step = 20, i;
  const GUI_BITMAP * pBm;
  
  switch (pMsg->MsgId) 
  {
    case WM_PAINT:    
    //GUI_SetBkColor(GUI_LIGHTBLUE);
    //GUI_Clear();

    // set layer0
    //		GUI_SelectLayer(0);
    //		GUI_SetLayerVisEx (0, 0);
    GUI_DrawBitmap(&bm_wt_startupA,0,0);
    //		GUI_SetLayerVisEx (0, 1);

    //		GUI_SelectLayer(1);
    //		GUI_SetBkColor(GUI_TRANSPARENT);
    //		GUI_Clear();
//    GUI_SetFont(&GUI_Font32_ASCII);
//    GUI_SetBkColor(GUI_WHITE);
//    GUI_SetColor(GUI_BLUE);
    //GUI_DispStringHCenterAt("LZYWT-RDC256",LCD_GetXSize() / 2,170);
//    GUI_SetColor(GUI_DARKBLUE);
    //GUI_FillRect(0,LCD_GetYSize()-20,LCD_GetXSize(),LCD_GetYSize());
    for (i = 0, xPos = LCD_GetXSize() / 2 - 3 * Step; i < 7; i++, xPos += Step) 
    {
        pBm = (idx == i) ? &bmBlue10 : &bmBlue6;
        GUI_DrawBitmap(pBm, xPos - pBm->XSize / 2, 230 - pBm->YSize / 2);
    }
    break;
    
  default:
    WM_DefaultProc(pMsg); 
  } 
}

void wt_Logo_StartUp(void)
{
	GUI_DrawBitmap(&bm_wt_startupA,0,0);	
}
/**
  * @brief  Startup
  * @param  None
  * @retval None
  */
#define cnt_time_startup 6
void wt_StartUp(void)
{
  uint8_t loop;
  GUI_RECT Rect = {0, 200, 480, 272}; 

  WM_SetCallback(WM_HBKWIN, BackGroundCallback);

  loop = cnt_time_startup ;
  while (loop--)
  {
    idx = (cnt_time_startup- loop) % 7;

    WM_InvalidateArea(&Rect);
    
    GUI_Delay(500);
  }
}



/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
