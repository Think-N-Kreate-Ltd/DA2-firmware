/* 
 * File:   ERM12864-7 Series Display
 * Author: KRH
 * Comments: ERM12864-7 is a 2.6" display
 * Revision history: 
 * 20230227     v0.1 Initial code based on example for Arduino
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ERM12864_7_HEADER
#define	ERM12864_7_HEADER

#include <xc.h> // include processor files - each processor file is guarded.  
#include "AsciiArrays.h"

#define CLEAR26     0x01


void Write26SmallString(char *string, unsigned char line, unsigned char column, unsigned char underline);
void Write26LargeString(char *string, unsigned char line, unsigned char column);
void Write26_5x7(unsigned char k,unsigned char page, unsigned char column, unsigned char underline);
void Write26_16x24(unsigned char k,unsigned char page, unsigned char column);
void Write26Data(unsigned int dat,unsigned char RS);
void Disp26Init(void);
void Display26Clear(void);
void SetLineColumnAddress(unsigned char vadd,unsigned char hadd);
void InitialDisplayLine26(unsigned char line);
void Display26Picture(unsigned char *adder);
void Disp26GraphInit(void);
void Display26PictureClear(void);

void initina2(void);
void initinal(void);
void   lcd_mesg(unsigned char *adder1);
void Write26_test(void);
void Write26_test2(void);
void Write26_test3(void);

#endif	/* XC_HEADER_TEMPLATE_H */

