/******* Loop-Delay-library for  PBA5 & other PIC-Hardware  *********************************
 *																							*
 * Titel: 			Board-Support-Library loop-delay for PIC16F877/877A						*
 * Autor:			Remo Seiler, Ascom (Schweiz) AG, Berufsbildungscenter					*
 *																							*
 * Info:			Library fior implementig a loop-delay in time-triggered systems			*
 *					like statemachines or small realtime operating systems.					*
 *					The used controller must have at least one onchip timer module.			*
 *																							*
 ********************************************************************************************/
 
#ifndef __loopdelay_H__
#define __loopdelay_H__

/***** Define wich timer you want to use (uncomment the appropriate #define) *****/
//#define	__USE_TIMER0
//#define	__USE_TIMER1
#define	__USE_TIMER2

void loop_delay_ms(int value);
void loop_delay_init(void);

#endif