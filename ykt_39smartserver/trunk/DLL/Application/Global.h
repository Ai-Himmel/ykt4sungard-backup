#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/***************************�ն��豸��̬��----����˵��****************************************************/
//Common.cpp
int _stdcall calc_crc16(unsigned char len,unsigned char *in,unsigned char *out);
//public.cpp
int _stdcall MakeBuf_SetID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *id);//�����ն��豸ID��
int _stdcall MakeBuf_GetID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//��ȡ�ն��豸ID��
int _stdcall MakeBuf_SearchID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *id);//ͨ��ID�����λ��ѯ�ն��豸ID��
int _stdcall MakeBuf_SetAddr(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *id);//ͨ���ն��豸ID�Ÿ��ն��豸���û���
int _stdcall MakeBuf_GetType(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//���ն��豸������������
int _stdcall MakeBuf_GetVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//���ն��豸����汾��
int _stdcall MakeBuf_ChangeBuadRate(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int nBaudRate);///  ����ͨ�Ų�����///    nBaudRate ������ֵ  19200  9600 4800 2400  1200 28800	57600	115200  38400
//clock.cpp
int _stdcall MakeBuf_SetClock(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *clock);/// ���ܣ�����ʱ��/// ���룺������ʱ��������
int _stdcall MakeBuf_GetClock(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//���ܣ���ȡʱ��  ע�⣺��ָ���ʱ��������
//flow.cpp
int _stdcall GetSmartProtocolRule(TSSmartProtocol *pSmartPT);/// ���ܣ�Э������庯��
int _stdcall UnMakeDeviceBuffer(TSCmdBuffer *pBuffer);//ͨ�ú���: �豸��̬�����յ������շ���ȷ������SMART411Э�� 
int _stdcall MakeBuf_SetTerminalToFactorySetting(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//�ָ��ն��豸Ϊ����״̬
int _stdcall MakeBuf_RecountAllStateData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//�������ݳ�ʼ��  �������: ������н��ʼ�¼�����������½��ʡ�
int _stdcall MakeBuf_ClearData(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ�������н�������
int _stdcall MakeBuf_CollectData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//�����ռ�������
int _stdcall MakeBuf_ConfirmData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *FlowNo);/// ���ܣ�����ȷ��
int _stdcall MakeBuf_CollectDataBySerialNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *SerialNo);//����:����ˮ�ϴ��ն˽��׼�¼
int _stdcall MakeBuf_CollectStateData(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ����:�ϴ����ʼ�¼
int _stdcall MakeBuf_ConfirmStateData(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *FlowNo);/// ����:ȷ�����ʼ�¼
int _stdcall MakeBuf_CollectStateDataBySerial(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *SerialNo);/// ����:����ˮ�ϴ����ʼ�¼
//List.cpp
int _stdcall MakeBuf_GetBlackUsefulLife(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ���ȡ��������Ч��
int _stdcall MakeBuf_SetBlackUsefulLife(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *date);/// ���ܣ��´���������Ч��
int _stdcall MakeBuf_GetBlackVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ��ϴ��������汾
int _stdcall MakeBuf_SetBlackVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *date);/// ���ܣ��´��������汾
int _stdcall MakeBuf_BoardBlackNo(unsigned char *Buffer, unsigned char *Version, unsigned char *CardNo);/// ���ܣ��㲥������pBuffer:������ CardNo: ����     3�ֽ�
int _stdcall MakeBuf_CheckBlackCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo);/// ���ܣ���������
int _stdcall MakeBuf_DownBlackCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo);/// ���ܣ��´�������( ע�⣺һ��ֻ���´�һ��������)
int _stdcall MakeBuf_DelOneBlackCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo);/// ���ܣ�ɾ��������(ע�⣺һ��ֻ��ɾ��һ��������)/// ������ *CardNo 3�ӽڿ���
int _stdcall MakeBuf_DelAllBlackCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ�ɾ�����к�����
int _stdcall MakeBuf_GetBlackAllCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ��ϴ�����������
int _stdcall MakeBuf_RecountAllBlackCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ�����ͳ�ƺ�����������
int _stdcall MakeBuf_DownWhiteCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int flag, unsigned char *CardNo);/// ���ܣ��´�������(ע�⣺һ��ֻ���´�һ��)/// ������ CardNo----3�ֽ�
int _stdcall MakeBuf_DelWhiteCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *CardNo);/// ���ܣ�ɾ��������(ע�⣺һ��ֻ��ɾ��һ��)/// ������CardNo---3�ֽ�
int _stdcall MakeBuf_DelAllWhiteCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ�ɾ�����а�����
int _stdcall MakeBuf_SetWhiteVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *date);/// ���ܣ��´��������汾/// ������*date ---- ���ӽں������汾
int _stdcall MakeBuf_GetWhiteVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ��ϴ��������汾
int _stdcall MakeBuf_CheckWhiteCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo);/// ���ܣ���������/// ������*CardNo	3�ֽڿ���
int _stdcall MakeBuf_BoardWhiteNo(unsigned char *Buffer, unsigned char *Version, unsigned char *CardNo);/// ���ܣ��㲥������/// ������///      pBuffer:������///      Version:�汾��Ϣ 6�ֽ�BCD��///      CardNo: ����     3�ֽ�/// ���أ�///      ͨ�Ű������峤��
int _stdcall MakeBuf_SetAssistVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Buffer);/// ���ܣ����������汾�´�/// ������///   Buffer: ///     �汾ʱ��:  6�ֽ�///     ������:    2�ֽ�///     �ܽ��:    4�ֽ�(��λ��ǰ)///     ��Ǯ������:2�ֽ�///     ��Ǯ�ܽ��:4�ֽ�(��λ��ǰ)///     ��Ǯ������:2�ֽ�///     ��Ǯ���:  4�ֽ�(��λ��ǰ)
int _stdcall MakeBuf_GetAssistVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ����������汾�ϴ�
int _stdcall MakeBuf_SetAssisList(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Buffer);/// ���ܣ��´���������/// ������*List///       3�ֽڽ��׿���///       2�ֽ�����///       2�ֽڽ��(��λ��ǰ)///       1�ֽڼӼ�Ǯ���(0---�ӣ�1---��)
int _stdcall MakeBuf_GetAssisList(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ��ϴ���������

int _stdcall MakeBuf_ClearAllAssisList(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ������������
int _stdcall MakeBuf_SetAssistState(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char switchflag);/// ���ܣ����ò������ܿ���/// ������/// switchflag ---00��///            ---FF��
int _stdcall MakeBuf_GetAssistState(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ���ȡ�������ܿ���
//Lport.cpp
int _stdcall MakeBuf_SetPortRegNoAndMacNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo,unsigned char *newRegNo,int MacNo);/// ���ܣ����÷�����ĳ�˿�ע��ż�����/// PortNo    ----- 1BYTE   ��Ӧ�˿ں�/// newRegNo  ----- 4BYTE   ��Ӧע���/// MacNo     ----- 1BYTE   ��Ӧ����/// ���������Lport�ö˿��������ݽ����
int _stdcall MakeBuf_ClearPortData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo);/// ���ܣ��˿����ݳ�ʼ��
int _stdcall MakeBuf_SetPortToFactorySetting(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo);/// ���ܣ��˿ڲ�����ʼ��(���˿�������Ϣ�ָ�Ϊ����״̬)/// ������///    PortNo ------ �˿ں�
int _stdcall MakeBuf_GetPortPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo);/// ���ܣ���������ĳ�˿ڲ���/// ������///    PortNo ------ �˿ں�
int _stdcall MakeBuf_SearchPort(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo);/// ����:�����˿�
int _stdcall MakeBuf_GetLportMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ����:��ȡLport������
int _stdcall MakeBuf_SetLportNewRegNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *newRegNo);/// ���ܣ�����ע���/// ������/// newRegNo ------ ��ע���
int _stdcall MakeBuf_SetLportToFactorySetting(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ���ʼ��������
int _stdcall MakeBuf_DebugGetLportMainPar(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ������ϴ�������������
int _stdcall MakeBuf_RemoteReset(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ�Զ�̸�λ

//Parameter.cpp
int _stdcall MakeBuf_SetMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *mainpar);/// ���ܣ�����������/// ���룺*mainpar 28�ֽ�
int _stdcall MakeBuf_GetMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ���ȡ������
int _stdcall MakeBuf_Debug_GetMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ����Ի�ȡ������(����ע���)
int _stdcall MakeBuf_SetRegNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *regno);/// ����:����ע���/// ����:*regno---4�ֽ�ע���
int _stdcall MakeBuf_SetSFJ_TimePhase(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int No,int Time,unsigned char *Buffer);/// ���ܣ�����ʱ���/// ������///    No   ---- ʱ���������///    Time ---  ���մ���///    Buffer--- no*10 ʱ��β���
int _stdcall MakeBuf_GetSFJ_TimePhase(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ���ȡʱ��β���
int _stdcall MakeBuf_SetSFJFastNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char No, unsigned char *Buffer);/// ���ܣ��´���ݱ��///   No:�������(1�ֽ�)///   Buffer:3*No�������
int _stdcall MakeBuf_GetSFJFastNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ��ϴ���ݱ��
int _stdcall MakeBuf_SetSFJConsumeNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char Flag, unsigned char No,unsigned char *Buffer);/// ����:�´����ѱ��/// ����:///    Flag:ȫ��/����ӱ��(1�ֽ�)///    No:  �����(1�ֽ�)///    Buffer:N*3�ֽڱ��
int _stdcall MakeBuf_DelSFJConsumeNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char No,unsigned char *Buffer);// ���ܣ�ɾ�����ѱ��/// ����:///   No:�������///   Buffer:N*3�ֽڱ��
int _stdcall MakeBuf_GetSFJConsumeVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ��ϴ����ѱ�Ű汾
int _stdcall MakeBuf_SetSFJComsumeVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Buffer);// ����:�´����ѱ�Ű汾	/// ������///  Buffer:���ѱ�Ű汾(6�ֽ�)
int _stdcall MakeBuf_SetDirSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int Sector);/// ���ܣ����ÿ�ƬĿ¼������/// ������Sector---��ƬĿ¼������
int _stdcall MakeBuf_GetDirSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ����ÿ�ƬĿ¼������
int _stdcall MakeBuf_SetV10PacketSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int Sector);/// ���ܣ�����V10��ƬǮ�����ڵ����� /// ������Sector --- ������
int _stdcall MakeBuf_GetV10PacketSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ���ȡV10��ƬǮ�����ڵ�����
int _stdcall MakeBuf_SetV10Password(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Password);/// ����:�´�V10����λ����/// ������Password(2�ֽ�,��λ��ǰ)
int _stdcall MakeBuf_GetStateTimeTable(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ����:�ϴ���ʱ����ʱ���
int _stdcall MakeBuf_SetStateTimeTable(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int No,unsigned char *Buffer);/// ���ܣ��´���ʱ����ʱ���/// ������///    No:��ʱ����������///    Buffer:��ʱ����ʱ����� ʱ��Ϊ1��
int _stdcall MakeBuf_State(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ���λ��Ҫ������
int _stdcall MakeBuf_ReState(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *SerialNo);/// ���ܣ���λ��Ҫ�󸴺�����/// ������///      SerialNo��Ҫ�󸴺�������ˮ��
int _stdcall MakeBuf_SetComsumeFlag(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char Flag);/// ���ܣ��������ѹ��ܿ�����ر�/// ������///    Flag --- 1 ����///    Flag --- 0 �ر�
int _stdcall MakeBuf_SetWorkingKey(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Plain,unsigned char KeyNo);/// ���ܣ����ù�����Կ���㷨���/// ������///     *Plain ------ ��Կ���� 9�ֽ�///     KeyNo  ------ �㷨���
int _stdcall MakeBuf_GetLargeConsumeMoney(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ���ȡ��������޶�
int _stdcall MakeBuf_SetLargeConsumeMoney(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Money);/// ���ܣ�������������޶�/// ������///     Money:3�ֽڽ���λ��ǰ
int _stdcall MakeBuf_SetManagePassword(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Password);/// ���ܣ�����ϵͳ����Ա����/// ������///     Password:����(3�ֽ� BCD��)
//Sensor.cpp
int _stdcall MakeBuf_SearchSensor(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ�������Ӧͷ
int _stdcall MakeBuf_GetSensorInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ��ϴ���Ӧͷ��Ϣ
int _stdcall MakeBuf_SetSensorAddress(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int No,unsigned char *Buffer);/// ���ܣ����ø�Ӧͷ����/// ������///     No----��Ӧͷ����///     Buffer----n*5�ֽ� 
int _stdcall MakeBuf_SetFireState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ�����Ϊ����״̬
int _stdcall MakeBuf_SetTheftState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ�����Ϊ����״̬
int _stdcall MakeBuf_SetNormalState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// ���ܣ��ָ�Ϊ����״̬
int _stdcall MakeBuf_SetMode3Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int No,unsigned char *Buffer);/// ���ܣ�����ģʽ���ڼ�����Ϣ/// ������///    No:�ڼ���������///    Buffer:�ڼ�����Ϣ
int _stdcall MakeBuf_SetMode3TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int WeekInfo,int No,unsigned char *Buffer);/// ���ܣ�����ģʽ��ʱ�����Ϣ/// ����:///    WeekInfo:������Ϣ 1Byte///    No:ʱ�����       1Byte///    Buffer:ʱ�����Ϣ No*8 Byte
int _stdcall MakeBuf_GetMode3Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// ���ܣ���ȡģʽ���ڼ�����Ϣ
int _stdcall MakeBuf_GetMode3TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int WeekInfo);/// ���ܣ���ȡģʽ��ʱ�����Ϣ/// ����: ///   WeekInfo:������Ϣ
int _stdcall MakeBuf_SetLoginPublic1Password(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *Password);/// ���ܣ��´���½������Ϣ1����Ҫ������/// ������///     Password
int _stdcall MakeBuf_ConfirmLost(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *Password);

void _stdcall GenerateWorkingKey(unsigned char *str1, unsigned char *str2);
void _stdcall Smart_CardDes(unsigned char *str1, 
						   unsigned char *str2,
						   unsigned char *str3,
						   unsigned char *str4,
						   unsigned char cFlag);

//����������ṩ��API��
extern 	lpfnGetDBHandle	            GetDBHandle;
extern 	lpfnFreeDBHandle            FreeDBHandle;
extern 	lpfnExecuteQuery			ExecuteQuery;
extern 	lpfnCloseRecHandle			CloseRecHandle;
extern 	lpfnIsOpen					IsOpen;
extern 	lpfnIsBOF					IsBOF;
extern 	lpfnIsEOF					IsEOF;
extern 	lpfnMoveFirst				MoveFirst;
extern 	lpfnMoveLast				MoveLast;
extern 	lpfnMoveNext				MoveNext;
extern 	lpfnMovePrev				MovePrev;
extern 	lpfnGetFieldCount			GetFieldCount;
extern 	lpfnGetRecordCount			GetRecordCount;
extern 	lpfnGetFieldName			GetFieldName;
extern 	lpfnGetFieldStringValue		GetFieldStringValue;
extern 	lpfnGetFieldStringValueEx	GetFieldStringValueEx;
extern 	lpfnGetFieldLongValue		GetFieldLongValue;
extern 	lpfnGetFieldLongValueEx		GetFieldLongValueEx;
extern 	lpfnGetFieldFloatValue		GetFieldFloatValue;
extern 	lpfnGetFieldFloatValueEx	GetFieldFloatValueEx;
extern 	lpfnGetFieldDoubleValue		GetFieldDoubleValue;
extern 	lpfnGetFieldDoubleValueEx	GetFieldDoubleValueEx;
extern 	lpfnLocate					Locate;
extern 	lpfnExecuteSQL				ExecuteSQL;
extern  lpfnSendRequest             SendRequest;
extern  lpfnBroadData               BroadData;
extern  lpfnAddNewSmartDoc          AddNewSmartDoc;
extern  lpfnDelSmartDoc             DelSmartDoc;
extern  lpfnBroadMessage            BroadMessage;
extern  lpfnBroadcastPro			BroadcastPro;
extern  lpfnSendData				SendDataEx;
extern  lpfnRecvData				RecvDataEx;
extern	lpfnOutputRealData			OutputRealData;
extern	lpfnGetParam				GetParameter;
extern	lpfnReportTaskResult		ReportTaskResult;
extern  lpfnReadCardGSInfo			ReadCardGSInfo;
extern  lpfnDownloadBlackCard		DownloadBlackCard;
extern  lpfnOutputBlackCard			OutputBlackCard;
extern  lpfnSignIn                  SignIn;
extern  lpfnSignOut                 SignOut;

extern void SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count);
extern void SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count);
extern int m_calc_crc16(unsigned char len,unsigned char *in,unsigned char *out);
extern void m_crcupdata(unsigned char in,unsigned short *accum,unsigned int *crctab);
extern void SmartEncrypt(unsigned char E_number,unsigned char *ID,unsigned char *Plain);

