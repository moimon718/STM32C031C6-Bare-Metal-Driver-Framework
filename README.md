# STM32C031C6 Bare-Metal Driver Framework

A register-level embedded systems project developed for the STM32C031C6 microcontroller using the NUCLEO-C031C6 board and Wokwi simulation.

## Project Overview

This project implements a simple bare-metal-style driver framework for the STM32C031C6. The goal is to understand microcontroller peripherals through direct register configuration rather than relying entirely on high-level APIs.

The project covers GPIO, RCC clock control, SysTick timing, USART2 communication, external interrupts, and software button debouncing.

## Features

- Register-level GPIO configuration
- RCC peripheral clock control
- GPIO input/output handling
- LED control using PA5
- Push-button input using PC13
- SysTick-based millisecond delay
- USART2 transmit and receive
- UART echo functionality
- External interrupt handling
- Falling-edge interrupt detection
- Software button debouncing
- Wokwi-based STM32 simulation

## Hardware

| Component | Pin | Function |
|---|---|---|
| User LED (LD4) | PA5 | GPIO output |
| User Button (B1) | PC13 | GPIO input / interrupt |
| USART2 TX | PA2 | Serial receive from PC |
| USART2 RX | PA3 | Serial transmit to PC |

## Software Architecture

**Application**

→ **GPIO Driver**
- GPIO Initialization
- GPIO Read
- GPIO Write
- GPIO Toggle

→ **RCC Clock Control**
- Peripheral Clock Enable

→ **SysTick Driver**
- Millisecond Delay

→ **USART2 Driver**
- Transmit
- Receive
- UART Echo

→ **EXTI Driver**
- External Interrupt
- Falling Edge Detection
- Button Debouncing

→ **PA5 LED**

## GPIO

The GPIO driver configures STM32 GPIO registers directly.

### Implemented Operations

- GPIO peripheral clock enable
- GPIO input/output mode configuration
- Push-pull output configuration
- Pull-up configuration
- Digital input reading
- Digital output writing
- GPIO output toggling

## RCC Clock Control

The RCC logic enables the required peripheral clocks before accessing the GPIO registers.

The project uses direct register access for peripheral clock configuration.

## SysTick

SysTick is configured as a basic timing source for generating millisecond delays.

The implementation provides a simple `delay_ms()` function used for timing and software button debouncing.

## USART2

USART2 is configured for serial communication between the STM32C031C6 and the Wokwi Serial Monitor.

### Implemented Operations

- USART2 initialization
- Character transmission
- Character reception
- UART echo

### Example

Received: HELLO

Enter text:

Received: APPLE

Enter text:

## External Interrupt

The PC13 button is configured to generate an interrupt on a falling edge.

The interrupt callback sets an event flag, while the main application handles the actual button processing.

This keeps interrupt processing short and allows the main loop to handle debouncing.

## Button Debouncing

Mechanical push buttons can produce multiple rapid electrical transitions during a single press.

Software debouncing is implemented to ensure that one physical button press results in one LED toggle.

### Debouncing Sequence

1. Detect button interrupt.
2. Set the button event flag.
3. Wait for a short debounce period.
4. Confirm that the button is still pressed.
5. Toggle the PA5 LED.
6. Wait for button release.
7. Clear the event flag.

## Interrupt Flow

**PC13 Button**

↓

**Falling Edge**

↓

**EXTI Interrupt Callback**

↓

**buttonEvent = true**

↓

**Main Loop**

↓

**Debounce**

↓

**Toggle PA5 LED**

## Simulation

The project was developed and tested using Wokwi with the NUCLEO-C031C6 board.

### Tested Functionality

- GPIO LED control
- GPIO button input
- External interrupt
- Falling-edge detection
- Button debouncing
- SysTick millisecond delay
- USART2 communication
- UART echo

## Project Structure

STM32C031C6-Bare-Metal-Driver-Framework/

├── sketch.ino  
├── gpio.h  
├── systick.h  
├── usart.h  
└── exti.h

## Key Concepts Demonstrated

- Memory-mapped peripheral registers
- RCC peripheral clock control
- GPIO register configuration
- GPIO input/output operation
- SysTick timer
- UART communication
- External interrupts
- Interrupt-driven programming
- `volatile` event flags
- Software button debouncing
- Embedded driver architecture

## Tools and Technologies

- STM32C031C6
- NUCLEO-C031C6
- C/C++
- STM32 Arduino Core
- Wokwi
- GitHub

## Future Improvements

- Refactor implementation into separate `.c` and `.h` driver files
- Add SPI driver
- Add I2C driver
- Add ADC driver
- Add Timer/PWM driver
- Add DMA support
- Add RTOS support

## Author

**Moimon Mandal**

Embedded Systems / Electronics Engineering
