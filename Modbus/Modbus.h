#ifndef __MODBUS__H__
#define __MODBUS__H__

//#include "stm32g4xx_hal.h"
#include "usart.h"

// Modbus init
#define ID_DEV 1 
#define ADR_MAX_AI 25
#define ADR_MAX_AO 25

#define UART_MODBUS huart1
// #define UART_DIR_PORT UART5_DIR_GPIO_Port
// #define UART_DIR_PIN UART5_DIR_Pin

#define Num_Data_buf 100

// Для работы библиотеки модбас
extern unsigned short *DATA_AO[ADR_MAX_AO];
extern unsigned short *DATA_AI[ADR_MAX_AI];
extern unsigned short BUF_DATA_AO[ADR_MAX_AO];
extern unsigned short BUF_DATA_AI[ADR_MAX_AI];
extern unsigned short MODBUS_FAULT;
extern uint16_t ID_Device;

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void ModbusRTU_Init();
void ModbusRTU_Deinit();
void ModbusRTU_Handler();
void ModbusRTU_Transmit();
void ModbusRTU_Receive();
void ModbusRTU_UART_Init();
void ModbusRTU_Init_AO();
void ModbusRTU_Init_AI();
void ModbusRTU_Data_In();
void ModbusRTU_Data_Out();
unsigned short ModbusRTU_Conv_Out_us(float in_x, float in_Min, float in_Max, float out_Min, float out_Max);
float ModbusRTU_Conv_Out_f(unsigned short in_x, float in_Min, float in_Max, float out_Min, float out_Max);
unsigned short CRC16(unsigned char * pcBlock, unsigned short len);

#endif

/*
// использовать в нужном месте
void ModbusRTU_Data_Out(){
//согласование принимаемых переменных
float var = ModbusRTU_Conv_Out_f(in_var, float in_Min, float in_Max, float out_Min, float out_Max)
}

// использовать в нужном месте
void ModbusRTU_Data_In(){
//согласование отправляемых переменных
unsigned short var = ModbusRTU_Conv_Out_us(in_var, float in_Min, float in_Max, float out_Min, float out_Max)
}
*/

/*
 UART_ERR = 1   =>   HAL_UART_ERROR_PE — ошибка контроля чётности.
 UART_ERR = 2   =>   HAL_UART_ERROR_NE — шум в линии.
 UART_ERR = 4   =>   HAL_UART_ERROR_FE — ошибка кадра. У передающего устройства «плавает» частота.
 UART_ERR = 8   =>   HAL_UART_ERROR_ORE — ошибка переполнения.
 Возникает когда в USART приходит новый байт, а предыдущий ещё не был считан из
 приёмного регистра — Data Register (DR). Это происходит из-за того,
 что прерывание обрабатывается слишком медленно и программа
 не успевает очистить приёмный регистр.
 */