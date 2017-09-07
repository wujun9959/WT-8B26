/**
  ******************************************************************************
  * @file    wt_bsp.h
  * @author  MCD Application Team
  * @version V2.1.1
  * @date    10-December-2014
  * @brief   This file contains definitions for STM32F429I-Discovery Kit LEDs,
  *          push-buttons hardware resources.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F429I_DISCOVERY_H
#define __STM32F429I_DISCOVERY_H

#ifdef __cplusplus
 extern "C" {
#endif
                                              
/* Includes ------------------------------------------------------------------*/
//#include "verision.h"
#include "wt_bsp_common.h"
#include "wt_bsp_define.h"   
#include "wt_bsp_ad.h"
#include "wt_bsp_eeprom.h"
#include "wt_bsp_file.h"
#include "wt_bsp_ili6480.h"
#include "wt_bsp_infrared.h"
#include "wt_bsp_io.h"
#include "wt_bsp_key_led.h"
#include "wt_bsp_lcd.h"
#include "wt_bsp_sd.h"
#include "wt_bsp_sdram.h"
#include "wt_bsp_spi_flash.h"
#include "wt_bsp_storage.h"
#include "wt_bsp_usart.h"
#include "wt_bsp_print.h"


// DMA Define
/**************************************************
DMA1_Stream4					EEPROM_I2C_DMA_STREAM_TX 
DMA1_Stream2					EEPROM_I2C_DMA_STREAM_RX
DMA2_Stream0					SDRAM_DMAx_STREAM
DMA2_Stream0	 				ADCx_DMA_STREAM
DMA2_Stream6	 				SD_DMAx_Tx_STREAM
DMA2_Stream3	 				SD_DMAx_Rx_STREAM
   
**************************************************/	 



/** @addtogroup STM32F429I_DISCOVERY LOW_LEVEL_BUS
  * @{
  */  
/* Exported constanIO --------------------------------------------------------*/
//#define IO_I2C_ADDRESS                      0x82 
//#define TS_I2C_ADDRESS                      0x82

//#define EEPROM_I2C_ADDRESS_A01              0xA0
//#define EEPROM_I2C_ADDRESS_A02              0xA6


/*##################### I2Cx ###################################*/
/* User can use this section to tailor I2Cx instance used and associated 
   resources */
//#define DISCOVERY_I2Cx                          I2C1
//#define DISCOVERY_I2Cx_CLOCK_ENABLE()           __I2C1_CLK_ENABLE()
//#define DISCOVERY_I2Cx_FORCE_RESET()            __I2C1_FORCE_RESET()
//#define DISCOVERY_I2Cx_RELEASE_RESET()          __I2C1_RELEASE_RESET()
//#define DISCOVERY_I2Cx_SDA_GPIO_CLK_ENABLE()    __GPIOB_CLK_ENABLE()
//#define DISCOVERY_I2Cx_SCL_GPIO_CLK_ENABLE()    __GPIOB_CLK_ENABLE() 
//#define DISCOVERY_I2Cx_SDA_GPIO_CLK_DISABLE()   __GPIOB_CLK_DISABLE()

///* Definition for DISCO I2Cx Pins */
//#define DISCOVERY_I2Cx_SCL_PIN                  GPIO_PIN_6
//#define DISCOVERY_I2Cx_SCL_GPIO_PORT            GPIOB
//#define DISCOVERY_I2Cx_SCL_SDA_AF               GPIO_AF4_I2C1
//#define DISCOVERY_I2Cx_SDA_PIN                  GPIO_PIN_7
//#define DISCOVERY_I2Cx_SDA_GPIO_PORT            GPIOB

///* Definition for IOE I2Cx's NVIC */
//#define DISCOVERY_I2Cx_EV_IRQn                  I2C1_EV_IRQn
//#define DISCOVERY_I2Cx_ER_IRQn                  I2C1_ER_IRQn

///* I2C clock speed configuration (in Hz) 
//  WARNING: 
//   Make sure that this define is not already declared in other files (ie. 
//  stm324x9i_disco.h file). It can be used in parallel by other modules. */
//#ifndef I2C_SPEED
// #define I2C_SPEED                          100000
//#endif /* I2C_SPEED */



///*##################### SPIx ###################################*/



///*##################### IOE ###################################*/
///** 
//  * @brief  IOE Control pin  
//  */ 
///* Definition for external IT for STMPE811 */
//#define STMPE811_INT_PIN                        GPIO_PIN_5
//#define STMPE811_INT_GPIO_PORT                  GPIOC
//#define STMPE811_INT_CLK_ENABLE()               __GPIOC_CLK_ENABLE()
//#define STMPE811_INT_CLK_DISABLE()              __GPIOC_CLK_DISABLE()
//#define STMPE811_INT_EXTI                       EXTI9_5_IRQn
//#define STMPE811_INT_EXTIHandler                EXTI9_5_IRQHandler
/**
  * @}
  */ 











