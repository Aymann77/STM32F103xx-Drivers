/*
 ******************************************************************************
 * @file           : USART_Program.c
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : Aug 17, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */

/*==============================================================================================================================================
 * INCLUDES SECTION START
 *==============================================================================================================================================*/

#include <stdint.h>

#include "../../../LIB/STM32F103xx.h"
#include "../../../LIB/ErrType.h"

#include "../Inc/USART_Interface.h"
#include "../Inc/USART_Config.h"
#include "../Inc/USART_Private.h"

/*==============================================================================================================================================
 * INCLUDES SECTION END
 *==============================================================================================================================================*/

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION START
 *==============================================================================================================================================*/

static USART_RegDef_t *USART[USART_MAX_NUMBER] = {USART1, USART2, USART3};

static void (*USART_PTR_TO_FUNC[USART_MAX_NUMBER][USART_IT_NUM])(void) = {NULL};

static uint16_t *USART_ReceivedData[USART_MAX_NUMBER] = {NULL};

static uint8_t *USART_SentBuffer[USART_MAX_NUMBER] = {NULL};

static uint8_t *USART_ReceivedBuffer[USART_MAX_NUMBER] = {NULL};

static uint8_t USART_SentbufferSize[USART_MAX_NUMBER] = {0};

static uint8_t USART_ReceivebufferSize[USART_MAX_NUMBER] = {0};

static USART_IRQ_SRC_t IRQ_SRC[USART_MAX_NUMBER] = {USART_NO_SRC};
/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION END
 *==============================================================================================================================================*/

/*==============================================================================================================================================
 * MODULES IMPLEMENTATION
 *==============================================================================================================================================*/

