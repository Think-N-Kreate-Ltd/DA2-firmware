/*
 * File:   RTCC.c
 * Author: kharris
 *
 * Created on March 1, 2023, 10:04 AM
 */


#include <xc.h>
#include <math.h>
#include "RTCC.h"
#include "delays.h"
#include "mcc_generated_files/i2c2_master.h"

extern TTIME ttime;

//................................................................................................
// The below function initializes the I2C RTCC (MCP7941x series))
// initialization of the I2C RTCC: enables the battery circuit
// START bit is located in the Sec register, local variable (stores the RTCC DAY register)
//RTCC chip defaults to 2001/1/1 0:0:0 at first power up
//................................................................................................
 void Init_I2C1_rtcc(void){                       
                                 
    unsigned char r1,r2,r3,wkday,count;
        
    count=0;
    while(count<10)
    {
        r1 = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_WKDAY)  ;  // read DAY OF WEEK
        delay_us(10);
        r2 = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_WKDAY)  ;  // read DAY OF WEEK
        delay_us(10);
        r3 = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_WKDAY)  ;  // read DAY OF WEEK
        delay_us(10);
        if((r1 == r2)&&(r1==r3)) 
        {
            wkday = r1;
            count = 20;
        }
        else count++;
    }
        
    //Reset time if first time startup    
    if((wkday&OSCON) == 0)    //if(yr < 0x19)
    {
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_YEAR,0x24);        // initialize YEAR  register : (20)19
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_MNTH,0x01);   	    // initialize MONTH register : Jan
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_DATE,0x01);   	    // initialize DATE  register : date = 01
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_HOUR,0x00);   	    // initialize HOUR  register : hour = 00, set to 24 hour clock
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_MIN,0x00) ;   	    // initialize MIN   register : min  = 00
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_WKDAY,VBATEN);       // enable the battery back-up
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_CTRL,0x04);          //Disable output pin, disable alarms, enable ext crystal
        
        // NHAN: enable MFP output to debug crystal
        // require 10K pull up on MFP pin
//        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_CTRL,0x04 | SQWE| MFP_01H);    // enable output pin at 1Hz, disable alarms, enable ext crystal                                
        
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_SEC,START_32KHZ);    //set seconds to zero and start oscillator
    }
