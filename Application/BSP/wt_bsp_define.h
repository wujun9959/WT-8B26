/**
  ******************************************************************************
  * @file    wt_bsp_define.h
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
#ifndef __WT_BSP_DEFINE_H
#define __WT_BSP_DEFINE_H

#ifdef __cplusplus
 extern "C" {
#endif
                                              
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"



/*###########################################################################################*/

/** 
  * @brief  LZY Wire Tester Pin Define 
  */ 

/*##################### LED Run ######################################################################*/

#define LED_RUN_PIN                             GPIO_PIN_9	//PF9
#define LED_PORT                                GPIOF
#define LED_GPIO_CLK_ENABLE()                   __GPIOF_CLK_ENABLE()  
#define LED_GPIO_CLK_DISABLE()                  __GPIOF_CLK_DISABLE()

#define LED_RUN_ON  														HAL_GPIO_WritePin(LED_PORT, LED_RUN_PIN, GPIO_PIN_RESET)
#define LED_RUN_OFF 														HAL_GPIO_WritePin(LED_PORT, LED_RUN_PIN, GPIO_PIN_SET)

/*##################### Infrared & RFU ####################################################################*/

#define IO_RFU_PB0_PIN		                     	GPIO_PIN_0	//PB0
#define IO_RFU_Infr_PIN                      		GPIO_PIN_1	//PB1
#define IO_RFU_0_PORT                           GPIOB
#define IO_RFU_0_GPIO_CLK_ENABLE()              __GPIOB_CLK_ENABLE()  
#define IO_RFU_0_GPIO_CLK_DISABLE()             __GPIOB_CLK_DISABLE()

#define IO_RFU_PF6_PIN		                      GPIO_PIN_6	//PF6
#define IO_RFU_PF7_PIN		                      GPIO_PIN_7	//PF7
#define IO_RFU_1_PORT                           GPIOF
#define IO_RFU_1_GPIO_CLK_ENABLE()              __GPIOF_CLK_ENABLE()  
#define IO_RFU_1_GPIO_CLK_DISABLE()             __GPIOF_CLK_DISABLE()

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

#define KEYLED_DAT0_PIN                         GPIO_PIN_2
#define KEYLED_DAT1_PIN                         GPIO_PIN_3
#define KEYLED_DAT2_PIN                         GPIO_PIN_4
#define KEYLED_DATx_PORT                        GPIOH
#define KEYLED_DATx_GPIO_CLK_ENABLE()           __GPIOH_CLK_ENABLE()  
#define KEYLED_DATx_GPIO_CLK_DISABLE()          __GPIOH_CLK_DISABLE()

#define KEYLED_LCH_PIN                          GPIO_PIN_3	//PD3
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
#define KEYWHEEL_1_INT_EXTI                     EXTI3_IRQn
#define KEYWHEEL_1_INT_EXTIHandler              EXTI3_IRQHandler
#define KEYWHEEL_1_INT_PREPRIO                  15
#define KEYWHEEL_2_INT_EXTI                     EXTI4_IRQn
#define KEYWHEEL_2_INT_EXTIHandler              EXTI4_IRQHandler
#define KEYWHEEL_2_INT_PREPRIO                  15

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

/* Definition for DACx clock resources */
#define DAC_OUT                            DAC
#define DAC_OUT_CLK_ENABLE()               __HAL_RCC_DAC_CLK_ENABLE()
#define DAC_OUT_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

#define DAC_OUT_FORCE_RESET()              __HAL_RCC_DAC_FORCE_RESET()
#define DAC_OUT_RELEASE_RESET()            __HAL_RCC_DAC_RELEASE_RESET()

#define DAC_OUT1_PIN                            GPIO_PIN_4
#define DAC_OUT2_PIN                            GPIO_PIN_5

#define DAC_OUT_PORT                            GPIOA
#define DAC_OUT_GPIO_CLK_ENABLE()               __GPIOA_CLK_ENABLE()  
#define DAC_OUT_GPIO_CLK_DISABLE()              __GPIOA_CLK_DISABLE()

/* Definition for ADCx's Channel */
#define DAC_OUT1_CHANNEL                    DAC_CHANNEL_1
#define DAC_OUT2_CHANNEL                    DAC_CHANNEL_2

/*##################### AD Control ##############################################################*/

#define AD_CTL_FindPoint_PIN										GPIO_PIN_8
#define AD_CTL_PORT                             GPIOF
#define AD_CTL_GPIO_CLK_ENABLE()                __GPIOF_CLK_ENABLE()  
#define AD_CTL_GPIO_CLK_DISABLE()               __GPIOF_CLK_DISABLE()

