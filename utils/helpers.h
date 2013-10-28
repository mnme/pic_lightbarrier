#ifndef __helpers_H__
#define __helpers_H__		   

// global macros

#define bit_clear( reg, bitNumb )	((reg) &= ~(1 << (bitNumb)))
#define bit_set( reg, bitNumb )		((reg) |= (1 << (bitNumb)))
#define bit_toggle( reg, bitNumb )	((reg) ^= (1 << (bitNumb)))
#define bit_test( reg, bitNumb )	(((reg) & (1 << (bitNumb)))>0)
#define delay_us_f(x) __delay_us(x)
	
// global function prototypes
 
void delay_ms(unsigned int t);
void delay_us(unsigned int value);
unsigned int BinBCD_int8(unsigned char value);
unsigned char Mirror_Byte(unsigned char value);
unsigned char Bitsumme(unsigned char value);
unsigned char Bitnummer(unsigned char value);

#endif