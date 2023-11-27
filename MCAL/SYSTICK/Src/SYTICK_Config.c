/*
 ******************************************************************************
 * @file           : SYTICK_Config.c
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : May 12, 2023
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
#include <stdint.h>

#include "../Inc/SYSTICK_Interface.h"


/* For Options Refer To Interface @SYSTICK_EXCEPTION_t  &  @SYSTICK_CLK_SOURCE_t */

SYSTICK_CONFIG_t SYSTICK_TIMER_CONFIG =
{
   .CLK = SYSTICK_AHB_BY8 , .CPU_FREQUENCY = 8000000UL
};

