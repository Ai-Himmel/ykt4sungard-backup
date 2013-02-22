
 /*********************************************
 **	    HT Lcd extended functions	     **
 *********************************************/

  #define __ASM       _asm
  #define __HTLCD     1

  #include <htlcd.h>
  #include <alloc.h>
  #include <dos.h>


  void ClrGraph(void)
  {
    __ASM {
      mov   ax, 1400h
      int   10h
    }
  }


  unsigned int LCDinChinese(void)
  {
    unsigned int result=0;
    __ASM {
      xor   bx, bx
      mov   ax, 1401h
      int   10h
      test  bl, 2
      jz    _end
      and   bl, 1
      inc   bl
      xor   bh, bh
      mov   result, bx
    }
    _end:
    return(result);
  }


  void SetFont(unsigned char FontID)
  {
    __ASM {
      mov   bh, 01h
      mov   bl, FontID
      dec   bl
      mov   ax, 1401h
      int   10h
    }
  }


  void RefreshWin(void)
  {
    __ASM {
      mov   ax, 1402h
      int   10h
    }
  }


  void RefreshLCD(void)
  {
    __ASM {
      mov   ax, 1403h
      int   10h
    }
  }


  void ClrLCDScr(void)
  {
    __ASM {
      mov   ax, 1404h
      int   10h
    }
  }


  void SetCurType(unsigned char CursorType)
  {
    __ASM {
      mov   bh, CursorType
      mov   ax, 1406h
      int   10h
    }
  }


  void GetLCDMap(int _far *X, int _far *Y)
  {
    __ASM {
      mov   ax, 1407h
      xor   bx, bx
      int   10h
      les   bx, X
      mov   es:[bx], cx
      les   bx, Y
      mov   es:[bx], dx
    }
  }


  void SetLCDMap(int X, int Y)
  {
    __ASM {
      mov   ax, 1407h
      mov   cx, X
      mov   dx, Y
      mov   bx, 1
      int   10h
    }
  }


  unsigned char SetPullMode(unsigned char PullMode)
  {
    unsigned char result;

    __ASM {
      mov   bh, PullMode
      and   bh, 3
      mov   ax, 1408h
      int   10h
      mov   result, bh
    }
    return(result);
  }


  unsigned char GetPullMode(void)
  {
    unsigned char result;

    __ASM {
      mov   bh, 0
      mov   ax, 1408h
      int   10h
      mov   result, bh
      mov   ax, 1408h
      int   10h
    }
    return(result);
  }


  void WriteAtDot(unsigned int dotX, unsigned int dotY,
		  unsigned char Mode, unsigned char Attr,
		  unsigned int dblChar)
  {
    __ASM {
      push  bp
      mov   bx, dotY
      mov   ch, Mode
      mov   cl, Attr
      mov   dx, dblChar
      mov   bp, dotX
      or    dh, dh
      jz    _notChg
      xchg  dh, dl
    }
    _notChg:
    __ASM {
      mov   ax, 1409h
      int   10h
      pop   bp
    }
  }


  void MoveLCDMap(unsigned char Direction)
  {
    __ASM {
      mov   bh, Direction
      mov   ax, 140ah
      int   10h
    }
  }


  void ReverseArea(unsigned char luX, unsigned char luY,
                   unsigned char rlX, unsigned char rlY)
  {
    __ASM {
      mov   ch, luY
      mov   cl, luX
      mov   dh, rlY
      mov   dl, rlX
      mov   ax, 140bh
      int   10h
    }
  }


  void ResetLCDMap(void)
  {
    __ASM {
      mov   ax, 140ch
      int   10h
    }
  }


  void LCDWindow(unsigned char luX, unsigned char luY,
                 unsigned char rlX, unsigned char rlY,
                 unsigned char ColCnt, unsigned char RowCnt)
  {
    __ASM {
      mov   ch, luY
      mov   cl, luX
      mov   dh, rlY
      mov   dl, rlX
      mov   bh, RowCnt
      mov   bl, ColCnt
      mov   ax, 140dh
      int   10h
    }
  }


  void SaveScreen(char _far *Buffer)
  {
    __ASM {
      les   di, Buffer
      mov   ax, 140Eh
      int   10h
    }
  }


  char _far *HeapSaveScr(void)
  {
    char *p;
    char _far *fp;
    unsigned int  sz;

    __ASM {
      mov   ax, 1416h
      int   10h
      mov   sz, cx
    }

    p=malloc(sizeof(sz));
    fp=MK_FP(FP_SEG(p), FP_OFF(p));

    __ASM {
      les   di, fp
      mov   ax, 140Eh
      int   10h
    }
    return fp;
  }


  void SaveGraph(char _far *Buffer)
  {
    __ASM {
      les   di, Buffer
      mov   ax, 140Fh
      int   10h
    }
  }


  void RestoreScreen(char _far *Buffer)
  {
    __ASM {
      les   di, Buffer
      mov   ax, 1410h
      int   10h
    }
  }


  void HeapRestoreScr(char _far *Buffer)
  {
    __ASM {
      les   di, Buffer
      mov   ax, 1410h
      int   10h
    }
    free((char *)Buffer);
  }

  void RestoreGraph(char _far *Buffer)
  {
    __ASM {
      les   di, Buffer
      mov   ax, 1411h
      int   10h
    }
  }


  void DotWrite(unsigned char dotX, unsigned char dotY,
                unsigned char Color)
  {
    __ASM {
      mov   dh, dotY
      mov   dl, dotX
      mov   bl, Color
      mov   ax, 1412h
      int   10h
    }
  }


  void DrawBox(unsigned char luX, unsigned char luY,
               unsigned char rlX, unsigned char rlY,
               char Color)
  {
    __ASM {
      mov   ax, 1413h
      mov   bl, Color
      mov   ch, luY
      mov   cl, luX
      mov   dh, rlY
      mov   dl, rlX
      int   10h
    }
  }


  unsigned int BackLightOn(void)
  {
    unsigned int result=0;
    __ASM {
      xor   bh, bh
      mov   ax, 1414h
      int   10h
      test  bl, 2
      jz    _End
      not   result
    }
    _End:
    return(result);
  }


  void TurnBackLight(unsigned char On_Off)
  {
    __ASM {
      mov   bh, 1
      mov   bl, On_Off
      mov   ax, 1414h
      int   10h
    }
  }


  unsigned int WinSize(unsigned char _far *ColCnt,
		       unsigned char _far *RowCnt)
  {
    unsigned int result;
    __ASM {
      mov   ax, 1416h
      int   10h
      mov   result, cx
      les   di, ColCnt
      mov   es:[di], bl
      les   di, RowCnt
      mov   es:[di], bh
    }
    return(result);
  }


  void DrawLine(unsigned char startX, unsigned char startY,
                unsigned char endX, unsigned char endY,
                unsigned char Color)
  {
    __ASM {
      mov   ax, 1417h
      mov   bl, Color
      mov   ch, startY
      mov   cl, startX
      mov   dh, endY
      mov   dl, endX
      int   10h
    }
  }


  void Draw(char _far *DrawStr)
  {
    __ASM {
      les  di, DrawStr
      mov  ax, 1418h
      int  10h
    }
  }


  void MovePen(unsigned char penX, unsigned char penY)
  {
    __ASM {
      mov  dh, penY
      mov   dl, penX
      mov  ax, 1419h
      int  10h
    }
  }


  void HTSound(unsigned int freq)
  {
    __ASM {
      mov  ax, 141Ah
      mov  bx, freq
      int  10h
    }
  }


  void HTNoSound(void)
  {
    __ASM {
      mov   ax, 141Bh
      int   10h
    }
  }


  void DrawSolidRec(unsigned char luX, unsigned char luY,
                    unsigned char rlX, unsigned char rlY,
                    char Color)
  {
    __ASM {
      mov   ax, 141ch
      mov   bl, Color
      mov   ch, luY
      mov   cl, luX
      mov   dh, rlY
      mov   dl, rlX
      int   10h
    }
  }


  void MusicPlay(char _far *MusicStr)
  {

    __ASM {
      les   di, MusicStr
      mov   ax, 141Dh
      int   10h
    }
  }


  void MusicStop(void)
  {
    __ASM {
      mov   ax, 141Eh
      int   10h
    }
  }

  void TurnOffHT(void)
  {
    __ASM {
      mov    ax, 141fh
      int    10h
    }
  }

  void TurnOnR232(void)
  {
    __ASM {
      mov    ax,1420h
      int    10h
      int    0e0h
    }
  }

  void TurnOffR232(void)
  {
    __ASM {
      mov    ax,1421h
      int    10h
      int    0e0h
    }
  }

  void HTShowBatt(void)
  {
    __ASM {
      mov  ax, 1422h
      int  10h
    }
  }

  unsigned HTGetBatt(void)
  {
    unsigned result;
    __ASM {
      mov  ax, 1423h
      int  10h
      mov  result, ax
    }
    return(result);
  }

  char _far *HTLogoCtrl(char _far *p)
  {
    char _far *q;
    __ASM {
      les  di, p
      mov  cx, es
      mov  bx, di
      mov  ax, 1424h
      int  10h
      mov  word ptr q+2, cx
      mov  word ptr q, bx
    }
    return(q);
  }

  void HTPutHDP(char _far *p)
  {
    __ASM {
      les  di, p
      mov  cx, es
      mov  bx, di
      mov  ax, 1425h
      int  10h
    }
  }

  unsigned char BackupBatt(void)
  {
    unsigned char result=0;
    __ASM {
      mov   ax, 1423h
      int   10h
      mov   result, bl
      }
    return(result);
  }

  void GetDotMatrix (unsigned int dblChar, unsigned char Attr, char _far *Buffer)
  {
    __ASM {
      mov    dx, dblChar
      mov    cl, Attr
      mov    ax, 142Ah
      int    10h
      push   ds
      mov    dx, es
      mov    ds, dx
      mov    si, di
      les    di, Buffer
      mov    al, 32
      cld
      stosb
      mov    cx, 32
      rep movsb
      pop    ds
    }
  }

  void LCDCntrstInc(void)
  {
    __ASM {
      mov  ax, 142bh
      int  10h
    }
  }

  void LCDCntrstReset(void)
  {
    __ASM {
      mov  ax, 142ch
      int  10h
    }
  }

  void LCDCntrstDec(void)
  {
    __ASM {
      mov  ax, 142dh
      int  10h
    }
  }

  void SetSleeper(unsigned int SleepSec)
  {
    __ASM {
      mov  bx, SleepSec
      mov  ax, 142eh
      int  10h
    }
  }

  unsigned int GetSleeper(void)
  {
    unsigned int result=0;
    __ASM {
      mov  ax, 142fh
      int  10h
      mov  result, bx
    }
    return(result);
  }

  void EnterClock(void)
  {
    __ASM {
      mov  ax, 1430h
      int  10h
    }
  }

  unsigned int HtMachineCode(void)
  {
    unsigned char HtMachCode;
    __ASM {
      xor  bx, bx
      mov  ax, 1438h
      int  10h
      mov  HtMachCode, ch
    }
    return(HtMachCode);
  }
