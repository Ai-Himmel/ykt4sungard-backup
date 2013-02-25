// VCInter.cpp : Defines the initialization routines for the DLL.
//

/*	�޸ļ�¼

  20031217 dengcb: ����69#-�ͻ����Բ�ѯ
  20040405 dengcb: 65#(�ͻ��˳�)��������ί�з�ʽ�ĸ�ֵ,
  ��Ϊswitch���˳�ʱ�����Ĭ�ϵ�bank_code2��ֵ
*/

#include "stdafx.h"
#include <afxdllx.h>
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////////////
//  ������Ҫ�ӵ��ļ����ݣ�
#define SPXDLL_EXPORTS	    // �ڹ���ģ���д��ʼ��Ҫ�����������
#include "SpxDllInfo.h"
#include "cpackc.h"

__declspec(dllimport) int GetZxjByScdmZqdm(char *scdm, char *zqdm, char *zxj, double &zxj2);

////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE VCInterDLL = { NULL, NULL };
double  ChangeDouble(double * pd,int len);
int GetInteger(const char * str);
void ChangeIdFromPhone(char *PhoneId, char sAccountsId[20]);
void ChangeIdFromPhone2(char *PhoneId, char sAccountsId[20]);

extern char *ltrim(char *str);
extern char *rtrim(char *str);
extern char *trim(char *str);

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
	
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("VCInter.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(VCInterDLL, hInstance))
			return 0;
		
		new CDynLinkLibrary(VCInterDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("VCInter.DLL Terminating!\n");
		AfxTermExtensionModule(VCInterDLL);
	}
	return 1;   // ok
}

// ���� CPack ��
BOOL CommFormPackFunc(int nFunction, char *buffer, CSList *plist, void *pvoid, int DestNO)
{
	ST_CPACK_C *pstpack=(ST_CPACK_C *)pvoid;
	//memset(&(pstpack->pack),0,sizeof(ST_PACKDATA_C));
	char sOldAppendPwd1[9]="", sOldAppendPwd2[9]="";
	char sNewAppendPwd1[9]="", sNewAppendPwd2[9]="";
	char sAccountsId[22] = "";						// ת���Ժ���ʺ�
	int  iLen=0;
	int tmp = 0;
	switch(nFunction) 
	{	
	case 11://������ϸ��ѯ	847184
		/*
		1.	���ܺţ�11
		2.	�����ַ
		3.	����
		4.	��ʱ���ã���գ�
		5.	����
		6.	���Ҵ���
		7.	��ʼ����
		8.	��ֹ����
		9.	������ˮ��
		10.	��෵������ - 10��
		11.	ί�з�ʽ
		*/
		tmp = GetInteger(plist->GetAt(7));
		AddFieldI_C(pstpack, F_LVOL0, tmp);		// ����
		AddField_C(pstpack, F_SDATE0, plist->GetAt(9));		// ��ʼ����
		AddField_C(pstpack, F_SDATE1, plist->GetAt(10));	// ��������
		tmp = GetInteger(plist->GetAt(12));
		AddFieldI_C(pstpack, F_LVOL1, tmp);		// ��ѯ���ؼ�¼��
		return TRUE;
	case 12: // ��ʧ��  847102
		 /*
		 1.	���ܺţ�12
		 2.	�����ַ
		 3.	����
		 4.	��ʱ���ã���գ�
		 5.	����
		 6.	����
		 7. �ͻ���
		 8.	ί�з�ʽ
		*/
		// TODO : �޸Ĺ�ʧ������
		tmp = GetInteger(plist->GetAt(7));
		AddFieldI_C(pstpack, F_LVOL1, tmp);	// ����
		AddField_C(pstpack, F_SCUST_LIMIT, "system");
		return TRUE;
	case 9:		//��ѯ���  700001
		/*
		*  1. ���ܺ� 9 
		*  2. �����ַ
		*  3. ���Ҵ���(����)
		*  4. ����
		*  5. ����
		*  6. ί�з�ʽ
		*/
		tmp = GetInteger(plist->GetAt(7));
        AddFieldI_C(pstpack, F_LVOL3, tmp);	// ����
		return TRUE;
	case 901:	//�û���¼ 700000
		//////////////////////////////////////////////////////////////////////////
		// ����
		//AfxMessageBox(plist->GetAt(7));						
		//////////////////////////////////////////////////////////////////////////
		ChangeIdFromPhone2(plist->GetAt(7), sAccountsId);	// ת���ʺţ�������ת��ĸ, ͨ������
		AddField_C(pstpack, F_SSTATUS0, plist->GetAt(5));	// �˺����
//		AddField_C(pstpack, F_SCUST_NO, plist->GetAt(7));	// �ͻ���
//		AddField_C(pstpack, F_SNAME, sAccountsId);			// �˺�, ���ϴ�ѧ��
		AddField_C(pstpack, F_SCUST_AUTH, sAccountsId);		// 2008������
//		AfxMessageBox(sAccountsId);
		//AddField_C(pstpack, F_LVOL0, plist->GetAt(7));	// ����
		AddField_C(pstpack, F_SBANK_PWD, plist->GetAt(8));	// ����
		return TRUE;
	}
	return FALSE;
}

