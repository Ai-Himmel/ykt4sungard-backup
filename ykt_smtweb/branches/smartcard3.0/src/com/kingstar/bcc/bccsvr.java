/********************************************************************
	created:	2006/05/31
	created:	31:5:2006   11:19
	filename: 	D:\proj\ksbass\bcclink\bccsvr\bccsvr.java
	file path:	D:\proj\ksbass\bcclink\bccsvr
	file base:	bccsvr
	file ext:	java
	author:		CHENYH
	
	purpose:	JAVA�ӿڿ⣬�Է���ʽͨ��ҵ��ͨѶƽ̨����֪ͨ��Ϣ��
         ͬʱҲ�ܽ�������Ȼ���Է���ʽ���������Ӧ������

   2006-11-27 10:39:32  ���ӿ��е�String������ת��Ϊbyte[] ���� �� PeterXҪ��
*********************************************************************/
package com.kingstar.bcc;

public class bccsvr
{
   ///////////////////////////////////////////////////////////////////////////////////////////////////
   /// ���к��������������޹أ�ֻ�����ڳ��Ի�XPACK�����XPACK�ṹ��Ϣ��ȡ

   // ������: NewXpackHandle
   // ���  : ������ 2006-11-14 17:57:39
   // ����  : ����һ������XPack���ݽ�����������
   // ����  : long : ���ظ�XPack�������ľ����==0(NULL): ʧ��
   // ����  : byte[] XpackDescribleFile [IN]: XPack�ṹ�����ļ��������ܳ���1024�ֽڳ�����: "/xpacks/cpack.dat"
	public native long NewXpackHandle(byte[] XpackDescribleFile);


   // ������: DeleteXpackHandle
   // ���  : ������ 2006-11-14 18:08:08
   // ����  : ���Ѿ���NewXpackHandle�õ����������ͷ�(ж��)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
	public native boolean DeleteXpackHandle(long Handle);

   // ������: GetMaxColumn
   // ���  : ������ 2006-11-14 21:11:20
   // ����  : ��ȡ����ʽ��XPack��������Ч�ֶ�����ֵ���뵱ʱ���ݿ鲻ͬ
   // ����  : int ����ST_PACK�е������Ч�ֶ�����ֵ
   // ����  : long Handle [IN]: ָ����XPack���������
	public native int GetMaxColumn(long Handle);

   // ������: GetFieldColumn
   // ���  : ������ 2006-11-14 21:11:29
   // ����  : �����ֶ����ƣ�����ֶ�������
   // ����  : int >=0 Ϊ��XPACK����Ч�ֶΣ����ص�ֵ��Ϊ�����ţ�<0Ϊ��XPACK��û������ֶ�
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
	public native int GetFieldColumn(long Handle, byte[] FieldName);

   // ������: GetFieldInfo
   // ���  : ������ 2006-11-17 15:11:24
   // ����  : ��ȡָ���ֶε���Ϣ
   // ����  : boolean : true-Ϊ��Ч�ֶ�
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Col [IN]: ָ�����ֶ�������
   // ����  : byte[] FieldName [OUT]: ����ָ�����ֶ�����, ����64�ֽڵĿռ�
   // ����  : int[] FieldType [OUT]: ָ�����ֶ�����
   // ����  : int[] FieldLength [OUT]: ָ�����ֶγ���
	public native boolean GetFieldInfo(long Handle,int Col, byte[] FieldName, int [] FieldType, int [] FieldLength);

