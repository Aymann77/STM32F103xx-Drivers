/*
 ******************************************************************************
 * @file           : LCD_Program.c
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : May 14, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */

/* ----------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------- INCLUDES SECTION  -------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------------------------- */

#include <stdint.h>

#include "../../../LIB/ErrType.h"
#include "../../../LIB/STM32F103xx.h"

#include "../../../MCAL/GPIO/Inc/GPIO_Interface.h"
#include "../../../MCAL/SYSTICK/Inc/SYSTICK_Interface.h"

#include "../Inc/LCD_Interface.h"
#include "../Inc/LCD_Config.h"
#include "../Inc/LCD_Private.h"



/* ----------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------- MODULES IMPLEMENTATION  -------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------------------------------- */

/**
 * @fn    : LCD_voidInit
 * @brief : This Function Does Initialization for LCD Pins & Initialization sequence for LCD
 * @note  : You can configure your LCD Pins from "LCD_Config" file
 *
 */

void LCD_voidInit( void )
{
	/* PINS INITIALIZATION */
	GPIO_PinConfig_t LCD_Pins [6] =
	{
			/* RS PIN */
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode= OUTPUT_PUSH_PULL , .Port = CTRL_PORT , .PinNum = RS_PIN } ,

			/* EN PIN */
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode= OUTPUT_PUSH_PULL , .Port = CTRL_PORT , .PinNum = EN_PIN } ,

			/* D4 Pin */
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode= OUTPUT_PUSH_PULL , .Port = DATA_PORT , .PinNum = D4_PIN } ,

			/* D5 Pin */
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode= OUTPUT_PUSH_PULL , .Port = DATA_PORT , .PinNum = D5_PIN } ,

			/* D6 Pin */
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode= OUTPUT_PUSH_PULL , .Port = DATA_PORT , .PinNum = D6_PIN } ,

			/* D7 Pin */
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode= OUTPUT_PUSH_PULL , .Port = DATA_PORT , .PinNum = D7_PIN }

	} ;

	/* Init */
	GPIO_u8PinsInit( LCD_Pins , 6 ) ;

	SYSTICK_Delayms(50);

	/* LCD_INTIALIZATION COMMANDS */
	LCD_voidSendCommand( FOUR_BIT_TWO_LINES_5X8 ); /* Function Set  : 4-bit LCD , 2Line Display , 5*8 Font */
	LCD_voidSendCommand( DISPLAY_ON_CURSOR_OFF ); /* Diplay ON/OFF : Display ON , Cursor OFF , Blink OFF */
	LCD_voidClear(  ) ; /* Clear */
	LCD_voidSendCommand( RETURN_HOME ) ;

	SYSTICK_Delayms(2);
}


/**
 * @fn    				 : LCD_voidSendCommand
 * @brief 			     : This Function is Used to Send Command to the LCD
 * @param Copy_u8Command : Command to Send To the LCD , you can Choose From commands listed in Interface File
 */

void LCD_voidSendCommand( uint8_t Copy_u8Command )
{
	uint8_t Local_u8Counter = 0 ;
	uint8_t Local_u8Bit = 0 ;
	uint8_t FLipped_Command = 0 ;

	/* For Command */
	GPIO_u8SetPinValue( CTRL_PORT , RS_PIN , PIN_LOW ) ;

	/* Flip The Entire Command Into Another Variable */
	for( Local_u8Counter = 0 ; Local_u8Counter < 8 ; Local_u8Counter++ )
	{

		Local_u8Bit = ( ( Copy_u8Command >> Local_u8Counter )& 0x01 ) ;
		/* Check on the Bit */
		if( Local_u8Bit == 0 )
			FLipped_Command &= ~(1<<(7-Local_u8Counter));
		else
			FLipped_Command |= ( 1 << ( 7-Local_u8Counter ) ) ;
	}

	/*Set First the Higher Bits of The Command	 */
	GPIO_u8SetFourPinsValue( DATA_PORT , D7_PIN  , ( ( FLipped_Command & 0x0F )  ) ) ;

	/* Enable Pulse */
	GPIO_u8SetPinValue( CTRL_PORT , EN_PIN , PIN_HIGH ) ;

	SYSTICK_Delayms( 2 ) ;

	GPIO_u8SetPinValue( CTRL_PORT , EN_PIN , PIN_LOW ) ;

	/*Set Second the Lower Bits of The Command	 */
	GPIO_u8SetFourPinsValue( DATA_PORT ,D7_PIN  , ( ( FLipped_Command & 0xF0 ) >> 4 ) ) ;


	/* Enable Pulse */
	GPIO_u8SetPinValue( CTRL_PORT , EN_PIN , PIN_HIGH ) ;

	SYSTICK_Delayms( 2 ) ;

	GPIO_u8SetPinValue( CTRL_PORT , EN_PIN , PIN_LOW ) ;

}


