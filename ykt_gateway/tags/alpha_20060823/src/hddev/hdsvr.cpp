#include "stdafx.h"
#include "ksglobal.h"
#include "hddev/hdsvr.h"
#include "ksgateway.h"
#include "bit_endian.h"
#include "F8583.h"
#include "device.h"
#include <ace/ACE.h>
#include <ace/File_Lock.h>
#include "xutils/xstring.h"
#include "ftplib.h"
#include "osutil.h"

unsigned long HDDEV::DecodeTermSN(const char * sn)
{
	int i = 0;
	char temp[2] = "";
	char text[12] = "";
	ACE_OS::strncpy(text,sn,4);
	temp[0] = sn[4];
	i = ACE_OS::strtoul(temp,NULL,16);
	if(i < 0)
		return -1;
	ACE_OS::sprintf(text+4,"%.02d",i);
	temp[0] = sn[5];
	i = ACE_OS::strtoul(temp,NULL,16);
	if(i < 0)
		return -1;
	ACE_OS::sprintf(text+6,"%.02d",i);
	ACE_OS::strncat(text+8,sn+6,2);
	text[10] = '\0';
	return ACE_OS::strtoul(text,NULL,10);
}

void HDDEV::EncodeTermSN(unsigned long termid,char* sn)
{
	int i = 0;
	int j = 0;
	char temp[3] = "";
	char text[12] = "";
	ACE_OS::sprintf(text,"%.010lu",termid);
	ACE_OS::strncpy(sn,text,4);
	ACE_OS::strncpy(temp,text+4,2);
	i = atoi(temp);
	if(i < 0 || i >15)
		return;
	ACE_OS::strncpy(temp,text+6,2);
	j = ACE_OS::atoi(temp);
	if(j < 0 || j > 15)
		return;
	ACE_OS::sprintf(sn+4,"%X%X",i,j);
	ACE_OS::strncat(sn+6,text+8,2);
	sn[9] = '\0';
}

unsigned long HDDEV::EncodeVersionNum(const char* version)
{
	unsigned long ret = 0;
	char tmp[3] = "";
	int i;
	int d_offset[6] = {6,4,5,5,6,6};
	int d_mask[7] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F};

	unsigned long dateval[7];
	for(i = 0;i < 6;++i)
	{
		ACE_OS::strncpy(tmp,version+i*2,2);
		dateval[i] = (unsigned long)ACE_OS::atoi(tmp);
	}
	int j = 0;
	for(i = 0;i < 6;++i)
	{
		j += d_offset[i];
		ret |= (dateval[i] & d_mask[d_offset[i]]) 
			<< (sizeof(unsigned long) * 8 - j);
	}
	return ret;
}
int HDDEV::DecodeVersionNum(unsigned long num,char* ver)
{
	int i;
	int d_offset[6] = {6,4,5,5,6,6};
	int d_mask[7] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F};

	int j = 0;
	for(i = 0;i < 6;++i)
	{
		j += d_offset[i];
		BYTE t = (BYTE)(num >> (sizeof(unsigned long)*8 - j)) & d_mask[d_offset[i]];
		ACE_OS::sprintf(ver,"%.02d",t);
		ver+=2;
	}
	return 0;
}

MYDATETIMESTRUCT HDDEV::HDGetDataTime()
{
	time_t now = ACE_OS::gettimeofday().sec();
	struct tm* tv = ACE_OS::localtime(&now);
	MYDATETIMESTRUCT ret;
	ret.Year = (tv->tm_year + 1900) % 2000;
	ret.Month = tv->tm_mon + 1;
	ret.Day = tv->tm_mday;
	ret.Hour = tv->tm_hour;
	ret.Minute = tv->tm_min;
	ret.Second = tv->tm_sec;
	ret.DayOfWeek = tv->tm_wday;
	return ret;
}

