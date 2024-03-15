/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:  Don Alarm Dual Display 
 * Author: KRH
 * Comments:
 * Revision history: V0.2
 * 
 * 20230508 V0.1    Original created with MCC and code added to control two displays
 * 20300719 V0.2    Added code based on Don Alarm input
 * 20230810 V0.3    Added define in pin_manager.h to allow for use with older R0 boards for testing
 * 20230822 V0.4    Fix am/pm time
 * 20230824 V0.5    Add linear adjustment to pressure. Modify EE alarm recording
 * 20230927 V0.6    Tested and fixed pressure calibration
 * 20231005 V0.7    Modifications based on email from Nate
 * 20231013 V0.8    Changes per 20231012 email from Nate
 * 20231129 V0.9    Clear display when going to sleep mode
 * 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/mcc.h"

const char FIRMWARE_VERSION_STRING[] = "v1.4.0";   // NHAN: show firmware version on device power on

#define DAQ_SCALE   0.002       //10bits equals 2.048v (vref) and DAQ_SCALE = (2.048/1025) = 0.002 volts per count
#define BAT_SCALE   0.004       //Bat volts is 2x analog input of 500cnts/v -> cnts*0.004=bat volts
#define PRESS_SCALE 0.15        //Sensor 5v = 150PSI (30psi/v), Rdivider =0.4 -> sensor is 2.5x analog -> cnts *0.15 = PSI

#define DEF_PRESS_OFFSET 14.7
#define SLOPESTEP        0.01

#define LOWBATTVOLTS                2.75    // actual low battery level, only do 3 quick chirps
#define LOWBATTVOLTS_HYSTERESIS     2.8     // Use this to prevent oscilatting when Vbatt is fluctuating around `LOWBATTVOTLS`
//#define SHOWLOWBATTSYMBOL           // to show low battery symbol or not
#ifdef SHOWLOWBATTSYMBOL
#define NEARLOWBATTVOLTS    2.7  // show low battery symbol when reaching this voltage, a little above low battery level
#endif

//#define TESTINGTIMES
#ifdef TESTINGTIMES
#define DISPLAYTIMEOUT      3600        //in seconds. Display off after 60 minutes of inactivity
#define ALARMDISPTIMEOUT    3600        //Leave display on for 30 minutes after an alarm is triggered
#define CLEARSHORTSILENT    60          //Alarm sound back on after 1 minutes
#define CLEARLONGSILENT     600          //Alarm sound back on after 10 minutes
#else
#define DISPLAYTIMEOUT      60          // Display off after 1 minute of inactivity
#define ALARMDISPTIMEOUT    60          // Leave display on for 1 minute after an alarm is triggered    
#define CLEARSHORTSILENT    30          // Alarm sound back on after this number of seconds
#define CLEARLONGSILENT     43200       // Alarm sound back on after 12 hours
#define ALARM_ACTIVATE_TIMEOUT  3       // pressure has to be out of limits for this amount of seconds to activate
#endif

// NOTE: device configurations are saved starting from address 0x0000.
// Therefore, do not use memory address from 0x0000 - (eeconfig last byte address).
// Otherwise, new data will override the configurations.
#define FIRST_WRITE_EEDATA      0xAA    // Indicator that EE has been written after initial programming
#define ALARM_TOTAL_ADDRESS     0x0025  // EE address to save alarm index, i.e. `lastAlarm`
#define ALARM_BASE_ADDRESS      0x0030  // Alarm logging start address
#define ALARM_SIZE              10      // Alarms are 10 bytes in length
#define MAX_ADDRESS             0x1022  // EE memory range ends here
#define MAX_EE_ALARMS           90      // Maximum number of alarms to save. Start overwriting at the beginning.
// Let's say 90 alarm event to be saved.
// Starting address of the first event is 0x0030.
// Each alarm event is 10 bytes in length.
// => Next available address is: 0x0030 + [(90*10) to HEX, which is 384] = 0x03B4.
// Choose 0x03C4 as the address for the next data to be saved, which will leave some bytes between this data and the 90th alarm event.
#define EE_MAX_PRESSURE_ADDRESS 0x03C4  // EE address to save Max pressure event, 9 bytes in length
#define EE_MIN_PRESSURE_ADDRESS 0x03D4  // EE address to save Min pressure event, 9 bytes in length
#define PRESSURE_EMPTY          -1     // used to indicate pressure value is empty

//Menu Levels
#define MAINLEVEL   0
#define MENULEVEL   1
#define TIMELEVEL   2
#define MAXMINLEVEL 3

//MenuLevel
#define EXITMAIN    1
#define PAST        102 // 2
#define HIGHTHRESH  2
#define LOWTHRESH   3 // 3
#define CAL_LOW     4 // 4
#define CAL_HIGH    5 // 5
#define CANCEL_12H  6   // 6
#define TIME        7   // 7
#define CLEAR       108 // 8
#define MAX_MIN_PRESSURE 8  // capture max and min pressure, see Bug ID 28

#define LASTMENULINE 8

//Time Adust Level
#define EXITTIME    1
#define YEAR        2
#define MONTH       3
#define DAY         4
#define HOUR        5
#define MINUTE      6
#define SECOND      7

#define LASTTIMELINE    7      //Last menu item

