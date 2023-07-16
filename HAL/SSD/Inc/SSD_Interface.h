/*
 ******************************************************************************
 * @file           : SSD_Interface.h
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
#ifndef SSD_INC_SSD_INTERFACE_H_
#define SSD_INC_SSD_INTERFACE_H_


/* ------------------------------------------------------------------------------------------------ */
/* ------------------------------- FUCTION PROTOTYPES SECTION START ------------------------------- */
/* ------------------------------------------------------------------------------------------------ */


/**
 * @fn    : SSD_voidInit
 * @brief : This Function Makes Intialization for SSD PINS ( MULTIPLIXING ) + COMMON PIN For EACH SSD All of these configurations can be found in ( SSD_Config file )
 *
 */

void SSD_voidInit( void ) ;


/**
 * @fn    				: SSD_MuxDisplayNumber
 * @brief		 		: This Function Displays a Number on a Specified SSD From the SEVEN SEGMENTS  ON PANDA KIT
 * @param Copy_u8SSDNum : SEVEN SEGMENT NUMBER TO Display a Number on it From ( 1 to 3 )
 * @param Number 		: Number To Be Displayed on a Speceific SEVEN SEGMENT From ( 0 to 9 )
 */

void SSD_MuxDisplayNumber( uint8_t Copy_u8SSDNum , uint8_t Number ) ;


/* ---------------------------------------------------------------------------------------------- */
/* ------------------------------- FUCTION PROTOTYPES SECTION END ------------------------------- */
/* ---------------------------------------------------------------------------------------------- */

#endif /* SSD_INC_SSD_INTERFACE_H_ */
