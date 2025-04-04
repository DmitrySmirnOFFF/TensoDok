#include "App.h"

App_struct App;

void app_main(void)
{
  app_init();
  

  while (1) // основной цикл
  {
    HAL_Delay(500);
  }
}


void app_init()
{
  MX_TIM7_Init();
  app_tim7_1k_start();

  ModbusRTU_Init();
}

void app_tim7_1k_start()
{
  HAL_TIM_Base_Start_IT(&htim7);
}

void app_tim7_1k_callback()
{
  app_Mdb_Update_Data_AI();
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

void app_Mdb_Update_Data_AI()
{
 BUF_DATA_AI[0] = App.Mdb_data_AI.State_led_rel;

}

void app_parce_Mdb_AO()
{
  ;
}
