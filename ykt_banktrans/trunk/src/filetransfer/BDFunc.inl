#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  ��ÿ��ҵ��������б�������������һ�У���ϸ�����ʾ�ĺ��壬��BDefine.h�е�������
   {1000     ,FTestProc   ,"Demo for SQC ҵ��������д����"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {���ܺ�   ,���̺���>    ,"��������"                                     ,"�����Ա����"       ,���ȼ�,false,0,0,0,0,0},
*/
// �����г����кϷ���ҵ������̺����б�

///////////////////////////////////////////////////////////////////////////////////
/*

*/

/* �Ž���̨���ܺŶ��� */
/**************************************************************************/


// ͨ��ǰ�û�����

//int FGetFile(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int FPutFile(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

///////////////////////////////////////////////////////////////////////////////////

// �������ݱ�Ϊ��ҵ����Ԫ�ܴ�������кϷ�ҵ������̼�����ز���
TBDefine g_XBDefines[]=
{
	/*
	INSERT_FUNCTION(1010,FTestIReply,"����ٵĴ������ڲ����ٶ�","CYH Demo",1)
	INSERT_FUNCTION(1011,FTestBCCShm,"���ڲ���BCCSHM�ٶ�","CYH Demo",1)
	INSERT_FUNCTION(1012,FTestBUShm,"���ڲ���BUSHM�ٶ�","CYH Demo",1)
	INSERT_FUNCTION(1013,FBCCShmMultiRows,"���ڲ���BCCSHM�Ķ�����ؼ��乤��","CYH Demo",1)
	INSERT_FUNCTION(1014,FBCCShmGetRecord,"��ȡBCCSHM�����ڴ��е�����","CYH Demo",1)
	INSERT_FUNCTION(1015,FBCCShmSetRecord,"��ȡ�����ڴ��е����ݷ��ظ��ͻ��ˣ���������е�ֵ���õ������ڴ���","CYH Demo",1)
	INSERT_FUNCTION(1016,FTestBCCIntCall,"�ù��ܺ�1013����BCC��IntCall/IntCallNext��RACall/RACallNext�Ĺ���","CYH Demo",1)
	INSERT_FUNCTION(1017,FTestBCCIntTransfer,"�ù��ܺ�1013����BCC��IntTransfer��RATransfer�Ĺ���","CYH Demo",1)
	INSERT_FUNCTION(1018,FTestBCCExtCall,"��1013���ܲ����������ExtCall/ExtCallNext","CYH Demo",1)
	INSERT_FUNCTION(1019,FTestBCCExtTransfer,"��1013���ܲ����ⲿת������ExtTransfer","CYH Demo",1)
	INSERT_FUNCTION(1020,FTestPushData,"��1010�������������͹���PushData","CYH Demo",2)
	INSERT_FUNCTION(1021,FTestBURunTime,"����BCC�ж�BU���е�MAXRUNTIME�Ƿ���˵��������","CYH Demo",3)
	INSERT_FUNCTION(1025,FGetBaseOperTimes,"���1013���ڲ�ͬƽ̨�¸��������ĺ�ʱ��ʱʱ��","CYH TEST",3)
	INSERT_FUNCTION(1030,FPTestExtCall,"��1010����ExtCall���ٶ�","CYH Demo",1)
	INSERT_FUNCTION(1031,FPTestIntCall,"��1010����IntCall/RACall���ٶ�","CYH Demo",1)
	INSERT_FUNCTION(1032,FPTestExtTransfer,"��1010����ExtTransfer���ٶ�","CYH Demo",1)
	INSERT_FUNCTION(1033,FPTestIntTransfer,"��1010����IntTransfer/RATransfer���ٶ�","CYH Demo",1)
	INSERT_FUNCTION(9990,FGetFile,"��BU�������ļ�","CYH Demo",3)
  */
	
	

	INSERT_FUNCTION(2000,FPutFile,"�´��ļ�","wenjian",1)
	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line��Don't remove this line
};
#endif