// Max Min Level
#define EXITMAXMIN      1
#define MAX_PRESSURE    2
#define MIN_PRESSURE    3

#define LASTMAXMINLINE  3

static char * MenuString[] = 
{
    "                 ",
    "EXIT             ",
//    "SAVED ALARMS     ",
    "SET HI ALARM     ",
    "SET LO ALARM     ",
    "PRESSURE CAL ZERO",
    "PRESSURE CAL HIGH",
    "CANCEL 12H SLEEP ",
    "SET TIME         ",  
//    "CLEAR ALARM HIST "
    "MAX/MIN PRESSURE ",
};

#define MAXMENUSTRING 9 // 10

static char * TimeString[] = 
{
    "      ",
    "<BACK ",
    "YEAR  ",
    "MONTH ",
    "DAY   ",
    "HOUR  ",
    "MINUTE",
    "SECOND"
};

#define MAXTIMESTRING   8

static char * MaxMinString[] =
{
    "            ",
    "<BACK       ",
    "MAX PRESSURE",
    "MIN PRESSURE",
};

#define MAXMAXMINSTRING 4

struct STATETIME {
    uint32_t    timecount;            //basic 100 ms counter
    uint16_t    seconds;
    uint8_t     hundredMSflag;
    uint8_t     oneSecondFlag;
} stime;

struct EECONFIG
{
    uint8_t     firstwrite;         //If this is anything other than FIRST_WRITE then we need to setup the eeprom
    int16_t     POffset;
    float       PSlope;
    uint8_t     AlarmHigh;          //Threshold for high alarm
    uint8_t     AlarmLow;           //Threshold for low alarm    
}eeconfig;

struct EEPROMALARM
{
    uint8_t     year;
    uint8_t     month;
    uint8_t     day;
    uint8_t     hour;
    uint8_t     min;
    uint8_t     sec;
    uint8_t     am;
    int16_t     pressure;
    uint8_t     alarm;              //0=okay, 1=low, 2=high
    
} alarm,readAlarm;

struct EEPROM_MAXMINPRESSURE {
    uint8_t     year;
    uint8_t     month;
    uint8_t     day;
    uint8_t     hour;
    uint8_t     min;
    uint8_t     sec;
    uint8_t     am;
    int16_t     pressure;
} maxPressure, minPressure;

struct PRESSVOLTS {
    adc_result_t rawPressure;
    adc_result_t rawVoltage;
    int16_t pressure;
    int16_t UnCalPressure;
    double battVolts;
}analog;

struct MSTATE {
    uint8_t alarmHigh;        //High pressure alarm is active
    uint8_t alarmLow;         //Low pressure alarm is active
    uint8_t alarmSilence;     //Silence the piezo sound.
    uint8_t shortSilenceTimeout;    // use to check whether short silence is timeout or not
    uint8_t alarmLongSilence; //Silence the alarm for 12 hours
    uint16_t alarmElapsedTime;  // NHAN: used to record alarm elapsed time. It will be reset when user acknowledges, i.e. press any button during alarm event.
                                // Number of seconds since an out of limit pressure value is first detected
                                // This needs to be inside `CheckAlarms()` because we need to update the 
                                // elapsed time during both normal and sleep mode. `CheckAlarms()` is called
                                // in both normal and sleep mode.
    uint8_t sleepMode;        //wake and check pressure on watchdog timeout after sleep
    uint8_t lowBattery;
    uint8_t nearLowBattery;   // a little above low battery voltage
    uint8_t displayActive;    //Display turns off after x seconds of no activity
    uint8_t displayCounter;   //counter to track no activity
    uint8_t displayMenu;      //If display menu=1 then we show menu lines. Else show default screen
    uint16_t displayClear;
    uint8_t menuMode;
    uint8_t menuLine;
    uint8_t menuLevel;
    uint8_t upPressed;
    uint8_t menuPressed;
    uint8_t downPressed;
    uint8_t adjusting;
    uint8_t adjusted;       // to indicate that some action has been performed, e.g. reset Max/Min pressure
    uint8_t updateDisplay;
    uint8_t buttonPressed;
    uint8_t pastAlarm;
    uint8_t portBDebouncedState;    // debounced state
    uint8_t portBStateLast;         // last state
    uint8_t debouncedStateLast;
}mstate;

#define PORTB_IOC_MASK (0b00111000)  // RB3 (BTN_UP), RB4 (BTN_ENTER), RB5 (BTN_DOWN)

void Initialize(void);
void GetAnalog(void);
void GetBattVolts(void);
uint16_t GetRefAnalog(void);
void ScanPB(void);
void HandlePB(void);
void UpdateDisplay(void);
void SaveEESetup(void);
void ReadEESetup(void);
void SaveAlarm(uint8_t alarmType);
void WriteAlarmEE(uint16_t add);
void ReadAlarmEE(uint16_t add);
void WritePressureEventEE(uint16_t add);
void ReadPressureEventEE(uint16_t add);
void CheckAlarms(void);
void GetAlarmEE(uint8_t num);
void ClearAlarmEE(void);
void sleep(void);
void wake(void);
void soundAlarm(void);
void secondTimer(void);
void buzzer12hSilence(void);
void displayVersion(void);
void alarmSilenceSet(void);
void lowBattSound(void);
#endif	/* XC_HEADER_TEMPLATE_H */

