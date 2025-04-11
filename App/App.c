#include "App.h"
#include "BSP.h"
#include "ProtocolMbRtuSlaveCtrl.h"

App_struct App;

void app_main(void)
{
  bsp_init();
  app_init();

  while (1) // основной цикл
  {
  asm ("nop");
  }
}

void app_init()
{
  protocolMbRtuSlaveCtrl_init(1);
  app_adc_filter_init();
  return;
}

void app_adc_filter_init()
{
// -------------------------- ADC_ADS1251 -------------------------- //
    App.adc_filter[ADC_ADS1251].value = 0.0f;
    App.adc_filter[ADC_ADS1251].value_last = 0.0f;
    App.adc_filter[ADC_ADS1251].valueRaw = 0.0f;
    for (uint8_t j = 0; j < PROGRAM_ADC_MAX_FILTER_ORDER; j++)
    {
      App.adc_filter[ADC_ADS1251].buf[j] = 0.0f;
    }
    App.adc_filter[ADC_ADS1251].bufIdx = 0;
    App.adc_filter[ADC_ADS1251].filter_N = 100;
    App.adc_filter[ADC_ADS1251].order = 24;
// ------------------------ ADC_ADS1251 END ------------------------ //

// -------------------------- ADC_CPU -------------------------- //
    App.adc_filter[ADC_CPU].value = 0.0f;
    App.adc_filter[ADC_CPU].value_last = 0.0f;
    App.adc_filter[ADC_CPU].valueRaw = 0.0f;
    for (uint8_t j = 0; j < PROGRAM_ADC_MAX_FILTER_ORDER; j++)
    {
      App.adc_filter[ADC_CPU].buf[j] = 0.0f;
    }
    App.adc_filter[ADC_CPU].bufIdx = 0;
    App.adc_filter[ADC_CPU].filter_N = 250;
    App.adc_filter[ADC_CPU].order = 24;
// ------------------------ ADC_CPU END ------------------------ //

}

void bsp_tim7_1ms_callback()
{
  static uint8_t i = 0;
  static uint16_t j = 0;


  if (i++ >= 10)
  {
    app_update_reg();
    protocolMbRtuSlaveCtrl_update_tables();
    i = 0;
  }

  if (j++ >= 500)
  {
    //APP_LED_TOGGLE(APP_LED_3);
    j = 0;
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
  App.Mdb_data_AO.ADC_data     = App.adc_filter[ADC_ADS1251].value;
  App.Mdb_data_AO.ADC_CPU_data = App.adc_filter[ADC_CPU].value;
  return;
}

void bsp_ADC_data_ready()
{
  APP_LED_TOGGLE(APP_LED_3);
  app_adc_data_filter((HAL_ADCEx_InjectedGetValue(&hadc2, ADC_INJECTED_RANK_2)/16), ADC_CPU);
  app_adc_data_filter(bsp_get_data_spi(), ADC_ADS1251);
}

#define ADC_ADS1251_MAX_VAL 8388607.0f
#define ADC_ADS1251_REF_VOLT  3.3f
#define ADC_CPU_MAX_VAL 4096.0f
#define ADC_CPU_REF_VOLT  3.3f
void app_adc_data_filter(uint32_t ADC_Buf_raw, ADC_enum adc)
{
  float value = 0.0f;
  float valueLast = 0.0f;
  float kFilter = 0.0f;
  float data = 0.0f;
  float sum = 0.0f;
  if (adc == ADC_ADS1251)
  {
    data = ((float)ADC_Buf_raw / ADC_ADS1251_MAX_VAL * ADC_ADS1251_REF_VOLT * 1000.0f);
  }
  else if (adc == ADC_CPU)
  {
    data = ((float)ADC_Buf_raw / ADC_CPU_MAX_VAL * ADC_CPU_REF_VOLT * 1000.0f);
  }

  App.adc_filter[adc].buf[App.adc_filter[adc].bufIdx++] = data;

  if (App.adc_filter[adc].bufIdx == App.adc_filter[adc].order) 
  {
    App.adc_filter[adc].bufIdx = 0;
  }

  for(uint8_t idx = 0; idx < App.adc_filter[adc].order; idx++)
  {
    sum += App.adc_filter[adc].buf[idx];
  }

  App.adc_filter[adc].valueRaw = sum / App.adc_filter[adc].order;
  
  //--------------------//
  value = App.adc_filter[adc].valueRaw;
  valueLast = App.adc_filter[adc].value_last;
  kFilter = 2.0f / ((float)App.adc_filter[adc].filter_N + 1.0f);
  value = valueLast + kFilter*(value - valueLast);
  App.adc_filter[adc].value = value;
  App.adc_filter[adc].value_last = value;
}

void app_control_led_rele(uint16_t control_led_rele)
{
    // LED1
    if(APP_GET_BIT(App.Mdb_data_AO.control_led_rele, LED_1))
    {
      APP_LED_ON(APP_LED_1);
    }
    else
    {
      APP_LED_OFF(APP_LED_1);
    }

    // LED2
    if(APP_GET_BIT(App.Mdb_data_AO.control_led_rele, LED_2))
    {
      APP_LED_ON(APP_LED_2);
    }
    else
    {
      APP_LED_OFF(APP_LED_2);
    }

    // LED3
    if(APP_GET_BIT(App.Mdb_data_AO.control_led_rele, LED_3))
    {
      APP_LED_ON(APP_LED_3);
    }
    else
    {
      APP_LED_OFF(APP_LED_3);
    }

    // LED4
    if(APP_GET_BIT(App.Mdb_data_AO.control_led_rele, LED_4))
    {
      APP_LED_ON(APP_LED_4);
    }
    else
    {
      APP_LED_OFF(APP_LED_4);
    }

    // REL_1
    if(APP_GET_BIT(App.Mdb_data_AO.control_led_rele, REL_1))
    {
      APP_REL_ON(APP_REL_1);
    }
    else
    {
      APP_REL_OFF(APP_REL_1);
    }

    // REL_2
    if(APP_GET_BIT(App.Mdb_data_AO.control_led_rele, REL_2))
    {
      APP_REL_ON(APP_REL_2);
    }
    else
    {
      APP_REL_OFF(APP_REL_2);
    }

    // REL_3
    if(APP_GET_BIT(App.Mdb_data_AO.control_led_rele, REL_3))
    {
      APP_REL_ON(APP_REL_3);
    }
    else
    {
      APP_REL_OFF(APP_REL_3);
    }

    // REL_4
    if(APP_GET_BIT(App.Mdb_data_AO.control_led_rele, REL_3))
    {
      APP_REL_ON(APP_REL_4);
    }
    else
    {
      APP_REL_OFF(APP_REL_4);
    }
}


