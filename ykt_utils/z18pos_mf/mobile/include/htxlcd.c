  #define __ASM  asm

  #include <dos.h>
  #include <conio.h>
  #include <string.h>
  #include <stdio.h>
  #include <stdarg.h>
  #include <alloc.h>
  #include <htlcd.h>
  #include <htxlcd.h>

  void blankscreen(unsigned char UpperLeftX, unsigned char UpperLeftY,
		   unsigned char LowerRightX, unsigned char LowerRightY)
  {
    __ASM {
      mov  ch, UpperLeftY
      mov  cl, UpperLeftX
      sub  cx, 0101h
      mov  dh, LowerRightY
      mov  dl, LowerRightX
      sub  dx, 0101h
      mov  ax, 0600h
      mov  bh, 7
      int  10h
    }
  }

  void scrollupscr(unsigned char UpperLeftX, unsigned char UpperLeftY,
		   unsigned char LowerRightX, unsigned char LowerRightY,
		   unsigned char ScrollLines)
  {
    __ASM {
      mov  ch, UpperLeftY
      mov  cl, UpperLeftX
      sub  cx, 0101h
      mov  dh, LowerRightY
      mov  dl, LowerRightX
      sub  dx, 0101h
      mov  al, ScrollLines
      mov  ah, 6
      mov  bh, 7
      int  10h
    }
  }

  void scrolldownscr(unsigned char UpperLeftX, unsigned char UpperLeftY,
		     unsigned char LowerRightX, unsigned char LowerRightY,
		     unsigned char ScrollLines)
  {
    __ASM {
      mov  ch, UpperLeftY
      mov  cl, UpperLeftX
      sub  cx, 0101h
      mov  dh, LowerRightY
      mov  dl, LowerRightX
      sub  dx, 0101h
      mov  al, ScrollLines
      mov  ah, 07
      mov  bh, 7
      int  10h
    }
  }


  void toxy(unsigned char X, unsigned char Y)
  {
    __ASM {
      mov  ah, 02h
      xor  bh, bh
      mov  dh, Y
      dec  dh
      mov  dl, X
      dec  dl
      int  10h
    }
  }


  void saycstr(unsigned char atX, unsigned char atY, char *str, unsigned char attr)
  {
    unsigned char i, chr;

    for (i=0; (str[i]!=0); i++) {
      chr=str[i];
      __ASM {
	mov  ah, 02h
	xor  bh, bh
	mov  dh, atY
	dec  dh
	mov  dl, atX
	add  dl, i
	dec  dl
	int  10h
	mov  ah, 09h
	mov  al, chr
	mov  bl, attr
	mov  cx, 1
	int  10h
      }
    }
    return;
  }


  unsigned readspckey()
  {
    unsigned k;

    __ASM {
      mov  ah, 0
      int  16h
      mov  k, ax
    }
    return(k);
  }

  void OpenLCDWindow(unsigned char luX, unsigned char luY,
		     unsigned char rlX, unsigned char rlY,
		     unsigned char ColCnt, unsigned char RowCnt,
		     char _far *Buffer)
  {
    SaveScreen(Buffer);
    LCDWindow(luX, luY, rlX, rlY, ColCnt, RowCnt);
    DrawBox(luX-1, luY-1, rlX+1, rlY+1, 0);
    DrawBox(luX-2, luY-2, rlX+2, rlY+2, 1);
    DrawBox(luX-3, luY-3, rlX+3, rlY+3, 0);
    RefreshLCD();
  }


  void CloseLCDWindow(char _far *Buffer)
  {
    RestoreScreen(Buffer);
  }

  void HideCursor(void)
  {
    __ASM {
      mov   ah, 01h
      mov   cx, 2000h
      int   10h
    }
  }

  void ShowCursor(void)
  {
    __ASM {
      mov   ax, 0100h
      mov   cx, 0607h
      int   10h
    }
  }


  void saystr(char *str, unsigned len)
  {
    unsigned i;

    for (i=0; ((i<len) && (str[i]!=0)); i++)
      putch(str[i]);
    return;
  }


  unsigned char menu( MENU_ITM menuset[],
		     char *title,  unsigned char deflbar,
		     unsigned char atX, unsigned char atY)
  {

    unsigned char i, j, maxi, barstart;
    unsigned akey;

    SetPullMode(_pul_NON);

    i=atY;
    if (title!=NULL) {
      saycstr(atX, i, title, _attr_NORM);
      i++;
    }

    barstart=i;
    j=0;

    while ((menuset[j].menubar!=NULL) && (i <25)) {
      saycstr(atX, i++, menuset[j++].menubar, _attr_NORM);
    }

    maxi = j;

    if (deflbar<maxi)
      i=deflbar;
    else
      i = 0;

    SetPullMode(_pul_VER);

    do {
      saycstr(atX, i+barstart, menuset[i].menubar, _attr_INVE);

      akey = readspckey();

      switch (akey) {
	case _RGT:
	case _DWN: {
	  saycstr(atX, i+barstart, menuset[i].menubar, _attr_NORM);
	  if (i < maxi-1)
	    i++;
	  break;
	}
	case _LFT:
	case _UP: {
	  saycstr(atX, i+barstart, menuset[i].menubar, _attr_NORM);
	  if (i == 0)
	    toxy(atX, atY);
	  else
	    i--;
	  break;
	}
	default: {
	   for (j=0; ((j<maxi) && ((unsigned char)akey!=menuset[j].menukey)); j++);
	   if (j!=maxi) {
	     i=j;
	     akey=_ENT;
	   }
	}
      }
    } while ((akey != _ENT) && (akey != _ESC));

    if (akey == _ESC)
      return(0);
    else
      return(menuset[i].menukey);
  }

  unsigned char menuwin(unsigned char luX, unsigned char luY,
			unsigned char rlX, unsigned char rlY,
			unsigned char ColCnt, unsigned char RowCnt,
			MENU_ITM menuset[],
			char *title,  unsigned char deflbar)
  {
    unsigned char result;
    char *p;
    char _far *fp;
    unsigned int  sz;

    __ASM {
      mov   ax, 1416h
      int   10h
      mov   sz, cx
    }
    sz=sz+2;
    p=malloc(sizeof(sz));
    fp=MK_FP(FP_SEG(p), FP_OFF(p));

    OpenLCDWindow(luX, luY, rlX, rlY, ColCnt, RowCnt, fp);
    result=menu(menuset, title, deflbar, 1, 1);
    CloseLCDWindow(fp);
    free(p);
    return(result);
  }


  int show2lnbox(char *fstLine, char *sndLine, ...)
  {
    int i, j, k;
    unsigned aKey;
    char *p;
    char _far *fp;
    unsigned int  sz;

    va_list ap;
    int arg;

    __ASM {
      mov   ax, 1416h
      int   10h
      mov   sz, cx
    }
    sz=sz+2;
    p=malloc(sizeof(sz));
    fp=MK_FP(FP_SEG(p), FP_OFF(p));

    i = strlen(fstLine);
    j = strlen(sndLine);
    if (i < j) {
       k =i;
       i =j;
       j =k;
    }
    j = (128 - ( i * 8 ) - 6) / 2;
    k = (i * 8) + 5 + j;

    va_start(ap, sndLine);
    if ((arg = va_arg(ap,int)) == 2)
       OpenLCDWindow((char)(j+3), 48, (char)(k-3), 78, 16, 2, fp);
    else
       OpenLCDWindow((char)(j+3), 18, (char)(k-3), 48, 16, 2, fp);

    gotoxy(1, 1);
    saystr(fstLine, 16);
    gotoxy(1, 2);
    saystr(sndLine, 16);

    do {
      aKey = readspckey();
    } while ((aKey !=  _ESC) && (aKey != _ENT));
    CloseLCDWindow(fp);
    free(p);
    return (aKey ==_ENT);
  }


