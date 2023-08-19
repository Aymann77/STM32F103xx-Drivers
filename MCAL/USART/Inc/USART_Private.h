/*
 ******************************************************************************
 * @file           : USART_Private.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : Aug 19, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */
#ifndef USART_INC_USART_PRIVATE_H_
#define USART_INC_USART_PRIVATE_H_

/* ======================================================================
 * PRIVATE FUNCTION
 * ====================================================================== */

/**
 * @brief  : This Function is Used to Check The Configuration of USART Peripheral
 *
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Check it
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
static ERRORS_t USART_CheckConfig(USART_Config_t *Config);

/**
 * @brief  : This Function is Used to Set The Parity Mode of USART Peripheral
 *
 * @param  : UsartNum => This Parameter is Used to Select The USART Peripheral Number to Be Used -> @USART_t
 * @param  : Parity   => This Parameter is Used to Select The Parity Mode to Be Used -> @USART_ParityMode_t
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
static ERRORS_t USART_SetParity(USART_t UsartNum, USART_ParityMode_t Parity);

/**
 * @brief  : This Function is Used to Set The Mode of USART Peripheral
 *
 * @param  : UsartNum => This Parameter is Used to Select The USART Peripheral Number to Be Used -> @USART_t
 * @param  : Mode     => This Parameter is Used to Select The Mode to Be Used -> @USART_Mode_t
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
static ERRORS_t USART_SetMode(USART_t UsartNum, USART_Mode_t Mode);

/**
 * @brief  : This Function is Used to Set The BaudRate of USART Peripheral
 *
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Set The BaudRate
 * @return : void
 */
static void USART_SetBaudRate(USART_Config_t *Config);

/**
 * @brief  : This Function is Used to Handle The Interrupts of USART Peripheral
 * @fn	   : USART_HANDLE_IT
 * @param  : USARTNum => This Parameter is Used to Select The USART Peripheral Number to Be Used -> @USART_t
 * @return : void
 * @note   : This Function is Used Inside All IRQ Handlers to Handle The Interrupts ( Private Function )
 */
static void USART_HANDLE_IT(USART_t USARTNum);

/* ======================================================================
 * PRIVATE MACROS
 * ====================================================================== */
#define USART_M_MASK 0xEFFF
#define USART_PEIE_MASK 0xFEFF
#define USART_TXEIE_MASK 0xFF7F
#define USART_TCIE_MASK 0xFFBF
#define USART_RXNEIE_MASK 0xFFDF
#define USART_IDLEIE_MASK 0xFFEF
#define USART_LBDIE_MASK 0xFFBF
#define USART_CTSIE_MASK 0xFBFF
#define USART_EIE_MASK 0xFFFE
#define USART_STOP_MASK 0xCFFF

#define USART_CLEAR_PARITY_8_MASK 0x7F
#define USART_CLEAR_PARITY_9_MASK 0xFF

/* ======================================================================
 * PRIVATE ENUMS
 * ====================================================================== */

typedef enum
{
    USART_NO_SRC = 0,
    USART_RECEIVE_DATA = 1,
    USART_SEND_DATA = 2,
    USART_SEND_BUFFER = 3,
    USART_RECEIVE_BUFFER = 4,

} USART_IRQ_SRC_t;

#endif /* USART_INC_USART_PRIVATE_H_ */
