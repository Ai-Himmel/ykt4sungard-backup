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
      sprintf(szBuf,"���ܴ������ļ�<%s>\n",inifile);
      return false;
   }
   tf.ReadString("DRTP","drtp_ip","127.0.0.1",g_para.drtp_ip,sizeof(g_para.drtp_ip)-1);
   g_para.drtp_port = tf.ReadInt("DRTP","drtp_port",4000);
   g_para.main_funcno = tf.ReadInt("DRTP","main_func",9000);
   g_para.drtp_timeout = tf.ReadInt("DRTP","time_out",5000);
   
   g_para.bank_lisnport = tf.ReadInt("BANK","listen_port",4001);
   g_para.bank_timeout = tf.ReadInt("BANK","time_out",3000);
    g_para.term_id= tf.ReadInt("BANK","term_id",3000);
   tf.Close();
   return true;   
}

static void GenResMsgHead(char *msghead,char *refno,int errcode,char *errmsg)
{
	char buf[1024]="";
	char sysdate[9]="";
	char systime[7]="";
	getsysdate(sysdate);
	getsystime(systime);
	AddXmlItemStr(buf,"AreaNo","");								//��������
	AddXmlItemStr(buf,"ChanNo","");								//��������
	if(refno != NULL)
		AddXmlItemStr(buf,"TransNo",refno);						//������ˮ��
	else
		AddXmlItemStr(buf,"TransNo","");							
	AddXmlItemStr(buf,"TransDate",sysdate);						//��������
	AddXmlItemStr(buf,"TransTime",systime);						//����ʱ��
	AddXmlItemStr(buf,"BankNo","");								//��������
	AddXmlItemStr(buf,"TellerNo","");								//��Ա����
	AddXmlItemInt(buf, "FuncTionFlag", 1);							//�����־
	if(errcode!=0)
		AddXmlItemInt(buf, "ResultCode", errcode);
	else
		AddXmlItemStr(buf, "ResultCode", "0000");
	AddXmlItemStr(buf, "Err_Info", errmsg);
	AddXmlItemStr(msghead, "MsgHead", buf);						// ȫ������MsgHead ��	
}
static void GenBindResMsgBody(char *msgbody,INFO_BIND &info_bind)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", info_bind.SchoolCode);
	AddXmlItemStr(buf, "TrType", info_bind.TrType);
	AddXmlItemStr(buf, "CusName", info_bind.CusName);
	AddXmlItemStr(buf, "IcCard", info_bind.IcCard);
	AddXmlItemStr(buf, "ReMark","");
	AddXmlItemStr(msgbody, "MsgBody", buf);						// ȫ������MsgBody ��		
}

static void GenTradeResMsgBody(char *msgbody,INFO_TRADE &info_trade)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", info_trade.SchoolCode);
	AddXmlItemStr(buf, "CusName", info_trade.CusName);
	AddXmlItemDbl(buf, "ICCardNotWrt", info_trade.ICCardNotWrt);
	AddXmlItemStr(buf, "ReMark","");
	AddXmlItemStr(msgbody, "MsgBody", buf);						// ȫ������MsgBody ��		
}

static void GenTransResMSG(char *msg,char *transcode,char *msghead,char *msgbody)
{
	char len_buf[16]="";
	char transcont[2048]="";
	char *trans_head="<TranResponse>";
	char *trans_tail="</TranResponse>";

	int transhead_len = strlen(trans_head);
	int msghead_len = strlen(msghead);
	int msgbody_len = strlen(msgbody);
	int transtail_len = strlen(trans_tail);
	int xmlhead_len = strlen(XML_HEAD);

	int transcont_len =   transhead_len + msghead_len + msgbody_len + transtail_len;
	
	memcpy(transcont,trans_head,transhead_len);
	memcpy(transcont+transhead_len,msghead,msghead_len);
	memcpy(transcont+transhead_len+msghead_len,msgbody,msgbody_len);
	memcpy(transcont+transhead_len+msghead_len+msgbody_len,trans_tail,transtail_len);

	sprintf(len_buf,"%08d",4 + xmlhead_len + transcont_len);
	memcpy(msg,len_buf,8);											// 8λ����
	memcpy(msg+8,transcode,4);										// 4λ������
	memcpy(msg+12,XML_HEAD,xmlhead_len);							// xml ͷ
	memcpy(msg + xmlhead_len +12,transcont,transcont_len);				// ��������(msghead + msgbody)
	
}


