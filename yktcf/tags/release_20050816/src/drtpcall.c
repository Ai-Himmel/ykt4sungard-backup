/** 
* 模块名			一卡通通用前置
* 文件名			drtpcall.c
* 文件实现功能		封装 DRTP 功能函数
* 作者				汤成
* 版本				V0.1
* 日期				2005-07-07
* 备注				基于公司 DRTP 功能
* $Id: drtpcall.c 4 2005-08-03 10:36:46Z cash $
*/

#include "drtpcall.h"
#include "kcc_util.h"
#include "kcc_conf.h"

/** 
* @brief 调用 DRTP 最后一次错误码
*/
static int kcc_drtp_err_code = 0;
/** 
* @brief 调用 DRTP 最后一次错误信息
*/
static char kcc_drtp_err_msg[512] = "";
/** 
* @brief 调用 DRTP 使用的主功能号
*/
static long kcc_drtp_curr_main_func = 0;


void kcc_drtp_set_main_func(long mainfunc)
{
	kcc_drtp_curr_main_func = mainfunc;
}

int kcc_drtp_get_last_err()
{
	return kcc_drtp_err_code;
}

void kcc_drtp_get_last_err_msg(char * msg)
{
	kcc_strcpy(msg,kcc_drtp_err_msg);
}

int kcc_drtp_init()
{
	int ret = DrtpInit(&kcc_drtp_err_code,kcc_drtp_err_msg);

	if( ret )
	{
		kcc_write_log(LOG_DEBUG,"connect to drtp[%s:%d] success!",
					  g_drtp_svr_ip,g_drtp_svr_port);
		return 0;
	}
	else
		kcc_write_log(LOG_DEBUG,"connect to drtp[%s:%d] failed!",
					  g_drtp_svr_ip,g_drtp_svr_port);
	return -1;
}

int kcc_drtp_uninit()
{
	DrtpExit();
	kcc_write_log(LOG_DEBUG,"release drtp[%s:%d]!",
				  g_drtp_svr_ip,g_drtp_svr_port);
	return 0;
}

int kcc_drtp_connect()
{
	// FIXME : we can just return handle
	int handle = DrtpConnect((char*)g_drtp_svr_ip,g_drtp_svr_port,
							 &kcc_drtp_err_code,kcc_drtp_err_msg,-1);
	if( handle > 0 )
	{
		kcc_write_log(LOG_DEBUG,"connect to drtp handle[%d]",handle);
		return handle;
	}
	kcc_write_log(LOG_ERR,"connect to drtp error [%s:%d]",
				  g_drtp_svr_ip,g_drtp_svr_port);
	return -1;
}

int kcc_drtp_reconnect(int handle)
{
	int ret = DrtpReConnect(handle,&kcc_drtp_err_code,kcc_drtp_err_msg);
	if( ret )
	{
		kcc_write_log(LOG_DEBUG,"reconnect drtp success handle[%d]",handle);
		return 0;
	}
	kcc_write_log(LOG_ERR,"reconnect drtp failed handle[%d]",handle);
	return -1;
}

void kcc_init_cpack(ST_CPACK * rpack,int rec_count,int req_no,int max_rec)
{
	kcc_memclr(rpack,sizeof(ST_CPACK));
	rpack->head.firstflag = 1;
	rpack->head.nextflag = 0;
	rpack->head.recCount = rec_count;
	rpack->head.RequestType = req_no;
	rpack->head.retCode = max_rec;
}

int kcc_drtp_close(int handle)
{
	kcc_write_log(LOG_DEBUG,"close drpt handle[%d]",handle);
	DrtpClose(handle,false);
	return 0;
}

