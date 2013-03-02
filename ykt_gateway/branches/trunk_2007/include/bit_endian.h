#ifndef _KSG_BIT_ENDIAN_H_
#define _KSG_BIT_ENDIAN_H_

#include "kstypes.h"

inline void _reverse_buf(void* ibuf,int len)
{
	unsigned char * ibytes = static_cast<unsigned char*>(ibuf);
	for(int i = 0;i < len / 2; ++i)
	{
		unsigned t = ibytes[i];
		ibytes[i] = ibytes[len - i - 1];
		ibytes[len - i -1] = t;
	}
}

#ifdef X86_ARCH

#define INT_2_BUF(v,b) do{ int _v = v; memcpy(b,(void*)&_v,sizeof(int)); } while(0)
#define SHORT_2_BUF(v,b) do{ short _v = (v); memcpy(b,(void*)&_v,sizeof(short)); } while(0)
#define LONG_2_BUF(v,b) INT_2_BUF(v,b)

#define BUF_2_INT(v,b) do{ memcpy((void*)&(v),b,sizeof(int)); } while(0)
#define BUF_2_SHORT(v,b) do{ memcpy((void*)&(v),b,sizeof(short)); } while(0)

#define BUF_2_LONG(v,b) BUF_2_INT(v,b)

#define INT_2_BUF_LE(v,b) INT_2_BUF(v,b)
#define SHORT_2_BUF_LE(v,b) SHORT_2_BUF(v,b)
#define LONG_2_BUF_LE(v,b) LONG_2_BUF(v,b)

#define BUF_2_INT_LE(v,b) BUF_2_INT(v,b)
#define BUF_2_SHORT_LE(v,b) BUF_2_SHORT(v,b)
#define BUF_2_LONG_LE(v,b) BUF_2_LONG(v,b)

#define INT_2_BUF_BE(v,b) do{ INT_2_BUF(v,b); _reverse_buf((void*)b,sizeof(int));} while(0)
#define SHORT_2_BUF_BE(v,b) do{ SHORT_2_BUF(v,b); _reverse_buf((void*)b,sizeof(short));} while(0)
#define LONG_2_BUF_BE(v,b) do{ LONG_2_BUF(v,b); _reverse_buf((void*)b,sizeof(long));} while(0)

#define BUF_2_INT_BE(v,b) do{ _reverse_buf((void*)b,sizeof(int)); BUF_2_INT(v,b); } while(0)
#define BUF_2_SHORT_BE(v,b) do{ _reverse_buf((void*)b,sizeof(short)); BUF_2_SHORT(v,b); } while(0)
#define BUF_2_LONG_BE(v,b) do{ _reverse_buf((void*)b,sizeof(long)); BUF_2_LONG(v,b); } while(0)

#elif SPARC_ARCH


#define INT_2_BUF(v,b) do{ int _v = v; memcpy(b,(void*)_v,sizeof(int));_reverse_buf((void*)b,sizeof(int));} while(0)
#define SHORT_2_BUF(v,b) do{ short _v = v;memcpy(b,(void*)_v,sizeof(short));_reverse_buf((void*)b,sizeof(short));} while(0)

#elif PWOERPC_ARCH

#endif

#endif // _BIT_ENDIAN_H_