   // ������: GetFieldTypeByName
   // ���  : ������ 2006-11-14 18:08:37
   // ����  : ȡ�ö�Ӧ�ֶε�����(��NewXpackHandle������Ľṹ�����ļ����)
   // ����  : int  : 0 - ���ֶ�; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
   //                -1 �ֶ����������ڻ�Handle����
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] FieldName [IN]: ָ�����ֶ�����,��"vsmess"
	public native int GetFieldTypeByName(long Handle,byte[] FieldName);


   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// ���нӿ������ָ����������������ݣ�������������
	
   // ������: GetIntFieldByName
   // ���  : ������ 2006-11-14 18:09:26
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (int)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : int[] Value [OUT]: ���صõ���ֵ
	public native boolean GetIntFieldByName(long Handle,int Row,byte[] FieldName,int[] Value);

   // ������: GetDoubleFieldByName
   // ���  : ������ 2006-11-14 18:09:31
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : double[] Value [OUT]: ���صõ���ֵ
	public native boolean GetDoubleFieldByName(long Handle,int Row,byte[] FieldName,double[] Value);

   // ������: GetStringFieldByName
   // ���  : ������ 2006-11-14 18:09:36
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : byte[] Value [OUT]: ���صõ���ֵ������1024�ֽڳ��ȵĿռ�
   // ����  : int ValueBufferSize [IN]: Value�������ĳ��ȣ������Դ�ŵ���󳤶ȣ� 
	public native boolean GetStringFieldByName(long Handle,int Row,byte[] FieldName,byte[] Value,int ValueBufferSize);
	
   // ������: GetRecordCount
   // ���  : ������ 2006-11-14 18:10:22
   // ����  : ������ȡ�����еļ�¼��RecordCount
   // ����  : int <0: ����>=0:�ɹ����ص�ǰ���ܵ������ݼ�¼��
   // ����  : long Handle [IN]: ָ����XPack���������
	public native int GetRecordCount(long Handle);

   // ������: GetXPackType
   // ���  : ������ 2006-11-14 21:11:05
   // ����  : ��ѯ��ǰ���ݿ������ݼ�¼����
   // ����  : int �������ݼ�¼���� 0-��׼ST_PACK��¼��1-ST_SDPACK��RawData��¼; <0 �� ����ľ��
   // ����  : long Handle [IN]: ָ����XPack���������
	public native int GetXPackType(long Handle); 

   // ������: GetRawRecord
   // ���  : ������ 2006-11-14 21:11:15
   // ����  : ����GetXPackType����Ϊ1��ST_SDPACK��ļ�¼��������ñ�������ȡ������Ч��¼�е�RawData��¼
   // ����  : int : >=0 - �ɹ�����RawData�����ݳ���(�ֽ���)
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] RawData [OUT]: ��Ŷ�ȡ��RawData���ݿ飬�ڲ���������������8K�ֽڵĻ���
   // ����  : int RawDataSize [IN]: RawData���ݿ�Ŀɴ�ŵ������
	public native int GetRawRecord(long Handle, int Row, byte[] RawData, int RawDataSize);

   // ������: GetRequestType
   // ���  : ������ 2006-7-11 14:06:12
   // ����  : ȡReceiveMsg��õ����ݵ������ܺ�
   // ����  : int �����ܺ�
   // ����  : long Handle [IN]: ָ����XPack���������
   public native int GetRequestType(long Handle);

   // ����  : ȡReceiveMsg��õ����ݵ�RetCodeֵ
   // ����  : int ��Ϣ�����������е�RetCodeֵ
   // ����  : long Handle [IN]: ָ����XPack���������
   public native int GetRetCode(long Handle);

   // ����  : ȡReceiveMsg��>0�ĵõ������Ǵ��ĸ�SvrID��ȡ�õ�
   // ����  : int ��Ϣ�����������Ǵ��ĸ�SvrID��ȡ�õ�
   // ����  : long Handle [IN]: ָ����XPack���������
   public native int GetSvrID(long Handle);

   // ����  : ����0��1����Ϣ��ȡ��Ϣ��ţ���Ϣ�����XPACKЭ���У�����Number*100+Day(��λ����)��ɵ�
   // ����  : int ������Ϣ��ż�XPACKͷ�е�hook.UserID
   // ����  : long Handle [IN]: ָ����XPack���������
   public native int GetMsgID(long Handle);

   // ����  : ����0��1����Ϣ��ȡ��Ϣ����ԴID
   // ����  : int ������Ϣ��ԴID��XPACKͷ�е�hook.queuetype
   // ����  : long Handle [IN]: ָ����XPack���������
   public native int GetMsgSource(long Handle);

   // ����  : ����0��1����Ϣ��ȡ��Ϣ�����κ�
   // ����  : int ������Ϣ���κż�XPACKͷ�е�userdata
   // ����  : long Handle [IN]: ָ����XPack���������
   public native int GetMsgBatchNo(long Handle);

   //////////////////////////////////////////////////////////////////////////
   // ����Ӧ������ݲ��ֵĺ�����
   ///////////////////////////////////////////////
   // ������: SetIntFieldByName
   // ���  : ������ 2006-11-14 18:09:57
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : int Value [IN]: ����ֵ
	public native boolean SetIntFieldByName(long Handle,byte[] FieldName,int Value);

   // ������: SetDoubleFieldByName
   // ���  : ������ 2006-11-14 18:10:02
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : double Value [IN]: ����ֵ
	public native boolean SetDoubleFieldByName(long Handle,byte[] FieldName,double Value);

   // ������: SetStringFieldByName
   // ���  : ������ 2006-11-14 18:10:07
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : byte[] Value [IN]: ����ֵ��һ�㲻���Գ���255���ȣ����Ǹ��ֶ�Ϊbinary���ͣ���0xXXXXXX...��ʾ������ֵ
	public native boolean SetStringFieldByName(long Handle,byte[] FieldName,byte[] Value);

   // ������: SetAPackMaxRows
   // ���  : ������ 2006-11-14 21:11:00
   // ����  : ����Ӧ���ÿ�η��ص�����¼��
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int MaxRetCount [IN]: ָ��������¼����0�����Զ����� [0..100]; 
	public native boolean SetAPackMaxRows(long Handle,int MaxRows);

   /// ��XPACK��RawData�Ķ�д������
   // ������: SetRawRecord
   // ���  : ������ 2006-11-14 21:11:11
   // ����  : ����ָ����¼Ϊָ����RawData��¼
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] RawData [IN]: Ҫ�������ݿ�
   // ����  : int RawDataLength [IN]: Ҫ�������ݿ鳤��
	public native boolean SetRawRecord(long Handle, byte[] RawData, int RawDataLength);

	///////////////////////////////////////////////////////////////////////////////////////
	// ��ҵ��ͨѶƽ̨��صĺ�����

   // ������: AddService
   // ���  : ������ 2006-6-15 11:24:25
   // ����  : ����һ��ͨѶ���񣬰������ӵ�ҵ��ͨѶƽ̨�ڵ��������Ϊ�˽�����Ϣ��������Ҫ��ͨѶ���ܺţ�
   //          ע�⣺basefno��privfno�����������ٱ���һ������Ч�ġ�
   // ����  : int ����ҵ��ͨѶƽ̨����ID�ţ�<0: ʧ��
   // ����  : byte[] ip [IN]: ��ҵ��ͨѶƽ̨��IP��ַ
   // ����  : int port [IN]: ��ҵ��ͨѶƽ̨�ṩ�Ķ˿ں�port
   // ����  : int[] funlist [IN]: ��ҵ��ͨѶƽ̨��ע��Ĺ��ܺ��б��������е�һ������Ϊ˽�й��ܺ�
   // ����  : int funcount [IN]: ��ҵ��ͨѶƽ̨��ע��Ĺ��ܺŸ�����������>0
   // ����  : boolean bretry [IN]: �Ƿ񵱶Ͽ����Ӻ󣬼���retry���ӡ�
   //                           1(true), �򵱽��մ������ӶϿ���ʱ�򣬻����²�ͣ���ӣ��ָ����գ���ReceiveMsg������-2��Ϣ
   //                           0(false)�������ӶϿ�ʱ����ص�ReceiveMsg�����л���յ�-2����Ϣ���˳�����
   public native int AddService(int branchno,byte[] ip,int port,int[] funlist, int funcount, boolean bretry);

   // ������: RemoveService
   // ���  : ������ 2006-8-25 16:38:58
   // ����  : �жϷ�������
   // ����  : boolean : ���������ӱ�Ŵ��󣬼�svrID<0 �� svrID>=10 ����Ϊfalse
   // ����  : int svrID [IN]: ��AddService�������ص�ͨѶƽ̨�������ӱ��
   public native boolean RemoveService(int svrID);

   // ������: BindService
   // ���  : ������ 2006-6-15 11:24:25
   // ����  : ��XPack���ݴ�������ͨѶ����ID
   // ����  : int ����ҵ��ͨѶƽ̨����ID�ţ�<0: ʧ��
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int svrID [IN]: ͨѶ����ID����AddService(...)���ص�ID
	public native int BindService(long Handle,int svrID);

   // ������: ReceiveMsg
   // ���  : ������ 2006-6-31 21:42:08
   // ����  : ��Ϊ�����Ա����õ�ͨѶ���ܺţ�ɨ�������Ϣ����������
   // ����  : int    1��0��֪ͨ��Ϣ��2��1��֪ͨ��Ϣ��3�������ͻ����������ݣ���Ҫ��PutRow/DataDone����Ӧ��
   //                0: һ���������ݷ��ش�����ɣ�ͬ-1һ����������
   //                -1: ��ʾ����ɨ�����Bind��Service��û���յ��µ���Ϣ������ע����������²�Ҫ��ɨ�裬���߳��м�������ȴ���
   //                -2: ��ʾ�󶨵�svrID���ӳ��������ˣ�errormessage�н������������Ϣ 
   //                <-2: ���ڴ��󣬲ο�errormessage��Ϣ -3: �������
   // ����  : long Handle [IN] : �ȴ����յ�XPACK���ݻ�����
   // ����  : byte[] errormessage [OUT] : ��������Ϊ<0��ʱ��Ĵ�����Ϣ
	public native int ReceiveMsg(long Handle, byte[] errormessage, int emlen);


   // ������: PutRow
   // ���  : ������ 2006-6-31 21:46:30
   // ����  : ����ǰ�����е��Ѿ����õ�����(Row=0��)��Ϊһ����¼��׼����ϣ������ύ���Է�
   //          ע�⣺��XPACK��CPACKЭ���У��ü�¼���ἴʱ���͸��Է������ǳ�Ϊһ�������İ�
   //             �����ڼ�ѹ��ȥ��ģʽ����ÿ�ζ�Ҫ��PutRow��ʾһ����¼׼����ϣ����
   //             ͨ������DataDone����ʾ���������������û�и��������Ҫ�����󷽡�
   // ����  : int : ���سɹ�>=0 ��ʧ��<0
   // ����  : long Handle [IN] : ��������XPACK���ݻ�����
   // ����  : int retCode [IN] : ��ǰ�ķ����룬һ����XPACKЭ����0��ʾ�ɹ�
	public native int PutRow(long Handle, int retCode);


   // ������: DataDone
   // ���  : ������ 2006-6-22 11:53:00
   // ����  : ���ζ��������ݴ����������������Ϣ���ظ�����
   // ����  : int : ���سɹ�>=0 ��ʧ��<0
   // ����  : long Handle [IN] : ��������XPACK���ݻ�����
   // ����  : int retCode [IN] : ��ǰ�ķ����룬һ����XPACKЭ����0��ʾ�ɹ�
   public native int DataDone(long Handle, int retCode);


   // ����  : �����ǰͨ��SetXXXXFieldByName��SetRawData�����ݣ�����ķ��ؼ�¼�����ݵ��ֶ���
   //          ���ʱ��ͻὫǰ���PutRow����ύ�����󷽵ġ�
   // ����  : int >=0: �ɹ���<0: ʧ�� 
   // ����  : long Handle [IN] : ��������XPACK���ݻ�����
   public native int ClearRow(long Handle);

   ////////////////////////////////////////////////////////////////////////////////////
   /// �������ڵ��Կ�����ʱ�򣬽����н�����������Ϣ��¼��KLG��־�ļ���
   /// �ڿ����׶ο���ͨ��OpenKLGFile����Ὣ�����뱾�ӿ���ص���Ҫ����Ϣ��¼��KLG��־��
   //////////////////////////////////////////////////////////////////////////
   // ������: KLGOpen
   // ���  : ������ 2006-6-2 15:42:08
   // ����  : ͨ�����ñ���������KLG��־�ļ������ڵ��Ը���ʹ�ã�
   //       ע�⣺��release�汾�У����鲻Ҫ����������ᵼ����Ϊ��¼KLG��־������Ч�ʽ���
   // ����  : boolean  
   // ����  : byte[] klgpath [IN]: KLG��־�ļ����·��, ���Ȳ�Ҫ1K
   public native boolean KLGOpen(byte[] klgpath);

   // ������KLGOpen�󣬿��Ե��ñ������������ԣ���Ϣ��¼��KLG�ļ��У�������غ���ֻ�ڽӿ��ڲ�ʹ��
   // message�ĳ���<1000
   public native boolean KLGMsg(byte[] message);

   // ɾ�������ļ�
   // path_mark��ɾ�����ļ�·�����������ļ��������������Ӧ��·���ָ����WINDOWS�µ�'\\'��UNIX�µ�'/'
   // ext��ɾ�����ļ���չ�����������'.'
   public native int RemoveOverdueFile(byte[] path_mark, byte[] ext, int overdue);

	static 
	{
		System.loadLibrary("bccsvr");
	}
}
