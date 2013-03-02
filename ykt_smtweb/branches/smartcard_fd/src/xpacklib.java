

public class xpacklib
{

   // ������: NewXpackHandle
   // ���  : ������ 2005-11-14 17:57:39
   // ����  : ����һ������XPack���ݽ�����������
   // ����  : long : ���ظ�XPack�������ľ����==0(NULL): ʧ��
   // ����  : byte[] XpackDescribleFile [IN]: XPack�ṹ�����ļ��������ܳ���1024�ֽڳ�����: "/xpacks/cpack.dat"
	public native long NewXpackHandle(byte[] XpackDescribleFile);

   // ������: ResetPackHandle
   // ���  : ������ 2005-11-14 18:01:30
   // ����  : �������������ݣ���Ҫ����׼���װ�����ʱ����д�������������ֶ�֮ǰ����
   // ����  : boolean : false - ����Ϊ�����Handle(==NULL��ʱ��)
   // ����  : long Handle [IN]: ָ����XPack���������
	public native boolean ResetPackHandle(long Handle);

   // ������: CopyHandle
   // ���  : ������ 2005-11-14 18:04:56
   // ����  : ��SourceHandle�е�״̬����ʽ�����ݵ���Ϣ���Ƶ�DestHandle��
   // ����  : boolean : false - ����Ϊ�����Handle(==NULL��ʱ��)
   // ����  : long SourceHandle [IN]: �����Ƶ�ԭXPack���������
   // ����  : long DestHandle   [OUT]: �����Ƶ�Ŀ��XPack������������ڲ����ݱ����ǣ�������������һ�����
	public native boolean CopyHandle(long SourceHandle,long DestHandle);

   // ������: DeleteXpackHandle
   // ���  : ������ 2005-11-14 18:08:08
   // ����  : ���Ѿ���NewXpackHandle�õ����������ͷ�(ж��)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
	public native boolean DeleteXpackHandle(long Handle);

   // ������: GetFieldTypeByCol
   // ���  : ������ 2005-11-14 18:08:31
   // ����  : ȡ�ö�Ӧ�ֶ������ŵ�����(��NewXpackHandle������Ľṹ�����ļ����)
   // ����  : int  : 0 - ���ֶ�; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
   //                -1 �ֶ����������ڻ�Handle����
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Col [IN]: �ֶ�������
	public native int GetFieldTypeByCol(long Handle,int Col);

