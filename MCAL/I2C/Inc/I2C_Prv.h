/*
 ******************************************************************************
 * @file           : I2C_Prv.h
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
#ifndef I2C_INC_I2C_PRV_H_
#define I2C_INC_I2C_PRV_H_
/*==============================================================================================================================================
 * PRIVATE MACROS SECTION
 *==============================================================================================================================================*/
#define I2C_MAX_NUMBER    2

#define I2C_OAR1_DEVICE_ADD_MASK 	( 0xF000 )
#define I2C_CR2_FREQ_MASK		 	( 0xFF00 )
#define I2C_CCR_MASK			 	( 0x0000 )

#define MAX_DELAY                   ( 0xFFFF )


/*==============================================================================================================================================
 * PRIVATE FUNCTIONS
 *==============================================================================================================================================*/

/**
 * @fn    : _u16CalculateCCR
 * @brief : Calculates CCR Value From SCL Frequency & PCLK1 Provided in Configurations
 *
 * @param : I2CConfig => Pointer to Structure that holds I2C Configuration Parameters
 * @retval: CCR Value
 * @note  : Private Function For Provider Use ONLY
 */
static uint16_t _u16CalculateCCR( I2C_Config_t * I2CConfig ) ;

/**
 * @fn 		: MI2C_vEnableACK
 * @brief 	: THIS FUNCTION ENABLES ACK BIT IN I2C CONFIGURATION
 *
 * @param 	: I2CConfig => A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @retval  : VOID
 * @note   	: PRIVATE FUNCTION
 */
static void MI2C_vEnableACK( I2C_Config_t * I2CConfig ) ;

/**
 * @fn 		: MI2C_vDisableACK
 * @brief 	: THIS FUNCTION DISABLES ACK BIT IN I2C CONFIGURATION
 *
 * @param 	: I2CConfig => A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @retval  : VOID
 * @note   	: PRIVATE FUNCTION
 */
static void MI2C_vDisableACK( I2C_Config_t * I2CConfig  ) ;

/**
 * @fn		: _eI2CCheckConfig
 * @brief 	: FUNCTION THAT CHECKS ON I2C CONFIGURATION PASSED BY CALLER
 *
 * @param 	: I2CConfig => A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @return	: ERROR STATUS INDICATE OF CONFIGURATION VALIDITY
 * @note 	: PRIVATE FUNCTION
 */
static ERRORS_t _eI2CCheckConfig( I2C_Config_t * I2CConfig ) ;

/**
 * @fn 		:  _vClearADDR(I2C_t)
 * @brief 	: THIS FUNCTION CLEARS ADDR FLAG IN SR1 REGISTER
 *
 * @param 	: I2CNumber => I2C NUMBER USED
 * @return	: NO VALID RETURN , MADE TO  AVOID ONLY COMPILER WARNNINGS
 * @note	: PRIVATE FUNCTION
 */
static uint16_t _vClearADDR( I2C_t I2CNumber ) ;

#endif /* I2C_INC_I2C_PRV_H_ */
