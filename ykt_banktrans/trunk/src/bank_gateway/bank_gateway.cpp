#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tcp.h>
#include "profile.h"
#include <signal.h>
#include <yktclt.h>
#include <pubfunc.h>
#include <bank_gateway.h>

#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))

CONFIG_PARA g_para;

bool ReadIni(char *inifile)
{
   TIniFile tf;
  
   char szBuf[256];
  
   memset(&g_para,0,sizeof(g_para));
   printf("Begin to read ini-file:%s...\n",inifile);
   if (!tf.Open(inifile))
   {
      sprintf(szBuf,"不能打开配置文件<%s>\n",inifile);
      return false;
   }
   tf.ReadString("DRTP","drtp_ip","127.0.0.1",g_para.drtp_ip,sizeof(g_para.drtp_ip)-1);
   g_para.drtp_port = tf.ReadInt("DRTP","drtp_port",4000);
   g_para.main_funcno = tf.ReadInt("DRTP","main_func",9000);
   g_para.drtp_timeout = tf.ReadInt("DRTP","time_out",5000);
   
   g_para.bank_lisnport = tf.ReadInt("BANK","listen_port",4001);
   g_para.bank_timeout = tf.ReadInt("DRTP","time_out",3000);
   tf.Close();
   return true;   
}
int doResponse(char *recv_buf,int recv_len,char *send_buf,int &send_len)
{
    int retcode = 0;
    char stuemp_no[33] = "";
    char idno[19]="";
    char name[20]="";
    char date[9] = "";
    char bankno[33]="";
    char bankseri[9] = "";
    char tradecode[8] = "";
    memcpy(tradecode,recv_buf,TRADECODE_LEN);
    
    send_len = 44;
    memset(send_buf,32,send_len);                        // 先填充空格
    sprintf(send_buf,"%04d",40);
    
        
    KS_YKT_Clt ykt_clt;
	char msg[256]="";
	ykt_clt.ResetHandler();
	
    if(strncmp(tradecode,TRADE_CHECK,TRADECODE_LEN) == 0)                       // 查询一卡通
    {
        memcpy(stuemp_no,recv_buf+4,32);
        trim(stuemp_no);
  		 writelog(LOG_INFO,"查询 stuempno[%s]\n",stuemp_no);
        ykt_clt.SetStringFieldByName("scust_auth2", stuemp_no);	
		ykt_clt.SetStringFieldByName("sstatus0", "R");	
    	if(!ykt_clt.SendRequest(841601, g_para.drtp_timeout))
    	{
    	    ykt_clt.GetStringFieldByName("vsmess",msg,sizeof msg);               
    		trim(msg);
    		
    		memcpy(send_buf+4,"111111",6);
			//memcpy(send_buf+10,msg,strlen(msg));
			STRLENCPY(send_buf+10,msg,34);
    		writelog(LOG_ERR,"向后台发送请求失败[%s]\n",msg);
    		return 	-1;
    	}
    	if(retcode = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",msg,sizeof msg);       
    		trim(msg);
    		sprintf(send_buf+4,"%06d",retcode);
    		//memcpy(send_buf+10,msg,strlen(msg));
    		STRLENCPY(send_buf+10,msg,34);
    		writelog(LOG_ERR,"后台功能执行失败,retcode[%d],msg[%s]\n",retcode,msg);
    		return 	-1;
    	}
    	ykt_clt.GetStringFieldByName("scust_auth",idno,sizeof idno);                // 身份证号
    	ykt_clt.GetStringFieldByName("sall_name",name,sizeof name);                 // 姓名
    	memcpy(send_buf+4,"000000",6);
    	//memcpy(send_buf+10,idno,strlen(idno));
    	//memcpy(send_buf+28,name,strlen(name));
    	STRLENCPY(send_buf+10,idno,18);
		STRLENCPY(send_buf+28,name,16);
    	return 0;
    }
    else if(strncmp(tradecode,TRADE_BIND,TRADECODE_LEN)== 0)                   // 绑定
    {
        memcpy(date,recv_buf+4,8);                  // 银行清算日期            
        memcpy(bankseri,recv_buf+12,8);             // 银行方流水号
        memcpy(stuemp_no,recv_buf+20,32);             // 学工号
        trim(stuemp_no);
        memcpy(name,recv_buf+52,32);                // 姓名
        trim(name);
        memcpy(idno,recv_buf+84,18);                // 身份证号
        trim(idno);
        memcpy(bankno,recv_buf+102,32);               // 银行账号
        trim(bankno);

		writelog(LOG_INFO,"绑定 stuempno[%s],bankno[%s]\n",stuemp_no,bankno);
        ykt_clt.SetStringFieldByName("sstatus0", "A");		
        ykt_clt.SetStringFieldByName("scust_auth2", stuemp_no);		
        ykt_clt.SetStringFieldByName("sname", idno);		
        ykt_clt.SetStringFieldByName("scust_limit", name);		
        ykt_clt.SetStringFieldByName("scust_auth", bankno);		
        ykt_clt.SetStringFieldByName("sdate1", date);	
        ykt_clt.SetStringFieldByName("scust_no", bankseri);	
        ykt_clt.SetStringFieldByName("sbank_code", BANKCODE);	
         
    	if(!ykt_clt.SendRequest(240022, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",msg,sizeof msg);       
    		trim(msg);
    		memcpy(send_buf+4,"111111",6);
    		//memcpy(send_buf+10,msg,strlen(msg));
    		STRLENCPY(send_buf+10,msg,34);
    		writelog(LOG_ERR,"向后台发送请求失败[%s]\n",msg);
    		return 	-1;
    	}
    	if(retcode = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",msg,sizeof msg);       
    		trim(msg);
    		sprintf(send_buf+4,"%06d",retcode);
    		//memcpy(send_buf+10,msg,strlen(msg));
    		STRLENCPY(send_buf+10,msg,34);
    		writelog(LOG_ERR,"后台功能执行失败,retcode[%d],msg[%s]\n",retcode,msg);
    		return 	-1;
    	}
    	
    	memcpy(send_buf+4,"000000",6);
    	memcpy(send_buf+10,"签约成功",8);
    	return 0;
    }
    else if(strncmp(tradecode,TRADE_UNBIND,TRADECODE_LEN)== 0)                 // 解除绑定
    {
        memcpy(stuemp_no,recv_buf+20,32);             // 学工号
        trim(stuemp_no); 

		writelog(LOG_INFO,"解除绑定 stuempno[%s]\n",stuemp_no);
        ykt_clt.SetStringFieldByName("sstatus0", "D");		
        ykt_clt.SetStringFieldByName("scust_auth2", stuemp_no);		
               
    	if(!ykt_clt.SendRequest(240022, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",msg,sizeof msg);       
    		trim(msg);
    		memcpy(send_buf+4,"111111",6);
    		//memcpy(send_buf+10,msg,strlen(msg));
    		STRLENCPY(send_buf+10,msg,34);
    		writelog(LOG_ERR,"向后台发送请求失败[%s]\n",msg);
    		return 	-1;
    	}
    	if(retcode = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",msg,sizeof msg);       
    		trim(msg);
    		sprintf(send_buf+4,"%06d",retcode);
    		//memcpy(send_buf+10,msg,strlen(msg));
    		STRLENCPY(send_buf+10,msg,34);
    		writelog(LOG_ERR,"后台功能执行失败,retcode[%d],msg[%s]\n",retcode,msg);
    		return 	-1;
    	}
    	
    	memcpy(send_buf+4,"000000",6);
    	memcpy(send_buf+10,"解约成功",8);
    	return 0;
    }
    else
        return E_TRANS_NONSUPPORT;
    return 0;
}
int doProcess(CTcpSocket &acpsocket)
{
    int ret = 0;
    int pack_len = 0;
    int send_len = 0;
    char recv_buf[256] = "";
    char send_buf[256] = "";
    ret = acpsocket.Recv(recv_buf, HEAD_LEN, g_para.bank_timeout);
    if(ret != HEAD_LEN)
    {
        writelog(LOG_ERR,"接收银行数据包头错误\n");
        return -1;
    }
    pack_len = atoi(recv_buf);
    ret = acpsocket.Recv(recv_buf, pack_len, g_para.bank_timeout);
    if(ret != pack_len)
    {
        writelog(LOG_ERR,"接收银行数据包体错误\n");
        return -1;
    }
	recv_buf[pack_len]=0;
    writelog(LOG_INFO,"len[%d],recv_buf[%s]\n",ret,recv_buf);
    ret = doResponse(recv_buf,pack_len,send_buf,send_len);
    if(ret)
    {
        if(ret>0)
            return ret;
    }    
    
    send_buf[send_len]=0;
    writelog(LOG_INFO,"len[%d],send_buf[%s]\n",strlen(send_buf),send_buf);
    ret = acpsocket.Send(send_buf,send_len);
    if(ret != send_len)
    {
        writelog(LOG_ERR,"发送数据错误\n");
        return -1;
    }
    return 0;
}
int main()
{
 //   int ret = 0;
	bool flag = false;
	int childpid = 0;
	char *inifile = "transconfig.ini";
	CTcpSocket tcpsocket ;
	CTcpSocket sockettmp ;
	
	openlog("yktbank_gateway",LOG_PID|LOG_CONS|LOG_NDELAY,LOG_LOCAL3);
	
	if( !ReadIni(inifile))
	{
	    printf("读取配置文件[%s]失败\n",inifile);
	    return -1;
	}
	
	writelog(LOG_DEBUG,"drtp_ip[%s],drtp_port[%d],mainfuncno[%d],list_port[%d]",g_para.drtp_ip, g_para.drtp_port, g_para.main_funcno,g_para.bank_lisnport);
	if(!KS_YKT_Clt::Initialize(g_para.drtp_ip, g_para.drtp_port, g_para.main_funcno))
	{
		printf("----------初始化通讯平台失败----------\n");
		return 	-1;
	}
		
	signal(SIGCHLD,SIG_IGN);
	signal(SIGINT,SIG_DFL);
	flag = tcpsocket.Create();
	if(!flag)
		exit(1);
	flag = tcpsocket.Listen(g_para.bank_lisnport);
	if(!flag)
		exit(1);
	while(1)
	{
			flag = tcpsocket.Accept(sockettmp);
			if(!flag)
				continue;
			if ((childpid = fork()) == 0)		/* 子进程 */
			{   
				tcpsocket.Close();  
				
				doProcess(sockettmp);     /* 处理请求 */  
				
				sockettmp.Close();
				exit(0);  
			}  
			else if(childpid < 0)
			{
                printf("创建子进程失败\n");
			}
			sockettmp.Close(); 		/* 父进程 */  
	}
	tcpsocket.Close();
	KS_YKT_Clt::Uninitialize();
	closelog();
	return 0;
}