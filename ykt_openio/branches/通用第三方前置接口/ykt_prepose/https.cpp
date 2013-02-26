#include "stdafx.h"
#include "https.h" 
#include <iconv.h>
#include "tinyxml.h"
#include "utf8.h"
#include <curl.h>
#include "md5str.h"
#include "socket.h"
#include <iostream>
#include <windows.h> 
//#include <shellapi.h>
#define ISALPHA(x)  (isalpha((int)  ((unsigned char)x)))
curl_slist* headerlist;
using namespace std;
static void *myrealloc(void *ptr, size_t size);

static void *myrealloc(void *ptr, size_t size)
{
  /* There might be a realloc() out there that doesn't like reallocing
     NULL pointers, so we take care of it here */
  if(ptr)
    return realloc(ptr, size);
  else
    return malloc(size);
}

static size_t
WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)data;
  mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory) {
    memcpy(&(mem->memory[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
  }
  return realsize;
}
 
char* getdatetime()
{
	time_t rawtime;
	char datetime[30]="";
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(datetime, 30, "%Y-%m-%d %H:%M:%S", timeinfo);
	return datetime;
}

//////////////////////////////////////////////////////////////////////////////////
//获得xml数据
//
//
//
////////////////////////////////////////////////////////////////////////////////
int GetXmlData(char * data,Agd_ThirdPay &ThirdPay,char* fistchild)
{
	char restlt[20]="";
	char ecard_id[20]="";
	char action[20]="";
	char log[1024]="";
	char msg[20]="";
	char reply_time[20]="";
	TiXmlDocument doc;
	KeyValueMap  _params;
	string temp;
	WriteLog("xml");
	//WriteLog(data);
	strcpy(log,"[response third]");
	strcat(log,data);
	WriteLog(log);
	doc.Parse(data);
	if (strlen(data)==0)
	{
	WriteLog("无返回信息！");
	return -1;
	}
	TiXmlNode* root = doc.FirstChild(fistchild);
	if(!root){
		WriteLog(fistchild);
		WriteLog("数据不合法");
		return -1;
	}
	TiXmlNode* elem = root->FirstChild();
	while(elem!=NULL)
	{
		TiXmlNode* t = elem->FirstChild();
		if(t)
		{
			KeyValueMap::iterator i = _params.find(elem->Value());
			if( i == _params.end() )
			{
			_params.insert(KeyValueMap::value_type(elem->Value(),t->Value()));
			}
		}
		elem = elem->NextSibling();
	}
	
	KeyValueMap::const_iterator i = _params.find("status");
	if(i != _params.end())
	{
		temp=i->second;
		char* str = _strdup ( temp.c_str() );
		strcpy(restlt,str);
		strcpy(ThirdPay.status,restlt);
		
	}
	 i = _params.find("ecard_id");
	if(i != _params.end())
	{
	temp=i->second;
	char* str = _strdup ( temp.c_str() );
	strcpy(ecard_id,str);
	}
	 i = _params.find("action");
	if(i != _params.end())
	{
	temp=i->second;
	char* str = _strdup ( temp.c_str() );
	strcpy(action,str);
	}  
	i = _params.find("msg");
	if(i != _params.end())
	{
	temp=i->second;
	char* str = _strdup ( temp.c_str() );
	strcpy(msg,str);
	}  
	 i = _params.find("reply_time");
	if(i != _params.end())
	{
	temp=i->second;
	char* str = _strdup ( temp.c_str() );
	strcpy(reply_time,str);
	strcpy(ThirdPay.reply_time,reply_time);
	strcpy(ThirdPay.update_time,reply_time);
	} 
	 i = _params.find("inpayamount_id");
	if(i != _params.end())
	{
	temp=i->second;
	char* str = _strdup ( temp.c_str() );
	strcpy(ThirdPay.inpayamount_id,str);
	} 
	 i = _params.find("fullname");
	if(i != _params.end())
	{
	temp=i->second;
	char* str = _strdup ( temp.c_str() );
	strcat(log,"获得第三方姓名：");
	strcat(log,str);
	WriteLog(log);
	strcpy(ThirdPay.fullname,str);
	} 
	memset(log,0,sizeof log);
	strcat(log,action);
	strcat(log,"   ");
	strcat(log,ecard_id);
	strcat(log,"   ");
	strcat(log,restlt);
	strcat(log,"   ");
	strcat(log,msg);
	strcat(log,"   ");
	strcat(log,reply_time);
	WriteLog(log);
	if (strcmp(restlt,"成功")!=0)
	{
	return -1;
	}
	WriteLog("成功！");
	return 0;

}




char* intdata(char* str)
{
	char senddata[1024]="";
	char urldata[1024]="";
	char * to_str = NULL;
	size_t nNonRevrt = 0;  //non-reversible characters
	size_t to_str_len = 0;
	unsigned  char  inmd5[1024]="";
	unsigned char soutmd5[32]="";
	char st[33]="";
	char temp[33]="";
	time_t   tmCurrent   =   time(NULL);
	memset(senddata,0,sizeof senddata);
	strcat(senddata,"action=init");
	strcat(senddata,"&time=");
	sprintf(urldata,"%ld",tmCurrent);
	strcat(senddata,urldata);
	strcat(temp,localip);
	strcat(temp,urldata);
	MD5 md5;
	md5.update(temp);
	strcat(senddata,"&code=");
	memset(urldata,0,sizeof urldata);
	strcpy(urldata,md5.toString().c_str());
	reverse_str(urldata);
	strcat(senddata,urldata);
	nNonRevrt = Gb2312ToUtf8(senddata,strlen(senddata),&to_str,&to_str_len);
	strcpy(senddata,to_str);
	strcpy(str,senddata);
	return senddata;
}



char* makegetname(kst_ald_pay pay)
{
	char senddata[1024]="";
	char urldata[1024]="";
	char tmpstr[1024]="";
	char logstr[1024]="";
	double money=0.0;
	char* to_str = NULL;
	size_t to_str_len = 0;
	unsigned  char  inmd5[1024]="";
	unsigned char soutmd5[32]="";
	size_t nNonRevrt = 0;  //non-reversible characters
	char st[32]="";
	char datetime[30]="";
	char temp[32]="";
	strcpy(datetime,getdatetime());
	time_t   tmCurrent   =   time(NULL);
	memset(senddata,0,sizeof senddata);
	strcat(senddata,"action=userinfo");
	strcat(senddata,"&username=");
	memset(tmpstr,0,sizeof tmpstr);
	WriteLog(pay.payaccount);
	memcpy(tmpstr,pay.payaccount,sizeof pay.payaccount);
	strcat(senddata,tmpstr);
	WriteLog(senddata);
	try
	{
	nNonRevrt = Gb2312ToUtf8(senddata,strlen(senddata),&to_str,&to_str_len);
	}
    catch (exception& e)
    {
	    strcpy(logstr,e.what());
		WriteLog(logstr);
	 } 
	//WriteLog(to_str);
	return to_str;
}




char* destorydata(char* str)
{
	char senddata[1024]="";
	char urldata[1024]="";
	char* to_str = NULL;
	size_t to_str_len = 0;
	size_t nNonRevrt = 0;  //non-reversible characters
	unsigned  char  inmd5[1024]="";
	unsigned char soutmd5[32]="";
	char st[32]="";
	char temp[32]="";
	time_t   tmCurrent   =   time(NULL);
	memset(senddata,0,sizeof senddata);
	strcat(senddata,"action=destroy");
	strcat(senddata,"&time=");
	sprintf_s(urldata,"%ld",tmCurrent);
	strcat(senddata,urldata);
	strcat(temp,localip);
	strcat(temp ,urldata);
	MD5 md5;
	md5.update(temp);
	strcat(senddata,"&code=");
	memset(urldata,0,sizeof urldata);
	strcpy(urldata,md5.toString().c_str());
	reverse_str(urldata);
	strcat(senddata,urldata);
	nNonRevrt = Gb2312ToUtf8(senddata,strlen(senddata),&to_str,&to_str_len);
	WriteLog(senddata);
	strcpy(str,to_str);
	return str;
}

char* paydata(kst_ald_sqr query)
{
	char senddata[1024]="";
	char urldata[1024]="";
	char tmpstr[1024]="";
	double money=0.0;
	 char* to_str = NULL;
	 size_t to_str_len = 0;
	unsigned  char  inmd5[1024]="";
	unsigned char soutmd5[32]="";
	size_t nNonRevrt = 0;  //non-reversible characters
	char st[32]="";
	char datetime[30]="";
	char temp[32]="";
	strcpy(datetime,getdatetime());
	time_t   tmCurrent   =   time(NULL);
	memset(senddata,0,sizeof senddata);
	strcat(senddata,"action=recharge_request");
	strcat(senddata,"&time=");
	sprintf_s(urldata,"%ld",tmCurrent);
	strcat(senddata,urldata);
	//memset(urldata,0,sizeof urldata);
	strcat(temp,localip);
	strcat(temp,urldata);
	MD5 md5;
	md5.update(temp);
	strcat(senddata,"&code=");
	memset(urldata,0,sizeof urldata);
	strcpy(urldata,md5.toString().c_str());
	reverse_str(urldata);
	strcat(senddata,urldata);
    strcat(senddata,"&ecard_id=");
	memset(urldata,0,sizeof urldata);
	sprintf_s(urldata,"%ld",tmCurrent);
	strcat(senddata,urldata);
	strcat(senddata,"&request_time=");
	strcat(senddata,datetime);
	strcat(senddata,"&ecard_num=");
	memset(tmpstr,0,sizeof tmpstr);
    memcpy(tmpstr,query.stdu,sizeof query.stdu);
	strcat(senddata,tmpstr);
	strcat(senddata,"&username=");
	memset(tmpstr,0,sizeof tmpstr);
	WriteLog(query.roomname);
	memcpy(tmpstr,query.roomname,sizeof query.roomname);
	strcat(senddata,tmpstr);
	strcat(senddata,"&fullname=");
	memset(tmpstr,0,sizeof tmpstr);
	memcpy(tmpstr,query.name,sizeof query.name);
	strcat(senddata,tmpstr);
	strcat(senddata,"&amount=");
	memset(tmpstr,0,sizeof tmpstr);
	money=atoi(query.amt)/100;
	WriteLog(query.amt);
	sprintf(query.amt,"%0.2f",money);//转化成元
	memcpy(tmpstr,query.amt,sizeof query.amt);
	WriteLog(query.amt);
	strcat(senddata,tmpstr);
	strcat(senddata,"&ecard_machine_id=");
	memset(tmpstr,0,sizeof tmpstr);
	memcpy(tmpstr,query.tmlid,sizeof query.tmlid);
	strcat(senddata,tmpstr);
	WriteLog(senddata);
	nNonRevrt = Gb2312ToUtf8(senddata,strlen(senddata),&to_str,&to_str_len);
	//WriteLog(to_str);
	return to_str;
}


char* get_std_name(kst_ald_sqr query)
{
	char senddata[1024]="";
	char urldata[1024]="";
	char tmpstr[1024]="";
	char logstr[1024]="";
	double money=0.0;
	 char* to_str = NULL;
	 size_t to_str_len = 0;
	unsigned  char  inmd5[1024]="";
	unsigned char soutmd5[32]="";
	size_t nNonRevrt = 0;  //non-reversible characters
	char st[32]="";
	char datetime[30]="";
	char temp[32]="";
	strcpy(datetime,getdatetime());
	time_t   tmCurrent   =   time(NULL);
	memset(senddata,0,sizeof senddata);
	strcat(senddata,"action=userinfo");
	strcat(senddata,"&username=");
	memset(tmpstr,0,sizeof tmpstr);
	WriteLog(query.roomname);
	memcpy(tmpstr,query.roomname,sizeof query.roomname);
	strcat(senddata,tmpstr);
	WriteLog(senddata);
	try
	{
	nNonRevrt = Gb2312ToUtf8(senddata,strlen(senddata),&to_str,&to_str_len);
	}
    catch (exception& e)
    {
	    strcpy(logstr,e.what());
		WriteLog(logstr);
	 } 
	//WriteLog(to_str);
	return to_str;
}


char* get_payid_date(kst_ald_pay pay,Agd_ThirdPay &ThirdPay)
{
	char senddata[1024]="";
	char urldata[1024]="";
	char tmpstr[1024]="";
	 char* to_str = NULL;
	 size_t to_str_len = 0;
	unsigned  char  inmd5[1024]="";
	double money=0.0;
	unsigned char soutmd5[32]="";
	size_t nNonRevrt = 0;  //non-reversible characters
	char st[32]="";
	char datetime[30]="";
	char temp[32]="";
	strcpy(datetime,getdatetime());
	time_t   tmCurrent   =   time(NULL);
	memset(senddata,0,sizeof senddata);
	strcat(senddata,"action=recharge_request");
	strcat(senddata,"&time=");
	sprintf_s(urldata,"%ld",tmCurrent);
	strcat(senddata,urldata);
	//memset(urldata,0,sizeof urldata);
	strcat(temp,localip);
	strcat(temp,urldata);
	MD5 md5;
	md5.update(temp);
	strcat(senddata,"&code=");
	memset(urldata,0,sizeof urldata);
	strcpy(urldata,md5.toString().c_str());
	reverse_str(urldata);
	strcat(senddata,urldata);
    strcat(senddata,"&ecard_id=");
	memset(tmpstr,0,sizeof tmpstr);
	memcpy(tmpstr,pay.rfn,sizeof pay.rfn);
	strcpy(ThirdPay.ecard_id,tmpstr);
	strcat(senddata,tmpstr);
	strcat(senddata,"&request_time=");
	strcpy(ThirdPay.request_time,datetime);
	strcat(senddata,datetime);
	strcat(senddata,"&ecard_num=");
	memset(tmpstr,0,sizeof tmpstr);
	memcpy(tmpstr,pay.stdu,sizeof pay.stdu);
	strcpy(ThirdPay.ecard_num,tmpstr);
	strcat(senddata,tmpstr);
	strcat(senddata,"&username=");
	memset(tmpstr,0,sizeof tmpstr);
	memcpy(tmpstr,pay.payaccount,sizeof pay.payaccount);
	strcpy(ThirdPay.username,tmpstr);
	strcat(senddata,tmpstr);
	strcat(senddata,"&fullname=");
	memset(tmpstr,0,sizeof tmpstr);
	memcpy(tmpstr,pay.name,sizeof pay.name);
	strcpy(ThirdPay.fullname,tmpstr);
	strcat(senddata,tmpstr);
	strcat(senddata,"&amount=");
	memset(tmpstr,0,sizeof tmpstr);
	money=atoi(pay.payamt)/100;
	WriteLog(pay.payamt);
	sprintf(pay.payamt,"%0.2f",money);//转化成元
	WriteLog(pay.payamt);
	memcpy(tmpstr,pay.payamt,sizeof pay.payamt);
	strcpy(ThirdPay.amount,tmpstr);
	strcat(senddata,tmpstr);
	strcat(senddata,"&ecard_machine_id=");
	memset(tmpstr,0,sizeof tmpstr);
	memcpy(tmpstr,pay.tmlid,sizeof pay.tmlid);
	strcpy(ThirdPay.ecard_machine_id,tmpstr);
	strcat(senddata,tmpstr);
	nNonRevrt = Gb2312ToUtf8(senddata,strlen(senddata),&to_str,&to_str_len);
	WriteLog(to_str);
	return to_str;
}



char* fixdata(kst_ald_pay pay,Agd_ThirdPay &ThirdPay)
{
	char senddata[1024]="";
	char urldata[1024]="";
	char tmpstr[1024]="";
	char* to_str = NULL;
	size_t to_str_len = 0;
	size_t nNonRevrt = 0;  //non-reversible characters
	char st[32]="";
	unsigned  char  inmd5[1024]="";
	unsigned char soutmd5[32]="";
	char temp[32]="";
	char datetime[30]="";
	char sql[1024]="";
	strcat(sql,"");
	strcpy(datetime,getdatetime());
	time_t   tmCurrent   =   time(NULL);
	memset(senddata,0,sizeof senddata);
	strcat(senddata,"action=recharge_ack");
	strcat(senddata,"&time=");
	sprintf_s(urldata,"%ld",tmCurrent);
	strcat(senddata,urldata);
	//memset(urldata,0,sizeof urldata);
	strcat(temp,localip);
	strcat(temp ,urldata);
	MD5 md5;
	md5.update(temp);
	strcat(senddata,"&code=");
	memset(urldata,0,sizeof urldata);
	strcpy(urldata,md5.toString().c_str());
	reverse_str(urldata);
	strcat(senddata,urldata);
	strcat(senddata,"&ecard_id=");
	memset(tmpstr,0,sizeof tmpstr);
	memcpy(tmpstr,pay.rfn,sizeof pay.rfn);
	strcat(senddata,tmpstr);
	strcat(senddata,"&inpayamount_id=");
	strcat(senddata,ThirdPay.inpayamount_id);
	strcat(senddata,"&ack_time=");
	strcpy(ThirdPay.ack_time,datetime);
    strcat(senddata,datetime);
	nNonRevrt = Gb2312ToUtf8(senddata, strlen(senddata),&to_str,&to_str_len);
	WriteLog(to_str);
	return to_str;
}

int sendhttpsint()
{
	  char strsend[1024]="";
	  char logstr[1024]="";
	  char temp[1024]="";
	  char restlt[1024]="";
	  size_t nSize=0;
	  char inpayamount_id[20]="";
	  char fullname[50]="";
	  int ret=0;
	  size_t nNonRevrt = 0;  //non-reversible characters
	 char* to_str = NULL;
     size_t to_str_len = 0;
	 struct MemoryStruct chunk={0};
     CURL *curl=0;
	 CURLcode res;
	 Agd_ThirdPay ThirdPay;
	 memset(&ThirdPay,0,sizeof(ThirdPay));
	 curl_global_init(CURL_GLOBAL_ALL);
	 curl = curl_easy_init();
	 if (curl)
	  {
		 res=curl_easy_setopt(curl,CURLOPT_URL,httppath);
		 if (CURLE_OK!=res)
		{
			WriteLog("设置连接失败！");
			 return -1;
		 }
		  memset(strsend,0,sizeof strsend);
		  intdata(strsend);
		  WriteLog(strsend);
		    WriteLog("准备数据！");
		  res=curl_easy_setopt(curl,CURLOPT_POSTFIELDS,strsend);
		 if (CURLE_OK!=res)
		  {
		   WriteLog("准备数据失败！");
		   return -1;
		  }
		  res= curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
         if (CURLE_OK!=res)
		 {
			 WriteLog("CURLOPT_SSL_VERIFYPEER！");
			 return -1;
		 }
		  res =curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		 if (res!= CURLE_OK)
		 {  
			memset(logstr,0,sizeof logstr);
			strcat(logstr,"WriteMemoryCallback！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
		     return -1;
		  }
		  res =  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		  if (res!= CURLE_OK)
		  {
				memset(logstr,0,sizeof logstr);
				strcat(logstr,"CURLOPT_WRITEDATA！错误码：");
				sprintf_s(temp,"%d",res);
				strcat(logstr,temp);
				 WriteLog(logstr);
				 return -1;
		  }
		    /* some servers don't like requests that are made without a user-agent
        field, so we provide one */
		 res =  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		 if (res!= CURLE_OK)
		 {   memset(logstr,0,sizeof logstr);
			 strcat(logstr,"CURLOPT_USERAGENT！错误码：");
			 sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			 return -1;
		  }
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR,"cookie.txt");  
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE,"cookie.txt");

		  WriteLog("curl_easy_perform！");
		  try
		  {
			 res = curl_easy_perform(curl);
		  }
		  catch (exception& e)
		  {
			   strcpy(logstr,e.what());
				WriteLog(logstr);
		  } 
		 if (res!= CURLE_OK)
	    {  
			memset(logstr,0,sizeof logstr);
			strcat(logstr,"请求数据失败！错误码：");
			sprintf_s(temp,"%d",res);
			strcat(logstr,temp);
			WriteLog(logstr);
			 return -1;
	  	 } 
		  WriteLog("chunk.memory！");
		 if(chunk.memory)
		{
		 WriteLog(chunk.memory);
			 nSize=strlen(chunk.memory);
			 nNonRevrt = Utf8ToGb2312(chunk.memory,nSize,&to_str,&to_str_len);
			 strcpy(restlt,to_str);
			 ret=GetXmlData(restlt,ThirdPay,"ecard");
			 if (ret)
			{
			 return -1 ;
			}
		}
		 WriteLog("curl_easy_cleanup！");
		 curl_easy_cleanup(curl);
	   if(chunk.memory)
		 free(chunk.memory);
		 curl_global_cleanup();
	 }
	  return 0;
}

int get_name_httpquest(kst_ald_pay &pay,Agd_ThirdPay &ThirdPay)
{
	  char strsend[1024]="";
	  char logstr[1024]="";
	  char temp[1024]="";
	  char restlt[1024]="";
	  char httpstr[100]="";
	  char inpayamount_id[20]="";
	  char *postdata=NULL;
	  size_t size=0;
	  size_t nSize=0;
	  int ret=0;
	  size_t nNonRevrt = 0;  //non-reversible characters
	  char* to_str = NULL;
      size_t to_str_len = 0;
	  struct MemoryStruct chunk={0};
      CURL *curl=0;
	  CURLcode res;
	  curl_global_init(CURL_GLOBAL_ALL);
	  curl = curl_easy_init();
		if (curl)
		{
		char *p;
		memset(temp,0,sizeof temp);
		strcpy(temp,httppath);
		p=strrchr(temp,'/');  
		memcpy(httpstr,temp,strlen(temp)-strlen(p));
		memset(temp,0,sizeof temp);
		strcpy(temp,httpstr);
		memset(httpstr,0,sizeof httpstr);
		p=strrchr(temp,'/');  
		memcpy(httpstr,temp,strlen(temp)-strlen(p));
		strcat(httpstr,"/info.html");
		res=curl_easy_setopt(curl,CURLOPT_URL,httpstr);
		 if (CURLE_OK!=res)
		{
		 WriteLog("设置连接失败！");
		 return -1;
		}
		 memset(strsend,0,sizeof strsend); 
		res=curl_easy_setopt(curl,CURLOPT_POSTFIELDS,makegetname(pay));
		 if (CURLE_OK!=res)
		{
			 WriteLog("准备数据失败！");
			 return -1;
		}

	   res= curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
       if (CURLE_OK!=res)
		{
		 WriteLog("CURLOPT_SSL_VERIFYPEER！");
		  return -1;
		}
		 res =curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		 if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"WriteMemoryCallback！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
		 return -1;
		}
		 res =  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		  if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_WRITEDATA！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		    /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
		res =  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_USERAGENT！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR,"cookie.txt");  
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE,"cookie.txt");
		try
		{
		 res = curl_easy_perform(curl);
		}
		 catch (exception& e)
		 {
		   strcpy(logstr,e.what());
	     	WriteLog(logstr);
		 } 
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"发送数据失败！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		if(chunk.memory)
		{
				 nSize=strlen(chunk.memory);
				 nNonRevrt = Utf8ToGb2312(chunk.memory,nSize,&to_str,&to_str_len);
				 strcpy(restlt,to_str);
				 ret=GetXmlData(restlt,ThirdPay,"info");
				 if (ret)
				 {
					 return -1 ;
				  }
			 memset(pay.name,0,sizeof pay.name);
			 strcpy(pay.name,ThirdPay.fullname);
				 
		}
		  curl_easy_cleanup(curl);
		  if(chunk.memory)
		  free(chunk.memory);

		 /* we're done with libcurl, so clean it up */
		 curl_global_cleanup();
	}
	return 0;
}


