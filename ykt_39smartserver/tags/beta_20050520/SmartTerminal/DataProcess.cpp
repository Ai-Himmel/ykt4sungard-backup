//ԭʼ���ݴ�������
#include "stdafx.h"
#include "SmartTerminal.h"
void Process_RawData_BaseMarkValue(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
int  Process_Lport_State(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
void Process_Lport_RawCollectData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
void Porcess_SFJData(  TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo);
void Process_StateData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo); //������������
void Process_JSBData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo);
void Process_GSJData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE ucNo);
/*************�ռ���������****************************
 * ԭʼ�����ռ���������
 * ���ߣ�����
 * �������ڣ�2004��1��7��
*******************************************************/

void CollectRawDataProcess(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int crcFlag,i;
	unsigned char out[3],ucAddr,ucNo;
	FILE *fp;
	char filename[512],chTemp[512];
	CTime tm = CTime::GetCurrentTime();
	
	ucNo = pDoc->m_ucNo;	  //��ǰͨѶ�˿ں�
	if(pBuffer->ucMode == 2)  //���յ�����
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
				Process_RawData_BaseMarkValue(pDoc,pBuffer); //�������ݷ���Markֵ����ԭʼ����
				return;
			}
			else//�������������������� Ŀǰ����������ʱ�����뿼��
			{
				GetCurrentDirectory(512,chTemp);
				sprintf(filename,"%s\\log\\�쳣��Ϣ\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",chTemp,
					    pDoc->m_TerminalInfo[ucNo].ucIDNo[0],pDoc->m_TerminalInfo[ucNo].ucIDNo[1],	
					    pDoc->m_TerminalInfo[ucNo].ucIDNo[2],pDoc->m_TerminalInfo[ucNo].ucIDNo[3],
				        tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");													   
				sprintf(chTemp,"%.2d��%d��%.2d�� %.2dʱ%d��%.2d�� ԭʼ���ݻ��Ŵ�,����Ϊ:\n ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
																     	                     tm.GetHour(),tm.GetMinute(),tm.GetSecond());
				fputs(chTemp,fp);
				for(i=0;i<pBuffer->wLength;i++)
				{
					sprintf(chTemp,"%.2X",pBuffer->ucBuffer[i]);
					fputs(chTemp,fp);
				}
				fputs("\n",fp);
				fclose(fp);
				goto CollectRawData1;//�����ռ�;���⣬��ʼ�ճ��ֻ��Ŵ�Ӧ��δ���
			}
		}
		else//CRC����
		{
			GetCurrentDirectory(512,chTemp);
			sprintf(filename,"%s\\log\\�쳣��Ϣ\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",chTemp,
				pDoc->m_TerminalInfo[ucNo].ucIDNo[0],pDoc->m_TerminalInfo[ucNo].ucIDNo[1],	
				pDoc->m_TerminalInfo[ucNo].ucIDNo[2],pDoc->m_TerminalInfo[ucNo].ucIDNo[3],
				tm.GetYear(),tm.GetMonth(),tm.GetDay());
			fp = fopen(filename,"a+");													   
			sprintf(chTemp,"%.2d��%d��%.2d�� %.2dʱ%d��%.2d�� ԭʼ����CRC��,����Ϊ:\n ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
																     	                tm.GetHour(),tm.GetMinute(),tm.GetSecond());
			fputs(chTemp,fp);
			for(i=0;i<pBuffer->wLength;i++)
			{
				sprintf(chTemp,"%.2X",pBuffer->ucBuffer[i]);
				fputs(chTemp,fp);
			}
			fputs("\n",fp);
			fclose(fp);
			goto CollectRawData1;
		}
	}
	else if(pBuffer->ucMode == 3) //δ���յ�����
	{
		//֪ͨ��ʾ����
		pDoc->m_wNoReponseTime++;
	}
	
