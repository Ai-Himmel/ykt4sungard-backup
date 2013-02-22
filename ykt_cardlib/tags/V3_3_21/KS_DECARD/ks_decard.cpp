#include "ksdevice.h"
#include "dcrf32.h"
#include "global_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "logfile.h"

static ks_device_op_t g_device_op;
static const char g_version[]="1.10";
static const char g_devname[]="decard";
static int g_cpu_last_slot = CARDSLOT_RF + 1;
static int m_Reader = 0;
static HANDLE g_dev_hd = 0;
static int g_lastCardType = 0;

static char gErrMsg[256] = {0};

#define GET_DECARD_SLOT(dev,p) do{ int s = get_decard_slot(dev,p); if(s != 0) { strcpy(gErrMsg,"卡座号错误"); return KS_PARAMERR;} }while(0)

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
	switch(nErrCode)
	{
	case -0x10:
		sprintf(gErrMsg,"Err-%04X:通讯错误",nErrCode);
		break;
	case -0x11:
		sprintf(gErrMsg,"Err-%04X:超时错误",nErrCode);
		break;
	case -0x20:
		sprintf(gErrMsg,"Err-%04X:打开端口错误",nErrCode);
		break;
	case -0x21:
		sprintf(gErrMsg,"Err-%04X:获得端口参数错误",nErrCode);
		break;
	case -0x22:
		sprintf(gErrMsg,"Err-%04X:设置端口参数错误",nErrCode);
		break;
	case -0x23:
		sprintf(gErrMsg,"Err-%04X:关闭端口出错",nErrCode);
		break;
	case -0x24:
		sprintf(gErrMsg,"Err-%04X:端口被占用",nErrCode);
		break;
	case -0x30:
		sprintf(gErrMsg,"Err-%04X:格式错误",nErrCode);
		break;
	case -0x31:
		sprintf(gErrMsg,"Err-%04X:数据格式错误",nErrCode);
		break;
	case -0x32:
		sprintf(gErrMsg,"Err-%04X:数据长度错误",nErrCode);
		break;
	case -0x40:
		sprintf(gErrMsg,"Err-%04X:读错误",nErrCode);
		break;
	case -0x41:
		sprintf(gErrMsg,"Err-%04X:写错误",nErrCode);
		break;
	case -0x42:
		sprintf(gErrMsg,"Err-%04X:无接收错误",nErrCode);
		break;
	case -0x50:
		sprintf(gErrMsg,"Err-%04X:不够减错误",nErrCode);
		break;
	case -0x51:
		sprintf(gErrMsg,"Err-%04X:CPU数据异或和错误",nErrCode);
		break;
	case -0x52:
		sprintf(gErrMsg,"Err-%04X:485通讯时地址号错误",nErrCode);
		break;
	case -0x73:
		sprintf(gErrMsg,"Err-%04X:取版本号错误",nErrCode);
		break;
	case -0xc2:
		sprintf(gErrMsg,"Err-%04X:CPU卡响应错误",nErrCode);
		break;
	case -0xd3:
		sprintf(gErrMsg,"Err-%04X:CPU卡响应超时",nErrCode);
		break;
	case -0xd6:
		sprintf(gErrMsg,"Err-%04X:CPU卡校验错误",nErrCode);
		break;
	case -0xd7:
		sprintf(gErrMsg,"Err-%04X:CPU卡命令过程字错误",nErrCode);
		break;
//////////////////////////////////////////////////////////////////
	case 0x01:
		sprintf(gErrMsg,"Err-%04X:未放置卡片或认证错误",nErrCode);
		break;
	case 0x02:
		sprintf(gErrMsg,"Err-%04X:数据校验错误",nErrCode);
		break;
	case 0x03:
		sprintf(gErrMsg,"Err-%04X:数值为空错误",nErrCode);
		break;
	case 0x04:
		sprintf(gErrMsg,"Err-%04X:认证失败",nErrCode);
		break;
	case 0x05:
		sprintf(gErrMsg,"Err-%04X:奇偶校验错误",nErrCode);
		break;
	case 0x06:
		sprintf(gErrMsg,"Err-%04X:读写设备与卡片通讯错误",nErrCode);
		break;
	case 0x08:
		sprintf(gErrMsg,"Err-%04X:读卡序列号错误",nErrCode);
		break;
	case 0x09:
		sprintf(gErrMsg,"Err-%04X:密码类型错误",nErrCode);
		break;
	case 0x0a:
		sprintf(gErrMsg,"Err-%04X:卡片尚未被认证",nErrCode);
		break;
	case 0x0b:
		sprintf(gErrMsg,"Err-%04X:读卡操作比特数错误",nErrCode);
		break;
	case 0x0c:
		sprintf(gErrMsg,"Err-%04X:读卡操作字节数错误",nErrCode);
		break;
	case 0x0f:
		sprintf(gErrMsg,"Err-%04X:写卡操作失败",nErrCode);
		break;
	case 0x10:
		sprintf(gErrMsg,"Err-%04X:增值操作失败",nErrCode);
		break;
	case 0x11:
		sprintf(gErrMsg,"Err-%04X:减值操作失败",nErrCode);
		break;
	case 0x12:
		sprintf(gErrMsg,"Err-%04X:读卡操作失败",nErrCode);
		break;
	case 0x13:
		sprintf(gErrMsg,"Err-%04X:传输缓冲区溢出",nErrCode);
		break;
	case 0x15:
		sprintf(gErrMsg,"Err-%04X:传输帧错误",nErrCode);
		break;
	case 0x17:
		sprintf(gErrMsg,"Err-%04X:未知的传输需求",nErrCode);
		break;
	case 0x18:
		sprintf(gErrMsg,"Err-%04X:防冲突错误",nErrCode);
		break;
	case 0x19:
		sprintf(gErrMsg,"Err-%04X:感应模块复位错误",nErrCode);
		break;
	case 0x1a:
		sprintf(gErrMsg,"Err-%04X:非认证接口",nErrCode);
		break;
	case 0x1b:
		sprintf(gErrMsg,"Err-%04X:模块通讯超时",nErrCode);
		break;
	case 0x3c:
		sprintf(gErrMsg,"Err-%04X:非正常操作",nErrCode);
		break;
	case 0x64:
		sprintf(gErrMsg,"Err-%04X:错误的数据",nErrCode);
		break;
	case 0x7c:
		sprintf(gErrMsg,"Err-%04X:错误的参数值",nErrCode);
		break;
	default:
		sprintf(gErrMsg,"Err-%04X:读卡器未知的错误",nErrCode);
		break;
	}
	if(sErrMsg)
		strcpy(sErrMsg,gErrMsg);
	return gErrMsg;
}
// function open_device
static int KSAPI open_device(ks_reader_dev_t *dev)
{
	int ret;
	if(dev->port != 100)
	{
		ret = dc_init(dev->port-1,dev->baud);
		if(ret<=0)
		{
			sprintf(gErrMsg, "打开串口 COM%d 失败", dev->port);
			return KS_OPENDEVICE;
		}
	}
	else
	{
		ret = dc_init(100,0);
		if(ret<=0)
		{
			strcpy(gErrMsg, "打开读卡器USB端口失败");
			return KS_OPENDEVICE;
		}
	}
	g_dev_hd = (HANDLE)ret;
	return 0;
}
// function close_device 
static int KSAPI close_device(ks_reader_dev_t *dev)
{
	if(g_dev_hd!=NULL)
	{
		dc_exit(g_dev_hd);
	}
	g_dev_hd = 0;
	return 0;
}