int send_https_get_usename(kst_ald_sqr &query,Agd_ThirdPay &ThirdPay)
{
	  char strsend[1024]="";
	  char logstr[1024]="";
	  char temp[1024]="";
	  char restlt[1024]="";
	  char inpayamount_id[20]="";
	  char *postdata=NULL;
	  char httpstr[100]="";
	  size_t size=0;
	  size_t nSize=0;
	  int ret=0;
	  size_t nNonRevrt = 0;  //non-reversible characters
	  char* to_str = NULL;
      size_t to_str_len = 0;
	  struct MemoryStruct chunk ={0};
      CURL *curl = 0;
	  CURLcode res;
	  curl_global_init(CURL_GLOBAL_ALL);
	  curl = curl_easy_init();
		if (curl)
		{
		char *p;
		memset(temp,0,sizeof temp);
		strcpy(temp,httppath);
		p=strrchr(temp,'/');  
		memcpy(httpstr,temp,strlen(temp)-strlen(p));
		memset(temp,0,sizeof temp);
		strcpy(temp,httpstr);
		memset(httpstr,0,sizeof httpstr);
		p=strrchr(temp,'/');  
		memcpy(httpstr,temp,strlen(temp)-strlen(p));
		strcat(httpstr,"/info.html");
		res=curl_easy_setopt(curl,CURLOPT_URL,httpstr);
		 if (CURLE_OK!=res)
		{
		 WriteLog("设置连接失败！");
		 return -1;
		}
		 memset(strsend,0,sizeof strsend); 
		res=curl_easy_setopt(curl,CURLOPT_POSTFIELDS,get_std_name(query));
		 if (CURLE_OK!=res)
		{
			 WriteLog("准备数据失败！");
			 return -1;
		}

	   res= curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
       if (CURLE_OK!=res)
		{
		 WriteLog("CURLOPT_SSL_VERIFYPEER！");
		  return -1;
		}
		 res =curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		 if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"WriteMemoryCallback！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
		 return -1;
		}
		 res =  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		  if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_WRITEDATA！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		    /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
		res =  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_USERAGENT！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR,"cookie.txt");  
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE,"cookie.txt");
		try
		{
		 res = curl_easy_perform(curl);
		}
		 catch (exception& e)
		 {
		   strcpy(logstr,e.what());
	     	WriteLog(logstr);
		 } 
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"发送数据失败！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		if(chunk.memory)
		{
				 nSize=strlen(chunk.memory);
				 nNonRevrt = Utf8ToGb2312(chunk.memory,nSize,&to_str,&to_str_len);
				 strcpy(restlt,to_str);
				  WriteLog("获得姓名：");
                  WriteLog(restlt);
				 ret=GetXmlData(restlt,ThirdPay,"info");
				 if (ret)
				 {
					 return -1 ;
				  }
				 memset(query.name,0,sizeof query.name);
				 strcpy(query.name,ThirdPay.fullname);
				 memset(query.area,0,sizeof query.area);
				 strcpy(query.area,logstr);
		}
		  curl_easy_cleanup(curl);
		  if(chunk.memory)
		  free(chunk.memory);

		 /* we're done with libcurl, so clean it up */
		 curl_global_cleanup();
	}
	return 0;
}

