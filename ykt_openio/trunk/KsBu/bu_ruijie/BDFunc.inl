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

// ���ܺź���ԭ������, ����BU�ص�
///////////////////////////////////////////////////////////////////////////////////
int F847360(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847361(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
///////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

// �������ݱ�Ϊ��ҵ����Ԫ�ܴ�������кϷ�ҵ������̼�����ز���
TBDefine g_XBDefines[]=
{
	INSERT_FUNCTION(847360 ,F847360, "����������ת�ʲ�ѯ", "lx", 1)
	INSERT_FUNCTION(847361 ,F847361, "����������ת��", "lx", 1)
	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line��Don't remove this line
};
#endif
