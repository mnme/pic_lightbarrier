#include "../config/board_config.h"
							   
void delay_ms(unsigned int t)											//Workaround f�r gr�ssere Delays bei 20MHz Systemtakt
{
	for(;t>=35;t-=35)
		__delay_ms(35);
	for(;t>=1;t--)
		__delay_ms(1);	
}

void delay_us(unsigned int value)										//Workaround f�r gr�ssere Delays bei 20MHz Systemtakt
{
	for(;value>=100;value-=100)
		__delay_us(100);
	for(;value>=10;value-=10)
		__delay_us(10);	
}

unsigned int BinBCD_int8(unsigned char value)							//Umwandlung Bin�r zu BCD
{
	unsigned char ei,ze;												//dekl. Lokale Variabeln
	unsigned int hu;	                								//dekl. Lokale Variabeln
	hu=value/100;		 												//Hunderter definieren
	ze=(value-=hu*100)/10;             									//Zehner definieren
	ei=value-ze*10;														//Einer definieren
	hu<<=8;
	ze<<=4;
	return hu|ze|ei;
}

unsigned char Mirror_Byte(unsigned char value)
{
	unsigned char i,rw;
	for(i=rw=0;i<=7;i++)
		if(bit_test(value,i))
			bit_set(rw,7-i);
	return rw;
}

unsigned char Bitsumme(unsigned char value)
{
	unsigned char i,result;
	for(i=result=0;i<=7;i++)
		result+=bit_test(value,i);
	return result;
}

unsigned char Bitnummer(unsigned char value)
{
	unsigned char i,result;
	result=0xFF;
	for(i=0;i<=7;i++)
		result = bit_test(value,i) ? i : result;
	return result;
}