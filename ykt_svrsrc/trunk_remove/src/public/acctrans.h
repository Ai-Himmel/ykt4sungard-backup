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
using namespace std;

#define LOGFLAG_NONE 0		//����¼��ˮ
#define LOGFLAG_SUCC 1		//ֻ��¼�ɹ�������ˮ
#define LOGFLAG_FAIL 2		//ֻ��¼ʧ�ܽ�����ˮ
#define LOGFLAG_ALL  3		//ȫ����¼(�����ɹ���ʧ��)

#define ACCTYPE_CARD  1			//�ֿ��˿��ʻ�
#define ACCTYPE_SHOP  2			//�̻��˺�
#define ACCTYPE_EACC  3			//����Ǯ���˻�
#define ACCTYPE_INNER 4			//�ڲ��ʻ�

#define TYPE_INPUT  1
#define TYPE_CONFIG 2
#define ACCFLAG_CARD   'C'		//���˻�
#define ACCFLAG_EACC   'E'		//�����˻�
#define ACCFLAG_SHOP   'S'		//�̻�
#define ACCFLAG_INNER  'N'		//�ڲ��̶��˻�
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
#define TRANSTYPE_CARDSAVING			201	//�ֿ��˴��
#define TRANSTYPE_CARDSHOPSAVING		202	//�ֿ��˴��(��ֵ�̻�)
#define TRANSTYPE_CARDSUBSIDY			203 //��������
#define TRANSTYPE_BANKTRANS				204 //����Ȧ��ת��

#define TRANSTYPE_CARDDRAW				231	//�ֿ���ȡ��
#define TRANSTYPE_POSPAYMENT			232	//POS����
#define TRANSTYPE_CARDPAYMENT			233	//֧������
#define TRANSTYPE_WATERTRANS			234	//ˮ��ת��
#define TRANSTYPE_MOBILETRANS   		235 //�ֻ�ת��

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
#define TRANSTYPE_SHOPPAYMENT			290	 //�̻����

#define TRANSTYPE_RETURNBOARDFEE		291	 //�̻��˴���
#define TRANSTYPE_SHOPRAKEOFF			292	 //���̻�Ӷ��
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
//�̿��651-660
#define TRANSTYPE_LESS_CARDBAL			651	//�˿�����ת-�����
#define TRANSTYPE_LESS_POSPAYMENT		652  //������ˮ������̿�(��Թ�ʧ��ע����)
#define TRANSTYPE_LESS_SHOPBOARDFEE		653  //������ˮ���Ѷ̿�(��Թ�ʧ��ע����),������̻��մ��ѵ����
#define TRANSTYPE_LESS_SCHOOLBOARDFEE	654  //������ˮ���Ѷ̿�(��Թ�ʧ��ע����),�����ѧУ�մ��ѵ����
#define TRANSTYPE_LESSOUT2MOREIN		655  //���̻��Ϳ�����ע���������,��ˮ��Ӫҵ��֧����Ӫҵ������
//����80-98
#define TRANSTYPE_MANDRCR				700	//�ֹ����

#define OPERRIGHT_SYSTEM				0 //ֻ��ϵͳ����Ա����ʹ��
#define OPERRIGHT_CHECK					1 //��˲���Ա����ʹ��
#define OPERRIGHT_OPER					2 //����Ա����ʹ��

