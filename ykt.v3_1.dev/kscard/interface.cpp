#include "interface.h"
#include "CIniFile.h"
#include <Windows.h>
#include <fstream>
#include "logfile.h"
#include "kslicense.h"
#include "global_func.h"
#include "cardtypemanager.h"

extern ks_cardlib_license g_license;

//extern std::ofstream log;

extern CardReaderManager g_ReaderManager;


ks_card_info_t g_cardinfo;

static int s_is_load = 0;


extern std::string g_card_read_right;
extern std::string g_card_write_right;

extern std::string g_drtpip;
extern std::string g_portno;
extern std::string g_funcno;
extern std::string g_termno;

#if 0

static int do_load_device_layer(HMODULE m,ks_device_op_t* dev) {
    LOAD_DLLFUNC(m,register_device_op);
    if(register_device_op(dev)==0)
        return 0;
    TRACE2_LOG(("ע��Ӳ����ʧ��"));
    return -1;
}
#if USE_CASE_TYPE_CLASS==0
static int do_load_cardtype_layer(HMODULE m,ks_cardtype_op_t* cardtype)
#else
static int do_load_cardtype_layer(HMODULE m,ks_cardtype_base* cardtype)
#endif
{
    LOAD_DLLFUNC(m,register_cardtype_op);
    if(register_cardtype_op(g_CardType)==0) {
        return 0;
    }
    TRACE2_LOG(("ע�Ῠ���Ͳ�ʧ��"));
    return -1;
}
static int do_load_enc_layer(HMODULE m) {
    LOAD_DLLFUNC(m,register_enc_op);
    if(register_enc_op(&g_enc_op)==0)
        return 0;
    TRACE2_LOG(("ע���㷨��ʧ��"));
    return -1;
}
#endif

