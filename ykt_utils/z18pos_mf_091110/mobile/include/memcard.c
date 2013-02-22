 /*********************************************
 **	    HT Mememory Card  functions	         **
 *********************************************/

   #define __ASM       _asm

   #include <memcard.h>

   int MemCard_Init(unsigned char MemCardType) {
       int  result = 0;
        __ASM {
               mov bl,  MemCardType
               mov ax,  0x1449
               int 0x10
               mov result, ax
        }
       return(result);
   }

   void MemCard_Exit(void){
        __ASM {
               mov ax,  0x144d
               int 0x10
        }
   }

   int MemCard_Read(char _far *RDaddr,unsigned char RDBytes,unsigned char ByteInv){
       int  result = 0;
        __ASM {
               les   di,  RDaddr
               mov   bl,  ByteInv
               mov   cl,  RDBytes
               mov   ax,  0x144b
               int   0x10
               mov   result, ax
        }
       return(result);
   }

   int MemCard_Write(char _far *WTaddr,unsigned char WTBits,unsigned char ByteInv){
       int  result = 0;
        __ASM {
               les di,  WTaddr
               mov bl,  ByteInv
               mov cl,  WTBits
               mov ax,  0x144c
               int 0x10
               mov result, ax
        }
       return(result);
   }

   int MemCard_PowerUp(void){
        int Result;
        __ASM {
               mov bl,  1
               mov ax,  0x144e
               int 0x10
               mov Result, ax
        }
        return(Result);
   }

   int MemCard_PowerDown(void){
        int Result;
        __ASM {
               xor bl,  bl
               mov ax,  0x144e
               int 0x10
               mov Result, ax
        }
        return(Result);
   }


   void MemCard_PinDir(unsigned char CDRio,unsigned char CDRc4,unsigned char CDRc8){
        unsigned char SetDirByte = 0;
        if (CDRio == 1)  SetDirByte = SetDirByte | 0x1;
        if (CDRc4 == 1)  SetDirByte = SetDirByte | 0x2;
        if (CDRc8 == 1)  SetDirByte = SetDirByte | 0x4;
        __ASM {
               xor bl,  bl
               mov bh,  SetDirByte
               mov ax,  0x144f
               int 0x10
        }
   }

   void MemCard_PinRd(unsigned char _far *CDRio,unsigned char _far *CDRc4,unsigned char _far *CDRc8){
        __ASM {
               mov bl,  2
               mov ax,  0x144f
               int 0x10
               les di,  CDRio
               xor al,  al
               mov es:[di], al
               test bh, 0x01
               jz  Next_Pin1
               mov al, 1
               mov es:[di], al
        }
       Next_Pin1:
        __ASM {
               les di,  CDRc4
               xor al,  al
               mov es:[di], al
               test bh, 0x02
               jz  Next_Pin2
               mov al, 1
               mov es:[di], al
       }
       Next_Pin2:
        __ASM {
               les di,  CDRc8
               xor al,  al
               mov es:[di], al
               test bh, 0x04
               jz  Pin_Checked
               mov al, 1
               mov es:[di], al
       }
       Pin_Checked:
   }

   void MemCard_PinSet(unsigned char CDRio,unsigned char CDRc4,unsigned char CDRc8,unsigned char CDRRst,unsigned char CClk){
        unsigned char SetBits = 0;
        if (CDRio == 1)   SetBits = SetBits | 0x1;
        if (CDRc4 == 1)   SetBits = SetBits | 0x2;
        if (CDRc8 == 1)   SetBits = SetBits | 0x4;
        if (CDRRst == 1)  SetBits = SetBits | 0x8;
        if (CClk == 1)    SetBits = SetBits | 0x10;
        __ASM {
               mov bl,  1
               mov bh,  SetBits
               mov ax,  0x144f
               int 0x10
        }
   }

   void SYNPulse_Width(unsigned char HDelay,unsigned char Delay){
        __ASM {
               mov bh,  HDelay
               mov bl,  Delay
               mov ax,  0x144a
               int 0x10
        }
   }
