#include "ksdevice.h"
#include <windows.h>
#include "global_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "logfile.h"
#include "ks_amass_reader.h"

static ks_device_op_t g_device_op;
static const char g_version[]="1.00";
static const char g_devname[]="amass";
static int g_dev_hd = 0;
static char gErrMsg[512];
static int g_cpu_last_slot = -1;
static int g_lastCardType = 0;
static AmassReader g_Reader;

#define SEND_HEAD	0xBA//define the head of the send 
#define RECE_HEAD	0xBD//define the head of the receive

#define GET_DECARD_SLOT(dev,p) do{ int s = get_decard_slot(dev,p); if(s != 0) { strcpy(gErrMsg,"卡座号错误"); return KS_PARAMERR;} }while(0)

/////////////////////////////////////////////////////////////////////
AmassReader::AmassReader()
{
}
AmassReader::~AmassReader()
{
}
bool AmassReader::PostRecv(unsigned char *ppszBuffer, int nBufferSize, long nTimeOut)
{
	assert(ppszBuffer!=NULL);
	char pszBuffer[1024];
	int nReadBytes=0,nDataLen;
	DWORD nResult=0;
	DWORD nStartTime=GetTickCount();
	
	memset(pszBuffer,0,sizeof pszBuffer);
	
	m_nRecvLen=0;
	
	while( (long)(GetTickCount()-nStartTime)<(long)nTimeOut )
	{
		nResult = InWaiting();
		if(nResult == 0) continue;
		nResult = min(nResult,nBufferSize-m_nRecvLen);
		if(Read((unsigned char*)pszBuffer+m_nRecvLen,nResult,nReadBytes))
		{
			if(nReadBytes>0) m_nRecvLen += nReadBytes;
			if(m_nRecvLen>=10) break;
		}
	}
	if( m_nRecvLen<10 ) return false; //超时
	
	nDataLen = pszBuffer[8] * 256 + pszBuffer[9];

	if( m_nRecvLen>=nDataLen + 11 ) //数据已经收完
	{
		memcpy(ppszBuffer,pszBuffer,nDataLen + 11);
		return true;
	}
	
	int nPack=0;	
	nPack=pszBuffer[1];
	nPack=nPack+2-m_nRecvLen;
	while( (long)(GetTickCount()-nStartTime)<(long)nTimeOut )
	{
		nResult = InWaiting();
		nResult = min(nResult,nBufferSize-m_nRecvLen);
		if(Read((unsigned char*)pszBuffer+m_nRecvLen,nResult,nReadBytes))
		{
			if(nReadBytes>0)
			{
				m_nRecvLen += nReadBytes;
				nPack -= nReadBytes;
			}
			if(nPack<=0) break;
		}
	}
	if( nPack>0 ) return false;
	nDataLen = pszBuffer[8] * 256 + pszBuffer[9];
	memcpy(ppszBuffer,pszBuffer,nDataLen + 11);
    return true;
}

