/*
 ******************************************************************************
 * @file           : GPIO_Private.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : May 8, 2023
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
#ifndef GPIO_INC_GPIO_PRIVATE_H_
#define GPIO_INC_GPIO_PRIVATE_H_

/*==============================================================================================================================================
 * MASKS
 *==============================================================================================================================================*/
#define MODE_BITS_MASK          0x3U
#define MODE_BITS_PIN_ACCESS    0x4U

#define CNF_BITS_MASK          0xCU
#define CNF_BITS_PIN_ACCESS    0x4U

/*==============================================================================================================================================
 * PRIVATE FUNCTIONS
 *==============================================================================================================================================*/

/**
 * @fn			         : GPIO_u8CheckPinConfig
 * @brief		         : Function to Check on Passed Pin Configuration if Valid or Not
 * @param     PinConfig  : Pin Configuration
 * @retval		         : PinConfigStatus ( ErrorStatus )
 *                           -> GPIO_VALID , GPIO_NOT_VALID
 * @note		         : Private Function
 **/

static uint8_t GPIO_u8CheckPinConfig(const GPIO_PinConfig_t * PinConfig );

#endif /* GPIO_INC_GPIO_PRIVATE_H_ */
