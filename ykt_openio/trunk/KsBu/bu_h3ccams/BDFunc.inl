#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  ��ÿ��ҵ��������б�������������һ�У���ϸ�����ʾ�ĺ��壬��BDefine.h�е�������
   {1000     ,FTestProc   ,"Demo for SQC ҵ��������д����"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {���ܺ�   ,���̺���>    ,"��������"                                     ,"�����Ա����"       ,���ȼ�,false,0,0,0,0,0},
*/
// �����г����кϷ���ҵ������̺����б�
//#ifdef __cplusplus
//extern "C" {
//#endif

// ���ܺź���ԭ������, ����BU�ص�
///////////////////////////////////////////////////////////////////////////////////
int F3001(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F3002(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);

///////////////////////////////////////////////////////////////////////////////////

//#ifdef __cplusplus
//}
//#endif

// �������ݱ�Ϊ��ҵ����Ԫ�ܴ�������кϷ�ҵ������̼�����ز���
TBDefine g_XBDefines[]=
{
	INSERT_FUNCTION(3001 ,F3001, "����ת���ʻ���ѯ�Ϸ���", "hlq", 1)
	INSERT_FUNCTION(3002 ,F3002, "���ѳ�ֵ", "hlq", 1)
	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line��Don't remove this line
};
#endif
