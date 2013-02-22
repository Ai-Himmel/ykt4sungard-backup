 /*********************************************
 **	    HTOS extended functions	     **
 *********************************************/

  #define __ASM       _asm
  #define __HLPREG    0x0ff

  #include <htosex.h>

  void reghlpsource(char _far * HlpFileNameStrs)
  {
    __ASM {
            les  di, HlpFileNameStrs
            int __HLPREG
    }
  }

