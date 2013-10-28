/******* Loop-Delay-library for  PBA5 & other PIC-Hardware  *********************************
 *																							*
 * Titel: 			Board-Support-Library loop-delay for PIC16F877/877A						*
 * Compiler:		HI-TECH C Version 9.60PL4 and higher									*
 * Autor:			Remo Seiler, Ascom (Schweiz) AG, Berufsbildungscenter					*
 * Date:			02.06.2009															  	*
 * Last modified:	18.05.2011															  	*
 * Version:			6.0.4																  	*
 * History:			R.Seiler	02.06.2009: Release 1 for HI-TECH C-Compiler				*
 *					R.Seiler	10.05.2010:	Release 2 with selectable timer-module			*
 *					R.Seiler	11.05.2010: Cleanup & optimization							*
 *					R.Seiler	18.05.2011: Changes for new library structures				*
 *					S.Liechti	08.11.2011: Bugfixes										*
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