int send_https_get_inpayamountid(kst_ald_sqr &query,Agd_ThirdPay &ThirdPay)
{
	  char strsend[1024]="";
	  char logstr[1024]="";
	  char temp[1024]="";
	  char restlt[1024]="";
	  char inpayamount_id[20]="";
	  char fullname[50]="";
	  char *postdata=NULL;
	  size_t size=0;
	  size_t nSize=0;
	  int ret=0;
	  size_t nNonRevrt = 0;  //non-reversible characters
	  char* to_str = NULL;
      size_t to_str_len = 0;
	  struct MemoryStruct chunk={0};
      CURL *curl=0;
	  CURLcode res;
	  curl_global_init(CURL_GLOBAL_ALL);
	  curl = curl_easy_init();
		if (curl)
		{
		res=curl_easy_setopt(curl,CURLOPT_URL,httppath);
		 if (CURLE_OK!=res)
		{
		 WriteLog("设置连接失败！");
		 return -1;
		}
		 memset(strsend,0,sizeof strsend); 
		res=curl_easy_setopt(curl,CURLOPT_POSTFIELDS,paydata(query));
		 if (CURLE_OK!=res)
		{
			 WriteLog("准备数据失败！");
			 return -1;
		}

	   res= curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
       if (CURLE_OK!=res)
		{
		 WriteLog("CURLOPT_SSL_VERIFYPEER！");
		  return -1;
		}
		 res =curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		 if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"WriteMemoryCallback！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
		 return -1;
		}
		 res =  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		  if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_WRITEDATA！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		    /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
		res =  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_USERAGENT！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR,"cookie.txt");  
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE,"cookie.txt");
		try
		{
		 res = curl_easy_perform(curl);
		}
		 catch (exception& e)
		 {
		   strcpy(logstr,e.what());
	     	WriteLog(logstr);
		 } 
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"发送数据失败！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
			if(chunk.memory)
		{
		 nSize=strlen(chunk.memory);
		 nNonRevrt = Utf8ToGb2312(chunk.memory,nSize,&to_str,&to_str_len);
         strcpy(restlt,to_str);
		 ret=GetXmlData(restlt,ThirdPay,"ecard");
		 if (ret)
		 {
			 return -1 ;
		  }
		 memset(query.area,0,sizeof query.area);
		 strcpy(query.area,logstr);
		}
		  curl_easy_cleanup(curl);
		  if(chunk.memory)
		  free(chunk.memory);

		 /* we're done with libcurl, so clean it up */
		 curl_global_cleanup();
	}
	return 0;
}

