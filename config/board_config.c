#include "board_config.h"

/**
 * Initialize oscillator, I/O's, enable Interrupts
 */
void init(void)
{
	// oscillator config
	OSCCON = 0x74; // 8 MHz
	//PLLEN = 1; // enable PLL
	// input/output
	TRISA = 0x0C;
	TRISB = 0x00;
	TRISC = 0x80;
	// no analog pls
	ANCON0 = 0xFF;
	ANCON1 = 0x31;
	// clear output latch
	LATA = 0;
	LATB = 0x3F;
	LATC = 0;

	// 0, 0101 (postscaler 6), 0 (off), 01 (prescaler 4)
	T2CON = 0b00101001;
	TMR2 = 0;
	// timer 2 init (76kHz)
	PR2 = 26;
	TMR2IE = 1;
	TMR2ON = 1;
	TMR2IP = 1;
	// enable interupts
	PEIE = 1;
	GIE = 1;
}

/**
 * printf => external LCD
 */
void putch(unsigned char c) 
{
	lcd_putc(c);
}