#include "ksdevice.h"
#include "dcrf32.h"
#include "global_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static ks_device_op_t g_device_op;
static const char g_version[]="1.00";
static const char g_devname[]="decard";

/*
int KSAPI open_device(ks_reader_dev_t *dev);
int KSAPI close_device(ks_reader_dev_t *dev);
int KSAPI request_card(ks_reader_dev_t *dev,uint8 *phyid);
int KSAPI halt(ks_reader_dev_t *dev);
 mifare one card 
int KSAPI login_card(ks_reader_dev_t *dev,ks_card_info_t *card,int sect_no,KS_MF_KEYTYPE keytype,const uint8 *key);
int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block);
int KSAPI write_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,const uint8 *block);
int KSAPI decrement_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount);
int KSAPI increment_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount);
int KSAPI transform_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no);
int KSAPI restore_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no);
 cpucard 
int KSAPI cpucard_poweron(ks_reader_dev_t *dev,uint8 *len,uint8 *buf);
int KSAPI cpucard_setpara(ks_reader_dev_t *dev);
int KSAPI cpucard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd);
*/

// function open_device
static int KSAPI open_device(ks_reader_dev_t *dev)
{
	HANDLE ret;
	if(dev->devtype == KS_READER_COM)
	{
		ret = dc_init(dev->port-1,dev->baud);
	}
	else
	{
		ret = dc_init(100,0);
	}
	if(ret>0)
	{
		dev->devhd = ret;
		return KS_SUCCESS;
	}
	return KS_OPENDEVICE;
}
// function close_device 
static int KSAPI close_device(ks_reader_dev_t *dev)
{

	if(dev->devhd!=NULL)
	{
		dc_exit(dev->devhd);
	}
	dev->devhd=NULL;
	return 0;
}

// function request_card 
static int KSAPI request_card(ks_reader_dev_t *dev,char* phyid,KS_CARD_TYPE t)
{
	int ret;
	unsigned long snr;
	unsigned short tagtype;
	unsigned char size;
	uint8 ucCardPhyID[4];
	uint8 rData[256];
	
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;
	//if(t == KS_CPUCARD || t == KS_FIXCARD)
	dc_reset(dev->devhd,1);
	ret = dc_request(dev->devhd,1,&tagtype);
	if(ret)
	{
		return KS_REQUESTCARD;
	}
	ret = dc_anticoll(dev->devhd,0,&snr);
	if(ret)
	{
		return KS_REQUESTCARD;
	}
	ret = dc_select(dev->devhd,snr,&size);
	if(ret)
		return KS_REQUESTCARD;

	if(t == KS_CPUCARD || t == KS_FIXCARD)
	{
		ret = dc_pro_reset_hex(dev->devhd, &size, (char *)rData);
		if(ret !=0 )
			return KS_REQUESTCARD;
	}
	set_4byte_int(ucCardPhyID,snr);
	dec2hex(ucCardPhyID,4,phyid);
	phyid[8]=0;	
	return 0;
}

// function halt 
static int KSAPI halt(ks_reader_dev_t *dev)
{
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;
	dc_halt(dev->devhd);
	return 0;
}

// function beep
static void KSAPI beep(ks_reader_dev_t *dev)
{
	if(!dev->devhd)
		return ;
	dc_beep(dev->devhd,10);
}

// function reset
static int KSAPI reset(ks_reader_dev_t *dev,size_t msec)
{
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;
	if(dc_reset(dev->devhd,msec))
		return KS_OPENDEVICE;
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
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;
	
	ret = dc_load_key(dev->devhd,mode,sect_no,(uint8*)key);
	if(ret)
		return KS_LOGINCARD;

	ret = dc_authentication(dev->devhd,mode,sect_no);
	if(ret)
		return KS_LOGINCARD;

	return 0;
}