//    else {
//        __debug_break();
//        // here means OSC is running
//    }
   
}
//................................................................................................
void SetTime(void)
{
    uint8_t tsec,tmin,thr,tday,tmon,tyr,ttmp;
    uint16_t tmp;
    int N,N1,N2,N3,tdrift,dadjust,negdrift;
    float ftemp, currentTime, dratio;

    //Save current clock time
    GetTime();
    //Find day of the year
    N1 = (int) floor(275 * ttime.month / 9);
    N2 = (int) floor((ttime.month + 9) / 12);
    N3 = (int) (1 + floor((ttime.year - 4 * floor(ttime.year / 4) + 2) / 3));
    N = N1 - (N2 * N3) + ttime.day - 30;
    currentTime = (float)(ttime.second + (ttime.minute*60) + (ttime.hour*3600) + (N*86400) + ((ttime.year-2020)*31536000));
    
    //Find day of the year and save new desired time
    N1 = (int) floor(275 * ttime.s_month / 9);
    N2 = (int) floor((ttime.s_month + 9) / 12);
    N3 = (int) (1 + floor((ttime.s_year - 4 * floor(ttime.s_year / 4) + 2) / 3));
    N = N1 - (N2 * N3) + ttime.s_day - 30;
    ttime.newTimeSet = (float)(ttime.s_second + (ttime.s_minute*60) + (ttime.s_hour*3600) + (N*86400) + ((ttime.s_year-2020)*31536000));
    
    //Setting time requires an input string YYYY,MM,DD,hh,mm,ss
    if(ttime.s_year < 2000) ttime.s_year += 2000;   //Assume that user just entered a two digit year
    
    /*First disable the RTCC oscillator by writing zero to the seconds*/
    I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_SEC,0x00);             // STOP Oscillator in RTCC
    tmp = ttime.s_year - 2000;
    ttmp = (uint8_t) tmp/10;
    tmp = tmp - (ttmp*10);
    ttmp *= 16;
    tyr = ttmp + (uint8_t) tmp;
    I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_YEAR,tyr);             // update YEAR    value in RTCC

    if(ttime.s_month > 0 && ttime.s_month <= 12)
    {
        tmp = ttime.s_month;
        ttmp = (uint8_t) ttime.s_month/10;
        tmp = tmp - (ttmp*10);
        ttmp *= 16;
        tmon = ttmp + (uint8_t)tmp;
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_MNTH,tmon);            // update MONTH   value in RTCC
    }
    
    if(ttime.s_day > 0 && ttime.s_day < 32)
    {
        tmp = ttime.s_day;
        ttmp = (uint8_t) ttime.s_day/10;
        tmp = tmp - (ttmp*10);
        ttmp *= 16;
        tday = ttmp + (uint8_t)tmp;
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_DATE,tday);            // update DATE    value in RTCC
    }

    ttime.shadj_debug = ttime.sadj_hour;

    if(ttime.s_am) 
    {
        if(ttime.sadj_hour == 12) ttime.s_hour = 0;
        else ttime.s_hour = ttime.sadj_hour;
    }
    else //pm 
    {
        if(ttime.sadj_hour != 12) ttime.s_hour = ttime.sadj_hour + 12;
        else ttime.s_hour = ttime.sadj_hour;
    }

    ttime.sh_debug = ttime.s_hour;

    if(ttime.s_hour <= 23)
    {
        tmp = (uint8_t) ttime.s_hour;
        ttmp = (uint8_t) ttime.s_hour/10;
        tmp = tmp - (ttmp*10);
        ttmp *= 16;
        thr = ttmp + (uint8_t)tmp;
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_HOUR,thr & HOUR_24);  // update HOUR    value in RTCC
    }
    
    if(ttime.s_minute <= 60)
    {
        tmp = ttime.s_minute;
        ttmp = (uint8_t) ttime.s_minute/10;
        tmp = tmp - (ttmp*10);
        ttmp *= 16;
        tmin = ttmp + (uint8_t)tmp;
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_MIN,tmin);             // update MINUTES value in RTCC
    }
    I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_WKDAY,VBATEN);      // enable the battery back-up
    
    if(ttime.s_second <= 60)
    {
        tmp = ttime.s_second;
        ttmp = (uint8_t) ttime.s_second/10;
        tmp = tmp - (ttmp*10);
        ttmp *= 16;
        tsec = ttmp + (uint8_t)tmp;
        tsec = tsec | START_32KHZ;              // restore oscillator START bit
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_SEC,tsec);    // update SECONDS value in RTCC
    }
    else
    {
        tmp = 0;
        ttmp = (uint8_t) ttime.s_second/10;
        tmp = tmp - (ttmp*10);
        ttmp *= 16;
        tsec = ttmp + (uint8_t)tmp;
        tsec = tsec | START_32KHZ;              // restore oscillator START bit
        I2C2_Write1ByteRegister(ADDR_RTCC,ADDR_SEC,tsec);    // update SECONDS value in RTCC        
    }

