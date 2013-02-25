#include "ksdevice.h"
#include <windows.h>
#include "ZT-C800.h"
#include "global_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "logfile.h"

static ks_device_op_t g_device_op;
static const char g_version[]="1.00";
static const char g_devname[]="zt-c800";
static int g_dev_hd = 0;
static char gErrMsg[512];
static int g_cpu_last_slot = -1;
static int g_lastCardType = 0;

#define SEND_HEAD	0xBA//define the head of the send 
#define RECE_HEAD	0xBD//define the head of the receive

#define GET_DECARD_SLOT(dev,p) do{ int s = get_decard_slot(dev,p); if(s != 0) { strcpy(gErrMsg,"�����Ŵ���"); return KS_PARAMERR;} }while(0)

/////////////////////////////////////////////////////////////////////
#if 0
bool CZTC800Com::PostRecv(unsigned char *lpBuffer, int nBufSize, long nTimeOut) {
    assert(ppszBuffer!=NULL);
    char pszBuffer[1024];
    int nReadBytes=0;
    DWORD nResult=0;
    DWORD nStartTime=GetTickCount();

    memset(pszBuffer,0,sizeof pszBuffer);

    m_nRecvLen=0;

    while( (long)(GetTickCount()-nStartTime)<(long)nTimeOut ) {
        nResult = InWaiting();
        if(nResult == 0) continue;
        nResult = min(nResult,nBufferSize-m_nRecvLen);
        if(Read((unsigned char*)pszBuffer+m_nRecvLen,nResult,nReadBytes)) {
            if(nReadBytes>0) m_nRecvLen += nReadBytes;
            if(m_nRecvLen>=2) break;
        }
    }
    if( m_nRecvLen<2 ) return false; //��ʱ
    if( m_nRecvLen>=pszBuffer[1]+2 ) { //�����Ѿ�����
        memcpy(ppszBuffer,pszBuffer,pszBuffer[1]+2);
        return true;
    }

    int nPack=0;
    nPack=pszBuffer[1];
    nPack=nPack+2-m_nRecvLen;
    while( (long)(GetTickCount()-nStartTime)<(long)nTimeOut ) {
        nResult = InWaiting();
        nResult = min(nResult,nBufferSize-m_nRecvLen);
        if(Read((unsigned char*)pszBuffer+m_nRecvLen,nResult,nReadBytes)) {
            if(nReadBytes>0) {
                m_nRecvLen += nReadBytes;
                nPack -= nReadBytes;
            }
            if(nPack<=0) break;
        }
    }
    if( nPack>0 ) return false;
    memcpy(ppszBuffer,pszBuffer,pszBuffer[1]+2);
    return true;
}
#endif

/////////////////////////////////////////////////////////////////////
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
    int i,found;
    typedef struct {
        unsigned char errCode;
        const char *errMsg;
    } _ErrDef;

    static _ErrDef PCDErr[] = {
        {CardOk,"�����ɹ�"},
        {CardPower,"��Ƭ��Դ״̬����ȷ"},
        {CardTimeout,"���ݽ��ճ�ʱ"},
        {CardParity,"���ݽ��գ�������ż��"},
        {CardLRC,"LRCУ�����"},
        {CardNoTS,"û�з���TS"},
        {CardNonStandard,"�Ǳ�׼��"},
        {CardTD1,"��֧��TD1�ж����Э������"},
        {CardTD2,"��֧��TD2�ж����Э������[WARN]"},
        {CardFIDI,"��֧��TA1�ж����FIDI"},
        {CardIFSI,"��֧�ֿ�ƬIFSI"},
        {CardTB3,"��֧�ֿ�ƬTB3"},
        {CardLc,"����ͷ��Lc����Lc��Ӧ����0��"},
        {CardNAD,"NAD�ڵ����T=1��"},
        {CardPCB,"��֧�ֿ�Ƭ���͵�PCB"},
        {CardLEN,"�����LEN�����LEN>32��"},
        {CardBreak,"��Ƭ��ֹ������T=1��"},
        {CardCard,"��Ƭ��������ʧ��"},
        {CardSync,"ͬ��ʧ��"},
        {CardNotOut,"��Ƭû�б��γ�"},
        {CardNotInsert,"��Ƭû�б�����"},
        {CardError,"����ʧ��"},
    };
    for(i = 0, found = 0; i < sizeof(PCDErr)/sizeof(PCDErr[0]); ++i) {
        if(nErrCode == PCDErr[i].errCode) {
            sprintf(gErrMsg,"Err-%04X:%s",nErrCode,PCDErr[i].errMsg);
            found = 1;
            break;
        }
    }
    if(!found) {
        sprintf(gErrMsg,"Err-%04X: δ֪����",nErrCode);
    }
    if(sErrMsg)
        strcpy(sErrMsg,gErrMsg);
    return gErrMsg;
}
// function open_device
static int KSAPI open_device(ks_reader_dev_t *dev) {
    BOOL ret;
    if(dev->port != 100) {
        SetBaud(9); // baud 38400
        ret = Connection(dev->cpuport-1);
        if(ret<=0) {
            sprintf(gErrMsg, "�򿪴��� COM%d ʧ��", dev->port);
            return KS_OPENDEVICE;
        }
    } else {
        SetBaud(9); // baud 38400
        ret = ConnectionUSBDevice();
        if(!ret) {
            strcpy(gErrMsg, "�򿪶�����USB�˿�ʧ��");
            return KS_OPENDEVICE;
        }
    }
    g_dev_hd = 1;
    return 0;
}
// function close_device
static int KSAPI close_device(ks_reader_dev_t *dev) {
    if(g_dev_hd) {
        Disconnection();
    }
    g_dev_hd = 0;
    return 0;
}

