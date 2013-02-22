#include "ks_psamcard.h"
#include <vector>
#include <string>
#include "mystring.h"
#include "global_func.h"
#include "des.h"
#include "kscardtype.h"
using namespace std;


ks_psamcard::ks_psamcard():ks_psamcard_base()
{
}

ks_psamcard::~ks_psamcard()
{
}


int ks_psamcard::PublishPSAMCard(ST_PSAMCARD* PSAMCard)
{
	int nRet=0;
	char tmpbuf[256]="";
	BYTE rbuf[256];
	unsigned char ucSendData[256];
	int nSendLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
	vector<string> CmdVector;
	string sMsg;
	string sCmd;
	char sHexStr[64];
	int uCmdLen=0;
	BYTE uCmd[256];
	ST_PSAMCARD15 Psam15;
	ST_PSAMCARD17 Psam17;

	memset(sHexStr,0,sizeof(sHexStr));
	memset(uCmd,0,sizeof(uCmd));
		
	memset(sCCK, 0,sizeof sCCK);
	memset(rbuf,0,sizeof rbuf);
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucRespData,0,sizeof ucRespData);
	
	memset(&Psam15, 0,sizeof Psam15);
	memset(&Psam17, 0,sizeof Psam17);

	if(!m_CardKeys.bLoad)
	{
		SET_ERR("δװ����Կ����Կ");
		return -1;
	}
	if(strlen(PSAMCard->sStartDate)!=8)
	{
		SetLastErrMsg("��ʼ���ڳ��ȴ���");
		return -1;
	}
	if(strlen(PSAMCard->sExpireDate)!=8)
	{
		SetLastErrMsg("��Ч���ڳ��ȴ���");
		return -1;
	}
	if(PSAMCard->nKeyIndex>2)
	{
		SetLastErrMsg("��Կ�������ܴ���2");
		return -1;
	}
	PSAMCard->nKeyIndex=1;

	//��λ�ϵ�
	unsigned char rbuff[256]={0};
	this->m_PowerOn = 0;
	nRet=this->ResetPSAM();
	if(nRet)
	{
		SET_ERR("SAM�����ϵ縴λ����");
		return nRet;
	}
	//���ܴ�
	sCmd="808A0000 2A 3F00 10 00 FFFF 0A 00 012A FF 81 FFFFFF 00 315041592E5359532E4444463031FFFF 00180100010002030300";
	string_replace(sCmd," ","");

	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));

	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			if(cmd.cmd_retcode==0x6985)
			{
				SET_ERR("�ÿ��ѷ���,nRet="<<ltohex(cmd.cmd_retcode));
				return nRet;
			}
			else
			{
				GetErrMsgByErrCode(cmd.cmd_retcode,cmd.cmd_retmsg);
				SET_ERR(cmd.cmd_retmsg);
				return nRet;
			}
		}
		else
		{
			m_Reader->GetErrMsg(cmd.cmd_retmsg);
			SET_ERR(cmd.cmd_retmsg);
			return nRet;
		}
		
	}
	sCmd="80800000080001 34  00 0040 00 02";
	string_replace(sCmd," ","");
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//��Ƭ������Ϣ�ļ�
	sCmd="80800000080015 31  00 000E 00 02";
	string_replace(sCmd," ","");
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//д������Ϣ�ļ�15
	sCmd="00D695000E";
	sCmd+=lpad(PSAMCard->sCardNo,20,'0');
	sCmd+=ltohex(PSAMCard->nCardVer);
	sCmd+=ltohex(PSAMCard->nCardType);
	sCmd+=ltohex(1);				//ָ��汾
	sCmd+=ltohex(0);				//FCI����
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//�ն���Ϣ�ļ�16
	sCmd="80800000080016 31 00 0006 00 FF";
	string_replace(sCmd," ","");
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//��������Ϣ�ļ�
	sCmd="80800000080017 31  00 0026 00 02";
	string_replace(sCmd," ","");
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//�޸Ĺ�����Ϣ�ļ�17
	sCmd="00D6970019";
	sCmd+=ltohex(PSAMCard->nKeyIndex);//��Կ����
	sCmd+=lpad(PSAMCard->sPublishID,16,'0');
	sCmd+=lpad(PSAMCard->sUserID,16,'0');
	sCmd+=PSAMCard->sStartDate;
	sCmd+=PSAMCard->sExpireDate;

	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//д�ն˻����
	sCmd = "00D6960006";
	sCmd += lpad(PSAMCard->sTermID,12,'0');
	//sCmd
	string_replace(sCmd," ","");
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//д�ⲿ��֤��Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.DACK1,16,sHexStr);
	sCmd="80D000001A0E180000010002030300";
	sCmd+=sHexStr;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//����
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="80800000 2ADF03 20 00 FFFF 0A FF 01C8 00 81 FFFFFF 00 D156000001BDF0CACBB4EFD6A7B8B6FF 00180100010002030300";
	string_replace(sCmd," ","");
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//����DF03��EF�ļ�
	//ѡ���ļ�Ŀ¼
	sCmd="00A40000 02DF03";
	CmdVector.push_back(sCmd);
	//������������ļ�
	sCmd="80800000 080019 31 00 0004 00 FF";
	CmdVector.push_back(sCmd);
	//д�ն˽�������ļ�
	sCmd="00D699000400000000";
	CmdVector.push_back(sCmd);
	//ѡ���ļ�Ŀ¼	
	sCmd="00A40000 02DF03";
	CmdVector.push_back(sCmd);
	//add new begin
	//�ⲿ��֤��Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.DACK1,16,sHexStr);
	sCmd="80D00000 1A27180100010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	////�ⲿ��֤��Կ2
	//memset(sHexStr,0,sizeof(sHexStr));
	//dec2hex(m_CardKeys.DACK2,16,sHexStr);
	//sCmd="80D00000 1A27180200010010030300";
	//sCmd+=sHexStr;
	//CmdVector.push_back(sCmd);
	////�ⲿ��֤��Կ3
	//memset(sHexStr,0,sizeof(sHexStr));
	//dec2hex(m_CardKeys.DACK3,16,sHexStr);
	//sCmd="80D00000 1A27180300010010030300";
	//sCmd+=sHexStr;
	//CmdVector.push_back(sCmd);
	//add new end
	//������Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.DPK1,16,sHexStr);
	sCmd="80D00000 1A22180100010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//������Կ2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.DPK2,16,sHexStr);
	sCmd="80D00000 1A22180200010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	//16�ֽ�Ӧ��ά������Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.DAMK,16,sHexStr);
	sCmd="80D00000 1A28180100010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//16�ֽڿ����������Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.DUK,16,sHexStr);
	sCmd="80D00000 1A28180200010010030300";
					
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//16�ֽڿ�����װ����Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.DRPK,16,sHexStr);
	sCmd="80D00000 1A28180300010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//16�ֽ��ڲ���֤����Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.DTAC,16,sHexStr);
	sCmd="80D00000 1A28180400010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	
	//������Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.DPK1,16,sHexStr);
	sCmd="80D00000 1A28180500010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	// DF 04
	CmdVector.push_back("ATR");
	sCmd="80800000 2ADF04 20 00 FFFF 0A	FF 01C8  00 81 FFFFFF 00 D156000004BDF0CACBB4EFD6A7B8B6FF 00180100010002030300";
	CmdVector.push_back(sCmd);
	sCmd="00A4000002DF04";
	CmdVector.push_back(sCmd);
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.LDACK,16,sHexStr);		//СǮ��16�ֽ��ⲿ��֤��Կ
	sCmd="80D00000 1A27180100010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	

	
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.LDACK,8,sHexStr);		//СǮ��8�ֽ��ⲿ��֤��Կ
	sCmd="80D00000 1227100201010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(m_CardKeys.LDAMK,16,sHexStr);
	sCmd="80D00000 1A28180100010010030300";
	sCmd+=sHexStr;								//СǮ��16�ֽ�Ӧ��ά������Կ
	sCmd="00A4000002DF03";
	CmdVector.push_back(sCmd);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			// ǿ���ظ�λ
			this->m_PowerOn = 0;
			nRet=this->ResetPSAM();
			if(nRet)
			{
				SET_ERR("SAM�����ϵ縴λ����");
				return nRet;
			}
			continue;
		}
		string_replace(sCmd," ","");
		string_replace(sCmd,"\t","");
		cmd.send_buf=(byte*)sCmd.c_str();
		cmd.send_len=sCmd.size();
		cmd.cmd_type=1;//16����
		nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
		if(nRet)
		{
			if(cmd.cmd_retcode)
			{
				SET_ERR("cmd["<<sCmd.substr(0,4).c_str()<<"]"<<GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
				return cmd.cmd_retcode;
			}
			else
			{
				SET_ERR(m_Reader->GetErrMsg(NULL));
				return nRet;
			}
		}
	}
	nRet = doInitNewPsam();
	if(nRet==0)
	{
		m_PowerOn = 0;
		nRet=this->ResetPSAM();	
	}
	return nRet;
}
int ks_psamcard::doInitNewPsam()
{
	int nRet;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	string sCmd;
	ks_cpu_cmd_t cmd;

	cmd.recv_buf = ucRespData;
	sCmd="801C000000";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			if(0x6E00==cmd.cmd_retcode)
			{
				return doInitOldPsam();
			}
			GetErrMsgByErrCode(cmd.cmd_retcode,cmd.cmd_retmsg);
			SET_ERR(cmd.cmd_retmsg);
			return nRet;
		}
		m_Reader->GetErrMsg(cmd.cmd_retmsg);
		SET_ERR(cmd.cmd_retmsg);
		return nRet;
	}
	sCmd="00A4000002DF04";
	////////////////////////////////////////////////////////////////////////////////////////////////////
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	sCmd="801C000000";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//����MF���˻�
	//�ϵ縴λ
	this->m_PowerOn = 0;
	nRet=this->ResetPSAM();
	if(nRet)
	{
		SET_ERR("SAM�����ϵ縴λ����");
		return nRet;
	}
	sCmd="801C000000";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}