/////////////////////////////////////////////////////////////////////
static void SetErrMsg(const char *errmsg,const char *file,int line)
{
	KS_Log_Tracer::instance()->SetTraceFile(file,line);
	KS_Log_Tracer::instance()->TraceMsg(errmsg);
	strncpy(gErrMsg,errmsg,sizeof(gErrMsg)-1);
}
static char* KSAPI GetErrMsg(char *errmsg)
{
	if(errmsg)
		strcpy(errmsg,gErrMsg);
	return gErrMsg;
}
static char* KSAPI GetErrMsgByErrCode(int nErrCode,char* sErrMsg)
{
	int i,found;
	typedef struct 
	{
		unsigned char errCode;
		const char *errMsg;
	}_ErrDef;

	static _ErrDef PCDErr[] = 
	{
		{0,"成功"},
		{0x0001,"返回失败"},
		{0x0011,"卡未启用"},
		{0x0012,"卡有效期已过"},
		{0x0013,"黑名单卡"},
		{0x0014,"错误卡号"},
		{0x0015,"POS流水号不符"},
		{0x0016,"状态错误"},
		{0x0017,"终端拒绝操作"},
	};
	for(i = 0, found = 0;i < sizeof(PCDErr)/sizeof(PCDErr[0]); ++i)
	{
		if(nErrCode == PCDErr[i].errCode)
		{
			sprintf(gErrMsg,"Err-%04X:%s",nErrCode,PCDErr[i].errMsg);
			found = 1;
			break;
		}
	}
	if(!found)
	{
		sprintf(gErrMsg,"Err-%04X: 未知错误",nErrCode);
	}
	if(sErrMsg)
		strcpy(sErrMsg,gErrMsg);
	return gErrMsg;
}
static int SendPOSCMD(const unsigned char *cmd,int cmdlen,unsigned char *recv,unsigned char &recvlen,int timeout=1000)
{
	unsigned char send_cmd[512]={0},xor_value;
	int sendlen = 0,offset,rc;
	sendlen = 8;
	memcpy(send_cmd,"\x0F\x0F\xAB\xAB\xFF\xFF\x00\x00",sendlen);
	send_cmd[sendlen++] = cmdlen/256;
	send_cmd[sendlen++] = cmdlen % 256;
	memcpy(send_cmd+sendlen,cmd,cmdlen);
	sendlen += cmdlen;
	send_cmd[sendlen++] = calc_xor(send_cmd+4,cmdlen+6);
	
	if(!g_Reader.PostSend(send_cmd,sendlen,timeout))
	{
		TRACE_ERR("发送数据包失败");
		return -1;
	}
	if(!g_Reader.PostRecv(send_cmd,256,timeout))
	{
		TRACE_ERR("接收数据包失败");
		return -1;
	}
	if(memcmp(send_cmd,"\x0F\x0F\xAB\xAB",4) != 0)
	{
		TRACE_ERR("接收到数据包格式错误");
		return -1;
	}
	sendlen = send_cmd[8] * 256 + send_cmd[9];
	xor_value = calc_xor(send_cmd+4,sendlen+6);
	offset = 10;
	if(xor_value != send_cmd[sendlen+offset])
	{
		TRACE_ERR("数据校验不合法");
		return -1;
	}
	if(cmd[0] != send_cmd[offset])
	{
		TRACE_ERR("数据包命令字不符");
		return -1;
	}
	
	rc = send_cmd[offset+1] * 256 + send_cmd[offset+2];
	if(rc)
		return rc;
	recvlen = sendlen-3;
	memcpy(recv,send_cmd+offset+3,recvlen);
	return 0;
}

// function open_device
static int KSAPI open_device(ks_reader_dev_t *dev)
{
	BOOL ret;
	char sCom[64]={0};
	sprintf(sCom,"\\\\.\\COM%d",dev->port);
	if(g_Reader.Open(sCom,115200) == false)
	{
		TRACE_ERR("打开读卡器端口失败,port["<<dev->port<<"]");
		return KS_OPENDEVICE;
	}
	g_dev_hd = 1;
	return 0;
}
// function close_device 
static int KSAPI close_device(ks_reader_dev_t *dev)
{
	if(g_dev_hd)
	{
		g_Reader.Close();
	}
	g_dev_hd = 0;
	return 0;
}

static int get_decard_slot(ks_reader_dev_t *dev,int SAMID)
{
	int slot = 100;
	unsigned char atr[256]={0},cmd[64]={0};
	unsigned char rlen,ret;
	switch(SAMID)
	{
	case CARDSLOT_1:
		slot = 1;
		break;
	case CARDSLOT_2:
		slot = 2;
		break;
	case CARDSLOT_3:
		slot = 3;
		break;
	default:
		slot = 100;
		break;
	}
	if(slot == 100)
		return KS_PARAMERR;
	if(g_cpu_last_slot != slot)
	{
		rlen = 4;
		memcpy(cmd,"\x40\x00\x00\x00",rlen);
		cmd[1] = (unsigned char)slot;
		ret = SendPOSCMD(cmd,rlen,atr,rlen);
		if(ret)
		{
			TRACE_ERR("PSAM卡复位错误");
			return KS_OPENDEVICE;
		}
		g_cpu_last_slot = slot;
	}
	return 0;
}