/**
 * @brief  : This Function is Used to Read A Specific USART Flag
 *
 * @param  : USART_Type => This Parameter is Used to Select The USART Peripheral Number to Be Used -> @USART_t
 * @param  : Flag       => This Parameter is Used to Select The Flag to Be Read -> @USART_Flag_t
 * @param  : FlagState  => This Parameter is Used to Store The Flag State As a Return  -> @USART_FlagStatus_t
 * @return : ERRORS_t   => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReadFlag(USART_t USART_Type, USART_Flag_t Flag, USART_FlagStatus_t *FlagState)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if (USART_Type < USART_PERIPH_1 || USART_Type > USART_PERIPH_3 ||
        Flag < USART_PARITY_ERROR || Flag > USART_CTS_TOGGLE)
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    else
    {
        /* Configurations Are OK */

        *FlagState = ((USART[USART_Type]->SR >> Flag) & 1);
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Initialize a Specific USART Peripheral
 * @fn     : USART_Init
 * @param  : USART_Config => This Parameter is Used to Pass The Configuration Struct to Initialize The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_Init(USART_Config_t *USART_Config)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if (USART_WRONG_CONFIGURATION != USART_CheckConfig(USART_Config))
    {
        /* Correct Configurations are Handled */

        /* Enable USART */
        USART[USART_Config->USART_Number]->CR1 |= (1 << UE);

        /* Set Word Length */
        USART[USART_Config->USART_Number]->CR1 &= (USART_M_MASK);
        USART[USART_Config->USART_Number]->CR1 |= (USART_Config->WordLength << M);

        /* Set Parity Mode Selected */
        USART_SetParity(USART_Config->USART_Number, USART_Config->ParityMode);

        /* Set All Configured Interrupt to there Initial States */
        USART_EnableIT(USART_Config);

        /* Set Stop Bits */
        USART[USART_Config->USART_Number]->CR2 &= (USART_STOP_MASK);
        USART[USART_Config->USART_Number]->CR2 |= (USART_Config->StopBits << STOP);

        /* Set BaudRate */
        USART_SetBaudRate(USART_Config);

        /* Set HW Flow Control */
        if (USART_Config->HW_FlowControlMode == USART_HW_FLOW_CTRL_DIS)
        {
            USART[USART_Config->USART_Number]->CR3 &= (~((1 << CTSE) | (1 << RTSE)));
        }
        else
        {
            /* Enable Both RTS & CTS */
            USART[USART_Config->USART_Number]->CR3 |= (1 << CTSE) | (1 << RTSE);
        }

        /* Set USART Mode */
        USART_SetMode(USART_Config->USART_Number, USART_Config->Mode);
    }
    else
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Receive Data Using a USART Peripheral ( Blocking Mode )
 *
 * @param  : config   => This Parameter is Used to Pass The Configuration Struct to Use it to Receive Data
 * @param  : ReceivedData     => This Parameter is Used to Return The Received Data From The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReceiveData(USART_Config_t *config, uint16_t *ReceivedData)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    USART_FlagStatus_t FlagState = USART_FLAG_RESET;

    if (NULL != ReceivedData)
    {

        while (USART_FLAG_SET != FlagState)
        {
            USART_ReadFlag(config->USART_Number, USART_RDATA_REG_NEMPTY, &FlagState);
        }

        *ReceivedData = USART[config->USART_Number]->DR;

        if (USART_PARITY_DIS != config->ParityMode)
        {
            /* Parity is Enabled */
            if (config->WordLength == USART_8_BITS_WIDTH)
            {
                /* Clear Parity Bit */
                *ReceivedData &= (USART_CLEAR_PARITY_8_MASK);
            }
            else if (config->WordLength == USART_8_BITS_WIDTH)
            {
                /* Clear Parity Bit */
                *ReceivedData &= (USART_CLEAR_PARITY_9_MASK);
            }
        }
    }
    else
    {
        Local_u8ErrorStatus = NULL_POINTER;
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Send Data Using a USART Peripheral ( Blocking Mode )
 *
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Send Data Using it
 * @param  : Data   => This Parameter is Used to Pass The Data to Be Sent Using The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_SendData(USART_Config_t *Config, uint16_t Data)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    USART_FlagStatus_t FlagStatus = USART_FLAG_RESET;

    if (USART_WRONG_CONFIGURATION != USART_CheckConfig(Config))
    {
        /* Configurations are OK */

        /* Wait Until Transmission Data Register Empty Flag is Set */

        while (USART_FLAG_SET != FlagStatus)
        {
            USART_ReadFlag(Config->USART_Number, USART_TDATA_REG_EMPTY, &FlagStatus);
        }

        /* Send Data */
        USART[Config->USART_Number]->DR = Data;

        /* Wait Untill Transmission Complete Flag is Set */
        FlagStatus = USART_FLAG_RESET;

        while (USART_FLAG_SET != FlagStatus)
        {
            USART_ReadFlag(Config->USART_Number, USART_TRANSMISSION_COMP, &FlagStatus);
        }
    }
    else
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    return Local_u8ErrorStatus;
}

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
ERRORS_t USART_SetCallBack(USART_t USARTNum, USART_IT_t ITNumber, void (*Pv_CallBackFunc)(void))
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if (USARTNum < USART_PERIPH_1 || USARTNum > USART_PERIPH_3 ||
        ITNumber < USART_IT_PE || ITNumber > USART_IT_EIE)
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    else
    {
        if (NULL != Pv_CallBackFunc)
        {
            USART_PTR_TO_FUNC[USARTNum][ITNumber] = Pv_CallBackFunc;
        }
        else
        {
            Local_u8ErrorStatus = NULL_POINTER;
        }
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Receive Data Using a USART Peripheral ( Non-Blocking Mode ) AKA Asycnchronous
 * @fn     : USART_SendData_IT
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Send Data Using it
 * @param  : Data   => This Parameter is Used to Pass The Variable to Be Received inside it
 * @param  : pv_CallBackFunc   => This Parameter is Used to Pass The CallBack Function to be Used in Interrupt Mode
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReceiveData_IT(USART_Config_t *Config, uint16_t *ReceivedData, void (*pv_CallBackFunc)(void))
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if ((NULL != ReceivedData) && (NULL != pv_CallBackFunc))
    {
        /* Setting IRQ Source */
        IRQ_SRC[Config->USART_Number] = USART_RECEIVE_DATA;

        /* Setting Global Variable */
        USART_ReceivedData[Config->USART_Number] = ReceivedData;

        /* Setting Call Back Function */
        USART_PTR_TO_FUNC[Config->USART_Number][USART_IT_RXNE] = pv_CallBackFunc;

        /* Enable Read Data Register Not Empty Interrupt */
        USART[Config->USART_Number]->CR1 |= (1 << RXNEIE);
    }
    else
    {
        Local_u8ErrorStatus = NULL_POINTER;
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Send String Using a USART Peripheral ( Non-Blocking Mode )
 * @fn     : USART_SendBuffer
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Send String Using it
 * @param  : Data   => This Parameter is Used to Pass The Buffer of Data to Be Sent Using The USART Peripheral
 * @param  : Size   => This Parameter is Used to Pass The Size of The Buffer to Be Sent Using The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_SendBuffer(USART_Config_t *Configuration, uint8_t *Data, uint8_t Size)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    uint8_t Local_u8Counter = 0;

    if ((NULL != Configuration) && (NULL != Data))
    {
        /* Send Buffer Elements One By One */
        for (Local_u8Counter = 0; Local_u8Counter < Size; Local_u8Counter++)
        {
            USART_SendData(Configuration, (uint16_t)Data[Local_u8Counter]);
        }
    }
    else
    {
        Local_u8ErrorStatus = NULL_POINTER;
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Receive String Using a USART Peripheral ( Blocking Mode )
 * @fn     :  USART_ReceiveBuffer
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Receive String Using it
 * @param  : ReceivedData   => This Parameter is Used to Pass The Buffer of Data to Be Received inside it Using The USART Peripheral
 * @param  : Size   => This Parameter is Used to Pass The Size of The Buffer to Be Received Using The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReceiveBuffer(USART_Config_t *Config, uint8_t *ReceivedData, uint8_t Size)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    uint8_t Local_u8Counter = 0;

    if ((NULL != Config) && (NULL != ReceivedData))
    {
        /* Receive Buffer Elements One By One */
        for (Local_u8Counter = 0; Local_u8Counter < Size; Local_u8Counter++)
        {
            USART_ReceiveData(Config, (uint16_t *)&ReceivedData[Local_u8Counter]);
        }
    }
    else
    {
        Local_u8ErrorStatus = NULL_POINTER;
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Enable DMA Receiver
 * @fn     : USART_EnableDMAReceiver
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Enable DMA Receiver
 * @return :  ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_EnableDMAReceiver(USART_Config_t *Config)
{
    ERRORS_t Local_u8ErrorState = USART_OK;

    if (USART_WRONG_CONFIGURATION != USART_CheckConfig(Config))
    {
        /* Enable DMA Receiver */
        USART[Config->USART_Number]->CR3 |= (1 << DMAR);
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}

/**
 * @brief  : This Function is Used to Enable DMA Transmitter
 * @fn     : USART_EnableDMATransmitter
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Enable DMA Transmitter
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_EnableDMATransmitter(USART_Config_t *Config)
{
    ERRORS_t Local_u8ErrorState = USART_OK;

    if (USART_WRONG_CONFIGURATION != USART_CheckConfig(Config))
    {
        /* Enable DMA Transmitter */
        USART[Config->USART_Number]->CR3 |= (1 << DMAT);
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}

/**
 * @brief  : This Function is Used to Enable USART Interrupts
 *
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Enable The Interrupts
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 * @note   : This Function is Used Inside USART_Init Function to Enable Interrupts , you can use it to Enable Interrupts Individually
 */
ERRORS_t USART_EnableIT(USART_Config_t *Config)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if (USART_WRONG_CONFIGURATION == USART_CheckConfig(Config))
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    else
    {
        /* Set Parity Error Interrupt */
        USART[Config->USART_Number]->CR1 &= (USART_PEIE_MASK);
        USART[Config->USART_Number]->CR1 |= (Config->IT_FlagEnable.ParityErrorIT << PEIE);

        /* Set Transmit Data Register Empty Interrupt */
        USART[Config->USART_Number]->CR1 &= (USART_TXEIE_MASK);
        USART[Config->USART_Number]->CR1 |= (Config->IT_FlagEnable.TDataRegEmptyIT << TXEIE);

        /* Set Transmission Complete Interrupt */
        USART[Config->USART_Number]->CR1 &= (USART_TCIE_MASK);
        USART[Config->USART_Number]->CR1 |= (Config->IT_FlagEnable.TransmissionCompleteIT << TRANS_CIE);

        /* Set Receive Data Register Not Empty Interrupt */
        USART[Config->USART_Number]->CR1 &= (USART_RXNEIE_MASK);
        USART[Config->USART_Number]->CR1 |= (Config->IT_FlagEnable.RDataRegNEmptyIT << RXNEIE);

        /* Set IDLE Line Detected Interrupt */
        USART[Config->USART_Number]->CR1 &= (USART_IDLEIE_MASK);
        USART[Config->USART_Number]->CR1 |= (Config->IT_FlagEnable.IDLELineDetectedIT << IDLEIE);

        /* Set LIN Break Detection Interrupt */
        USART[Config->USART_Number]->CR2 &= (USART_LBDIE_MASK);
        USART[Config->USART_Number]->CR2 |= (Config->IT_FlagEnable.LINBreakDetectedIT << LBDIE);

        /* Set CTS Interrupt */
        USART[Config->USART_Number]->CR3 &= (USART_CTSIE_MASK);
        USART[Config->USART_Number]->CR3 |= (Config->IT_FlagEnable.CTSIT << CTSIE);

        /* Set Error Interrupt */
        USART[Config->USART_Number]->CR3 &= (USART_EIE_MASK);
        USART[Config->USART_Number]->CR3 |= (Config->IT_FlagEnable.ErrorIT << EIE);
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Send Data Using a USART Peripheral ( Non-Blocking Mode ) AKA Asycnchronous
 * @fn     : USART_SendData_IT
 * @param  : Configuration => This Parameter is Used to Pass The Configuration Struct to Send Data Using it
 * @param  : Data => This Parameter is Used to Pass The Data to Be Sent Using The USART Peripheral
 * @param  : pv_CallBack_Func => This Parameter is Used to Pass The CallBack Function to be Used in Interrupt Mode to be invoked when Interrupt Occurs
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_SendData_IT(USART_Config_t *Configuration, uint16_t Data, void (*pv_CallBack_Func)(void))
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if ((USART_WRONG_CONFIGURATION != USART_CheckConfig(Configuration)) && (NULL != pv_CallBack_Func))
    {
        /* Correct Cofiguration */

        /* Setting IRQ_SRC */
        IRQ_SRC[Configuration->USART_Number] = USART_SEND_DATA;

        /* Setting Call Back Function */
        USART_PTR_TO_FUNC[Configuration->USART_Number][USART_IT_TC] = pv_CallBack_Func;

        /* Send Data */
        USART[Configuration->USART_Number]->DR = Data;

        /* Enable Transmission Complete Interrupt */
        USART[Configuration->USART_Number]->CR1 |= (1 < TRANS_CIE);
    }
    else
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Send String Using a USART Peripheral ( Non-Blocking Mode ) AKA Asycnchronous
 * @fn     : USART_SendBuffer_IT
 * @param  : Config  => This Parameter is Used to Pass The Configuration Struct to Send String Using it
 * @param  : DataBuffer => This Parameter is Used to Pass The Buffer of Data to Be Sent Using The USART Peripheral
 * @param  : BufferSize => This Parameter is Used to Pass The Size of The Buffer to Be Sent Using The USART Peripheral
 * @param  : pv_CallBackFunc => This Parameter is Used to Pass The CallBack Function to be Used in Interrupt Mode to be invoked when Interrupt Occurs
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_SendBuffer_IT(USART_Config_t *Config, uint8_t *DataBuffer, uint8_t BufferSize, void (*pv_CallBackFunc)(void))
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    USART_FlagStatus_t FlagState = USART_FLAG_RESET;

    if (USART_WRONG_CONFIGURATION != USART_CheckConfig(Config))
    {
        if (DataBuffer != NULL && pv_CallBackFunc != NULL)
        {
            /* Setting IRQ Source */
            IRQ_SRC[Config->USART_Number] = USART_SEND_BUFFER;

            /* Setting Buffer to Send Globaly */
            USART_SentBuffer[Config->USART_Number] = DataBuffer;

            /* Setting Buffer Size Globaly */
            USART_SentbufferSize[Config->USART_Number] = BufferSize;

            /* Setting Call Back Function */
            USART_PTR_TO_FUNC[Config->USART_Number][USART_IT_TC] = pv_CallBackFunc;

            /* Send First Character */
            while (USART_FLAG_SET != FlagState)
            {
                USART_ReadFlag(Config->USART_Number, USART_TDATA_REG_EMPTY, &FlagState);
            }

            /* Send First Element in the Buffer */
            USART[Config->USART_Number]->DR = DataBuffer[0];

            /* Enable Transfer Complete Interrupt */
            USART[Config->USART_Number]->CR1 |= (1 << TRANS_CIE);
        }
        else
        {
            Local_u8ErrorStatus = NULL_POINTER;
        }
    }
    else
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Receive a Buffer of Data Using a USART Peripheral ( Non-Blocking Mode ) AKA Asycnchronous
 * @fn     : USART_ReceiveBuffer_IT
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Receive Buffer Using it
 * @param  : ReceiveBuffer => This Parameter is Used to Pass The Buffer of Data to Be Received inside it Using The USART Peripheral
 * @param  : BufferSize => This Parameter is Used to Pass The Size of The Buffer to Be Received Using The USART Peripheral
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
ERRORS_t USART_ReceiveBuffer_IT(USART_Config_t *Config, uint8_t *ReceiveBuffer, uint8_t BufferSize, void(*pv_CallBackFunc))
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if (USART_WRONG_CONFIGURATION != USART_CheckConfig(Config))
    {
        if (ReceiveBuffer != NULL && pv_CallBackFunc != NULL)
        {
            /* Set IRQ Source */
            IRQ_SRC[Config->USART_Number] = USART_RECEIVE_BUFFER;

            /* Setting Buffer Size globally */
            USART_ReceivebufferSize[Config->USART_Number] = BufferSize;

            /* Setting Buffer to Receive globally */
            USART_ReceivedBuffer[Config->USART_Number] = ReceiveBuffer;

            /* Setting Call Back Function */
            USART_PTR_TO_FUNC[Config->USART_Number][USART_IT_RXNE] = pv_CallBackFunc;

            /* Enable Receive Data Register Not Empty Interrupt */
            USART[Config->USART_Number]->CR1 |= (1 << RXNEIE);
        }
        else
        {
            Local_u8ErrorStatus = NULL_POINTER;
        }
    }
    else
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Check The Configuration of USART Peripheral
 *
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Check it
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
static ERRORS_t USART_CheckConfig(USART_Config_t *Config)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if (Config->Mode < USART_Rx || Config->Mode > USART_Rx_Tx ||
        Config->USART_Number < USART_PERIPH_1 || Config->USART_Number > USART_PERIPH_3 ||
        Config->WordLength < USART_8_BITS_WIDTH || Config->WordLength > USART_9_BITS_WIDTH ||
        Config->ParityMode < USART_PARITY_DIS || Config->ParityMode > USART_PARITY_EN_ODD ||
        Config->IT_FlagEnable.ParityErrorIT < USART_IT_FLAG_DIS || Config->IT_FlagEnable.ParityErrorIT > USART_IT_FLAG_EN ||
        Config->IT_FlagEnable.TDataRegEmptyIT < USART_IT_FLAG_DIS || Config->IT_FlagEnable.TDataRegEmptyIT > USART_IT_FLAG_EN ||
        Config->IT_FlagEnable.TransmissionCompleteIT < USART_IT_FLAG_DIS || Config->IT_FlagEnable.TransmissionCompleteIT > USART_IT_FLAG_EN ||
        Config->IT_FlagEnable.RDataRegNEmptyIT < USART_IT_FLAG_DIS || Config->IT_FlagEnable.RDataRegNEmptyIT > USART_IT_FLAG_EN ||
        Config->IT_FlagEnable.IDLELineDetectedIT < USART_IT_FLAG_DIS || Config->IT_FlagEnable.IDLELineDetectedIT > USART_IT_FLAG_EN ||
        Config->IT_FlagEnable.CTSIT < USART_IT_FLAG_DIS || Config->IT_FlagEnable.CTSIT > USART_IT_FLAG_EN ||
        Config->IT_FlagEnable.ErrorIT < USART_IT_FLAG_DIS || Config->IT_FlagEnable.ErrorIT > USART_IT_FLAG_EN ||
        Config->IT_FlagEnable.LINBreakDetectedIT < USART_IT_FLAG_DIS || Config->IT_FlagEnable.LINBreakDetectedIT > USART_IT_FLAG_EN ||
        Config->StopBits < USART_ONE_SB || Config->StopBits > USART_ONE_AND_HALF_SB)
    {
        Local_u8ErrorStatus = USART_WRONG_CONFIGURATION;
    }

    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Set The BaudRate of USART Peripheral
 *
 * @param  : Config => This Parameter is Used to Pass The Configuration Struct to Set The BaudRate
 * @return : void
 */
static void USART_SetBaudRate(USART_Config_t *Config)
{
    float USART_DIV = 0;

    uint32_t DIV_Fraction = 0;

    USART[Config->USART_Number]->BRR = 0;

    /* BaudRate Equation */
    USART_DIV = F_PCLK / (float)(16U * Config->BaudRate);
    USART_DIV *= 1000UL;

    /* Set the Mantissa Part */
    USART[Config->USART_Number]->BRR |= ((uint32_t)USART_DIV / 1000UL) << DIV_MANTISSA;

    /* Calculte the Fraction */
    DIV_Fraction = (uint32_t)USART_DIV % 1000UL;

    DIV_Fraction = (DIV_Fraction * 16U);

    /* get Round */
    DIV_Fraction += 500UL;

    USART[Config->USART_Number]->BRR |= (uint32_t)(DIV_Fraction / 1000UL) << DIV_FRACTION;
}

/**
 * @brief  : This Function is Used to Set The Parity Mode of USART Peripheral
 *
 * @param  : UsartNum => This Parameter is Used to Select The USART Peripheral Number to Be Used -> @USART_t
 * @param  : Parity   => This Parameter is Used to Select The Parity Mode to Be Used -> @USART_ParityMode_t
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
static ERRORS_t USART_SetParity(USART_t UsartNum, USART_ParityMode_t Parity)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if (UsartNum < USART_PERIPH_1 || UsartNum > USART_PERIPH_3 ||
        Parity < USART_PARITY_DIS || Parity > USART_PARITY_EN_ODD)
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    else
    {
        switch (Parity)
        {
        case USART_PARITY_DIS:
            USART[UsartNum]->CR1 &= (~(1 << PCE));
            break;
        case USART_PARITY_EN_EVEN:
            USART[UsartNum]->CR1 |= (1 << PCE);
            USART[UsartNum]->CR1 &= (~(1 << PS));
            break;
        case USART_PARITY_EN_ODD:
            USART[UsartNum]->CR1 |= (1 << PCE);
            USART[UsartNum]->CR1 |= (1 << PS);
            break;
        }
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Set The Mode of USART Peripheral
 *
 * @param  : UsartNum => This Parameter is Used to Select The USART Peripheral Number to Be Used -> @USART_t
 * @param  : Mode     => This Parameter is Used to Select The Mode to Be Used -> @USART_Mode_t
 * @return : ERRORS_t => This Return Parameter is Used to Indicate The Function Execution If Executed Correctly or NOT
 */
static ERRORS_t USART_SetMode(USART_t UsartNum, USART_Mode_t Mode)
{
    ERRORS_t Local_u8ErrorStatus = USART_OK;

    if (UsartNum < USART_PERIPH_1 || UsartNum > USART_PERIPH_3 ||
        Mode < USART_Rx || Mode > USART_Rx_Tx)
    {
        Local_u8ErrorStatus = USART_NOK;
    }
    else
    {
        switch (Mode)
        {
        case USART_Rx:
            USART[UsartNum]->CR1 &= (~(1 << TE));
            USART[UsartNum]->CR1 |= (1 << RE);
            break;
        case USART_Tx:
            USART[UsartNum]->CR1 &= (~(1 << RE));
            USART[UsartNum]->CR1 |= (1 << TE);
            break;
        case USART_Rx_Tx:
            USART[UsartNum]->CR1 |= (1 << TE);
            USART[UsartNum]->CR1 |= (1 << RE);
            break;
        }
    }
    return Local_u8ErrorStatus;
}

/**
 * @brief  : This Function is Used to Handle The Interrupts of USART Peripheral
 * @fn	   : USART_HANDLE_IT
 * @param  : USARTNum => This Parameter is Used to Select The USART Peripheral Number to Be Used -> @USART_t
 * @return : void
 * @note   : This Function is Used Inside All IRQ Handlers to Handle The Interrupts ( Private Function )
 */
static void USART_HANDLE_IT(USART_t USARTNum)
{
    USART_FlagStatus_t FlagState = USART_FLAG_RESET;

    /* Read Data Register Not Empty Flag */
    USART_ReadFlag(USARTNum, USART_RDATA_REG_NEMPTY, &FlagState);

    if (FlagState == USART_FLAG_SET && IRQ_SRC[USARTNum] == USART_RECEIVE_DATA)
    {
        /* Clearing IRQ Source */

        IRQ_SRC[USARTNum] = USART_NO_SRC;

        /* Setting Received Data */
        *USART_ReceivedData[USARTNum] = USART[USARTNum]->DR;

        /* Disable Receive Data Register Not Empty Intterupt */
        USART[USARTNum]->CR1 &= (~(1 << RXNEIE));

        /* Invoke the Call Back Function */
        if (USART_PTR_TO_FUNC[USARTNum][USART_IT_RXNE] != NULL)
        {
            USART_PTR_TO_FUNC[USARTNum][USART_IT_RXNE]();
        }
    }
    else if (FlagState == USART_FLAG_SET && IRQ_SRC[USARTNum] == USART_RECEIVE_BUFFER)
    {
        static uint8_t Local_u8Counter = 0;

        /* Setting Received Data */
        USART_ReceivedBuffer[USARTNum][Local_u8Counter++] = USART[USARTNum]->DR;

        if (Local_u8Counter == USART_ReceivebufferSize[USARTNum])
        {
            /* clear IRQ Source */
            IRQ_SRC[USARTNum] = USART_NO_SRC;

            /* Disable Receive Data Register Not Empty Intterupt */
            USART[USARTNum]->CR1 &= (~(1 << RXNEIE));

            /* Invoke the Call Back Function */
            if (USART_PTR_TO_FUNC[USARTNum][USART_IT_RXNE] != NULL)
            {
                USART_PTR_TO_FUNC[USARTNum][USART_IT_RXNE]();
            }
        }
    }

    FlagState = USART_FLAG_RESET;

    /* Transmission Complete Flag */
    USART_ReadFlag(USARTNum, USART_TRANSMISSION_COMP, &FlagState);

    if (FlagState == USART_FLAG_SET && IRQ_SRC[USARTNum] == USART_SEND_BUFFER)
    {
        static uint8_t Local_u8counter = 1;

        /* Send Next Data */
        USART[USARTNum]->DR = USART_SentBuffer[USARTNum][Local_u8counter++];

        if (Local_u8counter == USART_SentbufferSize[USARTNum])
        {
            /* Clear IRQ Source */
            IRQ_SRC[USARTNum] = USART_NO_SRC;

            /* Disable Transmission Complete Interrupt */
            USART[USARTNum]->CR1 &= (~(1 << TRANS_CIE));

            /* Invoke Call Back Function */
            if (USART_PTR_TO_FUNC[USARTNum][USART_IT_TC] != NULL)
            {
                USART_PTR_TO_FUNC[USARTNum][USART_IT_TC]();
            }
        }
    }
    else if (FlagState == USART_FLAG_SET && IRQ_SRC[USARTNum] == USART_SEND_DATA)
    {
        /* Clear IRQ Source */
        IRQ_SRC[USARTNum] = USART_NO_SRC;

        /* Disable Transmission Complete Interrupt */
        USART[USARTNum]->CR1 &= (~(1 << TRANS_CIE));

        /* Invoke Call Back Function */
        if (USART_PTR_TO_FUNC[USARTNum][USART_IT_TC] != NULL)
        {
            USART_PTR_TO_FUNC[USARTNum][USART_IT_TC]();
        }
    }
}

/*==============================================================================================================================================
 * INTERRUPT HANDLERS IMPLEMENTATION
 *==============================================================================================================================================*/

/* USART1 Interrupt Handler */
void USART1_IRQHandler(void)
{
    USART_HANDLE_IT(USART_PERIPH_1);
}

/* USART2 Interrupt Handler */
void USART2_IRQHandler(void)
{
    USART_HANDLE_IT(USART_PERIPH_2);
}

/* USART3 Interrupt Handler */
void USART3_IRQHandler(void)
{
    USART_HANDLE_IT(USART_PERIPH_3);
}
