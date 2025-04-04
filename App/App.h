#ifndef __APP__H__
#define __APP__H__

#include "main.h"
#include "modbus.h"
#include "tim.h"

//-------------------------------- LED --------------------------------//
#define APP_LED_1               DO_LED_1_GPIO_Port, DO_LED_1_Pin
#define APP_LED_2               DO_LED_2_GPIO_Port, DO_LED_2_Pin
#define APP_LED_3               DO_LED_3_GPIO_Port, DO_LED_3_Pin
#define APP_LED_4               DO_LED_4_GPIO_Port, DO_LED_4_Pin

#define APP_LED_ON(LED)			HAL_GPIO_WritePin(LED, GPIO_PIN_SET)
#define APP_LED_OFF(LED)		HAL_GPIO_WritePin(LED, GPIO_PIN_RESET)
#define APP_LED_TOGGLE(LED)		HAL_GPIO_TogglePin(LED)
//------------------------------ LED END ------------------------------//


//-------------------------------- REL --------------------------------//
#define APP_REL_1               DO_REL_1_GPIO_Port, DO_REL_1_Pin
#define APP_REL_2               DO_REL_2_GPIO_Port, DO_REL_2_Pin
#define APP_REL_3               DO_REL_3_GPIO_Port, DO_REL_3_Pin
#define APP_REL_4               DO_REL_4_GPIO_Port, DO_REL_4_Pin

#define APP_REL_ON(REL)			HAL_GPIO_WritePin(REL, GPIO_PIN_SET)
#define APP_REL_OFF(REL)		HAL_GPIO_WritePin(REL, GPIO_PIN_RESET)
#define APP_REL_TOGGLE(REL)		HAL_GPIO_TogglePin(REL)
//------------------------------ REL END ------------------------------//


//------------------------------- STRUCT -------------------------------//
typedef struct 
{
    uint16_t State_led_rel; // AI[0]
} Mdb_data_AI_struct;

typedef struct 
{
    uint16_t Control_led_rel; // AO[0]
} Mdb_data_AO_struct;

typedef struct 
{
    Mdb_data_AI_struct Mdb_data_AI;
    Mdb_data_AO_struct Mdb_data_AO;
} App_struct;
//----------------------------- STRUCT END -----------------------------//

//------------------------------ FUNCTION ------------------------------//
void app_main();
void app_init();

void app_tim7_1k_start();
void app_tim7_1k_callback();

void app_parce_Mdb_AO();

void app_Mdb_Update_Data_AI();

//---------------------------- FUNCTION END ----------------------------//

#endif