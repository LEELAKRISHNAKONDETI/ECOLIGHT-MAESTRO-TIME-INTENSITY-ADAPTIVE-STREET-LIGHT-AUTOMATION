#include <lpc21xx.h>
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"
#include "kpm.h"
#include "types.h"
#include "rtc1.h"
char Input()
{
	char key='\0';
	do{
		
		key=KeyScan();
		while(ColScan()==0);
		delay_ms(200);
		CmdLCD(GTL2_P0);
		CharLCD(key);
	}while(key=='\0');
	return key;
}
int CheckNum(int*val,int low,int high)
{
	if(*val>=low && *val<=high)
		return 0;
	return 1;
}
void General()
{
	CmdLCD(CLR);
	CmdLCD(GTL1_P0);
	StringLCD("ENTER AGAIN!");
	delay_ms(2000);
	CmdLCD(CLR);
}

void DisplayMenu()
{
	CmdLCD(CLR);
	CmdLCD(GTL1_P0);
	StringLCD("1:HR 2:MIN 3:SEC");
	CmdLCD(GTL2_P0);
	StringLCD("4:DAY 5:MN 6:YR");
	//delay_s(2);
}
u32 ReadNum(){
  unsigned int num=0,key;
	while(1){
		key='\0';
    key=KeyScan();
    while(ColScan()==0);
		delay_ms(200);
    
    if(key>='0' && key<='9'){
			CharLCD(key);
      num=num*10+(key-'0');
    }
    else if(key=='c'){
    num/=10;
			CmdLCD(SHIFT_CUR_LEFT);
// Move cursor left
    CharLCD(' ');   
			
			CmdLCD(SHIFT_CUR_LEFT);

    }
    else if(key=='='){
      break;
    }
  }
  return num;
}







void myISR(void)__irq
{
	unsigned char opt='\0';
	int value=0;
	////IODIR0|=1<<LED;
	///temp=EXTINT;
	while(1)
	{
		DisplayMenu();
		//CmdLCD(CLR);
		//CmdLCD(GTL1_P0);
		//StringLCD("CHOSE YOUR OPT");
		opt=Input();
		if(opt!='0'){
	  CmdLCD(CLR);
    StringLCD("ENTER VALUE: ");
		}
		switch(opt)
		{
			case '1':value=ReadNum();
			         if(CheckNum(&value,0,23))
							 {
								 General();
								 break;
							 }
							 SetHour(value);
							 break;
			case '2':value=ReadNum();
			         if(CheckNum(&value,0,59))
							 {
								 General();
								 break;
							 }
							 SetMin(value);
							 break;
			case '3':value=ReadNum();
			         if(CheckNum(&value,0,59))
							 {
								 General();
								 break;
							 }
							 SetSec(value);
							 break;
			case '4':value=ReadNum();
			         if(CheckNum(&value,1,31))
							 {
								 General();
								 break;
							 }
							 SetDay(value);
							 break;
			case '5':value=ReadNum();
			         if(CheckNum(&value,1,12))
							 {
								 General();
								 break;
							 }
							 SetMonth(value);
							 break;
			case '6':value=ReadNum();
			         if(CheckNum(&value,2000,2025))
							 {
								 General();
								 break;
							 }
							 SetYear(value);
							 break;
			case '0' : break;
								 
		}
		if(opt=='0')
			break;
		
	}
	
	CmdLCD(CLR);
	StringLCD("EXISTING");
	delay_ms(200);
	CmdLCD(CLR);
	EXTINT=1<<0;
	VICVectAddr0=0x00;
}
void InitInterrupt(void)
{
	
	VICIntEnable=0x01<<14;
	VICVectCntl0=(0x01<<5)|14;
	VICVectAddr0=(unsigned) myISR;
	PINSEL1=0x15400001;
	EXTMODE|=0x01;
	EXTPOLAR|=0x00;
}
