#include <Arduino.h>
#include "gpio.h"
#include "systick.h"
#include "exti.h"


/* =========================================================
 * GLOBAL GPIO HANDLES
 * ========================================================= */

GPIO_Handle_t led;
GPIO_Handle_t button;


/* =========================================================
 * BUTTON EVENT FLAG
 * ========================================================= */

volatile bool buttonEvent = false;


/* =========================================================
 * RCC GPIO CLOCK CONTROL
 * ========================================================= */

void GPIO_PeriClockControl(GPIO_TypeDef *pGPIOx,
                           uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        /* GPIOA */

        if (pGPIOx == GPIOA)
        {
            RCC->IOPENR |= (1U << 0);
        }

        /* GPIOB */

        else if (pGPIOx == GPIOB)
        {
            RCC->IOPENR |= (1U << 1);
        }

        /* GPIOC */

        else if (pGPIOx == GPIOC)
        {
            RCC->IOPENR |= (1U << 2);
        }
    }
    else
    {
        /* GPIOA */

        if (pGPIOx == GPIOA)
        {
            RCC->IOPENR &= ~(1U << 0);
        }

        /* GPIOB */

        else if (pGPIOx == GPIOB)
        {
            RCC->IOPENR &= ~(1U << 1);
        }

        /* GPIOC */

        else if (pGPIOx == GPIOC)
        {
            RCC->IOPENR &= ~(1U << 2);
        }
    }
}


/* =========================================================
 * GPIO INITIALIZATION
 * ========================================================= */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint8_t pin;

    pin =
        pGPIOHandle->GPIO_Config.GPIO_PinNumber;


    /* Enable GPIO peripheral clock */

    GPIO_PeriClockControl(
        pGPIOHandle->pGPIOx,
        ENABLE
    );


    /* -----------------------------------------------------
     * GPIO MODE
     * ----------------------------------------------------- */

    pGPIOHandle->pGPIOx->MODER &=
        ~(3U << (2U * pin));

    pGPIOHandle->pGPIOx->MODER |=
        ((uint32_t)
        pGPIOHandle->GPIO_Config.GPIO_PinMode
        << (2U * pin));


    /* -----------------------------------------------------
     * OUTPUT TYPE
     * ----------------------------------------------------- */

    pGPIOHandle->pGPIOx->OTYPER &=
        ~(1U << pin);

    pGPIOHandle->pGPIOx->OTYPER |=
        ((uint32_t)
        pGPIOHandle->GPIO_Config.GPIO_PinOPType
        << pin);


    /* -----------------------------------------------------
     * PULL-UP / PULL-DOWN
     * ----------------------------------------------------- */

    pGPIOHandle->pGPIOx->PUPDR &=
        ~(3U << (2U * pin));

    pGPIOHandle->pGPIOx->PUPDR |=
        ((uint32_t)
        pGPIOHandle->GPIO_Config.GPIO_PinPuPdControl
        << (2U * pin));
}


/* =========================================================
 * GPIO WRITE
 * ========================================================= */

void GPIO_WritePin(GPIO_TypeDef *pGPIOx,
                   uint8_t PinNumber,
                   uint8_t Value)
{
    if (Value)
    {
        /* Set HIGH */

        pGPIOx->BSRR =
            (1U << PinNumber);
    }
    else
    {
        /* Set LOW */

        pGPIOx->BSRR =
            (1U << (PinNumber + 16U));
    }
}


/* =========================================================
 * GPIO READ
 * ========================================================= */

uint8_t GPIO_ReadPin(GPIO_TypeDef *pGPIOx,
                     uint8_t PinNumber)
{
    return (uint8_t)
           ((pGPIOx->IDR >> PinNumber) & 0x01U);
}


/* =========================================================
 * GPIO TOGGLE
 * ========================================================= */

void GPIO_TogglePin(GPIO_TypeDef *pGPIOx,
                    uint8_t PinNumber)
{
    pGPIOx->ODR ^=
        (1U << PinNumber);
}


/* =========================================================
 * SYSTICK INITIALIZATION
 * ========================================================= */

