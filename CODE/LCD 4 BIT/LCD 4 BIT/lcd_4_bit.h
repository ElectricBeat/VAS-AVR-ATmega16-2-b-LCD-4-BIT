/*
 * LCD_4_BIT.h
 *
 * Created: 26-04-2024 14:24:50
 *  Author: SRIDHAR
 */ 

#define LCD_Data_Dir		DDRA		/* Define LCD data port direction */
#define LCD_Command_Dir		DDRC		/* Define LCD command port direction register */

#define LCD_Data_Port		PORTA		/* Define LCD data port */
#define LCD_Command_Port	PORTC		/* Define LCD data port */

#define RS PC6							/* Define Register Select (data/command reg.)pin */
#define EN PC7							/* Define Enable signal pin */

void LCD_Command(unsigned char cmnd)
{
	LCD_Command_Port &= ~(1<<RS);		/* RS=0 command reg. */

	LCD_Command_Port |= (1<<EN);		/* Enable pulse */
	LCD_Data_Port = (LCD_Data_Port & 0X0F)|(cmnd & 0XF0);	/* sending upper nibble */
	_delay_us(5);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);

	LCD_Command_Port |= (1<<EN);		/* Enable pulse */
	LCD_Data_Port = (LCD_Data_Port & 0X0F)|(cmnd<<4);		/* sending lower nibble */
	_delay_us(5);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Command_Port |= (1<<RS);		/* RS=1 Data reg. */

	LCD_Command_Port |= (1<<EN);		/* Enable Pulse */
	LCD_Data_Port = (LCD_Data_Port & 0X0F)|(char_data & 0XF0);	/* sending upper nibble */
	_delay_us(5);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);

	LCD_Command_Port |= (1<<EN);		/* Enable Pulse */
	LCD_Data_Port = (LCD_Data_Port & 0X0F)|(char_data<<4);		/* sending lower nibble */
	_delay_us(5);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_String (char *str)				/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)				/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void lcd_cursor(unsigned char row,unsigned char col)
{
	if(row==1)
	LCD_Command(0X80+col);
	if(row==2)
	LCD_Command(0XC0+col);
	if(row==3)
	LCD_Command(0X94+col);
	if(row==4)
	LCD_Command(0XD4+col);
	
	//	if(col>20)
	//	return;
}

void LCD_Clear()
{
	LCD_Command (0x01);					/* clear display */
	LCD_Command (0x80);					/* cursor at home position */
}

void LCD_Init (void)					/* LCD Initialize function */
{
	LCD_Command_Dir |= (1<<PINC6);		/* Make LCD command port direction as o/p */
	LCD_Command_Dir |= (1<<PINC7);		/* Make LCD command port direction as o/p */

	LCD_Data_Dir |= (1<<PINA4);			/* Make LCD data port direction as o/p */
	LCD_Data_Dir |= (1<<PINA5);			/* Make LCD data port direction as o/p */
	LCD_Data_Dir |= (1<<PINA6);			/* Make LCD data port direction as o/p */
	LCD_Data_Dir |= (1<<PINA7);			/* Make LCD data port direction as o/p */

	_delay_ms(20);						/* LCD Power ON delay always >15ms */

	LCD_Command (0x02);					/* send for 4 bit initialization of LCD  */
	LCD_Command (0x28);					/* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command (0x0C);					/* Display ON Cursor OFF */
	LCD_Command (0x06);					/* Auto Increment cursor */
	LCD_Command (0x01);					/* Clear display */
	LCD_Command (0x80);					/* Cursor at home position */
}