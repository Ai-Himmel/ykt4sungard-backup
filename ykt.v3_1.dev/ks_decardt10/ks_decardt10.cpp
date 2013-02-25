#include "ksdevice.h"
#include "trf32.h"
#include "global_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static ks_device_op_t g_device_op;
static const char g_version[]="1.10";
static const char g_devname[]="decard";
static int g_cpu_last_slot = CARDSLOT_RF + 1;
static int m_Reader = 0;
static long g_dev_hd = 0;
static int g_lastCardType = 0;
static unsigned char g_sam_protocol = 0;

static char gErrMsg[256] = {0};
typedef unsigned char byte;

#define GET_DECARD_SLOT(dev,p) do{ int s = get_decard_slot(dev,p); if(s != 0) { TRACE_ERR("�����Ŵ���"); return KS_PARAMERR;} }while(0)

static void SetErrMsg(const char *errmsg,const char *file,int line) {
    KS_Log_Tracer::instance()->SetTraceFile(file,line);
    KS_Log_Tracer::instance()->TraceMsg(errmsg);
    strncpy(gErrMsg,errmsg,sizeof(gErrMsg)-1);
}
static char* KSAPI GetErrMsg(char *errmsg) {
    if(errmsg)
        strcpy(errmsg,gErrMsg);
    return gErrMsg;
}
static char* KSAPI GetErrMsgByErrCode(int nErrCode,char* sErrMsg) {
    switch(nErrCode) {
    case -0x10:
        sprintf(gErrMsg,"Err-%04X:ͨѶ����",nErrCode);
        break;
    case -0x11:
        sprintf(gErrMsg,"Err-%04X:��ʱ����",nErrCode);
        break;
    case -0x20:
        sprintf(gErrMsg,"Err-%04X:�򿪶˿ڴ���",nErrCode);
        break;
    case -0x21:
        sprintf(gErrMsg,"Err-%04X:��ö˿ڲ�������",nErrCode);
        break;
    case -0x22:
        sprintf(gErrMsg,"Err-%04X:���ö˿ڲ�������",nErrCode);
        break;
    case -0x23:
        sprintf(gErrMsg,"Err-%04X:�رն˿ڳ���",nErrCode);
        break;
    case -0x24:
        sprintf(gErrMsg,"Err-%04X:�˿ڱ�ռ��",nErrCode);
        break;
    case -0x30:
        sprintf(gErrMsg,"Err-%04X:��ʽ����",nErrCode);
        break;
    case -0x31:
        sprintf(gErrMsg,"Err-%04X:���ݸ�ʽ����",nErrCode);
        break;
    case -0x32:
        sprintf(gErrMsg,"Err-%04X:���ݳ��ȴ���",nErrCode);
        break;
    case -0x40:
        sprintf(gErrMsg,"Err-%04X:������",nErrCode);
        break;
    case -0x41:
        sprintf(gErrMsg,"Err-%04X:д����",nErrCode);
        break;
    case -0x42:
        sprintf(gErrMsg,"Err-%04X:�޽��մ���",nErrCode);
        break;
    case -0x50:
        sprintf(gErrMsg,"Err-%04X:����������",nErrCode);
        break;
    case -0x51:
        sprintf(gErrMsg,"Err-%04X:CPU�������ʹ���",nErrCode);
        break;
    case -0x52:
        sprintf(gErrMsg,"Err-%04X:485ͨѶʱ��ַ�Ŵ���",nErrCode);
        break;
    case -0x73:
        sprintf(gErrMsg,"Err-%04X:ȡ�汾�Ŵ���",nErrCode);
        break;
    case -0xc2:
        sprintf(gErrMsg,"Err-%04X:CPU����Ӧ����",nErrCode);
        break;
    case -0xd3:
        sprintf(gErrMsg,"Err-%04X:CPU����Ӧ��ʱ",nErrCode);
        break;
    case -0xd6:
        sprintf(gErrMsg,"Err-%04X:CPU��У�����",nErrCode);
        break;
    case -0xd7:
        sprintf(gErrMsg,"Err-%04X:CPU����������ִ���",nErrCode);
        break;
//////////////////////////////////////////////////////////////////
    case 0x01:
        sprintf(gErrMsg,"Err-%04X:δ���ÿ�Ƭ����֤����",nErrCode);
        break;
    case 0x02:
        sprintf(gErrMsg,"Err-%04X:����У�����",nErrCode);
        break;
    case 0x03:
        sprintf(gErrMsg,"Err-%04X:��ֵΪ�մ���",nErrCode);
        break;
    case 0x04:
        sprintf(gErrMsg,"Err-%04X:��֤ʧ��",nErrCode);
        break;
    case 0x05:
        sprintf(gErrMsg,"Err-%04X:��żУ�����",nErrCode);
        break;
    case 0x06:
        sprintf(gErrMsg,"Err-%04X:��д�豸�뿨ƬͨѶ����",nErrCode);
        break;
    case 0x08:
        sprintf(gErrMsg,"Err-%04X:�������кŴ���",nErrCode);
        break;
    case 0x09:
        sprintf(gErrMsg,"Err-%04X:�������ʹ���",nErrCode);
        break;
    case 0x0a:
        sprintf(gErrMsg,"Err-%04X:��Ƭ��δ����֤",nErrCode);
        break;
    case 0x0b:
        sprintf(gErrMsg,"Err-%04X:������������������",nErrCode);
        break;
    case 0x0c:
        sprintf(gErrMsg,"Err-%04X:���������ֽ�������",nErrCode);
        break;
    case 0x0f:
        sprintf(gErrMsg,"Err-%04X:д������ʧ��",nErrCode);
        break;
    case 0x10:
        sprintf(gErrMsg,"Err-%04X:��ֵ����ʧ��",nErrCode);
        break;
    case 0x11:
        sprintf(gErrMsg,"Err-%04X:��ֵ����ʧ��",nErrCode);
        break;
    case 0x12:
        sprintf(gErrMsg,"Err-%04X:��������ʧ��",nErrCode);
        break;
    case 0x13:
        sprintf(gErrMsg,"Err-%04X:���仺�������",nErrCode);
        break;
    case 0x15:
        sprintf(gErrMsg,"Err-%04X:����֡����",nErrCode);
        break;
    case 0x17:
        sprintf(gErrMsg,"Err-%04X:δ֪�Ĵ�������",nErrCode);
        break;
    case 0x18:
        sprintf(gErrMsg,"Err-%04X:����ͻ����",nErrCode);
        break;
    case 0x19:
        sprintf(gErrMsg,"Err-%04X:��Ӧģ�鸴λ����",nErrCode);
        break;
    case 0x1a:
        sprintf(gErrMsg,"Err-%04X:����֤�ӿ�",nErrCode);
        break;
    case 0x1b:
        sprintf(gErrMsg,"Err-%04X:ģ��ͨѶ��ʱ",nErrCode);
        break;
    case 0x3c:
        sprintf(gErrMsg,"Err-%04X:����������",nErrCode);
        break;
    case 0x64:
        sprintf(gErrMsg,"Err-%04X:���������",nErrCode);
        break;
    case 0x7c:
        sprintf(gErrMsg,"Err-%04X:����Ĳ���ֵ",nErrCode);
        break;
    case 0xA001:
        sprintf(gErrMsg,"Err-%04X:RFID-SIM��δ����",nErrCode);
        break;
    case 0xA002:
        sprintf(gErrMsg,"Err-%04X:RFID-SIM������ʧ��",nErrCode);
        break;
    case 0xA003:
        sprintf(gErrMsg,"Err-%04X:��֧�ֵĲ���",nErrCode);
        break;
    case 0xA004:
        sprintf(gErrMsg,"Err-%04X:�رղ���ʧ��",nErrCode);
        break;
    case 0xA005:
        sprintf(gErrMsg,"Err-%04X:�������ݸ�ʽ����",nErrCode);
        break;
    case 0xA006:
        sprintf(gErrMsg,"Err-%04X:����RFID-SIM���޻�Ӧ(�ȴ���ʱ)",nErrCode);
        break;
    case 0xA007:
        sprintf(gErrMsg,"Err-%04X:����RFID-SIM�����ݳ��ִ���",nErrCode);
        break;
    case 0xA008:
        sprintf(gErrMsg,"Err-%04X:δ֪����",nErrCode);
        break;
    case 0xA009:
        sprintf(gErrMsg,"Err-%04X:�������Լ�δͨ��",nErrCode);
        break;
    case 0xA00A:
        sprintf(gErrMsg,"Err-%04X:��ƬУ׼�����쳣",nErrCode);
        break;
    case 0xA00B:
        sprintf(gErrMsg,"Err-%04X:ˢ�������ܵ�����ĸ��ź�Ӱ��",nErrCode);
        break;
    default:
        sprintf(gErrMsg,"Err-%04X:������δ֪�Ĵ���",nErrCode);
        break;
    }
    if(sErrMsg)
        strcpy(sErrMsg,gErrMsg);
    return gErrMsg;
}

