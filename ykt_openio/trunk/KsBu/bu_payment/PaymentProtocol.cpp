#include "PaymentProtocol.h"
#include "md5.h"
#include "tcpsock.h"


//////////////////////////////////////////////////////////////////////////
// 
PaymentProtocol::PaymentProtocol()
{
	ptc_fields_.clear();
}
PaymentProtocol::~PaymentProtocol()
{
	ptc_fields_.clear();
}

size_t PaymentProtocol::find_next_pos(const std::string &data,size_t start_pos)
{
	for(;start_pos<data.length();++start_pos)
	{
		if(data.at(start_pos) == ':')
			return start_pos;
	}
	return std::string::npos;
}

int PaymentProtocol::parse_header(const std::string &data,int &head_len,int &data_len)
{
	int p,q,n;
	std::string fld_type,fld_value;
	int fld_len;
	if(data.at(0) != ':')
		return -1;
	ptc_fields_.clear();
	q = 1;
	p = find_next_pos(data,q);
	if(p == std::string::npos)
		return -1;

	fld_type = data.substr(q,p-q);
	if(fld_type.at(0)!='i')
		return -1;
	fld_len = atoi(fld_type.substr(1).c_str());
	if(data.length() < fld_type.length() + fld_len + 2)
		return -1;

	fld_value=data.substr(p+1,fld_len);
	data_len = atoi(fld_value.c_str());
	head_len = fld_len + fld_type.length()+2;
	/*if(data.length()-head_len < data_len)
		return -1;*/
	return 0;

}
int PaymentProtocol::parse(const std::string &data,int md5)
{
	int p,q,n;
	std::string fld_type,fld_value;
	int fld_len,head_len,data_len;
	q = 1;
	if(parse_header(data,head_len,data_len))
		return -1;
	ptc_fields_.clear();
	do 
	{
		p = find_next_pos(data,q);
		if(p == std::string::npos)
			break;
		
		fld_type = data.substr(q,p-q);
		if(fld_type.size()==0)
			return -1;
		/*switch(fld_type.at(0))
		{
		case 'i':
			if(fld_len==0)
				return -1;
			break;
		case 's':
			break;
		case 'd':
			if(fld_len==0)
				return -1;
			break;
		default:
			return -1;
		}*/
		fld_len = atoi(fld_type.substr(1).c_str());

		fld_value = data.substr(p+1,fld_len);
		ptc_fields_.push_back(fld_value);
		q = p + fld_len + 2;
	} while (1);
	if(ptc_fields_.size() <= 2)
		return -1;

	if(md5)
	{
		get_field(get_field_count()-1,fld_value);
		size_t len = data.length() - head_len - 32 - 5;
		if(check_buffer_md5(data.data()+head_len,len,fld_value.data()))
		{
			return -1;
		}
	}

	return 0;
}

int PaymentProtocol::check_buffer_md5(const char *buf,size_t len,const char *md5)
{
	unsigned char t[64];
	char m[4];
	int i,j;
	unsigned char md5str[20];
	MD5_CTX ctx;
	memset(&ctx,0,sizeof ctx);
	MD5Init(&ctx);
	MD5Update(&ctx,(unsigned char*)buf,len);
	MD5Final(md5str,&ctx);
	
	memset(m,0,sizeof m);
	for(i = 0;i < 16;++i)
	{
		memcpy(m,md5+i*2,2);
		t[i] = (unsigned char)strtoul(m,NULL,16);
	}
	if(memcmp(md5str,t,16)==0)
	{
		return 0;
	}
	return -1;
}

int PaymentProtocol::get_field(int idx,std::string &v)
{
	if(idx < 0 && idx >= ptc_fields_.size())
		return -1;
	v = ptc_fields_[idx];
	return 0;
}

int PaymentProtocol::get_int_field(int idx,int &v)
{
	std::string t;
	if(get_field(idx,t))
		return -1;
	v = atoi(t.c_str());
	return 0;
}

int PaymentProtocol::get_double_field(int idx,double &v)
{
	std::string t;
	if(get_field(idx,t))
		return -1;
	v = atof(t.c_str());
	return 0;
}

void PaymentProtocol::begin_filed()
{
	ptc_data_.clear();
}

