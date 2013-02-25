/* ----------------------------------------------------------
 * 程序名称：F930071.cpp
 * 创建日期：2007-8-16
 * 程序作者：
 * 版本信息：1.0.0.0
 * 程序功能：采集设备心跳数据
 * --------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "dictionary.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "acctrans.h"

static int g_flag = 0;
static int g_FrontType = SUBSYSTYPE_XSQ;
static int g_devtypeflag = 0;

static int do_check_buffer(char *status_buffer, const char *op_time) {
    int i;
    int buf_len;
    int ret;
    int deviceid = 0;
    char dev_phyno[31] = "";
    int dev_state = 0;
    T_t_devmonitor dev_monitor;
    char temp[3] = "";
    static const int sect_len = 10;
    char* delim = ";";
    char* delim2 = ",";
    char *devstatus_buffer;
    buf_len = strlen(status_buffer);
    char lastchar[2] = "";
    if (buf_len <= 0) {
        return 0;
    }
    if (g_devtypeflag == 3) {
        //判断status_buffer最后一位是否为 ';'
        strncpy(lastchar, status_buffer + buf_len - 1 , 1);
        if (strncmp(lastchar, ";", 1) != 0) {
            writelog(LOG_ERR, "上送记录不完整,status_buffer[%s].", status_buffer);
            return -1;
        }
        writelog(LOG_INFO, "上送记录,status_buffer[%s].", status_buffer);
        devstatus_buffer = strtok(status_buffer, delim);
        while (devstatus_buffer != NULL) {
            writelog(LOG_INFO, "devstatus_buffer=[%s]\n", devstatus_buffer);
            char* buf = strstr(devstatus_buffer, delim2);
            memset(temp, 0, sizeof temp);
            strncpy(temp, buf + 1 , 2);
            dev_state = strtoul(temp, NULL, 16);
            memset(dev_phyno, 0, sizeof dev_phyno);
            sscanf(devstatus_buffer, "%[^,]%*s", dev_phyno);
            writelog(LOG_INFO, "dev_phyno=[%s],dev_state=[%d]\n", dev_phyno, dev_state);
            if (g_flag == 1) {
                ret = GetDevIdByDevPhyId(&deviceid, dev_phyno);
                if (ret) {
                    writelog(LOG_ERR, "设备不存在,devphyid[%s].", dev_phyno);
                    //return ret;
                }
            } else {
                deviceid = atoi(dev_phyno);
                T_t_device tDevice;
                memset(&tDevice, 0, sizeof tDevice);
                ret = DB_t_device_read_by_deviceid(deviceid, &tDevice);
                if (ret) {
                    if (E_NOTEXIST_DEVICE == ret) {
                        writelog(LOG_ERR, "前置机心跳,设备不存在,deviceid[%s]", dev_phyno);
                        continue;
                    }
                    continue;
                }
            }
            memset(&dev_monitor, 0, sizeof dev_monitor);
            ret = DB_t_devmonitor_read_by_deviceid(deviceid, &dev_monitor);
            des2src(dev_monitor.optime, op_time);
            des2src(dev_monitor.coltime, CAccTrans::getInstance()->trans.sysdatetime);
            des2src(dev_monitor.devtime, op_time);
            dev_monitor.deviceid = deviceid;
            dev_monitor.beatstatus = dev_state;
            if (ret) {
                if (DB_NOTFOUND == ret) {
                    //dev_monitor.is_ws[0] = '1';
                    ret = DB_t_devmonitor_add(&dev_monitor);
                    if (ret) {
                        writelog(LOG_ERR, "增加设备监控记录失败!dev[%d] phyno[%s]", dev_monitor.deviceid, dev_phyno);
                        //return -1;
                    }
                    continue;
                }
                //return -1;
            } else {
                ret = DB_t_devmonitor_update_by_deviceid(deviceid, &dev_monitor);
                if (ret) {
                    writelog(LOG_ERR, "更新设备监控记录失败!");
                    if (DB_NOTFOUND == ret)
                        continue;
                    //return -1;
                }
            }
            /* 获取后续数据 */
            devstatus_buffer = strtok(NULL, delim);
        }
        return 1;
    } else if (g_devtypeflag == 0) {
        for (i = 0; i < buf_len; i += sect_len) {
            //鑫三强采用设备ID
            strncpy(dev_phyno, status_buffer + i, 8);
            dev_phyno[8] = '\0';
            strncpy(temp, status_buffer + i + 8, 2);
            dev_state = strtoul(temp, NULL, 16);
            if (g_flag == 1) {
                ret = GetDevIdByDevPhyId(&deviceid, dev_phyno);
                if (ret) {
                    writelog(LOG_ERR, "devphyid[%s]", dev_phyno);
                    return ret;
                }
            } else {
                deviceid = atoi(dev_phyno);
                T_t_device tDevice;
                memset(&tDevice, 0, sizeof tDevice);
                ret = DB_t_device_read_by_deviceid(deviceid, &tDevice);
                if (ret) {
                    if (E_NOTEXIST_DEVICE == ret) {
                        writelog(LOG_ERR, "前置机心跳,设备不存在[%s]", dev_phyno);
                        continue;
                    }
                    continue;
                }
            }
            memset(&dev_monitor, 0, sizeof dev_monitor);
            ret = DB_t_devmonitor_read_by_deviceid(deviceid, &dev_monitor);
            des2src(dev_monitor.optime, op_time);
            des2src(dev_monitor.coltime, CAccTrans::getInstance()->trans.sysdatetime);
            des2src(dev_monitor.devtime, op_time);
            dev_monitor.deviceid = deviceid;
            dev_monitor.beatstatus = dev_state;
            if (ret) {
                if (DB_NOTFOUND == ret) {
                    //dev_monitor.is_ws[0] = '1';
                    ret = DB_t_devmonitor_add(&dev_monitor);
                    if (ret) {
                        writelog(LOG_ERR, "增加设备监控记录失败!dev[%d] phyno[%s]", dev_monitor.deviceid, dev_phyno);
                        return -1;
                    }
                    continue;
                }
                return -1;
            } else {
                ret = DB_t_devmonitor_update_by_deviceid(deviceid, &dev_monitor);
                if (ret) {
                    writelog(LOG_ERR, "更新设备监控记录失败!");
                    if (DB_NOTFOUND == ret)
                        continue;
                    return -1;
                }
            }
        }
        if (buf_len < 250) {
            return 0;
        }
    }
    return 1;
}

