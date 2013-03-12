#include "msp430.h"

#define RED_LED BIT0
#define GREEN_LED BIT6


void init_clocks()
{
    // Disable WDT (Can this stay when using WDT as timer?)
    //WDTCTL = WDTPW + WDTHOLD; // watchdog timer setup
    // Set the calibrating things for the DCO
    BCSCTL1 = CALBC1_1MHZ; // Set range
    DCOCTL = CALDCO_1MHZ; // Set DCO step + modulation
    // ACLK runs from VLO
    BCSCTL3 |= LFXT1S_2;
    // Select DCO as MCLK and the /8 divider (125KHz)
    BCSCTL2 |= SELM_0 + DIVM_3;
}

void init_wdt_timer()
{
    // Enable WDT timer as interval from ACLK
    WDTCTL = WDT_ADLY_250;
    // And enable WDT interrupt
    IE1 |= WDTIE;
}


int main()
{
    init_clocks();
    init_wdt_timer();

    // P1.0 and 1.6 as outputs and output 0
    P1DIR = 0x41;
    P1OUT = 0;

    // Enable global interrupts (and LPM if needed)
    //_BIS_SR(LPM0_bits + GIE);
    _BIS_SR(GIE);

    while(1)
    {
        // Just toggling green led to show while loop
        P1OUT ^= GREEN_LED;
        __delay_cycles(50000);
        P1OUT ^= GREEN_LED;
        __delay_cycles(50000);
    }
    return 0;
}


__attribute__( (interrupt (WDT_VECTOR)) )
void WDT_ISR()
{
    //WTD interrupt ISR
    // Just toggling red led to show interrupt occuring
    P1OUT ^= RED_LED;
}