int ks_psamcard::CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac)
{
	int i=0;
	des_context ctx;
	BYTE uTemp[16];
	// ��ʼ��MAC�����ֵ ==> temp
	memset(uTemp, 0, sizeof(uTemp));
	memcpy(uTemp, uRandom, 8 * sizeof(BYTE));
	// ��ʽ������ֵ: �� "80 00 00 ...", ��8�ֽڳ��� ==> buf
	int nBlock=0;
	if(iMacDataLen%8)
		nBlock = iMacDataLen/8 + 1; // �ܿ���
	else
		nBlock = iMacDataLen/8;
	byte* buf = new byte[nBlock*8+1];
	memset(buf, 0, nBlock*8*sizeof(byte));
	memcpy(buf, uMacData, iMacDataLen*sizeof(byte));
	buf[iMacDataLen] = 0x80;
	des_set_key(&ctx,uKey);
	for (i=0; i<nBlock; i++)
	{
		// temp .EOR. block[i] ==> temp
		for(int j=0; j<8; j++)
		{
			uTemp[j] ^= buf[i*8+j];
		}
		// temp ==> DES ==> temp
		des_encrypt(&ctx,uTemp,uTemp);
		if (nKeyLen==3)
		{
			des_set_key(&ctx,uKey+8);
			des_decrypt(&ctx,uTemp,uTemp);
			des_set_key(&ctx,uKey);
			des_encrypt(&ctx,uTemp,uTemp);
		}
	}
	delete []buf;

	if (nKeyLen == 2)
	{
		des_set_key(&ctx,uKey+8);
		des_decrypt(&ctx, uTemp,uTemp);
		des_set_key(&ctx,uKey);
		des_encrypt(&ctx,uTemp,uTemp);
	}
	// temp ����λ ==> MAC
	memcpy(uMac, uTemp, 4 * sizeof(byte)); 
	return 0;
}