   // ������: GetFieldTypeByName
   // ���  : ������ 2005-11-14 18:08:37
   // ����  : ȡ�ö�Ӧ�ֶε�����(��NewXpackHandle������Ľṹ�����ļ����)
   // ����  : int  : 0 - ���ֶ�; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
   //                -1 �ֶ����������ڻ�Handle����
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] FieldName [IN]: ָ�����ֶ�����,��"vsmess"
	public native int GetFieldTypeByName(long Handle,byte[] FieldName);


   // ������: GetIntFieldByCol
   // ���  : ������ 2005-11-14 18:08:45
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (int)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : int Col [IN]: �ֶ�������
   // ����  : int[] Value [OUT]: ���صõ���ֵ
	public native boolean GetIntFieldByCol(long Handle,int Row,int Col,int[] Value);

   // ������: GetDoubleFieldByCol
   // ���  : ������ 2005-11-14 18:09:14
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : int Col [IN]: �ֶ�������
   // ����  : double[] Value [OUT]: ���صõ���ֵ
	public native boolean GetDoubleFieldByCol(long Handle,int Row,int Col,double[] Value);

   // ������: GetStringFieldByCol
   // ���  : ������ 2005-11-14 18:09:20
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (C�б�ʾ�ĵ��ֽ��ַ���)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : int Col [IN]: �ֶ�������
   // ����  : byte[] Value [OUT]: ���صõ���ֵ
   // ����  : int ValueBufferSize [IN]: Value�������ĳ��ȣ������Դ�ŵ���󳤶ȣ� һ�����Ϊ <=256
	public native boolean GetStringFieldByCol(long Handle,int Row,int Col,byte[] Value,int ValueBufferSize);
	

   // ������: GetIntFieldByName
   // ���  : ������ 2005-11-14 18:09:26
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (int)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : int[] Value [OUT]: ���صõ���ֵ
	public native boolean GetIntFieldByName(long Handle,int Row,byte[] FieldName,int[] Value);

   // ������: GetDoubleFieldByName
   // ���  : ������ 2005-11-14 18:09:31
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : double[] Value [OUT]: ���صõ���ֵ
	public native boolean GetDoubleFieldByName(long Handle,int Row,byte[] FieldName,double[] Value);

   // ������: GetStringFieldByName
   // ���  : ������ 2005-11-14 18:09:36
   // ����  : ����������ȡ��Row����¼�еĶ�Ӧ�ֶε�ֵ (double)
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : byte[] Value [OUT]: ���صõ���ֵ
   // ����  : int ValueBufferSize [IN]: Value�������ĳ��ȣ������Դ�ŵ���󳤶ȣ� һ�����Ϊ <=256
	public native boolean GetStringFieldByName(long Handle,int Row,byte[] FieldName,byte[] Value,int ValueBufferSize);
	

   // ������: SetIntFieldByCol
   // ���  : ������ 2005-11-14 18:09:41
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : int Col [IN]: �ֶ�������
   // ����  : int Value [IN]: ����ֵ
	public native boolean SetIntFieldByCol(long Handle,int Row,int Col,int Value);

   // ������: SetDoubleFieldByCol
   // ���  : ������ 2005-11-14 18:09:47
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : int Col [IN]: �ֶ�������
   // ����  : double Value [IN]: ����ֵ
	public native boolean SetDoubleFieldByCol(long Handle,int Row,int Col,double Value);

   // ������: SetStringFieldByCol
   // ���  : ������ 2005-11-14 18:09:52
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : int Col [IN]: �ֶ�������
   // ����  : byte[] Value [IN]: ����ֵ�������Գ���255����
	public native boolean SetStringFieldByCol(long Handle,int Row,int Col,byte[] Value);
	

   // ������: SetIntFieldByName
   // ���  : ������ 2005-11-14 18:09:57
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : int Value [IN]: ����ֵ
	public native boolean SetIntFieldByName(long Handle,int Row,byte[] FieldName,int Value);

   // ������: SetDoubleFieldByName
   // ���  : ������ 2005-11-14 18:10:02
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : double Value [IN]: ����ֵ
	public native boolean SetDoubleFieldByName(long Handle,int Row,byte[] FieldName,double Value);

   // ������: SetStringFieldByName
   // ���  : ������ 2005-11-14 18:10:07
   // ����  : ����ָ���������е�Row����¼�еĶ�Ӧ�ֶε�ֵ
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ������ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
   // ����  : byte[] Value [IN]: ����ֵ�������Գ���255����
	public native boolean SetStringFieldByName(long Handle,int Row,byte[] FieldName,byte[] Value);
	

   // ������: SetRequestType
   // ���  : ������ 2005-11-14 18:10:12
   // ����  : �������������еĹ��ܺ� ����EncodeXpackForRequest֮ǰһ��Ҫ���ã�
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int RequestType [IN]: ��Ӧ��ҵ���ܺ�
	public native boolean SetRequestType(long Handle,int RequestType);
	

   // ������: IsEof
   // ���  : ������ 2005-11-14 18:10:17
   // ����  : �Ƿ��Ѿ������һ��Ӧ����ˣ���HaveNextPack�����෴
   // ����  : boolean : true - ��ʾ�Ѿ�û�к���Ӧ�����ݰ��ˣ�false - Ҫͨ������EncodeXpackForNext������
   // ����  : long Handle [IN]: ָ����XPack���������
	public native boolean IsEof(long Handle);
	

   // ������: GetRecordCount
   // ���  : ������ 2005-11-14 18:10:22
   // ����  : ������ȡ�����еļ�¼��RecordCount
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int[] RecordCount [OUT]: ���ؽ����ļ�¼��
	public native boolean GetRecordCount(long Handle,int[] RecordCount);

   // ������: GetRetCode
   // ���  : ������ 2005-11-14 18:10:28
   // ����  : ������ȡ�䷵����
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int[] RetCode [OUT]: �����յ����ݰ��еķ�����
	public native boolean GetRetCode(long Handle,int[] RetCode);


   // ������: EnCodeXpackForRequest
   // ���  : ������ 2005-11-14 21:10:33
   // ����  : ��XPack���ݿ���б��롣���Ѿ������˵�XPack���ݴ����ָ�������ݿ�(PackBuffer)��
   //       Notice: ��Ŀǰ��Ӧ�÷�����ϵͳ�У�ͨ�����������¼�е����ݺ󣬵��ñ������������ݴ��Ϊ�������
   //                Ȼ����ڽ����������������ҵ��ͨѶƽ̨���͵�Ӧ�÷�������Զˡ�
   // ����  : boolean : ����ɹ����
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] PackBuffer [OUT]: ����ɹ����ŵĴ������ 
   // ����  : int PackBufferSize [IN]: PackBuffer�Ļ������ֽڳ��ȣ��ɴ������󳤶ȣ�
   // ����  : int[] PackDataLength [OUT]: ���ش�������ݳ��ȣ��ֽ�����
	public native boolean EnCodeXpackForRequest(long Handle,byte[] PackBuffer,int PackBufferSize,int[] PackDataLength);

   // ������: EnCodeXpackForNext
   // ���  : ������ 2005-11-14 21:10:39
   // ����  : �����ϴν������ݣ���ö�ȡ�������ݰ��������
   //       Notice: ����HaveNextPack()ȷ�����к���Ӧ�����ݰ���ʱ���ñ������õ���ȡ�������ݵ��������
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] PackBuffer [OUT]: ����ɹ����ŵĴ������ 
   // ����  : int PackBufferSize [IN]: PackBuffer�Ļ������ֽڳ��ȣ��ɴ������󳤶ȣ�
   // ����  : int[] PackDataLength [OUT]: ���ش�������ݳ��ȣ��ֽ�����
	public native boolean EnCodeXpackForNext(long Handle,byte[] PackBuffer,int PackBufferSize,int[] PackDataLength);

   // ������: DeCodeXpack
   // ���  : ������ 2005-11-14 21:10:44
   // ����  : ��ָ���ı������ݿ���н��롣
   //         Notice: ���յ��Է����ش�����ݺ��ñ����������ݽ��Ϊ��������
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] PackData [IN]: ��������ݣ��Դ˽��н���
   // ����  : int PackDataLength [IN]: �������ݳ���
	public native boolean DeCodeXpack(long Handle,byte[] PackData,int PackDataLength);

   // ������: GetPrivateFunctionForNext
   // ���  : ������ 2005-11-14 21:10:48
   // ����  : �����յý��������ݣ����еõ����ڿ��Ի�ȡ����Ӧ�����ݰ���Ӧ�÷�����ר��ͨѶ���ܺ�
   //          ��ϸ������ο�KSBCCʹ��˵����
   // ����  : int : >0 - �ɻ�ȡ�������ݵ�ר��ͨѶ���ܺţ�����ʧ��
   // ����  : long Handle [IN]: ָ����XPack���������
	public native int GetPrivateFunctionForNext(long Handle);

   // ������: GetBranchNoForNext
   // ���  : ������ 2005-11-14 21:10:52
   // ����  : �����յý��������ݣ����еõ����ڿ��Ի�ȡ����Ӧ�����ݰ���Ŀ��ͨѶƽ̨�ڵ���
   //          ��ϸ������ο�KSMBCCʹ��˵����
   // ����  : int >0: ��ȡ����Ӧ�����ݰ���Ŀ��ͨѶƽ̨�ڵ���; ��������ԭ���Ľڵ���
   //                ���ù�������Transferʵ�ֵ�ʱ����Ҫ������ܱ�����˵Ľڵ��
   // ����  : long Handle [IN]: ָ����XPack���������
	public native int GetBranchNoForNext(long Handle);

   // ������: SetRecordCount
   // ���  : ������ 2005-11-14 21:10:56
   // ����  : Ԥ�������������еļ�¼��
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int RecordCount [IN]: ���õļ�¼��
	public native boolean SetRecordCount(long Handle,int RecordCount);

   // ������: SetMaxRetCount
   // ���  : ������ 2005-11-14 21:11:00
   // ����  : ����Ӧ���ÿ�η��ص�����¼��
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int MaxRetCount [IN]: ָ��������¼����0����Ӧ�÷������� [0..100]; 
	public native boolean SetMaxRetCount(long Handle,int MaxRetCount);

   // ������: GetXPackType
   // ���  : ������ 2005-11-14 21:11:05
   // ����  : ��ѯ��ǰ���ݿ������ݼ�¼����
   // ����  : int �������ݼ�¼���� 0-��׼ST_PACK��¼��1-ST_SDPACK��RawData��¼
   // ����  : long Handle [IN]: ָ����XPack���������
	public native int GetXPackType(long Handle); 

   // ������: SetRawRecord
   // ���  : ������ 2005-11-14 21:11:11
   // ����  : ����ָ����¼Ϊָ����RawData��¼
   // ����  : boolean 
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ָ�����õļ�¼�� [0..RecordCount-1]
   // ����  : byte[] RawData [IN]: Ҫ�������ݿ�
   // ����  : int RawDataLength [IN]: Ҫ�������ݿ鳤��
	public native boolean SetRawRecord(long Handle, int Row, byte[] RawData, int RawDataLength);

   // ������: GetRawRecord
   // ���  : ������ 2005-11-14 21:11:15
   // ����  : ����GetXPackType����Ϊ1��ST_SDPACK��ļ�¼��������ñ�������ȡ������Ч��¼�е�RawData��¼
   // ����  : int : >=0 - �ɹ�����RawData�����ݳ���(�ֽ���)
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Row [IN]: ָ���ļ�¼�� [0..RecordCount-1]
   // ����  : byte[] RawData [OUT]: ��Ŷ�ȡ��RawData���ݿ� 
   // ����  : int RawDataSize [IN]: RawData���ݿ�Ŀɴ�ŵ������
	public native int GetRawRecord(long Handle, int Row, byte[] RawData, int RawDataSize);

   // ������: GetMaxColumn
   // ���  : ������ 2005-11-14 21:11:20
   // ����  : ��ȡ����ʽ��XPack��������Ч�ֶ�����ֵ���뵱ʱ���ݿ鲻ͬ
   // ����  : int ����ST_PACK�е������Ч�ֶ�����ֵ
   // ����  : long Handle [IN]: ָ����XPack���������
	public native int GetMaxColumn(long Handle);

   // ������: IsValidColumn
   // ���  : ������ 2005-11-14 21:11:24
   // ����  : ��ϵ�ǰ���ݣ�ȷ��ָ���ֶ��������Ƿ�Ϊ��Ч�ֶ�
   // ����  : boolean : true-Ϊ��Ч�ֶ�
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : int Col [IN]: ָ�����ֶ�������
	public native boolean IsValidColumn(long Handle, int Col);

   // ������: GetFieldColumn
   // ���  : ������ 2005-11-14 21:11:29
   // ����  : �����ֶ����ƣ�����ֶ�������
   // ����  : int >=0 Ϊ��XPACK����Ч�ֶΣ����ص�ֵ��Ϊ�����ţ�<0Ϊ��XPACK��û������ֶ�
   // ����  : long Handle [IN]: ָ����XPack���������
   // ����  : byte[] FieldName [IN]: �ֶ����� ��"vsmess"
	public native int GetFieldColumn(long Handle, byte[] FieldName);

   // ������: HaveNextPack
   // ���  : ������ 2005-11-14 22:01:15
   // ����  : �������ͨ���������ж��Ƿ��к���Ӧ���
   // ����  : boolean : true-��ʾ���к���Ӧ�����false���޺�����
   // ����  : long Handle [IN]: ָ����XPack���������
	public native boolean HaveNextPack(long Handle);

	static 
	{
		System.loadLibrary("xpacklib");
	}
}
