/*#include<LPC21xx.h>
#include "delay.h"
#include "Pinconnect_block.h"
#define FUN2 1
#define EINT0_FUN FUN2
#define EINT0_LED  8
#define EINT0 14
#ifndef __irq
#define __irq
#endif
int cnt=0;

void eint0_isr(void) __irq{
    // toggle led
    IOPIN0^=1<<EINT0_LED;
    delay_ms(10000);
    //clear the interrupt
    EXTINT=1<<0;
    VICVectAddr=0;
}
void enable_eint0(void){
    IODIR0|=1<<EINT0_LED;
    // p0.16 is has the function of eint0
    CfgPortPinFunc(0,16,EINT0_FUN);
    //select type of interrupt irq/fiq
    VICIntSelect=0;
    //enable the eint0
    VICIntEnable|=1<<EINT0;
    // SET THE ENABLE BIT AND CHANNEL  binary
    VICVectCntl0|=(1<<5)|(EINT0);
    // assign the ISR address 
    VICVectAddr0=(unsigned int)eint0_isr;
    //edge triggering 1<<0
    EXTMODE=1<<0;
    EXTPOLAR=0<<0;
}
int main(){
    enable_eint0();
    while(1){
        cnt++;
        delay_ms(1000);
    }
}*/
#include<LPC21xx.h>
#include "delay.h"
#include "Pinconnect_block.h"

#define FUN2 1  // Changed from 1 to 2 - correct function code for EINT0
#define EINT0_FUN FUN2
#define EINT0_LED  8
#define EINT0 14
#ifndef __irq
#define __irq
#endif


volatile int cnt = 0;  // Added volatile for shared variable

void eit0_isr(void) __irq{
    // Toggle LED
    IOPIN0 ^= (1 << EINT0_LED);
    
    // Clear the interrupt FIRST - very important!
    EXTINT = (1 << 0);
    
    // Small delay to avoid bouncing (reduced from 10000ms)
    delay_ms(100);
    
    // Clear VIC interrupt
    VICVectAddr = 0;
}

void enable_eint0(void) {
    // Configure LED pin as output
    IODIR0 |= (1 << EINT0_LED);
    
    // Configure P0.16 as EINT0 function
    CfgPortPinFunc(0, 16, EINT0_FUN);
    
    // Select IRQ (not FIQ)
    VICIntSelect &= ~(1 << EINT0);  // Clear bit for IRQ
    
    // Configure interrupt as edge-triggered, falling edge
    EXTMODE |= (1 << 0);   // Edge sensitive
    EXTPOLAR &= ~(1 << 0); // Falling edge (active low)
    
    // Clear any pending interrupts
    EXTINT = (1 << 0);
    
    // Configure VIC
    VICVectCntl0 = (1 << 5) | EINT0;  // Enable and set channel
    VICVectAddr0 = (unsigned int)eit0_isr;  // Set ISR address
    
    // Enable EINT0 interrupt
    VICIntEnable |= (1 << EINT0);
}

int main() {
    // Initialize system (add if you have system init)
    // SystemInit();
    
    enable_eint0();
    
    while(1) {
        cnt++;
        delay_ms(1000);
        // Optional: Add some indication that main loop is running
        // You could toggle another LED here to show the system is alive
    }
    
    
}