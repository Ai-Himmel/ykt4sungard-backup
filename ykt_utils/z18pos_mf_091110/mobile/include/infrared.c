
  #define __ASM       _asm

  unsigned char IRPowerCtrl(unsigned char ctrl)
  {
    unsigned char result;

    __ASM {
      mov   ax, 1426h
      mov   bl, ctrl
      int   10h
      mov   result, bh
    }
    return(result);
  }

  void SetIRMFreq(long freq)
  {
    unsigned long tfreq;
    tfreq = freq / 10;
    if (tfreq <= 65535) {
      __ASM {
        mov ax, 1427h
        mov bx, word ptr tfreq
        int 10h
      }
    } else {
      __ASM {
        mov ax, 1427h
        mov bx, 0ffffh
        mov cx, word ptr tfreq
        mov dx, word ptr tfreq + 2
        int 10h
      }
    }
  }

  void SetIROutput(unsigned char io)
  {
    __ASM {
      mov ax, 1428h
      mov bl, io
      int 10h
    }
  }

  unsigned char GetIRInput(void)
  {
    unsigned char result;

    __ASM {
      mov   ax, 1429h
      int   10h
      mov   result, bl
    }
    return(result);
  }