/**
 * @fn    				 : LCD_voidSendData
 * @brief 			     : This Function is Used to Send Data to the LCD
 * @param Copy_u8Data    : Data to Send To the LCD ( One Character Only )
 */

void LCD_voidSendData( uint8_t Copy_u8Data )
{
	uint8_t Local_u8Counter = 0 ;
	uint8_t Local_u8Bit = 0 ;
	uint8_t FLipped_Byte = 0 ;

	/* For Data */
	GPIO_u8SetPinValue( CTRL_PORT , RS_PIN , PIN_HIGH ) ;

	/* Flip The Entire Command Into Another Variable */
	for( Local_u8Counter = 0 ; Local_u8Counter < 8 ; Local_u8Counter++ )
	{

		Local_u8Bit = ( ( Copy_u8Data >> Local_u8Counter )& 0x01 ) ;
		/* Check on the Bit */
		if( Local_u8Bit == 0 )
			FLipped_Byte &= ~(1<<(7-Local_u8Counter));
		else
			FLipped_Byte |= ( 1 << ( 7-Local_u8Counter ) ) ;
	}

	/*Set First the Higher Bits of The Byte	 */
	GPIO_u8SetFourPinsValue( DATA_PORT , D7_PIN  , ( FLipped_Byte & 0x0F ) ) ;

	/* Enable Pulse */
	GPIO_u8SetPinValue( CTRL_PORT , EN_PIN , PIN_HIGH ) ;

	SYSTICK_Delayms( 2 ) ;

	GPIO_u8SetPinValue( CTRL_PORT , EN_PIN , PIN_LOW ) ;

	/*Set Second the Lower Bits of The Byte	 */
	GPIO_u8SetFourPinsValue( DATA_PORT ,D7_PIN  , ( ( FLipped_Byte & 0xF0 ) >> 4 ) ) ;

	/* Enable Pulse */
	GPIO_u8SetPinValue( CTRL_PORT , EN_PIN , PIN_HIGH ) ;

	SYSTICK_Delayms( 2 ) ;

	GPIO_u8SetPinValue( CTRL_PORT , EN_PIN , PIN_LOW ) ;

}


/**
 * @fn    			     : LCD_voidSendString
 * @brief 				 : This Function Allow you to Write an Entire String on the LCD Module
 *
 * @param Copy_pu8String : String to Write on the LCD
 * @retval               : Error Status
 */
uint8_t LCD_voidSendString ( char * Copy_pu8String )
{
	uint8_t Local_u8ErrorStatus = OK ;
	uint8_t Local_u8Counter = 0 ;

	if( NULL != Copy_pu8String  )
	{
		while( '\0' != Copy_pu8String[ Local_u8Counter ]  )
		{
			LCD_voidSendData( Copy_pu8String[ Local_u8Counter ] ) ;
			Local_u8Counter ++ ;
		}

	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER ;
	}
	return Local_u8ErrorStatus ;
}


/**
 * @fn    : LCD_voidClear
 * @brief : This Function Clears the LCD Display
 *
 */

void LCD_voidClear( void )
{
	LCD_voidSendCommand( CLEAR ) ;
}

/**
 * @fn    : LCD_voidShiftDisplayRight
 * @brief : This Function Shifts the Display One Time to the Right
 *
 */

void LCD_voidShiftDisplayRight( void )
{
	LCD_voidSendCommand( SHIFT_DISPLAY_RIGHT ) ;
}


/**
 * @fn    : LCD_voidShiftDisplayLeft
 * @brief : This Function Shifts the Display One Time to the Left
 *
 */

void LCD_voidShiftDisplayLeft ( void )
{
	LCD_voidSendCommand( SHIFT_DISPLAY_LEFT ) ;
}


/**
 * @fn     			  : LCD_voidGoToXY
 * @brief 			  : This Function goes to a certain position on the LCD
 * @param Copy_u8XPos : Specified X_POS on LCD STARTING FROM 0 TO 15
 * @param Copy_u8YPos : Specified Y_POS on LCD STARTING FROM 0 TO 1
 */
