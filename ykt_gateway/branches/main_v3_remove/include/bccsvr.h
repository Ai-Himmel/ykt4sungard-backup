/********************************************************************
	created:	2006/07/12
	created:	12:7:2006   10:59
	filename: 	D:\proj\ksbass\bcclink\bccsvr\bccsvr.h
	file path:	D:\proj\ksbass\bcclink\bccsvr
	file base:	bccsvr
	file ext:	h
	author:		CHENYH
	
	purpose: Ϊ�˸�C/C++�ṩ��JAVA���ƵĽӿ�	
*********************************************************************/
#ifndef BCCSVR_H
#define BCCSVR_H


#ifdef BCCSVR_EXPORTS
#include "XPData.h"
#define BCCSVR_API __declspec(dllexport)
#else
typedef void * XDHANDLE;
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

///////////////////////////////////////////////////////////////////////////////////////////////////
/// ���к��������������޹أ�ֻ�����ڳ��Ի�XPACK�����XPACK�ṹ��Ϣ��ȡ

// ����  : ����һ������XPack���ݽ�����������
// ����  : XDHANDLE : ���ظ�XPack�������ľ����==NULL: ʧ��
// ����  : const char *XpackDescribleFile [IN]: XPack�ṹ�����ļ��������ܳ���1024�ֽڳ�����: "/xpacks/cpack.dat"
BCCSVR_API XDHANDLE NewXpackHandle(const char * XpackDescribleFile);

// ����  : ���Ѿ���NewXpackHandle�õ����������ͷ�(ж��)
// ����  : bool 
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API bool DeleteXpackHandle(XDHANDLE Handle);

// ����  : ��ȡ����ʽ��XPack��������Ч�ֶ�����ֵ���뵱ʱ���ݿ鲻ͬ
// ����  : int ����ST_PACK�е������Ч�ֶ�����ֵ
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API int GetMaxColumn(XDHANDLE Handle);

// ������: GetFieldColumn
// ���  : ������ 2005-11-14 21:11:29
// ����  : �����ֶ����ƣ�����ֶ�������
// ����  : int >=0 Ϊ��XPACK����Ч�ֶΣ����ص�ֵ��Ϊ�����ţ�<0Ϊ��XPACK��û������ֶ�
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
BCCSVR_API int GetFieldColumn(XDHANDLE Handle, const char *fieldname);

// ����  : ��ȡָ���ֶε���Ϣ
// ����  : bool : true-Ϊ��Ч�ֶ�
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : int Col [IN]: ָ�����ֶ�������
// ����  : char *fieldname [OUT]: ����ָ�����ֶ�����
// ����  : int *fieldtype [OUT]: ָ�����ֶ�����
// ����  : int *fieldlength [OUT]: ָ�����ֶγ���
BCCSVR_API bool GetFieldInfo(XDHANDLE Handle,int Col, char *fieldname, int *fieldtype, int *fieldlength);

// ����  : ȡ�ö�Ӧ�ֶε�����(��NewXpackHandle������Ľṹ�����ļ����)
// ����  : int  : 0 - ���ֶ�; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
//                -1 �ֶ����������ڻ�Handle����
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : const char *fieldname [IN]: ָ�����ֶ�����,��"vsmess"
BCCSVR_API int GetFieldTypeByName(XDHANDLE Handle,const char *fieldname);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���нӿ������ָ����������������ݣ�������������

/////////////////////////////////////////////////////////////////////////////
// ȡ���յ����������Ϣ�������ݣ�

// ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (int)
// ����  : bool 
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
// ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
// ����  : long *value [OUT]: ���صõ���ֵ
BCCSVR_API bool GetIntFieldByName(XDHANDLE Handle,int Row,const char *fieldname,long *value);

// ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
// ����  : bool 
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
// ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
// ����  : double *value [OUT]: ���صõ���ֵ
BCCSVR_API bool GetDoubleFieldByName(XDHANDLE Handle,int Row,const char *fieldname,double *value);

// ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
// ����  : bool 
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
// ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
// ����  : char *value [OUT]: ���صõ���ֵ
// ����  : int ValueBufferSize [IN]: value�������ĳ��ȣ������Դ�ŵ���󳤶ȣ� һ�����Ϊ <=256
BCCSVR_API bool GetStringFieldByName(XDHANDLE Handle,int Row,const char *fieldname,char *value,int ValueBufferSize);

// ������: GetRecordCount
// ���  : ������ 2005-11-14 18:10:22
// ����  : ��ȡ��������еļ�¼��RecordCount
// ����  : int ���ؽ������ݵļ�¼��
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API int GetRecordCount(XDHANDLE Handle);

// ������: GetXPackType
// ���  : ������ 2005-11-14 21:11:05
// ����  : ��ѯ��ǰ���ݿ������ݼ�¼����
// ����  : int �������ݼ�¼���� 0-��׼ST_PACK��¼��1-ST_SDPACK��RawData��¼
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API int GetXPackType(XDHANDLE Handle); 


// ����  : ����GetXPackType����Ϊ1��ST_SDPACK��ļ�¼��������ñ�������ȡ������Ч��¼�е�RawData��¼
// ����  : int : >=0 - �ɹ�����RawData�����ݳ���(�ֽ���)
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : int Row [IN]: ָ���ļ�¼�� [0..RecordCount-1]
// ����  : char *RawData [OUT]: ��Ŷ�ȡ��RawData���ݿ飬�ڲ���������������8K�ֽڵĻ���
// ����  : int RawDataSize [IN]: RawData���ݿ�Ŀɴ�ŵ������
BCCSVR_API int GetRawRecord(XDHANDLE Handle, int Row, char *RawData, int RawDataSize);

// ����  : ȡReceiveMsg��õ����ݵ������ܺ�
// ����  : int �����ܺ�
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API int GetRequestType(XDHANDLE Handle);

// ����  : ȡReceiveMsg��õ����ݵ�RetCodeֵ
// ����  : int ��Ϣ�����������е�RetCodeֵ
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API int GetRetCode(XDHANDLE Handle);

// ����  : ȡReceiveMsg��>0�ĵõ������Ǵ��ĸ�SvrID��ȡ�õ�
// ����  : int ��Ϣ�����������Ǵ��ĸ�SvrID��ȡ�õ�
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API int GetSvrID(XDHANDLE Handle);

// ����  : ����0��1����Ϣ��ȡ��Ϣ��ţ���Ϣ�����XPACKЭ���У�����Number*100+Day(��λ����)��ɵ�
// ����  : int ������Ϣ��ż�XPACKͷ�е�hook.UserID
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API int GetMsgID(XDHANDLE Handle);


// ����  : ����0��1����Ϣ��ȡ��Ϣ����ԴID
// ����  : int ������Ϣ��ԴID��XPACKͷ�е�hook.queuetype
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API int GetMsgSource(XDHANDLE Handle);


// ����  : ����0��1����Ϣ��ȡ��Ϣ�����κ�
// ����  : int ������Ϣ���κż�XPACKͷ�е�userdata
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
BCCSVR_API int GetMsgBatchNo(XDHANDLE Handle);
//////////////////////////////////////////////////////////////////////////
// ����Ӧ���¼�����ݣ�
	
// ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
// ����  : bool 
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
// ����  : long value [IN]: ����ֵ
BCCSVR_API bool SetIntFieldByName(XDHANDLE Handle,const char *fieldname,long value);

// ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
// ����  : bool 
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
// ����  : double value [IN]: ����ֵ
BCCSVR_API bool SetDoubleFieldByName(XDHANDLE Handle,const char *fieldname,double value);

// ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
// ����  : bool 
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
// ����  : const char *fieldname [IN]: �ֶ����� ��"vsmess"
// ����  : const char *value [IN]: ����ֵ��һ�㲻���Գ���255���ȣ����Ǹ��ֶ�Ϊbinary���ͣ���0xXXXXXX...��ʾ������ֵ
BCCSVR_API bool SetStringFieldByName(XDHANDLE Handle,const char *fieldname,const char *value);

// ������: SetAPackMaxRows
// ���  : ������ 2005-11-14 21:11:00
// ����  : ����Ӧ���ÿ�η��ص�����¼��
// ����  : bool 
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : int MaxRetCount [IN]: ָ��������¼����0�����Զ����� [0..100]; 
BCCSVR_API bool SetAPackMaxRows(XDHANDLE Handle,int MaxRows);

/// ��XPACK��RawData�Ķ�д������
// ����  : ����ָ����¼Ϊָ����RawData��¼
// ����  : bool 
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : const char *RawData [IN]: Ҫ�������ݿ�
// ����  : int RawDataLength [IN]: Ҫ�������ݿ鳤��
BCCSVR_API bool SetRawRecord(XDHANDLE Handle, const char *RawData, int RawDataLength);


///////////////////////////////////////////////////////////////////////////////////////
// ��ҵ��ͨѶƽ̨��صĺ�����

// ����  : ����һ��ͨѶ���񣬰������ӵ�ҵ��ͨѶƽ̨�ڵ��������Ϊ�˽�����Ϣ��������Ҫ��ͨѶ���ܺţ�
//          ע�⣺basefno��privfno�����������ٱ���һ������Ч�ġ�
// ����  : int ����ҵ��ͨѶƽ̨����ID�ţ�<0: ʧ��
// ����  : const char *ip [IN]: ��ҵ��ͨѶƽ̨��IP��ַ
// ����  : int port [IN]: ��ҵ��ͨѶƽ̨�ṩ�Ķ˿ں�port
// ����  : int basefno [IN]: ��ҵ��ͨѶƽ̨��ע��Ĺ����Ĺ��ܺţ�û������д0��
// ����  : int privfno [IN]: ��ҵ��ͨѶƽ̨��ע���˽�еĹ��ܺţ�û������д0��
// ����  : bool bretry [IN]: �Ƿ񵱶Ͽ����Ӻ󣬼���retry���ӡ�
//                           true, �򵱽��մ������ӶϿ���ʱ�򣬻����²�ͣ���ӣ��ָ����գ���ReceiveMsg������-2��Ϣ
//                           false�������ӶϿ�ʱ����ص�ReceiveMsg�����л���յ�-2����Ϣ���˳�����
BCCSVR_API int AddService(int branchno,const char *ip,int port,int basefno, int privfno, bool bretry);

// ����  : ��XPack���ݴ�������ͨѶ����ID
// ����  : int ����ҵ��ͨѶƽ̨����ID�ţ�<0: ʧ��
// ����  : XDHANDLE Handle [IN]: ָ����XPack���������
// ����  : int svrID [IN]: ͨѶ����ID����AddService(...)���ص�ID
BCCSVR_API int BindService(XDHANDLE Handle,int svrID);

// ����  : ��Ϊ�����Ա����õ�ͨѶ���ܺţ�ɨ�������Ϣ����������
// ����  : int    1��0��֪ͨ��Ϣ��2��1��֪ͨ��Ϣ��3�������ͻ����������ݣ���Ҫ��PutRow/DataDone����Ӧ��
//                0: һ���������ݷ��ش�����ɣ�ͬ-1һ����������
//                -1: ��ʾ����ɨ�����Bind��Service��û���յ��µ���Ϣ������ע����������²�Ҫ��ɨ�裬���߳��м�������ȴ���
//                -2: ��ʾ�󶨵�svrID���ӳ��������ˣ�errormessage�н������������Ϣ 
//                <-2: ���ڴ��󣬲ο�errormessage��Ϣ -3: �������
// ����  : XDHANDLE Handle [IN] : �ȴ����յ�XPACK���ݻ�����
// ����  : char *errormessage [OUT] : ��������Ϊ<0��ʱ��Ĵ�����Ϣ
// ����  : int emlen[IN] : errormessage�Ļ��泤��
BCCSVR_API int ReceiveMsg(XDHANDLE Handle,char *errormessage, int emlen);


