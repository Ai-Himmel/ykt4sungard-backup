/* --------------------------------------------
 * 创建日期: 2008-06-15
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 检查卡状态模块
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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
//交易检查
inline bool CCheckCardStatus::OnlineTransCheck()
{
	_result=false;
	CAccTrans& ats =CAccTrans::GetInst();
	if(_card.delflag>0)
	{
		_msg="卡已销户";
		return _result;
	}
	if(_card.expdate<ats.hostdate)
	{
		_msg="该卡已过有效期";
		return _result;
	}
	if(_card.lossflag)
	{
		_msg="卡已挂失";
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
//翻译卡状态
inline const char* CCheckCardStatus::TranslateCardstatus(int cardstatus)
{
	std::string s;
	switch(cardstatus)
	{
		case CARDSTATUS_NORMAL:	
			s="该卡状态正常";
			break;
		case CARDSTATUS_CLOSE:
			s="该卡状态为待销户";
			break;
		case CARDSTATUS_NEW:		
			s="该卡状态为新申请";
			break;
		case CARDSTATUS_APROVE:		
			s="该卡状态为待审核";
			break;
		case CARDSTATUS_MAKE:
			s="该卡状态为待制卡";
			break;
		case CARDSTATUS_ISSUE:
			s="该卡状态为待发行";
			break;
		case CARDSTATUS_CHANGE:	
			s="该卡状态为待换卡";
			break;
		case CARDSTATUS_RENEW:	
			s="该卡状态为待补办";
			break;
		case CARDSTATUS_LOSS:
			s="该卡状态为待挂失";
			break;
		case CARDSTATUS_UNLOST:
			s="该卡状态为待解挂";
			break;
		case CARDSTATUS_LOST:
			s="该卡状态为挂失";
			break;
		case CARDSTATUS_CLOSED:
			s="该卡状态为销户";
			break;
		default:
			s="该卡状态异常";
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
		_msg="卡已销户";
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
				//销户补办				
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
				//补办
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
