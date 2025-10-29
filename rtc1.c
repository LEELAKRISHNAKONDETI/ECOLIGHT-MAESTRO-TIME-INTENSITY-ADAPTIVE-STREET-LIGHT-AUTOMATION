#include <lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/5)
#define INT_VAL (int)((PCLK/32768)-1)
#define FRAC_VAL (PCLK-((INT_VAL+1)*32768))
unsigned char week[7][7]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
void InitRTC(void)
{
	CCR=1<<1;
	PREINT=INT_VAL;
	PREFRAC=FRAC_VAL;
	CCR=1<<0;
}
void SetRTCTime(int h,int m,int s)
{
	HOUR=h;
	MIN=m;
	SEC=s;
}
void GetRTCTime(int*h,int*m,int*s)
{
	*h=HOUR;
	*m=MIN;
	*s=SEC;
}
void DisplayRTCTime(int h,int m,int s)
{
	//CmdLCD(CLR);
	CmdLCD(GTL2_P0);
	CharLCD((h/10)+48);
	CharLCD((h%10)+48);
	CharLCD(':');
	CharLCD((m/10)+48);
	CharLCD((m%10)+48);
	CharLCD(':');
	CharLCD((s/10)+48);
	CharLCD((s%10)+48);
}
void SetRTCDate(int d,int m,int y)
{
	DOM=d;
	MONTH=m;
	YEAR=y;
}
void GetRTCDate(int*d,int*m,int*y)
{
	*d=DOM;
	*m=MONTH;
	*y=YEAR;
}
void DisplayRTCDate(int d,int m,int y)
{
	CmdLCD(GTL1_P0);
	CharLCD((d/10)+48);
	CharLCD((d%10)+48);
	CharLCD('/');
	CharLCD((m/10)+48);
	CharLCD((m%10)+48);
	CharLCD('/');
	U32LCD(y);
}
void SetRTCDays(int day)
{
	DOW = day;
}
void GetRTCDays(int*day)
{
	*day=DOW;
}
void DisplayRTCDays(int day)
{
	CmdLCD(GTL1_P0+12);
	StringLCD(week[day]);
}
void SetHour(int num)
{

	HOUR=num;
}
void SetMin(int m)
{
	MIN=m;
}

void SetSec(int s)
{
	SEC=s;
}
void SetDay(int d)
{
	DOM=d;
}
void SetMonth(int m)
{
	MONTH=m;
}
void SetYear(int y)
{
	YEAR=y;
}
