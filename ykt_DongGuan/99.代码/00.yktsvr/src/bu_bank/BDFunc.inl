#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  ��ÿ��ҵ��������б�������������һ�У���ϸ�����ʾ�ĺ��壬��BDefine.h�е�������
   {1000     ,FTestProc   ,"Demo for SQC ҵ��������д����"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {���ܺ�   ,���̺���>    ,"��������"                                     ,"�����Ա����"       ,���ȼ�,false,0,0,0,0,0},
*/
// �����г����кϷ���ҵ������̺����б�


#define DEF_FUNC(x) int F##x(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
#define NEW_FUNC(x,m,a) {x,F##x,m,a,1,false,0,0,0,0,0}
#define NEW_FUNC_NO(n,x,m,a) {n,F##x,m,a,1,false,0,0,0,0,0}

///////////////////////////////////////////////////////////////////////////////////
DEF_FUNC(5000);
DEF_FUNC(5001);
DEF_FUNC(5002);
DEF_FUNC(5003);
DEF_FUNC(5004);
DEF_FUNC(5005);
DEF_FUNC(5101);
DEF_FUNC(5102);
///////////////////////////////////////////////////////////////////////////////////

// �������ݱ�Ϊ��ҵ����Ԫ�ܴ�������кϷ�ҵ������̼�����ز���
TBDefine g_XBDefines[]=
{
    NEW_FUNC_NO(50000,5000,"Ȧ�����״̬��ѯ","tc"),
    NEW_FUNC_NO(50001,5001,"Ȧ��ǰ�û�ǩ��","tc"),
    NEW_FUNC_NO(50002,5002,"Ȧ���ʼ��","tc"),
    NEW_FUNC_NO(50003,5003,"Ȧ��ȷ��","tc"),
    NEW_FUNC_NO(50004,5004,"Ȧ������֤","tc"),
    NEW_FUNC_NO(50005,5005,"Ȧ�油д","tc"),
    NEW_FUNC_NO(50101,5101,"��ѯȦ����ϸ","tc"),
    NEW_FUNC_NO(50102,5102,"��ѯ������ϸ","tc"),
	{0,NULL,"END BPFunctions List","CYH Marked",0} // the last mark line��Don't remove this line
};
#endif

