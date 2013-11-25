#include "..\Include\PBA_config.h"

// local function prototypes



// init

void init(void)
{
	// oscillator config
	OSCCON = 0xF3; // 8 MHz
	// input/output
 	TRISA = 0x0C;
 	TRISB = 0x00;
 	TRISC = 0x80;
	// clear outputs
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	// enable interupts
	PEIE = 1;
	GIE	= 1;
	// timer 2 init (38kHz)
	T2CON = 0b00010110;
	PR2 = 234;
	// library inits
	lcd_init();
}

void putch(unsigned char c) 
{
	lcd_putc(c);
}