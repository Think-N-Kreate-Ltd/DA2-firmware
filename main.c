/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18LF46K40
        Driver Version    :  2.00
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

/* 
 * TIMERS DESCRIPTIONS: 
 * 
 * Timer0   Buttons debouncing 
 * Timer1   Set 100ms and 1s flags
 * Timer2   Check timeout after HP or LP is acknowledged using any buttons
 * Timer3   Generate delay_us() and delay_ms()
 */

#include <string.h>
#include "main.h"
#include "mcc_generated_files/mcc.h"
#include "delays.h"
#include "RTCC.h"
#include "ERM12864-8.h"
#include "ERM12864-7.h"
#include "display.h"
#include "spiflash.h"

TTIME ttime;

uint8_t lastAlarm; //Number of last alarm written
uint8_t verified; //Part of calibration routine
uint8_t verify = 0; //Part of calibration routine

uint16_t displayCount = 0;
uint16_t displayAlarmCount = 0;

// NHAN: for debugging


enum ALARMSTATE {
    AlarmOKAY, AlarmLOW, AlarmHIGH
} alarmState;

/*
                         Main application
 */
void main(void) {
    
    uint8_t ii,jj;
    unsigned char outstring[100];   

    // Initialize the device
    SYSTEM_Initialize();
    
    Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
        
    SPI1_Open(SPI1_DEFAULT);

    Init_I2C1_rtcc();
    V5Enable_SetHigh();     //Enable display and sensor power
    DispInit();
    DispBKLT_SetHigh();  
    Display_Clear();
    displayVersion();    
    delay_ms(1000);   // wait some time to read the version
    ii=0;
    jj=0;
    Display_Clear();
    GetAnalog();  
    
    if(!DISP_SEL_GetValue()) 
    {
        initina2();
        //Display26Picture(pic1);
        Display26PictureClear();
        //Write26_test();
//        Write26_test3();
    }

    WWDT_SoftEnable();      //Enable watchdog timer

    while (1)
    {           
        WWDT_TimerClear();
        ScanPB();
        if(mstate.buttonPressed) 
        {
            HandlePB();
            displayCount = 0;
            displayAlarmCount = 0;
            mstate.buttonPressed = 0;
        }
        if(mstate.sleepMode)
        {
            sleep();
            GetAnalog();            
            if(!mstate.lowBattery)  // only check alarm when battery is not low
            {
                CheckAlarms();
                if((alarmState != AlarmOKAY) && !mstate.alarmSilence && !mstate.alarmLongSilence)
                {
                    __debug_break();
                    wake();
                }
                else
                {
                    secondTimer();
                }
            }
            else
            {
                // Here when low battery, do 3 quick chirps, then continue to sleep
                lowBattSound();
                __debug_break();
            }

            continue;              
        }
        if(stime.hundredMSflag)
        {
            stime.hundredMSflag = false;
            if(mstate.updateDisplay) 
            {
                UpdateDisplay();
                mstate.updateDisplay = 0;
            }

            if(!mstate.lowBattery)  // only check alarm when battery is not low
            {
                if(mstate.alarmHigh || mstate.alarmLow) soundAlarm();
                else PiezoEnable_SetLow();
            }            
        }
        if(stime.oneSecondFlag)
        {
            stime.oneSecondFlag = false;
            GetAnalog();
            if(!mstate.lowBattery)  // only check alarm when battery is not low
            {
                CheckAlarms();                
//                if(mstate.alarmHigh || mstate.alarmLow) mstate.displayActive = 1;
                secondTimer();
            }
            else
            {
                // Here when low battery, enable sleep mode and clear display                
                mstate.displayActive = 0;
                mstate.sleepMode = 1;
                mstate.displayClear = 1;
                UpdateDisplay();
            }            
        }
    }
}

void Initialize(void) {
    uint8_t addlow, addhigh;

    mstate.updateDisplay = 0;

    ttime.s_year = 2024;
    ttime.s_month = 1;
    ttime.s_day = 1;
    ttime.sadj_hour = 1;
    ttime.s_minute = 1;
    ttime.s_second = 1;

    mstate.lowBattery = 0;  // initially battery level should be normal
    mstate.menuLevel = MAINLEVEL;
    mstate.menuLine = EXITMAIN;
    mstate.adjusting = 0;
    mstate.adjusted = 0;
    mstate.alarmHigh = 0;
    mstate.alarmLow = 0;
    mstate.alarmSilence = 0;
    mstate.shortSilenceTimeout = 0;
    mstate.alarmElapsedTime = 0;
    mstate.displayActive = 1;
    mstate.displayCounter = 0;
    mstate.downPressed = 0;
    mstate.upPressed = 0;
    mstate.menuPressed = 0;
    mstate.menuMode = 0;
    mstate.pastAlarm = 0;
    
    // NHAN: initialize state variables for buttons debouncing
    mstate.portBDebouncedState = PORTB;
    mstate.portBStateLast = mstate.portBDebouncedState;
    mstate.debouncedStateLast = mstate.portBDebouncedState;    // get the cached debounced port state

    analog.pressure = 0;

    ReadEESetup();
    if (eeconfig.firstwrite != FIRST_WRITE_EEDATA) //We are just setting up for the first time
    {
        eeconfig.POffset = 15;
        eeconfig.PSlope = 1.18;
        eeconfig.firstwrite = FIRST_WRITE_EEDATA;
        eeconfig.AlarmHigh = 80;
        eeconfig.AlarmLow = 0;      // Chang from 40 -> 0. See Bug ID 43       
        SaveEESetup();

        // NHAN: initially, alarm history should be empty
        // Here we just save a normal event data as the 1st alarm, this will be required when checking "LAST ALARM"
        lastAlarm = 0;
        uint16_t alarmAddress = ALARM_BASE_ADDRESS + (lastAlarm * ALARM_SIZE);            
        alarm.alarm = AlarmOKAY;
        alarm.year = 24;
        alarm.month = 1;
        alarm.day = 1;
        alarm.hour = 0;
        alarm.min = 0;
        alarm.sec = 0;
        alarm.am = 1;             
        WriteAlarmEE(alarmAddress);
        
        // NHAN: update `lastAlarm` index, which is saved at `ALARM_TOTAL_ADDRESS`
        DATAEE_WriteByte(ALARM_TOTAL_ADDRESS, lastAlarm);
        
        // Initialize Max and Min pressure data
        maxPressure.year = 24;
        maxPressure.month = 1;
        maxPressure.day = 1;
        maxPressure.hour = 0;
        maxPressure.min = 0;
        maxPressure.sec = 0;
        maxPressure.am = 1;
        maxPressure.pressure = PRESSURE_EMPTY;    // to indicate that data is empty
        WritePressureEventEE(EE_MAX_PRESSURE_ADDRESS);
        
        minPressure.year = 24;
        minPressure.month = 1;
        minPressure.day = 1;
        minPressure.hour = 0;
        minPressure.min = 0;
        minPressure.sec = 0;
        minPressure.am = 1;
        minPressure.pressure = PRESSURE_EMPTY;    // to indicate that data is empty
        WritePressureEventEE(EE_MIN_PRESSURE_ADDRESS);
    }

    //Load latest alarm location
    lastAlarm = DATAEE_ReadByte(ALARM_TOTAL_ADDRESS);
    
    // Load Max and Min pressure data from EE
    ReadPressureEventEE(EE_MAX_PRESSURE_ADDRESS);
    ReadPressureEventEE(EE_MIN_PRESSURE_ADDRESS);
}

uint16_t GetRefAnalog(void) {
    uint16_t result;

    V5Enable_SetHigh(); //Enable sensor power
    delay_ms(200);
    result = ADCC_GetSingleConversion(Pressure);
    analog.UnCalPressure = (int16_t) (result * PRESS_SCALE); //ftemp1 result is in PSI
    //if(!mstate.displayActive) V5Enable_SetLow();     //Enable sensor power
    return result;
}

