#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

/******************** Includes, clock definition *******************************************/
#include <xc.h>

#include <stdio.h>
#include <string.h>

//#include "..\utils\statemachine.h"
#include "..\utils\loopdelay.h"
#include "..\utils\helpers.h"
#include "..\driver\driver_lcd44780.h"

#define _XTAL_FREQ 8000000 // 8 MHz Int Osc
#pragma jis // Enable JIS character handling in strings (ä,ö,ü)

// config bits

#pragma config PWRTE=OFF, BODEN=OFF, WDT=OFF, LVP=OFF, CPD=OFF, DEBUG=OFF, FOSC=INTOSC, CP=OFF

// useful datatypes

typedef bit						INT1;
typedef bit						BOOL;
typedef bit						BOOLEAN;
typedef unsigned char 			UINT8;
typedef unsigned int 			UINT16;
typedef unsigned short long 	UINT24;
typedef unsigned long			UINT32;
typedef signed char 			SINT8;
typedef signed int 				SINT16;
typedef signed short long 		SINT24;
typedef signed long				SINT32;

// define I/Os TODO

#define	LED0 
#define	LED1 

#define	IR1	
#define	IR2	

#define IR_R1 
#define IR_R2 

#define RELAIS 


/******************** Prototypes for boardsupport libray-Functions **************************/
void init_pba(void);
void putch(char c);

#endif