int get_pay_id(kst_ald_pay &query,Agd_ThirdPay &ThirdPay)
{
	  char strsend[1024]="";
	  char logstr[1024]="";
	  char temp[1024]="";
	  char restlt[1024]="";
	  char fullname[50]="";
	  char *postdata=NULL;
	  size_t size=0;
	  size_t nSize=0;
	  int ret=0;
	  size_t nNonRevrt = 0;  //non-reversible characters
	  char* to_str = NULL;
      size_t to_str_len = 0;
	  struct MemoryStruct chunk={0};
	  WriteLog("get_pay_id！");
      CURL *curl=0;
	  CURLcode res;
	  curl_global_init(CURL_GLOBAL_ALL);
	  curl = curl_easy_init();
		if (curl)
		{
		res=curl_easy_setopt(curl,CURLOPT_URL,httppath);
		 if (CURLE_OK!=res)
		{
		 WriteLog("设置连接失败！");
		 return -1;
		}
		 memset(strsend,0,sizeof strsend); 
		 try
		 {
			res=curl_easy_setopt(curl,CURLOPT_POSTFIELDS, get_payid_date(query,ThirdPay));
		 }
		  catch (exception& e)
		  {
			   strcpy(logstr,e.what());
				WriteLog(logstr);
		  } 
		 if (CURLE_OK!=res)
		{
		 WriteLog("准备数据失败！");
		  return -1;
		}
      res= curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
       if (CURLE_OK!=res)
		{
		 WriteLog("CURLOPT_SSL_VERIFYPEER！");
		  return -1;
		}
	   	   WriteLog("curl_easy_setopt！");
		 res =curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		 if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"WriteMemoryCallback！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
		     return -1;
		}
		 res =  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		  if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_WRITEDATA！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		    /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
		res =  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_USERAGENT！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			 return -1;
		}
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR,"cookie.txt");  
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE,"cookie.txt");
		try
		{
		 res = curl_easy_perform(curl);
		}
		catch (exception& e)
		 {
		   strcpy(logstr,e.what());
			WriteLog(logstr);
		 } 
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"发送数据失败！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		if(chunk.memory)
		{
			try

			{
				 nSize=strlen(chunk.memory);
				 WriteLog(chunk.memory);
				 nNonRevrt = Utf8ToGb2312(chunk.memory,nSize,&to_str,&to_str_len);
				 strcpy(restlt,to_str);
				 ret=GetXmlData(restlt,ThirdPay,"ecard");
				 if (ret)
				 {
					 return -1 ;
				  }
			}
				catch (exception& e)
			 {
			   strcpy(logstr,e.what());
				WriteLog(logstr);
			 } 	
		}
		  curl_easy_cleanup(curl);
		 if(chunk.memory)
		  free(chunk.memory);
		 /* we're done with libcurl, so clean it up */
		 curl_global_cleanup();
	}
	return 0;
}
int sendhttpsdestory()
{
	  char strsend[1024]="";
	  char logstr[1024]="";
	  char temp[1024]="";
	  char restlt[1024]="";
	  char inpayamount_id[20]="";
	  char fullname[50]="";
	  int ret=0;
	  size_t nNonRevrt = 0;  //non-reversible characters
	  char* to_str = NULL;
      size_t to_str_len = 0;
      size_t nSize=0;
	  struct MemoryStruct chunk={0};
      CURL *curl=0;
	  CURLcode res;
	  Agd_ThirdPay ThirdPay={0};
	  memset(&ThirdPay,0,sizeof(ThirdPay));
	  curl_global_init(CURL_GLOBAL_ALL);
	  curl = curl_easy_init();
	  if (curl)
		{
			res=curl_easy_setopt(curl,CURLOPT_URL,httppath);
			if (CURLE_OK!=res)
		{
			 WriteLog("设置连接失败！");
			 return -1;
		}
		 memset(strsend,0,sizeof strsend);
		 destorydata(strsend);
		res=curl_easy_setopt(curl,CURLOPT_POSTFIELDS,strsend);
		 if (CURLE_OK!=res)
		{
		 WriteLog("准备数据失败！");
		  return -1;
		}

     res= curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
       if (CURLE_OK!=res)
		{
			 WriteLog("CURLOPT_SSL_VERIFYPEER！");
			 return -1;
		}
		 res =curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		 if (res!= CURLE_OK)
		{  
			 memset(logstr,0,sizeof logstr);
			 strcat(logstr,"WriteMemoryCallback！错误码：");
			 sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			 return -1;
		}
		 res =  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		  if (res!= CURLE_OK)
		{   
			 memset(logstr,0,sizeof logstr);
			 strcat(logstr,"CURLOPT_WRITEDATA！错误码：");
			 sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		    /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
		res =  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		if (res!= CURLE_OK)
		{  
			 memset(logstr,0,sizeof logstr);
			 strcat(logstr,"CURLOPT_USERAGENT！错误码：");
			 sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			 return -1;
		}
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR,"cookie.txt");  
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE,"cookie.txt");
		try
		{
		 res = curl_easy_perform(curl);
		}
	 catch (exception& e)
		 {
		    strcpy(logstr,e.what());
			WriteLog(logstr);
		  } 
		if (res!= CURLE_OK)
		{   
			 memset(logstr,0,sizeof logstr);
			 strcat(logstr,"发送数据失败！错误码：");
			 sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		if(chunk.memory)
		{
			nSize=strlen(chunk.memory);
			nNonRevrt = Utf8ToGb2312(chunk.memory,nSize,&to_str,&to_str_len);
			strcpy(restlt,to_str);
			ret=GetXmlData(restlt,ThirdPay,"ecard");
			//if (ret)
			//{
			// return -1 ;
			//}
		}
		 curl_easy_cleanup(curl);
		 if(chunk.memory)
			free(chunk.memory);
		 /* we're done with libcurl, so clean it up */

		 curl_global_cleanup();
		
	}
	return 0;	
}

