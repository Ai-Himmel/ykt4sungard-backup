#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  ��ÿ��ҵ��������б�������������һ�У���ϸ�����ʾ�ĺ��壬��BDefine.h�е�������
   {1000     ,FTestProc   ,"Demo for SQC ҵ��������д����"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {���ܺ�   ,���̺���>    ,"��������"                                     ,"�����Ա����"       ,���ȼ�,false,0,0,0,0,0},
*/
// �����г����кϷ���ҵ������̺����б�

#define DEF_FUNC(x) int F##x(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
#define NEW_FUNC(x,m,a) {x,F##x,m,a,1,false,0,0,0,0,0}
///////////////////////////////////////////////////////////////////////////////////
DEF_FUNC(1001);
DEF_FUNC(1002);
DEF_FUNC(1003);
///////////////////////////////////////////////////////////////////////////////////

// �������ݱ�Ϊ��ҵ����Ԫ�ܴ�������кϷ�ҵ������̼�����ز���
TBDefine g_XBDefines[]=
{
    NEW_FUNC(1001,"�����ֵMAC�ӿ�","tc"),
    NEW_FUNC(1002,"��������TAC�ӿ�","tc"),
		NEW_FUNC(1003,"��������MAC�ӿ�2","tc"),
	{0,NULL,"END BPFunctions List","CYH Marked",0} // the last mark line��Don't remove this line
};
#endif

