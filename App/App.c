#include "App.h"
#include "BSP.h"
#include "ProtocolMbRtuSlaveCtrl.h"

App_struct App;

uint8_t SPI_DATA_RX[8];

uint16_t ADC_DATA = 0;

void app_main(void)
{
  app_init();

  while (1) // основной цикл
  {
  asm ("nop");
  }
}


void app_init()
{
  MX_TIM7_Init();

  MX_TIM1_Init();
  
  app_tim7_10ms_start();

  protocolMbRtuSlaveCtrl_init(1);

  adc_filter_init();

  return;
}

void adc_filter_init()
{
  App.adc_filter.value = 0.0f;
  App.adc_filter.value_last = 0.0f;
  App.adc_filter.valueRaw = 0.0f;
  for (uint8_t i = 0; i < PROGRAM_ADC_MAX_FILTER_ORDER; i++)
  {
    App.adc_filter.buf[i] = 0.0f;
  }
  App.adc_filter.bufIdx = 0;
  App.adc_filter.filter_N = 1;
  App.adc_filter.order = 10.0f;
  return;
}

void app_tim7_10ms_start()
{
  HAL_TIM_Base_Start_IT(&htim7);
}

void app_tim7_10ms_callback()
{
  static uint8_t i = 0;

  app_update_reg();
  if (i++ == 5)
  {
    adc_data_filter(get_data_spi());
    protocolMbRtuSlaveCtrl_update_tables();
    i = 0;
  }
  return;
}

void TIM7_DAC_IRQHandler(void)
{
  if (__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) != RESET)
    {
      __HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
      app_tim7_10ms_callback();
    }
  }
  return;
}

void app_update_reg()
{
  //LED1
  if (HAL_GPIO_ReadPin(APP_LED_1) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AO.state_led_rele, LED_1);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AO.state_led_rele, LED_1);
  }

  //LED2
  if (HAL_GPIO_ReadPin(APP_LED_2) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AO.state_led_rele, LED_2);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AO.state_led_rele, LED_2);
  }

  //LED3
  if (HAL_GPIO_ReadPin(APP_LED_3) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AO.state_led_rele, LED_3);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AO.state_led_rele, LED_3);
  }

  //LED4
  if (HAL_GPIO_ReadPin(APP_LED_4) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AO.state_led_rele, LED_4);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AO.state_led_rele, LED_4);
  }

  //REL1
  if (HAL_GPIO_ReadPin(APP_REL_1) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AO.state_led_rele, REL_1);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AO.state_led_rele, REL_1);
  }

  //REL2
  if (HAL_GPIO_ReadPin(APP_REL_2) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AO.state_led_rele, REL_2);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AO.state_led_rele, REL_2);
  }

  //REL3
  if (HAL_GPIO_ReadPin(APP_REL_3) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AO.state_led_rele, REL_3);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AO.state_led_rele, REL_3);
  }

  //REL4
  if (HAL_GPIO_ReadPin(APP_REL_4) == GPIO_PIN_SET)
  {
    APP_SET_BIT(App.Mdb_data_AO.state_led_rele, REL_4);
  }
  else
  {
    APP_RESET_BIT(App.Mdb_data_AO.state_led_rele, REL_4);
  }
  
  App.Mdb_data_AO.spi_buf_0[0] = SPI_DATA_RX[0];
  App.Mdb_data_AO.spi_buf_0[1] = SPI_DATA_RX[1];
  App.Mdb_data_AO.spi_buf_0[2] = SPI_DATA_RX[2];
  App.Mdb_data_AO.ADC_data     = ADC_DATA;
  return;
}

// void app_parce_Mdb_AO()
// {
//   // parce BUF_DATA_AO[0]
//   if (App.Mdb_data_AO.Control_led_rel != BUF_DATA_AO[0])
//   {
//     App.Mdb_data_AO.Control_led_rel = BUF_DATA_AO[0];

