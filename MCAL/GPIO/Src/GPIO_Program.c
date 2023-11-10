/*
 ******************************************************************************
 * @file           : GPIO_Program.c
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : May 8, 2023
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

#include "../../../LIB/STM32F103xx.h"
#include "../../../LIB/ErrType.h"

#include "../Inc/GPIO_Interface.h"
#include "../Inc/GPIO_Private.h"


/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION
 *==============================================================================================================================================*/
/* Array of Pointers */
GPIO_RegDef_t * GPIOs[ NUM_OF_GPIOs ] = { GPIOA , GPIOB , GPIOC , GPIOD , GPIOE } ;


/*==============================================================================================================================================
 * MODULES IMPLEMENTATION
 *==============================================================================================================================================*/


/**
 * @fn			         : GPIO_u8PinInit
 * @brief		         : Function Initializes A GPIO Pin According to the Input Parameters
 * @param     PinConfig  : Initialization Values of the Pin
 * @retval		         : Error Status
 *                           -> OK , GPIO_NOT_VALID , NULL_POINTER
 * @note			     : U don't Have To Use All Elements of the Struct
 *                             if u don't need one of them don't give it a Value
 **/

uint8_t GPIO_u8PinInit(const GPIO_PinConfig_t * PinConfig)
{
	/* Variable to Carry ErrorStatus */
	uint8_t Local_u8ErrorStatus = OK ;

	/* Variable To Indicate for Reg Num in Accessing CRLH & CRLL */
	uint8_t Local_u8RegNum = ( ( PinConfig->PinNum) >=8U ) ;

	/* Varaiable To Indicate for Bit Num When Accessing CNF Bits */
	uint8_t Local_u8BitNum = ( ( PinConfig->PinNum ) %8U ) ;

	/* Check if Pin Configurations Equals Null */
	if(  NULL != PinConfig  )
	{
		/* Check on All Pin Configuration If Valid Continue Initializing Pin */
		if( GPIO_NOT_VALID != GPIO_u8CheckPinConfig(PinConfig) )
		{
			/* Set Pin Mode : INPUT , OUTPUT_MAXSPEED_10MHZ , OUTPUT_MAXSPEED_2MHZ , OUTPUT_MAXSPEED_50MHZ */
			( GPIOs[ PinConfig->Port ]->CRL[ Local_u8RegNum ] ) &= ( ~ ( MODE_BITS_MASK << ( Local_u8BitNum * MODE_BITS_PIN_ACCESS )  ) ) ;
			( GPIOs[ PinConfig->Port ]->CRL[ Local_u8RegNum ] ) |= ( ( PinConfig->Mode ) <<  ( Local_u8BitNum * MODE_BITS_PIN_ACCESS )  ) ;

			if( ( PinConfig->Mode ) == INPUT )
			{
				/* Set Input Mode : ANALOG , FLOATING , PULL_UP_OR_PULL_DOWN */
				( GPIOs[ PinConfig->Port ] -> CRL[ Local_u8RegNum ] ) &= ( ~ ( CNF_BITS_MASK << ( Local_u8BitNum * CNF_BITS_PIN_ACCESS ) ) ) ;
				( GPIOs[ PinConfig->Port ] -> CRL[ Local_u8RegNum ] ) |= ( ( ( PinConfig->InMode )<<2 ) << ( Local_u8BitNum * CNF_BITS_PIN_ACCESS ) ) ;

				/* Check on Pull Type : PULL_UP OR PULL_DOWN */
				if( ( PinConfig->PullType ) == PULL_UP )
				{
					/* If Pull UP is Chosen , Set the Equivelant Bit */
					( GPIOs[ PinConfig->Port ]->ODR ) |= ( 1 << ( PinConfig->PinNum ) ) ;
				}
				else if( ( PinConfig->PullType ) == PULL_DOWN )
				{
					/* If Pull Down is Chosen , Clear the Equivelant Bit */
					( GPIOs[ PinConfig->Port ]->ODR ) &= ( ~ ( 1 << ( PinConfig->PinNum ) ) ) ;
				}

			}
			/* Check if Pin Mode is Output */
			else if( ( ( PinConfig->Mode ) == OUTPUT_MAXSPEED_10MHZ ) || ( ( PinConfig->Mode ) == OUTPUT_MAXSPEED_50MHZ ) || ( ( PinConfig->Mode ) == OUTPUT_MAXSPEED_2MHZ ) )
			{
				/* Set Output Mode : OUTPUT_PUSH_PULL , OUTPUT_OPEN_DRAIN , ALTERNATE_FUNC_PUSH_PULL , ALTERNATE_FUNC_OPEN_DRAIN */
				( GPIOs[ PinConfig->Port ] -> CRL[ Local_u8RegNum ] ) &= ( ~ ( CNF_BITS_MASK << ( Local_u8BitNum * CNF_BITS_PIN_ACCESS ) ) ) ;
				( GPIOs[ PinConfig->Port ] -> CRL[ Local_u8RegNum ] ) |= ( ( ( PinConfig->OutMode )<<2 ) << ( Local_u8BitNum * CNF_BITS_PIN_ACCESS ) ) ;
			}

		}
		else
		{
			/* If Pin Configurations is Not Valid */
			Local_u8ErrorStatus = GPIO_NOT_VALID ;
		}
	}
	else
	{
		/* If Pin Configuration Pointer Points To NULL */
		Local_u8ErrorStatus = NULL_POINTER ;
	}
	return Local_u8ErrorStatus ;
}


