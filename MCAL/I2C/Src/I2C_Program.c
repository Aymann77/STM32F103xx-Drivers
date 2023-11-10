/*
 ******************************************************************************
 * @file           : I2C_Program.c
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

/*==============================================================================================================================================
 * INCLUDES SECTION
 *==============================================================================================================================================*/
#include <stdint.h>

#include "../../../LIB/ErrType.h"
#include "../../../LIB/STM32F103xx.h"

#include "../Inc/I2C_Interface.h"
#include "../Inc/I2C_Prv.h"

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION
 *==============================================================================================================================================*/

I2C_RegDef_t * I2C[ I2C_MAX_NUMBER ] = { I2C1 , I2C2 } ;

/*==============================================================================================================================================
 * IMPLEMENTATIONS SECTION
 *==============================================================================================================================================*/

/**
 * @fn     : MI2C_eInit(I2C_Config_t*)
 * @brief  : FUNCTION THAT INITIALISZES I2C PERIPHERAL WITH REQUIRED CONFIGURATION
 * @param  : I2CConfig => POINTER TO STRUCT THAT CONTAINS I2C PERIPHERAL CONFIGURATION TO PROGRAM
 * @return : ERROR STATUS TO INDICATE OF VALID PARAMETERS
 */
ERRORS_t MI2C_eInit( I2C_Config_t * I2CConfig )
{
	ERRORS_t Local_ErrorStatus  = OK ;

	if( NOK != _eI2CCheckConfig(I2CConfig) )
	{
		/* RIGHT CONFIGURATIONS */
		uint16_t Local_u16CCRValue ;

		/* SETTING ADDRESS & ADDRESSING MODE */
		if( I2CConfig->AddressingMode == I2C_ADD_MODE_7BIT )
		{
			/* Set Addressing Mode & Device Address */
			I2C[ I2CConfig->I2CNumber ]->I2C_OAR1 |= (  (uint8_t)I2CConfig->SlaveAddress << 1 ) ;
		}
		else
		{
			/* I2C_ADD_MODE_10BIT */
			I2C[ I2CConfig->I2CNumber ]->I2C_OAR1 |= (1<<I2C_OAR1_BIT_ADDMODE) ;

			I2C[ I2CConfig->I2CNumber ]->I2C_OAR1 &= ( I2C_OAR1_DEVICE_ADD_MASK ) ;
			I2C[ I2CConfig->I2CNumber ]->I2C_OAR1 |= ( I2CConfig->SlaveAddress ) ;
		}

		/* SETTING CLOCK STRETCHING */
		if( I2CConfig->CLKStretch == I2C_CLK_STRETCH_DISABLE )
		{
			/* DISABLE CLOCK STRETCHING */
			I2C[ I2CConfig->I2CNumber ]->I2C_CR1 |= ( 1<<I2C_CR1_BIT_NOSTRETCH ) ;
		}
		else
		{
			/* ENABLE CLOCK STRETCHING */
			I2C[ I2CConfig->I2CNumber ]->I2C_CR1 &= ( ~ ( 1<<I2C_CR1_BIT_NOSTRETCH ) ) ;
		}

		/* SETTING SPEED MODE */
		I2C[ I2CConfig->I2CNumber ]->I2C_CCR &= ( I2C_CCR_MASK ) ;
		I2C[ I2CConfig->I2CNumber ]->I2C_CCR |= ( I2CConfig->SpeedMode << I2C_CCR_BIT_F_S ) ;


		/* SETTING FREQUENCY */
		I2C[ I2CConfig->I2CNumber ]->I2C_CR2 &=( I2C_CR2_FREQ_MASK ) ;
		I2C[ I2CConfig->I2CNumber ]->I2C_CR2 |= ( I2CConfig->APB1ClockFrequencyMhz ) ;


		/* SETTING CCR */
		Local_u16CCRValue = _u16CalculateCCR(I2CConfig) ;
		I2C[ I2CConfig->I2CNumber ]->I2C_CCR |= ( Local_u16CCRValue ) ;

		/* PERIPHERAL ENABLE */
		I2C[ I2CConfig->I2CNumber ]-> I2C_CR1 |= ( 1 << I2C_CR1_BIT_PE ) ;
	}
	else
	{
		/* FALSE CONFIGURATIONS */
		Local_ErrorStatus = NOK ;
	}
	return Local_ErrorStatus ;
}

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
ERRORS_t MI2C_eSendStartCondition( I2C_Config_t * I2CConfig , uint16_t Copy_u16SlaveAddress , I2C_RW_BIT_t Copy_u8RWBit )
{
	ERRORS_t local_ErrorStatus = OK ;

	if( NOK != _eI2CCheckConfig(I2CConfig) )
	{
		/* RIGHT CONFIGURATIONS */
		uint16_t Local_u16TimeoutVar = 0 ;

		/* Wait Until Bus is Free */
		while( ( ( I2C[ I2CConfig->I2CNumber ]->I2C_SR2 >> I2C_SR2_BUSY ) & 1U ) && ( Local_u16TimeoutVar != MAX_DELAY ) )
		{
			Local_u16TimeoutVar++;
		}

		/* IF BUSY FLAG IS STUCK */
		if( Local_u16TimeoutVar == MAX_DELAY )
		{
			/* Reset Peripheral */
			I2C[ I2CConfig->I2CNumber ]-> I2C_CR1 |= ( 1 << I2C_CR1_BIT_SWRST ) ;
			I2C[ I2CConfig->I2CNumber ]-> I2C_CR1 &= (~(1<<I2C_CR1_BIT_SWRST)) ;

			/* ReInitialize the Peripheral */
			MI2C_eInit(I2CConfig) ;
		}

		/* ENABLE ACKNOWLEDGE */
		MI2C_vEnableACK(I2CConfig) ;

		/* Send Start Condition */
		I2C[ I2CConfig->I2CNumber ]->I2C_CR1 |= ( 1 << I2C_CR1_BIT_START ) ;

		/* Wait Until SB Bit is Set */
		while( !( ( I2C[ I2CConfig->I2CNumber ]->I2C_SR1 >> I2C_SR1_SB ) & 1U ) ) ;

		/* Send Slave Address */
		if( I2CConfig->AddressingMode == I2C_ADD_MODE_7BIT )
		{
			/* CHECK ON SLAVE ADDRESS */
			if( Copy_u16SlaveAddress <= 255 )
			{
				/* Variable that Carry Slave Address with RW Bit */
				uint8_t Local_u8SlaveAddressWithRWBit = (uint8_t)( Copy_u16SlaveAddress << 1 ) ;

				/* Adding RW Bit to the Address */
				Local_u8SlaveAddressWithRWBit |= ( Copy_u8RWBit ) ;

				/* Send Slave Address */
				I2C[ I2CConfig->I2CNumber ]->I2C_DR = Local_u8SlaveAddressWithRWBit ;

				/* Wait Until Flag is Set */
				/* RESET TIMEOUT VARIABLE */
				Local_u16TimeoutVar = 0 ;

				while( ( !( ( I2C[ I2CConfig->I2CNumber ]->I2C_SR1 >> I2C_SR1_ADDR ) & 1U ) ) && ( Local_u16TimeoutVar != MAX_DELAY ) )
				{
					Local_u16TimeoutVar ++ ;
				}

				/* CLEAR ADDR FLAG */
				_vClearADDR(I2CConfig->I2CNumber);

			}
			else
			{
				local_ErrorStatus = NOK ;
			}
		}

	}
	else
	{
		local_ErrorStatus = NOK ;
	}

	return local_ErrorStatus ;
}

