#ifndef __BSP__H__
#define __BSP__H__

#include "main.h"


// ----------------------------- RS-485 -----------------------------

void bsp_rs485_setPortToModbusRtu(uint8_t portNo, uint8_t *bufRxTX, uint16_t bufSizeByte);

void bsp_rs485_sendBlock(uint8_t portNo, uint8_t *buf, uint8_t bufSizeByte);
void bsp_rs485_sendTestBlock(uint8_t portNo);

void bsp_rs485_callback_rxBlockReady(uint8_t portNo);
void bsp_rs485_callback_rxTimeout(uint8_t portNo);

#define BSP_RS485_1_IRQ_HANDLER_RTOF 			USART1_IRQHandler
#define BSP_RS485_1_IRQ_HANDLER_DMA_RX 			DMA1_Channel1_IRQHandler
#define BSP_RS485_1_IRQ_HANDLER_DMA_TX 			DMA1_Channel2_IRQHandler

// #define BSP_RS485_2_IRQ_HANDLER_RTOF 			USART3_IRQHandler
// #define BSP_RS485_2_IRQ_HANDLER_DMA_RX 			DMA1_Channel1_IRQHandler
// #define BSP_RS485_2_IRQ_HANDLER_DMA_TX 			DMA1_Channel2_IRQHandler

// ----------------------------- RS-485 END-----------------------------

#endif