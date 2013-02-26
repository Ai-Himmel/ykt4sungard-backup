#include "stdafx.h"
#include <iostream>
#include <cassert>
#include "mystring.h"
#include "httppost.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
using namespace std;
/* arrays for certificate chain and errors */
#define MAX_CERTS 20
X509 *certificate[MAX_CERTS];
long certificate_error[MAX_CERTS]; 
int verify_callback(int preverify_ok, X509_STORE_CTX *x509_ctx)
{
  X509 *cert = X509_STORE_CTX_get_current_cert(x509_ctx);
  int depth = X509_STORE_CTX_get_error_depth(x509_ctx);
  int err = X509_STORE_CTX_get_error(x509_ctx);

  /* save the certificate by incrementing the reference count and
   * keeping a pointer */
  if (depth < MAX_CERTS && !certificate[depth]) {
    certificate[depth] = cert;
    certificate_error[depth] = err;
    cert->references++;
  }

  return 1;
}
CURLcode sslctxfun(CURL *curl, SSL_CTX *sslctx, void *parm)
{
  SSL_CTX_set_verify(sslctx, SSL_VERIFY_PEER, verify_callback);

  return CURLE_OK;
}

CHttpPost::CHttpPost():
curlHandle(curl_easy_init()),headerlist(NULL),timeout(15)
{
    curlErr=CURLE_OK;
}

CHttpPost::~CHttpPost() {
	curl_easy_cleanup(curlHandle);
    if(headerlist)
         curl_slist_free_all(headerlist);
}
bool CHttpPost::init()
{
/*	curlErr = curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, httpWrite);
	if (curlErr != CURLE_OK) {
		cerr << "got curl error on setopt writefunction " << curlErr << endl;
		return false;
	}*/
/*	curlErr = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, this);
	if (curlErr != CURLE_OK) {
		cerr << "got curl error on setopt writedata " << curlErr << endl;
		return false;
	}*/
    /* Now specify we want to POST data */
/*   
	curlErr = curl_easy_setopt(curlHandle, CURLOPT_POST, 1);
	if (curlErr != CURLE_OK) {
		cerr << "got curl error on setopt post " << curlErr << endl;
		return false;
	}
	*/
    /* we want to use our own read function */
   curlErr = curl_easy_setopt(curlHandle, CURLOPT_READFUNCTION, httpRead);
	if (curlErr != CURLE_OK) {
		cerr << "got curl error on setopt readfunction " << curlErr << endl;
		return false;
	}

    /* pointer to pass to our read function */
    curlErr = curl_easy_setopt(curlHandle, CURLOPT_READDATA, &pooh);
	if (curlErr != CURLE_OK) {
		cerr << "got curl error on setopt readdata " << curlErr << endl;
		return false;
	}
    curlErr = curl_easy_setopt(curlHandle, CURLOPT_TIMEOUT,timeout);
	if (curlErr != CURLE_OK) {
		cerr << "got curl error on setopt timeout " << curlErr << endl;
		return false;
	}
    /* get verbose debug output please */
   //curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    return true;
}
bool CHttpPost::headSetopt()
{
    if(!headerlist)
        return false;
    CURLcode curlErr = curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headerlist);
	if (curlErr != CURLE_OK) {
		errMsg="got curl error on getinfo,errcode:"+ltos((int)curlErr);			
		//cerr <<errMsg<<endl;
		return false;
	}
    return true;
}
void CHttpPost::headAppend(std::string str)
{
    headerlist = curl_slist_append(headerlist,str.c_str());
}
bool CHttpPost::reset()
{
     curl_easy_cleanup(curlHandle);
     curlHandle=NULL;
     curl_slist_free_all(headerlist);
     headerlist=NULL;
     curlHandle=curl_easy_init();
     return init();
}
bool CHttpPost::setTimeout(int time_out)
{
    timeout=time_out;
    curlErr = curl_easy_setopt(curlHandle, CURLOPT_TIMEOUT,timeout);
	if (curlErr != CURLE_OK) {
		//cerr << "got curl error on setopt timeout " << curlErr << endl;
		return false;
	}
    return true;
}
bool CHttpPost::httpPostData(const std::string url,const std::string postdata) {
	char error_buffer[CURL_ERROR_SIZE] = "";
    //length = 0;
    repData.resize(0);
    
    pooh.readptr=postdata.c_str();
    pooh.sizeleft=postdata.size();
	//  set up transfer
/*     curlErr =curl_easy_setopt(curlHandle, CURLOPT_ERRORBUFFER, error_buffer);
	 if (curlErr != CURLE_OK) {
		errMsg="got curl error on setopt CURLOPT_ERRORBUFFER ,errcode:"+ltos((int)curlErr); 
		//cerr<<errMsg<< endl;
		return false;
	}
	*/
	curlErr = curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
	if (curlErr != CURLE_OK) {
		errMsg="got curl error on setopt url ,errcode:"+ltos((int)curlErr); 
		//cerr<<errMsg<< endl;
		return false;
	}
	   curlErr =curl_easy_setopt(curlHandle, CURLOPT_WRITEHEADER, stdout);
		 if (curlErr != CURLE_OK) {
		errMsg="got curl error on setopt CURLOPT_WRITEHEADER ,errcode:"+ltos((int)curlErr); 
		//cerr<<errMsg<< endl;
		return false;
	}
	
	  /* fetch the page even if verifying the certificates fails */
  curlErr = curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYPEER, 0L);
   if (curlErr != CURLE_OK) {
		errMsg="got curl error on setopt CURLOPT_SSL_VERIFYPEER ,errcode:"+ltos((int)curlErr); 
		//cerr<<errMsg<< endl;
		return false;
	}
  /*  curlErr =curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYHOST, 0L);
	if (curlErr != CURLE_OK) {
		errMsg="got curl error on setopt CURLOPT_SSL_VERIFYHOST ,errcode:"+ltos((int)curlErr); 
		//cerr<<errMsg<< endl;
		return false;
	}
	curlErr =curl_easy_setopt(curlHandle, CURLOPT_SSL_CTX_FUNCTION, sslctxfun);
	if (curlErr != CURLE_OK) {
		errMsg="got curl error on setopt CURLOPT_SSL_CTX_FUNCTION ,errcode:"+ltos((int)curlErr); 
		//cerr<<errMsg<< endl;
		return false;
	}
	*/
    /* Set the expected POST size. If you want to POST large amounts of data,
       consider CURLOPT_POSTFIELDSIZE_LARGE */
    curlErr = curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDSIZE, pooh.sizeleft);
	if (curlErr != CURLE_OK)
	{
		errMsg="got curl error on setopt postfieldsize,errcode:"+ltos((int)curlErr);
		//cerr<<errMsg<< endl;
		return false;
	}

	//  perform transfer
	curlErr = curl_easy_perform(curlHandle);
	if (curlErr != CURLE_OK) {
		errMsg="got curl error on perform to "+url+",errcode:"+ltos((int)curlErr);		
		//cerr<<errMsg<< endl;
		return false;
	}

	char* contentType = NULL;
	curlErr = curl_easy_getinfo(curlHandle, CURLINFO_CONTENT_TYPE, &contentType);
	if (curlErr != CURLE_OK) {
		errMsg="got curl error on getinfo,errcode:"+ltos((int)curlErr);		
		//cerr<<errMsg<< endl;
		return false;
	}
    if(contentType)
	    type = string(contentType);
    else 
        type="";
	return true;
}