//     // LED1
//     if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, LED_1))
//     {
//       APP_LED_ON(APP_LED_1);
//     }
//     else
//     {
//       APP_LED_OFF(APP_LED_1);
//     }

//     // LED2
//     if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, LED_2))
//     {
//       APP_LED_ON(APP_LED_2);
//     }
//     else
//     {
//       APP_LED_OFF(APP_LED_2);
//     }

//     // LED3
//     if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, LED_3))
//     {
//       APP_LED_ON(APP_LED_3);
//     }
//     else
//     {
//       APP_LED_OFF(APP_LED_3);
//     }

//     // LED4
//     if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, LED_4))
//     {
//       APP_LED_ON(APP_LED_4);
//     }
//     else
//     {
//       APP_LED_OFF(APP_LED_4);
//     }

//     // REL_1
//     if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, REL_1))
//     {
//       APP_REL_ON(APP_REL_1);
//     }
//     else
//     {
//       APP_REL_OFF(APP_REL_1);
//     }

//     // REL_2
//     if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, REL_2))
//     {
//       APP_REL_ON(APP_REL_2);
//     }
//     else
//     {
//       APP_REL_OFF(APP_REL_2);
//     }

//     // REL_3
//     if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, REL_3))
//     {
//       APP_REL_ON(APP_REL_3);
//     }
//     else
//     {
//       APP_REL_OFF(APP_REL_3);
//     }

//     // REL_4
//     if(APP_GET_BIT(App.Mdb_data_AO.Control_led_rel, REL_4))
//     {
//       APP_REL_ON(APP_REL_4);
//     }
//     else
//     {
//       APP_REL_OFF(APP_REL_4);
//     }
//     //App.Mdb_data_AO.Control_led_rel = BUF_DATA_AO[0] = 0;
//   }
// }


uint32_t get_data_spi()
{
  uint32_t ADC_DATA_RAW = 0;
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
  HAL_SPI_Receive(&hspi2, &SPI_DATA_RX[0], 3, 10);
  HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_1);

  ADC_DATA_RAW |= ((uint32_t)SPI_DATA_RX[0] << 16);
  ADC_DATA_RAW |= ((uint32_t)SPI_DATA_RX[1] << 8);
  ADC_DATA_RAW |= ((uint32_t)SPI_DATA_RX[2] << 0);
  return ADC_DATA_RAW;

  // ADC_DATA_FLOAT = (float)(ADC_DATA_RAW);
  // ADC_DATA = (uint16_t)((ADC_DATA_FLOAT/ADC_MAX_VALUE)*ADC_REF_VOLT*1000.0f);
  
}

#define ADC_MAX_VAL 8388607.0f
#define ADC_REF_VOLT  3.3f
void adc_data_filter(uint32_t ADC_Buf_raw)
{
  float value = 0.0f;
  float valueLast = 0.0f;
  float kFilter = 0.0f;
  float data = 0.0f;
  float sum = 0.0f;

  data = ((float)ADC_Buf_raw / ADC_MAX_VAL * ADC_REF_VOLT*1000.0f);

  App.adc_filter.buf[App.adc_filter.bufIdx++] = data;
  if (App.adc_filter.bufIdx == App.adc_filter.order) 
  {
    App.adc_filter.bufIdx = 0;
  }
  for(uint8_t idx = 0; idx < App.adc_filter.order; idx++)
  {
      sum += App.adc_filter.buf[idx];
  }
  App.adc_filter.valueRaw = sum / App.adc_filter.order;
  //--------------------//
  value = App.adc_filter.valueRaw;
  valueLast = App.adc_filter.value_last;
  kFilter = 2.0f / ((float)App.adc_filter.filter_N + 1.0f);
  value = valueLast + kFilter*(value - valueLast);
  App.adc_filter.value = value;
  App.adc_filter.value_last = value;
  ADC_DATA = value;
}

