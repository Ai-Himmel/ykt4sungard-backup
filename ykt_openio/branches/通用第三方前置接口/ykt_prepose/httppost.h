#include <string>
#include <curl.h>
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
    bool init();
    bool setTimeout(int time_out);
    string& getCurlErrMsg();
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
};
#ifndef   BU_ALD_H_H 
#define   BU_ALD_H_H
#endif

