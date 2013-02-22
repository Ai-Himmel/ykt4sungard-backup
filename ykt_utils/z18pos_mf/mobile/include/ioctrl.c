 /*********************************************
 **	    HT IO Control extended functions     **
 **     FOR HT2800                           **
 *********************************************/

  #define __ASM       _asm
  #define __IOCTRL    1

  #include <ioctrl.h>
  #include <alloc.h>
  #include <dos.h>

   unsigned int GetIOsts(void)
   {
       unsigned int result=0;
       __ASM {
          mov  bl, 0
          mov  ax, 143ah
          int  10h
          mov  result, cx
        }
       return(result);
   }

   void SetIOsts(unsigned int status)
   {
       __ASM {
          mov  cx, status
          mov  bl, 1
          mov  ax, 143ah
          int  10h
       }
   }

   unsigned int ReadIOPort(void)
   {
     unsigned int result=0;
       __ASM {
          mov  bl, 2
          mov  ax, 143ah
          int  10h
          mov  result, cx
       }
       return(result);
   }

   void SetIOPort(unsigned int value)
   {
       __ASM {
          mov  cx, value
          mov  bl, 3
          mov  ax, 143ah
          int  10h
       }
   }

   void NormalIOsts(void)
   {
       __ASM {
          mov  bl, 4
          mov  ax, 143ah
          int  10h
       }
   }
