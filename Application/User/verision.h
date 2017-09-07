/**
  ******************************************************************************
  * @file    verision.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2015-3-12
  * @brief   This file contains all the functions prototypes for the verision driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VERISION_H
#define __VERISION_H

#ifdef __cplusplus
 extern "C" {
#endif
   

// version
#define DEF_WT_VERSION_MAIN		(0x01)	/*!< [31:24] main version */
#define DEF_WT_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define DEF_WT_VERSION_SUB2   (0x08) /*!< [15:8]  sub2 version */

#define DEF_WT_VERSION				((DEF_WT_VERSION_MAIN << 16)\
															|(DEF_WT_VERSION_SUB1 << 8)\
															|(DEF_WT_VERSION_SUB2 )

//#define HD_VERSION1   //version2.0 10us, version1.0--->150us	
//#define TASKOUTPUT   1  //输出任务信息   

#ifdef __cplusplus
}
#endif

#endif /* __VERISION_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
