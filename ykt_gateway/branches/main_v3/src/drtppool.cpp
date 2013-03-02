#include "ksglobal.h"
#include "drtppool.h"
#include "ksgateway.h"

//////////////////////////////////////////////////////////////////////////
// KSG_DRTP_Creator
KSG_DRTP_Creator::KSG_DRTP_Creator()
{
	//empty
}
int KSG_DRTP_Creator::get_max()
{
	return max_;
}
CDRTPHelper* KSG_DRTP_Creator::create_new()
{
	const KSGConfig *config = theGlobalGateWay->GetConfig();
	return new CDRTPHelper(config->_drtpSvrIP.c_str()
		,config->_drtpSvrPort,config->_drtpMainFunc,config->_drtpNo);
}
void KSG_DRTP_Creator::delete_one(CDRTPHelper *p)
{
	delete p;
}

