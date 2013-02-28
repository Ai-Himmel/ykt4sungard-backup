#ifndef _KSBU_H_
#define _KSBU_H_
#ifdef __cplusplus
extern "C" {
#endif


void getpos(char *v_filename,int v_lineno);
void errlog(int level,char *fmt,...);
#define writelog getpos(__FILE__,__LINE__),errlog


int ERR_DEAL(char *msg,int retcode);

#ifdef __cplusplus
}
#endif

#endif // _KSBU_H_
