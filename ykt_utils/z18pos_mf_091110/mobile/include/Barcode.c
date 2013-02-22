 /*********************************************
 **	    HT Barcode Scan extended functions   **
 **     FOR HT2800                           **
 *********************************************/

  #define __ASM       _asm
  #include <barcode.h>

 int GetBarStr(char _far * StrBuffer, char * BarType)
 {
    char Result, nums;
    int i;
    __ASM {
          les di, StrBuffer
          mov ax, 0x1454
          int 0x10
          mov Result, ah
          mov nums, al
    }
    if (Result ==_BarRightEnd)
    {
        BarType = StrBuffer[0];
        for(i=1;i<nums;i++) StrBuffer[i-1] = StrBuffer[i];
        StrBuffer[i-1]='\0';
        return (nums-1);
    }else
        return 0;
 }

  int SetBarTemp(unsigned char SetLength, char _far * ParmStrBuffer)
  {
    char Result;
    __ASM {
          les  di, ParmStrBuffer
          mov  ax, 0x1452
          mov  bh,  SetLength
          mov  bl,  1
          int  0x10
          mov  Result, al
    }
    return Result;
  }

  int GetBarTemp(unsigned char GetLength, char _far * ParmStrBuffer)
  {
    char Result;
    __ASM {
          les  di,  ParmStrBuffer
          mov  ax,  0x1452
          mov  bh,  GetLength
          xor  bl,  bl
          int  0x10
          mov  Result, al
    }
    return Result;
  }

