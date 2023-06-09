/*
 ******************************************************************************
 * @file           : RCC_Interface.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Register File
 * @version        : 1.0.1
 * @Date           : Apr 10, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 */

#ifndef RCC_RCC_INTERFACE_H_
#define RCC_RCC_INTERFACE_H_
/* ------------------------------------------------------------------------------------- */
/* ------------------------------- DEFINES SECTION START ------------------------------- */
/* ------------------------------------------------------------------------------------- */

/* AHB Peripherals */
#define SDIO_CLK    10
#define FSMC_CLK     8
#define CRC_CLK      6
#define FLITF_CLK    4
#define SRAM_CLK     2
#define DMA2_CLK     1
#define DMA1_CLK     0

/* APB1 Peripherals */
#define DAC_CLK     29
#define PWR_CLK     28
#define BKP_CLK     27
#define CAN_CLK     25
#define USB_CLK     23
#define I2C2_CLK    22
#define I2C1_CLK    21
#define UART5_CLK   20
#define UART4_CLK   19
#define USART3_CLK  18
#define USART2_CLK  17
#define SPI3_CLK    15
#define SPI2_CLK    14
#define WWDG_CLK    11
#define TIM14_CLK    8
#define TIM13_CLK    7
#define TIM12_CLK    6
#define TIM7_CLK     5
#define TIM6_CLK     4
#define TIM5_CLK     3
#define TIM4_CLK     2
#define TIM3_CLK     1
#define TIM2_CLK     0

/* ABP2 Peripherals */
#define TIM11_CLK   21
#define TIM10_CLK   20
#define TIM9_CLK    19
#define ADC3_CLK    15
#define USART1_CLK  14
#define TIM8_CLK    13
#define SPI1_CLK    12
#define TIM1_CLK    11
#define ADC2_CLK    10
#define ADC1_CLK     9
#define IOPG_CLK     8
#define IOPF_CLK     7
#define IOPE_CLK     6
#define IOPD_CLK     5
#define IOPC_CLK     4
#define IOPB_CLK     3
#define IOPA_CLK     2
#define AFIO_CLK     0

/* PLL SRC Options */
#define PLL_SRC_HSE                1
#define PLL_SRC_HSI_DIVIDE_BY_2    0


/* PLL Multiplication Factor Options */
#define PLL_MUL_FACTOR_2     0b0000
#define PLL_MUL_FACTOR_3     0b0001
#define PLL_MUL_FACTOR_4     0b0010
#define PLL_MUL_FACTOR_5     0b0011
#define PLL_MUL_FACTOR_6     0b0100
#define PLL_MUL_FACTOR_7     0b0101
#define PLL_MUL_FACTOR_8     0b0110
#define PLL_MUL_FACTOR_9     0b0111
#define PLL_MUL_FACTOR_10    0b1000
#define PLL_MUL_FACTOR_11    0b1001
#define PLL_MUL_FACTOR_12    0b1010
#define PLL_MUL_FACTOR_13    0b1011
#define PLL_MUL_FACTOR_14    0b1100
#define PLL_MUL_FACTOR_15    0b1101
#define PLL_MUL_FACTOR_16    0b1110

/* HSEConfig Struct Options */
#define HSE_DIVIDE_BY_2     1
#define HSE_DIVIDE_BY_1     0

#define HSE_BYPASSED        1
#define HSE_NOTBYPASSED     0

/* ----------------------------------------------------------------------------------- */
/* ------------------------------- DEFINES SECTION END ------------------------------- */
/* ----------------------------------------------------------------------------------- */


/* ----------------------------------------------------------------------------------------------------- */
/* ------------------------------- USER DEFINED DATA TYPES SECTION START ------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */

/* HSE Configurations Struct */
typedef struct
{
	uint8_t HSE_Divider ;
	uint8_t HSE_ByPass ;
}RCC_HSEConfigStructure;


/* Erorr Status Enum */
typedef enum
{
	TimeoutError,
	OK,
	PLLMULFactorError,
	PLLSRCError,
	AHBPeripheralError,
	APB1PeripheralError,
	APB2PeripheralError,

}RCC_ErrorStatus;


/* Clock Type Enum  */
typedef enum
{
	HSI,
	HSE,
	PLL

}RCC_Clk_Type;


/* Clock Status Enum */
typedef enum
{
	OFF,
	ON

}RCC_Clk_Status;