void LCD_voidGoToXY( uint8_t Copy_u8XPos , uint8_t Copy_u8YPos )
{
	uint8_t Local_u8Address = 0 ;

	switch ( Copy_u8YPos )
	{
	/* First ROW */
	case 0 :  Local_u8Address = Copy_u8XPos + ADD_OF_FIRST_POS_IN_FIRST_ROW ; break ;

	/* Second ROW */
	case 1 :  Local_u8Address = Copy_u8XPos + ADD_OF_FIRST_POS_IN_SECOND_ROW ; break ;
	}

	LCD_voidSendCommand( Local_u8Address ) ;
}


/**
 * @fn                   : LCD_voidSendNumber
 * @brief                : Function that Displays a Certain Integer Number ( Signed OR Unsigned )
 *
 * @param Copy_s32Number : Integer Number that you want to display ON LCD Module
 */

void LCD_voidSendNumber( int32_t Copy_s32Number )
{
	/* Array to Holds the Digits of the Number */
	uint8_t Local_u8DigitsArr [ 10 ] = { } ;

	uint8_t Local_u8Counter = 0  , Local_u8LoopItterator = 0 ;

	/* Flag to Indicate if Number is Negative */
	uint8_t Local_u8NegativeNumber = 0 ;

	/* Check on Number IF Negative to Set the Flag */
	if( Copy_s32Number < 0 )
	{
		Local_u8NegativeNumber = 1 ;
		Copy_s32Number = Copy_s32Number * -1 ;
	}

	/* Divide Number into Digits and Put Each Digit Inside Array */
	while( 0 != Copy_s32Number  )
	{
		Local_u8DigitsArr[ Local_u8Counter ] = Copy_s32Number % 10 ;
		Copy_s32Number = Copy_s32Number / 10 ;
		Local_u8Counter ++ ;
	}

	/* If Number is Negative Type First Negative Sign */
	if( Local_u8NegativeNumber == 1 )
	{
		LCD_voidSendData('-') ;
	}

	/* Print Contents of Array By Reverse on LCD Module */
	for( Local_u8LoopItterator = 0 ; Local_u8LoopItterator < Local_u8Counter ; Local_u8LoopItterator++  )
	{
		LCD_voidSendData( Local_u8DigitsArr[ Local_u8Counter - Local_u8LoopItterator - 1 ] + '0'  ) ;
	}
}


/**
 * @fn                				: LCD_voidStoreSpecialChar
 * @brief                           : This Function Stores a Special Charactere in CGRAM
 * @param Copy_Pu8SpecialCharacter  : Pointer to an array that is holding a special character
 * @param Copy_u8BlockNumber        : Block Number to Save Special Character IN it ( Allowed From 0 to 7 )
 * @retval                          : Error Status
 */
uint8_t LCD_voidStoreSpecialChar( uint8_t * Copy_Pu8SpecialCharacter , uint8_t Copy_u8BlockNumber )
{
	uint8_t Local_ErrorStatus = 0 ;
	uint8_t Local_u8Counter = 0 ;

	if( NULL != Copy_Pu8SpecialCharacter )
	{
		/* First Address in Specified Block in CGRAM */
		uint8_t Local_u8CGRAMAddress = CGRAM_FIRST_ADDRESS + ( LOCATION_SIZE_IN_CGRAM * Copy_u8BlockNumber ) ;

		/* To Set CGRAM Address to Start Storing the Pattern */
		LCD_voidSendCommand( Local_u8CGRAMAddress ) ;

		/* Storing the Pattern Byte By Byte */
		for( Local_u8Counter = 0 ; Local_u8Counter < 8 ; Local_u8Counter++ )
		{
			LCD_voidSendData( Copy_Pu8SpecialCharacter[Local_u8Counter] ) ;
		}
	}
	else
	{
		Local_ErrorStatus = NULL_POINTER ;
	}
	return Local_ErrorStatus ;
}

/**
 * @fn                         : LCD_voidWriteSpecialChar
 * @brief                      : This Function takes Coordinates and Pattern Number ( IN CGRAM ) which have a Special Character that will be displayed on LCD Module
 * @param Copy_u8PatternNumber : Pattern Number which Holds a Special Character Desired to be Displayed on LCD
 * @param Copy_u8X_POS         : X Position on LCD
 * @param Copy_u8Y_POS         : Y Position on LCD
 */

void LCD_voidWriteSpecialChar( uint8_t Copy_u8PatternNumber , uint8_t Copy_u8X_POS , uint8_t Copy_u8Y_POS )
{
	/* Go to a Specific Position and Display the Special Character */
	LCD_voidGoToXY( Copy_u8X_POS , Copy_u8Y_POS ) ;

	LCD_voidSendData( Copy_u8PatternNumber ) ;
}
