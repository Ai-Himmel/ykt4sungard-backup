#ifndef _KSBU_H_
#define _KSBU_H_
#ifdef __cplusplus
extern "C" {
#endif

CLogFile g_LogFile;		// ���Ƶ�SvrLink.cpp�У���Ϊϵͳ��Ҫ������
ST_PACK *g_pArrays;		// ���ʱʹ��
int ERR_DEAL(char *msg,int retcode);

#ifdef __cplusplus
}
#endif

#endif // _KSBU_H_
