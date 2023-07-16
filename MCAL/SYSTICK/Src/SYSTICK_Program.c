/*
 ******************************************************************************
 * @file           : SYSTICK_Program.c
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : SYSTICK Main Program File
 * @Date           : May 12, 2023
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

#include "../../../LIB/ErrType.h"
#include "../../../LIB/STM32F103xx.h"

#include "../Inc/SYSTICK_Interface.h"
#include "../Inc/SYSTICK_Private.h"

/*==============================================================================================================================================
 * INCLUDES SECTION END
 *==============================================================================================================================================*/



/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION START
 *==============================================================================================================================================*/

extern SYSTICK_CONFIG_t SYSTICK_TIMER_CONFIG ;

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION END
 *==============================================================================================================================================*/


/*==============================================================================================================================================
 * MODULES IMPLEMENTATION
 *==============================================================================================================================================*/

/**
 * @fn			                    : SYSTICK_Delayms
 * @brief		                    : Fuction That Makes Delay in Software Based on Passed Number of Milliseconds
 * @param     Copy_u32TimeInMillis  : Time Passed To Delay in Milliseconds
 * @retval		                    : VOID
 * @note	                        : -> IN SYSTICK_CLK_AHB Maximum Delay is 2000ms ( 2 Seconds )
 *                                    -> IN SYSTICK_CLK_AHB_BY8 Maximum Delay is 16000ms ( 16 Seconds )
 **/

void SYSTICK_Delayms(uint32_t Copy_u32TimeInMillis)
{
	/* Variable To Carry RELOAD Value */
	uint32_t RELOAD_Value = 0 ;

		/* Check on TIMER_CLK  */
		if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB )
		{
			RELOAD_Value = ( Copy_u32TimeInMillis * 1000UL ) / AHB_TICK_TIME ;
		}
		else if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB_BY8 )
		{
			RELOAD_Value = ( Copy_u32TimeInMillis * 1000UL ) / AHB_BY8_TICK_TIME ;
		}

		/* Setting Reload Value */
		( SYSTICK->SYST_RVR ) = RELOAD_Value ;

		/* Clear Current */
		( SYSTICK->SYST_CVR ) = 0 ;

		/* Set Exception */
		( SYSTICK->SYST_CSR ) &= ~(1<<CSR_TICKINT) ;
		( SYSTICK->SYST_CSR ) |= ( ( SYSTICK_TIMER_CONFIG.Exception ) << CSR_TICKINT ) ;

		/* Set Clock Source */
		( SYSTICK->SYST_CSR ) &= ~(1<<CSR_CLKSOURCE) ;
		( SYSTICK->SYST_CSR ) |= ( ( SYSTICK_TIMER_CONFIG.CLK ) << CSR_CLKSOURCE ) ;

		/* Enable Timer */
		( SYSTICK->SYST_CSR ) |= ( 1 << CSR_ENABLE ) ;

		/* Check on Flag */
		while( !( ( (SYSTICK->SYST_CSR)>>CSR_COUNTFLAG )&0x01) ) ;

		/* Disable Timer */
		( SYSTICK->SYST_CSR ) &= ~( 1 << CSR_ENABLE ) ;

}


/**
 * @fn			                   		 : SYSTICK_Delayus
 * @brief		                    	 : Fuction That Makes Delay in Software Based on Passed Number of MicroSeconds
 * @param     Copy_u32TimeInMicroSeconds : Time Passed To Delay in MicroSeconds
 * @retval		                   		 : VOID
 **/

void SYSTICK_Delayus(uint32_t Copy_u32TimeInMicroSeconds)
{
	/* Variable To Carry RELOAD Value */
		uint32_t RELOAD_Value = 0 ;

			/* Check on TIMER_CLK  */
			if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB )
			{
				RELOAD_Value = ( Copy_u32TimeInMicroSeconds  / AHB_TICK_TIME ) ;
			}
			else if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB_BY8 )
			{
				RELOAD_Value = ( Copy_u32TimeInMicroSeconds  / AHB_BY8_TICK_TIME ) ;
			}

			/* Setting Reload Value */
			( SYSTICK->SYST_RVR ) = RELOAD_Value ;

			/* Clear Current */
			( SYSTICK->SYST_CVR ) = 0 ;

			/* Set Exception */
			( SYSTICK->SYST_CSR ) &= ~(1<<CSR_TICKINT) ;
			( SYSTICK->SYST_CSR ) |= ( ( SYSTICK_TIMER_CONFIG.Exception ) << CSR_TICKINT ) ;

			/* Set Clock Source */
			( SYSTICK->SYST_CSR ) &= ~(1<<CSR_CLKSOURCE) ;
			( SYSTICK->SYST_CSR ) |= ( ( SYSTICK_TIMER_CONFIG.CLK ) << CSR_CLKSOURCE ) ;

			/* Enable Timer */
			( SYSTICK->SYST_CSR ) |= ( 1 << CSR_ENABLE ) ;

			/* Check on Flag */
			while( !( ( (SYSTICK->SYST_CSR)>>CSR_COUNTFLAG )&0x01) ) ;

			/* Disable Timer */
			( SYSTICK->SYST_CSR ) &= ~( 1 << CSR_ENABLE ) ;

}
