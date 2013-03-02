#ifndef _SMARTBLACKLISTMEMORYOPER__H_
#define _SMARTBLACKLISTMEMORYOPER__H_

class CSmartBlackMemoryOper
{
public:
	CSmartBlackMemoryOper();
	~CSmartBlackMemoryOper();
	bool	SMT_CheckBlackCard (int nCardNo);	//判断卡号是否为黑卡
	bool	SMT_InsertBlackCard(int nCardNo);	//向内存块中增加黑卡
	bool	SMT_DeleteBlackCard(int nCardNo);	//从内存块中删除黑卡	
};
#endif