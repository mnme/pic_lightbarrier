#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

// Includes, clock definition

#include <xc.h>

#include <stdio.h>
#include <string.h>

//#include "../utils/loopdelay.h"
#include "../utils/helpers.h"
#include "../driver/driver_lcd44780.h"
#include "../driver/ir_led.h"

#define _XTAL_FREQ 8000000 // 8 MHz Int Osc
#pragma jis // Enable JIS character handling in strings (ä,ö,ü)

// PIC18F25J11 Configuration Bit Settings

// CONFIG1L
#pragma config WDTEN = OFF      // Watchdog Timer (Disabled - Controlled by SWDTEN bit)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset (Disabled)
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config CP0 = OFF        // Code Protect (Program memory is not code-protected)

// CONFIG2L
#pragma config OSC = INTOSCPLL  // Oscillator (INTOSCPLL)
#pragma config T1DIG = OFF      // T1OSCEN Enforcement (Secondary Oscillator clock source may not be selected)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator (High-power operation)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2H
#pragma config WDTPS = 32768    // Watchdog Postscaler (1:32768)

// CONFIG3L
#pragma config DSWDTOSC = INTOSCREF// DSWDT Clock Select (DSWDT uses INTRC)
#pragma config RTCOSC = INTOSCREF// RTCC Clock Select (RTCC uses INTRC)
#pragma config DSBOREN = OFF    // Deep Sleep BOR (Disabled)
#pragma config DSWDTEN = OFF    // Deep Sleep Watchdog Timer (Disabled)
#pragma config DSWDTPS = G2     // Deep Sleep Watchdog Postscaler (1:2,147,483,648 (25.7 days))

// CONFIG3H
#pragma config IOL1WAY = OFF    // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set and cleared as needed)
#pragma config MSSP7B_EN = MSK7 // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_31   // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 31)
#pragma config WPEND = PAGE_WPFP// Write/Erase Protect Region Select (valid when WPDIS = 0) (Page WPFP<5:0> through Configuration Words erase/write protected)
#pragma config WPCFG = OFF      // Write/Erase Protect Configuration Region (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF      // Write Protect Disable bit (WPFP<5:0>/WPEND region ignored)

// Useful datatypes

typedef unsigned char 		UINT8;
typedef unsigned int 		UINT16;
typedef unsigned short long 	UINT24;
typedef unsigned long		UINT32;
typedef signed char 		SINT8;
typedef signed int              SINT16;
typedef signed short long 	SINT24;
typedef signed long             SINT32;

// Global defines

#define TMR0_PRELOAD 196

// Define I/Os

#define	LED0_R LATB1
#define	LED0_G LATB2
#define	LED0_B LATB0
#define	LED1_R LATB4
#define	LED1_G LATB5
#define	LED1_B LATB3

#define	IR1 LATA0
#define	IR2 LATA1

#define IR_R1 RA2
#define IR_R2 RA3

#define RELAIS LATA5

#define OUT_1 LATA7
#define OUT_2 LATA6
#define OUT_3 LATC7

// Function Prototypes

void init(void);
void putch(char c);

#endif /* BOARD_CONFIG_H */