const int  SEQNO_BANK = -1;
const int  SEQNO_REFNO = -10;

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
//	char cardphyid[9];	//������ID
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
    char refno[21];		//����ƾ֤��
    int  revflag;		//0-��������1-��������
    int  termid;		//�ն˱��
	int  termseqno; 	//�ն�������ˮ��
    char sysdate[9];	//ϵͳ����
    char systime[7];	//ϵͳʱ��
    char transdate[9];	//��������
    char transtime[7];	//����ʱ��
    int  branchno;		//����Ա�����
    int  loginsiteno;	//��ǰ��¼��վ��
    char opercode[9];	//����Ա��
    char chkopercode[9];//��˲���Ա
    int  offlineflag;	//�Ƿ���������1-�ѻ�����0-��������
    int  usecardflag;	//1�뿨�й�ϵ�Ľ���0-�뿨�޹�ϵ�Ľ���
    int  cardflag;		//���޿���־(1�п�����0�޿�����)
    int  cardtype;		//������
    char cardphyid[11];	//������
    int  cardno;		//����
    int  purseno;		//Ǯ����
    int  cardcnt;		//�����״���
    int  cardsubsidyno;	//���������κ�
    double  cardbefbal;	//����ǰ�����
    double  cardaftbal;	//���׺����
    char showcardno[11];//��ʾ����
    int  feetype;		//���շ�����
    int  custid;		//�ͻ���
    char custname[61];	//�ͻ���
    char stuempno[31];	//ѧ����    
    int  shopid;		//�̻���
    char cardaccno[21];	//���ʻ���
    char eaccno[21];	//����Ǯ���˺�
    char shopaccno[21]; //�̻��˺�
    char draccno[21];	//����ֵ:�跽�˺�
    char craccno[21];	//����ֵ:�����˺�
    int  fundtype;		//�ʽ����� 1-�ֽ�2-֧Ʊ3-���ѱ�4-�����ʻ����5-���д��
    char voucherno[21];	//ƾ֤��
    char drsubjno[21];	//���ֵ:�跽��Ŀ
    char crsubjno[21];	//���ֵ:������Ŀ
    char draccname[241];//���ֵ:�跽�˻���
    char craccname[241];//���ֵ:�����˻���
    int  transtype;			//��������
    int  subseqno;			//����ˮ��
    double  inputamt;		//������
    double  transamt;		//���׽��
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
    int  iPosdtlMaxDayCnt;		//POS�ѻ���ˮ���δ�ϴ�����
    char sSettleDate[9];		//��������
    char sPreSettleDate[9];		//��һ����������
    char sNextSettleDate[9];		//��һ����������
    char sPosdtlExpireDate[9];	//POS��ˮ��������
    char sRenewAccDate[9];		//��������
    double dAutoRenewAccMaxAmt;	//�Զ���������޶�
    int  iLossEffectTime;		//��ʧ��Ч���ʱ��(����)
    int  iShopBoardFeeFlag;		//�Ƿ����̻��մ���
    int  bEnableCardMgr;		//�Ƿ����ÿ�Ƭ������
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
	int _freeflag;	//�⿨�ɱ��ѻ�Ѻ���־
    string _errmsg;
	string _errtip;
	string _tip;
	char  right; //0-ֻ��ϵͳ����Ա1-��˲���Ա2-ҵ�����Ա3-����ʾ
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
        return _pSelf;
    };
    int Reset();
    int end();
    int GetCfgVerNo(int& cfgverno);
    int UpdateCfgVerNo(char* opercode);
    int CheckCfgUpdate();
	int LoadCfg();
    int LoadInitCfg();
	int LoadDynCfg();
	int LoadErrInfo();
	int SetErrMsg(int errcode,const char *paraval,const char *paraval2=NULL);
	int SetErrMsg(int errcode,int paraval=-9999,int paraval2=-9999);
	int SetErrMsg(int errcode,double paraval=-9999,double paraval2=-9999);
	void SetErrTip(char *errtip);	
	void SetFreeFlag();
	
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
//    int updAcc(char *accno,int dcflag,T_t_cfgsplit& cfgsplit,T_t_account& account);
	int UpdCardAcc(char *accno,int dcflag,int calccardbalflag);
	int UpdShopAcc(char *accno,int dcflag);	
	int UpdNetAcc(char *accno,int dcflag);
	int UpdInnerAcc(char *accno,int dcflag);
    int AddAccDtl(int dcflag);
    int DoSplitTrans();
    int DoTransByTransType();
    int InitTrans();
    virtual int doTrans();
    int doFeeTrans();
    int doMainTrans();
	int doTransEnd();
    int doReverseTrans(char *accdate,int termid,int termseqno);
};
#endif
