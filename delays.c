/*
 * File:   delays.c
 * Author: kharris
 *
 * Created on March 1, 2023, 10:16 AM
 */


#include <xc.h>
#include "delays.h"
#include "mcc_generated_files/device_config.h"

// NHAN: delay_us() and delay_ms() generated using Timer3


void delay_us( unsigned int t)          // See Timers tutorial for more info on this function
{
    //T1GE disabled; T1GTM disabled; T1GPOL low; T1GGO done; T1GSPM disabled; 
    T3GCON = 0x00;

    //GSS T1G_pin; 
    T3GATE = 0x00;

    //CS FOSC/4; 
    T3CLK = 0x02; // Timer3 ???

    T3CONbits.ON = true;          // enable Timer3

    // delay 100us per loop until less than 100us remain
    while( t >= 100){
        t-=100;
        TMR3 = 0;
        while( TMR3 < _XTAL_FREQ/10000);
    }

    // delay 10us per loop until less than 10us remain
    while( t >= 10){
        t-=10;
        TMR3 = 0;
        while( TMR3 < _XTAL_FREQ/100000);
    }

    // delay 1us per loop until finished
    while( t > 0)
    {
        t--;
        TMR3 = 0;
        while( TMR3 < _XTAL_FREQ/1000000);
    }

    // turn off Timer4 so function is self-contained
    T3CONbits.ON = false;

} // END delay_us()

void delay_ms(unsigned int ms)
{
    do
    {
        delay_us(1000);
        ms--;
    }while(ms);
}