/*###########################################################################################*/

/** 
  * @brief  LZY Wire Tester Pin Define 
  */ 

/*##################### LED Run ######################################################################*/

/** @addtogroup WT LOW_LEVEL_LED
  * @{
  */
//#define LEDn                                    2
//  
//#define LED3_PIN                                GPIO_PIN_8
//#define LED3_GPIO_PORT                          GPIOF
//#define LED3_GPIO_CLK_ENABLE()                  __GPIOF_CLK_ENABLE()  
//#define LED3_GPIO_CLK_DISABLE()                 __GPIOF_CLK_DISABLE()  


//#define LED4_PIN                                GPIO_PIN_9
//#define LED4_GPIO_PORT                          GPIOF
//#define LED4_GPIO_CLK_ENABLE()                  __GPIOF_CLK_ENABLE()  
//#define LED4_GPIO_CLK_DISABLE()                 __GPIOF_CLK_DISABLE()  

//#define LEDx_GPIO_CLK_ENABLE(__INDEX__)         (((__INDEX__) == 0) ? LED3_GPIO_CLK_ENABLE() : LED4_GPIO_CLK_ENABLE())
//#define LEDx_GPIO_CLK_DISABLE(__INDEX__)        (((__INDEX__) == 0) ? LED3_GPIO_CLK_DISABLE() : LED4_GPIO_CLK_DISABLE())


#define LED_RUN_PIN                             GPIO_PIN_9	//PF9
#define LED_PORT                                GPIOF
#define LED_GPIO_CLK_ENABLE()                   __GPIOF_CLK_ENABLE()  
#define LED_GPIO_CLK_DISABLE()                  __GPIOF_CLK_DISABLE()

#define LED_RUN_ON  														HAL_GPIO_WritePin(LED_PORT, LED_RUN_PIN, GPIO_PIN_RESET)
#define LED_RUN_OFF 														HAL_GPIO_WritePin(LED_PORT, LED_RUN_PIN, GPIO_PIN_SET)

/*##################### Infrared & RFU ####################################################################*/

//#define IO_RFU_PB0_PIN		                     	GPIO_PIN_0	//PB0
//#define IO_RFU_Infr_PIN                      		GPIO_PIN_1	//PB1
//#define IO_RFU_0_PORT                           GPIOB
//#define IO_RFU_0_GPIO_CLK_ENABLE()              __GPIOB_CLK_ENABLE()  
//#define IO_RFU_0_GPIO_CLK_DISABLE()             __GPIOB_CLK_DISABLE()

//#define IO_RFU_PF6_PIN		                      GPIO_PIN_6	//PF6
//#define IO_RFU_PF7_PIN		                      GPIO_PIN_7	//PF7
//#define IO_RFU_1_PORT                           GPIOF
//#define IO_RFU_1_GPIO_CLK_ENABLE()              __GPIOF_CLK_ENABLE()  
//#define IO_RFU_1_GPIO_CLK_DISABLE()             __GPIOF_CLK_DISABLE()

#define IO_INFRARED_TX_PIN                     GPIO_PIN_6	//PC6
#define IO_INFRARED_RX_PIN                     GPIO_PIN_7	//PC7
#define INFRARED_PORT                          GPIOC
#define INFRARED_GPIO_CLK_ENABLE()             __GPIOC_CLK_ENABLE()  
#define INFRARED_GPIO_CLK_DISABLE()            __GPIOC_CLK_DISABLE()

#define INFRARED_RUN_ON  											 HAL_GPIO_WritePin(INFRARED_PORT, IO_INFRARED_TX_PIN, GPIO_PIN_SET)
#define INFRARED_RUN_OFF 											 HAL_GPIO_WritePin(INFRARED_PORT, IO_INFRARED_TX_PIN, GPIO_PIN_RESET)

/*##################### DIO & DIN ####################################################################*/

#define DIO_IN1_PIN                             GPIO_PIN_11	//PD11
#define DIO_IN2_PIN                             GPIO_PIN_12	//PD12
#define DIO_IN3_PIN                             GPIO_PIN_13	//PD13
#define DIO_IN_PORT                             GPIOD
#define DIO_IN_GPIO_CLK_ENABLE()                __GPIOD_CLK_ENABLE()  
#define DIO_IN_GPIO_CLK_DISABLE()               __GPIOD_CLK_DISABLE()

