/*
 ******************************************************************************
 * @file           : RCC_Register.h
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


/* ---------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------- INCLUDES SECTION START -------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------------------------- */
#include <stdint.h>

#include "RCC_Private.h"
#include "RCC_Register.h"
#include "RCC_Interface.h"

/* ---------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------- INCLUDES SECTION END   -------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------------------------- */



/* ---------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------- MAIN FUNCTIONS SECTION -------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------------------------- */



/* ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------ */
/* ----------------      NAME     : RCC_SetClkStatus                			     	      ----------------- */
/* ----------------      FUNCTION : Set ClK Status       		                              ----------------- */
/* ----------------      ARGUMENT : CLK TYPE ( enum ) , CLK Status ( enum )		              ----------------- */
/* ----------------                  1- HSE                 1- OFF                            ----------------- */
/* ----------------                  2- HSI                 2- ON                             ----------------- */
/* ----------------                  3- PLL                                                   ----------------- */
/* ----------------      RETURN   : Erorr Status( TimeOut Indication )                        ----------------- */
/* ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------ */
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



/* ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------ */
/* ----------------      NAME     : RCC_SetSYSCLK                			     	          ----------------- */
/* ----------------      FUNCTION : SET SYSCLK      		                                  ----------------- */
/* ----------------      ARGUMENT : CLK TYPE ( enum )                       	              ----------------- */
/* ----------------                  1- HSE                                                   ----------------- */
/* ----------------                  2- HSI                                                   ----------------- */
/* ----------------                  3- PLL                                                   ----------------- */
/* ----------------      RETURN   : Void             								          ----------------- */
/* ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------ */
void RCC_SetSYSCLK( RCC_Clk_Type Copy_eClkType )
{
	/* BIT MASKING */

	/* Set SYSCLK */
	RCC -> RCC_CFGR &= ( SW_MASK ) ;
	RCC -> RCC_CFGR |= ( Copy_eClkType << CFGR_SW0 ) ;
}


