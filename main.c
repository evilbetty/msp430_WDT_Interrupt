#include "msp430.h"

#define RED_LED BIT0
#define GREEN_LED BIT6

void init_clocks()
{
    // Disable WDT
    WDTCTL = WDTPW + WDTHOLD; // watchdog timer setup
    // Set the calibrating things for the DCO
    BCSCTL1 = CALBC1_1MHZ; // Set range
    DCOCTL = CALDCO_1MHZ; // Set DCO step + modulation
    // ACLK runs from VLO
    BCSCTL3 |= LFXT1S_2;
    // Select DCO as MCLK and the /8 divider (125KHz)
    BCSCTL2 |= SELM_0 + DIVM_3;
}

void init_wdt_timer();
{
    WDTCTL = WDT_ADLY_250;              // WDT as interval timer
    IE1 |= WDTIE;                       // Enable WDT interrupt
}

void main()
{
    init_clocks();
    init_wdt_timer();
	
    // P1.0 and 1.6 as outputs and output 0
    P1DIR = 0x41;
    P1OUT = 0;

    while(1)
    {
	    // Just toggling green led to show while loop
        P1OUT ^= GREEN_LED;
        __delay_cycles(50000);
        P1OUT ^= GREEN_LED;
        __delay_cycles(50000);
    }
}

