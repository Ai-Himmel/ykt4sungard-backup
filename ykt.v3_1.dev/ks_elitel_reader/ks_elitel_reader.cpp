#include "ksdevice.h"
#include "global_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <windows.h>
#include <exception>
#include "ks_elitel_reader.h"
#include <fstream>

static ks_device_op_t g_device_op;
static const char g_version[]="1.00";
static const char g_devname[]="elitel";
static int g_cpu_last_slot = CARDSLOT_RF + 1;
static int m_Reader = 0;
static HANDLE g_dev_hd = 0;

static int g_lastCardType = 0;

static long g_default_timeout = 5000;

std::ofstream log("elitel.log");
static char gErrMsg[256] = {0};

#define GET_DECARD_SLOT(dev,p) do{ int s = get_decard_slot(dev,p); if(s != 0) { strcpy(gErrMsg,"卡座号错误"); return KS_PARAMERR;} }while(0)

static CElitelCom g_comport;

///////////////////////////////////////////////////////////////////////////
CElitelCom::CElitelCom():CComSmart() {
}
CElitelCom::~CElitelCom() {
}

/*=================================================================
* Function ID :  PostRecv
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  从服务端接收数据
* Notice	  :  pszBuffer 保存接收的数据   nBuffersize 缓冲区长度
*			  :	 nTimeOut 等待时间
*
*=================================================================*/
bool CElitelCom::PostRecv(unsigned char *ppszBuffer, int nBufferSize, long nTimeOut) {
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
    if( m_nRecvLen<2 ) return false; //超时
    if( m_nRecvLen>=pszBuffer[1]+2 ) { //数据已经收完
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

static int KSAPI reset(ks_reader_dev_t *dev,size_t msec);
//////////////////////////////////////////////////////////////////////////
static int pack_pos_cmd(const unsigned char *data,int len,unsigned char *cmd) {
    if(len+2>256)
        return -1;
    cmd[0] = 0x80;
    cmd[1] = len;
    memcpy(cmd+2,data,len);
    return len+2;
}
static int pack_rfuim_cmd(const unsigned char *data,int len,unsigned char *cmd) {
    if(len+2>256)
        return -1;
    cmd[0] = 0xA0;
    cmd[1] = len;
    memcpy(cmd+2,data,len);
    return len+2;
}
/*
static int pack_cpucard_cmd(const unsigned char *data,int len,unsigned char *cmd)
{
	int offset;
	if(len+7>256)
		return -1;
	offset = 0;
	cmd[offset++] = 0xC8;
	cmd[offset++] = len+5;
	memcpy(cmd+offset,"\x40\x53\x00\x00",4);
	offset+=4;
	cmd[offset++] = len;
	memcpy(cmd+offset,data,len);
	return len+offset;
}
*/
static int pack_cpucard_cmd(const unsigned char *data,int len,unsigned char *cmd) {
    if(len+2>256)
        return -1;
    cmd[0] = 0xC8;
    cmd[1] = len;
    memcpy(cmd+2,data,len);
    return len+2;
}

static int do_send_recv_pos_cmd(const unsigned char *cmd,int len,unsigned char *recv,int &recvlen,int timeout = 1000) {
    unsigned char send_cmd[256];
    int rlen;
    len = pack_pos_cmd(cmd,len,send_cmd);
    /*
    if(!g_comport.PostSend((char*)send_cmd,len,timeout))
    {
    	return -1;
    }
    if(!g_comport.PostRecv((char*)send_cmd,sizeof(send_cmd),timeout))
    {
    	return -2;
    }
    */
    recvlen = 256;
    if(!g_comport.SendCommand(send_cmd,len,send_cmd,&recvlen,timeout)) {
        return -1;
    }
    rlen = send_cmd[1];
    recvlen = rlen;
    memcpy(recv,send_cmd+2,recvlen);
    if(send_cmd[rlen] == 0x90 && send_cmd[rlen+1] == 0x00) {
        return 0;
    }
    return -3;
}

static int do_send_recv_rfuim_cmd(const unsigned char *cmd,int len,unsigned char *recv,int &recvlen,int timeout = 1000) {
    unsigned char send_cmd[256];
    int rlen;
    len = pack_rfuim_cmd(cmd,len,send_cmd);
    /*
    if(!g_comport.PostSend((char*)send_cmd,len,timeout))
    {
    	return -1;
    }
    if(!g_comport.PostRecv((char*)send_cmd,sizeof(send_cmd),timeout))
    {
    	return -2;
    }
    */
    recvlen = 256;
    if(!g_comport.SendCommand(send_cmd,len,send_cmd,&recvlen,timeout)) {
        return -1;
    }
    rlen = send_cmd[1];
    recvlen = rlen;
    memcpy(recv,send_cmd+2,recvlen);
    if(send_cmd[rlen] == 0x90 && send_cmd[rlen+1] == 0x00) {
        return 0;
    }
    return -3;
}
static int do_send_recv_cpu_cmd(const unsigned char *cmd,int len,unsigned char *recv,int &recvlen,int timeout = 1000) {
    unsigned char send_cmd[300];
    int rlen;
    len = pack_cpucard_cmd(cmd,len,send_cmd);
    /*
    if(!g_comport.PostSend((char*)send_cmd,len,timeout))
    {
    	return -1;
    }
    if(!g_comport.PostRecv((char*)send_cmd,sizeof(send_cmd),timeout))
    {
    	return -2;
    }
    */
    recvlen = 256;
    if(!g_comport.SendCommand(send_cmd,len,send_cmd,&recvlen,timeout)) {
        return -1;
    }
    rlen = send_cmd[1];
    recvlen = rlen;
    memcpy(recv,send_cmd+2,recvlen);
    if(send_cmd[rlen] == 0x90 && send_cmd[rlen+1] == 0x00) {
        return 0;
    }
    return -3;
}
static int do_send_recv_cpucard_cmd(const unsigned char *cmd,int len,unsigned char *recv,int &recvlen,int timeout = 1000) {
    unsigned char send_cmd[300];
    uint8 temp[300];
    int rlen,offset;
    if(len + 7 > 256)
        return -1;
    memcpy(temp,"\x40\x53\x00\x00",4);
    offset = 4;
    temp[offset++] = len;
    memcpy(temp+offset,cmd,len);
    offset += len;
    len = pack_cpucard_cmd(temp,offset,send_cmd);
    /*
    if(!g_comport.PostSend((char*)send_cmd,len,timeout))
    {
    	return -1;
    }
    if(!g_comport.PostRecv((char*)send_cmd,sizeof(send_cmd),timeout))
    {
    	return -2;
    }
    */
    recvlen = 256;
    if(!g_comport.SendCommand(send_cmd,len,send_cmd,&recvlen,timeout)) {
        return -1;
    }
    rlen = send_cmd[1];
    recvlen = rlen;
    memcpy(recv,send_cmd+2,recvlen);
    if(send_cmd[rlen] == 0x90 && send_cmd[rlen+1] == 0x00) {
        return 0;
    }
    return -3;
}

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
static int KSAPI open_device(ks_reader_dev_t *dev) {
    int ret;
    uint8 data[256];
    uint8 cmd[256];
    int len;
    if(dev->devtype == KS_READER_COM) {
        char comstr[64];
        sprintf(comstr,"\\\\.\\COM%d",dev->port);
        if(g_comport.Open(comstr,115200) == false) {
            sprintf(gErrMsg, "打开串口 COM%d 失败", dev->port);
            return KS_OPENDEVICE;
        }
        // 连接RF 读卡器
        /*
        len = 29;
        memcpy(data,"\x90\xB0\x01\x00\x18\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00\x00\x03\x00\x00\x01\x00\x00\x00\x00\x00",len);
        if(do_send_recv_pos_cmd(data,len,cmd,len,g_default_timeout))
        {
        	g_comport.Close();
        	sprintf(gErrMsg, "打开串口 COM%d 失败", dev->port);
        	return KS_OPENDEVICE;
        }
        */
    } else {
        strcpy(gErrMsg, "打开读卡器USB端口失败");
        return KS_OPENDEVICE;
    }
    gErrMsg[0]=0;
    g_dev_hd = g_comport.handle();
    return 0;
}
// function close_device
static int KSAPI close_device(ks_reader_dev_t *dev) {
    if(g_dev_hd!=NULL) {
        unsigned char data[256];
        int len;
        len = 5;
        memcpy(data,"\x90\xb0\x00\x00\x00",len);
        do_send_recv_pos_cmd(data,len,data,len,1000);
        g_comport.Close();
    }
    g_dev_hd = 0;
    return 0;
}
// function beep
static int KSAPI beep(ks_reader_dev_t *dev) {
    int ret=0;
    int len;
    unsigned char data[256];
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    //
    len = 5;
    memcpy(data,"\x90\xB0\x0D\x010\x00",len);
    do_send_recv_pos_cmd(data,len,data,len,g_default_timeout);
    return 0;
}
static int KSAPI beeperr(ks_reader_dev_t *dev) {
    int ret=0;
    int len;
    unsigned char data[256];
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    //
    len = 5;
    memcpy(data,"\x90\xB0\x0D\xA0\x00",len);
    do_send_recv_pos_cmd(data,len,data,len,g_default_timeout);
    return 0;
}

// function halt
static int KSAPI halt(ks_reader_dev_t *dev) {
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;
    unsigned char data[64];
    int len;
    len = 5;
    memcpy(data,"\x40\x04\x80\x00\x00",len);
    if(do_send_recv_pos_cmd(data,len,data,len,g_default_timeout)==0)
        return 0;
    return KS_REQUESTCARD;
}
// function request_card
static int KSAPI request_card(ks_reader_dev_t *dev,char* phyid,KS_CARD_TYPE t) {
    int ret,i;
    unsigned long snr;
    unsigned short tagtype;
    unsigned char size,sw1,sw2;
    uint8 ucCardPhyID[8];
    uint8 rData[256];
    uint8 cmd[256];
    int len,rlen,retries;
    //g_lastCardType = 0;
    gErrMsg[0]=0;
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    if(!g_dev_hd) {
        return KS_PORT_NOTOPEN;
    }
    /*
    if(KS_SIMCARD ==  t )
    {
    	if(KS_SIMCARD == g_lastCardType || 0 == g_lastCardType)
    	{
    		// 上次寻卡是手机卡，不用reset
    	}
    	if(dev->cpuport == CARDSLOT_RF)
    	{
    		len = 5;
    		retries = 10;
    		while(--retries > 0)
    		{
    			memset(rData,0,sizeof(rData));
    			memcpy(cmd,"\x90\xB0\x04\x00\x00",5);
    			if(do_send_recv_pos_cmd(cmd,5,rData,rlen,300))
    			{
    				if(rData[0] == 0x9C && rData[1] == 0x02)
    				{
    					// read success
    					break;
    				}
    				else if(rData[0] == 0x9C && rData[1] == 0x03)
    				{

    					Sleep(100); // 100ms
    				}
    			}
    		}
    		if(retries == 0)
    		{
    			TRACE_ERR("检测RFUIM卡超时");
    			return KS_REQUESTCARD;
    		}
    		if((rData[2] & 0xF0) != 0x10) // 2.4 G 卡
    		{
    			TRACE_ERR("检测RFUIM状态错误,code["<<(int)rData[2]<<"]");
    			return KS_REQUESTCARD;
    		}
    		memcpy(ucCardPhyID,rData+3,8); // physical id
    		dec2hex(ucCardPhyID,8,phyid);
    		phyid[16]=0;
    		dev->cardtype = KS_SIMCARD;
    		g_lastCardType = dev->cardtype;
    		return 0;
    	}
    	else
    	{
    		TRACE_ERR("发送手机卡寻卡指令,参数错误");
    		return KS_REQUESTCARD;
    	}
    }
    else if(KS_MFCARD ==t || KS_CPUCARD == t || KS_FIXCARD == t)
    {
    	len = 5;
    	retries = 3;
    	if(KS_SIMCARD == g_lastCardType || 0 == g_lastCardType)
    	{
    		// 上次寻卡是手机卡，不用reset
    	}
    	else
    	{
    		reset(dev,300);
    	}
    	while(--retries > 0)
    	{
    		memcpy(cmd,"\x90\xB0\x04\x52\x00",5);
    		memset(rData,0,sizeof(rData));
    		if(do_send_recv_pos_cmd(cmd,5,rData,rlen,300))
    		{
    			if(rData[0] == 0x9C && rData[1] == 0x02)
    			{
    				// read success
    			}
    			else if(rData[0] == 0x9C && rData[1] == 0x03)
    			{
    				Sleep(100);
    				continue;
    			}
    		}
    		else
    		{
    			TRACE_ERR("检测IC读卡器无应答");
    			return KS_REQUESTCARD;
    		}

    		if(rData[2] != 0x45)
    		{
    			TRACE_ERR("检测IC状态错误code["<<(int)rData[2]<<"]");
    			return KS_REQUESTCARD;
    		}
    		if(memcmp(rData+7,"\x04\x00",2) == 0
    			|| memcmp(rData+7,"\x02\x00",2) == 0)
    		{
    			// m1 卡
    			if(rData[9] != 0x08)
    			{
    				// 7+1 卡
    				dev->cardtype = KS_FIXCARD;
    			}
    			else
    			{
    				dev->cardtype = KS_MFCARD;
    			}
    			break;
    		}
    		else if(memcmp(rData+7,"\x08\x00",2) == 0)
    		{
    			// CPU 卡
    			dev->cardtype = KS_CPUCARD;
    		}
    		else
    		{
    			TRACE_ERR("检测IC卡时，无法识别卡类型");
    			return KS_REQUESTCARD;
    		}
    	}
    	if(retries == 0)
    	{
    		TRACE_ERR("检测IC卡超时");
    		return KS_REQUESTCARD;
    	}
    	// read success
    	for(i = 0;i < 4; ++i)
    		ucCardPhyID[3-i] = rData[3+i]; // physical id

    	if(dev->cardtype == KS_FIXCARD || dev->cardtype == KS_CPUCARD)
    	{
    		// CPU 卡reset
    		if(t == KS_CPUCARD || t == KS_FIXCARD)
    		{
    			len = 5;
    			memcpy(cmd,"\x40\x50\x00\x00\x00",len);
    			if(do_send_recv_cpu_cmd(cmd,len,rData,rlen,300))
    			{
    				TRACE_ERR("检测IC卡为CPU卡，CPU卡复位错误");
    				return KS_REQUESTCARD;
    			}
    		}
    	}
    	dec2hex(ucCardPhyID,4,phyid);
    	phyid[8] = 0;
    	g_lastCardType = dev->cardtype;
    	return 0;
    }
    */
    if(g_lastCardType != 0 ) { //&& g_lastCardType != KS_SIMCARD && g_lastCardType != KS_MFCARD)
        reset(dev,300);
    }
    len = 5;
    retries = 3;
    while(--retries > 0) {
        memcpy(cmd,"\x90\xB0\x04\x52\x00",5);
        memset(rData,0,sizeof(rData));
        if(do_send_recv_pos_cmd(cmd,5,rData,rlen,300)) {
            if(rData[0] == 0x9C && rData[1] == 0x02) {
                // read success
            } else if(rData[0] == 0x9C && rData[1] == 0x03) {
                Sleep(100);
                continue;
            }
        } else {
            TRACE_ERR("检测IC读卡器无应答");
            return KS_REQUESTCARD;
        }
        // 如果是手机卡
        if(rData[2] != 0x45) {
            // SIMCARD
            memcpy(ucCardPhyID,rData+3,8); // physical id
            dec2hex(ucCardPhyID,8,phyid);
            phyid[16]=0;
            dev->cardtype = KS_SIMCARD;
            g_lastCardType = dev->cardtype;
            return 0;
        } else {
            if(memcmp(rData+7,"\x04\x00",2) == 0
                    || memcmp(rData+7,"\x02\x00",2) == 0) {
                // m1 卡
                if(rData[9] == 0x08) {
                    // mifare one
                    dev->cardtype = KS_MFCARD;
                } else if(rData[9] == 0x18) {
                    // mifare one
                    //if(memcmp(rData+7,"\x02\x00",2) == 0)  S70
                    dev->cardtype = KS_MFCARD;
                } else if(rData[9] != 0x28) {
                    // 7+1 卡
                    dev->cardtype = KS_FIXCARD;
                } else {
                    dev->cardtype = KS_CPUCARD;
                }
            } else if(memcmp(rData+7,"\x08\x00",2) == 0) {
                // CPU 卡
                dev->cardtype = KS_CPUCARD;
            } else {
                TRACE_ERR("检测IC卡时，无法识别卡类型");
                return KS_REQUESTCARD;
            }
            // read success
            for(i = 0; i < 4; ++i)
                ucCardPhyID[3-i] = rData[3+i]; // physical id
            dec2hex(ucCardPhyID,4,phyid);
            phyid[8] = 0;
            g_lastCardType = dev->cardtype;
            return 0;
        }
    }
    if(retries == 0) {
        TRACE_ERR("检测IC卡超时");
        return KS_REQUESTCARD;
    }


    TRACE_ERR("传入参数有误");
    return KS_REQUESTCARD;
}
// function login_card
static int KSAPI login_card(ks_reader_dev_t *dev,ks_card_info_t *card,int sect_no,
                            KS_MF_KEYTYPE keytype,const uint8 *key) {
    int ret,retcode;
    uint8 data[24];
    uint8 cmd[256];
    int len;
    uint8 mode;
    if(keytype == MF_KEYA) {
        mode = 1;
    } else {
        mode = 0;
    }
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    len = 2;
    memcpy(data,"\x40\x08",2);
    data[len++] = sect_no;
    data[len++] = mode;
    data[len++] = 0x06;
    memcpy(data+len,key,6);
    len+=6;
    if(do_send_recv_pos_cmd(data,len,cmd,len,g_default_timeout)==0)
        return 0;
    retcode=cmd[0]*256+cmd[1];
    return retcode;
}

// function read_block
static int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block) {
    int ret;
    uint8 data[64];
    uint8 cmd[256];
    int len;
    // TODO : 根据卡类型判断，只能处理32个扇区之前的
    if(block_no >= 32*4 || block_no < 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    len = 5;
    memcpy(data,"\x40\x02\x01\x00\x00",len);
    data[3] = block_no % 4;
    if(do_send_recv_pos_cmd(data,len,cmd,ret,g_default_timeout)!=0)
        return KS_READCARD;
    if(ret < 18)
        return KS_READCARD;

    memcpy(block,cmd,16);
    return 0;
}

// function write_block
static int KSAPI write_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,const uint8 *block) {
    int ret;
    uint8 data[64];
    uint8 cmd[256];
    int len;
    // TODO : 根据卡类型判断，只能处理32个扇区之前的
    if(block_no >= 32*4 || block_no < 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    len = 5;
    memcpy(data,"\x40\x02\x02\x00\x10",len);
    data[3] = block_no % 4;
    memcpy(data+len,block,16);
    len += 16;
    if(do_send_recv_pos_cmd(data,len,cmd,ret,g_default_timeout)!=0)
        return KS_READCARD;
    return 0;
}

// function decrement_card
static int KSAPI decrement_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount) {
    int ret;
    if(block_no >= 32*4 || block_no <= 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;
    return KS_NOTSUPPORT;
}

// function increment_card
static int KSAPI increment_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount) {
    int ret;
    if(block_no >= 32*4 || block_no <= 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;
    return KS_NOTSUPPORT;
}

// function transform_card
static int KSAPI transform_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no) {

    int ret;
    if(block_no >= 32*4 || block_no <= 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    return KS_NOTSUPPORT;
}

// function restore_card
static int KSAPI restore_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no) {
    int ret;
    if(block_no >= 32*4 || block_no <= 0)
        return KS_BLOCK_OVERFLOW;
    if(!g_dev_hd)
        return KS_PORT_NOTOPEN;

    return KS_NOTSUPPORT;
}

// function procard_cmd
static int KSAPI procard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd) {
    return 0;
}

