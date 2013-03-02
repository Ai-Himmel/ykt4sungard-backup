#ifndef _KSG_SOYAL_PUB_H_
#define _KSG_SOYAL_PUB_H_

#include <ace/OS.h>
#include <ace/SOCK_Stream.h>
#include <ace/Svc_Handler.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Reactor.h>

typedef unsigned char	byte;

namespace SOYALDEV
{
	typedef struct _datetime_str
	{
		byte sec;
		byte min;
		byte hr;
		byte week;
		byte day;
		byte mon;
		byte year;
	} Datetime_str;

	typedef struct  _datapack
	{
		byte head;
		byte len;
		byte destid;
		byte cmdcode;
		byte data[256];
		byte xorchk;
		byte sumchk;
	} DataPack;

	typedef struct _timesec				// 分钟为单位
	{
		short begin_time;				
		short end_time;
	}TimeSec;

	typedef struct _timegroup			// 
	{
		TimeSec sun_timesec;
		TimeSec mon_timesec;
		TimeSec tues_timesec;
		TimeSec wed_timesec;
		TimeSec thur_timesec;
		TimeSec fri_timesec;
		TimeSec sat_timesec;
	}TimeGroup;

	typedef struct _downcard_info
	{
#ifdef KSG_SOYAL_4_BYTE
		byte timezone[65];
#else
		byte timezone[17];				// 每个门的时间段编号
#endif
		byte mapping[3];				// 开门位图(1-16)
		byte expdate[4];				// 过期时间
		char phyno[12];					// 物理卡号
		short cardaddr;					// 卡号占用地址(0-14999)
		bool delflag;					// 删除
	} DownCard_info;

	typedef struct _ctrlmsg				// 门禁事件
	{
		char phyno[12];					// 物理卡号
		char date[9];					// 刷卡日期
		char time[7];					// 刷卡时间
		byte termid;					// 读头号 (1--16)
		byte txmark;					// 事件
	}CtrlMsg;

	int SendRev(ACE_HANDLE handler,DataPack *pDataPack,int datalen,byte *recvbuf,size_t &recvlen);

	int GetMacChk(DataPack *pDataPack,int datalen,byte &xorchk,byte &sumchk);
	int GetSendBuf(DataPack *pDataPack,byte *pBuf,int datalen);

	int ClearCardData(ACE_HANDLE handler,int ctrlid,short cardaddr,bool delall=false);		// 删除卡名单

	int SetCardData(ACE_HANDLE handler,int ctrlid,DownCard_info info,int cardtype);			// 下载卡名单

	int SetGroupSet(ACE_HANDLE handler,int ctrlid,DownCard_info info);			// 设置门组

	int DeleteCtrlMsg(ACE_HANDLE handler,int ctrlid,bool delall=false);			// 删除当前(全部)流水信息

	int ReadCtrlMsg(ACE_HANDLE handler,int ctrlid,CtrlMsg &ctrlmsg,int cardtype);			// 取1条当前流水信息

	int TimeGroupToBuf(TimeGroup timegroup,byte *buf);
	int SetTimeZone(ACE_HANDLE handler,int ctrlid,int zoneidx,int zonelink,TimeGroup timegroup);	// 设置时间段

	int CtrlReader(ACE_HANDLE handler,int ctrlid,int reader,int flag);			// 远程开（关）门

	int SetCtrlTime(ACE_HANDLE handler,int ctrlid,Datetime_str datetime);		// 设置控制器时钟

	int GetCtrlTime(ACE_HANDLE handler,int ctrlid,Datetime_str &datetime);		// 获取控制器时钟

	int CtrlReaderAutoOpen(ACE_HANDLE handler,int ctrlid,int reader,byte cmdcode,byte addrL);			//设置读头在指定的时段自动开门
}


#endif