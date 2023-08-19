/*
 ******************************************************************************
 * @file           : USART_Interface.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : Aug 19, 2023
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
#ifndef USART_INC_USART_INTERFACE_H_
#define USART_INC_USART_INTERFACE_H_

/* ======================================================================
 * USART Option Enums
 * ====================================================================== */

/**
 * @brief : This Enum Holds Values of USART Peripheral Numbers
 * @enum  : @USART_t
 */
typedef enum
{
    USART_PERIPH_1 = 0,
    USART_PERIPH_2 = 1,
    USART_PERIPH_3 = 2,
    USART_MAX_NUMBER = 3,

} USART_t;

/**
 * @brief : This Enum Holds Values of All USART Flags
 * @enum  : @USART_Flag_t
 */

typedef enum
{
    USART_PARITY_ERROR = 0,      /* Parity Error */
    USART_FRAME_ERROR = 1,       /* Framing Error */
    USART_NOISE_FLAG = 2,        /* Noise Flag */
    USART_OVERRNUN_ERROR = 3,    /* OverRun Error */
    USART_IDLE_LINE_DETECT = 4,  /* IDLE Line Detected */
    USART_RDATA_REG_NEMPTY = 5,  /* Read Data Register Not Empty */
    USART_TRANSMISSION_COMP = 6, /* Transmission Complete */
    USART_TDATA_REG_EMPTY = 7,   /* Transmit Data Register Empty */
    USART_LIN_BREAK_DETECT = 8,  /* LIN Break Detection Flag */
    USART_CTS_TOGGLE = 9,        /* CTS Flag */

} USART_Flag_t;

/**
 * @brief : This Enum Holds Values of USART Flag Status
 * @enum  : @USART_FlagStatus_t
 */
typedef enum
{
    USART_FLAG_RESET = 0,
    USART_FLAG_SET = 1,

} USART_FlagStatus_t;

/**
 * @brief : This Enum Holds Values of USART Word Length Options
 * @enum : @USART_WordLength_t
 */
typedef enum
{
    USART_8_BITS_WIDTH = 0,
    USART_9_BITS_WIDTH = 1,

} USART_WordLength_t;

/**
 * @brief: This Enum Holds Values of USART Mode Options
 * @enum : @USART_Mode_t
 */
typedef enum
{
    USART_Rx = 0,    /* Receive Only */
    USART_Tx = 1,    /* Transmit Only */
    USART_Rx_Tx = 2, /* Receive and Transmit */

} USART_Mode_t;

/**
 * @brief: This Enum Holds Values of USART Parity Mode Options
 * @enum : @USART_ParityMode_t
 */
typedef enum
{
    USART_PARITY_DIS = 0,
    USART_PARITY_EN_EVEN = 1,
    USART_PARITY_EN_ODD = 2,

} USART_ParityMode_t;

/**
 * @brief: This Enum Holds Values of USART Interrupt Enable Options
 * @enum : @USART_IT_FlagEnable_t
 */
typedef enum
{
    USART_IT_FLAG_DIS = 0,
    USART_IT_FLAG_EN = 1,

} USART_IT_Flag_InitialState_t;

/**
 * @brief : This Struct Holds Values of USART Interrupt Flags to Enable or Disable Them
 * @struct: @USART_IT_FlagEnable_t
 * @note  : This Struct is Used in USART_Config_t Struct to Configure All Interrupts for a Specific USART Peripheral
 */
typedef struct
{
    USART_IT_Flag_InitialState_t ParityErrorIT;          /* Parity Error */
    USART_IT_Flag_InitialState_t TDataRegEmptyIT;        /* Transmit Data Register Empty */
    USART_IT_Flag_InitialState_t TransmissionCompleteIT; /* Transmission Complete */
    USART_IT_Flag_InitialState_t RDataRegNEmptyIT;       /* Read Data Register Not Empty */
    USART_IT_Flag_InitialState_t IDLELineDetectedIT;     /* IDLE Line Detected */
    USART_IT_Flag_InitialState_t CTSIT;                  /* CTS Flag */
    USART_IT_Flag_InitialState_t ErrorIT;                /* OverRun, Framing, Noise Error */
    USART_IT_Flag_InitialState_t LINBreakDetectedIT;     /* LIN Break Detection Flag */
} USART_IT_FlagEnable_t;

/**
 * @brief : This Enum Holds Values of USART Interrupt Types Ordered to access Call Back Function Easily
 * @enum  : @USART_IT_t
 */