int sendhttpsfix(kst_ald_pay &pay,Agd_ThirdPay &ThirdPay)
{
	  char strsend[1024]="";
	  char logstr[1024]="";
	  char temp[1024]="";
	  char restlt[1024]="";
	  char fullname[50]="";
	  size_t nSize=0;
	  int ret=0;
	  size_t nNonRevrt = 0;  //non-reversible characters
	  char* to_str = NULL;
      size_t to_str_len = 0;
	  struct MemoryStruct chunk={0};
      CURL *curl = 0;
	  CURLcode res;
	  curl_global_init(CURL_GLOBAL_ALL);
	  curl = curl_easy_init();
		if (curl)
		{
		res=curl_easy_setopt(curl,CURLOPT_URL,httppath);
		 if (CURLE_OK!=res)
		{
		 WriteLog("设置连接失败！");
		 return -1;
		}
		 memset(strsend,0,sizeof strsend); 
		res=curl_easy_setopt(curl,CURLOPT_POSTFIELDS,fixdata(pay,ThirdPay));
		 if (CURLE_OK!=res)
		{
		 WriteLog("准备数据失败！");
		  return -1;
		}
		 res= curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
       if (CURLE_OK!=res)
		{
		 WriteLog("CURLOPT_SSL_VERIFYPEER！");
		  return -1;
		}
		 res =curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		 if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"WriteMemoryCallback！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
		 return -1;
		}
		 res =  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		  if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_WRITEDATA！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		    /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
		res =  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"CURLOPT_USERAGENT！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR,"cookie.txt");  
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE,"cookie.txt");
		try
		{
		 res = curl_easy_perform(curl);
		}
		 catch (exception& e)
		  {
			   strcpy(logstr,e.what());
				WriteLog(logstr);
		  } 
		if (res!= CURLE_OK)
		{   memset(logstr,0,sizeof logstr);
			strcat(logstr,"发送数据失败！错误码：");
			sprintf_s(temp,"%d",res);
			 strcat(logstr,temp);
			 WriteLog(logstr);
			  return -1;
		}
			if(chunk.memory)
		{
		 nSize=strlen(chunk.memory);
		nNonRevrt = Utf8ToGb2312(chunk.memory,nSize,&to_str,&to_str_len);
         strcpy(restlt,to_str);
		 ret=GetXmlData(restlt,ThirdPay,"ecard");
		 if (ret)
		 {
			 return -1 ;
		  }
		}
		  curl_easy_cleanup(curl);
		    if(chunk.memory)
		  free(chunk.memory);

		 /* we're done with libcurl, so clean it up */
		 curl_global_cleanup();
	}
	 return 0;
}
 /* char Connectstr[1024]="Provider=OraOLEDB.Oracle.1;Persist Security Info=true;User ID=ykt_cur;Password=kingstar;\
		Data Source=(DESCRIPTION =(ADDRESS_LIST =(ADDRESS = (PROTOCOL = TCP)(HOST = 10.253.42.146)(PORT = 1522)))(CONNECT_DATA =\
		(SERVICE_NAME =ykt2007)))";
	*/
