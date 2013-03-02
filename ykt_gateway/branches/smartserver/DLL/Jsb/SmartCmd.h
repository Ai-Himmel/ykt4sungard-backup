#ifndef __SMART_CMD_H__
#define __SMART_CMD_H__


//******************************************************************************
//*����: TSSmartMacCmd
//*����: ������ص���������
//******************************************************************************
struct TSSmartMacCmd
{
	char  szMacCode[8];
	char  szCommand[8];
	char  szFormat[32];
	int   nLen;
};

//******************************************************************************
//*����: TSSmartCmdUnit
//*����: ��������
//******************************************************************************
struct TSSmartCmdUnit
{
	long  nCmdIndex;				//��������
	char  szInFormat[32];           //���������ʽ
	char  szOutFormat[32];          //��������ʽ
	char  szCommand[8];             //ͨ�õ�������
	char  szFormat[32];             //ͨ�õ������ʽ
	int   nLen;						//�����峤��

	long  nMacCount;				//��������
	TSSmartMacCmd *pMacCmd;			//������������
};


#endif //__SMART_CMD_H__