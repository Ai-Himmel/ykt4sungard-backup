// mobileterm.cpp : Defines the initialization routines for the DLL.
//
/** 
 * ģ����						39�ֳֻ���
 * �ļ���						mobileterm.cpp
 * �ļ�ʵ�ֹ���					39�ֳֻ��������װ
 * ����							����
 * �汾							V0.1
 * ����							2005-10-19
 * ��ע
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
// ��д�Ľӿں���
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
 * @brief �������
 */
static int gs_errno = 0;
/** 
 * @brief �����Ƿ�� ��1��ʾ�Ѵ� 0��ʾδ��
 */
static int gs_com_is_open = 0;

/** 
 * @brief ��������������Ϣ��Ӧ�ṹ����
 */
struct err_msg_no_def {
	int err_no;
	char *err_msg;
};
/** 
 * @brief ��ǰ���ӵ��ֳֻ��豸
 */
static SMART_TERMINAL_T gs_term_info;

/** 
 * @brief ȫ�ִ�������������Ϣ����
 */
static struct err_msg_no_def gs_msg_def[]=
{
	{-1,"���ݳ��Ȳ���ֵ̫�����ڸ�ֵ,"},
	{-2,"�������ݴ�����û�д򿪼�ͨѶ��"},
	{-3,"�������ݴ�����û�д򿪼�ͨѶ��"},
	{-4,"�������ݳ�ʱ;"},
	{-5,"���ص�ַ��ƥ��"},
	{-6,"�ն��޷�Ӧ"},
	{-7,"���ڴ�/�رմ�"},
	{-8,"�������ݳ��ȴ���"},
	{-9,"����У���"},
	{-10,"���������"},
	{0,"�ɹ�"},
	{1,"�Ƿ���"},
	{2,"ʱ�Ӵ�"},
	{3,"Ǯ����ʽ��"},
	{4,"������"},
	{5,"��ˮ�Ŵ�"},
	{7,"���������"},
	{8,"�޴�����������޷���ʱʹ��"},
	{9,"�ظ�����"},
	{10,"�޼�¼������"},
	{11,"��Ȩ�Ų���"},
	{13,"����ǩ��"},
	{14,"��������Ч�ڹ���"},
	{15,"���ڽ���"},
	{17,"���м�¼δ�ռ�"},
	{18,"��ʹ�ô�������"},
	{19,"��Ƭ�ѹ���Ч��"},
	{20,"��Ƭ���̫��"},
	{22,"�ѽ��ʵĽ�����ˮ�ѱ�����(�޷�����)"},
	{23,"���н��˼�¼δ�ϴ�"},
	{24,"�豸δ��Ȩ�޷�ǩ��"},
	{E_COM_NOT_OPEN,"����δ��"},
	{E_LOAD_SMARTCOM,"����SmartCom411SCJʧ��!"},
	{E_COM_BAND,"���ڲ����ʲ���ȷ"},
	{E_SMART_TERM_NO,"���ŷ�Χ����ȷ"},
	{E_SMART_TERM_INFO,"δ��ȡ�ֳֻ�����"},
	{0xFFFF,""}
};

/** 
 * @brief ȡ����һ�ε��ú�Ĵ������
 * 
 * @return - �������
 */
int CALLAPI MBLGetErrno()
{
	return gs_errno;
}
/** 
 * @brief ȡ����һ�ε��ú�Ĵ�����Ϣ
 * 
 * @param msg - [out] ������Ϣ
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
	strcpy(msg,"һ���Դ���");
}
/** 
 * @brief ��ʾ��һ�ε��õĴ�����Ϣ
 * 
 */
void CALLAPI MBLShowErrMsg()
{
	char tmp[512] = "";
	MBLGetErrMsg(tmp);
	AfxMessageBox(tmp);
}
/** 
 * @brief ����ȫ�ֲ���
 */
static void do_reset_params()
{
	gs_com_is_open = 0;
	gs_has_key = 0;
	memset(&gs_term_info,0,sizeof gs_term_info);
}

/** 
 * @brief ��Buffer�ߵ�λ����
 * 
 * @param inbuf - ����buffer
 * @param outbuf - [out]����������buffer
 * @param buflen - ����buffer�ĳ���
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
 * @brief ȡ�õ�ǰ�ֳֻ��Ĳ���
 * 
 * @param term - [out]�ֳֻ��ṹ
 * 
 */
