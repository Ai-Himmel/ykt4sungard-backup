#include "Windows.h"
#include "ksdevice.h"
#include "global_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "logfile.h"
#include "MWRF32.h"


static ks_device_op_t g_device_op;
static const char g_version[]="1.0";
static const char g_devname[]="newcapec";
static int g_cpu_last_slot = CARDSLOT_RF + 1;
static int m_Reader = 0;
static HANDLE g_dev_hd = 0;
static int g_lastCardType = 0;

static char gErrMsg[256] = {0};

static CMwrf32App RWD;


int DbgOut(char *fmt, ...) {
    static char sprint_buf[1024];
    va_list args;
    int n;
    va_start(args, fmt);
    n = vsprintf(sprint_buf, fmt, args);
    va_end(args);
    OutputDebugString(sprint_buf);
    return n;
}

#define DEBUG(fmt, ...)/* \
            DbgOut("[%s@%s:%d] " fmt"\n", strrchr (__FILE__, '\\') == 0 ?  \
                                       __FILE__ : strrchr (__FILE__, '\\') + 1, \
									   __FUNCTION__, \
                                       __LINE__, __VA_ARGS__);
*/


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
    case 1:
        sprintf(gErrMsg,"Err-%04X:�޿�",nErrCode);
        break;
    case 2:
        sprintf(gErrMsg,"Err-%04X:CRCУ���",nErrCode);
        break;
    case 3:
        sprintf(gErrMsg,"Err-%04X:ֵ���",nErrCode);
        break;
    case 4:
        sprintf(gErrMsg,"Err-%04X:δ��֤����",nErrCode);
        break;
    case 5:
        sprintf(gErrMsg,"Err-%04X:��żУ���",nErrCode);
        break;
    case 6:
        sprintf(gErrMsg,"Err-%04X:ͨѶ����",nErrCode);
        break;
    case 8:
        sprintf(gErrMsg,"Err-%04X: ��������к�",nErrCode);
        break;
    case 10:
        sprintf(gErrMsg,"Err-%04X:��֤����ʧ��",nErrCode);
        break;
    case 11:
        sprintf(gErrMsg,"Err-%04X:���յ�����λ����",nErrCode);
        break;
    case 12:
        sprintf(gErrMsg,"Err-%04X:���յ������ֽڴ���",nErrCode);
        break;
    case 14:
        sprintf(gErrMsg,"Err-%04X:Transfer����",nErrCode);
        break;
    case 15:
        sprintf(gErrMsg,"Err-%04X:дʧ��",nErrCode);
        break;
    case 16:
        sprintf(gErrMsg,"Err-%04X:��ֵʧ��",nErrCode);
        break;
    case 17:
        sprintf(gErrMsg,"Err-%04X:��ֵʧ��",nErrCode);
        break;
    case 18:
        sprintf(gErrMsg,"Err-%04X:��ʧ��",nErrCode);
        break;
    case -0x10:
        sprintf(gErrMsg,"Err-%04X:PC���д��ͨѶ����",nErrCode);
        break;
    case -0x11:
        sprintf(gErrMsg,"Err-%04X:ͨѶ��ʱ",nErrCode);
        break;
    case -0x20:
        sprintf(gErrMsg,"Err-%04X:��ͨ�ſ�ʧ��",nErrCode);
        break;
    case -0x24:
        sprintf(gErrMsg,"Err-%04X:�����ѱ�ռ��",nErrCode);
        break;
    case -0x30:
        sprintf(gErrMsg,"Err-%04X:��ַ��ʽ����",nErrCode);
        break;
    case -0x31:
        sprintf(gErrMsg,"Err-%04X:�ÿ����ݲ���ֵ��ʽ",nErrCode);
        break;
    case -0x32:
        sprintf(gErrMsg,"Err-%04X:���ȴ���",nErrCode);
        break;
    case -0x40:
        sprintf(gErrMsg,"Err-%04X:ֵ����ʧ��",nErrCode);
        break;
    case -0x50:
        sprintf(gErrMsg,"Err-%04X:���е�ֵ������",nErrCode);
        break;
    default:
        sprintf(gErrMsg,"Err-%04X:������δ֪�Ĵ���",nErrCode);
        break;
    }

    if(sErrMsg)
        strcpy(sErrMsg,gErrMsg);
    return gErrMsg;
}
// function open_device
static int KSAPI open_device(ks_reader_dev_t *dev) {
    if(dev->port <5) {	//���ںţ�ȡֵΪ0��3
        g_dev_hd = RWD.rf_init(dev->port-1,dev->baud);
        if(!g_dev_hd) {
            sprintf(gErrMsg, "�򿪴��� COM%d ʧ��", dev->port);
            return KS_OPENDEVICE;
        }
    } else {
        return KS_PARAMERR;
    }

    DEBUG("open_device");

    return 0;
}
// function close_device
static int KSAPI close_device(ks_reader_dev_t *dev) {
    if(g_dev_hd!=NULL) {
        RWD.rf_exit(g_dev_hd);
    }
    g_dev_hd = 0;

    DEBUG("close_device" );
    return 0;
}



