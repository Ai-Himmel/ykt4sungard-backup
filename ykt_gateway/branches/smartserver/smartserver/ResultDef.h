#ifndef __RESULT_DEF_H__
#define __RESULT_DEF_H__

#pragma once

//////////////////////////////////////////////////////////////////////////////////////////
//////以下定义操作结果的返回值
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RESULT_VALUE_DEFINE_H__
#define __RESULT_VALUE_DEFINE_H__
#define RET_DATAVALUE_ERROR            -1       //-1:数据长度参数值太大或等于负值,
#define RET_RECV_ERROR                 -2       //-2:接收数据错（串口没有打开即通讯）
#define RET_SEND_ERROR                 -3       //-3:发送数据错（串口没有打开即通讯）
#define RET_RECV_TIMEOUT               -4       //-4:接收数据超时;
#define RET_ADDR_ERROR                 -5       //-5:返回地址不匹配
#define RET_TERME_NOANSWER             -6       //-6:终端无反应
#define RET_COMMONU_ERROR              -7       //-7:串口打开/关闭错
#define RET_DATALENGTH_ERROR           -8       //-8返回数据长度错误
#define RET_DATACRC_ERROR              -9       //-9:数据校验错
#define RET_PARAMETER_ERROR1           -10      //-10:传入参数错
#define RET_OK                          0       //0：成功
#define RET_CARD_INVALID                1       //1:非法卡
#define RET_CLOCK_ERROR                 2       //2:时钟错
#define RET_MONEY_FORMAT_ERROR          3       //3:钱包格式错
#define RET_DATA_FULL                   4       //4:数据满
#define RET_SEQNUM_ERROR                5       //5:流水号错
#define RET_PARAMETER_ERROR2            7       //7:传入参数错
#define RET_COMMAND_ERROR               8       //8:无此命令或命令无法此时使用
#define RET_REMARK_ERROR                9       //9:重复打标记
#define RET_NO_RECORD                   10      //10:无记录或数据
#define RET_AUTHNO_ERROR                11      //11:授权号不符
#define RET_REQU_SIGNIN                 13      //13:申请签到
#define RET_BLACKLIST_ERROR             14      //14:黑名单有效期过期
#define RET_CARD_MONEY_ENOUGH           15      //15:卡内金额不足
#define RET_RECORD_NO_COLLECT           17      //17:还有记录未收集
#define RET_CARD_DEGREE_ERROR           18      //18:卡使用次数超限
#define RET_CARD_EXPECT_ERROR           19      //19:卡片已过有效期
#define RET_CARD_MONEY_LARGE            20      //20:卡片金额太大
#define RET_CARD_SEQOVER                22      //22:已结帐的交易流水已被覆盖(无法复核)
#define RET_ACCREC_NOTUP                23      //23:还有结账记录未上传
#define RET_NOT_AUTH                    24      //24:设备未授权无法签到

#define NETWORK_PAR_NONE                0       //直连
#define NETWORK_PAR_STAR                1       //星形
#define NETWORK_PAR_BUS                 2       //总线
#endif //__RESULT_VALUE_DEFINE_H__

//*------------------------------------------------------------------------------------
//*名称: TSSmartProtocol
//*功能: 通讯协议规则定义
//*------------------------------------------------------------------------------------
struct TSSmartProtocol
{
    unsigned char  PTHead[8];        //包起始符内容(目前为C2)
    unsigned short PTHeadLen;        //包起始符长度(目前为1)
	unsigned char  PTTail[8];        //包结束符内容(目前为C3)
    unsigned short PTTailLen;        //包结束符长度(目前为1)
	unsigned int   nLenOffset;       //数据包长度偏移(0..n)
	unsigned short nLenSize;         //长度字节数(目前为1)
	unsigned int   nMinPKSize;       //包最小的长度(0.不限长)
	unsigned int   nMaxPKSize;       //包最大的长度(0.不限长)
};

//*------------------------------------------------------------------------------------
//*名称: TSDeviceInfo
//*功能: 设备信息(供命令打包时用)
//*------------------------------------------------------------------------------------
struct TSDeviceInfo
{
	long nAuthID;                   //机器授权号
	int  nHardware;                 //硬件类型
	char sVersion[24];              //硬件版本号
	int  nAddr;                     //机器机号(0-255) 0表示广播通讯
	int  nNetPar;                   //网络结构: 直连, 星形, 总线
	int  nLevel;					//终端设备所连接的数据服务器的级别数
	unsigned char sLevelArray[32];	//级联级别
	int  nTotalNo;                  //终端机总数量
	int  nPort;                     //星型当前通讯端口 总线当前通讯机数组编号
	int  nNoReponseTime;            //终端无反应次数
};

