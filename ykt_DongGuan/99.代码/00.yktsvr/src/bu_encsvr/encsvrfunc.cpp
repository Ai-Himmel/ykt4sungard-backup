/* --------------------------------------------
 * 创建日期: 2010-12-08
 * 程序作者: tc
 * 版本信息: 3.0.0.0
 * 程序功能: 
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <map>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "cpack.h"
#include "ksbu.h"
#include "svrlink.h"
#include "bupub.h"
#include "pubfunc.h"
#include "encsvrfunc.h"



BKConfiguration* BKConfiguration::instance_ = NULL;
const char BKConfiguration::SHMCFG_NAME[]="ENCCFGSHM";


BKConfiguration::BKConfiguration():cfgshm_(NULL)
{
	memset(&localcfg_,0,sizeof localcfg_);
}
BKConfiguration::~BKConfiguration()
{
}
int BKConfiguration::init_shm()
{
	cfgshm_ = (CFGSHM_T*)cfgshm_handle_.Open(SHMCFG_NAME,sizeof(cfgshm_));
	if(cfgshm_==NULL)
	{
		return -1;
	}
	return 0;
}
void BKConfiguration::delete_shm()
{
	cfgshm_ = NULL;
	cfgshm_handle_.Remove(SHMCFG_NAME);
}

BKConfiguration* BKConfiguration::instance()
{
	if(NULL == instance_)
	{
		instance_ = new BKConfiguration();
	}
	return instance_;
}
int BKConfiguration::save_para(const char *para,const char *value)
{
	VALUE_MAP_TYPE::iterator iter;
	iter = para_map_.find(para);
	if(iter!=para_map_.end())
	{
		para_map_.erase(iter);
	}
	para_map_.insert(VALUE_MAP_TYPE::value_type(para,value));
	return 0;
}
int BKConfiguration::save_int_para(const char *para,int value)
{
	char msg[128];
	sprintf(msg,"%d",value);
	return save_para(para,msg);
}

int BKConfiguration::load_config()
{
	save_para("encsvr.remoteip","127.0.0.1");
	save_int_para("encsvr.remoteport",18220);

	init_shm();
	
	BK_SHMLOCK_GUARD_RET(cfgshm_handle_,-1);
	localcfg_ = *cfgshm_;
	return 0;
}
int BKConfiguration::check_config_ver()
{
	BK_SHMLOCK_GUARD_RET(cfgshm_handle_,0);
	if(localcfg_.vernum < cfgshm_->vernum)
		return 1;
	return 0;
}

int BKConfiguration::get_int_para(const char *para,int *value) const
{
	char v[256]={0};
	if(get_string_para(para,v))
		return -1;
	*value = atoi(v);
	return 0;
}
int BKConfiguration::get_string_para(const char *para,char *value) const
{
	VALUE_MAP_TYPE::const_iterator iter;
	iter = para_map_.find(para);
	if(iter == para_map_.end())
		return -1;
	strcpy(value,(iter->second).c_str());
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
YangjiangDebitComm::YangjiangDebitComm(const char* svrip,int svrport):svrport_(svrport)
{
	strcpy(svrip_,svrip);	
}

YangjiangDebitComm::~YangjiangDebitComm()
{
}

void YangjiangDebitComm::Reset()
{
	memset(host_date_,0,sizeof host_date_);
	memset(host_time_,0,sizeof host_time_);
	memset(mac2_,0,sizeof mac2_);
}

int YangjiangDebitComm::SendRequest(ST_PACK *rPack,char* szMsg)
{
	Reset();
	char senddata[512],temp[256];
	int ret,offset,recvlen;
	CTcpSocket sock;

	if(strlen(rPack->sholder_ac_no) != 12)
	{
		strcpy(szMsg,"输入PSAM卡号长度错误");
		return -1;
	}
	if(strlen(rPack->sdate0)!=8 || strlen(rPack->stime0)!=6)
	{
		strcpy(szMsg,"输入终端日期时间错误");
		return -1;
	}
	if(strlen(rPack->scust_auth2)!=8 || strlen(rPack->sholder_ac_no2)!=8)
	{
		strcpy(szMsg,"输入加密因子长度错误");
		return -1;
	}
	/*
	if(strlen(rPack->scust_auth) !=18)
	{
		strcpy(szMsg,"输入卡应用序列号错误");
		return -1;
	}
	*/
	offset = 4;
	offset += sprintf(senddata+offset,"100105"); // 请求码
	offset += snprintf(senddata+offset,9,"%s",rPack->sdate0); // 日期
 	offset += snprintf(senddata+offset,7,"%s",rPack->stime0); // 时间
 	offset += snprintf(senddata+offset,13,"%s",rPack->sholder_ac_no); // PSAM卡终端号
 	offset += snprintf(senddata+offset,37,"00000000%s%s%08d",rPack->sdate0,rPack->sholder_ac_no,rPack->lserial0); // 流水号
 	offset += snprintf(senddata+offset,20,"0000000000000001230");//卡号?
 	int applen = strlen(rPack->scust_auth);
	char appno[17]={0};
	if(applen > 16)
	{
		strncpy(appno,rPack->scust_auth+applen-16,16);
	}
	else
	{
		strcpy(appno,rPack->scust_auth);
	}
 	offset += snprintf(senddata+offset,21,"0000%s",appno);//应用序列号
 	offset += sprintf(senddata+offset,"%08d",rPack->lvol2); //交易前余额
 	offset += sprintf(senddata+offset,"%08d",rPack->lvol0); //交易金额
 	offset += snprintf(senddata+offset,9,"%s",rPack->scust_auth2); //随机数
 	offset += sprintf(senddata+offset,"%04X",rPack->lvol1); //交易次数
 	offset += sprintf(senddata+offset,"02");//交易类型
 	offset += snprintf(senddata+offset,9,"%s",rPack->sholder_ac_no2);//MAC1

	
	writelog(LOG_ERR,"try connect server[%s][%d]",svrip_,svrport_);
 	if(!sock.ConnectTcpEx(svrip_,svrport_,8000))
 	{
 		// TODO: 必须
 		char errmsg[256]={0};
		sock.GetLastError(errmsg);
 		strcpy(szMsg,"连接加密平台失败:");
		//strcat(szMsg,errmsg);
 		return -1;
 	}

	sprintf(temp,"%04d",offset-4);
	memcpy(senddata,temp,4);

	writelog(LOG_ERR,"send data calc mac len[%d]",offset);
	if(sock.Send(senddata,offset)!=offset)
	{
		strcpy(szMsg,"发送加密平台失败");
 		return -1;
	}

 	ret=sock.Recv(temp,4,3000);
 	if(ret<0)
 	{
 		strcpy(szMsg,"接收加密平台数据超时");
 		return -1;
 	}
 	temp[4]=0;
 	recvlen = atoi(temp);
 	writelog(LOG_ERR,"recv len[%d]",recvlen);
 	ret = sock.Recv(senddata,recvlen,3000);
 	if(ret<0)
 	{
 		strcpy(szMsg,"接收加密平台数据超时");
 		return -1; 
 	}
 	senddata[recvlen]=0;
 	//writelog(LOG_ERR,"recv[%s]",senddata);
 	if(strncmp(senddata,"100105",6)!=0)
 	{
 		strcpy(szMsg,"接收加密平台数据错误");
 		return -1;
 	}
 	if(strncmp(senddata+6,"000000000",9)!=0)
 	{
 		memcpy(temp,senddata+6,9+60);
 		temp[69]=0;
 		sprintf(szMsg,"接收加密平台数据错误[%s]",temp);
 		return -1;
 	}
 	
 	offset=6+9+60;
 	offset+=36;
 	strncpy(host_date_,senddata+offset,8); // 主机日期
 	offset+=8;
 	strncpy(host_time_,senddata+offset,6); // 主机时间
 	offset+=6;
 	strncpy(mac2_,senddata+offset,8); // MAC2
 	return 0;
}