//������־
extern void WriteLog(const char *format, ...);
extern void GetCurDateTime(char *pszDateTime);
extern void DebugPrint(const char *format, ...);
extern void GetCurDateTime(char *pszDateTime);

extern void GetValue(CString strValue, char *pResult);
extern void GetValue(CString strValue, long& nResult);
extern void GetValue(CString strValue, int& Result);
extern void Trim(char *pszString);
extern void GetNumberRange(char *pszBuffer, int& iBegin, int& iEnd);

extern void ReportLog(TSSmartDoc *pDoc, TSSmartTask *pTask, long nRet, char *pszTask, char *pszString);
extern void ReportLog(TSSmartDocEx *pDocEx, TSSmartTask *pTask, long nRet, char *pszTask, char *pszString);
extern void GetResultMessage(long nRet, char *pszString);
extern void ReportLog(long nRet, char *pszTask, char *pszString);

extern BOOL QueryRepeatRecord(long nInvoice, CString strDateTime, CString strTableName);
extern CString GetAdjustCode(char *strCode, long nInvoice, CString strDateTime, CString strTableName);

extern DWORD HexToDWORD(char *pszHex);

extern TCHAR szErrorLogPath[MAX_PATH];
extern TCHAR szDataLogPath[MAX_PATH];
extern TCHAR szTempPath[MAX_PATH];

extern CRITICAL_SECTION   Lock;

//���ܲ��������е�ȫ�ֱ���
#ifdef __PERFORMANCE__
extern CRITICAL_SECTION   DebugLock;
extern DWORD  gTick;         //��ʼʱ���
extern DWORD  gTryCount;     //������Դ���
extern DWORD  gSuccess;      //�ɹ�����
extern DWORD  gTryWriteFile; //д�ļ�����
extern DWORD  gWriteFile;    //д�ļ��ܺ�ʱ
extern DWORD  gTryWriteDB;   //д���ݿ����
extern DWORD  gWriteDB;      //д���ݿ��ܺ�ʱ
extern DWORD  gTryMark;      //����Ǵ���
extern DWORD  gMark;         //����Ǻ�ʱ
extern DWORD  gSendRecv;     //�õ����ݺ�ʱ
extern DWORD  gTrySendRecv;  //���ճɹ�����
extern DWORD  gTotalTime;
extern DWORD  gNotFound;
#endif 

#endif //__GLOBAL_H__

