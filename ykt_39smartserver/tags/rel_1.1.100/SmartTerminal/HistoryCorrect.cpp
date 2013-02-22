//��ʷ�����ռ�

#include "stdafx.h"
#include "SmartTerminal.h"

void CollectHistoryData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
void Process_HistoryData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
void Write_SFJData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,unsigned char *Buffer);

//�ռ���ʷ��������
void CollectHistoryDealData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int crcFlag;
	unsigned char ucNo,out[3],ucAddr;
	ucNo = pDoc->m_ucNo;
	if(pBuffer->ucMode == 2) //�����ݷ���
	{
		if(pDoc->m_wNoReponseTime != 0) //�ɲ�ͨѶ��ͨѶ���ڹ涨�Ĵ�����Ӧ����ͨѶ�ɹ���Ϣ
		{
			pDoc->m_wNoReponseTime = 0; //������Ŀǰȱ�ٴ���
		}
		crcFlag = calc_crc16((unsigned char)(pBuffer->wLength),pBuffer->ucBuffer,out);
		if(crcFlag == 1)//CRC��ȷ
		{
			ucAddr = pBuffer->ucBuffer[1];
			if(ucAddr == pDoc->m_TerminalInfo[ucNo].ucMacNo) //������������������
			{
				if(pBuffer->ucBuffer[2] == 0) //��ȷ
					Process_HistoryData(pDoc,pBuffer);
				else //���������
				{
				}
				return;
			}
			else //���Ų��Դ�������
			{
				pDoc->m_ucNo = 0;
				pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
				pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
		}
		else//�������ݰ�CRC���Դ�������
		{
			pDoc->m_ucNo = 0;
			pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
			pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
			pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
			pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		return;
	}
	else //δ�ӵ�����
	{
		pDoc->m_TaskInfo.ucRetryNo++;
		if(pDoc->m_TaskInfo.ucRetryNo == pDoc->m_TaskInfo.ucERetryNo) //���Դ�����
		{
			if(pDoc->m_bNetPar == true) //���ͽṹ
			{
				pDoc->m_ucNo = 0;
				pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
				pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
		}
		else //�����ռ�
		{
			pBuffer->ucMode = 0;
			return;
		}
	}
}

//������ʷ��������
void Process_HistoryData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int PortNo;
	PortNo = pDoc->m_ucNo;
	if( (pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 01) || //��ֵ��
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 26) || //�շѻ�		
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 28) || //���ػ� 
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 30) || //����� 
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 32) || //�ϻ�������
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 34) || //��ԡ�����
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 40) || //��Ʊ��
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 01 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 30) || //���ʶ���
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 01 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 40) //��Ʊ��
	)	
	{
		Write_SFJData_Process(pDoc,pBuffer,&(pBuffer->ucBuffer[4]));
		return;
	}
	if( (pDoc->m_TerminalInfo[PortNo].ucType[0] == 01 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 21) ||//��ʱ������
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 55 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 01) //��ʱ������
      ) 
	{
		//Write_JSBData_Process(pDoc,pBuffer,&(pBuffer->ucBuffer[4]));
		//******************add here
		return;
	}

}

