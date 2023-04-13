/*
 ******************************************************************************
 * @file           : RCC_Register.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Register File
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
#ifndef RCC_RCC_REGISTER_H_
#define RCC_RCC_REGISTER_H_

/* ************************* RCC Registers Section ************************* */
typedef struct
{
	uint32_t RCC_CR ;     /* Clock Control Register */
	uint32_t RCC_CFGR ;    /* Clock Configuration Register */
	uint32_t RCC_CIR ;      /* Clock Interrupt Register */
	uint32_t RCC_APB2RSTR ;  /* APB2 Peripheral Reset Register */
	uint32_t RCC_APB1RSTR ;   /* APB1 Peripheral Reset Register */
	uint32_t RCC_AHBENR ;      /* AHB Peripheral Clock Enable Register */
	uint32_t RCC_APB2ENR ;    /* APB2 Peripheral Clock Enable Register */
	uint32_t RCC_APB1ENR ;   /* APB1 Peripheral Clock Enable Register */
	uint32_t RCC_BDCR ;     /* Backup domain Control Register */
	uint32_t RCC_CSR ;     /* Control/Status Register */

}RCC_Reg_t;

RCC_Reg_t * RCC = RCC_BASE_ADD ;


/* ************************* RCC Register's Bits ************************* */

/* RCC_CR Reg Bits */
#define CR_PLLRDY      25 /* PLL Clock ready Flag */
#define CR_PLLON       24 /* PLL Enable */
#define CR_CSSON       19 /* Clock Security System Enable */
#define CR_HSEBYP      18 /* HSE Clock Bypass */
#define CR_HSERDY      17 /* HSE Clock Ready Flag */
#define CR_HSEON       16 /* HSE Clock Enable */
#define CR_HSICAL7     15 /* HSE Clock Clibration Bit 7 */
#define CR_HSICAL6     14 /* HSE Clock Clibration Bit 6 */
#define CR_HSICAL5     13 /* HSE Clock Clibration Bit 5 */
#define CR_HSICAL4     12 /* HSE Clock Clibration Bit 4 */
#define CR_HSICAL3     11 /* HSE Clock Clibration Bit 3 */
#define CR_HSICAL2     10 /* HSE Clock Clibration Bit 2 */
#define CR_HSICAL1      9 /* HSE Clock Clibration Bit 1 */
#define CR_HSICAL0      8 /* HSE Clock Clibration Bit 0 */
#define CR_HSITRM4      7 /* HSE Clock Trimming Bit 4 */
#define CR_HSITRM3      6 /* HSE Clock Trimming Bit 3 */
#define CR_HSITRM2      5 /* HSE Clock Trimming Bit 2 */
#define CR_HSITRM1      4 /* HSE Clock Trimming Bit 1 */
#define CR_HSITRM0      3 /* HSE Clock Trimming Bit 0 */
#define CR_HSIRDY       1 /* HSI Clock Ready Flag */
#define CR_HSION        0 /* HSI Clock Enable */


/* RCC_CFGR Reg Bits */
#define CFGR_MCO2      26 /* Microcontroller Clock Output Bit 2  */
#define CFGR_MCO1      25 /* Microcontroller Clock Output Bit 1  */
#define CFGR_MCO0      23 /* Microcontroller Clock Output Bit 0  */
#define CFGR_USBPRE    22 /* USB Prescaler */
#define CFGR_PLLMUL3   21 /* PLL Multiplication Factor Bit 3 */
#define CFGR_PLLMUL2   20 /* PLL Multiplication Factor Bit 2 */
#define CFGR_PLLMUL1   19 /* PLL Multiplication Factor Bit 1 */
#define CFGR_PLLMUL0   18 /* PLL Multiplication Factor Bit 0 */
#define CFGR_PLLXTPRE  17 /* HSE Divider for PLL Entry */
#define CFGR_PLLSRC    16 /* PLL Entry Clock Source */
#define CFGR_ADCPRE1   15 /* ADC Prescaler Bit 1 */
#define CFGR_ADCPRE0   14 /* ADC Prescaler Bit 0 */
#define CFGR_PPRE22    13 /* APB2 Prescaler Bit 2 */
#define CFGR_PPRE21    12 /* APB2 Prescaler Bit 1 */
#define CFGR_PPRE20    11 /* APB2 Prescaler Bit 0 */
#define CFGR_PPRE12    10 /* APB1 Prescaler Bit 2 */
#define CFGR_PPRE11     9 /* APB1 Prescaler Bit 1 */
#define CFGR_PPRE10     8 /* APB1 Prescaler Bit 0 */
#define CFGR_HPRE3      7 /* AHB Prescaler Bit 3 */
#define CFGR_HPRE2      6 /* AHB Prescaler Bit 2 */
#define CFGR_HPRE1      5 /* AHB Prescaler Bit 1 */
#define CFGR_HPRE0      4 /* AHB Prescaler Bit 0 */
#define CFGR_SWS1       3 /* System Clock Switch Status Bit 1 */
#define CFGR_SWS0       2 /* System Clock Switch Status Bit 0 */
#define CFGR_SW1        1 /* System Clock Switch Bit 1 */
#define CFGR_SW0        0 /* System Clock Switch Bit 0 */

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




#endif /* RCC_RCC_REGISTER_H_ */