void GetAnalog(void) {
    float ftemp1, ftemp2;
    int16_t itemp;

    V5Enable_SetHigh(); // Enable sensor power
    // We need to have some delay since:
    // 1. R1202 has soft-start time, typically 2ms
    // 2. Pressure transducer has response time (rise time).
    //    It's not clear what this value is. It's not available in the datasheet.
    //    Looking at oscilloscope shows that this might be 50 - 80ms
    // Also, during active mode, we don't have to delay every time, since power to sensor is always on.
    // Only in sleep mode, we need to apply enough delay to read correct value.
    // If we don't have enough delay during sleep, we may read the wrong value.
    if(!mstate.sleepMode) {
        delay_ms(5);
    }
    else {
        delay_ms(100);    
    }
    
    analog.rawPressure = ADCC_GetSingleConversion(Pressure);
    analog.rawVoltage = ADCC_GetSingleConversion(Volts);
    
    if(!mstate.displayActive)
    {
        V5Enable_SetLow();  // Turn off sensor power   
    }

    analog.battVolts = analog.rawVoltage * BAT_SCALE;
    // Update battery state based on current voltage and previous state    
    if((analog.battVolts < LOWBATTVOLTS) && !mstate.lowBattery)
    {
        mstate.lowBattery = 1;
        return;
    }
    else if((analog.battVolts > LOWBATTVOLTS_HYSTERESIS) && mstate.lowBattery)
    {
        mstate.lowBattery = 0;
    }   
    
    //Now do calibration
    itemp = (int16_t) analog.rawPressure - eeconfig.POffset;
    ftemp1 = (float) (itemp * PRESS_SCALE); //ftemp1 result is in PSI
    ftemp2 = ftemp1 * eeconfig.PSlope;
    ftemp2 += 0.5;
    analog.pressure = (int16_t) ftemp2;
    
    if(analog.pressure < 0)
    {
//        __debug_break();
        analog.pressure = 0;    // set to 0 to prevent beeping when device is not yet connected to water system. See Bug ID 43.
    }
}

// Check battery voltage to detect low battery

void GetBattVolts(void) {
    analog.rawVoltage = ADCC_GetSingleConversion(Volts);
    analog.battVolts = analog.rawVoltage * BAT_SCALE;
}

// Scan buttons and update their states
void ScanPB(void)
{  
    uint8_t portState = mstate.portBDebouncedState;
   
    // Since buttons are pulled LOW, we are only interested in rising edge, i.e. button is pressed
    uint8_t risingEdge = (portState ^ mstate.debouncedStateLast) & portState;
    
    // Now update individual button state
    if ((risingEdge & (1<<3)) != 0)   // RB3, i.e. BTN_UP
    {
        mstate.upPressed = 1;
        mstate.buttonPressed = 1;
    }
    if ((risingEdge & (1<<4)) != 0)   // RB4, i.e. BTN_ENTER
    {
        mstate.menuPressed = 1;
        mstate.buttonPressed = 1;
    }
    if ((risingEdge & (1<<5)) != 0)   // RB5, i.e. BTN_DOWN
    {
        mstate.downPressed = 1;
        mstate.buttonPressed = 1;
    }
    
    mstate.debouncedStateLast = portState; // save state for next time
}