#define DIO_IN_LOCK_PIN                         GPIO_PIN_8	//PI8
#define DIO_IN_LOCK_PORT                        GPIOI
#define DIO_IN_LOCK_GPIO_CLK_ENABLE()           __GPIOI_CLK_ENABLE()  
#define DIO_IN_LOCK_GPIO_CLK_DISABLE()          __GPIOI_CLK_DISABLE()

#define DIO_OUT1_PIN                            GPIO_PIN_2
#define DIO_OUT2_PIN                            GPIO_PIN_3
#define DIO_OUT3_PIN                            GPIO_PIN_9
#define DIO_OUT_PORT                            GPIOG
#define DIO_OUT_GPIO_CLK_ENABLE()               __GPIOG_CLK_ENABLE()  
#define DIO_OUT_GPIO_CLK_DISABLE()              __GPIOG_CLK_DISABLE()


#define DOUT_1_ON																HAL_GPIO_WritePin(DIO_OUT_PORT, DIO_OUT1_PIN, GPIO_PIN_SET) 
#define DOUT_1_OFF															HAL_GPIO_WritePin(DIO_OUT_PORT, DIO_OUT1_PIN, GPIO_PIN_RESET)
#define DOUT_2_ON																HAL_GPIO_WritePin(DIO_OUT_PORT, DIO_OUT2_PIN, GPIO_PIN_SET)
#define DOUT_2_OFF															HAL_GPIO_WritePin(DIO_OUT_PORT, DIO_OUT2_PIN, GPIO_PIN_RESET)
#define DOUT_3_ON																HAL_GPIO_WritePin(DIO_OUT_PORT, DIO_OUT3_PIN, GPIO_PIN_SET)
#define DOUT_3_OFF															HAL_GPIO_WritePin(DIO_OUT_PORT, DIO_OUT3_PIN, GPIO_PIN_RESET)


/*##################### KEY & LED ######################################################################*/

#define KEY_S1_PIN                              GPIO_PIN_0
#define KEY_S2_PIN                              GPIO_PIN_1
#define KEY_S3_PIN                              GPIO_PIN_2
#define KEY_S4_PIN                              GPIO_PIN_3
#define KEY_PORT                                GPIOB
#define KEY_GPIO_CLK_ENABLE()                   __GPIOB_CLK_ENABLE()  
#define KEY_GPIO_CLK_DISABLE()                  __GPIOB_CLK_DISABLE()
#define KEY_S1_EXTI                             EXTI0_IRQn
#define KEY_S1_INT_EXTIHandler                  EXTI0_IRQHandler
#define KEY_S1_INT_PREPRIO                      15
#define KEY_S2_EXTI                             EXTI1_IRQn
#define KEY_S2_INT_EXTIHandler                  EXTI1_IRQHandler
#define KEY_S2_INT_PREPRIO                      15
#define KEY_S3_EXTI                             EXTI2_IRQn
#define KEY_S3_INT_EXTIHandler                  EXTI2_IRQHandler
#define KEY_S3_INT_PREPRIO                      15
#define KEY_S4_EXTI                             EXTI3_IRQn
#define KEY_S4_INT_EXTIHandler                  EXTI3_IRQHandler
#define KEY_S4_INT_PREPRIO                      15

#define KEYLED_LCH_PIN                          GPIO_PIN_3	//PD7 
#define KEYLED_CTL_LCH_PORT                     GPIOD
#define KEYLED_CTL_LCH_GPIO_CLK_ENABLE()        __GPIOD_CLK_ENABLE()  
#define KEYLED_CTL_LCH_GPIO_CLK_DISABLE()       __GPIOD_CLK_DISABLE()

#define KEYLED_CLK_PIN                          GPIO_PIN_3	//PI3
#define KEYLED_DAT_PIN                          GPIO_PIN_11	//PI11
#define KEYLED_CTL_PORT                         GPIOI
#define KEYLED_CTL_GPIO_CLK_ENABLE()            __GPIOI_CLK_ENABLE()  
#define KEYLED_CTL_GPIO_CLK_DISABLE()           __GPIOI_CLK_DISABLE()


#define KL_CLK_H																HAL_GPIO_WritePin(KEYLED_CTL_PORT, KEYLED_CLK_PIN, GPIO_PIN_RESET)
#define KL_CLK_L																HAL_GPIO_WritePin(KEYLED_CTL_PORT, KEYLED_CLK_PIN, GPIO_PIN_SET)
#define KL_LCH_H																HAL_GPIO_WritePin(KEYLED_CTL_LCH_PORT, KEYLED_LCH_PIN, GPIO_PIN_RESET)
#define KL_LCH_L																HAL_GPIO_WritePin(KEYLED_CTL_LCH_PORT, KEYLED_LCH_PIN, GPIO_PIN_SET)
#define KL_DAT_H																HAL_GPIO_WritePin(KEYLED_CTL_PORT, KEYLED_DAT_PIN, GPIO_PIN_RESET)
#define KL_DAT_L																HAL_GPIO_WritePin(KEYLED_CTL_PORT, KEYLED_DAT_PIN, GPIO_PIN_SET)


