#ifndef __APP__H__
#define __APP__H__

#include "main.h"

//------------------------------- STRUCT -------------------------------//

#define PROGRAM_ADC_MAX_FILTER_ORDER         (24)
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
void app_update_reg();
void adc_data_filter(uint32_t ADC_Buf_raw);
void adc_filter_init();

//---------------------------- FUNCTION END ----------------------------//


#endif