/******* pic_lightbarrier *******************************************************************
 *																							*
 * Autor:				Nicolas Jeker														*
 * Datum:				28.10.2013															*
 *																							*
 * Kurzbeschreibung:	Light barrier wth optional Display and (optional) external IR-LEDs,	*
 * 						-Receivers and Relay. 												*
 *																							*
 ********************************************************************************************/

#include "config/board_config.h"

char burst = 0;
char antiburst = 0;

/**
 * Interrupt Service Routine (High Priority)
 */
void interrupt isr()
{
	if (TMR2IF && TMR2IE)
	{
		TMR2IF = 0;
		if (burst)
		{
			IR2 = !IR2;
		}
		antiburst++;
		if ((burst && (antiburst == 30)) || (!burst && (antiburst == 1000)))
		{
			IR2 = 0;
			antiburst = 0;
			burst = !burst;
		}
		return;
	}
}

/**
 * Main Subroutine
 */
int main()
{
	// oscillator config
	OSCCON = 0x74; // 8 MHz
	PLLEN = 1; // enable PLL
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
	T2CON = 0x00;
	TMR2 = 0;
	// timer 2 init (76kHz)
	PR2 = 26;
	// TMR2IE = 1;
	TMR2ON = 1;
	TMR2IP = 1;
	// enable interupts
	PEIE = 1;
	GIE = 1;
	
	RELAIS = 1;
	
	while (1)
	{
		for (int i = 0; i < 10; i++)
		{
			__delay_us(13);
			IR2 = 1;
			__delay_us(13);
			IR2 = 0;
			LED0_G = IR_R2;
		}
		for (int i=0; i < 1000; i++)
		{
			__delay_us(10);
			LED0_G = IR_R2;
		}
	}

	return 0;
}