void CALLAPI MBLGetTermInfo(SMART_TERMINAL_T *term)
{
	memcpy(term,&gs_term_info,sizeof(SMART_TERMINAL_T));
}

/** 
 * @brief �򿪴���
 * 
 * @param port - ���ں�,��1��ʼ
 * @param band - ������,ʹ��19200
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �رմ���
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief - ȡ���ֳֻ�����ID �� ����
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
 */
int CALLAPI MBLReadId()
{
	uchar8 rawData[5] = "";
	VALIDATE_COM;
	gs_errno = ReadId(gs_term_info.port,rawData,gs_term_info.level
		,gs_term_info.level_array);
	if(!gs_errno)
	{
		// ����ID
		memcpy(gs_term_info.phyid,rawData,sizeof gs_term_info.phyid);
		// ����
		gs_term_info.termno = rawData[4];
		// ��Ȩ��
		memcpy(gs_term_info.commision,gs_term_info.phyid,sizeof gs_term_info.commision);
		return 0;
	}
	return -1;
}

/** 
 * @brief - �����ֳֻ���
 * 
 * @param id - Ҫ���õĻ���
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief - ��BCDת�����ַ���
 * 
 * @param outstr - [out]���ת�����ַ���
 * @param inbuf - ����BCD��
 * @param buflen  - ���볤��
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
 * @brief ���ַ���ת����BCD��
 * 
 * @param outbuf - [out]�����BCD��
 * @param instr - ����Ҫת�����ַ���
 * @param inlen - Ҫת�����ַ�������
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
 * @brief ��Hexת�����ַ���
 * 
 * @param inbuf - Ҫת�����ַ���HEX��ʽ
 * @param outstr - [out]ת����������ַ���
 * @param inlen - Ҫת�����ַ�������, �����buf��СҪ���ڵ���inlen+1
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
 * @brief ���ַ���ת����HEX��ʽ
 * 
 * @param instr - ����Ҫת�����ַ���
 * @param outbuf - ���HEX��ʽ���ַ���
 * @param inlen - Ҫת�����ַ������ȣ����buf����Ϊoutbuf / 2
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
 * @brief ��ȡ�ֳֻ�����汾
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief ��ȡ�ֳֻ����ʹ���
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief ��ȡ�ֳֻ��Ĳ�������������ID�����ͣ����ţ�����汾�������浽ȫ�ֱ�����
 * 
 * @param term - [out]�����ֳֻ��Ĳ�����term�У�����ΪNULL
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief ��28�ֽڵ�Buffer����ת����MBL_TRADE_LOG�ṹ��
 * 
 * @param log - [out]������ˮ�����������
 * @param rawData - �������ˮ���ݰ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
 */
static int do_format_trade_log(MBL_TRADE_LOG *log,uchar8 *rawData)
{
	uchar8 tmp[7] = "";
	int i;
	int j;
	// ����ID
	memcpy(log->phyid,rawData,sizeof log->phyid);
	// ͨ�Ű汾
	log->ver = rawData[4];
	// ����ԭ��
	log->runreason = rawData[5];
	// ������ˮ��
	memset(tmp,0,sizeof tmp);
	do_reverse_buffer(rawData + 6,tmp,2);
	memcpy((char*)&(log->serial_no),tmp,4);
	// ���׿���
	memset(tmp,0,sizeof tmp);
	do_reverse_buffer(rawData + 8,tmp,3);
	memcpy((char*)&(log->card_id),tmp,4);
	// ����ʱ��
	memset(tmp,0,sizeof tmp);
	j = 0;
	for (i = 0;i < 6;++i) 
	{
		char c = *(rawData + 11 + i);
		j += sprintf(log->tx_datetime + j,"%.02d",c);
	}
	// �ۼ�ʹ�ü���
	memset(tmp,0,sizeof tmp);
	do_reverse_buffer(rawData + 17,tmp,2);
	memcpy((char*)&(log->tx_cnt),tmp,4);
	// �뿨���
	memset(tmp,0,sizeof tmp);
	memcpy(tmp,rawData + 19,3);
	memcpy((char*)&(log->in_card_amount),tmp,4);
	// �������
	memset(tmp,0,sizeof tmp);
	memcpy(tmp,rawData + 22,3);
	memcpy((char*)&(log->out_card_amount),tmp,4);
	// ���㽻�׽��
	log->tx_trade_amount = log->in_card_amount - log->out_card_amount;
	// ���ױ��
	log->tx_mark = rawData[25];
	// CRC
	memcpy(log->crc,rawData + 26,2);
	return 0;
}
/** 
 * @brief �ϴ�һ����ˮ
 * 
 * @param log - [out]�����ˮ
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
 */