int ks_psamcard::doInitOldPsam()
{
	int nRet;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	int uCmdLen=0;
	BYTE uCmd[256];
	string sCmd;
	ks_cpu_cmd_t cmd;
	cmd.recv_buf = ucRespData;
	//ȡ�����
	sCmd="0084000008";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//����DF03���˻�����ָ��MAC
	sCmd="841C000004";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	BYTE uKey[16];
	memcpy(uKey,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);
	BYTE uMac[4];
	CalcMac(ucRespData,uKey,2,uCmd,uCmdLen,uMac);
	memcpy(uCmd+5,uMac,4);
	cmd.send_buf=uCmd;
	cmd.send_len=9;
	cmd.cmd_type=0;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	/////////////////////////////////////////////////////
	sCmd="00A4000002DF04";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}	////////////////////////////////////////////////////////////////////////////////////////////////////
	//ȡ�����
	sCmd="0084000008";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}		//����DF04���˻�����ָ��MAC
	sCmd="841C000004";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	CalcMac(ucRespData,uKey,2,uCmd,uCmdLen,uMac);
	memcpy(uCmd+5,uMac,4);
	cmd.send_buf=uCmd;
	cmd.send_len=9;
	cmd.cmd_type=0;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}		//����MF���˻�
	//�ϵ縴λ
	this->m_PowerOn = 0;
	nRet=this->ResetPSAM();
	if(nRet)
	{
		SET_ERR("SAM�����ϵ縴λ����");
		return nRet;
	}
	sCmd="0084000008";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	sCmd="841C000004";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	CalcMac(ucRespData,uKey,2,uCmd,uCmdLen,uMac);
	memcpy(uCmd+5,uMac,4);
	cmd.send_buf=uCmd;
	cmd.send_len=9;
	cmd.cmd_type=0;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}

