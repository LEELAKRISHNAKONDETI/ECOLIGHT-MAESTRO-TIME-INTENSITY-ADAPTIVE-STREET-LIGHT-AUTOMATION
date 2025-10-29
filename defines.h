//defines.h//
#include"types.h"
#define WRITEBIT(word,bitpos,bit) word=((word&~(1<<bitpos))|(bit<<bitpos))
#define READBIT(word,bit) ((word>>bit)&1)
#define READNIBBLE(word,bit) ((word>>bit)&15)
#define WRITENIBBLE(word,bsp,val) word=((word&~(15<<bsp))|(val<<bsp))
#define READBYTE(word,bit) ((word>>bit)&255)
#define WRITEBYTE(word,bsp,val) (word=(word&~(0xff<<bsp))|(val<<bsp))
