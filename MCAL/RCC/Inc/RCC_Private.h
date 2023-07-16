/*
 ******************************************************************************
 * @file           : RCC_Private.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Register File
 * @version        : 1.0.1
 * @Date           : Apr 10, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 */


#ifndef RCC_RCC_PRIVATE_H_
#define RCC_RCC_PRIVATE_H_

/* SETTINGS */

/* MCO Options */
#define MCO_NO_CLK                      0b000
#define MCO_SYSCLK                      0b100
#define MCO_HSI                         0b101
#define MCO_HSE                         0b110
#define MCO_PLL_BY2                     0b111



/* ---------------------------------------------------- */
/* ----------------- Register's Masks ----------------- */
/* ---------------------------------------------------- */
#define SW_MASK                   (uint32_t)0xFFFFFFFC
#define PLL_MUL_MASK              (uint32_t)0xFFC3FFFF



/* ------------------------------------------------------------ */
/* ----------------------- Timout Value ----------------------- */
/* ------------------------------------------------------------ */
#define Timeout_MAX                         400


#endif /* RCC_RCC_PRIVATE_H_ */
