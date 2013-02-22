#include "stdafx.h"
#include "SmartTerminal.h"

int nAllocateMemoryFlag = 0;

/*********************��ʼ��ҵ��ԽӲ���*********************/
/* ���ߣ�   ����
*  ���ڣ�   2004��1��6��
*  ��;��   ��ȡ�ն��豸�������еĻ�����Ϣ���������ݸ�ͨ�Ų�
**************************************************************/
int _stdcall Ini_SmartDocPar(DWORD *dwTotalNo,TSSmartDoc **p)
{
	if(nAllocateMemoryFlag != 0) //�Ƿ��Ѿ������
		return RET_ERROR;
	*dwTotalNo = 2;
	if(*dwTotalNo <= 0)   //û���ն��豸��Ϣ
		return RET_ERROR;
	//�����ڴ�
	*p = new TSSmartDoc[*dwTotalNo];
	if(*p == NULL)
		return RET_ERROR;
	//������Ϣ
	nAllocateMemoryFlag = 1;
	(*p)[0].m_dwLength  = sizeof(TSSmartDoc);
	(*p)[0].m_bNetPar   = true;              //���ͽṹ
	(*p)[0].m_ucTotalNo = 2;                 //�ýṹ������̨��������������)
	(*p)[0].m_ucNo      = 0;				  //��ǰͨѶ�˿�Ϊ������	
	(*p)[0].m_wNoReponseTime =0;			  //����Ӧ����Ϊ0
	//ͨ�Ų���
	(*p)[0].m_CommunicationInfo.dwLength = sizeof(CommunicationProperty);
	(*p)[0].m_CommunicationInfo.ucMode   = TCPIP; 
	(*p)[0].m_CommunicationInfo.bStyle   = false;//������ʽ
	(*p)[0].m_CommunicationInfo.bNetFlag = true;//����
	(*p)[0].m_CommunicationInfo.bServerOrClient = true;//������
	sprintf((*p)[0].m_CommunicationInfo.cServerIpAddr,"%s","192.168.0.34");
	(*p)[0].m_CommunicationInfo.wServerPortNo = 10001;
	//�������
	(*p)[0].m_TaskInfo.dwLength = sizeof(TaskProperty);
	(*p)[0].m_TaskInfo.wIDNo    = 0; //��¼�ռ�
	(*p)[0].m_TaskInfo.ucMode   = 0; //Ĭ������
	(*p)[0].m_TaskInfo.ucCommandTotalNo = 1;
	(*p)[0].m_TaskInfo.ucCommandCurrentNo = 0;
	(*p)[0].m_TaskInfo.ucCommandArray[0]  = 0x03;
	//�ն˲���
	//0---������
	(*p)[0].m_TerminalInfo[0].dwLength  = sizeof(TerminalProperty);
	(*p)[0].m_TerminalInfo[0].dwMainKey = 0;
	(*p)[0].m_TerminalInfo[0].ucState   = 1; //����̬
	(*p)[0].m_TerminalInfo[0].ucIDNo[0] = 0x00;//ID��
	(*p)[0].m_TerminalInfo[0].ucIDNo[1] = 0x00;
	(*p)[0].m_TerminalInfo[0].ucIDNo[2] = 0x45;
	(*p)[0].m_TerminalInfo[0].ucIDNo[3] = 0x9B;
	(*p)[0].m_TerminalInfo[0].ucMacNo   = 1;//����
	(*p)[0].m_TerminalInfo[0].ucRegNo[0]= 0x00;//ע���
	(*p)[0].m_TerminalInfo[0].ucRegNo[1]= 0x00;
	(*p)[0].m_TerminalInfo[0].ucRegNo[2]= 0x45;
	(*p)[0].m_TerminalInfo[0].ucRegNo[3]= 0x9B;
	(*p)[0].m_TerminalInfo[0].ucType[0] = 53;//������
	(*p)[0].m_TerminalInfo[0].ucType[1] = 1;
	(*p)[0].m_TerminalInfo[0].ucProgVer[0]= 04;//����汾
	(*p)[0].m_TerminalInfo[0].ucProgVer[1]= 01;
	(*p)[0].m_TerminalInfo[0].ucProgVer[2]= 02;
	(*p)[0].m_TerminalInfo[0].ucProgVer[3]= 10;
	(*p)[0].m_TerminalInfo[0].wEDFlowNo   = 0;//����������ˮ��
	(*p)[0].m_TerminalInfo[0].wECFlowNo   = 0;//����������ˮ��
	//1�˿�---�շѻ�
	(*p)[0].m_TerminalInfo[1].dwLength  = sizeof(TerminalProperty);
	(*p)[0].m_TerminalInfo[1].dwMainKey = 1;
	(*p)[0].m_TerminalInfo[1].ucState   = 1; //����̬
	(*p)[0].m_TerminalInfo[1].ucIDNo[0] = 0x00;//ID��
	(*p)[0].m_TerminalInfo[1].ucIDNo[1] = 0x00;
	(*p)[0].m_TerminalInfo[1].ucIDNo[2] = 0x33;
	(*p)[0].m_TerminalInfo[1].ucIDNo[3] = 0x06;
	(*p)[0].m_TerminalInfo[1].ucMacNo   = 1;//����
	(*p)[0].m_TerminalInfo[1].ucRegNo[0]= 0x00;//ע���
	(*p)[0].m_TerminalInfo[1].ucRegNo[1]= 0x00;
	(*p)[0].m_TerminalInfo[1].ucRegNo[2]= 0x33;
	(*p)[0].m_TerminalInfo[1].ucRegNo[3]= 0x06;
	(*p)[0].m_TerminalInfo[1].ucType[0] = 02;//������
	(*p)[0].m_TerminalInfo[1].ucType[1] = 26;
	(*p)[0].m_TerminalInfo[1].ucProgVer[0]= 03;//����汾
	(*p)[0].m_TerminalInfo[1].ucProgVer[1]= 12;
	(*p)[0].m_TerminalInfo[1].ucProgVer[2]= 28;
	(*p)[0].m_TerminalInfo[1].ucProgVer[3]= 10;
	(*p)[0].m_TerminalInfo[1].wEDFlowNo   = 11;//����������ˮ��
	(*p)[0].m_TerminalInfo[1].wECFlowNo   = 0;//����������ˮ��

	//������Ϣ
	(*p)[1].m_dwLength  = sizeof(TSSmartDoc);
	(*p)[1].m_bNetPar   = true;              //���ͽṹ
	(*p)[1].m_ucTotalNo = 2;                 //�ýṹ������̨��������������)
	(*p)[1].m_ucNo      = 0;				  //��ǰͨѶ�˿�Ϊ������	
	(*p)[1].m_wNoReponseTime =0;			  //����Ӧ����Ϊ0
	//ͨ�Ų���
	(*p)[1].m_CommunicationInfo.dwLength = sizeof(CommunicationProperty);
	(*p)[1].m_CommunicationInfo.ucMode   = TCPIP; 
	(*p)[1].m_CommunicationInfo.bStyle   = false;//������ʽ
	(*p)[1].m_CommunicationInfo.bNetFlag = true;//����
	(*p)[1].m_CommunicationInfo.bServerOrClient = true;//������
	sprintf((*p)[1].m_CommunicationInfo.cServerIpAddr,"%s","192.168.0.35");
	(*p)[1].m_CommunicationInfo.wServerPortNo = 10001;
	//�������
	(*p)[1].m_TaskInfo.dwLength = sizeof(TaskProperty);
	(*p)[1].m_TaskInfo.wIDNo    = 0; //��¼�ռ�
	(*p)[1].m_TaskInfo.ucMode   = 0; //Ĭ������
	(*p)[1].m_TaskInfo.ucCommandTotalNo = 1;
	(*p)[1].m_TaskInfo.ucCommandCurrentNo = 0;
	(*p)[1].m_TaskInfo.ucCommandArray[0]  = 0x03;
	//�ն˲���
	//0---������
	(*p)[1].m_TerminalInfo[0].dwLength  = sizeof(TerminalProperty);
	(*p)[1].m_TerminalInfo[0].dwMainKey = 0;
	(*p)[1].m_TerminalInfo[0].ucState   = 1; //����̬
	(*p)[1].m_TerminalInfo[0].ucIDNo[0] = 0x00;//ID��
	(*p)[1].m_TerminalInfo[0].ucIDNo[1] = 0x00;
	(*p)[1].m_TerminalInfo[0].ucIDNo[2] = 0x46;
	(*p)[1].m_TerminalInfo[0].ucIDNo[3] = 0xBA;
	(*p)[1].m_TerminalInfo[0].ucMacNo   = 1;//����
	(*p)[1].m_TerminalInfo[0].ucRegNo[0]= 0x00;//ע���
	(*p)[1].m_TerminalInfo[0].ucRegNo[1]= 0x00;
	(*p)[1].m_TerminalInfo[0].ucRegNo[2]= 0x46;
	(*p)[1].m_TerminalInfo[0].ucRegNo[3]= 0xBA;
	(*p)[1].m_TerminalInfo[0].ucType[0] = 53;//������
	(*p)[1].m_TerminalInfo[0].ucType[1] = 1;
	(*p)[1].m_TerminalInfo[0].ucProgVer[0]= 04;//����汾
	(*p)[1].m_TerminalInfo[0].ucProgVer[1]= 01;
	(*p)[1].m_TerminalInfo[0].ucProgVer[2]= 02;
	(*p)[1].m_TerminalInfo[0].ucProgVer[3]= 10;
	(*p)[1].m_TerminalInfo[0].wEDFlowNo   = 0;//����������ˮ��
	(*p)[1].m_TerminalInfo[0].wECFlowNo   = 0;//����������ˮ��
	//1�˿�---�շѻ�
	(*p)[1].m_TerminalInfo[1].dwLength  = sizeof(TerminalProperty);
	(*p)[1].m_TerminalInfo[1].dwMainKey = 1;
	(*p)[1].m_TerminalInfo[1].ucState   = 1; //����̬
	(*p)[1].m_TerminalInfo[1].ucIDNo[0] = 0x00;//ID��
	(*p)[1].m_TerminalInfo[1].ucIDNo[1] = 0x00;
	(*p)[1].m_TerminalInfo[1].ucIDNo[2] = 0x48;
	(*p)[1].m_TerminalInfo[1].ucIDNo[3] = 0x18;
	(*p)[1].m_TerminalInfo[1].ucMacNo   = 1;//����
	(*p)[1].m_TerminalInfo[1].ucRegNo[0]= 0x00;//ע���
	(*p)[1].m_TerminalInfo[1].ucRegNo[1]= 0x00;
	(*p)[1].m_TerminalInfo[1].ucRegNo[2]= 0x48;
	(*p)[1].m_TerminalInfo[1].ucRegNo[3]= 0x18;
	(*p)[1].m_TerminalInfo[1].ucType[0] = 02;//������
	(*p)[1].m_TerminalInfo[1].ucType[1] = 26;
	(*p)[1].m_TerminalInfo[1].ucProgVer[0]= 03;//����汾
	(*p)[1].m_TerminalInfo[1].ucProgVer[1]= 12;
	(*p)[1].m_TerminalInfo[1].ucProgVer[2]= 28;
	(*p)[1].m_TerminalInfo[1].ucProgVer[3]= 10;
	(*p)[1].m_TerminalInfo[1].wEDFlowNo   = 0;//����������ˮ��
	(*p)[1].m_TerminalInfo[1].wECFlowNo   = 0;//����������ˮ��

	for(int i=3;i<25;i++)
	{
		(*p)[0].m_TerminalInfo[i].dwLength = sizeof(TerminalProperty);
		(*p)[0].m_TerminalInfo[i].dwMainKey = 0;
		(*p)[0].m_TerminalInfo[i].ucState = 0;
	}

	/*
	for(int i=2;i<25;i++)
	{
		p[0].m_TerminalInfo[i].dwLength   = sizeof(TerminalProperty);
		p[0].m_TerminalInfo[i].dwMainKey  = 0;
		p[0].m_TerminalInfo[i].ucRunFlag    = 3;
	}*/
		
	return RET_OK;
}