int CALLAPI MBLUpRecordOne(MBL_TRADE_LOG *log)
{
	uchar8 rawData[28] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	// �ϴ�һ����¼
	gs_errno = UpRecordOne(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,rawData
		,gs_term_info.level,gs_term_info.level_array);
	if(gs_errno)
	{
		return -1;
	}
	// TODO: ���� CRC У�����
	gs_errno = do_format_trade_log(log,rawData);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief �����ϴ�һ����ˮ������ˮ��Ϊ��ʷ��ˮ
 * 
 * @param serial_no - ��ˮ��
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �ϴ�һ����ʷ��ˮ
 * 
 * @param serial_no - ��ˮ��
 * @param log - [out]������ˮ����
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
 */
int CALLAPI MBLUpHisBySerial(int serial_no,MBL_TRADE_LOG *log)
{
	uchar8 rawData[28] = "";
	uchar8 tmp[4] = "";
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	memcpy(tmp,(char*)&serial_no,2);
	do_reverse_buffer(tmp,tmp,2);
	// �ϴ�һ����¼
	gs_errno = UpHisBySerial(gs_term_info.port,gs_term_info.termno
		,gs_term_info.commision,tmp,rawData
		,gs_term_info.level,gs_term_info.level_array);
	if(gs_errno)
	{
		return -1;
	}
	// TODO: ���� CRC У�����
	gs_errno = do_format_trade_log(log,rawData);
	if(!gs_errno)
	{
		return 0;
	}
	return -1;
}

/** 
 * @brief �����ֳֻ��еĹ�����Կ����ԿΪ���ܵĸ�ʽ��Կ
 * 
 * @param key - ���ܸ�ʽ����Կ��HEX��ʽ��8���ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �����ֳֻ��еĹ�����Կ����ԿΪ���ܵĸ�ʽ��Կ
 * 
 * @param key - ���ܸ�ʽ����Կ���ַ�����16���ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief ����ֳֻ��е�Flash
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
 */
int CALLAPI MBLEmptyFlash()
{
	VALIDATE_COM;
	VALIDATE_TERM_INFO;
	gs_errno = EmptyFlash(gs_term_info.port,gs_term_info.termno,gs_term_info.commision
		,gs_term_info.level,gs_term_info.level_array);
	if(!gs_errno)
	{
		//��ʼ���ɹ�������ֳֻ������ṹ
		int port = gs_term_info.port;
		memset(&gs_term_info,0,sizeof gs_term_info);
		gs_term_info.port = port;
		return 0;
	}
	return -1;
}

/** 
 * @brief �����ֳֻ��е��豸��Ȩ��
 * 
 * @param commision - �豸��Ȩ��,HEX��ʽ,����4���ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �����ֳֻ��е��豸��Ȩ��
 * 
 * @param commision - �豸��Ȩ�ţ��ַ�����ʽ,����Ϊ8���ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �����豸������ID
 * 
 * @param id - ����ID��HEX��ʽ��4�ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �����豸������ID
 * 
 * @param id - ����ID���ַ�����ʽ��8�ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �ϴ��ֳֻ��豸����
 * 
 * @param param - [out]���ò���33���ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �´�������
 * 
 * @param cardid - ���׿���
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief ɾ��������
 * 
 * @param cardid - ���׿���
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief ɾ�����еĺ�����
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �´��������汾
 * 
 * @param version - �������汾,12���ֽڸ�ʽ,yymmddHHnnss
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �ϴ��������汾
 * 
 * @param version - [out]�������汾��12���ֽ�,yymmddHHnnss
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �ϴ���������������
 * 
 * @param expire - [out]��������������,yymmddHHnnss,Ŀǰ�ǵ�������Ч
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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
 * @brief �´���������������
 * 
 * @param expire - �������ڣ�yymmddHHnnss,ֻ��������Ч
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1��MBLGetErrno()ȡ�ô�����
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


