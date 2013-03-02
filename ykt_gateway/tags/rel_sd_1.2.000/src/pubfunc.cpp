#include "stdafx.h"
#include "pubfunc.h"
#include "ksgateway.h"

int KsgGetSystemParam(int param,std::string& value)
{
	DRTPPoolType::SmartObject obj;
	obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		obj->SetRequestHeader(KSG_GET_SYSTEM_PARAM);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SCUST_LIMIT,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
		obj->AddField(F_LVOL0,param);
		if(obj->Connect())
		{
			ACE_DEBUG((LM_ERROR,"连接应用服务器失败[%s]",obj->GetErrMsg().c_str()));
			return -1;
		}
		if(obj->SendRequest(500))
		{
			ACE_DEBUG((LM_ERROR,"发送请求失败[%s]",obj->GetErrMsg().c_str()));
			return -1;
		}
		if(obj->HasMoreRecord())
		{
			ST_PACK * data = obj->GetNextRecord();
			value = data->scard0;
			return 0;
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"查询失败[%s]",obj->GetReturnMsg().c_str()));
			return -1;
		}
	}
	return -1;
}

