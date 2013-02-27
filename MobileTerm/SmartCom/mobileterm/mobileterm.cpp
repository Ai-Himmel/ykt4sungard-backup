// mobileterm.cpp : Defines the initialization routines for the DLL.
//
/** 
 * 模块名						39手持机库
 * 文件名						mobileterm.cpp
 * 文件实现功能					39手持机函数库封装
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-10-19
 * 备注
 * $Id$
 */

#include "stdafx.h"
#include "mobileterm.h"
#include "importdef.h"
#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//


//////////////////////////////////////////////////////////////////////////
// 编写的接口函数
#define VALIDATE_COM	\
	if(!gs_com_is_open) \
	{ \
		gs_errno = E_COM_NOT_OPEN; \
		return -1; \
	}

#define VALIDATE_KEY \
	if(!gs_has_key) \
	{ \
		gs_errno = E_NOT_HAS_KEY; \
		return -1; \
	}

#define VALIDATE_TERM_INFO \
	if(0 == gs_term_info.termno) \
	{ \
		gs_errno = E_SMART_TERM_INFO; \
		return -1; \
	}

/** 
 * @brief 错误代码
 */
static int gs_errno = 0;
/** 
 * @brief 串口是否打开 ，1表示已打开 0表示未打开
 */
static int gs_com_is_open = 0;

/** 
 * @brief 错误代码与错误信息对应结构定义
 */
struct err_msg_no_def {
	int err_no;
	char *err_msg;
};
/** 
 * @brief 当前连接的手持机设备
 */
static SMART_TERMINAL_T gs_term_info;

/** 
 * @brief 全局错误代码与错误信息定义
 */
static struct err_msg_no_def gs_msg_def[]=
{
	{-1,"数据长度参数值太大或等于负值,"},
	{-2,"接收数据错（串口没有打开即通讯）"},
	{-3,"发送数据错（串口没有打开即通讯）"},
	{-4,"接收数据超时;"},
	{-5,"返回地址不匹配"},
	{-6,"终端无反应"},
	{-7,"串口打开/关闭错"},
	{-8,"返回数据长度错误"},
	{-9,"数据校验错"},
	{-10,"传入参数错"},
	{0,"成功"},
	{1,"非法卡"},
	{2,"时钟错"},
	{3,"钱包格式错"},
	{4,"数据满"},
	{5,"流水号错"},
	{7,"传入参数错"},
	{8,"无此命令或命令无法此时使用"},
	{9,"重复打标记"},
	{10,"无记录或数据"},
	{11,"授权号不符"},
	{13,"申请签到"},
	{14,"黑名单有效期过期"},
	{15,"卡内金额不足"},
	{17,"还有记录未收集"},
	{18,"卡使用次数超限"},
	{19,"卡片已过有效期"},
	{20,"卡片金额太大"},
	{22,"已结帐的交易流水已被覆盖(无法复核)"},
	{23,"还有结账记录未上传"},
	{24,"设备未授权无法签到"},
	{E_COM_NOT_OPEN,"串口未打开"},
	{E_LOAD_SMARTCOM,"加载SmartCom411SCJ失败!"},
	{E_COM_BAND,"串口波特率不正确"},
	{E_SMART_TERM_NO,"机号范围不正确"},
	{E_SMART_TERM_INFO,"未读取手持机参数"},
	{0xFFFF,""}
};

/** 
 * @brief 取得上一次调用后的错误代码
 * 
 * @return - 错误代码
 */
int CALLAPI MBLGetErrno()
{
	return gs_errno;
}
/** 
 * @brief 取得上一次调用后的错误信息
 * 
 * @param msg - [out] 错误信息
 * 
 */
void CALLAPI MBLGetErrMsg(char *msg)
{
	int i = 0;
	while(1)
	{
		if(0xFFFF == gs_msg_def[i].err_no)
		{
			break;
		}
		if( gs_errno == gs_msg_def[i].err_no)
		{
			strcpy(msg,gs_msg_def[i].err_msg);
			return;
		}
		++i;
	}
	strcpy(msg,"一般性错误");
}
/** 
 * @brief 提示上一次调用的错误信息
 * 
 */
void CALLAPI MBLShowErrMsg()
{
	char tmp[512] = "";
	MBLGetErrMsg(tmp);
	AfxMessageBox(tmp);
}
/** 
 * @brief 重置全局参数
 */
