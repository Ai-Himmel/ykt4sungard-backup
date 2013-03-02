/* --------------------------------------------
 * ��������: 2008-06-15
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ������
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/
#ifndef ACCTRANS_H_
#define ACCTRANS_H_
#include "transcode.h"
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include "compare.h"
using namespace std;

#define TERMID_WEB			1 //web
#define TERMID_TEL			2 //�绰�ն�
#define TERMID_SVR		    4 //��������
#define TERMID_SYSTEM		5//��������

#define LOGFLAG_NONE 0		//����¼��ˮ
#define LOGFLAG_SUCC 1		//ֻ��¼�ɹ�������ˮ
#define LOGFLAG_FAIL 2		//ֻ��¼ʧ�ܽ�����ˮ
#define LOGFLAG_ALL  3		//ȫ����¼(�����ɹ���ʧ��)

#define ACCTYPE_CARD  1			//�ֿ��˿��ʻ�
#define ACCTYPE_SHOP  2			//�̻��˺�
#define ACCTYPE_EACC  3			//����Ǯ���˻�
#define ACCTYPE_INNER 4			//�ڲ��ʻ�

typedef enum {
	CS_NORMAL=1,	     // ��״̬���� 
	CS_LOST,    	     // ��״̬��ʧ
	CS_FROZEN,  	     // ��״̬����
	CS_BAD,     	     // ��״̬����
	CS_LOCKED,  	     // ��״̬����
                	                     
	CS_CLOSED,  	     // ��״̬ע��
	CS_UNLOST,  	     // ��״̬δ��ʧ
	CS_UNFROZEN,	     // ��״̬δ����
	CS_UNBAD,   	     // ��״̬�ǻ���
	CS_UNLOCKED, 	     // ��״̬δ����

	CS_EXPIREDATE,		// ����Ч��
	CS_LOSSDATE,		// ����ʧʱ��
	CS_FROZEDATE,		// ������ʱ��
	CS_BADDATE,			// ���Ǽǻ���ʱ��
	CS_LOCKDATE,		// ������ʱ��
	CS_OPENDATE,		// ����ʱ��
	CS_CLOSEDATE,		// ע��ʱ��

}CARD_STATUS;

#define TYPE_INPUT  1
#define TYPE_CONFIG 2
#define ACCFLAG_CARD   'C'		//���˻�
#define ACCFLAG_EACC   'E'		//�����˻�
#define ACCFLAG_SHOP   'S'		//�̻�
#define ACCFLAG_INNER  'N'		//�ڲ��̶��˻�
#define ACCFLAG_INNER_INPUT  'X' //�ڲ��̶��˻�
#define ACCFLAG_FIX    'F'		//�̶��˻�
#define ACCFLAG_INPUT  'I'		//�����˻�

#define SUBJECT_CASH				"1001"			//�ֽ�
#define SUBJECT_BANKACC				"1002"			//���д��
#define SUBJECT_SHEET				"1121"			//Ӧ��Ʊ��
#define SUBJECT_SHEET_BILL			"112101"		//Ӧ��Ʊ��-֧Ʊ
#define SUBJECT_SHEET_OUTLAY		"112102"		//Ӧ��Ʊ��-���ѱ�
#define SUBJECT_CARDSAVING			"2001"			//�������
#define SUBJECT_CARDFOREGIFT		"2002"			//����Ѻ��
#define SUBJECT_ESAVING				"2003"			//�����ʻ����
#define SUBJECT_SHOPINCOME			"2004"			//�̻�Ӫҵ����
#define SUBJECT_SHOPSAVING			"2005"			//�̻����
#define SUBJECT_PROFIT  			"4001"			//��������
#define SUBJECT_INCOME  			"6001"          //Ӫҵ������ 
#define SUBJECT_INCOME_FEE  		"6002"          //����������
#define SUBJECT_INCOME_RAKEOFF 	 	"6003"          //Ӷ������ 
#define SUBJECT_INCOME_BOARD  		"6004"          //��������
#define SUBJECT_INCOME_CARDCOST  	"6005"          //���ɱ�������
#define SUBJECT_INCOME_BACKCARDBAL  "6006"          //�˿�ӯ������
#define SUBJECT_INCOME_DEPRFEE  	"6007"          //�۾ɷ�����
#define SUBJECT_OUT   				"6201"			//Ӫҵ��֧�� 
#define SUBJECT_OUT_SHOP_DISCOUNT   "6202"			//�̻����֧��

//201-204 �ֿ��˽�����-
#define TRANSTYPE_ISSUESAVING			200	//������ֵ
#define TRANSTYPE_CARDSAVING			201	//�ֿ��˴��
#define TRANSTYPE_CARDSHOPSAVING		202	//�ֿ��˴��(��ֵ�̻�)
#define TRANSTYPE_CARDSUBSIDY			203 //��������
#define TRANSTYPE_BANKTRANS				204 //����Ȧ��ת��
#define TRANSTYPE_WATERREFUND			205	//ˮ���˿�
#define TRANSTYPE_ACCSUBSIDY			206 //�������·������첹��
#define TRANSTYPE_GETSUBSIDY			207 //�Ӵ��첹����ȡ
#define TRANSTYPE_BANKSUBSIDY			208	//��������
#define TRANSTYPE_WATERNOBALAREFUND		209	//ˮ�ز�ƽ����˿�
#define TRANSTYPE_BANKCHKADD			210	//Ȧ�油��

#define TRANSTYPE_CARDDRAW				231	//�ֿ���ȡ��
#define TRANSTYPE_POSPAYMENT			232	//POS����
#define TRANSTYPE_CARDPAYMENT			233	//֧������
#define TRANSTYPE_CLOSEDRAW		   		234 //�����˿�
#define TRANSTYPE_WATERTRANS			235	//ˮ��ת��
#define TRANSTYPE_POSPAYCANCEL			236	//����ȡ��
#define TRANSTYPE_CARD2CARD				237	//����ת��
#define TRANSTYPE_WATERDEPOSIT			238	//ˮ�س�ֵ
#define TRANSTYPE_WATERDRAW				239	//ˮ������
#define TRANSTYPE_WATERPAY				240 //�󸶷Ѳ���

//�����˻���41-50				
#define TRANSTYPE_EACCSAVING    		241  //�����˻����
#define TRANSTYPE_CARD2EACC     		242  //�����˻�ת��(���������˻�)
#define TRANSTYPE_BANK2EACC     		243  //�����˻�Ȧ��(���п��������˻�)

#define TRANSTYPE_EACCDRAW				251  //�����˻�ȡ��
#define TRANSTYPE_EACC2CARD				252  //�����˻�ת�˵���(�����˻�����)
#define TRANSTYPE_EACCPAYMENT			253  //֧������

//��ֵ�̻���51-59
#define TRANSTYPE_DEPOSITSHOPSAV		261  //��ֵ�̻����
#define TRANSTYPE_DEPOSITSHOPSAVDISCNT	262  //��ֵ�̻�������
#define TRANSTYPE_DEPOSITSHOPDRAW		271  //��ֵ�̻�ȡ��
#define TRANSTYPE_DEPOSITSHOPDRAWDISCNT	272  //��ֵ�̻������
//�շ��̻���61-70
#define TRANSTYPE_SHOPBOARDFEE			281	 //�̻��մ���
#define TRANSTYPE_SHOPBOARDFEE2			283	// �̻��մ���(Ԥ��ģʽ����ˮ�����������̻�)
#define TRANSTYPE_SHOPPAYMENT			290	 //�̻����

#define TRANSTYPE_RETURNBOARDFEE		291	 //�̻��˴���
#define TRANSTYPE_SHOPREFUND			292	 //�̻��˿�
#define TRANSTYPE_SHOPDRAW				293  //�̻�ȡ��

//����
#define TRANSTYPE_PROFIT				401	//��������
//601-620
#define TRANSTYPE_FOREGIFT				601	//��Ѻ��
#define TRANSTYPE_CARDCOSTFEE   		602	//�տ��ɱ���
#define TRANSTYPE_POUNDAGE				603	//��������
#define TRANSTYPE_BOARDFEE				604	//ѧУ�մ���
#define TRANSTYPE_DEPRFEE				605 //���۾ɷ�
//621-640
#define TRANSTYPE_RETURNFOREGIFT		621	//�˻�Ѻ��
#define TRANSTYPE_RETURNCARDCOSTFEE		622 //�˿��ɱ���
#define TRANSTYPE_RETURNPOUNDAGE		623 //��������
#define TRANSTYPE_RETURNADVBOARDFEE     624 //��ѧУ����
#define TRANSTYPE_RETURNDEPRFEE			625 //���۾ɷ�

#define TRANSTYPE_FOREGIFT2COSTFEE		631	//��Ѻ��ת�ɱ�������
#define TRANSTYPE_CARDBAL2COSTFEE		632 //�����ת���ɱ�������
#define TRANSTYPE_CARDBAL2FORGIFT		633 //�����ת��Ѻ��
//�����-641-650
#define TRANSTYPE_MORE_CARDBAL			641  //�����ת�˿�ӯ��
#define TRANSTYPE_MORE_POSPAYMENT		642  //������ˮ�������(������̻���ˮ)
#define TRANSTYPE_MORE_SHOPBOARDFEE		643  //������ˮ���ѳ���(������̻���ˮ)
#define TRANSTYPE_MORE_CARDBALINCOME	644  //�����תӪҵ������
#define TRANSTYPE_DEDUCTMONEY			645  //�ۿ��

//�̿��651-660
#define TRANSTYPE_LESS_CARDBAL			651	//�˿�����ת-�����
#define TRANSTYPE_LESS_POSPAYMENT		652  //������ˮ������̿�(��Թ�ʧ��ע����)
#define TRANSTYPE_LESS_SHOPBOARDFEE		653  //������ˮ���Ѷ̿�(��Թ�ʧ��ע����),������̻��մ��ѵ����
#define TRANSTYPE_LESS_SCHOOLBOARDFEE	654  //������ˮ���Ѷ̿�(��Թ�ʧ��ע����),�����ѧУ�մ��ѵ����
#define TRANSTYPE_LESSOUT2MOREIN		655  //���̻��Ϳ�����ע���������,��ˮ��Ӫҵ��֧����Ӫҵ������
//����80-98
#define TRANSTYPE_MANDRCR				700	//�ֹ����
#define TRANSTYPE_SHOPRAKEOFF			900	//Ӷ�𻮲�

#define OPERRIGHT_SYSTEM				0 //ֻ��ϵͳ����Ա����ʹ��
#define OPERRIGHT_CHECK					1 //��˲���Ա����ʹ��
#define OPERRIGHT_OPER					2 //����Ա����ʹ��

const int  SEQNO_BANK = -1;				//����Ȧ��
const int  SEQNO_RECORD= -2;			//��¼��
const int  SEQNO_HOSTNO = -5;			//������ˮ��
const int  SEQNO_REFNO = -10;			//һ��ͨʹ��
const int  SEQNO_MEDICAL=-20;			//ҽ��ϵͳ

const int MAXAMT_CARDGTACC=200;			//���ȿ��ƽ���������
#define RS_INIT			0		//��ʼ״̬
#define RS_FAIL			1		//����ʧ��״̬
#define RS_SUCC			2		//���׳ɹ�
#define RS_WAITREV  	3		//һ��ͨ��̨������
#define RS_YKTREVSUCC	4		//���з�������
#define RS_REVSUCC		5		//ȫ�������ɹ�

typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned short	WORD;
#define MAKELONG(feetype,funtype)   ((LONG)(((WORD)(feetype)) | ((DWORD)((WORD)(funtype))) << 16))
#define TIPINFO 	CAccTrans::getInstance()->SetTip
#define ERRTIP 		CAccTrans::getInstance()->SetErrTip
#define ERRINFO 	getpos(__FILE__,__LINE__),CAccTrans::getInstance()->SetErrMsg
//typedef struct {
//	int  cardflag;		//���޿���־
//	int  cardtype;		//������
//	int  feetype;		//�շ�����
//	int  cardno;		//����
//	int  purseno;		//Ǯ����
//	int  cardcnt;		//�����״���
//	double  cardbefbal;	//����ǰ�����
//	double  cardaftbal;	//���׺����
//	int  befbalflag;	//0-���뿨ֵ1-���뿨ֵ
//	int  aftbalflag;	//0-�޳���ֵ��1-�г���ֵ
//	int  calaftbalflag;	//�Ƿ���Ҫ�������ֵ0-������1-����
//	double  transamt;	//���׽��
//	double  managefee;	//�����
//	char transdate[9];	//��������
//	char transtime[7];	//����ʱ��
//	char collectdate[9];//�ɼ�����
//	char collecttime[7];//�ɼ�ʱ��
//	char cardphyid[17];	//������ID
//	char devphyid[31];  //�豸����ID
//	int  devseqno;		//�豸��ˮ��
//	char cardaccno[21];	//���˺�
//}CARDTRANSINFO;


typedef struct
{
    int feetype;
    int transtype;
    int ratetype;
    double rateamt;
    char remark[241];
}CfgFee;
typedef struct
{
    int	transtype;
    int	ratetype;
    double	rateamt;
    char remark[241];
}CfgTrans;

typedef struct
{
    int transcode;		//������
    int  termid;		//�ն˱��
    int  termseqno; 	//�ն���ˮ��
    char accdate[9];	//��������
    char acctime[7];	//����ʱ��
    char transdate[9];	//��������
    char transtime[7];	//����ʱ��
    char opercode[9];	//����Ա��
    int  cardno;		//���׿���
    int  cardflag;		//���޿���־ 1-�п�����0-�޿�����

}BASETRANSINFO;
typedef struct
{
    int  transcode;		//������
    char refno[21];		//���ײο���
    int  revflag;		//0-��������1-��������
    int  termid;		//�ն˱��
    int  termsno;		//�ն˷��ͷ���ˮ��
	int  termseqno; 	//�ն�������ˮ��
    char accdate[9];	//��������
    char acctime[7];	//����ʱ��
    char transdate[9];	//��������
    char transtime[7];	//����ʱ��
    char sysdatetime[15];//ϵͳʱ�� yyyymmddhhmiss
    int  branchno;		//����Ա�����
    int  loginsiteno;	//��ǰ��¼��վ��
    char opercode[9];	//����Ա��
    char chkopercode[9];//��˲���Ա
    int  offlineflag;	//�Ƿ���������1-�ѻ�����0-��������
    int  usecardflag;	//1�뿨�й�ϵ�Ľ���0-�뿨�޹�ϵ�Ľ���
    int  cardflag;		//���޿���־(1�п�����0�޿�����)
    int  calccardbalflag;//���㿨����־
    int  cardtype;		//������
    int  cardphytype;	//����������
    char cardphyid[17];	//������
    char cardpwd[9];	//������
    int  cardno;		//����
    int  purseno;		//Ǯ����
    int  dpscnt;		//����ֵ����
    int  paycnt;		//�����Ѵ���
    int  aftdpscnt;		//����ֵ�����
    int  aftpaycnt;		//�����Ѻ����
    int  transflag;		//�������ͣ�1��ֵ2����
    int  cardsubsidyno;	//���������κ�
    double  cardbefbal;	//����ǰ�����
    double  cardaftbal;	//���׺����
    char showcardno[11];//��ʾ����
    int  feetype;		//���շ�����
    int  custid;		//�ͻ���
    char custname[61];	//�ͻ���
    char stuempno[21];	//ѧ����
    char deptcode[31];	//���ź�
    int  shopid;		//�̻���
    char cardaccno[11];	//���ʻ���
    char eaccno[11];	//����Ǯ���˺�
    char shopaccno[11]; //�̻��˺�
    char draccno[21];	//����ֵ:�跽�˺�
    char craccno[21];	//����ֵ:�����˺�
    int  fundtype;		//�ʽ����� 1-�ֽ�2-֧Ʊ3-���ѱ�4-�����ʻ����5-���д��
    char voucherno[21];	//ƾ֤��
    char drsubjno[21];	//���ֵ:�跽��Ŀ
    char crsubjno[21];	//���ֵ:������Ŀ
    char draccname[61];	//���ֵ:�跽�˻���
    char craccname[61];	//���ֵ:�����˻���
    int  transtype;			//��������
    int  subseqno;			//����ˮ��
    double  inputamt;		//������
    double  transamt;		//���׽��
    double  addamt;			//��д���
    double  unusedamt; 		//ʣ����
    double  totalfeeamt;	//���շѽ��(���)
    double  totaltransamt;	//�ܽ��׽��(���)
    double  forgift;		//Ѻ����
    double  draccbefbal;	//����ǰ�跽�ʻ����
    double  craccbefbal;	//����ǰ�����ʻ����
    double  draccaftbal;	//���׺�跽�ʻ����
    double  craccaftbal;	//���׺�����ʻ����
    char summary[61];		//ժҪ
    int  errcode;			//������
    char remark[241];		//��ע
}TRANS;
typedef struct
{
    int  iRenewCardDayCnt;		//���쿨����
    char sSettleDate[9];		//��������
    char sPreSettleDate[9];		//��һ����������
    char sNextSettleDate[9];		//��һ����������
    char sPosdtlExpireDate[9];	//POS��ˮ��������
    char sRenewAccDate[9];		//���쿨����
    double dAutoRenewAccMaxAmt;	//�Զ���������޶�
    int  iShopBoardFeeFlag;		//�Ƿ����̻��մ���
    int  bEnableCardMgr;		//�Ƿ����ÿ�Ƭ������
    int  iQryMaxCnt;			//��ѯ�������
//    double dCardMaxBal;			//����ֵ���
}SYSPARA;


typedef map<int,list<CfgFee> > MAPCFGFEELIST;
typedef map<int,list<CfgTrans> >  MAPCFGTRANSLIST;

typedef map<int,T_t_cfgsplit>  MAPCFGSPLIT;
typedef map<int,T_t_transcode> MAPCFGTRANSCODE;
typedef map<int,string> MAPERRINFO;
inline string ltos(long l)
{
	char a[20];
	sprintf(a, "%ld", l);
	return string(a);
}
inline string dtos(double l)
{
	char a[32];
	sprintf(a, "%.2lf", l);
	return string(a);
}
inline void split2list(const char *str,const char delim,vector<string>& strlist)
{
    strlist.clear();
    stringstream ss(str);
    while(1)
    {
        string token;
        getline(ss,token,delim);
        if(ss.fail()) 
            break;
        strlist.push_back(token);
    }
}
//ȥ�����˵Ŀո��ַ�
inline string& string_trim(string &str)
{
    const string &delim =" \t\n" ;
    str=str.erase(str.find_last_not_of(delim)+1);
    str=str.erase(0,str.find_first_not_of(delim));
    return str;
}
inline void string_replace(string & strBig, const string & strsrc, const string &strdst) {
    string::size_type pos=0;
    string::size_type srclen=strsrc.size();
    string::size_type dstlen=strdst.size();
    while( (pos=strBig.find(strsrc, pos)) != string::npos){
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
}
//����Ψһ��ˮ��
int GetUniqSno(char *serialno,int type);
//����Ψһ��¼��
int GetRecordNo(char *recordno);
//��������Ψһ��ˮ��
int GetHostSno(char *serialno);

//�����µĽ��ײο���
int GetNewRefno(char *refno);

class CAccTrans
{
private:
	MAPERRINFO   mapErrInfo;
    MAPCFGTRANSLIST mapTransList;
    MAPCFGSPLIT  mapSplit;
    static CAccTrans *_pSelf;
    int _cfgverno;		//���ð汾��
    int _CalcCardBalCnt;//���㿨������
    int _errcode;
	int _freeflag;		//�⿨�ɱ��ѻ�Ѻ���־
	int _summaryflag;	//ժҪ��־
    string _errmsg;
	string _errtip;
	string _tip;
	char  right; //0-ֻ��ϵͳ����Ա1-��˲���Ա2-ҵ�����Ա3-����ʾ
	ST_CPACK* _ReqCpack;
public:
    SYSPARA   	   sysPara;
    MAPCFGTRANSCODE mapCfgTransCode;
    MAPCFGFEELIST  mapFeeList;
    T_t_transcode *_pCfgTransCode;
    TRANS trans;
    string remark;
    char  cpackdata[2001];
    CAccTrans();
    virtual ~CAccTrans(){};
    static CAccTrans * getInstance()
    {
		if(NULL==_pSelf)
		{
			_pSelf=new CAccTrans();
		}
        return _pSelf;
    };
	int Reset(ST_CPACK* rPack=NULL);
    int end();
    int GetCfgVerNo(int& cfgverno);
    int UpdateCfgVerNo(char* opercode);
    int CheckCfgUpdate();
	int LoadCfg();
    int LoadInitCfg();
	int LoadDynCfg();
	int LoadErrInfo();
	int SetErrMsg(const char *errmsg,...);
	int SetErrMsg(int errcode,const char *paraval,const char *paraval2=NULL);
	int SetErrMsg(int errcode,int paraval=-9999,int paraval2=-9999);
	int SetErrMsg(int errcode,double paraval,double paraval2=-9999);
	void SetErrTip(char *errtip,...);	
	void SetFreeFlag();
	void SetSummary(const char *summary);
	void SetTip(char *tip);
	string& GetTip();
	string& GetErrTip();
	string& GetErrMsg(int errcode=0);
	string& GetErrMsgTip(int errcode=0);
    int LoadCfgTransCode();
    int LoadCfgFeeList();
    int LoadCfgTransList();
    int LoadCfgSplit();
    int LoadSysPara(bool lockflag=false);
    int GetTermSeqno(int termid=0);
    T_t_transcode* getCfgTranscode(int transcode=0);
    int doForegift(char *cardaccno,double foregiftamt);
	int UpdCardAcc(char *accno,int dcflag,int calccardbalflag);
	int UpdShopAcc(char *accno,int dcflag);	
	int UpdNetAcc(char *accno,int dcflag);
	int UpdInnerAcc(char *accno,int dcflag);
    int AddAccDtl(int dcflag);
    int DoSplitTrans();
    int DoTransByTransType();
	void SetCardCntAndCardBal(int dpscnt,int paycnt,double cardbal);		
	void SetCardCntAndCardBal(int dpscnt,int paycnt,int cardbal);
	void SetInputAmt(double amount);
    int InitTrans();
    virtual int doTrans();
    int doFeeTrans();
    int doMainTrans();
	int doTransEnd();
    int doTodayReverseTrans(char *accdate,int termid,int termseqno);
	int doHistoryReverseTrans(char *accdate,int termid,int termseqno);
public:
	// ��������
	CAccTrans& CardExpect(CARD_STATUS idx)
	{
		// ����Ҫ�����
		if(checkResult != 0)
			return *this;

		if(checkCard == NULL)
		{
			checkResult = 1;
			return *this;
		}
		switch(idx)
		{
		case CS_NORMAL:
			checkResult = (checkCard->status[0] == '1');
			break;
		case CS_LOST:
			checkResult = (checkCard->lossflag[0] == '1');
			break;
		case CS_FROZEN:
			checkResult = (checkCard->frozeflag[0] == '1');
			break;
		case CS_BAD:
			checkResult = (checkCard->badflag[0] == '1');
			break;
		case CS_LOCKED:
			checkResult = (checkCard->lockflag[0] == '1');
			break;
		case CS_CLOSED:
			checkResult = (checkCard->status[0] == '2');
			break;
		case CS_UNLOST:
			checkResult = (checkCard->lossflag[0] == '0');
			break;
		case CS_UNFROZEN:
			checkResult = (checkCard->frozeflag[0] == '0');
			break;
		case CS_UNBAD:
			checkResult = (checkCard->badflag[0] == '0');
			break;
		case CS_UNLOCKED:
			checkResult = (checkCard->lockflag[0] == '0');
			break;
		default:
			checkResult = 0;
			break;
		}
		if(checkResult)
			checkResult = 0;
		else
		{
			checkResult = 1;
			checkCardMsg<<"���״̬["<<idx<<"]����";
		}
		return *this;
	}
	template<class T>
	CAccTrans& CardExpectEx(CARD_STATUS idx,T compare)
	{
		// ����Ҫ�����
		if(checkResult != 0)
			return *this;

		if(checkCard == NULL)
		{
			checkResult = 1;
			return *this;
		}
		switch(idx)
		{
		case CS_NORMAL:
		case CS_CLOSED:
			checkResult = compare.Compare(checkCard->status[0]);
			break;
		case CS_LOST:
		case CS_UNLOST:
			checkResult = compare.Compare(checkCard->lockflag[0]);
			break;
		case CS_FROZEN:
		case CS_UNFROZEN:
			checkResult = compare.Compare(checkCard->frozeflag[0]);
			break;
		case CS_BAD:
		case CS_UNBAD:
			checkResult = compare.Compare(checkCard->badflag[0]);
			break;
		case CS_LOCKED:
		case CS_UNLOCKED:
			checkResult = compare.Compare(checkCard->lockflag[0]);
			break;
		case CS_EXPIREDATE:
			checkResult = compare.Compare(checkCard->expiredate);
			break;
		case CS_LOSSDATE:
			checkResult = compare.Compare(checkCard->lossdate);
			break;
		case CS_FROZEDATE:
			checkResult = compare.Compare(checkCard->frozedate);
			break;
		case CS_LOCKDATE:
			checkResult = compare.Compare(checkCard->lockdate);
			break;
		case CS_BADDATE:
			checkResult = compare.Compare(checkCard->baddate);
			break;
		default:
			checkResult = 1;
			return *this;
		}
		if(checkResult)
			checkCardMsg<<"���״̬["<<idx<<"]����";
		return *this;

	}
	template<class T,class U>
	CAccTrans& ExpectValue(T& v,U compare,int ErrCode,const char *errmsg = NULL)
	{
		int ret;
		if(checkResult !=0 )
			return *this;
		ret = compare.Compare(v);
		if(ret)
		{
			if(ErrCode!=0)
				checkResult = ErrCode;
			else
				checkResult = E_COMMON_ERR;
			if(errmsg)
				checkCardMsg<<errmsg;
			else
				checkCardMsg<<"������";
		}
		return *this;
	}
	CAccTrans& CheckCardStatus(T_t_card *card)
	{
		checkCard = card;
		checkResult = 0;
		checkCardMsg.str("");
		return *this;
	}
	CAccTrans& CheckCardStatus(int cardno,T_t_card *card);
	int CheckExpect()
	{
		int ret = checkResult;
		checkResult = 0;
		checkCard = NULL;
		return ret;
	}
	int CheckAcc(T_t_card *card,T_t_account *account=NULL,T_t_transdtl *dtl=NULL);
	int GenTransdtl(T_t_transdtl *dtl,int status);
private:
	int checkResult;
	T_t_card *checkCard;
	std::stringstream checkCardMsg;
};

int acc_process();
#endif
