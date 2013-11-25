/******* PROJEKTNAME ************************************************************************
 *																							*
 * Autor:				Nicolas Jeker														*
 * Datum:				28.10.2013															*
 *																							*
 * Kurzbeschreibung:	Light barrier wth optional Display and (optional) external IR-LEDs,	*
 * 						-Receivers and Relay. 												*
 *																							*
 ********************************************************************************************/

#include "config\board_config.h"

//************************** Zustands-Datentyp generieren ***********************************

typedef enum {  } state;

//************************** Globale Variablen **********************************************

//************************** Funktions-Prototypen *******************************************

//************************** Unterprogramme *************************************************

//************************** Hauptprogramm **************************************************
int main(void)
{
	init();
	
	while(1)
	{
		loop_delay_ms(1);
		
		
	}
	
	return 0;
}