static void do_reset_params()
{
	gs_com_is_open = 0;
	gs_has_key = 0;
	memset(&gs_term_info,0,sizeof gs_term_info);
}

/** 
 * @brief 将Buffer高低位互换
 * 
 * @param inbuf - 输入buffer
 * @param outbuf - [out]输出互换后的buffer
 * @param buflen - 输入buffer的长度
 */
static void do_reverse_buffer(uchar8 *inbuf,uchar8 *outbuf,int buflen)
{
	memcpy(outbuf,inbuf,buflen);
	int midpos = buflen / 2 + buflen % 2;
	int i;
	for(i = 0;i < midpos;++i)
	{
		uchar8 t = outbuf[i];
		outbuf[i] = outbuf[buflen - i - 1];
		outbuf[buflen - i - 1] = t;
	}
}

/** 
 * @brief 取得当前手持机的参数
 * 
 * @param term - [out]手持机结构
 * 
 */
void CALLAPI MBLGetTermInfo(SMART_TERMINAL_T *term)
{
	memcpy(term,&gs_term_info,sizeof(SMART_TERMINAL_T));
}

/** 
 * @brief 打开串口
 * 
 * @param port - 串口号,从1开始
 * @param band - 比特率,使用19200
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLOpenCom(int port,int band)
{
	int band_index = 0;
	do_reset_params();
	if(LoadSmartCom411SCJ() != 0)
	{
		gs_errno = E_LOAD_SMARTCOM;
		return -1;
	}
	switch(band)
	{
	case 19200:
		band_index = 0;
		break;
	case 9600:
		band_index = 1;
		break;
	case 38400:
		band_index = 8;
		break;
	default:
		gs_errno = E_COM_BAND;
		return -1;
	}
	gs_errno = IniCom(port,band_index);
	if(!gs_errno)
	{
		gs_term_info.port = port;
		gs_com_is_open = 1;
		return 0;
	}
	return -1;
}

/** 
 * @brief 关闭串口
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLCloseCom()
{
	if(gs_com_is_open)
	{
		gs_errno = CloseCom(gs_term_info.port);
		if(gs_errno)
		{
			return -1;
		}
		do_reset_params();
	}
	return 0;
}

/** 
 * @brief - 取得手持机物理ID 与 机号
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLReadId()
{
	uchar8 rawData[5] = "";
	VALIDATE_COM;
	gs_errno = ReadId(gs_term_info.port,rawData,gs_term_info.level
		,gs_term_info.level_array);
	if(!gs_errno)
	{
		// 物理ID
		memcpy(gs_term_info.phyid,rawData,sizeof gs_term_info.phyid);
		// 机号
		gs_term_info.termno = rawData[4];
		// 授权号
		memcpy(gs_term_info.commision,gs_term_info.phyid,sizeof gs_term_info.commision);
		return 0;
	}
	return -1;
}

/** 
 * @brief - 设置手持机号
 * 
 * @param id - 要设置的机号
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLWriteJh(int id)
{
	uchar8 rawData[5] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	if(id < 1 || id > 254 )
	{
		gs_errno = E_SMART_TERM_NO;
		return -1;
	}
	memcpy(rawData,gs_term_info.phyid,4);
	rawData[4] = (uchar8)id;
	gs_errno = WriteJh(gs_term_info.port,rawData,gs_term_info.level
		,gs_term_info.level_array);
	if(!gs_errno)
	{
		gs_term_info.termno = id;
		return 0;
	}
	return -1;
}

/** 
 * @brief - 将BCD转换成字符串
 * 
 * @param outstr - [out]输出转码后的字符串
 * @param inbuf - 输入BCD码
 * @param buflen  - 输入长度
 */
static void do_format_bcd_2_str(char *outstr,const uchar8 *inbuf,int buflen)
{
	int i;
	i = 0;
	while(i < buflen)
	{
		outstr[i<<1] = ((inbuf[i] >> 4) & 0x0F) + '0';
		outstr[(i<<1) + 1] = (inbuf[i] & 0x0F) + '0';
		++i;
	}
}
/** 
 * @brief 将字符串转换成BCD码
 * 
 * @param outbuf - [out]输出的BCD码
 * @param instr - 输入要转换的字符串
 * @param inlen - 要转换的字符串长度
 */