//д�շѻ���������
void Write_SFJData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,unsigned char *Buffer)
{
	unsigned char ucFlowNo[2],out[3];
	CTime tm=CTime::GetCurrentTime();
	FILE  *fp;
	char  filename[512],temp[512];
	int   crcFlag,PortNo;
	WORD  wFlowNo,wFlow1;
	
	PortNo = pDoc->m_ucNo;
	GetCurrentDirectory(512,temp);
	sprintf(filename,"%s\\log\\No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d��ʷ��������.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d��%.2d��%.2d�� %.2dʱ%.2d��%.2d���ռ���ʷ��������\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fputs(temp,fp);
	sprintf(temp,"ע���   %.2X%.2X%.2X%.2X\n", Buffer[0],Buffer[1],Buffer[2],Buffer[3]);	fputs(temp,fp);	
	sprintf(temp,"ͨ�Ű汾 %.2X\n",Buffer[4]);												fputs(temp,fp);
	sprintf(temp,"����ԭ�� %.2X\n",Buffer[5]);												fputs(temp,fp);
	sprintf(temp,"������ˮ %d\n",  Buffer[6]*256+Buffer[7]);								fputs(temp,fp);
	sprintf(temp,"���׿��� %.10d\n",Buffer[8]*65536+Buffer[9]*256+Buffer[10]);				fputs(temp,fp);
	sprintf(temp,"����ʱ�� %.2d%.2d%.2d-%.2d%.2d%.2d\n",Buffer[11],Buffer[12],Buffer[13],
														Buffer[14],Buffer[15],Buffer[16]);	fputs(temp,fp);
	sprintf(temp,"��Ƭ�ۼ�ʹ�ô��� %d\n",Buffer[17]*256+Buffer[18]);						fputs(temp,fp);
	sprintf(temp,"�뿨��� %d��\n",	Buffer[19]+Buffer[20]*256+Buffer[21]*65536);			fputs(temp,fp);
	sprintf(temp,"������� %d��\n", Buffer[22]+Buffer[23]*256+Buffer[24]*65536);			fputs(temp,fp);
	sprintf(temp,"���ױ�� %.2X\n", Buffer[25]);											fputs(temp,fp);
	sprintf(temp,"CRC=%.2X%.2X ",   Buffer[26],Buffer[27]);									fputs(temp,fp);
	
	wFlowNo = (WORD)(Buffer[6]*256)+Buffer[7];
	
	crcFlag = calc_crc16(28,Buffer,out);
	if(crcFlag == 0)
		sprintf(temp,"%s","��ȷ\n");
	else
		sprintf(temp,"%s","����\n");
	fputs(temp,fp);
	fclose(fp);
	
	pDoc->m_TaskInfo.wTaskCurrentNo += 1;
	pDoc->m_TerminalInfo[PortNo].wEDFlowNo = wFlowNo; 
	if(pDoc->m_TaskInfo.wTaskCurrentNo == pDoc->m_TaskInfo.wTaskTotalNo) //��ʷ�����ռ����
	{
		if(pDoc->m_bNetPar == true) //���ͽṹ
		{
			pDoc->m_ucNo            = 0;
			pDoc->m_TaskInfo.wIDNo  = 0; //����IDΪ0 
			pDoc->m_TaskInfo.ucMode = 0; //Ĭ������
			pDoc->m_TaskInfo.wTaskTotalNo = 0;
			pDoc->m_TaskInfo.wTaskCurrentNo =0;
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
			pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
			pDoc->m_TaskInfo.ucRetryNo  = 0;
			BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,0);
			//AfxMessageBox("�ռ���������");
			return;
		}
	}
	else//��ʷ�����ռ�δ���
	{
		pDoc->m_ucNo = PortNo; //��ǰ�����˿�
		pDoc->m_TaskInfo.wIDNo = 1; //����ID
		pDoc->m_TaskInfo.ucMode = 1; //�ƴ�����
		//pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo; //���������ܴ���
//		pDoc->m_TaskInfo.wTaskCurrentNo = 0; //��ǰ����Ϊ0
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//�����ܴ���
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�� 
		pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //�ռ���ʷ����
		pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
		pDoc->m_TaskInfo.ucRetryNo  = 0;
		if(wFlowNo == 0xFFFF)
			wFlow1 = 0;
		else
			wFlow1 = wFlowNo+1;
		//sprintf(temp,"�ռ���ʷ����---%d",wFlow1);
		//AfxMessageBox(temp);
		ucFlowNo[0] = (unsigned char)(wFlow1 / 256);
		ucFlowNo[1] = (unsigned char)(wFlow1 % 256);
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
	}
		
	return;
}

