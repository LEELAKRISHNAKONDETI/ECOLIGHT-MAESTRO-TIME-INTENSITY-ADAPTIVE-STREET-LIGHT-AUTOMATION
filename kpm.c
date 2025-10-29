#include <lpc21xx.h>
#include "kpm.h"
#include "kpm_defines.h"
#include "types.h"
#include "defines.h"
#include "lcd.h"
#include "lcd_defines.h"
u8 KPMLUT[4][4]=
{
	{'7','8','9','+'},{'4','5','6','-'},{'1','2','3','*'},{'c','0','=','i'}
};
void InitKPM(void)
{
	WRITENIBBLE(IODIR1,ROW0,15);
}
u32 ColScan(void)
{
	return ((IOPIN1>>COL0)&15)<15?0:1;
}
u32 RowCheck(void)
{
	u32 i;
	while(ColScan());
	for(i=0;i<4;i++)
	{
		WRITENIBBLE(IOPIN1,ROW0,~(1<<i));
		if(ColScan()==0)
			break;
	}
	WRITENIBBLE(IOPIN1,ROW0,0);
	return i;
}
u32 ColCheck(void)
{
	u32 i;
	for(i=0;i<4;i++)
	{
		if(!(READBIT(IOPIN1,(COL0+i))))
			break;
	}
	return i;
}
u8 KeyScan(void)
{
	u8 KEY;
	u32 row,col;
	while(ColScan());
	row=RowCheck();
	col=ColCheck();
	KEY=KPMLUT[row][col];
	return KEY;
}
unsigned int ReadNumber()
{
	unsigned char key;
	unsigned int num=0;
	CmdLCD(CLR);
	CmdLCD(GTL1_P0);
	StringLCD("enter hour");
	CmdLCD(GTL2_P0);
	while(1)
	{
		key=KeyScan();
		CharLCD(key);
		num=((num*10)+(key-48));
		if(key=='=')
			break;
	}
	return num;
}