// function read_block 
static int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block)
{
	int ret;
	// TODO : 根据卡类型判断，只能处理32个扇区之前的
	if(block_no >= 32*4 || block_no < 0)
		return KS_BLOCK_OVERFLOW;
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;

	ret = dc_read(dev->devhd,block_no,block);
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
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;

	ret = dc_write(dev->devhd,block_no,(uint8*)block);
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
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;
	ret = dc_decrement(dev->devhd,block_no,amount);
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
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;
	ret = dc_increment(dev->devhd,block_no,amount);
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
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;

	ret = dc_transfer(dev->devhd,block_no);
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
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;

	ret = dc_restore(dev->devhd,block_no);
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
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;

	if(t == KS_MFCARD) // mifare card
		return KS_NOTSUPPORT;
	else if(t == KS_CPUCARD)
		ret = dc_pro_reset(dev->devhd,len,buf); // cpucard
	else if(t == KS_FIXCARD)
		ret = dc_pro_reset(dev->devhd,len,buf); // 7+1 card
	else 
		ret = dc_cpureset(dev->devhd,len,buf); // psam
	if(ret)
		return KS_OPENDEVICE;
	return 0;
}

// function cpucard_setpara 
static int KSAPI cpucard_setpara(ks_reader_dev_t *dev)
{
	int ret;
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;

	uint8 cputype,cpupro,cputu;

	switch(dev->cpuport)
	{
	case CARDSLOT_1:
		cputype = 12;
		break;
	case CARDSLOT_2:
		cputype = 13;
		break;
	case CARDSLOT_3:
		cputype = 14;
		break;
	case CARDSLOT_4:
		cputype = 15;
		break;
	default:
		return KS_PARAMERR;
	}
	if(dev->cputype <0 || dev->cputype >1)
		return KS_PARAMERR;

	cpupro = dev->cputype;

	switch (dev->cpubaud)
	{
	case 9600:
		cputu = 92;
		break;
	case 38400:
	default:
		cputu = 20;
		break;
	}

	ret = dc_setcpu(dev->devhd,cputype);
	if(ret)
		return KS_OPENDEVICE;
	ret = dc_setcpupara(dev->devhd,cputype,cpupro,cputu);
	if(ret)
		return KS_OPENDEVICE;

	return 0;
}

// function cpucard_cmd 
static int KSAPI cpucard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd,KS_CARD_TYPE t)
{
	int ret;
	uint8 sw1,sw2;
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;

	if(t == KS_CPUCARD)
	{
		// 非接触式
		if(cmd->cmd_type == 0)
			ret = dc_pro_commandlink(dev->devhd,cmd->send_len,cmd->send_buf,&(cmd->recv_len),cmd->recv_buf,7,56);
		else
			ret = dc_pro_commandlink_hex(dev->devhd,cmd->send_len,cmd->send_buf,&(cmd->recv_len),cmd->recv_buf,7,56);
	}
	else
	{
		if(cmd->cmd_type == 0)
			ret = dc_cpuapdu(dev->devhd,cmd->send_len,cmd->send_buf,&(cmd->recv_len),cmd->recv_buf);
		else
			ret = dc_cpuapdu_hex(dev->devhd,cmd->send_len,(char*)cmd->send_buf,&(cmd->recv_len),(char*)cmd->recv_buf);
	}
	if(ret)
	{
		cmd->cmd_retcode = 1;
		return KS_CMDERROR;
	}
	if(cmd->recv_len < 2)
	{
		cmd->cmd_retcode = 2;
		return KS_CMDERROR;
	}

	sw1 = cmd->recv_buf[cmd->recv_len-2];
	sw2 = cmd->recv_buf[cmd->recv_len-1];
	if(sw1 != 0x90 && sw1 != 0x61)
	{
		ret = sw1;
		ret = ret*256 + sw2;
		cmd->cmd_retcode = ret;
		return KS_CMDFAILD;
	}
	return 0;
}

int KSAPI config_card(ks_reader_dev_t *dev,KS_CPUCARD_TYPE t)
{
	if(!dev->devhd)
		return KS_PORT_NOTOPEN;
	if(t == CPUCARD_A)
		return dc_config_card(dev->devhd,'A');
	else
		return dc_config_card(dev->devhd,'B');
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

	memcpy(op,&g_device_op,sizeof(ks_device_op_t));
	return 0;
}