void HandlePB(void) {
    if(mstate.buttonPressed && !mstate.displayActive)
    {
        mstate.displayActive = 1;
    }
    
    if (mstate.upPressed) {
        if ((mstate.alarmHigh || mstate.alarmLow) && (mstate.menuLevel == MAINLEVEL)) { // NHAN: when inside menu, not able to silence
//            if (mstate.alarmHigh || mstate.alarmLow) {
            alarmSilenceSet();          
        }
        /*    
                if(mstate.menuLevel == MAINLEVEL)
                {
                    if(upBTNTwice == 1) 
                    {
                        mstate.menuLevel = MENULEVEL;
                        mstate.menuLine = EXIT;
                        upBTNTwice = 0;
                        mstate.upPressed = 0;
                        mstate.upLong = 0;
                        upBTN = 0;
                    }
                    else upBTNTwice=1;
                    return;
                }
         */
        mstate.updateDisplay = 1;
        if (mstate.adjusting) {
            if (mstate.menuLevel == MENULEVEL) {
                switch (mstate.menuLine) {
                    case PAST:
                        if (mstate.pastAlarm < lastAlarm) mstate.pastAlarm++;
                        GetAlarmEE(mstate.pastAlarm);
                        break;
                    case HIGHTHRESH:
                        if (eeconfig.AlarmHigh < 150) eeconfig.AlarmHigh++;
                        break;
                    case LOWTHRESH:
                        if (eeconfig.AlarmLow < 150) eeconfig.AlarmLow++;
                        break;
                    case CAL_LOW:
                        verify = 0;
                        mstate.menuLine = EXITMAIN;
                        mstate.adjusting = 0;
                        break;
                    case CAL_HIGH:
                        if (verified == 0) {
                            verify = 0;
                            mstate.menuLine = EXITMAIN;
                        } else eeconfig.PSlope += SLOPESTEP;
                        break;
                    default:
                        break;
                }
            } else if (mstate.menuLevel == TIMELEVEL) {
                ttime.new_time = 1;
                switch (mstate.menuLine) {
                    case YEAR:
                        if (ttime.s_year < 3000) ttime.s_year++;
                        break;
                    case MONTH:
                        if (ttime.s_month < 11) ttime.s_month++;
                        else ttime.s_month = 1;
                        break;
                    case DAY:                        
                        if (ttime.s_day < 31) ttime.s_day++;
                        else ttime.s_day = 1;
                        break;
                    case HOUR:
                        if (ttime.sadj_hour == 11) {
                            if(!ttime.s_am) {  // 11PM -> 0AM, to avoid 12PM
                                ttime.sadj_hour = 0;
                                ttime.s_am = 1;
                            }
                            else {  // 11AM -> 12PM, to avoid 12AM
                                ttime.sadj_hour = 12;
                                ttime.s_am = 0;
                            }
                        } else if (ttime.sadj_hour == 12) ttime.sadj_hour = 1;  // 12PM -> 1PM
                        else ttime.sadj_hour++;
                        break;
                    case MINUTE:
                        if (ttime.s_minute < 59) ttime.s_minute++;
                        else ttime.s_minute = 0;
                        break;
                    case SECOND:
                        if (ttime.s_second < 59) ttime.s_second++;
                        else ttime.s_second = 0;
                        break;
                    default:
                        break;
                }
            }
        } else {
            mstate.menuLine--;
            if (mstate.menuLine == 0) {
                if (mstate.menuLevel == MENULEVEL) mstate.menuLine = LASTMENULINE;
                else mstate.menuLine = LASTTIMELINE;
            }
        }
        //mstate.upPressed = 0;
    }

    if (mstate.downPressed) {
        if ((mstate.alarmHigh || mstate.alarmLow) && (mstate.menuLevel == MAINLEVEL)) { // NHAN: when inside menu, not able to silence
//        if (mstate.alarmHigh || mstate.alarmLow) {
            alarmSilenceSet(); 
        }

        /*        
                if(mstate.menuLevel == MAINLEVEL)
                {
                    if(downBTNTwice == 1) 
                    {
                        mstate.menuLevel = MENULEVEL;
                        mstate.menuLine = EXIT;
                        downBTNTwice = 0;
                        mstate.downPressed=0;
                        mstate.downLong = 0;
                        mstate.downPressed = 0;
                        downBTN = 0;
                    }
                    else downBTNTwice=1;
                    return;
                }
         */
        mstate.updateDisplay = 1;
        if (mstate.adjusting) {
            if (mstate.menuLevel == MENULEVEL) {    // main menu, adjusting
                switch (mstate.menuLine) {
                    case PAST:
                        if (mstate.pastAlarm > 0) mstate.pastAlarm--;
                        GetAlarmEE(mstate.pastAlarm);
                        break;
                    case HIGHTHRESH:
                        if (eeconfig.AlarmHigh > 0) eeconfig.AlarmHigh--;
                        break;
                    case LOWTHRESH:
                        if (eeconfig.AlarmLow > 0) eeconfig.AlarmLow--;
                        break;
                    case CAL_LOW:
                        if (verified == 0) {
                            verified = 1;
                            verify = 0;
                        } else eeconfig.POffset = (int16_t) analog.rawPressure;
                        break;
                    case CAL_HIGH:
                        if (verified == 0) {
                            verified = 1;
                            verify = 0;
                        }
                        eeconfig.PSlope -= SLOPESTEP;
                        break;
                    default:
                        break;
                }
            } else if(mstate.menuLevel == TIMELEVEL) {  // time menu, adjusting
                ttime.new_time = 1;
                switch (mstate.menuLine) {
                    case YEAR:
                        if (ttime.s_year > 2023) ttime.s_year--;
                        break;
                    case MONTH:
                        if (ttime.s_month > 1) ttime.s_month--;
                        else ttime.s_month = 12;
                        break;
                    case DAY:
                        if (ttime.s_day > 1) ttime.s_day--;
                        else ttime.s_day = 31;
                        break;
                    case HOUR:
                        if (ttime.sadj_hour == 12) {
                            ttime.sadj_hour = 11;
                            if (ttime.s_am) ttime.s_am = 0;
                            else ttime.s_am = 1;
                        }
                        else if (ttime.sadj_hour == 1 && !ttime.s_am) {  // 1PM -> 12PM, to avoid 0PM
                            ttime.sadj_hour = 12; 
                         }                         
                        else if (ttime.sadj_hour == 0) {
                            ttime.sadj_hour = 11;
                            if(ttime.s_am) ttime.s_am = 0;
                            else ttime.s_am = 1;
                        }
                        else ttime.sadj_hour--;
                        break;
                    case MINUTE:
                        if (ttime.s_minute > 0) ttime.s_minute--;
                        else ttime.s_minute = 59;
                        break;
                    case SECOND:
                        if (ttime.s_second > 0) ttime.s_second--;
                        else ttime.s_second = 59;
                        break;
                    default:
                        break;
                }
            }
            else if(mstate.menuLevel == MAXMINLEVEL)  // Max Min menu, adjusting
            {
                switch(mstate.menuLine)
                {
                    case MAX_PRESSURE:
                        maxPressure.year = 24;
                        maxPressure.month = 1;
                        maxPressure.day = 1;
                        maxPressure.hour = 0;
                        maxPressure.min = 0;
                        maxPressure.sec = 0;
                        maxPressure.am = 1;
                        maxPressure.pressure = PRESSURE_EMPTY;    // to indicate that data is empty
                        WritePressureEventEE(EE_MAX_PRESSURE_ADDRESS);
                        mstate.adjusted = 1;
                        break;
                    case MIN_PRESSURE:
                        minPressure.year = 24;
                        minPressure.month = 1;
                        minPressure.day = 1;
                        minPressure.hour = 0;
                        minPressure.min = 0;
                        minPressure.sec = 0;
                        minPressure.am = 1;
                        minPressure.pressure = PRESSURE_EMPTY;    // to indicate that data is empty
                        WritePressureEventEE(EE_MIN_PRESSURE_ADDRESS);
                        mstate.adjusted = 1;
                        break;
                    default:
                        break;
                }
            }
        } else {
            mstate.menuLine++;
            if (mstate.menuLevel == MENULEVEL) {
                if (mstate.menuLine > LASTMENULINE) mstate.menuLine = 1;
            } else if (mstate.menuLevel == TIMELEVEL) {
                if (mstate.menuLine > LASTTIMELINE) mstate.menuLine = 1;
            }
            else if (mstate.menuLevel == MAXMINLEVEL) {
                if (mstate.menuLine > LASTMAXMINLINE) mstate.menuLine = 1;
            }
            else {
                // When having new menus, need to handle
                __debug_break();
            }
        }
        //mstate.downPressed = 0;
    }

    if (mstate.menuPressed) {
        /*        
                if(mstate.menuLevel == MAINLEVEL)
                {
                    if(enterBTNTwice == 1) 
                    {
                        mstate.menuLevel = MENULEVEL;
                        mstate.menuLine = EXIT;
                        enterBTNTwice = 0;
                        mstate.menuPressed=0;
                    }
                    else enterBTNTwice=1;
                    return;
                }
         */

        mstate.updateDisplay = 1;
        if ((mstate.alarmHigh || mstate.alarmLow) && (mstate.menuLevel == MAINLEVEL)) { // NHAN: when inside menu, not able to silence
//        if (mstate.alarmHigh || mstate.alarmLow) {
            alarmSilenceSet();
        }
        if (mstate.menuLevel == MAINLEVEL) {
            mstate.menuLevel = MENULEVEL;
            mstate.menuLine = EXITMAIN;
        } else if (mstate.adjusting) mstate.adjusting = 0;
        else //case not adjusting
        {
            if (mstate.menuLevel == MENULEVEL) {    // main menu, not adjusting
                switch (mstate.menuLine) {
                    case EXITMAIN:
                        mstate.menuLevel = MAINLEVEL;
                        mstate.menuMode = 0;
                        SaveEESetup();
                        break;
                    case PAST:
                        mstate.pastAlarm = lastAlarm;
                        mstate.adjusting = 1;
                        GetAlarmEE(mstate.pastAlarm);
                        break;
                    case HIGHTHRESH:
                    case LOWTHRESH:
                        mstate.adjusting = 1;
                        break;
                    case CAL_LOW:
                        if (verify == 1 || verified == 1) {
                            verify = 0;
                            verified = 0;
                            mstate.adjusting = 0;
                        } else {
                            verify = 1;
                            mstate.adjusting = 1;
                        }
                        break;
                    case CAL_HIGH:
                        if (verify == 1 || verified == 1) {
                            verify = 0;
                            verified = 0;
                            mstate.adjusting = 0;
                        } else {
                            verify = 1;
                            mstate.adjusting = 1;
                        }
                        break;
                    case CANCEL_12H:
//                        mstate.alarmSilence = 0;        // NHAN: also cancel previously silenced alarm
                        mstate.alarmLongSilence = 0;
                        PiezoEnable_SetHigh();
                        delay_ms(50);
                        PiezoEnable_SetLow();
                        break;
                    case TIME:
                        mstate.menuLevel = TIMELEVEL;
                        mstate.menuLine = EXITTIME;
                        GetTime();
                        ttime.s_year = ttime.year;
                        ttime.s_month = ttime.month;
                        ttime.s_day = ttime.day;
                        ttime.sadj_hour = ttime.hour;
                        ttime.s_am = ttime.am;
                        ttime.s_minute = ttime.minute;
                        ttime.s_second = ttime.second;
                        break;
                    case CLEAR:                        
                        mstate.adjusting = 1;
                        ClearAlarmEE();                                                
                        mstate.adjusted = 1;                        
                        break;
                    case MAX_MIN_PRESSURE:
                        mstate.menuLevel = MAXMINLEVEL;
                        mstate.menuLine = EXITMAXMIN;                        
                        ReadPressureEventEE(EE_MAX_PRESSURE_ADDRESS);
                        ReadPressureEventEE(EE_MIN_PRESSURE_ADDRESS);                        
                        break;
                    default:
                        break;
                }
            } else if(mstate.menuLevel == TIMELEVEL)    // Time menu, not adjusting
            {
                switch (mstate.menuLine) {
                    case EXITTIME:
                        mstate.menuLevel = MENULEVEL;
                        mstate.adjusting = 0;
                        if (ttime.new_time == 1) {
                            SetTime();
                            ttime.new_time = 0;
                        }
                        mstate.menuLine = EXITMAIN;
                        break;
                    case YEAR:
                    case MONTH:
                    case DAY:
                    case HOUR:
                    case MINUTE:
                    case SECOND:
                        mstate.adjusting = 1;
                        break;
                    default:
                        break;
                }
            }
            else if(mstate.menuLevel == MAXMINLEVEL)    // Max Min menu, not adjusting
            {
                switch(mstate.menuLine)
                {
                    case EXITMAXMIN:
                        mstate.menuLevel = MENULEVEL;
                        mstate.adjusting = 0;
                        mstate.menuLine = EXITMAIN;
                        break;
                    case MAX_PRESSURE:
                    case MIN_PRESSURE:                    
                        mstate.adjusting = 1;
                        break;
                    case CLEAR_MAXMIN:
//                        __debug_break();
                        maxPressure.year = 24;
                        maxPressure.month = 1;
                        maxPressure.day = 1;
                        maxPressure.hour = 0;
                        maxPressure.min = 0;
                        maxPressure.sec = 0;
                        maxPressure.am = 1;
                        maxPressure.pressure = PRESSURE_EMPTY;    // to indicate that data is empty
                        WritePressureEventEE(EE_MAX_PRESSURE_ADDRESS);
                        minPressure.year = 24;
                        minPressure.month = 1;
                        minPressure.day = 1;
                        minPressure.hour = 0;
                        minPressure.min = 0;
                        minPressure.sec = 0;
                        minPressure.am = 1;
                        minPressure.pressure = PRESSURE_EMPTY;    // to indicate that data is empty
                        WritePressureEventEE(EE_MIN_PRESSURE_ADDRESS);
                        mstate.adjusted = 1;
                        break;
                    default:
                        break;                                                     
                }
            }
            else
            {
                // When having more menus, this should be handled
                __debug_break();
            }
        }
        //mstate.menuPressed = 0;
    }
    mstate.menuPressed = 0;
    mstate.downPressed = 0;
    mstate.upPressed = 0;

}

