#ifndef _SMARTBLACKLISTMEMORYOPER__H_
#define _SMARTBLACKLISTMEMORYOPER__H_

class CSmartBlackMemoryOper
{
public:
	CSmartBlackMemoryOper();
	~CSmartBlackMemoryOper();
	bool	SMT_CheckBlackCard (int nCardNo);	//�жϿ����Ƿ�Ϊ�ڿ�
	bool	SMT_InsertBlackCard(int nCardNo);	//���ڴ�������Ӻڿ�
	bool	SMT_DeleteBlackCard(int nCardNo);	//���ڴ����ɾ���ڿ�	
};
#endif