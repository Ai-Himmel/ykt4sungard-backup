//历史数据收集

#include "stdafx.h"
#include "SmartTerminal.h"

void CollectHistoryData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
void Process_HistoryData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
void Write_SFJData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,unsigned char *Buffer);

//收集历史数据流程
void CollectHistoryDealData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int crcFlag;
	unsigned char ucNo,out[3],ucAddr;
	ucNo = pDoc->m_ucNo;
	if(pBuffer->ucMode == 2) //有数据返回
	{
		if(pDoc->m_wNoReponseTime != 0) //由不通讯到通讯，在规定的次数内应发出通讯成功信息
		{
			pDoc->m_wNoReponseTime = 0; //本部分目前缺少代码
		}
		crcFlag = calc_crc16((unsigned char)(pBuffer->wLength),pBuffer->ucBuffer,out);
		if(crcFlag == 1)//CRC正确
		{
			ucAddr = pBuffer->ucBuffer[1];
			if(ucAddr == pDoc->m_TerminalInfo[ucNo].ucMacNo) //返回数据体机号相符合
			{
				if(pBuffer->ucBuffer[2] == 0) //正确
					Process_HistoryData(pDoc,pBuffer);
				else //错误待处理
				{
				}
				return;
			}
			else //机号不对处理流程
			{
				pDoc->m_ucNo = 0;
				pDoc->m_TaskInfo.ucMode = 0;//默认任务
				pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
				pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
		}
		else//接收数据包CRC不对处理流程
		{
			pDoc->m_ucNo = 0;
			pDoc->m_TaskInfo.ucMode = 0;//默认任务
			pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
			pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
			pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		return;
	}
	else //未接到数据
	{
		pDoc->m_TaskInfo.ucRetryNo++;
		if(pDoc->m_TaskInfo.ucRetryNo == pDoc->m_TaskInfo.ucERetryNo) //重试次数到
		{
			if(pDoc->m_bNetPar == true) //星型结构
			{
				pDoc->m_ucNo = 0;
				pDoc->m_TaskInfo.ucMode = 0;//默认任务
				pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
				pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
		}
		else //重新收集
		{
			pBuffer->ucMode = 0;
			return;
		}
	}
}

//处理历史交易数据
void Process_HistoryData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int PortNo;
	PortNo = pDoc->m_ucNo;
	if( (pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 01) || //增值机
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 26) || //收费机		
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 28) || //车载机 
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 30) || //管理机 
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 32) || //上机上网机
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 34) || //淋浴管理机
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 02 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 40) || //售票机
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 01 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 30) || //身份识别机
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 01 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 40) //检票机
	)	
	{
		Write_SFJData_Process(pDoc,pBuffer,&(pBuffer->ucBuffer[4]));
		return;
	}
	if( (pDoc->m_TerminalInfo[PortNo].ucType[0] == 01 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 21) ||//计时宝数据
		(pDoc->m_TerminalInfo[PortNo].ucType[0] == 55 && pDoc->m_TerminalInfo[PortNo].ucType[1] == 01) //计时宝数据
      ) 
	{
		//Write_JSBData_Process(pDoc,pBuffer,&(pBuffer->ucBuffer[4]));
		//******************add here
		return;
	}

}

