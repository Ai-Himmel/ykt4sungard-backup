#include "StdAfx.h"

#include "drtphelper.h"
#include "DRTPAPI.h"
#include "drtperr.h"

static void SetValue(ST_PACKHEAD *head, ST_PACK *pack,int ids,const char *data)
{
	long lv;
	double dv;
#define PC(a)	{ SetParmBit(head,ids);strncpy((char *)pack->a,data,sizeof(pack->a));pack->a[sizeof(pack->a)-1]=0;}//CHAR[]
#define PI(a)	{ SetParmBit(head,ids);lv=atol(data);memcpy(&pack->a,&lv,sizeof(pack->a));}//INT
#define PD(a)	{ SetParmBit(head,ids);dv=atof(data);memcpy(&pack->a,&dv,sizeof(pack->a));}//LONG

	switch(ids)
	{                                
	case F_SCUST_NO:                     
		PC(scust_no);                
		break;                       
	case F_SCUST_NO2:                    
		PC(scust_no2);               
		break;                       
	case F_SHOLDER_AC_NO:                
		PC(sholder_ac_no);           
		break;                       
	case F_SHOLDER_AC_NO2:               
		PC(sholder_ac_no2);          
		break;                       
	case F_SHOLDER_TYPE:                 
		PC(sholder_type);            
		break;                       
	case F_SHOLDER_TYPE2:                
		PC(sholder_type2);           
		break;                       
	case F_SNAME:                        
		PC(sname);                   
		break;                       
	case F_SNAME2:                       
		PC(sname2);                  
		break;                       
	case F_SALL_NAME:                    
		PC(sall_name);               
		break;                       
	case F_SMARKET_CODE:                 
		PC(smarket_code);            
		break;                       
	case F_SMARKET_CODE2:                
		PC(smarket_code2);           
		break;                       
	case F_SDATE0:                       
		PC(sdate0);                  
		break;                       
	case F_SDATE1:                       
		PC(sdate1);                  
		break;                       
	case F_SDATE2:                       
		PC(sdate2);                  
		break;                       
	case F_SDATE3:                       
		PC(sdate3);                  
		break;                       
	case F_STIME0:                       
		PC(stime0);                  
		break;                       
	case F_STIME1:                       
		PC(stime1);                  
		break;                       
	case F_STIME2:                       
		PC(stime2);                  
		break;                       
	case F_STIME3:                       
		PC(stime3);                  
		break;                       
	case F_LVOL0:                        
		PI(lvol0);                   
		break;                       
	case F_LVOL1:                        
		PI(lvol1);                   
		break;                       
	case F_LVOL2:                        
		PI(lvol2);                   
		break;                       
	case F_LVOL3:                        
		PI(lvol3);                   
		break;                       
	case F_LVOL4:                        
		PI(lvol4);                   
		break;                       
	case F_LVOL5:                        
		PI(lvol5);                   
		break;                       
	case F_LVOL6:                        
		PI(lvol6);                   
		break;                       
	case F_LVOL7:                        
		PI(lvol7);                   
		break;                       
	case F_LVOL8:                        
		PI(lvol8);                   
		break;                       
	case F_LVOL9:                        
		PI(lvol9);                   
		break;                       
	case F_LVOL10:                       
		PI(lvol10);                  
		break;                       
	case F_LVOL11:                       
		PI(lvol11);                  
		break;                       
	case F_LVOL12:                       
		PI(lvol12);                  
		break;                       
	case F_DAMT0:                        
		PD(damt0);                   
		break;                       
	case F_DAMT1:                        
		PD(damt1);                   
		break;                       
	case F_DAMT2:                        
		PD(damt2);                   
		break;                       
	case F_DAMT3:                        
		PD(damt3);                   
		break;                       
	case F_DAMT4:                        
		PD(damt4);                   
		break;                       
	case F_DAMT5:                        
		PD(damt5);                   
		break;                       
	case F_DAMT6:                        
		PD(damt6);                   
		break;                       
	case F_DAMT7:                        
		PD(damt7);                   
		break;                       
	case F_DAMT8:                        
		PD(damt8);                   
		break;                       
	case F_DAMT9:                        
		PD(damt9);                   
		break;                       
	case F_DAMT10:                       
		PD(damt10);                  
		break;                       
	case F_DAMT11:                       
		PD(damt11);                  
		break;                       
	case F_DAMT12:                       
		PD(damt12);                  
		break;                       
	case F_DAMT13:                       
		PD(damt13);                  
		break;                       
	case F_DAMT14:                       
		PD(damt14);                  
		break;                       
	case F_DAMT15:                       
		PD(damt15);                  
		break;                       
	case F_DAMT16:                       
		PD(damt16);                  
		break;                       
	case F_DAMT17:                       
		PD(damt17);                  
		break;                       
	case F_DAMT18:                       
		PD(damt18);                  
		break;                       
	case F_DAMT19:                       
		PD(damt19);                  
		break;                       
	case F_DAMT20:                       
		PD(damt20);                  
		break;                       
	case F_DAMT21:                       
		PD(damt21);                  
		break;                       
	case F_DAMT22:                       
		PD(damt22);                  
		break;                       
	case F_DAMT23:                       
		PD(damt23);                  
		break;                       
	case F_DAMT24:                       
		PD(damt24);                  
		break;                       
	case F_DAMT25:                       
		PD(damt25);                  
		break;                       
	case F_DAMT26:                       
		PD(damt26);                  
		break;                       
	case F_DAMT27:                       
		PD(damt27);                  
		break;                       
	case F_DAMT28:                       
		PD(damt28);                  
		break;                       
	case F_DAMT29:                       
		PD(damt29);                  
		break;                       
	case F_DAMT30:                       
		PD(damt30);                  
		break;                       
	case F_DAMT31:                       
		PD(damt31);                  
		break;                       
	case F_DAMT32:                       
		PD(damt32);                  
		break;                       
	case F_DAMT33:                       
		PD(damt33);                  
		break;                       
	case F_SSTOCK_CODE:                  
		PC(sstock_code);             
		break;                       
	case F_SSTOCK_CODE2:                 
		PC(sstock_code2);            
		break;                       
	case F_SCUST_TYPE:                   
		PC(scust_type);              
		break;                       
	case F_SCUST_TYPE2:                  
		PC(scust_type2);             
		break;                       
	case F_SSTAT_TYPE:                   
		PC(sstat_type);              
		break;                       
	case F_SSTAT_TYPE2:                  
		PC(sstat_type2);             
		break;                       
	case F_SROOM_NO:                     
		PC(sroom_no);                
		break;                       
	case F_SROOM_NO2:                    
		PC(sroom_no2);               
		break;                       
	case F_SOPEN_EMP:                    
		PC(sopen_emp);               
		break;                       
	case F_SCLOSE_EMP:                   
		PC(sclose_emp);              
		break;                       
	case F_SCHANGE_EMP:                  
		PC(schange_emp);             
		break;                       
	case F_SCHECK_EMP:                   
		PC(scheck_emp);              
		break;                       
	case F_SEMP:                         
		PC(semp);                    
		break;                       
	case F_SNATION_CODE:                 
		PC(snation_code);            
		break;                       
	case F_LCERT_CODE:                   
		PI(lcert_code);              
		break;                       
	case F_STX_PWD:                      
		PC(stx_pwd);                 
		break;                       
	case F_STX_PWD2:                     
		PC(stx_pwd2);                
		break;                       
	case F_SWITHDRAW_PWD:                
		PC(swithdraw_pwd);           
		break;                       
	case F_SWITHDRAW_PWD2:               
		PC(swithdraw_pwd2);          
		break;                       
	case F_SEMP_PWD:                     
		PC(semp_pwd);                
		break;                       
	case F_SEMP_PWD2:                    
		PC(semp_pwd2);               
		break;                       
	case F_SBANK_PWD:                    
		PC(sbank_pwd);               
		break;                       
	case F_SBANK_PWD2:                   
		PC(sbank_pwd2);              
		break;                       
	case F_SCUST_AUTH:                   
		PC(scust_auth);              
		break;                       
	case F_SCUST_AUTH2:                  
		PC(scust_auth2);             
		break;                       
	case F_SCUST_LIMIT:                  
		PC(scust_limit);             
		break;                       
	case F_SCUST_LIMIT2:                 
		PC(scust_limit2);            
		break;                       
	case F_LSAFE_LEVEL:                  
		PI(lsafe_level);             
		break;                       
	case F_LSAFE_LEVEL2:                 
		PI(lsafe_level2);            
		break;                       
	case F_SPOST_CODE:                   
		PC(spost_code);              
		break;                       
	case F_SPOST_CODE2:                  
		PC(spost_code2);             
		break;                       
	case F_SPHONE:                       
		PC(sphone);                  
		break;                       
	case F_SPHONE2:                      
		PC(sphone2);                 
		break;                       
	case F_SPHONE3:                      
		PC(sphone3);                 
		break;                       
	case F_SPAGER:                       
		PC(spager);                  
		break;                       
	case F_SEMAIL:                       
		PC(semail);                  
		break;                       
	case F_SEMAIL2:                      
		PC(semail2);                 
		break;                       
	case F_SNOTE:                        
		PC(snote);                   
		break;                       
	case F_SNOTE2:                       
		PC(snote2);                  
		break;                       
	case F_SCERT_NO:                     
		PC(scert_no);                
		break;                       
	case F_SCERT_NO2:                    
		PC(scert_no2);               
		break;                       
	case F_SCERT_ADDR:                   
		PC(scert_addr);              
		break;                       
	case F_SSTATUS0:                     
		PC(sstatus0);                
		break;                       
	case F_SSTATUS1:                     
		PC(sstatus1);                
		break;                       
	case F_SSTATUS2:                     
		PC(sstatus2);                
		break;                       
	case F_SSTATUS3:                     
		PC(sstatus3);                
		break;                       
	case F_SSTATUS4:                     
		PC(sstatus4);                
		break;                       
	case F_LWITHDRAW_FLAG:               
		PI(lwithdraw_flag);          
		break;                       
	case F_SADDR:                        
		PC(saddr);                   
		break;                       
	case F_SADDR2:                       
		PC(saddr2);                  
		break;                       
	case F_SSERIAL0:                     
		PC(sserial0);                
		break;                       
	case F_SSERIAL1:                     
		PC(sserial1);                
		break;                       
	case F_SSERIAL2:                     
		PC(sserial2);                
		break;                       
	case F_SSERIAL3:                     
		PC(sserial3);                
		break;                       
	case F_SSERIAL4:                     
		PC(sserial4);                
		break;                       
	case F_SCURRENCY_TYPE:               
		PC(scurrency_type);          
		break;                       
	case F_SCURRENCY_TYPE2:              
		PC(scurrency_type2);         
		break;                       
	case F_SBRANCH_CODE0:                
		PC(sbranch_code0);           
		break;                       
	case F_SBRANCH_CODE1:                
		PC(sbranch_code1);           
		break;                       
	case F_SBRANCH_CODE2:                
		PC(sbranch_code2);           
		break;                       
	case F_USSET0:                       
		PC(usset0);                  
		break;                       
	case F_USSET1:                       
		PC(usset1);                  
		break;                       
	case F_USSET2:                       
		PC(usset2);                  
		break;                       
	case F_USSET3:                       
		PC(usset3);                  
		break;                       
	case F_USSET4:                       
		PC(usset4);                  
		break;                       
	case F_USSET5:                       
		PC(usset5);                  
		break;                       
	case F_USSET6:                       
		PC(usset6);                  
		break;                       
	case F_SSTATION0:                    
		PC(sstation0);               
		break;                       
	case F_SSTATION1:                    
		PC(sstation1);               
		break;                       
	case F_SBANK_ACC:                    
		PC(sbank_acc);               
		break;                       
	case F_SBANK_ACC2:                   
		PC(sbank_acc2);              
		break;                       
	case F_LBANK_ACC_TYPE:               
		PI(lbank_acc_type);          
		break;                       
	case F_LBANK_ACC_TYPE2:              
		PI(lbank_acc_type2);         
		break;                       
	case F_SMAIN_FLAG:                   
		PC(smain_flag);              
		break;                       
	case F_SMAIN_FLAG2:                  
		PC(smain_flag2);             
		break;                       
	case F_SBANK_CODE:                   
		PC(sbank_code);              
		break;                       
	case F_SBANK_CODE2:                  
		PC(sbank_code2);             
		break;                       
	case F_SEMP_NO:                      
		PC(semp_no);                 
		break;                       
	case F_SEMP_NO2:                     
		PC(semp_no2);                
		break;                       
	case F_DRATE0:                       
		PD(drate0);                  
		break;                       
	case F_DRATE1:                       
		PD(drate1);                  
		break;                       
	case F_LSERIAL0:                     
		PI(lserial0);                
		break;                       
	case F_LSERIAL1:                     
		PI(lserial1);                
		break;                       
	case F_SBANKNAME:                    
		PC(sbankname);               
		break;                       
	case F_SBANKNAME2:                   
		PC(sbankname2);              
		break;                       
	case F_SCARD0:                       
		PC(scard0);                  
		break;                       
	case F_SCARD1:                       
		PC(scard1);                  
		break;                       
	case F_SORDER0:                      
		PC(sorder0);                 
		break;                       
	case F_SORDER1:                      
		PC(sorder1);                 
		break;                       
	case F_SORDER2:                      
		PC(sorder2);                 
		break;                       
	case F_VSMESS:                       
		PC(vsmess);                  
		break;       
	case F_SCUSTTYPES:
		PC(scusttypes);
		break;
	case F_SSECTYPES:
		PC(ssectypes);
		break;
	case F_VSVARSTR0:                    
		PC(vsvarstr0);               
		break;                       
	case F_VSVARSTR1:                    
		PC(vsvarstr1);               
		break;                       
	case F_VSVARSTR2:                    
		PC(vsvarstr2);               
		break;                       
	case F_VSVARSTR3:                    
		PC(vsvarstr3);               
		break;                       
	default:
		printf("not existed parameter=%d....\n",ids);

	}                                
}  
//////////////////////////////////////////////////////////////////////////