/**
 * @fn 		: MI2C_eMasterWriteData
 * @brief   : THIS FUNCTION SENDS DATA BYTES ON COMMUNICATINON BUS
 * @param   : I2CConfig			=> A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @param 	: Copy_pu8DataBuffer=> POINTER TO DATA BUFFER TO SEND VIA I2C BUS LANE ( SDA )
 * @param 	: Copy_u8BufferSize => SIZE OF DATA TO SEND TO LOOP ON
 * @return 	: ERROR STATUS
 */
ERRORS_t MI2C_eMasterWriteData( I2C_Config_t * I2CConfig , uint8_t * Copy_pu8DataBuffer , uint8_t Copy_u8BufferSize )
{
	ERRORS_t Local_ErrorStatus = OK ;

	uint8_t Local_u8LoopCounter = 0 ;

	for( Local_u8LoopCounter = 0 ; Local_u8LoopCounter < Copy_u8BufferSize ; Local_u8LoopCounter++ )
	{
		/* Wait Untill Transmit Register Empty Flag is Set */
		while( !( ( I2C[ I2CConfig->I2CNumber ]->I2C_SR1 >> I2C_SR1_TXE ) & 1U ) ) ;

		I2C[ I2CConfig->I2CNumber ]->I2C_DR = Copy_pu8DataBuffer[ Local_u8LoopCounter ] ;

	}

	return Local_ErrorStatus ;
}