// function cpucard_poweron
static int KSAPI cpucard_poweron(ks_reader_dev_t *dev,KS_CARD_TYPE t,uint8 *len,uint8 *buf) {
    int ret;
    uint8 cmd[256];
    uint8 data[256];
    int rlen;
    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }

    if( t == KS_MFCARD) // mifare card
        return KS_NOTSUPPORT;
    else if(t == KS_CPUCARD || t == KS_FIXCARD) {
        if(dev->cpuport == CARDSLOT_RF) {
            //ret = dc_pro_reset(g_dev_hd,len,buf); // cpucard
            rlen = 5;
            memcpy(cmd,"\x40\x50\x00\x00\x00",rlen);
            if(do_send_recv_cpu_cmd(cmd,rlen,data,rlen,300)) {
                return KS_READCARD;
            }
            return 0;
        } else {
            return KS_NOTSUPPORT;
        }
    } else {
        return KS_NOTSUPPORT;
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
    int rlen,len;
    unsigned char rdata[64];
    uint8 cmd[64];

    if(!g_dev_hd) {
        ret=open_device(dev);
        if(ret)
            return ret;
    }
    if(dev->cpuport == CARDSLOT_RF) {
        len = 5;
        memcpy(cmd,"\x40\x51\x00\x00\x00",len);
        //memcpy(cmd,"\x40\x04\x80\x00\x00",len);
        do_send_recv_cpu_cmd(cmd,len,rdata,len,300);
        /*
        {
        	return KS_READCARD;
        }
        */
        return 0;
    } else {
        return KS_NOTSUPPORT;
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
    return 0;
    /*
    uint8 cputype,cpupro,cputu;

    GET_DECARD_SLOT(dev,dev->samport);
    if(dev->cputype <0 || dev->cputype >1)
    	return KS_PARAMERR;

    cpupro = dev->cputype;
    cputype = g_cpu_last_slot;

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
    ret = dc_setcpupara(g_dev_hd,cputype,cpupro,cputu);
    if(ret)
    {
    	GetErrMsgByErrCode(ret,gErrMsg);
    	return KS_OPENDEVICE;
    }
    return 0;
    */
}

// function cpucard_cmd
static int KSAPI cpucard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd,KS_CARD_TYPE t) {
    int ret;
    uint8 sw1,sw2;
    int rlen;
    char szCmd[256];
    ks_cpu_cmd_t innerCmd;
    cmd->cmd_retcode=0;
    assert(dev != NULL);
    if(!g_dev_hd) {
        strcpy(gErrMsg,"读卡器端口未打开");
        strcpy(cmd->cmd_retmsg,gErrMsg);
        return KS_PORT_NOTOPEN;
    }

    if(t == KS_SIMCARD) {
        // 非接触式
        if(dev->cpuport == CARDSLOT_RF) {
            if(cmd->cmd_type == 0) {
                ret = do_send_recv_rfuim_cmd(cmd->send_buf,cmd->send_len,cmd->recv_buf,rlen,g_default_timeout);
                cmd->recv_len = rlen;
            } else {
                unsigned char ucCmd[512];
                int  iCmdLen=0;
                hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
                ret = do_send_recv_rfuim_cmd(ucCmd,iCmdLen,cmd->recv_buf,rlen,g_default_timeout);
                cmd->recv_len = rlen;
            }
        } else {
            return KS_NOTSUPPORT;
        }
    } else if(t == KS_CPUCARD || t == KS_FIXCARD) {
        // 非接触式
        if(dev->cpuport == CARDSLOT_RF) {
            if(cmd->cmd_type == 0) {
                ret = do_send_recv_cpucard_cmd(cmd->send_buf,cmd->send_len,cmd->recv_buf,rlen,g_default_timeout);
                cmd->recv_len = rlen;
            } else {
                unsigned char ucCmd[512];
                int  iCmdLen=0;
                hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
                ret = do_send_recv_cpucard_cmd(ucCmd,iCmdLen,cmd->recv_buf,rlen,g_default_timeout);
                cmd->recv_len = rlen;
            }
        } else {
            return KS_NOTSUPPORT;
        }
    } else if(t == KS_MFCARD) {
        // 非接触式
        if(dev->cpuport == CARDSLOT_RF) {
            if(cmd->cmd_type == 0) {
                ret = do_send_recv_pos_cmd(cmd->send_buf,cmd->send_len,cmd->recv_buf,rlen,g_default_timeout);
                cmd->recv_len = rlen;
            } else {
                unsigned char ucCmd[512];
                int  iCmdLen=0;
                hex2dec((char*)cmd->send_buf,cmd->send_len,ucCmd,iCmdLen);
                ret = do_send_recv_pos_cmd(ucCmd,iCmdLen,cmd->recv_buf,rlen,g_default_timeout);
                cmd->recv_len = rlen;
            }
        } else {
            return KS_NOTSUPPORT;
        }
    } else {
        // 接触式
        return KS_NOTSUPPORT;
    }
    if(ret<0 && ret > -3) {
        cmd->cmd_retcode = 0;
        GetErrMsgByErrCode(ret,gErrMsg);
        strcpy(cmd->cmd_retmsg,gErrMsg);
        return KS_CMDERROR;
    }

    sw1 = cmd->recv_buf[cmd->recv_len-2];
    sw2 = cmd->recv_buf[cmd->recv_len-1];
    if(sw1 != 0x90 && sw1 != 0x61) {
        ret = sw1;
        ret = ret*256 + sw2;
        cmd->cmd_retcode = ret;
        return cmd->cmd_retcode;
    }
    if(sw1 == 0x61 && sw2 != 0x00) {
        TRACE_ERR("自动发起取后续数据请求");
        // 61XX ,调用 00C0 取后续数据
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