void UpdateDisplay(void) {
    char outstring[30];
    uint8_t ii, dispLine, startline, endline;
    static char alternate = 0;
    int itemp;
    unsigned int yy;
    static int16_t oldPressure;

    if (mstate.displayActive == 0) {
        if (mstate.displayClear == 1) {
            Display_Clear();
            mstate.displayClear = 0;
        }
        DispBKLT_SetLow();                   
        V5Enable_SetLow(); //Disable sensor power
        return;
    } else {
        V5Enable_SetHigh(); //Enable display and sensor power
        DispBKLT_SetHigh();          
    }
        
    Display_Clear();    
    
    // When it's low battery, only display the symbol, then return
    if(mstate.lowBattery)
    {
        WriteLowBattSymbol(3, 5);
        return;
    }

    switch (mstate.menuLevel) {
        case MAINLEVEL:
            if (oldPressure != analog.pressure) {
                //kh Display_Clear();
                oldPressure = analog.pressure;
            }

            if (!mstate.alarmHigh && !mstate.alarmLow) alternate = 0;
            if (alternate > 10) alternate = 0;

            if (alternate < 5) {
                // NHAN: increase current pressure font size
                if(analog.pressure >= 0)
                {
                    sprintf(outstring, "%3d", analog.pressure);
                    WriteLargeString(outstring, 1, 1);
                    // NHAN: show unit, PSI
                    sprintf(outstring, "PSI");
                    WriteSmallString(outstring, 4, 13, 0);
                }
                else
                {
                    // when pressure reading is < 0                    
                    sprintf(outstring, "PLEASE CALIB ZERO");
                    WriteSmallString(outstring, 4, 0, 0);
                }


#ifdef SHOWLOWBATTSYMBOL
                if (mstate.nearLowBattery) {                   
                    // NHAN: show low batt symbol
                    // This is to say battery is about to run out, not actual low level yet
                    WriteLowBattSymbol(1, 8);
                }
#endif

                if ((alarmState == AlarmHIGH) && !mstate.alarmSilence && !mstate.alarmLongSilence) {
                    sprintf(outstring, "PRESSURE: HIGH!!!");
                    WriteSmallString(outstring, 6, 0, 0);
                } else if ((alarmState == AlarmLOW) && !mstate.alarmSilence && !mstate.alarmLongSilence) {
                    sprintf(outstring, "PRESSURE: LOW!!!");
                    WriteSmallString(outstring, 6, 0, 0);
                }
                // NHAN: show "12H SLEEP MODE" when dual pressed
                else if (mstate.alarmLongSilence)
                {
                    sprintf(outstring, "12H SLEEP MODE");
                    WriteSmallString(outstring, 6, 0, 0);  
                }
//                else if (alarmState == AlarmHIGH) {
//                    if (mstate.alarmLongSilence) {
//                        sprintf(outstring, "12H SILENCED");
//                        WriteSmallString(outstring, 6, 0, 0);
//                    } else if (mstate.alarmSilence) {
//                        sprintf(outstring, "HIGH SILENCED");
//                        WriteSmallString(outstring, 6, 0, 0);
//                    }
//                } else if (alarmState == AlarmLOW) {
//                    if (mstate.alarmLongSilence) {
//                        sprintf(outstring, "12H SILENCED");
//                        WriteSmallString(outstring, 6, 0, 0);
//                    } else if (mstate.alarmSilence) {
//                        sprintf(outstring, "LOW SILENCED");
//                        WriteSmallString(outstring, 6, 0, 0);
//                    }
//                } 
                else {
                    //                    sprintf(outstring,"PRESSURE: OKAY");
                    //                    WriteSmallString(outstring, 5, 0,0);
                    
                    // NHAN: show silence symbol
                    if (mstate.alarmSilence) {
                        WriteSilenceSymbol(2, 0);
                        
                        // NHAN: start timing to cancel silence, i.e. reactivate alarm if it happens
                        // Basically, start Timer2
                        PIR4bits.TMR2IF = 0;  // clear Timer2 IF
                        TMR2_Start();
                    }
                    // NHAN:add LAST ALARM xx PSI @ 06:46AM 01/18/24                                                              
                    GetAlarmEE(lastAlarm);  // read last alarm event and save to `readAlarm` struct variable
                    if (readAlarm.alarm != AlarmOKAY)
                    {
                        sprintf(outstring, "LAST ALARM:%3d PSI", readAlarm.pressure);
                        WriteSmallString(outstring, 6, 0, 0);

                        if (readAlarm.am) { // AM
                            sprintf(outstring, "@ %02d/%02d/%02d %02d:%02dAM", readAlarm.month, readAlarm.day, readAlarm.year, readAlarm.hour, readAlarm.min);
                        } else { // PM
                            sprintf(outstring, "@ %02d/%02d/%02d %02d:%02dPM", readAlarm.month, readAlarm.day, readAlarm.year, readAlarm.hour, readAlarm.min);
                        }
                        WriteSmallString(outstring, 7, 0, 0);
                    }
                    else {
                        sprintf(outstring, "LAST ALARM: NO");
                        WriteSmallString(outstring, 6, 0, 0);
                    }
                }

                // Show date and time on top bar of display
                GetTime();

                //KRH Testing
                //sprintf(outstring,"%d %d",analog.rawVoltage,(int)(analog.battVolts*100));
                //WriteSmallString(outstring, 6, 0,0);
                //sprintf(outstring,"%d %d",(int)(eeconfig.POffset),(int)(eeconfig.PSlope*100));
                //WriteSmallString(outstring, 6, 0,0);
                //sprintf(outstring,"%d %d %d %d",eeconfig.RefHighCts,eeconfig.RefLowCts,eeconfig.RawHighCts,eeconfig.RawLowCts);
                //WriteSmallString(outstring, 7, 0,0);

                yy = ttime.year - 2000;   // NHAN: get last 2 digits of a given year (this only works for 20xx years)                
                if (ttime.am) sprintf(outstring, "%02d/%02d/%02d   %02d:%02dAM", ttime.month, ttime.day, yy, ttime.hour, ttime.minute);
                else sprintf(outstring, "%02d/%02d/%02d   %02d:%02dPM", ttime.month, ttime.day, yy, ttime.hour, ttime.minute);
                WriteSmallString(outstring, 0, 0, 0);

                alternate++;
            } else {  // NHAN: don't show silence instructions when 12h sleep activated
                if (!mstate.alarmSilence && !mstate.alarmLongSilence)
                {
                    sprintf(outstring, "PRESS ANY BUTTON");
                    WriteSmallString(outstring, 0, 0, 0);
                    sprintf(outstring, "TO SILENCE");
                    WriteSmallString(outstring, 1, 0, 0);

                    sprintf(outstring, "PRESS UP AND DOWN");
                    WriteSmallString(outstring, 3, 0, 0);
                    sprintf(outstring, "BUTTONS FOR 5 SEC");
                    WriteSmallString(outstring, 4, 0, 0);
                    sprintf(outstring, "TO SLEEP FOR");
                    WriteSmallString(outstring, 5, 0, 0);
                    sprintf(outstring, "12 HOURS");
                    WriteSmallString(outstring, 6, 0, 0);

                    alternate++;
                }
                else
                {
                    alternate = 0;                    
                }
                
            }
            break;
        case MENULEVEL:
            if (mstate.adjusting) {
                if (verify == 1) {
                    sprintf(outstring, "CHANGE");
                    WriteSmallString(outstring, 3, 0, 0);
                    sprintf(outstring, "CALIBRATION?");
                    WriteSmallString(outstring, 4, 0, 0);
                    sprintf(outstring, "PRESS DOWN: YES");
                    WriteSmallString(outstring, 5, 0, 0);
                } else {
                    switch (mstate.menuLine) {
                        case PAST: // i.e. "SAVE ALARMS" menu
                            if (lastAlarm > 0) {
                                sprintf(outstring, "       %02d/%02d/%02d", readAlarm.month, readAlarm.day, readAlarm.year);
                                WriteSmallString(outstring, 0, 0, 0);
                                if (readAlarm.am == 1) sprintf(outstring, "%02d     %02d:%02d AM", mstate.pastAlarm, readAlarm.hour, readAlarm.min);
                                else sprintf(outstring, "%02d     %02d:%02d PM", mstate.pastAlarm, readAlarm.hour, readAlarm.min);
                                WriteSmallString(outstring, 1, 0, 0);

                                sprintf(outstring, "%3d", readAlarm.pressure);
                                WriteLargeString(outstring, 3, 1);
                                sprintf(outstring, "PSI");
                                WriteSmallString(outstring, 4, 8, 0);

                                sprintf(outstring, "Alarm Status:");
                                WriteSmallString(outstring, 6, 0, 0);

                                switch (readAlarm.alarm) {
                                    case AlarmOKAY:
                                        sprintf(outstring, "Pressure Okay");
                                        break;
                                    case AlarmHIGH:
                                        sprintf(outstring, "Pressure High");
                                        break;
                                    case AlarmLOW:
                                        sprintf(outstring, "Pressure Low");
                                        break;
                                }
                                WriteSmallString(outstring, 7, 0, 0);
                            } else {
                                sprintf(outstring, "NO ALARMS SAVED");
                                WriteSmallString(outstring, 4, 0, 0);
                            }
                            break;
                        case HIGHTHRESH:
                            sprintf(outstring, "%s", MenuString[mstate.menuLine]);
                            WriteSmallString(outstring, 1, 0, 0);

                            // NHAN: increase font
                            sprintf(outstring, "%3d", eeconfig.AlarmHigh);
                            WriteLargeString(outstring, 3, 1);

                            // NHAN: show unit, PSI
                            sprintf(outstring, "PSI");
                            WriteSmallString(outstring, 6, 13, 0);
                            break;
                        case LOWTHRESH:
                            sprintf(outstring, "%s", MenuString[mstate.menuLine]);
                            WriteSmallString(outstring, 1, 0, 0);

                            // NHAN: increase font
                            sprintf(outstring, "%3d", eeconfig.AlarmLow);
                            WriteLargeString(outstring, 3, 1);

                            // NHAN: show unit, PSI
                            sprintf(outstring, "PSI");
                            WriteSmallString(outstring, 6, 13, 0);
                            break;
                        case CAL_LOW:
                            GetRefAnalog();
                            sprintf(outstring, "%s", MenuString[mstate.menuLine]);
                            WriteSmallString(outstring, 2, 0, 0);
                            sprintf(outstring, "Cal:%03d", analog.pressure);
                            WriteSmallString(outstring, 3, 0, 0);
                            sprintf(outstring, "SET ZERO?");
                            WriteSmallString(outstring, 5, 0, 0);
                            sprintf(outstring, "DOWN:YES UP:EXIT");
                            WriteSmallString(outstring, 6, 0, 0);
                            break;
                        case CAL_HIGH:
                            GetRefAnalog();
                            sprintf(outstring, "%s", MenuString[mstate.menuLine]);
                            WriteSmallString(outstring, 2, 0, 0);
                            sprintf(outstring, "PSI: %d", analog.pressure);
                            WriteSmallString(outstring, 4, 0, 0);
                            sprintf(outstring, "SLOPE: %5.2f", eeconfig.PSlope);
                            WriteSmallString(outstring, 6, 0, 0);
                            break;
                        case CLEAR:                            
                            if(mstate.adjusted) {        
                                if(!DisplayMessage("CLEAR SUCCESS", 4, 2)) {                               
                                    mstate.adjusted = 0;
                                    mstate.adjusting = 0;
                                    mstate.menuLine = EXITMAIN;   
                                }                                
                            }
                            
                            break;
                        default:
                            break;
                    }
                }
            } else {
                // TODO: after adjusting high pressure threshold, show the confirmation here

                itemp = mstate.menuLine - 4;
                if (itemp < 0) itemp = 0;
                startline = (uint8_t) itemp;
                endline = startline + 7;
                if (endline > MAXMENUSTRING) endline = MAXMENUSTRING;
                for (ii = startline; ii < endline; ii++) {
                    dispLine = (uint8_t) (ii - startline + 1);
                    if (ii == mstate.menuLine)
                        WriteSmallString(MenuString[ii], dispLine, 0, 1);
                    else
                        WriteSmallString(MenuString[ii], dispLine, 0, 0);
                }
            }
            break;
        case TIMELEVEL:
            if (mstate.adjusting) {
                switch (mstate.menuLine) {
                    case YEAR:
                        sprintf(outstring, "%s", TimeString[mstate.menuLine]);
                        WriteSmallString(outstring, 1, 7, 0);
                        sprintf(outstring, "%4d", ttime.s_year);
                        WriteLargeString(outstring, 3, 1);
                        break;
                    case MONTH:
                        sprintf(outstring, "%s", TimeString[mstate.menuLine]);
                        WriteSmallString(outstring, 1, 7, 0);
                        sprintf(outstring, "%2d", ttime.s_month);
                        WriteLargeString(outstring, 3, 2);
                        break;
                    case DAY:
                        sprintf(outstring, "%s", TimeString[mstate.menuLine]);
                        WriteSmallString(outstring, 1, 7, 0);
                        sprintf(outstring, "%2d", ttime.s_day);
                        WriteLargeString(outstring, 3, 2);
                        break;
                    case HOUR:
                        sprintf(outstring, "%s", TimeString[mstate.menuLine]);
                        WriteSmallString(outstring, 1, 7, 0);
                        sprintf(outstring, "%2d", ttime.sadj_hour);
                        WriteLargeString(outstring, 3, 2);
                        if (ttime.s_am) {
                            sprintf(outstring, "AM");
                            WriteSmallString(outstring, 6, 12, 0);
                        }
                        else {
                            sprintf(outstring, "PM");
                            WriteSmallString(outstring, 6, 12, 0);
                        }
                        //KRH Testing
                        //sprintf(outstring,"%02d %02d %02d %d,%d",ttime.h_debug,ttime.sadj_hour,ttime.sh_debug,ttime.am,ttime.s_am);
                        //WriteSmallString(outstring, 6, 5,0);
                        break;
                    case MINUTE:
                        sprintf(outstring, "%s", TimeString[mstate.menuLine]);
                        WriteSmallString(outstring, 1, 7, 0);
                        sprintf(outstring, "%2d", ttime.s_minute);
                        WriteLargeString(outstring, 3, 2);
                        break;
                    case SECOND:
                        sprintf(outstring, "%s", TimeString[mstate.menuLine]);
                        WriteSmallString(outstring, 1, 7, 0);
                        sprintf(outstring, "%2d", ttime.s_second);
                        WriteLargeString(outstring, 3, 2);
                        break;
                    default:
                        break;
                }

            } else {
                for (ii = 1; ii < MAXTIMESTRING; ii++) {
                    if (ii == mstate.menuLine)
                        WriteSmallString(TimeString[ii], ii, 0, 1);
                    else
                        WriteSmallString(TimeString[ii], ii, 0, 0);
                }
                
                // NHAN: add symbol to indicate that we're in "SET TIME" menu
                Write15Bitmap(V_testBitmap, 40, 40, 1, 75);
            }
            break;
        case MAXMINLEVEL:
            if(mstate.adjusted) {                
                if(!DisplayMessage("CLEAR SUCCESS", 4, 2)) {                               
                    mstate.adjusted = 0;
                    mstate.adjusting = 0;
                    mstate.menuLine = EXITMAXMIN;
                }  
            }
            else if(mstate.adjusting) {
                switch(mstate.menuLine) {
                    case MAX_PRESSURE:
                        // Instructions
                        sprintf(outstring, "ENT:BACK ]:RESET");                        
                        WriteSmallString(outstring, 0, 0, 0); 

                        // Max pressure
                        sprintf(outstring, "MAX");
                        WriteSmallString(outstring, 2, 0, 0);
                        if(maxPressure.pressure >= 0) {
                            sprintf(outstring, "%3d", maxPressure.pressure);
                        }
                        else {
                            // data is empty, write "---"
                            sprintf(outstring, "---");
                        }                        
                        WriteLargeString(outstring, 2, 1);
                        sprintf(outstring, "PSI");
                        WriteSmallString(outstring, 5, 13, 0);
                        if (maxPressure.am) { // AM
                            sprintf(outstring, "@ %02d/%02d/%02d %02d:%02dAM", maxPressure.month, maxPressure.day, maxPressure.year, maxPressure.hour, maxPressure.min);
                        } else { // PM
                            sprintf(outstring, "@ %02d/%02d/%02d %02d:%02dPM", maxPressure.month, maxPressure.day, maxPressure.year, maxPressure.hour, maxPressure.min);
                        }
                        WriteSmallString(outstring, 7, 0, 0);                           
                        break;
                    case MIN_PRESSURE:
                        // Instructions
                        sprintf(outstring, "ENT:BACK ]:RESET");
                        WriteSmallString(outstring, 0, 0, 0); 

                        // Max pressure
                        sprintf(outstring, "MIN");
                        WriteSmallString(outstring, 2, 0, 0);
                        if(minPressure.pressure >= 0) {
                            sprintf(outstring, "%3d", minPressure.pressure);
                        }
                        else {
                            // data is empty, write "---"
                            sprintf(outstring, "---");
                        }                        
                        WriteLargeString(outstring, 2, 1);
                        sprintf(outstring, "PSI");
                        WriteSmallString(outstring, 5, 13, 0);
                        if (minPressure.am) { // AM
                            sprintf(outstring, "@ %02d/%02d/%02d %02d:%02dAM", minPressure.month, minPressure.day, minPressure.year, minPressure.hour, minPressure.min);
                        } else { // PM
                            sprintf(outstring, "@ %02d/%02d/%02d %02d:%02dPM", minPressure.month, minPressure.day, minPressure.year, minPressure.hour, minPressure.min);
                        }
                        WriteSmallString(outstring, 7, 0, 0);                              
                        break;
                    default:
                        break;
                }
            }
            else {
                for (ii = 1; ii < MAXMAXMINSTRING; ii++) {
                    if (ii == mstate.menuLine)
                        WriteSmallString(MaxMinString[ii], ii, 0, 1);
                    else
                        WriteSmallString(MaxMinString[ii], ii, 0, 0);
                }
            }
            break;
        default:
            break;
    }
}