#define KEYWHEEL_1_PIN                          GPIO_PIN_4	//PB4
#define KEYWHEEL_2_PIN                          GPIO_PIN_5	//PB5
#define KEYWHEEL_PORT                           GPIOB
#define KEYWHEEL_GPIO_CLK_ENABLE()              __GPIOB_CLK_ENABLE()  
#define KEYWHEEL_GPIO_CLK_DISABLE()             __GPIOB_CLK_DISABLE()
#define WHEELKEY_PIN                            GPIO_PIN_8	//PI8
#define WHEELKEY_PORT                           GPIOI
#define WHEELKEY_GPIO_CLK_ENABLE()              __GPIOI_CLK_ENABLE()  
#define WHEELKEY_GPIO_CLK_DISABLE()             __GPIOI_CLK_DISABLE()
#define WHEELKEY_INT_EXTI                       EXTI9_5_IRQn
#define WHEELKEY_INT_EXTIHandler                EXTI9_5_IRQHandler
#define WHEELKEY_INT_PREPRIO                    15

/*##################### USB #####################################################################*/

#define USBOTG_POWER_SW_PIN                     GPIO_PIN_4		// USB power switch
//#define USBOTG_POWER_OC_PIN                     GPIO_PIN_5		// over current limit
#define USBOTG_POWER_PORT                       GPIOC
#define USBOTG_POWER_GPIO_CLK_ENABLE()          __GPIOC_CLK_ENABLE()  
#define USBOTG_POWER_GPIO_CLK_DISABLE()         __GPIOC_CLK_DISABLE()

//#define USBOTG_POWER_OC_INT_EXTI                EXTI9_5_IRQn
//#define USBOTG_POWER_OC_INT_EXTIHandler         EXTI9_5_IRQHandler
//#define USBOTG_POWER_OC_INT_PREPRIO             15

#define USBOTG_FS_ID_PIN                        GPIO_PIN_12		// maybe not use
#define USBOTG_FS_VBUS_PIN                      GPIO_PIN_13
#define USBOTG_FS_DM_PIN                        GPIO_PIN_14
#define USBOTG_FS_DP_PIN                        GPIO_PIN_15
#define USBOTG_FS_PORT                          GPIOB
#define USBOTG_FS_GPIO_CLK_ENABLE()             __GPIOB_CLK_ENABLE()  
#define USBOTG_FS_GPIO_CLK_DISABLE()            __GPIOB_CLK_DISABLE()



/*##################### SDIO ####################################################################*/

#define SDIO_D0_PIN                             GPIO_PIN_8
#define SDIO_D1_PIN                             GPIO_PIN_9
#define SDIO_D2_PIN                             GPIO_PIN_10
#define SDIO_D3_PIN                             GPIO_PIN_11
#define SDIO_CK_PIN                             GPIO_PIN_12
#define SDIO_DETECT_PIN                         GPIO_PIN_13
#define SDIO_DAT_PORT                           GPIOC
#define SDIO_DAT_GPIO_CLK_ENABLE()              __GPIOC_CLK_ENABLE()  
#define SDIO_DAT_GPIO_CLK_DISABLE()             __GPIOC_CLK_DISABLE()

#define SDIO_CMD_PIN                            GPIO_PIN_2
#define SDIO_CMD_PORT                           GPIOD
#define SDIO_CMD_GPIO_CLK_ENABLE()              __GPIOD_CLK_ENABLE()  
#define SDIO_CMD_GPIO_CLK_DISABLE()             __GPIOD_CLK_DISABLE()


/*##################### FM24C64 - I2C ###########################################################*/

#define FM24C64_I2C_SCL_PIN                     GPIO_PIN_6
#define FM24C64_I2C_SDA_PIN                     GPIO_PIN_7
#define FM24C64_I2C_SCL_SDA_AF               		GPIO_AF4_I2C1
#define FM24C64_I2C_PORT                        GPIOB

#define FM24C64_I2C_CLOCK_ENABLE()           		__I2C1_CLK_ENABLE()
#define FM24C64_I2C_FORCE_RESET()            		__I2C1_FORCE_RESET()
#define FM24C64_I2C_RELEASE_RESET()          		__I2C1_RELEASE_RESET()
#define FM24C64_I2C_GPIO_CLK_ENABLE()           __GPIOB_CLK_ENABLE()  
#define FM24C64_I2C_GPIO_CLK_DISABLE()          __GPIOB_CLK_DISABLE()

