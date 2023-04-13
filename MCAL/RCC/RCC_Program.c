/*
 ******************************************************************************
 * @file           : RCC_Program.c
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : Apr 10, 2023
 * @Version        : 1.0.1
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




/* ************************************************** Includes Section Start ************************************************** */
#include <stdint.h>

#include "RCC_Private.h"
#include "RCC_Register.h"
#include "RCC_Interface.h"

/* ************************************************** Includes Section End   ************************************************** */



/* ************************************************** Main Funcions Section   ************************************************** */


RCC_ErrorStatus RCC_SetClkStatus( RCC_Clk_Type Copy_eClktype , RCC_Clk_Status Copy_eClkStatus )
{
	/* Timout Variable to Prevent HW Malfunction */
	uint32_t Local_uint32Timeout = 0 ;

	/* Error Status if Timeout is Reached */
	RCC_ErrorStatus Local_ErrorStatus = OK ;

	switch ( Copy_eClktype )
	{
	case HSE :
		/* HSE ON */
		if ( Copy_eClkStatus == ON )
		{
			/* Enable HSE */
			( RCC -> RCC_CR ) |= ( 1 << CR_HSEON ) ;

			/* Loop Until HSE Flag is Ready or Timout is Reached */
			while (  ((RCC -> RCC_CR >> CR_HSERDY)&0x01) == 0 && ( Local_uint32Timeout < Timeout_MAX )   )
			{
				Local_uint32Timeout ++ ;
			}
			/* Check if Timeout is Reached */
			if( Local_uint32Timeout == Timeout_MAX )
			{
				Local_ErrorStatus = TimeoutError ;
			}
		}
		else
		{
			/* HSE OFF */

			/* Disable HSE */
			( RCC -> RCC_CR ) &=  (~( 1 << CR_HSEON ) ) ;
		}
		break ;

	case HSI :
		/* HSI ON */
		if ( Copy_eClkStatus == ON )
		{
			/* Enable HSI */
			( RCC -> RCC_CR ) |= ( 1 << CR_HSION ) ;

			/* Loop Until HSI Flag is Ready or Timout is Reached */
			while (  ((RCC -> RCC_CR >> CR_HSIRDY)&0x01) == 0 && ( Local_uint32Timeout < Timeout_MAX )   )
			{
				Local_uint32Timeout ++ ;
			}
			/* Check if Timeout is Reached */
			if( Local_uint32Timeout == Timeout_MAX )
			{
				Local_ErrorStatus = TimeoutError ;
			}
		}
		else
		{
			/* HSI OFF */

			/* Disabel HSI */
			( RCC -> RCC_CR ) &=  (~( 1 << CR_HSION ) ) ;
		}
		break ;

	case PLL :
		/* PLL ON */
		if ( Copy_eClkStatus == ON )
		{
			/* Enable PLL */
			( RCC -> RCC_CR ) |= ( 1 << CR_PLLON ) ;

			/* Loop Until PLL Flag is Ready or Timout is Reached */
			while (  ((RCC -> RCC_CR >> CR_PLLRDY)&0x01) == 0 && ( Local_uint32Timeout < Timeout_MAX )   )
			{
				Local_uint32Timeout ++ ;
			}
			/* Check if Timeout is Reached */
			if( Local_uint32Timeout == Timeout_MAX )
			{
				Local_ErrorStatus = TimeoutError ;
			}
		}
		else
		{
			/* PLL OFF */

			/* Disable PLL */
			( RCC -> RCC_CR ) &=  (~( 1 << CR_PLLON ) ) ;
		}
		break ;
	}
	return Local_ErrorStatus ;
}


void RCC_SetSYSCLK( RCC_Clk_Type Copy_eClkType )
{
	/* BIT MASKING */

	/* Set SYSCLK */
	RCC -> RCC_CFGR &= ( SW_MASK ) ;
	RCC -> RCC_CFGR |= ( Copy_eClkType << CFGR_SW0 ) ;
}

