#include <msp430.h> 
#include "msp430g2553.h"
//Reference: http://www.embeddedrelated.com/showarticle/179.php
int main(void)  //Main program
{
   WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

   P1DIR |= BIT0; // Set P1.0 to output and P1.3 to input direction
   P1OUT &= ~BIT0; // set P1.0 to Off
   P1IE |= BIT3; // P1.3 interrupt enabled
   P1IFG &= ~BIT3; // P1.3 interrupt flag cleared
   P1REN |= BIT3;	// Enable Pull Up on (P1.3)
   P1IES |= BIT3; // P1.3 Hi/lo edge
   __bis_SR_register(GIE); // Enable all interrupts

   while(1) //Loop forever, we'll do our job in the interrupt routine...
   {}
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;  // Toggle P1.0
    P1IFG &= ~BIT3; // P1.3 interrupt flag cleared
}
