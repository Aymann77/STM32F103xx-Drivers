/*
 ******************************************************************************
 * @file           : SSD_Config.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : May 14, 2023
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
#ifndef SSD_INC_SSD_CONFIG_H_
#define SSD_INC_SSD_CONFIG_H_
/* OPTIONS :
 *         COM_CATHODE     ,     COM_ANODE
 **/
#define SSD_1_COM_TYPE   COM_CATHODE

#define SSD_2_COM_TYPE   COM_CATHODE

#define SSD_3_COM_TYPE   COM_CATHODE

/* SSD LEDS PORTS AND PINS */
#define LEDA_PORT   PORTA
#define LEDA_PIN    PIN11

#define LEDB_PORT   PORTA
#define LEDB_PIN    PIN8


#define LEDC_PORT   PORTB
#define LEDC_PIN    PIN15

#define LEDD_PORT   PORTB
#define LEDD_PIN    PIN14


#define LEDE_PORT   PORTB
#define LEDE_PIN    PIN13

#define LEDF_PORT   PORTB
#define LEDF_PIN    PIN12

#define LEDG_PORT   PORTA
#define LEDG_PIN    PIN12

#define DOT_PORT    PORTA
#define DOT_PIN     PIN15

#define COM_SSD_1_PORT PORTB
#define COM_SSD_1_PIN  PIN8

#define COM_SSD_2_PORT PORTB
#define COM_SSD_2_PIN  PIN9

#define COM_SSD_3_PORT PORTB
#define COM_SSD_3_PIN  PIN3

#endif /* SSD_INC_SSD_CONFIG_H_ */
