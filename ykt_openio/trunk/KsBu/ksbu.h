#ifndef _KSBU_H_
#define _KSBU_H_
#ifdef __cplusplus
extern "C" {
#endif

class CLogFile;
typedef struct _ST_PACK ST_PACK;

extern CLogFile g_LogFile;		// ���Ƶ�SvrLink.cpp�У���Ϊϵͳ��Ҫ������
extern ST_PACK *g_pArrays;		// ���ʱʹ��
int ERR_DEAL(char *msg,int retcode);

#ifdef __cplusplus
}
#endif

#endif // _KSBU_H_