/* Definition for IOE I2Cx's NVIC */
#define FM24C64_I2C_EV_IRQn                  		I2C1_EV_IRQn
#define FM24C64_I2C_ER_IRQn                  		I2C1_ER_IRQn

#define I2Cx_SPEED                          		100000	/* I2C clock speed configuration (in Hz) */
#define I2Cx_TIMEOUT_MAX                    		0x3000 	/*<! The value of the maximal timeout for I2C waiting loops */

#define FM24C64_I2C                          		I2C1
#define FM24C64_I2C_ADDRESS              				0xA0




/*##################### FM25V01 - SPI ###########################################################*/

//#define FM25V01_SPI_MISO_PIN                    GPIO_PIN_12
//#define FM25V01_SPI_SCK_PIN                     GPIO_PIN_13
//#define FM25V01_SPI_MOSI_PIN                    GPIO_PIN_14
//#define FM25V01_SPI_AF                       		GPIO_AF5_SPI6
//#define FM25V01_SPI_PORT                        GPIOG
//#define FM25V01_SPI_GPIO_CLK_ENABLE()           __GPIOG_CLK_ENABLE()  
//#define FM25V01_SPI_GPIO_CLK_DISABLE()          __GPIOG_CLK_DISABLE()

//#define FM25V01_SPI_CLK_ENABLE()             		__SPI6_CLK_ENABLE()
//#define FM25V01_SPI                          		SPI6

//#define FM25V01_SPI_NSS_PIN                     GPIO_PIN_15
//#define FM25V01_SPI_NSS_PORT                    GPIOA
//#define FM25V01_SPI_NSS_GPIO_CLK_ENABLE()       __GPIOA_CLK_ENABLE()  
//#define FM25V01_SPI_NSS_GPIO_CLK_DISABLE()      __GPIOA_CLK_DISABLE()


///* Maximum Timeout values for flags waiting loops. These timeouts are not based
//   on accurate values, they just guarantee that the application will not remain
//   stuck if the SPI communication is corrupted.
//   You may modify these timeout values depending on CPU frequency and application
//   conditions (interrupts routines ...). */   
//#define SPIx_TIMEOUT_MAX              ((uint32_t)0x1000)


//// FM25V10 Command Define
//#define FM25V_WREN			0x06	//Set Write Enable Latch 
//#define FM25V_WRDI			0x04	//Write Disable
//#define FM25V_RDSR			0x05	//Read Status Register
//#define FM25V_WRSR			0x01	//Write Status Register
//#define FM25V_READ			0x03	//Read Memory Data
//#define FM25V_FSTRD			0x0B	//Fast Read Memory Data
//#define FM25V_WRITE			0x02	//Write Memory Data
//#define FM25V_SLEEP			0xB9	//Enter Sleep Mode
//#define FM25V_RDID			0x9F	//Read Device ID
//#define FM25V_SNR				0xC3	//Read S/N


//#define FM25V_NSS_L()			HAL_GPIO_WritePin(FM25V01_SPI_NSS_PORT, FM25V01_SPI_NSS_PIN, GPIO_PIN_RESET)
//#define FM25V_NSS_H()			HAL_GPIO_WritePin(FM25V01_SPI_NSS_PORT, FM25V01_SPI_NSS_PIN, GPIO_PIN_SET)


/*##################### AD Control ##############################################################*/

#define AD_CTL_FindPoint_PIN										GPIO_PIN_8
#define AD_CTL_PORT                             GPIOF
#define AD_CTL_GPIO_CLK_ENABLE()                __GPIOF_CLK_ENABLE()  
#define AD_CTL_GPIO_CLK_DISABLE()               __GPIOF_CLK_DISABLE()

//#define AD_SIGNAL_VALUE_PIN                     GPIO_PIN_0

//#define AD_UART_TX_PIN                          GPIO_PIN_7
//#define AD_UART_RX_PIN                          GPIO_PIN_6
//#define AD_UART_PORT                            GPIOF
//#define AD_UART_GPIO_CLK_ENABLE()               __GPIOF_CLK_ENABLE()  
//#define AD_UART_GPIO_CLK_DISABLE()              __GPIOF_CLK_DISABLE()
//#define AD_UART_CLK_ENABLE()               			__UART7_CLK_ENABLE()


/* User can use this section to tailor ADCx instance used and associated 
   resources */
/* Definition for ADCx clock resources */
//#define ADCx                            ADC3
//#define ADCx_CLK_ENABLE()               __ADC3_CLK_ENABLE()
//#define DMAx_CLK_ENABLE()               __DMA2_CLK_ENABLE()     
//#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __GPIOC_CLK_ENABLE()
//     
//#define ADCx_FORCE_RESET()              __ADC_FORCE_RESET()
//#define ADCx_RELEASE_RESET()            __ADC_RELEASE_RESET()

