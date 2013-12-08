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

char burst, received = 0;
int antiburst, flag = 0;

/**
 * Interrupt Service Routine (High Priority)
 */
void interrupt isr()
{
	if (TMR0IF && TMR0IE)
	{
		TMR0IF = 0; // reset interrupt flag
		TMR0 = TMR0_PRELOAD; // generates 38 kHz burst
		
		if (burst)
		{
			IR2 = !IR2;
		}
		antiburst++; // counter
		// after 10 pulses
		if (burst && (antiburst == 20))
		{
			IR2 = 0; // just to be sure
			antiburst = 0; // reset counter
			burst = 0; // disable burst mode
			received = !IR_R2;
		}
		// it's time for the next burst
		if (!burst && (antiburst == 1000))
		{
			antiburst = 0; // reset counter
			burst = 1; // enable next burst
		}
		return; // get me out of here!
	}
}

/**
 * Main Subroutine
 */
int main()
{
	init();

	LED0_R = 0; // Power-LED (inverted!)
	
	while (1)
	{
		// pseudo-loopdelay
		for (int i = 0; i < 10000; ++i)
		{
			__delay_us(1);
			if (received)
			{
				flag++;
			}
		}
		if (flag >= 10)
		{
			LED1_B = 1;
		} else {
			LED1_B = 0;
		}
		flag = 0;
	}

	return 0;
}