#include "std.h"
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <sstream>
#include <iomanip>
#include "daemonsvr.h"
#include "svrrequest.h"

///////////////////////////////////////////////////////////////////////////////
KsCardMsgRecv::KsCardMsgRecv()
{
	Reset();
}
KsCardMsgRecv::~KsCardMsgRecv()
{
}
int KsCardMsgRecv::SetClient(void *client)
{
	sock_ = reinterpret_cast<wxSocketClient*>(client);
	if(NULL == sock_)
		return -1;
	return 0;
}
void KsCardMsgRecv::Reset()
{
	memset(msgbuf_,0,sizeof msgbuf_);
	msg_recvlen_ = 0;
	msg_length_ = 0;
}
int KsCardMsgRecv::RecvData(KsCardMsg &msg)
{
	size_t recvlen=0;
	int msglen;
	if(NULL == sock_)
		return -3;

	
	if(KsCardMsgRecv::max_msgbuf_len <= msg_recvlen_)
	{
		wxLogError(wxT("消息长度太长,关闭客户端连接"));
		return -2;
	}
	msglen = max_msgbuf_len - msg_recvlen_;
	sock_->Read(msgbuf_ + msg_recvlen_,msglen);
	recvlen = sock_->LastCount();
	if(recvlen == 0)
	{
		// may be socket closed
		wxLogMessage(wxT("关闭客户端连接"));
		return -2;
	}

	msg_recvlen_ += recvlen;
	if(msg_recvlen_ >= KsCardMsgRecv::msg_header_len)
	{
		wxString temp(msgbuf_,KsCardMsgRecv::msg_header_len);
		long l = 0;
		temp.ToLong(&l);
		msg_length_ = l;
	}
	else
	{
		// 包头没有，返回错误
		wxLogError(wxT("数据包包头错误"));
		return -1;
	}
	if(msg_length_ <= KsCardMsgRecv::msg_header_len 
		|| msg_length_ >= KsCardMsgRecv::msg_header_len + KsCardMsgRecv::max_msgbuf_len)
	{
		wxLogError(wxT("数据包长度合法"));
		return -1;
	}
	if(msg_recvlen_ >= msg_length_+KsCardMsgRecv::msg_header_len)
	{
		msgbuf_[msg_recvlen_] = 0; // NULL terminated
		if(!msg.ParseMsg(msgbuf_+KsCardMsgRecv::msg_header_len))
		{
			Reset();
			wxLogError(wxT("数据包格式解析错误"));
			return -1;
		}
		Reset();
		return 0;
	}
	else
	{
		// 继续接收
		return 1;
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
KsCardMsg::KsCardMsg():msgtype_(""),parseLevel_(0)
{
	msg_field_.clear();
}
KsCardMsg::~KsCardMsg()
{
}
void KsCardMsg::Reset()
{
	msg_field_.clear();
	msgtype_.clear();
}
bool KsCardMsg::ParseMsg(const std::string &msg)
{
	Json::Value root;
	Json::Reader reader;
	msgtype_="";

	msg_field_.clear();

	if(!reader.parse(msg,root))
	{
		wxLogError(wxT("数据格式错误"));
		return false;
	}
	std::string value;
	value = root.get("msgtype","None").asString();
	msgtype_ = value;
	if(msgtype_.length() == 0)
	{
		wxLogError(wxT("数据格式错误,没有消息类型"));
		return false;
	}
	parseLevel_ = 0;
	bool rc = parseJsonData("",root);
	if(!rc)
		msg_field_.clear();
	return rc;
}
bool KsCardMsg::parseJsonData(const std::string& rootname,Json::Value &root)
{
	size_t i;
	Json::Value::Members mbs = root.getMemberNames();
	++parseLevel_;
	if(parseLevel_>2)
		return false;
	for(i = 0;i < mbs.size(); ++i)
	{
		Json::Value& clt = root[mbs[i]];
		std::string fullname = rootname;
		if(rootname.length() > 0)
			 fullname += ".";
		fullname += mbs[i];
		if(clt.isArray() || clt.isObject())
		{
			if(!parseJsonData(fullname,clt))
				return false;
		}
		else
		{
			msg_field_.insert(PARA_MAP_TYPE::value_type(fullname,root.get(mbs[i],"").asString()));
		}
	}
	return true;
}
#if 0
std::string KsCardMsg::ToMsg()
{
	size_t i;
	// 先排序
	PARA_MAP_TYPE::const_iterator citer;
	std::vector<std::string> keynames;
	for(citer = msg_field_.begin(); citer != msg_field_.end(); ++citer)
	{
		keynames.push_back(citer->first);
	}
	std::sort(keynames.begin(),keynames.end());
	// 生成
	std::stringstream content;
	int level = 0;
	int current_level = 0;
	size_t j=0 ,k = 0;
	for(i = 0;i < keynames.size(); ++i)
	{
		const std::string nkey = keynames[i];
		std::string fldname,arrname,fldstr;
		citer = msg_field_.find(nkey);
		assert(citer != msg_field_.end());

		j = k = 0;
		fldstr = nkey;
		arrname = "";
		current_level = 0;
		do
		{
			j = fldstr.find('.');
			++current_level;
			if(j == std::string::npos)
			{
				fldname=fldstr;
				break;
			}
			else
			{
				arrname = fldstr.substr(0,j);
				fldstr = fldstr.substr(j+1);
			}
		}while(nkey.length()>0);
		if(fldname.empty())
		{
			// no field name ,ignore
			continue;
		}

		if(level != current_level)
		{
			if(level > 0)
			{
				content<<"},";
			}
			else
			{
				content<<"{";
			}
			if(current_level>1)
			{
				if(arrname.length()>0)
					content<<"\""<<arrname<<"\":{";
				else
					content<<"{";
			}
		}
		if(level == current_level)
		{
			content<<",";
		}
		content<<"\""<<fldname<<"\":\""<<citer->second<<"\"";
		level = current_level;
	}
	while(--level>=0)
	{
		content<<"}";
	}
	return content.str();
}
#else
std::string KsCardMsg::ToMsg()
{
	size_t i;
	// 先排序
	PARA_MAP_TYPE::const_iterator citer;
	std::vector<std::string> keynames;
	for(citer = msg_field_.begin(); citer != msg_field_.end(); ++citer)
	{
		keynames.push_back(citer->first);
	}
	std::sort(keynames.begin(),keynames.end());
	// 生成
	Json::Value root;
	Json::Value* current;
	int current_level = 0;
	size_t j=0 ,k = 0;
	for(i = 0;i < keynames.size(); ++i)
	{
		const std::string nkey = keynames[i];
		std::string fldname,arrname,fldstr;
		citer = msg_field_.find(nkey);
		assert(citer != msg_field_.end());

		j = k = 0;
		fldstr = nkey;
		arrname = "";
		current_level = 0;
		do
		{
			j = fldstr.find('.');
			++current_level;
			if(j == std::string::npos)
			{
				fldname=fldstr;
				break;
			}
			else
			{
				arrname = fldstr.substr(0,j);
				fldstr = fldstr.substr(j+1);
			}
		}while(nkey.length()>0);
		if(fldname.empty())
		{
			// no field name ,ignore
			continue;
		}

		if(current_level == 1)
		{
			current = &(root[fldname]);
		}
		else
		{
			assert(!arrname.empty());
			assert(current_level<=2);
			current = &(root[arrname][fldname]);
		}
		*current = Json::Value(citer->second);
	}
	return root.toStyledString();
}
#endif
std::string KsCardMsg::MsgType() const
{
	return msgtype_;
}
void KsCardMsg::SetMsgType(const std::string &msgtype)
{
	msgtype_ = msgtype;
	SetStrPara("msgtype",msgtype_);
}
bool KsCardMsg::GetStrPara(const std::string &para_name,std::string &para_value) const
{
	PARA_MAP_TYPE::const_iterator iter;
	iter = msg_field_.find(para_name);
	if(iter == msg_field_.end())
	{
		return false;
	}
	para_value = iter->second;
	return true;
}
bool KsCardMsg::GetIntPara(const std::string &para_name,int *para_value) const
{
	std::string v;
	bool rc;
	rc = GetStrPara(para_name,v);
	if(!rc)
	{
		return rc;
	}
	*para_value = atoi(v.c_str());
	return true;
}
bool KsCardMsg::SetStrPara(const std::string &para_name,const std::string &para_value)
{
	PARA_MAP_TYPE::iterator iter;
	iter = msg_field_.find(para_name);
	if(iter != msg_field_.end())
	{
		return false;
	}
	msg_field_.insert(PARA_MAP_TYPE::value_type(para_name,para_value));
	return true;
}
bool KsCardMsg::SetIntPara(const std::string &para_name,int para_value)
{
	char v[256] = {0};
	sprintf(v,"%d",para_value);
	return SetStrPara(para_name,v);
}