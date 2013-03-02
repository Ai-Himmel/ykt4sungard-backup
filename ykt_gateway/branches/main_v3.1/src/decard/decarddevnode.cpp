#include "ksgateway.h"
#include "osutil.h"
#include "pubfunc.h"
#include "ksglobal.h"
#include "task_scheduler.h"
#include "impl/schdimpl.h"
#include "xutils/xstring.h"
#include "decard/decarddevnode.h"
#include "netutil.h"
#include "F8583.h"

#ifdef HAS_DECARD_SUPPORT

DECLARE_NAMESPACE_BEGIN(DECARD)

KSG_REG_FACTORY_INTERFACE(KSG_DECARD_DEV,KSG_DC_DevInterfaceFactory);

// ע���豸����
KSG_REG_DEVICE_OBJECT(KSG_DECARD_DEV,KSG_BUSPOS_DEV,DC_BusPos_Device);

static DC_Service_Request g_global_dc_request;

static unsigned char calc_sum(unsigned char *buf,int len)
{
	int i;
	unsigned char r;
	for(i=0,r=0;i<len;++i)
		r += buf[i];
	return r;
}
void DC_DeviceLoader::SetupDeviceGroup(KSGDeviceNode* node)
{
	KSG_Task_Queue *queue = NULL;
	if(node->get_vendor() != KSG_DECARD_DEV)
		return;
	node->connect_module(KSGDeviceNode::cm_long_conn);
	if(node->GetDeviceType() == KSG_BUSPOS_DEV)
	{
		queue = Task_Queue_Pool::instance()->add_initial_queue(KSG_SCHEDULER_STATUS);
	}
	else
	{
		return;
	}
	ACE_ASSERT(queue != NULL);
	// �޷������豸
	if(queue->load_all_device(node))
	{
		ACE_DEBUG((LM_ERROR,"�޷������豸dev[%d]",node->GetDevId()));
		throw KSGException();
	}
	return;
}
int DC_DeviceLoader::LoadDevice(KSGDeviceManager* manager)
{
	return 0;
}
int DC_DeviceLoader::Finish(KSGDeviceManager* manager)
{
	KSGDeviceManager::DeviceList * devs = manager->GetDevices();
	try
	{
		manager->Traseval(boost::bind(&DC_DeviceLoader::SetupDeviceGroup,this,_1));
	}
	catch (KSGException &e)
	{
		KSG_DUMP_EXCEPTION(e);
		return -1;
	}
	return 0;
}

int DC_DevInterfaceLoader::LoadInterface(KSGDeviceManager *manager)
{
	return 0;
}

int DC_TaskExecutorLoader::LoadExecutor()
{
	return 0;
}
//////////////////////////////////////////////////////////////////////////
// Device define
int DC_BusPos_Device::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}
int DC_BusPos_Device::close_handler(KSGDeviceNode* node,ACE_HANDLE handler)
{
	return 1;
}
bool DC_BusPos_Device::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	return false;
}