// ����  : ����ǰ�����е��Ѿ����õ�����(Row=0��)��Ϊһ����¼��׼����ϣ������ύ���Է�
//          ע�⣺��XPACK��CPACKЭ���У��ü�¼���ἴʱ���͸��Է������ǳ�Ϊһ�������İ�
//             �����ڼ�ѹ��ȥ��ģʽ����ÿ�ζ�Ҫ��PutRow��ʾһ����¼׼����ϣ����
//             ͨ������DataDone����ʾ���������������û�и��������Ҫ�����󷽡�
// ����  : int : ���سɹ�>=0 ��ʧ��<0
// ����  : XDHANDLE Handle [IN] : ��������XPACK���ݻ�����
// ����  : int retCode [IN] : ��ǰ�ķ����룬һ����XPACKЭ����0��ʾ�ɹ�
BCCSVR_API int PutRow(XDHANDLE Handle, int retCode);


// ����  : ���ζ��������ݴ����������������Ϣ���ظ�����
// ����  : int : ���سɹ�>=0 ��ʧ��<0
// ����  : XDHANDLE Handle [IN] : ��������XPACK���ݻ�����
// ����  : int retCode [IN] : ��ǰ�ķ����룬һ����XPACKЭ����0��ʾ�ɹ�
BCCSVR_API int DataDone(XDHANDLE Handle, int retCode);

// ����  : �����ǰͨ��SetXXXXFieldByName��SetRawData�����ݣ�����ķ��ؼ�¼�����ݵ��ֶ���
//          ���ʱ��ͻὫǰ��Ľ���ύ�����󷽵ġ�
// ����  : int >=0: �ɹ���<0: ʧ�� 
// ����  : XDHANDLE Handle [IN] : ��������XPACK���ݻ�����
BCCSVR_API int ClearRow(XDHANDLE Handle);
////////////////////////////////////////////////////////////////////////////////
// ��������

// ����  : ����Ϣ��¼��KLG�ļ��У�ֻ����KLGOpen�ɹ�����Ч��
// ����  : void 
// ����  : char *fmt ����Ϣ�ĸ�ʽ����
// ����  : ... ����Ϣ����������������sprintf�еĲ������뷽ʽ
BCCSVR_API void KLGMsg(char *fmt,...);

// ����  : ��KLG�ļ���¼ģʽ��ע��ֻ���Ե���һ�Σ����������ڳ��Ի���ʱ��
// ����  : bool �������Ƿ�ɹ���
// ����  : char *path ��KLG��ŵ�·��
BCCSVR_API bool KLGOpen(char *path);

// ����  : ��¼XPACK���ݰ������ݵ�KLG�ļ��У�ֻ����KLGOpen�ɹ�����Ч��
// ����  : bool �������Ƿ�ɹ�
// ����  : void *pBuf ��XPACK�����ݿ�
// ����  : int nBufLen��XPACK���ݿ�ĳ���
// ����  : const char *pszPackHint�����ݿ�ı�ע��Ϣ�����޳���
BCCSVR_API bool KLGWritePack(void *pBuf, int nBufLen,const char *pszPackHint);


// ����  : ɾ�������ļ�
// ����  : int ���ر�ɾ���ļ��ĸ���
// ����  : char *path_mark ��ɾ�����ļ�·�����������ļ�����
// ����  : char *ext ��ɾ�����ļ���չ��������.xxx
// ����  : int overdue : ���ڵ���Ȼ����
BCCSVR_API int RemoveOverdueFile(const char *path_mark,char *ext,int overdue);


#ifdef __cplusplus
}
#endif

#undef BCCSVR_API

#endif