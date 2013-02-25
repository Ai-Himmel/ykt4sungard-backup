// RequestSocket.cpp : implementation file
/** 
 * ģ����						�����ϵͳ
 * �ļ���						RequestSocket.cpp
 * �ļ�ʵ�ֹ���					�������������Socket
 * ����							����
 * �汾							V0.3
 * ����							2005-07-02
 * ��ע
 * $Id: RequestSocket.cpp 23 2005-09-02 08:41:36Z cheng.tang $
 *
 *
 *	�޸�ʱ��		�汾	����	˵��
 *  2005-08-29		V0.2	����	����ͨ��IP��ַ����ȡMAC��ַ�ĺ���
 *  2005-09-02		V0.3	����	�����˼�����Կʱ��Bug
 *									�����ȴ����ݵ�Socket�޷���ʱ���رյ�Bug
 *
 */

#include "stdafx.h"
#include "XMLFile.h"
#include <string>
#include "yktsubsystem.h"
#include "RequestSocket.h"
#include "sysutil.h"
#include "LogFactory.h"
#include "KLogfile.h"
#include "rijndael-api-fst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static unsigned char static_key[] = "54869752";
/////////////////////////////////////////////////////////////////////////////
// CRequestSocket
CRequestSocket::CRequestSocket(CYktsubsystemDoc * pDoc)
:m_pDoc(pDoc),m_buf_len(0),m_reqStatus(REQ_REQUEST),m_IsRunning(FALSE)
{
	//m_buf.SetSize(DEFAULT_BUF_SIZE);
	memset(m_buf,0,DEFAULT_BUF_SIZE);
	m_startTick = GetTickCount();
}
CRequestSocket::CRequestSocket()
{
}