/* ----------------------------------------------------------------------------------------------------- */
/* ------------------------------- USER DEFINED DATA TYPES SECTION END  -------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */



/* ---------------------------------------------------------------------------------------- */
/* ------------------------------- PROTOTYPES SECTION START ------------------------------- */
/* ---------------------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------ */
/* ----------------      NAME     : RCC_SetClkStatus                			      ----------------- */
/* ----------------      FUNCTION : Set ClK Status       		                      ----------------- */
/* ----------------      ARGUMENT : CLK TYPE ( enum ) , CLK Status ( enum )		      ----------------- */
/* ----------------                  1- HSE                 1- OFF                            ----------------- */
/* ----------------                  2- HSI                 2- ON                             ----------------- */
/* ----------------                  3- PLL                                                   ----------------- */
/* ----------------      RETURN   : Erorr Status( TimeOut Indication )                        ----------------- */
/* ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------ */
RCC_ErrorStatus RCC_SetClkStatus( RCC_Clk_Type Copy_eClktype , RCC_Clk_Status Copy_eClkStatus ) ;



/* ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------ */
/* ----------------      NAME     : RCC_SetSYSCLK                			      ----------------- */
/* ----------------      FUNCTION : SET SYSCLK      		                              ----------------- */
/* ----------------      ARGUMENT : CLK TYPE ( enum )                       	              ----------------- */
/* ----------------                  1- HSE                                                   ----------------- */
/* ----------------                  2- HSI                                                   ----------------- */
/* ----------------                  3- PLL                                                   ----------------- */
/* ----------------      RETURN   : Void                                                      ----------------- */
/* ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------ */
void RCC_SetSYSCLK( RCC_Clk_Type Copy_eClkType ) ;



/* NOTE:
 *       Must Be Called While HSE is Disabled( OFF )
 */

/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_HSEConfig                			     	 ----------------- */
/* ----------------      FUNCTION : SET HSE Configuration        		                 ----------------- */
/* ----------------      ARGUMENT : HSEConfig ( Structure )                       	         ----------------- */
/* ----------------                  1- HSE_Divider  --> ( HSE_DIVIDE_BY_1  , HSE_DIVIDE_BY_2 )  ----------------- */
/* ----------------                  2- HSI_BYPASS   --> ( HSE_BYPASSED , HSE_NOTBYPASSED )      ----------------- */
/* ----------------      RETURN   : Void    					  		 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
void RCC_HSEConfig ( RCC_HSEConfigStructure * Copy_sHSEConfig ) ;



/* NOTE:
 *       Must Be Called While PLL is Disabled( OFF )
 */