///* Definition for ADCx Channel Pin */
//#define ADCx_CHANNEL_PIN                GPIO_PIN_0
//#define ADCx_CHANNEL_GPIO_PORT          GPIOC 

///* Definition for ADCx's Channel */
//#define ADCx_CHANNEL                    ADC_CHANNEL_10

///* Definition for ADCx's DMA */
//#define ADCx_DMA_CHANNEL                DMA_CHANNEL_2
//#define ADCx_DMA_STREAM                 DMA2_Stream1         

///* Definition for ADCx's NVIC */
//#define ADCx_DMA_IRQn                   DMA2_Stream1_IRQn
//#define ADCx_DMA_IRQHandler             DMA2_Stream1_IRQHandler


/*##################### USART 1_2_3_4 (_6) #######################################################*/

#define USARTn																	5

#define USART1_TX_PIN                           GPIO_PIN_9
#define USART1_RX_PIN                           GPIO_PIN_10
#define USART1_PORT                             GPIOA
#define USART1_GPIO_CLK_ENABLE()                __GPIOA_CLK_ENABLE()  
#define USART1_GPIO_CLK_DISABLE()               __GPIOA_CLK_DISABLE()
#define USART1_CLK_ENABLE()               		__USART1_CLK_ENABLE()

/* Definition for USAR1's DMA */
#define USART1_TX_DMA_CHANNEL                   DMA_CHANNEL_4
#define USART1_TX_DMA_STREAM                    DMA2_Stream7         
#define USART1_RX_DMA_CHANNEL                   DMA_CHANNEL_4
#define USART1_RX_DMA_STREAM                    DMA2_Stream5

/* Definition for USARTx's NVIC */
#define USART1_DMA_TX_IRQn                      DMA2_Stream7_IRQn
#define USART1_DMA_RX_IRQn                      DMA2_Stream5_IRQn
#define USART1_DMA_TX_IRQHandler                DMA2_Stream7_IRQHandler
#define USART1_DMA_RX_IRQHandler                DMA2_Stream5_IRQHandler
#define USART1_IRQn                             USART1_IRQn
#define USART1_IRQHandler                       USART1_IRQHandler

#define USART2_TX_PIN                           GPIO_PIN_2
#define USART2_RX_PIN                           GPIO_PIN_3
#define USART2_PORT                             GPIOA
#define USART2_GPIO_CLK_ENABLE()                __GPIOA_CLK_ENABLE()  
#define USART2_GPIO_CLK_DISABLE()               __GPIOA_CLK_DISABLE()
#define USART2_CLK_ENABLE()               		__USART2_CLK_ENABLE()

#define USART3_TX_PIN                           GPIO_PIN_10
#define USART3_RX_PIN                           GPIO_PIN_11
#define USART3_PORT                             GPIOB
#define USART3_GPIO_CLK_ENABLE()                __GPIOB_CLK_ENABLE()  
#define USART3_GPIO_CLK_DISABLE()               __GPIOB_CLK_DISABLE()
#define USART3_CLK_ENABLE()               		__USART3_CLK_ENABLE()

#define UART4_TX_PIN                            GPIO_PIN_0
#define UART4_RX_PIN                            GPIO_PIN_1
#define UART4_PORT                              GPIOA
#define UART4_GPIO_CLK_ENABLE()                 __GPIOA_CLK_ENABLE()  
#define UART4_GPIO_CLK_DISABLE()                __GPIOA_CLK_DISABLE()
#define UART4_CLK_ENABLE()               		__UART4_CLK_ENABLE()

#define USART6_TX_PIN                           GPIO_PIN_6
#define USART6_RX_PIN                           GPIO_PIN_7
#define USART6_PORT                             GPIOC
#define USART6_GPIO_CLK_ENABLE()                __GPIOC_CLK_ENABLE()  
#define USART6_GPIO_CLK_DISABLE()               __GPIOC_CLK_DISABLE()
#define USART6_CLK_ENABLE()               		__USART6_CLK_ENABLE()
//------------------------------------------------------------------------
//#define PowerSW_Audio_PIN                       GPIO_PIN_2	// PH2
//#define PowerSW_WireLess_PIN                    GPIO_PIN_3	// PH3 
//#define PowerSW_PORT                          	GPIOH
//#define PowerSW_GPIO_CLK_ENABLE()             	__GPIOH_CLK_ENABLE()  
//#define PowerSW_GPIO_CLK_DISABLE()            	__GPIOH_CLK_DISABLE()


