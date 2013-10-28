/******* PROJEKTNAME ************************************************************************
 *																							*
 * Autor:				Nicolas Jeker														*
 * Datum:				20.06.2013															*
 * Nummer:				4976																*
 *																							*
 * Kurzbeschreibung:	Funktion															*
 *																							*
 ********************************************************************************************/

#include "..\Include\PBA_config.h"

//************************** Zustands-Datentyp generieren ***********************************
typedef enum {S_Zustand_1, S_Zustand_2, S_Zustand_3} TState;
TState state = S_Zustand_1;

//************************** Globale Variablen **********************************************

//************************** Funktions-Prototypen *******************************************

//************************** Unterprogramme *************************************************

//************************** Hauptprogramm **************************************************
int main(void)
{
	init_pba();
	state_machine_init(&state);
	
	while(1)
	{
		loop_delay_ms(10);
		get_events();
		switch(state)
		{
			
		}
	}
	
	return 0;
}