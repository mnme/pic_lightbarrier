#include "board_config.h"

/**
 * Initialize oscillator, I/O's, enable Interrupts
 */
void init(void)
{
	// oscillator config
	OSCCON = 0x77; // 8 MHz
	// input/output
	TRISA = 0x0C;
	TRISB = 0x00;
	TRISC = 0x80;
	// clear outputs / enable pull-ups (latch)
	LATA = 0;
	LATB = 0x3F;
	LATC = 0;
	// enable interupts
	GIE = 1;
	PEIE = 1;
}

/**
 * printf => external LCD
 */
void putch(unsigned char c) 
{
	lcd_putc(c);
}