void RCC_HSEConfig ( RCC_HSEConfigStructure * Copy_sHSEConfig )
{
	/* Set HSE BYPASSED OR NOT */
	if( Copy_sHSEConfig -> HSE_ByPass == HSE_NOTBYPASSED  )
	{
		/* HSE is Not Bypassed */
		RCC -> RCC_CR &= (~(1<<CR_HSEBYP) );
	}
	else if ( Copy_sHSEConfig -> HSE_ByPass == HSE_BYPASSED )
	{
		/* HSE is Bypassed */
		RCC -> RCC_CR |= (1<<CR_HSEBYP) ;
	}

	/* Set HSE Divider Configuration */
	if( Copy_sHSEConfig ->  HSE_Divider == HSE_DIVIDE_BY_1  )
	{
		/* HSE Divide By 1 */
		RCC -> RCC_CFGR &= (~(1<<CFGR_PLLXTPRE) );
	}
	else if ( Copy_sHSEConfig -> HSE_Divider == HSE_DIVIDE_BY_2 )
	{
		/* HSE Divided By 2 */
		RCC -> RCC_CFGR |= (1<<CFGR_PLLXTPRE) ;
	}

}

RCC_ErrorStatus RCC_PLLConfig ( uint8_t Copy_uint8PLLMulFactor , uint8_t Copy_uint8PLLSrc )
{
	/* Error Status in Case of Wrong Input */
	RCC_ErrorStatus Local_Erorr_Status = OK ;

	/* Setting PLL Multiplication Factor */
	if( ( Copy_uint8PLLMulFactor >= PLL_MUL_FACTOR_2 ) && ( Copy_uint8PLLMulFactor <= PLL_MUL_FACTOR_16 ) )
	{
		/* BIT MASKING */

		/* Set PLL Multiplication Factor */
		RCC -> RCC_CFGR &= ( PLL_MUL_MASK ) ;
		RCC -> RCC_CFGR |= ( Copy_uint8PLLMulFactor << CFGR_PLLMUL0 ) ;
	}
	else
	{
		/* Wrong PLL MUL FAC Input */
		Local_Erorr_Status = PLLMULFactorError ;
	}

	/* Setting PLL SRC */
	if( Copy_uint8PLLSrc == PLL_SRC_HSE )
	{
		/* PLL Source is HSE */
		RCC -> RCC_CFGR |= ( 1 << CFGR_PLLSRC );
	}
	else if ( Copy_uint8PLLSrc == PLL_SRC_HSI_DIVIDE_BY_2 )
	{
		/* PLL Source is HSI Divided By 2 */
		RCC -> RCC_CFGR &= (~( 1 << CFGR_PLLSRC ) );
	}
	else
	{
		/* Wrong PLL Source Input */
		Local_Erorr_Status = PLLSRCError ;
	}
	return Local_Erorr_Status ;
}


RCC_ErrorStatus RCC_AHBEnableCLK ( uint8_t Copy_uint8AHBPeripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK;

	/* Enable Required AHB Peripheral */
	switch( Copy_uint8AHBPeripheral )
	{
	case SDIO_CLK : RCC -> RCC_AHBENR |= ( 1 << AHBENR_SDIOEN ) ; break ;
	case FSMC_CLK : RCC -> RCC_AHBENR |= ( 1 << AHBENR_FSMCEN ) ; break ;
	case CRC_CLK  : RCC -> RCC_AHBENR |= ( 1 << AHBENR_CRCEN )  ; break ;
	case FLITF_CLK: RCC -> RCC_AHBENR |= ( 1 << AHBENR_FLITFEN ); break ;
	case SRAM_CLK : RCC -> RCC_AHBENR |= ( 1 << AHBENR_SRAMEN ) ; break ;
	case DMA2_CLK : RCC -> RCC_AHBENR |= ( 1 << AHBENR_DMA2EN ) ; break ;
	case DMA1_CLK : RCC -> RCC_AHBENR |= ( 1 << AHBENR_DMA1EN ) ; break ;
	default       : Local_ErrorStatus = AHBPeripheralError ;
	}
	return Local_ErrorStatus ;
}

