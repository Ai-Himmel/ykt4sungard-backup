#ifndef NL8900_DEF_H
#define NL8900_DEF_H

#define rsSuccess	 1			// 成功
#define rsTimeOut	-1			// 命令超时
#define rsUnknowCmd	-2			// 未知命令
#define rsTransErr	-3			// 传输错误
#define rsUnknowResp -4			// 未知响应
#define rsEscExit	-5			// 按ESC退出

#define rrERR_FORMAT	-4001		// 调用参数错
#define rrERR_DATAFORMAT	-4002	// 数据格式错
#define rrERR_LENGTH	-4003		// 接收长度错
#define rrERR_READ	-4004			// 读错
#define rrERR_WRITE	-4005			// 写错
#define rrERR_LESS	-4006			// ERR_LESS
#define RrERR_BCC	-4007			// 校验错
#define RrERR_CardData	-4008		// 卡数据错
#define RrERR_OpenCom	-4009		// 打开串口错
#define rrNotag	-4012				// 在操作区址没有射频卡
#define rrCrc	-4013				// 接收CRC错误
#define rrEmpty	-4014				// 值溢出
#define rrAuth	-4015				// 认证错误
#define rrParity	-4016			// 奇偶校验错误
#define rrCode	-4017				// 和RF卡中的通讯错误
#define rrKey	-4018				// 认证密钥错误
#define rrBitcount		-4019		// 接收比特数错误
#define rrBytecount	-4021			// 接收字节数错误
#define rrTrans	-4022				// 命令Transfer执行错误
#define rrWrite	-4023				// 命令Write执行错误
#define rrIncr	-4024				// 命令Increment执行错误
#define rrDecr	-4025				// 命令Decrement执行错误
#define rrRead	-4026				// 命令Read执行错误
#define rrOvfl	-4027				// 值溢出错误
#define rrFraming		-4028		// 帧错误
#define rrUnknowncommand	-4029	// 无效命令
#define rrColl	-4030				// 冲突错误
#define rrInit		-4031			// 初始化错误
#define rrInterface	-4032			// 接口错误
#define rrAccesstimeout	-4033		// 访问超时
#define rrNobit		-4034			// 防冲突过程中的TagType码错误
#define rrQuit	-4035				// 命令被中断退出
#define rrRevbufoverflow	-4036	// 接收缓冲区溢出
#define rrSenbufoverflow	-4037	// 发送缓冲区溢出
#define rrPara	-4038				// 参数错误
#define RrNoloadkey	-4039			// 没装密钥错误


#define DCLR_NLFUNC(r,name,arg) \
	typedef r (* LP##name) arg; \
	extern LP##name name;

#define DEF_NLFUNC(name) \
	LP##name name = NULL;	\
	
#define LOAD_NLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if( NULL == name) \
		return -1;

//////////////////////////////////////////////////////////////////////////
// 接口函数定义

DCLR_NLFUNC(int,Mag_ReadCard,(char *tk2,char *tk3, int wTime,int tkNum))
DCLR_NLFUNC(int,IC_SelectCard,(char *str))
DCLR_NLFUNC(int,IC_Powerup,(char *str, unsigned char* rcvData))
DCLR_NLFUNC(int,IC_Powerdown,(char *str))
DCLR_NLFUNC(int,IC_IcCRW,(int len ,char sendcmdbuf[200], char rcvbuf[200]))
DCLR_NLFUNC(BOOL,ICMag_ComInit,(char *_ComType, int _Syn))
DCLR_NLFUNC(int,ICMag_OpenCom,(void))
DCLR_NLFUNC(int,ICMag_CloseCom,(void))
DCLR_NLFUNC(int,IC_ReadState,(unsigned char *Resp))
DCLR_NLFUNC(int,ICMag_ReadEdition,(unsigned char *Resp))
DCLR_NLFUNC(int,IC_StopOper,(void))
DCLR_NLFUNC(int,IC_SoftRest,(void))
DCLR_NLFUNC(void,IC_getReceData,(char cpto[200]))
DCLR_NLFUNC(int,IC_getReceLen,(void))
DCLR_NLFUNC(int,IC_SelectIcCardType,(int cardtype_num))
DCLR_NLFUNC(void,ICMag_GetErrMsg,(char *ErrMsg,int ErrCode))

DCLR_NLFUNC(int,Rf_GetStatus,(unsigned char *_Status))
DCLR_NLFUNC(int,Rf_StoreKey,(unsigned char _Mode,unsigned char _SecNr,
			unsigned char *_Nkey))
DCLR_NLFUNC(int,Rf_LoadKey,(unsigned char _Mode,unsigned char _SecNr,
			unsigned char _AuthSector))
DCLR_NLFUNC(int,Rf_HL_Read,(unsigned char _Mode,unsigned char _BlockAddr,
			unsigned long _Snr,
			unsigned char *_Data,
			unsigned long *_NSnr))
DCLR_NLFUNC(int,Rf_HL_Write,(unsigned char _Mode,unsigned char _BlockAddr,
			unsigned long *_Snr,
			unsigned char *_Data))
DCLR_NLFUNC(int,Rf_HL_Initval,(unsigned char _Mode,unsigned char _BlockAddr,
			unsigned long _Value,
			unsigned long *_Snr))
			
DCLR_NLFUNC(int,Rf_ComInit,(char *_ComType,int _Syn))
DCLR_NLFUNC(BOOL,Rf_GetSerial,(unsigned char *_serial))
DCLR_NLFUNC(BOOL,Rf_ComClose,())

#endif