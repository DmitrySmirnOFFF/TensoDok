#include "App.h"

App_struct App;

uint8_t SPI_DATA_RX[5];
uint8_t *data_rx = &SPI_DATA_RX[0];
uint32_t ADC_DATA_RAW = 0;
float ADC_DATA_FLOAT = 0.0f;
uint16_t ADC_DATA = 0;

uint32_t tim1_cnt = 0;

void app_main(void)
{
  app_init();
  

  while (1) // основной цикл
  {
  //   if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET)
  //   {
  //     APP_LED_ON(APP_LED_3);
  //   }
  //   else
  //   {
  //     APP_LED_OFF(APP_LED_3);
  //   }
  asm ("nop");
  }
  
}


void app_init()
{
  MX_TIM7_Init();
  app_tim7_1k_start();

  // HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);
  //HAL_TIM_Base_Start_IT(&htim1);
  //HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_1);
  ModbusRTU_Init();
}

void app_tim7_1k_start()
{
  HAL_TIM_Base_Start_IT(&htim7);
}

void app_tim7_1k_callback()
{
  static uint16_t i = 0;

  if ((i++ > 500))
  {
    app_update_Mdb_Data_AI();
    app_parce_Mdb_AO();
    get_data_spi();
    i = 0;
  }
}

void TIM7_DAC_IRQHandler(void)
{
  if (__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) != RESET)
    {
      __HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
      app_tim7_1k_callback();
    }
  }
}

void app_update_Mdb_Data_AI()
{
  //LED1
  if (HAL_GPIO_ReadPin(APP_LED_1) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AI.State_led_rel, LED_1);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AI.State_led_rel, LED_1);
  }

  //LED2
  if (HAL_GPIO_ReadPin(APP_LED_2) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AI.State_led_rel, LED_2);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AI.State_led_rel, LED_2);
  }

  //LED3
  if (HAL_GPIO_ReadPin(APP_LED_3) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AI.State_led_rel, LED_3);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AI.State_led_rel, LED_3);
  }

  //LED4
  if (HAL_GPIO_ReadPin(APP_LED_4) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AI.State_led_rel, LED_4);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AI.State_led_rel, LED_4);
  }

  //REL1
  if (HAL_GPIO_ReadPin(APP_REL_1) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AI.State_led_rel, REL_1);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AI.State_led_rel, REL_1);
  }

  //REL2
  if (HAL_GPIO_ReadPin(APP_REL_2) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AI.State_led_rel, REL_2);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AI.State_led_rel, REL_2);
  }

  //REL3
  if (HAL_GPIO_ReadPin(APP_REL_3) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AI.State_led_rel, REL_3);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AI.State_led_rel, REL_3);
  }

  //REL4
  if (HAL_GPIO_ReadPin(APP_REL_4) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AI.State_led_rel, REL_4);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AI.State_led_rel, REL_4);
  }
  
  BUF_DATA_AI[0] = App.Mdb_data_AI.State_led_rel;
  App.Mdb_data_AO.Control_led_rel = App.Mdb_data_AI.State_led_rel;
  BUF_DATA_AI[1] = SPI_DATA_RX[0];
  BUF_DATA_AI[2] = SPI_DATA_RX[1];
  BUF_DATA_AI[3] = SPI_DATA_RX[2];
  BUF_DATA_AI[4] = ADC_DATA;
}

void app_parce_Mdb_AO()
{
  // parce BUF_DATA_AO[0]
  if (App.Mdb_data_AO.Control_led_rel != BUF_DATA_AO[0])
  {
    App.Mdb_data_AO.Control_led_rel = BUF_DATA_AO[0];

    // LED1
    if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, LED_1))
    {
      APP_LED_ON(APP_LED_1);
    }
    else
    {
      APP_LED_OFF(APP_LED_1);
    }

    // LED2
    if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, LED_2))
    {
      APP_LED_ON(APP_LED_2);
    }
    else
    {
      APP_LED_OFF(APP_LED_2);
    }

    // LED3
    if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, LED_3))
    {
      APP_LED_ON(APP_LED_3);
    }
    else
    {
      APP_LED_OFF(APP_LED_3);
    }

    // LED4
    if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, LED_4))
    {
      APP_LED_ON(APP_LED_4);
    }
    else
    {
      APP_LED_OFF(APP_LED_4);
    }

    // REL_1
    if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, REL_1))
    {
      APP_REL_ON(APP_REL_1);
    }
    else
    {
      APP_REL_OFF(APP_REL_1);
    }

    // REL_2
    if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, REL_2))
    {
      APP_REL_ON(APP_REL_2);
    }
    else
    {
      APP_REL_OFF(APP_REL_2);
    }

    // REL_3
    if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, REL_3))
    {
      APP_REL_ON(APP_REL_3);
    }
    else
    {
      APP_REL_OFF(APP_REL_3);
    }

    // REL_4
    if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, REL_4))
    {
      APP_REL_ON(APP_REL_4);
    }
    else
    {
      APP_REL_OFF(APP_REL_4);
    }
    //App.Mdb_data_AO.Control_led_rel = BUF_DATA_AO[0] = 0;
  }
}

#define ADC_MAX_VALUE 8388607.0f
#define ADC_REF_VOLT  3.3f

void get_data_spi()
{
  // while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET)
  // {
  //   ;
  // }
  // while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET)
  // {
  //   ;
  // }
  // app_tim1_clear_cnt();
  // while((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET))
  // {
  //   ;
  // }
  // if (app_tim1_get_cnt() > 20)
  // {
  //   while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET)
  //   {
  //     ;
  //   }
  //   while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET)
  //   {
  //     ;
  //   }
  //   HAL_SPI_Receive(&hspi2, data_rx, 3, 100);
  // }
  // else
  // {
  //   while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET)
  //   {
  //     ;
  //   }
  //   while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET)
  //   {
  //     ;
  //   }
  //   app_tim1_clear_cnt();
  //   while((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET))
  //   {
  //     ;
  //   }
  //   while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET)
  //   {
  //     ;
  //   }
  //   while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET)
  //   {
  //     ;
  //   }
  //   HAL_SPI_Receive(&hspi2, data_rx, 3, 100);
  // }

  HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_1);
  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET)
  {
    ;
  }
  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET)
  {
    ;
  }
  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET)
  {
    ;
  }
  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET)
  {
    ;
  }
  //HAL_Delay(1);
  HAL_SPI_Receive(&hspi2, data_rx, 3, 100);
  HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_1);
//
  asm ("nop");
  ADC_DATA_RAW = 0;
  ADC_DATA_RAW |= ((uint32_t)SPI_DATA_RX[0] << 16);
  ADC_DATA_RAW |= ((uint32_t)SPI_DATA_RX[1] << 8);
  ADC_DATA_RAW |= ((uint32_t)SPI_DATA_RX[2] << 0);
  ADC_DATA_FLOAT = (float)(ADC_DATA_RAW);
  ADC_DATA = (uint16_t)((ADC_DATA_FLOAT/ADC_MAX_VALUE)*ADC_REF_VOLT*1000.0f);
}

void TIM1_UP_TIM16_IRQHandler(void)
{
if (__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(&htim1, TIM_IT_UPDATE) != RESET)
    {
      __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);
      tim1_cnt++;
    }
  }
}

uint32_t app_tim1_get_cnt()
{
  return tim1_cnt;
}

void app_tim1_clear_cnt()
{
  tim1_cnt = 0;
}