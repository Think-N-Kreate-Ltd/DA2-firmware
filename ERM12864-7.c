/*
 * File:   ERM12864-7.c
 * Author: kharris
 *
 * Created on February 27, 2023, 2:26 PM
 */

#include <xc.h>
#include "ERM12864-7.h"
#include "delays.h"
#include "mcc_generated_files/mcc.h"
#include <string.h>

void Write26SmallString(char *string, unsigned char line, unsigned char column, unsigned char underline)
{
    unsigned int size;
    unsigned char out, row, col;

    DispCS_SetHigh();

    row = line;
    if(row > 8) return;
    col = column;
    size = strlen(string);
    while(size)
    {
        out = *string - 32;
        //Write26_5x7(out,page,vert,underline);
        Write26_5x7(out,row,col,underline);
        string++;       // transmit next character on following loop
        if(col++ > 16)
        {
            col=0;
            if(row++ > 32)
            {
                row = 0;
            }            
        }
        size--;                     // loop until all characters sent (when size = 0)
    }
    DispCS_SetLow();

}
void Write26LargeString(char *string, unsigned char line, unsigned char column)
{
    int test;
    unsigned int size;
    unsigned char out, page, vert;

    DispCS_SetHigh();

    page = line;
    vert = column;
    size = strlen(string);
    while(size)
    {
        //First adjust ascii to be numbers only using a shortened 0-9 plus "." ascii table
        test = *string;
        if(test == 32) test = 11;
        else if(test == 46) test = 9;
        else 
        {
            test -=48;
            if(test < 0) test = 10;
            else if(test > 9) test = 10;
        }
        //Now send output
        out = (unsigned char) (test & 0xFF);
        Write26_16x24(out,page,vert);
        string++;                   // transmit next character on following loop
        if(vert++ > 10)
        {
            vert=0;
            if(page++ > 4)
            {
                page = 0;
            }            
        }
        size--;                     // loop until all characters sent (when size = 0)
    }
    DispCS_SetLow();

}
void Write26_5x7(unsigned char k,unsigned char row, unsigned char column, unsigned char underline)
{
    unsigned char i; 

    if(column > 17) return;

    SetLineColumnAddress(row*8,column*7);
	for(i=0;i<6;i++)
	{
        if(underline>0) Write26Data((H_Ascii_6x8[k][i])+0x80,1);
        else Write26Data(H_Ascii_6x8[k][i],1);
	}
    if(underline>0) Write26Data(0x80,1);
    else Write26Data(0x00,1);
}
//void Write26_test(void)
//{
//    unsigned char i,j,m,k; 
//
//    DispCS_SetHigh();
//
//    m=1;
//    k=0;
//
//	for(i=16;i<20;i+=2)
//	{
//        for(j=0;j<8;j++)
//        {
//            SetLineColumnAddress(m+j,1);
//            Write26Data(H_Ascii_6x8[i][j],1);
//            Write26Data(H_Ascii_6x8[i+1][j],1);
//        }
//        m+=8;
//	}
// 
//    DispCS_SetLow(); 
//   
//}
//void Write26_test2(void)
//{
//    unsigned char j,m; 
//
//    DispCS_SetHigh();
//
//    m=5;
//
//    for(j=0;j<26;j+=2)
//    {
//        SetLineColumnAddress(m,1);
//        Write26Data(H_Ascii_16x24[3][j],1);
//        Write26Data(H_Ascii_16x24[3][j+1],1);
//        m++;
//    }
//    m=5;
//    for(j=26;j<52;j++)
//    {
//        SetLineColumnAddress(m,9);
//        Write26Data(H_Ascii_16x24[3][j],1);
//        Write26Data(H_Ascii_16x24[3][j+1],1);
//        m++;
//    }
//
//    DispCS_SetLow(); 
//   
//}
//void Write26_test3(void)
//{
//    unsigned char i,j,m; 
//
//    DispCS_SetHigh();
//
//    
//    i=0;
//    for(i=0;i<3;i++)
//    {
//        m=i*5;
//        for(j=0;j<24;j++)
//        {
//            Write26Data((0x80 + m),0);
//            Write26Data((0x80 + i),0);
//            //SetLineColumnAddress(m,i);
//            Write26Data((unsigned char)((H_Ascii_16x24[i][j] >> 8) & 0x00FF),1);
//            Write26Data((unsigned char)(H_Ascii_16x24[i][j] & 0x00FF),1);
//            m++;
//        }        
//    }
//    for(i=0;i<3;i++)
//    {
//        m=i*5;
//        for(j=0;j<24;j++)
//        {
//            Write26Data((0x80 + m),0);
//            Write26Data((0x88 + i),0);
//            //SetLineColumnAddress(m,i);
//            Write26Data((unsigned char)((H_Ascii_16x24[i][j] >> 8) & 0x00FF),1);
//            Write26Data((unsigned char)(H_Ascii_16x24[i][j] & 0x00FF),1);
//            m++;
//        }        
//    }
//    DispCS_SetLow(); 
//   
//}
void Write26_16x24(unsigned char k,unsigned char page, unsigned char column)
{
    unsigned char i; 
    
    if(column > 10) return;

    SetLineColumnAddress(page,column);  //each page is 8 bits tall. Total display is 8 pages tall
	for(i=0;i<24;i+=2)
	{
		Write26Data(H_Ascii_16x24[k][i],1);
	}
    SetLineColumnAddress((page+1)*8,column*12);
	for(i=1;i<24;i+=2)
	{
		Write26Data(H_Ascii_16x24[k][i],1);
	}

}

void Write26Data(unsigned int dat,unsigned char RS)
{
    delay_us(5);
    SPI1_ExchangeByte(0xf8 + (unsigned char)(RS<<1));
    delay_us(5);
    SPI1_ExchangeByte(dat & 0xf0);
    delay_us(5);
    SPI1_ExchangeByte((dat<<4) & 0xf0);
	return;
}