//*------------------------------------------------------------------------------------
//*名称: TSCmdBuffer
//*功能: 返回的命令缓冲区包
//*------------------------------------------------------------------------------------
struct TSCmdBuffer
{
	int nBufferSize;					//传入的缓冲区的长度
	unsigned char *pBuffer;             //传入的缓冲区
	int nCmdSize;                       //返回的命令包长度
	long  nTimeOut1;                    //返回的超时时间1
	long  nTimeOut2;                    //返回的超时时间2
};

//功能: 得到999Smart设备协议的规则
long GetSmartProtocolRule(TSSmartProtocol *pSmartPT);

///////////////////////////////////////////////////////////////////////////////////////////
/// 功    能: -- 收到包的一部分后对其进行校验, 检测是否合法。
/// 参    数: 
///        pBuffer     --  要校验的数据块
///        nBufferSize --  数据块长度
///
/// 返 回 值: 
///        见返回值定义
///
/// 说    明:
///        只检验协议的正确性,如包的数据长度, CRC等错误
///////////////////////////////////////////////////////////////////////////////////////////
int VerifyBufferValid(unsigned char *pBuffer, int nBufferSize);

///////////////////////////////////////////////////////////////////////////////////////////
/// 以下函数完成创建发送到硬件的命令数据包的工作. 它屏蔽了硬件设备类型与网络的结构类型，
/// 用户只需传入相关的参数便可构建出相关的数据包。
/// 
/// 公共参数: 
///        pDevice --  该设备信息、网络结构信息
///        pBuffer --  要返回的命令数据包
///
/// 其他参数:
///        见设备动态库文档
///////////////////////////////////////////////////////////////////////////////////////////

//功能: 设置终端设备ID号（串行口上只允许接一个终端设备）
int MakeBufWriteID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id);

//读取终端设备ID号（串行口上只允许接一个终端设备）
int MakeBufReadID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id);

//调用通过ID号最低字节查询终端设备ID号
int MakeBufSearchId(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id);

//通过终端设备ID号给终端设备设置机号
int MakeBufWriteJh(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id);

//读终端设备机器类型
int MakeBufReadType(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//读终端设备程序完成时间（年、月、日、时）
int MakeBufReadDate(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//更改通信波特率
int MakeBufChangeBaudRate(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int baudrate);

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------专用命令（适用于计时宝与收费机）-----------------------------------------------------

//设置授权号
int MakeBufSetCommision(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *newcommision);

//下传系统主参数
int MakeBufDownParam(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char* Buffer);

//用户上传系统主参数(需授权号)
int MakeBufUserUpParam(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char* Buffer);

//上传系统主参数(不需授权号，公司内部使用)
int MakeBufUpParam(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//下传黑名单
int MakeBufDownBlackCard (TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision, ,int *num unsigned char *Buffer);

//删除黑名单
int MakeBufDownDelBlack (TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int *num unsigned char *Buffer,unsigned char *buffer);

//删除所有黑名单
int MakeBufDownDelBAll (TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision);

//判断一张卡是否是黑名单
int MakeBufIsBlack(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *blackno);

//广播方式下传黑名单版本
int MakeBufBroadcastBlack(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned *blackno,unsigned char* Buffer);

//下传黑名单版本
int MakeBufDownBlackVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Commision, unsigned char* Buffer);

//上传黑名单版本
int MakeBufUpBlackVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//传一条当前记录
int MakeBufUpRecordOne(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//传一条记录结束
int MakeBufEndUpRecordOne(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *serialno);

//上传一条历史记录
int MakeBufUpHisBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *serialno,  unsigned char *buffer);

//下传一条历史记录(三九内部使用)
int	MakeBufDownHisBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,  unsigned char *serialno, unsigned char *buffer);

//清空Flash（即初始化)
int MakeBufEmptyFlash(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//下传系统员密码（3字节6位BCD）
int MakeBufDownSysPWD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Commision, unsigned char *buffer);

//按块上传FLASH信息块
int MakeBufUpFlash(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int blocknum,unsigned char *buffer);

//上传终端机状态
int MakeBufUpStatus(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//下传更新时钟
int MakeBufDownClock (TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char* Buffer);

//上传时钟
int MakeBufUpClock(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//授权信息算法
void MakeBufSmartEncrypt(unsigned char E_number,unsigned char *ID, unsigned char *Plain);

//工作密钥下传
int MakeBufDownAuthinfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *Plain,unsigned char E_number);


//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------收费类Pos专用命令-----------------------------------------------------

//下传时间段
int MakeBufDownSJD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int num,int daycount,unsigned char* Buffer);

//上传时间段
int MakeBufUpSJD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int *num,unsigned char *Buffer);

