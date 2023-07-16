/*
 ******************************************************************************
 * @file           : RCC_Register.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Register File
 * @version        : 1.0.1
 * @Date           : Apr 10, 2023
 * @Target         : STM32F103
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 */


#ifndef STM32F103XX_H_
#define STM32F103XX_H_



/* ---------------------------------------------------------------------- */
/* ------------------------------- MACROS ------------------------------- */
/* ---------------------------------------------------------------------- */
#define NULL ((void*)0)


/* --------------------------------------------------------------------------------------------- */
/* ------------------------------- AHB PERIPHERAL BASE ADDRESSES ------------------------------- */
/* --------------------------------------------------------------------------------------------- */
#define RCC_BASE_ADDRESS      0x40021000UL




/* ---------------------------------------------------------------------------------------------- */
/* ------------------------------- APB1 PERIPHERAL BASE ADDRESSES ------------------------------- */
/* ---------------------------------------------------------------------------------------------- */


/* ---------------------------------------------------------------------------------------------- */
/* ------------------------------- APB2 PERIPHERAL BASE ADDRESSES ------------------------------- */
/* ---------------------------------------------------------------------------------------------- */
#define GPIOA_BASE_ADDRESS    0x40010800UL
#define GPIOB_BASE_ADDRESS    0x40010C00UL
#define GPIOC_BASE_ADDRESS    0x40011000UL
#define GPIOD_BASE_ADDRESS    0x40011400UL
#define GPIOE_BASE_ADDRESS    0x40011800UL


/* ------------------------------------------------------------------------------------------------------------- */
/* ------------------------------- CORTEX-M3 INTERNAL PERIPHERALS BASE ADDRESSES ------------------------------- */
/* ------------------------------------------------------------------------------------------------------------- */
#define SYSTICK_BASE_ADDRESS 0xE000E010UL


/* -------------------------------------------------------------------------------------- */
/* ------------------------- RCC REGISTERS Definition Structure ------------------------- */
/* -------------------------------------------------------------------------------------- */
typedef struct
{
	volatile uint32_t RCC_CR ;     /* Clock Control Register */
	volatile uint32_t RCC_CFGR ;    /* Clock Configuration Register */
	volatile uint32_t RCC_CIR ;      /* Clock Interrupt Register */
	volatile uint32_t RCC_APB2RSTR ;  /* APB2 Peripheral Reset Register */
	volatile uint32_t RCC_APB1RSTR ;   /* APB1 Peripheral Reset Register */
	volatile uint32_t RCC_AHBENR ;      /* AHB Peripheral Clock Enable Register */
	volatile uint32_t RCC_APB2ENR ;    /* APB2 Peripheral Clock Enable Register */
	volatile uint32_t RCC_APB1ENR ;   /* APB1 Peripheral Clock Enable Register */
	volatile uint32_t RCC_BDCR ;     /* Backup domain Control Register */
	volatile uint32_t RCC_CSR ;     /* Control/Status Register */

}RCC_Reg_t;


/* ----------------------------------------------------------------------------------------- */
/* ------------------------------- RCC Peripheral Definition ------------------------------- */
/* ----------------------------------------------------------------------------------------- */
#define RCC       ( ( RCC_Reg_t *) RCC_BASE_ADDRESS )


/* ---------------------------------------------------------------------------------- */
/* ------------------------------- RCC REGISTERS Bits ------------------------------- */
/* ---------------------------------------------------------------------------------- */

/* RCC_CR Reg Bits */
#define CR_PLLRDY      25  /* PLL Clock ready Flag */
#define CR_PLLON       24  /* PLL Enable */
#define CR_CSSON       19  /* Clock Security System Enable */
#define CR_HSEBYP      18  /* HSE Clock Bypass */
#define CR_HSERDY      17  /* HSE Clock Ready Flag */
#define CR_HSEON       16  /* HSE Clock Enable */
#define CR_HSITRM       3  /* HSE Clock Trimming Bits */
#define CR_HSIRDY       1  /* HSI Clock Ready Flag */
#define CR_HSION        0  /* HSI Clock Enable */


/* RCC_CFGR Reg Bits */
#define CFGR_MCO       23  /* Microcontroller Clock Output Bits  */
#define CFGR_USBPRE    22  /* USB Prescaler */
#define CFGR_PLLMUL    18  /* PLL Multiplication Factor Bits */
#define CFGR_PLLXTPRE  17  /* HSE Divider for PLL Entry */
#define CFGR_PLLSRC    16  /* PLL Entry Clock Source */
#define CFGR_ADCPRE    14  /* ADC Prescaler Bits */
#define CFGR_PPRE2     11  /* APB2 Prescaler Bits */
#define CFGR_PPRE1      8  /* APB1 Prescaler Bits */
#define CFGR_HPRE       4  /* AHB Prescaler Bits */
#define CFGR_SWS        2  /* System Clock Switch Status Bit */
#define CFGR_SW         0  /* System Clock Switch Bit 0 */

