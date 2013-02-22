#include "StdAfx.h"
#include "curl_http_request.h"
#include "curl.h"
#include "mprintf.h"

CCurlHttp::CCurlHttp()
{

}

CCurlHttp::~CCurlHttp()
{

}

//
int CCurlHttp::curl_easy_http_request(MemoryStruct *chunk, char *post_data, char *http_url, char *user)
{
	CURL *curl;
    CURLcode res;

	struct MemoryStruct temp_chunk;
	temp_chunk.memory = NULL;
	temp_chunk.size = 0;

	int nStrPos = 0;
	char cardno[50] = "";

	nStrPos = sprintf(cardno, "cardno=%s", post_data);
	nStrPos += sprintf(cardno + nStrPos, "%s", "&");
	sprintf(cardno + nStrPos, "username=%s", user);
	curl = curl_easy_init();
	
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, http_url);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cardno);
//		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, user);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&temp_chunk);
		res = curl_easy_perform(curl);
	
		if (res == CURLE_OK)
		{
			chunk->memory = temp_chunk.memory;
			chunk->size = temp_chunk.size;
		}
		
		curl_easy_cleanup(curl);
		if (res != CURLE_OK && temp_chunk.memory == NULL)
		{	
			return res;
		}
	}
	return 0;	
}

//
int CCurlHttp::curl_easy_http_request_ext(MemoryStruct *chunk, HttpInfo *http_info)
{
	CURL *curl;
	CURLcode res;

	struct MemoryStruct temp_chunk;
	temp_chunk.memory = NULL;
	temp_chunk.size = 0;

	char data_info[1024] = "";
//	PACKETSTR(data_info, SPLIT_VL1, "");		// +++++?
	PACKETSTREXT(data_info, "cmd=", http_info->cmd, SPLIT_VL3);
	PACKETSTREXT(data_info, "username=", http_info->user, SPLIT_VL3);
	PACKETSTREXT(data_info, "password=", http_info->pwd, SPLIT_VL3);
	PACKETSTREXT(data_info, "conid=", http_info->conid, SPLIT_VL3);
	PACKETSTREXT(data_info, "cardno=", http_info->card_id, "");

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, http_info->http_url);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_info);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&temp_chunk);
		res = curl_easy_perform(curl);

		if (res == CURLE_OK)
		{
			chunk->memory = temp_chunk.memory;
			chunk->size = temp_chunk.size;
		}

		curl_easy_cleanup(curl);
		if (res != CURLE_OK && temp_chunk.memory == NULL)
		{	
			return res;
		}
	}

	return 0;	
}

//
void *CCurlHttp::myreadlloc(void *ptr, size_t size)
{
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

//
size_t CCurlHttp::WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;
	mem->memory = (char*)myreadlloc(mem->memory, mem->size + realsize + 10);
	if (mem->memory)
	{
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}