/* 
 * File:   ERM12864-8 Series Display
 * Author: KRH
 * Comments: ERM12864-8 is a 1.6" display
 * Revision history: 
 * 20230227     v0.1 Initial code based on example for Arduino
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ERM12864_8_HEADER
#define	ERM12864_8_HEADER

#include <xc.h> // include processor files - each processor file is guarded.  
#include "AsciiArrays.h"

#define REVERSE_DISPLAY_ON()   Write15Instruction(0xa7)   //  Reverse display : 0 illuminated
#define REVERSE_DISPLAY_OFF()  Write15Instruction(0xa6)   //  Normal display : 1 illuminated
#define ENTIRE_DISPLAY_ON()    Write25Instruction(0xa5)   //  Entire dislay   Force whole LCD point
#define ENTIRE_DISPLAY_OFF()   Write15Instruction(0xa4)   //  Normal display


#define Start_column	0x00
#define Start_page		0x02
#define	StartLine_set	0x00
#define Contrast_level  10

void Write15SmallString(char *string, unsigned char line, unsigned char column, unsigned char underline);
void Write15LargeString(char *string, unsigned char line, unsigned char column);
void WriteLowBattSymbol(unsigned char line, unsigned char column);
void WriteSilenceSymbol(unsigned char line, unsigned char column);
void Write15_5x7(unsigned char k,unsigned char page, unsigned char column, unsigned char underline);
void Write15_12x16(unsigned char k,unsigned char page, unsigned char column);
//void Write15_16x24(unsigned char k,unsigned char page, unsigned char column);
void Write15_20x32(unsigned char k,unsigned char page, unsigned char column);
void adj_Contrast(void);
void Busy();
void Write15Data(unsigned char dat);
void Write15Instruction(unsigned char cmd);
void InitialDisplayLine15(unsigned char line);
void Set_Page_Address(unsigned char add);
void Set_Column_Address(unsigned char add);
void Set_Contrast_Control_Register(unsigned char mod);
void Disp15Init(void);
void Display15Picture(unsigned char pic[]);
void Display15Clear(void);

#endif	/* XC_HEADER_TEMPLATE_H */

