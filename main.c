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
		
		OUT_3 = !OUT_3;
		
		/*
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
		*/
		return;
	}
}

/**
 * Main Subroutine
 */
int main()
{
	init();
	
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