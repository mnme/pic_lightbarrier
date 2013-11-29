/******* LCD-Library ************************************************************************
 *																							*
 * Title:		PBA5 Board-Support-Library, LCD-hardware-drivers for dog-m LCD-Series		*
 * Author:		Remo Seiler, Ascom (Schweiz) AG, Berufsbildungscenter						*
 *																							*
 ********************************************************************************************/


#include "..\config\board_config.h"

#define MAX_ADDR 			80
static unsigned char get_spec_char(unsigned char ch);

/**
 * Sendet ein Datenbyte (z.B. ein Zeichen) oder einen Befehl ans LCD
 * 
 * @param value		Das zu �betragende Datenbyte / der zu �betragende Befehl (8Bit)
 */
void lcd_send(unsigned char value)
{	
	LCD_EN=1;						//Pos. Flanke am Enable-Pin
	LCD_D7 = bit_test(value,7);		//Oberes Daten-Nibble anlegen
	LCD_D6 = bit_test(value,6);
	LCD_D5 = bit_test(value,5);
	LCD_D4 = bit_test(value,4);
	LCD_EN=0;						//Oberes Nibble senden	
	LCD_EN=1;						//Pos. Flanke am Enable-Pin								
	LCD_D7 = bit_test(value,3);		//Unteres Daten-Nibble anlegen
	LCD_D6 = bit_test(value,2);
	LCD_D5 = bit_test(value,1);
	LCD_D4 = bit_test(value,0);
	LCD_EN=0;						//Unteres Nibble senden
	__delay_us(30);					//Maximaler Zeitbedarf einer �bertragung (blocking)
 }

/**
 * Display l�schen -> Das gesamte LCD-Daten-RAM wird mit 0x20 (Leerschlag) �berschrieben
 * Da der Vorgang bis zu 2ms dauern kann muss der Programmablauf nach dem Senden des
 * Befehls entsprechend lang blockiert werden (delay).
 */
void lcd_clear(void)						
{
	lcd_send_command(0b00000001);					//clear display
	//lcd_send(0b00000001);							//clear display
	delay_ms(2);									//max. Zeitbedarf des LCD-Clear-Befehls
}

/**
 * Display-RAM zur�ckschieben (Ausgangsposition). Die Funktion setzt den Anzeigebereich
 * des LCDs und den Cursor zur�ck auf die Anfangsposition (Adresse 0).
 */
void lcd_home(void)							
 {	
	lcd_send_command(0b00000010);					//return home
	delay_ms(2);
 }

/**
 * Display-RAM im Anzeigebereich nach links schieben
 * 
 * @param value		Anzahl Verschiebungsschritte des Display-RAMs
 */
void lcd_shle(unsigned char value)			
{
	for(;value!=0;value--)
		lcd_send_command(0b00011000);				//display shift left
}

/**
 * Display-RAM im Anzeigebereich nach rechts schieben
 * 
 * @param value		Anzahl Verschiebungsschritte des Display-RAMs
 */
void lcd_shri(unsigned char value)			
{
	for(;value!=0;value--)
		lcd_send_command(0b00011100);				//display shift right 
}

/**
 * Setzt die Cursor-Position f�r ein 2 Zeilen-Display
 * 
 * @param dispx		X-Koordinate (0-15) resp. Spalte auf die der Cursor gesetzt werden soll
 * @param dispy		Y-Koordinate (0-1) resp. Zeile auf die der Cursor gesetzt werden soll
 */
void lcd_gotoxy(unsigned char dispx, unsigned char dispy)	
{
	unsigned char disp_address;
	if(dispy == 0) disp_address = 0x00;						//Basisadresse 1. Zeile
	if(dispy == 1) disp_address = 0x40; 					//Basisadresse 2. Zeile
	disp_address += dispx;									//Basisadresse + Spaltenadresse
	lcd_send_command((0b10000000 | disp_address));			//Cursor-Adresse an LCD senden
}

