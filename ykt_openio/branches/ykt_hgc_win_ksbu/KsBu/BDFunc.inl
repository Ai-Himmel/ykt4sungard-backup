#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  ��ÿ��ҵ��������б�������������һ�У���ϸ�����ʾ�ĺ��壬��BDefine.h�е�������
   {1000     ,FTestProc   ,"Demo for SQC ҵ��������д����"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {���ܺ�   ,���̺���>    ,"��������"                                     ,"�����Ա����"       ,���ȼ�,false,0,0,0,0,0},
*/
// �����г����кϷ���ҵ������̺����б�
#ifdef __cplusplus
extern "C" {
#endif
int FTestIReply(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);
int FTestBCCShm(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
int FBCCShmMultiRows(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
int FTestBUShm(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
int FBCCShmGetRecord(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
int FBCCShmSetRecord(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);

// ������: FTestBCCIntCall
// ���  : ������ 2005-9-22 11:07:44
// ����  : �ù��ܺ�1013����BCC��IntCall/IntCallNext��RACall/RACallNext�Ĺ���
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack��vsmess=����ģ£���ţ��������RACall/RACallNext
// ����  : int *iRetCode
// ����  : char *szMsg
int FTestBCCIntCall(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);

// ������: FTestBCCIntTransfer
// ���  : ������ 2005-9-23 15:42:19
// ����  : �ù��ܺ�1013����BCC��IntTransfer��RATransfer�Ĺ���
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack: vsmess=����ģ£���ţ��������RATransfer
// ����  : int *iRetCode
// ����  : char *szMsg
int FTestBCCIntTransfer(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);


// ������: FTestBCCExtCall
// ���  : ������ 2005-9-24 12:28:40
// ����  : ��1013���ܲ����������
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack : lvol0-sourceno; lvol1-destno; lvol2-funcno; vsmess-BCCSHMWrite�ļ�¼��
// ����  : int *iRetCode
// ����  : char *szMsg
int FTestBCCExtCall(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);


// ������: FTestBCCExtTransfer
// ���  : ������ 2005-9-24 12:31:15
// ����  : ��1013���ܲ����ⲿת������
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack : lvol1-destno; lvol2-funcno; vsmess-BCCSHMWrite�ļ�¼��
// ����  : int *iRetCode
// ����  : char *szMsg
int FTestBCCExtTransfer(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);


// ������: FTestPushData
// ���  : ������ 2005-9-25 11:30:31
// ����  : ��1010�������������͹��ܵĸ������
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack:lvol0=sourceno,lvol1=destno,lvol2=funcno
// ����  : int *iRetCode
// ����  : char *szMsg
int FTestPushData(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);

// ������: FTestBURunTime
// ���  : ������ 2005-9-27 15:06:29
// ����  : Ϊ�˲���BCC�ж�BU���е�MAXRUNTIME�Ƿ���˵��������
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack : vsmess-hold time in second
// ����  : int *iRetCode
// ����  : char *szMsg
int FTestBURunTime(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
/*
int FTestProc(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);
int FTestMultiRows(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int FTestExtCall(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int FTestMultiCols(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);
*/


// ������: FGetFile
// ���  : ������ 2005-10-19 10:30:34
// ����  : ��BU�������ļ�
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack : vsmess - ����Ի����·�����ļ�
// ����  : int *iRetCode
// ����  : char *szMsg
int FGetFile(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);



// ������: FPTestExtCall
// ���  : ������ 2005-10-25 14:45:42
// ����  : ��1010����ExtCall���ٶ�
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rPack : lvol0 - sno; lvol1 - dno; lvol2 - fno
// ����  : int *iRetCode
// ����  : char *szMsg
int FPTestExtCall(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);


// ������: FPTestIntCall
// ���  : ������ 2005-10-25 14:47:31
// ����  : ��1010����IntCall/RACall���ٶ�
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rPack: vsmess - �ڲ�����BU��ID���ձ�ʾ��RACall
// ����  : int *iRetCode
// ����  : char *szMsg
int FPTestIntCall(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);


// ������: FPTestExtTransfer
// ���  : ������ 2005-10-25 14:49:29
// ����  : ��1010����ExtTransfer���ٶ�
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rPack: lvol1-dno, lvol2-fno
// ����  : int *iRetCode
// ����  : char *szMsg
int FPTestExtTransfer(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);



// ������: FPTestIntTransfer
// ���  : ������ 2005-10-25 14:51:13
// ����  : ��1010����IntTransfer/RATransfer���ٶ�
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rPack: vsmess - �ڲ�����BU��ID���ձ�ʾ��RATransfer
// ����  : int *iRetCode
// ����  : char *szMsg
int FPTestIntTransfer(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);


// ������: FGetBaseOperTimes
// ���  : ������ 2005-10-29 1:51:40
// ����  : 
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack��vsmess - loops
// ����  : int *iRetCode
// ����  : char *szMsg
int FGetBaseOperTimes(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);


// ���ܺź���ԭ������, ����BU�ص�
///////////////////////////////////////////////////////////////////////////////////
int F847307(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847308(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847350(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847351(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847352(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847355(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847356(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847357(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847360(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847361(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
///////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

// �������ݱ�Ϊ��ҵ����Ԫ�ܴ�������кϷ�ҵ������̼�����ز���
TBDefine g_XBDefines[]=
{
	INSERT_FUNCTION(847307 ,F847307, "�����շ��ʻ���ѯ", "lx", 1)
	INSERT_FUNCTION(847308 ,F847308, "�����շ��ʻ�ת��", "lx", 1)
	INSERT_FUNCTION(847350 ,F847350, "�Ϻ�����Ա��Ϣ�Խ�", "lx", 1)
	INSERT_FUNCTION(847351 ,F847351, "���ݿ�������Ϣ�Խ�", "lx", 1)
	INSERT_FUNCTION(847352 ,F847352, "����ר��ˮ��ת�ʶԽ�", "lx", 1)
	INSERT_FUNCTION(847355 ,F847355, "���´�ѧ��ز������ݿ�����", "lx", 1)
	INSERT_FUNCTION(847356 ,F847356, "���´�ѧ���ת�ʲ�ѯ", "lx", 1)
	INSERT_FUNCTION(847357 ,F847357, "���´�ѧ���ת�ʶԽ�", "lx", 1)
	INSERT_FUNCTION(847360 ,F847360, "����������ת�ʲ�ѯ", "lx", 1)
	INSERT_FUNCTION(847361 ,F847361, "����������ת��", "lx", 1)
	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line��Don't remove this line
};
#endif