// �ֽ� CPack ���� SPX Э��
BOOL CommFormStrFunc(int nFunction, char *buffer, CSList *plist, void *pvoid, bool bFirstRow)
{
	// buffer ��СΪ 4k 
   	ST_CPACK_C *pstpack=(ST_CPACK_C *)pvoid;
	switch(nFunction) {
	case 9:		//����ѯ
		sprintf(buffer, "A|%s|%s|%s|%.2f|%.2f|%s|%.2f|", plist->GetAt(1), plist->GetAt(2),
			"Y",					// �ɹ���־
			pstpack->pack.damt0,	// �����
			pstpack->pack.damt1,	// �������
			"RMB",					// ��������
			pstpack->pack.damt2		// �������
			);
		return TRUE;
	case 11:// ������ϸ��ѯ	 847180
		sprintf(buffer,"A|%s|%s|%s|%d|%s|%.2f|%.2f|%s|%d|%d|%s|",plist->GetAt(1),plist->GetAt(2)
			,pstpack->pack.sdate0					// ��������
			,pstpack->pack.lvol0					// �������
			,pstpack->pack.scusttypes				// ����˵��
			,pstpack->pack.damt0					// ���׽��
			,pstpack->pack.damt1					// ���׺����
			,pstpack->pack.sbankname2				// ���׵ص�
			,pstpack->pack.lvol1					// ��ˮ��
			,1										// ���Ҵ���
			,"RMB"									// ��������
			);
		//sprintf(buffer,"%s|%s|%s|",plist->GetAt(1),plist->GetAt(2),"Y");
		return TRUE;
	case 12: // ����ʧ
		sprintf(buffer,"A|%s|%s|%s|",plist->GetAt(1),plist->GetAt(2)
			,"Y"									// �ɹ���־
			);
		return TRUE;
	case 901:	//�û���¼
		sprintf(buffer,"A|%s|%s|%s|%s|%d|%s|%d|%d|%s|%s|%s|%s|%s|%d|%s|",plist->GetAt(1),plist->GetAt(2)
			,"Y"										// �ɹ���־
			,pstpack->pack.scusttypes					// ����
			,pstpack->pack.lvol2						// �˺����
			,pstpack->pack.sbank_acc					// ԭ����������ʺŴ���
			,1											// ���Ҵ���
			,pstpack->pack.lvol0						// ����
			,pstpack->pack.scert_addr					// ����
			,pstpack->pack.sbankname					// ���Ű༶����
			,pstpack->pack.sdate0						// ϵͳ��������
			,pstpack->pack.sstatus1						// ϵͳ����״̬
			,pstpack->pack.sbankname2					// ϵͳ����״̬����
			,pstpack->pack.lvol1						// �ͻ���
			,pstpack->pack.scust_auth					// ѧ��
			);
		return TRUE;
	}
	return FALSE;
}