std::string CHttpPost::contentType() const {
	return type;
}

unsigned int CHttpPost::contentLength() const {
	//return length;
    return repData.length();
}

char* CHttpPost::content() const {
	return (char*)repData.c_str();
}
std::string& CHttpPost::getContent() {
	return repData;
}
std::string& CHttpPost::getErrMsg() 
{
	return errMsg;
}
size_t CHttpPost::httpRead(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *pooh = (struct WriteThis *)userp;

  if(size*nmemb < 1)
    return 0;

  if(pooh->sizeleft) {
    *(char *)ptr = pooh->readptr[0]; /* copy one single byte */
    pooh->readptr++;                 /* advance pointer */
    pooh->sizeleft--;                /* less data left */
    return 1;                        /* we return 1 byte at a time! */
  }

  return -1;                         /* no more data left to deliver */
}
//size_t CHttpPost::httpWrite(void* ptr, size_t size, size_t nmemb, void* stream) {
//	CHttpPost* handle = (CHttpPost*)stream;
//	size_t newDataSize = size*nmemb;
//
//	if (handle->data == NULL) {
//		assert(handle->allocatedLength == 0);
//		handle->data = (char*)malloc(kInitialBufferSize);
//		handle->allocatedLength = kInitialBufferSize;
//		handle->length = 0;
//	}
//
//	while (handle->length+newDataSize+1 > handle->allocatedLength) {
//		assert(handle->allocatedLength > 0);
//		handle->data = (char*)realloc(handle->data, handle->allocatedLength*2);
//		handle->allocatedLength *= 2;
//	}
//
//	memcpy(handle->data + handle->length, ptr, newDataSize);
//	handle->length += newDataSize;
//	return newDataSize;
//}
size_t CHttpPost::httpWrite(void* ptr, size_t size, size_t nmemb, void* stream) {
	CHttpPost* handle = (CHttpPost*)stream;
	size_t newDataSize = size*nmemb;
    std::string str((char*)ptr,newDataSize);
    handle->repData+=str;
//	handle->length += newDataSize;
	return newDataSize;
}
string& CHttpPost::getCurlErrMsg()
{
#if 0
  CURLE_OK = 0,
  CURLE_UNSUPPORTED_PROTOCOL,    /* 1 */
  CURLE_FAILED_INIT,             /* 2 */
  CURLE_URL_MALFORMAT,           /* 3 */
  CURLE_OBSOLETE4,               /* 4 - NOT USED */
  CURLE_COULDNT_RESOLVE_PROXY,   /* 5 */
  CURLE_COULDNT_RESOLVE_HOST,    /* 6 */
  CURLE_COULDNT_CONNECT,         /* 7 */
  CURLE_FTP_WEIRD_SERVER_REPLY,  /* 8 */
  CURLE_REMOTE_ACCESS_DENIED,    /* 9 a service was denied by the server
                                    due to lack of access - when login fails
                                    this is not returned. */
  CURLE_OBSOLETE10,              /* 10 - NOT USED */
  CURLE_FTP_WEIRD_PASS_REPLY,    /* 11 */
  CURLE_OBSOLETE12,              /* 12 - NOT USED */
  CURLE_FTP_WEIRD_PASV_REPLY,    /* 13 */
  CURLE_FTP_WEIRD_227_FORMAT,    /* 14 */
  CURLE_FTP_CANT_GET_HOST,       /* 15 */
  CURLE_OBSOLETE16,              /* 16 - NOT USED */
  CURLE_FTP_COULDNT_SET_TYPE,    /* 17 */
  CURLE_PARTIAL_FILE,            /* 18 */
  CURLE_FTP_COULDNT_RETR_FILE,   /* 19 */
  CURLE_OBSOLETE20,              /* 20 - NOT USED */
  CURLE_QUOTE_ERROR,             /* 21 - quote command failure */
  CURLE_HTTP_RETURNED_ERROR,     /* 22 */
  CURLE_WRITE_ERROR,             /* 23 */
  CURLE_OBSOLETE24,              /* 24 - NOT USED */
  CURLE_UPLOAD_FAILED,           /* 25 - failed upload "command" */
  CURLE_READ_ERROR,              /* 26 - could open/read from file */
  CURLE_OUT_OF_MEMORY,           /* 27 */
  /* Note: CURLE_OUT_OF_MEMORY may sometimes indicate a conversion error
           instead of a memory allocation error if CURL_DOES_CONVERSIONS
           is defined
  */
  CURLE_OPERATION_TIMEDOUT,      /* 28 - the timeout time was reached */
  CURLE_OBSOLETE29,              /* 29 - NOT USED */
  CURLE_FTP_PORT_FAILED,         /* 30 - FTP PORT operation failed */
  CURLE_FTP_COULDNT_USE_REST,    /* 31 - the REST command failed */
  CURLE_OBSOLETE32,              /* 32 - NOT USED */
  CURLE_RANGE_ERROR,             /* 33 - RANGE "command" didn't work */
  CURLE_HTTP_POST_ERROR,         /* 34 */
  CURLE_SSL_CONNECT_ERROR,       /* 35 - wrong when connecting with SSL */
  CURLE_BAD_DOWNLOAD_RESUME,     /* 36 - couldn't resume download */
  CURLE_FILE_COULDNT_READ_FILE,  /* 37 */
  CURLE_LDAP_CANNOT_BIND,        /* 38 */
  CURLE_LDAP_SEARCH_FAILED,      /* 39 */
  CURLE_OBSOLETE40,              /* 40 - NOT USED */
  CURLE_FUNCTION_NOT_FOUND,      /* 41 */
  CURLE_ABORTED_BY_CALLBACK,     /* 42 */
  CURLE_BAD_FUNCTION_ARGUMENT,   /* 43 */
  CURLE_OBSOLETE44,              /* 44 - NOT USED */
#endif
    switch(curlErr)
    {
    case CURLE_OK:
        curlErrMsg="";
        break;
    case CURLE_UNSUPPORTED_PROTOCOL:
        curlErrMsg="通讯错误-通讯协议不支持";
        break;
    case CURLE_FAILED_INIT:
        curlErrMsg="通讯错误-通讯初始化错误";
        break;
    case CURLE_URL_MALFORMAT:
        curlErrMsg="通讯错误-网络地址格式错误";
        break;
    case CURLE_COULDNT_RESOLVE_PROXY:
        curlErrMsg="通讯错误-不能解析代理";
        break;
    case CURLE_COULDNT_RESOLVE_HOST:
        curlErrMsg="通讯错误-不能解析主机";
        break;
    case CURLE_COULDNT_CONNECT:
        curlErrMsg="通讯错误-连接目标主机失败";
        break;
    case CURLE_FTP_WEIRD_SERVER_REPLY:
        curlErrMsg="FTP_WEIRD_SERVER_REPLY";
        break;
    //case CURLE_REMOTE_ACCESS_DENIED:
    //    curlErrMsg="通讯错误-远程主机拒绝访问";
    //    break;
    case CURLE_FTP_WEIRD_PASS_REPLY:
         curlErrMsg="FTP_WEIRD_PASS_REPLY";
         break;
    case CURLE_FTP_WEIRD_PASV_REPLY:    /* 13 */
         curlErrMsg="FTP_WEIRD_PASV_REPLY";
         break;
    case CURLE_FTP_WEIRD_227_FORMAT:    /* 14 */
         curlErrMsg="FTP_WEIRD_227_FORMAT";
         break;
    case CURLE_FTP_CANT_GET_HOST:       /* 15 */
         curlErrMsg="FTP_CANT_GET_HOST";
         break;
    //case CURLE_FTP_COULDNT_SET_TYPE:    /* 17 */
    //     curlErrMsg="FTP_COULDNT_SET_TYPE";
    //     break;
    case CURLE_PARTIAL_FILE:            /* 18 */
         curlErrMsg="PARTIAL_FILE";
         break;
    case CURLE_FTP_COULDNT_RETR_FILE:   /* 19 */
         curlErrMsg="FTP_COULDNT_RETR_FILE";
         break;
    //case CURLE_QUOTE_ERROR:             /* 21 - quote command failure */
    //     curlErrMsg="QUOTE_ERROR";
    //     break;
    case CURLE_HTTP_RETURNED_ERROR:     /* 22 */
        curlErrMsg="通讯错误-http返回失败";
        break;
    case CURLE_WRITE_ERROR:             /* 23 */
        curlErrMsg="WRITE_ERROR";
        break;
    //case CURLE_UPLOAD_FAILED:           /* 25 - failed upload "command" */
    //    curlErrMsg="通讯错误-上传失败";
    //    break;
    case CURLE_READ_ERROR:              /* 26 - could open/read from file */
        curlErrMsg="通讯错误-read error";
        break;
    case CURLE_OUT_OF_MEMORY:
        curlErrMsg="通讯错误-内存错误";
        break;
    case CURLE_OPERATION_TIMEDOUT:      /* 28 - the timeout time was reached */
        curlErrMsg="通讯超时";
        break;
    case CURLE_FTP_PORT_FAILED:         /* 30 - FTP PORT operation failed */
        curlErrMsg="FTP_PORT_FAILED";
        break;
    case CURLE_FTP_COULDNT_USE_REST:    /* 31 - the REST command failed */
        curlErrMsg="FTP_COULDNT_USE_REST";
        break;
    case CURLE_HTTP_POST_ERROR:         /* 34 */
        curlErrMsg="通讯错误-http post error";
        break;
    case CURLE_SSL_CONNECT_ERROR:       /* 35 - wrong when connecting with SSL */
        curlErrMsg="通讯错误-ssl connect error";
        break;
    case CURLE_BAD_DOWNLOAD_RESUME:     /* 36 - couldn't resume download */
        curlErrMsg="通讯错误-ssl connect error";
        break;
    case CURLE_FILE_COULDNT_READ_FILE:  /* 37 */
        curlErrMsg="通讯错误-ssl connect error";
        break;
    case CURLE_LDAP_CANNOT_BIND:        /* 38 */
        errMsg="通讯错误-ldap cannot bind";
        break;
    case CURLE_LDAP_SEARCH_FAILED:      /* 39 */
         curlErrMsg="通讯错误-ldap search failed";
         break;
    case CURLE_FUNCTION_NOT_FOUND:      /* 41 */
         curlErrMsg="通讯错误-function not found";
         break;
    case CURLE_ABORTED_BY_CALLBACK:     /* 42 */
         errMsg="通讯错误-function not found";
         break;
    case CURLE_BAD_FUNCTION_ARGUMENT:   /* 43 */
         curlErrMsg="通讯错误-bad function argument";
         break;
    default:
         curlErrMsg="通讯错误";
    }
    return curlErrMsg;
}
