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
 
#include "..\config\board_config.h"

#if !defined(__USE_TIMER0) && !defined(__USE_TIMER1) && !defined(__USE_TIMER2)
	#error please specify the timer-modul for loop-delay in the file loopdelay.h
#endif

#if defined(__USE_TIMER0)
	#if _XTAL_FREQ <= 8000000
		#define	TIMER0_RELOAD_VALUE	(0xFF-(_XTAL_FREQ/32000UL))+1
		#define reset_timer0()	TMR0=(TIMER0_RELOAD_VALUE)
	#else
		#error _XTAL_FREQ value to big for loop-delay, use another timer-modul or smaller frequency
	#endif
#endif
#if defined(__USE_TIMER1)
	#if _XTAL_FREQ >= 1000000
		#define	TIMER1_RELOAD_VALUE	(0xFFFF-(_XTAL_FREQ/32000UL))+1
		#define reset_timer1()	TMR1H=(TIMER1_RELOAD_VALUE)>>8; TMR1L=(TIMER1_RELOAD_VALUE) 
	#else
		#error _XTAL_FREQ value to small for loop-delay, use another timer-modul or bigger frequency
	#endif
#endif
#if defined(__USE_TIMER2)
	#if _XTAL_FREQ >= 2000000
		#define	TIMER2_PERIODE	((_XTAL_FREQ/80000UL))-1
	#else
		#error _XTAL_FREQ value to small for loop-delay, use another timer-modul or bigger frequency
	#endif	
#endif

#define MAX_LOOP_DELAY_MS	10000
static volatile int loop_delay_value = 0;

void interrupt loop_delay_timer_interrupt(void)
{
#if defined(__USE_TIMER0)
	if(T0IF && T0IE)
	{
		//Timer neu laden um genau 1kHz Interruptfrequenz zu erreichen
		reset_timer0();
		//Interrupt-Flag Timer 0 löschen
		T0IF=0;
		//Loop-Delay-Zähler inkrementieren (x1ms)
		if(loop_delay_value<MAX_LOOP_DELAY_MS)
			loop_delay_value++;
	}
#endif

#if defined(__USE_TIMER1)
	if(TMR1IF && TMR1IE)
	{
		//Timer neu laden um genau 1kHz Interruptfrequenz zu erreichen
		reset_timer1();
		//Interrupt-Flag Timer 1 löschen
		TMR1IF=0;
		//Loop-Delay-Zähler inkrementieren (x1ms)
		if(loop_delay_value<MAX_LOOP_DELAY_MS)
			loop_delay_value++;
	}
#endif

#if defined(__USE_TIMER2)
	if(TMR2IF && TMR2IE)
	{
		//Interrupt-Flag Timer 0 löschen
		TMR2IF=0;
		//Loop-Delay-Zähler inkrementieren (x1ms)
		if(loop_delay_value<MAX_LOOP_DELAY_MS)
			loop_delay_value++;
	}
#endif
}

void loop_delay_ms(int value)
{
	while(loop_delay_value < value);
	loop_delay_value = 0;
}

void loop_delay_init(void)
{
#if defined(__USE_TIMER0)
	OPTION &= 0xC0;								//TIMER0-Bits im OPTION-Register löschen
	OPTION |= 0b00000010;						//TIMER0 einstellen (OPTION-Register) (Prescaler = 8)
	reset_timer0();
	T0IF 	= 0;								//Timer0-Interrupt-Flag löschen
	T0IE	= 1;								//Timer0-Interrupt einschalten
#endif
#if defined(__USE_TIMER1)
	T1CON 	= 0b00110001;						//Prescaler = 8, Timer on
	reset_timer1();
	TMR1IF 	= 0;								//Timer1-Interrupt-Flag löschen
	TMR1IE	= 1;								//Timer1-Interrupt einschalten
#endif
#if defined(__USE_TIMER2)
	T2CON 	= 0b00100101;						//Prescaler = 4, Timer on, Postscaler = 5
	PR2	  	= TIMER2_PERIODE;					//Timer2 Periode festlegen
	TMR2	= 0;								//Timer2-Register löschen
	TMR2IF 	= 0;								//Timer2-Interrupt-Flag löschen
	TMR2IE	= 1;								//Timer2-Interrupt einschalten
#endif
}
