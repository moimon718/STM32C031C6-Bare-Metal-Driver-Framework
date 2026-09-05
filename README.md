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

```text
Application
    │
    ├── GPIO Driver
    │     ├── GPIO Init
    │     ├── GPIO Read
    │     ├── GPIO Write
    │     └── GPIO Toggle
    │
    ├── SysTick Driver
    │     └── Millisecond Delay
    │
    ├── USART2 Driver
    │     ├── Transmit
    │     └── Receive
    │
    └── EXTI Driver
          ├── External Interrupt
          ├── Falling Edge Detection
          └── Button Debouncing
                │
                ▼
             PA5 LED
External Interrupt Flow
PC13 Button Press
       │
       ▼
Falling Edge Detected
       │
       ▼
EXTI Interrupt Callback
       │
       ▼
Set buttonEvent = true
       │
       ▼
Main Loop
       │
       ▼
Debounce + Confirm Press
       │
       ▼
Toggle PA5 LED
       │
       ▼
Wait for Button Release
USART2 Communication

USART2 is used for serial communication between the STM32C031C6 and the Wokwi Serial Monitor.

PC / Serial Monitor
        │
        │ TX
        ▼
      PA3
        │
     USART2
        │
        ▼
      PA2
        │
        │ RX
        ▼
PC / Serial Monitor

The project supports transmitting and receiving characters and implements a simple UART echo test.

Example:

Received: HELLO
Enter text:
Received: APPLE
Enter text:
Simulation

The project was developed and tested using Wokwi with the NUCLEO-C031C6 board.

Tested functionality:

PA5 LED output
PC13 button input
External interrupt
Button debouncing
SysTick millisecond delay
USART2 communication
Project Files
STM32C031C6-Bare-Metal-Driver-Framework/
│
├── sketch.ino
├── gpio.h
├── systick.h
├── usart.h
└── exti.h
Key Concepts Demonstrated
Memory-mapped peripheral registers
RCC peripheral clock control
GPIO register configuration
GPIO input/output operation
SysTick timer
UART communication
External interrupts
Interrupt-driven programming
volatile event flags
Software debouncing
Basic embedded driver architecture
Tools & Technologies
STM32C031C6
NUCLEO-C031C6
C/C++
STM32 Arduino Core
Wokwi
GitHub
Future Improvements
Refactor implementation into separate .c and .h driver files
Add SPI driver
Add I2C driver
Add ADC driver
Add Timer/PWM driver
Add DMA support
Add RTOS support
Author

Moimon Mandal