static int get_decard_slot(ks_reader_dev_t *dev,int SAMID)
{
	int slot = 100;
	switch(SAMID)
	{
	case CARDSLOT_1:
		slot = 0x0c;
		break;
	case CARDSLOT_2:
		slot = 0x0d;
		break;
	case CARDSLOT_3:
		slot = 0x0e;
		break;
	case CARDSLOT_4:
		slot = 0x0f;
		break;
	default:
		slot = 100;
		break;
	}
	if(slot == 100)
		return KS_PARAMERR;
	//if(g_cpu_last_slot != slot)
	{
		if(dc_setcpu(g_dev_hd,slot))
		{
			return KS_OPENDEVICE;
		}
		g_cpu_last_slot = slot;
	}
	return 0;
}

// function request_card 
static int KSAPI request_card(ks_reader_dev_t *dev,char* phyid,KS_CARD_TYPE t)
{
	int ret;
	unsigned long snr;
	unsigned short tagtype;
	unsigned char size;
	uint8 ucCardPhyID[8];
	uint8 rData[256];
	
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
	//if(t == KS_CPUCARD || t == KS_FIXCARD)
	if(dev->cpuport == CARDSLOT_RF)
	{
		dc_reset(g_dev_hd,1);
		ret = dc_request(g_dev_hd,1,&tagtype);
		if(ret)
		{
			GetErrMsgByErrCode(ret,gErrMsg);
			TRACE_ERR("检测卡错误， "<<gErrMsg);
			return KS_REQUESTCARD;
		}
		ret = dc_anticoll(g_dev_hd,0,&snr);
		if(ret)
		{
			GetErrMsgByErrCode(ret,gErrMsg);
			TRACE_ERR("检测卡错误， "<<gErrMsg);
			return KS_REQUESTCARD;
		}
		ret = dc_select(g_dev_hd,snr,&size);
		if(ret)
		{
			GetErrMsgByErrCode(ret,gErrMsg);
			TRACE_ERR("检测卡错误， "<<gErrMsg);
			return KS_REQUESTCARD;
		}

		switch(tagtype)
		{
		case 8:
			g_lastCardType = KS_CPUCARD;
			break;
		case 4:
			if(size == 40)
				g_lastCardType = KS_FIXCARD;
			else
				g_lastCardType = KS_MFCARD; // S50
			break;
		case 2: // S70
			g_lastCardType = KS_MFCARD;
			break;
		}

		/*
		if(t == KS_CPUCARD || t == KS_FIXCARD)
		{
			ret = dc_pro_reset_hex(g_dev_hd, &size, (char *)rData);
			if(ret !=0 )
			{
				GetErrMsgByErrCode(ret,gErrMsg);
				TRACE_ERR("CPU卡复位错误， "<<gErrMsg);
				return KS_REQUESTCARD;
			}
		}
		*/
		dev->cardtype = g_lastCardType;
		set_4byte_int(ucCardPhyID,snr);
		dec2hex(ucCardPhyID,4,phyid);
		phyid[8]=0;	
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
	dc_halt(g_dev_hd);
	return 0;
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
	dc_beep(g_dev_hd,10);
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
	dc_beep(g_dev_hd,160);
	return 0;
}
// function login_card 
static int KSAPI login_card(ks_reader_dev_t *dev,ks_card_info_t *card,int sect_no,
							KS_MF_KEYTYPE keytype,const uint8 *key)
{
	int ret;
	uint8 mode;
	if(keytype == MF_KEYA)
	{
		mode = 0;
	}
	else 
	{
		mode = 4;
	}
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;
	
	ret = dc_load_key(g_dev_hd,mode,sect_no,(uint8*)key);
	if(ret)
	{
		GetErrMsgByErrCode(ret,gErrMsg);
		return KS_LOGINCARD;
	}
	ret = dc_authentication(g_dev_hd,mode,sect_no);
	if(ret)
	{
		GetErrMsgByErrCode(ret,gErrMsg);
		return KS_LOGINCARD;
	}
	return 0;
}

// function read_block 
static int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block)
{
	int ret;
	// TODO : 根据卡类型判断，只能处理32个扇区之前的
	if(block_no >= 32*4 || block_no < 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;

	ret = dc_read(g_dev_hd,block_no,block);
	if(ret)
		return KS_READCARD;

	return 0;
}

// function write_block 
static int KSAPI write_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,const uint8 *block)
{
	int ret;
	// TODO : 根据卡类型判断，只能处理32个扇区之前的
	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;

	ret = dc_write(g_dev_hd,block_no,(uint8*)block);
	if(ret)
		return KS_WRITECARD;
	return 0;
}

