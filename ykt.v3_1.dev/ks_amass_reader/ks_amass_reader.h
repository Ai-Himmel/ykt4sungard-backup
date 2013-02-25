#ifndef _KS_AMASS_READER_H_
#define _KS_AMASS_READER_H_

#include "kscomlib.h"

class AmassReader : public CComSmart
{
public:
	AmassReader();
	~AmassReader();
	bool PostRecv(unsigned char *lpBuffer, int nBufSize, long nTimeOut);	
};

#endif // _KS_AMASS_READER_H_