//写收费机交易数据
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
	sprintf(filename,"%s\\log\\No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d历史交易数据.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d年%.2d月%.2d日 %.2d时%.2d分%.2d秒收集历史交易数据\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fputs(temp,fp);
	sprintf(temp,"注册号   %.2X%.2X%.2X%.2X\n", Buffer[0],Buffer[1],Buffer[2],Buffer[3]);	fputs(temp,fp);	
	sprintf(temp,"通信版本 %.2X\n",Buffer[4]);												fputs(temp,fp);
	sprintf(temp,"启动原因 %.2X\n",Buffer[5]);												fputs(temp,fp);
	sprintf(temp,"交易流水 %d\n",  Buffer[6]*256+Buffer[7]);								fputs(temp,fp);
	sprintf(temp,"交易卡号 %.10d\n",Buffer[8]*65536+Buffer[9]*256+Buffer[10]);				fputs(temp,fp);
	sprintf(temp,"交易时间 %.2d%.2d%.2d-%.2d%.2d%.2d\n",Buffer[11],Buffer[12],Buffer[13],
														Buffer[14],Buffer[15],Buffer[16]);	fputs(temp,fp);
	sprintf(temp,"卡片累计使用次数 %d\n",Buffer[17]*256+Buffer[18]);						fputs(temp,fp);
	sprintf(temp,"入卡金额 %d分\n",	Buffer[19]+Buffer[20]*256+Buffer[21]*65536);			fputs(temp,fp);
	sprintf(temp,"出卡金额 %d分\n", Buffer[22]+Buffer[23]*256+Buffer[24]*65536);			fputs(temp,fp);
	sprintf(temp,"交易标记 %.2X\n", Buffer[25]);											fputs(temp,fp);
	sprintf(temp,"CRC=%.2X%.2X ",   Buffer[26],Buffer[27]);									fputs(temp,fp);
	
	wFlowNo = (WORD)(Buffer[6]*256)+Buffer[7];
	
	crcFlag = calc_crc16(28,Buffer,out);
	if(crcFlag == 0)
		sprintf(temp,"%s","正确\n");
	else
		sprintf(temp,"%s","错误\n");
	fputs(temp,fp);
	fclose(fp);
	
	pDoc->m_TaskInfo.wTaskCurrentNo += 1;
	pDoc->m_TerminalInfo[PortNo].wEDFlowNo = wFlowNo; 
	if(pDoc->m_TaskInfo.wTaskCurrentNo == pDoc->m_TaskInfo.wTaskTotalNo) //历史数据收集完成
	{
		if(pDoc->m_bNetPar == true) //星型结构
		{
			pDoc->m_ucNo            = 0;
			pDoc->m_TaskInfo.wIDNo  = 0; //任务ID为0 
			pDoc->m_TaskInfo.ucMode = 0; //默认任务
			pDoc->m_TaskInfo.wTaskTotalNo = 0;
			pDoc->m_TaskInfo.wTaskCurrentNo =0;
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
			pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
			pDoc->m_TaskInfo.ucRetryNo  = 0;
			BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,0);
			//AfxMessageBox("收集交易数据");
			return;
		}
	}
	else//历史数据收集未完成
	{
		pDoc->m_ucNo = PortNo; //当前操作端口
		pDoc->m_TaskInfo.wIDNo = 1; //任务ID
		pDoc->m_TaskInfo.ucMode = 1; //计次任务
		//pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo; //期望运行总次数
//		pDoc->m_TaskInfo.wTaskCurrentNo = 0; //当前次数为0
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令总次数
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前数 
		pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //收集历史数据
		pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
		pDoc->m_TaskInfo.ucRetryNo  = 0;
		if(wFlowNo == 0xFFFF)
			wFlow1 = 0;
		else
			wFlow1 = wFlowNo+1;
		//sprintf(temp,"收集历史数据---%d",wFlow1);
		//AfxMessageBox(temp);
		ucFlowNo[0] = (unsigned char)(wFlow1 / 256);
		ucFlowNo[1] = (unsigned char)(wFlow1 % 256);
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
	}
		
	return;
}