size_t HDDEV::PackRequestStruct(HD8583STRUCT& req,MESSAGETYPE msg_type
						 ,void* buf,size_t maxlen,bool with_crc )
{
	HDISO8583Msg msg;
	char * output = (char*)buf;
	char * bitmap = output+3;
	size_t packlen = msg.Pack(req,output+3,maxlen-3);
	if(packlen <= 0)
		return 0;
	output[2] = (char)msg_type;
	packlen++;
	if(with_crc)
	{
		bitmap[FIELD_MACOFBASALBITMAP/8] |= 1 << (7 - FIELD_MACOFBASALBITMAP % 8);
		int i = (int)GenerateCRC16((unsigned char*)output+2,packlen);
		output[packlen+3] = i % 0x100;
		output[packlen+2] = i / 0x100;	
		packlen+=2;
	}
	SHORT_2_BUF(packlen,output);
	return packlen+2;
}
int HDDEV::UnPackResponseStruct(HD8583STRUCT& resp,MESSAGETYPE* msg_type,
						 void* buf,size_t buflen)
{
	short datalen;
	HDISO8583Msg msg;
	char * input = (char*)buf;
	BUF_2_SHORT(datalen,input);
	if(datalen > buflen - 2)
		return -1;
	*msg_type = (MESSAGETYPE)(input[2] & 0xFF);
	unsigned char zero[2] = {0x00,0x00};
	if(msg.Unpack(resp,input+3,datalen-1) > 0)
	{
		if(ACE_OS::memcmp(resp->mac,zero,2))
		{
			// 2 byte ����, 2 byte mac ��
			unsigned short i = GenerateCRC16((unsigned char*)input+2,buflen-4);
			char tmp[3] = "";
			tmp[0] = (char)((i & 0xFF00) >> 8);
			tmp[1] = (char)(i & 0xFF);
			if(ACE_OS::memcmp(resp->mac,tmp,2))
				return -1;
			return 0;
		}
		return 0;
	}
	return -1;
}

unsigned short HDDEV::GetDeviceAddress(KSGDeviceNode* node)
{
	if(!node)
		return 0;
	unsigned short addr = (unsigned short)
		ACE_OS::atoi(node->GetDevAddr().GetDevCode().c_str());
	if(node->GetDeviceType() == KSG_HD_POS_DEV
		|| node->GetDeviceType() == KSG_HD_ADD_POS_DEV)
	{
		addr |= HDA_SYSTEMIDOFPOS1_1;
	}
	else if(node->GetDeviceType() == KSG_HD_GCU_DEV)
	{
		addr |= HDA_SYSTEMIDOFACC1_1;
	}
	else if(node->GetDeviceType() == KSG_HD_SERVER_DEV)
	{
		addr = HDA_SYSTEMIDOFALL;
	}
	return addr;
}

int HDDEV::HDSendBuffer(ACE_HANDLE handler,char* buf,size_t buflen
				 ,ACE_Time_Value* timeout)
{
	if(ACE_INVALID_HANDLE == handler)
		return -1;
	ACE_SOCK_Stream stream(handler);
	size_t transfered;
	ACE_Time_Value tv(3);
	if(ACE::handle_write_ready(handler,&tv) <= 0) 
		return -1;
	stream.send_n(buf,buflen,timeout,&transfered);
	if(buflen == transfered)
	{
		return 0;
	}
	return -1;
}
int HDDEV::HDRecvBuffer(ACE_HANDLE handler,char* buf,size_t maxbuf
				 ,ACE_Time_Value* timeout)
{
	ACE_SOCK_Stream stream(handler);
	// USE recv_n ��ȡ����
	size_t transfered =	0;
	ACE_Time_Value tv(3);
	if(ACE::handle_read_ready(handler,&tv) <= 0) 
		return -1;
	stream.recv_n(buf,maxbuf,timeout,&transfered);
	if(transfered <= 0 || transfered > maxbuf)
	{
		return -1;
	}
	return transfered;
}

