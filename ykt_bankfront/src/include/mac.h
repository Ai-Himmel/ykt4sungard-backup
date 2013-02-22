#include <stdio.h>

#ifdef __cplusplus

extern "C" {
#endif

void DES(unsigned char *text, unsigned char *mtext, unsigned char *key);
void _DES(unsigned char *text, unsigned char *mtext, unsigned char *key);
void ANSIX99(char	*mac_key,char 	*buf,int 	len,char	*mac);

#ifdef __cplusplus
}
#endif