/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_HSEConfig                			     	             ----------------- */
/* ----------------      FUNCTION : SET HSE Configuration        		                         ----------------- */
/* ----------------      ARGUMENT : HSEConfig ( Structure )                       	             ----------------- */
/* ----------------                  1- HSE_Divider  --> ( HSE_DIVIDE_BY_1  , HSE_DIVIDE_BY_2 )  ----------------- */
/* ----------------                  2- HSI_BYPASS   --> ( HSE_BYPASSED , HSE_NOTBYPASSED )      ----------------- */
/* ----------------      RETURN   : Void    								                     ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
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



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_PLLConfig                			     	             ----------------- */
/* ----------------      FUNCTION : SET PLL Configuration        		                         ----------------- */
/* ----------------      ARGUMENT : PLLMULFactor     ,            PLL SRC                        ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- PLL_MUL_FACTOR_2         01- PLL_SRC_HSE                  ----------------- */
/* ----------------                02- PLL_MUL_FACTOR_3         02- PLL_SRC_HSI_DIVIDE_BY_2      ----------------- */
/* ----------------                03- PLL_MUL_FACTOR_4                                          ----------------- */
/* ----------------                04- PLL_MUL_FACTOR_5                                          ----------------- */
/* ----------------                05- PLL_MUL_FACTOR_6                                          ----------------- */
/* ----------------                06- PLL_MUL_FACTOR_7                                          ----------------- */
/* ----------------                07- PLL_MUL_FACTOR_8                                          ----------------- */
/* ----------------                08- PLL_MUL_FACTOR_9                                          ----------------- */
/* ----------------                09- PLL_MUL_FACTOR_10                                         ----------------- */
/* ----------------                10- PLL_MUL_FACTOR_11							             ----------------- */
/* ----------------                11- PLL_MUL_FACTOR_12                                         ----------------- */
/* ----------------                12- PLL_MUL_FACTOR_13                                         ----------------- */
/* ----------------                13- PLL_MUL_FACTOR_14                                         ----------------- */
/* ----------------                14- PLL_MUL_FACTOR_15                                         ----------------- */
/* ----------------                15- PLL_MUL_FACTOR_16                                         ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
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



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_AHBEnableCLK                			     	         ----------------- */
/* ----------------      FUNCTION : Enable CLK on an AHB Peripheral    		                     ----------------- */
/* ----------------      ARGUMENT : AHB Peripheral to Enable                                     ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                       01- SDIO_CLK        					                 ----------------- */
/* ----------------                       02- FSMC_CLK          							     ----------------- */
/* ----------------                       03- CRC_CLK                                            ----------------- */
/* ----------------                       04- FLITF_CLK                                          ----------------- */
/* ----------------                       05- SRAM_CLK                                           ----------------- */
/* ----------------                       06- DMA2_CLK                                           ----------------- */
/* ----------------                       07- DMA1_CLK                                           ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_AHBEnableCLK ( uint8_t Copy_uint8AHBPeripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK;

	/* Enable Required AHB Peripheral */
	if( ( Copy_uint8AHBPeripheral >= DMA1_CLK ) && ( Copy_uint8AHBPeripheral <= SDIO_CLK ) )
	{
		RCC -> RCC_AHBENR |= ( 1 << Copy_uint8AHBPeripheral ) ;
	}
	else
	{
		Local_ErrorStatus = AHBPeripheralError ;
	}

	return Local_ErrorStatus ;
}



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_AHBDisableCLK                			     	         ----------------- */
/* ----------------      FUNCTION : Disable CLK on an AHB Peripheral    		                 ----------------- */
/* ----------------      ARGUMENT : AHB Peripheral to Disable                                    ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                       01- SDIO_CLK        					                 ----------------- */
/* ----------------                       02- FSMC_CLK          							     ----------------- */
/* ----------------                       03- CRC_CLK                                            ----------------- */
/* ----------------                       04- FLITF_CLK                                          ----------------- */
/* ----------------                       05- SRAM_CLK                                           ----------------- */
/* ----------------                       06- DMA2_CLK                                           ----------------- */
/* ----------------                       07- DMA1_CLK                                           ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_AHBDisableCLK ( uint8_t Copy_uint8AHBPeripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK;

	/* Disable Required AHB Peripheral */
	if( ( Copy_uint8AHBPeripheral >= DMA1_CLK ) && ( Copy_uint8AHBPeripheral <= SDIO_CLK ) )
	{
		RCC -> RCC_AHBENR &= ( ~ ( 1 << Copy_uint8AHBPeripheral ) ) ;
	}
	else
	{
		Local_ErrorStatus = AHBPeripheralError ;
	}

	return Local_ErrorStatus ;
}



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_APB1EnableCLK                			     	         ----------------- */
/* ----------------      FUNCTION : Enable CLK on an APB1 Peripheral    	     	             ----------------- */
/* ----------------      ARGUMENT : APB1 Peripheral to Enable                                    ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- DAC_CLK                                                   ----------------- */
/* ----------------                02- PWR_CLK                                                   ----------------- */
/* ----------------                03- BKP_CLK                                                   ----------------- */
/* ----------------                04- CAN_CLK                                                   ----------------- */
/* ----------------                05- USB_CLK                                                   ----------------- */
/* ----------------                06- I2C2_CLK                                                  ----------------- */
/* ----------------                07- I2C1_CLK                                                  ----------------- */
/* ----------------                08- UART5_CLK                                                 ----------------- */
/* ----------------                09- UART4_CLK                                                 ----------------- */
/* ----------------                10- USART3_CLK       							             ----------------- */
/* ----------------                11- USART2_CLK                                                ----------------- */
/* ----------------                12- SPI3_CLK                                                  ----------------- */
/* ----------------                13- SPI2_CLK                                                  ----------------- */
/* ----------------                14- WWDG_CLK                                                  ----------------- */
/* ----------------                15- TIM14_CLK                                                 ----------------- */
/* ----------------                16- TIM13_CLK                                                 ----------------- */
/* ----------------                17- TIM12_CLK                                                 ----------------- */
/* ----------------                18- TIM7_CLK                                                  ----------------- */
/* ----------------                19- TIM6_CLK                                                  ----------------- */
/* ----------------                20- TIM5_CLK                                                  ----------------- */
/* ----------------                21- TIM4_CLK                                                  ----------------- */
/* ----------------                22- TIM3_CLK                                                  ----------------- */
/* ----------------                23- TIM2_CLK                                                  ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_APB1EnableCLK ( uint8_t Copy_uint8APB1Peripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK;

	/* Enable Required APB1 Peripheral */
	if( ( Copy_uint8APB1Peripheral >= TIM2_CLK ) && ( Copy_uint8APB1Peripheral <= DAC_CLK ) )
	{
		RCC -> RCC_APB1ENR |= ( 1 << Copy_uint8APB1Peripheral )  ;
	}
	else
	{
		Local_ErrorStatus = APB1PeripheralError ;
	}
	return Local_ErrorStatus ;
}



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_APB1DisableCLK                			     	         ----------------- */
/* ----------------      FUNCTION : Disable CLK on an APB1 Peripheral    	     	             ----------------- */
/* ----------------      ARGUMENT : APB1 Peripheral to Disable                                   ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- DAC_CLK                                                   ----------------- */
/* ----------------                02- PWR_CLK                                                   ----------------- */
/* ----------------                03- BKP_CLK                                                   ----------------- */
/* ----------------                04- CAN_CLK                                                   ----------------- */
/* ----------------                05- USB_CLK                                                   ----------------- */
/* ----------------                06- I2C2_CLK                                                  ----------------- */
/* ----------------                07- I2C1_CLK                                                  ----------------- */
/* ----------------                08- UART5_CLK                                                 ----------------- */
/* ----------------                09- UART4_CLK                                                 ----------------- */
/* ----------------                10- USART3_CLK       							             ----------------- */
/* ----------------                11- USART2_CLK                                                ----------------- */
/* ----------------                12- SPI3_CLK                                                  ----------------- */
/* ----------------                13- SPI2_CLK                                                  ----------------- */
/* ----------------                14- WWDG_CLK                                                  ----------------- */
/* ----------------                15- TIM14_CLK                                                 ----------------- */
/* ----------------                16- TIM13_CLK                                                 ----------------- */
/* ----------------                17- TIM12_CLK                                                 ----------------- */
/* ----------------                18- TIM7_CLK                                                  ----------------- */
/* ----------------                19- TIM6_CLK                                                  ----------------- */
/* ----------------                20- TIM5_CLK                                                  ----------------- */
/* ----------------                21- TIM4_CLK                                                  ----------------- */
/* ----------------                22- TIM3_CLK                                                  ----------------- */
/* ----------------                23- TIM2_CLK                                                  ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_APB1DisableCLK ( uint8_t Copy_uint8APB1Peripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK;

	/* Disable Required APB1 Peripheral */
	if( ( Copy_uint8APB1Peripheral >= TIM2_CLK ) && ( Copy_uint8APB1Peripheral <= DAC_CLK ) )
	{
		RCC -> RCC_APB1ENR &= ( ~ ( 1 << Copy_uint8APB1Peripheral ) )  ;
	}
	else
	{
		Local_ErrorStatus = APB1PeripheralError ;
	}
	return Local_ErrorStatus ;
}



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_APB2EnableCLK                			     	         ----------------- */
/* ----------------      FUNCTION : Enable CLK on an APB2 Peripheral    	     	             ----------------- */
/* ----------------      ARGUMENT : APB2 Peripheral to Enable                                    ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- TIM11_CLK                                                 ----------------- */
/* ----------------                02- TIM10_CLK                                                 ----------------- */
/* ----------------                03- TIM9_CLK                                                  ----------------- */
/* ----------------                04- ADC3_CLK                                                  ----------------- */
/* ----------------                05- USART1_CLK                                                ----------------- */
/* ----------------                06- TIM8_CLK                                                  ----------------- */
/* ----------------                07- SPI1_CLK                                                  ----------------- */
/* ----------------                08- TIM1_CLK                                                  ----------------- */
/* ----------------                09- ADC2_CLK                                                  ----------------- */
/* ----------------                10- ADC1_CLK         							             ----------------- */
/* ----------------                11- IOPG_CLK                                                  ----------------- */
/* ----------------                12- IOPF_CLK                                                  ----------------- */
/* ----------------                13- IOPE_CLK                                                  ----------------- */
/* ----------------                14- IOPD_CLK                                                  ----------------- */
/* ----------------                15- IOPC_CLK                                                  ----------------- */
/* ----------------                16- IOPB_CLK                                                  ----------------- */
/* ----------------                17- IOPA_CLK                                                  ----------------- */
/* ----------------                18- AFIO_CLK                                                  ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_APB2EnableCLK ( uint8_t Copy_uint8APB2Peripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK ;

	/* Enable Required APB2 Peripheral */
	if( ( Copy_uint8APB2Peripheral >= AFIO_CLK ) && ( Copy_uint8APB2Peripheral <= TIM11_CLK ) )
	{
		RCC -> RCC_APB2ENR |= ( 1 << Copy_uint8APB2Peripheral )  ;
	}
	else
	{
		Local_ErrorStatus = APB2PeripheralError ;
	}
	return Local_ErrorStatus ;
}