int HDDEV::HDParsePosRecord(BYTE* buf,TRADERECORDSTRUCT* trade)
{
	BUF_2_INT(trade->CardNumber,buf);
	BUF_2_INT(trade->Balance,buf+4);
	BUF_2_INT(trade->Amount,buf+8);
	trade->Year = *(buf+12);
	trade->Month = *(buf+13);
	trade->Day = *(buf+14);
	trade->Hour = *(buf+15);
	trade->Minute = *(buf+16);
	trade->Second = *(buf+17);
	BUF_2_SHORT(trade->TraceOfEW,buf+18);
	BUF_2_INT(trade->TraceOfPOS,buf+20);
	BUF_2_INT(trade->OrgTransTrace,buf+24);
	BUF_2_INT(trade->OperatorID,buf+28);
	BUF_2_INT(trade->TerminalSN,buf+32); // �ն˺�
	BUF_2_SHORT(trade->AdditionalMoney,buf+36); // �����
	BUF_2_SHORT(trade->GoodsNumber,buf+38);
	trade->IndexOfEW = *(buf+40);
	if(trade->IndexOfEW > 0)
		trade->IndexOfEW--;
	trade->RecordType = *(buf+41);
	trade->ConsumeMode = *(buf+42);
	memcpy(trade->MAC,buf+43,4);
	uint16 i = GenerateCRC16(buf,43);
	if( (i & 0xFF) != trade->MAC[1] || ((i & 0xFF00)>>8) != trade->MAC[0])
		return -1;
	return 0;
}
namespace HDDEV
{

///////////////////////////////////////////////////////////////////
//
int HDCCUSvrHandler::open(void*)
{
	
	ACE_INET_Addr peer_addr;
	if(peer().get_remote_addr(peer_addr) == -1)
	{
		return -1;
	}
	ACE_DEBUG((LM_DEBUG,"������������[%s]",peer_addr.get_host_addr()));
	// TODO : ���IP��ַ�Ƿ�Ϸ�
	/*
	 if( IP ���Ϸ� )
		return -1;
	 */
	_close_time = 1;
	try
	{
		REACTOR::instance()->register_handler(this,READ_MASK);
	}
	catch(...)
	{
		return -1;
	}
	
	return 0;
}

int HDCCUSvrHandler::handle_input(ACE_HANDLE fd)
{
	ACE_Message_Block * mb;
	ACE_NEW_RETURN(mb,ACE_Message_Block(MAX_MESBUF_LEN),0);
	// read data
	ACE_INT32 n = 0;
	ACE_INT32 m = 0;
	while( (n = peer().recv(mb->wr_ptr(),mb->size() - m)) >= 0 )
	{
		mb->wr_ptr(n);
	}
	if(mb->length() <= 0)
	{
		mb->release();
		return -1;
	}

	// �������
	if(putq(mb) == -1)
	{
		ACE_DEBUG((LM_ERROR,"����ʧ��"));
		return -1;
	}
	_close_time = 2;
	activate(THR_NEW_LWP|THR_JOINABLE,1);
	return 0;
}

int HDCCUSvrHandler::handle_timeout(const ACE_Time_Value &time, const void *)
{
	return 0;
}

int HDCCUSvrHandler::handle_close(ACE_HANDLE handler, ACE_Reactor_Mask mask)
{
	REACTOR::instance()->remove_handler(this,ACE_Event_Handler::READ_MASK|ACE_Event_Handler::DONT_CALL);
	dec_close_time();
	delete_self();
	return 0;
}

int HDCCUSvrHandler::close(u_long flags)
{
	dec_close_time();
	delete_self();
	return 0;
}

void HDCCUSvrHandler::dec_close_time()
{
	_mutex.acquire();
	_close_time = (--_close_time >=  0 ) ? _close_time : 0;
	_mutex.release();
}

void HDCCUSvrHandler::delete_self()
{
	bool canClose = false;
	_mutex.acquire();
	canClose = (_close_time == 0);
	_mutex.release();
	if(canClose)
		delete this;
}

int HDCCUSvrHandler::svc()
{
#define MES_DATA_HEAD_LEN 2

	ACE_Message_Block * mb = NULL;
	
	ACE_Time_Value tv(5);
	if (this->getq(mb,&tv) == -1) return -1;
	HD8583STRUCT req;
	HD8583STRUCT resp;
	MESSAGETYPE msg_type;
	char * buffer = mb->rd_ptr();
	int len = 0;
	// ���ݶγ��ȳ�������Χ,��������
	if(UnPackResponseStruct(req,&msg_type,buffer,mb->length()) != 0)
	{
		ACE_ERROR((LM_ERROR,"���ݰ����Ϸ�"));
		mb->release();
		return -1;
	}
	
	ACE_HEX_DUMP((LM_DEBUG,mb->rd_ptr(),mb->length()));
	try
	{
		HDResponseHandler* handler = HDCCUProcessUnits::Instance().Create(msg_type);
		if(handler)
		{
			resp.Init();
			
			int result = handler->DoResponse(req,resp,peer().get_handle());
			if(result > 0)
			{
				// send back
				mb->reset();
				buffer = mb->wr_ptr();
				len = (int)PackRequestStruct(resp,msg_type,buffer,mb->size());
				mb->wr_ptr(len);
				ACE_HEX_DUMP((LM_DEBUG,buffer,mb->length()));
				ACE_DEBUG((LM_DEBUG,"���ݰ�����[%d]",mb->length()));
				if(peer().send_n(mb->rd_ptr(),mb->length()) <=0 )
				{
					ACE_DEBUG((LM_ERROR,"����Ӧ���ʧ��"));
				}
				
			}
			else if(result == 0)
			{
				// OK
				ACE_DEBUG((LM_DEBUG,"����ɹ�"));
			}
			else
			{
				// error
				ACE_DEBUG((LM_ERROR,"��������ʧ�ܣ�������[%d]",result));
			}
		}
		else
		{
			ACE_ERROR((LM_ERROR,"���ܴ����������[%c]",msg_type));
		}	
	}
	catch(...)
	{
		// �������е��쳣
		ACE_ERROR((LM_ERROR,"���������쳣,�������[%02x]",msg_type));
	}	
	mb->release();
	return 0;
}

////////////////////////////////////////////////////////////////////////
// 
HD_REGISTER_HANDLER(MT_REECHO1,HDReechoHandler1);
int HDReechoHandler1::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	
	unsigned int termid = req->TerminalSN;
	unsigned short canid = req->Address;
	//��������Բ���Ҫ�ж� CCU �µ��豸�Ƿ����
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_SUCCESS);
	ACE_SOCK_Stream stream(peer);
	ACE_INET_Addr peer_addr;
	if(stream.get_remote_addr(peer_addr) == -1)
	{
		return -1;
	}
	char ipbuf[10] = "";
	ACE_UINT32 ip = peer_addr.get_ip_address();
	// ȫ��ʹ�������ֽ���
	ip = ACE_HTONL(ip);
	ACE_OS::memcpy(ipbuf,(const void*)&ip,sizeof ip);
	resp.SetFieldValue(FIELD_ADDITIONALDATA1,ipbuf,ACE_OS::strlen(ipbuf));
	// ��ҪӦ��
	return 1;
}

