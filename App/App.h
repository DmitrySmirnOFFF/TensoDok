#ifndef __APP__H__
#define __APP__H__

#include "main.h"
// #include "modbus.h"
#include "tim.h"
#include "spi.h"

//------------------------------ DEFINE ------------------------------//
#define APP_LED_1               DO_LED_1_GPIO_Port, DO_LED_1_Pin
#define APP_LED_2               DO_LED_2_GPIO_Port, DO_LED_2_Pin
#define APP_LED_3               DO_LED_3_GPIO_Port, DO_LED_3_Pin
#define APP_LED_4               DO_LED_4_GPIO_Port, DO_LED_4_Pin

#define APP_LED_ON(LED)			HAL_GPIO_WritePin(LED, GPIO_PIN_SET)
#define APP_LED_OFF(LED)		HAL_GPIO_WritePin(LED, GPIO_PIN_RESET)
#define APP_LED_TOGGLE(LED)		HAL_GPIO_TogglePin(LED)

#define APP_REL_1               DO_REL_1_GPIO_Port, DO_REL_1_Pin
#define APP_REL_2               DO_REL_2_GPIO_Port, DO_REL_2_Pin
#define APP_REL_3               DO_REL_3_GPIO_Port, DO_REL_3_Pin
#define APP_REL_4               DO_REL_4_GPIO_Port, DO_REL_4_Pin

#define APP_REL_ON(REL)			HAL_GPIO_WritePin(REL, GPIO_PIN_SET)
#define APP_REL_OFF(REL)		HAL_GPIO_WritePin(REL, GPIO_PIN_RESET)
#define APP_REL_TOGGLE(REL)		HAL_GPIO_TogglePin(REL)

#define APP_GET_BIT(REG, BIT)   (REG & (1 << BIT))
#define APP_SET_BIT(REG, BIT)   (REG |= (1 << BIT))
#define APP_RESET_BIT(REG, BIT) (REG &= ~(1 << BIT))

#define PROGRAM_ADC_MAX_FILTER_ORDER         (16)

//---------------------------- DEFINE END ----------------------------//

//------------------------------- ENUM -------------------------------//
typedef enum
{
    LED_1 = 0,
    LED_2,
    LED_3,
    LED_4,
    REL_1,
    REL_2,
    REL_3,
    REL_4
}LED_REL_ENUM;
//----------------------------- ENUM END -----------------------------//

//------------------------------- STRUCT -------------------------------//

typedef struct 
{
    uint16_t state_led_rele;
    uint16_t control_led_rele; 
    uint16_t spi_buf_0[3];
    uint16_t ADC_data;
} Mdb_data_AO_struct;

typedef struct {
    float value;
    float value_last;
    float valueRaw;
    float buf[PROGRAM_ADC_MAX_FILTER_ORDER];
    uint8_t bufIdx;
    uint8_t filter_N;
    float order;
}ADC_filter_typedef;

typedef struct 
{
    Mdb_data_AO_struct Mdb_data_AO;
    ADC_filter_typedef adc_filter;
} App_struct;
//----------------------------- STRUCT END -----------------------------//

//------------------------------ FUNCTION ------------------------------//
void app_main();
void app_init();
void app_tim7_10ms_start();
void app_tim7_10ms_callback();
// void app_parce_Mdb_AO();
void app_update_reg();
uint32_t get_data_spi();
void adc_data_filter(uint32_t ADC_Buf_raw);

void adc_filter_init();



//---------------------------- FUNCTION END ----------------------------//


#endif