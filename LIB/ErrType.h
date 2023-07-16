/*
 ******************************************************************************
 * @file           : ErrType.h
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
#ifndef ERRTYPE_H_
#define ERRTYPE_H_

/*==============================================================================================================================================
 * ERRORS
 *==============================================================================================================================================*/

typedef enum
{
	OK,
	NOK,
	NULL_POINTER,
	GPIO_NOK,
	GPIO_NOT_VALID,
	GPIO_VALID,
	TimeoutError,
	PLLMULFactorError,
	PLLSRCError,
	AHBEnPeripheralError,
	AHBDisPeripheralError,
	APB1EnPeripheralError,
	APB1DisPeripheralError,
	APB2EnPeripheralError,
	APB2DisPeripheralError

}ERRORS_t;


#endif /* ERRTYPE_H_ */
