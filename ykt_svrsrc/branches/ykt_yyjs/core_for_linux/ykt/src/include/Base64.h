#ifndef __BASE64_H_
#define __BASE64_H_
                                                                                
#define BAD     -1 

#include <ctype.h>
#include <stdio.h>
#include <string.h>

extern void Encode(unsigned char *, const unsigned char *, int);
extern int Decode(char *out, const char *in);

#endif                                    