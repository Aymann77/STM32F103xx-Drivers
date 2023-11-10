/*
 ******************************************************************************
 * @file           : I2C_Interface.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : Nov 6, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */
#ifndef I2C_INC_I2C_INTERFACE_H_
#define I2C_INC_I2C_INTERFACE_H_


/**
 * @def   : &I2C_ADD_MODE_t
 * @brief : SPECIFIES I2C ADDRESSING MODES
 *
 */
#define I2C_ADD_MODE_7BIT    0
#define I2C_ADD_MODE_10BIT   1

typedef enum
{
	I2C_RW_BIT_WRITE = 0 ,
	I2C_RW_BIT_READ
}I2C_RW_BIT_t;


/**
 * @enum  : @I2C_t
 * @brief : SPECIFIES I2C AVAILABLE NUMBERS
 *
 */
typedef enum
{
	I2C_1 = 0 ,/**< I2C_1 */
	I2C_2 = 1  /**< I2C_2 */
}I2C_t;

/**
 * @enum  : @I2C_FREQ_t
 * @brief : SPECIFIES AVAILABLE PCLK1 FREQUENCIES
 *
 */
typedef enum
{
	 I2C_FREQ_2MHz = 2 , I2C_FREQ_3MHz , I2C_FREQ_4MHz , I2C_FREQ_5MHz , I2C_FREQ_6MHz , I2C_FREQ_7MHz ,
	 I2C_FREQ_8MHz 	   , I2C_FREQ_9MHz , I2C_FREQ_10MHz, I2C_FREQ_11MHz, I2C_FREQ_12MHz, I2C_FREQ_13MHz,
	 I2C_FREQ_14MHz	   , I2C_FREQ_15MHz, I2C_FREQ_16MHz, I2C_FREQ_17MHz, I2C_FREQ_18MHz, I2C_FREQ_19MHz,
	 I2C_FREQ_20MHz    , I2C_FREQ_21MHz, I2C_FREQ_22MHz, I2C_FREQ_23MHz, I2C_FREQ_24MHz, I2C_FREQ_25MHz,
     I2C_FREQ_26MHz    , I2C_FREQ_27MHz, I2C_FREQ_28MHz, I2C_FREQ_29MHz, I2C_FREQ_30MHz, I2C_FREQ_31MHz,
	 I2C_FREQ_32MHz	   , I2C_FREQ_33MHz, I2C_FREQ_34MHz, I2C_FREQ_35MHz, I2C_FREQ_36MHz, I2C_FREQ_37MHz,
	 I2C_FREQ_38MHz	   , I2C_FREQ_39MHz, I2C_FREQ_40MHz, I2C_FREQ_41MHz, I2C_FREQ_42MHz, I2C_FREQ_43MHz,
     I2C_FREQ_44MHz	   , I2C_FREQ_45MHz, I2C_FREQ_46MHz, I2C_FREQ_47MHz, I2C_FREQ_48MHz, I2C_FREQ_49MHz,
	 I2C_FREQ_50MHz	   ,
}I2C_FREQ_t;

/**
 * @enum  : @I2C_SPEED_MODE_t
 * @brief : SPECIFIES AVAILABLE SPEED MODES
 *
 */
typedef enum
{
	I2C_SPEED_MODE_STANDARD = 0 , /*!< UP TO 100KHz >!*//**< I2C_SPEED_MODE_STANDARD */
	I2C_SPEED_MODE_FAST		= 1   /*!< UP TO 400KHz >!*/   /**< I2C_SPEED_MODE_FAST */

}I2C_SPEED_MODE_t;

/**
 * @enum  : @I2C_CLK_STRETCH_t
 * @brief : SPECIFIES CLOCK STRETCHING OPTIONS
 *
 */
typedef enum
{
	I2C_CLK_STRETCH_ENABLE = 0 ,/**< I2C_CLK_STRETCH_ENABLE */
	I2C_CLK_STRETCH_DISABLE     /**< I2C_CLK_STRETCH_DISABLE */
}I2C_CLK_STRETCH_t;

typedef struct
{
	I2C_t 	   			I2CNumber ; /*!< I2C NUMBER TO CONFIGURE ,
										 CHECK AVAILABLE ONES @I2C_t >!*/

	I2C_SPEED_MODE_t	SpeedMode ; /*!< CONFIGURE BUS SPEED MODE
										 CHECK @I2C_SPEED_MODE_t >!*/

	I2C_FREQ_t 			APB1ClockFrequencyMhz ; /*!< PROVIDE THE ABP1 CLOCK FREQUENCY
												CHECK @I2C_FREQ_t >!*/

	uint16_t  		    SlaveAddress	   ; /*!< DEVICE ADDRESS OR SLAVE ADDRESS >!*/

	uint8_t             AddressingMode     ; /*!< CONFIGURE DEVICE ADDRESSING MODE ,
												  CHECK AVAILABLE OPTIONS @I2C_ADD_MODE_t >!*/

	uint8_t  			SCLFrequencyKHz    ; /*!< CONFIGURE SPEED OF COMMUNICATION IN KHz ,
												FOR SM : MAX 100KHz , FOR FM : MAX 400KHZ >!*/

	I2C_CLK_STRETCH_t	CLKStretch		   ; /*!< CONFIGURE CLOCK STRETCHING OPTIONS ,
												CHECK AVAILABLE OPTIONS @I2C_CLK_STRETCH_t >!*/


}I2C_Config_t;