int ks_psamcard::RecyclePSAMCard()
{
	int nRet=0;
	byte uCmd[256]={0};
	int uCmdLen=0;
	byte rbuff[256]={0};
	byte ucRespData[256]={0};
	string sCmd;
	//�ϵ縴λ
	this->m_PowerOn = 0;
	nRet=this->ResetPSAM();
	if(nRet)
	{
		SET_ERR("SAM�����ϵ縴λ����");
		return nRet;
	}
	sCmd="0084000008";
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//����MAC
	///////////////////////////////////////////
	sCmd="848A010004800000";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	for(int i=0;i<8;i++)
		uCmd[i]=uCmd[i]^ucRespData[i];
	//����
	des3_context ctx3;
	BYTE uKey[16];
	memcpy(uKey,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);
	des3_set_2keys(&ctx3,uKey,uKey+8);
	des3_encrypt(&ctx3,uCmd,ucRespData);

	memset(uCmd,0,sizeof(uCmd));
	memcpy(uCmd,"\x84\x8A\x01\x00\x04",5);
	memcpy(uCmd+5,ucRespData,4);
	cmd.send_buf=uCmd;
	cmd.send_len=9;
	cmd.cmd_type=0;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
	if(nRet)
	{

		if(cmd.cmd_retcode)
		{
			if(cmd.cmd_retcode==0x6985)
			{
				SET_ERR("��PSAM���ѻ���");
				return nRet;
			}
			else
			{
				GetErrMsgByErrCode(cmd.cmd_retcode,cmd.cmd_retmsg);
				SET_ERR(cmd.cmd_retmsg);
				return nRet;
			}
		}
		else
		{
			m_Reader->GetErrMsg(cmd.cmd_retmsg);
			SET_ERR(cmd.cmd_retmsg);
			return nRet;
		}
	}
	return 0;
}
int ks_psamcard::ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData)
{
	int nRet=0;
	char	szCmd[256];
	byte respLen;
	sprintf(szCmd,"00B0%02X%02X%02X",0x80+ucSFI,ucOffset,ucLength);	
	nRet = this->Adpu4HexSAM(szCmd,strlen(szCmd),ucData,respLen);
	if(nRet)
	{
		SET_ERR(GetErrMsgByErrCode(nRet,NULL));
		return nRet;
	}
	return 0;
}
int ks_psamcard::ReadPSAMCard(ST_PSAMCARD* PSAMCard)
{
	char szBuf[256];
	string sCmd,sMsg;
	int i;
	int ret;
	byte ucRespData[256],ucRespLen;

	//sCmd="00a40000023F00";
	memset(ucRespData,0,sizeof(ucRespData));	
	//ret=Adpu4HexSAM(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	ret=this->selectADFBySFI(MF_SFI);
	if(ret)
	{
		SET_ERR("ѡ��Ŀ¼3F00ʧ��");
		return ret;
	}

	memset(ucRespData,0,sizeof(ucRespData));	
	ret=ReadBinaryFile4Sam(0x15,0x00,14,ucRespData);
	if(ret)
	{
		SET_ERR("��PSAM��0x15�ļ�ʧ��");
		return ret;
	}	
	ST_PSAMCARD15 Psam15;
	memcpy(&Psam15,ucRespData,sizeof(Psam15));

	memset(szBuf,0,sizeof(szBuf));	
	if(Psam15.ucCardNo[0]!=0xFF)
	{
		bcd2asc(Psam15.ucCardNo,sizeof(Psam15.ucCardNo),szBuf);
		for(i=0;i<19;i++)
		{
			if(szBuf[i]!='0')
				break;
		}
		strcpy(PSAMCard->sCardNo,szBuf+i);
		PSAMCard->nCardVer=(int)Psam15.ucCardVerNo;
		PSAMCard->nCardType=(int)Psam15.ucCardType;
	}
	//��ȡ�ն˱��
	memset(ucRespData,0,sizeof(ucRespData));	
	ret=ReadBinaryFile4Sam(0x16,0x00,6,ucRespData);
	if(ret)
	{
		SET_ERR("��PSAM��0x16�ļ�ʧ��");
		return ret;
	}	
	memset(szBuf,0,sizeof(szBuf));	
	bcd2asc(ucRespData,6,szBuf);

	strcpy(PSAMCard->sTermID,szBuf);

	ret=ReadBinaryFile4Sam(0x17,0x00,25,ucRespData);
	if(ret)
	{
		SET_ERR("��PSAM��0x17�ļ�ʧ��");
		return ret;
	}	
	ST_PSAMCARD17 Psam17;
	memcpy(&Psam17,ucRespData,sizeof(Psam17));
	PSAMCard->nKeyIndex=(int)Psam17.ucKeyIndex;

	bcd2asc(Psam17.ucPublishID,sizeof(Psam17.ucPublishID),szBuf);
	for(i=0;i<15;i++)
	{
		if(szBuf[i]!='0')
			break;
	}
	strcpy(PSAMCard->sPublishID,szBuf+i);

	memset(szBuf,0,sizeof(szBuf));
	bcd2asc(Psam17.ucUserID,sizeof(Psam17.ucUserID),szBuf);

	for(i=0;i<15;i++)
	{
		if(szBuf[i]!='0')
			break;
	}
	strcpy(PSAMCard->sUserID,szBuf+i);
 	bcd2asc(Psam17.ucStartDate,sizeof(Psam17.ucStartDate),PSAMCard->sStartDate);
	bcd2asc(Psam17.ucExpireDate,sizeof(Psam17.ucExpireDate),PSAMCard->sExpireDate);
	//	PSAMCard->nCardNo= Psam17.
	//sCmd="00a4000002df03";
	//ret=Adpu4HexSAM(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	ret=this->selectADFBySFI("DF03");
	if(ret)
	{
		SET_ERR("ѡ��Ŀ¼DF03ʧ��");
		return ret;
	}
	memset(ucRespData,0,sizeof(ucRespData));	
	ret=ReadBinaryFile4Sam(0x19,0x00,4,ucRespData);
	if(ret)
	{
		SET_ERR("��PSAM��0x18�ļ�ʧ��");
		return ret;
	}	
	for(i=0;i<4;i++)
		if(ucRespData[i]==0xFF)
			ucRespData[i]=0;
	PSAMCard->nTermSeqno=get_4byte_int(ucRespData);
	return 0;
}

