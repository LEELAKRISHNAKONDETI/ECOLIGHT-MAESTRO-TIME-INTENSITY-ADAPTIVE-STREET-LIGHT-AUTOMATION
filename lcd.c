#include "delay.h"
#include "defines.h"
#include <lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
void WriteLCD(u8 data)
{
	//TO ACTIVATE WRITE MODE
	IOCLR0|=1<<LCD_RW;
	//WRITE TO LCD
  WRITEBYTE(IOPIN1,LCD_DATA,data);
	//IOPIN0=(IOPIN0&~(255<<LCD_DATA)|(data<<LCD_DATA));
	//IOPIN1=(IOPIN1&(~(
	IOSET0|=1<<LCD_EN;
	delay_us(5);
	IOCLR0|=1<<LCD_EN;
	delay_ms(37);
}
void CmdLCD(u8 cmd)
{
	//TO ACTIVATE CMD MODE
	IOCLR0=1<<LCD_RS;
	WriteLCD(cmd);
	delay_ms(2);
}
void InitLCD(void)
{
	//SET FOR DIRECTIONS TO LCD PINS
	WRITEBYTE(IODIR1,LCD_DATA,255);
	//IODIR0=(IODIR0&(~(7<<LCD_RS))|(7<<LCD_RS));
	WRITENIBBLE(IODIR0,LCD_RS,7);
	
	delay_ms(15);
	CmdLCD(0x30);
	delay_ms(4);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	CmdLCD(BM2L);
	CmdLCD(DOCB);
	CmdLCD(CLR);
	CmdLCD(SCR);
}
void CharLCD(u8 asciival)
{
	//TOACTIVATE DATA MODE
	IOSET0=1<<LCD_RS;
	WriteLCD(asciival);
}
void StringLCD(u8 *ptr)
{
	while(*ptr)
	{
		CharLCD(*ptr);
		ptr++;
	}
}
void U32LCD(u32 num)
{
	u8 arr[10];
	int i=0;
	while(num)
	{
		arr[i++]=((num%10)+'0');
		num=num/10;
	}
	while(i--)
	{
		CharLCD(arr[i]);
	}
}
void F32LCD(float fNum, unsigned char nDP){
	unsigned char i;
    unsigned int intPart;
    if(fNum < 0){
        CharLCD('-');
        fNum = -fNum;
    }
	 intPart = (unsigned int)fNum;
    U32LCD(intPart);

    CharLCD('.');

    fNum = fNum - intPart;

    for(i = 0; i < nDP; i++){
        fNum *= 10;
        intPart = (unsigned int)fNum;
        CharLCD(intPart + '0');
        fNum -= intPart;
    }
}