typedef enum
{
    USART_IT_PE = 0,
    USART_IT_TXE = 1,
    USART_IT_TC = 2,
    USART_IT_RXNE = 3,
    USART_IT_IDLE = 4,
    USART_IT_CTS = 5,
    USART_IT_ERR = 6,
    USART_IT_LBD = 7,
    USART_IT_EIE = 8,
    USART_IT_NUM = 9,
} USART_IT_t;

/**
 * @brief : This Enum Holds Values of USART Stop Bits Options
 * @enum  : @USART_STOP_BITS_t
 */
typedef enum
{
    USART_ONE_SB = 0,
    USART_HALF_SB = 1,
    USART_TWO_SB = 2,
    USART_ONE_AND_HALF_SB = 3,

} USART_STOP_BITS_t;

/**
 * @brief : This Enum Holds Values of USART Hardware Flow Control Options
 * @enum  : @USART_HW_FLOW_CTRL_t
 */
typedef enum
{
    USART_HW_FLOW_CTRL_DIS = 0,
    USART_HW_FLOW_CTRL_EN = 1,

} USART_HW_FLOW_CTRL_t;

/**
 * @brief : This Struct Holds Values of USART Configuration Options
 * @struct: @USART_Config_t
 * @note  : This Struct is Used in USART_Init Function to Configure a Specific USART Peripheral
 */
typedef struct
{
    USART_Mode_t Mode;
    USART_t USART_Number;
    USART_WordLength_t WordLength;
    USART_ParityMode_t ParityMode;
    USART_IT_FlagEnable_t IT_FlagEnable;
    USART_STOP_BITS_t StopBits;
    USART_HW_FLOW_CTRL_t HW_FlowControlMode;
    uint32_t BaudRate;

} USART_Config_t;

/* ------------------------------------------------------------------------------------------------ */
/* ------------------------------- FUCTION PROTOTYPES SECTION START ------------------------------- */
/* ------------------------------------------------------------------------------------------------ */

/**
 * @brief  : This Function is Used to Read A Specific USART Flag
 *
 * @param  : USART_Type => This Parameter is Used to Select The USART Peripheral Number to Be Used -> @USART_t
 * @param  : Flag       => This Parameter is Used to Select The Flag to Be Read -> @USART_Flag_t
 * @param  : FlagState  => This Parameter is Used to Store The Flag State As a Return  -> @USART_FlagStatus_t
 * @return : ERRORS_t   => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReadFlag(USART_t USART_Type, USART_Flag_t Flag, USART_FlagStatus_t *FlagState);

/**
 * @brief  : This Function is Used to Initialize a Specific USART Peripheral
 * @fn     : USART_Init
 * @param  : USART_Config => This Parameter is Used to Pass The Configuration Struct to Initialize The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_Init(USART_Config_t *USART_Config);

/**
 * @brief  : This Function is Used to Receive Data Using a USART Peripheral ( Blocking Mode )
 *
 * @param  : config   => This Parameter is Used to Pass The Configuration Struct to Use it to Receive Data
 * @param  : ReceivedData     => This Parameter is Used to Return The Received Data From The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReceiveData(USART_Config_t *config, uint16_t *ReceivedData);

/**
 * @brief  : This Function is Used to Send Data Using a USART Peripheral ( Blocking Mode )
 *
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Send Data Using it
 * @param  : Data   => This Parameter is Used to Pass The Data to Be Sent Using The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_SendData(USART_Config_t *Config, uint16_t Data);

/**
 * @brief  : This Function is to Set CallBack Function to be Used in Interrupt Mode For a Specifiic Interrupt Type
 * @fn     : USART_SetCallBack
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Send String Using it
 * @param  : ITNumber   => This Parameter is Used to Pass The Interrupt Type to Set CallBack Function For it
 * @param  : Pv_CallBackFunc   => This Parameter is Used to Pass The CallBack Function to be Used in Interrupt Mode
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 * @note   : This Function Can Be Used Individually if Function You are calling use Interrupt Mode ( asycnchronous ) & Call Back Function is not One of It's
 * 		 Arguments
 */
ERRORS_t USART_SetCallBack(USART_t USARTNum, USART_IT_t ITNumber, void (*Pv_CallBackFunc)(void));