int ks_psamcard::ReadPSAMTermno(char *sTermno)
{
	int nRet=0;
	string sCmd,sMsg;
	char szTermno[13]={0};
	byte rbuff[256]={0};
	byte ucRespData[256]={0};

	//�ϵ縴λ
	nRet=this->ResetPSAM();
	if(nRet)
	{
		SET_ERR("SAM�����ϵ縴λ����["<<m_ReaderPara->cpuport<<"]");
		return nRet;
	}
	nRet=this->selectADFBySFI(MF_SFI);
	if(nRet)
		return nRet;
	//��ȡ�ն˱��
	nRet=ReadBinaryFile4Sam(0x16,0x00,6,ucRespData);
	if(nRet)
	{
		return nRet;
	}	
	bcd2asc(ucRespData,6,szTermno);
	strcpy(sTermno,szTermno);
	return 0;
}
int ks_psamcard::CalcTransMac4Sam(ST_TRANSPACK *transpack,char *sMac)
{
	string sCmd;
	unsigned char uCmd[256],uResp[256],nRespLen;
	int ret;
	char temp[20]="";
	if(strlen(transpack->sCardPhyID)!=16)
	{
		if(strlen(transpack->sCardPhyID)==8)
		{
			strcat(transpack->sCardPhyID,"80000000");
		}
		else
		{
			SET_ERR("�����ų��ȴ���");
		}
	}
	if(strlen(transpack->sTermno)!=12)
	{
		SET_ERR("�ն˱�ų��ȴ���");
		return -1;
	}
	if(strlen(transpack->sTransDate)!=8)
	{
		SET_ERR("�������ڳ��ȴ���");
		return -1;
	}
	if(strlen(transpack->sTransTime)!=6)
	{
		SET_ERR("����ʱ�䳤�ȴ���");
		return -1;
	}
	if(transpack->nTransAmt==0)
	{
		SET_ERR("���׽���Ϊ0");
		return -1;
	}
	/*ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		return ret;
	}*/
	//sCmd = "00A4000002DF03";
	//ret=Adpu4HexSAM((char*)sCmd.c_str(),sCmd.size(),uResp,nRespLen);
	ret=this->selectADFBySFI("DF03");
	if(ret)
	{
		//sMsg=sCmd+":"+ltohex(ret);
		//MessageBox(NULL,sMsg.c_str(),"",MB_OK);
		return ret;
	}
	memset(uCmd,0,sizeof uCmd);
	memset(uResp,0,sizeof uResp);
	sCmd = "807000001C";
	sCmd += transpack->sRandom;
	sprintf(temp,"%04X",transpack->nPayCardCnt);
	sCmd += temp;
	sprintf(temp,"%08X",transpack->nTransAmt);
	sCmd += temp;
	if(transpack->nTransType == ks_cardtype_base::TRNS_TYPE_PURCHASE 
		|| transpack->nTransType == ks_cardtype_base::TRNS_TYPE_POSTPAID)
	{
		sCmd += "06";
	}
	else if(transpack->nTransType == ks_cardtype_base::TRNS_TYPE_CAPP_PURCHASE)
	{
		sCmd += "09";
	}
	else if(transpack->nTransType == ks_cardtype_base::TRNS_TYPE_GRAYLOCK)
	{
		sCmd += "92";
	}
	else
	{
		return -1;
	}
	sCmd += transpack->sTransDate;
	sCmd += transpack->sTransTime;
	sCmd += "0100";
	//sprintf(temp,"%016d",transpack->nCardNo);
	//sCmd += temp;
	sCmd += transpack->sCardPhyID;
	ret=Adpu4HexSAM((char*)sCmd.c_str(),sCmd.size(),uResp,nRespLen);
	if(ret)
	{
		return ret;
	}

	dec2hex(uResp+4,4,sMac);
	transpack->nTermSeqno = get_4byte_int(uResp);
	return 0;
}

int ks_psamcard::CalcSafeMac(const char *cmd,int len,char *sMac)
{
	return 0;
}
int ks_psamcard::CalcDepositMac(ST_TRANSPACK *transpack)
{
	return 0;
}
int ks_psamcard::CalcConsumeMac(ST_TRANSPACK *transpack)
{
	return 0;
}

