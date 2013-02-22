#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/***************************终端设备动态库----函数说明****************************************************/
//Common.cpp
int _stdcall calc_crc16(unsigned char len,unsigned char *in,unsigned char *out);
//public.cpp
int _stdcall MakeBuf_SetID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *id);//设置终端设备ID号
int _stdcall MakeBuf_GetID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//读取终端设备ID号
int _stdcall MakeBuf_SearchID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *id);//通过ID号最低位查询终端设备ID号
int _stdcall MakeBuf_SetAddr(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *id);//通过终端设备ID号给终端设备设置机号
int _stdcall MakeBuf_GetType(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//读终端设备机号类型命令
int _stdcall MakeBuf_GetVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//读终端设备程序版本号
int _stdcall MakeBuf_ChangeBuadRate(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int nBaudRate);///  更改通信波特率///    nBaudRate 波特率值  19200  9600 4800 2400  1200 28800	57600	115200  38400
//clock.cpp
int _stdcall MakeBuf_SetClock(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *clock);/// 功能：设置时钟/// 输入：年月日时分秒星期
int _stdcall MakeBuf_GetClock(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//功能：读取时钟  注意：该指令返回时不带星期
//flow.cpp
int _stdcall GetSmartProtocolRule(TSSmartProtocol *pSmartPT);/// 功能：协议规则定义函数
int _stdcall UnMakeDeviceBuffer(TSCmdBuffer *pBuffer);//通用函数: 设备动态库检测收到数据收否正确：符合SMART411协议 
int _stdcall MakeBuf_SetTerminalToFactorySetting(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//恢复终端设备为出厂状态
int _stdcall MakeBuf_RecountAllStateData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//扎帐数据初始化  产生后果: 清空所有结帐记录，并按天重新结帐。
int _stdcall MakeBuf_ClearData(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：清除所有交易数据
int _stdcall MakeBuf_CollectData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);//数据收集函数。
int _stdcall MakeBuf_ConfirmData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *FlowNo);/// 功能：数据确认
int _stdcall MakeBuf_CollectDataBySerialNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *SerialNo);//功能:按流水上传终端交易纪录
int _stdcall MakeBuf_CollectStateData(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能:上传扎帐纪录
int _stdcall MakeBuf_ConfirmStateData(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *FlowNo);/// 功能:确认扎帐纪录
int _stdcall MakeBuf_CollectStateDataBySerial(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *SerialNo);/// 功能:按流水上传扎帐纪录
//List.cpp
int _stdcall MakeBuf_GetBlackUsefulLife(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：获取黑名单有效期
int _stdcall MakeBuf_SetBlackUsefulLife(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *date);/// 功能：下传黑名单有效期
int _stdcall MakeBuf_GetBlackVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：上传黑名单版本
int _stdcall MakeBuf_SetBlackVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *date);/// 功能：下传黑名单版本
int _stdcall MakeBuf_BoardBlackNo(unsigned char *Buffer, unsigned char *Version, unsigned char *CardNo);/// 功能：广播黑名单pBuffer:数据体 CardNo: 卡号     3字节
int _stdcall MakeBuf_CheckBlackCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo);/// 功能：检查黑名单
int _stdcall MakeBuf_DownBlackCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo);/// 功能：下传黑名单( 注意：一次只能下传一条黑名单)
int _stdcall MakeBuf_DelOneBlackCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo);/// 功能：删除黑名单(注意：一次只能删除一条黑名单)/// 参数： *CardNo 3子节卡号
int _stdcall MakeBuf_DelAllBlackCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：删除所有黑名单
int _stdcall MakeBuf_GetBlackAllCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：上传黑名单条数
int _stdcall MakeBuf_RecountAllBlackCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：重新统计黑名单总条数
int _stdcall MakeBuf_DownWhiteCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int flag, unsigned char *CardNo);/// 功能：下传白名单(注意：一次只能下传一条)/// 参数： CardNo----3字节
int _stdcall MakeBuf_DelWhiteCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *CardNo);/// 功能：删除白名单(注意：一次只能删除一条)/// 参数：CardNo---3字节
int _stdcall MakeBuf_DelAllWhiteCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：删除所有白名单
int _stdcall MakeBuf_SetWhiteVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *date);/// 功能：下传白名单版本/// 参数：*date ---- 六子节黑名单版本
int _stdcall MakeBuf_GetWhiteVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：上传白名单版本
int _stdcall MakeBuf_CheckWhiteCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo);/// 功能：检查白名单/// 参数：*CardNo	3字节卡号
int _stdcall MakeBuf_BoardWhiteNo(unsigned char *Buffer, unsigned char *Version, unsigned char *CardNo);/// 功能：广播白名单/// 参数：///      pBuffer:数据体///      Version:版本信息 6字节BCD码///      CardNo: 卡号     3字节/// 返回：///      通信包数据体长度
int _stdcall MakeBuf_SetAssistVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Buffer);/// 功能：补助名单版本下传/// 参数：///   Buffer: ///     版本时间:  6字节///     总条数:    2字节///     总金额:    4字节(低位在前)///     加钱总条数:2字节///     加钱总金额:4字节(低位在前)///     减钱总条数:2字节///     减钱金额:  4字节(低位在前)
int _stdcall MakeBuf_GetAssistVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：补助名单版本上传
int _stdcall MakeBuf_SetAssisList(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Buffer);/// 功能：下传补助名单/// 参数：*List///       3字节交易卡号///       2字节批号///       2字节金额(低位在前)///       1字节加减钱标记(0---加，1---减)
int _stdcall MakeBuf_GetAssisList(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：上传补助名单

int _stdcall MakeBuf_ClearAllAssisList(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：清除补助名单
int _stdcall MakeBuf_SetAssistState(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char switchflag);/// 功能：设置补助功能开关/// 参数：/// switchflag ---00开///            ---FF关
int _stdcall MakeBuf_GetAssistState(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：获取补助功能开关
//Lport.cpp
int _stdcall MakeBuf_SetPortRegNoAndMacNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo,unsigned char *newRegNo,int MacNo);/// 功能：设置服务器某端口注册号及机号/// PortNo    ----- 1BYTE   对应端口号/// newRegNo  ----- 4BYTE   对应注册号/// MacNo     ----- 1BYTE   对应机号/// 产生后果：Lport该端口所有数据将清空
int _stdcall MakeBuf_ClearPortData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo);/// 功能：端口数据初始化
int _stdcall MakeBuf_SetPortToFactorySetting(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo);/// 功能：端口参数初始化(将端口所有信息恢复为出厂状态)/// 参数：///    PortNo ------ 端口号
int _stdcall MakeBuf_GetPortPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo);/// 功能：读服务器某端口参数/// 参数：///    PortNo ------ 端口号
int _stdcall MakeBuf_SearchPort(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo);/// 功能:搜索端口
int _stdcall MakeBuf_GetLportMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能:读取Lport主参数
int _stdcall MakeBuf_SetLportNewRegNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *newRegNo);/// 功能：设置注册号/// 参数：/// newRegNo ------ 新注册号
int _stdcall MakeBuf_SetLportToFactorySetting(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：初始化服务器
int _stdcall MakeBuf_DebugGetLportMainPar(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：调试上传服务器主参数
int _stdcall MakeBuf_RemoteReset(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：远程复位

//Parameter.cpp
int _stdcall MakeBuf_SetMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *mainpar);/// 功能：设置主参数/// 输入：*mainpar 28字节
int _stdcall MakeBuf_GetMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：获取主参数
int _stdcall MakeBuf_Debug_GetMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：调试获取主参数(不带注册号)
int _stdcall MakeBuf_SetRegNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *regno);/// 功能:设置注册号/// 参数:*regno---4字节注册号
int _stdcall MakeBuf_SetSFJ_TimePhase(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int No,int Time,unsigned char *Buffer);/// 功能：设置时间段/// 参数：///    No   ---- 时间段总条数///    Time ---  节日次数///    Buffer--- no*10 时间段参数
int _stdcall MakeBuf_GetSFJ_TimePhase(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：获取时间段参数
int _stdcall MakeBuf_SetSFJFastNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char No, unsigned char *Buffer);/// 功能：下传快捷编号///   No:编号总数(1字节)///   Buffer:3*No编号内容
int _stdcall MakeBuf_GetSFJFastNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：上传快捷编号
int _stdcall MakeBuf_SetSFJConsumeNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char Flag, unsigned char No,unsigned char *Buffer);/// 功能:下传消费编号/// 参数:///    Flag:全部/或添加标记(1字节)///    No:  编号数(1字节)///    Buffer:N*3字节编号
int _stdcall MakeBuf_DelSFJConsumeNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char No,unsigned char *Buffer);// 功能：删除消费编号/// 参数:///   No:编号总数///   Buffer:N*3字节编号
int _stdcall MakeBuf_GetSFJConsumeVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：上传消费编号版本
int _stdcall MakeBuf_SetSFJComsumeVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Buffer);// 功能:下传消费编号版本	/// 参数：///  Buffer:消费编号版本(6字节)
int _stdcall MakeBuf_SetDirSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int Sector);/// 功能：设置卡片目录扇区号/// 参数：Sector---卡片目录扇区号
int _stdcall MakeBuf_GetDirSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：设置卡片目录扇区号
int _stdcall MakeBuf_SetV10PacketSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int Sector);/// 功能：设置V10卡片钱包所在的扇区 /// 参数：Sector --- 扇区号
int _stdcall MakeBuf_GetV10PacketSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：读取V10卡片钱包所在的扇区
int _stdcall MakeBuf_SetV10Password(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Password);/// 功能:下传V10卡单位密码/// 参数：Password(2字节,低位在前)
int _stdcall MakeBuf_GetStateTimeTable(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能:上传定时结帐时间表
int _stdcall MakeBuf_SetStateTimeTable(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int No,unsigned char *Buffer);/// 功能：下传定时结帐时间表/// 参数：///    No:定时扎帐总条数///    Buffer:定时扎帐时间参数 时分为1组
int _stdcall MakeBuf_State(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：上位机要求扎帐
int _stdcall MakeBuf_ReState(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *SerialNo);/// 功能：上位机要求复核扎帐/// 参数：///      SerialNo：要求复核扎帐流水号
int _stdcall MakeBuf_SetComsumeFlag(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char Flag);/// 功能：设置消费功能开启或关闭/// 参数：///    Flag --- 1 开启///    Flag --- 0 关闭
int _stdcall MakeBuf_SetWorkingKey(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Plain,unsigned char KeyNo);/// 功能：设置工作密钥及算法编号/// 参数：///     *Plain ------ 密钥密文 9字节///     KeyNo  ------ 算法编号
int _stdcall MakeBuf_GetLargeConsumeMoney(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：获取最大消费限额
int _stdcall MakeBuf_SetLargeConsumeMoney(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Money);/// 功能：设置最大消费限额/// 参数：///     Money:3字节金额低位在前
int _stdcall MakeBuf_SetManagePassword(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Password);/// 功能：设置系统管理员密码/// 参数：///     Password:密码(3字节 BCD码)
//Sensor.cpp
int _stdcall MakeBuf_SearchSensor(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：搜索感应头
int _stdcall MakeBuf_GetSensorInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：上传感应头信息
int _stdcall MakeBuf_SetSensorAddress(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int No,unsigned char *Buffer);/// 功能：设置感应头机号/// 参数：///     No----感应头总数///     Buffer----n*5字节 
int _stdcall MakeBuf_SetFireState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：设置为防火状态
int _stdcall MakeBuf_SetTheftState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：设置为防盗状态
int _stdcall MakeBuf_SetNormalState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer);/// 功能：恢复为正常状态
int _stdcall MakeBuf_SetMode3Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int No,unsigned char *Buffer);/// 功能：设置模式三节假日信息/// 参数：///    No:节假日总条数///    Buffer:节假日信息
int _stdcall MakeBuf_SetMode3TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int WeekInfo,int No,unsigned char *Buffer);/// 功能：设置模式三时间段信息/// 参数:///    WeekInfo:星期信息 1Byte///    No:时间段数       1Byte///    Buffer:时间段信息 No*8 Byte
int _stdcall MakeBuf_GetMode3Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer);/// 功能：获取模式三节假日信息
int _stdcall MakeBuf_GetMode3TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int WeekInfo);/// 功能：获取模式三时间段信息/// 参数: ///   WeekInfo:星期信息
int _stdcall MakeBuf_SetLoginPublic1Password(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *Password);/// 功能：下传登陆公共信息1所需要的密码/// 参数：///     Password
int _stdcall MakeBuf_ConfirmLost(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *Password);

void _stdcall GenerateWorkingKey(unsigned char *str1, unsigned char *str2);
void _stdcall Smart_CardDes(unsigned char *str1, 
						   unsigned char *str2,
						   unsigned char *str3,
						   unsigned char *str4,
						   unsigned char cFlag);

//定义服务器提供的API集
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

//定义日志
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

//性能测试数据中的全局变量
#ifdef __PERFORMANCE__
extern CRITICAL_SECTION   DebugLock;
extern DWORD  gTick;         //起始时间点
extern DWORD  gTryCount;     //任务测试次数
extern DWORD  gSuccess;      //成功次数
extern DWORD  gTryWriteFile; //写文件次数
extern DWORD  gWriteFile;    //写文件总耗时
extern DWORD  gTryWriteDB;   //写数据库次数
extern DWORD  gWriteDB;      //写数据库总耗时
extern DWORD  gTryMark;      //做标记次数
extern DWORD  gMark;         //做标记耗时
extern DWORD  gSendRecv;     //得到数据耗时
extern DWORD  gTrySendRecv;  //接收成功次数
extern DWORD  gTotalTime;
extern DWORD  gNotFound;
#endif 

#endif //__GLOBAL_H__