static int do_load_license(const char *path,const std::string &pubkey,const std::string &lcs) {
    int ret;
    char syspath[2048+1];
    char module_path[1024];
    if( !GetSystemDirectory( syspath ,sizeof(syspath) -1 ) ) {
        ks_setlasterr("��ȡϵͳ·��ʧ��",-1);
        return -1;
    }
    ret = g_license.load_public_key_file(pubkey.c_str());
    if(ret) {
        sprintf(module_path,"%s\\pub.key",syspath);

        TRACE2_LOG(("����pubkeyʧ��[%s],���Զ�ȡ[%s]",pubkey.c_str(), module_path));

        ret = g_license.load_public_key_file(module_path);
        if(ret) {
            TRACE2_LOG(("����pubkeyʧ�� [%s]",module_path));

            ks_setlasterr("���ع�Կʧ�ܣ������ļ��Ƿ����[pub.key]");
            return ret;
        } else {
            TRACE2_LOG(("����pubkey�ɹ� [%s]",module_path));
        }
    } else {
        TRACE2_LOG(("����pubkey�ɹ� [%s]",pubkey.c_str()));
    }

    ret = g_license.load_license_file(lcs.c_str());
    if(ret) {
        sprintf(module_path,"%s\\license.lcs",syspath);
        TRACE2_LOG(("����licenseʧ��[%s], ���Զ�ȡ[%s]",lcs.c_str(), module_path));

        ret = g_license.load_license_file(module_path);
        if(ret) {
            TRACE2_LOG(("����licenseʧ�� [%s]",module_path));

            ks_setlasterr("���ع�Կʧ�ܣ������ļ��Ƿ����[license.lcs]");
            return ret;
        } else {
            TRACE2_LOG(("����license�ɹ� [%s]",module_path));
        }
    } else {
        TRACE2_LOG(("����license�ɹ� [%s]",lcs.c_str()));
    }

    return 0;
}
static int do_check_interface() {
    char current[18]="";
    char expired[20]="";
    char cardright[2048];
    if(g_license.get_public_param("kscardlib.expired",expired,sizeof(expired)-1)) {
        ks_setlasterr("��Ȩ�ѹ���");
        return -1;
    }

    get_current_datetime(current);
    if(strncmp(current,expired,8)>0) {
        ks_setlasterr("��Ȩ�ѹ���");
        return -1;
    }

    memset(cardright,0,sizeof cardright);
    if(g_license.get_public_param("kscardlib.cardreadright",cardright,sizeof(cardright)-1)) {
        ks_setlasterr("δ����Ȩ��");
        return -1;
    }
    g_card_read_right = cardright;

    memset(cardright,0,sizeof cardright);
    if(g_license.get_public_param("kscardlib.cardwriteright",cardright,sizeof(cardright)-1)) {
        ks_setlasterr("δ����Ȩ��");
        return -1;
    }
    g_card_write_right = cardright;
    return 0;
}
int load_interface_layer(const char *path) {
    DCLR_LOGMSG("load_interface_layer");
    char module_path[1024];
    char param_value[2048+1];
    int param_len = 0;
    std::string sPortNo1,sPortNo2,sLibReader1,sLibReader2,sLibEnc,sLibCardType,sPubKey,sLicense;
    if(s_is_load == 1) {
        TRACE_LOG("�ײ��Ѿ����أ�����");
        return 0;
    }

    TRACE_LOG("��ȡ����");
    //free_interface_layer();
    sprintf(module_path,"%s\\kscard.ini",path);
    CCIniFile ini(module_path);

    TRACE2_LOG(("��ȡ������INI[%s]",module_path));

    sPubKey = ini.ReadString("INTERFACE","PUBKEY","");
    if(sPubKey.empty()) {
        sprintf(module_path,"%s\\pub.key",path);
        sPubKey = module_path;
    } else {
        // ʹ��kscard.dll Ŀ¼�е�pubkey
        sprintf(module_path,"%s\\%s",path, sPubKey.c_str());
        sPubKey = module_path;
    }

    sLicense = ini.ReadString("INTERFACE","LICENSE","");
    if(sLicense.empty()) {
        sprintf(module_path,"%s\\license.lcs",path);
        sLicense = module_path;
    } else {
        // ʹ��kscard.dll Ŀ¼�е�License
        sprintf(module_path,"%s\\%s",path, sLicense.c_str());
        sLicense = module_path;
    }

    TRACE2_LOG(("��ȡlicense[%s]",sLicense.c_str()));
    if(do_load_license(path,sPubKey,sLicense)) {
        ks_setlasterr("����license����");
        return -1;
    }
    if(do_check_interface()) {
        ks_setlasterr("���license����");
        return -1;
    }
    sPortNo1=ini.ReadString("INTERFACE","PORTNO1",0);
    sPortNo2=ini.ReadString("INTERFACE","PORTNO2",0);

    g_drtpip=ini.ReadString("INTERFACE","DRTPIP",0);
    g_portno=ini.ReadString("INTERFACE","PORTNO",0);
    g_funcno=ini.ReadString("INTERFACE","FUNCNO",0);
    g_termno=ini.ReadString("INTERFACE","TERMNO",0);

    TRACE2_LOG(("��ȡ DRTP ���� DRTPIP[%s] PORTNO[%s] FUNCNO[%s]", g_drtpip.c_str(), g_portno.c_str(), g_funcno.c_str()));

    TRACE_LOG("���ؿ����Ϳ�");
    if(CardTypeManager::instance()->loadCardTypeDLL(&g_license,path)!=0) {
        memset(param_value,0,sizeof param_value);
        CardTypeManager::instance()->getErrorMsg(param_value,"����DLLʧ��");
        TRACE_LOG(param_value);
        ks_setlasterr(param_value);
        return -1;
    }
    TRACE_LOG("���ض�������");
    if(g_ReaderManager.loadReaderDLL(&g_license,path)!=0) {
        memset(param_value,0,sizeof param_value);
        g_ReaderManager.getErrorMsg(param_value);
        TRACE_LOG(param_value);
        ks_setlasterr(param_value);
        return -1;
    }
    TRACE_LOG("��ʼ������");
    if(g_ReaderManager.initAllCardType(&g_license,CardTypeManager::instance())!=0) {
        memset(param_value,0,sizeof param_value);
        CardTypeManager::instance()->getErrorMsg(param_value);
        TRACE_LOG(param_value);
        ks_setlasterr(param_value);
        return -1;
    }
    g_ReaderManager.setReaderPortByNo(1,atoi(sPortNo1.c_str()),115200);
    if(g_ReaderManager.getReaderCount() == 2) {
        g_ReaderManager.setReaderPortByNo(2,atoi(sPortNo2.c_str()),115200);
    }
    TRACE2_LOG(("���صײ�ɹ�"));
    param_len = sizeof(param_value)-1;
    g_license.get_public_param(ks_cardlib_license::LCNS_CUST_ID,param_value,param_len);
    TRACEMSG_LOG("CUST["<<param_value<<"]");
    g_license.get_public_param(ks_cardlib_license::LCNS_EXPIRED_DATE,param_value,param_len);
    TRACEMSG_LOG("EXPIREDATE["<<param_value<<"]");
    s_is_load = 1;
    return 0;

}

int free_interface_layer() {
    CardTypeManager::instance()->freeAll();
    g_ReaderManager.freeAll();
    s_is_load = 0;
    return 0;
}