/*
int exec_ora_sql(char *sql)
{     
   
	  _RecordsetPtr pPtr;
	  int ret=0;
	  _variant_t  vsql;
	  _variant_t connstr;
	  WriteLog(Connectstr);
	  WriteLog(sql);
	  connstr.SetString(Connectstr);
	  vsql.SetString(sql);
	  ::CoInitialize(NULL);///初始化COM库
	  if (FAILED(pPtr.CreateInstance("ADODB.Recordset")))
		{
			return -1;
		}
	 try
		{
			if(FAILED(pPtr->Open(vsql,connstr,adOpenStatic,adLockOptimistic,adCmdText)))
			{
				WriteLog("Open table failed!");
				return  -1;
			}
		}
		catch(_com_error e)
		{
			return -1;
		}
      try
		{
			pPtr->Close();
		 }
		catch(_com_error e)
		{		

		}
	  return 0;
}
*/
int recodepaydata(Agd_ThirdPay &ThirdPay)
{
	char sql[1024]="";
	strcpy(ThirdPay.ecard_ip,localip);
	char filename[1024]="sqldata";
	strcat(sql,"insert into T_ThirdPay_JJLink(Ecard_Id,Request_Time,Ecard_Num,username,fullname,amount,ecard_machine_id, \
                ecard_ip,inpayamount_id,reply_time,ack_time,status,update_time) values(");
	strcat(sql,ThirdPay.ecard_id);//交易参考号
	strcat(sql,",'");
	strcat(sql,ThirdPay.request_time);//交易请求时间
	strcat(sql,"','");
	strcat(sql,ThirdPay.ecard_num);//一卡通学工号
	strcat(sql,"','");
	strcat(sql,ThirdPay.username);//充值帐号
	strcat(sql,"','");
	strcat(sql,ThirdPay.fullname);//姓名
	strcat(sql,"',");
	strcat(sql,ThirdPay.amount);//金额
	strcat(sql,",");
	strcat(sql,ThirdPay.ecard_machine_id);//设备号
    strcat(sql,",'");
	strcat(sql,ThirdPay.ecard_ip);//IP地址
	strcat(sql,"','");
	strcat(sql,ThirdPay.inpayamount_id);//第三方返回参考号
	strcat(sql,"','");
	strcat(sql,ThirdPay.reply_time);//交易请求返回时间
	strcat(sql,"','");
	strcat(sql,ThirdPay.ack_time);//请求确认时间 
	strcat(sql,"',decode('");
	strcat(sql,ThirdPay.status);//decode('成功1','成功',1,'失败',2,0)
	strcat(sql,"','成功',2,'失败',3,0),'");
	strcat(sql,ThirdPay.update_time);//
	strcat(sql,"');");
	//WriteLog(runpath);
	Writedata(filename,sql); 
//	exec_ora_sql(sql);
	//ShellExecute(NULL,(LPCSTR)("open"),(LPCSTR)(runpath),sql,NULL,SW_SHOW); 
return 0;
}