static int RFSIMSendCommand(const unsigned char *sbuff,int slen,unsigned char * rbuff,int *rlen) {
    unsigned char sCmd[512]= {0},sResp[512]= {0};
    unsigned char nCmdLen=0,nRecvLen=0;
    int ret;
    if(g_dev_hd == 0)
        return -2;
    sCmd[0]=0x02;
    sCmd[1]=slen/256;
    sCmd[2]=slen%256;
    memcpy(sCmd+3,sbuff,slen);
    nCmdLen=3+slen;
    sCmd[nCmdLen]=calc_xor(sbuff,slen);
    nCmdLen++;
    sCmd[nCmdLen]=0x03;
    nCmdLen++;
    ret = dc_rf_sim(g_dev_hd,nCmdLen,sCmd,&nRecvLen,sResp);
    if(ret) {
        return -1;
    }
//Resp:���ݳ���(2�ֽ�)+״̬��(2�ֽ�)+����
    *rlen=sResp[1]*256+sResp[2]-2;	//ȥ��2�ֽ�״̬��
    if(*rlen>256)
        *rlen=256;
    if(*rlen>0) memcpy(rbuff,sResp+5,*rlen);
    return sResp[3]*256+sResp[4];
}

// function open_device
static int KSAPI open_device(ks_reader_dev_t *dev) {
    int ret;
    long h;
    unsigned char version[32];
    if(dev->port != 100) {
        h = dc_init(dev->port-1,115200);
        if(h < 0) {
            sprintf(gErrMsg, "�򿪴��� COM%d ʧ��", dev->port);
            return KS_OPENDEVICE;
        }
    } else {
        h = dc_init(100,0);
        if(h < 0) {
            strcpy(gErrMsg, "�򿪶�����USB�˿�ʧ��");
            return KS_OPENDEVICE;
        }
    }
    if(dc_getver(h,version)<0) {
        strcpy(gErrMsg,"�򿪶��������󣬿����豸û�����ӻ��߲�����ʹ�ô���!");
        dc_exit(h);
        return KS_OPENDEVICE;
    }
    g_dev_hd = h;
    // open success
    return 0;
}
// function close_device
static int KSAPI close_device(ks_reader_dev_t *dev) {
    if(g_dev_hd!=NULL) {
        dc_exit(g_dev_hd);
    }
    g_dev_hd = 0;
    return 0;
}

