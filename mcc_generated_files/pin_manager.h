/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18LF46K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

//#define R0_LAYOUT 1     //Software to be used on old R0 design layout

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

#ifdef R0_LAYOUT
// get/set Pressure aliases
#define Pressure_TRIS                 TRISAbits.TRISA0
#define Pressure_LAT                  LATAbits.LATA0
#define Pressure_PORT                 PORTAbits.RA0
#define Pressure_WPU                  WPUAbits.WPUA0
#define Pressure_OD                   ODCONAbits.ODCA0
#define Pressure_ANS                  ANSELAbits.ANSELA0
#define Pressure_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define Pressure_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define Pressure_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define Pressure_GetValue()           PORTAbits.RA0
#define Pressure_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define Pressure_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define Pressure_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define Pressure_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define Pressure_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define Pressure_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define Pressure_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define Pressure_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set Volts aliases
#define Volts_TRIS                 TRISAbits.TRISA1
#define Volts_LAT                  LATAbits.LATA1
#define Volts_PORT                 PORTAbits.RA1
#define Volts_WPU                  WPUAbits.WPUA1
#define Volts_OD                   ODCONAbits.ODCA1
#define Volts_ANS                  ANSELAbits.ANSELA1
#define Volts_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define Volts_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define Volts_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define Volts_GetValue()           PORTAbits.RA1
#define Volts_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define Volts_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define Volts_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define Volts_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define Volts_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define Volts_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define Volts_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define Volts_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set DispReset aliases
#define DispReset_TRIS                 TRISBbits.TRISB0
#define DispReset_LAT                  LATBbits.LATB0
#define DispReset_PORT                 PORTBbits.RB0
#define DispReset_WPU                  WPUBbits.WPUB0
#define DispReset_OD                   ODCONBbits.ODCB0
#define DispReset_ANS                  ANSELBbits.ANSELB0
#define DispReset_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define DispReset_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define DispReset_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define DispReset_GetValue()           PORTBbits.RB0
#define DispReset_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define DispReset_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define DispReset_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define DispReset_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define DispReset_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define DispReset_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define DispReset_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define DispReset_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSELB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set BTN_UP aliases
#define BTN_UP_TRIS                 TRISBbits.TRISB3
#define BTN_UP_LAT                  LATBbits.LATB3
#define BTN_UP_PORT                 PORTBbits.RB3
#define BTN_UP_WPU                  WPUBbits.WPUB3
#define BTN_UP_OD                   ODCONBbits.ODCB3
#define BTN_UP_ANS                  ANSELBbits.ANSELB3
#define BTN_UP_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define BTN_UP_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define BTN_UP_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define BTN_UP_GetValue()           PORTBbits.RB3
#define BTN_UP_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define BTN_UP_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define BTN_UP_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define BTN_UP_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define BTN_UP_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define BTN_UP_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define BTN_UP_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define BTN_UP_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set BTN_ENTER aliases
#define BTN_ENTER_TRIS                 TRISBbits.TRISB4
#define BTN_ENTER_LAT                  LATBbits.LATB4
#define BTN_ENTER_PORT                 PORTBbits.RB4
#define BTN_ENTER_WPU                  WPUBbits.WPUB4
#define BTN_ENTER_OD                   ODCONBbits.ODCB4
#define BTN_ENTER_ANS                  ANSELBbits.ANSELB4
#define BTN_ENTER_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define BTN_ENTER_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define BTN_ENTER_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define BTN_ENTER_GetValue()           PORTBbits.RB4
#define BTN_ENTER_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define BTN_ENTER_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define BTN_ENTER_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define BTN_ENTER_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define BTN_ENTER_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define BTN_ENTER_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define BTN_ENTER_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define BTN_ENTER_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set BTN_DOWN aliases
#define BTN_DOWN_TRIS                 TRISBbits.TRISB5
#define BTN_DOWN_LAT                  LATBbits.LATB5
#define BTN_DOWN_PORT                 PORTBbits.RB5
#define BTN_DOWN_WPU                  WPUBbits.WPUB5
#define BTN_DOWN_OD                   ODCONBbits.ODCB5
#define BTN_DOWN_ANS                  ANSELBbits.ANSELB5
#define BTN_DOWN_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define BTN_DOWN_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define BTN_DOWN_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define BTN_DOWN_GetValue()           PORTBbits.RB5
#define BTN_DOWN_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define BTN_DOWN_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define BTN_DOWN_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define BTN_DOWN_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define BTN_DOWN_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define BTN_DOWN_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define BTN_DOWN_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define BTN_DOWN_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set DispA0 aliases
#define DispA0_TRIS                 TRISCbits.TRISC6
#define DispA0_LAT                  LATCbits.LATC6
#define DispA0_PORT                 PORTCbits.RC6
#define DispA0_WPU                  WPUCbits.WPUC6
#define DispA0_OD                   ODCONCbits.ODCC6
#define DispA0_ANS                  ANSELCbits.ANSELC6
#define DispA0_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define DispA0_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define DispA0_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define DispA0_GetValue()           PORTCbits.RC6
#define DispA0_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define DispA0_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define DispA0_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define DispA0_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define DispA0_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define DispA0_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define DispA0_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define DispA0_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set DispCS aliases
#define DispCS_TRIS                 TRISCbits.TRISC7
#define DispCS_LAT                  LATCbits.LATC7
#define DispCS_PORT                 PORTCbits.RC7
#define DispCS_WPU                  WPUCbits.WPUC7
#define DispCS_OD                   ODCONCbits.ODCC7
#define DispCS_ANS                  ANSELCbits.ANSELC7
#define DispCS_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define DispCS_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define DispCS_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define DispCS_GetValue()           PORTCbits.RC7
#define DispCS_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define DispCS_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define DispCS_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define DispCS_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define DispCS_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define DispCS_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define DispCS_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define DispCS_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set FlashCS aliases
#define FlashCS_TRIS                 TRISDbits.TRISD4
#define FlashCS_LAT                  LATDbits.LATD4
#define FlashCS_PORT                 PORTDbits.RD4
#define FlashCS_WPU                  WPUDbits.WPUD4
#define FlashCS_OD                   ODCONDbits.ODCD4
#define FlashCS_ANS                  ANSELDbits.ANSELD4
#define FlashCS_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define FlashCS_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define FlashCS_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define FlashCS_GetValue()           PORTDbits.RD4
#define FlashCS_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define FlashCS_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define FlashCS_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define FlashCS_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define FlashCS_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define FlashCS_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define FlashCS_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define FlashCS_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set DispBKLT aliases
#define DispBKLT_TRIS                 TRISDbits.TRISD5
#define DispBKLT_LAT                  LATDbits.LATD5
#define DispBKLT_PORT                 PORTDbits.RD5
#define DispBKLT_WPU                  WPUDbits.WPUD5
#define DispBKLT_OD                   ODCONDbits.ODCD5
#define DispBKLT_ANS                  ANSELDbits.ANSELD5
#define DispBKLT_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define DispBKLT_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define DispBKLT_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define DispBKLT_GetValue()           PORTDbits.RD5
#define DispBKLT_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define DispBKLT_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define DispBKLT_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define DispBKLT_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define DispBKLT_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define DispBKLT_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define DispBKLT_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define DispBKLT_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set PiezoEnable aliases
#define PiezoEnable_TRIS                 TRISDbits.TRISD6
#define PiezoEnable_LAT                  LATDbits.LATD6
#define PiezoEnable_PORT                 PORTDbits.RD6
#define PiezoEnable_WPU                  WPUDbits.WPUD6
#define PiezoEnable_OD                   ODCONDbits.ODCD6
#define PiezoEnable_ANS                  ANSELDbits.ANSELD6
#define PiezoEnable_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define PiezoEnable_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define PiezoEnable_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define PiezoEnable_GetValue()           PORTDbits.RD6
#define PiezoEnable_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define PiezoEnable_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define PiezoEnable_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define PiezoEnable_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define PiezoEnable_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define PiezoEnable_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define PiezoEnable_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define PiezoEnable_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set V5Enable aliases
#define V5Enable_TRIS                 TRISDbits.TRISD7
#define V5Enable_LAT                  LATDbits.LATD7
#define V5Enable_PORT                 PORTDbits.RD7
#define V5Enable_WPU                  WPUDbits.WPUD7
#define V5Enable_OD                   ODCONDbits.ODCD7
#define V5Enable_ANS                  ANSELDbits.ANSELD7
#define V5Enable_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define V5Enable_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define V5Enable_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define V5Enable_GetValue()           PORTDbits.RD7
#define V5Enable_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define V5Enable_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define V5Enable_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define V5Enable_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define V5Enable_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define V5Enable_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define V5Enable_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define V5Enable_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set LED1 aliases
#define LED1_TRIS                 TRISEbits.TRISE1
#define LED1_LAT                  LATEbits.LATE1
#define LED1_PORT                 PORTEbits.RE1
#define LED1_WPU                  WPUEbits.WPUE1
#define LED1_OD                   ODCONEbits.ODCE1
#define LED1_ANS                  ANSELEbits.ANSELE1
#define LED1_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define LED1_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define LED1_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define LED1_GetValue()           PORTEbits.RE1
#define LED1_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define LED1_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define LED1_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define LED1_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define LED1_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define LED1_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define LED1_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS                 TRISEbits.TRISE2
#define LED2_LAT                  LATEbits.LATE2
#define LED2_PORT                 PORTEbits.RE2
#define LED2_WPU                  WPUEbits.WPUE2
#define LED2_OD                   ODCONEbits.ODCE2
#define LED2_ANS                  ANSELEbits.ANSELE2
#define LED2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define LED2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define LED2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define LED2_GetValue()           PORTEbits.RE2
#define LED2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define LED2_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define LED2_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define LED2_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define LED2_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define LED2_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define LED2_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

