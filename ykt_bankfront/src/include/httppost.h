#include <string>
#include <curl/curl.h>

#ifndef HTTPPOST_H
#define HTTPPOST_H
struct WriteThis {
  const char *readptr;
  int sizeleft;
};

class CHttpPost {
public:
	CHttpPost();
	~CHttpPost();

	//bool downloadFile(const std::string url);
    void headAppend(std::string str);
    bool headSetopt();
    bool reset();
    bool setDebug();
    bool init();
    bool setTimeout(int time_out);
    string& getCurlErrMsg();
    bool httpSetProxyHostPort(char* proxyHostPort);
    bool httpSetProxyUserPwd(char* proxyUserPwd);
    bool httpPostData(const std::string url,const std::string postdata);
	std::string contentType() const;
	unsigned int contentLength() const;
	char* content() const;
    std::string& getContent();
    std::string& getErrMsg();
    curl_slist* headerlist;
private:

    static size_t httpWrite(void* ptr, size_t size, size_t nmemb, void* stream);
    static size_t httpRead(void *ptr, size_t size, size_t nmemb, void *userp);
    static void dump(const char *text,FILE *stream, unsigned char *ptr, size_t size,bool nohex);
    static int my_trace(CURL *handle, curl_infotype type,unsigned char *data, size_t size,void *userp);
	
    CURL* curlHandle;
	//char* data;
    std::string errMsg;
    std::string  repData;
//	unsigned int length;
	//unsigned int allocatedLength;
    std::string type;
    int timeout;
    struct WriteThis pooh;
    CURLcode curlErr;
    string   curlErrMsg;
    bool bDebug;
};

#endif /* HTTPPOST_H */