RCC_ErrorStatus RCC_AHBDisableCLK ( uint8_t Copy_uint8AHBPeripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK;

	/* Disable Required AHB Peripheral */
	switch( Copy_uint8AHBPeripheral )
	{
	case SDIO_CLK : RCC -> RCC_AHBENR &= (~( 1 << AHBENR_SDIOEN ) ); break ;
	case FSMC_CLK : RCC -> RCC_AHBENR &= (~( 1 << AHBENR_FSMCEN ) ); break ;
	case CRC_CLK  : RCC -> RCC_AHBENR &= (~( 1 << AHBENR_CRCEN )  ); break ;
	case FLITF_CLK: RCC -> RCC_AHBENR &= (~( 1 << AHBENR_FLITFEN )); break ;
	case SRAM_CLK : RCC -> RCC_AHBENR &= (~( 1 << AHBENR_SRAMEN ) ); break ;
	case DMA2_CLK : RCC -> RCC_AHBENR &= (~( 1 << AHBENR_DMA2EN ) ); break ;
	case DMA1_CLK : RCC -> RCC_AHBENR &= (~( 1 << AHBENR_DMA1EN ) ); break ;
	default       : Local_ErrorStatus = AHBPeripheralError ;
	}
	return Local_ErrorStatus ;
}

RCC_ErrorStatus RCC_APB1EnableCLK ( uint8_t Copy_uint8Peripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK;

	/* Enable Required APB1 Peripheral */
	switch( Copy_uint8Peripheral )
	{
	case DAC_CLK   : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_DACEN )   ; break ;
	case PWR_CLK   : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_PWREN )   ; break ;
	case BKP_CLK   : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_BKPEN )   ; break ;
	case CAN_CLK   : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_CANEN )   ; break ;
	case USB_CLK   : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_USBEN )   ; break ;
	case I2C2_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_I2C2EN )  ; break ;
	case I2C1_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_I2C1EN )  ; break ;
	case UART5_CLK : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_UART5EN ) ; break ;
	case UART4_CLK : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_UART4EN ) ; break ;
	case USART3_CLK: RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_USART3EN ); break ;
	case USART2_CLK: RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_USART2EN ); break ;
	case SPI3_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_SPI3EN )  ; break ;
	case SPI2_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_SPI2EN )  ; break ;
	case WWDG_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_WWDGEN )  ; break ;
	case TIM14_CLK : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_TIM14EN ) ; break ;
	case TIM13_CLK : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_TIM13EN ) ; break ;
	case TIM12_CLK : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_TIM12EN ) ; break ;
	case TIM7_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_TIM7EN )  ; break ;
	case TIM6_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_TIM6EN )  ; break ;
	case TIM5_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_TIM5EN )  ; break ;
	case TIM4_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_TIM4EN )  ; break ;
	case TIM3_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_TIM3EN )  ; break ;
	case TIM2_CLK  : RCC -> RCC_APB1ENR  |=  ( 1 << APB1ENR_TIM2EN )  ; break ;
	default        : Local_ErrorStatus = APB1PeripheralError ;
	}
	return Local_ErrorStatus ;
}

RCC_ErrorStatus RCC_APB1DisableCLK ( uint8_t Copy_uint8Peripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK;

	/* Disable Required APB1 Peripheral */
	switch( Copy_uint8Peripheral )
	{
	case DAC_CLK   : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_DACEN ) )   ; break ;
	case PWR_CLK   : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_PWREN ) )   ; break ;
	case BKP_CLK   : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_BKPEN ) )   ; break ;
	case CAN_CLK   : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_CANEN ) )   ; break ;
	case USB_CLK   : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_USBEN ) )   ; break ;
	case I2C2_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_I2C2EN ) )  ; break ;
	case I2C1_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_I2C1EN ) )  ; break ;
	case UART5_CLK : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_UART5EN ) ) ; break ;
	case UART4_CLK : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_UART4EN ) ) ; break ;
	case USART3_CLK: RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_USART3EN ) ); break ;
	case USART2_CLK: RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_USART2EN ) ); break ;
	case SPI3_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_SPI3EN ) )  ; break ;
	case SPI2_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_SPI2EN ) )  ; break ;
	case WWDG_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_WWDGEN ) )  ; break ;
	case TIM14_CLK : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_TIM14EN ) ) ; break ;
	case TIM13_CLK : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_TIM13EN ) ) ; break ;
	case TIM12_CLK : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_TIM12EN ) ) ; break ;
	case TIM7_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_TIM7EN ) )  ; break ;
	case TIM6_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_TIM6EN ) )  ; break ;
	case TIM5_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_TIM5EN ) )  ; break ;
	case TIM4_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_TIM4EN ) )  ; break ;
	case TIM3_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_TIM3EN ) )  ; break ;
	case TIM2_CLK  : RCC -> RCC_APB1ENR  &=  (~ ( 1 << APB1ENR_TIM2EN ) )  ; break ;
	default        : Local_ErrorStatus = APB1PeripheralError ;
	}
	return Local_ErrorStatus ;
}