//////////////////////////////////////////////////////////////////////////
// 
KSG_ADD_LISTENER_CLASS(KSG_DECARD_LISTENER,DC_Service_Acceptor);
int DC_Service_Acceptor::blk_per_dl_ = 9;
int DC_Service_Acceptor::start_listen()
{
	// �˿ڴӺ�̨�ж�ȡ1
	std::string value;
	int port = 6002;
	if(open(ACE_INET_Addr(port)) == -1 )
	{
		ACE_DEBUG((LM_ERROR,"�¿����ػ�������������ʧ��\n"));
		return -1;
	}
	ACE_DEBUG((LM_INFO,"�¿����ػ������߳�ThreadId[%u]�˿�[%d]\n",ACE_OS::thr_self(),port));

	if(KsgGetSystemParam(156,value)==0)
	{
		DC_Service_Acceptor::blk_per_dl_ = ACE_OS::atoi(value.c_str());
		DC_Service_Acceptor::blk_per_dl_ = 
			(DC_Service_Acceptor::blk_per_dl_ < 1 || DC_Service_Acceptor::blk_per_dl_ > 9) ? 
			3 : DC_Service_Acceptor::blk_per_dl_;
	}
	ACE_DEBUG((LM_DEBUG,"�¿����ػ�ÿ�����غ���������[%d]",DC_Service_Acceptor::blk_per_dl_));
	return 0;
}
int DC_Service_Acceptor::stop_listen()
{
	handle_close();
	return 0;
}
KSG_Service_Handler * DC_Service_Acceptor::new_handle()
{
	KSG_Service_Handler * hd = NULL;
	try
	{
		hd = new DC_Service_Handler(this->reactor());
	}
	catch (...)
	{
		ACE_DEBUG((LM_EMERGENCY,"���ܴ����µ��������󣡣���"));
	}
	return hd;
}
int DC_Service_Acceptor::free_handle(KSG_Service_Handler *handle)
{
	delete handle;
	return 0;
}
//////////////////////////////////////////////////////////////////////////
DC_Service_Handler::DC_Service_Handler(ACE_Reactor *r):KSG_Service_Handler(r)
{
	this->request_ = &g_global_dc_request;
}
int DC_Service_Handler::recv_data(ACE_Message_Block *&blk)
{
	int ret;
	size_t maxlen;
	ACE_Time_Value tv(0);
	if(blk == NULL)
	{
		ACE_NEW_RETURN(blk,ACE_Message_Block(512),-1);
	}
	else
	{

	}
	maxlen = blk->size()-blk->length();
	ret = KSGNetUtil::recv_buffer(peer().get_handle(),(unsigned char*)blk->wr_ptr(),maxlen,&tv);
	if(ret)
	{
		return -1;
	}
	if(maxlen==0)
		return 0;
	blk->wr_ptr(maxlen);
	// TODO: �жϰ�����
	return 1;
}
int DC_Service_Handler::process_request(long timeout )
{
	return -1;
}

int DC_Service_Request::process_request(void *arg,long timeout )
{
	int ret;
	KSG_WORK_SVR_HANDLER * hd = reinterpret_cast<KSG_WORK_SVR_HANDLER*>(arg);
	if(hd==NULL)
		return -1;
	try
	{
		ret = do_request(hd);
		return ret;
	}
	catch (...)
	{
		ACE_DEBUG((LM_ERROR,"����¿�ҵ������ʧ�ܣ�"));
		return -1;
	}
}
int DC_Service_Request::do_request(KSG_WORK_SVR_HANDLER *handle)
{
	ACE_Message_Block *mblk = handle->mblk_;
	ACE_SOCK_Stream peer;
	ACE_Message_Block *resp_buf;
	unsigned char *msg_begin = (unsigned char*)mblk->rd_ptr();
	unsigned char *out_buf;
	unsigned char crc_code[4];
	int data_len = mblk->length();
	short pack_len;
	int len;
	int ret;
	peer.set_handle(handle->handle_);
	ACE_HEX_DUMP((LM_DEBUG,mblk->rd_ptr(),mblk->length()));

	if(msg_begin[0]!=0xC0 && msg_begin[data_len]!=0xC1)
	{
		ACE_DEBUG((LM_ERROR,"�յ����ݰ���ʼ������..."));
		return -1;
	}
	BUF_2_SHORT_BE(pack_len,(msg_begin+1));
	if(data_len - 3 < pack_len )
	{
		ACE_DEBUG((LM_ERROR,"�յ��������ݰ����ȴ���..."));
		return -1;
	}
	// check crc
	/*
	pack_len = GenerateCRC16(msg_begin+3,data_len-3-3);
	SHORT_2_BUF_BE(pack_len,crc_code);
	if(memcmp(crc_code,msg_begin+data_len-3,2)!=0)
	{
		ACE_DEBUG((LM_ERROR,"�յ����ݰ�CRCУ�����..."));
		return 0;
	}
	*/
	if(calc_sum(msg_begin+3,data_len-3-2)!=msg_begin[data_len-2])
	{
		ACE_DEBUG((LM_ERROR,"�յ����ݰ�CRCУ�����..."));
		return 0;
	}
	ACE_NEW_RETURN(resp_buf,ACE_Message_Block(512),-1);
	len = 0;
	out_buf = (unsigned char*)resp_buf->wr_ptr();
	out_buf[0]=0xC2;
	out_buf[3]=msg_begin[3];
	switch(msg_begin[3])
	{
	case 0x70:
		ret = do_upload_serial(msg_begin,data_len,out_buf+4,len);
		break;
	case 0x71:
		ret = do_download_blkcard(msg_begin,data_len,out_buf+4,len);
		break;
	default:
		ret = -1;
		break;
	}
	if(ret == 1)
	{
		if(len > 0)
		{	
			// ����CRC
			out_buf[4+len]=calc_sum(out_buf+3,len+1);
			len+=5;
			out_buf[len++] = 0xC3;
			pack_len = len - 3;
			SHORT_2_BUF_BE(pack_len,(out_buf+1));
			resp_buf->wr_ptr(len);
			ACE_HEX_DUMP((LM_DEBUG,resp_buf->rd_ptr(),resp_buf->length()));
			ACE_Time_Value tv(0);
			if(peer.send_n(resp_buf,&tv) <=0 )
			{
				ACE_DEBUG((LM_ERROR,"����Ӧ���ʧ��"));
				ret = -1;
			}
			else
			{
				ret = 1;
			}
		}
		else
			ret = 0;
	}
	resp_buf->release();
	return ret;
}

