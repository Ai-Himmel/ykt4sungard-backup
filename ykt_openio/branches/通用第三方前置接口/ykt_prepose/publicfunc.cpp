#include "stdafx.h"
#include "publicfunc.h"
char *getalderr(int errcode)
{
	
switch(errcode)  
	{
	 case   1:   return   "成功/房间存在";   break;  
	 case   400:   return   "数据校验错";   break; 
	 case   401:   return   "连接数据库错误";   break; 
	 case   402:   return   "一卡通帐号与房间不对应";   break; 
	 case   403:   return   "不存在的房间";   break; 
	 case   404:   return   "不存在的工作站";   break; 
	 case   406:   return   "数据丢失";   break; 
	 case   407:   return   "其它错误";   break; 
	 case   408:   return   "流水号无效";   break; 
	 case   409:   return   "存款余额不足";   break; 
	 case   410:   return   "流水号已存在";   break;
	 default: return ""; break;
	}
}

int makekstsqldata(queryaldrec &rcvquery,char *Tdata)
{   char log[1024]="[gateway_send]查询应答：";
	char *data=Tdata;
	size_t len=0;
	int errid=0;
	queryaldrec *ald_rcv=&rcvquery;
	char intem[200]="";
	char *temp=new char[200];
	char str[1024]="";
	char mmm[256]="";
	char mm[20]="";
	char *lenstr=new char[4];
	try
	{
		makestr("s","00000000",temp);
		strcat(str,temp);
		memset(intem,0,sizeof(intem));
		memcpy(intem,ald_rcv->type,4);
		//memcpy(intem,"1000",4);
		makestr("s",intem,temp);
		strcat(str,temp);
		memset(intem,0,sizeof(intem));
		memcpy(intem,ald_rcv->roomname,sizeof(ald_rcv->roomname));
		makestr("s",intem,temp);
		strcat(str,temp);
		makestr("s","",temp);
		strcat(str,temp);
		memset(intem,0,sizeof(intem));
		memcpy(intem,ald_rcv->money,16);
		if (strlen(intem)==0)
		{
			strcpy(intem,"0");
		}
		makestr("i",trim(intem),temp);
		strcat(str,temp);
		memset(intem,0,sizeof(intem));
		//memcpy(intem,ald_rcv->retnum,4);
		strcat(mmm,"返回：");
		memcpy(mm,ald_rcv->retnum,4);
		strcat(mmm,mm);
         WriteLog(mmm);
		if (strncmp(ald_rcv->retnum,"0001",4)==0)
		{
			strcpy(intem,"1");
		}
		else
		{	
			strcpy(intem,"3");
		}
		makestr("s",trim(intem),temp);
		strcat(str,temp);
		memset(intem,0,sizeof(intem));
		//memcpy(intem,"",1);
		if (strlen(ald_rcv->retnum)>0)
		{
			 if (strncmp(ald_rcv->retnum,"1111",4)==0)
			{
			memcpy(intem,"房间号不唯一",200);

			}
		    else if (strncmp(ald_rcv->retnum,"1112",4)==0)
			{
			memcpy(intem,"房间号不存在",200);
			} 
			else
			{
				errid=atoi(intem);
				if (errid)
				{
				memcpy(intem,getalderr(errid),strlen(getalderr(errid)));
				}
				else
				{
					if (strlen(ald_rcv->signature)==0)
					{
						memcpy(intem,"第三方连接超时！",30);
					}
					else
					{
					memcpy(intem,ald_rcv->signature,30);
					}
				}
			}
		}
		makestr("s",intem,temp);
		strcat(str,temp);
		len=strlen(str);
		_itoa((int)len,lenstr,10);
		makestr("i",lenstr,temp);
		strcat(data,temp);
		strcat(data,str);
		strcat(log,data);
		WriteLog(log);
		delete [] temp;
		delete [] lenstr;
	}
	catch (exception& e)
	{
		strcpy(log,e.what());
		WriteLog(log);
	}
	return 0;
}