int kcc_drtp_send(int handle,char * buf,int len,int mainfunc)
{
	//TAG_DRTPHANDLE tag_handle;
	int ret;
	int retries;
	if( mainfunc == 0 )
		mainfunc = g_drtp_func_no;
	/*
	   if(DrtpAttachServer(g_drtp_svr_id,mainfunc,handle,&tag_handle,
	   &kcc_drtp_err_code,kcc_drtp_err_msg))
	   {
	 */
	retries = 3;
	while(retries-- > 0)
	{
		if(retries < 2)
		{
			// 重试的时候要重连
			if( kcc_drtp_reconnect(handle) != 0)
			{
				return -1;
			}
		}
		while(DrtpCheckMessage(&kcc_drtp_err_code,kcc_drtp_err_msg,handle)==0);
		/*
		   ret = DrtpSendMessage(buf,len,&kcc_drtp_err_code,
		   kcc_drtp_err_msg,&tag_handle, 0,handle,0,-1,2);
		 */
		ret = DrtpPostMessage(3,g_drtp_svr_id,mainfunc,buf,len,
							  &kcc_drtp_err_code,kcc_drtp_err_msg,
							  handle,0,0);
		if(ret)
		{
			return 0;
		}
	}
	//	}
	kcc_write_log(LOG_ERR,"send drtp data error. handle[%d]M[%s]",
				  handle,kcc_drtp_err_msg);
	return -1;
}

int kcc_drtp_send_cpack(int handle,ST_CPACK * rpack)
{
	char buf[8182] = "";
	int buflen;
	int ret;
	ret = EncodeBuf(rpack,(unsigned char*)buf,&buflen,kcc_drtp_err_msg);
	if( !ret )
	{
		kcc_write_log(LOG_ERR,"encode buffer error .handle[%d]",handle);
		return -1;
	}
	kcc_write_log(LOG_DEBUG,"cpack request type[%d]handle[%d]",
				  rpack->head.RequestType,handle);
	ret = kcc_drtp_send(handle,buf,buflen,kcc_drtp_curr_main_func);
	kcc_drtp_set_main_func(g_drtp_func_no);
	return ret;
}

int kcc_drtp_receive(int handle,char * buf,int len,int timeout)
{
	TAG_DRTPHANDLE tag_handle;
	int ret;
	int rec_len;
	int retries;
	if( timeout <= 0 )
	{
		timeout = -1;
	}
	retries = 3;
	while( retries-- > 0)
	{
		if(retries < 2)
		{
			// 重试的时候要重连
			if( kcc_drtp_reconnect(handle) != 0)
			{
				return -1;
			}
		}
		ret = DrtpReadMessage(buf,len,&rec_len,handle,&tag_handle,
							  &kcc_drtp_err_code,kcc_drtp_err_msg,timeout);
		if(ret)
		{
			return rec_len;
		}
	}
	kcc_write_log(LOG_ERR,"receive drtp data error. handle[%d]M[%s]",
				  handle,kcc_drtp_err_msg);
	return -1;
}

int kcc_drtp_recv_cpack(int handle,ST_CPACK * apack,
						   ST_PACK * apackarray,int pa_len)
{
	int ret = 0;
	char buf[8182] = "";
	int rows;
	int rec_len = 0;
	// FIXME : get timeout from config file
	rec_len = kcc_drtp_receive(handle,buf,sizeof(buf),30000);
	if(rec_len < 0)
	{
		return -1;
	}
	// decode buffer
	ret = DecodeBufWithArray((unsigned char*)buf,rec_len,apack,apackarray+1,&rows,
							 kcc_drtp_err_msg);
	if(!ret)
	{
		kcc_write_log(LOG_ERR,"decode buf error.",handle);
		return -1;
	}
	if( rows > pa_len )
	{
		// FIXME : there are maybe some error.
		;
	}
	rows = apack->head.recCount;
	ret = rows;
	kcc_memcpy(&apackarray[0],&apack->pack,sizeof(apackarray[0]));
	kcc_write_log(LOG_DEBUG,"receive drpt pack [%d] rows",rows);
	switch(kcc_drtp_valid_cpack(apack))
	{
	case -1:
		ret = -1;
		kcc_write_log(LOG_INFO,"receive request type not exists![%d]",
					  apack->head.RequestType);
		break;
	case 1:
		ret = -1;
		kcc_write_log(LOG_ERR,"receive request[%d] error return code[%d]",
					  apack->head.RequestType,apack->head.retCode);
		break;
	}
	// print debuf info
	if( g_debug_level > 5 )
	{
		ShowPack(apack,buf);
		/*
		for(i = 1;i < rows;++i)
		{
			printf("===========================>>>>row%03d",i+1);
			ShowPackNext(apack,&apackarray[i],buf);
			printf("%s\n",buf);
		}
		*/
	}
	return ret;
}