char * ks_psamcard::GetErrMsgByErrCode( int nErrCode,char *sErrInfo)
{
	switch( nErrCode)
	{
	case 0x9000:
	case 0x0000:
		sprintf(m_ErrMsg,"Err-%04X:�ɹ�",nErrCode);
		break;
	case 0x6200:
		sprintf(m_ErrMsg,"Err-%04X:�����豸�п�δ���뵽λ",nErrCode);
		break;
	case 0x6281:
		sprintf(m_ErrMsg,"Err-%04X:���͵����ݿ��ܴ���",nErrCode);
		break;
	case 0x6283:
		sprintf(m_ErrMsg,"Err-%04X:ѡ���ļ���Ч���ļ�����ԿУ�����",nErrCode);
		break;
	case 0x63C1:
		sprintf(m_ErrMsg,"Err-%04X:�����,����1�λ���",nErrCode);
		break;
	case 0x63C2:
		sprintf(m_ErrMsg,"Err-%04X:�����,����2�λ���",nErrCode);
		break;
	case 0x63C3:
		sprintf(m_ErrMsg,"Err-%04X:�����,����3�λ���",nErrCode);
		break;
	case 0x63C4:
		sprintf(m_ErrMsg,"Err-%04X:�����,����4�λ���",nErrCode);
		break;
	case 0x63C5:
		sprintf(m_ErrMsg,"Err-%04X:�����,����5�λ���",nErrCode);
		break;
	case 0x63C6:
		sprintf(m_ErrMsg,"Err-%04X:�����,����6�λ���",nErrCode);
		break;
	case 0x63C7:
		sprintf(m_ErrMsg,"Err-%04X:�����,����7�λ���",nErrCode);
		break;
	case 0x63C8:
		sprintf(m_ErrMsg,"Err-%04X:�����,����8�λ���",nErrCode);
		break;
	case 0x63C9:
		sprintf(m_ErrMsg,"Err-%04X:�����,����9�λ���",nErrCode);
		break;
	case 0x63CA:
		sprintf(m_ErrMsg,"Err-%04X:�����,����10�λ���",nErrCode);
		break;
	case 0x63CB:
		sprintf(m_ErrMsg,"Err-%04X:�����,����11�λ���",nErrCode);
		break;
	case 0x63CC:
		sprintf(m_ErrMsg,"Err-%04X:�����,����12�λ���",nErrCode);
		break;
	case 0x63CD:
		sprintf(m_ErrMsg,"Err-%04X:�����,����13�λ���",nErrCode);
		break;
	case 0x63CE:
		sprintf(m_ErrMsg,"Err-%04X:�����,����14�λ���",nErrCode);
		break;
	case 0x6400:
		sprintf(m_ErrMsg,"Err-%04X:״̬��־δ�ı�",nErrCode);
		break;
	case 0x6581:
		sprintf(m_ErrMsg,"Err-%04X:дEEPROM���ɹ�",nErrCode);
		break;
	case 0x6700:
		sprintf(m_ErrMsg,"Err-%04X:ָ�������Ȳ���ȷ",nErrCode);
		break;
	case 0x6900:
		sprintf(m_ErrMsg,"Err-%04X:CLA����·����Ҫ��ƥ��",nErrCode);
		break;
	case 0x6901:
		sprintf(m_ErrMsg,"Err-%04X:��Ч��״̬",nErrCode);
		break;
	case 0x6981:
		sprintf(m_ErrMsg,"Err-%04X:�������ļ��ṹ������",nErrCode);
		break;
	case 0x6982:
		sprintf(m_ErrMsg,"Err-%04X:������д���޸Ŀ�Ƭ�İ�ȫ״̬",nErrCode);
		break;
	case 0x6983:
		sprintf(m_ErrMsg,"Err-%04X:��Կ�Ѿ�������",nErrCode);
		break;
	case 0x6984:
		sprintf(m_ErrMsg,"Err-%04X:�������Ч,����ȡ�����",nErrCode);
		break;
	case 0x6985:
		sprintf(m_ErrMsg,"Err-%04X:ʹ������������",nErrCode);
		break;
	case 0x6986:
		sprintf(m_ErrMsg,"Err-%04X:����������ִ������,��ǰ�ļ�����EF",nErrCode);
		break;
	case 0x6987:
		sprintf(m_ErrMsg,"Err-%04X:�ް�ȫ���Ļ�MAC��ʧ",nErrCode);
		break;
	case 0x6988:
		sprintf(m_ErrMsg,"Err-%04X:��ȫ��������MAC����ȷ",nErrCode);
		break;
	case 0x6A80:
		sprintf(m_ErrMsg,"Err-%04X:�������������",nErrCode);
		break;
	case 0x6A81:
		sprintf(m_ErrMsg,"Err-%04X:���ܲ�֧�ֻ�����MF��Ƭ�Ѿ�����",nErrCode);
		break;
	case 0x6A82:
		sprintf(m_ErrMsg,"Err-%04X:��Ƭ���ļ�δ�ҵ�",nErrCode);
		break;
	case 0x6A83:
		sprintf(m_ErrMsg,"Err-%04X:��Ƭ�м�¼δ�ҵ�",nErrCode);
		break;
	case 0x6A84:
		sprintf(m_ErrMsg,"Err-%04X:�ļ����㹻�ռ�",nErrCode);
		break;
	case 0x6A86:
		sprintf(m_ErrMsg,"Err-%04X:����P1P2����",nErrCode);
		break;
	case 0x6A87:
		sprintf(m_ErrMsg,"Err-%04X:�ް�ȫ����",nErrCode);
		break;
	case 0x6A88:
		sprintf(m_ErrMsg,"Err-%04X:��Կδ�ҵ�",nErrCode);
		break;
	case 0x6B00:
		sprintf(m_ErrMsg,"Err-%04X:�ڴﵽLe/Lc�ֽ�֮ǰ�ļ�����,ƫ��������",nErrCode);
		break;
	case 0x6D00:
		sprintf(m_ErrMsg,"Err-%04X:��Ч��INS",nErrCode);
		break;
	case 0x6E00:
		sprintf(m_ErrMsg,"Err-%04X:��Ч��CLA",nErrCode);
		break;
	case 0x6F00:
		sprintf(m_ErrMsg,"Err-%04X:������Ч",nErrCode);
		break;
	case 0x6FF0:
		sprintf(m_ErrMsg,"Err-%04X:������ϵͳ����",nErrCode);
		break;
	case 0xFFFF:
		sprintf(m_ErrMsg,"Err-%04X:�޷��жϵĴ���",nErrCode);
		break;
	case 0x9210:
		sprintf(m_ErrMsg,"Err-%04X:��Ƭ��DF���ڴ治��",nErrCode);
		break;
	case 0x9220:
		sprintf(m_ErrMsg,"Err-%04X:�ļ�ID�Ѵ���",nErrCode);
		break;
	case 0x9240:
		sprintf(m_ErrMsg,"Err-%04X:��Ƭ�ڴ�����",nErrCode);
		break;
	case 0x9302:
		sprintf(m_ErrMsg,"Err-%04X:MAC����",nErrCode);
		break;
	case 0x9303:
		sprintf(m_ErrMsg,"Err-%04X:Ӧ���ѱ�����",nErrCode);
		break;	
	case 0x9400:
		sprintf(m_ErrMsg,"Err-%04X:û��ѡ��ǰ��EF�ļ�ID",nErrCode);
		break;
	case 0x9401:
		sprintf(m_ErrMsg,"Err-%04X:����",nErrCode);
		break;
	case 0x9402:
		sprintf(m_ErrMsg,"Err-%04X:������Χ��û�иü�¼",nErrCode);
		break;
	case 0x9403:
		sprintf(m_ErrMsg,"Err-%04X:��Կδ�ҵ�",nErrCode);
		break;	
	case 0x9404:
		sprintf(m_ErrMsg,"Err-%04X:EF���ļ�IDû���ҵ�",nErrCode);
		break;
	case 0x9406:
		sprintf(m_ErrMsg,"Err-%04X:�����MAC������",nErrCode);
		break;	
	case 0x9802:
		sprintf(m_ErrMsg,"Err-%04X:û����Ҫ����Կ",nErrCode);
		break;
	case 0x9804:
		sprintf(m_ErrMsg,"Err-%04X:��������û�������MAC��",nErrCode);
		break;
	case 0x9810:
		sprintf(m_ErrMsg,"Err-%04X:��Ӧ�ñ�����",nErrCode);
		break;
	case 0x9835:
		sprintf(m_ErrMsg,"Err-%04X:û��ȡ�����",nErrCode);
		break;
	case 0x9840:
		sprintf(m_ErrMsg,"Err-%04X:��KEY����ס",nErrCode);
		break;
	default:
		sprintf(m_ErrMsg,"Err-%04X:��֪���Ĵ���",nErrCode);
		break;
	}
	if(sErrInfo)
		strcpy(sErrInfo,m_ErrMsg);
	return m_ErrMsg;
}
int ks_psamcard::CalcSafeMac4Sam(ks_cardtype_base *cardtype,const char *szCmdbuf,char *szMac)
{
	char szBuf[512];

	string sCmd,sMacData;
	vector<string> CmdVector;
	int nRet;
	int nCmdLen;
	byte uCmd[256];
	byte uResp[256];

	nRet=this->selectADFBySFI("DF03");
	if(nRet)
		return nRet;
	sCmd="801A280108";
	sCmd+=cardtype->m_szCardUID;
	if(strlen(cardtype->m_szCardUID)==8)
		sCmd+="80000000";
	CmdVector.push_back(sCmd);

	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdbuf);
	memcpy(szBuf,szCmdbuf,nCmdBufLen);
	nCmdBufLen/=2;
	if( nCmdBufLen%8 )
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
	else				 
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",16);		

	sMacData=cardtype->m_szRandomNum;
	sMacData+=szBuf;

	int nMacDataLen=sMacData.size()/2;
	const char *pBuf=sMacData.c_str();
	int nBlockLen=0x30;
	if(nMacDataLen>nBlockLen)
	{
		sCmd="80FA0700";
		sCmd+=ltohex(nBlockLen);
		sCmd.append(pBuf,nBlockLen*2);
		CmdVector.push_back(sCmd);
		pBuf+=nBlockLen*2;
		nMacDataLen -= nBlockLen;
		if(nMacDataLen>nBlockLen)
		{
			sCmd="80FA0300";
			sCmd+=ltohex(nBlockLen);
			sCmd.append(pBuf,nBlockLen*2);
			CmdVector.push_back(sCmd);
			nMacDataLen -= nBlockLen;
			pBuf+=nBlockLen*2;
		}
		sCmd="80FA0100";
		sCmd+=ltohex(nMacDataLen);
		sCmd.append(pBuf,nMacDataLen*2);
		CmdVector.push_back(sCmd);
	}
	else
	{
		sCmd="80FA0500";
		sCmd+=ltohex(nMacDataLen);
		sCmd+=sMacData;
		CmdVector.push_back(sCmd);
	}
	//sCmd="00C0000004";
	//CmdVector.push_back(sCmd);

	ks_cpu_cmd_t cmd;
	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			nRet= this->ResetPSAM();
			if(nRet)
			{
				SET_ERR("SAM�����ϵ縴λ����,PSAM������MACʧ�� ����PSAM���Ƿ���ȷ��װ");
				return nRet;
			}
			continue;
		}
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
		int nRet=0;
		memset(&cmd,0,sizeof cmd);
		cmd.cmd_type = 0;
		cmd.send_len = nCmdLen;
		cmd.send_buf = uCmd;
		cmd.recv_buf = uResp;
		nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
		if(nRet)
		{
			if(cmd.cmd_retcode)
			{
				SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL)<<",PSAM������MACʧ��");
				return cmd.cmd_retcode;
			}
			else
			{
				SET_ERR(m_Reader->GetErrMsg(NULL)<<",PSAM������MACʧ��");
				return nRet;
			}
		}
	}
	dec2hex(uResp,4,szMac);
	return 0;
}

