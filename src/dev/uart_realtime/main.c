#include <msp430.h> 
#include "msp430g2553.h"

const char string[] = { "Hello World\r\n" };
unsigned int i; //Counter
/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
	CCTL0 = CCIE;                             // CCR0 interrupt enabled
	TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
	CCR0 =  10000;                     // 12.5 Hz
	P1OUT &= 0x00;               // Shut down everything
	P1DIR &= 0x00;
	P1DIR |= BIT0 + BIT6;            // P1.0 and P1.6 pins output the rest are input
	P1REN |= BIT3;                   // Enable internal pull-up/down resistors
	P1OUT |= BIT3;                   //Select pull-up mode for P1.3
	P1IE |= BIT3;                       // P1.3 interrupt enabled
	P1IES |= BIT3;                     // P1.3 Hi/lo edge
	P1IFG &= ~BIT3;                  // P1.3 IFG cleared
	UCA0CTL1 |= UCSSEL_2; // SMCLK
	UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
	UCA0BR1 = 0; // Set baud rate to 9600 with 1MHz clock
	UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
	i = 0;
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	_BIS_SR(CPUOFF + GIE);          // Enter LPM0 w/ interrupt

	while(1)                          //Loop forever, we work with interrupts!


	{}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
   P1OUT ^= BIT0;
   UCA0TXBUF = string[i++]; // TX next character
      if (i == sizeof string - 1) // TX over?
      {
    	  i = 0;
         UC0IE &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt// Toggle P1.0
      }
}