static int KSAPI reset(ks_reader_dev_t *dev,size_t msec);
// function request_card 
static int KSAPI request_card(ks_reader_dev_t *dev,char* phyid,KS_CARD_TYPE t)
{
	int ret;
	
	uint8 ucCardPhyID[8];
	uint8 rData[256],cmd[128],rlen;
	
	if(!g_dev_hd)
	{
		ret=open_device(dev);
		if(ret)
			return ret;
	}
	if(!g_dev_hd)
	{
		return KS_PORT_NOTOPEN;
	}
	if(t == KS_CPUCARD || t == KS_FIXCARD)
	{
		if(dev->cpuport == CARDSLOT_RF)
		{
			//if(g_lastCardType == KS_CPUCARD || g_lastCardType == KS_FIXCARD)
			{
				reset(dev,100);
			}
			rlen = 2;
			memcpy(cmd,"\x4F\x04",rlen);
			ret=SendPOSCMD(cmd,rlen,rData,rlen);
			if(ret)
			{
				TRACE_ERR("选卡错误");
				return KS_REQUESTCARD;

			}
			// 卡类型
			// rData[0]
            unsigned char i;
			for(i = 0;i < 4; ++i)
				ucCardPhyID[i] = rData[4-i];

			g_lastCardType = KS_CPUCARD;
			dev->cardtype = g_lastCardType;
			
			dec2hex(ucCardPhyID,4,phyid);
			phyid[8]=0;	
		}
		else
		{
			TRACE_ERR("输入参数错误");
			return KS_REQUESTCARD;
		}
	}
	else
	{
		TRACE_ERR("输入参数错误");
		return KS_REQUESTCARD;
	}
	return 0;
}

// function halt 
static int KSAPI halt(ks_reader_dev_t *dev)
{
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;
	// halt 
	return KS_NOTSUPPORT;
}

static void do_beep(ks_reader_dev_t *dev,unsigned char t)
{
	unsigned char cmd[64],rlen;
	rlen = 3;
	memcpy(cmd,"\x4F\x06\x01",rlen);
	t = (t > 10) ? 10 : t;
	cmd[2] = t;
	SendPOSCMD(cmd,rlen,cmd,rlen,100);
}
// function beep
static int KSAPI beep(ks_reader_dev_t *dev)
{
	if(!g_dev_hd)
	{
        int ret=0;
		ret=open_device(dev);
		if(ret)
			return ret;
	}
	do_beep(dev,1);
	return 0;
}
static int KSAPI beeperr(ks_reader_dev_t *dev)
{
	if(!g_dev_hd)
	{
        int ret=0;
		ret=open_device(dev);
		if(ret)
			return ret;
	}
	do_beep(dev,3);
	return 0;
}
// function login_card 
static int KSAPI login_card(ks_reader_dev_t *dev,ks_card_info_t *card,int sect_no,
							KS_MF_KEYTYPE keytype,const uint8 *key)
{
	uint8 mode;
	if(keytype == MF_KEYA)
	{
		mode = 0;
	}
	else 
	{
		mode = 1;
	}
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;

	return KS_NOTSUPPORT;
}

// function read_block 
static int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block)
{
	// TODO : 根据卡类型判断，只能处理32个扇区之前的
	if(block_no >= 32*4 || block_no < 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;

	return KS_NOTSUPPORT;
}

// function write_block 
static int KSAPI write_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,const uint8 *block)
{
	// TODO : 根据卡类型判断，只能处理32个扇区之前的
	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;

	return KS_NOTSUPPORT;
}

// function decrement_card 
static int KSAPI decrement_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount)
{
	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;
	return KS_NOTSUPPORT;
}

// function increment_card 
static int KSAPI increment_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount)
{
	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;
	return KS_NOTSUPPORT;
}

// function transform_card 
static int KSAPI transform_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no)
{

	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;
	return KS_NOTSUPPORT;
}

// function restore_card 
static int KSAPI restore_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no)
{
	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;

	return KS_NOTSUPPORT;
}

// function procard_cmd
static int KSAPI procard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd)
{
	return 0;
}

