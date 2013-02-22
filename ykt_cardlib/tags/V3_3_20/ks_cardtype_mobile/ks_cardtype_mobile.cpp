
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sstream>
using namespace std;

#include "mystring.h"
#include "kscardtype.h"
#include "global_func.h"
#include "ks_cardtype_mobile.h"
#include "ksreader.h"
#include "des.h"
#include "log.h"
#include "ucs2code.h"
#pragma pack(1)	
typedef struct 
{
	byte ucCardStatus;		//卡状态	CHAR
	byte ucCardVerNo[7];	//黑名单版本号 BCD
	byte ucAppType;			//应用类型
	byte ucAppVer;			//应用版本
	byte ucCardNo[10];		//交易卡号
	byte ucSubsidyno[4];	//补助批次号 int32
	byte ucExpireDate[4];	//截止日期
	byte ucFeeType;			//收费类别
	byte ucIssueID[1];		//发卡方ID
}EF_PUBLICAPP;
typedef struct 
{
	byte ucCardType;	//卡类型
	byte ucSex;			//性别
	byte ucName[20];	//姓名
	byte ucIDNo[32];	//身份证号
	byte ucIDType;		//用户证件类型
}EF_USERINFO;

typedef struct 
{
	byte ucLastTransDate[4];	//最后交易日期,BCD
	byte ucDayTotalAmt[3];		//当日累计消费金额,INT24
	byte ucDayMaxAmt[3];		//日累计限额,INT24，单位分
	byte ucCardPwd[3];			//卡密码
	byte ucCustType;			//客户类别,CHAR
	byte ucCustID[4];			//客户号,INT32
	byte ucSchoolCode;			//校区代码,CHAR
	byte ucStuempNo[20];		//学工号，ANSI
	byte ucDeptCode[20];		//部门代码,ANSI
	byte ucUnused[5];			//备用
}EF_PRIVATEAPP;
#pragma pack()

#include "log.h"