void PaymentProtocol::add_field(const std::string &v)
{
	char t[256];
	sprintf(t,":s%d:%s",v.length(),v.data());
	ptc_data_ += t ;
}
void PaymentProtocol::add_int_field(int v)
{
	char t[256];
	char m[256];
	sprintf(t,"%d",v);
	sprintf(m,":i%d:%s",strlen(t),t);
	ptc_data_ += m;

}
void PaymentProtocol::add_double_field(double v)
{
	char t[256];
	char m[256];
	sprintf(t,"%f",v);
	sprintf(m,":i%d:%s",strlen(t),t);
	ptc_data_ += m;
}
int PaymentProtocol::final_add_field(std::string &data,int md5)
{
	char t[256];
	char m[256];
	int i,j;
	unsigned char md5str[20];
	MD5_CTX ctx;
	if(ptc_data_.length()<=0)
		return -1;
	if(md5)
	{
		memset(&ctx,0,sizeof ctx);
		MD5Init(&ctx);
		MD5Update(&ctx,(unsigned char*)(ptc_data_.data()),ptc_data_.length());
		MD5Final(md5str,&ctx);
		for(i = 0,j = 0;i < 16;++i)
		{
			j+= sprintf(t+j,"%02X",md5str[i]);
		}
		t[32] = '\0';
		add_field(t);
	}
	
	sprintf(t,"%d",ptc_data_.length());
	sprintf(m,":i%d:%s",strlen(t),t);
	data = m + ptc_data_;
	return 0;
}

int payment_process(payment_request_t * payment,int needret)
{
	int ret;
	unsigned char resp_data[2048];
	char msg[256];
	int head_len,data_len,recv_len;
	TCPSockStream sock;
	ret = sock.connect(payment->host,payment->port,payment->timeout);
	if(ret>0)
	{
		ANSWER_MSG(payment,PYM_CONN_TIMEOUT,"连接服务器超时");
		return -1;
	}
	else if(ret == -1)
	{
		ANSWER_MSG(payment,PYM_CONN_TIMEOUT,"无法连接服务器");
		return -1;
	}
	ret = sock.send_n((unsigned char*)payment->req.c_str(),payment->req.length(),payment->timeout);
	if(ret>0)
	{
		ANSWER_MSG(payment,PYM_TIMEOUT,"无法连接服务器");
		return -1;
	}
	else if(ret==-1)
	{
		ANSWER_MSG(payment,PYM_TIMEOUT,"发送第三方请求失败");
		return -1;
	}
	// 不需要等待
	if(!needret)
	{
		return 0;
	}
	recv_len = sock.recv_n((unsigned char*)resp_data,10,payment->timeout);
	if(recv_len==-2)
	{
		ANSWER_MSG(payment,PYM_TIMEOUT,"接收应答超时");
		payment->retcode=PYM_RET_ERR;
		return -1;
	}
	else if(recv_len==-1)
	{
		sprintf(msg,"接收第三方应答失败 : %d,recv_len[%d]",sock.get_last_error(),recv_len);
		ANSWER_MSG(payment,PYM_TIMEOUT,msg);
		payment->retcode=PYM_RET_ERR;
		return -1;
	}
	payment->resp=std::string((const char *)resp_data,recv_len);
	if(payment->protocol->parse_header(payment->resp,head_len,data_len))
	{
		ANSWER_MSG(payment,PYM_TIMEOUT,"发送第三方请求失败");
			payment->retcode=PYM_RET_ERR;
		return -1;
	}

	ret = sock.recv_n((unsigned char*)resp_data+recv_len,data_len+head_len-recv_len,payment->timeout);
	if(ret==-2)
	{
		ANSWER_MSG(payment,PYM_TIMEOUT,"接收应答超时");
			payment->retcode=PYM_RET_ERR;
		return -1;
	}
	else if(ret==-1)
	{
		sprintf(msg,"接收第三方应答失败 : %d,ret[%d]",sock.get_last_error(),ret);
		ANSWER_MSG(payment,PYM_TIMEOUT,msg);
		payment->retcode=PYM_RET_ERR;
		return -1;
	}
	payment->resp=std::string((const char *)resp_data,ret+recv_len);
	return 0;
}

