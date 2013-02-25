/* --------------------------------------------
 * 程序名称: F950998.cpp
 * 创建日期: 2008-1-11
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  下传数据文件
 * --------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "cpack.h"
#include "busqc.h"
#include "acctrans.h"

int F950998(TRUSERID *handle, int iRequest, ST_PACK *rpack, int *pRetCode, char *szMsg) {
    char szfile[256];
    char full_path[512] = "";
    int maxlen,ret,is_del;
    FILE *fp;
    ST_SDPACK *psd;
    char *pend;
    struct stat fst;
    memset(&fst,0,sizeof fst);

    is_del = rpack->lvol0;
    // 获取文件名, 去掉路径
    pend = strrchr(rpack->vsmess,'/');
    if(pend) {
        if(pend >= strlen(rpack->vsmess) + rpack->vsmess) {
            *pRetCode = E_INPUT_DATA_INVAILD;
            return -1;
        }
        strcpy(szfile,pend+1);
    } else
        strcpy(szfile, rpack->vsmess);
    maxlen = sizeof(ST_PACK) - 4;
    if (maxlen > 4096)
        maxlen = 4096;
    // 获取文件存放路径
    ret = GetSysParaVal(GLOBAL_DOWNLOAD_PATH,full_path);
    if(ret) {
        *pRetCode = ret;
        return -1;
    }
    strcat(full_path,"/");
    strcat(full_path,szfile);
    // 以二进制打开文件
    fp = fopen(full_path, "rb");
    if (fp == NULL) {
        sprintf(szMsg, "Cannot open the file:<%s>!", full_path);
        writelog(LOG_ERR,szMsg);
        *pRetCode = 9980;
    } else {
        psd = (ST_SDPACK *)rpack;
        while (!feof(fp)) {
            psd->usDataLength = fread(psd->data, 1, maxlen, fp);
            PutRowData(rpack);
        }
        fclose(fp);
        stat(full_path, &fst);
        sprintf(szMsg, "%ld", fst.st_mtime);
        if(is_del == 1) {
            // 删除原始文件
            unlink(full_path);
        }
        *pRetCode = 0;
    }
    SetCol(handle,F_LVOL0, F_VSMESS, 0);
    // 文件大小
    rpack->lvol0 = fst.st_size;
    des2src(rpack->vsmess, szMsg);
    PutRow(handle, rpack, pRetCode, szMsg);
    return 0;
}