/**
 * @fn		: MI2C_vSendStopCondition
 * @brief 	: THIS FUNCTION SEND STOP CONDITION ON COMMUNICATION BUS
 * @param 	: I2CConfig => A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @retval  : VOID
 */
void MI2C_vSendStopCondition( I2C_Config_t * I2CConfig )
{
	/* Send Stop Condition */
	I2C[ I2CConfig->I2CNumber ]->I2C_CR1 |= ( 1 << I2C_CR1_BIT_STOP ) ;

}

/**
 * @fn 		: MI2C_vEnableACK
 * @brief 	: THIS FUNCTION ENABLES ACK BIT IN I2C CONFIGURATION
 *
 * @param 	: I2CConfig => A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @retval  : VOID
 * @note   	: PRIVATE FUNCTION
 */
static void MI2C_vEnableACK( I2C_Config_t * I2CConfig )
{
	I2C[ I2CConfig->I2CNumber ]->I2C_CR1 |= ( 1 << I2C_CR1_BIT_ACK ) ;
}

/**
 * @fn 		: MI2C_vDisableACK
 * @brief 	: THIS FUNCTION DISABLES ACK BIT IN I2C CONFIGURATION
 *
 * @param 	: I2CConfig => A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @retval  : VOID
 * @note   	: PRIVATE FUNCTION
 */
static void MI2C_vDisableACK( I2C_Config_t * I2CConfig  )
{
	I2C[ I2CConfig->I2CNumber ]->I2C_CR1 &= ( ~ ( 1 << I2C_CR1_BIT_ACK ) )  ;

}

/**
 * @fn 		: MI2C_eReadData
 * @brief 	: THIS FUNCTION READS DATA ON SDA LINE AS MASTER ( MASTER RECEIVER )
 * @param   : I2CConfig			=> A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @param 	: Copy_u8DataBuffer	=> POINTER TO THE DATA TO BE READ FROM I2C BUS LANE ( SDA )
 * @param 	: Copy_u8BufferSize	=> BUFFER SIZE OF DATA TO READ FROM COM BUS
 * @return	: ERROR STATUS
 */
ERRORS_t MI2C_eReadData( I2C_Config_t * I2CConfig , uint8_t* Copy_u8DataBuffer , uint8_t Copy_u8BufferSize )
{
	ERRORS_t Local_ErrorStatus = OK ;

	uint8_t Local_u8LoopCounter = 0 ;

	uint16_t Local_u16TimeoutVar = 0 ;

	for( Local_u8LoopCounter = 0 ; Local_u8LoopCounter < Copy_u8BufferSize ; Local_u8LoopCounter++ )
	{
		/* Wait Untill Flag is Set */
		while( ( !( ( I2C[ I2CConfig->I2CNumber ]->I2C_SR1  >> I2C_SR1_RXNE ) & 1U ) ) && ( Local_u16TimeoutVar != MAX_DELAY ) )
		{
			Local_u16TimeoutVar++ ;
		}

		if( Local_u16TimeoutVar == MAX_DELAY )
		{
			Local_u16TimeoutVar = TIME_OUT_ERROR ;
			break ;
		}

		/* READ DATA FROM DATA REGISTER */
		Copy_u8DataBuffer[ Local_u8LoopCounter ] = I2C[ I2CConfig->I2CNumber ]->I2C_DR ;

		/* CHECK IF LAST ELEMENT IS ABOUT TO BE READ , DISABLE ACK BIT */
		if( ( Local_u8LoopCounter + 2 ) == Copy_u8BufferSize )
		{
			/* DISABLE ACKNOWLEDGE */
			MI2C_vDisableACK(I2CConfig);
		}
	}
	return Local_ErrorStatus ;
}

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
ERRORS_t MI2C_eSendRepeatedStart( I2C_Config_t * I2CConfig , uint16_t Copy_u16SlaveAddress , I2C_RW_BIT_t Copy_u8RWBit )
{
	ERRORS_t local_ErrorStatus = OK ;

	if( NOK != _eI2CCheckConfig(I2CConfig) )
	{
		/* RIGHT CONFIGURATIONS */

		/* Send Repeated Start Condition */
		I2C[ I2CConfig->I2CNumber ]->I2C_CR1 |= ( 1 << I2C_CR1_BIT_START ) ;

		/* Wait Until SB Bit is Set */
		while( !( ( I2C[ I2CConfig->I2CNumber ]->I2C_SR1 >> I2C_SR1_SB ) & 1U ) ) ;

		/* ENABLE ACKNOWLEDGE */
		MI2C_vEnableACK(I2CConfig) ;

		/* Send Slave Address */
		if( I2CConfig->AddressingMode == I2C_ADD_MODE_7BIT )
		{
			if( Copy_u16SlaveAddress <= 255 )
			{
				uint16_t Local_u16TimeoutVar = 0 ;
				/* Variable that Carry Slave Address with RW Bit */
				uint8_t Local_u8SlaveAddressWithRWBit = (uint8_t)( Copy_u16SlaveAddress << 1 ) ;

				/* Adding RW Bit to the Address */
				Local_u8SlaveAddressWithRWBit |= ( Copy_u8RWBit ) ;

				/* Send Slave Address */
				I2C[ I2CConfig->I2CNumber ]->I2C_DR = Local_u8SlaveAddressWithRWBit ;

				/* Wait Until Flag is Set */
				while( ( !( ( I2C[ I2CConfig->I2CNumber ]->I2C_SR1 >> I2C_SR1_ADDR ) & 1U ) ) &&( Local_u16TimeoutVar != MAX_DELAY )  )
				{
					Local_u16TimeoutVar++;
				}

				/* CLEAR ADDR FLAG */
				_vClearADDR(I2CConfig->I2CNumber);

			}
			else
			{
				local_ErrorStatus = NOK ;
			}

		}


	}
	else
	{
		local_ErrorStatus = NOK ;
	}

	return local_ErrorStatus ;
}


