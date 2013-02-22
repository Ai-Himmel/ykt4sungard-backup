#include "StdAfx.h"
#include "DataParse.h"

DataParse::DataParse(void):m_logWriter("com"),kdbc()
{
	memset(m_RecvData,0,sizeof(m_RecvData));
	m_RecvLen = 0;
	//s_PreRecvLen = 0;
	m_deviceIDMap = NULL;    
	
}

DataParse::~DataParse(void)
{
	
}

void DataParse::SetDeviceIDMap(FIELDMAP *devicedIDMap)
{
	m_deviceIDMap = devicedIDMap;
}

// �����յ������ݣ���1���յ��������󣬣�2������δ�����꣬0����ȷ
int DataParse::Recv(char *buf,int bufLen)
{
	int lrc = 0, i,size;
	unsigned char c = 0;
	
	if(bufLen < 10 || bufLen > 67)
	{
		//s_PreRecvLen = bufLen;
		return -1;
	}

	memcpy(m_RecvData,buf,bufLen);

	if (m_RecvData[0] != STX)
		return -1;

	size = (m_RecvData[2] >> 4) * 10 + (m_RecvData[2] & 0x0f) +
		(m_RecvData[1] >> 4) * 1000 + (m_RecvData[1] & 0x0f) * 100 ;
	if(size < 5 || size > 62)  //����3�Ϊ62
		return -1;

	if(size > bufLen) 
	{
		//s_PreRecvLen = bufLen;
		return -1;
	}
	
	if(m_RecvData[size+3] != ETX)
	{
		//s_PreRecvLen = bufLen;
		return -1;
	}

	////У��
	for(i = 1; i < size + 5; i++) 
		lrc ^= m_RecvData[i];

	if(lrc == 0) 
	{
		memmove(m_RecvData, m_RecvData + 3, size); 
		m_RecvData[size] = 0;
		m_RecvLen = size;
		return 0;
	}

	return -1;
}
int DataParse::GetResponse()
{	
	int ret = 0;
	memset(m_SendData,0,sizeof(m_SendData));
	m_SendLen = 0;

	FIELDMAP::const_iterator conIter;
	FIELDMAP reqMap,resMap;	
	
	memset((char*)&comm_res,0,sizeof(comm_res));
	memset((char*)&comm_req,0,sizeof(comm_req));
	memcpy(comm_res.reqno,m_RecvData,2);
	memcpy(comm_res.deviceid,m_RecvData + 2,3);
	
	//ת�����ж��豸��Ϊһ��ͨ��̨�豸��
	conIter = m_deviceIDMap->find(comm_res.deviceid);
	if(conIter == m_deviceIDMap->end())
	{
		m_logWriter.writelog("���ж��ն˺�:%sδ�ͺ�̨�ն˺Ź���,���������ļ�",comm_res.deviceid);
		return -1;
	}

	reqMap["sorder2"] = conIter->second;
	accMap["sorder2"] = conIter->second;
	
	if(m_RecvLen != 0 && strncmp(m_RecvData,"01",2) == 0)  ///ǩ��
	{		
		m_logWriter.writelog("signReq: %s",comm_res.deviceid);
		kdbc.SetReqNo(240008);
		kdbc.SetReqField(&reqMap);

		resMap["scard0"] = "";
		ret = kdbc.GetReqValue(&resMap);
		if (ret == 0)
		{
			std::string str = resMap["scard0"];
			int len = str.length();
			memcpy(comm_res.respno,"00",2);
			memcpy(m_SendData+5,str.c_str(),(len > 32)? 32:len);
			m_logWriter.writelog("signResp: %s",str.c_str());
		}
		else			
		{
			memcpy(comm_res.respno,"FF",2);
			m_logWriter.writelog("signResp: get response from ykt backgroud error");
		}
		m_SendLen = 39;
		memcpy(m_SendData,comm_res.reqno,2);
		memcpy(m_SendData+2,comm_res.deviceid,3);
		memcpy(m_SendData+37,comm_res.respno,2);		
	}
	
	if (m_RecvLen != 0 && strncmp(m_RecvData,"03",2) == 0)  ///��̨������
	{
		kdbc.SetReqNo(240002);
		memcpy(comm_req.cardid,m_RecvData+5,11);
		memcpy(comm_req.tradeamt,m_RecvData+16,6);
		memcpy(comm_req.serialno,m_RecvData+22,6);
		memcpy(comm_req.cardbala,m_RecvData+28,10);
		memcpy(comm_req.tradecount,m_RecvData+38,5);
		memcpy(comm_req.bankno,m_RecvData+43,19);
		m_logWriter.writelog("tryAcc_req: %s,%s,%s,%s,%s,%s,%s",comm_res.deviceid,comm_req.cardid,
			comm_req.tradeamt,comm_req.serialno,comm_req.cardbala,comm_req.tradecount,comm_req.bankno);
		// TODO: 
		if(strlen(comm_req.bankno) < 15)
		{
			m_logWriter.writelog("tryAcc_req: bad bankno [%s],less then 15",comm_req.bankno);
			return -1;
		}
		reqMap["sserial0"] = comm_req.cardid;		//����
		accMap["sserial0"] = comm_req.cardid;		
		reqMap["lvol5"] = comm_req.tradeamt;		//���׽��
		accMap["lvol5"] = comm_req.tradeamt;		
		reqMap["lvol0"] = comm_req.serialno;		//Ȧ�����ˮ��
		reqMap["lvol6"] = comm_req.cardbala;		//�����
		reqMap["lvol1"] = comm_req.tradecount;		//���״���
		reqMap["scust_auth"] = comm_req.bankno;		//���п���
		kdbc.SetReqField(&reqMap);
		resMap["lvol2"] = "";						//���ؿ����(��λΪ��)
		resMap["lvol1"] = "";						//������ˮ��
		ret = kdbc.GetReqValue(&resMap);
		if (ret == 0)
		{
			std::string str ;
			memcpy(comm_res.respno,"00",2);
			str = resMap["lvol2"];					
			memcpy(comm_res.cardbala,str.c_str(),str.length());
			str = resMap["lvol1"];
			accMap["lvol7"] = str;			//�����˷�����ˮ�ţ�������ʽ����
			m_logWriter.writelog("tryAcc_resp: %s,%s,%s",resMap["lvol1"].c_str(),resMap["lvol2"].c_str(),comm_req.serialno);
		}
		else			
		{
			memcpy(comm_res.respno,"FF",2);
			m_logWriter.writelog("tryAcc_resp: get response from ykt backgroud error");
		}
	
		m_SendLen = 40;
		memcpy(m_SendData,comm_res.reqno,2);		
		memcpy(m_SendData+2,comm_res.deviceid,3);		//�豸��
		memcpy(m_SendData+5,comm_req.cardid,11);		//����
		memcpy(m_SendData+16,resMap["lvol1"].c_str(),6);		//У԰������ˮ��
		memcpy(m_SendData+22,comm_req.serialno,6);				//Ȧ�����ˮ�ţ����ػ�ȥ����Ȧ�����֤
		memcpy(m_SendData+28,comm_res.cardbala,10);				//����ֵ
		memcpy(m_SendData+38,comm_res.respno,2);				
	}

	else if (m_RecvLen != 0 && strncmp(m_RecvData,"02",2) == 0)  ///��̨��ʽ����
	{	
		char temp[3] = "";				
		memcpy(temp,m_RecvData + 11,2);					//д���Ƿ�ɹ�
		memcpy(comm_req.serialno,m_RecvData+5,6);		//�����˷��ص���ˮ��
	
		m_logWriter.writelog("accReq: %s,%s,%s",comm_res.deviceid,comm_req.serialno,temp);
		if (strncmp(m_RecvData+11,"00",2) == 0)
		{			
			//���յ�����ˮ���� accMap["lvol7"] ���бȽϣ�һ�µĻ�����ʽ����
			if (strncmp(comm_req.serialno,accMap["lvol7"].c_str(),6) == 0)
			{
				kdbc.SetReqNo(240001);			
				kdbc.SetReqField(&accMap);

				resMap["damt0"] = "";
				resMap["lvol1"] = "";
				int ret = kdbc.GetReqValue(&resMap,1);
				if (ret == 0)
					m_logWriter.writelog("accResp: %s,%s",resMap["lvol1"].c_str(),resMap["damt0"].c_str());
				else
					m_logWriter.writelog("accResp: get response from ykt backgroud error");
				
			}		
			else
				m_logWriter.writelog("accResp: recv serino[%s],need[%d]",comm_req.serialno,accMap["lvol7"].c_str());
		}		
		else
        {
			m_logWriter.writelog("accResp: Ȧ�����֪д��ʧ��");
            // Add by TC 2009-9-24 ����Ȧ��д��״̬��¼
            if(strncmp(m_RecvData+13,"00",2)==0)
            {
                m_logWriter.writelog("serial[%s][00]���쳣״̬",resMap["lvol1"].c_str());
            }
            else if(strncmp(m_RecvData+13,"01",2)==0)
            {
                m_logWriter.writelog("serial[%s][01]�״�д��ǰ��ȡ��״̬�ǳ���",resMap["lvol1"].c_str());
            }
            else if(strncmp(m_RecvData+13,"02",2)==0)
            {
                m_logWriter.writelog("serial[%s][02]�״�д��ǰ��ȡ���Ų����",resMap["lvol1"].c_str());
            }
            else if(strncmp(m_RecvData+13,"03",2)==0)
            {
                m_logWriter.writelog("serial[%s][03] ����д��ǰ�û�ȡ��",resMap["lvol1"].c_str());
            }
            else if(strncmp(m_RecvData+13,"04",2)==0)
            {
                m_logWriter.writelog("serial[%s][04]����д��ǰ����ʧ��",resMap["lvol1"].c_str());
            }
            else if(strncmp(m_RecvData+13,"05",2)==0)
            {
                m_logWriter.writelog("serial[%s][05]����д��ǰ�ж��û����Ų����",resMap["lvol1"].c_str());
            }
            else if(strncmp(m_RecvData+13,"06",2)==0)
            {
                m_logWriter.writelog("serial[%s][06]��д����ȷ��δ��д�뵽���ڣ����ж˳���",resMap["lvol1"].c_str());
            }
            else if(strncmp(m_RecvData+13,"07",2)==0)
            {
                m_logWriter.writelog("serial[%s][07] �ڶ���д���ɹ�",resMap["lvol1"].c_str());
            }
            else if(strncmp(m_RecvData+13,"08",2)==0)
            {
                m_logWriter.writelog("serial[%s][08]�޷��ж��Ƿ�д���ɹ�",resMap["lvol1"].c_str());
            }
        }
		accMap.clear();
		reqMap.clear();
		resMap.clear();
		return 1;    //���÷��ر���
	}
	reqMap.clear();
	resMap.clear();
	return 0;
}
int DataParse::Send(char *buf,int &bufLen)
{
	unsigned char lrc = 0;
	int i = 0;

	memmove(m_SendData + 3,m_SendData,m_SendLen);

	m_SendData[0] = STX;

	m_SendData[1] = (int)(m_SendLen / 1000) << 4 | (int)(m_SendLen % 1000) / 100;
	m_SendData[2] = (int)((m_SendLen %100) / 10) << 4 |(int)((m_SendLen % 100) % 10);

	m_SendData[m_SendLen+3] = ETX;

	for(lrc=0,i=1; i<m_SendLen+4; i++)
		lrc ^= m_SendData[i];
	m_SendData[m_SendLen+4] = lrc;

	bufLen = m_SendLen + 5;

	memcpy(buf,m_SendData,bufLen);
	buf[bufLen] = 0;

	return 0;
}
void DataParse::Flush()
{
	memset(m_RecvData,0,sizeof(m_RecvData));
	m_RecvLen = 0;
//	s_PreRecvLen = 0;
}