CCardTypeMobile::CCardTypeMobile()
{
	set_cardtype_name("ks_cardtype_mobile.dll");
	m_sDefaultPin="1234";
	EF_FIELD EField;
	memset(&EField,0,sizeof(EField));
	//先初始化为0
	if(m_FieldVect.size())
		m_FieldVect.clear();
	if(m_EFMap.size())
		m_EFMap.clear();
	EField.unused=1;
	for(int i=0;i<=CF_END;i++)
		m_FieldVect.push_back(EField);

	assert(sizeof(EF_PUBLICAPP)==30);
	assert(sizeof(EF_USERINFO)==55);
	assert(sizeof(EF_PRIVATEAPP)==64);

	EF_PUBLICAPP	PublicApp;
	EF_USERINFO		UserInfo;
	EF_PRIVATEAPP	PrivateApp;

	//卡状态
	m_FieldVect[CF_CARDSTATUS].unused=0;
	m_FieldVect[CF_CARDSTATUS].offset = &PublicApp.ucCardStatus - (byte*)&PublicApp;
	m_FieldVect[CF_CARDSTATUS].length = sizeof(PublicApp.ucCardStatus);
	m_FieldVect[CF_CARDSTATUS].fid=0x15;
	m_FieldVect[CF_CARDSTATUS].type=FT_INT8;
	//卡版本号
	m_FieldVect[CF_CARDVERNO].unused=0;
	m_FieldVect[CF_CARDVERNO].offset = PublicApp.ucCardVerNo - (byte*)&PublicApp;
	m_FieldVect[CF_CARDVERNO].length = sizeof(PublicApp.ucCardVerNo);
	m_FieldVect[CF_CARDVERNO].fid=0x15;
	m_FieldVect[CF_CARDVERNO].type=FT_BCD;
	//应用类型
	m_FieldVect[CF_APPTYPE].unused=0;
	m_FieldVect[CF_APPTYPE].offset = &PublicApp.ucAppType-(byte*)&PublicApp;
	m_FieldVect[CF_APPTYPE].length = sizeof(PublicApp.ucAppType);
	m_FieldVect[CF_APPTYPE].fid=0x15;
	m_FieldVect[CF_APPTYPE].type=FT_INT8;
	//卡号
	m_FieldVect[CF_CARDNO].unused=0;
	m_FieldVect[CF_CARDNO].offset = PublicApp.ucCardNo-(byte*)&PublicApp;
	m_FieldVect[CF_CARDNO].length = sizeof(PublicApp.ucCardNo);
	m_FieldVect[CF_CARDNO].fid=0x15;
	m_FieldVect[CF_CARDNO].type=FT_BCD_LAPDZERO;
	//补助批次号
	m_FieldVect[CF_SUBSIDYNO].unused=0;
	m_FieldVect[CF_SUBSIDYNO].offset = PublicApp.ucSubsidyno - (byte*)&PublicApp;
	m_FieldVect[CF_SUBSIDYNO].length = sizeof(PublicApp.ucSubsidyno);
	m_FieldVect[CF_SUBSIDYNO].fid=0x15;
	m_FieldVect[CF_SUBSIDYNO].type=FT_INT32;
	//启用日期
	//m_FieldVect[CF_STARTDATE].offset = PublicApp.ucStartDate-(byte*)&PublicApp;
	//m_FieldVect[CF_STARTDATE].length = sizeof(PublicApp.ucStartDate);
	//m_FieldVect[CF_STARTDATE].fid=0x15;
	//m_FieldVect[CF_STARTDATE].type=FT_BCD;
	//有效期
	m_FieldVect[CF_EXPIREDATE].unused=0;
	m_FieldVect[CF_EXPIREDATE].offset = PublicApp.ucExpireDate-(byte*)&PublicApp;
	m_FieldVect[CF_EXPIREDATE].length = sizeof(PublicApp.ucExpireDate);
	m_FieldVect[CF_EXPIREDATE].fid=0x15;
	m_FieldVect[CF_EXPIREDATE].type=FT_BCD;
	//卡结构版本
	m_FieldVect[CF_CARDSTRUCTVER].unused=0;
	m_FieldVect[CF_CARDSTRUCTVER].offset = &PublicApp.ucAppVer-(byte*)&PublicApp;
	m_FieldVect[CF_CARDSTRUCTVER].length = sizeof(PublicApp.ucAppVer);
	m_FieldVect[CF_CARDSTRUCTVER].fid=0x15;
	m_FieldVect[CF_CARDSTRUCTVER].type=FT_INT8;
	//收费类别
	m_FieldVect[CF_FEETYPE].unused=0;
	m_FieldVect[CF_FEETYPE].offset = &PublicApp.ucFeeType - (byte*)&PublicApp;
	m_FieldVect[CF_FEETYPE].length = sizeof(PublicApp.ucFeeType);
	m_FieldVect[CF_FEETYPE].fid=0x15;
	m_FieldVect[CF_FEETYPE].type=FT_INT8;
	//发行方标识
	m_FieldVect[CF_PUBLISHID].unused=0;
	m_FieldVect[CF_PUBLISHID].offset = PublicApp.ucIssueID-(byte*)&PublicApp;
	m_FieldVect[CF_PUBLISHID].length = sizeof(PublicApp.ucIssueID);
	m_FieldVect[CF_PUBLISHID].fid=0x15;
	m_FieldVect[CF_PUBLISHID].type=FT_ANSI;
	//卡类型
	m_FieldVect[CF_CARDTYPE].unused=0;
	m_FieldVect[CF_CARDTYPE].offset = &UserInfo.ucCardType - (byte*)&UserInfo;
	m_FieldVect[CF_CARDTYPE].length = sizeof(UserInfo.ucCardType);
	m_FieldVect[CF_CARDTYPE].fid=0x16;
	m_FieldVect[CF_CARDTYPE].type=FT_INT8;
	//性别
	m_FieldVect[CF_SEX].unused=0;
	m_FieldVect[CF_SEX].offset = &UserInfo.ucSex - (byte*)&UserInfo;
	m_FieldVect[CF_SEX].length = sizeof(UserInfo.ucSex);
	m_FieldVect[CF_SEX].fid=0x16;
	m_FieldVect[CF_SEX].type=FT_INT8;
	//姓名
	m_FieldVect[CF_NAME].unused=0;
	m_FieldVect[CF_NAME].offset = UserInfo.ucName - (byte*)&UserInfo;
	m_FieldVect[CF_NAME].length = sizeof(UserInfo.ucName);
	m_FieldVect[CF_NAME].fid=0x16;
	m_FieldVect[CF_NAME].type=FT_UCS2;
	//身份证号
	m_FieldVect[CF_IDNO].unused=0;
	m_FieldVect[CF_IDNO].offset = UserInfo.ucIDNo - (byte*)&UserInfo;
	m_FieldVect[CF_IDNO].length = sizeof(UserInfo.ucIDNo);
	m_FieldVect[CF_IDNO].fid=0x16;
	m_FieldVect[CF_IDNO].type=FT_ANSI;
	//证件类型
	m_FieldVect[CF_IDTYPE].unused=0;
	m_FieldVect[CF_IDTYPE].offset = &UserInfo.ucIDType - (byte*)&UserInfo;
	m_FieldVect[CF_IDTYPE].length = sizeof(UserInfo.ucIDType);
	m_FieldVect[CF_IDTYPE].fid=0x16;
	m_FieldVect[CF_IDTYPE].type=FT_INT8;

	//最后交易日期
	m_FieldVect[CF_TRANSDATE].unused=0;
	m_FieldVect[CF_TRANSDATE].offset = PrivateApp.ucLastTransDate - (byte*)&PrivateApp;
	m_FieldVect[CF_TRANSDATE].length = sizeof(PrivateApp.ucLastTransDate);
	m_FieldVect[CF_TRANSDATE].fid=0x1B;
	m_FieldVect[CF_TRANSDATE].type=FT_BCD;
	//日累计最大限额
	m_FieldVect[CF_DAYMAXAMT].unused=0;
	m_FieldVect[CF_DAYMAXAMT].offset = PrivateApp.ucDayMaxAmt - (byte*)&PrivateApp;
	m_FieldVect[CF_DAYMAXAMT].length = sizeof(PrivateApp.ucDayMaxAmt);
	m_FieldVect[CF_DAYMAXAMT].fid=0x1B;
	m_FieldVect[CF_DAYMAXAMT].type=FT_INT24;
	//单次累计限额(同日累计最大限额)
	//m_FieldVect[CF_SINGLEMAXAMT].unused=0;
	//m_FieldVect[CF_SINGLEMAXAMT].offset = PrivateApp.ucDayMaxAmt - (byte*)&PrivateApp;
	//m_FieldVect[CF_SINGLEMAXAMT].length = sizeof(PrivateApp.ucDayMaxAmt);
	//m_FieldVect[CF_SINGLEMAXAMT].fid=0x1B;
	//m_FieldVect[CF_SINGLEMAXAMT].type=FT_INT24;
	//卡密码
	m_FieldVect[CF_CARDPWD].unused=0;
	m_FieldVect[CF_CARDPWD].offset = PrivateApp.ucCardPwd - (byte*)&PrivateApp;
	m_FieldVect[CF_CARDPWD].length = sizeof(PrivateApp.ucCardPwd);
	m_FieldVect[CF_CARDPWD].fid=0x1B;
	m_FieldVect[CF_CARDPWD].type=FT_BCD;	
	//客户类别
	m_FieldVect[CF_CUSTTYPE].unused=0;
	m_FieldVect[CF_CUSTTYPE].offset = &PrivateApp.ucCustType - (byte*)&PrivateApp;
	m_FieldVect[CF_CUSTTYPE].length = sizeof(PrivateApp.ucCustType);
	m_FieldVect[CF_CUSTTYPE].fid=0x1B;
	m_FieldVect[CF_CUSTTYPE].type=FT_INT8;
	//客户号
	m_FieldVect[CF_CUSTID].unused=0;
	m_FieldVect[CF_CUSTID].offset = PrivateApp.ucCustID - (byte*)&PrivateApp;
	m_FieldVect[CF_CUSTID].length = sizeof(PrivateApp.ucCustID);
	m_FieldVect[CF_CUSTID].fid=0x1B;
	m_FieldVect[CF_CUSTID].type=FT_INT32;
	//学工号
	m_FieldVect[CF_STUEMPNO].unused=0;
	m_FieldVect[CF_STUEMPNO].offset = PrivateApp.ucStuempNo - (byte*)&PrivateApp;
	m_FieldVect[CF_STUEMPNO].length = sizeof(PrivateApp.ucStuempNo);
	m_FieldVect[CF_STUEMPNO].fid=0x1B;
	m_FieldVect[CF_STUEMPNO].type=FT_ANSI;
	//校区
	m_FieldVect[CF_SCHOOLCODE].unused=0;
	m_FieldVect[CF_SCHOOLCODE].offset = &PrivateApp.ucSchoolCode - (byte*)&PrivateApp;
	m_FieldVect[CF_SCHOOLCODE].length = sizeof(PrivateApp.ucSchoolCode);
	m_FieldVect[CF_SCHOOLCODE].fid=0x1B;
	m_FieldVect[CF_SCHOOLCODE].type=FT_INT8;
	//部门代码
	m_FieldVect[CF_DEPTCODE].unused=0;
	m_FieldVect[CF_DEPTCODE].offset = PrivateApp.ucDeptCode - (byte*)&PrivateApp;
	m_FieldVect[CF_DEPTCODE].length = sizeof(PrivateApp.ucDeptCode);
	m_FieldVect[CF_DEPTCODE].fid=0x1B;
	m_FieldVect[CF_DEPTCODE].type=FT_ANSI;

	//钱包文件
	//卡余额
	m_FieldVect[CF_CARDBAL].unused=0;
	m_FieldVect[CF_CARDBAL].offset =0;
	m_FieldVect[CF_CARDBAL].length =0;
	m_FieldVect[CF_CARDBAL].fid=MONEY_SFID;
	m_FieldVect[CF_CARDBAL].type=FT_INT32;
	m_FieldVect[CF_CARDBAL].rw=RW_R;
	//消费次数
	m_FieldVect[CF_PAYCNT].unused=0;
	m_FieldVect[CF_PAYCNT].offset =0;
	m_FieldVect[CF_PAYCNT].length =0;
	m_FieldVect[CF_PAYCNT].fid=MONEY_SFID;
	m_FieldVect[CF_PAYCNT].type=FT_INT32;
	m_FieldVect[CF_PAYCNT].rw=RW_R;
	//充值次数
	m_FieldVect[CF_DPSCNT].unused=0;
	m_FieldVect[CF_DPSCNT].offset =0;
	m_FieldVect[CF_DPSCNT].length =0;
	m_FieldVect[CF_DPSCNT].fid=MONEY_SFID;
	m_FieldVect[CF_DPSCNT].type=FT_INT32;
	m_FieldVect[CF_DPSCNT].rw=RW_R;

	EFBUF efbuf;
	
	memset(efbuf.ReadBuf,0,sizeof(efbuf.ReadBuf));
	memset(efbuf.WriteBuf,0,sizeof(efbuf.WriteBuf));

	efbuf.FileSize=30;
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x15]=efbuf;

	efbuf.FileSize=55;
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x16]=efbuf;

	//efbuf.FileSize=10;
	//efbuf.ReadRight=FR_MAC;
	//m_EFMap[0x1A]=efbuf;

	efbuf.FileSize=64;
	efbuf.ReadRight=FRR_MAC;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x1B]=efbuf;
	//钱包
	efbuf.FileSize=0;
	efbuf.ReadRight=FRR_NULL;
	efbuf.WriteRight=FRW_NULL;
	m_EFMap[MONEY_SFID]=efbuf;

}
CCardTypeMobile::~CCardTypeMobile()
{
}