//#define AD_SIGNAL_VALUE_PIN                     GPIO_PIN_0
#define AD_LOGIC_COMPARE1_PIN                   GPIO_PIN_1
#define AD_LOGIC_COMPARE2_PIN                   GPIO_PIN_2
#define AD_SIGNAL_PORT                          GPIOC
#define AD_SIGNAL_GPIO_CLK_ENABLE()             __GPIOC_CLK_ENABLE()  
#define AD_SIGNAL_GPIO_CLK_DISABLE()            __GPIOC_CLK_DISABLE()

//#define AD_SIGNAL_VALUE_PIN                     GPIO_PIN_0
//#define AD_SIGNAL_V01_PIN                       GPIO_PIN_1
//#define AD_SIGNAL_V10_PIN                       GPIO_PIN_2
//#define AD_SIGNAL_SBD_PIN                       GPIO_PIN_3
//#define AD_SIGNAL_PORT                          GPIOC
//#define AD_SIGNAL_GPIO_CLK_ENABLE()             __GPIOC_CLK_ENABLE()  
//#define AD_SIGNAL_GPIO_CLK_DISABLE()            __GPIOC_CLK_DISABLE()

//#define AD_UART_TX_PIN                          GPIO_PIN_7
//#define AD_UART_RX_PIN                          GPIO_PIN_6
//#define AD_UART_PORT                            GPIOF
//#define AD_UART_GPIO_CLK_ENABLE()               __GPIOF_CLK_ENABLE()  
//#define AD_UART_GPIO_CLK_DISABLE()              __GPIOF_CLK_DISABLE()
//#define AD_UART_CLK_ENABLE()               			__UART7_CLK_ENABLE()


/*##################### Board Switch Control ##############################################################*/

#define TEST_BOARD_A0_PIN						   GPIO_PIN_3
#define TEST_BOARD_A1_PIN						   GPIO_PIN_5
#define TEST_BOARD_CTL_PORT                        GPIOC
#define BOARD_CTL_GPIO_CLK_ENABLE()                __GPIOC_CLK_ENABLE()  
#define BOARD_CTL_GPIO_CLK_DISABLE()               __GPIOC_CLK_DISABLE()

#define BROAD_A0_CTL_H							   HAL_GPIO_WritePin(TEST_BOARD_CTL_PORT, TEST_BOARD_A0_PIN, GPIO_PIN_SET)
#define BROAD_A0_CTL_L							   HAL_GPIO_WritePin(TEST_BOARD_CTL_PORT, TEST_BOARD_A0_PIN, GPIO_PIN_RESET)
#define BROAD_A1_CTL_H							   HAL_GPIO_WritePin(TEST_BOARD_CTL_PORT, TEST_BOARD_A1_PIN, GPIO_PIN_SET)
#define BROAD_A1_CTL_L							   HAL_GPIO_WritePin(TEST_BOARD_CTL_PORT, TEST_BOARD_A1_PIN, GPIO_PIN_RESET)


/*##################### CC2PC Control ##############################################################*/
#define PS_MOSI_RST_PIN                                 GPIO_PIN_3	
#define PS_MOSI_RST_PORT                                GPIOE
#define PS_MOSIRST_GPIO_CLK_ENABLE()         			__GPIOE_CLK_ENABLE()  
#define PS_MOSIRST_GPIO_CLK_DISABLE()        			__GPIOE_CLK_DISABLE()

#define PS_MOSI_INC_OUT_PIN                             GPIO_PIN_4
#define PS_MOSI_INC_OUT_PORT                      		GPIOH
#define PS_MOSI_INC_OUT_GPIO_CLK_ENABLE()         		__GPIOH_CLK_ENABLE()  
#define PS_MOSI_INC_OUT_GPIO_CLK_DISABLE()        		__GPIOH_CLK_DISABLE()

#define PS_MOSI_INC_IN_PIN                              GPIO_PIN_8
#define PS_MOSI_INC_IN_PORT                      		GPIOF
#define PS_MOSI_INC_IN_GPIO_CLK_ENABLE()         		__GPIOF_CLK_ENABLE()  
#define PS_MOSI_INC_IN_GPIO_CLK_DISABLE()        		__GPIOF_CLK_DISABLE()

#define PS_MISO_ACK1_PIN                                GPIO_PIN_4
#define PS_MISO_ACK2_PIN                                GPIO_PIN_5
#define PS_MISO_ACK3_PIN                                GPIO_PIN_6
#define PS_MISO_ACK4_PIN                                GPIO_PIN_7
#define PS_MISO_ACK_PORT                      		    GPIOD
#define PS_MISO_ACK_GPIO_CLK_ENABLE()         		    __GPIOD_CLK_ENABLE()  
#define PS_MISO_ACK_GPIO_CLK_DISABLE()        		    __GPIOD_CLK_DISABLE()

#define MISO_ACK1_EXTI                                  EXTI9_5_IRQn
#define MISO_ACK1_INT_EXTIHandler                       EXTI9_5_IRQHandler
#define MISO_ACK1_INT_PREPRIO                           14

