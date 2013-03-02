/********************************************************************
 created:	2006/05/29
 created:	29:5:2006   16:56
 filename: 	D:\proj\ksbass\bcclink\bccclt\bccclt.java
 file path:	D:\proj\ksbass\bcclink\bccclt
 file base:	bccclt
 file ext:	java
 author:		CHENYH
 
 purpose:	JAVA�ӿڿ⣬�Կͻ���ʽͨ��ҵ��ͨѶƽ̨����BCCҵ����
 *********************************************************************/
package com.kingstar.bcc;

public class bccclt {
	// ������: SetDebugSwitch
	// ��� : ������ 2006-8-24 10:26:51
	// ���� : �����Ƿ�򿪵��Ը����ļ�
	// ���� : void
	// ���� : bool bDebug [IN]: 0(false) - off; 1(true) - on
	public native boolean SetDebugSwitch(boolean bDebug);

	// ������: XPackInit
	// ��� : ������ 2005-11-15 11:18:52
	// ���� : Ԥ�����ñ�ϵͳһ�����ж��ٸ�XpackDescribleFile�ļ�����ͬ�ļ�ʹ�ж��XPack�������������Ȼ��һ��
	// Notice: һ��ϵͳֻ�ܵ�������һ��
	// ���� : boolean
	// ���� : int maxXPackDefs [IN]: ���õ�XpackDescribleFile�ļ������ο�NewXpackHandle()����
	public native boolean XPackInit(int maxXPackDefs);

	// ������: NewXpackHandle
	// ��� : ������ 2005-11-14 17:57:39
	// ���� : ����һ������XPack���ݽ�����������
	// ���� : long : ���ظ�XPack�������ľ����==0(NULL): ʧ��
	// ���� : byte[] XpackDescribleFile [IN]: XPack�ṹ�����ļ��������ܳ���1024�ֽڳ�����:
	// "/xpacks/cpack.dat"
	public native long NewXpackHandle(byte[] XpackDescribleFile);

	// ������: ResetPackHandle
	// ��� : ������ 2005-11-14 18:01:30
	// ���� : �������������ݣ���Ҫ����׼���װ�����ʱ����д�������������ֶ�֮ǰ����
	// ���� : boolean : false - ����Ϊ�����Handle(==NULL��ʱ��)
	// ���� : long Handle [IN]: ָ����XPack���������
	public native boolean ResetPackHandle(long Handle);

	// ������: CopyHandle
	// ��� : ������ 2005-11-14 18:04:56
	// ���� : ��SourceHandle�е�״̬����ʽ�����ݵ���Ϣ���Ƶ�DestHandle��
	// ���� : boolean : false - ����Ϊ�����Handle(==NULL��ʱ��)
	// ���� : long SourceHandle [IN]: �����Ƶ�ԭXPack���������
	// ���� : long DestHandle [OUT]: �����Ƶ�Ŀ��XPack������������ڲ����ݱ����ǣ�������������һ�����
	public native boolean CopyHandle(long SourceHandle, long DestHandle);

	// ������: DeleteXpackHandle
	// ��� : ������ 2005-11-14 18:08:08
	// ���� : ���Ѿ���NewXpackHandle�õ����������ͷ�(ж��)
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	public native boolean DeleteXpackHandle(long Handle);

	// ������: GetFieldTypeByName
	// ��� : ������ 2005-11-14 18:08:37
	// ���� : ȡ�ö�Ӧ�ֶε�����(��NewXpackHandle������Ľṹ�����ļ����)
	// ���� : int : 0 - ���ֶ�; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double
	// -1 �ֶ����������ڻ�Handle����
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : byte[] FieldName [IN]: ָ�����ֶ�����,��"vsmess"
	public native int GetFieldTypeByName(long Handle, byte[] FieldName);

	// ������: GetIntFieldByName
	// ��� : ������ 2005-11-14 18:09:26
	// ���� : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (int)
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
	// ���� : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
	// ���� : int[] Value [OUT]: ���صõ���ֵ
	public native boolean GetIntFieldByName(long Handle, int Row,
			byte[] FieldName, int[] Value);

	// ������: GetDoubleFieldByName
	// ��� : ������ 2005-11-14 18:09:31
	// ���� : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
	// ���� : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
	// ���� : double[] Value [OUT]: ���صõ���ֵ
	public native boolean GetDoubleFieldByName(long Handle, int Row,
			byte[] FieldName, double[] Value);

	// ������: GetStringFieldByName
	// ��� : ������ 2005-11-14 18:09:36
	// ���� : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
	// ���� : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
	// ���� : byte[] Value [OUT]: ���صõ���ֵ
	// ���� : int ValueBufferSize [IN]: Value�������ĳ��ȣ������Դ�ŵ���󳤶ȣ� һ�����Ϊ <=256
	public native boolean GetStringFieldByName(long Handle, int Row,
			byte[] FieldName, byte[] Value, int ValueBufferSize);

