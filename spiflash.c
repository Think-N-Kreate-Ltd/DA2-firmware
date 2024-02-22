/*
 * File:   flash.c
 * Author: kharris
 *
 * Created on March 8, 2023, 7:38 PM
 */
#include <xc.h>
#include "spiflash.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/pin_manager.h"
#include "delays.h"

extern EEPROMALARM eealarm;

void Write_EEPROM_data(void){
    unsigned int len;
    void *ptr;
    unsigned char *data;
    uint8_t addrLow,addrMid,addrHigh;
    
    ptr = &eealarm;
    len = sizeof(eealarm);
    addrMid = EEPROM_ADDR_MID;

    data = ptr;
    addrHigh = EEPROM_ADDR_HIGH;
    addrLow = EEPROM_ADDR_LOW;
    
    //First we set the write status to allow writes to EEPROM
    FlashCS_SetLow();
    SPI1_ExchangeByte(WRITE_STATUS_EN_EEPROM);
    FlashCS_SetHigh();
    delay_us(2);
    FlashCS_SetLow();
    SPI1_ExchangeByte(WRITE_STATUS_EEPROM);
    SPI1_ExchangeByte(0x00);
    FlashCS_SetHigh();
    delay_us(2);    
    FlashCS_SetLow();
    SPI1_ExchangeByte(WREN_EEPROM);
    FlashCS_SetHigh();
    delay_us(2);
    //Erase Sector prior to write
    FlashCS_SetLow();
    SPI1_ExchangeByte(SECTOR_ERASE_EEPROM);
    SPI1_ExchangeByte(addrHigh);
    SPI1_ExchangeByte(addrMid);
    SPI1_ExchangeByte(addrLow);
    FlashCS_SetHigh();
    delay_ms(30);
    addrLow = EEPROM_ADDR_DATA;
    while(len--){ //Now write the data
        FlashCS_SetLow();
        SPI1_ExchangeByte(WREN_EEPROM);
        FlashCS_SetHigh();
        delay_us(2);
        FlashCS_SetLow();
        SPI1_ExchangeByte(BYTE_PROG_EEPROM);
        SPI1_ExchangeByte(addrHigh);
        SPI1_ExchangeByte(addrMid);
        SPI1_ExchangeByte(addrLow);
        SPI1_ExchangeByte(*data++);
        FlashCS_SetHigh();
        if(addrLow == 0xFF){ //next address calculations
            addrLow = 0x00;
            if(addrMid == 0xFF){
                addrHigh++;
                addrMid = 0x00;
            }
            else addrMid++;
        }
        else addrLow++;
        delay_us(2);
    }    
    FlashCS_SetLow();
    SPI1_ExchangeByte(WRDI_EEPROM);
    FlashCS_SetHigh();
}
void EraseHistory(int number){             //This is a factory only function and requires a password
    if(number == 2000){    
        FlashCS_SetLow();    //First we set the write status to allow writes to EEPROM
        SPI1_ExchangeByte(WRITE_STATUS_EN_EEPROM);
        FlashCS_SetHigh();
        delay_us(2);
        FlashCS_SetLow();
        SPI1_ExchangeByte(WRITE_STATUS_EEPROM);
        SPI1_ExchangeByte(0x00);
        FlashCS_SetHigh();
        delay_us(2);    
        FlashCS_SetLow();
        SPI1_ExchangeByte(WREN_EEPROM);
        FlashCS_SetHigh();
        delay_us(2);
        //Erase Sector prior to write
        FlashCS_SetLow();
        SPI1_ExchangeByte(SECTOR_ERASE_EEPROM);
        SPI1_ExchangeByte(EEPROM_ADDR_HIGH);
        SPI1_ExchangeByte(EEPROM_ADDR_HISTORY);
        SPI1_ExchangeByte(EEPROM_ADDR_LOW);
        FlashCS_SetHigh();
        delay_ms(30);
        FlashCS_SetLow();
        SPI1_ExchangeByte(WRDI_EEPROM);
        FlashCS_SetHigh();
    }
}
/*Read data from EEPROM chip*/
void Read_EEPROM_data(void){
    unsigned int len;
    void *ptr;
    unsigned char *data;
    uint8_t addrLow,addrMid,addrHigh;

    ptr = &eealarm;
    len = sizeof(eealarm);
    addrMid = EEPROM_ADDR_MID;

    data = ptr;
    addrHigh = EEPROM_ADDR_HIGH;
    addrLow = EEPROM_ADDR_DATA;
    //Chip select
    FlashCS_SetLow();
    SPI1_ExchangeByte(READ_EEPROM);
    
    SPI1_ExchangeByte(addrHigh);
    SPI1_ExchangeByte(addrMid);
    SPI1_ExchangeByte(addrLow);
    while(len--)
        *data++ = SPI1_ExchangeByte(SPI_ZERO);
    FlashCS_SetHigh(); 
}

