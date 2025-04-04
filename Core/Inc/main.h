/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TIM7_Presc (168-1)
#define DO_LED_1_Pin GPIO_PIN_1
#define DO_LED_1_GPIO_Port GPIOC
#define DO_LED_2_Pin GPIO_PIN_2
#define DO_LED_2_GPIO_Port GPIOC
#define AI_T_Pin GPIO_PIN_0
#define AI_T_GPIO_Port GPIOA
#define DO_REL_1_Pin GPIO_PIN_3
#define DO_REL_1_GPIO_Port GPIOA
#define DO_REL_2_Pin GPIO_PIN_4
#define DO_REL_2_GPIO_Port GPIOA
#define DO_REL_3_Pin GPIO_PIN_5
#define DO_REL_3_GPIO_Port GPIOA
#define DO_REL_4_Pin GPIO_PIN_6
#define DO_REL_4_GPIO_Port GPIOA
#define AI_R_Pin GPIO_PIN_5
#define AI_R_GPIO_Port GPIOC
#define DO_LED_3_Pin GPIO_PIN_10
#define DO_LED_3_GPIO_Port GPIOA
#define DO_LED_4_Pin GPIO_PIN_11
#define DO_LED_4_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