CollectRawData1:
	if(pDoc->m_TaskInfo.ucMode == 0) //Ĭ������
	{
		//�����ռ�
		if(pDoc->m_bNetPar == true)//���ͽṹ�������ռ�
		{	
			pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		else //(pDoc->m_ucNetPar == 1)//���߽ṹ
		{
			pDoc->m_ucNo++;
			if(pDoc->m_ucNo == pDoc->m_ucTotalNo ) //����ն���
				pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
	}
}
/*********************************************************
  * ����˵���������ռ�ʱ�������ݷ���Markֵ����ԭʼ����
  * ���ߣ�    ����
  *�������ڣ�2004��1��
*********************************************************/
void Process_RawData_BaseMarkValue(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int  retCode;
	BYTE ucMark,ucNo,out[3];
	
	ucNo = pDoc->m_ucNo;
	
	ucMark = pBuffer->ucBuffer[2];
	switch(ucMark)
	{
	case 0x00: //������
		if(pDoc->m_TerminalInfo[ucNo].ucType[0] == 53 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 01)//������
		{
			retCode = Process_Lport_State(pDoc,pBuffer);//����Lport�˿�״̬
			if(retCode == 1)//������״̬��Ҫ����
			{
				Process_Lport_RawCollectData(pDoc,pBuffer);//����Lportԭʼ��������
				return;
			}
			else
			{
				//��������״̬
				return;
			}
		}
		//����Ӧ�û��д��������������ʹ���
		//else if(pDoc->m_TerminalInfo[ucNo].ucMacType[0] == 01 && pDoc->m_TerminalInfo[ucNo].ucMacType[1] == 21)//��ʱ��
		//{
		//
		//}
		//else 
		//�շѻ�
		break;
	case 0x0a://������
		if(pDoc->m_TaskInfo.ucMode == 0) //Ĭ������
		{
			//�����ռ�
			if(pDoc->m_bNetPar == true)//���ͽṹ�������ռ�
			{	
				//AfxMessageBox("���ݼ����ռ�");
				pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
			else //(pDoc->m_ucNetPar == 1)//���߽ṹ
			{
				pDoc->m_ucNo++;
				if(pDoc->m_ucNo == pDoc->m_ucTotalNo)
					pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
		}
		break;
	case 0x01://��д����������
		break;
	case 0x02://ʱ�Ӵ���
		break;
	case 0x03://FLASH��������
		break;
	case 0x04://������
		break;
	case 0x05://��ˮ�Ŵ�
		break;
	case 0x07://������
		break;
	case 0x08://�����������
		break;
	case 0x09://�ظ�����
		break;
	case 0x0b://ע��Ŵ�
		break;
	case 0x0c://δ����
		break;
	case 0x0d://����ǩ��
		break;
	case 0x0E://�������汾����
		break;
	case 0x17://����������
		break;
	default:
		break;
	}
	if(pDoc->m_TaskInfo.ucMode == 0) //Ĭ������
	{
		//�����ռ�
		if(pDoc->m_bNetPar == true)//���ͽṹ�������ռ�
		{	
			pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		else //���߽ṹ
		{
			pDoc->m_ucNo++;
			if(pDoc->m_ucNo == pDoc->m_ucTotalNo)
				pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
	}
}

/*******************************************************************
* ����˵��������LPORT������״̬��Ϣ
* ���ߣ�    ����
* ��������: 2004��1��9��
* ����ֵ��  0:�����ռ�����
            1:������
			2:������״̬��Ҫ����
******************************************************************/
int Process_Lport_State(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
		
	BYTE  ucPortTotalNo,ucTemp,ucVer,ucState;
	unsigned char out[3];
	char chTemp[512];
	CTime tm = CTime::GetCurrentTime();
	//FILE *fp;
	
	//AfxMessageBox("3");
	ucVer         = pBuffer->ucBuffer[4];//�汾
	ucState       = pBuffer->ucBuffer[5];//״̬
	ucPortTotalNo = pBuffer->ucBuffer[6];//�˿�������
	
	GetCurrentDirectory(512,chTemp);
	//sprintf(filename,"%s//log//LPORT%.2X%.2X%.2X%.2X_ %.2d%.2d%.2d�˿�״̬.txt",chTemp,
	//	pDoc->m_TerminalInfo[0].ucIDNo[0],pDoc->m_TerminalInfo[0].ucIDNo[1],
	//	pDoc->m_TerminalInfo[0].ucIDNo[2],pDoc->m_TerminalInfo[0].ucIDNo[3],
	//	tm.GetYear(),tm.GetMonth(),tm.GetDay());
	//fp = fopen(filename,"a+");
	//sprintf(chTemp,"%.2d��%.2d��%.2d��%.2dʱ%.2d��%.2d��:\n",tm.GetYear(),tm.GetMonth(),
	//														  tm.GetDay(), tm.GetHour(),
	//														  tm.GetMinute(),tm.GetSecond());
	//fputs(chTemp,fp);
	for(ucTemp=0;ucTemp<ucPortTotalNo;ucTemp++)//����״ֵ̬�����ж��ִ���ҵ������
	{
		//sprintf(chTemp," L%.2d״̬=%.2X",ucTemp+1,pBuffer->ucBuffer[7+ucTemp]);
		//fputs(chTemp,fp);
		switch(pBuffer->ucBuffer[7+ucTemp])
		{
		case 0x0a:
			//������
			break;
		case 0x0b:
			//ע��Ŵ�
			break;
		case 0x0d:
			//����ǩ��
			break;
		default:
			break;
		}
	}
	//fputs("\n",fp);
	//fclose(fp);
	if(ucState == 0x0a) //������
	{
		if(pDoc->m_TaskInfo.ucMode == 0) //Ĭ������
		{	
			//�����ռ�
			if(pDoc->m_bNetPar == true)//���ͽṹ�������ռ�
			{	
				pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
			}
			else //(pDoc->m_ucNetPar == 1)//���߽ṹ
			{
				pDoc->m_ucNo++;
				if(pDoc->m_ucNo == pDoc->m_ucTotalNo ) //����ն���
					pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
			}
		}
		return 0;
	}
	else
	{
		//AfxMessageBox("����������");
		return 1;
	}
}

//*******1.2 �����������������************************************//
void Process_Lport_RawCollectData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
		
	BYTE  ucPortTotalNo,out[3],ucNo;
	
	ucPortTotalNo = pBuffer->ucBuffer[6];
	ucNo          = pBuffer->ucBuffer[7+ucPortTotalNo];
	if(pBuffer->ucBuffer[8+ucPortTotalNo] == 0x01) //��������
	{
		if( (pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 01) || //��ֵ��
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 26) || //�շѻ�		
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 28) || //���ػ� 
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 30) || //����� 
		    (pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 32) || //�ϻ�������
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 34) || //��ԡ�����
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 40) || //��Ʊ��
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 01 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 30) || //���ʶ���
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 01 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 40) //��Ʊ��
		  )	
			//(pDoc->m_TerminalInfo[ucNo].
		{
			Porcess_SFJData(pDoc,pBuffer,&pBuffer->ucBuffer[9+ucPortTotalNo],ucNo); 
			return;
		}
		if( (pDoc->m_TerminalInfo[ucNo].ucType[0] == 01 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 21) ||//��ʱ������
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 55 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 01) //��ʱ������
          ) 
		{
			Process_JSBData(pDoc,pBuffer,&pBuffer->ucBuffer[9+ucPortTotalNo],ucNo);
			return;
		}
		if( (pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 24) ) //��ʧ��
		{
			Process_GSJData(pDoc,pBuffer,&pBuffer->ucBuffer[9+ucPortTotalNo],ucNo);
			return;
		}
	}
	else if(pBuffer->ucBuffer[8+ucPortTotalNo] == 0x17) //��������
	{
		Process_StateData(pDoc,pBuffer,&pBuffer->ucBuffer[9+ucPortTotalNo],ucNo);
		return;
	}
	else if(pBuffer->ucBuffer[8+ucPortTotalNo] == 0x1b) //��������
	{
	}
	else//δ֪����
	{
		if(pDoc->m_TaskInfo.ucMode == 0) //Ĭ������
		{	
			//AfxMessageBox("�ռ���������δ֪����");
			//�����ռ�
			if(pDoc->m_bNetPar  == TRUE)//���ͽṹ�������ռ�
			{	
				pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
			else //(pDoc->m_ucNetPar == 1)//���߽ṹ
			{
				pDoc->m_ucNo++;
				if(pDoc->m_ucNo == pDoc->m_ucTotalNo)
					pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
		}
	}
}

/***************************************************************************************
 *����˵��: �����շѻ�ԭʼ����
 *���ߣ�    ����
 *�������ڣ�2004��1��8��
 *����˵����
            Buffer ----ԭʼ��������
			PortNo ----pDoc->m_TerminalInfo[PortNo]�ն�����ָ��
***************************************************************************************/
void Porcess_SFJData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo)
{
	
	CTime tm=CTime::GetCurrentTime();
	FILE  *fp;
	char  filename[512],temp[512];
	int   crcFlag;
	unsigned char ucFlowNo[2],out[3];
	WORD  wFlowNo;
	
	GetCurrentDirectory(512,temp);
	sprintf(filename,"%s\\log\\��������\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d��%.2d��%.2d�� %.2dʱ%.2d��%.2d���ռ���������\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
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
	ucFlowNo[0] = Buffer[6];
	ucFlowNo[1] = Buffer[7];	
	
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
	{
		wFlowNo = ((WORD)(ucFlowNo[0])*256)+(WORD)ucFlowNo[1];
		if(wFlowNo == pDoc->m_TerminalInfo[PortNo].wEDFlowNo)//�����ˮ�ŵ���������ˮ��
		{
			//�����ݿ�дһ�ʼ�¼
			if(wFlowNo == 0xFFFF)
				pDoc->m_TerminalInfo[PortNo].wEDFlowNo =0;
			else
				pDoc->m_TerminalInfo[PortNo].wEDFlowNo=pDoc->m_TerminalInfo[PortNo].wEDFlowNo + 1;
			if(pDoc->m_bNetPar == TRUE)//���ͽṹ
			{
				pDoc->m_ucNo = 0;
			}
			pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
			pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
			pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
			pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
			BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
			return;	
		}
		else if(pDoc->m_TerminalInfo[PortNo].wEDFlowNo < wFlowNo)//������ˮ��С��ʵ��������ˮ��
		{
			if(wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo <= 10240) //��������������ˮ��100��ʵ��500 //�ռ���ʷ����
			{
				GetCurrentDirectory(512,temp);
				sprintf(filename,"%s\\log\\�쳣��Ϣ\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X���ռ���ʷ��������:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wEDFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //��ǰ�����˿�
				pDoc->m_TaskInfo.wIDNo = 1; //����ID
				pDoc->m_TaskInfo.ucMode = 1; //�ƴ�����
				pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo+1; //���������ܴ���
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //��ǰ����Ϊ0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//�����ܴ���
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�� 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //�ռ���ʷ����
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
			else //����100 ʵ�� 65530 �ظ��ռ�
			{
				if(pDoc->m_bNetPar == TRUE)//���ͽṹ
				{
					pDoc->m_ucNo = 0;
				}	
				pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
				pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
		}
		else ////������ˮ�Ŵ���ʵ��������ˮ��
		{
			if(65536 - wFlowNo + pDoc->m_TerminalInfo[PortNo].wEDFlowNo <10240) //����65530 ʵ�� 100
			{
				GetCurrentDirectory(512,temp);
				sprintf(filename,"%s\\log\\�쳣��Ϣ\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X���ռ���ʷ��������:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wEDFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //��ǰ�����˿�
				pDoc->m_TaskInfo.wIDNo = 1; //����ID
				pDoc->m_TaskInfo.ucMode = 1; //�ƴ�����
				pDoc->m_TaskInfo.wTaskTotalNo = 65536-wFlowNo+pDoc->m_TerminalInfo[PortNo].wEDFlowNo; //���������ܴ���
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //��ǰ����Ϊ0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//�����ܴ���
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�� 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //�ռ���ʷ����
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
			else //����100 ʵ�� 90�ظ��ռ�
			{
				if(pDoc->m_bNetPar == TRUE)//���ͽṹ
				{
					pDoc->m_ucNo = 0;
				}	
				pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
				pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
		}
	}
	else //  CRC����ȷ �����ռ�
	{
		wFlowNo = pDoc->m_TerminalInfo[PortNo].wEDFlowNo;
		if(wFlowNo == 0xFFFF )
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo = 0;
		else
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo++;
		if(pDoc->m_bNetPar == TRUE)//���ͽṹ
		{
			pDoc->m_ucNo = 0;
		}	
		pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
		pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
		pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
		return;
	}
}

/***************************************************************************************
 *����˵��: �����ն˻���������
 *���ߣ�    ����
 *�������ڣ�2004��2��6��
 *����˵����
            Buffer ----ԭʼ��������
			PortNo ----pDoc->m_TerminalInfo[PortNo]�ն�����ָ��
***************************************************************************************/
void Process_StateData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo)
{
	CTime tm=CTime::GetCurrentTime();
	FILE  *fp;
	char  filename[512],temp[512];
	int   crcFlag;
	unsigned char ucFlowNo[2],out[3];
	WORD  wFlowNo;
	
	GetCurrentDirectory(512,temp);
	sprintf(filename,"%s\\log\\��������\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d��%.2d��%.2d�� %.2dʱ%.2d��%.2d���ռ���������\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fputs(temp,fp);
	sprintf(temp,"ע���          0x%.2X%.2X%.2X%.2X\n",Buffer[0],Buffer[1],Buffer[2],Buffer[3]);fputs(temp,fp);
	sprintf(temp,"ͨ�Ű汾        0x%.2X\n",Buffer[4]);fputs(temp,fp);
	sprintf(temp,"����ԭ��        0x%.2X\n",Buffer[5]);fputs(temp,fp);
	sprintf(temp,"������ˮ        %d\n",  Buffer[6]*256+Buffer[7]);fputs(temp,fp);
	sprintf(temp,"����ʱ��        %.2d%.2d%.2d-%.2d%.2d%.2d\n",Buffer[8],Buffer[9],Buffer[10],
		                                                      Buffer[11],Buffer[12],Buffer[13]);
	fputs(temp,fp);
	sprintf(temp,"��ʼ��ˮ��      %d\n",Buffer[14]*256+Buffer[15]);fputs(temp,fp);
	sprintf(temp,"������ˮ��      %d\n",Buffer[16]*256+Buffer[17]);fputs(temp,fp);
	sprintf(temp,"���������ܱ�����%d\n",Buffer[18]*256+Buffer[19]);fputs(temp,fp);
	sprintf(temp,"���������ܽ��  %d\n",Buffer[20]+Buffer[21]*256+Buffer[22]*65536);fputs(temp,fp);
	sprintf(temp,"���������ܱ�����%d\n",Buffer[23]*256+Buffer[24]);fputs(temp,fp);
	sprintf(temp,"���������ܽ�%d\n",Buffer[25]+Buffer[26]*256+Buffer[27]*65536);fputs(temp,fp);
	sprintf(temp,"�쳣�����ܱ�����%d\n",Buffer[28]*256+Buffer[29]);fputs(temp,fp);
	sprintf(temp,"�쳣�����ܽ�%d\n",Buffer[30]+Buffer[31]*256+Buffer[32]*65536);fputs(temp,fp);	
	sprintf(temp,"���������ܱ���  %d\n",Buffer[33]*256+Buffer[34]);fputs(temp,fp);
	sprintf(temp,"���ʱ�ǡ�����  0x%.2X\n",Buffer[35]);fputs(temp,fp);
	sprintf(temp,"CRC=%.2X%.2X",Buffer[36],Buffer[37]); fputs(temp,fp);
	crcFlag = calc_crc16(38,Buffer,out);
	if(crcFlag == 0)
		fputs("��ȷ\n",fp);
	else
		fputs("����\n",fp);
	fclose(fp);
	ucFlowNo[0] = Buffer[6];	ucFlowNo[1] = Buffer[7];
	wFlowNo = Buffer[6]*256+Buffer[7];
	if(crcFlag == 0)//��ȷ
	{
		if(wFlowNo == pDoc->m_TerminalInfo[PortNo].wECFlowNo)//�����ˮ�ŵ���������ˮ��
		{
			if(wFlowNo == 0xFFFF)
				pDoc->m_TerminalInfo[PortNo].wECFlowNo = 0;
			else
				pDoc->m_TerminalInfo[PortNo].wECFlowNo += 1;

			if(pDoc->m_bNetPar == true) //����
			{
				pDoc->m_ucNo = 0;
			}

			pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
			pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
			pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
			pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
			BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);

			return;	

		}
		else if(wFlowNo > pDoc->m_TerminalInfo[PortNo].wECFlowNo) //�ϴ���ˮ�Ŵ���������ˮ��
		{
			//if(65536-wFlowNo + pDoc->m_TerminalInfo[PortNo].wECFlowNo <= 128 ) //���� 10 �ϴ� 100 ��ʷ�ռ�
			if(wFlowNo - pDoc->m_TerminalInfo[PortNo].wECFlowNo <= 128 )
			{
				//AfxMessageBox("�ռ���ʷ��������");
				sprintf(filename,"%s\\log\\�쳣��Ϣ\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X���ռ���ʷ��������:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						wFlowNo,pDoc->m_TerminalInfo[PortNo].wECFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //��ǰ�����˿�
				pDoc->m_TaskInfo.wIDNo = 2; //����ID
				pDoc->m_TaskInfo.ucMode = 1; //�ƴ�����
				pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wECFlowNo+1; //���������ܴ���
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //��ǰ����Ϊ0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//�����ܴ���
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�� 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0x8A; //�ռ���ʷ����
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wECFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wECFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				
				return;	
			}
			else // ���� 10 ʵ�� 5000 �ظ��ռ�
			{
				if(pDoc->m_bNetPar == true) //����
				{
					pDoc->m_ucNo = 0;
				}
				pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
				pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;		
			}
		}
		else //�ϴ���ˮ��С��������ˮ�� ��--10 ��100  ��65530 ���� 10
		{
			if(pDoc->m_TerminalInfo[PortNo].wECFlowNo - wFlowNo <= 128) //���� 100 �ϴ� 10 �ظ��ռ�
			{
				if(pDoc->m_bNetPar == true) //����
				{
					pDoc->m_ucNo = 0;
				}
				pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
				pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;		
			}
			else //���� 10 �ϴ� 65530 ��ʷ�ռ�
			{
				sprintf(filename,"%s\\log\\�쳣��Ϣ\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X���ռ���ʷ��������:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wECFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);

				pDoc->m_ucNo = PortNo; //��ǰ�����˿�
				pDoc->m_TaskInfo.wIDNo = 2; //����ID
				pDoc->m_TaskInfo.ucMode = 1; //�ƴ�����
				pDoc->m_TaskInfo.wTaskTotalNo = 65536-wFlowNo+pDoc->m_TerminalInfo[PortNo].wECFlowNo; //���������ܴ���
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //��ǰ����Ϊ0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//�����ܴ���
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�� 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0x8A; //�ռ���ʷ����
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wECFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wECFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
			}

		}
		//AfxMessageBox("��ȷ");

	}
	else//CRC����ȷ
	{
		AfxMessageBox("����");
		wFlowNo = pDoc->m_TerminalInfo[PortNo].wECFlowNo;
		if(wFlowNo == 0xFFFF )
			pDoc->m_TerminalInfo[PortNo].wECFlowNo = 0;
		else
			pDoc->m_TerminalInfo[PortNo].wECFlowNo++;
		if(pDoc->m_bNetPar == TRUE)//���ͽṹ
		{
			pDoc->m_ucNo = 0;
		}	
		pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
		pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
		pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
		//AfxMessageBox("����");
		return;	
	}
	return;
}

////////////////20040217����Ϊֹ ��������������������******************************/
void Process_JSBData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo)
{
	CTime tm=CTime::GetCurrentTime();
	FILE  *fp;
	char  filename[512],temp[512];
	int   crcFlag;
	unsigned char ucFlowNo[2],out[3];
	WORD  wFlowNo;
	
	GetCurrentDirectory(512,temp);
	sprintf(filename,"%s\\log\\��������\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d��%.2d��%.2d�� %.2dʱ%.2d��%.2d���ռ���������\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fputs(temp,fp);
	sprintf(temp,"ע���   %.2X%.2X%.2X%.2X\n", Buffer[0],Buffer[1],Buffer[2],Buffer[3]);	fputs(temp,fp);	
	sprintf(temp,"ͨ�Ű汾 %.2X\n",Buffer[4]);												fputs(temp,fp);
	sprintf(temp,"����ԭ�� %.2X\n",Buffer[5]);												fputs(temp,fp);
	sprintf(temp,"������ˮ %d\n",  Buffer[6]*256+Buffer[7]);								fputs(temp,fp);
	sprintf(temp,"����     0X%.2X%.2X%.2X%.2X%.2X\n",Buffer[8],Buffer[9],Buffer[10],Buffer[11],Buffer[12]);				fputs(temp,fp);
	sprintf(temp,"����ʱ�� %.2d%.2d%.2d-%.2d%.2d%.2d ����%d\n",Buffer[13],Buffer[14],Buffer[15],
														Buffer[16],Buffer[17],Buffer[18],Buffer[19]);	fputs(temp,fp);
	sprintf(temp,"����ģʽ���� %d\n",Buffer[20]);						fputs(temp,fp);
	sprintf(temp,"��������     %d\n",Buffer[21]);			fputs(temp,fp);
	sprintf(temp,"���ʹ���     %d\n",Buffer[22]);			fputs(temp,fp);
	sprintf(temp,"��Ӧͷ���   %d\n",Buffer[23]);			fputs(temp,fp);
	sprintf(temp,"���°���   %d\n",Buffer[24]);			fputs(temp,fp);
	sprintf(temp,"���ױ�� %.2X\n", Buffer[25]);			fputs(temp,fp);
	sprintf(temp,"CRC=%.2X%.2X ",   Buffer[26],Buffer[27]);									fputs(temp,fp);
	ucFlowNo[0] = Buffer[6];
	ucFlowNo[1] = Buffer[7];	
	
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
	{
		wFlowNo = ((WORD)(ucFlowNo[0])*256)+(WORD)ucFlowNo[1];
		if(wFlowNo == pDoc->m_TerminalInfo[PortNo].wEDFlowNo)//�����ˮ�ŵ���������ˮ��
		{
			//�����ݿ�дһ�ʼ�¼
			if(wFlowNo == 0xFFFF)
				pDoc->m_TerminalInfo[PortNo].wEDFlowNo =0;
			else
				pDoc->m_TerminalInfo[PortNo].wEDFlowNo=pDoc->m_TerminalInfo[PortNo].wEDFlowNo + 1;
			if(pDoc->m_bNetPar == TRUE)//���ͽṹ
			{
				pDoc->m_ucNo = 0;
			}
			pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
			pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
			pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
			pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
			BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
			return;	
		}
		else if(pDoc->m_TerminalInfo[PortNo].wEDFlowNo < wFlowNo)//������ˮ��С��ʵ��������ˮ��
		{
			if(wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo <= 10240) //��������������ˮ��100��ʵ��500 //�ռ���ʷ����
			{
				GetCurrentDirectory(512,temp);
				sprintf(filename,"%s\\log\\�쳣��Ϣ\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X���ռ���ʷ��������:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wEDFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //��ǰ�����˿�
				pDoc->m_TaskInfo.wIDNo = 1; //����ID
				pDoc->m_TaskInfo.ucMode = 1; //�ƴ�����
				pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo+1; //���������ܴ���
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //��ǰ����Ϊ0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//�����ܴ���
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�� 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //�ռ���ʷ����
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
			else //����100 ʵ�� 65530 �ظ��ռ�
			{
				if(pDoc->m_bNetPar == TRUE)//���ͽṹ
				{
					pDoc->m_ucNo = 0;
				}	
				pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
				pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
		}
		else ////������ˮ�Ŵ���ʵ��������ˮ��
		{
			if(65536 - wFlowNo + pDoc->m_TerminalInfo[PortNo].wEDFlowNo <10240) //����65530 ʵ�� 100
			{
				GetCurrentDirectory(512,temp);
				sprintf(filename,"%s\\log\\�쳣��Ϣ\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X���ռ���ʷ��������:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wEDFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //��ǰ�����˿�
				pDoc->m_TaskInfo.wIDNo = 1; //����ID
				pDoc->m_TaskInfo.ucMode = 1; //�ƴ�����
				pDoc->m_TaskInfo.wTaskTotalNo = 65536-wFlowNo+pDoc->m_TerminalInfo[PortNo].wEDFlowNo; //���������ܴ���
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //��ǰ����Ϊ0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//�����ܴ���
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�� 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //�ռ���ʷ����
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������������Դ���
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
			else //����100 ʵ�� 90�ظ��ռ�
			{
				if(pDoc->m_bNetPar == TRUE)//���ͽṹ
				{
					pDoc->m_ucNo = 0;
				}	
				pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
				pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
				pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
		}
	}
	else //  CRC����ȷ �����ռ�
	{
		wFlowNo = pDoc->m_TerminalInfo[PortNo].wEDFlowNo;
		if(wFlowNo == 0xFFFF )
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo = 0;
		else
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo++;
		if(pDoc->m_bNetPar == TRUE)//���ͽṹ
		{
			pDoc->m_ucNo = 0;
		}	
		pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
		pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
		pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
		return;
	}
}

void Process_GSJData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo)
{
	CTime tm=CTime::GetCurrentTime();
	FILE  *fp;
	char  filename[512],temp[512];
	int   crcFlag;
	unsigned char ucFlowNo[2],out[3];
	WORD  wFlowNo;
	
	GetCurrentDirectory(512,temp);
	sprintf(filename,"%s\\log\\��������\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d��%.2d��%.2d�� %.2dʱ%.2d��%.2d���ռ���������\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fputs(temp,fp);
	sprintf(temp,"ע���   %.2X%.2X%.2X%.2X\n", Buffer[0],Buffer[1],Buffer[2],Buffer[3]);	fputs(temp,fp);	
	sprintf(temp,"ͨ�Ű汾 %.2X\n",Buffer[4]);												fputs(temp,fp);
	sprintf(temp,"����ԭ�� %.2X\n",Buffer[5]);												fputs(temp,fp);
	sprintf(temp,"������ˮ %d\n",  Buffer[6]*256+Buffer[7]);								fputs(temp,fp);
	sprintf(temp,"��ʾ���� %.2X%.2X%.2X%.2X%.2X\n",Buffer[8],Buffer[9],Buffer[10],Buffer[11],Buffer[12]);				fputs(temp,fp);
	sprintf(temp,"������������ %.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X\n",
		Buffer[13],Buffer[14],Buffer[15],Buffer[16],
		Buffer[17],Buffer[18],Buffer[19],Buffer[20]);	fputs(temp,fp);
	sprintf(temp,"����ʱ�� %.2d��%.2d��%.2dʱ%.2d��\n",Buffer[21],Buffer[22],Buffer[23],Buffer[24]);		fputs(temp,fp);
	sprintf(temp,"���ױ�� %.2X\n", Buffer[25]);			fputs(temp,fp);
	sprintf(temp,"CRC=%.2X%.2X ",   Buffer[26],Buffer[27]);									fputs(temp,fp);
	ucFlowNo[0] = Buffer[6];
	ucFlowNo[1] = Buffer[7];	
	
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
	{
		wFlowNo = ((WORD)(ucFlowNo[0])*256)+(WORD)ucFlowNo[1];
		pDoc->m_TerminalInfo[PortNo].wEDFlowNo = wFlowNo;
		if(pDoc->m_bNetPar == TRUE)//���ͽṹ
		{
			pDoc->m_ucNo = 0;
		}
		//һ��δ�������
		pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
		pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
		pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
		return;	
	}
	else //  CRC����ȷ �����ռ�
	{
		wFlowNo = pDoc->m_TerminalInfo[PortNo].wEDFlowNo;
		if(wFlowNo == 0xFFFF )
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo = 0;
		else
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo++;
		if(pDoc->m_bNetPar == TRUE)//���ͽṹ
		{
			pDoc->m_ucNo = 0;
		}	
		pDoc->m_TaskInfo.ucMode = 0;//Ĭ������
		pDoc->m_TaskInfo.wIDNo  = 0;//����ID�ţ�0----���������ռ���ȷ��
		pDoc->m_TaskInfo.ucERetryNo = 3;//�������Դ���Ϊ3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//��ǰ�������Դ��� 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//����������Ϊ1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//�����ֵ�ǰ�������
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
		return;
	}

}



//////////************************����ȷ������************************/////
void ConfirmRawDataProcess(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int crcFlag,i;
	unsigned char out[3],ucAddr,ucNo;
	FILE *fp;
	char filename[512],chTemp[512];
	CTime tm = CTime::GetCurrentTime();
	ucNo = pDoc->m_ucNo;	  //��ǰͨѶ�˿ں�
	if(pBuffer->ucMode == 2)  //���յ�����
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
				Sleep(500);
				goto ConFirmData;
			}
			else//��������������������
			{
				
				GetCurrentDirectory(512,chTemp);
				sprintf(filename,"%s\\log\\No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d����",chTemp,
					pDoc->m_TerminalInfo[ucNo].ucIDNo[0],pDoc->m_TerminalInfo[ucNo].ucIDNo[1],	
					pDoc->m_TerminalInfo[ucNo].ucIDNo[2],pDoc->m_TerminalInfo[ucNo].ucIDNo[3],
				    tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");													   
				sprintf(chTemp,"%.2d��%d��%.2d�� %.2dʱ%d��%.2d�� ԭʼ���ݻ��Ŵ�,����Ϊ:\n ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
																     	                     tm.GetHour(),tm.GetMinute(),tm.GetSecond());
				fputs(chTemp,fp);
				for(i=0;i<pBuffer->wLength;i++)
				{
					sprintf(chTemp,"%.2X",pBuffer->ucBuffer[i]);
					fputs(chTemp,fp);
				}
				fputs("\n",fp);
				fclose(fp);
				goto ConFirmData;//�����ռ�;���⣬��ʼ�ճ��ֻ��Ŵ�Ӧ��δ���
			}
		}
		else //CRC����ȷ
		{
			//�����ռ���¼
			goto ConFirmData;
		}
	}
	else if(pBuffer->ucMode == 3) //δ���յ�����
	{
		//֪ͨ��ʾ����
		pDoc->m_wNoReponseTime++;
	}
ConFirmData:
	if(pDoc->m_TaskInfo.ucMode == 0) //Ĭ������
	{
		pDoc->m_TaskInfo.ucCommandTotalNo  = 1;
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
		//�����ռ�
		if(pDoc->m_bNetPar == true)//���ͽṹ�������ռ�
		{	
			pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		else //(pDoc->m_ucNetPar == 1)//���߽ṹ
		{
			pDoc->m_ucNo++;
			if(pDoc->m_ucNo == pDoc->m_ucTotalNo ) //����ն���
				pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
	}
	

	
/*	int crcFlag,i;
	unsigned char out[3],ucAddr,ucNo;
	FILE *fp;
	char filename[256],chTemp[256];
	CTime tm = CTime::GetCurrentTime();
	WORD   wFlowNo;
	ucNo = pDoc->m_ucNo;
	if(pBuffer->ucFlag == 2) //���յ�����
	{
		if(pDoc->wNoReponseTime != 0) //����ͨѶ�ɹ���Ϣ
			pDoc->wNoReponseTime = 0;
		crcFlag = calc_crc16((unsigned char)pBuffer->m_wBufferSize,
			                                pBuffer->m_ucBuffer,out);
		if(crcFlag == 1)//CRC��ȷ
		{
			ucAddr = pBuffer->m_ucBuffer[1];
			if(ucAddr == pDoc->m_TerminalInfo[ucNo].ucMacNo)
			{
				if(pBuffer->m_ucBuffer[2] == 0) //Markֵ
					goto ConFirmRawData1;
				else
					goto ConFirmRawData1;
				
			}
			else//��������������������
			{
				sprintf(filename,"No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d����",pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[0],
																       pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[1],	
																	   pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[2],	
																	   pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[3],
																	   tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");													   
				sprintf(chTemp,"%.2d��%d��%.2d�� %.2dʱ%d��%.2d�� ԭʼ���ݻ��Ŵ�,����Ϊ ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
																	     	             tm.GetHour(),tm.GetMinute(),tm.GetSecond());
				fputs(chTemp,fp);
				for(i=0;i<pBuffer->m_wBufferSize;i++)
				{
					sprintf(chTemp,"%.2X",pBuffer->m_ucBuffer[i]);
					fputs(chTemp,fp);
				}
				fputs("\n",fp);
				fclose(fp);
				goto ConFirmRawData1;
			} 
		}
		else//CRC����
		{
			sprintf(filename,"No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d����",pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[0],
															       pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[1],	
																   pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[2],	
																   pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[3],
																   tm.GetYear(),tm.GetMonth(),tm.GetDay());
			fp = fopen(filename,"a+");													   
			sprintf(chTemp,"%.2d��%d��%.2d�� %.2dʱ%d��%.2d�� ԭʼ����CRC��,����Ϊ ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
																     	             tm.GetHour(),tm.GetMinute(),tm.GetSecond());
			fputs(chTemp,fp);
			for(i=0;i<pBuffer->m_wBufferSize;i++)
			{
				sprintf(chTemp,"%.2X",pBuffer->m_ucBuffer[i]);
				fputs(chTemp,fp);
			}
			fputs("\n",fp);
			fclose(fp);
			goto ConFirmRawData1;
		}
	}
	else if(pBuffer->ucFlag == 3) //δ���յ�����
	{
		//֪ͨ��ʾ����
		pDoc->wNoReponseTime++;
		pDoc->m_TaskInfo.wRetryNo++;
		if(pDoc->m_TaskInfo.wRetryNo <= pDoc->m_TaskInfo.wERetryNo)
		{
			pDoc->m_TaskInfo.wTaskID    = 0;
			pDoc->m_TaskInfo.ucTaskType = 0;
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
			pDoc->m_TaskInfo.wCommandTotalNo = 1;
			pDoc->m_TaskInfo.wCommandStep = 1;
			wFlowNo = pDoc->m_TerminalInfo[pDoc->m_ucPortNo].wEDealNo;
			if( pDoc->m_TerminalInfo[pDoc->m_ucPortNo].wEDealNo == 0)
				wFlowNo = 0xFFFF;
			else
				wFlowNo = pDoc->m_TerminalInfo[pDoc->m_ucPortNo].wEDealNo -1; 
			out[0] = wFlowNo / 256;
			out[1] = wFlowNo % 256;
			BuildTaskBuffer(pDoc,pBuffer,out,2);
			return;
		}
	}
	
ConFirmRawData1:
	pDoc->m_ucPortNo = 0;
	pDoc->m_TaskInfo.wTaskID = 0;
	pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
	pDoc->m_TaskInfo.wCommandTotalNo   = 1;
	pDoc->m_TaskInfo.wCommandStep      = 1;
	pDoc->m_TaskInfo.wERetryNo         = 1;
	pDoc->m_TaskInfo.wRetryNo          = 0;
	pDoc->m_TaskInfo.wRunNo            = 1; //������Ҫ���д���
	
	if(pDoc->m_TaskInfo.ucTaskType == 0) //Ĭ������
	{
		//�����ռ�
		if(pDoc->m_ucNetPar == 0)//���ͽṹ�������ռ�
		{	
			pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		else //(pDoc->m_ucNetPar == 1)//���߽ṹ
		{
			pDoc->m_ucNo++;
			if(pDoc->m_ucNo == pDoc->m_ucTerminalTotalNo)
				pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
	}*/
}
 