//下传快捷键编号
int MakeBufDownQuickBH(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,int num,unsigned char *Buffer);

//上传快捷编号
int MakeBufUpQuickBH(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int *num,unsigned char *Buffer);

//下传消费编号
int MakeBufDownXFBH(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char flag,int num,unsigned char *Buffer);

//删除消费编号
int MakeBufDownDelXFBH(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id,int *num,unsigned char* Buffer);

//下传消费编号版本
int MakeBufDownXFBHVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//上传消费编号版本
int MakeBufUpXFBHVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//下传个人密码启动限额
int MakeBufDownLimitPWD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//上传个人密码启动限额
int MakeBufUpLimitPWD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//重新统计黑名单条数
int MakeBufCaculateBlack(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* commision);

//上传黑名单条数
int MakeBufUpBlackNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,int *num);

//下传黑名单有效期
int MakeBufDownBlackExpire(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *date);

//上传黑名单有效期
int MakeBufUpBlackExpire(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,unsigned char *date);

//结帐命令
int MakeBufCount(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision);

//上传一条结帐记录
int MakeBufUpCountOne(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,unsigned char *data);

//确认上传一条结帐记录
int MakeBufEndUpCountOne(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,unsigned char *ser);

//按流水号上传一条结帐记录
int MakeBufUpCountBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision, unsigned char *ser,unsigned char *data);

//按流水下传一条结帐记录(三九内部使用)
int MakeBufDownCountBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Id,unsigned char *data);

//上传任何交易记录(三九内部使用)
int MakeBufUpBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *serialno,   unsigned char *buffer);

//下传任何交易记录(三九内部使用)
int MakeBufDownBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *serialno,unsigned char *buffer);

//机器签到确认
int MakeBufStartUse(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int flag);

//下传卡片单位密码（2字节HEX，低位在前,V10专用）
int MakeBufDownCompanyPWD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int password);

//上传V10卡钱包扇区(v10专用)  
int MakeBufUpSectorNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int *sectornum);

//下传V10卡钱包扇区(v10专用) 
int MakeBufDownSectorNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int sectornum);

//按结帐流水号复核结帐(测试中)
int MakeBufDownCountAgain(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *ser);

//按流水上传复核结帐记录(测试中)
int MakeBufUpCountAgain(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *ser,unsigned char *data);

//上传定时结帐时间表(测试中)
int MakeBufUpCountTime(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *buffer);

//下传定时结帐时间表(测试中)
int MakeBufDownCountTime(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *buffer);

//记录体CRC重算并下传(11月11日增)
int MakeBufDownHisRecord(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *buffer);

//广播方式下传或删除黑名单版本
int MakeBufDownOrDelBlackAndVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *blackno, unsigned char* version, bool flag);

//启动或禁止补助
int MakeBufBuZhuSwitch(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, BOOL _switch);


//判断补助开关状态
int MakeBufIsBuZhuSwitch(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int *nswitch);


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//------------------------------------计时Pos专用命令
 
//下传白名单(模式2,3)
int MakeBufDownWhiteCard(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int *num,unsigned char *Buffer);

//删除白名单(模式2,3)
int MakeBufDownDelWhite(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,int *num unsigned char *Buffer,unsigned char *buffer);

//删除所有白名单(模式2,3)
int MakeBufDownDelWAll(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//判断一张卡是否是白名单(模式2,3)
int MakeBufIsWhite(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *blackno);

//广播方式下传一条白名单+版本(模式2,3)
int MakeBufBroadcastWhite(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned *blackno,unsigned char* Buffer);

//下传白名单版本(模式2,3)
int MakeBufDownWhiteVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char* Buffer);

//上传白名单版本(模式2,3)
int MakeBufUpWhiteVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//下传计时宝时间段(模式3)
int MakeBufDownJSBSJD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int day,int num, unsigned char* Buffer);

//上传计时宝时间段(模式3)
int MakeBufUpJSBSJD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int date,unsigned char *Buffer);

//下传计时宝节假日 (模式3)
int MakeBufDownHoliday(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int num, unsigned char* Buffer);

//上传计时宝节假日(模式3)
int MakeBufUpHoliday(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);


