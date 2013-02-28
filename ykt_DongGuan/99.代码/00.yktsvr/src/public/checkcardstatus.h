/* --------------------------------------------
 * ��������: 2008-06-15
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ��鿨״̬ģ��
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/
#ifndef  __CHECKCARDSTATUS_H_
#define  __CHECKCARDSTATUS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "bufunc.h"
#include "errdef.h"
#include "pubdef.h"
#include "esqlc.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include <iostream>
#include <sstream>
#include <set>
enum CARDEXCEPTSTATUS {EXPIRED,LOST,FROZE,LOCKED};

class CCheckCardStatus
{
private:
	T_t_card _card; 
	bool _result;
	std::string _msg;
public:
	CCheckCardStatus(){};
	CCheckCardStatus(const T_t_card& card);
	const char*  GetCheckMsg();
	const char* TranslateCardstatus(int cardstatus);
	bool OnlineTransCheck();
	bool GetResult();
	bool VerifyCardStatus(int cardstatus);
	bool VerifyApplyType(int applytype);
};
inline CCheckCardStatus::CCheckCardStatus(const T_t_card& card)
{
	_result = false;
	memcpy(&_card,&card,sizeof(card));
}
inline const char* CCheckCardStatus::GetCheckMsg()
{
	return _msg.c_str();
}
inline bool CCheckCardStatus::GetResult()
{
	return _result;
}
//���׼��
inline bool CCheckCardStatus::OnlineTransCheck()
{
	_result=false;
	CAccTrans& ats =CAccTrans::GetInst();
	if(_card.delflag>0)
	{
		_msg="��������";
		return _result;
	}
	if(_card.expdate<ats.hostdate)
	{
		_msg="�ÿ��ѹ���Ч��";
		return _result;
	}
	if(_card.lossflag)
	{
		_msg="���ѹ�ʧ";
		return _result;
	}	
	if(_card.status != CARDSTATUS_NORMAL)
	{
		_msg=TranslateCardstatus(_card.status);
		return _result;
	}	
	_result=true;
	return _result;
}
//���뿨״̬
inline const char* CCheckCardStatus::TranslateCardstatus(int cardstatus)
{
	std::string s;
	switch(cardstatus)
	{
		case CARDSTATUS_NORMAL:	
			s="�ÿ�״̬����";
			break;
		case CARDSTATUS_CLOSE:
			s="�ÿ�״̬Ϊ������";
			break;
		case CARDSTATUS_NEW:		
			s="�ÿ�״̬Ϊ������";
			break;
		case CARDSTATUS_APROVE:		
			s="�ÿ�״̬Ϊ�����";
			break;
		case CARDSTATUS_MAKE:
			s="�ÿ�״̬Ϊ���ƿ�";
			break;
		case CARDSTATUS_ISSUE:
			s="�ÿ�״̬Ϊ������";
			break;
		case CARDSTATUS_CHANGE:	
			s="�ÿ�״̬Ϊ������";
			break;
		case CARDSTATUS_RENEW:	
			s="�ÿ�״̬Ϊ������";
			break;
		case CARDSTATUS_LOSS:
			s="�ÿ�״̬Ϊ����ʧ";
			break;
		case CARDSTATUS_UNLOST:
			s="�ÿ�״̬Ϊ�����";
			break;
		case CARDSTATUS_LOST:
			s="�ÿ�״̬Ϊ��ʧ";
			break;
		case CARDSTATUS_CLOSED:
			s="�ÿ�״̬Ϊ����";
			break;
		default:
			s="�ÿ�״̬�쳣";
			break;			
	}
	return s.c_str();
}
inline bool CCheckCardStatus::VerifyCardStatus(int cardstatus)
{
	_result=false;
	/*
	if(_card.delflag)
	{
		_msg="��������";
		return _result;
	}
	*/
	if(_card.status != cardstatus)
	{
		_msg=TranslateCardstatus(_card.status);
		return _result;
	}	
	_result=true;
	return _result;
}
inline bool CCheckCardStatus::VerifyApplyType(int applytype)
{
	switch(applytype)
	{
		case APPLYTYPE_CHANGECARD:
		case APPLYTYPE_LOSTCARD:
			if(!VerifyCardStatus(CARDSTATUS_NORMAL))
				return _result;
			break;
		case APPLYTYPE_UNLOSTCARD:
			if(!VerifyCardStatus(CARDSTATUS_LOSS))
				return _result;
			break;
		case APPLYTYPE_RENEWCARD:
			if(_card.delflag)
			{
				//��������				
				if(_card.status != CARDSTATUS_CLOSED)
				{
					_result=false;
					_msg=TranslateCardstatus(_card.status);
					return _result; 			
				}
				_result=true;
				break;				
			}
			else
			{
				//����
				if(!VerifyCardStatus(CARDSTATUS_LOSS))
					return _result;
			}
			break;
		case APPLYTYPE_CLOSECARD:
			if(_card.lossflag)
			{
				if(!VerifyCardStatus(CARDSTATUS_LOSS))
					return _result;
			}
			else
			{
				if(!VerifyCardStatus(CARDSTATUS_NORMAL))
					return _result;
			}
			break;
	}
	return _result;	
}
#endif
