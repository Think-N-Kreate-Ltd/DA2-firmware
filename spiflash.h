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
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SPIFLASH_HEADER
#define	SPIFLASH_HEADER

#include <xc.h> // include processor files - each processor file is guarded.

/*******************************************************************/
/******** ADDRESSES for EEPROM IC***********************************/
/*******************************************************************/ 
#define EEPROM_ADDR_HIGH    0x00        //Highest 8 bits of address
#define EEPROM_ADDR_MID     0x00        //Middle 8 bit of address
#define EEPROM_ADDR_LOW     0x00        //Final 8 bit of address (used for sector erase)
#define EEPROM_ADDR_HISTORY 0x10        //Middle 8 bit of address. 16 sectors in for storing history data
#define EEPROM_ADDR_DATA    0x01        //Location of first data byte
#define WREN_EEPROM         0x06        //Write Enable
#define WRDI_EEPROM         0x04        //Write disable
#define BYTE_PROG_EEPROM    0x02        //Byte method program
#define AAI_PROG_EEPROM     0xAF        //Auto incremeting write mode
#define READ_EEPROM         0x03        //Read Command
#define SECTOR_ERASE_EEPROM 0x20        //Sector Erase Command
#define BLOCK_ERASE_EEPROM  0x52        //Block Erase Command
#define READ_ID_EEPROM      0x90        //Read memory ID, should return 0xBF,0x48
#define READ_STATUS_EEPROM  0x05        //Read status register
#define WRITE_STATUS_EEPROM 0x01        //Write status register
#define WRITE_STATUS_EN_EEPROM 0x50     //Write status enable to write to status register
#define SPI_ZERO            0x00        //Part of receiving data
#define FIRST_WRITE_DATA    0xAA        //Indicates that data has been written to the eeprom and that we should use the eeprom data

#define ALARMOKAY   0
#define ALARMLOW    1
#define ALARMHIGH   2

typedef struct  
{
    uint8_t   firstwrite;         //If this is anything other than FIRST_WRITE then we need to setup the eeprom    
    uint8_t   date[8];
    uint8_t   time[6];
    int16_t   pressure;
    uint8_t   alarm;              //0=okay, 1=low, 2=high
    
} EEPROMALARM;

/*SPI EEPROM routines*/
void Write_EEPROM_data(void);
void Read_EEPROM_data(void);
void EraseHistory(int number);          //Deletes EEPROM data. Requires a password.

#endif	/* XC_HEADER_TEMPLATE_H */

