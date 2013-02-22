/********************************************************************
	created:	2005/06/27
	created:	27:6:2005   19:25
	filename: 	D:\proj\ksbass\ksbu\bupub.cpp
	file path:	D:\proj\ksbass\ksbu
	file base:	bupub
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 �����г��˿��Թ�ҵ��ģ�飨C/C++�����ԣ����õ�������BCC����
   �Ŀ��ƺ�������SetCol��PutRow�Ⱥ�����
*********************************************************************/

#include "stdafx.h"
#include <stdio.h>
#include "cxpack.h"
#include "svrlink.h"
#include "logfile.h"
#include "bdefine.h"


CSvrLink g_SvrLink;  // ��ҵ��������ĵ�����
extern CLogFile *g_pLogFile;


/* ****** Updated by CHENYH at 2004-3-10 22:17:31 ****** 
// ������: SetCol
// ���  : ������ 2004-2-8 23:26:38
// ����  : ����CPACK����λͼ�����Ѿ���PutRow��������ݼ�¼�����ϴ����ݴ�����͸�ԭ�����
// ����  : int 0:�ɹ�����BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : void *handle �� ��ʱ�Ͷ�Ӧ�� TRUSERID *, �ڱ�ϵͳû�����壬��Ϊ���̵߳�Ե��
// ����  : ...  �� F_XXXXX ���������ֶ��б���END_FIELD��ʾ��������handle��ΪEND_FIELD�������λͼ��������λͼ
*/
int SetCol(TRUSERID *handle,...)
{
	va_list ap;
	int arg;
   ST_PACKHEAD head;
   memset(&head,0,sizeof(head));
	va_start(ap, handle);

/* ****** Updated by CHENYH at 2005-1-25 14:27:25 ****** 
	while ((arg = va_arg(ap, int)) != 0)
*/
   while ((arg=va_arg(ap,int))>=0)
//////////////////////////////////////////////////////////////////////////
	{
		SetParmBit( &head, arg);
	}
	va_end(ap);
   return(g_SvrLink.SetCol(handle,head.ParmBits));
}



/* ****** Updated by CHENYH at 2005-6-27 19:45:04 ****** 
��������Ϊ��PutRow�����Բ�����Ҫ�ˡ�
// ������: PutRowData
// ���  : ������ 2004-2-8 23:30:07
// ����  : �������CPACK����������һ��ST_PACK�����¼��ʵ�ʶ�֮ǰ��SetCol������ֶ���Ч��û�ж������Ч
// ����  : int 0:�ɹ�����BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : ST_PACK *pdata  �� ���ӵ�ST_PACK�������
int PutRowData(ST_PACK *pdata)
{
   return(g_SvrLink.PutRowData(pdata));
}
*******************************************************/

// ������: AnswerData
// ���  : ������ 2004-2-8 23:32:42
// ����  : ��ruserid�Ŀͻ��ˣ�������SetCol��PutRowData���õ�Ӧ�𷵻ص�����
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TRUSERID *ruserid  Ŀ��ͻ��˵ı�ʶ
// ����  : int retcode Ӧ�����ݵķ����� ��ӦST_CPACK��ͷ�е�RetCode
// ����  : char *szmsg ���ΪNULL�򡰡�����Ӧ�������У��Ͳ�����vsmess�ֶ�����
int AnswerData(TRUSERID *ruserid,int retcode,char *szmsg)
{
   return(g_SvrLink.AnswerData(ruserid,retcode,szmsg,0));
}


// ������: AnswerDataPart
// ���  : ������ 2004-2-12 12:12:09
// ����  : ��AnswerData���ƣ���������֪ͨ�ͻ��ˣ����и�������ݷ���
//         �����ڽ��д��������ݷ��أ�������������ͬ����Ϊ�˲��ÿͻ��˳�ʱ��ȴ�
//         �ȷ��Ͳ������ݡ�
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TRUSERID *ruserid
// ����  : int retcode
// ����  : char *szmsg
int AnswerDataPart(TRUSERID *ruserid,int retcode,char *szmsg)
{
   return(g_SvrLink.AnswerData(ruserid,retcode,szmsg,1));
}

// ������: AnswerDataEx
// ���  : ������ 2004-2-8 23:37:00
// ����  : ��ruserid�Ŀͻ��ˣ�����apack��pArrays���Ӧ�𷵻ص�����
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TRUSERID *ruserid  Ŀ��ͻ��˵ı�ʶ
// ����  : ST_CPACK *apack  Ӧ������ͷ���ױ���
// ����  : ST_PACK *pArrays �������ݱ��壬��apack->head.RetCount<=1ʱ����Ч ������дΪNULL
// ����  : int retcode Ӧ�����ݵķ����� ��ӦST_CPACK��ͷ�е�RetCode
// ����  : char *szmsg ���ΪNULL�򡰡�����Ӧ�������У��Ͳ�����vsmess�ֶ�����
int AnswerDataEx(TRUSERID *ruserid,ST_CPACK *apack,ST_PACK *pArrays,int retcode,char *szmsg)
{
   return(g_SvrLink.AnswerDataEx(ruserid,apack,pArrays,retcode,szmsg));
}

