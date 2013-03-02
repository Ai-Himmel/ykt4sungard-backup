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

	typedef struct _timesec				// ����Ϊ��λ
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
		byte timezone[17];				// ÿ���ŵ�ʱ��α��
#endif
		byte mapping[3];				// ����λͼ(1-16)
		byte expdate[4];				// ����ʱ��
		char phyno[12];					// ������
		short cardaddr;					// ����ռ�õ�ַ(0-14999)
		bool delflag;					// ɾ��
	} DownCard_info;

	typedef struct _ctrlmsg				// �Ž��¼�
	{
		char phyno[12];					// ������
		char date[9];					// ˢ������
		char time[7];					// ˢ��ʱ��
		byte termid;					// ��ͷ�� (1--16)
		byte txmark;					// �¼�
	}CtrlMsg;

	int SendRev(ACE_HANDLE handler,DataPack *pDataPack,int datalen,byte *recvbuf,size_t &recvlen);

	int GetMacChk(DataPack *pDataPack,int datalen,byte &xorchk,byte &sumchk);
	int GetSendBuf(DataPack *pDataPack,byte *pBuf,int datalen);

	int ClearCardData(ACE_HANDLE handler,int ctrlid,short cardaddr,bool delall=false);		// ɾ��������

	int SetCardData(ACE_HANDLE handler,int ctrlid,DownCard_info info,int cardtype);			// ���ؿ�����

	int SetGroupSet(ACE_HANDLE handler,int ctrlid,DownCard_info info);			// ��������

	int DeleteCtrlMsg(ACE_HANDLE handler,int ctrlid,bool delall=false);			// ɾ����ǰ(ȫ��)��ˮ��Ϣ

	int ReadCtrlMsg(ACE_HANDLE handler,int ctrlid,CtrlMsg &ctrlmsg,int cardtype);			// ȡ1����ǰ��ˮ��Ϣ

	int TimeGroupToBuf(TimeGroup timegroup,byte *buf);
	int SetTimeZone(ACE_HANDLE handler,int ctrlid,int zoneidx,int zonelink,TimeGroup timegroup);	// ����ʱ���

	int CtrlReader(ACE_HANDLE handler,int ctrlid,int reader,int flag);			// Զ�̿����أ���

	int SetCtrlTime(ACE_HANDLE handler,int ctrlid,Datetime_str datetime);		// ���ÿ�����ʱ��

	int GetCtrlTime(ACE_HANDLE handler,int ctrlid,Datetime_str &datetime);		// ��ȡ������ʱ��

	int CtrlReaderAutoOpen(ACE_HANDLE handler,int ctrlid,int reader,byte cmdcode,byte addrL);			//���ö�ͷ��ָ����ʱ���Զ�����
}


#endif