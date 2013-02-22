// CardFun.h: interface for the CCardFun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARDFUN_H__74CCB31D_32F2_4DC5_88C9_D36931611A71__INCLUDED_)
#define AFX_CARDFUN_H__74CCB31D_32F2_4DC5_88C9_D36931611A71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCardFunction  
{
public:
	int ReadAuthorWorkKeyAndFlag();
	int ResetAuthCard();
	int InitAuthCard();
//	void TestComOpen();
	int ReadCardInformation();
	int ModifyShowCardId();
	int ModifyCardId();
	int ReadAuthCardByMan();
	int ReadAuthCardByCard();
	int OpenCom();
	int ModifySepNo();
	CCardFunction();
	virtual ~CCardFunction();

private:
	bool m_is_com_open;
	BYTE m_main_key[9];
	bool m_is_auth;
	int m_card_id;
//	CExceptionErr *err_exce; 
};

#endif // !defined(AFX_CARDFUN_H__74CCB31D_32F2_4DC5_88C9_D36931611A71__INCLUDED_)
