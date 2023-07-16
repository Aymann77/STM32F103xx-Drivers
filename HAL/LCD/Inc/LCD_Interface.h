/*
 ******************************************************************************
 * @file           : LCD_Interface.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : May 14, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#ifndef LCD_INC_LCD_INTERFACE_H_
#define LCD_INC_LCD_INTERFACE_H_


/* --------------------------------------------------------------------------------- */
/* ------------------------------- LCD COMMANDS Enum ------------------------------- */
/* --------------------------------------------------------------------------------- */

/**
 * @enum   : LCD_COM_t
 * @brief  : Holds Values of ALL COMMANDS that can be used with the LCD Module
 *
 */
typedef enum
{
	CLEAR = 0x01 , RETURN_HOME , DISPLAY_ON_CURSOR_OFF = 0x0C , FOUR_BIT_TWO_LINES_5X8 = 0x28 ,
	SHIFT_DISPLAY_RIGHT = 0x1C , SHIFT_DISPLAY_LEFT = 0x18 , INCREMENT_CURSOR_TO_RIGHT = 0x06 , DECREMENT_CURSOR_TO_LEFT = 0x04
}LCD_COM_t;



/* ------------------------------------------------------------------------------------------------ */
/* ------------------------------- FUCTION PROTOTYPES SECTION START ------------------------------- */
/* ------------------------------------------------------------------------------------------------ */

/**
 * @fn    : LCD_voidInit
 * @brief : This Function Does Initialization for LCD Pins & Initialization sequence for LCD
 * @note  : You can configure your LCD Pins from "LCD_Config" file
 *
 */
void LCD_voidInit( void ) ;

/**
 * @fn    				 : LCD_voidSendCommand
 * @brief 			     : This Function is Used to Send Command to the LCD
 * @param Copy_u8Command : Command to Send To the LCD , you can Choose From commands listed in Interface File
 */
void LCD_voidSendCommand( uint8_t Copy_u8Command ) ;


/**
 * @fn    				 : LCD_voidSendData
 * @brief 			     : This Function is Used to Send Data to the LCD
 * @param Copy_u8Data    : Data to Send To the LCD ( One Character Only )
 */
void LCD_voidSendData( uint8_t Copy_u8Data ) ;

/**
 * @fn    			     : LCD_voidSendString
 * @brief 				 : This Function Allow you to Write an Entire String on the LCD Module
 *
 * @param Copy_pu8String : String to Write on the LCD
 * @retval               : Error Status
 */
uint8_t LCD_voidSendString ( char * Copy_pu8String ) ;


/**
 * @fn    : LCD_voidShiftDisplayLeft
 * @brief : This Function Shifts the Display One Time to the Left
 *
 */

void LCD_voidShiftDisplayLeft ( void ) ;


/**
 * @fn    : LCD_voidShiftDisplayRight
 * @brief : This Function Shifts the Display One Time to the Right
 *
 */

void LCD_voidShiftDisplayRight( void ) ;


/**
 * @fn    : LCD_voidClear
 * @brief : This Function Clears the LCD Display
 *
 */

void LCD_voidClear( void ) ;


/**
 * @fn     			  : LCD_voidGoToXY
 * @brief 			  : This Function goes to a certain position on the LCD
 * @param Copy_u8XPos : Specified X_POS on LCD STARTING FROM 0 TO 15
 * @param Copy_u8YPos : Specified Y_POS on LCD STARTING FROM 0 TO 1
 */
void LCD_voidGoToXY( uint8_t Copy_u8XPos , uint8_t Copy_u8YPos ) ;



/**
 * @fn                   : LCD_voidSendNumber
 * @brief                : Function that Displays a Certain Integer Number ( Signed OR Unsigned )
 *
 * @param Copy_s32Number : Integer Number that you want to display ON LCD Module
 */

void LCD_voidSendNumber( int32_t Copy_s32Number ) ;



/**
 * @fn                				: LCD_voidStoreSpecialChar
 * @brief                           : This Function Stores a Special Charactere in CGRAM
 * @param Copy_Pu8SpecialCharacter  : Pointer to an array that is holding a special character
 * @param Copy_u8BlockNumber        : Block Number to Save Special Character IN it ( Allowed From 0 to 7 )
 * @retval                          : Error Status
 */
uint8_t LCD_voidStoreSpecialChar( uint8_t * Copy_Pu8SpecialCharacter , uint8_t Copy_u8BlockNumber ) ;


/**
 * @fn                         : LCD_voidWriteSpecialChar
 * @brief                      : This Function takes Coordinates and Pattern Number ( IN CGRAM ) which have a Special Character that will be displayed on LCD Module
 * @param Copy_u8PatternNumber : Pattern Number which Holds a Special Character Desired to be Displayed on LCD
 * @param Copy_u8X_POS         : X Position on LCD
 * @param Copy_u8Y_POS         : Y Position on LCD
 */

void LCD_voidWriteSpecialChar( uint8_t Copy_u8PatternNumber , uint8_t Copy_u8X_POS , uint8_t Copy_u8Y_POS ) ;

/* ---------------------------------------------------------------------------------------------- */
/* ------------------------------- FUCTION PROTOTYPES SECTION END ------------------------------- */
/* ---------------------------------------------------------------------------------------------- */

#endif /* LCD_INC_LCD_INTERFACE_H_ */