#define MISO_ACK2_EXTI                                  EXTI4_IRQn
#define MISO_ACK2_INT_EXTIHandler                       EXTI4_IRQHandler
#define MISO_ACK2_INT_PREPRIO                           14

#define MISO_ACK3_EXTI                                  EXTI9_5_IRQn
#define MISO_ACK3_INT_EXTIHandler                       EXTI9_5_IRQHandler
#define MISO_ACK3_INT_PREPRIO                           14

#define MISO_ACK4_EXTI                                  EXTI9_5_IRQn
#define MISO_ACK4_INT_EXTIHandler                       EXTI9_5_IRQHandler
#define MISO_ACK4_INT_PREPRIO                           14
    
#define PS_MOSI_RST_H								    HAL_GPIO_WritePin(PS_MOSI_RST_PORT, PS_MOSI_RST_PIN, GPIO_PIN_SET)
#define PS_MOSI_RST_L					                HAL_GPIO_WritePin(PS_MOSI_RST_PORT, PS_MOSI_RST_PIN, GPIO_PIN_RESET)
#define PS_MOSI_INC_OUT_H				    			HAL_GPIO_WritePin(PS_MOSI_INC_OUT_PORT, PS_MOSI_INC_OUT_PIN, GPIO_PIN_SET)
#define PS_MOSI_INC_OUT_L			                	HAL_GPIO_WritePin(PS_MOSI_INC_OUT_PORT, PS_MOSI_INC_OUT_PIN, GPIO_PIN_RESET)
#define PS_MOSI_INC_IN_H				    			HAL_GPIO_WritePin(PS_MOSI_INC_IN_PORT, PS_MOSI_INC_IN_PIN, GPIO_PIN_SET)
#define PS_MOSI_INC_IN_L			            		HAL_GPIO_WritePin(PS_MOSI_INC_IN_PORT, PS_MOSI_INC_IN_PIN, GPIO_PIN_RESET)

//----------------------------------------------------------------------------
/* User can use this section to tailor ADCx instance used and associated 
   resources */
/* Definition for ADCx clock resources */
#define ADCx                            ADC1
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE();
#define DMAx_CLK_ENABLE()               __DMA2_CLK_ENABLE()     
#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE();
     
#define ADCx_FORCE_RESET()              __ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __ADC_RELEASE_RESET()

/* Definition for ADCx Channel Pin */
#define ADCx_CHANNEL_PIN                GPIO_PIN_0
#define ADCx_CHANNEL_GPIO_PORT          GPIOC 

/* Definition for ADCx's Channel */
#define ADCx_CHANNEL                    ADC_CHANNEL_10

/* Definition for ADCx's DMA */
#define ADCx_DMA_CHANNEL                DMA_CHANNEL_2
#define ADCx_DMA_STREAM                 DMA2_Stream1         

/* Definition for ADCx's NVIC */
#define ADCx_DMA_IRQn                   DMA2_Stream1_IRQn
#define ADCx_DMA_IRQHandler             DMA2_Stream1_IRQHandler

#define ADCx_IRQn                      ADC_IRQn


/*##################### USART 1_2_3_4 (_6) #######################################################*/

#define USARTn																	5

#define USART1_TX_PIN                           GPIO_PIN_9
#define USART1_RX_PIN                           GPIO_PIN_10
#define USART1_PORT                             GPIOA
#define USART1_GPIO_CLK_ENABLE()                __GPIOA_CLK_ENABLE()  
#define USART1_GPIO_CLK_DISABLE()               __GPIOA_CLK_DISABLE()
#define USART1_CLK_ENABLE()               		__USART1_CLK_ENABLE()

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
#define PowerSW_Audio_PIN                       GPIO_PIN_3	// PH3
#define PowerSW_WireLess_PIN                    GPIO_PIN_2	// PH2 
#define PowerSW_PORT                          	GPIOH
#define PowerSW_GPIO_CLK_ENABLE()             	__GPIOH_CLK_ENABLE()  
#define PowerSW_GPIO_CLK_DISABLE()            	__GPIOH_CLK_DISABLE()

#define RST_WIFI_PIN                            GPIO_PIN_7	// PA7 
#define RST_WIFI_PORT                          	GPIOA
#define RST_WIFI_GPIO_CLK_ENABLE()             	__GPIOA_CLK_ENABLE()  
#define RST_WIFI_GPIO_CLK_DISABLE()            	__GPIOA_CLK_DISABLE()
#define RST_WIFI_ON()                           HAL_GPIO_WritePin(RST_WIFI_PORT, RST_WIFI_PIN, GPIO_PIN_SET)
#define RST_WIFI_OFF()                          HAL_GPIO_WritePin(RST_WIFI_PORT, RST_WIFI_PIN, GPIO_PIN_RESET)


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


/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __WT_BSP_DEFINE_H */
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
