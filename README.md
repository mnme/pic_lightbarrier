PIC Lightbarrier
================

A Light Barrier with a PIC18F25J11 powered over Micro-USB. 

# Principle

The device counts the people who walk through the lightbarrier and with the help of the second lightbarrier also detects in which direction they went. 

Optional Features: 
- A night-mode (1 person in the room also turns off the ouput/relay), display the mode on the LCD.
- Show person count on the LCD

# Specs

## Overview

### External
- Connector for IR-Receiver, IR-LEDs, Relay (or something else with 5V input) and 3 additional free I/Os
- Connector for display (HD44780 compatible, contrast regulaton possible)

### On-board
- 1 microcontroller (PIC18F25J11)
- 2 IR-receiver (TSSOP3438) and IR-LEDs with associated drivers (PNP-MOSFET)
- 1 solid-state-relay (230V AC)
- 1 volatge regulator (5V to 3.3V)
- Micro-USB connector

## Microcontroller

The internal oscillator is configured with a freqency of 8 MHz (maximum without PLL). The reasons for using the internal oscilltor over an external are saving precious PCB space, saving money and the whole device isn't laid-out for high-speed applications. 



## TSSOP3438

The TSSOP3438 detects IR light with 38 kHz frequency. 

## Relay (and gneral output)

The output is high as soon as someone is in the room. Additionally there is also an onboard solid-state-relay to toggle up to 230 V AC. 