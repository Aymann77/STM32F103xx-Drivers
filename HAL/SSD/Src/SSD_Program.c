/*
 ******************************************************************************
 * @file           : SSD_Program.c
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

#include "../../../MCAL/GPIO/Inc/GPIO_Interface.h"

#include "../Inc/SSD_Interface.h"
#include "../Inc/SSD_Config.h"
#include "../Inc/SSD_Private.h"


/* ------------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------- GLOBAL VARIABLES SECTION  -------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------- */


static uint8_t SSD_Arr[3][10] =
{
		{ZERO_SSD1 , ONE_SSD1 , TWO_SSD1 , THREE_SSD1 , FOUR_SSD1 , FIVE_SSD1 ,	SIX_SSD1 , SEVEN_SSD1 , EIGHT_SSD1 , NINE_SSD1 } ,

		{ZERO_SSD2 , ONE_SSD2 , TWO_SSD2 , THREE_SSD2 , FOUR_SSD2 , FIVE_SSD2 , SIX_SSD2 , SEVEN_SSD2 , EIGHT_SSD2 , NINE_SSD2 } ,

		{ZERO_SSD3 , ONE_SSD3 , TWO_SSD3 , THREE_SSD3 , FOUR_SSD3 , FIVE_SSD3 , SIX_SSD3 , SEVEN_SSD3 , EIGHT_SSD3 , NINE_SSD3 }

} ;


static uint8_t SSD_PORT [ 8 ] = {
		LEDA_PORT , LEDB_PORT , LEDC_PORT , LEDD_PORT , LEDE_PORT , LEDF_PORT  , LEDG_PORT , DOT_PORT
};

static uint8_t SSD_PIN [ 8 ] = {
		LEDA_PIN , LEDB_PIN , LEDC_PIN , LEDD_PIN , LEDE_PIN , LEDF_PIN  , LEDG_PIN , DOT_PIN
};

static uint8_t MUX_SSD_COM_PORT[ 3 ] = {
		COM_SSD_1_PORT , COM_SSD_2_PORT , COM_SSD_3_PORT
};

static uint8_t MUX_SSD_COM_PIN[ 3 ] = {
		COM_SSD_1_PIN , COM_SSD_2_PIN , COM_SSD_3_PIN
};


/* ----------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------- MODULES IMPLEMENTATION  -------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------------------------------- */


/**
 * @fn    : SSD_voidInit
 * @brief : This Function Makes Intialization for SSD PINS ( MULTIPLIXING ) + COMMON PIN For EACH SSD All of these configurations can be found in ( SSD_Config file )
 *
 */

void SSD_voidInit( void )
{
	/* SSD LEDS Array */
	GPIO_PinConfig_t SSD_LEDS [8] =
	{
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=SSD_PORT[0] , .PinNum=SSD_PIN[0] },
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=SSD_PORT[1] , .PinNum=SSD_PIN[1] },
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=SSD_PORT[2] , .PinNum=SSD_PIN[2] },
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=SSD_PORT[3] , .PinNum=SSD_PIN[3] },
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=SSD_PORT[4] , .PinNum=SSD_PIN[4] },
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=SSD_PORT[5] , .PinNum=SSD_PIN[5] },
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=SSD_PORT[6] , .PinNum=SSD_PIN[6] },
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=SSD_PORT[7] , .PinNum=SSD_PIN[7] }

	};

	GPIO_u8PinsInit( SSD_LEDS , 8 ) ;

	/* SSD COM Array */
	GPIO_PinConfig_t SSD_COM[3] =
	{

			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=MUX_SSD_COM_PORT[0] , .PinNum=MUX_SSD_COM_PIN[0] } ,
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=MUX_SSD_COM_PORT[1] , .PinNum=MUX_SSD_COM_PIN[1] } ,
			{ .Mode = OUTPUT_MAXSPEED_2MHZ , .OutMode = OUTPUT_PUSH_PULL , .Port=MUX_SSD_COM_PORT[2] , .PinNum=MUX_SSD_COM_PIN[2] } ,

	};

	GPIO_u8PinsInit( SSD_COM , 3 ) ;

}


/**
 * @fn    				: SSD_MuxDisplayNumber
 * @brief		 		: This Function Displays a Number on a Specified SSD From the SEVEN SEGMENTS  ON PANDA KIT
 * @param Copy_u8SSDNum : SEVEN SEGMENT NUMBER TO Display a Number on it From ( 1 to 3 )
 * @param Number 		: Number To Be Displayed on a Speceific SEVEN SEGMENT From ( 0 to 9 )
 */

void SSD_MuxDisplayNumber( uint8_t Copy_u8SSDNum , uint8_t Number )
{
	uint8_t Counter = 0 ;

	/* Enable The Specified SEVEN SEGMENT */
	switch( Copy_u8SSDNum )
	{
	case 1 :
		GPIO_u8SetPinValue( MUX_SSD_COM_PORT[0] , MUX_SSD_COM_PIN[0] , PIN_HIGH ) ;
		GPIO_u8SetPinValue( MUX_SSD_COM_PORT[1] , MUX_SSD_COM_PIN[1] , PIN_LOW ) ;
		GPIO_u8SetPinValue( MUX_SSD_COM_PORT[2] , MUX_SSD_COM_PIN[2] , PIN_LOW ) ;
		break;
	case 2 :
		GPIO_u8SetPinValue( MUX_SSD_COM_PORT[0] , MUX_SSD_COM_PIN[0] , PIN_LOW ) ;
		GPIO_u8SetPinValue( MUX_SSD_COM_PORT[1] , MUX_SSD_COM_PIN[1] , PIN_HIGH ) ;
		GPIO_u8SetPinValue( MUX_SSD_COM_PORT[2] , MUX_SSD_COM_PIN[2] , PIN_LOW ) ;
		break;
	case 3 :
		GPIO_u8SetPinValue( MUX_SSD_COM_PORT[0] , MUX_SSD_COM_PIN[0] , PIN_LOW ) ;
		GPIO_u8SetPinValue( MUX_SSD_COM_PORT[1] , MUX_SSD_COM_PIN[1] , PIN_LOW ) ;
		GPIO_u8SetPinValue( MUX_SSD_COM_PORT[2] , MUX_SSD_COM_PIN[2] , PIN_HIGH ) ;
		break;

	}

/* DISPLAY The Number on the Required SSD */
	for( Counter = 0 ; Counter < 8 ; Counter ++ )
	{
		GPIO_u8SetPinValue( SSD_PORT[ Counter ] , SSD_PIN[ Counter ] , ( ( SSD_Arr[ Copy_u8SSDNum - 1 ][ Number ] >> Counter )&0x01 ) ) ;
	}

}
