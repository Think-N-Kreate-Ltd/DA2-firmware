/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18LF46K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB             :  MPLAB X 6.00

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "pin_manager.h"
#include "../main.h"
#include "../delays.h"




void (*IOCBF3_InterruptHandler)(void);
void (*IOCBF4_InterruptHandler)(void);
void (*IOCBF5_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */

#ifdef R0_LAYOUT
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISE = 0x01;
    TRISA = 0xFF;
    TRISB = 0xFE;
    TRISC = 0x17;
    TRISD = 0x0F;

    /**
    ANSELx registers
    */
    ANSELD = 0x0F;
    ANSELC = 0x07;
    ANSELB = 0xC0;
    ANSELE = 0x01;
    ANSELA = 0xFF;

    /**
    WPUx registers
    */
    WPUD = 0x00;
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    ODCOND = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x07;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0x0F;
    
#else
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x43;   //0x7F;
    TRISB = 0xFE;
    TRISC = 0x10;
    TRISD = 0xFF;
    TRISE = 0x00;

    /**
    ANSELx registers
    */
    ANSELA = 0x03;  //0x3F;
    ANSELB = 0x00;  //0xC0;
    ANSELC = 0x00;
    ANSELD = 0x00;
    ANSELE = 0x00;

    /**
    WPUx registers
    */
    WPUA = 0x00;
    WPUB = 0x00;
    WPUC = 0x00;
    WPUD = 0x00;
    WPUE = 0x00;

    /**
    ODx registers
    */
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    ODCOND = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x07;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0x0F;

#endif
    /**
    IOCx registers 
    */
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF3 = 0;
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF4 = 0;
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF5 = 0;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN3 = 0;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN4 = 0;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN5 = 0;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP3 = 1;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP4 = 1;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP5 = 1;



    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCBF3_SetInterruptHandler(IOC_InterruptHandler);
    IOCBF4_SetInterruptHandler(IOC_InterruptHandler);
    IOCBF5_SetInterruptHandler(IOC_InterruptHandler);
   
    // NHAN: only enable IOC when device goes to sleep mode
    // Check buttons states will be handled by Timer0 scan
    // Enable IOCI interrupt 
//    PIE0bits.IOCIE = 1; 
    
	
    SSP2DATPPS = 0x0A;   //RB2->MSSP2:SDA2;    
    SSP1CLKPPS = 0x13;   //RC3->MSSP1:SCK1;    
    RB1PPS = 0x11;   //RB1->MSSP2:SCL2;    
    RC3PPS = 0x0F;   //RC3->MSSP1:SCK1;    
    RB2PPS = 0x12;   //RB2->MSSP2:SDA2;    
//    T2INPPS = 0x13;   //RC3->TMR2:T2IN;   // external reset source for Timer2
    RC5PPS = 0x10;   //RC5->MSSP1:SDO1;    
    SSP1DATPPS = 0x14;   //RC4->MSSP1:SDI1;    
    SSP2CLKPPS = 0x09;   //RB1->MSSP2:SCL2;    
}
  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCBF3
    if(IOCBFbits.IOCBF3 == 1)
    {
        IOCBF3_ISR();  
    }	
	// interrupt on change for pin IOCBF4
    if(IOCBFbits.IOCBF4 == 1)
    {
        IOCBF4_ISR();  
    }	
	// interrupt on change for pin IOCBF5
    if(IOCBFbits.IOCBF5 == 1)
    {
        IOCBF5_ISR();  
    }
    PIE0bits.IOCIE = 0;         //Disable IOC interrupts until ready again 

}

/**
   IOCBF3 Interrupt Service Routine
*/
void IOCBF3_ISR(void) {

    // Add custom IOCBF3 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF3_InterruptHandler)
    {
        IOCBF3_InterruptHandler();
    }
    IOCBFbits.IOCBF3 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF3 at application runtime
*/
void IOCBF3_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF3_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF3
*/
void IOCBF3_DefaultInterruptHandler(void){
    // add your IOCBF3 interrupt custom code
    // or set custom function using IOCBF3_SetInterruptHandler()
    
    //BTN_UP
    if(mstate.upPressed == 0) mstate.upPressed = 1;
    mstate.buttonPressed = 1;
}

/**
   IOCBF4 Interrupt Service Routine
*/
void IOCBF4_ISR(void) {

    // Add custom IOCBF4 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF4_InterruptHandler)
    {
        IOCBF4_InterruptHandler();
    }
    IOCBFbits.IOCBF4 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF4 at application runtime
*/
void IOCBF4_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF4_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF4
*/
void IOCBF4_DefaultInterruptHandler(void){
    // add your IOCBF4 interrupt custom code
    // or set custom function using IOCBF4_SetInterruptHandler()
    
    // BTN_ENTER
    if(mstate.menuPressed == 0) mstate.menuPressed = 1;
    mstate.buttonPressed = 1;
}

/**
   IOCBF5 Interrupt Service Routine
*/
void IOCBF5_ISR(void) {

    // Add custom IOCBF5 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF5_InterruptHandler)
    {
        IOCBF5_InterruptHandler();
    }
    IOCBFbits.IOCBF5 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF5 at application runtime
*/
void IOCBF5_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF5_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF5
*/
void IOCBF5_DefaultInterruptHandler(void){
    // add your IOCBF5 interrupt custom code
    // or set custom function using IOCBF5_SetInterruptHandler()
    
    //BTN_DN
    if(mstate.downPressed == 0) mstate.downPressed = 1;
    mstate.buttonPressed = 1;
}

// When any IOC happens, run this handler
void IOC_InterruptHandler(void)
{    
    // Re-enable Timer0 to scan buttons states
    TMR0 = 0;   // reset Timer0 
//    TMR0H = 0xF9; 
//    TMR0L = 0x00;
    PIR0bits.TMR0IF = 0;    // clear Timer0 interrupt flag
    PIE0bits.TMR0IE = 1;    // Enable Timer0 interrupt
    T0CON0bits.T0EN = 1;    // Start Timer0
}

/**
 End of File
*/