// ������: PushData
// ���  : ������ 2004-2-8 23:43:01
// ����  : ��һ����Ϊ����ʽע���Ŀ��㣬��������
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int sourceno  ��������ʹ�õ�ͨѶƽ̨�ı�ţ��μ�TRUSERID::SourceNo
// ����  : int destno    �������ݵ�Ŀ��ͨѶƽ̨���
// ����  : int funcno    Ŀ��������ͨѶƽ̨��ע���ͨѶ���ܺ�
// ����  : int batchno   ��Ը�Ŀ���Ự���κ�
// ����  : ST_CPACK *ppack  ���͵����ݰ���ppack->head.RetCount<=1�����������ݲ��ܳ���1�������¼
// ����  : char pushmode  ����ģʽ�������������PM_xxx
// ����  : int acktime   ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч 
int PushData(int sourceno,int destno,int funcno,int batchno,ST_CPACK *ppack,char pushmode,int acktime)
{
   return(g_SvrLink.PushData(sourceno,destno,funcno,batchno,ppack,pushmode,acktime));
}



// ������: ExtCall
// ���  : ������ 2004-3-6 17:47:14
// ����  : ������һ������㷢������Ҫ��Է�����Ӧ�𷵻أ������ܳ������ڲ�ͬϵͳ֮��ĶԽӣ���Ҫ��������Χϵͳ����
// ����  : int >=0:�ɹ������ص�ΪӦ�����ݰ����¼����<0:����-2:�ȴ�����Ӧ��ʱ��-1:����ͨѶ����
// ����  : int sourceno  ʹ�õ�ͨѶƽ̨�ı�ţ��μ�TRUSERID::SourceNo
// ����  : int destno    Ŀ��ͨѶƽ̨���
// ����  : int funcno    Ŀ��������ͨѶƽ̨��ע���ͨѶ���ܺ�
// ����  : int batchno   ��Ŀ���Ự���κ� (���ȷ����Ը�Ŀ��㣬����������������ģʽ�������ֱ����дΪ0)
// ����  : int acktime   ���������Чʱ�䣬�����
// ����  : ST_CPACK *rpack  ���������
// ����  : ST_CPACK *apack  Ŀ���Ӧ������ݷ���
// ����  : ST_PACK *pArrays Ӧ�����ݺ���������
int ExtCall(int sourceno,int destno,int funcno,int batchno,int acktime,ST_CPACK *rpack,ST_CPACK *apack,ST_PACK *pArrays)
{
   return(g_SvrLink.ExtCall(sourceno,destno,funcno,batchno,acktime,rpack,apack,pArrays));
}



// ������: ExtCallNext
// ���  : ������ 2004-3-8 17:31:47
// ����  : �ڵ���ExtCall֮�󣬷��ֶԷ��������ݻ�û��ȡ���������ñ����ܻ�ȡ��������
// ����  : int >=0:�ɹ������ص�ΪӦ�����ݰ����¼����<0:����-2:�ȴ�����Ӧ��ʱ��-1:����ͨѶ����-3:�Ѿ�ȡ���˺�������
// ����  : int acktime
// ����  : ST_CPACK *apack
// ����  : ST_PACK *pArrays
int ExtCallNext(int acktime,ST_CPACK *apack,ST_PACK *pArrays)
{
   return(g_SvrLink.ExtCallNext(acktime,apack,pArrays));
}


// ������: PushDataEx
// ���  : ������ 2004-2-9 0:10:53
// ����  : ��pushdests�������Ϊ����ʽע��Ŀ�����������
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TPUSHDEST *pushdests �����Ŀ����б�
// ����  : int pdcount  Ŀ���ĸ���
// ����  : ST_CPACK *ppack ���͵Ĳ�����һ����¼�����ݰ�
// ����  : char pushmode ����ģʽ�������������PM_xxx
// ����  : int acktime  ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч 
int PushDataEx(TPUSHDEST *pushdests,int pdcount,ST_CPACK *ppack,char pushmode,int acktime)
{
   return(g_SvrLink.PushDataEx(pushdests,pdcount,ppack,pushmode,acktime));
}



// ������: PutRow
// ���  : ������ 2004-2-20 10:03:04
// ����  : һ�������PutRowData �� AnswerData, ���ǲ������Ϸ��� ��Ϊ������а汾���ݣ�
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TRUSERID *handle
// ����  : ST_PACK *pdata
// ����  : int *pRetCode
// ����  : char *rtnMsg
int PutRow(TRUSERID *handle,ST_PACK *pdata,int *pRetCode,char *rtnMsg)
{
   return(g_SvrLink.PutRow(handle,pdata,*pRetCode,rtnMsg));
}


// �ļ�����ʹ�øù���, add by ���� 2007-1-14
int PutRowData(ST_PACK *pdata)
{
   return(g_SvrLink.PutRowData(pdata));
}