int CDRTPHelper::InitDrtp()
{
	int ecode;
	char msg[512] = "";
	if(DrtpInit(&ecode,msg))
	{
		return 0;
	}
	return -1;
}

void CDRTPHelper::UninitDrtp()
{
	DrtpExit();
}

//////////////////////////////////////////////////////////////////////////

CDRTPHelper::CDRTPHelper(const char* ip,int port,int funcno)
:m_serverPort(port),m_funcNo(funcno),m_drtpHandle(0)
{
	memset(m_serverIP,0,sizeof(m_serverIP));
	strncpy(m_serverIP,ip,sizeof(m_serverIP));
	Reset();
}

CDRTPHelper::~CDRTPHelper(void)
{
	Close();
}

// 申请Drtp连接
int CDRTPHelper::Connect(void)
{
	
	if(m_drtpHandle > 0)
	{
		return 0;
	}
	m_errcode = 0;
	m_drtpHandle = DrtpConnect(m_serverIP, m_serverPort,&m_errcode,m_errmsg,1);
	if(m_drtpHandle <= 0 || m_errcode != 0)
	{
//		ACE_DEBUG((LM_ERROR,"申请DRTP连接失败,错误[%d][%s]",m_errcode
//			,m_errmsg));
		m_drtpHandle = 0;
		return -1;
	}
//	ACE_DEBUG((LM_DEBUG,"连接DRTP成功，返回Handle[%d]",m_drtpHandle));
	return 0;
}