static int get_decard_slot(ks_reader_dev_t *dev,int SAMID) {
    int slot = 100;
    unsigned char atr[256]= {0};
    unsigned char rlen,ret;
    switch(SAMID) {
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
    if(g_cpu_last_slot != slot) {
        SetICCBaudRate(0);
        ret = IccPowerUp(atr,rlen);
        if(ret) {
            TRACE_ERR("PSAM����λ����");
            return KS_OPENDEVICE;
        }
        g_cpu_last_slot = slot;
    }
    return 0;
}

// function request_card
static int KSAPI request_card(ks_reader_dev_t *dev,char* phyid,KS_CARD_TYPE t) {
    int ret;
    unsigned short tagtype;
    unsigned char size,i;
    uint8 ucCardPhyID[8];
    uint8 rData[256];

    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    if(!g_dev_hd) {
        return KS_PORT_NOTOPEN;
    }
    if(t == KS_CPUCARD || t == KS_FIXCARD) {
        if(dev->cpuport == CARDSLOT_RF) {
            if(g_lastCardType == KS_CPUCARD || g_lastCardType == KS_FIXCARD) {
                MIFARE_Deselect();
            }
            ret = MIFARE_SelectCard(rData);
            if(ret) {
                TRACE_ERR("ѡ������");
                return KS_REQUESTCARD;

            }
            for(i = 0; i < 4; ++i)
                ucCardPhyID[i] = rData[3-i];

            g_lastCardType = KS_CPUCARD;
            dev->cardtype = g_lastCardType;

            dec2hex(ucCardPhyID,4,phyid);
            phyid[8]=0;
        } else {
            TRACE_ERR("�����������");
            return KS_REQUESTCARD;
        }
    } else {
        TRACE_ERR("�����������");
        return KS_REQUESTCARD;
    }
    return 0;
}

// function halt
static int KSAPI halt(ks_reader_dev_t *dev) {
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;
    MIFARE_Halt();
    return 0;
}

// function beep
static int KSAPI beep(ks_reader_dev_t *dev) {
    int ret=0;
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    BuzzerSound(2);
    return 0;
}
static int KSAPI beeperr(ks_reader_dev_t *dev) {
    int ret=0;
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    BuzzerSound(5);
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
        mode = 1;
    }
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    ret = MIFARE_LoginSector(sect_no,mode,(uint8*)key);
    if(ret)
        TRACE_ERR("��¼��ʧ��");

    return ret;
}