int DC_Service_Request::do_save_record(unsigned char *recbuf)
{
	int offset,int_value,out_bala,retries;
	short short_value;
	char phyid[9] = "";
	unsigned char buf[4];
	char dt_str[20] = "";
	char str[10]= "";
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		return -1;
	}
	obj->SetRequestHeader(950031);
	offset = 0;
	// �汾��
	offset++;
	// �豸���� ID	
	xutil::StringUtil::Hex2Str(recbuf+offset,4,phyid);
	obj->AddField(F_SDATE0,phyid);
	obj->AddField(F_SPHONE3,phyid);
	offset+=4;
	// ��ˮ��
	BUF_2_INT_BE(int_value,(recbuf+offset));
	offset+=4;
	obj->AddField(F_LVOL4,int_value);
	// ���׿���
	memset(buf,0,sizeof buf);
	memcpy(buf+1,recbuf+offset,3);
	BUF_2_INT_BE(int_value,buf);
	obj->AddField(F_LVOL5,int_value);
	offset +=3;
	// �뿨���
	BUF_2_INT_BE(int_value,(recbuf+offset));
	obj->AddField(F_LVOL9,int_value);
	offset+=4;
	out_bala = int_value;
	// ���׽��
	memset(buf,0,sizeof buf);
	memcpy(buf+1,recbuf+offset,3);
	BUF_2_INT_BE(int_value,buf);
	obj->AddField(F_LVOL8,int_value);
	offset+=3;
	// �������
	out_bala -= int_value;
	obj->AddField(F_LVOL10,out_bala);
	// ���״���
	BUF_2_SHORT_BE(short_value,(recbuf+offset));
	obj->AddField(F_LVOL7,(int)short_value);
	offset+=2;
	// ����ʱ��
	//str2bcd(record->tx_datetime,12,buffer+offset);
	xutil::StringUtil::BCD2Str(recbuf+offset,6,dt_str);
	strncpy(str,dt_str,6);
	obj->AddField(F_SPOST_CODE,str);
	memset(str,0,sizeof str);
	strncpy(str,dt_str+6,6);
	obj->AddField(F_SPOST_CODE2,str);
	offset+=6;
	// ���ױ�־
	int_value = recbuf[offset];
	if(int_value == 0x0A)
		int_value = 0x99;
	obj->AddField(F_LVOL12,int_value);
	offset++;
	// ��������
	offset++;
	// Ǯ����
	int_value = recbuf[offset++];
	obj->AddField(F_LVOL6,int_value);

	// ��ϵͳ��
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());

	retries = 3;
	while(retries-->0)
	{
		if(obj->Connect())
		{
			// ����ʧ��
			continue;
		}
		if(!obj->SendRequest(5000))
		{
			if(obj->GetReturnCode()==0)
			{
				ACE_DEBUG((LM_INFO,"���泵�ػ���ˮ�ɹ�!"));
				return 0;
			}
		}
	}
	return -1;
}

