#ifndef _KSBU_H_
#define _KSBU_H_
#ifdef __cplusplus
extern "C" {
#endif

class CLogFile;
typedef struct _ST_PACK ST_PACK;

extern CLogFile g_LogFile;		// 被移到SvrLink.cpp中，作为系统必要的属性
extern ST_PACK *g_pArrays;		// 多包时使用
int ERR_DEAL(char *msg,int retcode);

#ifdef __cplusplus
}
#endif

#endif // _KSBU_H_