int _stdcall ReleaseSmartDocPar(TSSmartDoc **p)
{
	if(nAllocateMemoryFlag != 1)
		return RET_ERROR;
	delete [](*p);
	nAllocateMemoryFlag = 0;
	*p = NULL;
	return RET_OK;
}


int _stdcall BuildTaskBuffer(TSSmartDoc *pDoc,TSSmartBuffer *pBuf,unsigned char *Data,int nLen)
{
	unsigned char  ucCommand,level_Array[256],Buffer[256];
	int  level,len,retLen,addr,no;

	if(nAllocateMemoryFlag != 1)
		return RET_ERROR;
	
	no = pDoc->m_TaskInfo.ucCommandCurrentNo;

	ucCommand = pDoc->m_TaskInfo.ucCommandArray[no];
	
	//������������ṹ
	if(pDoc->m_bNetPar == true)
	{
		if(pDoc->m_ucNo != 0) //��ǰ���ж˿ڲ�Ϊ0
		{
			level = 1;
			level_Array[0] = pDoc->m_TerminalInfo[0].ucMacNo;    //����������
			level_Array[1] = pDoc->m_ucNo;
			if( pDoc->m_CommunicationInfo.ucMode == TCPIP || //TCPIP
				pDoc->m_CommunicationInfo.ucMode == SERIAL   //����
			  )    
			{
				pBuf->wWaitTime1  = (WORD)(500*1.5);
				pBuf->wWaitTime2  = (WORD)(1000*1.5);
			}
			else 
			{
				pBuf->wWaitTime1 = (WORD)(500*2.5);
				pBuf->wWaitTime2 = (WORD)(1000*2.5);
			}
		}
		else //ֱ�ӶԷ���������
		{
			level = 0;
			if( pDoc->m_CommunicationInfo.ucMode == TCPIP || //TCPIP
				pDoc->m_CommunicationInfo.ucMode == SERIAL   //����
			  )    
			{
				pBuf->wWaitTime1 = (WORD)(200*1.0);
				pBuf->wWaitTime2 = (WORD)(1000*1.0);
			}
			else 
			{
				pBuf->wWaitTime1 = (WORD)(200*2.0);
				pBuf->wWaitTime2 = (WORD)(1000*2.0);
			}	
		}
	}
	
	no = pDoc->m_ucNo;
//	char ucTemp[256];
	//sprintf(ucTemp,"ucCommand = %.2X",ucCommand);
	//AfxMessageBox(ucTemp);
	switch(ucCommand)
	{
	case 0x03://�����ռ�
		len = 4;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		break;
	case 0x04://���������
		len = 9;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		Buffer[4] = 0x20;
		Buffer[5] = 0xd0;
		Buffer[6] = 0x10;
		memcpy(Buffer+7,Data,nLen);
		break;
	case 0xBB://�ռ���ʷ���� --- ����
		len = 6;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		memcpy(Buffer+4,Data,nLen);
		break;
	case 0xDE://�ռ���ʷ���� --- ����
		len = 6;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		memcpy(Buffer+4,Data,nLen);
		break;
	case 0x8A://�ռ���ʷ���� --- ����
		len = 6;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		memcpy(Buffer+4,Data,nLen);
		break;
	default:
		len = 4;
		ucCommand = 0x03;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[pDoc->m_ucNo].ucRegNo,4);
		break;
	}
	retLen         = PubCommands(addr,ucCommand,len,Buffer,level,level_Array);
	pBuf->ucMode   = 0;   //���ݷ���
	pBuf->wLength  = retLen;
	memcpy(pBuf->ucBuffer,Buffer,retLen);
	return RET_OK;
}



//���ݽ������
int _stdcall UpPacketBuffer(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	WORD wTaskID;
	if(nAllocateMemoryFlag != 1)
		return RET_ERROR;

	wTaskID = pDoc->m_TaskInfo.wIDNo;
	if(wTaskID == 0) //�����ռ�������ȷ��
	{
		switch(pDoc->m_TaskInfo.ucCommandArray[0]) //�����ռ�
		{
		case 0x03://�����ռ�
			CollectRawDataProcess(pDoc,pBuffer); //ԭʼ�����ռ�
			break;
		case 0x04://����ȷ��
			ConfirmRawDataProcess(pDoc,pBuffer);
			//Sleep(500);
			break;
		default:
			CollectRawDataProcess(pDoc,pBuffer);
			break;
		}
	}
	if(wTaskID == 1) //�ռ���ʷ���ݽ���
		CollectHistoryDealData_Process(pDoc,pBuffer);
	if(wTaskID == 2) //�ռ���ʷ��������
		CollectHistoryCheckInData_Process(pDoc,pBuffer);

	return RET_OK;
}