// function request_card
static int KSAPI request_card(ks_reader_dev_t *dev,char* phyid,KS_CARD_TYPE t) {
    int ret;
    unsigned long snr;
    uint8 ucCardPhyID[8];

    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    if(!g_dev_hd) {
        return KS_PORT_NOTOPEN;
    }

    ret= RWD.rf_card(g_dev_hd, 0, &snr);
    if(ret) {
        GetErrMsgByErrCode(ret,gErrMsg);
        TRACE_ERR("��⿨���� "<<gErrMsg);
        return KS_REQUESTCARD;
    }

    g_lastCardType = KS_MFCARD;

    dev->cardtype = g_lastCardType;
    set_4byte_int(ucCardPhyID,snr);
    dec2hex(ucCardPhyID,4,phyid);
    phyid[8]=0;

    DEBUG("request_card:[%s]",phyid );

    return 0;
}

// function halt
static int KSAPI halt(ks_reader_dev_t *dev) {
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;
    RWD.rf_halt(g_dev_hd);
    return 0;
}

// function beep
static int KSAPI beep(ks_reader_dev_t *dev) {
    if(!g_dev_hd) {
        int ret=0;
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    RWD.rf_beep(g_dev_hd,10);
    return 0;
}
static int KSAPI beeperr(ks_reader_dev_t *dev) {
    if(!g_dev_hd) {
        int ret=0;
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    RWD.rf_beep(g_dev_hd,160);
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

    char hex[16]= {0};
    bcd2asc(key, 6, hex);
    ret =  RWD.rf_load_key_hex(g_dev_hd,mode,sect_no,hex); // rf_load_key ��bug, �ᵼ�� keya ��֤��ͨ��

    //unsigned char stuff[7]={0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,0};
    //ret =  RWD.rf_load_key(g_dev_hd,mode,sect_no,stuff);
    if(ret) {
        GetErrMsgByErrCode(ret,gErrMsg);
        return KS_LOGINCARD;
    }
    ret = RWD.rf_authentication((int)g_dev_hd,mode,sect_no);
    if(ret) {
        GetErrMsgByErrCode(ret,gErrMsg);
        return KS_LOGINCARD;
    }
    return 0;
}

// function read_block
static int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block) {
    int ret;
    // TODO : ���ݿ������жϣ�ֻ�ܴ���16������֮ǰ��
    //if(block_no >= 64*4 || block_no < 0)
    //return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    memset(block, 0x30, 16);

    ret = RWD.rf_read(g_dev_hd,block_no,block);
    if(ret)
        return KS_READCARD;
    return 0;
}

// function write_block
static int KSAPI write_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,const uint8 *block) {
    int ret = 0;
    // TODO : ���ݿ������жϣ�ֻ�ܴ���16������֮ǰ��
    //if(block_no >= 64*4 || block_no <= 0)
    //return KS_BLOCK_OVERFLOW;

    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    //if(block_no%4 == 3)
    //{
    //	char tmp[64]={0};
    //	dec2hex(block,32,tmp);
    //	tmp[32]=0;
    //	DEBUG("write key block[%d][%s]", block_no, tmp);
    //}

    ret = RWD.rf_write(g_dev_hd,block_no,(uint8*)block);
    if(ret)
        return KS_WRITECARD;

    return 0;
}

// function decrement_card
static int KSAPI decrement_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount) {
    return 0;
}

// function increment_card
static int KSAPI increment_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount) {
    return 0;
}

// function transform_card
static int KSAPI transform_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no) {
    return 0;
}

// function restore_card
static int KSAPI restore_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no) {
    return 0;
}

// function procard_cmd
static int KSAPI procard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd) {
    return 0;
}

// function cpucard_poweron
static int KSAPI cpucard_poweron(ks_reader_dev_t *dev,KS_CARD_TYPE t,uint8 *len,uint8 *buf) {
    return 0;
}


// function reset
static int KSAPI reset(ks_reader_dev_t *dev,size_t msec) {
    return 0;
}


// function cpucard_setpara
static int KSAPI cpucard_setpara(ks_reader_dev_t *dev) {
    return 0;
}

// function cpucard_cmd
static int KSAPI cpucard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd,KS_CARD_TYPE t) {
    return 0;
}

int KSAPI config_card(ks_reader_dev_t *dev,KS_CPUCARD_TYPE t) {
    return 0;
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