static void do_format_str_2_bcd(uchar8 *outbuf,const char *instr,int inlen)
{
	int i;
	for(i = 0;i < inlen;i+=2)
	{
		outbuf[i / 2] = ((instr[i] - '0') & 0x0F) << 4;
		outbuf[i / 2] |= (instr[i + 1] - '0') & 0x0F;
	}
}

/** 
 * @brief 将Hex转换成字符串
 * 
 * @param inbuf - 要转换的字符串HEX格式
 * @param outstr - [out]转换后输出的字符串
 * @param inlen - 要转换的字符串长度, 输出的buf大小要大于等于inlen+1
 */
static void do_hex_2_str(const uchar8 *inbuf,char *outstr,int inlen)
{
	int i,j;
	for(i = 0,j = 0;i < inlen;++i)
	{
		j += sprintf(outstr + j,"%02X",inbuf[i]);
	}
}
/** 
 * @brief 将字符串转换成HEX格式
 * 
 * @param instr - 输入要转换的字符串
 * @param outbuf - 输出HEX格式的字符串
 * @param inlen - 要转换的字符串长度，输出buf长度为outbuf / 2
 */
static void do_str_2_hex(const char *instr,uchar8 *outbuf,int inlen)
{
	char tmp[3] = "";
	int i;
	for (i = 0;i < inlen;i+=2)
	{
		memcpy(tmp,instr+i,2);
		outbuf[i / 2] = (uchar8)strtoul(tmp,NULL,16);
	}
}
/** 
 * @brief 读取手持机程序版本
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLReadDate()
{
	uchar8 buf[4] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = ReadDate(gs_term_info.port,gs_term_info.termno
		,buf,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		do_format_bcd_2_str(gs_term_info.verdate,buf,4);
		return 0;
	}
	return -1;
}

/** 
 * @brief 读取手持机机型代码
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLReadType()
{
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = ReadType(gs_term_info.port,gs_term_info.termtype,gs_term_info.termno
		,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief 读取手持机的参数，包括物理ID，机型，机号，程序版本，并保存到全局变量中
 * 
 * @param term - [out]拷贝手持机的参数到term中，可以为NULL
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLReadTermInfo(SMART_TERMINAL_T *term)
{
	int ret;
	ret = MBLReadId();
	if(ret)
	{
		return -1;
	}
	ret = MBLReadType();
	if(ret)
	{
		return -1;
	}
	ret = MBLReadDate();
	if(ret)
	{
		return -1;
	}
	if(term != NULL)
	{
		MBLGetTermInfo(term);
	}
	return 0;
}

/** 
 * @brief 将28字节的Buffer分析转换到MBL_TRADE_LOG结构中
 * 
 * @param log - [out]保存流水到这个变量中
 * @param rawData - 输入的流水数据包
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
static int do_format_trade_log(MBL_TRADE_LOG *log,uchar8 *rawData)
{
	uchar8 tmp[7] = "";
	int i;
	int j;
	// 物理ID
	memcpy(log->phyid,rawData,sizeof log->phyid);
	// 通信版本
	log->ver = rawData[4];
	// 启动原因
	log->runreason = rawData[5];
	// 交易流水号
	memset(tmp,0,sizeof tmp);
	do_reverse_buffer(rawData + 6,tmp,2);
	memcpy((char*)&(log->serial_no),tmp,4);
	// 交易卡号
	memset(tmp,0,sizeof tmp);
	do_reverse_buffer(rawData + 8,tmp,3);
	memcpy((char*)&(log->card_id),tmp,4);
	// 交易时间
	memset(tmp,0,sizeof tmp);
	j = 0;
	for (i = 0;i < 6;++i) 
	{
		char c = *(rawData + 11 + i);
		j += sprintf(log->tx_datetime + j,"%.02d",c);
	}
	// 累计使用计数
	memset(tmp,0,sizeof tmp);
	do_reverse_buffer(rawData + 17,tmp,2);
	memcpy((char*)&(log->tx_cnt),tmp,4);
	// 入卡金额
	memset(tmp,0,sizeof tmp);
	memcpy(tmp,rawData + 19,3);
	memcpy((char*)&(log->in_card_amount),tmp,4);
	// 出卡金额
	memset(tmp,0,sizeof tmp);
	memcpy(tmp,rawData + 22,3);
	memcpy((char*)&(log->out_card_amount),tmp,4);
	// 计算交易金额
	log->tx_trade_amount = log->in_card_amount - log->out_card_amount;
	// 交易标记
	log->tx_mark = rawData[25];
	// CRC
	memcpy(log->crc,rawData + 26,2);
	return 0;
}
/** 
 * @brief 上传一条流水
 * 
 * @param log - [out]输出流水
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLUpRecordOne(MBL_TRADE_LOG *log)
{
	uchar8 rawData[28] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	// 上传一条记录
	gs_errno = UpRecordOne(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,rawData
		,gs_term_info.level,gs_term_info.level_array);
	if(gs_errno)
	{
		return -1;
	}
	// TODO: 增加 CRC 校验代码
	gs_errno = do_format_trade_log(log,rawData);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief 结束上传一条流水，该流水将为历史流水
 * 
 * @param serial_no - 流水号
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLEndUpRecordOne(int serial_no)
{
	uchar8 tmp[4] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	memcpy(tmp,(char*)&serial_no,2);
	do_reverse_buffer(tmp,tmp,2);
	gs_errno = EndUpRecordOne(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,tmp,gs_term_info.level
		,gs_term_info.level_array);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief 上传一条历史流水
 * 
 * @param serial_no - 流水号
 * @param log - [out]保存流水数据
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLUpHisBySerial(int serial_no,MBL_TRADE_LOG *log)
{
	uchar8 rawData[28] = "";
	uchar8 tmp[4] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	memcpy(tmp,(char*)&serial_no,2);
	do_reverse_buffer(tmp,tmp,2);
	// 上传一条记录
	gs_errno = UpHisBySerial(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,tmp,rawData
		,gs_term_info.level,gs_term_info.level_array);
	if(gs_errno)
	{
		return -1;
	}
	// TODO: 增加 CRC 校验代码
	gs_errno = do_format_trade_log(log,rawData);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief 设置手持机中的工作密钥，密钥为加密的格式密钥
 * 
 * @param key - 加密格式的密钥，HEX格式，8个字节
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLSetWorkKey(uchar8 *key)
{
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = SetWorkKey(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,key,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}
/** 
 * @brief 设置手持机中的工作密钥，密钥为加密的格式密钥
 * 
 * @param key - 加密格式的密钥，字符串，16个字节
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLSetWorkKey2(const char *key)
{
	int i = 0;
	char tmp[3] = "";
	uchar8 tmpkey[8] = "";
	for (i = 0;i < 16;i+=2)
	{
		strncpy(tmp,key+i,2);
		tmpkey[i/2] = (uchar8)strtoul(tmp,NULL,16);
	}
	return MBLSetWorkKey(tmpkey);
}

/** 
 * @brief 清空手持机中的Flash
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLEmptyFlash()
{
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = EmptyFlash(gs_term_info.port,gs_term_info.termno,gs_term_info.commision
		,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		//初始化成功后清除手持机参数结构
		int port = gs_term_info.port;
		memset(&gs_term_info,0,sizeof gs_term_info);
		gs_term_info.port = port;
		return 0;
	}
	return -1;
}

/** 
 * @brief 设置手持机中的设备授权号
 * 
 * @param commision - 设备授权号,HEX格式,长度4个字节
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLSetCommision(uchar8 *commision)
{
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	//uchar8 tmp[4] = {0x0,0x0,0x8A,0xC6};
	gs_errno = SetCommision(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,commision,gs_term_info.level
		,gs_term_info.level_array);
	if(!gs_errno)
	{
		MBLReadTermInfo(NULL);
		return 0;
	}
	return -1;
}

/** 
 * @brief 设置手持机中的设备授权号
 * 
 * @param commision - 设备授权号，字符串格式,长度为8个字节
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLSetCommision2(const char *commision)
{
	uchar8 commbuf[4] = "";
	char tmp[3] = "";
	int i;
	for (i = 0;i < 8;i+=2)
	{
		strncpy(tmp,commision+i,2);
		commbuf[i/2] = (uchar8)strtoul(tmp,NULL,16);
	}
	return MBLSetCommision(commbuf);
}

/** 
 * @brief 设置设备的物理ID
 * 
 * @param id - 物理ID，HEX格式，4字节
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLWriteId(uchar8 *id)
{
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = WriteId(gs_term_info.port,id,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		memcpy(gs_term_info.phyid,id,sizeof gs_term_info.phyid);
		return 0;
	}
	return -1;
}
/** 
 * @brief 设置设备的物理ID
 * 
 * @param id - 物理ID，字符串格式，8字节
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLWriteId2(const char *id)
{
	uchar8 idbuf[4] = "";
	char tmp[3] = "";
	int i;
	for (i = 0;i < 8;i+=2)
	{
		strncpy(tmp,id+i,2);
		idbuf[i/2] = (uchar8)strtoul(tmp,NULL,16);
	}
	return MBLWriteId(idbuf);
}

/** 
 * @brief 上传手持机设备参数
 * 
 * @param param - [out]设置参数33个字节
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLUserUpParam(uchar8 *param)
{
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = UserUpParam(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,param,gs_term_info.level
		,gs_term_info.level_array);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief 下传黑名单
 * 
 * @param cardid - 交易卡号
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLDownBlackCard(int cardid)
{
	uchar8 buf[3] = "";
	uchar8 tmp[3] = "";
	int num = 1;
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	assert(cardid > 0);
	memcpy(buf,(char*)&cardid,sizeof buf);

	do_reverse_buffer(buf,buf,3);
	gs_errno = DownBlackCard(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,num,buf,gs_term_info.level
		,gs_term_info.level_array);
	if(!gs_errno)
	{
		if(1 == num)
		{
			return 0;
		}
	}
	return -1;
}

/** 
 * @brief 删除黑名单
 * 
 * @param cardid - 交易卡号
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLDownDelBlack(int cardid)
{
	uchar8 buf[3] = "";
	int num = 1;
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	assert(cardid > 0);
	memcpy(buf,(char*)&cardid,sizeof buf);
	do_reverse_buffer(buf,buf,3);
	gs_errno = DownDelBlack(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,num,buf,gs_term_info.level
		,gs_term_info.level_array);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief 删除所有的黑名单
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLDownDelBAll()
{
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = DownDelBAll(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief 下传黑名单版本
 * 
 * @param version - 黑名单版本,12个字节格式,yymmddHHnnss
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLDownBlackVersion(const char *version)
{
	uchar8 verbuf[6] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	do_format_str_2_bcd(verbuf,version,12);
	gs_errno = DownBlackVersion(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,verbuf,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief 上传黑名单版本
 * 
 * @param version - [out]黑名单版本，12个字节,yymmddHHnnss
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLUpBlackVersion(char *version)
{
	uchar8 verbuf[6] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = UpBlackVersion(gs_term_info.port,gs_term_info.termno
		,verbuf,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		do_format_bcd_2_str(version,verbuf,6);
		return 0;
	}
	return -1;
}

/** 
 * @brief 上传黑名单过期日期
 * 
 * @param expire - [out]黑名单过期日期,yymmddHHnnss,目前是到年月有效
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLUpBlackExpire(char *expire)
{
	uchar8 datebuf[6] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = UpBlackExpire(gs_term_info.port,gs_term_info.termno,gs_term_info.commision
		,datebuf,gs_term_info.level,gs_term_info.level_array);

	if(!gs_errno)
	{
		do_hex_2_str(datebuf,expire,6);
		return 0;
	}
	return -1;
}

/** 
 * @brief 下传黑名单过期日期
 * 
 * @param expire - 过期日期，yymmddHHnnss,只有年月有效
 * 
 * @return - 成功返回0，失败返回 -1，MBLGetErrno()取得错误码
 */
int CALLAPI MBLDownBlackExpire(const char *expire)
{
	uchar8 datebuf[6] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	do_str_2_hex(expire,datebuf,12);
	gs_errno = DownBlackExpire(gs_term_info.port,gs_term_info.termno,gs_term_info.commision
		,datebuf,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// CmobiletermApp

BEGIN_MESSAGE_MAP(CmobiletermApp, CWinApp)
END_MESSAGE_MAP()


// CmobiletermApp construction

CmobiletermApp::CmobiletermApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CmobiletermApp object

CmobiletermApp theApp;


// CmobiletermApp initialization

BOOL CmobiletermApp::InitInstance()
{
	CWinApp::InitInstance();
	memset(&gs_term_info,0,sizeof gs_term_info);
	return TRUE;
}


