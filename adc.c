#include <lpc21xx.h>
#include "delay.h"
#include "adc.h"
#include "lcd.h"
#include "lcd_defines.h"
void InitADC(void)
{
	PINSEL1|=1<<24;
	ADCR=(1<<0)|(4<<8)|(1<<21);
}
unsigned int ReadADCVal()
{
	unsigned int ADCVAL;
	//to start the converstion//
	ADCR|=1<<24;
	delay_ms(2);
	//check the status of adc//
	while(!((ADDR>>31)&1));
	CmdLCD(GTL2_P0+13);
	StringLCD("   ");
	//to read the val//
	ADCVAL=((ADDR>>6)&1023);
	ADCR&=~(7<<24);
	return ADCVAL;
}

/*int main()
{
	
	unsigned int ADCVAL;
	float Eav ;
	IODIR0|=(1<<LED);
	InitLCD();
	InitADC();
	CmdLCD(GTL1_P0);
	StringLCD("ADC TEST 3:");
	while(1)
	{
		CmdLCD(GTL2_P0);
		ADCVAL=ReadADCVal();
		Eav=(ADCVAL*(3.3/1024));
		F32LCD(Eav,2);
	}
}*/