// function cpucard_poweron 
static int KSAPI cpucard_poweron(ks_reader_dev_t *dev,KS_CARD_TYPE t,uint8 *len,uint8 *buf)
{
	unsigned char cmd[64];
	unsigned char cmdlen;
	int ret;
	if(!g_dev_hd)
	{
		ret=open_device(dev);
		if(ret)
			return ret;
	}

	if( t == KS_MFCARD) // mifare card
		return KS_NOTSUPPORT;
	else if(t == KS_CPUCARD || t == KS_FIXCARD)
	{
		if(dev->cpuport == CARDSLOT_RF)
		{
			//ret = IccPowerUp(buf,*len); // cpucard
			cmdlen = 2;
			memcpy(cmd,"\x4F\x00",cmdlen);
			ret = SendPOSCMD(cmd,cmdlen,buf,*len);
			if(ret)
			{
				TRACE_ERR("ATS错误");
			}
		}
		else
		{
			return KS_NOTSUPPORT;
		}
	}
	else
	{
		//TODO: SAM 复位
		
		GET_DECARD_SLOT(dev,dev->cpuport);
		cmdlen = 2;
		memcpy(cmd,"\x4F\x01",cmdlen);
		ret = SendPOSCMD(cmd,cmdlen,buf,*len);
	}
	if(ret)
	{
		GetErrMsgByErrCode(ret,gErrMsg);
		return KS_OPENDEVICE;
	}
	return 0;
}


// function reset
static int KSAPI reset(ks_reader_dev_t *dev,size_t msec)
{
	int ret=0;
	unsigned char rlen;
	unsigned char rdata[64],cmd[64];
	if(!g_dev_hd)
	{
		ret=open_device(dev);
		if(ret)
			return ret;
	}
	if(dev->cpuport == CARDSLOT_RF)
	{
		rlen=2;
		// DSELECT
		memcpy(cmd,"\x4F\x05",rlen);
		ret = SendPOSCMD(cmd,rlen,rdata,rlen);
		if(ret)
		{
			GetErrMsgByErrCode(ret,gErrMsg);
			return KS_OPENDEVICE;
		}
	}
	else
	{
		ret = cpucard_poweron(dev,KS_CPUCARD,&rlen,rdata);
	}
	return 0;
}


// function cpucard_setpara 
static int KSAPI cpucard_setpara(ks_reader_dev_t *dev)
{
	int ret;
	if(!g_dev_hd)
	{
		ret=open_device(dev);
		if(ret)
			return ret;
	}

	g_cpu_last_slot = -1;
	GET_DECARD_SLOT(dev,dev->cpuport);
	return 0;
}