void SaveEESetup(void) {
    uint16_t len;
    uint16_t eeaddress;
    void *ptr;
    uint8_t *data;

    ptr = &eeconfig;
    data = ptr;
    len = sizeof (eeconfig);

    eeaddress = 0x0000;

    while (len--) { //Now write the data
        DATAEE_WriteByte(eeaddress++, *data++);
    }
}

// NHAN: This function reads configuration data saved in EEPROM
// to `eeconfig` struct variable.
// Configuration is saved starting from address 0x0000
void ReadEESetup(void) {
    uint16_t len;
    uint16_t eeaddress;
    void *ptr;
    uint8_t *data;

    ptr = &eeconfig;
    data = ptr;
    len = sizeof (eeconfig);
    eeaddress = 0x0000;

    while (len--)
        *data++ = DATAEE_ReadByte(eeaddress++);
}

/* Set alarm data fields and save them */
void SaveAlarm(uint8_t alarmType)
{
    uint16_t alarmAddress;
    
    if(alarmType == AlarmHIGH)
    {
        alarm.alarm = AlarmHIGH;
    }
    else if(alarmType == AlarmLOW)
    {
        alarm.alarm = AlarmLOW;
    }
    else
    {
        __debug_break();
        // AlarmOKAY here, nothing to do
    }
    
    GetTime();
    alarm.year = (uint8_t) (ttime.year - 2000);
    alarm.month = ttime.month;
    alarm.day = ttime.day;
    alarm.pressure = analog.pressure;
    alarm.hour = (uint8_t) ttime.hour;
    alarm.min = ttime.minute;
    alarm.sec = ttime.second;
    alarm.am = ttime.am;
    
    lastAlarm++;
    alarmAddress = ALARM_BASE_ADDRESS + (lastAlarm * ALARM_SIZE);
    // Override alarm at the base memory location of EEPROM
    if ((lastAlarm > MAX_EE_ALARMS) || (alarmAddress > MAX_ADDRESS))
    {
        lastAlarm = 0;                      // Wrap around on index
        alarmAddress = ALARM_BASE_ADDRESS;  // Wrap around on memory    
    }

    // Write new alarm and update its index
    WriteAlarmEE(alarmAddress);
    DATAEE_WriteByte(ALARM_TOTAL_ADDRESS, lastAlarm);
}