#define BSP_UartAudio_PowerON()                 HAL_GPIO_WritePin(PowerSW_PORT, PowerSW_Audio_PIN, GPIO_PIN_SET)
#define BSP_UartAudio_PowerOFF()                HAL_GPIO_WritePin(PowerSW_PORT, PowerSW_Audio_PIN, GPIO_PIN_RESET)
#define BSP_UartNRF_PowerON()                   HAL_GPIO_WritePin(PowerSW_PORT, PowerSW_WireLess_PIN, GPIO_PIN_SET)
#define BSP_UartNRF_PowerOFF()                  HAL_GPIO_WritePin(PowerSW_PORT, PowerSW_WireLess_PIN, GPIO_PIN_RESET)


#define UART_COM1                               USART1
#define UART_24GHz                              USART2 
#define UART_COM2                               USART3 
#define UART_AUDIO                              UART4 
#define UART_Infr                               USART6 
//#define UART_AD                               UART7 



/*##################### LCD ##################################################################*/

/* +------------------------+-----------------------+----------------------------+
   +                       LCD pins assignment                                   +
   +------------------------+-----------------------+----------------------------+
   |  LCD_TFT R2 <-> PH.08  |  LCD_TFT G2 <-> PH.13 |  LCD_TFT B2 <-> PG.10      |
   |  LCD_TFT R3 <-> PH.09  |  LCD_TFT G3 <-> PH.14 |  LCD_TFT B3 <-> PG.11      |
   |  LCD_TFT R4 <-> PH.10  |  LCD_TFT G4 <-> PH.15 |  LCD_TFT B4 <-> PI.04      |
   |  LCD_TFT R5 <-> PH.11  |  LCD_TFT G5 <-> PI.00 |  LCD_TFT B5 <-> PI.05      |
   |  LCD_TFT R6 <-> PH.12  |  LCD_TFT G6 <-> PI.01 |  LCD_TFT B6 <-> PI.06      |
   |  LCD_TFT R7 <-> PG.06  |  LCD_TFT G7 <-> PI.02 |  LCD_TFT B7 <-> PI.07      |
   -------------------------------------------------------------------------------
            |  LCD_TFT HSYNC <-> PI.10  | LCDTFT VSYNC <->  PI.09 |
            |  LCD_TFT PCLK  <-> PG.07  | LCD_TFT DE   <->  PF.10 |
             -----------------------------------------------------    */

/** 
  * @brief  LCD Control pin  
  */ 
#define LCD_PWM_PIN                GPIO_PIN_8
#define LCD_PWM_GPIO_PORT          GPIOB
#define LCD_PWM_GPIO_CLK_ENABLE()  __GPIOB_CLK_ENABLE()
#define LCD_PWM_GPIO_CLK_DISABLE() __GPIOB_CLK_DISABLE()
  
#define LCD_DISP_PIN                GPIO_PIN_9
#define LCD_DISP_GPIO_PORT          GPIOB
#define LCD_DISP_GPIO_CLK_ENABLE()  __GPIOB_CLK_ENABLE()
#define LCD_DISP_GPIO_CLK_DISABLE() __GPIOB_CLK_DISABLE()

/* Set PWM */
#define LCD_PWM_LOW()      HAL_GPIO_WritePin(LCD_PWM_GPIO_PORT, LCD_PWM_PIN, GPIO_PIN_RESET)
#define LCD_PWM_HIGH()     HAL_GPIO_WritePin(LCD_PWM_GPIO_PORT, LCD_PWM_PIN, GPIO_PIN_SET)

/* Set DISP */
#define LCD_DISP_OFF()     HAL_GPIO_WritePin(LCD_DISP_GPIO_PORT, LCD_DISP_PIN, GPIO_PIN_RESET)
#define LCD_DISP_ON()      HAL_GPIO_WritePin(LCD_DISP_GPIO_PORT, LCD_DISP_PIN, GPIO_PIN_SET)



/*##################### SDRAM ######################################################################*/