// function cpucard_cmd 
static int KSAPI cpucard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd,KS_CARD_TYPE t)
{
	int ret = -1;
	uint8 sw1,sw2;
	char szCmd[256];
	unsigned char ucCmd[512];
	unsigned char recvlen = 0;
	ks_cpu_cmd_t innerCmd;
	cmd->cmd_retcode=0;
	assert(dev != NULL);
	if(!g_dev_hd)
	{
		strcpy(gErrMsg,"读卡器端口未打开");
		strcpy(cmd->cmd_retmsg,gErrMsg);
		return KS_PORT_NOTOPEN;
	}
	
	if(t == KS_CPUCARD || t == KS_FIXCARD)
	{
		// 非接触式
		if(dev->cpuport == CARDSLOT_RF)
		{
			if(cmd->cmd_type == 0)
			{
				memcpy(ucCmd,"\x4F\x02",2);
				memcpy(ucCmd+2,cmd->send_buf,cmd->send_len);
				ret = SendPOSCMD(ucCmd,cmd->send_len+2,cmd->recv_buf,recvlen,3000);
				cmd->recv_len = recvlen;
			}
			else
			{
				
				int  iCmdLen=0;
				memcpy(ucCmd,"\x4F\x02",2);
				hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd+2,iCmdLen);
				ret = SendPOSCMD(ucCmd,iCmdLen+2,cmd->recv_buf,recvlen,3000);
				cmd->recv_len = recvlen;
			}
		}
		else
		{
			return KS_NOTSUPPORT;
		}
	}
	else
	{
		// 接触式
		if(dev->cpuport == CARDSLOT_RF)
		{
			return KS_CMDERROR;
		}
		else
		{
			GET_DECARD_SLOT(dev,dev->cpuport);
			
			if(cmd->cmd_type == 0)
			{
				memcpy(ucCmd,"\x4F\x03",2);
				memcpy(ucCmd+2,cmd->send_buf,cmd->send_len);
				ret = SendPOSCMD(ucCmd,cmd->send_len+2,cmd->recv_buf,recvlen);
				cmd->recv_len = recvlen;
			}
			else
			{
				int  iCmdLen=0;
				memcpy(ucCmd,"\x4F\x03",2);
				hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd+2,iCmdLen);
				ret = SendPOSCMD(ucCmd,iCmdLen+2,cmd->recv_buf,recvlen);
				cmd->recv_len = recvlen;
			}
		}
	}

	
	if(ret)
	{
		if(cmd->recv_len <= 0)
		{
			TRACE_ERR("执行指令错误，但没有返回数据,ret["<<ret<<"]");
			return -1;
		}
	}
	sw1 = cmd->recv_buf[cmd->recv_len-2];
	sw2 = cmd->recv_buf[cmd->recv_len-1];
	if(sw1 != 0x90 && sw1 != 0x61)
	{
		ret = sw1;
		ret = ret*256 + sw2;
		cmd->cmd_retcode = ret;
		TRACE_ERR("执行指令返回状态错误,sw["<<std::hex<<(int)sw1<<" "<<(int)sw2<<"]");
		return cmd->cmd_retcode;
	}
	if(sw1 == 0x61 && sw2 != 0x00)
	{
		// 61XX ,调用 00C0 取后续数据
		TRACE_ERR("自动获取后续数据");
		memset(&innerCmd,0,sizeof innerCmd);
		innerCmd.send_len = sprintf(szCmd,"00C00000%02X",sw2);
		innerCmd.send_buf = (unsigned char*)szCmd;
		innerCmd.recv_buf = cmd->recv_buf;
		innerCmd.cmd_type = 1; // 16 hex
		ret = cpucard_cmd(dev,&innerCmd,t);
		if(ret==0)
		{
			cmd->recv_len = innerCmd.recv_len;
		}
		cmd->cmd_retcode = innerCmd.cmd_retcode;
		return ret;
	}
	return 0;
}

int KSAPI config_card(ks_reader_dev_t *dev,KS_CPUCARD_TYPE t)
{
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;
	return 0;
}

//////////////////////////////////////////////////////////////
//
int KSAPI card_type()
{
	return g_lastCardType;
}
void KSAPI set_logger(void *para)
{
	KS_Log_Tracer::instance((KS_Log_Tracer*)para);
}

int KSAPI register_device_op(ks_device_op_t *op)
{
	g_device_op.version = g_version;
	g_device_op.devname = g_devname;
	// 接口函数

	g_device_op.open_device=open_device;

	g_device_op.close_device=close_device;

	g_device_op.request_card=request_card;

	g_device_op.halt=halt;

	g_device_op.beep=beep;

	g_device_op.beeperr=beeperr;

	g_device_op.reset=reset;

	g_device_op.login_card=login_card;

	g_device_op.read_block=read_block;

	g_device_op.write_block=write_block;

	g_device_op.decrement_card=decrement_card;

	g_device_op.increment_card=increment_card;

	g_device_op.transform_card=transform_card;

	g_device_op.restore_card=restore_card;

	g_device_op.procard_cmd = procard_cmd;

	g_device_op.cpucard_poweron=cpucard_poweron;

	g_device_op.cpucard_setpara=cpucard_setpara;

	g_device_op.cpucard_cmd=cpucard_cmd;

	g_device_op.config_card=config_card;

	g_device_op.GetErrMsg=GetErrMsg;

	g_device_op.card_type=card_type;

	g_device_op.set_logger = set_logger;

	memcpy(op,&g_device_op,sizeof(ks_device_op_t));
	return 0;

}
