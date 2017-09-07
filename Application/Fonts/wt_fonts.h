/**
  ******************************************************************************
  * @file    wt_bsp_fonts.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2019-08-11
  * @brief   This file contains all the functions prototypes for the E2PROM driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_BSP_FONTS_H
#define __WT_BSP_FONTS_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "LCD.h"
#include "GUI.h"
#include "GUIConf.h"


/* SPI: SPI Flash fonts ( For GB2312, cndz_add_20160808)*/
#define GUI_FONTTYPE_PROP_USER                  \
  GUIPROP_X_DispChar,                           \
  (GUI_GETCHARDISTX *) GUIPROP_X_GetCharDistX,  \
  GUIMONO_GetFontInfo,                          \
  GUIMONO_IsInFont,                             \
  (GUI_GETCHARINFO *)0,                         \
  (tGUI_ENC_APIList*)0




   
/************************************************************************
*						emWin×ÖÌå
************************************************************************/
// spi flash font
extern GUI_CONST_STORAGE  GUI_FONT GUI_FontHZ32;
extern GUI_CONST_STORAGE  GUI_FONT GUI_FontHZ24;
extern GUI_CONST_STORAGE  GUI_FONT GUI_FontHZ16;
extern GUI_CONST_STORAGE  GUI_FONT GUI_FontHZ12;

//internal C file font
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ_Song_48;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ_Song_32;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ_Song_24;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ_Song_16;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ_Song_12;




//extern function


#ifdef __cplusplus
}
#endif
#endif /* __WT_BSP_FONTS_H */
   
/************************ (C) COPYRIGHT CNDZ *****END OF FILE****/
