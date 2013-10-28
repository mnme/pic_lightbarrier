#include "..\Include\PBA_config.h"

// local function prototypes



// init

void init_pba(void)
{
	// oscillator config
	OSCCON = 0xF3; // 8 MHz
	// input/output
 	//TRIS? = 0x;
	// clear outputs
	//PORT? = 0;
	// enable interupts
	PEIE = 1;
	GIE	= 1;
	// library inits
	lcd_init();
}
void putch(unsigned char c) 
{
	lcd_putc(c);
}