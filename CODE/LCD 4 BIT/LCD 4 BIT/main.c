/*
 * LCD 4 BIT.c
 *
 * Created: 25-04-2024 17:51:16
 * Author : SRIDHAR
 */

#define F_CPU 1000000UL					/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */
#include "lcd_4_bit.h"
 
int main()
{
	LCD_Init();							/* Initialize LCD */

	while (1)
	{
		lcd_cursor(1,0);				/* Go to 1st line*/
		LCD_String("VAS");				/* write string on 1st line of LCD*/
		LCD_Command (0x1C);
		_delay_ms(100);
	}
}