/* Write configured alarm to EEPROM */
void WriteAlarmEE(uint16_t add) {
    uint16_t len;
    uint16_t eeaddress;
    void *ptr;
    uint8_t *data;

    ptr = &alarm;
    data = ptr;
    len = sizeof (alarm);

    eeaddress = add;

    while (len--) { //Now write the data
        DATAEE_WriteByte(eeaddress++, *data++);
    }
}

/* Read saved alarm from EEPROM */
void ReadAlarmEE(uint16_t add) {
    uint16_t len;
    uint16_t eeaddress;
    void *ptr;
    uint8_t *data;

    ptr = &readAlarm;
    data = ptr;
    len = sizeof (readAlarm);
    eeaddress = add;

    while (len--)
        *data++ = DATAEE_ReadByte(eeaddress++);
}

/* Write configured pressure event to EEPROM */
// Used to write Max and Min pressure events,
// but could be used for other types of event in the future.
void WritePressureEventEE(uint16_t add) {
    uint16_t len;
    uint16_t eeaddress;
    void *ptr;
    uint8_t *data;

    if(add == EE_MAX_PRESSURE_ADDRESS){
        ptr = &maxPressure;
        len = sizeof(maxPressure);
    }
    else if(add == EE_MIN_PRESSURE_ADDRESS){
        ptr = &minPressure;
        len = sizeof(minPressure);
    }
    else{
        __debug_break();
        // Not handle yet
    }
    
    data = ptr;
    
    eeaddress = add;

    while (len--) { //Now write the data
        DATAEE_WriteByte(eeaddress++, *data++);
    }
}