int CCardTypeMobile::SelectADF()
{	
	return this->selectADFByName("D1560001018003800000000100001002");
}
int CCardTypeMobile::UpdateKey(const byte ucMainKey[16],byte ucKeyIndex,byte ucKey[16])
{
	int nRet=0;
	byte ucCmd[256]={0};
	byte ucCmdLen=0;
	byte ucOutBuf[128]={0};
	int  iOutLen=0;
	byte ucMac[4]={0};
	byte ucSessionKey[17]={0};
	byte ucRandom[9]={0};
	byte ucPlainKey[20]={0};

	memcpy(ucCmd,"\x84\xD4\x00\x00\x1C",5);
	ucPlainKey[0]=0x13;
	ucPlainKey[1]=ucKeyIndex;
	ucPlainKey[2]=0x01;
	ucPlainKey[3]=0x82;	
	memcpy(ucPlainKey+4,ucKey,16);

	nRet=GetRandomNum(ucRandom);
	if(nRet)
	{
		return nRet;
	}
	//先计算主控会话密钥
	EncryptKey(ucMainKey,2,ucRandom,4,ucSessionKey,iOutLen);
	//用主控会话密钥加密待加密数据
	EncryptKey(ucSessionKey,1,ucPlainKey,20,ucOutBuf,iOutLen);

	memcpy(ucCmd+5,ucOutBuf,iOutLen);
	ucCmdLen=iOutLen+5;
	//计算mac，初始化数据为全0
	memset(ucRandom,0,sizeof(ucRandom));
	CalcMac(ucRandom,ucSessionKey,1,ucCmd,ucCmdLen,ucMac);

	memcpy(ucCmd+ucCmdLen,ucMac,4);
	ucCmdLen+=4;

	byte ucRes[256]={0};
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.send_buf=ucCmd;
	cmd.recv_buf=ucRes;
	cmd.send_len=ucCmdLen;
	cmd.cmd_type=0;//16进制
	
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
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
int CCardTypeMobile::InitUserCard(const char *sShowCardNo)
{
	int nRet=0;
	int iLen=0;
	//char sCardPhyID[17]={0};
	byte ucCardPhyID[9]={0};
	if(!m_CardKeys.bLoad)
	{
		SetLastErrMsg("密钥未装载");
		return -1;
	}
	//寻卡
	nRet=RequestCard();
	if(nRet)
	{
		return nRet;
	}
	if(strlen(m_szCardUID)==8)
		strcat(m_szCardUID,"80000000");
	if(strlen(m_szCardUID)!=16)
	{
		SET_ERR("卡物理ID["<<m_szCardUID<<"]长度错误");
		return -1;
	}
	hex2dec(m_szCardUID,16,ucCardPhyID,iLen);
	
	nRet=SelectADF();
	if(nRet)
	{
		return nRet;
	}
	//先判断该卡是否已经初始化，如果已经初始化，则不更换密钥
	//判断方法:判断补助批次号字段是否已经至0
	//
	byte ucData[128]={0};
	nRet=ReadBinaryFile(0x15,0x00,30,ucData);
	if(nRet)
	{
		return nRet;
	}
	/*
	if(0x02==ucData[9])
	{
		SET_ERR("该卡已经初始化");
		return -1;
	}
	*/
	byte ucMainKey[16]={0};
	byte ucDiverKey[16]={0};

	memset(ucMainKey,0x00,16);	//出厂密钥
	//修改维护密钥
	PbocDiverKey(ucCardPhyID,m_CardKeys.DAMK,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x02,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//修改消费密钥
	PbocDiverKey(ucCardPhyID,m_CardKeys.DPK1,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x03,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//修改充值密钥
	PbocDiverKey(ucCardPhyID,m_CardKeys.DLK1,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x04,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//修改TAC密钥
	PbocDiverKey(ucCardPhyID,m_CardKeys.DTAC,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x05,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//修改PIN解锁密钥
	PbocDiverKey(ucCardPhyID,m_CardKeys.DUK,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x06,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//修改PIN重装密钥
	PbocDiverKey(ucCardPhyID,m_CardKeys.DRPK,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x07,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	byte ucAnsiData[21]={0};
	byte ucUCS2Data[21]={0};
	strcpy((char*)ucAnsiData,"移动e卡通");
	EncodeUCS2((byte*)ucAnsiData,ucUCS2Data);
	nRet=UpdateBinaryFile(0x1A,0,10,ucUCS2Data);
	if(nRet)
	{
		return nRet;
	}
	memset(ucData,0,sizeof(ucData));
	//初始化0x15
	ucData[8]=0x01;//应用类型标识
	ucData[9]=0x02;//应用版本号
	ucData[29]=0x06;//发行方标识
	nRet=UpdateBinaryFile(0x15,0,30,ucData);
	if(nRet)
	{
		return nRet;
	}
	//初始化0x16
	memset(ucData,0,sizeof(ucData));
	nRet=UpdateBinaryFile(0x16,0,55,ucData);
	if(nRet)
	{
		return nRet;
	}
	//初始化0x1B
	memset(ucData,0xFF,sizeof(ucData));
	memset(ucData,0x00,sizeof(ucData)-5);
	nRet=UpdateBinaryFile(0x1B,0,64,ucData);
	if(nRet)
	{
		return nRet;
	}
	//暂时返回
	//修改主控密钥
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x01,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	return 0;
}
//恢复到出厂状态
int CCardTypeMobile::RestoreFactorySettings()
{
	int nRet=0;
	int iLen=0;
	byte ucData[128]={0};
	byte ucCardPhyID[9]={0};
	if(!m_CardKeys.bLoad)
	{
		SetLastErrMsg("密钥未装载");
		return -1;
	}
	//寻卡
	nRet=RequestCard();
	if(nRet)
	{
		return nRet;
	}
	if(strlen(m_szCardUID)==8)
		strcat(m_szCardUID,"80000000");
	if(strlen(m_szCardUID)!=16)
	{
		SET_ERR("卡物理ID["<<m_szCardUID<<"]长度错误");
		return -1;
	}
	hex2dec(m_szCardUID,16,ucCardPhyID,iLen);

	nRet=SelectADF();
	if(nRet)
	{
		return nRet;
	}
	//先判断该卡是否已经初始化，如果已经初始化，则不更换密钥
	//判断方法:判断补助批次号字段是否已经至0
	//
	memset(ucData,0,sizeof(ucData));
	nRet=ReadBinaryFile(0x15,0x00,30,ucData);
	if(nRet)
	{
		return nRet;
	}
	if(0x02!=ucData[9])
	{
		SET_ERR("该卡未初始化,不能回收");
		return -1;
	}
	//先清空信息
	memset(ucData,0xFF,sizeof(ucData));
	nRet=UpdateBinaryFile(0x1A,0,10,ucData);
	if(nRet)
	{
		return nRet;
	}
	//初始化0x15
	memset(ucData,0xFF,sizeof(ucData));
	nRet=UpdateBinaryFile(0x15,0,30,ucData);
	if(nRet)
	{
		return nRet;
	}
	//初始化0x16
	memset(ucData,0xFF,sizeof(ucData));
	nRet=UpdateBinaryFile(0x16,0,55,ucData);
	if(nRet)
	{
		return nRet;
	}
	//初始化0x1B
	memset(ucData,0xFF,sizeof(ucData));
	nRet=UpdateBinaryFile(0x1B,0,64,ucData);
	if(nRet)
	{
		return nRet;
	}
	byte ucMainKey[16]={0};
	byte ucKey[16]={0};
	//计算主控密钥
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,ucMainKey);
	
	memset(ucKey,0xFF,sizeof(ucKey));
	nRet=UpdateKey(ucMainKey,0x02,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x03,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x04,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x05,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x06,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x07,ucKey);
	if(nRet)
	{
		return nRet;
	}
	memset(ucKey,0x00,16);
	nRet=UpdateKey(ucMainKey,0x01,ucKey);
	if(nRet)
	{
		return nRet;
	}
	return 0;
}

int CCardTypeMobile::RequestCard(char* szCardPhyID)
{
	if(m_ReaderPara->cpuport == CARDSLOT_RF)
	{
		return CCardType::RequestCard(szCardPhyID);
	}
	else
	{
		char szCmd[30];
		unsigned char recv_data[30];
		unsigned char recv_len;
		int ret;
		ret = m_Reader->cpucard_poweron(m_ReaderPara,KS_CPUCARD,&recv_len,recv_data);
		if(ret)
		{
			return ret;
		}
		ks_cpu_cmd_t cmd;
		memset(&cmd,0,sizeof(cmd));
		strcpy(szCmd,"3097431800");
		cmd.send_buf=(byte*)szCmd;
		cmd.recv_buf=recv_data;
		cmd.send_len=strlen(szCmd);
		cmd.cmd_type=1;//16进制

		ret = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
		if(ret)
		{
			return ret;
		}

		memset(&cmd,0,sizeof(cmd));
		strcpy(szCmd,"3011111108");
		cmd.send_buf=(byte*)szCmd;
		cmd.recv_buf=recv_data;
		cmd.send_len=strlen(szCmd);
		cmd.cmd_type=1;//16进制

		ret = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
		if(ret)
		{
			return ret;
		}


		dec2hex(recv_data,8,m_szCardUID);
		m_szCardUID[16] = 0;
		if(szCardPhyID)
			strcpy(szCardPhyID,m_szCardUID);
		return 0;
	}
}
int CCardTypeMobile::WriteCard()
{
	int ret;
	std::set<int>::iterator iter = m_EFMap[m_FieldVect[CF_CUSTID].fid].WriteFieldSet.find(CF_CUSTID);
	if(iter != m_EFMap[m_FieldVect[CF_CUSTID].fid].WriteFieldSet.end())
	{
		// 需要对应修改移动门禁文件的客户号！！！
		ret = UpdateDoorCustId();
	}
	ret = CCardType::WriteCard();
	if(ret)
		return ret;
	return 0;
}
int CCardTypeMobile::CalcSafeMacWithKey(const unsigned char *key,const char* szCmdBuf,int szLen,char *szMac)
{
	char szBuf[256];
	byte uCmd[256];
	int nCmdLen;
	string sCmd,sMsg;
	byte uRandom[9]={0},uMac[9]={0};
	int nRet;
	nRet=GetRandomNum(uRandom);
	if(nRet)
	{
		return nRet;
	}
	memset(szBuf,0,sizeof(szBuf));

	byte uDAMK[32]={0};
	byte uCardDAMK[32]={0};
	byte uCardUID[9]={0};;
	int nKeyLen=0;
	hex2dec(szCmdBuf,szLen,uCmd,nCmdLen);
	memcpy(uCardDAMK,key,16);
	hex2dec(m_szCardUID,16,uCardUID,nKeyLen);
	//PbocDiverKey(uCardUID,uDAMK,uCardDAMK);
	CalcMac(uRandom,uCardDAMK,2,uCmd,nCmdLen,uMac);
	dec2hex(uMac,4,szMac);
	return 0;
}
int CCardTypeMobile::UpdateDoorCustId()
{
	byte ucCustId[4];
	EF_FIELD fld;
	int offset,length,ret,custId,i;
	char sCmd[256] = {0};
	byte ucResp[256] = {0};
	char szMac[20] = {0};
	byte ucMainKey[16] = {0};
	char custNoStr[256] = {0};
	ks_cpu_cmd_t cmd;

	fld = m_FieldVect[CF_CUSTID];
	length = fld.length;
	offset = fld.offset;
	memcpy(ucCustId,m_EFMap[fld.fid].WriteBuf+offset,length);
	custId = get_4byte_int(ucCustId);
	memset(custNoStr,0,sizeof custNoStr);
	sprintf(custNoStr,"%d",custId);
	length = strlen(custNoStr);
	memset(custNoStr+length,' ',20-length);
	

#if 0
	dec2hex(m_EFMap[fld.fid].WriteBuf,64,ucResp);
#else
	// 选择门禁目录
	
	ret = this->selectADFByName("D1560001018003800000000100001001");
	if(ret)
		return ret;
#endif

	// 更新的 CMD
	memset(sCmd,0,sizeof sCmd);
	sprintf(sCmd,"04D69A%02X%02X",24,20+4);
	cmd.send_len = strlen(sCmd);

	dec2hex((byte*)custNoStr,20,sCmd+cmd.send_len);
	cmd.send_len = strlen(sCmd);
	memset(ucMainKey,0xFF,sizeof ucMainKey);
	ret = this->CalcSafeMacWithKey(ucMainKey,sCmd,cmd.send_len,szMac);
	if(ret)
	{
		return ret;
	}
	strcat(sCmd,szMac);
	cmd.send_len = strlen(sCmd);
	cmd.cmd_type = 1;
	cmd.send_buf = (byte*)sCmd;
	cmd.recv_buf = ucResp;
	ret = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(ret)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return ret;
		}
	}
	return 0;
}
void CCardTypeMobile::GetSupportCardType(unsigned int cardTypes[],int &cnt)
{
	int i = 0;
	cardTypes[i++] = 0x0501;
	cardTypes[i++] = 0x0300;
	cardTypes[i++] = 0x0400;
	cnt = i;
}
int CCardTypeMobile::checkCardType(int ct)
{
	switch(ct)
	{
	case KS_SIMCARD:
		m_CardTypeCode = 0x0501;
		return 0;
	case KS_CPUCARD:
		m_CardTypeCode = 0x0400;
		return 0;
	default:
		return -1;
	}
}
