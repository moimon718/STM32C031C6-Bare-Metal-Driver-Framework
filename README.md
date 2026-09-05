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
```
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

The RCC driver logic enables the required GPIO peripheral clocks before accessing the GPIO registers.

The project uses direct register access for peripheral clock configuration.

## SysTick

SysTick is configured as a basic timing source for generating millisecond delays.

The implementation provides a simple:

```c
delay_ms()
