#ifndef _PAYMENTPROTOCOL_H_
#define _PAYMENTPROTOCOL_H_

#include <vector>
#include <string>
#include <sys/types.h>


#define PYM_SUCCESS 0		// 成功
#define PYM_TIMEOUT 1000 // 请求超时
#define PYM_RET_ERR 1001    // 请求错误
#define PYM_INPUT_DATA 1002	// 请求数据错误
#define PYM_CONN_TIMEOUT 1003  // 连接超时


class PaymentProtocol 
{
public:
	PaymentProtocol();
	virtual ~PaymentProtocol();
	typedef std::vector<std::string> PROTOCOL_FIELDS;

	virtual int parse(const std::string &data,int md5);
	int parse_header(const std::string &data,int &head_len,int &data_len);
	int get_field(int idx,std::string &v);
	int get_int_field(int idx,int &v);
	int get_double_field(int idx,double &v);


	void begin_filed();
	void add_field(const std::string &v);
	void add_int_field(int v);
	void add_double_field(double v);
	int final_add_field(std::string &data,int md5);

	inline size_t get_field_count() const 
	{
		return ptc_fields_.size();
	}
private:
	PROTOCOL_FIELDS ptc_fields_;
	std::string ptc_data_;
	size_t find_next_pos(const std::string &data,size_t start_pos);
	int check_buffer_md5(const char *buf,size_t len,const char *md5);
};

#define GET_STR_FIELD(p,i,f) \
	do{ std::string _v; if(p.get_field(i,_v)==0) { strncpy(f,_v.c_str(),sizeof(f)-1); } }while(0)


#define ANSWER_MSG(o,r,m) do { \
	o->retcode = r; o->retmsg = m;}while(0);


typedef struct {
	const char *host;
	int port;
	long timeout;
	std::string req;
	std::string resp;
	int retcode;
	std::string retmsg;
	PaymentProtocol * protocol;
}payment_request_t;

int payment_process(payment_request_t * payment,int needret);

#endif // _PAYMENTPROTOCOL_H_

