#include "project_headers.h"
#include <string.h>
#define LED 2
int main()
{
	//char msg[]="EcoLight Maestro - Time & Intensity Adaptive Street Light Automation";
	int h,m,s,d,mon,y,adcval,day;
	float EAV;
	//IODIR0|=1<<LED;
	WRITENIBBLE(IODIR0,LED,15);
	InitRTC();
	InitADC();
	InitKPM();
	InitLCD();
	
	CmdLCD(GTL1_P0);
	StringLCD("TITLE:");
	//CmdLCD(CLR);
	CmdLCD(GTL2_P0);
	StringLCD("ECOLIGHT MAESTROE");
	delay_ms(100);
	CmdLCD(GTL2_P0);
	StringLCD("                ");
	CmdLCD(GTL2_P0);
	StringLCD("TIME & INTENSITY");
	delay_ms(100);
	CmdLCD(GTL2_P0);
	StringLCD("                ");
	CmdLCD(GTL2_P0);
	StringLCD("ADAPTIVE STREET");
	delay_ms(100);
	CmdLCD(GTL2_P0);
	StringLCD("                ");
	CmdLCD(GTL2_P0);
	StringLCD("LIGHT AUTOMATION");
	delay_ms(100);
	CmdLCD(CLR);
	SetRTCTime(18,59,50);
	SetRTCDate(13,10,2025);
	SetRTCDays(5);
	
	while(1)
	{
		
		InitInterrupt();
	  GetRTCDate(&d,&mon,&y);
	  DisplayRTCDate(d,mon,y);
		GetRTCTime(&h,&m,&s);
	  DisplayRTCTime(h,m,s);
	  GetRTCDays(&day);
	  DisplayRTCDays(day);
		adcval=ReadADCVal();
		EAV=(adcval*(3.3/1024));
		CmdLCD(GTL2_P0+9);
	  StringLCD("LDR:");
		CmdLCD(GTL2_P0+13);
		F32LCD(EAV,1);
		
		
		
		if((h >= 18 && h <= 23) || (h >= 0 && h <6)) 
			{
        
			
        if(EAV>2.7f)  // adcVal came 0x174 still it going to this if condition 
				{  
            WRITENIBBLE(IOPIN0,LED,15);  // Turn ON LED in dark
        } 
				else 
					{
            WRITENIBBLE(IOPIN0,LED,0);    // Turn OFF LED in light
          }
      }
		else
		{
		WRITENIBBLE(IOPIN0,LED,0); 
		}
}
}
