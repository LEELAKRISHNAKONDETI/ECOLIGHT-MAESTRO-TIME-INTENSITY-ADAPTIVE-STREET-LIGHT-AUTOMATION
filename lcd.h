#include "types.h"
void WriteLCD(u8 data);
void CmdLCD(u8 cmd);
void InitLCD(void);
void CharLCD(u8 asciival);
void StringLCD(u8*ptr);
void U32LCD(u32 num);
void F32LCD(float fNum, unsigned char nDP);