// function decrement_card 
static int KSAPI decrement_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount)
{
	int ret;
	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;
	ret = dc_decrement(g_dev_hd,block_no,amount);
	if(ret)
		return KS_WRITEPURSE;
	return 0;
}

// function increment_card 
static int KSAPI increment_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount)
{
	int ret;
	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;
	ret = dc_increment(g_dev_hd,block_no,amount);
	if(ret)
		return KS_WRITEPURSE;
	return 0;
}

// function transform_card 
static int KSAPI transform_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no)
{

	int ret;
	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;

	ret = dc_transfer(g_dev_hd,block_no);
	if(ret)
		return KS_WRITEPURSE;
	return 0;
}

// function restore_card 
static int KSAPI restore_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no)
{
	int ret;
	if(block_no >= 32*4 || block_no <= 0)
		return KS_BLOCK_OVERFLOW;
	if(!g_dev_hd)
		return KS_PORT_NOTOPEN;

	ret = dc_restore(g_dev_hd,block_no);
	if(ret)
		return KS_WRITEPURSE;

	return 0;
}

// function procard_cmd
static int KSAPI procard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd)
{
	return 0;
}

// function cpucard_poweron 
static int KSAPI cpucard_poweron(ks_reader_dev_t *dev,KS_CARD_TYPE t,uint8 *len,uint8 *buf)
{
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
			ret = dc_pro_reset(g_dev_hd,len,buf); // cpucard
		}
		else
		{
			GET_DECARD_SLOT(dev,dev->cpuport);
			ret = dc_cpureset(g_dev_hd,len,buf); // sam
		}
	}
	else
	{
		GET_DECARD_SLOT(dev,dev->cpuport);
		ret = dc_cpureset(g_dev_hd,len,buf); // sam
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
	unsigned char rdata[64];
	if(!g_dev_hd)
	{
		ret=open_device(dev);
		if(ret)
			return ret;
	}
	if(dev->cpuport == CARDSLOT_RF)
	{
		ret=dc_reset(g_dev_hd,msec);
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
	uint8 cputype,cpupro,cputu;

	g_cpu_last_slot = -1;
	GET_DECARD_SLOT(dev,dev->cpuport);
	if(dev->cputype <0 || dev->cputype >1)
		return KS_PARAMERR;

	cpupro = dev->cputype;
	cputype = g_cpu_last_slot;

	switch (dev->cpubaud)
	{
	default:
	case 9600:
		cputu = 92;
		break;
	case 38400:
		cputu = 20;
		break;
	}

	ret = dc_setcpupara(g_dev_hd,cputype,cpupro,cputu);
	if(ret)
	{
		GetErrMsgByErrCode(ret,gErrMsg);
		return KS_OPENDEVICE;
	}
	return 0;
}

// function cpucard_cmd 
static int KSAPI cpucard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd,KS_CARD_TYPE t)
{
	int ret = -1;
	uint8 sw1,sw2;
	char szCmd[256];
	ks_cpu_cmd_t innerCmd;
	cmd->cmd_retcode=0;
	assert(dev != NULL);
	if(!g_dev_hd)
	{
		strcpy(gErrMsg,"读卡器端口未打开");
		strcpy(cmd->cmd_retmsg,gErrMsg);
		return KS_PORT_NOTOPEN;
	}
	
	int recvlen;
	if(t == KS_CPUCARD || t == KS_FIXCARD)
	{
		// 非接触式
		if(dev->cpuport == CARDSLOT_RF)
		{
			if(cmd->cmd_type == 0)
			{
				ret = dc_pro_commandlink(g_dev_hd,cmd->send_len,cmd->send_buf,(unsigned char*)&recvlen,cmd->recv_buf,7,56);
				cmd->recv_len = recvlen;
			}
			else
			{
				unsigned char ucCmd[512];
				int  iCmdLen=0;
				hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
				ret = dc_pro_commandlink(g_dev_hd,iCmdLen,ucCmd,(unsigned char*)&recvlen,ucCmd,7,56);
				cmd->recv_len = recvlen;
				memcpy(cmd->recv_buf,ucCmd,cmd->recv_len);
			}
		}
		else
		{
			//GET_DECARD_SLOT(dev,dev->cpuport);
			if(cmd->cmd_type == 0)
			{
				ret = dc_cpuapdu(g_dev_hd,cmd->send_len,cmd->send_buf,(unsigned char*)&recvlen,cmd->recv_buf);
				cmd->recv_len = recvlen;
			}
			else
			{
				unsigned char ucCmd[512];
				int  iCmdLen=0;
				hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
				ret = dc_cpuapdu(g_dev_hd,iCmdLen,ucCmd,(unsigned char*)&recvlen,cmd->recv_buf);
				cmd->recv_len=recvlen;
			}
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
			//GET_DECARD_SLOT(dev,dev->cpuport);
			
			if(cmd->cmd_type == 0)
			{
				ret = dc_cpuapdu(g_dev_hd,cmd->send_len,cmd->send_buf,(unsigned char*)&recvlen,cmd->recv_buf);
				cmd->recv_len = recvlen;
			}
			else
			{
				unsigned char ucCmd[512];
				int  iCmdLen=0;
				hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
				ret = dc_cpuapdu(g_dev_hd,iCmdLen,ucCmd,(unsigned char*)&recvlen,cmd->recv_buf);
				cmd->recv_len = recvlen;
			}
		}
	}
	if(ret)
	{
		cmd->cmd_retcode = 0;
		TRACE_ERR("执行指令错误,type["<<t<<"]");
		GetErrMsgByErrCode(ret,gErrMsg);
		strcpy(cmd->cmd_retmsg,gErrMsg);
		return KS_CMDERROR;
	}
	//if(cmd->recv_len < 2)
	//{
	//	cmd->cmd_retcode = 0;
	//	strcpy(cmd->cmd_retmsg,"读卡器读返回数据错误");
	//	cmd->cmd_retcode = 2;
	//	return KS_CMDERROR;
	//}
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
	if(t == CPUCARD_A)
		return dc_config_card(g_dev_hd,'A');
	else
		return dc_config_card(g_dev_hd,'B');
}
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