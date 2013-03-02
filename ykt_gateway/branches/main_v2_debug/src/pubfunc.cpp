
#include "pubfunc.h"
#include "ksgateway.h"
#include "bit_endian.h"

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

int KsgCardID_M1_2_WG(const char *m1_no,char *wg_no,int wg_len)
{
	char temp[10] = "";
	char fmt[10] = "";
	unsigned long hi_word,low_word,card_no;
	strncpy(temp,m1_no+2,2);
	strncpy(temp+2,m1_no,2);
	temp[4] = '\0';

	low_word = strtoul(temp,NULL,16);

	strncpy(temp,m1_no+4,2);
	temp[2] = '\0';
	hi_word = strtoul(temp,NULL,16);

	card_no = hi_word * 100000 + low_word;
	
	sprintf(fmt,"%%0%dd",wg_len);
	sprintf(wg_no,fmt,card_no);
	return 0;
}

int KsgCardPhyNo_dec2hex(unsigned long card_no,char phyno[9])
{
	char reverse_phyno[9] = "";
	sprintf(reverse_phyno,"%08X",card_no);
	int i;
	for(i = 0;i < 4;++i)
	{
		strncpy(phyno+i*2,reverse_phyno+(3-i)*2,2);
		//strncpy(phyno+(3-i)*2,reverse_phyno+i*2,2);
	}
	return 0;
}