RCC_ErrorStatus RCC_APB2EnableCLK ( uint8_t Copy_uint8Peripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK ;

	/* Enable Required APB2 Peripheral */
	switch ( Copy_uint8Peripheral )
	{
	case TIM11_CLK : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_TIM11EN ) ; break ;
	case TIM10_CLK : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_TIM10EN ) ; break ;
	case TIM9_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_TIM9EN )  ; break ;
	case ADC3_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_ADC3EN )  ; break ;
	case USART1_CLK: RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_USART1EN ); break ;
	case TIM8_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_TIM8EN )  ; break ;
	case SPI1_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_SPI1EN )  ; break ;
	case TIM1_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_TIM1EN )  ; break ;
	case ADC2_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_ADC2EN )  ; break ;
	case ADC1_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_ADC1EN )  ; break ;
	case IOPG_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_IOPGEN)   ; break ;
	case IOPF_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_IOPFEN )  ; break ;
	case IOPE_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_IOPEEN )  ; break ;
	case IOPD_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_IOPDEN )  ; break ;
	case IOPC_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_IOPCEN )  ; break ;
	case IOPB_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_IOPBEN)   ; break ;
	case IOPA_CLK  : RCC -> RCC_APB2ENR  |= ( 1 << APB2ENR_IOPAEN )  ; break ;
	default        : Local_ErrorStatus = APB2PeripheralError         ; break ;
	}
	return Local_ErrorStatus ;
}

RCC_ErrorStatus RCC_APB2DisableCLK ( uint8_t Copy_uint8Peripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK ;

	/* Enable Required APB2 Peripheral */
		switch ( Copy_uint8Peripheral )
		{
		case TIM11_CLK : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_TIM11EN ) ); break ;
		case TIM10_CLK : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_TIM10EN ) ); break ;
		case TIM9_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_TIM9EN )  ); break ;
		case ADC3_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_ADC3EN )  ); break ;
		case USART1_CLK: RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_USART1EN )); break ;
		case TIM8_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_TIM8EN )  ); break ;
		case SPI1_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_SPI1EN )  ); break ;
		case TIM1_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_TIM1EN )  ); break ;
		case ADC2_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_ADC2EN )  ); break ;
		case ADC1_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_ADC1EN )  ); break ;
		case IOPG_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_IOPGEN)   ); break ;
		case IOPF_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_IOPFEN )  ); break ;
		case IOPE_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_IOPEEN )  ); break ;
		case IOPD_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_IOPDEN )  ); break ;
		case IOPC_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_IOPCEN )  ); break ;
		case IOPB_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_IOPBEN)   ); break ;
		case IOPA_CLK  : RCC -> RCC_APB2ENR  &= (~( 1 << APB2ENR_IOPAEN )  ); break ;
		default        : Local_ErrorStatus = APB2PeripheralError            ; break ;
		}
		return Local_ErrorStatus ;
}

/**
 ***************************************************************************************************************
User                       Date                           Brief
 ****************************************************************************************************************
Mohammed Ayman            11APR2023                       ALL Functions
Mohammed Ayman            12APR2023                       Documentation For Functions

 */
