/********************************************************************
	created:	2006/07/12
	created:	12:7:2006   10:59
	filename: 	D:\proj\ksbass\bcclink\bccsvr\bccsvr.h
	file path:	D:\proj\ksbass\bcclink\bccsvr
	file base:	bccsvr
	file ext:	h
	author:		CHENYH
	
	purpose: Ϊ�˸�C/C++�ṩ��JAVA���ƵĽӿ�	

   2009-5-12 14:55:46 ����BSGetPCharFieldByName��������BSGetStringFieldByName��unsigned char�ֶ�������ͬ
*********************************************************************/
#ifndef NBCCSVR_H
#define NBCCSVR_H


#ifdef BCCSVR_EXPORTS
#include "XPData.h"
#ifdef _WINDOWS
#define BCCSVR_API __declspec(dllexport)
#else
#define BCCSVR_API 
#endif
#else
typedef void * BSHANDLE;
#ifdef _WINDOWS
#define BCCSVR_API __declspec(dllimport)
#else
#define BCCSVR_API 
#endif
#endif

#ifdef __cplusplus
extern "C" {
#else
   typedef unsigned char bool;
/* ****** Updated by CHENYH at 2006-7-12 11:04:58 ****** 
   #define true 1
   #define false 0
*******************************************************/
#endif

//////////////////////////////////////////////////////////////////////////
// ��ģ���ʼ�����֣�
   
   // ������: BCCSvrInit
   // ���  : ������ 2006-8-24 18:22:23
   // ����  : ���Ի�BCCSvrģ�飬ָ��Forward�ļ����Ŀ¼�ͺ������ݹ���ʱ�䣨�룩
   // ����  : bool 
   // ����  : char *fwdpath [IN/OUT]: �����ļ����Ŀ¼
   // ����  : int clearseconds [IN]: �������ݹ���ʱ�䣨�룩
   BCCSVR_API bool BCCSvrInit(char *fwdpath, int clearseconds);
   

   BCCSVR_API void BCCSvrExit();

   ///////////////////////////////////////////////////////////////////////////////////////
   // ��ҵ��ͨѶƽ̨��صĺ�����
   
   // ����  : ����һ��ͨѶ���񣬰������ӵ�ҵ��ͨѶƽ̨�ڵ��������Ϊ�˽�����Ϣ��������Ҫ��ͨѶ���ܺţ�
   //          ע�⣺basefno��privfno�����������ٱ���һ������Ч�ġ�
   // ����  : int ����ҵ��ͨѶƽ̨����ID�ţ�<0: ʧ��
   // ����  : const char *ip [IN]: ��ҵ��ͨѶƽ̨��IP��ַ
   // ����  : int port [IN]: ��ҵ��ͨѶƽ̨�ṩ�Ķ˿ں�port
   // ����  : int *funlist [IN]: ��ҵ��ͨѶƽ̨��ע��Ĺ��ܺ��б��������е�һ������Ϊ˽�й��ܺ�
   // ����  : int funcount [IN]: ��ҵ��ͨѶƽ̨��ע��Ĺ��ܺŸ�����������>0
   // ����  : bool bretry [IN]: �Ƿ񵱶Ͽ����Ӻ󣬼���retry���ӡ�
   //                           true, �򵱽��մ������ӶϿ���ʱ�򣬻����²�ͣ���ӣ��ָ����գ���BSReceiveMsg������-2��Ϣ
   //                           false�������ӶϿ�ʱ����ص�BSReceiveMsg�����л���յ�-2����Ϣ���˳�����
   BCCSVR_API int BSAddService(int branchno,const char *ip,int port,int *funlist, int funcount, bool bretry);
   
   // ������: BSRemoveService
   // ���  : ������ 2006-8-25 16:38:58
   // ����  : �жϷ�������
   // ����  : bool : ��svrID<0 �� svrID>=10 ����Ϊfalse
   // ����  : int svrID [IN]: ��AddService�������ص�ͨѶƽ̨�������ӱ��
   BCCSVR_API bool BSRemoveService(int svrID);
   

   // ������: BSStopService
   // ���  : ������ 2008-11-18 15:16:55
   // ����  : ֹͣ���񣬼���ͨ��ƽ̨��ע�������ܺ�
   // ����  : BCCSVR_API bool 
   // ����  : int svrID
   BCCSVR_API bool BSStopService(int svrID);

   // ������: BSIsServiceOK
   // ���  : ������ 2007-12-24 17:21:06
   // ����  : �Ƿ�÷��������Ƿ����������ڽ�������
   // ����  : bool : ��svrID<0 �� svrID>=10 ������Ӳ�����(�Ͽ�״̬),����Ϊfalse
   // ����  : int svrID [IN]: ��AddService�������ص�ͨѶƽ̨�������ӱ��
   BCCSVR_API bool BSIsServiceOK(int svrID);
   
   //////////////////////////////////////////////////////////////////////////
   // ����  : ����һ������XPack���ݽ�����������
   // ����  : BSHANDLE : ���ظ�XPack�������ľ����==NULL: ʧ��
   // ����  : const char *XpackDescribleFile [IN]: XPack�ṹ�����ļ��������ܳ���1024�ֽڳ�����: "/xpacks/cpack.dat"
   BCCSVR_API BSHANDLE BSNewHandle(const char * XpackDescribleFile);

   // ����  : ���Ѿ���BSNewHandle�õ����������ͷ�(ж��)
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API bool BSDeleteHandle(BSHANDLE Handle);


   //////////////////////////////////////////////////////////////////////////
   // ����  : ��XPack���ݴ�������ͨѶ����ID
   // ����  : int ����ҵ��ͨѶƽ̨����ID�ţ�<0: ʧ��
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int svrID [IN]: ͨѶ����ID����AddService(...)���ص�ID
   BCCSVR_API int BSBindService(BSHANDLE Handle,int svrID);
   
   // ����  : ��Ϊ�����Ա����õ�ͨѶ���ܺţ�ɨ�������Ϣ����������
   // ����  : int    1��0��֪ͨ��Ϣ��2��1��֪ͨ��Ϣ��3�������ͻ����������ݣ���Ҫ��BSPutRow/BSDataDone����Ӧ��
   //                0: һ���������ݷ��ش�����ɣ�ͬ-1һ����������
   //                -1: ��ʾ����ɨ�����Bind��Service��û���յ��µ���Ϣ������ע����������²�Ҫ��ɨ�裬���߳��м�������ȴ���
   //                -2: ��ʾ�󶨵�svrID���ӳ��������ˣ�errormessage�н������������Ϣ 
   //                <-2: ���ڴ��󣬲ο�errormessage��Ϣ -3: �������
   // ����  : BSHANDLE Handle [IN] : �ȴ����յ�XPACK���ݻ�����
   // ����  : char *errormessage [OUT] : ��������Ϊ<0��ʱ��Ĵ�����Ϣ
   // ����  : int emlen[IN] : errormessage�Ļ��泤��
   BCCSVR_API int BSReceiveMsg(BSHANDLE Handle,char *errormessage, int emlen);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���нӿ������ָ����������������ݣ�������������
/////////////////////////////////////////////////////////////////////////////
// ȡ���յ����������Ϣ�������ݣ�

   // ����  : ���Ӧ�������У��Ƿ���ָ���ֶε�ֵ
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : char *FieldName [IN]: �ֶ����� ��"vsmess"
   BCCSVR_API  bool BSIsValidField(BSHANDLE Handle, char *FieldName);


   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (int)
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
   // ����  : long *value [OUT]: ���صõ���ֵ
   BCCSVR_API bool BSGetIntFieldByName(BSHANDLE Handle,int Row,const char *fieldname,long *value);

   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
   // ����  : double *value [OUT]: ���صõ���ֵ
   BCCSVR_API bool BSGetDoubleFieldByName(BSHANDLE Handle,int Row,const char *fieldname,double *value);

   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (�ɴ�ӡ���ַ���) ��unsigned char �ֶΣ�����0x��ʼ����ת��Ϊ�ɴ�ӡ�ַ���ʽ��ȡ
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
   // ����  : char *value [OUT]: ���صõ���ֵ
   // ����  : int ValueBufferSize [IN]: value�������ĳ��ȣ������Դ�ŵ���󳤶ȣ� һ�����Ϊ <=256
   BCCSVR_API bool BSGetStringFieldByName(BSHANDLE Handle,int Row,const char *fieldname,char *value,int ValueBufferSize);


   // ������: BSGetPCharFieldByName
   // ���  : ������ 2009-5-12 14:47:40
   // ����  : ��BSGetStringFieldByName�ڶ��ֶ�unsigned char����������ͬ���ڣ������Value����ԭʼ���ֶ��е�ֵ
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : const char *FieldName
   // ����  : char *Value [IN]: �ֶ����� ��"vsmess"
   // ����  : int ValueBufferSize [IN]: value�������ĳ��ȣ������Դ�ŵ���󳤶ȣ� һ�����Ϊ <=256
   BCCSVR_API bool BSGetPCharFieldByName(BSHANDLE Handle,int Row,const char *FieldName,char *Value,int ValueBufferSize);

   //-------------------------------------------------------------------------------------------------------

   // ���  : ������ 2005-11-14 18:10:22
   // ����  : ��ȡ��������еļ�¼��RecordCount
   // ����  : int ���ؽ������ݵļ�¼��
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API int BSGetRecordCount(BSHANDLE Handle);

   // ���  : ������ 2005-11-14 21:11:05
   // ����  : ��ѯ��ǰ���ݿ������ݼ�¼����
   // ����  : int �������ݼ�¼���� 0-��׼ST_PACK��¼��1-ST_SDPACK��RawData��¼
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API int BSGetXPackType(BSHANDLE Handle); 

   // ����  : ����BSGetXPackType����Ϊ1��ST_SDPACK��ļ�¼��������ñ�������ȡ������Ч��¼�е�RawData��¼
   // ����  : int : >=0 - �ɹ�����RawData�����ݳ���(�ֽ���)
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : char *RawData [OUT]: ��Ŷ�ȡ��RawData���ݿ飬�ڲ���������������8K�ֽڵĻ���
   // ����  : int RawDataSize [IN]: RawData���ݿ�Ŀɴ�ŵ������
   BCCSVR_API int BSGetRawRecord(BSHANDLE Handle, int Row, char *RawData, int RawDataSize);

   // ����  : ȡBSReceiveMsg��õ����ݵ������ܺ�
   // ����  : int �����ܺ�
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API int BSGetRequestType(BSHANDLE Handle);

   // ����  : ȡBSReceiveMsg��õ����ݵ�RetCodeֵ
   // ����  : int ��Ϣ�����������е�RetCodeֵ
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API int BSGetRetCode(BSHANDLE Handle);

   // ����  : ȡBSReceiveMsg��>0�ĵõ������Ǵ��ĸ�SvrID��ȡ�õ�
   // ����  : int ��Ϣ�����������Ǵ��ĸ�SvrID��ȡ�õ�
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API int BSGetSvrID(BSHANDLE Handle);

   // ����  : ����0��1����Ϣ��ȡ��Ϣ��ţ���Ϣ�����XPACKЭ���У�����Number*100+Day(��λ����)��ɵ�
   // ����  : int ������Ϣ��ż�XPACKͷ�е�hook.UserID
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API int BSGetMsgID(BSHANDLE Handle);


   // ����  : ����0��1����Ϣ��ȡ��Ϣ����ԴID
   // ����  : int ������Ϣ��ԴID��XPACKͷ�е�hook.queuetype
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API int BSGetMsgSource(BSHANDLE Handle);


   // ����  : ����0��1����Ϣ��ȡ��Ϣ�����κ�
   // ����  : int ������Ϣ���κż�XPACKͷ�е�userdata
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API int BSGetMsgBatchNo(BSHANDLE Handle);

//////////////////////////////////////////////////////////////////////////
// ����Ӧ���¼�����ݣ�

   // ���  : ������ 2005-11-14 21:11:00
   // ����  : ����Ӧ���ÿ�η��ص�����¼��
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int MaxRetCount [IN]: ָ��������¼����0�����Զ����� [0..100]; 
   BCCSVR_API bool BSSetAPackMaxRows(BSHANDLE Handle,int MaxRows);

   /// ��XPACK��RawData�Ķ�д������
   // ����  : ����ָ����¼Ϊָ����RawData��¼
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : const char *RawData [IN]: Ҫ�������ݿ�
   // ����  : int RawDataLength [IN]: Ҫ�������ݿ鳤��
   BCCSVR_API bool BSSetRawRecord(BSHANDLE Handle, const char *RawData, int RawDataLength);
	
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
   // ����  : long value [IN]: ����ֵ
   BCCSVR_API bool BSSetIntFieldByName(BSHANDLE Handle,const char *fieldname,long value);

   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
   // ����  : double value [IN]: ����ֵ
   BCCSVR_API bool BSSetDoubleFieldByName(BSHANDLE Handle,const char *fieldname,double value);

   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : bool 
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
   // ����  : const char *value [IN]: ����ֵ��һ�㲻���Գ���255���ȣ����Ǹ��ֶ�Ϊbinary���ͣ���0xXXXXXX...��ʾ������ֵ
   BCCSVR_API bool BSSetStringFieldByName(BSHANDLE Handle,const char *fieldname,const char *value);


//////////////////////////////////////////////////////////////////////////
// ��BSSetXXXXӦ�����Ĳ�����
   // ����  : ����ǰ�����е��Ѿ����õ�����(Row=0��)��Ϊһ����¼��׼����ϣ������ύ���Է�
   //          ע�⣺��XPACK��CPACKЭ���У��ü�¼���ἴʱ���͸��Է������ǳ�Ϊһ�������İ�
   //             �����ڼ�ѹ��ȥ��ģʽ����ÿ�ζ�Ҫ��BSPutRow��ʾһ����¼׼����ϣ����
   //             ͨ������BSDataDone����ʾ���������������û�и��������Ҫ�����󷽡�
   // ����  : int : ���سɹ�>=0 ��ʧ��<0
   // ����  : BSHANDLE Handle [IN] : ��������XPACK���ݻ�����
   // ����  : int retCode [IN] : ��ǰ�ķ����룬һ����XPACKЭ����0��ʾ�ɹ�
   BCCSVR_API int BSPutRow(BSHANDLE Handle, int retCode);


   // ����  : �����ǰͨ��SetXXXXFieldByName��SetRawData�����ݣ�����ķ��ؼ�¼�����ݵ��ֶ���
   //          ���ʱ��ͻὫǰ��Ľ���ύ�����󷽵ġ�
   // ����  : int >=0: �ɹ���<0: ʧ�� 
   // ����  : BSHANDLE Handle [IN] : ��������XPACK���ݻ�����
   BCCSVR_API int BSClearRow(BSHANDLE Handle);


   // ����  : ���ζ��������ݴ����������������Ϣ���ظ�����
   // ����  : int : ���سɹ�>=0 ��ʧ��<0
   // ����  : BSHANDLE Handle [IN] : ��������XPACK���ݻ�����
   // ����  : int retCode [IN] : ��ǰ�ķ����룬һ����XPACKЭ����0��ʾ�ɹ�
   BCCSVR_API int BSDataDone(BSHANDLE Handle, int retCode);

   
   ///////////////////////////////////////////////////////////////////////////////////////////////////
   /// ���к��������������޹أ�ֻ�����ڳ��Ի�XPACK�����XPACK�ṹ��Ϣ��ȡ
   //////////////////////////////////////////////////////////////////////////
   // ����  : ��ȡ����ʽ��XPack��������Ч�ֶ�����ֵ���뵱ʱ���ݿ鲻ͬ
   // ����  : int ����ST_PACK�е������Ч�ֶ�����ֵ
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   BCCSVR_API int BSGetMaxColumn(BSHANDLE Handle);
   
   // ���  : ������ 2005-11-14 21:11:29
   // ����  : �����ֶ����ƣ�����ֶ�������
   // ����  : int >=0 Ϊ��XPACK����Ч�ֶΣ����ص�ֵ��Ϊ�����ţ�<0Ϊ��XPACK��û������ֶ�
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
   BCCSVR_API int BSGetFieldColumn(BSHANDLE Handle, const char *fieldname);
   
   // ����  : ��ȡָ���ֶε���Ϣ
   // ����  : bool : true-Ϊ��Ч�ֶ�
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Col [IN]: ָ�����ֶ�������
   // ����  : char *fieldname [OUT]: ����ָ�����ֶ�����
   // ����  : int *fieldtype [OUT]: ָ�����ֶ�����
   // ����  : int *fieldlength [OUT]: ָ�����ֶγ���
   BCCSVR_API bool BSGetFieldInfo(BSHANDLE Handle,int Col, char *fieldname, int *fieldtype, int *fieldlength);
   
   // ����  : ȡ�ö�Ӧ�ֶε�����(��BSNewHandle������Ľṹ�����ļ����)
   // ����  : int  : 0 - ���ֶ�; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
   //                -1 �ֶ����������ڻ�Handle����
   // ����  : BSHANDLE Handle [IN]: ָ����XPack���������
   // ����  : const char *fieldname [IN]: ָ�����ֶ�����,��"vsmess"
   BCCSVR_API int BSGetFieldTypeByName(BSHANDLE Handle,const char *fieldname);
   
   
////////////////////////////////////////////////////////////////////////////////
// ��������

// ����  : ����Ϣ��¼��KLG�ļ��У�ֻ����BSKLGOpen�ɹ�����Ч��
// ����  : void 
// ����  : char *fmt ����Ϣ�ĸ�ʽ����
// ����  : ... ����Ϣ����������������sprintf�еĲ������뷽ʽ
BCCSVR_API void BSKLGMsg(char *fmt,...);

// ����  : ��KLG�ļ���¼ģʽ��ע��ֻ���Ե���һ�Σ����������ڳ��Ի���ʱ��
// ����  : bool �������Ƿ�ɹ���
// ����  : char *path ��KLG��ŵ�·��
BCCSVR_API bool BSKLGOpen(char *path);

// ����  : ɾ�������ļ�
// ����  : int ���ر�ɾ���ļ��ĸ���
// ����  : char *path_mark ��ɾ�����ļ�·�����������ļ�����
// ����  : char *ext ��ɾ�����ļ���չ��������.xxx
// ����  : int overdue : ���ڵ���Ȼ����
BCCSVR_API int BSRemoveOverdueFile(const char *path_mark,char *ext,int overdue);

BCCSVR_API void BSOutErrorFile(char *efilename,char *msg,char *sourcefile,int lineno);


#ifdef __cplusplus
}
#endif

#undef BCCSVR_API

#endif