/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* ----------------      NAME     : RCC_APB2DisableCLK                			     	         ----------------- */
/* ----------------      FUNCTION : Disable CLK on an APB2 Peripheral    	     	             ----------------- */
/* ----------------      ARGUMENT : APB2 Peripheral to Disable                                   ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------                01- TIM11_CLK                                                 ----------------- */
/* ----------------                02- TIM10_CLK                                                 ----------------- */
/* ----------------                03- TIM9_CLK                                                  ----------------- */
/* ----------------                04- ADC3_CLK                                                  ----------------- */
/* ----------------                05- USART1_CLK                                                ----------------- */
/* ----------------                06- TIM8_CLK                                                  ----------------- */
/* ----------------                07- SPI1_CLK                                                  ----------------- */
/* ----------------                08- TIM1_CLK                                                  ----------------- */
/* ----------------                09- ADC2_CLK                                                  ----------------- */
/* ----------------                10- ADC1_CLK         							             ----------------- */
/* ----------------                11- IOPG_CLK                                                  ----------------- */
/* ----------------                12- IOPF_CLK                                                  ----------------- */
/* ----------------                13- IOPE_CLK                                                  ----------------- */
/* ----------------                14- IOPD_CLK                                                  ----------------- */
/* ----------------                15- IOPC_CLK                                                  ----------------- */
/* ----------------                16- IOPB_CLK                                                  ----------------- */
/* ----------------                17- IOPA_CLK                                                  ----------------- */
/* ----------------                18- AFIO_CLK                                                  ----------------- */
/* ----------------                                                                              ----------------- */
/* ----------------      RETURN   : Erorr Status                                                 ----------------- */
/* --------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------- */
RCC_ErrorStatus RCC_APB2DisableCLK ( uint8_t Copy_uint8APB2Peripheral )
{
	/* Error Status to If Wrong Input is Detected */
	RCC_ErrorStatus Local_ErrorStatus = OK ;

	/* Enable Required APB2 Peripheral */
	if( ( Copy_uint8APB2Peripheral >= AFIO_CLK ) && ( Copy_uint8APB2Peripheral <= TIM11_CLK ) )
	{
		RCC -> RCC_APB2ENR &= ( ~ ( 1 << Copy_uint8APB2Peripheral ) )  ;
	}
	else
	{
		Local_ErrorStatus = APB2PeripheralError ;
	}
	return Local_ErrorStatus ;
}

/* ******************************************************************************************************* */
/* ***************************************** SOURCE REVISION LOG ***************************************** */
/* ******************************************************************************************************* */
/*      @User                  @Date                           @Brief                                      */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  *
   Mohammed Ayman            11APR2023                       ALL Functions
   Mohammed Ayman            12APR2023                       Documentation For Functions

 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
