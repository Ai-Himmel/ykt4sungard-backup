#include "ks_cpumf_cardtype.h"
#include "global_func.h"
#include "yktclt.h"
#include "log.h"
#pragma comment (lib, "bccclt.lib")

typedef int (KSAPI *mf_register_cardtype_op)(ks_cardtype_base *&op);

mf_register_cardtype_op mf_reg_op = NULL;

static ks_cpumf_cardtype CardTypeMb;


ks_cpumf_cardtype::ks_cpumf_cardtype():CCardType(),m_childct(NULL)
{
	mf_cardtype_handle=NULL;
	m_nReadCardType=RCT_CPU;
	set_cardtype_name("ks_cpumf_cardtype.dll");
	if(load_mfcard_type()!=0)
		throw std::exception();
}
ks_cpumf_cardtype::~ks_cpumf_cardtype()
{
	if(mf_cardtype_handle!=NULL)
		FreeLibrary(mf_cardtype_handle);
}
int ks_cpumf_cardtype::InitCardTypeDLL()
{
	int ret;
	ret = CCardType::InitCardTypeDLL();
	if(ret)
		return ret;
	m_childct->set_license(this->m_license);
	m_childct->SetPSAMCardType(this->GetPSAMCardType());
	return m_childct->InitCardTypeDLL();
}
int ks_cpumf_cardtype::load_mfcard_type()
{
	char path[1024];
	char exec_path[2048]="";
	char *p;
	GetModuleFileName(NULL,path,1023);
	p = strrchr(path,'\\');
	if(p)
	{
		//strncpy(exec_path,path,p-path+1);
		*p = 0;
	}
	sprintf(exec_path,"%s\\%s",path,"ks_mfcard.dll");
	mf_cardtype_handle = LoadLibrary(exec_path);
	if(!mf_cardtype_handle)
	{
		if( !GetSystemDirectory(path,sizeof(path)-1) )
		{
			SET_ERR("获取系统路径失败");
			return -1;
		}
		sprintf(exec_path,"%s\\%s",path,"ks_mfcard.dll");
		mf_cardtype_handle = LoadLibrary(exec_path);
		if(!mf_cardtype_handle)
		{
			SET_ERR("无法加载mfcardtype");
			return -1;
		}
	}
	mf_reg_op = (mf_register_cardtype_op)GetProcAddress(mf_cardtype_handle,"register_cardtype_op");
	if(mf_reg_op==NULL)
	{
		SET_ERR("无法加载mfcardtype,接口函数错误");
		return -1;
	}
	mf_reg_op(m_childct);
	return 0;
}

void  ks_cpumf_cardtype::Attach(ks_device_op_t *device,ks_reader_dev_t *reader,READER_TYPE t)
{
	CCardType::Attach(device,reader,t);
	m_childct->Attach(device,reader,t);
}
/*
int  ks_cpumf_cardtype::AttachDecard(ks_device_op_t *device,ks_reader_dev_t *reader)
{
	int nRet;
	nRet = CCardType::AttachDecard(device,reader);
	if(nRet)
	{
		return nRet;
	}
	return m_childct->AttachDecard(device,reader);
}
*/
int ks_cpumf_cardtype::LoadKeysFromKeyCard(const char *sKeyCardPwd)
{
	char mainkey[36]={0};
	int nRet;
	nRet = CCardType::LoadKeysFromKeyCard(sKeyCardPwd);
	if(nRet)
	{
		return nRet;
	}
	//dec2hex(this->cardtype_buff,16,mainkey);
	//m_childct->AuthDLL(mainkey,0);
	this->SetKeyCard(m_childct);
	return 0;
}
int ks_cpumf_cardtype::InitUserCard(const char *sShowCardNo)
{
	int nRet;
	nRet = CCardType::InitUserCard(sShowCardNo);
	if(nRet)
	{
		return nRet;
	}
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	nRet=m_childct->InitUserCard(sShowCardNo);
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	return 0;
}
int ks_cpumf_cardtype::RestoreFactorySettings()
{
	int nRet;
	nRet = CCardType::RestoreFactorySettings();
	if(nRet)
	{
		return nRet;
	}
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	nRet= m_childct->RestoreFactorySettings();
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	return 0;
}