//////////////////////////////////////////////////////////////////////////////
// �豸ǩ��ָ��
HD_REGISTER_HANDLER(MT_SIGNIN1,HDEnrollHandler);
int HDEnrollHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	// 
	// �����豸
	KSGDeviceManager * manager = KsgGetGateway()->GetDeviceManager();
	char phyid[12] = "";
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode * node = manager->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_DEBUG,"�豸������[%s]",phyid));
		return -1;
	}
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_RESPONSECODE,(short)RC_SUCCESS);
	// �豸Ӧ�����
	
	return 1;
}

///////////////////////////////////////////////////////////////////////////
//
HD_REGISTER_HANDLER(MT_INITKEY1,HDInitKeyHandler);
int HDInitKeyHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	// ����豸��Ϣ
	
	KSGDeviceManager * manager = KsgGetGateway()->GetDeviceManager();
	char phyid[12] = "";
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode * node = manager->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_DEBUG,"�豸������[%s]",phyid));
		return -1;
	}
	
	char buf[32] = "";
	if(xutil::StringUtil::Str2Hex(
		KsgGetGateway()->GetConfig()->_cardKey.c_str(),(unsigned char*)buf,8) == -1)
		return -1;
	ACE_OS::memset(buf+8,0xFF,16);
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,24);

	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_SUCCESS);
	// ������Կ
	return 1;
}

