/*
 * File:   ERM12864-8.c
 * Author: kharris
 *
 * Created on February 27, 2023, 2:26 PM
 */

#include <xc.h>
#include "ERM12864-8.h"
#include "delays.h"
#include "mcc_generated_files/mcc.h"
#include <string.h>

void Write15SmallString(char *string, unsigned char line, unsigned char column, unsigned char underline)
{
    unsigned int size;
    unsigned char out, page, vert;
    int tout;

    page = line;
    vert = column;
    size = strlen(string);
    while(size)
    {
        tout = *string;
//        if (tout == 38) tout = 1;              // "&"
        if (tout == 46) tout = 2;         // "." 
        else if (tout == 91) tout = 47; // UP symbol
        else if (tout == 93) tout = 48; // DOWN symbol
        else {
            tout -= 44;
            if(tout < 0) tout = 0;                          //No ascii below "."
            else if(tout > 50 && tout < 78) tout -= 32;     //Move lower case to upper case
            else if(tout > 76) tout = 44;                   //No letters above Z
        }
            
        out = (unsigned char) tout;
        Write15_5x7(out,page,vert,underline);
        string++;                   // transmit next character on following loop
        if(vert++ > 16)
        {
            vert=0;
            if(page++ > 8)
            {
                page = 0;
            }            
        }
        size--;                     // loop until all characters sent (when size = 0)
    }
    
}
void Write15LargeString(char *string, unsigned char line, unsigned char column)
{
    int test;
    unsigned int size;
    unsigned char out, page, vert;

    page = line;
    vert = column;
    size = strlen(string);
    while(size)
    {
        //First adjust ascii to be numbers only using a shortened 0-9 plus "." ascii table
        test = *string;
        if(test == 32) test = 11;
        else if(test == 46) test = 10;
        else 
        {
            test -=48;     // NHAN: looks like converting from char to int
            if(test < 0) test = 11;
            else if(test > 9) test = 11;
        }
        //Now send output
        out = (unsigned char) (test & 0xFF);
        
        // TEST: increase font size
        Write15_20x32(out,page,vert);
//        Write15_12x16(out,page,vert);
        string++;                   // transmit next character on following loop
        if(vert++ > 10)   // NHAN: iterate to next column
        {
            vert=0;
            if(page++ > 4)
            {
                page = 0;
            }            
        }
        size--;                     // loop until all characters sent (when size = 0)
    }   
}

void WriteLowBattSymbol(unsigned char line, unsigned char column)
{
    unsigned char i; 
    unsigned char page = line;
    
    if(column > 10) return;
    
    // 1st page
	Set_Page_Address(page);
    Set_Column_Address(Start_column+column*11);	
	for(i=0;i<40;i+=2)  // 20 times
	{
		Write15Data(V_LowBattSymbol[i]);
	}
    
    // 2nd page
	Set_Page_Address(page+1);
    Set_Column_Address(Start_column+column*11);	
	for(i=1;i<40;i+=2)  // 20 times
	{
		Write15Data(V_LowBattSymbol[i]);
	}
}

void WriteSilenceSymbol(unsigned char line, unsigned char column)
{
    unsigned char i; 
    unsigned char page = line;
    
    if(column > 10) return;
    
    // 1st page
	Set_Page_Address(page);
    Set_Column_Address(Start_column+column*11);	
	for(i=0;i<40;i+=2)  // 20 times
	{
		Write15Data(V_SilenceSymbol[i]);
	}
    
    // 2nd page
	Set_Page_Address(page+1);
    Set_Column_Address(Start_column+column*11);	
	for(i=1;i<40;i+=2)  // 20 times
	{
		Write15Data(V_SilenceSymbol[i]);
	}
}

void Write15_5x7(unsigned char k,unsigned char page, unsigned char column, unsigned char underline)
{
    unsigned char i; 

    if(column > 17) return;

	Set_Page_Address(page)	;
    Set_Column_Address(Start_column+column*7);	
	for(i=0;i<6;i++)
	{
        if(underline>0) Write15Data((V_Ascii_6x8[k][i])+0x80);
        else Write15Data(V_Ascii_6x8[k][i]);
	}
    if(underline>0) Write15Data(0x80);
    else Write15Data(0x00);            
}
//void Write15_12x16(unsigned char k,unsigned char page, unsigned char column)
//{
//    unsigned char i; 
//    
//    if(column > 10) return;
//    
//	Set_Page_Address(page)	;
//    Set_Column_Address(Start_column+column*13);	
//	for(i=0;i<24;i+=2)  // 12 times
//	{
//		Write15Data(V_Ascii_12x16[k][i]);
//	}
//	Set_Page_Address(page+1)	;
//    Set_Column_Address(Start_column+column*13);	
//	for(i=1;i<24;i+=2)  // 12 times
//	{
//		Write15Data(V_Ascii_12x16[k][i]);
//	}
//}
//void Write15_16x24(unsigned char k,unsigned char page, unsigned char column)
//{
//    unsigned char i; 
//    
//    if(column > 10) return;
//    
//	Set_Page_Address(page);
//    Set_Column_Address(Start_column+column*17);	
//	for(i=0;i<48;i+=2)
//	{
//		Write15Data(V_Ascii_16x24[k][i]);
//	}
//	Set_Page_Address(page+1);
//    Set_Column_Address(Start_column+column*17);	
//	for(i=1;i<48;i+=2)
//	{
//		Write15Data(V_Ascii_16x24[k][i]);
//	}
//}