	// ������: SetIntFieldByName
	// ��� : ������ 2005-11-14 18:09:57
	// ���� : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
	// ���� : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
	// ���� : int Value [IN]: ����ֵ
	public native boolean SetIntFieldByName(long Handle, int Row,
			byte[] FieldName, int Value);

	// ������: SetDoubleFieldByName
	// ��� : ������ 2005-11-14 18:10:02
	// ���� : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
	// ���� : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
	// ���� : double Value [IN]: ����ֵ
	public native boolean SetDoubleFieldByName(long Handle, int Row,
			byte[] FieldName, double Value);

	// ������: SetStringFieldByName
	// ��� : ������ 2005-11-14 18:10:07
	// ���� : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
	// ���� : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
	// ���� : byte[] Value [IN]: ����ֵ�������Գ���255����
	public native boolean SetStringFieldByName(long Handle, int Row,
			byte[] FieldName, byte[] Value);

	// ������: SetRequestType
	// ��� : ������ 2005-11-14 18:10:12
	// ���� : �������������еĹ��ܺ� ����EncodeXpackForRequest֮ǰһ��Ҫ���ã�
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int RequestType [IN]: ��Ӧ��ҵ���ܺ�
	public native boolean SetRequestType(long Handle, int RequestType);

	// ������: IsEof
	// ��� : ������ 2005-11-14 18:10:17
	// ���� : �Ƿ��Ѿ������һ��Ӧ����ˣ���HaveNextPack�����෴
	// ���� : boolean : true - ��ʾ�Ѿ�û�к���Ӧ�����ݰ��ˣ�false - Ҫͨ������EncodeXpackForNext������
	// ���� : long Handle [IN]: ָ����XPack���������
	public native boolean IsEof(long Handle);

	// ������: GetRecordCount
	// ��� : ������ 2005-11-14 18:10:22
	// ���� : ������ȡ�����еļ�¼��RecordCount
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int[] RecordCount [OUT]: ���ؽ����ļ�¼��
	public native boolean GetRecordCount(long Handle, int[] RecordCount);

	// ������: GetRetCode
	// ��� : ������ 2005-11-14 18:10:28
	// ���� : ������ȡ�䷵����
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int[] RetCode [OUT]: �����յ����ݰ��еķ�����
	public native boolean GetRetCode(long Handle, int[] RetCode);

	// ������: GetPrivateFunctionForNext
	// ��� : ������ 2005-11-14 21:10:48
	// ���� : �����յý��������ݣ����еõ����ڿ��Ի�ȡ����Ӧ�����ݰ���Ӧ�÷�����ר��ͨѶ���ܺ�
	// ��ϸ������ο�KSBCCʹ��˵����
	// ���� : int : >0 - �ɻ�ȡ�������ݵ�ר��ͨѶ���ܺţ�����ʧ��
	// ���� : long Handle [IN]: ָ����XPack���������
	public native int GetPrivateFunctionForNext(long Handle);

	// ������: GetBranchNoForNext
	// ��� : ������ 2005-11-14 21:10:52
	// ���� : �����յý��������ݣ����еõ����ڿ��Ի�ȡ����Ӧ�����ݰ���Ŀ��ͨѶƽ̨�ڵ���
	// ��ϸ������ο�KSMBCCʹ��˵����
	// ���� : int >0: ��ȡ����Ӧ�����ݰ���Ŀ��ͨѶƽ̨�ڵ���; ��������ԭ���Ľڵ���
	// ���ù�������Transferʵ�ֵ�ʱ����Ҫ������ܱ�����˵Ľڵ��
	// ���� : long Handle [IN]: ָ����XPack���������
	public native int GetBranchNoForNext(long Handle);

	// ������: SetRecordCount
	// ��� : ������ 2005-11-14 21:10:56
	// ���� : Ԥ�������������еļ�¼��
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int RecordCount [IN]: ���õļ�¼��
	public native boolean SetRecordCount(long Handle, int RecordCount);

	// ������: SetMaxRetCount
	// ��� : ������ 2005-11-14 21:11:00
	// ���� : ����Ӧ���ÿ�η��ص�����¼��
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int MaxRetCount [IN]: ָ��������¼����0����Ӧ�÷������� [0..100];
	public native boolean SetMaxRetCount(long Handle, int MaxRetCount);

	// ������: GetXPackType
	// ��� : ������ 2005-11-14 21:11:05
	// ���� : ��ѯ��ǰ���ݿ������ݼ�¼����
	// ���� : int �������ݼ�¼���� 0-��׼ST_PACK��¼��1-ST_SDPACK��RawData��¼
	// ���� : long Handle [IN]: ָ����XPack���������
	public native int GetXPackType(long Handle);