/* Read saved pressure event from EEPROM */
// Used to retrieve Max and Min pressure events,
// but could be used for other types of event in the future.
void ReadPressureEventEE(uint16_t add) {
    uint16_t len;
    uint16_t eeaddress;
    void *ptr;
    uint8_t *data;
    
    if(add == EE_MAX_PRESSURE_ADDRESS){
        ptr = &maxPressure;
        len = sizeof(maxPressure);
    }
    else if(add == EE_MIN_PRESSURE_ADDRESS){
        ptr = &minPressure;
        len = sizeof(minPressure);
    }
    else{
        __debug_break();
        // Not handle yet
    }
    
    data = ptr;
    eeaddress = add;

    while (len--)
        *data++ = DATAEE_ReadByte(eeaddress++);
}

void CheckAlarms(void) {
    // TODO: disable LED flashing to further reduce sleep current
    // LED1 blinks to indicate that we are checking alarm
    LED1_SetHigh();
    delay_ms(50);
    LED1_SetLow();
    
    static uint8_t lasthigh = 0;
    static uint8_t lastlow = 0;
    bool pressureIsHigh = (analog.pressure > eeconfig.AlarmHigh);
    bool pressureIsLow = (analog.pressure < eeconfig.AlarmLow);

    if(( pressureIsHigh || pressureIsLow)  &&
        (!mstate.alarmSilence && !mstate.alarmLongSilence))
    {
        // Here pressure is out of limit, update elapsed time.
        // Note that during sleep mode, this function is called about every 4s
        if (mstate.sleepMode)
        {
            mstate.alarmElapsedTime += 4;
        }
        else    // normal mode
        {
            mstate.alarmElapsedTime += 1;
        }
                
        if(pressureIsHigh)  // When pressure is High
        {
            if (lasthigh == 1) {
                if ((alarmState != AlarmHIGH) || mstate.shortSilenceTimeout) {                               
                    // If elapsed time exceeds the timeout, activate the alarm and write to EE
                    if (mstate.alarmElapsedTime > ALARM_ACTIVATE_TIMEOUT)
                    {
                        __debug_break();
                        lasthigh = 0;                    
                        mstate.alarmHigh = 1;
                        alarmState = AlarmHIGH;

                        mstate.shortSilenceTimeout = 0;
                        SaveAlarm(alarmState);
                    }
                    else
                    {
                        // Not handled yet
                    }                
                }
                else
                {
                    // Not handled yet
                }
            } else lasthigh = 1;
        }
        else if(pressureIsLow)  // When pressure is Low
        {
            if (lastlow == 1) {
            if (alarmState != AlarmLOW || mstate.shortSilenceTimeout) {
                // If elapsed time exceeds the timeout, activate the alarm and write to EE
                if (mstate.alarmElapsedTime > ALARM_ACTIVATE_TIMEOUT)
                {
                    __debug_break();
                    lastlow = 0;                    
                    mstate.alarmLow = 1;
                    alarmState = AlarmLOW;

                    mstate.shortSilenceTimeout = 0;
                    SaveAlarm(alarmState);
                }
                else
                {
                    // Not handled yet
                }                
            }
            else
            {
                // Not handled yet
            }            
            } else lastlow = 1;
        }
        else
        {
            __debug_break();
            // Should never jump here
        }        
    }
    else {
        if (alarmState != AlarmOKAY) {
            __debug_break();
            lasthigh = 0;
            lastlow = 0;
        }
        else
        {
            // Not handled yet
        }
        
        // NHAN: here should be normal
        alarmState = AlarmOKAY;
        mstate.alarmElapsedTime = 0;
    }
    
    // Check if new Max/Min pressure value is recorded
    if((analog.pressure > maxPressure.pressure) || (maxPressure.pressure == PRESSURE_EMPTY)) {        
        __debug_break();
        GetTime();
        maxPressure.year = (uint8_t) (ttime.year - 2000);
        maxPressure.month = ttime.month;
        maxPressure.day = ttime.day;        
        maxPressure.hour = (uint8_t) ttime.hour;
        maxPressure.min = ttime.minute;
        maxPressure.sec = ttime.second;
        maxPressure.am = ttime.am;
        maxPressure.pressure = analog.pressure;
        WritePressureEventEE(EE_MAX_PRESSURE_ADDRESS);
    }
    else if((analog.pressure < minPressure.pressure) || (minPressure.pressure == PRESSURE_EMPTY)) {
        __debug_break();
        GetTime();
        minPressure.year = (uint8_t) (ttime.year - 2000);
        minPressure.month = ttime.month;
        minPressure.day = ttime.day;        
        minPressure.hour = (uint8_t) ttime.hour;
        minPressure.min = ttime.minute;
        minPressure.sec = ttime.second;
        minPressure.am = ttime.am;
        minPressure.pressure = analog.pressure;
        WritePressureEventEE(EE_MIN_PRESSURE_ADDRESS);
    }
    else {
        // Current pressure is within Max and Min,
        // no need to override
    }
}

/* Get saved alarm using index EEPROM */
void GetAlarmEE(uint8_t num) {
    uint16_t alarmAddress;

    if (num <= lastAlarm) alarmAddress = ALARM_BASE_ADDRESS + (num * ALARM_SIZE);
    // NHAN: what to do here?
    else alarmAddress = ALARM_BASE_ADDRESS + (lastAlarm * ALARM_SIZE);

    ReadAlarmEE(alarmAddress);
}

/* Delete saved alarms from EEPROM */
void ClearAlarmEE(void) {
    // TODO: below only change the index to the base alarm address,
    // it's not deleting anything. Need to properly delete the alarms here!!!
    lastAlarm = 0;
    DATAEE_WriteByte(ALARM_TOTAL_ADDRESS, lastAlarm);
}

void sleep(void) {
    DispBKLT_SetLow(); //Turn off backlight
    V5Enable_SetLow(); //Disable sensor power
    PiezoEnable_SetLow(); //disable piezo power


    // NHAN: test to reduce current consumption of display during sleep:
    //    DispCS_SetHigh();
    DispCS_SetLow();
    DispReset_SetLow();
    DispA0_SetLow();

    // To further reduce power consumption, check the operations in wake()


    FlashCS_SetHigh();

    SPI1_Close();
    TMR1_StopTimer();
    TMR2_StopTimer();
    INTERRUPT_GlobalInterruptDisable();
    //INTERRUPT_PeripheralInterruptEnable();
//    VREGCONbits.VREGPM = 1; //Low current voltage regulator mode; NHAN: PIC18LF46K40 doesn't have this register
    
    // NHAN: disable Timer0, wakeup using IOC
    TMR0_StopTimer();
//    PIR0bits.TMR0IF = 0;    // clear Timer0 interrupt flag
//    PIE0bits.TMR0IE = 0;    // Disable Timer0 interrupt
//    T0CON0bits.T0EN = 0;    // Stop Timer0
    
    IOCBFbits.IOCBF3 = 0;
    IOCBFbits.IOCBF4 = 0;
    IOCBFbits.IOCBF5 = 0;
    PIR0bits.IOCIF = 0; // Clear IOC flag;
    PIE0bits.IOCIE = 1; // Enable IOC interrupts.
    CPUDOZEbits.IDLEN = 0; //deep sleep
    SLEEP();
    WWDT_TimerClear();
    delay_ms(100);  // TODO: why delay here?
    if (PIR0bits.IOCIF == 1) {
        PIR0bits.IOCIF = 0;
//        __debug_break();
        wake();
    }
}