////////////////////////////////////////////////////////////////////////
//
int HDDownloadBlkCard::DownloadBlackCard(BYTE addflag,KSGDeviceNode* node
										 ,KSGDeviceNode::Task* task)
{
	int ret = TASK_ERR_COMMON;
	try
	{
		
		int cardid = task->GetParams().GetParamIntVal(XML_KEY_CARDID);
		std::string version = task->GetParams().GetParam(XML_KEY_VERNUM);
		KSGDeviceNode* task_node = task->GetDeviceNode();
		unsigned short addr;
		addr = GetDeviceAddress(task->GetDeviceNode());
		HD8583STRUCT req;
		req.Init();
		req.SetFieldValue(FIELD_ADDRESS,addr);
		req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId());
		unsigned long encode_ver = EncodeVersionNum(version.c_str());
		req.SetFieldValue(FIELD_VERSIONOFLIST,encode_ver);
		char data[256] = "";
		ACE_OS::memset(data,0,sizeof data);
		data[0] = addflag;
		INT_2_BUF(cardid,data+1);
		req.SetFieldValue(FIELD_ADDITIONALDATA2,data,5);
		data[0] = 0x01;
		req.SetFieldValue(FIELD_ADDITIONALDATA3,data,1);
		ACE_OS::memset(data,0,sizeof data);
		ACE_HANDLE handler = ACE_INVALID_HANDLE;
		ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
		int recvlen = -1;
		size_t packlen;
		if((packlen = PackRequestStruct(req,MT_UPDATELIST2,data,sizeof data,true)) == 0)
		{
			// ��������ݰ�
			ret = TASK_ERR_COMMON;
		}		
		else if(node->GetDevice()->find_handler(node,&handler))
		{
			// �޷�����
			ret = TASK_ERR_CONNECT;
		}
		else if(HDSendBuffer(handler,data,packlen,&tv))
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else if((recvlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else
		{
			HD8583STRUCT resp;
			MESSAGETYPE msg_type;
			if(UnPackResponseStruct(resp,&msg_type,data,(size_t)recvlen))
			{
				ret = TASK_ERR_EXECUTE;
			}
			else if( (req->Address != resp->Address)
				|| (req->VerOfList != resp->VerOfList))
			{
				ret = TASK_ERR_EXECUTE;
			}
			else
			{
				KSGTaskResponse &tresp = task->GetResponse();
				tresp.AddField(XML_KEY_CARDID,cardid);
				char version_str[14] = "";
				DecodeVersionNum(resp->VerOfList,version_str);
				tresp.AddField(XML_KEY_VERNUM,version_str);
				ret = TASK_SUCCESS;
			}
		}
		//node->GetDevice()->close_handler(node,handler);
		task->SetNeedResponse();
		return ret;
	}
	catch(KeyNotFoundException& )
	{
		return TASK_ERR_COMMON;
	}
	catch(...)
	{
		return TASK_ERR_COMMON;
	}
}
/////////////////////////////////////////////////////////////////////////////
//
HDRecordFileReader::~HDRecordFileReader()
{
	
}
int HDRecordFileReader::ReadFile()
{
	if(ACE_OS::filesize(_filepath.c_str()) == 0)
	{
		ACE_DEBUG((LM_INFO,"�ռ�¼�ļ�,����Ҫ�ɼ�"));
		return 0;
	}
	if((_file_handler = ACE_OS::open(_filepath.c_str()
		,O_RDWR)) == ACE_INVALID_HANDLE)
	{
		ACE_DEBUG((LM_ERROR,"����ˮ��¼�ļ�ʧ��"));
		return -1;
	}
	int ret = ReadPosRecord();
	ACE_OS::close(_file_handler);
	if(ret == 0)
	{	
		if(ACE_OS::unlink(_filepath.c_str()))
		{
			ACE_DEBUG((LM_ERROR,"ɾ����¼�ļ�ʧ��[%s]",_filepath.c_str()));
		}
	}
	return ret;
}
int HDRecordFileReader::ReadPosRecord()
{
	std::string index_file = _filepath + ".ind";
	ACE_File_Lock file_lock(_file_handler);
	int ret = 0;
	_file_handler = ACE_OS::dup(file_lock.get_handle());
	if(file_lock.tryacquire())
	{
		ACE_DEBUG((LM_ERROR,"������¼�ļ�ʧ��[%s]",_filepath.c_str()));
		return -1;
	}
	try
	{
		ret = DoReadRecordFile();
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"�����¼�ļ��쳣......."));
	}
	
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"�����¼ʧ��"));
	}
	else
	{
		ACE_OS::unlink(index_file.c_str());
	}
	file_lock.release();
	return ret;
}
int HDRecordFileReader::SaveIndex(size_t index)
{
	std::string index_file = _filepath + ".ind";
	FILE* fp;
	if((fp = ACE_OS::fopen(index_file.c_str(),"w+")) == NULL)
	{
		return -1;
	}
	ACE_OS::fwrite((void*)&index,1,sizeof(size_t),fp);
	ACE_OS::fclose(fp);
	return 0;
}
size_t HDRecordFileReader::LoadIndex()
{
	std::string index_file = _filepath + ".ind";
	if(!KSGOSUtil::FileExists(index_file))
		return 0;
	FILE* fp;
	if((fp = ACE_OS::fopen(index_file.c_str(),"r")) == NULL)
	{
		return 0;
	}
	size_t ind = 0;
	size_t readbytes = ACE_OS::fread((void*)&ind,1,sizeof(size_t),fp);
	if(readbytes != sizeof(size_t))
		ind = 0;
	ACE_OS::fclose(fp);
	return ind;
}
int HDRecordFileReader::DoReadRecordFile()
{
	unsigned char buf[47] = "";
	long filesize = 0;
	if((filesize = ACE_OS::lseek(_file_handler,0L,SEEK_END)) == -1 )
	{
		return -1;
	}
	// ��СΪ�յ��ļ���Ҫɾ��
	if(filesize == 0)
	{
		ACE_DEBUG((LM_DEBUG,"�ռ�¼�ļ����Զ�ɾ��.."));
		return 0;
	}

	// �ļ���С����
	if(filesize % sizeof buf != 0)
	{
		ACE_DEBUG((LM_ERROR,"��ˮ��¼�ļ���С����ȷ!"));
		return -2;
	}
	size_t reccnt = filesize / sizeof(buf);
	size_t index = LoadIndex();
	// ��Ϊ��ȡ��
	if(index >= reccnt)
		return 0;
	if(ACE_OS::lseek(_file_handler,sizeof(buf)*index,SEEK_SET) == -1)
	{
		ACE_DEBUG((LM_DEBUG,"��λ��¼ʧ��!"));
		return -1;
	}
	size_t readbytes = 0;
	size_t bufsize = 0;
	do
	{
		readbytes = ACE_OS::read(_file_handler,buf+bufsize,sizeof(buf) - bufsize);
		if(readbytes == 0)
		{
			if(bufsize == sizeof buf)
			{
				// һ����ˮ
				if(SavePosRecord(buf))
					return -1;
				SaveIndex(++index);
			}
			return 0;
		}
		bufsize += readbytes;
		if(bufsize == sizeof buf)
		{
			// һ����ˮ
			if(SavePosRecord(buf))
				return -1;
			SaveIndex(++index);
			bufsize = 0;
		}
		//KSGThreadUtil::Sleep(1000);
	}while(1);
	return 0;
}
int HDRecordFileReader::SavePosRecord(BYTE* buf)
{
	TRADERECORDSTRUCT trade;
	memset(&trade,0,sizeof trade);
	if(HDParsePosRecord(buf,&trade))
	{
		ACE_DEBUG((LM_ERROR,"POS��ˮ��¼У�����"));
		// CRC ����Ҫɾ��
		return 0;
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	int tx_mark = E_999_FAILED;
	BYTE t = trade.RecordType & 0x0F;
	switch(t)
	{
	case 0x00:
		tx_mark = E_999_FAILED;
		break;
	case 0x01:
		tx_mark = E_999_SUCCESS;
		break;
	case 0x02:
		ACE_DEBUG((LM_DEBUG,"���׽��[%d][%d]",trade.Balance,trade.Amount));
		tx_mark = E_999_CANCEL;
		break;
	case 0x03:
		break;
	case 0x04:
		break;
	case 0x0A:
		tx_mark = E_999_ADD_MENOY;
		break;
	case 0x0B:
		break;
	case 0x0C:
		break;
	case 0x0D:
		break;
	case 0x0E:
		break;
	case 0x0F:
		break;
	}
	if((trade.RecordType & 0x40) == 0)
	{
		// �ڿ�����
		tx_mark = E_999_BLKCARD;
	}
	if(trade.RecordType & 0x20)
	{
		// ��;����
		tx_mark = E_999_UNCONFIRM;
	}
	if(tx_mark == E_999_ADD_MENOY)
	{
		// ����ǳ�ֵ����
		obj->SetRequestHeader(930034);
	}
	else 
	{
		if(E_999_CANCEL == tx_mark && trade.Amount < 0)
		{
			obj->SetRequestHeader(930034);
		}
		else
			obj->SetRequestHeader(950031);
	}
	
	obj->AddField(F_LVOL4,trade.TraceOfPOS); // ��ˮ��
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	char sn[12] = "";
	EncodeTermSN(trade.TerminalSN,sn);
	obj->AddField(F_SDATE1,sn);
	obj->AddField(F_STX_PWD,"");
	obj->AddField(F_LBANK_ACC_TYPE,19); // ͨѶ�汾�� 39 ����
	obj->AddField(F_LBANK_ACC_TYPE2,0); // ��Ŀ�շ�
	char crc[5] = "";
	xutil::StringUtil::Hex2Str(trade.MAC,2,crc); // CRC У��
	obj->AddField(F_SBANK_CODE2,crc);
	obj->AddField(F_LVOL6,trade.IndexOfEW); // Ǯ����
	obj->AddField(F_LVOL5,trade.CardNumber); // ���׿���
	/*
	 1. ����ʱ, ���׽���� ��ֵ , ������� ��ֵ
	 2. ��ֵʱ, ���׽���� ��ֵ
	 3. ���ѳ���ʱ, ���׽���� ��ֵ , ������� ��ֵ
	 4. ��ֵ����ʱ,���׽���� ��ֵ
	 */
	obj->AddField(F_LVOL9,trade.Balance + (-1*trade.Amount)); //�뿨ֵ 
	obj->AddField(F_LVOL10,trade.Balance); // ����ֵ
	if(E_999_CANCEL == tx_mark)
	{
		obj->AddField(F_LVOL8,ABS(trade.Amount) * -1); // ���׽��
		obj->AddField(F_LVOL1,ABS(trade.AdditionalMoney) * -1); // �����
	}
	else
	{
		obj->AddField(F_LVOL8,ABS(trade.Amount));	//���׽��
		obj->AddField(F_LVOL1,ABS(trade.AdditionalMoney)); // �����
	}
	obj->AddField(F_LVOL7,trade.TraceOfEW); // Ǯ��ˮ�ź�
	char dt_buf[9] = "";
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",trade.Year,trade.Month,trade.Day);
	obj->AddField(F_SPOST_CODE,dt_buf);
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",trade.Hour,trade.Minute,trade.Second);
	obj->AddField(F_SPOST_CODE2,dt_buf);
	
	obj->AddField(F_LVOL12,tx_mark);

	int retries = 3;
	while(retries-->0)
	{
		if(obj->Connect())
		{
			// ����ʧ��
			continue;
		}
		// ������ˮ
		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_DEBUG,"������ˮʧ��[%s][%d]������[%d][%s]"
				,sn,trade.TraceOfPOS,obj->GetReturnCode()
				,obj->GetReturnMsg().c_str()));
			}
			else
				return 0;
		}
		// 1 �������
		ACE_DEBUG((LM_NOTICE,"�ϴ���ˮ����ʧ��,�ȴ�����!!!"));
		KSGThreadUtil::Sleep(1000);
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// CCU ����֪ͨ
HD_REGISTER_HANDLER(MT_CCUONLINENOTICE1,HDCCUNoticeHandler);
int HDCCUNoticeHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int recordcnt = 0;
	int packlen;
	std::string filepath;
	char data[128] = "";
	int ret;
	char phyid[12] = "";
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
		return -1;

	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	
	MYDATETIMESTRUCT now = HDDEV::HDGetDataTime();
	resp.SetFieldValue(FIELD_DATEANDTIME,(char*)&now,sizeof now);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	unsigned char buf[(FILEID_ARECORD+1)* 6];
	ACE_OS::memset(buf,0x00,sizeof buf);
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,(char*)buf,sizeof buf);
	packlen = PackRequestStruct(resp,MT_CCUONLINENOTICE1,data,sizeof data);
	if(HDSendBuffer(peer,data,packlen,&tv))
	{
		ACE_DEBUG((LM_ERROR,"����Ӧ��ʧ��"));
	}
	// ����Ӧ��
	filepath = HDA_FILENAME_PRECORD1;
	ret = DoFile(FILEID_PRECORD1,req->AdditionalData2+FILEID_PRECORD1*6
		,node,req,filepath);
	if(ret)
	{
		// ����
		ACE_DEBUG((LM_ERROR,"�����ļ�ʧ��"));
	}
	filepath = HDA_FILENAME_PRECORD2;
	ret = DoFile(FILEID_PRECORD2,req->AdditionalData2+FILEID_PRECORD2*6
		,node,req,filepath);
	if(ret)
	{
		// ����
		ACE_DEBUG((LM_ERROR,"�����ļ�ʧ��"));
	}
	return ret;
}