int ks_cpumf_cardtype::SetFieldReadMode(int fieldid)
{
	int nRet;
	nRet = CCardType::SetFieldReadMode(fieldid);
	if(nRet)
		return nRet;
	nRet= m_childct->SetFieldReadMode(fieldid);
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	return 0;
}
//清除所有字段的读模式
void ks_cpumf_cardtype::ClearAllFieldReadMode()
{
	CCardType::ClearAllFieldReadMode();
	m_childct->ClearAllFieldReadMode();
}
//清除该字段读模式
void ks_cpumf_cardtype::ClearFieldReadMode(int fieldID)
{
	CCardType::ClearFieldReadMode(fieldID);
	m_childct->ClearFieldReadMode(fieldID);

}
int ks_cpumf_cardtype::SetFieldWriteMode(int fieldid)
{
	int nRet;
	nRet = CCardType::SetFieldWriteMode(fieldid);
	if(nRet)
		return nRet;
	nRet = m_childct->SetFieldWriteMode(fieldid);
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	return 0;
}
//设置该字段读写模式
int ks_cpumf_cardtype::SetFieldAllMode(int fieldID)
{
	int nRet;
	nRet = CCardType::SetFieldAllMode(fieldID);
	if(nRet)
		return nRet;
	nRet= m_childct->SetFieldAllMode(fieldID);
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	return 0;
}
//清除该字段写模式
void ks_cpumf_cardtype::ClearFieldWriteMode(int fieldID)
{
	CCardType::ClearFieldWriteMode(fieldID);
	m_childct->ClearFieldWriteMode(fieldID);
}
//清除该字段所有模式
void ks_cpumf_cardtype::ClearFieldAllMode(int fieldID)
{
	CCardType::ClearFieldAllMode(fieldID);
	m_childct->ClearFieldAllMode(fieldID);
}
//清除所有字段的写模式
void ks_cpumf_cardtype::ClearAllFieldWriteMode()
{
	CCardType::ClearAllFieldWriteMode();
	m_childct->ClearAllFieldWriteMode();
}
//清除所有字段的读写模式
void ks_cpumf_cardtype::ClearAllFieldAllMode()
{
	CCardType::ClearAllFieldAllMode();
	m_childct->ClearAllFieldAllMode();
}
int ks_cpumf_cardtype::ReadCard()
{
	m_nReadCardType=RCT_CPU;
	return CCardType::ReadCard();	
}
int ks_cpumf_cardtype::ReadCard(int ReadType)
{
	int nRet=0;
	m_nReadCardType=ReadType;
	switch(m_nReadCardType)
	{
		case RCT_CPU:
			nRet= CCardType::ReadCard();
			break;
		case RCT_MF1:
			nRet=m_childct->doSubRequestCard(NULL);
			if(nRet)
			{
				SET_ERR(m_childct->GetLastErrMsg(NULL));
				return nRet;
			}
			nRet=m_childct->ReadCard();	
			if(nRet)
			{
				SET_ERR(m_childct->GetLastErrMsg(NULL));
				return nRet;
			}
			break;
		case RCT_ALL:
			nRet= CCardType::ReadCard();	
			if(nRet)
				return nRet;
			nRet=m_childct->doSubRequestCard(NULL);
			if(nRet)
			{
				SET_ERR(m_childct->GetLastErrMsg(NULL));
				return nRet;
			}
			nRet=m_childct->ReadCard();	
			if(nRet)
			{
				SET_ERR(m_childct->GetLastErrMsg(NULL));
				return nRet;
			}
			break;
		default:
			nRet= CCardType::ReadCard();	
			break;
	}
	return nRet;	
}
int ks_cpumf_cardtype::WriteCard()
{
	int nRet;
	nRet = CCardType::WriteCard();
	if(nRet)
		return nRet;
	
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	
	nRet = m_childct->WriteCard();
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	return CCardType::RequestCard(NULL);
}