/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_PLLConfig                			         ----------------- */
/* ----------------      FUNCTION : SET PLL Configuration        		                 ----------------- */
/* ----------------      ARGUMENT : PLLMULFactor     ,            PLL SRC                        ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- PLL_MUL_FACTOR_2         01- PLL_SRC_HSE                  ----------------- */
/* ----------------                02- PLL_MUL_FACTOR_3         02- PLL_SRC_HSI_DIVIDE_BY_2      ----------------- */
/* ----------------                03- PLL_MUL_FACTOR_4                                          ----------------- */
/* ----------------                04- PLL_MUL_FACTOR_5                                          ----------------- */
/* ----------------                05- PLL_MUL_FACTOR_6                                          ----------------- */
/* ----------------                06- PLL_MUL_FACTOR_7                                          ----------------- */
/* ----------------                07- PLL_MUL_FACTOR_8                                          ----------------- */
/* ----------------                08- PLL_MUL_FACTOR_9                                          ----------------- */
/* ----------------                09- PLL_MUL_FACTOR_10                                         ----------------- */
/* ----------------                10- PLL_MUL_FACTOR_11				         ----------------- */
/* ----------------                11- PLL_MUL_FACTOR_12                                         ----------------- */
/* ----------------                12- PLL_MUL_FACTOR_13                                         ----------------- */
/* ----------------                13- PLL_MUL_FACTOR_14                                         ----------------- */
/* ----------------                14- PLL_MUL_FACTOR_15                                         ----------------- */
/* ----------------                15- PLL_MUL_FACTOR_16                                         ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_PLLConfig ( uint8_t Copy_uint8PLLMulFactor , uint8_t Copy_uint8PLLSrc ) ;



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_AHBEnableCLK                			     	 ----------------- */
/* ----------------      FUNCTION : Enable CLK on an AHB Peripheral    		                 ----------------- */
/* ----------------      ARGUMENT : AHB Peripheral to Enable                                     ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                       01- SDIO_CLK        					 ----------------- */
/* ----------------                       02- FSMC_CLK          			         ----------------- */
/* ----------------                       03- CRC_CLK                                            ----------------- */
/* ----------------                       04- FLITF_CLK                                          ----------------- */
/* ----------------                       05- SRAM_CLK                                           ----------------- */
/* ----------------                       06- DMA2_CLK                                           ----------------- */
/* ----------------                       07- DMA1_CLK                                           ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_AHBEnableCLK ( uint8_t Copy_uint8AHBPeripheral ) ;



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_AHBDisableCLK                			     	 ----------------- */
/* ----------------      FUNCTION : Disable CLK on an AHB Peripheral    		         ----------------- */
/* ----------------      ARGUMENT : AHB Peripheral to Disable                                    ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                       01- SDIO_CLK        					 ----------------- */
/* ----------------                       02- FSMC_CLK          		                 ----------------- */
/* ----------------                       03- CRC_CLK                                            ----------------- */
/* ----------------                       04- FLITF_CLK                                          ----------------- */
/* ----------------                       05- SRAM_CLK                                           ----------------- */
/* ----------------                       06- DMA2_CLK                                           ----------------- */
/* ----------------                       07- DMA1_CLK                                           ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_AHBDisableCLK ( uint8_t Copy_uint8AHBPeripheral ) ;



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_APB1EnableCLK                			     	 ----------------- */
/* ----------------      FUNCTION : Enable CLK on an APB1 Peripheral    	     	         ----------------- */
/* ----------------      ARGUMENT : APB1 Peripheral to Enable                                    ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- DAC_CLK                                                   ----------------- */
/* ----------------                02- PWR_CLK                                                   ----------------- */
/* ----------------                03- BKP_CLK                                                   ----------------- */
/* ----------------                04- CAN_CLK                                                   ----------------- */
/* ----------------                05- USB_CLK                                                   ----------------- */
/* ----------------                06- I2C2_CLK                                                  ----------------- */
/* ----------------                07- I2C1_CLK                                                  ----------------- */
/* ----------------                08- UART5_CLK                                                 ----------------- */
/* ----------------                09- UART4_CLK                                                 ----------------- */
/* ----------------                10- USART3_CLK       				         ----------------- */
/* ----------------                11- USART2_CLK                                                ----------------- */
/* ----------------                12- SPI3_CLK                                                  ----------------- */
/* ----------------                13- SPI2_CLK                                                  ----------------- */
/* ----------------                14- WWDG_CLK                                                  ----------------- */
/* ----------------                15- TIM14_CLK                                                 ----------------- */
/* ----------------                16- TIM13_CLK                                                 ----------------- */
/* ----------------                17- TIM12_CLK                                                 ----------------- */
/* ----------------                18- TIM7_CLK                                                  ----------------- */
/* ----------------                19- TIM6_CLK                                                  ----------------- */
/* ----------------                20- TIM5_CLK                                                  ----------------- */
/* ----------------                21- TIM4_CLK                                                  ----------------- */
/* ----------------                22- TIM3_CLK                                                  ----------------- */
/* ----------------                23- TIM2_CLK                                                  ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_APB1EnableCLK ( uint8_t Copy_uint8APB1Peripheral ) ;



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_APB1DisableCLK                			     	 ----------------- */
/* ----------------      FUNCTION : Disable CLK on an APB1 Peripheral    	     	         ----------------- */
/* ----------------      ARGUMENT : APB1 Peripheral to Disable                                   ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- DAC_CLK                                                   ----------------- */
/* ----------------                02- PWR_CLK                                                   ----------------- */
/* ----------------                03- BKP_CLK                                                   ----------------- */
/* ----------------                04- CAN_CLK                                                   ----------------- */
/* ----------------                05- USB_CLK                                                   ----------------- */
/* ----------------                06- I2C2_CLK                                                  ----------------- */
/* ----------------                07- I2C1_CLK                                                  ----------------- */
/* ----------------                08- UART5_CLK                                                 ----------------- */
/* ----------------                09- UART4_CLK                                                 ----------------- */
/* ----------------                10- USART3_CLK       				         ----------------- */
/* ----------------                11- USART2_CLK                                                ----------------- */
/* ----------------                12- SPI3_CLK                                                  ----------------- */
/* ----------------                13- SPI2_CLK                                                  ----------------- */
/* ----------------                14- WWDG_CLK                                                  ----------------- */
/* ----------------                15- TIM14_CLK                                                 ----------------- */
/* ----------------                16- TIM13_CLK                                                 ----------------- */
/* ----------------                17- TIM12_CLK                                                 ----------------- */
/* ----------------                18- TIM7_CLK                                                  ----------------- */
/* ----------------                19- TIM6_CLK                                                  ----------------- */
/* ----------------                20- TIM5_CLK                                                  ----------------- */
/* ----------------                21- TIM4_CLK                                                  ----------------- */
/* ----------------                22- TIM3_CLK                                                  ----------------- */
/* ----------------                23- TIM2_CLK                                                  ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_APB1DisableCLK ( uint8_t Copy_uint8APB1Peripheral ) ;



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_APB2EnableCLK                			         ----------------- */
/* ----------------      FUNCTION : Enable CLK on an APB2 Peripheral    	     	         ----------------- */
/* ----------------      ARGUMENT : APB2 Peripheral to Enable                                    ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- TIM11_CLK                                                 ----------------- */
/* ----------------                02- TIM10_CLK                                                 ----------------- */
/* ----------------                03- TIM9_CLK                                                  ----------------- */
/* ----------------                04- ADC3_CLK                                                  ----------------- */
/* ----------------                05- USART1_CLK                                                ----------------- */
/* ----------------                06- TIM8_CLK                                                  ----------------- */
/* ----------------                07- SPI1_CLK                                                  ----------------- */
/* ----------------                08- TIM1_CLK                                                  ----------------- */
/* ----------------                09- ADC2_CLK                                                  ----------------- */
/* ----------------                10- ADC1_CLK         				         ----------------- */
/* ----------------                11- IOPG_CLK                                                  ----------------- */
/* ----------------                12- IOPF_CLK                                                  ----------------- */
/* ----------------                13- IOPE_CLK                                                  ----------------- */
/* ----------------                14- IOPD_CLK                                                  ----------------- */
/* ----------------                15- IOPC_CLK                                                  ----------------- */
/* ----------------                16- IOPB_CLK                                                  ----------------- */
/* ----------------                17- IOPA_CLK                                                  ----------------- */
/* ----------------                18- AFIO_CLK                                                  ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_APB2EnableCLK ( uint8_t Copy_uint8APB2Peripheral ) ;



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_APB2DisableCLK                			     	 ----------------- */
/* ----------------      FUNCTION : Disable CLK on an APB2 Peripheral    	     	         ----------------- */
/* ----------------      ARGUMENT : APB2 Peripheral to Disable                                   ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- TIM11_CLK                                                 ----------------- */
/* ----------------                02- TIM10_CLK                                                 ----------------- */
/* ----------------                03- TIM9_CLK                                                  ----------------- */
/* ----------------                04- ADC3_CLK                                                  ----------------- */
/* ----------------                05- USART1_CLK                                                ----------------- */
/* ----------------                06- TIM8_CLK                                                  ----------------- */
/* ----------------                07- SPI1_CLK                                                  ----------------- */
/* ----------------                08- TIM1_CLK                                                  ----------------- */
/* ----------------                09- ADC2_CLK                                                  ----------------- */
/* ----------------                10- ADC1_CLK         					 ----------------- */
/* ----------------                11- IOPG_CLK                                                  ----------------- */
/* ----------------                12- IOPF_CLK                                                  ----------------- */
/* ----------------                13- IOPE_CLK                                                  ----------------- */
/* ----------------                14- IOPD_CLK                                                  ----------------- */
/* ----------------                15- IOPC_CLK                                                  ----------------- */
/* ----------------                16- IOPB_CLK                                                  ----------------- */
/* ----------------                17- IOPA_CLK                                                  ----------------- */
/* ----------------                18- AFIO_CLK                                                  ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_APB2DisableCLK ( uint8_t Copy_uint8APB2Peripheral ) ;


/* ---------------------------------------------------------------------------------------- */
/* ------------------------------- PROTOTYPES SECTION END   ------------------------------- */
/* ---------------------------------------------------------------------------------------- */

#endif /* RCC_RCC_INTERFACE_H_ */
