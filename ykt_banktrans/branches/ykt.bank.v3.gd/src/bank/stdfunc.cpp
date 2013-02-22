/**********************stdfunc.c***********************/

#include "stdfunc.h"


int ASC2BCD (unsigned char *bcd, const char *asc, int len, int fmt)
{
 int i, odd;
 char c;
 
 odd = len&0x01;
 
 if ( odd && !fmt)
  *bcd++ = (*asc++) & '\x0F';
 
 len >>= 1;

 for (i=0; i<len; i++) {
  c = (*asc++) << 4;
  c |= (*asc++) & '\x0F';
  
  *bcd++ = c;
 }
 
 if ( odd && fmt)
  *bcd = (*asc) << 4;

 return (i+odd);
}

int BCD2ASC (char *asc, const unsigned char *bcd, int len, int fmt)
{
 int i, odd;
 unsigned char c;
 
 odd = len&0x01;
 
 if ( odd && !fmt)
  *asc++ = ((*bcd++)&'\x0F') + '0';

 len >>= 1;

 for (i=0; i<len; i++) {
  c = *bcd++; 
  *asc++ = (c>>4) + '0';
  *asc++ = (c&'\x0F') + '0';
 }
  
 if ( odd && fmt)
  *asc = ((*bcd)>>4) + '0';
 
 return (i+odd);
}

int BCD2INT(int *plen, const unsigned char *bcd, int len, int fmt)
{
 int l=0, i, odd;
 unsigned char c;
 
 odd = len&0x01;
 
 if ( odd && !fmt)
  l = (*bcd++)&'\x0F';

 len >>= 1;

 for (i=0; i<len; i++) {
  c = *bcd++;
  l *= 10;
  l += c>>4;
  l *= 10;
  l += c&'\x0F';
 }
  
 if ( odd && fmt)
 {
  l *= 10;
  l += (*bcd)>>4;
 }

 *plen = l;
 
 return (i+odd);
}