//收集扎帐历史数据
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

	if(pBuffer->ucMode == 2) //有数据返回
	{
		if(pDoc->m_wNoReponseTime != 0) //由不通讯到通讯，在规定的次数内应发出通讯成功信息
		{
			pDoc->m_wNoReponseTime = 0; //本部分目前缺少代码
		}
		crcFlag = calc_crc16((unsigned char)(pBuffer->wLength),pBuffer->ucBuffer,out);
		if(crcFlag == 1)//CRC正确
		{
			ucAddr = pBuffer->ucBuffer[1];
			if(ucAddr == pDoc->m_TerminalInfo[ucNo].ucMacNo) //返回数据体机号相符合
			{
				if(pBuffer->ucBuffer[2] == 0) //正确
				{
					GetCurrentDirectory(512,temp);
					sprintf(filename,"%s\\log\\No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d扎帐历史数据.txt",temp,	
					pDoc->m_TerminalInfo[ucNo].ucIDNo[0],pDoc->m_TerminalInfo[ucNo].ucIDNo[1],
					pDoc->m_TerminalInfo[ucNo].ucIDNo[2],pDoc->m_TerminalInfo[ucNo].ucIDNo[3],
					tm.GetYear(),tm.GetMonth(),tm.GetDay());
					fp = fopen(filename,"a+");
					sprintf(temp,"%.2d年%.2d月%.2d日 %.2d时%.2d分%.2d秒收集扎帐历史数据\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
					fputs(temp,fp);
					sprintf(temp,"注册号          0x%.2X%.2X%.2X%.2X\n",pBuffer->ucBuffer[4],pBuffer->ucBuffer[5],pBuffer->ucBuffer[6],pBuffer->ucBuffer[7]);fputs(temp,fp);
					sprintf(temp,"通信版本        0x%.2X\n",pBuffer->ucBuffer[8]);fputs(temp,fp);
					sprintf(temp,"启动原因        0x%.2X\n",pBuffer->ucBuffer[9]);fputs(temp,fp);
					sprintf(temp,"扎帐流水        %d\n",  pBuffer->ucBuffer[10]*256+pBuffer->ucBuffer[11]);fputs(temp,fp);
					sprintf(temp,"扎帐时间        %.2d%.2d%.2d-%.2d%.2d%.2d\n",pBuffer->ucBuffer[12],pBuffer->ucBuffer[13],
						                                                       pBuffer->ucBuffer[14],pBuffer->ucBuffer[15],
																			   pBuffer->ucBuffer[16],pBuffer->ucBuffer[17]);
					fputs(temp,fp);
					sprintf(temp,"起始流水号      %d\n",pBuffer->ucBuffer[18]*256+pBuffer->ucBuffer[19]);fputs(temp,fp);
					sprintf(temp,"结束流水号      %d\n",pBuffer->ucBuffer[20]*256+pBuffer->ucBuffer[21]);fputs(temp,fp);
					sprintf(temp,"正常消费总笔数　%d\n",pBuffer->ucBuffer[22]*256+pBuffer->ucBuffer[23]);fputs(temp,fp);
					sprintf(temp,"正常消费总金额  %d\n",pBuffer->ucBuffer[24]+pBuffer->ucBuffer[25]*256+pBuffer->ucBuffer[26]*65536);fputs(temp,fp);
					sprintf(temp,"冲正消费总笔数　%d\n",pBuffer->ucBuffer[27]*256+pBuffer->ucBuffer[28]);fputs(temp,fp);
					sprintf(temp,"冲正消费总金额　%d\n",pBuffer->ucBuffer[29]+pBuffer->ucBuffer[30]*256+pBuffer->ucBuffer[31]*65536);fputs(temp,fp);
					sprintf(temp,"异常消费总笔数　%d\n",pBuffer->ucBuffer[32]*256+pBuffer->ucBuffer[33]);fputs(temp,fp);
					sprintf(temp,"异常消费总金额　%d\n",pBuffer->ucBuffer[34]+pBuffer->ucBuffer[35]*256+pBuffer->ucBuffer[36]*65536);fputs(temp,fp);	
					sprintf(temp,"其他交易总笔数  %d\n",pBuffer->ucBuffer[37]*256+pBuffer->ucBuffer[38]);fputs(temp,fp);
					sprintf(temp,"扎帐标记　　　  0x%.2X\n",pBuffer->ucBuffer[39]);fputs(temp,fp);
					sprintf(temp,"CRC=%.2X%.2X",pBuffer->ucBuffer[40],pBuffer->ucBuffer[41]); fputs(temp,fp);
					crcFlag = calc_crc16(38,&(pBuffer->ucBuffer[4]),out);
					if(crcFlag == 0)
						fputs("正确\n",fp);
					else
						fputs("错误\n",fp);
					fclose(fp);
					wFlowNo =  pBuffer->ucBuffer[10]*256+pBuffer->ucBuffer[11];
					pDoc->m_TerminalInfo[ucNo].wECFlowNo = wFlowNo; 
					pDoc->m_TaskInfo.wTaskCurrentNo += 1;
					
					if(pDoc->m_TaskInfo.wTaskCurrentNo == pDoc->m_TaskInfo.wTaskTotalNo) //历史数据收集完成
					{
						if(pDoc->m_bNetPar == true) //星型结构
						{
							pDoc->m_ucNo            = 0;
							pDoc->m_TaskInfo.wIDNo  = 0; //任务ID为0 
							pDoc->m_TaskInfo.ucMode = 0; //默认任务
							pDoc->m_TaskInfo.wTaskTotalNo = 0;
							pDoc->m_TaskInfo.wTaskCurrentNo =0;
							pDoc->m_TaskInfo.ucCommandTotalNo = 1;
							pDoc->m_TaskInfo.ucCommandCurrentNo = 0;
							pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
							pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
							pDoc->m_TaskInfo.ucRetryNo  = 0;
							BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,0);
							//AfxMessageBox("收集交易数据");
							return;
						}
					}
					else//历史数据收集未完成
					{
						//pDoc->m_ucNo = PortNo; //当前操作端口
						pDoc->m_TaskInfo.wIDNo = 2; //任务ID
						pDoc->m_TaskInfo.ucMode = 1; //计次任务
						//pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo; //期望运行总次数
						//		pDoc->m_TaskInfo.wTaskCurrentNo = 0; //当前次数为0
						pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令总次数
						pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前数 
						pDoc->m_TaskInfo.ucCommandArray[0]  = 0x8A; //收集历史数据
						pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
						pDoc->m_TaskInfo.ucRetryNo  = 0;
						if(wFlowNo == 0xFFFF)
							wFlow1 = 0;
						else
							wFlow1 = wFlowNo+1;
						sprintf(temp,"收集历史数据---%d",wFlow1);
						//AfxMessageBox(temp);
						ucFlowNo[0] = (unsigned char)(wFlow1 / 256);
						ucFlowNo[1] = (unsigned char)(wFlow1 % 256);
						BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
					}
		

				}
				else
				{
					sprintf(cTemp,"收集扎帐数据---返回数据体Mark值%.2X",pBuffer->ucBuffer[2]);
					AfxMessageBox(cTemp);
					return;
				}
			}
			else //返回数据体机号不符合
			{
				sprintf(cTemp,"收集扎帐数据 ---- 返回数据体机号不符合 = %d",ucAddr);
				AfxMessageBox(cTemp);
				return;
			}
		}
		else //CRC不正确
		{
			AfxMessageBox("返回数据体CRC错误");
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
		sprintf(temp,"%s","正确");
	else
		sprintf(temp,"%s","错误");//CRC出错处理
	
	crcFlag = calc_crc16(26,Buffer,out);
	if(out[0] == Buffer[26] && out[1] == Buffer[27])
	{
		sprintf(temp,"%s","正确\n");
		crcFlag = 1;
	}
	else
	{
		sprintf(temp,"%s","错误\n");
		crcFlag = 0;
	}
	fputs(temp,fp);
	fclose(fp);
	if(crcFlag == 1) //CRC正确

}*/