/*==============================================================================================================================================
 * PROTOTYPES SECTION
 *==============================================================================================================================================*/

/**
 * @fn     : MI2C_eInit(I2C_Config_t*)
 * @brief  : FUNCTION THAT INITIALISZES I2C PERIPHERAL WITH REQUIRED CONFIGURATION
 * @param  : I2CConfig => POINTER TO STRUCT THAT CONTAINS I2C PERIPHERAL CONFIGURATION TO PROGRAM
 * @return : ERROR STATUS TO INDICATE OF VALID PARAMETERS
 */
ERRORS_t MI2C_eInit( I2C_Config_t * I2CConfig ) ;

/**
 * @fn 		: MI2C_eSendStartCondition
 * @brief 	: THIS FUNCTION SENDS START CONDITION FOLLOWED BY SLAVE ADDRESS FOLLOWED BY RW BIT
 *
 * @param   : I2CConfig				=> A POINTER TO STRUCTURE THAT CARRIES I2C CONFIGURATION INFO
 * @param 	: Copy_u16SlaveAddress 	=> SLAVE ADDRESS ON THE BUS TO COMMUNICATE WITH
 * @param 	: Copy_u8RWBit			=> RW BIT FOLLOWED BY SLAVE ADDRESS , CHECK @I2C_RW_BIT_t
 * @return	: ERROR  STATUS TO INDICATE FOR MALFUNCTION
 * @note    : 10 BIT SLAVE ADDRESS NOT SUPPORTED YET
 */
ERRORS_t MI2C_eSendStartCondition( I2C_Config_t * I2CConfig , uint16_t Copy_u16SlaveAddress , I2C_RW_BIT_t Copy_u8RWBit ) ;

/**
 * @fn 		: MI2C_eMasterWriteData
 * @brief   : THIS FUNCTION SENDS DATA BYTES ON COMMUNICATINON BUS
 * @param   : I2CConfig			=> A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @param 	: Copy_pu8DataBuffer=> POINTER TO DATA BUFFER TO SEND VIA I2C BUS LANE ( SDA )
 * @param 	: Copy_u8BufferSize => SIZE OF DATA TO SEND TO LOOP ON
 * @return 	: ERROR STATUS
 */
ERRORS_t MI2C_eMasterWriteData( I2C_Config_t * I2CConfig , uint8_t * Copy_pu8DataBuffer , uint8_t Copy_u8BufferSize ) ;


/**
 * @fn		: MI2C_vSendStopCondition
 * @brief 	: THIS FUNCTION SEND STOP CONDITION ON COMMUNICATION BUS
 * @param 	: I2CConfig => A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @retval  : VOID
 */
void MI2C_vSendStopCondition( I2C_Config_t * I2CConfig ) ;

/**
 * @fn 		: MI2C_eReadData
 * @brief 	: THIS FUNCTION READS DATA ON SDA LINE AS MASTER ( MASTER RECEIVER )
 * @param   : I2CConfig			=> A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @param 	: Copy_u8DataBuffer	=> POINTER TO THE DATA TO BE READ FROM I2C BUS LANE ( SDA )
 * @param 	: Copy_u8BufferSize	=> BUFFER SIZE OF DATA TO READ FROM COM BUS
 * @return	: ERROR STATUS
 */
ERRORS_t MI2C_eReadData( I2C_Config_t * I2CConfig , uint8_t* Copy_u8DataBuffer , uint8_t Copy_u8BufferSize ) ;

/**
 * @fn 		: MI2C_eSendRepeatedStart
 * @brief 	: THIS FUNCTION SENDS REPEATED START ON COMMUNICATION BUS , SAME AS  @MI2C_eSendStartCondition ,
 * 				BUT WITHOUT CHECKING ON THE BUSY FLAG
 * @param 	: I2CConfig				=> A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @param   : Copy_u16SlaveAddress	=> SLAVE ADDRESS TO SEND ON COMMUNICATION BUS
 * @param 	: Copy_u8RWBit			=> R/W BIT FOLLOWED BY THE 7 BIT SLAVE ADDRESS
 * @return	: ERROR STATUS
 * @note    : 10 BIT SLAVE ADDRESS NOT SUPPORTED YET
 */
ERRORS_t MI2C_eSendRepeatedStart( I2C_Config_t * I2CConfig , uint16_t Copy_u16SlaveAddress , I2C_RW_BIT_t Copy_u8RWBit ) ;


#endif /* I2C_INC_I2C_INTERFACE_H_ */