	// ������: SetRawRecord
	// ��� : ������ 2005-11-14 21:11:11
	// ���� : ����ָ����¼Ϊָ����RawData��¼
	// ���� : boolean
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int Row [IN]: ָ�����õļ�¼�� [0..RecordCount-1]
	// ���� : byte[] RawData [IN]: Ҫ�������ݿ�
	// ���� : int RawDataLength [IN]: Ҫ�������ݿ鳤��
	public native boolean SetRawRecord(long Handle, int Row, byte[] RawData,
			int RawDataLength);

	// ������: GetRawRecord
	// ��� : ������ 2005-11-14 21:11:15
	// ���� : ����GetXPackType����Ϊ1��ST_SDPACK��ļ�¼��������ñ�������ȡ������Ч��¼�е�RawData��¼
	// ���� : int : >=0 - �ɹ�����RawData�����ݳ���(�ֽ���)
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int Row [IN]: ָ���ļ�¼�� [0..RecordCount-1]
	// ���� : byte[] RawData [OUT]: ��Ŷ�ȡ��RawData���ݿ�
	// ���� : int RawDataSize [IN]: RawData���ݿ�Ŀɴ�ŵ������
	public native int GetRawRecord(long Handle, int Row, byte[] RawData,
			int RawDataSize);

	// ������: GetMaxColumn
	// ��� : ������ 2005-11-14 21:11:20
	// ���� : ��ȡ����ʽ��XPack��������Ч�ֶ�����ֵ���뵱ʱ���ݿ鲻ͬ
	// ���� : int ����ST_PACK�е������Ч�ֶ�����ֵ
	// ���� : long Handle [IN]: ָ����XPack���������
	public native int GetMaxColumn(long Handle);

	// ������: GetFieldColumn
	// ��� : ������ 2005-11-14 21:11:29
	// ���� : �����ֶ����ƣ�����ֶ�������
	// ���� : int >=0 Ϊ��XPACK����Ч�ֶΣ����ص�ֵ��Ϊ�����ţ�<0Ϊ��XPACK��û������ֶ�
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
	public native int GetFieldColumn(long Handle, byte[] FieldName);

	// ������: GetFieldInfo
	// ��� : ������ 2005-11-17 15:11:24
	// ���� : ��ȡָ���ֶε���Ϣ
	// ���� : boolean : true-Ϊ��Ч�ֶ�
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int Col [IN]: ָ�����ֶ�������
	// ���� : byte[] FieldName [OUT]: ����ָ�����ֶ�����
	// ���� : int[] FieldType [OUT]: ָ�����ֶ�����
	// ���� : int[] FieldLength [OUT]: ָ�����ֶγ���
	public native boolean GetFieldInfo(long Handle, int Col, byte[] FieldName,
			int[] FieldType, int[] FieldLength);

	// ������: HaveNextPack
	// ��� : ������ 2005-11-14 22:01:15
	// ���� : �������ͨ���������ж��Ƿ��к���Ӧ���
	// ���� : boolean : true-��ʾ���к���Ӧ�����false���޺�����
	// ���� : long Handle [IN]: ָ����XPack���������
	public native boolean HaveNextPack(long Handle);

	// /////////////////////////////////////////////////////////////////////////////////////
	// ��ҵ��ͨѶƽ̨��صĺ�����

	// ������: BCCCLTInit
	// ��� : ������ 2005-11-15 11:22:35
	// ���� : ���Ի���ϵͳ��ֱ�����Ӷ��ٸ�ҵ��ͨѶƽ̨�ڵ����
	// Notice: ϵͳֻ�ܵ���һ��
	// ���� : boolean
	// ���� : int maxnodes=1 [IN]: ���������ж��ٸ����ӽڵ�
	public native boolean BCCCLTInit(int maxnodes);

	// ������: AddDrtpNode
	// ��� : ������ 2005-11-15 11:24:25
	// ���� : ����һ��Ҫֱ�����ӵ�ҵ��ͨѶƽ̨�ڵ�
	// ��Ϊϵͳ���Ի����֣������ڵ���BCCCLTInit����ͳһһ���߳���һ���Ե�������ϣ�����������ʹ��
	// ���� : int ���ӵ�ҵ��ͨѶƽ̨�ڵ��� >=0:�ɹ������򣬿���û����ȷ����BCCCLTInit()
	// ���� : byte[] ip [IN]: ��ҵ��ͨѶƽ̨��IP��ַ
	// ���� : int port [IN]: ��ҵ��ͨѶƽ̨�ṩ�Ķ˿ں�port
	public native int AddDrtpNode(byte[] ip, int port);