//Specify DDRAM line for COM0 0~63
void InitialDisplayLine26(unsigned char line)
{
    Write26Data((0x80 + (line * 8)),0);
    Write26Data(0x80,0);
	return;
}


// Set page address 0~15
void SetLineColumnAddress(unsigned char vadd,unsigned char hadd)
{
    Write26Data((0x80 + vadd),0);

    //if(vadd < 32)
        Write26Data((0x80 + hadd),0);
    //else
       // Write26Data((0x88 + hadd),0);
	return;
}


void Disp26Init(void)
{
    DispCS_SetHigh();
    delay_ms(40);
    DispReset_SetLow();         //Reset
    delay_ms(5);
    DispReset_SetHigh();        //Reset set H
    delay_ms(5);
    
    Write26Data(0x30,0);
    delay_us(100);            
    Write26Data(0x30,0);  //Function Set
    delay_us(37);             
    Write26Data(0x08,0);  //Display on Control
    delay_us(100);            
    Write26Data(0x10,0);  //Cursor Display Control
    delay_us(100);            
    Write26Data(0x0C,0);  //Display Control,D=1,display on
    delay_us(100);            
    Write26Data(0x01,0);  //Display Clear
    delay_us(10);             
    Write26Data(0x06,0);  //Entry Mode Set
    delay_us(100);  
    DispCS_SetLow();
}

void Disp26GraphInit(void)
{
    DispCS_SetHigh();
    Write26Data(0x30,0);  //Extended Function Set RE=1: extended instruction
    delay_us(100);       
    Write26Data(0x01,0);  //Display Clear
    delay_ms(10);     
    Write26Data(0x36,0);  //Extended Function Set:RE=1: extended instruction set
    delay_us(37);            
    Write26Data(0x3E,0);  //EXFUNCTION(DL=8BITS,RE=1,G=1)
    delay_us(100);   
    DispCS_SetLow();
 }

void Display26PictureClear(void)
{
    unsigned char i,j,num=0;
//*******display top half screen
    DispCS_SetHigh();
    for(i=0;i<32;i++)              //
    { 
      Write26Data((0x80 + i),0); //SET   VERTICAL ADDRESS
      Write26Data(0x80,0);       //SET   HORIZONTAL ADDRESS
      for(j=0;j<16;j++) Write26Data(0x00,1);
    }
//*******display bottom half screen
   for(i=0;i<32;i++)              //
    {
      Write26Data((0x80 + i),0); //SET VERTICAL ADDRESS
      Write26Data(0x88,0);       //SET HORIZONTAL ADDRESS
      for(j=0;j<16;j++) Write26Data(0x00,1);
    }    
    DispCS_SetLow();
    return;
}

void Display26Clear(void)
{
    DispCS_SetHigh();
    SPI1_ExchangeByte(CLEAR26);
    delay_ms(10);     
    DispCS_SetLow();
    return;
}

void Display26Picture(unsigned char *adder)
{
    unsigned char i,j,num=0;
//*******display top half screen
    DispCS_SetHigh();
    for(i=0;i<32;i++)              //
    { 
      Write26Data((0x80 + i),0); //SET   VERTICAL ADDRESS
      Write26Data(0x80,0);       //SET   HORIZONTAL ADDRESS
      for(j=0;j<16;j++)
       {
         Write26Data(*adder,1);
         adder++;
       }
    }
//*******display bottom half screen
   for(i=0;i<32;i++)              //
    {
      Write26Data((0x80 + i),0); //SET VERTICAL ADDRESS
      Write26Data(0x88,0);       //SET HORIZONTAL ADDRESS
      for(j=0;j<16;j++)
       {
         Write26Data(*adder,1);
         adder++;
       }
    }    

    DispCS_SetLow();
    return;
}

void initina2(void)           //Graphic display Mode
{
    DispCS_SetHigh();
    Write26Data(0x30,0);  //Extended Function Set RE=1: extended instruction
    delay_us(100);       
    Write26Data(0x01,0);  //Display Clear
    delay_ms(10);     
    Write26Data(0x36,0);  //Extended Function Set:RE=1: extended instruction set
    delay_us(37);            
    Write26Data(0x3E,0);  //EXFUNCTION(DL=8BITS,RE=1,G=1)
    delay_us(100);   
    DispCS_SetLow();
}

void initinal(void)           //LCD initinal  Fonts Mode
{
    DispCS_SetHigh();
    Write26Data(0x30,0);  //Extended Function Set :8BIT,RE=0: basic instruction set, G=0 :graphic display OFF
    delay_us(100);            
    Write26Data(0x30,0);  //Function Set
    delay_us(37);             
    Write26Data(0x08,0);  //Display on Control
    delay_us(100);            
    Write26Data(0x10,0);  //Cursor Display Control
    delay_us(100);            
    Write26Data(0x0C,0);  //Display Control,D=1,display on
    delay_us(100);            
    Write26Data(0x01,0);  //Display Clear
    delay_ms(10);             
    Write26Data(0x06,0);  //Entry Mode Set
    delay_us(100);
    DispCS_SetLow();
}

void   lcd_mesg(unsigned char *adder1)
{
	unsigned char i;
    
    DispCS_SetHigh();
    Write26Data(0x80,0);  //Set RAM Address
    delay_us(100);
	for(i=0;i<32;i++)
    {
        Write26Data(*adder1,1);
        adder1++;
    }

    Write26Data(0x90,0);  //Set RAM Address
    delay_us(100);
	for(i=32;i<64;i++)
    {
        Write26Data(*adder1,1);
        adder1++;
    }
    DispCS_SetLow();
}