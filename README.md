# pic16f877a-temperature-fan-control
Fan speed control based on temperature using PIC16F877A and LM35 (CCS C)
# Temperature-Based Fan Speed Control using PIC16F877A (CCS C)

This is a small embedded project using a **PIC16F877A** microcontroller and **CCS C** compiler to control the speed of a DC fan based on temperature.  
The system reads temperature from an **LM35 sensor**, displays it on a **16x2 LCD**, and adjusts fan speed using **PWM**. A **PIR sensor** is used to detect human presence and stop the fan when no one is detected.

## Features

- Measure ambient temperature using **LM35** connected to the ADC input.
- Display temperature (in °C) on a **16x2 character LCD**.
- Control DC fan speed using **PWM (CCP1 + Timer2)**:
  - Fan OFF when temperature is below 30 °C.
  - Low speed when 30–35 °C.
  - Medium speed when 35–40 °C.
  - High speed when above 40 °C.
- Use a **PIR sensor** to detect presence:
  - If no person is detected, the fan is stopped and a message is shown on the LCD. :contentReference[oaicite:0]{index=0}

## Hardware

- Microcontroller: **PIC16F877A** (20 MHz external crystal)
- Temperature sensor: **LM35**
- PIR motion sensor
- 16x2 character LCD (4-bit mode)
- DC fan (controlled via PWM and a transistor/MOSFET driver stage)
- Power supply 
- Miscellaneous: resistors, wires, breadboard or PCB

## Software & Tools

- **Compiler**: CCS C for PIC (`#include <16F877A.h>`)  
- Clock: 20 MHz (`#use delay(clock=20M)`)
- LCD library: `lcd.c` (standard CCS LCD driver)
- IDE: MPLAB X IDE or CCS IDE (depending on your setup)
- Programmer: PICkit or compatible programmer for PIC16F877A

## Code Overview

Main source file: `temp_fan_control.c`

Key points:
- ADC is configured with 10-bit resolution and channel AN0 is used to read LM35.
- Temperature is computed from the ADC reading and averaged over multiple samples for noise reduction.
- LCD shows the current temperature on the first line.
- PWM is generated on CCP1 using Timer2 and the duty cycle is adjusted according to the temperature range.
- A PIR sensor input is used to decide whether to run the fan or stop it and show "no person" on the LCD.

PWM levels (example from the code):

- `< 30 °C`  → duty = 0 (fan stopped)  
- `30–35 °C` → duty ≈ 400 (low speed)  
- `35–40 °C` → duty ≈ 700 (medium speed)  
- `> 40 °C`  → duty ≈ 1000 (high speed)

## How It Works (High-Level)

1. Initialize:
   - Configure I/O directions.
   - Initialize LCD.
   - Configure ADC for LM35.
   - Configure Timer2 and CCP1 for PWM.

2. In the main loop:
   - Read temperature from LM35 using the ADC.
   - Display the temperature on the first line of the LCD.
   - Check the PIR sensor:
     - If no person is detected, stop the fan and display a message.
     - If a person is detected, set the PWM duty cycle based on the current temperature and display the fan status (OFF / Level 1 / Level 2 / Level 3).

│  ├─ lcd_wiring.png       # optional
├─ README.md
