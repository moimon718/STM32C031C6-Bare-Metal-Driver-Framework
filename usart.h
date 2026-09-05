#ifndef USART_H
#define USART_H

#include <Arduino.h>

#define USART_BAUDRATE_115200    115200U

#define USART_OK                 0U
#define USART_ERROR              1U

void USART2_Init(uint32_t baudrate);

void USART2_SendChar(char data);

void USART2_SendString(const char *string);

uint8_t USART2_ReceiveChar(char *data);

#endif