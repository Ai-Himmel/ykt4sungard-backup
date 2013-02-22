#ifndef _CUR_HTTP_REQUEST_H_
#define _CUR_HTTP_REQUEST_H_

#include "DataType.h"

struct HttpInfo 
{
	char cmd[10];
	char user[20];
	char pwd[16];
	char conid[10];
	char card_id[11];
	char con_name[1024];
	char http_url[1024]; 
};

struct MemoryStruct 
{
	char *memory;
	size_t size;
};

/*
int curl_easy_http_request(MemoryStruct *chunk, char *post_data, char *http_url, char *user = "");
int curl_easy_http_request_ext(MemoryStruct *chunk, HttpInfo *http_info);
size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);
void *myreadlloc(void *ptr, size_t size);
*/

class CCurlHttp
{
public:
	CCurlHttp();
	~CCurlHttp(void);	
	int curl_easy_http_request(MemoryStruct *chunk, char *post_data, char *http_url, char *user = "");
	int curl_easy_http_request_ext(MemoryStruct *chunk, HttpInfo *http_info);
	static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);
	static void *myreadlloc(void *ptr, size_t size);

public:

private:
};

#endif