// function read_block
static int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block) {
    int ret;
    // TODO : ���ݿ������жϣ�ֻ�ܴ���32������֮ǰ��
    if(block_no >= 32*4 || block_no < 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    ret = MIFARE_ReadDataBlock(block_no,block);
    if(ret)
        TRACE_ERR("������ʧ��["<<ret<<"]");
    return ret;
}

// function write_block
static int KSAPI write_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,const uint8 *block) {
    int ret;
    // TODO : ���ݿ������жϣ�ֻ�ܴ���32������֮ǰ��
    if(block_no >= 32*4 || block_no <= 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    ret = MIFARE_WriteDataBlock(block_no,(uint8*)block);
    if(ret) {
        TRACE_ERR("д����ʧ��["<<ret<<"]");
        return KS_WRITECARD;
    }
    return 0;
}

// function decrement_card
static int KSAPI decrement_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount) {
    int ret;
    if(block_no >= 32*4 || block_no <= 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;
    uint8 data[4];
    memcpy(data,&amount,sizeof(data));
    ret = MIFARE_DecrementValue(block_no,data);
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
    uint8 data[4];
    memcpy(data,&amount,sizeof(data));
    ret = MIFARE_IncrementValue(block_no,data);
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

    ret = MIFARE_CopyValue(block_no,block_no+1);
    if(ret)
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

    ret = MIFARE_CopyValue(block_no,block_no+1);
    if(ret)
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
            //ret = IccPowerUp(buf,*len); // cpucard
            ret = MIFARE_GetATS(buf,*len);
            if(ret) {
                TRACE_ERR("ATS����");
            }
        } else {
            return KS_NOTSUPPORT;
        }
    } else {
        //TODO: SAM ��λ

        GET_DECARD_SLOT(dev,dev->cpuport);
        //ret = dc_cpureset(g_dev_hd,len,buf); // sam
        ret = 0;
    }
    if(ret) {
        GetErrMsgByErrCode(ret,gErrMsg);
        return KS_OPENDEVICE;
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
        ret = MIFARE_Deselect();
        if(ret) {
            GetErrMsgByErrCode(ret,gErrMsg);
            return KS_OPENDEVICE;
        }
        ret=MIFARE_Reset();
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

    if(dev->cputype <0 || dev->cputype >1)
        return KS_PARAMERR;

    cpupro = dev->cputype;
    cputype = g_cpu_last_slot;

    switch (dev->cpubaud) {
    default:
    case 9600:
        cputu = 0;
        break;
    case 38400:
        cputu = 1;
        break;
    }

    ret = SetICCBaudRate(cputu);
    if(ret) {
        GetErrMsgByErrCode(ret,gErrMsg);
        return KS_OPENDEVICE;
    }
    GET_DECARD_SLOT(dev,dev->cpuport);
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

    if(t == KS_CPUCARD || t == KS_FIXCARD) {
        // �ǽӴ�ʽ
        if(dev->cpuport == CARDSLOT_RF) {
            if(cmd->cmd_type == 0) {
                ret = MIFARE_ExchangeAPDU(cmd->send_buf,cmd->send_len,cmd->recv_buf,cmd->recv_len);
            } else {
                unsigned char ucCmd[512];
                int  iCmdLen=0;
                hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
                ret = MIFARE_ExchangeAPDU(ucCmd,iCmdLen,cmd->recv_buf,cmd->recv_len);
            }
        } else {
            return KS_NOTSUPPORT;
        }
    } else {
        // �Ӵ�ʽ
        if(dev->cpuport == CARDSLOT_RF) {
            return KS_CMDERROR;
        } else {
            GET_DECARD_SLOT(dev,dev->cpuport);

            if(cmd->cmd_type == 0) {
                ret = IccExchangeApdu(cmd->send_buf,cmd->send_len,cmd->recv_buf,cmd->recv_len);
            } else {
                unsigned char ucCmd[512];
                int  iCmdLen=0;
                hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
                ret = IccExchangeApdu(ucCmd,iCmdLen,cmd->recv_buf,cmd->recv_len);
            }
        }
    }


    if(ret) {
        if(cmd->recv_len <= 0) {
            TRACE_ERR("ִ��ָ����󣬵�û�з�������,ret["<<ret<<"]");
            return -1;
        }
    }
    sw1 = cmd->recv_buf[cmd->recv_len-2];
    sw2 = cmd->recv_buf[cmd->recv_len-1];
    if(sw1 != 0x90 && sw1 != 0x61) {
        ret = sw1;
        ret = ret*256 + sw2;
        cmd->cmd_retcode = ret;
        TRACE_ERR("ִ��ָ���״̬����,sw["<<std::hex<<(int)sw1<<" "<<(int)sw2<<"]");
        return cmd->cmd_retcode;
    }
    if(sw1 == 0x61 && sw2 != 0x00) {
        // 61XX ,���� 00C0 ȡ��������
        TRACE_ERR("�Զ���ȡ��������");
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
        return MIFARE_SetCardType(0);
    else
        return MIFARE_SetCardType(1);
}

//////////////////////////////////////////////////////////////
//
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