int ks_psamcard::CalcExtAuthEncrypt4Sam(ks_cardtype_base *cardtype,int keyidx,const char *szCmdbuf,char *szEncrypt)
{
	char szBuf[512];

	string sCmd,sMacData;
	vector<string> CmdVector;
	int nRet=0;
	byte uResp[256]={0};

	char szCardPhyID[17]={0};
	strncpy(szCardPhyID,cardtype->m_szCardUID,16);
	if(strlen(szCardPhyID)!=16)
	{
		if(strlen(szCardPhyID)==8)
		{
			strcat(szCardPhyID,"80000000");
		}
		else
		{
			SET_ERR("�����ⲿ��֤ʱ�����ų��ȴ���");
			return -1;
		}
	}
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof cmd);
	cmd.recv_buf=uResp;


	nRet=this->selectADFBySFI("DF03");
	if(nRet)
		return nRet;
	//��ɢ��Կ
	sCmd="801A27"+ltohex(keyidx)+"08";
	sCmd+=szCardPhyID;
//	if(strlen(szCardPhyID)==8)
//		sCmd+="80000000";
	CmdVector.push_back(sCmd);

	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdbuf);
	memcpy(szBuf,szCmdbuf,nCmdBufLen);
	nCmdBufLen/=2;
	if( nCmdBufLen%8 )
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);	

	sMacData=szBuf;

	int nMacDataLen=sMacData.size()/2;
	const char *pBuf=sMacData.c_str();
	int nBlockLen=0x30;
	if(nMacDataLen>nBlockLen)
	{
		sCmd="80FA0700";
		sCmd+=ltohex(nBlockLen);
		sCmd.append(pBuf,nBlockLen*2);
		CmdVector.push_back(sCmd);
		pBuf+=nBlockLen*2;
		nMacDataLen -= nBlockLen;
		if(nMacDataLen>nBlockLen)
		{
			sCmd="80FA0300";
			sCmd+=ltohex(nBlockLen);
			sCmd.append(pBuf,nBlockLen*2);
			CmdVector.push_back(sCmd);
			nMacDataLen -= nBlockLen;
			pBuf+=nBlockLen*2;
		}
		sCmd="80FA0100";
		sCmd+=ltohex(nMacDataLen);
		sCmd.append(pBuf,nMacDataLen*2);
		CmdVector.push_back(sCmd);
	}
	else
	{
		sCmd="80FA0000";
		sCmd+=ltohex(nMacDataLen);
		sCmd+=sMacData;
		CmdVector.push_back(sCmd);
	}
	//sCmd="00C0000008";
	//CmdVector.push_back(sCmd);

	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			nRet= this->ResetPSAM();
			if(nRet)
			{
				SET_ERR("SAM�����ϵ縴λ����");
				return nRet;
			}
			continue;
		}
		//string_replace(sCmd," ","");
		//hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
		memset(uResp,0,sizeof(uResp));
		cmd.cmd_type = 1;
		cmd.send_len = sCmd.size();
		cmd.send_buf = (byte*)sCmd.c_str();
		cmd.recv_buf = uResp;
		nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
		if(nRet)
		{
			if(cmd.cmd_retcode)
			{
				SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
				return cmd.cmd_retcode;
			}
			else
			{
				SET_ERR(m_Reader->GetErrMsg(NULL));
				return nRet;
			}
		}
	}
	dec2hex(uResp,8,szEncrypt);
	return 0;
}

int ks_psamcard::InitDll(ks_cardlib_license *lic)
{
	m_license = lic;
	return 0;
}
////////////////////////////////////////////////////////////////////////
int __stdcall register_sam_op(ks_psamcard_base *&sam)
{
	sam = new ks_psamcard();
	return 0;
}