static int get_decard_slot(ks_reader_dev_t *dev,int SAMID) {
    unsigned char rlen,rdata[256],protocol;
    int slot = 100;
    int slotreset = 100;
    long nRet;
    switch(SAMID) {
    case CARDSLOT_1:
        slot = 0x0c;
        slotreset = 3;
        break;
    case CARDSLOT_2:
        slot = 0x0d;
        slotreset = 1;
        break;
    case CARDSLOT_3:
        slot = 0x0e;
        slotreset = 2;
        break;
    case CARDSLOT_4:
        slot = 0x0f;
        slotreset = 4;
        break;
    default:
        slot = 100;
        break;
    }
    if(slot == 100)
        return KS_PARAMERR;

    //if(g_cpu_last_slot != slot)
    {
        if((nRet=dc_setcpu(g_dev_hd,slot))) {
            TRACE_ERR("SAM����������,ret["<<nRet<<"]");
            return KS_OPENDEVICE;
        }
        if((nRet=dc_cpureset(g_dev_hd,slotreset,1,2,&rlen,rdata,&g_sam_protocol))) {
            TRACE_ERR("SAM����λ����,ret["<<nRet<<"]");
            return KS_OPENDEVICE;
        }
        g_cpu_last_slot = slot;
    }
    return 0;
}

