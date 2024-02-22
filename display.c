/*
 * File:   display.c
 * Author: kharris
 *
 * Created on May 7, 2023, 11:35 AM
 */


#include <xc.h>
#include "mcc_generated_files/pin_manager.h"
#include "ERM12864-7.h"
#include "ERM12864-8.h"
#include "display.h"


void Write_Data(unsigned char dat)
{   //high is 1.5" display and low is 2.6" display
    if(DISP_SEL_GetValue()) Write15Data(dat);     
    else Write26Data(dat,0);
}
void WriteDisplayCommand(unsigned char cmd)
{   //high is 1.5" display and low is 2.6" display
    if(DISP_SEL_GetValue()) Write15Instruction(cmd);    
    else Write26Data(cmd,1);
}
void Write_5x7(unsigned char k,unsigned char page, unsigned char column, unsigned char underline)
{   //high is 1.5" display and low is 2.6" display
    if(DISP_SEL_GetValue()) Write15_5x7(k, page, column, underline);  
    else Write26_5x7(k, page, column, underline);
}
void Write_16x24(unsigned char k,unsigned char page, unsigned char column)
{   //high is 1.5" display and low is 2.6" display
    if(DISP_SEL_GetValue()) Write15_16x24(k, page, column);    
    else Write26_16x24(k, page, column);
}
void WriteSmallString(char *string, unsigned char line, unsigned char column, unsigned char underline)
{   //high is 1.5" display and low is 2.6" display
    if(DISP_SEL_GetValue()) Write15SmallString(string, line, column, underline);    
    else Write26SmallString(string, line, column, underline);
}
void WriteLargeString(char *string, unsigned char line, unsigned char column)
{   //high is 1.5" display and low is 2.6" display
    if(DISP_SEL_GetValue()) Write15LargeString(string, line, column);    
    else Write26LargeString(string, line, column);
}
void Display_Clear(void)
{   //high is 1.5" display and low is 2.6" display
    if(DISP_SEL_GetValue()) Display15Clear();   
    else Disp26GraphInit(); //Display26Clear(); 
}
void DispInit(void)
{   //high is 1.5" display and low is 2.6" display
    if(DISP_SEL_GetValue()) Disp15Init();    
    else 
    {
        Disp26Init();
        Disp26GraphInit();
    }
}