int doBind(KS_YKT_Clt &ykt_clt,INFO_BIND &info_bind,char *recv_buf)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
	char id_no[21]="";							// ���֤��
	char bank_no[21]="";						// ���п���
	char bankseri[21]="";						// ���ж���ˮ��
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	trim(stuemp_no);
	ret = GetXmlValue(id_no, 21, "CusNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡCusNo �Ŵ���");
		return ret;
	}
	trim(id_no);
	
	ret = GetXmlValue(bank_no, 21, "ActNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡActNo �Ŵ���");
		return ret;
	}
	trim(bank_no);
	ret = GetXmlValue(bankseri, 21, "TransNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡTransNo �Ŵ���");
		return ret;
	}
	trim(bankseri);
	
	writelog(LOG_INFO,"�� stuempno[%s],bankno[%s]\n",stuemp_no,bank_no);
        ykt_clt.SetStringFieldByName("sstatus0", "A");		
        ykt_clt.SetStringFieldByName("scust_auth2", stuemp_no);		
        ykt_clt.SetStringFieldByName("sname", id_no);		
   //     ykt_clt.SetStringFieldByName("scust_limit", name);		
        ykt_clt.SetStringFieldByName("scard1", bank_no);		
  //     ykt_clt.SetStringFieldByName("sdate1", date);	
        ykt_clt.SetStringFieldByName("scust_no", bankseri);	
        ykt_clt.SetStringFieldByName("sbank_code", BANKCODE);	
	ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);

    	if(!ykt_clt.SendRequest(841602, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	des2src(info_bind.TrType,"01");
	des2src(info_bind.IcCard, stuemp_no);
	des2src(info_bind.SchoolCode,SCHOOLCODE_AHUT);
	des2src(info_bind.ReMark,"ǩԼ�ɹ�");
	return 0;
}
int doUnbind(KS_YKT_Clt &ykt_clt,INFO_BIND &info_bind,char *recv_buf)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
	char bank_no[21]="";						// ���п���
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	trim(stuemp_no);
	
	ret = GetXmlValue(bank_no, 21, "ActNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡActNo �Ŵ���");
		return ret;
	}
	trim(bank_no);
	
	writelog(LOG_INFO,"��ɾ�� stuempno[%s],bankno[%s]\n",stuemp_no,bank_no);
        ykt_clt.SetStringFieldByName("sstatus0", "D");		
        ykt_clt.SetStringFieldByName("scust_auth2", stuemp_no);		       
        ykt_clt.SetStringFieldByName("scard0", bank_no);		
         ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);
		 
    	if(!ykt_clt.SendRequest(841602, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	des2src(info_bind.TrType,"03");
	des2src(info_bind.IcCard, stuemp_no);
	des2src(info_bind.SchoolCode,SCHOOLCODE_AHUT);
	des2src(info_bind.ReMark,"��Լ�ɹ�");
	return 0;
}

// �󶨹�ϵ�޸�
int doUpbing(KS_YKT_Clt &ykt_clt,INFO_BIND &info_bind,char *recv_buf)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
	char bank_no[21]="";						// ���п���
	char bankseri[21]="";						// ���ж���ˮ��
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	trim(stuemp_no);
	
	ret = GetXmlValue(bank_no, 21, "ActNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡActNo �Ŵ���");
		return ret;
	}
	trim(bank_no);
	ret = GetXmlValue(bankseri, 21, "TransNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡTransNo �Ŵ���");
		return ret;
	}
	trim(bankseri);
	
	writelog(LOG_INFO,"���޸� stuempno[%s],bankno[%s]\n",stuemp_no,bank_no);
        ykt_clt.SetStringFieldByName("sstatus0", "U");		
        ykt_clt.SetStringFieldByName("scust_auth2", stuemp_no);		
        ykt_clt.SetStringFieldByName("scard1", bank_no);		
        ykt_clt.SetStringFieldByName("scust_no", bankseri);	
        ykt_clt.SetStringFieldByName("sbank_code", BANKCODE);	
        ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);
		
    	if(!ykt_clt.SendRequest(841602, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	des2src(info_bind.TrType,"02");
	des2src(info_bind.IcCard, stuemp_no);
	des2src(info_bind.SchoolCode,SCHOOLCODE_AHUT);
	des2src(info_bind.ReMark,"�޸ĳɹ�");
	return 0;
}
int doCkbing(KS_YKT_Clt &ykt_clt,INFO_BIND &info_bind,char *recv_buf)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	trim(stuemp_no);
	ykt_clt.SetStringFieldByName("sstatus0", "R");		
        ykt_clt.SetStringFieldByName("spager", stuemp_no);		
        ykt_clt.SetStringFieldByName("sbank_code", BANKCODE);	
	ykt_clt.SetStringFieldByName("sstatus1", "1");	
	ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);
         
    	if(!ykt_clt.SendRequest(841602, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	else
	{
		ykt_clt.GetStringFieldByName("sall_name",info_bind.CusName, sizeof(info_bind.CusName));		
		des2src(info_bind.TrType,"04");
		des2src(info_bind.IcCard, stuemp_no);
		des2src(info_bind.SchoolCode,SCHOOLCODE_AHUT);
		des2src(info_bind.ReMark,"��ѯ�ɹ�");
		return 0;
	}
	return 0;
}

//�޿���ֵ��ѯ
int doCkbala(KS_YKT_Clt &ykt_clt,INFO_TRADE &info_trade,char *recv_buf)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
		
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	trim(stuemp_no);
	
	ykt_clt.SetStringFieldByName("spager", stuemp_no);		
	ykt_clt.SetStringFieldByName("sstatus1", "C");				// ���ױ�־
	ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);

	if(!ykt_clt.SendRequest(847133, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_trade.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_trade.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	else
	{
		ykt_clt.GetStringFieldByName("sall_name",info_trade.CusName, sizeof(info_trade.CusName));		// ����
		ykt_clt.GetDoubleFieldByName("damt0", &info_trade.ICCardNotWrt);							//δ��ֵ���
		ykt_clt.GetDoubleFieldByName("damt1", &info_trade.IcCardBal);								//�ʻ����
	}
	
	return 0;
}

//�޿���ֵ,����
int doTrade(KS_YKT_Clt &ykt_clt,INFO_TRADE &info_trade,char *recv_buf,bool bRev)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
	char samount[32]="";						//���
	double damount = 0;
	char RSeqNo[21]="";						// ������ˮ��
	char TransNo[21]="";
	char transflag[2]="";

	ret = GetXmlValue(TransNo, 21, "TransNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡTransNo �Ŵ���");
		return ret;
	}
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	ret = GetXmlValue(samount, 32, "Amount", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡAmount ����");
		return ret;
	}

	transflag[0]='T';				// ��ֵ
	if(bRev)					// ����
	{
		ret = GetXmlValue(RSeqNo, 21, "RSeqNo", recv_buf);
		if(ret)
		{
			writelog(LOG_ERR,"��ȡRSeqNo ����");
			return ret;
		}
		trim(RSeqNo);
		transflag[0]='R';				// ����
		ykt_clt.SetStringFieldByName("scust_auth", RSeqNo);			// ������ˮ��
		
	}
	trim(stuemp_no);
	trim(samount);
	damount = atof(samount);	

	ykt_clt.SetStringFieldByName("sstatus1", transflag);				// ���ױ�־
	ykt_clt.SetStringFieldByName("scust_auth2", TransNo);		
        ykt_clt.SetStringFieldByName("spager", stuemp_no);		
        ykt_clt.SetDoubleFieldByName("damt0", damount);	
	ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);
         
    	if(!ykt_clt.SendRequest(847133, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_trade.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_trade.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	else
	{
		ykt_clt.GetStringFieldByName("sall_name",info_trade.CusName, sizeof(info_trade.CusName));			// ����
		ykt_clt.GetDoubleFieldByName("damt0", &info_trade.ICCardNotWrt);								//δ��ֵ���
		ykt_clt.GetStringFieldByName("sname2", info_trade.Refno, sizeof(info_trade.Refno));				// ��ˮ��
	}
	return 0;
}


int doResponse(char *recv_buf,int recv_len,char *send_buf,int &send_len)
{
	int retcode = 0;
	char tradecode[8] = "";
	char  trtype[3]="";
	INFO_BIND info_bind;
	INFO_TRADE info_trade;

	memset(&info_bind,0,sizeof info_bind);
	memset(&info_trade,0,sizeof info_trade);
	
    	memcpy(tradecode,recv_buf,TRADECODE_LEN);    
            
    	KS_YKT_Clt ykt_clt;
	char msghead[1024]="";
	char msgbody[1024]="";
	ykt_clt.ResetHandler();

	 if(strncmp(tradecode,TRADE_BIND,TRADECODE_LEN) == 0)                       // ǩԼ
 	{
 		retcode= GetXmlValue(trtype, 3, "TrType", recv_buf);
		if(retcode)
		{
			writelog(LOG_INFO,"get TrType err,errcode[%d]",retcode);
			return retcode;
		}
	
		switch(atoi(trtype))
		{
			case 1:								// ǩԼ
				retcode = doBind(ykt_clt,info_bind,recv_buf);
				break;
			case 2:								// �޸�
				retcode = doUpbing(ykt_clt,info_bind,recv_buf);
				break;
			case 3:								// ��Լ
				retcode = doUnbind(ykt_clt,info_bind,recv_buf);
				break;
			case 4:								// ��ѯ
				retcode = doCkbing(ykt_clt,info_bind,recv_buf);
				break;
			default:
				return E_TRANS_NONSUPPORT;
		}
		if(retcode)
		{
			if(retcode<0)
				retcode = 1111;
		}
		GenResMsgHead(msghead,NULL,retcode,info_bind.ReMark);			// ����msghead
		GenBindResMsgBody(msgbody,info_bind);
		GenTransResMSG(send_buf,"2140",msghead,msgbody);
		send_len = strlen(send_buf);
 	}
	 else
 	{
 		if(strncmp(tradecode,TRADE_PAY_NOCARD,TRADECODE_LEN) == 0)                       // �޿���ֵ
	 		retcode = doTrade(ykt_clt, info_trade, recv_buf, false);
		
		else if(strncmp(tradecode,TRADE_REV_NOCARD,TRADECODE_LEN) == 0)
			retcode = doTrade(ykt_clt, info_trade, recv_buf, true);
		
		else if(strncmp(tradecode,TRADE_CHK_NOCARD,TRADECODE_LEN) == 0)
			retcode = doCkbala(ykt_clt, info_trade, recv_buf);
		else
	        	return E_TRANS_NONSUPPORT;
		
		if(retcode)
		{
			if(retcode<0)
				retcode = 1111;
		}
		writelog(LOG_DEBUG,"δд�����[%.2f]\n",info_trade.ICCardNotWrt);
		GenResMsgHead(msghead,info_trade.Refno,retcode,info_trade.ReMark);			// ����msghead
		GenTradeResMsgBody(msgbody,info_trade);		
		tradecode[1]='1';
		GenTransResMSG(send_buf,tradecode,msghead,msgbody);
		send_len = strlen(send_buf);

 	}
    	return 0;
    }
    
int doProcess(CTcpSocket &acpsocket)
{
    int ret = 0;
    int pack_len = 0;
    int send_len = 0;
    char recv_buf[4096] = "";
    char send_buf[4096] = "";
    ret = acpsocket.Recv(recv_buf, HEAD_LEN, g_para.bank_timeout);
    if(ret != HEAD_LEN)
    {
        writelog(LOG_ERR,"�����������ݰ�ͷ����\n");
        return -1;
    }
    pack_len = atoi(recv_buf);
    ret = acpsocket.Recv(recv_buf, pack_len, g_para.bank_timeout);
    if(ret != pack_len)
    {
        writelog(LOG_ERR,"�����������ݰ������\n");
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
    writelog(LOG_INFO,"len[%d],send_buf[%s]\n",send_len,send_buf);
    ret = acpsocket.Send(send_buf,send_len);
    if(ret != send_len)
    {
        writelog(LOG_ERR,"�������ݴ���\n");
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
	    printf("��ȡ�����ļ�[%s]ʧ��\n",inifile);
	    return -1;
	}
	
	writelog(LOG_DEBUG,"drtp_ip[%s],drtp_port[%d],mainfuncno[%d],list_port[%d]",g_para.drtp_ip, g_para.drtp_port, g_para.main_funcno,g_para.bank_lisnport);
	if(!KS_YKT_Clt::Initialize(g_para.drtp_ip, g_para.drtp_port, g_para.main_funcno))
	{
		printf("----------��ʼ��ͨѶƽ̨ʧ��----------\n");
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
			if ((childpid = fork()) == 0)		/* �ӽ��� */
			{   
				tcpsocket.Close();  
				
				doProcess(sockettmp);     /* �������� */  
				
				sockettmp.Close();
				exit(0);  
			}  
			else if(childpid < 0)
			{
                		printf("�����ӽ���ʧ��\n");
			}
			sockettmp.Close(); 		/* ������ */  
	}
	tcpsocket.Close();
	KS_YKT_Clt::Uninitialize();
	closelog();
	return 0;
}