//下传模式4版本号
int MakeBufDownMode4Ver(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//上传模式4版本号
int MakeBufUpMode4Ver(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//下传模式4白名单一条
int MakeBufDownMode4OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *Buffer);

//上传模式4白名单一条
int MakeBufUpMode4OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//下传模式4节假日
int MakeBufDownMode4Holiday(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *Buffer);

//上传模式四节假日
int MakeBufUpMode4Holiday(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//下传模式4时间段
int MakeBufDownMode4TimeSegment(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *Buffer);

//上传模式4时间段
int MakeBufUpMode4TimeSegment(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//下传ID名单或4字节M1卡序列号一条(模式1,2,3)
int MakeBufIDDownList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//删除一条ID名单或4字节M1卡序列号(模式1,2,3)
int MakeBufIDDelList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//判断一条ID名单或4字节M1卡序列号(模式1,2,3)
int MakeBufIDJudgeList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//广播下传ID名单一条或4字节M1卡序列号(模式1,2,3)
int MakeBufIDBoardcastDownList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//广播删除ID名单一条或4字节M1卡序列号(模式1,2,3)
int MakeBufIDBoardcastDelList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//搜索感应头
int MakeBufSearchReaderInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//上传感应头信息
int MakeBufUpReaderInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//设置感应头机号
int MakeBufSetReaderMacNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//防火
int MakeBufAntiFire(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//防盗
int MakeBufAntiThief(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//恢复正常运行
int MakeBufResumeNormal(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//下传模式5白名单一条
int MakeBufDownMode5OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//删除模式5白名单一条
int MakeBufDelMode5OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//查询模式5白名单一条
int MakeBufQueryMode5OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//清除模式5所有白名单
int MakeBufDelAllMode5WhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//下传模式5房间号与设备号一条
int MakeBufDownMode5OneRoomNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//删除模式5房间号一条
int MakeBufDelMode5OneRoomNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);


// 清除模式5所有房间号和设备号
int MakeBufDelAllMode5RoomNumAndEquipNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//查询模式5一个设备的状态
int MakeBufQueryMode5OneEquipStatus(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char * buffer);

// 上传当前借出钥匙的总数
int MakeBufUpMode5LoanKeyAmount(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, int *num);

////////////////////////////////////////////////////////////////////////
///////////////////挂失机专用命令///////////////////////////////////////

//发送比对结果 
int MakeBufConfirmLost(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *serialno);

////////////////////////////////////////////////////////////////////////
///////////////////验票机专用命令///////////////////////////////////////

//设置票号
int MakeBufSetTicket(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int ticketnum);

//读取票号
int MakeBufGetTicket(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int *ticketnum);

////////////////////////////////////////////////////////////////////////
///////////////////上机上网机专用命令///////////////////////////////////////

//读卡信息
int MakeBufReadCard(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *CardNum,unsigned char *CardNum1,
	unsigned char *Password, unsigned char *CardID,unsigned char *Name,int *Money);

//扣卡金额
int MakeBufDecCard(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *CardNum,int DecMoney);

//比较个人密码
int MakeBufCheckPassword(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Password,unsigned char *CardID,unsigned char *PWD);

//显示字符串
int MakeBufDisplay(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *XSbuffer,int DelayTime);

//用户显示金额
int MakeBufDisplayMoney(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int Money);

//读卡信息并声音提示刷卡
int MakeBufReadCardBeep(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, 
				      unsigned char *CardNum,
					  unsigned char *CardNum1,
					  unsigned char *Password,
					  unsigned char *CardID,
					  unsigned char *Name,
					  int *Money);

//读个人详细信息
int MakeBufReadPersonalInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Name,unsigned char *buffer);

//读卡详细信息
int MakeBufReadCardInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *CardNum,unsigned char *CardNum1,
	unsigned char *CardID,int *CardType,unsigned char *ExpireDay);

//读第三方信息(如借书证号)
int MakeBufReadLiberyNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *ThirdInfo);

//初始化数据服务器
int MakeBufIni_Fwq(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *BautRateBuffer, unsigned char port);

//搜索服务器参数
int MakeBufSearch_FwqPort(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char port);

//上传子终端参数
int MakeBufFwq_State(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//通过数据服务器查询端口记录情况(主动方式收记录)
 int MakeBufQueryFwqPortStat(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//传七个端口当前记录(主动方式收记录)
int MakeBufUpByFwqZD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//传七端口记录结束(打标记,主动方式收记录)
int MakeBufEndUpByFwqZD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//重设端口授权号
int MakeBufResetCommision(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//下传补助名单给服务器
int MakeBufDownBZ(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);

//下传补助名单版本号
int MakeBufDownFWQBZVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);

//上传补助名单版本号
int MakeBufUpFWQBZVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);

//收取一笔补助名单
int MakeBufUpBZMD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);

//按流水上传补助记录
int MakeBufUpBZBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);