int HDCCUNoticeHandler::DoFile(int fileid,BYTE* filebuf
							   ,KSGDeviceNode* node,HD8583STRUCT& req
							   ,std::string& filepath)
{
	int ret;
	char devid[12] = "";
	char data[128] = "";
	HD8583STRUCT resp;
	int packlen;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();

	ACE_OS::sprintf(devid,"%.010d",req->TerminalSN);
	// 1. ��鲢���ؼ�¼�ļ�
	// 2. ������سɹ�,ɾ��CCU�еļ�¼�ļ�
	// 3. �ɼ���¼�ļ��еļ�¼����̨
	ret = CheckFile(fileid,filebuf,devid,filepath);
	
	if(ret == 0)
	{
		resp.Init();
		resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
		char tmp[3] = "";
		tmp[0] = fileid;
		resp.SetFieldValue(FIELD_ADDITIONALDATA2,tmp,1);
		packlen = (size_t)PackRequestStruct(resp,MT_CLEARFILE2,data,sizeof data,true);
		int retries = 3;
		ACE_HANDLE handler = ACE_INVALID_HANDLE;
		node->GetDevice()->make_handler(node,&handler);
		MESSAGETYPE msg_type;
		while(retries-- > 0)
		{
			if(!HDSendBuffer(handler,data,packlen,&tv))
				break;
		}
		if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
		{
			ACE_DEBUG((LM_ERROR,"�������ʧ��"));
		}
		else if(UnPackResponseStruct(resp,&msg_type,data,packlen))
		{
			ACE_DEBUG((LM_ERROR,"�������ݰ�ʧ��"));
		}
		else if(resp->ResponseCode != RC_SUCCESS
			&& resp->ResponseCode != 28 // ��¼�ļ�ԭ�����ǿյ�
			&& resp->TerminalSN != req->TerminalSN)
		{
			ACE_DEBUG((LM_ERROR,"ɾ����¼�ļ�ʧ��[%x]",fileid));
			// FIXME : �Ƿ�Ҫɾ����¼�ļ���
			// XXX: ��ɾ��,���Բɼ�
		}
		if(handler != ACE_INVALID_HANDLE)
			node->GetDevice()->close_handler(node,handler);
		if(retries <= 0)
		{
			ACE_DEBUG((LM_DEBUG,"����CCUʧ��"));
			return -1;
		}
		// ������ˮ
		HDRecordFileReader reader(filepath);
		ret = reader.ReadFile();
		if(ret)
		{
			ACE_DEBUG((LM_DEBUG,"��ȡ��ˮʧ��[%d]",ret));
		}
	}
	else if(ret > 0)
	{
		// �޼�¼��δ�ر�
		if(KSGOSUtil::FileExists(filepath))
		{
			HDRecordFileReader reader(filepath);
			ret = reader.ReadFile();
			if(ret)
			{
				ACE_DEBUG((LM_DEBUG,"��ȡ��ˮʧ��[%d]",ret));
			}
		}
	}
	else
	{
		// ����
		ACE_DEBUG((LM_ERROR,"�����ļ�ʧ��"));
	}
	return ret;

}
int HDCCUNoticeHandler::CheckDownloadPath(const std::string& devid,std::string& filepath)
{
	std::string basepath = KsgGetGateway()->GetConfig()->_basedir;
	basepath = KSGOSUtil::JoinPath(basepath,"data/");
	ACE_DIR* dir = ACE_OS::opendir(basepath.c_str());
	if(!dir)
	{
		if(ACE_OS::mkdir(basepath.c_str()))
		{
			ACE_DEBUG((LM_ERROR,"����Ŀ¼ʧ��[%s]",basepath.c_str()));
			return -1;
		}
	}
	else
		ACE_OS::closedir(dir);
	basepath = KSGOSUtil::JoinPath(basepath,devid);
	dir = ACE_OS::opendir(basepath.c_str());
	if(!dir)
	{
		if(ACE_OS::mkdir(basepath.c_str()))
		{
			ACE_DEBUG((LM_ERROR,"����Ŀ¼ʧ��[%s]",basepath.c_str()));
			return -1;
		}
	}
	else 
		ACE_OS::closedir(dir);
	filepath = KSGOSUtil::JoinPath(basepath,filepath);
	if(KSGOSUtil::FileExists(filepath))
	{
		if(ACE_OS::filesize(filepath.c_str()) == 0)
		{
			// �ռ�¼�ļ�, ɾ��
			if(ACE_OS::unlink(filepath.c_str()))
				// ��ʾ�ļ��Ѵ���
				return 1;
			// ����
			return 0;
		}
		// ��ʾ�ļ��Ѵ���
		return 1;
	}
	return 0;
}
int HDCCUNoticeHandler::CheckFile(int fileid,BYTE* data
								  ,const std::string& devid
								  ,std::string& filepath)
{
	int recordcnt = 0;
	int ret;
	// ������ˮ�ļ�
	std::string datafile = filepath;

	BYTE file_index = *data;
	BYTE file_flag = 0x00;
	if(file_index == fileid)
	{
		// ����¼�ļ� 1
		BUF_2_INT(recordcnt,data + 1);
		file_flag = *(data + 5);
		ACE_DEBUG((LM_DEBUG,"CCU Notice [��¼��%d]",recordcnt));
		// �����ʱĿ¼
		ret = CheckDownloadPath(devid,filepath);
		if(ret > 0)
		{
			ACE_DEBUG((LM_ERROR,"�ļ��Ѿ�����!"));
			// �ļ��Ѿ�����,��������ʹ����
			return ret;
		}
		else if(ret < 0)
		{
			// ����Ŀ¼ʧ��
			return ret;
		}
		if(file_flag != FILE_CLOSE)
		{
			ACE_DEBUG((LM_DEBUG,"��¼�ļ�����ʹ���� ... "));
			return -1;
		}
		// û�м�¼
		if(recordcnt <= 0)
			return 1;
	}
	else
	{
		return -1;
	}
	
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(devid);
	if(node == NULL)
		return -1;
	
	// �����ļ�
	ftplib::netbuf nb;
	memset(&nb,0,sizeof nb);
	ftplib::netbuf* control = &nb;
	
	std::string ipstr = node->GetDevAddr().GetConnect() + ":";
	ipstr += HD_CCH_FTP_PORT;

	if(ftplib::FtpConnect(ipstr.c_str(),&control) != 1)
	{
		ACE_DEBUG((LM_ERROR,"����CCUʧ��,[%s]",node->GetPhyId().c_str()));
		return -1;
	}
	try
	{

		// �ɼ���ˮ
		if(ftplib::FtpLogin(HD_CCU_FTP_USER,HD_CCU_FTP_PSWD,control) != 1)
		{
			ACE_DEBUG((LM_ERROR,"��¼CCUʧ��,�û������������[%s]",node->GetPhyId().c_str()));
			return -1;
		}
		if(ftplib::FtpGet(filepath.c_str(),datafile.c_str(),FTPLIB_IMAGE,control) != 1)
		{
			ACE_DEBUG((LM_ERROR,"���ؼ�¼�ļ�ʧ��[%s]",datafile.c_str()));
			return -1;
		}
		else if(ACE_OS::filesize(filepath.c_str()) == 0)
		{
			// ���ص��ļ�Ϊ��,ɾ��֮
			if(ACE_OS::unlink(datafile.c_str()))
			{
				ACE_DEBUG((LM_ERROR,"ɾ���ռ�¼�ļ�ʧ��!"));
			}
			return -2;
		}
	}
	catch(...)
	{
		// �����ļ�ʧ��,���� ERROR
		return -1;
	}

	try
	{
		ftplib::FtpQuit(control);
		ftplib::FtpClose(control);
	}
	catch(...)
	{
		// �ر�����ʧ��,�����κ���
	}
	return 0;
}

} // end of namespace