BOOL InitFunc(char *IniFileName)
{
	return TRUE;
}

BOOL ExitFunc(void)
{
	return TRUE;
}

DLLFUNCENTRY  DllFunctions[]={
	// { 5, "�޸�����", 847111, 1, NULL, NULL},			// del 
	{ 9, "����ѯ", 700001, 1, NULL, NULL},			// ok
	{ 11, "������ϸ", 700002, 2, NULL, NULL},			// ok
	{ 12, "��ʧ", 847102, 1, NULL, NULL},				// test
	{ 901, "��¼", 700000, 1, NULL, NULL},				// dev
};

DLLINFO  stDllInfo={
		4,
		DllFunctions,
		InitFunc,
		ExitFunc,
		CommFormPackFunc,
		CommFormStrFunc,
		9,901,
		"VCInter", // ��ʾ�Ǵ��й�̨
		100,
		200505015,
		"����"
};

SPXDLL_API DLLINFO *GetDllInfo(void)
{
	return (&stDllInfo);
}


/* ------------------------------------------------------------------------- */
/*     �������룬������λ��Чλ     */
double  ChangeDouble(double * pd,int len)

{
	double d=0.00,d2=0.00;
	d = *pd;
	d2 =floor(d*100);
	if ( (d*100 - d2) >=0.5 )
		*pd=ceil(d*100)/100;
	else
		*pd =floor(d*100)/100;
	return  *pd;
}

int GetInteger(const char * str)
{
	int ret = atoi(str);
	return ret;
}
//////////////////////////////////////////////////

char PhoIdToAccId[8][8] = 
{
		'A', 'B', 'C', 'a', 'b', 'c', '$', '$',
		'D', 'E', 'F', 'd', 'e', 'f', '$', '$',
		'G', 'H', 'I', 'g', 'h', 'i', '$', '$',
		'J', 'K', 'L', 'j', 'k', 'l', '$', '$',
		'M', 'N', 'O', 'm', 'n', 'o', '$', '$',
		'P', 'Q', 'R', 'S', 'p', 'q', 'r', 's',
		'T', 'U', 'V', 't', 'u', 'v', '$', '$',
		'W', 'X', 'Y', 'Z', 'w', 'x', 'y', 'z'
};		// $������û���������

void ChangeIdFromPhone2(char *pcPhoneId, char sAccountsId[22])
{
	char *pcPosition = NULL;
	int nCountForAccounts = 0;
	int nRow = 0,
		nCol = 0;

	while (*pcPhoneId != '\0')
	{
		if (*pcPhoneId != '*')
		{
			pcPosition = pcPhoneId;		// ��ʼλ��
			sAccountsId[nCountForAccounts] = *pcPosition;		// û�в��������
		}
		else	// * + row + col���ڲ�������� *23 == C *26 == c ...........
		{
			pcPosition = ++pcPhoneId;
			if (*pcPosition != '\0' && *(++pcPhoneId) != '\0')	// *�����2λ����'\0'
			{
				nRow = *pcPosition - 0x30;
				nCol = *pcPhoneId - 0x30;
				sAccountsId[nCountForAccounts] = PhoIdToAccId[nRow - 2][nCol - 1];	// ��-2, ��-1
			}
			else
			{
				sAccountsId[nCountForAccounts] = '$';
			}
		}
		pcPosition = ++pcPhoneId;
		nCountForAccounts++;
	}
	// ҵ����Ҫ, ���һ���ַ�����'#'
	if ('#' == *(--pcPosition))
	{
		sAccountsId[--nCountForAccounts] = '\0';
	}
	return ;
}

