/* RCC_AHBENR */
#define AHBENR_SDIOEN    10
#define AHBENR_FSMCEN     8
#define AHBENR_CRCEN      6
#define AHBENR_FLITFEN    4
#define AHBENR_SRAMEN     2
#define AHBENR_DMA2EN     1
#define AHBENR_DMA1EN     0

/* RCC_APB2ENR */
#define APB2ENR_TIM11EN  21
#define APB2ENR_TIM10EN  20
#define APB2ENR_TIM9EN   19
#define APB2ENR_ADC3EN   15
#define APB2ENR_USART1EN 14
#define APB2ENR_TIM8EN   13
#define APB2ENR_SPI1EN   12
#define APB2ENR_TIM1EN   11
#define APB2ENR_ADC2EN   10
#define APB2ENR_ADC1EN    9
#define APB2ENR_IOPGEN    8
#define APB2ENR_IOPFEN    7
#define APB2ENR_IOPEEN    6
#define APB2ENR_IOPDEN    5
#define APB2ENR_IOPCEN    4
#define APB2ENR_IOPBEN    3
#define APB2ENR_IOPAEN    2
#define APB2ENR_AFIOEN    0


/* RCC_APB1ENR */
#define APB1ENR_DACEN    29
#define APB1ENR_PWREN    28
#define APB1ENR_BKPEN    27
#define APB1ENR_CANEN    25
#define APB1ENR_USBEN    23
#define APB1ENR_I2C2EN   22
#define APB1ENR_I2C1EN   21
#define APB1ENR_UART5EN  20
#define APB1ENR_UART4EN  19
#define APB1ENR_USART3EN 18
#define APB1ENR_USART2EN 17
#define APB1ENR_SPI3EN   15
#define APB1ENR_SPI2EN   14
#define APB1ENR_WWDGEN   11
#define APB1ENR_TIM14EN   8
#define APB1ENR_TIM13EN   7
#define APB1ENR_TIM12EN   6
#define APB1ENR_TIM7EN    5
#define APB1ENR_TIM6EN    4
#define APB1ENR_TIM5EN    3
#define APB1ENR_TIM4EN    2
#define APB1ENR_TIM3EN    1
#define APB1ENR_TIM2EN    0

/* --------------------------------------------------------------------------------------- */
/* ------------------------- GPIO REGISTERS Definition Structure ------------------------- */
/* --------------------------------------------------------------------------------------- */

typedef struct
{
	volatile uint32_t CRL[2] ; /*!< Port Configuration Registers Low & High  >!*/
	volatile uint32_t IDR ;    /*!< Port Input Data Register                 >!*/
	volatile uint32_t ODR ;    /*!< Port Output Data Register                >!*/
	volatile uint32_t BSRR ;   /*!< Port Bit Set/Reset Register              >!*/
	volatile uint32_t BRR ;    /*!< Port Bit Reset Register                  >!*/
	volatile uint32_t LCKR ;   /*!< Port Configuration Lock Register         >!*/

}GPIO_RegDef_t;

/* ------------------------------------------------------------------------------------------- */
/* ------------------------------- GPIO Peripheral Definitions ------------------------------- */
/* ------------------------------------------------------------------------------------------- */
 #define GPIOA     ( ( GPIO_RegDef_t * ) GPIOA_BASE_ADDRESS )
 #define GPIOB     ( ( GPIO_RegDef_t * ) GPIOB_BASE_ADDRESS )
 #define GPIOC     ( ( GPIO_RegDef_t * ) GPIOC_BASE_ADDRESS )
 #define GPIOD     ( ( GPIO_RegDef_t * ) GPIOD_BASE_ADDRESS )
 #define GPIOE     ( ( GPIO_RegDef_t * ) GPIOE_BASE_ADDRESS )


/* ------------------------------------------------------------------------------------------------------ */
/* ------------------------------- SYSTICK REGISTERS Definition Structure ------------------------------- */
/* ------------------------------------------------------------------------------------------------------ */
typedef struct
{
	volatile uint32_t SYST_CSR;	  /*<! SYSTICK Control and Status Register  >!*/
	volatile uint32_t SYST_RVR;	  /*<! SYSTICK Reload Value Register        >!*/
	volatile uint32_t SYST_CVR;	  /*<! SYSTICK Current Value Register       >!*/
	volatile uint32_t SYST_CALIB; /*<! SYSTICK Calibration Value Register   >!*/
} SYSTICK_RegDef_t;

/* --------------------------------------------------------------------------------------------- */
/* ------------------------------- SYSTICK Peripheral Definition ------------------------------- */
/* --------------------------------------------------------------------------------------------- */
#define SYSTICK ((SYSTICK_RegDef_t *)SYSTICK_BASE_ADDRESS)

/* -------------------------------------------------------------------------------------- */
/* ------------------------------- SYSTICK REGISTERS Bits ------------------------------- */
/* -------------------------------------------------------------------------------------- */

/* SYST_CSR */
#define CSR_COUNTFLAG 16
#define CSR_CLKSOURCE 2
#define CSR_TICKINT 1
#define CSR_ENABLE 0

#endif /* STM32F103XX_H_ */
