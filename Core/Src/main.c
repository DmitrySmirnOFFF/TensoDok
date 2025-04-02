/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "comp.h"
#include "dac.h"
#include "fdcan.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

int16_t shift = 0;
int16_t low_shift = 5;
int16_t high_shift= 995;
uint8_t upDown = 0; // 0 - Up, 1 - Down

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */




/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_FDCAN1_Init();
  MX_COMP2_Init();
  MX_DAC2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_2);
  TIM1->CCR1 = 995;
  shift = TIM1->CCR1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_RESET);
    if (HAL_GPIO_ReadPin(But2_Fall_GPIO_Port,But2_Fall_Pin) == GPIO_PIN_RESET)
    {
      //HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_SET);
      shift_fim(But2_Fall_Pin);      
    }
    // else
    // {
    //   HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_RESET);
    // }

    if (HAL_GPIO_ReadPin(But1_Rise_GPIO_Port,But1_Rise_Pin) == GPIO_PIN_RESET)
    {
      //HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_SET);
      shift_fim(But1_Rise_Pin);
    }
    // else
    // {
    //   HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_RESET);
    // }

  HAL_Delay(100);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1)
  {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
      HAL_GPIO_TogglePin(PWM_chA_GPIO_Port, PWM_chA_Pin);
      //HAL_GPIO_TogglePin(BUZZ_GPIO_Port, BUZZ_Pin);
    }
    else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
    {
      HAL_GPIO_TogglePin(PWM_chB_GPIO_Port, PWM_chB_Pin);
    }
  }
}

// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
// {
//   if (GPIO_Pin == But2_Fall_Pin)
//   {
//     if (shift > low_shift)
//     {
//       shift--;
//       TIM1->CCR1--;
//     }
//   }
//   else if (GPIO_Pin == But1_Rise_Pin)
//   {
//     if (shift < high_shift)
//      {
//       shift++;
//       TIM1->CCR1++;
//      }
//   }
// }

void shift_fim(uint16_t GPIO_Pin)
{
  HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_SET);
  if (GPIO_Pin == But2_Fall_Pin)
  {
    if (shift > low_shift)
    {
      shift -= 1;
      if (shift <= low_shift)
      {
        shift = low_shift;
      }
      TIM1->CCR1 = shift;
    }
  }
  else if (GPIO_Pin == But1_Rise_Pin)
  {
    if (shift < high_shift)
     {
      if (shift >= high_shift)
      {
        shift = high_shift;
      }
      shift += 1;
      TIM1->CCR1 = shift;
     }
  }
}
/*void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  static uint16_t a = 20;
  if (htim->Instance == TIM4)
  {
  if (a++ % 10 == 0)
  {
    if (upDown == 0)
    {
      if ((shift >= -400) || (shift < 400))
      {
        TIM4->ARR += 100;
        shift += 100;
      } 
      else if (shift ==400)
      {
        upDown = 1;
      }
    }
    else
    {
      if ((shift > -400) || (shift <= 400))
      {
        TIM4->ARR -= 100;
        shift -= 100;
      } 
      else if (shift == 400)
      {
        upDown = 0;
      }  
    }
  }
  }
}
 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