static int send_rfsim_cmd(const unsigned char *cmd,byte slen,byte *resp,byte *rlen) {
    byte send_cmd[512],resp_cmd[256] = {0};
    byte offset,sw1,sw2;
    long ret;
    int datalen;
    offset = 0;
    send_cmd[offset++]=0x02;
    send_cmd[offset++]=0;
    send_cmd[offset++]=slen%256;
    memcpy(send_cmd+offset,cmd,slen);
    offset += slen;
    send_cmd[offset++]=calc_xor(cmd,slen);
    send_cmd[offset++]=0x03;

    ret = dc_rf_sim(g_dev_hd,offset,send_cmd,&offset,resp_cmd);
    if(ret)
        return -1;
    if(offset < 4)
        return -1;
    if(resp_cmd[0] != 0x02 || resp_cmd[offset-1] != 0x03)
        return -1;
    datalen = resp_cmd[1] * 256;
    datalen += resp_cmd[2];
    if(datalen > 0 && datalen > offset - 5)
        return -3;
    if(calc_xor(resp_cmd+3,datalen) != resp_cmd[offset-2])
        return -4;
    sw1 = resp_cmd[3];
    sw2 = resp_cmd[4];
    if(sw1 != 0 || sw2 != 0)
        return (sw1 * 256 + sw2);
    if(datalen > 2)
        memcpy(resp,resp_cmd+5,datalen-2);
    *rlen = datalen - 2;
    return 0;
}

