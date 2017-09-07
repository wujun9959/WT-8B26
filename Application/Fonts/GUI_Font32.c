#include "wt_fonts.h"

extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c);


GUI_CONST_STORAGE GUI_CHARINFO GUI_FontHZ32_CharInfo[2] =  
{     
      {  16,  16,  2, (void *)"A32"},    
      {  32,  32,  4, (void *)"H32"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontHZ32_PropHZ= { 
      0xA1A1,  
      0xFEFE,  
      &GUI_FontHZ32_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_FontHZ32_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_FontHZ32_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_FontHZ32_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_FontHZ32 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	32,  
	32,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_FontHZ32_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_FontHZ32x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	32,  
	32,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_FontHZ32_PropASC 
};