/**
 * Zeichen im erweiterten Zeichensatz (�,�,�) f�r den japanischen Zeichensatz ermitteln. Falls
 * Das �bergebene Zeichen kein Umlaut ist wird das Originalzeichen zur�ck gegeben ansonsten
 * der f�r den dog-m-Zeichensatz korrekte Zeichenwert.
 * 
 * @param ch		Zeichen das gepr�ft und falls Umlaut korrigiert werden soll
 * @return			Originalzeichen oder gem�ss dog-m-Zeichensatz korrigiertes Zeichen
 */
static unsigned char get_spec_char(char ch)
{
	switch (ch)
	{
		case 0xE4: return 0x84;		//'�'
		case 0xC4: return 0x8E;		//'�'
		case 0xF6: return 0x94;		//'�'
		case 0xD6: return 0x99;		//'�'
		case 0xFC: return 0x81;		//'�'
		case 0xDC: return 0x9A;		//'�'
		default:  return ch;
	}
}

/**
 * Ein Zeichen an das LCD senden (inkl. Sonderzeichenbearbeitung)
 * 
 * @param ch		Zeichen das ans LCD gesendet werden soll
 */
void lcd_putc(char ch)
{
	switch (ch)
	{
		case '\r':								//Wenn Zeilenumbruch oder Zeilenvorschub...
		case '\n': lcd_gotoxy(0,1); break;		//-> Cursor auf 1. Zeichen, 2. Zeile
		case '\f': lcd_clear(); break;			//Wenn form feed -> LCD l�schen
		default:
			lcd_send_data(get_spec_char(ch)); 	//Zeichen an LCD senden
	}
}

/**
 * String an LCD ausgeben mit Verwendung der lcd_putc-Funktion
 * 
 * @param *ptr		Zeiger auf den String mit Null-Terminierung
 */
void lcd_puts(char *ptr)
{
	while(*ptr!=0) 								//Solange Nullterminierung noch nicht erreicht
		lcd_putc(*ptr++);						//Zeichen an LCD senden und Pointer auf n�chstes Zeichen
}

/**
 * Cursor oder blinkender Cursor ein-/ausschalten
 * 
 * @param c_mode	Der einzustellende Cursor-Modus (LCD_CURSOR_ON, LCD_CURSOR_OFF, LCD_CURSOR_OFF_BLINK oder LCD_CURSOR_ON_BLINK)
 */
void lcd_curs(unsigned char c_mode)
{			
	lcd_send_command(0b00001000|c_mode);		//Cursor-Wert an LCD senden
}

/**
 * Initialsiert das dog-m-Text-LCD
 * 
 * Initialiert LCD mit 4-Bit-Modus, Cursor increment, Cursor off, Blink off, 
 * Einstellungen des Boost-Converters, ...)
 *
 * Das LCD wird nach dem Initialisierungsvorgang zus�tzlich gel�scht.
 * Diese Funktion sollte in einem Projekt nur einmal ausgef�hrt werden.
 *
 * Die TRIS-Register der LCD-Pins m�ssen diese als Ausgang definieren!
 */
void lcd_init(void)
{ 
	delay_ms(40);						//Betriebsspannung am LCD f�r mind. 40ms vorhanden
	LCD_RS=0;							//LCD interpretiert n�chstes Zeichen als Befehl 
	LCD_RW=0;							//Auf LCD schreiben...
	lcd_send_command(0b00000011);		//Function Set 8-Bit
	delay_ms(2);						//Pause gem�ss init-Ablauf (siehe Datenblatt)
	lcd_send_command(0b00110011);		//Function Set 8-Bit (2x)
	lcd_send_command(0b00100010);		//Function Set 4-Bit-Modus
	lcd_send_command(0b00101001);		//Function Set
	lcd_send_command(0b00010100);		//Internal OSC frequency
	lcd_send_command(0b01111000);		//Contrast Set
	lcd_send_command(0b01010101);		//Power/ICON/Contrast control
	lcd_send_command(0b01101101);		//Follower control
	lcd_send_command(0b00001100);		//Display ON/OFF control
	lcd_send_command(0b00000001);		//Display l�schen / Cursor home
	delay_ms(2);						//max. Zeitbedarf des LCD-Clear-Befehls
	lcd_send_command(0b00000110);		//Cursor Auto-increment
	lcd_send_command(0b00101000);		//Function Set
}