// 重置
void CDRTPHelper::Reset(void)
{
	memset(&m_requestPack,0,sizeof m_requestPack);
	memset(&m_dataArray,0,sizeof m_dataArray);
	m_currRecord = NULL;
	m_currIndex = 0;
	m_currRecordCount = 0;
}

// 设置请求包头信息
void CDRTPHelper::SetRequestHeader(int funcno, int first)
{
	Reset();
	m_requestPack.head.RequestType = funcno;
	m_requestType = funcno;
	m_requestPack.head.firstflag = first;
	m_requestPack.head.nextflag = (!first);
	m_requestPack.head.recCount = 1;
}

void CDRTPHelper::AddField(int field,const char * value,int len)
{
	SetValue(&(m_requestPack.head),&(m_requestPack.pack),field,value);
}
void CDRTPHelper::AddField(int field,int value)
{
	char buf[64] = "";
	sprintf(buf,"%d",value);
	AddField(field,buf);
}
void CDRTPHelper::AddField(int field,float value)
{
	char buf[64] = "";
	sprintf(buf,"%f",value);
	AddField(field,buf);
}
void CDRTPHelper::AddField(int field,double value)
{
	char buf[64] = "";
	sprintf(buf,"%f",value);
	AddField(field,buf);
}
void CDRTPHelper::AddField(int field,long value)
{
	char buf[64] = "";
	sprintf(buf,"%ld",value);
	AddField(field,buf);
}
void CDRTPHelper::AddField(int field,unsigned long value)
{
	char buf[64] = "";
	sprintf(buf,"%lu",value);
	AddField(field,buf);
}
int CDRTPHelper::testDrtpHandle()
{
	if(m_drtpHandle > 0)
	{
		/*
		m_errcode = 0;
		memset(&m_errmsg,0,sizeof m_errmsg);
		DrtpPing(m_drtpHandle,&m_errcode,m_errmsg);
		*/
//		ACE_DEBUG((LM_ERROR,"Ping DRTP 服务器返回错误码[%d][%s]"
//			,m_errcode,m_errmsg));
		switch(m_errcode)
		{
		case ERROR_NO_FUNCTION:
		case ERROR_NO_BRANCHNO:
			// 没有功能号
			return 0;
		case 0:
			// 需要重连
			if(DrtpReConnect(m_drtpHandle,&m_errcode,m_errmsg))
				return 0;
			return -1;
		case ERROR_SOCKET:
			//if(strcmp("通讯错误:10057",m_errmsg) == 0)
			m_drtpHandle = 0;
		case ERROR_INVALID_ID:
			
		case ERROR_NO_ID:
		case ERROR_MEMORY:
			Close();
			//KSGThreadUtil::Sleep(2000);
			return Connect();
		default:
		case ERROR_UNSUPPORT_PROXY:
			return -1;
		}
		return -1;
	}
	return 0;
}
int CDRTPHelper::SendRequest(int timeout /*=0*/)
{
	m_errcode = 0;
	memset(&m_errmsg,0,sizeof m_errmsg);
	int len = sizeof m_drtpBuf;
	int retries = 3;
	BOOL bRet = FALSE;
	m_currRecord = NULL;
	m_currIndex = 0;
	m_currRecordCount = 0;
	m_timeout = timeout;
	TAG_DRTPHANDLE tag;
	memset(&tag,0,sizeof(tag));
	memset(m_drtpBuf,0,sizeof m_drtpBuf);
	if(!DrtpAttachServer(0,m_funcNo,m_drtpHandle,&tag,&m_errcode,m_errmsg))
	{
		try
		{
			testDrtpHandle();
			return -1;
		}
		catch (DrtpConnectException&)
		{
			return -2;
		}
	}
	EncodeBuf(&m_requestPack, m_drtpBuf,&len, NULL);
	while(--retries >= 0)
	{
		bRet = DrtpSendMessage((char*)m_drtpBuf,len,&m_errcode,m_errmsg,&tag,
			0,-1,0,-1,2);
		if(bRet)
		{
			break;
		}
		
	}
	if(!bRet)
	{
		GetErrMsg();
		return -1;
	}
	retries = 3;
	int iRet = 0;
	int readLen = 0;

	while(--retries >= 0)
	{
		iRet = DrtpReadMessage((char*)m_drtpBuf, sizeof m_drtpBuf,&readLen,
			m_drtpHandle,&tag,&m_errcode,m_errmsg,m_timeout);
		if (iRet>0)
		{
			break;
		}
	}
	if(iRet <= 0)
	{
		GetErrMsg();
		logDrtpErrMsg();
		//testDrtpHandle();
		return -1;
	}
	memset(&m_requestPack, 0, sizeof(m_requestPack));
	memset(m_dataArray, 0, sizeof(m_dataArray));
	// 把接收缓冲区中的内容解码到Pack和DataArray中
	len = sizeof m_drtpBuf;
	int nCount = 0;
	bRet = DecodeBufWithArray((BYTE*)m_drtpBuf,readLen, &m_requestPack
		,m_dataArray, &nCount, 0);
	// 记录返回结果集数
	m_currRecordCount = m_requestPack.head.recCount;
	return 0;
}
std::string CDRTPHelper::GetErrMsg()
{
	return std::string(m_errmsg);
}
std::string CDRTPHelper::GetReturnMsg()
{
	std::string retmsg(m_requestPack.pack.vsmess);
	return retmsg;
}
int CDRTPHelper::GetReturnCode()
{
	return m_requestPack.head.retCode;
}
bool CDRTPHelper::HasMoreRecord()
{
	if(m_currRecord)
	{
		return true;
	}
	// 数据已经读取完
	if(m_currIndex >= m_currRecordCount)
	{
		// 有后继包
		if(m_requestPack.head.nextflag)
		{
			// 读取后继包
//			ACE_DEBUG((LM_DEBUG,"取后继数据包"));
			SetNextRequest();
			if(SendRequest(m_timeout))
				return false;
		}
		else
		{
			// 没有后继包，也没有数据返回 false
			return false;
		}
	}
	// 如果没有记录
	if(m_currRecordCount == 0 || m_requestPack.head.retCode != 0)
		return false;
	//
	if(m_currIndex == 0)
	{
		// 第一条记录在 m_requestPack.pack 中
		m_currRecord = &(m_requestPack.pack);
	}
	else
	{
		m_currRecord = &(m_dataArray[m_currIndex-1]);
	}
	m_currIndex++;
	return true;
}

