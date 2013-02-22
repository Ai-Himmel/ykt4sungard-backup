#ifndef _KS_ELITEL_READER_H_
#define _KS_ELITEL_READER_H_

#include "kscomlib.h"

class CElitelCom : public CComSmart
{
public:
	CElitelCom();
	~CElitelCom();
	bool PostRecv(unsigned char *lpBuffer, int nBufSize, long nTimeOut);	
};


#endif // _KS_ELITEL_READER_H_