int makekstsqldata_rj(queryaldrec &rcvquery,char *Tdata)
{   char log[1024]="[gateway_send]查询应答：";
	char *data=Tdata;
	size_t len=0;
	queryaldrec *ald_rcv=&rcvquery;
	char intem[200]="";
	char *temp=new char[200];
	char str[1024]="";
	char *lenstr=new char[4];
	makestr("s","00000000",temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	//memcpy(intem,ald_rcv->type,4);
	memcpy(intem,"1100",4);
	makestr("s",intem,temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,ald_rcv->roomname,22);
	makestr("s",intem,temp);
	strcat(str,temp);
	makestr("s","",temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,ald_rcv->money,16);
	makestr("i",trim(intem),temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,ald_rcv->retnum,4);
	makestr("s",intem,temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,"",1);
	makestr("s",intem,temp);
	strcat(str,temp);
	len=strlen(str);
	_itoa((int)len,lenstr,10);
	makestr("i",lenstr,temp);
    strcat(data,temp);
	strcat(data,str);
	strcat(log,data);
	WriteLog(log);
	delete [] temp;
	delete [] lenstr;
	return 0;
}




int getkst_ald_sqr(char *Tdata,kst_ald_sqr &sqr)
{
	char *data=Tdata;
	char dotype[5];
	int alllen;
	kst_ald_sqr *kstquery=&sqr;
	memset(kstquery,0,sizeof kstquery);
	char seps[]=":"   ;   
	char *token =NULL;
	WriteLog(data);
	char *buf = strstr(data, seps);
	buf[0]='\0';
	data = buf + strlen(seps);    
	token=getnextstr(data,seps,data); //报文长度
	alllen=atoi(token);
	token= getnextstr(data,seps,data); //标识码
	token= getnextstr(data,seps,data); //交易码查询
	strncpy(dotype,token,4); 
	token= getnextstr(data,seps,data); //收款方帐号
	strncpy(kstquery->roomname,token,sizeof(kstquery->roomname));
	token= getnextstr(data,seps,data); 
	strncpy(kstquery->stdu,token,sizeof(kstquery->stdu)); 
	token= getnextstr(data,seps,data); //姓名
	strncpy(kstquery->name, token,sizeof(kstquery->name));
	token= getnextstr(data,seps,data); //终端号
	strncpy(kstquery->tmlid,token,sizeof(kstquery->tmlid));
	token= getnextstr(data,seps,data);//支付金额
	strncpy(kstquery->amt,token,sizeof(kstquery->amt));
	token= getnextstr(data,seps,data);//附加域
	strncpy(kstquery->area,token,sizeof(kstquery->area));
  return 0;
}

int getkst_ald_pay(char *Tdata,kst_ald_pay &pay)
{
	char *data=Tdata;
	kst_ald_pay *kstpay=&pay;
	memset(kstpay,0,sizeof kstpay);
	int alllen;
	char dotype[5];
	char seps[]=":"   ;   
	char *token =NULL;
	WriteLog(data);
	char *buf = strstr(data, seps);
	buf[0]='\0';
	data = buf + strlen(seps);    
	token=getnextstr(data,seps,data); //报文长度
	alllen=atoi(token); 
	token= getnextstr(data,seps,data); //标识码
	strncpy(kstpay->idf,token,sizeof(kstpay->idf));
	token= getnextstr(data,seps,data); //交易码查询
	strncpy(kstpay->trcd, token,sizeof(kstpay->trcd));
	strncpy(dotype, token,4); 
	token= getnextstr(data,seps,data); //收款方帐号
	strncpy(kstpay->payaccount,token,sizeof(kstpay->payaccount));
	token= getnextstr(data,seps,data); //一卡通帐号
	strncpy(kstpay->account,token,sizeof(kstpay->account));  
	token= getnextstr(data,seps,data); //客户号
	strncpy(kstpay->customerid,token,sizeof(kstpay->customerid));
	token= getnextstr(data,seps,data); //学工号
	strncpy(kstpay->stdu,token,sizeof(kstpay->stdu));
	token= getnextstr(data,seps,data); //姓名
	strncpy(kstpay->name,token,sizeof(kstpay->name));
	token= getnextstr(data,seps,data); //校区
	strncpy(kstpay->schid,token,sizeof(kstpay->schid));
	token= getnextstr(data,seps,data); 
	strncpy(kstpay->tmlid,token,sizeof(kstpay->tmlid));//终端号 
	token= getnextstr(data,seps,data); 
	strncpy(kstpay->bfamt,token,sizeof(kstpay->bfamt));//交易前金额
	token= getnextstr(data,seps,data); 
	strncpy(kstpay->payamt,token,sizeof(kstpay->payamt));//
	token= getnextstr(data,seps,data); 
	strncpy(kstpay->datetime,token,sizeof(kstpay->datetime));//
	token= getnextstr(data,seps,data); 
	strncpy(kstpay->rfn,token,sizeof(kstpay->rfn));//
	token= getnextstr(data,seps,data); 
	strncpy(kstpay->paycode,token,sizeof(kstpay->paycode));//
	token= getnextstr(data,seps,data); 
	strncpy(kstpay->paytype,token,sizeof(kstpay->paytype));//
	token= getnextstr(data,seps,data); 
	strncpy(kstpay->remark,token,sizeof(kstpay->remark));//
	token= getnextstr(data,seps,data); 
	strncpy(kstpay->code,token,sizeof(kstpay->code));//
   return 0;
}


int getkst_ald_rvs(char *Tdata,kst_ald_rvs &rvs)
{
  char *data=Tdata;
  kst_ald_rvs *ald_pay=&rvs;
  memset(ald_pay,0,sizeof ald_pay);
  	int alllen;
	char dotype[5];
	char seps[]=":"   ;   
	char *token =NULL;
	char *buf = strstr(data, seps);
	buf[0]='\0';
	data = buf + strlen(seps);    
	token=getnextstr(data,seps,data); //报文长度
	alllen=atoi(token);
	token= getnextstr(data,seps,data); //标识码
	token= getnextstr(data,seps,data); //交易码查询
	strncpy(dotype,token,4); 
	token= getnextstr(data,seps,data); //收款方帐号
	strncpy(ald_pay->account,token,sizeof(ald_pay->account));
	token= getnextstr(data,seps,data); //终端号
	strncpy(ald_pay->tmlid,token,sizeof(ald_pay->tmlid));
	token= getnextstr(data,seps,data); //冲正金额
	strncpy(ald_pay->payamt,token,sizeof(ald_pay->payamt));
	token= getnextstr(data,seps,data); //冲正参考号
	strncpy(ald_pay->rfn,token,sizeof(ald_pay->rfn));
	token= getnextstr(data,seps,data); //备注
	strncpy(ald_pay->remark,token,sizeof(ald_pay->remark));
	token= getnextstr(data,seps,data); //验证码
	strncpy(ald_pay->code,token,sizeof(ald_pay->code));

  return 0;
}
int makequerysenddata(queryald &Tdata,kst_ald_sqr &sqr)
{
	char log[1024]="[gateway_receive]查询请求：";
	char strlog[1024]="";
	char str[1024]="";
	 kst_ald_sqr *kstquery=&sqr;
	 queryald *query=&Tdata;
	 memset(query,0,sizeof(query));
  	 strncpy(query->discern,"0",1);
	 strncpy(str,query->discern,sizeof(query->discern));  
	 strcat(strlog,str);
	 strncpy(query->length,"0142",4);
	 strncpy(str,query->length,sizeof(query->length));
	 strcat(strlog,str);
	 strncpy(query->type,"0006",4);
	 strncpy(str,query->type,sizeof(query->type));
	 strcat(strlog,str);
	 strncpy(query->bitmap,"0000000000000000",16);	
     strncpy(str,query->bitmap,sizeof(query->bitmap));
	 strcat(strlog,str);
	 strncpy(query->roomname,kstquery->roomname,sizeof(query->roomname));
	 strncpy(str,query->roomname,sizeof(query->roomname));
	 strcat(strlog,str);
	 strncpy(query->account,kstquery->stdu,22);  // 无需一卡通帐号
	// strncpy(query->account,"1                     ",22);  // 无需一卡通帐号
	 strncpy(str,query->account,sizeof(query->account));
	 strcat(strlog,str);
	 strncpy(query->Correspondence,"0",1);
	 strncpy(str,query->Correspondence,sizeof(query->Correspondence));
	 strcat(strlog,str);
	 strncpy(query->station,trim(kstquery->tmlid),sizeof(query->station));
     strncpy(str,query->station,sizeof(query->station));
	 strcat(strlog,str);
	 strncpy(query->signature,"                                ",32); 
	 strncpy(str,query->signature,sizeof(query->signature));
	 strcat(strlog,str);
	 strcat(log,strlog);
	 WriteLog(log);
  return 0;
}

int makepaysenddata(payelect &Tdata,kst_ald_pay &pay)
{
   char log[1024]="[gateway_receive]支付请求：";
  char strlog[1024]="";
  char str[1024]="";
  char mdstr[1024]="";
  int offset;
  unsigned  char  inmd5[105]="";
  unsigned char soutmd5[32]="";
  char signature[33]="";
  kst_ald_pay *ald_pay=&pay;
  payelect *query=&Tdata;
  memset(query,0,sizeof(query));
  strncpy(query->discern,"1",1);
  strncpy(str,query->discern,sizeof(query->discern)); 
  strcat(strlog,str);
  strncpy(query->length,"0142",4);
  strncpy(str,query->length,sizeof(query->length)); 
  strcat(strlog,str);
  strncpy(query->type,"0002",4);
  strncpy(str,query->type,sizeof(query->type)); 
  strcat(strlog,str);
  strncpy(query->bitmap,"0000000000000000",16);
  strncpy(str,query->bitmap,sizeof(query->bitmap));
  strcat(strlog,str);
  strncpy(query->roomname,ald_pay->payaccount,sizeof(query->roomname));
  strncpy(str,query->roomname,sizeof(query->roomname));
  strcat(strlog,str);
  strncpy(query->account,ald_pay->account,sizeof(query->account)); 
  strncpy(str,query->account,sizeof(query->account));
  strcat(strlog,str);
  strncpy(query->money,ald_pay->payamt,sizeof(query->money));
  strncpy(str,query->money,sizeof(query->money));
  strcat(strlog,str);
  strncpy(query->datetime,ald_pay->datetime,sizeof(query->datetime));
  strncpy(str,query->datetime,sizeof(query->datetime));
  strcat(strlog,str);  
  strncpy(query->tracenum,ald_pay->rfn,sizeof(ald_pay->rfn)); 
  strncpy(str,query->tracenum,sizeof(query->tracenum));
  strcat(strlog,str);
  strncpy(query->retnum,"    ",4);
  strncpy(str,query->retnum,sizeof(query->retnum));
   strcat(strlog,str); 
  strncpy(query->station,ald_pay->trcd,sizeof(query->station));
  strncpy(str,query->station,sizeof(query->station));
  strcat(strlog,str);
  offset=0;
  memcpy(mdstr,query->type,4);
  offset+=4;
  memcpy(mdstr+offset,query->bitmap,16);
  offset+=16;
  memcpy(mdstr+offset,query->roomname,20);
   offset+=20;
  memcpy(mdstr+offset,query->account,22);
   offset+=22;
  memcpy(mdstr+offset,query->money,7);
   offset+=7;
  memcpy(mdstr+offset,query->datetime,10);
   offset+=10;
  memcpy(mdstr+offset,query->tracenum,18);
   offset+=18;
  memcpy(mdstr+offset,query->retnum,4);
   offset+=4;
  memcpy(mdstr+offset,query->station,4);
   offset+=4;
  memcpy(inmd5,mdstr,105);
  memset(query->signature,0,sizeof(query->signature));
  CalcMD5(inmd5,sizeof(inmd5),soutmd5);
  dec2hex(soutmd5,16,signature);
  memcpy(query->signature,signature,32);
  strncpy(str,query->signature,sizeof(query->signature));
  strcat(strlog,str); 				  
  strcat(log,strlog);
  WriteLog(log);
  
  return 0;
}

int makervssenddata(payelect &Tdata,kst_ald_rvs &rvs)
{
  char log[1024]="[gateway_receive]请求冲正请求：";
  char strlog[1024]="";
  char str[1024]="";
  kst_ald_rvs *ald_rvs=&rvs;
  payelect *query=&Tdata;
  strncpy(query->bitmap, "0000000000000000",16);
  strncpy(query->length, "0142",4);
  strncpy(query->discern,"1",1);
  strncpy(query->type,"0003",4);
  strncpy(query->roomname,ald_rvs->account,sizeof(query->roomname));
  strncpy(query->station,ald_rvs->tmlid,sizeof(query->station)); 
  strncpy(query->signature,ald_rvs->code,sizeof(query->signature));
  strncpy(query->money,ald_rvs->payamt,sizeof(query->money));
  strncpy(query->retnum,"    ",4); 
  strncpy(query->tracenum,"                  ",18); 
  strncpy(str,query->discern, sizeof(query->discern)); 
  strcat(strlog,str);
  strncpy(str,query->length,sizeof(query->length)); 
  strcat(strlog,str);
  strncpy(str,query->type,sizeof(query->type)); 
  strcat(strlog,str);
  strncpy(str,query->bitmap,sizeof(query->bitmap));
  strcat(strlog,str);
  strncpy(str,query->roomname,sizeof(query->roomname));
  strcat(strlog,str);
  strncpy(str,query->tracenum,sizeof(query->tracenum));
  strcat(strlog,str);
  strncpy(str,query->retnum,sizeof(query->retnum));
  strcat(strlog,str);
  strncpy(str,query->money,sizeof(query->money));
  strcat(strlog,str);
  strncpy(str,query->station,sizeof(query->station));
  strcat(strlog,str);
  strncpy(str,query->signature,sizeof(query->signature));
  strcat(strlog,str);				
  strcat(log,strlog);
  WriteLog(log);
  return 0;
}
int makekstpaydata(ext_elect_req_t &pay,char *Tdata)
{
	char log[1024]="[gateway_send]支付应答：";
	char *data=Tdata;
	int errid;
	size_t len=0;
	ext_elect_req_t *pay_rcv=&pay;
	char *temp=new char[200];
	char intem[200]="";
	char str[1024]="";
	char *lenstr=new char[4];
	makestr("s","00000000",temp);	
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->type,4);
	//memcpy(intem,"1001",4);
	makestr("s",intem,temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->roomname,20);
	makestr("s",intem,temp);
	strcat(str,temp);
	memcpy(intem,pay_rcv->account,22);
	makestr("s",intem,temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->money,7);
	if (strlen(intem)==0)
	{
		strcpy(intem,"0");
	}
	makestr("i",intem,temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->tracenum,18);
	makestr("s",intem,temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	//memcpy(intem,pay_rcv->retnum,4);
	if (strncmp(pay_rcv->retnum,"0001",4)==0)
	{
		strcpy(intem, "1");
	}
	else
	{
		strcpy(intem,"3");
	}
	makestr("i",intem,temp);
	strcat(str,temp);
	if (strlen(trim(intem))>0)
	{
		errid=atoi(intem);
		memcpy(intem,getalderr(errid),200);
	}
	makestr("s",intem,temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->signature,32);
	makestr("s",intem,temp);
	strcat(str,temp);
	len=strlen(str);
	_itoa((int)len,lenstr,10);
	makestr("i",lenstr,temp);
    strcat(data,temp);
	strcat(data,str);
	strcat(log,data);
	WriteLog(log);
	delete [] temp;
	delete [] lenstr;
	return 0;
}

int makekstrecdata(ext_elect_req_t &pay,char *Tdata)
{
	char log[1024]="[gateway_send]冲正应答：";
	char *data=Tdata;
	size_t len=0;
	ext_elect_req_t *pay_rcv=&pay;
	char *temp=new char[200];
	char intem[200]="";
	char str[1024]="";
	char *lenstr=new char[4];
	makestr("s","00000000",temp);	
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
//	memcpy(intem,pay_rcv->type,4);
	memcpy(intem,"1002",4);
	makestr("s",intem,temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->account,22);
	makestr("s",intem,temp);
	strcat(str,temp);
	makestr("s","",temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->money,7);
	makestr("i",intem,temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->tracenum,18);
	makestr("s",intem,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->retnum,4);
	makestr("i",intem,temp);
	strcat(str,temp);
	makestr("s","",temp);
	strcat(str,temp);
	memset(intem,0,sizeof(intem));
	memcpy(intem,pay_rcv->signature,32);
	makestr("s",intem,temp);
	strcat(str,temp);
	len=strlen(str);
	_itoa((int)len,lenstr,10);
	makestr("i",lenstr,temp);
    strcat(data,temp);
	strcat(data,str);
	strcat(log,data);
	WriteLog(log);
	delete [] temp;
	delete [] lenstr;
	return 0;
}
int get_rj_query(char *Tdata,queryaldrec &rtquery)
{
	queryaldrec *query=&rtquery;
	char *data=Tdata;
	char *temp=new char[256];
	char seps0[]=":"   ;   
	char seps1[]="="   ; 
	char seps2[]="\""   ; 
	char seps4[]=","   ; 
	char *token =NULL;
	WriteLog(data);
//	strcpy(data,"ACK:LOGININFO=\"\",SEX=\"0\",AUTHORIP=\"\",STATEFLAG=\"2\",CERTTYPE=\"0\",NASIP=\"\",ADDRESS=\"\",FILTERID=\"\",EDU=\"0\",CERTNO=\"\",PACKAGENAME=\"免费\",POSTCODE=\"\",MOBILE=\"\",NASPORT=\"0\",EMAIL=\"\",SELFSERVPERM=\"所有自助权限\",TEL=\"\",ATNAME=\"default\",USERNAME=\"王家荣\",FREEAUTHEN=\"1\",USERGROUPNAME=\"root\",USERIP=\"\",USERVLAN=\"0\",USERID=\"20100820\",USERMAC=\"\",USERPRIVILEGE=\"0\"");
	char *buf = strstr(data, seps0);
	buf[0]='\0';
	if (strcmp(data,"ACK")==0)
	{
		data = buf + strlen(seps0);    
		token=getnextstr(data,seps1,data); //报文长度 
		strcpy(temp,token);
		token=getnextstr(temp,seps2,temp);
		strcpy(query->roomname, token); 
		strcpy(query->retnum,"0001");
	}
	else
	{
		strcpy(query->retnum, "0003");
	}
	delete [] temp;
	return 0;
}