int kcc_drtp_recv_next_cpack(int handle,int req_no,
							 ST_CPACK *apack,ST_PACK * apackarray)
{
	// there is no next buffer
	ST_CPACK rpack;
	long next_main_func;
	int ret = 0;
	char buf[4096] = "";
	int rows,i;
	int rec_len = 0;

	if( apack->head.nextflag == 0 )
		return 0;

	// send request again
	kcc_memclr(&rpack,sizeof(ST_CPACK));
	rpack.head.firstflag = 0;
	rpack.head.nextflag = 1;
	rpack.head.RequestType = req_no;
	kcc_memcpy(&rpack.head.hook,&apack->head.hook,sizeof(rpack.head.hook));
	rpack.head.hook.queuetype = apack->head.hook.queuetype;
	next_main_func = atol(apack->head.hook.hostname);
	kcc_drtp_set_main_func(next_main_func);
	ret = kcc_drtp_send_cpack(handle,&rpack);

	if( !ret )
		return ret;
	// receive buffer
	rec_len = kcc_drtp_receive(handle,buf,sizeof(buf),100);
	if( rec_len < 0 )
	{
		kcc_write_log(LOG_ERR,"get next pack error. handle[%d]",handle);
		return -1;
	}
	// decode buffer
	ret = DecodeBufWithArray((unsigned char*)buf,rec_len,apack,apackarray,&rows,
							 kcc_drtp_err_msg);
	if(!ret)
	{
		kcc_write_log(LOG_ERR,"decode buf error.",handle);
		return -1;
	}
	// print debuf info
	if( g_debug_level > 5 )
	{
		ShowPack(apack,buf);
		printf("row%03d",i+2);
		ShowPackNext(apack,&apackarray[i],buf);
		printf("====================================\n");
	}
	return rows;
}

int kcc_drtp_valid_cpack(ST_CPACK * rpack)
{
	switch(rpack->head.retCode)
	{
	case 9998:
		// no request type exists
		return -1;
	case 0:
		return 0;
	default:
		return 1;
	}
}

void kcc_drtp_set_value(ST_PACKHEAD *head, ST_PACK *pack,int ids,char *data)
{
	long lv;
	double dv;

#define PC(a)	{ \
	SetParmBit(head,ids);\
		kcc_strncpy((char *)pack->a,data,sizeof(pack->a)); \
		pack->a[sizeof(pack->a)-1]=0;}//CHAR[]

#define PI(a)	{\
	SetParmBit(head,ids);\
		lv=atol(data);\
		kcc_memcpy(&pack->a,&lv,sizeof(pack->a));}//INT

