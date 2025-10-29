#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define ADCCLK 3000000
#define CLKDIV_VAL ((PCLK/ADCCLK)-1)

//pin defines//
//ADCR//
#define CLKDIV_BITS 8
#define PDN_BIT 21
#define START_BIT 24

//ADDR//
#define DONE_BIT 31
#define ADC_RESULT 6
