//原始数据处理流程
#include "stdafx.h"
#include "SmartTerminal.h"
void Process_RawData_BaseMarkValue(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
int  Process_Lport_State(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
void Process_Lport_RawCollectData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
void Porcess_SFJData(  TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo);
void Process_StateData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo); //处理扎帐数据
void Process_JSBData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo);
void Process_GSJData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE ucNo);
/*************收集数据流程****************************
 * 原始数据收集处理流程
 * 作者：李呐
 * 创建日期：2004年1月7日
*******************************************************/

void CollectRawDataProcess(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int crcFlag,i;
	unsigned char out[3],ucAddr,ucNo;
	FILE *fp;
	char filename[512],chTemp[512];
	CTime tm = CTime::GetCurrentTime();
	
	ucNo = pDoc->m_ucNo;	  //当前通讯端口号
	if(pBuffer->ucMode == 2)  //接收到数据
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
				Process_RawData_BaseMarkValue(pDoc,pBuffer); //根据数据返回Mark值处理原始数据
				return;
			}
			else//数据体机号与参数不符合 目前此类问题暂时不给与考虑
			{
				GetCurrentDirectory(512,chTemp);
				sprintf(filename,"%s\\log\\异常信息\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",chTemp,
					    pDoc->m_TerminalInfo[ucNo].ucIDNo[0],pDoc->m_TerminalInfo[ucNo].ucIDNo[1],	
					    pDoc->m_TerminalInfo[ucNo].ucIDNo[2],pDoc->m_TerminalInfo[ucNo].ucIDNo[3],
				        tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");													   
				sprintf(chTemp,"%.2d年%d月%.2d日 %.2d时%d分%.2d秒 原始数据机号错,数据为:\n ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
																     	                     tm.GetHour(),tm.GetMinute(),tm.GetSecond());
				fputs(chTemp,fp);
				for(i=0;i<pBuffer->wLength;i++)
				{
					sprintf(chTemp,"%.2X",pBuffer->ucBuffer[i]);
					fputs(chTemp,fp);
				}
				fputs("\n",fp);
				fclose(fp);
				goto CollectRawData1;//继续收集;问题，若始终出现机号错应如何处理
			}
		}
		else//CRC错误
		{
			GetCurrentDirectory(512,chTemp);
			sprintf(filename,"%s\\log\\异常信息\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",chTemp,
				pDoc->m_TerminalInfo[ucNo].ucIDNo[0],pDoc->m_TerminalInfo[ucNo].ucIDNo[1],	
				pDoc->m_TerminalInfo[ucNo].ucIDNo[2],pDoc->m_TerminalInfo[ucNo].ucIDNo[3],
				tm.GetYear(),tm.GetMonth(),tm.GetDay());
			fp = fopen(filename,"a+");													   
			sprintf(chTemp,"%.2d年%d月%.2d日 %.2d时%d分%.2d秒 原始数据CRC错,数据为:\n ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
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
	else if(pBuffer->ucMode == 3) //未接收到数据
	{
		//通知显示程序
		pDoc->m_wNoReponseTime++;
	}
	
CollectRawData1:
	if(pDoc->m_TaskInfo.ucMode == 0) //默认任务
	{
		//继续收集
		if(pDoc->m_bNetPar == true)//星型结构，继续收集
		{	
			pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		else //(pDoc->m_ucNetPar == 1)//总线结构
		{
			pDoc->m_ucNo++;
			if(pDoc->m_ucNo == pDoc->m_ucTotalNo ) //最大终端数
				pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
	}
}
/*********************************************************
  * 函数说明：数据收集时根据数据返回Mark值处理原始数据
  * 作者：    李呐
  *创建日期：2004年1月
*********************************************************/
void Process_RawData_BaseMarkValue(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int  retCode;
	BYTE ucMark,ucNo,out[3];
	
	ucNo = pDoc->m_ucNo;
	
	ucMark = pBuffer->ucBuffer[2];
	switch(ucMark)
	{
	case 0x00: //有数据
		if(pDoc->m_TerminalInfo[ucNo].ucType[0] == 53 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 01)//服务器
		{
			retCode = Process_Lport_State(pDoc,pBuffer);//处理Lport端口状态
			if(retCode == 1)//无特殊状态需要处理
			{
				Process_Lport_RawCollectData(pDoc,pBuffer);//处理Lport原始交易数据
				return;
			}
			else
			{
				//处理特殊状态
				return;
			}
		}
		//后续应该还有处理其他机器类型代码
		//else if(pDoc->m_TerminalInfo[ucNo].ucMacType[0] == 01 && pDoc->m_TerminalInfo[ucNo].ucMacType[1] == 21)//计时宝
		//{
		//
		//}
		//else 
		//收费机
		break;
	case 0x0a://无数据
		if(pDoc->m_TaskInfo.ucMode == 0) //默认任务
		{
			//继续收集
			if(pDoc->m_bNetPar == true)//星型结构，继续收集
			{	
				//AfxMessageBox("数据继续收集");
				pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
			else //(pDoc->m_ucNetPar == 1)//总线结构
			{
				pDoc->m_ucNo++;
				if(pDoc->m_ucNo == pDoc->m_ucTotalNo)
					pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
		}
		break;
	case 0x01://读写器操作错误
		break;
	case 0x02://时钟错误
		break;
	case 0x03://FLASH操作错误
		break;
	case 0x04://数据满
		break;
	case 0x05://流水号错
		break;
	case 0x07://参数错
		break;
	case 0x08://命令操作不当
		break;
	case 0x09://重复操作
		break;
	case 0x0b://注册号错
		break;
	case 0x0c://未定义
		break;
	case 0x0d://申请签到
		break;
	case 0x0E://黑名单版本过期
		break;
	case 0x17://有扎帐数据
		break;
	default:
		break;
	}
	if(pDoc->m_TaskInfo.ucMode == 0) //默认任务
	{
		//继续收集
		if(pDoc->m_bNetPar == true)//星型结构，继续收集
		{	
			pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		else //总线结构
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
* 函数说明：处理LPORT服务器状态信息
* 作者：    李呐
* 创建日期: 2004年1月9日
* 返回值：  0:继续收集数据
            1:有数据
			2:有其他状态需要处理
******************************************************************/
int Process_Lport_State(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
		
	BYTE  ucPortTotalNo,ucTemp,ucVer,ucState;
	unsigned char out[3];
	char chTemp[512];
	CTime tm = CTime::GetCurrentTime();
	//FILE *fp;
	
	//AfxMessageBox("3");
	ucVer         = pBuffer->ucBuffer[4];//版本
	ucState       = pBuffer->ucBuffer[5];//状态
	ucPortTotalNo = pBuffer->ucBuffer[6];//端口总数据
	
	GetCurrentDirectory(512,chTemp);
	//sprintf(filename,"%s//log//LPORT%.2X%.2X%.2X%.2X_ %.2d%.2d%.2d端口状态.txt",chTemp,
	//	pDoc->m_TerminalInfo[0].ucIDNo[0],pDoc->m_TerminalInfo[0].ucIDNo[1],
	//	pDoc->m_TerminalInfo[0].ucIDNo[2],pDoc->m_TerminalInfo[0].ucIDNo[3],
	//	tm.GetYear(),tm.GetMonth(),tm.GetDay());
	//fp = fopen(filename,"a+");
	//sprintf(chTemp,"%.2d年%.2d月%.2d日%.2d时%.2d分%.2d秒:\n",tm.GetYear(),tm.GetMonth(),
	//														  tm.GetDay(), tm.GetHour(),
	//														  tm.GetMinute(),tm.GetSecond());
	//fputs(chTemp,fp);
	for(ucTemp=0;ucTemp<ucPortTotalNo;ucTemp++)//根据状态值还会有多种处理业务流程
	{
		//sprintf(chTemp," L%.2d状态=%.2X",ucTemp+1,pBuffer->ucBuffer[7+ucTemp]);
		//fputs(chTemp,fp);
		switch(pBuffer->ucBuffer[7+ucTemp])
		{
		case 0x0a:
			//无数据
			break;
		case 0x0b:
			//注册号错
			break;
		case 0x0d:
			//申请签到
			break;
		default:
			break;
		}
	}
	//fputs("\n",fp);
	//fclose(fp);
	if(ucState == 0x0a) //无数据
	{
		if(pDoc->m_TaskInfo.ucMode == 0) //默认任务
		{	
			//继续收集
			if(pDoc->m_bNetPar == true)//星型结构，继续收集
			{	
				pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
			}
			else //(pDoc->m_ucNetPar == 1)//总线结构
			{
				pDoc->m_ucNo++;
				if(pDoc->m_ucNo == pDoc->m_ucTotalNo ) //最大终端数
					pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
			}
		}
		return 0;
	}
	else
	{
		//AfxMessageBox("处理交易数据");
		return 1;
	}
}

//*******1.2 处理服务器交易数据************************************//
void Process_Lport_RawCollectData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
		
	BYTE  ucPortTotalNo,out[3],ucNo;
	
	ucPortTotalNo = pBuffer->ucBuffer[6];
	ucNo          = pBuffer->ucBuffer[7+ucPortTotalNo];
	if(pBuffer->ucBuffer[8+ucPortTotalNo] == 0x01) //交易数据
	{
		if( (pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 01) || //增值机
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 26) || //收费机		
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 28) || //车载机 
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 30) || //管理机 
		    (pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 32) || //上机上网机
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 34) || //淋浴管理机
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 40) || //售票机
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 01 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 30) || //身份识别机
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 01 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 40) //检票机
		  )	
			//(pDoc->m_TerminalInfo[ucNo].
		{
			Porcess_SFJData(pDoc,pBuffer,&pBuffer->ucBuffer[9+ucPortTotalNo],ucNo); 
			return;
		}
		if( (pDoc->m_TerminalInfo[ucNo].ucType[0] == 01 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 21) ||//计时宝数据
			(pDoc->m_TerminalInfo[ucNo].ucType[0] == 55 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 01) //计时宝数据
          ) 
		{
			Process_JSBData(pDoc,pBuffer,&pBuffer->ucBuffer[9+ucPortTotalNo],ucNo);
			return;
		}
		if( (pDoc->m_TerminalInfo[ucNo].ucType[0] == 02 && pDoc->m_TerminalInfo[ucNo].ucType[1] == 24) ) //挂失机
		{
			Process_GSJData(pDoc,pBuffer,&pBuffer->ucBuffer[9+ucPortTotalNo],ucNo);
			return;
		}
	}
	else if(pBuffer->ucBuffer[8+ucPortTotalNo] == 0x17) //扎帐数据
	{
		Process_StateData(pDoc,pBuffer,&pBuffer->ucBuffer[9+ucPortTotalNo],ucNo);
		return;
	}
	else if(pBuffer->ucBuffer[8+ucPortTotalNo] == 0x1b) //补助数据
	{
	}
	else//未知代码
	{
		if(pDoc->m_TaskInfo.ucMode == 0) //默认任务
		{	
			//AfxMessageBox("收集服务器有未知代码");
			//继续收集
			if(pDoc->m_bNetPar  == TRUE)//星型结构，继续收集
			{	
				pDoc->m_ucNo = 0;
				BuildTaskBuffer(pDoc,pBuffer,out,0);
				return;
			}
			else //(pDoc->m_ucNetPar == 1)//总线结构
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
 *函数说明: 处理收费机原始数据
 *作者：    李呐
 *创建日期：2004年1月8日
 *参数说明：
            Buffer ----原始数据数组
			PortNo ----pDoc->m_TerminalInfo[PortNo]终端类型指针
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
	sprintf(filename,"%s\\log\\交易数据\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d年%.2d月%.2d日 %.2d时%.2d分%.2d秒收集交易数据\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
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
	ucFlowNo[0] = Buffer[6];
	ucFlowNo[1] = Buffer[7];	
	
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
	{
		wFlowNo = ((WORD)(ucFlowNo[0])*256)+(WORD)ucFlowNo[1];
		if(wFlowNo == pDoc->m_TerminalInfo[PortNo].wEDFlowNo)//如果流水号等于期望流水号
		{
			//向数据库写一笔纪录
			if(wFlowNo == 0xFFFF)
				pDoc->m_TerminalInfo[PortNo].wEDFlowNo =0;
			else
				pDoc->m_TerminalInfo[PortNo].wEDFlowNo=pDoc->m_TerminalInfo[PortNo].wEDFlowNo + 1;
			if(pDoc->m_bNetPar == TRUE)//星型结构
			{
				pDoc->m_ucNo = 0;
			}
			pDoc->m_TaskInfo.ucMode = 0;//默认任务
			pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
			pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
			pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
			BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
			return;	
		}
		else if(pDoc->m_TerminalInfo[PortNo].wEDFlowNo < wFlowNo)//期望流水号小于实际数据流水号
		{
			if(wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo <= 10240) //例如期望交易流水号100，实际500 //收集历史数据
			{
				GetCurrentDirectory(512,temp);
				sprintf(filename,"%s\\log\\异常信息\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X机收集历史交易数据:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wEDFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //当前操作端口
				pDoc->m_TaskInfo.wIDNo = 1; //任务ID
				pDoc->m_TaskInfo.ucMode = 1; //计次任务
				pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo+1; //期望运行总次数
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //当前次数为0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令总次数
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前数 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //收集历史数据
				pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
			else //期望100 实际 65530 重复收集
			{
				if(pDoc->m_bNetPar == TRUE)//星型结构
				{
					pDoc->m_ucNo = 0;
				}	
				pDoc->m_TaskInfo.ucMode = 0;//默认任务
				pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
				pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
		}
		else ////期望流水号大于实际数据流水号
		{
			if(65536 - wFlowNo + pDoc->m_TerminalInfo[PortNo].wEDFlowNo <10240) //期望65530 实际 100
			{
				GetCurrentDirectory(512,temp);
				sprintf(filename,"%s\\log\\异常信息\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X机收集历史交易数据:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wEDFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //当前操作端口
				pDoc->m_TaskInfo.wIDNo = 1; //任务ID
				pDoc->m_TaskInfo.ucMode = 1; //计次任务
				pDoc->m_TaskInfo.wTaskTotalNo = 65536-wFlowNo+pDoc->m_TerminalInfo[PortNo].wEDFlowNo; //期望运行总次数
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //当前次数为0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令总次数
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前数 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //收集历史数据
				pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
			else //期望100 实际 90重复收集
			{
				if(pDoc->m_bNetPar == TRUE)//星型结构
				{
					pDoc->m_ucNo = 0;
				}	
				pDoc->m_TaskInfo.ucMode = 0;//默认任务
				pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
				pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
		}
	}
	else //  CRC不正确 继续收集
	{
		wFlowNo = pDoc->m_TerminalInfo[PortNo].wEDFlowNo;
		if(wFlowNo == 0xFFFF )
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo = 0;
		else
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo++;
		if(pDoc->m_bNetPar == TRUE)//星型结构
		{
			pDoc->m_ucNo = 0;
		}	
		pDoc->m_TaskInfo.ucMode = 0;//默认任务
		pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
		pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
		return;
	}
}

/***************************************************************************************
 *函数说明: 处理终端机扎帐数据
 *作者：    李呐
 *创建日期：2004年2月6日
 *参数说明：
            Buffer ----原始数据数组
			PortNo ----pDoc->m_TerminalInfo[PortNo]终端类型指针
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
	sprintf(filename,"%s\\log\\扎帐数据\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d年%.2d月%.2d日 %.2d时%.2d分%.2d秒收集扎帐数据\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fputs(temp,fp);
	sprintf(temp,"注册号          0x%.2X%.2X%.2X%.2X\n",Buffer[0],Buffer[1],Buffer[2],Buffer[3]);fputs(temp,fp);
	sprintf(temp,"通信版本        0x%.2X\n",Buffer[4]);fputs(temp,fp);
	sprintf(temp,"启动原因        0x%.2X\n",Buffer[5]);fputs(temp,fp);
	sprintf(temp,"扎帐流水        %d\n",  Buffer[6]*256+Buffer[7]);fputs(temp,fp);
	sprintf(temp,"扎帐时间        %.2d%.2d%.2d-%.2d%.2d%.2d\n",Buffer[8],Buffer[9],Buffer[10],
		                                                      Buffer[11],Buffer[12],Buffer[13]);
	fputs(temp,fp);
	sprintf(temp,"起始流水号      %d\n",Buffer[14]*256+Buffer[15]);fputs(temp,fp);
	sprintf(temp,"结束流水号      %d\n",Buffer[16]*256+Buffer[17]);fputs(temp,fp);
	sprintf(temp,"正常消费总笔数　%d\n",Buffer[18]*256+Buffer[19]);fputs(temp,fp);
	sprintf(temp,"正常消费总金额  %d\n",Buffer[20]+Buffer[21]*256+Buffer[22]*65536);fputs(temp,fp);
	sprintf(temp,"冲正消费总笔数　%d\n",Buffer[23]*256+Buffer[24]);fputs(temp,fp);
	sprintf(temp,"冲正消费总金额　%d\n",Buffer[25]+Buffer[26]*256+Buffer[27]*65536);fputs(temp,fp);
	sprintf(temp,"异常消费总笔数　%d\n",Buffer[28]*256+Buffer[29]);fputs(temp,fp);
	sprintf(temp,"异常消费总金额　%d\n",Buffer[30]+Buffer[31]*256+Buffer[32]*65536);fputs(temp,fp);	
	sprintf(temp,"其他交易总笔数  %d\n",Buffer[33]*256+Buffer[34]);fputs(temp,fp);
	sprintf(temp,"扎帐标记　　　  0x%.2X\n",Buffer[35]);fputs(temp,fp);
	sprintf(temp,"CRC=%.2X%.2X",Buffer[36],Buffer[37]); fputs(temp,fp);
	crcFlag = calc_crc16(38,Buffer,out);
	if(crcFlag == 0)
		fputs("正确\n",fp);
	else
		fputs("错误\n",fp);
	fclose(fp);
	ucFlowNo[0] = Buffer[6];	ucFlowNo[1] = Buffer[7];
	wFlowNo = Buffer[6]*256+Buffer[7];
	if(crcFlag == 0)//正确
	{
		if(wFlowNo == pDoc->m_TerminalInfo[PortNo].wECFlowNo)//如果流水号等于期望流水号
		{
			if(wFlowNo == 0xFFFF)
				pDoc->m_TerminalInfo[PortNo].wECFlowNo = 0;
			else
				pDoc->m_TerminalInfo[PortNo].wECFlowNo += 1;

			if(pDoc->m_bNetPar == true) //星型
			{
				pDoc->m_ucNo = 0;
			}

			pDoc->m_TaskInfo.ucMode = 0;//默认任务
			pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
			pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
			pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
			BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);

			return;	

		}
		else if(wFlowNo > pDoc->m_TerminalInfo[PortNo].wECFlowNo) //上传流水号大于期望流水号
		{
			//if(65536-wFlowNo + pDoc->m_TerminalInfo[PortNo].wECFlowNo <= 128 ) //期望 10 上传 100 历史收集
			if(wFlowNo - pDoc->m_TerminalInfo[PortNo].wECFlowNo <= 128 )
			{
				//AfxMessageBox("收集历史扎帐数据");
				sprintf(filename,"%s\\log\\异常信息\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X机收集历史扎帐数据:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						wFlowNo,pDoc->m_TerminalInfo[PortNo].wECFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //当前操作端口
				pDoc->m_TaskInfo.wIDNo = 2; //任务ID
				pDoc->m_TaskInfo.ucMode = 1; //计次任务
				pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wECFlowNo+1; //期望运行总次数
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //当前次数为0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令总次数
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前数 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0x8A; //收集历史数据
				pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wECFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wECFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				
				return;	
			}
			else // 期望 10 实际 5000 重复收集
			{
				if(pDoc->m_bNetPar == true) //星型
				{
					pDoc->m_ucNo = 0;
				}
				pDoc->m_TaskInfo.ucMode = 0;//默认任务
				pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
				pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;		
			}
		}
		else //上传流水号小于期望流水号 上--10 期100  上65530 期望 10
		{
			if(pDoc->m_TerminalInfo[PortNo].wECFlowNo - wFlowNo <= 128) //期望 100 上传 10 重复收集
			{
				if(pDoc->m_bNetPar == true) //星型
				{
					pDoc->m_ucNo = 0;
				}
				pDoc->m_TaskInfo.ucMode = 0;//默认任务
				pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
				pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;		
			}
			else //期望 10 上传 65530 历史收集
			{
				sprintf(filename,"%s\\log\\异常信息\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X机收集历史扎帐数据:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wECFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);

				pDoc->m_ucNo = PortNo; //当前操作端口
				pDoc->m_TaskInfo.wIDNo = 2; //任务ID
				pDoc->m_TaskInfo.ucMode = 1; //计次任务
				pDoc->m_TaskInfo.wTaskTotalNo = 65536-wFlowNo+pDoc->m_TerminalInfo[PortNo].wECFlowNo; //期望运行总次数
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //当前次数为0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令总次数
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前数 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0x8A; //收集历史数据
				pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wECFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wECFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
			}

		}
		//AfxMessageBox("正确");

	}
	else//CRC不正确
	{
		AfxMessageBox("错误");
		wFlowNo = pDoc->m_TerminalInfo[PortNo].wECFlowNo;
		if(wFlowNo == 0xFFFF )
			pDoc->m_TerminalInfo[PortNo].wECFlowNo = 0;
		else
			pDoc->m_TerminalInfo[PortNo].wECFlowNo++;
		if(pDoc->m_bNetPar == TRUE)//星型结构
		{
			pDoc->m_ucNo = 0;
		}	
		pDoc->m_TaskInfo.ucMode = 0;//默认任务
		pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
		pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
		//AfxMessageBox("错误");
		return;	
	}
	return;
}

////////////////20040217到此为止 加上其他交易数据问题******************************/
void Process_JSBData(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer,BYTE *Buffer,BYTE PortNo)
{
	CTime tm=CTime::GetCurrentTime();
	FILE  *fp;
	char  filename[512],temp[512];
	int   crcFlag;
	unsigned char ucFlowNo[2],out[3];
	WORD  wFlowNo;
	
	GetCurrentDirectory(512,temp);
	sprintf(filename,"%s\\log\\交易数据\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d年%.2d月%.2d日 %.2d时%.2d分%.2d秒收集交易数据\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fputs(temp,fp);
	sprintf(temp,"注册号   %.2X%.2X%.2X%.2X\n", Buffer[0],Buffer[1],Buffer[2],Buffer[3]);	fputs(temp,fp);	
	sprintf(temp,"通信版本 %.2X\n",Buffer[4]);												fputs(temp,fp);
	sprintf(temp,"启动原因 %.2X\n",Buffer[5]);												fputs(temp,fp);
	sprintf(temp,"交易流水 %d\n",  Buffer[6]*256+Buffer[7]);								fputs(temp,fp);
	sprintf(temp,"卡号     0X%.2X%.2X%.2X%.2X%.2X\n",Buffer[8],Buffer[9],Buffer[10],Buffer[11],Buffer[12]);				fputs(temp,fp);
	sprintf(temp,"交易时间 %.2d%.2d%.2d-%.2d%.2d%.2d 星期%d\n",Buffer[13],Buffer[14],Buffer[15],
														Buffer[16],Buffer[17],Buffer[18],Buffer[19]);	fputs(temp,fp);
	sprintf(temp,"工作模式代码 %d\n",Buffer[20]);						fputs(temp,fp);
	sprintf(temp,"考勤类型     %d\n",Buffer[21]);			fputs(temp,fp);
	sprintf(temp,"卡型代码     %d\n",Buffer[22]);			fputs(temp,fp);
	sprintf(temp,"感应头编号   %d\n",Buffer[23]);			fputs(temp,fp);
	sprintf(temp,"上下班标记   %d\n",Buffer[24]);			fputs(temp,fp);
	sprintf(temp,"交易标记 %.2X\n", Buffer[25]);			fputs(temp,fp);
	sprintf(temp,"CRC=%.2X%.2X ",   Buffer[26],Buffer[27]);									fputs(temp,fp);
	ucFlowNo[0] = Buffer[6];
	ucFlowNo[1] = Buffer[7];	
	
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
	{
		wFlowNo = ((WORD)(ucFlowNo[0])*256)+(WORD)ucFlowNo[1];
		if(wFlowNo == pDoc->m_TerminalInfo[PortNo].wEDFlowNo)//如果流水号等于期望流水号
		{
			//向数据库写一笔纪录
			if(wFlowNo == 0xFFFF)
				pDoc->m_TerminalInfo[PortNo].wEDFlowNo =0;
			else
				pDoc->m_TerminalInfo[PortNo].wEDFlowNo=pDoc->m_TerminalInfo[PortNo].wEDFlowNo + 1;
			if(pDoc->m_bNetPar == TRUE)//星型结构
			{
				pDoc->m_ucNo = 0;
			}
			pDoc->m_TaskInfo.ucMode = 0;//默认任务
			pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
			pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
			pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
			pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
			pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
			pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
			BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
			return;	
		}
		else if(pDoc->m_TerminalInfo[PortNo].wEDFlowNo < wFlowNo)//期望流水号小于实际数据流水号
		{
			if(wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo <= 10240) //例如期望交易流水号100，实际500 //收集历史数据
			{
				GetCurrentDirectory(512,temp);
				sprintf(filename,"%s\\log\\异常信息\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X机收集历史交易数据:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wEDFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //当前操作端口
				pDoc->m_TaskInfo.wIDNo = 1; //任务ID
				pDoc->m_TaskInfo.ucMode = 1; //计次任务
				pDoc->m_TaskInfo.wTaskTotalNo = wFlowNo-pDoc->m_TerminalInfo[PortNo].wEDFlowNo+1; //期望运行总次数
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //当前次数为0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令总次数
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前数 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //收集历史数据
				pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
			else //期望100 实际 65530 重复收集
			{
				if(pDoc->m_bNetPar == TRUE)//星型结构
				{
					pDoc->m_ucNo = 0;
				}	
				pDoc->m_TaskInfo.ucMode = 0;//默认任务
				pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
				pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
		}
		else ////期望流水号大于实际数据流水号
		{
			if(65536 - wFlowNo + pDoc->m_TerminalInfo[PortNo].wEDFlowNo <10240) //期望65530 实际 100
			{
				GetCurrentDirectory(512,temp);
				sprintf(filename,"%s\\log\\异常信息\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",
					pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
					pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
					temp,tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");
				sprintf(temp,"%.2X%.2X%.2X%.2X机收集历史交易数据:%d----%d\n",pDoc->m_TerminalInfo[PortNo].ucIDNo[0],
						pDoc->m_TerminalInfo[PortNo].ucIDNo[1],pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
						pDoc->m_TerminalInfo[PortNo].wEDFlowNo,wFlowNo);
				fputs(temp,fp);
				fclose(fp);
				pDoc->m_ucNo = PortNo; //当前操作端口
				pDoc->m_TaskInfo.wIDNo = 1; //任务ID
				pDoc->m_TaskInfo.ucMode = 1; //计次任务
				pDoc->m_TaskInfo.wTaskTotalNo = 65536-wFlowNo+pDoc->m_TerminalInfo[PortNo].wEDFlowNo; //期望运行总次数
				pDoc->m_TaskInfo.wTaskCurrentNo = 0; //当前次数为0
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令总次数
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前数 
				pDoc->m_TaskInfo.ucCommandArray[0]  = 0xBB; //收集历史数据
				pDoc->m_TaskInfo.ucERetryNo = 3;//命令字期望重试次数
				pDoc->m_TaskInfo.ucRetryNo  = 0;
				ucFlowNo[0] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo / 256);
				ucFlowNo[1] = (unsigned char)(pDoc->m_TerminalInfo[PortNo].wEDFlowNo % 256);
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
			else //期望100 实际 90重复收集
			{
				if(pDoc->m_bNetPar == TRUE)//星型结构
				{
					pDoc->m_ucNo = 0;
				}	
				pDoc->m_TaskInfo.ucMode = 0;//默认任务
				pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
				pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
				pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
				pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
				pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
				pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
				BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
				return;
			}
		}
	}
	else //  CRC不正确 继续收集
	{
		wFlowNo = pDoc->m_TerminalInfo[PortNo].wEDFlowNo;
		if(wFlowNo == 0xFFFF )
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo = 0;
		else
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo++;
		if(pDoc->m_bNetPar == TRUE)//星型结构
		{
			pDoc->m_ucNo = 0;
		}	
		pDoc->m_TaskInfo.ucMode = 0;//默认任务
		pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
		pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
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
	sprintf(filename,"%s\\log\\交易数据\\ID%.2X%.2X%.2X%.2X_%.2d%.2d%.2d.txt",temp,	
		pDoc->m_TerminalInfo[PortNo].ucIDNo[0],pDoc->m_TerminalInfo[PortNo].ucIDNo[1],
		pDoc->m_TerminalInfo[PortNo].ucIDNo[2],pDoc->m_TerminalInfo[PortNo].ucIDNo[3],
		tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	sprintf(temp,"%.2d年%.2d月%.2d日 %.2d时%.2d分%.2d秒收集交易数据\n",	tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fputs(temp,fp);
	sprintf(temp,"注册号   %.2X%.2X%.2X%.2X\n", Buffer[0],Buffer[1],Buffer[2],Buffer[3]);	fputs(temp,fp);	
	sprintf(temp,"通信版本 %.2X\n",Buffer[4]);												fputs(temp,fp);
	sprintf(temp,"启动原因 %.2X\n",Buffer[5]);												fputs(temp,fp);
	sprintf(temp,"交易流水 %d\n",  Buffer[6]*256+Buffer[7]);								fputs(temp,fp);
	sprintf(temp,"显示卡号 %.2X%.2X%.2X%.2X%.2X\n",Buffer[8],Buffer[9],Buffer[10],Buffer[11],Buffer[12]);				fputs(temp,fp);
	sprintf(temp,"个人密码密文 %.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X\n",
		Buffer[13],Buffer[14],Buffer[15],Buffer[16],
		Buffer[17],Buffer[18],Buffer[19],Buffer[20]);	fputs(temp,fp);
	sprintf(temp,"交易时间 %.2d月%.2d日%.2d时%.2d分\n",Buffer[21],Buffer[22],Buffer[23],Buffer[24]);		fputs(temp,fp);
	sprintf(temp,"交易标记 %.2X\n", Buffer[25]);			fputs(temp,fp);
	sprintf(temp,"CRC=%.2X%.2X ",   Buffer[26],Buffer[27]);									fputs(temp,fp);
	ucFlowNo[0] = Buffer[6];
	ucFlowNo[1] = Buffer[7];	
	
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
	{
		wFlowNo = ((WORD)(ucFlowNo[0])*256)+(WORD)ucFlowNo[1];
		pDoc->m_TerminalInfo[PortNo].wEDFlowNo = wFlowNo;
		if(pDoc->m_bNetPar == TRUE)//星型结构
		{
			pDoc->m_ucNo = 0;
		}
		//一大段处理流程
		pDoc->m_TaskInfo.ucMode = 0;//默认任务
		pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
		pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
		return;	
	}
	else //  CRC不正确 继续收集
	{
		wFlowNo = pDoc->m_TerminalInfo[PortNo].wEDFlowNo;
		if(wFlowNo == 0xFFFF )
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo = 0;
		else
			pDoc->m_TerminalInfo[PortNo].wEDFlowNo++;
		if(pDoc->m_bNetPar == TRUE)//星型结构
		{
			pDoc->m_ucNo = 0;
		}	
		pDoc->m_TaskInfo.ucMode = 0;//默认任务
		pDoc->m_TaskInfo.wIDNo  = 0;//任务ID号，0----代表数据收集与确认
		pDoc->m_TaskInfo.ucERetryNo = 3;//期望重试次数为3
		pDoc->m_TaskInfo.ucRetryNo  = 0;//当前命令重试次数 
		pDoc->m_TaskInfo.ucCommandTotalNo = 1;//命令字总数为1
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;//命令字当前运行序号
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x04;
		BuildTaskBuffer(pDoc,pBuffer,ucFlowNo,2);
		return;
	}

}



//////////************************数据确认流程************************/////
void ConfirmRawDataProcess(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	int crcFlag,i;
	unsigned char out[3],ucAddr,ucNo;
	FILE *fp;
	char filename[512],chTemp[512];
	CTime tm = CTime::GetCurrentTime();
	ucNo = pDoc->m_ucNo;	  //当前通讯端口号
	if(pBuffer->ucMode == 2)  //接收到数据
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
				Sleep(500);
				goto ConFirmData;
			}
			else//数据体机号与参数不符合
			{
				
				GetCurrentDirectory(512,chTemp);
				sprintf(filename,"%s\\log\\No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d错误",chTemp,
					pDoc->m_TerminalInfo[ucNo].ucIDNo[0],pDoc->m_TerminalInfo[ucNo].ucIDNo[1],	
					pDoc->m_TerminalInfo[ucNo].ucIDNo[2],pDoc->m_TerminalInfo[ucNo].ucIDNo[3],
				    tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");													   
				sprintf(chTemp,"%.2d年%d月%.2d日 %.2d时%d分%.2d秒 原始数据机号错,数据为:\n ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
																     	                     tm.GetHour(),tm.GetMinute(),tm.GetSecond());
				fputs(chTemp,fp);
				for(i=0;i<pBuffer->wLength;i++)
				{
					sprintf(chTemp,"%.2X",pBuffer->ucBuffer[i]);
					fputs(chTemp,fp);
				}
				fputs("\n",fp);
				fclose(fp);
				goto ConFirmData;//继续收集;问题，若始终出现机号错应如何处理
			}
		}
		else //CRC不正确
		{
			//重新收集纪录
			goto ConFirmData;
		}
	}
	else if(pBuffer->ucMode == 3) //未接收到数据
	{
		//通知显示程序
		pDoc->m_wNoReponseTime++;
	}
ConFirmData:
	if(pDoc->m_TaskInfo.ucMode == 0) //默认任务
	{
		pDoc->m_TaskInfo.ucCommandTotalNo  = 1;
		pDoc->m_TaskInfo.ucCommandCurrentNo = 0;
		pDoc->m_TaskInfo.ucCommandArray[0] = 0x03;
		//继续收集
		if(pDoc->m_bNetPar == true)//星型结构，继续收集
		{	
			pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		else //(pDoc->m_ucNetPar == 1)//总线结构
		{
			pDoc->m_ucNo++;
			if(pDoc->m_ucNo == pDoc->m_ucTotalNo ) //最大终端数
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
	if(pBuffer->ucFlag == 2) //接收到数据
	{
		if(pDoc->wNoReponseTime != 0) //发出通讯成功信息
			pDoc->wNoReponseTime = 0;
		crcFlag = calc_crc16((unsigned char)pBuffer->m_wBufferSize,
			                                pBuffer->m_ucBuffer,out);
		if(crcFlag == 1)//CRC正确
		{
			ucAddr = pBuffer->m_ucBuffer[1];
			if(ucAddr == pDoc->m_TerminalInfo[ucNo].ucMacNo)
			{
				if(pBuffer->m_ucBuffer[2] == 0) //Mark值
					goto ConFirmRawData1;
				else
					goto ConFirmRawData1;
				
			}
			else//数据体机号与参数不符合
			{
				sprintf(filename,"No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d错误",pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[0],
																       pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[1],	
																	   pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[2],	
																	   pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[3],
																	   tm.GetYear(),tm.GetMonth(),tm.GetDay());
				fp = fopen(filename,"a+");													   
				sprintf(chTemp,"%.2d年%d月%.2d日 %.2d时%d分%.2d秒 原始数据机号错,数据为 ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
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
		else//CRC错误
		{
			sprintf(filename,"No%.2X%.2X%.2X%.2X_%.2d%.2d%.2d错误",pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[0],
															       pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[1],	
																   pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[2],	
																   pDoc->m_TerminalInfo[pDoc->m_ucNo].ucIDNo[3],
																   tm.GetYear(),tm.GetMonth(),tm.GetDay());
			fp = fopen(filename,"a+");													   
			sprintf(chTemp,"%.2d年%d月%.2d日 %.2d时%d分%.2d秒 原始数据CRC错,数据为 ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
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
	else if(pBuffer->ucFlag == 3) //未接收到数据
	{
		//通知显示程序
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
	pDoc->m_TaskInfo.wRunNo            = 1; //命令需要运行次数
	
	if(pDoc->m_TaskInfo.ucTaskType == 0) //默认任务
	{
		//继续收集
		if(pDoc->m_ucNetPar == 0)//星型结构，继续收集
		{	
			pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
		else //(pDoc->m_ucNetPar == 1)//总线结构
		{
			pDoc->m_ucNo++;
			if(pDoc->m_ucNo == pDoc->m_ucTerminalTotalNo)
				pDoc->m_ucNo = 0;
			BuildTaskBuffer(pDoc,pBuffer,out,0);
			return;
		}
	}*/
}
 