#define PD(a)	{\
	SetParmBit(head,ids);\
		dv=atof(data);\
		kcc_memcpy(&pack->a,&dv,sizeof(pack->a));}//LONG

	switch(ids)
	{                                
	case F_SCUST_NO:                     
		PC(scust_no);                
		break;                       
	case F_SCUST_NO2:                    
		PC(scust_no2);               
		break;                       
		case
			F_SHOLDER_AC_NO:                
			PC(sholder_ac_no);           
		break;                       
		case
			F_SHOLDER_AC_NO2:               
			PC(sholder_ac_no2);          
		break;                       
		case
			F_SHOLDER_TYPE:                 
			PC(sholder_type);            
		break;                       
		case
			F_SHOLDER_TYPE2:                
			PC(sholder_type2);           
		break;                       
		case
			F_SNAME:                        
			PC(sname);                   
		break;                       
		case
			F_SNAME2:                       
			PC(sname2);                  
		break;                       
		case
			F_SALL_NAME:                    
			PC(sall_name);               
		break;                       
		case
			F_SMARKET_CODE:                 
			PC(smarket_code);            
		break;                       
		case
			F_SMARKET_CODE2:                
			PC(smarket_code2);           
		break;                       
		case
			F_SDATE0:                       
			PC(sdate0);                  
		break;                       
		case
			F_SDATE1:                       
			PC(sdate1);                  
		break;                       
		case
			F_SDATE2:                       
			PC(sdate2);                  
		break;                       
		case
			F_SDATE3:                       
			PC(sdate3);                  
		break;                       
		case
			F_STIME0:                       
			PC(stime0);                  
		break;                       
		case
			F_STIME1:                       
			PC(stime1);                  
		break;                       
		case
			F_STIME2:                       
			PC(stime2);                  
		break;                       
		case
			F_STIME3:                       
			PC(stime3);                  
		break;                       
		case
			F_LVOL0:                        
			PI(lvol0);                   
		break;                       
		case
			F_LVOL1:                        
			PI(lvol1);                   
		break;                       
		case
			F_LVOL2:                        
			PI(lvol2);                   
		break;                       
		case
			F_LVOL3:                        
			PI(lvol3);                   
		break;                       
		case
			F_LVOL4:                        
			PI(lvol4);                   
		break;                       
		case
			F_LVOL5:                        
			PI(lvol5);                   
		break;                       
		case
			F_LVOL6:                        
			PI(lvol6);                   
		break;                       
		case
			F_LVOL7:                        
			PI(lvol7);                   
		break;                       
		case
			F_LVOL8:                        
			PI(lvol8);                   
		break;                       
		case
			F_LVOL9:                        
			PI(lvol9);                   
		break;                       
		case
			F_LVOL10:                       
			PI(lvol10);                  
		break;                       
		case
			F_LVOL11:                       
			PI(lvol11);                  
		break;                       
		case
			F_LVOL12:                       
			PI(lvol12);                  
		break;                       
		case
			F_DAMT0:                        
			PD(damt0);                   
		break;                       
		case
			F_DAMT1:                        
			PD(damt1);                   
		break;                       
		case
			F_DAMT2:                        
			PD(damt2);                   
		break;                       
		case
			F_DAMT3:                        
			PD(damt3);                   
		break;                       
		case
			F_DAMT4:                        
			PD(damt4);                   
		break;                       
		case
			F_DAMT5:                        
			PD(damt5);                   
		break;                       
		case
			F_DAMT6:                        
			PD(damt6);                   
		break;                       
		case
			F_DAMT7:                        
			PD(damt7);                   
		break;                       
		case
			F_DAMT8:                        
			PD(damt8);                   
		break;                       
		case
			F_DAMT9:                        
			PD(damt9);                   
		break;                       
		case
			F_DAMT10:                       
			PD(damt10);                  
		break;                       
		case
			F_DAMT11:                       
			PD(damt11);                  
		break;                       
		case
			F_DAMT12:                       
			PD(damt12);                  
		break;                       
		case
			F_DAMT13:                       
			PD(damt13);                  
		break;                       
		case
			F_DAMT14:                       
			PD(damt14);                  
		break;                       
		case
			F_DAMT15:                       
			PD(damt15);                  
		break;                       
		case
			F_DAMT16:                       
			PD(damt16);                  
		break;                       
		case
			F_DAMT17:                       
			PD(damt17);                  
		break;                       
		case
			F_DAMT18:                       
			PD(damt18);                  
		break;                       
		case
			F_DAMT19:                       
			PD(damt19);                  
		break;                       
		case
			F_DAMT20:                       
			PD(damt20);                  
		break;                       
		case
			F_DAMT21:                       
			PD(damt21);                  
		break;                       
		case
			F_DAMT22:                       
			PD(damt22);                  
		break;                       
		case
			F_DAMT23:                       
			PD(damt23);                  
		break;                       
		case
			F_DAMT24:                       
			PD(damt24);                  
		break;                       
		case
			F_DAMT25:                       
			PD(damt25);                  
		break;                       
		case
			F_DAMT26:                       
			PD(damt26);                  
		break;                       
		case
			F_DAMT27:                       
			PD(damt27);                  
		break;                       
		case
			F_DAMT28:                       
			PD(damt28);                  
		break;                       
		case
			F_DAMT29:                       
			PD(damt29);                  
		break;                       
		case
			F_DAMT30:                       
			PD(damt30);                  
		break;                       
		case
			F_DAMT31:                       
			PD(damt31);                  
		break;                       
		case
			F_DAMT32:                       
			PD(damt32);                  
		break;                       
		case
			F_DAMT33:                       
			PD(damt33);                  
		break;                       
		case
			F_SSTOCK_CODE:                  
			PC(sstock_code);             
		break;                       
		case
			F_SSTOCK_CODE2:                 
			PC(sstock_code2);            
		break;                       
		case
			F_SCUST_TYPE:                   
			PC(scust_type);              
		break;                       
		case
			F_SCUST_TYPE2:                  
			PC(scust_type2);             
		break;                       
		case
			F_SSTAT_TYPE:                   
			PC(sstat_type);              
		break;                       
		case
			F_SSTAT_TYPE2:                  
			PC(sstat_type2);             
		break;                       
		case
			F_SROOM_NO:                     
			PC(sroom_no);                
		break;                       
		case
			F_SROOM_NO2:                    
			PC(sroom_no2);               
		break;                       
		case
			F_SOPEN_EMP:                    
			PC(sopen_emp);               
		break;                       
		case
			F_SCLOSE_EMP:                   
			PC(sclose_emp);              
		break;                       
		case
			F_SCHANGE_EMP:                  
			PC(schange_emp);             
		break;                       
		case
			F_SCHECK_EMP:                   
			PC(scheck_emp);              
		break;                       
		case
			F_SEMP:                         
			PC(semp);                    
		break;                       
		case
			F_SNATION_CODE:                 
			PC(snation_code);            
		break;                       
		case
			F_LCERT_CODE:                   
			PI(lcert_code);              
		break;                       
		case
			F_STX_PWD:                      
			PC(stx_pwd);                 
		break;                       
		case
			F_STX_PWD2:                     
			PC(stx_pwd2);                
		break;                       
		case
			F_SWITHDRAW_PWD:                
			PC(swithdraw_pwd);           
		break;                       
		case
			F_SWITHDRAW_PWD2:               
			PC(swithdraw_pwd2);          
		break;                       
		case
			F_SEMP_PWD:                     
			PC(semp_pwd);                
		break;                       
		case
			F_SEMP_PWD2:                    
			PC(semp_pwd2);               
		break;                       
		case
			F_SBANK_PWD:                    
			PC(sbank_pwd);               
		break;                       
		case
			F_SBANK_PWD2:                   
			PC(sbank_pwd2);              
		break;                       
		case
			F_SCUST_AUTH:                   
			PC(scust_auth);              
		break;                       
		case
			F_SCUST_AUTH2:                  
			PC(scust_auth2);             
		break;                       
		case
			F_SCUST_LIMIT:                  
			PC(scust_limit);             
		break;                       
		case
			F_SCUST_LIMIT2:                 
			PC(scust_limit2);            
		break;                       
		case
			F_LSAFE_LEVEL:                  
			PI(lsafe_level);             
		break;                       
		case
			F_LSAFE_LEVEL2:                 
			PI(lsafe_level2);            
		break;                       
		case
			F_SPOST_CODE:                   
			PC(spost_code);              
		break;                       
		case
			F_SPOST_CODE2:                  
			PC(spost_code2);             
		break;                       
		case
			F_SPHONE:                       
			PC(sphone);                  
		break;                       
		case
			F_SPHONE2:                      
			PC(sphone2);                 
		break;                       
		case
			F_SPHONE3:                      
			PC(sphone3);                 
		break;                       
		case
			F_SPAGER:                       
			PC(spager);                  
		break;                       
		case
			F_SEMAIL:                       
			PC(semail);                  
		break;                       
		case
			F_SEMAIL2:                      
			PC(semail2);                 
		break;                       
		case
			F_SNOTE:                        
			PC(snote);                   
		break;                       
		case
			F_SNOTE2:                       
			PC(snote2);                  
		break;                       
		case
			F_SCERT_NO:                     
			PC(scert_no);                
		break;                       
		case
			F_SCERT_NO2:                    
			PC(scert_no2);               
		break;                       
		case
			F_SCERT_ADDR:                   
			PC(scert_addr);              
		break;                       
		case
			F_SSTATUS0:                     
			PC(sstatus0);                
		break;                       
		case
			F_SSTATUS1:                     
			PC(sstatus1);                
		break;                       
		case
			F_SSTATUS2:                     
			PC(sstatus2);                
		break;                       
		case
			F_SSTATUS3:                     
			PC(sstatus3);                
		break;                       
		case
			F_SSTATUS4:                     
			PC(sstatus4);                
		break;                       
		case
			F_LWITHDRAW_FLAG:               
			PI(lwithdraw_flag);          
		break;                       
		case
			F_SADDR:                        
			PC(saddr);                   
		break;                       
		case
			F_SADDR2:                       
			PC(saddr2);                  
		break;                       
		case
			F_SSERIAL0:                     
			PC(sserial0);                
		break;                       
		case
			F_SSERIAL1:                     
			PC(sserial1);                
		break;                       
		case
			F_SSERIAL2:                     
			PC(sserial2);                
		break;                       
		case
			F_SSERIAL3:                     
			PC(sserial3);                
		break;                       
		case
			F_SSERIAL4:                     
			PC(sserial4);                
		break;                       
		case
			F_SCURRENCY_TYPE:               
			PC(scurrency_type);          
		break;                       
		case
			F_SCURRENCY_TYPE2:              
			PC(scurrency_type2);         
		break;                       
		case
			F_SBRANCH_CODE0:                
			PC(sbranch_code0);           
		break;                       
		case
			F_SBRANCH_CODE1:                
			PC(sbranch_code1);           
		break;                       
		case
			F_SBRANCH_CODE2:                
			PC(sbranch_code2);           
		break;                       
		case
			F_USSET0:                       
			PC(usset0);                  
		break;                       
		case
			F_USSET1:                       
			PC(usset1);                  
		break;                       
		case
			F_USSET2:                       
			PC(usset2);                  
		break;                       
		case
			F_USSET3:                       
			PC(usset3);                  
		break;                       
		case
			F_USSET4:                       
			PC(usset4);                  
		break;                       
		case
			F_USSET5:                       
			PC(usset5);                  
		break;                       
		case
			F_USSET6:                       
			PC(usset6);                  
		break;                       
		case
			F_SSTATION0:                    
			PC(sstation0);               
		break;                       
		case
			F_SSTATION1:                    
			PC(sstation1);               
		break;                       
		case
			F_SBANK_ACC:                    
			PC(sbank_acc);               
		break;                       
		case
			F_SBANK_ACC2:                   
			PC(sbank_acc2);              
		break;                       
		case
			F_LBANK_ACC_TYPE:               
			PI(lbank_acc_type);          
		break;                       
		case
			F_LBANK_ACC_TYPE2:              
			PI(lbank_acc_type2);         
		break;                       
		case
			F_SMAIN_FLAG:                   
			PC(smain_flag);              
		break;                       
		case
			F_SMAIN_FLAG2:                  
			PC(smain_flag2);             
		break;                       
		case
			F_SBANK_CODE:                   
			PC(sbank_code);              
		break;                       
		case
			F_SBANK_CODE2:                  
			PC(sbank_code2);             
		break;                       
		case
			F_SEMP_NO:                      
			PC(semp_no);                 
		break;                       
		case
			F_SEMP_NO2:                     
			PC(semp_no2);                
		break;                       
		case
			F_DRATE0:                       
			PD(drate0);                  
		break;                       
		case
			F_DRATE1:                       
			PD(drate1);                  
		break;                       
		case
			F_LSERIAL0:                     
			PI(lserial0);                
		break;                       
		case
			F_LSERIAL1:                     
			PI(lserial1);                
		break;                       
		case
			F_SBANKNAME:                    
			PC(sbankname);               
		break;                       
		case
			F_SBANKNAME2:                   
			PC(sbankname2);              
		break;                       
		case
			F_SCARD0:                       
			PC(scard0);                  
		break;                       
		case
			F_SCARD1:                       
			PC(scard1);                  
		break;                       
		case
			F_SORDER0:                      
			PC(sorder0);                 
		break;                       
		case
			F_SORDER1:                      
			PC(sorder1);                 
		break;                       
		case
			F_SORDER2:                      
			PC(sorder2);                 
		break;                       
		case
			F_VSMESS:                       
			PC(vsmess);                  
		break;       
		case
			F_SCUSTTYPES:
			PC(scusttypes);
		break;
		case
			F_SSECTYPES:
			PC(ssectypes);
		break;
		case
			F_VSVARSTR0:                    
			PC(vsvarstr0);               
		break;                       
		case
			F_VSVARSTR1:                    
			PC(vsvarstr1);               
		break;                       
		case
			F_VSVARSTR2:                    
			PC(vsvarstr2);               
		break;                       
		case
			F_VSVARSTR3:                    
			PC(vsvarstr3);               
		break;                       
	default:
		printf("not existed parameter=%d....\n",ids);
	}                                
}          