int DC_Service_Request::do_upload_serial(unsigned char *inbuf,int inlen,unsigned char *outbuf,int &outlen)
{
	short crccode;
	int i,ret;
	outlen = 2;
	unsigned char mybuf[64];
	for(i = 0;i < inbuf[5];++i)
	{
		memcpy(mybuf,inbuf+7+i*48,48);
		ret = do_save_record(mybuf);
		if(ret)
		{
			ACE_DEBUG((LM_ERROR,"�ϴ���ˮ����̨ʧ�ܣ�"));
			break;
		}
		else
		{
			// ������ˮ��
			memcpy(outbuf+2+i*4,inbuf+7+i*48+5,4);
			outlen+=4;
		}
	}
	if(i > 0)
	{
		outbuf[0] = 0;
		outbuf[1] = i * 4;
	}
	else
	{
		// �ϴ�ʧ��
		outbuf[0] = 0xFF;
		outbuf[1] = 0;
	}
	
	return 1;
}
int DC_Service_Request::do_download_blkcard(unsigned char *inbuf,int inlen,unsigned char *outbuf,int &outlen)
{
	char blkversion[13] = "";
	char max_vol[13] = "";
	char phyid[9] = "";
	int count;
	KSGDeviceNode *node;
	int blk_card_cnt = DC_Service_Acceptor::blk_per_dl_ + 1;

	// �豸����ID��
	xutil::StringUtil::Hex2Str(inbuf+7,4,phyid);
	node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_ERROR,"�豸[%s]δע��",phyid));
		return -1;
	}
	// �豸�������汾��
	outlen=1;
	outbuf[0] = 0xFF;
	xutil::StringUtil::BCD2Str(inbuf+7+4,6,blkversion);
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		return 1;
	}
	if(obj->Connect())
	{
		// ����ʧ��
		return 1;
	}
	obj->SetRequestHeader(950007);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
	obj->AddField(F_LVOL1,blk_card_cnt);
	obj->AddField(F_LVOL5,node->GetDevId());
	obj->AddField(F_SNAME,blkversion);
	if(obj->SendRequest(5000))
	{
		// ����ָ��ʧ��
		ACE_DEBUG((LM_DEBUG,"����ָ�ʱ�ȴ�����!"));
		return 1;
	}
	if(obj->GetReturnCode())
	{
		ACE_DEBUG((LM_ERROR,"���غ�����ʧ�ܣ�����[%d][%s]",
			obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
		return 1;
	}
	count = 0;
	ACE_OS::memset(max_vol,0,sizeof max_vol);
	while(obj->HasMoreRecord()&&count < blk_card_cnt - 1)
	{
		ST_PACK * data = obj->GetNextRecord();
		// ����ָ��
		int flag = data->lvol3;
		int devid = data->lvol5;
		int cardid = data->lvol2;
		ACE_OS::strcpy(max_vol,data->sname);
		// ��ɾ��־
		flag = (flag == 0) ? 0 : 1;
		unsigned char buf[10] = "";
		INT_2_BUF_BE(cardid,buf);
		memcpy(outbuf+2+count*4,buf+1,3);
		outbuf[5+count*4] = flag;
		count++;
	}
	if(count > 0)
	{
		outbuf[1] = count*4+6;
		outlen = 2+4*count;
		xutil::StringUtil::Str2BCD(max_vol,12,outbuf+outlen);
		outlen += 6;
		if(obj->HasMoreRecord())
		{
			outbuf[outlen]=0xFF;
		}
		else
			outbuf[outlen]=0x00;
		outlen++;
		outbuf[0] = 0x00;
		outbuf[1] = 4*count+7;
	}
	else
	{
		// ��ʾϵͳ�޺�����
		outbuf[0] = 0x5D;
	}
	return 1;
}

DECLARE_NAMESPACE_END(DECARD);

#endif //HAS_DECARD_SUPPORT