//�ռ�������ʷ����
void CollectHistoryCheckInData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int           crcFlag;
	unsigned char ucNo,out[3],ucAddr,ucFlowNo[2];
	char          cTemp[256];
	CTime tm=CTime::GetCurrentTime();
	FILE  *fp;
	char  filename[512],temp[512];
	WORD  wFlowNo,wFlow1;
	ucNo = pDoc->m_ucNo;

	if(pBuffer->ucMode == 2) //�����ݷ���
	{
		if(pDoc->m_wNoReponseTime != 0) //�ɲ�ͨѶ��ͨѶ���ڹ涨�Ĵ�����Ӧ����ͨѶ�ɹ���Ϣ
		{
			pDoc->m_wNoReponseTime = 0; //������Ŀǰȱ�ٴ���
		}
		crcFlag = calc_crc16((unsigned char)(pBuffer->wLength),pBuffer->ucBuffer,out);
		if(crcFlag == 1)//CRC��ȷ
		{
			ucAddr = pBuffer->ucBuffer[1];
			if(ucAddr == pDoc->m_TerminalInfo[ucNo].ucMacNo) //������������������
			{
				if(pBuffer->ucBuffer[2] == 0) //��ȷ
				{
					GetCurrentDirectory(512,temp);
					sprintf(filename,"%s\\log\\No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d������ʷ����.txt",temp,	
					pDoc->m_TerminalInfo[ucNo].ucIDNo[0],pDoc->m_TerminalInfo[ucNo].ucIDNo[1],
					pDoc->m_TerminalInfo[ucNo].ucIDNo[2],pDoc->m_TerminalInfo[ucNo].ucIDNo[3],
					tm.GetYear(),tm.GetMonth(),tm.GetDay());
					fp = fopen(filename,"a+");
					sprintf(temp,"%.2d��%.2d��%.2d�� %.2dʱ%.2d��%.2d���ռ�������ʷ����\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
					fputs(temp,fp);
					sprintf(temp,"ע���          0x%.2X%.2X%.2X%.2X\n",pBuffer->ucBuffer[4],pBuffer->ucBuffer[5],pBuffer->ucBuffer[6],pBuffer->ucBuffer[7]);fputs(temp,fp);
					sprintf(temp,"ͨ�Ű汾        0x%.2X\n",pBuffer->ucBuffer[8]);fputs(temp,fp);
					sprintf(temp,"����ԭ��        0x%.2X\n",pBuffer->ucBuffer[9]);fputs(temp,fp);
					sprintf(temp,"������ˮ        %d\n",  pBuffer->ucBuffer[10]*256+pBuffer->ucBuffer[11]);fputs(temp,fp);
					sprintf(temp,"����ʱ��        %.2d%.2d%.2d-%.2d%.2d%.2d\n",pBuffer->ucBuffer[12],pBuffer->ucBuffer[13],
						                                                       pBuffer->ucBuffer[14],pBuffer->ucBuffer[15],
																			   pBuffer->ucBuffer[16],pBuffer->ucBuffer[17]);
					fputs(temp,fp);
					sprintf(temp,"��ʼ��ˮ��      %d\n",pBuffer->ucBuffer[18]*256+pBuffer->ucBuffer[19]);fputs(temp,fp);
					sprintf(temp,"������ˮ��      %d\n",pBuffer->ucBuffer[20]*256+pBuffer->ucBuffer[21]);fputs(temp,fp);
					sprintf(temp,"���������ܱ�����%d\n",pBuffer->ucBuffer[22]*256+pBuffer->ucBuffer[23]);fputs(temp,fp);
					sprintf(temp,"���������ܽ��  %d\n",pBuffer->ucBuffer[24]+pBuffer->ucBuffer[25]*256+pBuffer->ucBuffer[26]*65536);fputs(temp,fp);
					sprintf(temp,"���������ܱ�����%d\n",pBuffer->ucBuffer[27]*256+pBuffer->ucBuffer[28]);fputs(temp,fp);
					sprintf(temp,"���������ܽ�%d\n",pBuffer->ucBuffer[29]+pBuffer->ucBuffer[30]*256+pBuffer->ucBuffer[31]*65536);fputs(temp,fp);
					sprintf(temp,"�쳣�����ܱ�����%d\n",pBuffer->ucBuffer[32]*256+pBuffer->ucBuffer[33]);fputs(temp,fp);
					sprintf(temp,"�쳣�����ܽ�%d\n",pBuffer->ucBuffer[34]+pBuffer->ucBuffer[35]*256+pBuffer->ucBuffer[36]*65536);fputs(temp,fp);	
					sprintf(temp,"���������ܱ���  %d\n",pBuffer->ucBuffer[37]*256+pBuffer->ucBuffer[38]);fputs(temp,fp);
					sprintf(temp,"���ʱ�ǡ�����  0x%.2X\n",pBuffer->ucBuffer[39]);fputs(temp,fp);
					sprintf(temp,"CRC=%.2X%.2X",pBuffer->ucBuffer[40],pBuffer->ucBuffer[41]); fputs(temp,fp);
					crcFlag = calc_crc16(38,&(pBuffer->ucBuffer[4]),out);
					if(crcFlag == 0)
						fputs("��ȷ\n",fp);
					else
						fputs("����\n",fp);
					fclose(fp);
					wFlowNo =  pBuffer->ucBuffer[10]*256+pBuffer->ucBuffer[11];
					pDoc->m_TerminalInfo[ucNo].wECFlowNo = wFlowNo; 
					pDoc->m_TaskInfo.wTaskCurrentNo += 1;
					
					if(pDoc->m_TaskInfo.wTaskCurrentNo == pDoc->m_TaskInfo.wTaskTotalNo) //��ʷ�����ռ����
					{
						if(pDoc->m_bNetPar == true) //���ͽṹ
						{
							pDoc->m_ucNo            = 0;
							pDoc->m_TaskInfo.wIDNo  = 0; //����IDΪ0 
							pDoc->m_TaskInfo.ucMode = 0; //Ĭ������
							pDoc->m_TaskInfo.wTaskTotalNo = 0;
							pDoc->m_TaskInfo.wTaskCurrentNo =0;
							pDoc->m_TaskInfo.ucCommandTotalNo = 1;
							pDoc->m_TaskInfo.ucCommandCurrentNo = 0;
							pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
							pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
							pDoc->m_TaskInfo.ucRetryNo  = 0;
							BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,0);
							//AfxMessageBox("�ռ���������");
							return;
						}
					}
					else//��ʷ�����ռ�δ���
					{
						//pDoc->m_ucNo = PortNo; //��ǰ�����˿�
						pDoc->m_TaskInfo.wIDNo = 2; //����ID
						pDoc->m_TaskInfo.ucMode = 1; //�ƴ�����
						//pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo; //���������ܴ���
						//		pDoc->m_TaskInfo.wTaskCurrentNo = 0; //��ǰ����Ϊ0
						pDoc->m_TaskInfo.ucCommandTotalNo = 1;//�����ܴ���
						pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�� 
						pDoc->m_TaskInfo.ucCommandArray[0]  = 0x8A; //�ռ���ʷ����
						pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
						pDoc->m_TaskInfo.ucRetryNo  = 0;
						if(wFlowNo == 0xFFFF)
							wFlow1 = 0;
						else
							wFlow1 = wFlowNo+1;
						sprintf(temp,"�ռ���ʷ����---%d",wFlow1);
						//AfxMessageBox(temp);
						ucFlowNo[0] = (unsigned char)(wFlow1 / 256);
						ucFlowNo[1] = (unsigned char)(wFlow1 % 256);
						BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
					}
		

				}
				else
				{
					sprintf(cTemp,"�ռ���������---����������Markֵ%.2X",pBuffer->ucBuffer[2]);
					AfxMessageBox(cTemp);
					return;
				}
			}
			else //������������Ų�����
			{
				sprintf(cTemp,"�ռ��������� ---- ������������Ų����� = %d",ucAddr);
				AfxMessageBox(cTemp);
				return;
			}
		}
		else //CRC����ȷ
		{
			AfxMessageBox("����������CRC����");
			return;
		}
	}
}
		
	

	

	
	

		
/*	ucFlowNo[0] = Buffer[6];
	ucFlowNo[1] = Buffer[7];	
	/*int i;
	for(i=0;i<28;i++)
	{
		sprintf(temp,"%.2X",Buffer[i]);
		fputs(temp,fp);
	}
	crcFlag = calc_crc16(26,Buffer,out);
	if(crcFlag == 1)
		sprintf(temp,"%s","��ȷ");
	else
		sprintf(temp,"%s","����");//CRC������
	
	crcFlag = calc_crc16(26,Buffer,out);
	if(out[0] == Buffer[26] && out[1] == Buffer[27])
	{
		sprintf(temp,"%s","��ȷ\n");
		crcFlag = 1;
	}
	else
	{
		sprintf(temp,"%s","����\n");
		crcFlag = 0;
	}
	fputs(temp,fp);
	fclose(fp);
	if(crcFlag == 1) //CRC��ȷ

}*/