	// ������: CallRequest
	// ��� : ������ 2005-11-15 11:27:07
	// ���� : ��ǰ�����ú�XPack�������ݴ�����͸�ָ����ͨѶƽ̨��Ӧ�÷�����
	// ���� : boolean : true �ɹ����ͣ����ҽ��ս�����Ӧ�����ݣ�false ����ʧ�ܣ�������󣬲μ�������
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int drtpno [IN]: ���Ǹ�ֱ����ҵ��ͨѶƽ̨�ڵ㷢�ͺͽ������ݣ��μ�AddDrtpNode()�ķ���ֵ
	// ���� : int branchno [IN]: Ŀ��Ӧ�÷��������ӵ�ҵ��ͨѶƽ̨�ڵ��ţ��μ�ҵ��ͨѶƽ̨�����ò�����
	// ���� : int function [IN]: Ŀ��Ӧ�÷�����ע����ҵ��ͨѶƽ̨�Ĺ��ܺ� (�μ�BCC�����ļ��е�BASEFUNCNO)
	// ���� : int timeout [IN]: ���ͽ������ݵĳ�ʱʱ�䣬�Ժ����
	// ���� : int[] errcode [OUT]: ���صĴ�����
	// ���� : byte[] errormessage [OUT]: ���صĴ�����Ϣ
	public native boolean CallRequest(long Handle, int drtpno, int branchno,
			int function, int timeout, int[] errcode, byte[] errormessage);

	// ������: CallNext
	// ��� : ������ 2005-11-15 11:30:38
	// ���� : ȡ��һ������Ӧ���
	// �ڳɹ�����CallRequest�������鵽HaveNextPack()�����ñ����ܻ�ȡ��һ������Ӧ���
	// ���� : boolean ��true �ɹ����ͣ����ҽ��ս�����Ӧ�����ݣ�false ����ʧ�ܣ�������󣬲μ�������
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int timeout [IN]: ���ͽ������ݵĳ�ʱʱ�䣬�Ժ����
	// ���� : int[] errcode [OUT]: ���صĴ�����
	// ���� : byte[] errormessage [OUT]: ���صĴ�����Ϣ
	public native boolean CallNext(long Handle, int timeout, int[] errcode,
			byte[] errormessage);

	// ������: EmulateMaxRows
	// ��� : ������ 2006-8-23 9:53:42
	// ���� : ����Ҫ��һ�������ʱ������������Ҫ���Ͷ��¼��ʱ��Ϊ�˻��һ���ܹ����Ͷ��ټ�¼��
	// ��Ҫ�ڵ�һ����¼��SetxxxxFieldByName�����󣬲ſɵ��ñ�������
	// ע�⣺���м�¼ʹ�õ��ֶα�����ͬ�������ǵ�һ����¼���õ���Щ�ֶ�
	// ���� : int �������������ö�������¼
	// ���� : long Handle [IN]: ָ����XPack���������
	public native int EmulateMaxRows(long Handle);

	// ������: Broad
	// ��� : ������ 2006-8-25 18:41:34
	// ���� : ��ǰ�����ú�XPack�������������з��������ķ����(destno:funcno)�㲥
	// ע��:���ڽ��ն˿�����࣬����ģʽ��ͬBCC�ܹ��е�������Ϣ0ģʽ����
	// ���ն˲�Ҫ����Ӧ���ȷ����Ϣ������Ҳ��Ҫ����
	// ������ֻ����DRTP4�汾��ʵ�֣�DRTP3һ�ŷ���false
	// ���� : boolean:
	// ���� : long Handle [IN]: ָ����XPack���������
	// ���� : int drtpno [IN]: ���Ǹ�ֱ����ҵ��ͨѶƽ̨�ڵ�㲥���ݣ��μ�AddDrtpNode()�ķ���ֵ
	// ���� : int branchno [IN]: Ŀ��Ӧ�÷������ӵ�ҵ��ͨѶƽ̨�ڵ��� >=0; =0: ��ȫ���㲥,�������ָ���ڵ��ϵĹ㲥
	// ���� : int funcno [IN]: Ŀ��Ӧ�÷���ע����ҵ��ͨѶƽ̨�����ڽ��չ㲥�Ĺ��ܺţ�����Ϊͨ�ù��ܺŻ�ר�Ž��չ㲥�Ĺ��ܺţ�
	// ���� : int* errcode [OUT]: ���صĴ�����
	// ���� : char *errmsg [OUT]: ��Ҫ512�ֽڿռ䣬���ش�����Ϣ
	public native boolean Broad(long Handle, int drtpno, int destno,
			int funcno, int[] errcode, byte[] errmsg);

	static {
		try {
			System.out.println(System.getProperty("java.library.path"));
			System.loadLibrary("bccclt");
		} catch (UnsatisfiedLinkError e) {			
			System.err.println("���ܼ���so�ļ�(can not load so file!):\n " + e.toString());
		}

	}
}
