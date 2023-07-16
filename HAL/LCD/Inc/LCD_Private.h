/*
 ******************************************************************************
 * @file           : LCD_Private.h
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
#ifndef LCD_INC_LCD_PRIVATE_H_
#define LCD_INC_LCD_PRIVATE_H_

/*==============================================================================================================================================
 * MACROS
 *==============================================================================================================================================*/

#define ADD_OF_FIRST_POS_IN_FIRST_ROW    ( 0x80UL )
#define ADD_OF_FIRST_POS_IN_SECOND_ROW   ( 0x80UL + 0x40UL )

#define CGRAM_FIRST_ADDRESS  ( 64UL )
#define LOCATION_SIZE_IN_CGRAM ( 8UL )

#endif /* LCD_INC_LCD_PRIVATE_H_ */