/**
 * @fn			         : GPIO_u8SetPinValue
 * @brief		         : Function To Set A GPIO Pin to A Certain Value
 * @param     Port       : USED PORT , To get Values -> @Port_t
 * @param     PinNum     : USED PIN , To get Values -> @Pin_t
 * @param     PinValue   : Value to Put on a Certain Pin , To get Values -> @PinValue_t
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t PinNum, PinValue_t PinValue)
{
	/* Variable to Carry ErrorStatus */
	uint8_t Local_u8ErrorStatus = OK ;

	/* Check ON PortNumber and PinNumber */
	if( ( Port <= PORTE ) && ( PinNum  <= PIN15 ) )
	{
		if( PinValue == PIN_LOW )
		{
			/* Using Bit Reset Register */
			( GPIOs[ Port ]->BRR ) = ( 1 << PinNum ) ;
		}
		else if( PinValue == PIN_HIGH )
		{
			/* Using bit Set / Reset Register */
			( GPIOs[ Port ]->BSRR ) = ( 1 << PinNum ) ;
		}
		else
		{
			Local_u8ErrorStatus = NOK ;
		}

	}
	else
	{
		/* If Wrong Port Number or Pin Number is Passed */
		Local_u8ErrorStatus = NOK ;
	}
	return Local_u8ErrorStatus ;
}



/**
 * @fn			         : GPIO_u8TogglePinValue
 * @brief		         : Function To Toggle A GPIO Pin Value ( From High to Low or Vice Versa )
 * @param     Port       : USED PORT , To get Values -> @Port_t
 * @param     PinNum     : USED PIN , To get Values -> @Pin_t
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum)
{
	/* Variable to Carry ErrorStatus */
	uint8_t Local_u8ErrorStatus = OK ;

	/* Check ON PortNumber and PinNumber */
	if( ( Port <= PORTE ) && ( PinNum  <= PIN15 ) )
	{
		/* Toggle The Specified Bit */
		( GPIOs[ Port ]->ODR ) ^= ( 1 << PinNum ) ;
	}
	else
	{
		/* If Wrong Port Number or Pin Number is Passed */
		Local_u8ErrorStatus = NOK ;
	}
	return Local_u8ErrorStatus ;
}


/**
 * @Fn			         : GPIO_u8ReadPinValue
 * @brief		         : Function To Read GPIO Pin and Return in Pointer the Value on the Pin
 * @param     Port       : USED PORT , To get Values -> @Port_t
 * @param     PinNum     : USED PIN , To get Values -> @Pin_t
 * @param     PinValue   : Pointer To Put the Result init , Values -> @PinValue_t
 * @retval		         : Error Status
 *                           -> OK , NOK , NULL_POINTER
 **/

uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinValue_t *PinValue)
{
	/* Variable to Carry ErrorStatus */
	uint8_t Local_u8ErrorStatus = OK ;

	/* Check on Pointer If Carries a Valid Address */
	if( PinValue != NULL )
	{
		/* Check ON PortNumber and PinNumber */
		if( ( Port <= PORTE ) && ( PinNum  <= PIN15 ) )
		{
			*PinValue = ( ( ( GPIOs[ Port ]->IDR ) >> PinNum )&1U ) ;
		}
		else
		{
			/* If Wrong Port Number or Pin Number is Passed */
			Local_u8ErrorStatus = NOK ;
		}
	}
	else
	{
		/* If Pointer Carries NULL */
		Local_u8ErrorStatus = NULL_POINTER ;
	}

	return Local_u8ErrorStatus ;
}


/**
 * @fn			         : GPIO_u8SetFourPinsValue
 * @brief		         : Function To Value of  Four Pins
 * @param     Port       : USED PORT , To get Values -> @Port_t
 * @param     PinNum     : USED PIN ( Starting Pin to Put the Value From it ) , To get Values -> @Pin_t
 * @param     Value      : Value to Put on the Four Pins From the Starting Pin Number
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

uint8_t GPIO_u8SetFourPinsValue( Port_t PortNum , Pin_t PinNum , uint8_t Copy_u8Value  )
{
	/* Variable to Carry ErrorStatus */
	uint8_t Local_u8ErrorStatus = OK ;

	/* Check ON PortNumber and PinNumber */
	if( ( PortNum <= PORTE ) && ( PinNum <= PIN12 ) )
	{
		/* Clear the Bits */
		GPIOs[PortNum]->ODR &= ~( 0b1111 << PinNum ) ;

		/* Put the Required Value */
		GPIOs[PortNum]->ODR |=  ( Copy_u8Value << PinNum ) ;

	}
	else
	{
		/* If Wrong Port Number or Pin Number is Passed */
		Local_u8ErrorStatus = NOK ;
	}
	return Local_u8ErrorStatus ;
}