// function request_card
static int KSAPI request_card(ks_reader_dev_t *dev,char* phyid,KS_CARD_TYPE t) {
    int ret,i;
    unsigned long snr;
    unsigned short tagtype;
    unsigned char size,sw1,sw2;
    uint8 ucCardPhyID[8];
    uint8 rData[256],rlen;

    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    if(!g_dev_hd) {
        return KS_PORT_NOTOPEN;
    }
    /*
    	if(dev->cpuport == CARDSLOT_RF)
    	{
    		if(t == KS_MFCARD)
    		{
    			dc_reset(g_dev_hd);
    			ret = dc_card(g_dev_hd,0,&snr);
    			if(ret)
    			{
    				TRACE_ERR("M1��Ѱ��ʧ��,ret["<<ret<<"]");
    				return KS_REQUESTCARD;
    			}
    			memcpy(ucCardPhyID,&snr,4);
    			dec2hex(ucCardPhyID,4,phyid);
    			phyid[8] = 0;
    			g_lastCardType = KS_MFCARD;
    		}
    		else if(t == KS_MFCARD || t == KS_CPUCARD || t == KS_FIXCARD || t == KS_SIMCARD)
    		{
    			dc_reset(g_dev_hd);
    			//ret = dc_request(g_dev_hd,1,&tagtype);
    			ret = dc_config_card(g_dev_hd, 'A');
    			if(ret)
    			{
    				TRACE_ERR("���ÿ����ʹ���");
    				return KS_REQUESTCARD;
    			}
    			ret = dc_card_pro(g_dev_hd,&rlen,rData);
    			if(ret)
    			{
    				byte slen,rlen;
    				byte cmd[256],resp[256];
    				// �����ֻ���Ѱ��
    				slen = 4;
    				memcpy(cmd,"\xA2\x32\x00\x00",slen);
    				ret = send_rfsim_cmd(cmd,slen,resp,&rlen);
    				if(ret)
    				{
    					GetErrMsgByErrCode(ret,gErrMsg);
    					TRACE_ERR("���ͶϿ���������ʧ��, "<<gErrMsg);
    					return KS_REQUESTCARD;
    				}
    				memcpy(cmd,"\xA2\x31\x07\xD0",slen);
    				ret = send_rfsim_cmd(cmd,slen,resp,&rlen);
    				if(ret)
    				{
    					GetErrMsgByErrCode(ret,gErrMsg);
    					TRACE_ERR("����Ѱ������ʧ��, "<<gErrMsg);
    					return KS_REQUESTCARD;
    				}
    				rlen = (resp[0] > 8) ? 8 : resp[0];
    				memcpy(ucCardPhyID,resp+1,rlen);
    				dec2hex(ucCardPhyID,rlen,phyid);
    				phyid[rlen*2] = 0;
    				g_lastCardType = KS_SIMCARD;
    				dev->cardtype = g_lastCardType;
    			}
    			else
    			{

    				//memcpy(phyid,rData,rlen*2);

    				for(i = 0;i < 4;++i)
    					ucCardPhyID[3-i] = rData[i];
    				dec2hex(ucCardPhyID,4,phyid);
    				phyid[8]=0;
    				memset(rData, 0, sizeof(rData));
    				ret = dc_pro_resethex(g_dev_hd, &rlen, rData);
    				if(ret)
    				{
    					TRACE_ERR("CPU����λʧ��,ret["<<ret<<"]");
    					return KS_REQUESTCARD;
    				}
    				g_lastCardType = KS_FIXCARD;
    			}
    		}
    		dev->cardtype = g_lastCardType;
    	}
    	else
    	{
    		TRACE_ERR("�����������");
    		return KS_REQUESTCARD;
    	}
    */
    if(t == KS_MFCARD) {
        dc_reset(g_dev_hd);
        ret = dc_card(g_dev_hd,0,&snr);
        if(ret) {
            TRACE_ERR("M1��Ѱ��ʧ��,ret["<<ret<<"]");
            return KS_REQUESTCARD;
        }
        memcpy(rData,&snr,4);
        for(i = 0; i < 4; ++i) {
            ucCardPhyID[3-i] = rData[i];
        }
        dec2hex(ucCardPhyID,4,phyid);
        phyid[8] = 0;
        g_lastCardType = KS_MFCARD;
        return 0;
    }
    if(g_lastCardType != 0 && (g_lastCardType == KS_CPUCARD || g_lastCardType == KS_FIXCARD
                               || g_lastCardType == KS_MFCARD )) {
        dc_reset(g_dev_hd);
    }
    ret = dc_config_card(g_dev_hd, 'A');
    if(ret) {
        TRACE_ERR("���ÿ����ʹ���");
        return KS_REQUESTCARD;
    }
    ret = dc_card_pro(g_dev_hd,&rlen,rData);
    if(ret) {
        byte slen,rlen;
        byte cmd[256],resp[256];
        // �����ֻ���Ѱ��
        slen = 4;
        memcpy(cmd,"\xA2\x32\x00\x00",slen);
        ret = send_rfsim_cmd(cmd,slen,resp,&rlen);
        if(ret) {
            GetErrMsgByErrCode(ret,gErrMsg);
            TRACE_ERR("���ͶϿ���������ʧ��, "<<gErrMsg);
            return KS_REQUESTCARD;
        }
        memcpy(cmd,"\xA2\x31\x07\xD0",slen);
        ret = send_rfsim_cmd(cmd,slen,resp,&rlen);
        if(ret) {
            GetErrMsgByErrCode(ret,gErrMsg);
            TRACE_ERR("����Ѱ������ʧ��, "<<gErrMsg);
            return KS_REQUESTCARD;
        }
        rlen = (resp[0] > 8) ? 8 : resp[0];
        memcpy(ucCardPhyID,resp+1,rlen);
        dec2hex(ucCardPhyID,rlen,phyid);
        phyid[rlen*2] = 0;
        g_lastCardType = KS_SIMCARD;

    } else {
        for(i = 0; i < 4; ++i) {
            ucCardPhyID[3-i] = rData[i];
            //ucCardPhyID[i] = rData[i];
        }
        dec2hex(ucCardPhyID,4,phyid);
        phyid[8]=0;
        /*
        memset(rData, 0, sizeof(rData));
        ret = dc_pro_resethex(g_dev_hd, &rlen, rData);
        if(ret)
        {
        	TRACE_ERR("CPU����λʧ��,ret["<<ret<<"]");
        	return KS_REQUESTCARD;
        }
        */
        g_lastCardType = KS_FIXCARD;
    }
    dev->cardtype = g_lastCardType;
    return 0;
}