void wake(void) {    
    WWDT_TimerClear();
//    IOCBFbits.IOCBF3 = 0;
//    IOCBFbits.IOCBF4 = 0;
//    IOCBFbits.IOCBF5 = 0;
//    PIR0bits.IOCIF = 0;
    TMR1_StartTimer();
    SPI1_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    //INTERRUPT_PeripheralInterruptEnable();
    V5Enable_SetHigh(); //Enable display and sensor power
    mstate.sleepMode = 0;
    mstate.displayActive = 1;
    mstate.menuLevel = MAINLEVEL;
    SPI1_Open(SPI1_DEFAULT);
    delay_ms(10);   // TODO: check why delay here
    DispInit();
    UpdateDisplay();
}

void soundAlarm(void) //In case of an alarm, this routine is called every 100ms
{
    static uint8_t batPeriod;
    static uint8_t batDuty;
    static uint8_t highDuty;
    static uint8_t lowPeriod;
    static uint8_t lowDuty;
    
//    if (mstate.lowBattery) {
//        batPeriod++;
//        if (batPeriod < 50) {
//            batDuty++;
//            if (batDuty < 2) {
//                PiezoEnable_SetHigh();
//            } else if (batDuty < 4) {
//                PiezoEnable_SetLow();
//            } else if (batDuty < 6) {
//                PiezoEnable_SetHigh();
//            } else if (batDuty < 8) {
//                PiezoEnable_SetLow();
//            } else if (batDuty < 10) {
//                PiezoEnable_SetHigh();
//            } else PiezoEnable_SetLow();
//        } else {
//            batPeriod = 0;
//            batDuty = 0;
//        }
//    }   // End of low battery alarm
//    else
//    {
    if (mstate.alarmSilence || mstate.alarmLongSilence) {
        PiezoEnable_SetLow();
    }
    else {
        if (mstate.alarmHigh == 1) {
            highDuty++;
            if (highDuty < 5) {
                PiezoEnable_SetHigh();
            } else if (highDuty < 9) {
                PiezoEnable_SetLow();
            } else highDuty = 0;
        }   // End of HP alarm 
        else if (mstate.alarmLow == 1) {
            lowPeriod++;
            if (lowPeriod < 30) {
                lowDuty++;
                if (lowDuty < 3) {
                    PiezoEnable_SetHigh();
                } else if (lowDuty < 6) {
                    PiezoEnable_SetLow();
                } else if (lowDuty < 10) {
                    PiezoEnable_SetHigh();
                } else PiezoEnable_SetLow();
            } else {
                lowPeriod = 0;
                lowDuty = 0;
            }
        }   // End of LP alarm
    }
//    }
}

void secondTimer(void) {
    static uint8_t dualPressButton = 0;
    static uint16_t longSleepCount = 0;
         
    if (mstate.sleepMode) //If in sleep mode, this gets called every 4.096 seconds
    {
        displayCount += 4;
        displayAlarmCount += 4;
        if (BTN_DOWN_GetValue() && BTN_UP_GetValue()) dualPressButton += 4;
        else dualPressButton = 0;

        if (mstate.alarmLongSilence) longSleepCount += 4;
    } else {
        displayCount++;
        displayAlarmCount++;
        if (BTN_DOWN_GetValue() && BTN_UP_GetValue()) dualPressButton++;
        else dualPressButton = 0;
        if (mstate.alarmLongSilence) longSleepCount++;
    }

    if (dualPressButton > 5) {
        // NHAN: 12 hour sleep confirmed
        buzzer12hSilence();
        mstate.alarmLongSilence = 1;
        longSleepCount = 0;
        dualPressButton = 0;  // NHAN: reset to avoid continuous buzzer
    }

    if (longSleepCount > CLEARLONGSILENT) mstate.alarmLongSilence = 0;

    // NHAN: sleep even at menu screens. See Bug ID 16
    //    if(mstate.menuLevel != MAINLEVEL) displayCount = 0; //If in menu mode don't go to sleep

    if (displayCount > DISPLAYTIMEOUT) {        
        mstate.displayActive = 0;
        mstate.sleepMode = 1;
        mstate.displayClear = 1;
        UpdateDisplay();
    }
    if (mstate.alarmHigh || mstate.alarmLow) {
        if ((displayAlarmCount > ALARMDISPTIMEOUT) && mstate.displayActive) {
            mstate.displayActive = 0;
            mstate.displayClear = 1;
            UpdateDisplay();
        }
        if (!mstate.alarmSilence && !mstate.alarmLongSilence) mstate.sleepMode = 0; //If alarm and not silenced then don't sleep
    } else displayAlarmCount = 0;

    if (mstate.displayActive == 0) displayCount = 0;
    
    // NHAN: check battery voltage, show low battery symbol when reaching voltage
#ifdef SHOWLOWBATTSYMBOL
    if (analog.battVolts < NEARLOWBATTVOLTS) mstate.nearLowBattery = 1;
    else mstate.nearLowBattery = 0;
#endif
    mstate.updateDisplay = 1;
}

// NHAN: 6 quick chirps to indicate 12h sleep mode
void buzzer12hSilence(void)
{
    PiezoEnable_SetHigh();
    delay_ms(50);
    PiezoEnable_SetLow();
    delay_ms(50);
    PiezoEnable_SetHigh();
    delay_ms(50);
    PiezoEnable_SetLow();
    delay_ms(50);
    PiezoEnable_SetHigh();
    delay_ms(50);
    PiezoEnable_SetLow();
    delay_ms(50);
    PiezoEnable_SetHigh();
    delay_ms(50);
    PiezoEnable_SetLow();
    delay_ms(50);
    PiezoEnable_SetHigh();
    delay_ms(50);
    PiezoEnable_SetLow();
    delay_ms(50);
    PiezoEnable_SetHigh();
    delay_ms(50);
    PiezoEnable_SetLow();
}

/* Display firmware version when device is powered on */
void displayVersion(void)
{
    char outstring[30];
    sprintf(outstring, "Firmware: %s", FIRMWARE_VERSION_STRING);
    WriteSmallString(outstring, 4, 0, 0);        
}

// When alarm is silenced, i.e. press any button during alarm event, set corresponding state variables
void alarmSilenceSet(void)
{
    mstate.alarmSilence = 1;
    mstate.alarmHigh = 0;
    mstate.alarmLow = 0;
}

// 3 quick chirps to indicate low battery
void lowBattSound(void)
{                
    PiezoEnable_SetHigh();
    delay_ms(50);
    PiezoEnable_SetLow();
    delay_ms(50);
    PiezoEnable_SetHigh();
    delay_ms(50);
    PiezoEnable_SetLow();
    delay_ms(50);
    PiezoEnable_SetHigh();
    delay_ms(50);
    PiezoEnable_SetLow(); 
}

/* Display a message with hold time, in seconds */
// Example use case: when we want to display confirmation message
bool DisplayMessage(char *msg, uint8_t line, uint8_t column) {
    static uint8_t holdTime = DISPLAY_MESSAGE_HOLDTIME;
    WriteSmallString(msg, line, column, 0);
    holdTime--;

    if(holdTime == 0) {
        holdTime = DISPLAY_MESSAGE_HOLDTIME;
        return false;
    }
    else {
        return true;
    }    
}

/**
 End of File
 */