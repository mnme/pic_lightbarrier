/******* LCD-Library ************************************************************************
 *																							*
 * Title:		PBA5 Board-Support-Library, LCD-hardware-drivers for dog-m LCD-Series		*
 * Author:		Remo Seiler, Ascom (Schweiz) AG, Berufsbildungscenter						*
 *																							*
 ********************************************************************************************/

#ifndef __driver_lcd44780_H__
#define __driver_lcd44780_H__

// Display-Pins

#define LCD_D4 RC0
#define LCD_D5 RC1
#define LCD_D6 RC2
#define LCD_D7 RC3
#define LCD_EN RC4
#define LCD_RW RC5
#define LCD_RS RC6

// Defines for Cursor-Function (dispcurs(mode);)

#define LCD_CURSOR_ON 			0x06
#define LCD_CURSOR_OFF 			0x04
#define LCD_CURSOR_OFF_BLINK 	0x05
#define LCD_CURSOR_ON_BLINK 	0x07

// macros

#define lcd_send_command(command)	lcd_send(command)
#define lcd_send_data(value)		LCD_RS=1;lcd_send(value);LCD_RS=0

// prototypes

void lcd_send(unsigned char value);
void lcd_clear(void);
void lcd_home(void);
void lcd_shle(unsigned char value);	
void lcd_shri(unsigned char value);
void lcd_gotoxy(unsigned char dispx, unsigned char dispy);
void lcd_putc(char ch);
void lcd_puts(unsigned char *ptr);
void lcd_puts_rom(const unsigned char *ptr);
void lcd_curs(unsigned char c_mode);
void lcd_init(void);

#endif