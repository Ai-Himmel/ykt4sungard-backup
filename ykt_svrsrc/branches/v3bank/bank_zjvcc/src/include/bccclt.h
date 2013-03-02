/********************************************************************
	created:	2006/08/23
	created:	23:8:2006   9:41
	filename: 	D:\proj\ksbass\bcclink\bccclt\bccclt.h
	file path:	D:\proj\ksbass\bcclink\bccclt
	file base:	bccclt
	file ext:	h
	author:		CHENYH
	
	purpose:	���ͷ�ļ�Ŀ����Ϊ���ܹ����ɿ�����C��C++Ҳ�ܵ��õĽӿ�
*********************************************************************/
#ifndef BCCCLT_H
#define BCCCLT_H
#ifdef BCCCLT_EXPORTS
#include "XPData.h"
typedef CXPData * XDHANDLE;
#ifdef _WINDOWS
#define BCCCLT_API __declspec(dllexport)
#else
#define BCCCLT_API 
#endif
#else
typedef void * XDHANDLE;
#ifdef _WINDOWS
#define BCCCLT_API __declspec(dllimport)
#else
#define BCCCLT_API 
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

   // ������: XPackInit
   // ���  : ������ 2005-11-15 11:18:52
   // ����  : Ԥ�����ñ�ϵͳһ�����ж��ٸ�XpackDescribleFile�ļ�����ͬ�ļ�ʹ�ж��XPack�������������Ȼ��һ��
   //		Notice: һ��ϵͳֻ�ܵ�������һ��
   // ����  : bool 
   // ����  : int maxXPackDefs [IN]: ���õ�XpackDescribleFile�ļ������ο�NewXpackHandle()����
	BCCCLT_API  bool XPackInit(int maxXPackDefs);

   // ������: NewXpackHandle
   // ���  : ������ 2005-11-14 17:57:39
   // ����  : ����һ������XPack���ݽ�����������
   // ����  : XDHANDLE : ���ظ�XPack�������ľ����==0(NULL): ʧ��
   // ����  : const char * XpackDescribleFile [IN]: XPack�ṹ�����ļ��������ܳ���1024�ֽڳ�����: "/xpacks/cpack.dat"
	BCCCLT_API  XDHANDLE NewXpackHandle(const char * XpackDescribleFile);

   // ������: ResetPackHandle
   // ���  : ������ 2005-11-14 18:01:30
   // ����  : �������������ݣ���Ҫ����׼���װ�����ʱ����д�������������ֶ�֮ǰ����
   // ����  : bool : false - ����Ϊ�����Handle(==NULL��ʱ��)
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
	BCCCLT_API  bool ResetPackHandle(XDHANDLE Handle);

   // ������: CopyHandle
   // ���  : ������ 2005-11-14 18:04:56
   // ����  : ��SourceHandle�е�״̬����ʽ�����ݵ���Ϣ���Ƶ�DestHandle��
   // ����  : bool : false - ����Ϊ�����Handle(==NULL��ʱ��)
   // ����  : XDHANDLE SourceHandle [IN]: �����Ƶ�ԭXPack���������
   // ����  : XDHANDLE DestHandle   [OUT]: �����Ƶ�Ŀ��XPack������������ڲ����ݱ����ǣ�������������һ�����
	BCCCLT_API  bool CopyHandle(XDHANDLE SourceHandle,XDHANDLE DestHandle);

   // ������: DeleteXpackHandle
   // ���  : ������ 2005-11-14 18:08:08
   // ����  : ���Ѿ���NewXpackHandle�õ����������ͷ�(ж��)
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
	BCCCLT_API  bool DeleteXpackHandle(XDHANDLE Handle);

   // ������: GetFieldTypeByName
   // ���  : ������ 2005-11-14 18:08:37
   // ����  : ȡ�ö�Ӧ�ֶε�����(��NewXpackHandle������Ľṹ�����ļ����)
   // ����  : int  : 0 - ���ֶ�; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
   //                -1 �ֶ����������ڻ�Handle����
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : char * FieldName [IN]: ָ�����ֶ�����,��"vsmess"
	BCCCLT_API  int GetFieldTypeByName(XDHANDLE Handle,char * FieldName);
	

   // ������: GetIntFieldByName
   // ���  : ������ 2005-11-14 18:09:26
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (int)
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : char * FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : int* Value [OUT]: ���صõ���ֵ
	BCCCLT_API  bool GetIntFieldByName(XDHANDLE Handle,int Row,char * FieldName,int * Value);

   // ������: GetDoubleFieldByName
   // ���  : ������ 2005-11-14 18:09:31
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : char * FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : double* Value [OUT]: ���صõ���ֵ
	BCCCLT_API  bool GetDoubleFieldByName(XDHANDLE Handle,int Row,char * FieldName,double * Value);

   // ������: GetStringFieldByName
   // ���  : ������ 2005-11-14 18:09:36
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : char * FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : char * Value [OUT]: ���صõ���ֵ
   // ����  : int ValueBufferSize [IN]: Value�������ĳ��ȣ������Դ�ŵ���󳤶ȣ� һ�����Ϊ <=256
	BCCCLT_API  bool GetStringFieldByName(XDHANDLE Handle,int Row,char * FieldName,char * Value,int ValueBufferSize);
		

   // ������: SetIntFieldByName
   // ���  : ������ 2005-11-14 18:09:57
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : char * FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : int Value [IN]: ����ֵ
	BCCCLT_API  bool SetIntFieldByName(XDHANDLE Handle,int Row,char * FieldName,int Value);

   // ������: SetDoubleFieldByName
   // ���  : ������ 2005-11-14 18:10:02
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : char * FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : double Value [IN]: ����ֵ
	BCCCLT_API  bool SetDoubleFieldByName(XDHANDLE Handle,int Row,char * FieldName,double Value);

   // ������: SetStringFieldByName
   // ���  : ������ 2005-11-14 18:10:07
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : char * FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : char * Value [IN]: ����ֵ�������Գ���255����
	BCCCLT_API  bool SetStringFieldByName(XDHANDLE Handle,int Row,char * FieldName,char * Value);
	

   // ������: SetRequestType
   // ���  : ������ 2005-11-14 18:10:12
   // ����  : �������������еĹ��ܺ� ����EncodeXpackForRequest֮ǰһ��Ҫ���ã�
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int RequestType [IN]: ��Ӧ��ҵ���ܺ�
	BCCCLT_API  bool SetRequestType(XDHANDLE Handle,int RequestType);
	

   // ������: IsEof
   // ���  : ������ 2005-11-14 18:10:17
   // ����  : �Ƿ��Ѿ������һ��Ӧ����ˣ���HaveNextPack�����෴
   // ����  : bool : true - ��ʾ�Ѿ�û�к���Ӧ�����ݰ��ˣ�false - Ҫͨ������EncodeXpackForNext������
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
	BCCCLT_API  bool IsEof(XDHANDLE Handle);
	

   // ������: GetRecordCount
   // ���  : ������ 2005-11-14 18:10:22
   // ����  : ������ȡ�����еļ�¼��RecordCount
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int * RecordCount [OUT]: ���ؽ����ļ�¼��
	BCCCLT_API  bool GetRecordCount(XDHANDLE Handle,int * RecordCount);

   // ������: GetRetCode
   // ���  : ������ 2005-11-14 18:10:28
   // ����  : ������ȡ�䷵����
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int* RetCode [OUT]: �����յ����ݰ��еķ�����
	BCCCLT_API  bool GetRetCode(XDHANDLE Handle,int * RetCode);


   // ������: GetPrivateFunctionForNext
   // ���  : ������ 2005-11-14 21:10:48
   // ����  : �����յý��������ݣ����еõ����ڿ��Ի�ȡ����Ӧ�����ݰ���Ӧ�÷�����ר��ͨѶ���ܺ�
   //          ��ϸ������ο�KSBCCʹ��˵����
   // ����  : int : >0 - �ɻ�ȡ�������ݵ�ר��ͨѶ���ܺţ�����ʧ��
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
	BCCCLT_API  int GetPrivateFunctionForNext(XDHANDLE Handle);

   // ������: GetBranchNoForNext
   // ���  : ������ 2005-11-14 21:10:52
   // ����  : �����յý��������ݣ����еõ����ڿ��Ի�ȡ����Ӧ�����ݰ���Ŀ��ͨѶƽ̨�ڵ���
   //          ��ϸ������ο�KSMBCCʹ��˵����
   // ����  : int >0: ��ȡ����Ӧ�����ݰ���Ŀ��ͨѶƽ̨�ڵ���; ��������ԭ���Ľڵ���
   //                ���ù�������Transferʵ�ֵ�ʱ����Ҫ������ܱ�����˵Ľڵ��
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
	BCCCLT_API  int GetBranchNoForNext(XDHANDLE Handle);

   // ������: SetRecordCount
   // ���  : ������ 2005-11-14 21:10:56
   // ����  : Ԥ�������������еļ�¼��
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int RecordCount [IN]: ���õļ�¼��
	BCCCLT_API  bool SetRecordCount(XDHANDLE Handle,int RecordCount);

   // ������: SetMaxRetCount
   // ���  : ������ 2005-11-14 21:11:00
   // ����  : ����Ӧ���ÿ�η��ص�����¼��
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int MaxRetCount [IN]: ָ��������¼����0����Ӧ�÷������� [0..100]; 
	BCCCLT_API  bool SetMaxRetCount(XDHANDLE Handle,int MaxRetCount);

   // ������: GetXPackType
   // ���  : ������ 2005-11-14 21:11:05
   // ����  : ��ѯ��ǰ���ݿ������ݼ�¼����
   // ����  : int �������ݼ�¼���� 0-��׼ST_PACK��¼��1-ST_SDPACK��RawData��¼
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
	BCCCLT_API  int GetXPackType(XDHANDLE Handle); 

   // ������: SetRawRecord
   // ���  : ������ 2005-11-14 21:11:11
   // ����  : ����ָ����¼Ϊָ����RawData��¼
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ָ�����õļ�¼�� [0..RecordCount-1]
   // ����  : char * RawData [IN]: Ҫ�������ݿ�
   // ����  : int RawDataLength [IN]: Ҫ�������ݿ鳤��
	BCCCLT_API  bool SetRawRecord(XDHANDLE Handle, int Row, char * RawData, int RawDataLength);

   // ������: GetRawRecord
   // ���  : ������ 2005-11-14 21:11:15
   // ����  : ����GetXPackType����Ϊ1��ST_SDPACK��ļ�¼��������ñ�������ȡ������Ч��¼�е�RawData��¼
   // ����  : int : >=0 - �ɹ�����RawData�����ݳ���(�ֽ���)
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : char * RawData [OUT]: ��Ŷ�ȡ��RawData���ݿ� 
   // ����  : int RawDataSize [IN]: RawData���ݿ�Ŀɴ�ŵ������
	BCCCLT_API  int GetRawRecord(XDHANDLE Handle, int Row, char * RawData, int RawDataSize);

   // ������: GetMaxColumn
   // ���  : ������ 2005-11-14 21:11:20
   // ����  : ��ȡ����ʽ��XPack��������Ч�ֶ�����ֵ���뵱ʱ���ݿ鲻ͬ
   // ����  : int ����ST_PACK�е������Ч�ֶ�����ֵ
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
	BCCCLT_API  int GetMaxColumn(XDHANDLE Handle);

   // ������: GetFieldColumn
   // ���  : ������ 2005-11-14 21:11:29
   // ����  : �����ֶ����ƣ�����ֶ�������
   // ����  : int >=0 Ϊ��XPACK����Ч�ֶΣ����ص�ֵ��Ϊ�����ţ�<0Ϊ��XPACK��û������ֶ�
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : char * FieldName [IN]: �ֶ����� ��"vsmess"
	BCCCLT_API  int GetFieldColumn(XDHANDLE Handle, char * FieldName);

   // ������: GetFieldInfo
   // ���  : ������ 2005-11-17 15:11:24
   // ����  : ��ȡָ���ֶε���Ϣ
   // ����  : bool : true-Ϊ��Ч�ֶ�
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int Col [IN]: ָ�����ֶ�������
   // ����  : char * FieldName [OUT]: ����ָ�����ֶ�����
   // ����  : int* FieldType [OUT]: ָ�����ֶ�����
   // ����  : int* FieldLength [OUT]: ָ�����ֶγ���
	BCCCLT_API  bool GetFieldInfo(XDHANDLE Handle,int Col, char * FieldName, int * FieldType, int * FieldLength);

   // ������: HaveNextPack
   // ���  : ������ 2005-11-14 22:01:15
   // ����  : �������ͨ���������ж��Ƿ��к���Ӧ���
   // ����  : bool : true-��ʾ���к���Ӧ�����false���޺�����
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
	BCCCLT_API  bool HaveNextPack(XDHANDLE Handle);

	///////////////////////////////////////////////////////////////////////////////////////
	// ��ҵ��ͨѶƽ̨��صĺ�����

   // ������: BCCCLTInit
   // ���  : ������ 2005-11-15 11:22:35
   // ����  : ���Ի���ϵͳ��ֱ�����Ӷ��ٸ�ҵ��ͨѶƽ̨�ڵ����
   //		Notice: ϵͳֻ�ܵ���һ��
   // ����  : bool 
   // ����  : int maxnodes=1 [IN]: ���������ж��ٸ����ӽڵ�
	BCCCLT_API  bool BCCCLTInit(int maxnodes);


   // ������: AddDrtpNode
   // ���  : ������ 2005-11-15 11:24:25
   // ����  : ����һ��Ҫֱ�����ӵ�ҵ��ͨѶƽ̨�ڵ�
   //       ��Ϊϵͳ���Ի����֣������ڵ���BCCCLTInit����ͳһһ���߳���һ���Ե�������ϣ�����������ʹ��
   // ����  : int  ���ӵ�ҵ��ͨѶƽ̨�ڵ��� >=0:�ɹ������򣬿���û����ȷ����BCCCLTInit()
   // ����  : char * ip [IN]: ��ҵ��ͨѶƽ̨��IP��ַ
   // ����  : int port [IN]: ��ҵ��ͨѶƽ̨�ṩ�Ķ˿ں�port
	BCCCLT_API  int AddDrtpNode(char * ip,int port);


   // ������: CallRequest
   // ���  : ������ 2005-11-15 11:27:07
   // ����  : ��ǰ�����ú�XPack�������ݴ�����͸�ָ����ͨѶƽ̨��Ӧ�÷�����
   // ����  : bool : true �ɹ����ͣ����ҽ��ս�����Ӧ�����ݣ�false ����ʧ�ܣ�������󣬲μ�������
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int drtpno [IN]: ���Ǹ�ֱ����ҵ��ͨѶƽ̨�ڵ㷢�ͺͽ������ݣ��μ�AddDrtpNode()�ķ���ֵ
   // ����  : int branchno [IN]: Ŀ��Ӧ�÷��������ӵ�ҵ��ͨѶƽ̨�ڵ��ţ��μ�ҵ��ͨѶƽ̨�����ò�����
   // ����  : int function [IN]: Ŀ��Ӧ�÷�����ע����ҵ��ͨѶƽ̨�Ĺ��ܺ� (�μ�BCC�����ļ��е�BASEFUNCNO)
   // ����  : int timeout [IN]: ���ͽ������ݵĳ�ʱʱ�䣬�Ժ����
   // ����  : int* errcode [OUT]: ���صĴ�����
   // ����  : char * errormessage [OUT]: ���صĴ�����Ϣ
	BCCCLT_API  bool CallRequest(XDHANDLE Handle, int drtpno, int branchno,int function, int timeout, int *errcode,char * errormessage);


   // ������: CallNext
   // ���  : ������ 2005-11-15 11:30:38
   // ����  : ȡ��һ������Ӧ���
   //          �ڳɹ�����CallRequest�������鵽HaveNextPack()�����ñ����ܻ�ȡ��һ������Ӧ���
   // ����  : bool ��true �ɹ����ͣ����ҽ��ս�����Ӧ�����ݣ�false ����ʧ�ܣ�������󣬲μ�������
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int timeout [IN]: ���ͽ������ݵĳ�ʱʱ�䣬�Ժ����
   // ����  : int* errcode [OUT]: ���صĴ�����
   // ����  : char * errormessage [OUT]: ���صĴ�����Ϣ
	BCCCLT_API  bool CallNext(XDHANDLE Handle, int timeout, int* errcode,char * errormessage);


   // ������: EmulateMaxRows
   // ���  : ������ 2006-8-23 9:53:42
   // ����  : ����Ҫ��һ�������ʱ������������Ҫ���Ͷ��¼��ʱ��Ϊ�˻��һ���ܹ����Ͷ��ټ�¼��
   //         ��Ҫ�ڵ�һ����¼��SetxxxxFieldByName�����󣬲ſɵ��ñ�������
   //          ע�⣺���м�¼ʹ�õ��ֶα�����ͬ�������ǵ�һ����¼���õ���Щ�ֶ�
   // ����  : int �������������ö�������¼
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   BCCCLT_API  int EmulateMaxRows(XDHANDLE Handle);


   // ������: SetDebugSwitch
   // ���  : ������ 2006-8-24 10:26:51
   // ����  : �����Ƿ�򿪵��Ը����ļ�
   // ����  : void 
   // ����  : bool bDebug [IN]: 0(false) - off; 1(true) - on
   BCCCLT_API  void SetDebugSwitch(bool bDebug);

   // ������: Broad
   // ���  : ������ 2006-8-25 18:41:34
   // ����  : ��ǰ�����ú�XPack�������������з��������ķ����(destno:funcno)�㲥
   //          ע��:���ڽ��ն˿�����࣬����ģʽ��ͬBCC�ܹ��е�������Ϣ0ģʽ����
   //                ���ն˲�Ҫ����Ӧ���ȷ����Ϣ������Ҳ��Ҫ����
   //                ������ֻ����DRTP4�汾��ʵ�֣�DRTP3һ�ŷ���false
   // ����  : bool 
   // ����  : XDHANDLE Handle [IN]: ָ����XPack���������
   // ����  : int drtpno [IN]: ���Ǹ�ֱ����ҵ��ͨѶƽ̨�ڵ�㲥���ݣ��μ�AddDrtpNode()�ķ���ֵ
   // ����  : int branchno [IN]: Ŀ��Ӧ�÷������ӵ�ҵ��ͨѶƽ̨�ڵ��� >=0;  =0: ��ȫ���㲥,�������ָ���ڵ��ϵĹ㲥
   // ����  : int function [IN]: Ŀ��Ӧ�÷���ע����ҵ��ͨѶƽ̨�����ڽ��չ㲥�Ĺ��ܺţ�����Ϊͨ�ù��ܺŻ�ר�Ž��չ㲥�Ĺ��ܺţ�
   // ����  : int* errcode [OUT]: ���صĴ�����
   // ����  : char *errmsg [OUT]: ��Ҫ512�ֽڿռ䣬���ش�����Ϣ
   BCCCLT_API bool Broad(XDHANDLE Handle, int drtpno, int destno, int funcno, int *errcode, char *errmsg);

#ifdef __cplusplus
}
#endif

#undef BCCCLT_API
   

#endif