/**
 * @fn			         : GPIO_u8SetHalfPortValue
 * @brief		         : Function To Set Eight Pins ( Half Port ) Value
 * @param     PortNum    : USED PORT , To get Values -> @Port_t
 * @param     HalfPort   : USED Part of Port , To get Values -> @HalfPort_t
 * @param     Value      : Value to Put on the Eight Pins Pins
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

uint8_t GPIO_u8SetHalfPortValue( Port_t PortNum , HalfPort_t HalfPort , uint8_t Copy_u8Value )
{
	/* Variable to Carry ErrorStatus */
	uint8_t Local_u8ErrorStatus = OK ;

	/* Check ON PortNumber and HalfPortValue */
	if( ( PortNum <= PORTE ) && ( HalfPort <= UPPER_PORT ) )
	{
		if( HalfPort == LOWER_PORT )
		{
			/* LOWER HALF */
			GPIOs[PortNum]->ODR |= Copy_u8Value ;
		}
		else
		{
			/* UPPER HALF */
			GPIOs[ PortNum ]->ODR |= ( ( uint16_t )Copy_u8Value << 8 ) ;
		}

	}
	else
	{
		/* If Wrong Port Number or Half Port Value is Passed */
		Local_u8ErrorStatus = NOK ;
	}
	return Local_u8ErrorStatus ;
}


/**
 * @fn			         : GPIO_u8CheckPinConfig
 * @brief		         : Function to Check on Passed Pin Configuration if Valid or Not
 * @param     PinConfig  : Pin Configuration
 * @retval		         : PinConfigStatus ( ErrorStatus )
 *                           -> GPIO_VALID , GPIO_NOT_VALID
 * @note		         : Private Function
 **/

static uint8_t GPIO_u8CheckPinConfig(const GPIO_PinConfig_t * PinConfig )
{
	/* Variable To Carry Error Status of Pin Config  */
	uint8_t Local_u8PinConfigStatus = GPIO_VALID ;

	/* Check on All Configuration */
	if( ( PinConfig->InMode  < ANALOG ) || ( PinConfig->InMode > PULL_UP_OR_PULL_DOWN ) ||
			( PinConfig->Mode < INPUT ) || ( PinConfig->Mode > OUTPUT_MAXSPEED_50MHZ ) ||
			( PinConfig->OutMode < OUTPUT_PUSH_PULL ) || (PinConfig->OutMode > ALTERNATE_FUNC_OPEN_DRAIN )	||
			( PinConfig->PinNum < PIN0 ) || ( PinConfig->PinNum > PIN15 ) ||
			( PinConfig->Port  < PORTA ) || ( PinConfig->Port > PORTE ) ||
			( PinConfig->PullType < PULL_DOWN ) ||( PinConfig->PullType > PULL_UP ) )
	{
		/* If One of The Configurations Are Wrong */
		Local_u8PinConfigStatus = GPIO_NOT_VALID ;
	}
	return Local_u8PinConfigStatus ;
}

/**
 * @fn			          : GPIO_u8PinsInit
 * @brief		          : Function Initializes Punch of Gpio Pins Combined in Array
 * @param     PinsConfig  : Initialization Values of All Pins
 * @param     Copy_u8Size : Size of Array to Indicate for Number of Pins You want to Initialize
 * @retval		          : Error Status
 *                           -> OK , GPIO_NOK
 * @note			      : In Order to Use this Function Make in your App Array of Structs <GPIO_PinConfig_t>
 *                  Fill the array with the values and pass it by reference to the function with the size of array
 **/

uint8_t GPIO_u8PinsInit(const GPIO_PinConfig_t * PinsConfig , uint8_t Copy_u8Size )
{
	/* Variable to Carry ErrorStatus */
	uint8_t Local_u8ErrorStatus = OK ;

	/* Loop Itterator */
	uint8_t Local_u8Itterator = 0 ;

	/* Intitialize All Pins  */
	for( Local_u8Itterator = 0 ; Local_u8Itterator < Copy_u8Size ; Local_u8Itterator++ )
	{
		/* Initialize Pin and Store ErrorStatus */
        Local_u8ErrorStatus = GPIO_u8PinInit( PinsConfig ++ ) ;

        /* Check on ErrorStatus */
        if( ( GPIO_NOT_VALID == Local_u8ErrorStatus ) || ( NULL_POINTER == Local_u8ErrorStatus ) )
        {
        	/* IF GPIO didn't Work Correctly */
        	return GPIO_NOK ;
        }
	}
	return Local_u8ErrorStatus ;

}
