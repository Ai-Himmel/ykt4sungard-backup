#include "stdafx.h"
#include <ace/ACE.h>
#include <ksgateway.h>

int ACE_TMAIN(int, ACE_TCHAR *[])
{
	KSGateway gateway;
	KsgStartServer(&gateway);
	system("pause");
	return 0;
}
