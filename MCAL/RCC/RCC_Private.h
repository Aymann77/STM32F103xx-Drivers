/*
 ******************************************************************************
 * @file           : RCC_Private.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Private File
 * @Date           : Apr 10, 2023
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
#ifndef RCC_RCC_PRIVATE_H_
#define RCC_RCC_PRIVATE_H_

/* SETTINGS */

/* MCO Options */
#define MCO_NO_CLK      0b000
#define MCO_SYSCLK      0b100
#define MCO_HSI         0b101
#define MCO_HSE         0b110
#define MCO_PLL_BY2     0b111



/* ---------------------------------------------------- */
/* ----------------- Register's Masks ----------------- */
/* ---------------------------------------------------- */

#define SW_MASK            (uint32_t)0xFFFFFFFC
#define PLL_MUL_MASK       (uint32_t)0xFFC3FFFF





/* ************** RCC Peripheral Base Address ************** */
#define RCC_BASE_ADD          ( ( RCC_Reg_t *) 0x40021000 )


/* ********************** Timeout VALUE ********************** */
#define Timeout_MAX                        300


#endif /* RCC_RCC_PRIVATE_H_ */