#define DISP_SEL_GetValue() 1

#else
// get/set Pressure aliases
#define Pressure_TRIS                 TRISAbits.TRISA0
#define Pressure_LAT                  LATAbits.LATA0
#define Pressure_PORT                 PORTAbits.RA0
#define Pressure_WPU                  WPUAbits.WPUA0
#define Pressure_OD                   ODCONAbits.ODCA0
#define Pressure_ANS                  ANSELAbits.ANSELA0
#define Pressure_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define Pressure_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define Pressure_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define Pressure_GetValue()           PORTAbits.RA0
#define Pressure_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define Pressure_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define Pressure_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define Pressure_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define Pressure_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define Pressure_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define Pressure_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define Pressure_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set Volts aliases
#define Volts_TRIS                 TRISAbits.TRISA1
#define Volts_LAT                  LATAbits.LATA1
#define Volts_PORT                 PORTAbits.RA1
#define Volts_WPU                  WPUAbits.WPUA1
#define Volts_OD                   ODCONAbits.ODCA1
#define Volts_ANS                  ANSELAbits.ANSELA1
#define Volts_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define Volts_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define Volts_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define Volts_GetValue()           PORTAbits.RA1
#define Volts_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define Volts_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define Volts_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define Volts_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define Volts_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define Volts_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define Volts_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define Volts_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set DispReset aliases
#define DispReset_TRIS                 TRISBbits.TRISB0
#define DispReset_LAT                  LATBbits.LATB0
#define DispReset_PORT                 PORTBbits.RB0
#define DispReset_WPU                  WPUBbits.WPUB0
#define DispReset_OD                   ODCONBbits.ODCB0
#define DispReset_ANS                  ANSELBbits.ANSELB0
#define DispReset_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define DispReset_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define DispReset_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define DispReset_GetValue()           PORTBbits.RB0
#define DispReset_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define DispReset_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define DispReset_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define DispReset_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define DispReset_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define DispReset_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define DispReset_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define DispReset_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSELB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set BTN_UP aliases
#define BTN_UP_TRIS                 TRISBbits.TRISB3
#define BTN_UP_LAT                  LATBbits.LATB3
#define BTN_UP_PORT                 PORTBbits.RB3
#define BTN_UP_WPU                  WPUBbits.WPUB3
#define BTN_UP_OD                   ODCONBbits.ODCB3
#define BTN_UP_ANS                  ANSELBbits.ANSELB3
#define BTN_UP_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define BTN_UP_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define BTN_UP_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define BTN_UP_GetValue()           PORTBbits.RB3
#define BTN_UP_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define BTN_UP_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define BTN_UP_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define BTN_UP_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define BTN_UP_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define BTN_UP_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define BTN_UP_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define BTN_UP_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set BTN_ENTER aliases
#define BTN_ENTER_TRIS                 TRISBbits.TRISB4
#define BTN_ENTER_LAT                  LATBbits.LATB4
#define BTN_ENTER_PORT                 PORTBbits.RB4
#define BTN_ENTER_WPU                  WPUBbits.WPUB4
#define BTN_ENTER_OD                   ODCONBbits.ODCB4
#define BTN_ENTER_ANS                  ANSELBbits.ANSELB4
#define BTN_ENTER_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define BTN_ENTER_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define BTN_ENTER_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define BTN_ENTER_GetValue()           PORTBbits.RB4
#define BTN_ENTER_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define BTN_ENTER_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define BTN_ENTER_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define BTN_ENTER_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define BTN_ENTER_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define BTN_ENTER_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define BTN_ENTER_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define BTN_ENTER_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set BTN_DOWN aliases
#define BTN_DOWN_TRIS                 TRISBbits.TRISB5
#define BTN_DOWN_LAT                  LATBbits.LATB5
#define BTN_DOWN_PORT                 PORTBbits.RB5
#define BTN_DOWN_WPU                  WPUBbits.WPUB5
#define BTN_DOWN_OD                   ODCONBbits.ODCB5
#define BTN_DOWN_ANS                  ANSELBbits.ANSELB5
#define BTN_DOWN_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define BTN_DOWN_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define BTN_DOWN_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define BTN_DOWN_GetValue()           PORTBbits.RB5
#define BTN_DOWN_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define BTN_DOWN_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define BTN_DOWN_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define BTN_DOWN_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define BTN_DOWN_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define BTN_DOWN_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define BTN_DOWN_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define BTN_DOWN_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set BTN_DOWN aliases
#define DISP_SEL_TRIS                 TRISAbits.TRISA6
#define DISP_SEL_LAT                  LATAbits.LATA6
#define DISP_SEL_PORT                 PORTAbits.RA6
#define DISP_SEL_WPU                  WPUAbits.WPUA6
#define DISP_SEL_OD                   ODCONAbits.ODCA6
#define DISP_SEL_ANS                  ANSELAbits.ANSELA6
#define DISP_SEL_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define DISP_SEL_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define DISP_SEL_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define DISP_SEL_GetValue()           PORTAbits.RA6
#define DISP_SEL_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define DISP_SEL_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define DISP_SEL_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define DISP_SEL_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define DISP_SEL_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define DISP_SEL_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define DISP_SEL_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define DISP_SEL_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set DispA0 aliases
#define DispA0_TRIS                 TRISCbits.TRISC6
#define DispA0_LAT                  LATCbits.LATC6
#define DispA0_PORT                 PORTCbits.RC6
#define DispA0_WPU                  WPUCbits.WPUC6
#define DispA0_OD                   ODCONCbits.ODCC6
#define DispA0_ANS                  ANSELCbits.ANSELC6
#define DispA0_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define DispA0_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define DispA0_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define DispA0_GetValue()           PORTCbits.RC6
#define DispA0_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define DispA0_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define DispA0_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define DispA0_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define DispA0_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define DispA0_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define DispA0_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define DispA0_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set DispCS aliases
#define DispCS_TRIS                 TRISCbits.TRISC7
#define DispCS_LAT                  LATCbits.LATC7
#define DispCS_PORT                 PORTCbits.RC7
#define DispCS_WPU                  WPUCbits.WPUC7
#define DispCS_OD                   ODCONCbits.ODCC7
#define DispCS_ANS                  ANSELCbits.ANSELC7
#define DispCS_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define DispCS_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define DispCS_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define DispCS_GetValue()           PORTCbits.RC7
#define DispCS_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define DispCS_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define DispCS_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define DispCS_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define DispCS_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define DispCS_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define DispCS_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define DispCS_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set DispBKLT aliases
#define DispBKLT_TRIS                 TRISAbits.TRISA7
#define DispBKLT_LAT                  LATAbits.LATA7
#define DispBKLT_PORT                 PORTAbits.RA7
#define DispBKLT_WPU                  WPUAbits.WPUA7
#define DispBKLT_OD                   ODCONDbits.ODCA7
#define DispBKLT_ANS                  ANSELAbits.ANSELA7
#define DispBKLT_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define DispBKLT_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define DispBKLT_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define DispBKLT_GetValue()           PORTAbits.RA7
#define DispBKLT_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define DispBKLT_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define DispBKLT_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define DispBKLT_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define DispBKLT_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define DispBKLT_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define DispBKLT_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define DispBKLT_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set PiezoEnable aliases
#define PiezoEnable_TRIS                 TRISCbits.TRISC0
#define PiezoEnable_LAT                  LATCbits.LATC0
#define PiezoEnable_PORT                 PORTCbits.RC0
#define PiezoEnable_WPU                  WPUCbits.WPUC0
#define PiezoEnable_OD                   ODCONCbits.ODCC0
#define PiezoEnable_ANS                  ANSELCbits.ANSELC0
#define PiezoEnable_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define PiezoEnable_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define PiezoEnable_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define PiezoEnable_GetValue()           PORTCbits.RC0
#define PiezoEnable_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define PiezoEnable_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define PiezoEnable_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define PiezoEnable_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define PiezoEnable_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define PiezoEnable_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define PiezoEnable_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define PiezoEnable_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set V5Enable aliases
#define V5Enable_TRIS                 TRISCbits.TRISC1
#define V5Enable_LAT                  LATCbits.LATC1
#define V5Enable_PORT                 PORTCbits.RC1
#define V5Enable_WPU                  WPUCbits.WPUC1
#define V5Enable_OD                   ODCONCbits.ODCC1
#define V5Enable_ANS                  ANSELCbits.ANSELC1
#define V5Enable_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define V5Enable_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define V5Enable_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define V5Enable_GetValue()           PORTCbits.RC1
#define V5Enable_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define V5Enable_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define V5Enable_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define V5Enable_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define V5Enable_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define V5Enable_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define V5Enable_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define V5Enable_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set FlashCS aliases
#define FlashCS_TRIS                 TRISCbits.TRISC2
#define FlashCS_LAT                  LATCbits.LATC2
#define FlashCS_PORT                 PORTCbits.RC2
#define FlashCS_WPU                  WPUCbits.WPUC2
#define FlashCS_OD                   ODCONCbits.ODCC2
#define FlashCS_ANS                  ANSELCbits.ANSELC2
#define FlashCS_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define FlashCS_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define FlashCS_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define FlashCS_GetValue()           PORTCbits.RC2
#define FlashCS_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define FlashCS_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define FlashCS_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define FlashCS_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define FlashCS_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define FlashCS_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define FlashCS_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define FlashCS_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set LED1 aliases
#define LED1_TRIS                 TRISEbits.TRISE1
#define LED1_LAT                  LATEbits.LATE1
#define LED1_PORT                 PORTEbits.RE1
#define LED1_WPU                  WPUEbits.WPUE1
#define LED1_OD                   ODCONEbits.ODCE1
#define LED1_ANS                  ANSELEbits.ANSELE1
#define LED1_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define LED1_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define LED1_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define LED1_GetValue()           PORTEbits.RE1
#define LED1_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define LED1_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define LED1_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define LED1_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define LED1_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define LED1_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define LED1_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS                 TRISEbits.TRISE2
#define LED2_LAT                  LATEbits.LATE2
#define LED2_PORT                 PORTEbits.RE2
#define LED2_WPU                  WPUEbits.WPUE2
#define LED2_OD                   ODCONEbits.ODCE2
#define LED2_ANS                  ANSELEbits.ANSELE2
#define LED2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define LED2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define LED2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define LED2_GetValue()           PORTEbits.RE2
#define LED2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define LED2_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define LED2_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define LED2_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define LED2_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define LED2_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define LED2_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