/*==============================================================================================================================================
 * PRIVATE FUNCTIONS SECTION
 *==============================================================================================================================================*/

/**
 * @fn    : _u16CalculateCCR
 * @brief : Calculates CCR Value From SCL Frequency & PCLK1 Provided in Configurations
 *
 * @param : I2CConfig => Pointer to Structure that holds I2C Configuration Parameters
 * @retval: CCR Value
 * @note  : Private Function For Provider Use ONLY
 */
static uint16_t _u16CalculateCCR( I2C_Config_t * I2CConfig )
{
	uint32_t Local_u32CCRValue = ( I2CConfig->APB1ClockFrequencyMhz * 1000000 ) / ( I2CConfig->SCLFrequencyKHz * 1000 ); /* Convert the Units to KHz */
	Local_u32CCRValue = Local_u32CCRValue / 2  ;

	return (uint16_t)Local_u32CCRValue ;

}

/**
 * @fn		: _eI2CCheckConfig
 * @brief 	: FUNCTION THAT CHECKS ON I2C CONFIGURATION PASSED BY CALLER
 *
 * @param 	: I2CConfig => A POINTER TO STRUCTURE THAT HOLDS I2C CONFIGURATION INFO
 * @return	: ERROR STATUS INDICATE OF CONFIGURATION VALIDITY
 * @note 	: PRIVATE FUNCTION
 */
static ERRORS_t _eI2CCheckConfig( I2C_Config_t * I2CConfig )
{
	ERRORS_t Local_ErrorStatus = OK ;

	if( ( I2CConfig->APB1ClockFrequencyMhz < I2C_FREQ_2MHz )  || (  I2CConfig->APB1ClockFrequencyMhz > I2C_FREQ_50MHz ) ||
			( I2CConfig->AddressingMode < I2C_ADD_MODE_7BIT ) || ( I2CConfig->AddressingMode > I2C_ADD_MODE_10BIT )  ||
			( I2CConfig->I2CNumber < I2C_1 ) || ( I2CConfig->I2CNumber > I2C_2 ) ||
			( I2CConfig->CLKStretch < I2C_CLK_STRETCH_ENABLE ) || ( I2CConfig->CLKStretch > I2C_CLK_STRETCH_DISABLE ) ||
			( I2CConfig->SpeedMode < I2C_SPEED_MODE_STANDARD ) || ( I2CConfig->SpeedMode > I2C_SPEED_MODE_FAST ) )
	{
		Local_ErrorStatus = NOK ;
	}
	return Local_ErrorStatus ;
}


/**
 * @fn 		:  _vClearADDR(I2C_t)
 * @brief 	: THIS FUNCTION CLEARS ADDR FLAG IN SR1 REGISTER
 *
 * @param 	: I2CNumber => I2C NUMBER USED
 * @return	: NO VALID RETURN , MADE TO  AVOID ONLY COMPILER WARNNINGS
 * @note	: PRIVATE FUNCTION
 */
static uint16_t _vClearADDR( I2C_t I2CNumber )
{
	uint16_t Local_u16TempVar = 0 ;
	Local_u16TempVar = I2C[ I2CNumber ]->I2C_SR1 ;
	Local_u16TempVar = I2C[ I2CNumber ]->I2C_SR2 ;

	return Local_u16TempVar;
}