void Write15_20x32(unsigned char k,unsigned char page, unsigned char column)
{
    unsigned char i; 
    
    if(column > 10) return;
    
    // 1st page
	Set_Page_Address(page);
    Set_Column_Address(Start_column+column*21);	
	for(i=0;i<80;i+=4)  // 20 times
	{
		Write15Data(V_Ascii_20x32[k][i]);
	}
    
    // 2nd page
	Set_Page_Address(page+1);
    Set_Column_Address(Start_column+column*21);	
	for(i=1;i<80;i+=4)  // 20 times
	{
		Write15Data(V_Ascii_20x32[k][i]);
	}
    
    // 3rd page
	Set_Page_Address(page+2);
    Set_Column_Address(Start_column+column*21);	
	for(i=2;i<80;i+=4)  // 20 times
	{
		Write15Data(V_Ascii_20x32[k][i]);
	}
    
    // 4th page
	Set_Page_Address(page+3);
    Set_Column_Address(Start_column+column*21);	
	for(i=3;i<80;i+=4)  // 20 times
	{
		Write15Data(V_Ascii_20x32[k][i]);
	}
}

void adj_Contrast(void)
{	
    Set_Contrast_Control_Register(Contrast_level);	
}

void Write15Data(unsigned char dat)
{
    DispA0_SetHigh();
    DispCS_SetLow();
    SPI1_ExchangeByte(dat);
    DispCS_SetHigh();
	return;
}

void Write15Instruction(unsigned char cmd)
{
    DispA0_SetLow();
    DispCS_SetLow();
    SPI1_ExchangeByte(cmd);
    DispCS_SetHigh();
	return;
}

//Specify DDRAM line for COM0 0~63
void InitialDisplayLine15(unsigned char line)
{
    line|=0x40;
    Write15Instruction(line);
	return;
}


// Set page address 0~15
void Set_Page_Address(unsigned char add)
{
    add=0xb0|add;
    Write15Instruction(add);
	return;
}

void Set_Column_Address(unsigned char add)
{	add+=4;
    Write15Instruction((0x10|(add>>4)));
	Write15Instruction((0x0f&add));
	return;
}

//a(0-63) 32default   Vev=(1-(63-a)/162)Vref   2.1v
void Set_Contrast_Control_Register(unsigned char mod)
{
    Write15Instruction(0x81);
	Write15Instruction(mod);
	return;
}

void Disp15Init(void)
{

    DispReset_SetHigh();
    delay_ms(2);
    DispReset_SetLow();
    delay_ms(5);
    DispReset_SetHigh();
    delay_ms(5);
    
	Write15Instruction(0xa2);//bias set:1/9
	Write15Instruction(0xa1);//ADC select:nomal,0->128
	Write15Instruction(0xa6);//normal/reverse  display
	Write15Instruction(0xc8);//commom output mode select: reverse
	Write15Instruction(0xf8);//booster ratio set
	Write15Instruction(0x00);//booster ratio:4x
	Write15Instruction(0x2f);//power control set
	Write15Instruction(0x26);//set (Rb/Ra)
	Write15Instruction(0x81);//vo output voltage set
	Write15Instruction(Contrast_level);//voltage volume =9.0v
	Write15Instruction(0x40);  //start lie		 
	Write15Instruction(0xaf);//display on
    
    REVERSE_DISPLAY_OFF();
    ENTIRE_DISPLAY_OFF();
}

/* Display bitmap represented by 1D array */
// bitmap: bitmap to be displayed
// Width: width of bitmap, in pixels
// Height: height of bitmap, in pixels
// page: each page has 8 rows, from 0 -> 7
// y: column, from 0 -> 127
void Write15Bitmap(unsigned char bitmap[], uint8_t Width, uint8_t Height, unsigned char page, unsigned char y)
{
    unsigned char i, j;    
    unsigned numPages = Height / 8; // each page has 8 rows. Note: only accept numPages multiples of 8
    uint16_t len = Width * numPages;
    
    // Handle out of bound coordinates
    if((page > 7) || (y > 127))     // since display resolution is 128x64
    {
        return;
    }
    
    for(i=0; i<numPages; i++)
    {
        Set_Page_Address(page+i);
        Set_Column_Address(Start_column+y);  // not sure yet
        for(j=i; j<len; j+=numPages)
        {
            Write15Data(bitmap[j]);
        }
    }    
    return;
}

void Display15Clear(void)
{
    unsigned char i,j;
	InitialDisplayLine15(0x40);
	for(i=0;i<0x08;i++)
	{
        Set_Page_Address(i);
        Set_Column_Address(0x00);
        for(j=0;j<0x80;j++)
		{
		    Write15Data(0x00);
		}
	}
    return;
}
