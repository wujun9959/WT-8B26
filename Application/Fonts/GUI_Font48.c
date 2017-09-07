#include "wt_fonts.h"

extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c);


GUI_CONST_STORAGE GUI_CHARINFO GUI_FontHZ48_CharInfo[2] =  
{     
      {  24,  24,  3, (void *)"A48"},    
      {  48,  48,  6, (void *)"H48"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontHZ48_PropHZ= { 
      0xA1A1,  
      0xFEFE,  
      &GUI_FontHZ48_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_FontHZ48_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_FontHZ48_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_FontHZ48_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_FontHZ48 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	48,  
	48,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_FontHZ48_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_FontHZ48x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	48,  
	48,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_FontHZ48_PropASC 
};


