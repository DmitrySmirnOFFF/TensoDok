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
#define BUZZ_Pin GPIO_PIN_0
#define BUZZ_GPIO_Port GPIOC
#define LED0_MC_Pin GPIO_PIN_1
#define LED0_MC_GPIO_Port GPIOC
#define LED1_MC_Pin GPIO_PIN_2
#define LED1_MC_GPIO_Port GPIOC
#define LED2_MC_Pin GPIO_PIN_3
#define LED2_MC_GPIO_Port GPIOC
#define AI1_MesU_MK_Pin GPIO_PIN_0
#define AI1_MesU_MK_GPIO_Port GPIOA
#define PWM_chA_Pin GPIO_PIN_4
#define PWM_chA_GPIO_Port GPIOB
#define But2_Fall_Pin GPIO_PIN_5
#define But2_Fall_GPIO_Port GPIOB
#define PWM_chB_Pin GPIO_PIN_6
#define PWM_chB_GPIO_Port GPIOB
#define But1_Rise_Pin GPIO_PIN_7
#define But1_Rise_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

void shift_fim(uint16_t GPIO_Pin);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