void SysTick_Init(void)
{
    /* Disable SysTick */

    SysTick->CTRL = 0;


    /*
     * 48 MHz CPU clock
     *
     * 1 ms:
     *
     * 48,000,000 / 1000 - 1
     *
     * = 47,999
     */

    SysTick->LOAD = 47999;


    /* Clear current counter */

    SysTick->VAL = 0;


    /*
     * CTRL:
     *
     * Bit 2 = CLKSOURCE
     * Bit 0 = ENABLE
     */

    SysTick->CTRL =
        (1U << 2) |
        (1U << 0);
}


/* =========================================================
 * DELAY MILLISECONDS
 * ========================================================= */

void delay_ms(uint32_t delay)
{
    uint32_t i;

    for (i = 0; i < delay; i++)
    {
        /*
         * COUNTFLAG = bit 16
         */

        while ((SysTick->CTRL & (1U << 16)) == 0)
        {
        }
    }
}


/* =========================================================
 * EXTI CALLBACK
 * ========================================================= */

void EXTI_PC13_Callback(void)
{
    /*
     * Keep interrupt callback short.
     *
     * Only record the button event.
     */

    buttonEvent = true;
}


/* =========================================================
 * EXTI PC13 INITIALIZATION
 * ========================================================= */

void EXTI_PC13_Init(void)
{
    /*
     * PC13:
     *
     * Released = HIGH
     * Pressed  = LOW
     *
     * Therefore use FALLING edge.
     *
     * Wokwi STM32 Arduino core handles the
     * EXTI4_15 interrupt vector internally.
     */

    attachInterrupt(
        digitalPinToInterrupt(PC13),
        EXTI_PC13_Callback,
        FALLING
    );
}


/* =========================================================
 * SETUP
 * ========================================================= */

void setup()
{
    /* =====================================================
     * INITIALIZE SYSTICK
     * ===================================================== */

    SysTick_Init();


    /* =====================================================
     * LED CONFIGURATION
     *
     * PA5 -> LD4
     * ===================================================== */

    led.pGPIOx =
        GPIOA;

    led.GPIO_Config.GPIO_PinNumber =
        GPIO_PIN_5;

    led.GPIO_Config.GPIO_PinMode =
        GPIO_MODE_OUTPUT;

    led.GPIO_Config.GPIO_PinSpeed =
        GPIO_SPEED_LOW;

    led.GPIO_Config.GPIO_PinPuPdControl =
        GPIO_NO_PUPD;

    led.GPIO_Config.GPIO_PinOPType =
        GPIO_OUTPUT_PP;


    /* Initialize LED */

    GPIO_Init(&led);


    /* Start with LED OFF */

    GPIO_WritePin(
        GPIOA,
        GPIO_PIN_5,
        0
    );


    /* =====================================================
     * BUTTON CONFIGURATION
     *
     * PC13
     *
     * Active LOW
     * ===================================================== */

    button.pGPIOx =
        GPIOC;

    button.GPIO_Config.GPIO_PinNumber =
        GPIO_PIN_13;

    button.GPIO_Config.GPIO_PinMode =
        GPIO_MODE_INPUT;

    button.GPIO_Config.GPIO_PinSpeed =
        GPIO_SPEED_LOW;

    button.GPIO_Config.GPIO_PinPuPdControl =
        GPIO_PULLUP;

    button.GPIO_Config.GPIO_PinOPType =
        GPIO_OUTPUT_PP;


    /* Initialize button */

    GPIO_Init(&button);


    /* =====================================================
     * INITIALIZE EXTI
     * ===================================================== */

    EXTI_PC13_Init();
}


/* =========================================================
 * MAIN LOOP
 * ========================================================= */

void loop()
{
    /*
     * Check for button interrupt event.
     */

    if (buttonEvent)
    {
        /*
         * Debounce.
         */

        delay_ms(30);


        /*
         * Confirm button is still pressed.
         *
         * PC13 LOW = pressed.
         */

        if (GPIO_ReadPin(
                GPIOC,
                GPIO_PIN_13
            ) == 0)
        {
            /*
             * Toggle LD4 once.
             */

            GPIO_TogglePin(
                GPIOA,
                GPIO_PIN_5
            );


            /*
             * Wait for physical release.
             *
             * This prevents multiple toggles
             * from one press.
             */

            while (GPIO_ReadPin(
                       GPIOC,
                       GPIO_PIN_13
                   ) == 0)
            {
                delay_ms(5);
            }


            /*
             * Release debounce.
             */

            delay_ms(30);
        }


        /*
         * Clear event.
         */

        buttonEvent = false;
    }


    delay_ms(5);
}