CRequestSocket::~CRequestSocket()
{
	KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
	m_pDoc->DecRunningRequest(this);
	log->WriteLog("���󱻹ر�!");
	//
	//AfxMessageBox("shut down!");
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRequestSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CRequestSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRequestSocket member functions

void CRequestSocket::ResetReceive()
{
	m_buf_len = 0;
	memset(m_buf,0,DEFAULT_BUF_SIZE);
}
void CRequestSocket::SaveData(BYTE * buf,int len)
{
	int packlen;
	int shouldLen;
	KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
	if(m_buf_len + len > DEFAULT_BUF_SIZE )
	{
		log->WriteLog("�������ݳ���̫����",m_buf_len + len);
		m_reqStatus = REQ_ERROR;
		return;
	}
	memcpy((BYTE *)m_buf + m_buf_len,buf,len);

	m_buf_len += len;
	if(m_buf_len >= 4)
	{
		memcpy(&packlen,m_buf,sizeof(packlen));
		packlen = ntohl(packlen);
		shouldLen = packlen + sizeof(ksf_card_info) - sizeof(char[1]);
		if(shouldLen <= m_buf_len)
		{
			m_buf_len = shouldLen;
			log->WriteLog("�������ݰ�ͷ����[%d]",packlen);
			m_reqStatus = REQ_RECV_OK;
		}
	}
}
int CRequestSocket::ProcessRequest()
{
	long startTick = GetTickCount();
	BYTE buf[DEFAULT_BUF_SIZE];
	KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
	int bytes;
	while(m_reqStatus != REQ_DONE)
	{
		bytes = Receive(buf,DEFAULT_BUF_SIZE);
		while(bytes > 0)
		{
			if(m_buf_len + bytes > DEFAULT_BUF_SIZE)
			{
				log->WriteLog("���ݰ����Ȳ���ȷ!");
				goto L_SHUTDOWN;
			}
			SaveData(buf,bytes);
			bytes = Receive(buf,DEFAULT_BUF_SIZE);
		}
		
		if(m_buf_len <= 0)
		{
			log->WriteLog("û�н��յ����ݰ�! ");
			goto L_SHUTDOWN;
		}
		log->WriteLog("�������ݰ�,����[%d]",m_buf_len);
		DoGetData();
		ResetReceive();
	}
L_SHUTDOWN:
	ShutDown(both);
	Release();
	return 0;
}
void CRequestSocket::OnReceive(int nErrorCode) 
{
	BYTE buf[DEFAULT_BUF_SIZE];
	KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
	int bytes;
	bytes = Receive(buf,DEFAULT_BUF_SIZE);
	if(bytes != SOCKET_ERROR)
	{	
		if(bytes)
		{
			if(m_buf_len + bytes > DEFAULT_BUF_SIZE)
			{
				log->WriteLog("���ݰ����Ȳ���ȷ!");
				goto L_SHUTDOWN;
			}
			SaveData(buf,bytes);
		}
	}
	
	if(m_buf_len <= 0)
	{
		log->WriteLog("û�н��յ����ݰ�! ");
		goto L_SHUTDOWN;
	}
	log->WriteLog("�������ݰ�,����[%d]",m_buf_len);
	switch(m_reqStatus)
	{
	case REQ_GET_NEXT_PACK:
	case REQ_REQUEST:
		goto L_END;
	case REQ_RECV_OK:
		DoGetData();
		break;
	case REQ_DONE:
	default:
		// ���
		goto L_SHUTDOWN;
	}
L_END:
	CAsyncSocket::OnReceive(nErrorCode);
	return;
L_SHUTDOWN:
	ShutDown(both);
	Release();
}

void CRequestSocket::Release()
{
	delete this;
}

void CRequestSocket::DoGetData()
{
	ksf_card_info * card_info;
	KLogfile * log= KLogFactory::GetInstance()->GetLogSys();
	m_IsRunning = TRUE;
	// �����ڴ�ռ�
	card_info = (ksf_card_info *)malloc(m_buf_len);
	memcpy(card_info,m_buf,m_buf_len);
	card_info->length = ntohl(card_info->length);
	card_info->count = ntohl(card_info->count);
	card_info->func_no = ntohl(card_info->func_no);
	card_info->pack_index = ntohl(card_info->pack_index);
	card_info->next_pack = ntohl(card_info->next_pack);
	int shouldLen = m_buf_len - sizeof(ksf_card_info) + sizeof(card_info->data);
	if(card_info->length != shouldLen )
	{
		log->WriteLog("ȫ��[%d]��ȡ���ݰ���������Ϊ[%d],ʵ��Ϊ[%d]",
			m_buf_len,card_info->length,shouldLen);
		// bad pack
		m_IsRunning = FALSE;
		ShutDown(both);
		return;
	}
	ProcessRequest(card_info);
	m_IsRunning = FALSE;
	ResetReceive();
	// ʹ����֮��Ҫ�ͷ�
	if(card_info)
	{
		free(card_info);
	}
}

int CRequestSocket::DecryptAES128(ksf_card_info* info)
{
	// ���� KEY ��
	BYTE bin_key[MAXKC<<2] = "";
	char key_meterial[320] = "";
	BYTE md5[16];
	char * p;
	char tmp[4] = "";
	char tokentmp[30]="";
	int i,j;
	int key_length = 128;
	cipherInstance cipher_inst;
	keyInstance key_inst;
	ksf_server_conf* svr = m_pDoc->GetServerConfig();
	KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
	// log->WriteLog("ʹ��AES128�������ݰ�!");
	i = 0;
	/***********************************************
	����Key ���㷨
	IP��ַ����λ��Ϊ 0 ~ 3 λ
	MAC ��ַ��λ��Ϊ 4 ~ 9 λ
	10 ~ 15 λΪ0 ,Ȼ�����MD5[16Bytes]
	��0 ~ 15λ��λȡ���
	*************************************************/
	memset(bin_key,0,sizeof(bin_key));
	// IP
	strcpy(tokentmp,svr->ip);
	p = strtok(tokentmp,".");
	while(p != NULL)
	{
		strncpy(tmp,p,sizeof(tmp));
		bin_key[i++] = (BYTE)strtoul(tmp,NULL,10);
		p = strtok(NULL,".");
	}
	if (i != 4)
	{
		/*
		kcc_write_log(LOG_ERR,"gen server key error!ip[%s]",
			svr->conf.ip);
		*/
		return -1;
	}
	// MAC
	memset(tmp,0,sizeof(tmp));
	strcpy(tokentmp,svr->mac);
	for(j = 0;tokentmp[j] != '\0';j+=2)
	{
		strncpy(tmp,&tokentmp[j],2);
		bin_key[i++] = (BYTE)strtoul(tmp,NULL,16);
	}
	if (i != 10)
	{
		/*
		kcc_write_log(LOG_ERR,"gen server key error!MAC[%s]",
			svr->conf.mac);
		*/
		return -1;
	}
	
	ksf_md5_helper(bin_key,md5,16);
	i = 0;
	for(j = 0;j < key_length/8;++j)
	{
		bin_key[j] ^= md5[j];
		i += sprintf(key_meterial+i,"%02X",bin_key[j]);
	}
	key_meterial[i] = '\0';
	// ����Key���
	/*
	kcc_write_log(LOG_DEBUG,"gen key [%s] server[%d]",
		key_meterial,svr->server_no);
	*/
	makeKey(&key_inst,DIR_DECRYPT,key_length,key_meterial);
	cipherInit(&cipher_inst,MODE_ECB,NULL);
	if(info->padded)
	{
		i = padDecrypt(&cipher_inst,&key_inst,(BYTE*)info->data,
			info->length,(BYTE*)info->data);
		if(i > 0)
		{
			// ���ܺ��ʵ�ʳ���
			info->length = i;
			log->WriteLog("ʹ��AES128�������ݰ� �ɹ�![%d]",i);
			return 0;
		}
		log->WriteLog("ʹ��AES128�������ݰ� ʧ��[%d]!padding",i);
	}
	else
	{
		if(blockDecrypt(&cipher_inst,&key_inst,(BYTE*)info->data,
			info->length<<3,(BYTE*)info->data) > 0)
		{
			log->WriteLog("ʹ��AES128�������ݰ� �ɹ�!");
			return 0;
		}
		log->WriteLog("ʹ��AES128�������ݰ� ʧ��!");
	}
	return -1;
}
ksf_xml_data * CRequestSocket::DecryptData(ksf_card_info * info )
{
	//ksf_server_conf * server_conf = m_pDoc->GetServerConfig();
	//ksf_gen_key(server_conf,static_key,(unsigned char*)salt);
	ksf_xml_data * xml_data = NULL;
	unsigned char md5[16] = "";
	// ������ݱ�����,��Ҫ�Ƚ���
	switch(info->enc_type)
	{
	default:
	case ENC_TYPE_NONE:
		break;
	case ENC_TYPE_AES128:
		if(DecryptAES128(info) != 0)
		{
			return NULL;
		}
		break;
	}
	ksf_md5_helper((unsigned char *)info->data,md5,info->length);
	if( memcmp(md5,info->CRC,16) != 0)
	{
		return NULL;
	}
	int len = sizeof(ksf_xml_data) - sizeof(char[1]) + info->length;
	xml_data = (ksf_xml_data *)malloc(len+1);
	xml_data->count = info->count;
	xml_data->func_no = info->func_no;
	xml_data->length = info->length;
	memcpy(xml_data->data,info->data,info->length);
	xml_data->data[xml_data->length] = '\0';
	//AfxMessageBox(xml_data->data);
	return xml_data;
}

int CRequestSocket::ProcessRequest(ksf_card_info * card_info)
{
	if(m_pDoc)
	{
		KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
		CPluginManage * manage = m_pDoc->GetPluginModule();
		const ksf_plugin_module * module = manage->GetPluginModule();
		ksf_server_conf * server_conf = m_pDoc->GetServerConfig();
		ksf_xml_data * data = NULL;
		ksf_card_result res;
		res.ret = RET_FAILD;
		if( (data = DecryptData(card_info)) == NULL )
		{
			log->WriteLog("�յ����ݰ���ʽ����");
			// ���ݰ�����ȷ
			// XXXX : ����ʧ����Ϣ
			SendResult(&res);
			return -1;
		}
		log->WriteLog("�������ݰ���ȷ�����ܺ�[%d]�����[%d]���ݳ�[%d]",
			data->func_no,card_info->pack_index,data->length);
		// �������ݳɹ�
		int ret = -1;
		if(module->module_receive)
		{
			// ���ò�����д���
			try
			{
				log->WriteLog("���ò����������...");
				ret = module->module_receive(server_conf,data,&res);
			}
			catch(...)
			{
				log->WriteLog("����������ݳ����쳣!");
				// ignore
			}
			
		}
		res.pack_index = card_info->pack_index;
		m_reqStatus = REQ_DONE;
		if( ret == 0)
		{
			log->WriteLog("�������ݳɹ�!");
			if( card_info->next_pack > 0 )
			{
				// ������к�̰������õ�ǰ״̬Ϊ������ȡ
				log->WriteLog("������ȡ������!");
				m_reqStatus = REQ_GET_NEXT_PACK;
			}
		}
		else
		{
			log->WriteLog("��������ʧ�ܣ�return code[%d]",ret);
		}
		log->WriteLog("Ӧ�����ݴ������!");
		SendResult(&res);
		if( data )
			free(data);
	}
	return 0;
}

void CRequestSocket::SendResult(ksf_card_result * res)
{
	//
	try
	{
		res->pack_index = htonl(res->pack_index);
		res->ret = (ksf_ret_result)htonl(res->ret);
		Send(res,sizeof(ksf_card_result));
	}
	catch(...)
	{
		// ���ͽ��ʧ��
		// ���ܶԷ��Ѿ��Ͽ�������
	}
	
}

void CRequestSocket::OnSend(int nErrorCode) 
{
	//	
}

void CRequestSocket::OnClose(int nErrorCode) 
{
	CAsyncSocket::OnClose(nErrorCode);
	if(this->IsRunning())
	{
		//
	}
	else
	{
		Release();
	}
}