int F930071(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg) {
    int ret = 0;
    writelog(LOG_ERR, "前置机密钥sysid[%d][%s]", in_pack->lcert_code, in_pack->scust_limit2);
    writelog(LOG_ERR, "设备心跳vsmess[%s]", in_pack->vsmess);
    writelog(LOG_ERR, "设备心跳vsvarstr0[%s]", in_pack->vsvarstr0);
    writelog(LOG_ERR, "设备id,  lvol1=[%d], 1表示用物理ID，0表示deviceid", in_pack->lvol1);
    writelog(LOG_ERR, "监控数据类型lvol2=[%d], 0：8位设备物理ID+2位设备状态，3：非定长设备物理ID+2位设备状态", in_pack->lvol2);
    /*
    ret = chk_dyn_key(in_pack->lcert_code, in_pack->scust_limit2);
    if (ret)
    {
        *pRetCode = ret;
        goto L_RETU;
    }
    */
    T_t_subsystem  subsystem;
    memset(&subsystem, 0, sizeof(subsystem));
    ret = DB_t_subsystem_read_by_sysid(in_pack->lcert_code, &subsystem);
    if (ret) {
        if (DB_NOTFOUND == ret)
            return E_DB_SUBSYSTEM_N;
        else
            return E_DB_SUBSYSTEM_R;
    }
    g_FrontType = subsystem.systype;
    // 1 : 表示用设备物理ID 号
    // 0 : 表示用设备ID 号
    g_flag = in_pack->lvol1;
    //g_flag = 1;
    //0：8位设备物理ID+2位设备状态
    //3：非定长设备物理ID+2位设备状态.  devphyid1,devtype1;devphyid2,devtype2;devphyid3,devtype3;
    if (in_pack->lvol2 > 0) {
        g_devtypeflag = in_pack->lvol2;
    }
    writelog(LOG_DEBUG, "前置机时钟sysid[%d][%s]", in_pack->lcert_code, in_pack->sphone3);
    ret = do_check_buffer(in_pack->vsmess, in_pack->sphone3);
    if (ret < 0) {
        *pRetCode = E_DB_DEVMONITOR_U;
        goto L_RETU;
    } else if (ret == 0) {
        return 0;
    }
    ret = do_check_buffer(in_pack->vsvarstr0, in_pack->sphone3);
    if (ret < 0) {
        *pRetCode = E_DB_DEVMONITOR_U;
        goto L_RETU;
    } else if (ret == 0) {
        return 0;
    }
    ret = do_check_buffer(in_pack->vsvarstr1, in_pack->sphone3);
    if (ret < 0) {
        *pRetCode = E_DB_DEVMONITOR_U;
        goto L_RETU;
    } else if (ret == 0) {
        return 0;
    }
    ret = do_check_buffer(in_pack->vsvarstr2, in_pack->sphone3);
    if (ret < 0) {
        *pRetCode = E_DB_DEVMONITOR_U;
        goto L_RETU;
    } else if (ret == 0) {
        return 0;
    }
    ret = do_check_buffer(in_pack->vsvarstr3, in_pack->sphone3);
    if (ret < 0) {
        *pRetCode = E_DB_DEVMONITOR_U;
        goto L_RETU;
    } else if (ret == 0) {
        return 0;
    }
    return 0;
L_RETU:
    return  -1;
}

