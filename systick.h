#ifndef SYSTICK_H
#define SYSTICK_H

#include <Arduino.h>


/* =========================================================
 * SysTick Driver
 * ========================================================= */

void SysTick_Init(void);

void delay_ms(uint32_t delay);


#endif