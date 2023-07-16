/*
 ******************************************************************************
 * @file           : SSD_Private.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : May 14, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */
#ifndef SSD_INC_SSD_PRIVATE_H_
#define SSD_INC_SSD_PRIVATE_H_

#define COM_ANODE   1
#define COM_CATHODE 2


#if SSD_1_COM_TYPE == COM_CATHODE

#define ZERO_SSD1  0x3F
#define ONE_SSD1   0x06
#define TWO_SSD1   0x5B
#define THREE_SSD1 0x4F
#define FOUR_SSD1  0x66
#define FIVE_SSD1  0x6D
#define SIX_SSD1   0x7D
#define SEVEN_SSD1 0x07
#define EIGHT_SSD1 0x7F
#define NINE_SSD1  0x6F

#elif SSD_1_COM_TYPE == COM_ANODE

#define ZERO_SSD1  ~(0x3F)
#define ONE_SSD1   ~(0x06)
#define TWO_SSD1   ~(0x5B)
#define THREE_SSD1 ~(0x4F)
#define FOUR_SSD1  ~(0x66)
#define FIVE_SSD1  ~(0x6D)
#define SIX_SSD1   ~(0x7D)
#define SEVEN_SSD1 ~(0x07)
#define EIGHT_SSD1 ~(0x7F)
#define NINE_SSD1  ~(0x6F)

#endif



#if SSD_2_COM_TYPE == COM_CATHODE

#define ZERO_SSD2  0x3F
#define ONE_SSD2   0x06
#define TWO_SSD2   0x5B
#define THREE_SSD2 0x4F
#define FOUR_SSD2  0x66
#define FIVE_SSD2  0x6D
#define SIX_SSD2   0x7D
#define SEVEN_SSD2 0x07
#define EIGHT_SSD2 0x7F
#define NINE_SSD2  0x6F

#elif SSD_2_COM_TYPE == COM_ANODE

#define ZERO_SSD2  ~(0x3F)
#define ONE_SSD2   ~(0x06)
#define TWO_SSD2   ~(0x5B)
#define THREE_SSD2 ~(0x4F)
#define FOUR_SSD2  ~(0x66)
#define FIVE_SSD2  ~(0x6D)
#define SIX_SSD2   ~(0x7D)
#define SEVEN_SSD2 ~(0x07)
#define EIGHT_SSD2 ~(0x7F)
#define NINE_SSD2  ~(0x6F)

#endif

#if SSD_3_COM_TYPE == COM_CATHODE

#define ZERO_SSD3  0x3F
#define ONE_SSD3   0x06
#define TWO_SSD3   0x5B
#define THREE_SSD3 0x4F
#define FOUR_SSD3  0x66
#define FIVE_SSD3  0x6D
#define SIX_SSD3   0x7D
#define SEVEN_SSD3 0x07
#define EIGHT_SSD3 0x7F
#define NINE_SSD3  0x6F

#elif SSD_3_COM_TYPE == COM_ANODE

#define ZERO_SSD3  ~(0x3F)
#define ONE_SSD3   ~(0x06)
#define TWO_SSD3   ~(0x5B)
#define THREE_SSD3 ~(0x4F)
#define FOUR_SSD3  ~(0x66)
#define FIVE_SSD3  ~(0x6D)
#define SIX_SSD3   ~(0x7D)
#define SEVEN_SSD3 ~(0x07)
#define EIGHT_SSD3 ~(0x7F)
#define NINE_SSD3  ~(0x6F)

#endif

#endif /* SSD_INC_SSD_PRIVATE_H_ */
