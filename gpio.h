#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>
#include "rcc.h"


/* =========================================================
 * GPIO PIN NUMBERS
 * ========================================================= */

#define GPIO_PIN_0      0
#define GPIO_PIN_1      1
#define GPIO_PIN_2      2
#define GPIO_PIN_3      3
#define GPIO_PIN_4      4
#define GPIO_PIN_5      5
#define GPIO_PIN_6      6
#define GPIO_PIN_7      7
#define GPIO_PIN_8      8
#define GPIO_PIN_9      9
#define GPIO_PIN_10     10
#define GPIO_PIN_11     11
#define GPIO_PIN_12     12
#define GPIO_PIN_13     13
#define GPIO_PIN_14     14
#define GPIO_PIN_15     15


/* =========================================================
 * GPIO MODES
 * ========================================================= */

#define GPIO_MODE_INPUT      0
#define GPIO_MODE_OUTPUT     1
#define GPIO_MODE_AF         2
#define GPIO_MODE_ANALOG     3


/* =========================================================
 * GPIO OUTPUT TYPE
 * ========================================================= */

#define GPIO_OUTPUT_PP       0
#define GPIO_OUTPUT_OD       1


/* =========================================================
 * GPIO PULL-UP / PULL-DOWN
 * ========================================================= */

#define GPIO_NO_PUPD         0
#define GPIO_PULLUP          1
#define GPIO_PULLDOWN        2


/* =========================================================
 * GPIO SPEED
 * ========================================================= */

#define GPIO_SPEED_LOW       0
#define GPIO_SPEED_MEDIUM    1
#define GPIO_SPEED_HIGH      2
#define GPIO_SPEED_VERY_HIGH 3


/* =========================================================
 * GPIO CONFIGURATION
 * ========================================================= */

typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPuPdControl;
    uint8_t GPIO_PinOPType;

} GPIO_Config_t;


/* =========================================================
 * GPIO HANDLE
 * ========================================================= */

typedef struct
{
    GPIO_TypeDef *pGPIOx;

    GPIO_Config_t GPIO_Config;

} GPIO_Handle_t;


/* =========================================================
 * GPIO APIs
 * ========================================================= */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

void GPIO_WritePin(GPIO_TypeDef *pGPIOx,
                   uint8_t PinNumber,
                   uint8_t Value);

void GPIO_TogglePin(GPIO_TypeDef *pGPIOx,
                    uint8_t PinNumber);
                    
 uint8_t GPIO_ReadPin(GPIO_TypeDef *pGPIOx,
                     uint8_t PinNumber);
void GPIO_SetAlternateFunction(GPIO_TypeDef *pGPIOx,
                              uint8_t PinNumber,
                              uint8_t AlternateFunction);
            
#endif