/*-- GPIOs Configuration -----------------------------------------------------*/
/*
 +-------------------+--------------------+--------------------+--------------------+
 +                       SDRAM pins assignment                                      +
 +-------------------+--------------------+--------------------+--------------------+
 | PD0  <-> FMC_D2   | PE0  <-> FMC_NBL0  | PF0  <-> FMC_A0    | PG0  <-> FMC_A10   |
 | PD1  <-> FMC_D3   | PE1  <-> FMC_NBL1  | PF1  <-> FMC_A1    | PG1  <-> FMC_A11   |
 | PD8  <-> FMC_D13  | PE7  <-> FMC_D4    | PF2  <-> FMC_A2    | PG4  <-> FMC_BA0   |
 | PD9  <-> FMC_D14  | PE8  <-> FMC_D5    | PF3  <-> FMC_A3    | PG5  <-> FMC_BA1   |
 | PD10 <-> FMC_D15  | PE9  <-> FMC_D6    | PF4  <-> FMC_A4    | PG8  <-> FMC_SDCLK |
 | PD14 <-> FMC_D0   | PE10 <-> FMC_D7    | PF5  <-> FMC_A5    | PG15 <-> FMC_NCAS  |  
 | PD15 <-> FMC_D1   | PE11 <-> FMC_D8    | PF11 <-> FMC_NRAS  |--------------------+  
 +-------------------| PE12 <-> FMC_D9    | PF12 <-> FMC_A6    | 
                     | PE13 <-> FMC_D10   | PF13 <-> FMC_A7    |    
                     | PE14 <-> FMC_D11   | PF14 <-> FMC_A8    |
                     | PE15 <-> FMC_D12   | PF15 <-> FMC_A9    |
 +-------------------+--------------------+--------------------+
 | PH7 <-> FMC_SDCKE1| 
 | PH6 <-> FMC_SDNE1 | 
 | PH5 <-> FMC_SDNWE |
 +-------------------+  */



/*##################### END ######################################################################*/




/**
  * @}
  */ 


/*##################### GYRO ##########################*/
/* Read/Write command */
//#define READWRITE_CMD              ((uint8_t)0x80) 
///* Multiple byte read/write command */ 
//#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
///* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
//#define DUMMY_BYTE                 ((uint8_t)0x00)

///* Chip Select macro definition */
//#define GYRO_CS_LOW()       HAL_GPIO_WritePin(GYRO_CS_GPIO_PORT, GYRO_CS_PIN, GPIO_PIN_RESET)
//#define GYRO_CS_HIGH()      HAL_GPIO_WritePin(GYRO_CS_GPIO_PORT, GYRO_CS_PIN, GPIO_PIN_SET)

///**
//  * @brief  GYRO SPI Interface pins
//  */
//#define GYRO_CS_PIN                    GPIO_PIN_1                  /* PC.01 */
//#define GYRO_CS_GPIO_PORT              GPIOC                       /* GPIOC */
//#define GYRO_CS_GPIO_CLK_ENABLE()      __GPIOC_CLK_ENABLE()
//#define GYRO_CS_GPIO_CLK_DISABLE()     __GPIOC_CLK_DISABLE()

//#define GYRO_INT_GPIO_CLK_ENABLE()         __GPIOA_CLK_ENABLE()
//#define GYRO_INT_GPIO_CLK_DISABLE()        __GPIOA_CLK_DISABLE()
//#define GYRO_INT_GPIO_PORT                 GPIOA                       /* GPIOA */
//#define GYRO_INT1_PIN                      GPIO_PIN_1                  /* PA.01 */
//#define GYRO_INT1_EXTI_IRQn                EXTI1_IRQn 
//#define GYRO_INT2_PIN                      GPIO_PIN_2                  /* PA.02 */
//#define GYRO_INT2_EXTI_IRQn                EXTI2_IRQn 
/**
  * @}
  */ 


/** @addtogroup STM32F429I_DISCOVERY LOW_LEVEL_I2C_EE
  * @{
  */
/**
  * @brief  I2C EEPROM Interface pins
  */
#define EEPROM_I2C_DMA                          DMA1   
#define EEPROM_I2C_DMA_CHANNEL                  DMA_CHANNEL_3
#define EEPROM_I2C_DMA_STREAM_TX                DMA1_Stream4
#define EEPROM_I2C_DMA_STREAM_RX                DMA1_Stream2
#define EEPROM_I2C_DMA_CLK_ENABLE()             __DMA1_CLK_ENABLE()
   
#define EEPROM_I2C_DMA_TX_IRQn                  DMA1_Stream4_IRQn
#define EEPROM_I2C_DMA_RX_IRQn                  DMA1_Stream2_IRQn
#define EEPROM_I2C_DMA_TX_IRQHandler            DMA1_Stream4_IRQHandler
#define EEPROM_I2C_DMA_RX_IRQHandler            DMA1_Stream2_IRQHandler
#define EEPROM_I2C_DMA_PREPRIO                  0


/** @defgroup STM32F429I_DISCOVERY LOW_LEVEL_Exported_Functions
  * @{
  */
uint32_t  BSP_GetVersion(void);  
//void      BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
//uint32_t  BSP_PB_GetState(Button_TypeDef Button);
void Infra_pwm_Init(void);
void Infra_PWM_ON(void);
void Infra_PWM_OFF(void);


/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F429I_DISCOVERY_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
