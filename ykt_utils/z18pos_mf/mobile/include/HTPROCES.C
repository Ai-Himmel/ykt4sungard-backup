 /*********************************************
 **	    HT Process Control Functions     **
 *********************************************/

  #define __ASM       _asm
  #define __HTPROCESS 1

  #include "htproces.h"
  #include <stdlib.h>

  char chiName[34]={0};
  char engName[34]={0};

  void SetorSwtProcess(unsigned char ProcType,
                       char *ChiProcName, char *EngProcName)
  {
    int  i;

    for (i=0; (i<33)&&(ChiProcName[i]!=0); i++)
      chiName[i+1]=ChiProcName[i];
    chiName[0]=i;
    for (i=0; (i<33)&&(EngProcName[i]!=0); i++)
      engName[i+1]=EngProcName[i];
    engName[0]=i;

    __ASM {
      lea  si, chiName
      lea  di, engName
      push ds
      pop  es
      mov  al, ProcType
      xor  ah, ah
      int  4ch
    }
  }



  unsigned int  SwtProcess(unsigned char EndSelf, char _far *EngProcName)
  {
    int result=0;
    __ASM  {
      mov   al, EndSelf
      les   di, EngProcName
      mov   ah, 1
      int   4ch
      jc    _end
      not   result
    }
    _end:
    return(result);
  }

  unsigned int execsub(char _far *pathname,  char _far *commdln)
  {
    unsigned result=0;
    unsigned i;
    char     command[128];

    struct execstru {
      unsigned int    segenv;
      char _far       *commdln;
      unsigned int    fcb1ofs;
      unsigned int    fcb1seg;
      unsigned int    fcb2ofs;
      unsigned int    fcb2seg;
    }  execpara;

    for (i=0; ((commdln[i]!=0)&&(i<126)); i++)
      command[i+1]=commdln[i];
    command[i+1]=0x0d;
    command[0]=i;

    execpara.commdln=command;

    __ASM {
      mov  es, _psp
      mov  ax, es:[002ch]
      mov  i, ax
    }

    execpara.segenv=i;
    execpara.fcb1ofs=0x005c;
    execpara.fcb1seg=_psp;
    execpara.fcb2ofs=0x006c;
    execpara.fcb2seg=_psp;

    __ASM {
      lea  bx, execpara
      push ss
      pop  es
      mov  ax, 4b00h
      push ds
      lds  dx, pathname
      int  21h
      pop  ds
      jnc  __end
      mov  result, ax
    }
    __end:
    return(result);
  }