// function halt
static int KSAPI halt(ks_reader_dev_t *dev) {
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;
    dc_halt(g_dev_hd);
    return 0;
}

// function beep
static int KSAPI beep(ks_reader_dev_t *dev) {
    int ret=0;
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return -1;
    }
    dc_beep(g_dev_hd,100);
    return 0;
}

// function beep
static int KSAPI beeperr(ks_reader_dev_t *dev) {
    int ret=0;
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return -1;
    }
    dc_beep(g_dev_hd,300);
    return 0;
}

// function login_card
static int KSAPI login_card(ks_reader_dev_t *dev,ks_card_info_t *card,int sect_no,
                            KS_MF_KEYTYPE keytype,const uint8 *key) {
    int ret;
    uint8 mode;
    if(keytype == MF_KEYA) {
        mode = 0;
    } else {
        mode = 4;
    }
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    ret = dc_load_key(g_dev_hd,mode,sect_no,(uint8*)key);
    if(ret) {
        GetErrMsgByErrCode(ret,gErrMsg);
        return KS_LOGINCARD;
    }
    ret = dc_authentication(g_dev_hd,mode,sect_no);
    if(ret) {
        GetErrMsgByErrCode(ret,gErrMsg);
        return KS_LOGINCARD;
    }
    return 0;
}

// function read_block
static int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block) {
    int ret;
    // TODO : ���ݿ������жϣ�ֻ�ܴ���32������֮ǰ��
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
static int KSAPI write_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,const uint8 *block) {
    int ret;
    // TODO : ���ݿ������жϣ�ֻ�ܴ���32������֮ǰ��
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
static int KSAPI decrement_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount) {
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
static int KSAPI increment_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount) {
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
static int KSAPI transform_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no) {

    int ret;
    if(block_no >= 32*4 || block_no <= 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    //ret = dc_transfer(g_dev_hd,block_no);
    //if(ret)
    return KS_WRITEPURSE;
    return 0;
}

// function restore_card
static int KSAPI restore_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no) {
    int ret;
    if(block_no >= 32*4 || block_no <= 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

//	ret = dc_restore(g_dev_hd,block_no);
//	if(ret)
    return KS_WRITEPURSE;

    return 0;
}

// function procard_cmd
static int KSAPI procard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd) {
    return 0;
}

// function cpucard_poweron
static int KSAPI cpucard_poweron(ks_reader_dev_t *dev,KS_CARD_TYPE t,uint8 *len,uint8 *buf) {
    int ret;
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }

    if( t == KS_MFCARD) // mifare card
        return KS_NOTSUPPORT;
    else if(t == KS_CPUCARD || t == KS_FIXCARD) {
        if(dev->cpuport == CARDSLOT_RF) {
            ret = dc_pro_reset(g_dev_hd,len,buf); // cpucard
        } else {
            GET_DECARD_SLOT(dev,dev->cpuport);
            //ret = dc_cpureset(g_dev_hd,len,buf); // sam
        }
    } else {
        GET_DECARD_SLOT(dev,dev->cpuport);
        //ret = dc_cpureset(g_dev_hd,len,buf); // sam
    }

    return 0;
}