// ������: CT_ERR_DEAL
// ���  : ������ 2004-2-22 16:39:51
// ����  : ���ԭ��׼����Ӧ����Ϣ������������ʱ�����ļ��м�¼��������Ϣ��Ϊ���뼯�н��׼��ݣ�
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : char *msg
// ����  : int retcode
int CT_ERR_DEAL(char *msg,int retcode)
{
   return(g_SvrLink.Err_Deal(msg,retcode));
}


// ������: Error_Deal
// ���  : ������ 2004-2-22 16:43:34
// ����  : ���ԭ��׼����Ӧ����Ϣ������������ʱ�����ļ��м�¼��������Ϣ ������ϵͳʹ�ñ��������ԭ����ERR_DEAL
//         �ϲ���ԭ����Ҫ��sprintf����omsg
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int retcode
// ����  : char *omsg  OUT
// ����  : char *pFormat IN
// ����  : ... IN
int Error_Deal(int retcode,char *omsg,char *pFormat,...)
{
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(CT_ERR_DEAL(omsg,retcode));
}


// ������: SQLDebugLog
// ���  : ������ 2004-3-4 17:45:16
// ����  : ר��Ϊ��SQCʹ�ã���C��ʹ�õģ���¼��Ϣ��LOG��־��
// ����  : void 
// ����  : int errorcode
// ����  : char *pFormat
// ����  : ...
void SQLDebugLog(int errorcode,char *pFormat,...)
{
   char omsg[8192];
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   g_pLogFile->WriteLogEx(errorcode,"%s",omsg);   
}

void TextLogOut(int errorcode, char *textlog)
{
   g_pLogFile->WriteLogEx(errorcode,"%s",textlog);
}


// ������: CheckProcCancel
// ���  : ������ 2004-3-10 15:44:20
// ����  : ����Ƿ񱾴�������ǰ̨�Ƿ�Ҫ��ֹͣ��ע�⣺�������Ҫ����������Ƿ��и�ֹͣ������ᵼ�µ�1���룬��ʹ�ô���Ч�ʽ���
// ����  : int 1:��ʾǰ̨��Ҫ��ֹͣ�����0:û��
int CheckProcCancel()
{
   if (g_SvrLink.CheckProcCancel())
      return(1);
   else 
      return(0);
}

// ������: SetAnswerMode
// ���  : ������ 2004-3-10 18:48:18
// ����  : ����Ӧ��ģʽ����AM_xxxx�Ķ���
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : char iAnswerMode ��AM_xxxx�Ķ���
int SetAnswerMode(char iAnswerMode)
{
   return(g_SvrLink.SetAnswerMode(iAnswerMode));
}


// ������: BCCMsgLogOut
// ���  : ������ 2004-3-10 19:31:25
// ����  : ��BCC���������BU���ı���־��Ϣ
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int logid ������־��ID��
// ����  : char *pFormat ���ı���־�ĸ�ʽ����
// ����  : ... ����pFormat������������
int BCCMsgLogOut(int logid,char *pFormat,...)
{
   char omsg[1024];
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(g_SvrLink.BCCLogOut(LT_MSG,logid,strlen(omsg),omsg));
}


// ������: ResetNormalCPack
// ���  : ������ 2004-3-11 20:30:59
// ����  : ���ݱ�ҵ�������������һ��CPACK��ͷ��λͼ�����ݶ��������
// ����  : void 
// ����  : ST_CPACK *pack
void ResetNormalCPack(ST_CPACK *pack,unsigned char nextflag,int recCount)
{
   g_SvrLink.ResetNormalCPack(pack,nextflag,recCount);
}


// ������: SetMaxRow
// ���  : ������ 2004-3-22 11:41:26
// ����  : ���ñ��ι��ܴ���ʱ��ÿ��Ӧ������ص�����¼����ֻ�Ա��ι��ܴ�����Ч
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int maxrows
int SetMaxRow(int maxrows)
{
   return(g_SvrLink.SetMaxRow(maxrows));
}


// ������: SetBUError
// ���  : ������ 2004-3-22 11:42:37
// ����  : ���ñ�BU������Ϣ�������ṩ��ǰ�˳���
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int errcode
// ����  : char *pFormat
// ����  : ...
int SetBUError(int errcode,char *pFormat,...)
{
   char omsg[1024];
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(g_SvrLink.SetBUError(errcode,omsg));   
}


// ������: SetAnswerTimeout
// ���  : ������ 2004-3-22 12:49:02
// ����  : �趨��ҵ��ÿ��Ӧ����ĳ�ʱʱ�䣬�Ժ���ƣ���������������ʱ������Ĵ���
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : unsigned int atimeout  ָ���ĳ�ʱʱ�䣨�Ժ���ƣ�
int SetAnswerTimeout(unsigned int atimeout)
{
   return(g_SvrLink.SetAnswerTimeout(atimeout));
}




// ������: ResetAnswerData
// ���  : ������ 2004-3-24 22:16:17
// ����  : ��������Ѿ��ύ��Ӧ�����ݣ�����������ִ��һ������������Ϊ����������Retry
// ����  : int 
int ResetAnswerData()
{
   return(g_SvrLink.ResetAnswerData());
}