/**
 * @brief  : This Function is Used to Receive Data Using a USART Peripheral ( Non-Blocking Mode ) AKA Asycnchronous
 * @fn     : USART_SendData_IT
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Send Data Using it
 * @param  : Data   => This Parameter is Used to Pass The Variable to Be Received inside it
 * @param  : pv_CallBackFunc   => This Parameter is Used to Pass The CallBack Function to be Used in Interrupt Mode
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReceiveData_IT(USART_Config_t *Config, uint16_t *ReceivedData, void (*pv_CallBackFunc)(void));

/**
 * @brief  : This Function is Used to Send String Using a USART Peripheral ( Non-Blocking Mode )
 * @fn     : USART_SendBuffer
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Send String Using it
 * @param  : Data   => This Parameter is Used to Pass The Buffer of Data to Be Sent Using The USART Peripheral
 * @param  : Size   => This Parameter is Used to Pass The Size of The Buffer to Be Sent Using The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_SendBuffer(USART_Config_t *Configuration, uint8_t *Data, uint8_t Size);

/**
 * @brief  : This Function is Used to Receive String Using a USART Peripheral ( Blocking Mode )
 * @fn     :  USART_ReceiveBuffer
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Receive String Using it
 * @param  : ReceivedData   => This Parameter is Used to Pass The Buffer of Data to Be Received inside it Using The USART Peripheral
 * @param  : Size   => This Parameter is Used to Pass The Size of The Buffer to Be Received Using The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReceiveBuffer(USART_Config_t *Config, uint8_t *ReceivedData, uint8_t Size);

/**
 * @brief  : This Function is Used to Enable DMA Receiver
 * @fn     : USART_EnableDMAReceiver
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Enable DMA Receiver
 * @return :  ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_EnableDMAReceiver(USART_Config_t *Config);

/**
 * @brief  : This Function is Used to Enable DMA Transmitter
 * @fn     : USART_EnableDMATransmitter
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Enable DMA Transmitter
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_EnableDMATransmitter(USART_Config_t *Config);

/**
 * @brief  : This Function is Used to Enable USART Interrupts
 *
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Enable The Interrupts
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 * @note   : This Function is Used Inside USART_Init Function to Enable Interrupts , you can use it to Enable Interrupts Individually
 */
ERRORS_t USART_EnableIT(USART_Config_t *Config);

/**
 * @brief  : This Function is Used to Send Data Using a USART Peripheral ( Non-Blocking Mode ) AKA Asycnchronous
 * @fn     : USART_SendData_IT
 * @param  : Configuration => This Parameter is Used to Pass The Configuration Struct to Send Data Using it
 * @param  : Data => This Parameter is Used to Pass The Data to Be Sent Using The USART Peripheral
 * @param  : pv_CallBack_Func => This Parameter is Used to Pass The CallBack Function to be Used in Interrupt Mode to be invoked when Interrupt Occurs
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_SendData_IT(USART_Config_t *Configuration, uint16_t Data, void (*pv_CallBack_Func)(void));

/**
 * @brief  : This Function is Used to Send String Using a USART Peripheral ( Non-Blocking Mode ) AKA Asycnchronous
 * @fn     : USART_SendBuffer_IT
 * @param  : Config  => This Parameter is Used to Pass The Configuration Struct to Send String Using it
 * @param  : DataBuffer => This Parameter is Used to Pass The Buffer of Data to Be Sent Using The USART Peripheral
 * @param  : BufferSize => This Parameter is Used to Pass The Size of The Buffer to Be Sent Using The USART Peripheral
 * @param  : pv_CallBackFunc => This Parameter is Used to Pass The CallBack Function to be Used in Interrupt Mode to be invoked when Interrupt Occurs
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_SendBuffer_IT(USART_Config_t *Config, uint8_t *DataBuffer, uint8_t BufferSize, void (*pv_CallBackFunc)(void));

/**
 * @brief  : This Function is Used to Receive a Buffer of Data Using a USART Peripheral ( Non-Blocking Mode ) AKA Asycnchronous
 * @fn     : USART_ReceiveBuffer_IT
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Receive Buffer Using it
 * @param  : ReceiveBuffer => This Parameter is Used to Pass The Buffer of Data to Be Received inside it Using The USART Peripheral
 * @param  : BufferSize => This Parameter is Used to Pass The Size of The Buffer to Be Received Using The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReceiveBuffer_IT(USART_Config_t *Config, uint8_t *ReceiveBuffer, uint8_t BufferSize, void(*pv_CallBackFunc));
/* ---------------------------------------------------------------------------------------------- */
/* ------------------------------- FUCTION PROTOTYPES SECTION END ------------------------------- */
/* ---------------------------------------------------------------------------------------------- */

#endif /* USART_INC_USART_INTERFACE_H_ */