#ifdef ADJUST_DRIFT
    if(ttime.lastTimeSet != 0)      //We adjust the clock drift if enough time has elapsed
    {
        ftemp = ttime.newTimeSet - ttime.lastTimeSet;
        if(ftemp > 600000)  //We need drift over at lease a week
        {
            tdrift = (int)(currentTime - ttime.newTimeSet);
            if(tdrift > 10.0)                            //adjust if drift is greater than 10 seconds
            {
                negdrift = 0;
                dratio = tdrift/ftemp;                  //clock drift in seconds per second;
                if(dratio < 0) 
                {
                    negdrift = 1;
                    dratio = dratio * -1.0;
                }
                dadjust = (int)((dratio * 32768) * 60);        //clock counts to adjust per minute
                if(dadjust > 128) dadjust = 128;                //maximum adjust
                if(negdrift == 0)
                {
                    I2C1_write(ADDR_RTCC,ADDR_OSCTRIM,dadjust);
                    ttime.driftAjd = dadjust;
                }
                else
                {
                    I2C1_write(ADDR_RTCC,ADDR_OSCTRIM,(0x80 | dadjust));
                    ttime.driftAjd = dadjust * -1;
                }
                ttime.lastTimeSet = ttime.newTimeSet;
            }
        }
    }
    else ttime.lastTimeSet = ttime.newTimeSet;  
    
    mstate.newSetupData=true;
    mstate.writefile = true;
#endif    
    
}
//Read RTCC and put date and time into proper variables
void GetTime(void)
{
    uint8_t yr,mon,day,hr,min,sec,tsec,tmon,tday,thr;
    int syear,tmp;
    uint8_t smon,smday,shour,smin,ssec;

    yr  = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_YEAR)  ;  // read YEAR
    mon = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_MNTH)  ;  // read MONTH
    day = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_DATE)  ;  // read DATE
    hr  = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_HOUR)  ;  // read HOUR
    min = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_MIN)   ;  // read MIN
    sec = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_SEC)   ;  // read SEC
    
    // NHAN: add code to verify OSC running during debug
    uint8_t wk_day = I2C2_Read1ByteRegister(ADDR_RTCC,ADDR_WKDAY);
    if((wk_day & OSCON) == 0) {  // OSCON bit is 5th bit in RTCWKDAY register
        __debug_break();
        // here means the OSC is running normally
    }
    
  
    tmp = yr / 16;
    syear = tmp * 10;
    tmp = yr - (tmp * 16);
    syear += tmp;
    ttime.year = (unsigned int) syear + 2000;

    tmon = mon & 0x1F;
    tmp = tmon / 16;
    smon = (uint8_t)tmp * 10;
    tmp = tmon - ((uint8_t)tmp * 16);
    ttime.month = smon + (uint8_t)tmp;

    tday = day & 0x3F;
    tmp = tday / 16;
    smday = (uint8_t)tmp * 10;
    tmp = tday - (tmp * 16);
    ttime.day = smday + (uint8_t)tmp;

    thr = hr & 0x3F;
    tmp = thr / 16;
    shour = (uint8_t)tmp * 10;
    tmp = thr - (tmp * 16);
    ttime.hour = shour + (uint8_t)tmp;
    
    ttime.h_debug = ttime.hour;
    if(ttime.hour > 12)
    {
        ttime.hour -= 12;
        ttime.am = 0;
    }
    else if(ttime.hour == 0)
    {
        ttime.hour = 1;
        ttime.am = 1;        
    }
    else ttime.am = 1;
    
 
    tmp = min / 16;
    smin = (uint8_t)tmp * 10;
    tmp = min - ((uint8_t)tmp * 16);
    ttime.minute = smin + (uint8_t)tmp;

    tsec = sec & 0x7F;
    tmp = tsec / 16;
    ssec = (uint8_t)tmp * 10;
    tmp = tsec - ((uint8_t)tmp * 16);
    ttime.second = ssec + (uint8_t)tmp;
    return;
}
void GetSerial(void)
{
    unsigned char ii;
    uint8_t eui;
    
    eui = I2C2_Read1ByteRegister(ADDR_EEPROM_READ,ADDR_EEPROM_EUI);
    if(eui == 0xFF)
    {
        for(ii=0;ii<8;ii++)
        {
            ttime.EUIbytes[ii] = 0;
        }
    }
    else
    {
        for(ii=0;ii<8;ii++)
        {
            ttime.EUIbytes[ii] = I2C2_Read1ByteRegister(ADDR_EEPROM_READ,ADDR_EEPROM_EUI+ii);
        }
    }
    return;
}

