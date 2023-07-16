/*
 ******************************************************************************
 * @file           : GPIO_Interface.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : May 8, 2023
 * @Target         : STM32F103xx
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/* --------------------------------------------------------------------------------- */
/* ------------------------------- GPIO Option Enums ------------------------------- */
/* --------------------------------------------------------------------------------- */

/* *************
 *  @Port_t
 *
 *
 **/
typedef enum
{
	PORTA = 0,	PORTB,	PORTC,	PORTD,	PORTE, NUM_OF_GPIOs
}Port_t;


/* *************
 *  @HalfPort_t
 *
 *
 **/
typedef enum
{
	LOWER_PORT = 0 , UPPER_PORT
}HalfPort_t;

/* *************
 *  @Pin_t
 *
 *
 **/
typedef enum
{
	PIN0 = 0, PIN1, PIN2, PIN3, PIN4, PIN5,	PIN6, PIN7,
	PIN8,PIN9,PIN10,PIN11,PIN12,PIN13,PIN14,PIN15
} Pin_t;

/* *************
 *  @Mode_t
 *
 *
 **/
typedef enum
{
	INPUT = 0,
    OUTPUT_MAXSPEED_10MHZ ,
	OUTPUT_MAXSPEED_2MHZ ,
	OUTPUT_MAXSPEED_50MHZ
} Mode_t;


/* *************
 *  @InputMode_t
 *
 *
 **/
typedef enum
{
  ANALOG = 0 ,
  FLOATING ,
  PULL_UP_OR_PULL_DOWN ,
} InputMode_t;

/* *************
 *  @PullType_t
 *
 *
 **/
typedef enum
{
  PULL_DOWN = 0 ,
  PULL_UP
} PullType_t;


/* *************
 *  @OutputMode_t
 *
 *
 **/
typedef enum
{
	OUTPUT_PUSH_PULL = 0,
	OUTPUT_OPEN_DRAIN ,
	ALTERNATE_FUNC_PUSH_PULL ,
	ALTERNATE_FUNC_OPEN_DRAIN
} OutputMode_t;


/* *************
 *  @PinValue_t
 *
 *
 **/
typedef enum
{
	PIN_LOW,
	PIN_HIGH
} PinValue_t;

/* ----------------------------------------------------------------------------------------- */
/* ------------------------------- GPIO Pin Config Structure ------------------------------- */
/* ----------------------------------------------------------------------------------------- */

typedef struct
{
	Port_t Port;
	Pin_t PinNum;
	Mode_t Mode;
	InputMode_t InMode ;
	PullType_t PullType ;
	OutputMode_t OutMode ;

} GPIO_PinConfig_t;

/* ------------------------------------------------------------------------------------------------ */
/* ------------------------------- FUCTION PROTOTYPES SECTION START ------------------------------- */
/* ------------------------------------------------------------------------------------------------ */



/**
 * @fn			         : GPIO_u8PinInit
 * @brief		         : Function Initializes A GPIO Pin According to the Input Parameters
 * @param     PinConfig  : Initialization Values of the Pin
 * @retval		         : Error Status
 *                           -> OK , GPIO_NOT_VALID , NULL_POINTER
 * @note			     : U don't Have To Use All Elements of the Struct
 *                             if u don't need one of them don't give it a Value
 **/

uint8_t GPIO_u8PinInit(const GPIO_PinConfig_t * PinConfig) ;

/**
 * @fn			         : GPIO_u8SetPinValue
 * @brief		         : Function To Set A GPIO Pin to A Certain Value
 * @param     Port       : USED PORT , To get Values -> @Port_t
 * @param     PinNum     : USED PIN , To get Values -> @Pin_t
 * @param     PinValue   : Value to Put on a Certain Pin , To get Values -> @PinValue_t
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t PinNum, PinValue_t PinValue) ;

/**
 * @fn			         : GPIO_u8TogglePinValue
 * @brief		         : Function To Toggle A GPIO Pin Value ( From High to Low or Vice Versa )
 * @param     Port       : USED PORT , To get Values -> @Port_t
 * @param     PinNum     : USED PIN , To get Values -> @Pin_t
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum) ;

/**
 * @Fn			         : GPIO_u8ReadPinValue
 * @brief		         : Function To Read GPIO Pin and Return in Pointer the Value on the Pin
 * @param     Port       : USED PORT , To get Values -> @Port_t
 * @param     PinNum     : USED PIN , To get Values -> @Pin_t
 * @param     PinValue   : Pointer To Put the Result init , Values -> @PinValue_t
 * @retval		         : Error Status
 *                           -> OK , NOK , NULL_POINTER
 **/

uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinValue_t *PinValue);



/**
 * @fn			         : GPIO_u8SetFourPinsValue
 * @brief		         : Function To Value of  Four Pins
 * @param     Port       : USED PORT , To get Values -> @Port_t
 * @param     PinNum     : USED PIN ( Starting Pin to Put the Value From it ) , To get Values -> @Pin_t
 * @param     Value      : Value to Put on the Four Pins From the Starting Pin Number
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

uint8_t GPIO_u8SetFourPinsValue( Port_t PortNum , Pin_t PinNum , uint8_t Copy_u8Value  ) ;


/**
 * @fn			         : GPIO_u8SetHalfPortValue
 * @brief		         : Function To Set Eight Pins ( Half Port ) Value
 * @param     PortNum    : USED PORT , To get Values -> @Port_t
 * @param     HalfPort   : USED Part of Port , To get Values -> @HalfPort_t
 * @param     Value      : Value to Put on the Eight Pins Pins
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

uint8_t GPIO_u8SetHalfPortValue( Port_t PortNum , HalfPort_t HalfPort , uint8_t Copy_u8Value ) ;



/**
 * @fn			          : GPIO_u8PinsInit
 * @brief		          : Function Initializes Punch of Gpio Pins Combined in Array
 * @param     PinsConfig  : Initialization Values of All Pins
 * @param     Copy_u8Size : Size of Array to Indicate for Number of Pins You want to Initialize
 * @retval		          : Error Status
 *                           -> OK , GPIO_NOK
 * @note			      : In Order to Use this Function Make in your App Array of Structs <GPIO_PinConfig_t>
 *                  Fill the array with the values and pass it by reference to the function with the size of array
 **/

uint8_t GPIO_u8PinsInit( const GPIO_PinConfig_t * PinsConfig , uint8_t Copy_u8Size ) ;
/* ---------------------------------------------------------------------------------------------- */
/* ------------------------------- FUCTION PROTOTYPES SECTION END ------------------------------- */
/* ---------------------------------------------------------------------------------------------- */


#endif /* GPIO_INTERFACE_H_ */