#endif
/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF3 pin functionality
 * @Example
    IOCBF3_ISR();
 */
void IOCBF3_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF3 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF3 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF3 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF3_SetInterruptHandler() method.
    This handler is called every time the IOCBF3 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(IOCBF3_InterruptHandler);

*/
extern void (*IOCBF3_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF3 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF3_SetInterruptHandler() method.
    This handler is called every time the IOCBF3 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(IOCBF3_DefaultInterruptHandler);

*/
void IOCBF3_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF4 pin functionality
 * @Example
    IOCBF4_ISR();
 */
void IOCBF4_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF4 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF4 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF4_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF4 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF4_SetInterruptHandler() method.
    This handler is called every time the IOCBF4 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(IOCBF4_InterruptHandler);

*/
extern void (*IOCBF4_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF4 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF4_SetInterruptHandler() method.
    This handler is called every time the IOCBF4 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(IOCBF4_DefaultInterruptHandler);

*/
void IOCBF4_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF5 pin functionality
 * @Example
    IOCBF5_ISR();
 */
void IOCBF5_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF5 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF5 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF5_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF5_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF5 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF5_SetInterruptHandler() method.
    This handler is called every time the IOCBF5 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF5_SetInterruptHandler(IOCBF5_InterruptHandler);

*/
extern void (*IOCBF5_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF5 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF5_SetInterruptHandler() method.
    This handler is called every time the IOCBF5 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF5_SetInterruptHandler(IOCBF5_DefaultInterruptHandler);

*/
void IOCBF5_DefaultInterruptHandler(void);

void IOC_InterruptHandler(void);


#endif // PIN_MANAGER_H
/**
 End of File
*/