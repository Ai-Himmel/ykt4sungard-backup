#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  ��ÿ��ҵ��������б�������������һ�У���ϸ�����ʾ�ĺ��壬��BDefine.h�е�������
   {1000     ,FTestProc   ,"Demo for SQC ҵ��������д����"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {���ܺ�   ,���̺���>    ,"��������"                                     ,"�����Ա����"       ,���ȼ�,false,0,0,0,0,0},
*/
// �����г����кϷ���ҵ������̺����б�

///////////////////////////////////////////////////////////////////////////////////
int F2401(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900077(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F260001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F260002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F260006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F270001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950996(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
///////////////////////////////////////////////////////////////////////////////////

// �������ݱ�Ϊ��ҵ����Ԫ�ܴ�������кϷ�ҵ������̼�����ز���
TBDefine g_XBDefines[]=
{
	INSERT_FUNCTION(2401 ,F2401, "xxx", "wyb", 1)
	INSERT_FUNCTION(900077 ,F900077, "xxx", "wj", 1)
	INSERT_FUNCTION(250001 ,F250001, "xxx", "wj", 1)
	INSERT_FUNCTION(250002 ,F250002, "xxx", "hlq", 1)
	INSERT_FUNCTION(250003 ,F250003, "xxx", "hlq", 1)
	INSERT_FUNCTION(250004 ,F250004, "xxx", "hlq", 1)
	INSERT_FUNCTION(250006 ,F250006, "xxx", "hlq", 1)
	INSERT_FUNCTION(260001 ,F260001, "xxx", "lx", 1)
	INSERT_FUNCTION(260002 ,F260002, "xxx", "lx", 1)
	INSERT_FUNCTION(260006 ,F260006, "xxx", "lx", 1)
	INSERT_FUNCTION(270001 ,F270001, "���п���", "wj", 1)
	INSERT_FUNCTION(950996 ,F950996, "xxx", "hlq", 1)
	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line��Don't remove this line
};
#endif