// function reset
static int KSAPI reset(ks_reader_dev_t *dev,size_t msec) {
    int ret=0;
    unsigned char rlen;
    unsigned char rdata[64];
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    if(dev->cpuport == CARDSLOT_RF) {
        ret=dc_reset(g_dev_hd);
        if(ret) {
            GetErrMsgByErrCode(ret,gErrMsg);
            return KS_OPENDEVICE;
        }
    } else {
        ret = cpucard_poweron(dev,KS_CPUCARD,&rlen,rdata);
    }
    return 0;
}


// function cpucard_setpara
static int KSAPI cpucard_setpara(ks_reader_dev_t *dev) {
    int ret;
    if(!g_dev_hd) {
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

    switch (dev->cpubaud) {
    default:
    case 9600:
        cputu = 1;
        break;
    case 14400:
        cputu = 2;
        break;
    case 19200:
        cputu = 3;
        break;
    case 38400:
        cputu = 4;
        break;
    case 57600:
        cputu = 5;
        break;
    }
    /*
    ret = dc_setcpupara(g_dev_hd,cputype,cpupro,cputu);
    if(ret)
    {
    	GetErrMsgByErrCode(ret,gErrMsg);
    	return KS_OPENDEVICE;
    }
    */
    return 0;
}

// function cpucard_cmd
static int KSAPI cpucard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd,KS_CARD_TYPE t) {
    int ret = -1;
    uint8 sw1,sw2;
    char szCmd[256];
    ks_cpu_cmd_t innerCmd;
    cmd->cmd_retcode=0;
    assert(dev != NULL);
    if(!g_dev_hd) {
        strcpy(gErrMsg,"�������˿�δ��");
        strcpy(cmd->cmd_retmsg,gErrMsg);
        return KS_PORT_NOTOPEN;
    }

    unsigned char recvlen = 0;
    if(t == KS_CPUCARD || t == KS_FIXCARD) {
        // �ǽӴ�ʽ
        if(dev->cpuport == CARDSLOT_RF) {
            if(cmd->cmd_type == 0) {
                ret = dc_pro_commandlink(g_dev_hd,cmd->send_len,cmd->send_buf,(unsigned char*)&recvlen,cmd->recv_buf,7,56);
                cmd->recv_len = recvlen;
            } else {
                unsigned char ucCmd[512];
                int  iCmdLen=0;
                hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
                ret = dc_pro_commandlink(g_dev_hd,iCmdLen,ucCmd,(unsigned char*)&recvlen,ucCmd,7,56);
                cmd->recv_len = recvlen;
                memcpy(cmd->recv_buf,ucCmd,cmd->recv_len);
            }
        } else {
            //GET_DECARD_SLOT(dev,dev->cpuport);
            if(cmd->cmd_type == 0) {
                ret = dc_cpuapdu(g_dev_hd,g_cpu_last_slot,cmd->send_len,cmd->send_buf,(unsigned char*)&recvlen,cmd->recv_buf,0);
                cmd->recv_len = recvlen;
            } else {
                unsigned char ucCmd[512];
                int  iCmdLen=0;
                hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
                ret = dc_cpuapdu(g_dev_hd,g_cpu_last_slot,iCmdLen,ucCmd,(unsigned char*)&recvlen,cmd->recv_buf,0);
                cmd->recv_len=recvlen;
            }
        }
    } else if(t == KS_SIMCARD) {
        // �ֻ������
        unsigned char ucCmd[512];
        int  iCmdLen=0;
        ucCmd[0] = 0xA2;
        ucCmd[1] = 0x33;
        if(cmd->cmd_type == 0) {
            memcpy(ucCmd+2,cmd->send_buf,cmd->send_len);
            iCmdLen = cmd->send_len + 2;
            ret = send_rfsim_cmd(ucCmd,iCmdLen,cmd->recv_buf,(unsigned char*)&recvlen);
            cmd->recv_len=recvlen;
        } else {
            hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd+2,iCmdLen);
            iCmdLen += 2;
            ret = send_rfsim_cmd(ucCmd,iCmdLen,cmd->recv_buf,(unsigned char*)&recvlen);
            cmd->recv_len=recvlen;
        }
    } else if(t == KS_PSAM) {
        // �Ӵ�ʽ
        if(dev->cpuport == CARDSLOT_RF) {

        } else {
            //GET_DECARD_SLOT(dev,dev->cpuport);

            if(cmd->cmd_type == 0) {
                ret = dc_cpuapdu(g_dev_hd,g_cpu_last_slot,cmd->send_len,cmd->send_buf,(unsigned char*)&recvlen,cmd->recv_buf,g_sam_protocol);
                cmd->recv_len = recvlen;
            } else {
                unsigned char ucCmd[512];
                int  iCmdLen=0;
                hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
                ret = dc_cpuapdu(g_dev_hd,g_cpu_last_slot,iCmdLen,ucCmd,(unsigned char*)&recvlen,cmd->recv_buf,g_sam_protocol);
                //iCmdLen = cmd->send_len / 2;
                //ret = dc_cpuapdu_hex(g_dev_hd,g_cpu_last_slot,iCmdLen,cmd->send_buf,&recvlen,cmd->recv_buf,g_sam_protocol);
                cmd->recv_len = recvlen;
            }
        }
    }
    if(ret) {
        cmd->cmd_retcode = 0;
        GetErrMsgByErrCode(ret,gErrMsg);
        strcpy(cmd->cmd_retmsg,gErrMsg);
        return KS_CMDERROR;
    }
    //if(cmd->recv_len < 2)
    //{
    //	cmd->cmd_retcode = 0;
    //	strcpy(cmd->cmd_retmsg,"���������������ݴ���");
    //	cmd->cmd_retcode = 2;
    //	return KS_CMDERROR;
    //}
    sw1 = cmd->recv_buf[cmd->recv_len-2];
    sw2 = cmd->recv_buf[cmd->recv_len-1];
    if(sw1 != 0x90 && sw1 != 0x61) {
        ret = sw1;
        ret = ret*256 + sw2;
        cmd->cmd_retcode = ret;
        return cmd->cmd_retcode;
    }
    if(sw1 == 0x61 && sw2 != 0x00) {
        // 61XX ,���� 00C0 ȡ��������
        TRACE_ERR("�Զ�����ȡ������������");
        memset(&innerCmd,0,sizeof innerCmd);
        innerCmd.send_len = sprintf(szCmd,"00C00000%02X",sw2);
        innerCmd.send_buf = (unsigned char*)szCmd;
        innerCmd.recv_buf = cmd->recv_buf;
        innerCmd.cmd_type = 1; // 16 hex
        ret = cpucard_cmd(dev,&innerCmd,t);
        if(ret==0) {
            cmd->recv_len = innerCmd.recv_len;
        }
        cmd->cmd_retcode = innerCmd.cmd_retcode;
        return ret;
    }
    return 0;
}

int KSAPI config_card(ks_reader_dev_t *dev,KS_CPUCARD_TYPE t) {
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;
    if(t == CPUCARD_A)
        return dc_config_card(g_dev_hd,'A');
    else
        return dc_config_card(g_dev_hd,'B');
}
int KSAPI card_type() {
    return g_lastCardType;
}
void KSAPI set_logger(void *para) {
    KS_Log_Tracer::instance((KS_Log_Tracer*)para);
}

int KSAPI register_device_op(ks_device_op_t *op) {
    g_device_op.version = g_version;
    g_device_op.devname = g_devname;
    // �ӿں���
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