ST_PACK* CDRTPHelper::GetNextRecord()
{
	ST_PACK* rec = m_currRecord;
	m_currRecord = NULL;
	return rec;
}

void CDRTPHelper::SetNextRequest()
{
	ST_HOOK hook;
	memcpy(&hook,&m_requestPack.head.hook,sizeof(hook));
	Reset();
	m_requestPack.head.RequestType = m_requestType;
	m_requestPack.head.firstflag = 0;
	m_requestPack.head.recCount = 1;
	m_requestPack.head.nextflag = 1;
	memcpy(&m_requestPack.head.hook,&hook,sizeof(hook));
}

void CDRTPHelper::Close()
{
	if(m_drtpHandle > 0)
	{
		DrtpClose(m_drtpHandle,false);
//		ACE_DEBUG((LM_DEBUG,"关闭DRTP连接[%d]",m_drtpHandle));
		m_drtpHandle = 0;
	}
}

                                      

;
// }
// 
// void CDRTPHelper::SetNextRequest()
// {
// 	ST_HOOK hook;
// 	memcpy(&hook,&m_requestPack.head.hook,sizeof(hook));
// 	Reset();
// 	m_requestPack.head.RequestType = m_requestType;
// 	m_requestPack.head.firstflag = 0;
// 	m_requestPack.head.recCount = 1;
// 	m_requestPack.head.nextflag = 1;
// 	memcpy(&m_requestPack.head.hook,&hook,sizeof(hook));
// }
// 
// void CDRTPHelper::Close()
// {
// 	if(m_drtpHandle > 0)
// 	{
// 		DrtpClose(m_drtpHandle,false);
// 		ACE_DEBUG((LM_DEBUG,"关闭DRTP连接[%d]",m_drtpHandle));
// 		m_drtpHandle = 0;
// 	}
// }

                                      