int ks_cpumf_cardtype::SetFieldVal(int FieldID,const char *fieldval)
{
	int nRet;
	nRet = CCardType::SetFieldVal(FieldID,fieldval);
	if(nRet)
		return nRet;
	nRet = m_childct->SetFieldVal(FieldID,fieldval);
	if(nRet)
	{
		SET_ERR(m_childct->GetLastErrMsg(NULL));
		return nRet;
	}
	return 0;
}
int ks_cpumf_cardtype::GetFieldVal(int FieldID,char *fieldval)
{
	int nRet;
	switch(m_nReadCardType)
	{
		case RCT_CPU:
			nRet = CCardType::GetFieldVal(FieldID,fieldval);
			break;
		case RCT_MF1:
			nRet = m_childct->GetFieldVal(FieldID,fieldval);
			if(nRet)
			{
				SET_ERR(m_childct->GetLastErrMsg(NULL));
				return nRet;
			}
			break;
		case RCT_ALL:
			nRet = CCardType::GetFieldVal(FieldID,fieldval);
			if(nRet)
				return nRet;
			nRet = m_childct->GetFieldVal(FieldID,fieldval);
			if(nRet)
			{
				SET_ERR(m_childct->GetLastErrMsg(NULL));
				return nRet;
			}
			break;
		default:
			nRet = CCardType::GetFieldVal(FieldID,fieldval);
			break;
	}	
	return 0;
}
void ks_cpumf_cardtype::SetMifare1Key(const char *sCipherKey)
{
	m_childct->AuthDLL(sCipherKey,1);
}
void ks_cpumf_cardtype::GetSupportCardType(unsigned int cardTypes[],int &cnt)
{
	int i = 0;
	cardTypes[i++] = 0x0101;
	cardTypes[i++] = 0x0300;
	cardTypes[i++] = 0x0400;
	cardTypes[i++] = 0x0409;
	cnt = i;
}
int ks_cpumf_cardtype::checkCardType(int ct)
{
	switch(ct)
	{
	case KS_FIXCARD:
		m_CardTypeCode = 0x0101;
		return 0;
	case KS_CPUCARD:
		m_CardTypeCode = 0x0400;
		return 0;
	case KS_MFCARD:
		m_CardTypeCode = 0x0409;
		return 0;
	default:
		return -1;
	}
}

int ks_cpumf_cardtype::water_publishcard(int watertype,ks_water_pack_t *pack)
{
	int nRet;
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
		return nRet;
	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return -1;
	}
	return m_childct->water_publishcard(watertype,pack);
}
int ks_cpumf_cardtype::water_recyclecard(int watertype)
{
	int nRet;
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
		return nRet;
	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return -1;
	}
	return m_childct->water_recyclecard(watertype);
}
int ks_cpumf_cardtype::water_readmoney(int watertype,ks_water_pack_t *pack)
{
	int nRet;
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
		return nRet;
	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return -1;
	}
	return m_childct->water_readmoney(watertype,pack);
}
int ks_cpumf_cardtype::water_writemoney(int watertype,ks_water_pack_t *pack)
{
	int nRet;
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
		return nRet;
	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return -1;
	}
	return m_childct->water_writemoney(watertype,pack);
}
int ks_cpumf_cardtype::water_publishparamcard(int watertype,ks_water_param_t *param)
{
	int nRet;
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
		return nRet;
	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return -1;
	}
	return m_childct->water_publishparamcard(watertype,param);
}
int ks_cpumf_cardtype::water_recycleparamcard(int watertype)
{
	int nRet;
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
		return nRet;
	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return -1;
	}
	return m_childct->water_recycleparamcard(watertype);
}
int ks_cpumf_cardtype::water_read_paramcard(int watertype,ks_water_param_t *param)
{
	int nRet;
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
		return nRet;
	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return -1;
	}
	return m_childct->water_read_paramcard(watertype,param);
}
int ks_cpumf_cardtype::water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate)
{
	int nRet;
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
		return nRet;
	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return -1;
	}
	return m_childct->water_publish_legacycard(watertype,fee_rate);
}
int ks_cpumf_cardtype::water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate)
{
	int nRet;
	nRet=m_childct->doSubRequestCard(NULL);
	if(nRet)
		return nRet;
	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return -1;
	}
	return m_childct->water_read_legacycard(watertype,fee_rate);
}
void ks_cpumf_cardtype::DumpSectData(int watertype)
{
	int nRet;
	nRet = m_childct->doSubRequestCard(NULL);
	if(nRet)
		return;

	if(m_childct->m_defaultCardType != KS_MFCARD)
	{
		SET_ERR("该卡类型不支持该操作");
		return;
	}
	m_childct->DumpSectData(watertype);
}
//////////////////////////////////////////////////////////////////////////
int KSAPI register_cardtype_op(ks_cardtype_base *&op)
{
	op = &CardTypeMb;
	return 0;
}
