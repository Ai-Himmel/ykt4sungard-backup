#include "ksdevice.h"
#include "NT_ReaderLib.h"
#include "global_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
static ks_device_op_t g_device_op;
static const char g_version[]="1.00";
static const char g_devname[]="ntcard";
static CNTReader NTReader;
static char gErrMsg[512] = {0};

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
//切换读卡器
static int KSAPI attach(HANDLE hndReader)
{
	NTReader.Attach(hndReader);
}
static HANDLE KSAPI Detach()
{
	NTReader.Detach();
}
static int KSAPI open_device(ks_reader_dev_t *dev)
{
	HANDLE hnd;
	byte cmd[20];
	int ret= NTReader.OpenPort(dev->port,115200);
	if(ret)
	{
		sprintf(gErrMsg, "打开串口 COM%d 失败", dev->port);
		return KS_OPENDEVICE;
	}
	//dev->devhd = NTReader.GetHandle();
	if(NTReader.PowerOn())
	{
		sprintf(gErrMsg, "串口 COM%d 上电失败", dev->port);
		return KS_OPENDEVICE;
	}
	return KS_SUCCESS;

}
// function close_device 
static int KSAPI close_device(ks_reader_dev_t *dev)
{
	NTReader.Close();
	return 0;
}

// function request_card 
static int KSAPI request_card(ks_reader_dev_t *dev,char* phyid,KS_CARD_TYPE t)
{
	int ret;
	char sCardPhyID[17]={0};
	if(!NTReader.IsOpen())
	{
		ret= open_device(dev);
		if(ret)
			return ret;
	}
	NTReader.PowerOff();
	ret = NTReader.RequestCard(sCardPhyID);
	if(ret)
	{
		NTReader.GetErrMsg(ret,gErrMsg);
		return ret;
	}
	//dev->devhd=NTReader.GetHandle();
	strcpy(phyid,sCardPhyID);	
	return 0;
}

// function halt 
static int KSAPI halt(ks_reader_dev_t *dev)
{
	NTReader.PowerOff();
	return 0;
}

// function beep
static int KSAPI beep(ks_reader_dev_t *dev)
{
	return -1;
}
static int KSAPI beeperr(ks_reader_dev_t *dev)
{
	return -1;
}

// function reset
static int KSAPI reset(ks_reader_dev_t *dev,size_t msec)
{
	NTReader.PowerOn();
	return 0;
}
// function login_card 
static int KSAPI login_card(ks_reader_dev_t *dev,ks_card_info_t *card,int sect_no,
							KS_MF_KEYTYPE keytype,const uint8 *key)
{
	return -1;
}

// function read_block 
static int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block)
{
	return -1;
}

// function write_block 
static int KSAPI write_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,const uint8 *block)
{
	return -1;
}

// function decrement_card 
static int KSAPI decrement_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount)
{
	return -1;
}

// function increment_card 
static int KSAPI increment_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount)
{
	return -1;
}

// function transform_card 
static int KSAPI transform_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no)
{
	return -1;
}

// function restore_card 
static int KSAPI restore_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no)
{
	return -1;
}

// function procard_cmd
static int KSAPI procard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd)
{
	return 0;
}

// function cpucard_poweron 
static int KSAPI cpucard_poweron(ks_reader_dev_t *dev,KS_CARD_TYPE t,uint8 *len,uint8 *buf)
{
	NTReader.PowerOn();
	return 0;
}

// function cpucard_setpara 
static int KSAPI cpucard_setpara(ks_reader_dev_t *dev)
{
	return 0;
}

// function cpucard_cmd 
static int KSAPI cpucard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd,KS_CARD_TYPE t)
{
	int ret;
	uint8 sw1,sw2;
	char szCmd[256];
	ks_cpu_cmd_t innerCmd;
	int nRespCode=0;
		// 非接触式
	cmd->cmd_retcode=0;
	if(t == KS_CPUCARD || t == KS_SIMCARD)
	{
		if(dev->cpuport == CARDSLOT_RF)
		{
			if(cmd->cmd_type == 0)
				ret = NTReader.Apdu(cmd->send_buf,cmd->send_len,&nRespCode,cmd->recv_buf,cmd->recv_len);
			else
				ret = NTReader.Apdu4Hex((char*)(cmd->send_buf),cmd->send_len,&nRespCode,cmd->recv_buf,cmd->recv_len);
			if(ret)
			{
				NTReader.GetErrMsg(ret,cmd->cmd_retmsg);
				return KS_CMDERROR;
			}
			sw1 = (nRespCode&0xFF00)>>8;
			sw2 = nRespCode & 0x00FF;
			if(nRespCode!=0)
			{
				cmd->cmd_retcode = nRespCode;
				return cmd->cmd_retcode;
			}
		}
		else return KS_CMDFAILD;
	}
	else
	{
		return KS_CMDFAILD;
	}
	if(sw1 == 0x61 && sw2 != 0x00)
	{
		// 61XX ,调用 00C0 取后续数据
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
	return 0;
}

int KSAPI card_type()
{
	return KS_SIMCARD;
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
	g_device_op.card_type = card_type;

	g_device_op.set_logger = set_logger;

	memcpy(op,&g_device_op,sizeof(ks_device_op_t));
	return 0;
}