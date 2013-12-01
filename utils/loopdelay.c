/******* Loop-Delay-library for  PBA5 & other PIC-Hardware  *********************************
 *																							*
 * Titel: 			Board-Support-Library loop-delay for PIC16F877/877A						*
 * Autor:			Remo Seiler, Ascom (Schweiz) AG, Berufsbildungscenter					*
 *																							*
 * Info:			Library for implementig a loop-delay in time-triggered systems			*
 *					like statemachines or small realtime operating systems.					*
 *					The used controller must have at least one onchip timer module.			*
 *																							*
 ********************************************************************************************/
 
#include "../config/board_config.h"

#define	TIMER0_RELOAD_VALUE (0xFF-(_XTAL_FREQ/32000UL))+1
#define reset_timer0() TMR0=(TIMER0_RELOAD_VALUE)

#define MAX_LOOP_DELAY_MS 10000
static volatile int loop_delay_value = 0;


void loop_delay_ms(int value)
{
    while(loop_delay_value < value);
    loop_delay_value = 0;
}

void loop_delay_init()
{
    T0IF 	= 0;
    T0IE	= 1;
    reset_timer0();
}
