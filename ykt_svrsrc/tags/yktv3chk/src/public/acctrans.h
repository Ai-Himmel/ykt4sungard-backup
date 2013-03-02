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
//#include <sstream>
#include <map>
#include <list>
using namespace std;

#define ACCTYPE_CARD  1			//�ֿ��˿��ʻ�
#define ACCTYPE_SHOP  2			//�̻��˺�
#define ACCTYPE_EACC  3			//����Ǯ���˻�
#define ACCTYPE_INNER 4			//�ڲ��ʻ�

#define TYPE_INPUT  1
#define TYPE_CONFIG 2

typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned short	WORD;
#define MAKELONG(feetype,funtype)   ((LONG)(((WORD)(feetype)) | ((DWORD)((WORD)(funtype))) << 16))

typedef struct {
	int  cardflag;		//���޿���־
	int  cardtype;		//������	
	int  feetype;		//�շ�����
	int  cardno;		//����
	int  purseno;		//Ǯ����
	int  cardcnt;		//�����״���
	double  cardbefbal;	//����ǰ�����
	double  cardaftbal;	//���׺����
	int  befbalflag;	//0-���뿨ֵ1-���뿨ֵ
	int  aftbalflag;	//0-�޳���ֵ��1-�г���ֵ
	int  calaftbalflag;	//�Ƿ���Ҫ�������ֵ0-������1-����
	double  transamt;	//���׽��
	double  managefee;	//�����
	char transdate[9];	//��������
	char transtime[7];	//����ʱ��
	char collectdate[9];//�ɼ�����
	char collecttime[7];//�ɼ�ʱ��
	char cardphyid[9];	//������ID
	char devphyid[31];  //�豸����ID
	int  devseqno;		//�豸��ˮ��
	char cardaccno[21];	//���˺�
}CARDTRANSINFO;


typedef struct 
{
	int cardtype;
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

typedef struct {
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
typedef struct {
	int  transcode;		//������
	int  termid;		//�ն˱��
	int  termseqno; 	//�ն���ˮ��
	char accdate[9];	//��������
	char acctime[7];	//����ʱ��
	char transdate[9];	//��������
	char transtime[7];	//����ʱ��		
	int  loginsiteno;	//��ǰ��¼��վ��
	char opercode[9];	//����Ա��
	int  offlineflag;	//�Ƿ���������1-�ѻ�����0-��������
	int  usecardflag;	//1�뿨�й�ϵ�Ľ���0-�뿨�޹�ϵ�Ľ���
	int cardno;			//����
	int  custid;		//�ͻ���
	int  shopid;		//�̻���
	int  feetype;		//�ͻ��շ�����
	int  fundtype;		//�ʽ����� 1-�ֽ�2-֧Ʊ3-���ѱ�4-�����ʻ����5-���д��
	double  inputamt;		//������
	char voucherno[21];	//ƾ֤��
	char dbaccno[21];	//�跽�˺�
	char dbaccname[241];	//�跽�˻���
	char craccno[21];	//�������˺�	
	char craccname[241];	//�����˻���
	int  dbacctype;		//�跽�ʻ�����
	int  cracctype;		//�����ʻ�����
//////////////////////����Ϊ���///////////////////	
	int  transtype;		//��������
	int  subseqno;		//����ˮ��
	double  transamt;		//���׽��
	double  unusedamt; 	//ʣ����
	double  forgift;		//Ѻ����
	char dbsubjno[21];	//�跽��Ŀ
	char crsubjno[21];	//������Ŀ	
	double  dbaccbal;		//�跽�ʻ����
	double  craccbal;		//�����ʻ����	
	double  dbcardaftbal;	//�跽�����
	double  crcardaftbal;	//���������
	double  cardaftbal;	//�����
	char summary[61];	//ժҪ
}TRANS;


typedef map<int,list<CfgFee> > MAPCFGFEELIST;
typedef map<int,list<CfgTrans> >  MAPCFGTRANSLIST;

typedef map<int,T_t_cfgsplit>  MAPCFGSPLIT;


class CAccTrans
{
private:
	MAPCFGTRANSLIST mapTransList;
	MAPCFGSPLIT  mapSplit;
    static CAccTrans *_pSelf;	
	int  _cfgverno;
public:
	MAPCFGFEELIST  mapFeeList;
	CARDTRANSINFO cti;
	TRANS trans;
	string remark;		
	char  cpackdata[2001];
	CAccTrans();
	virtual ~CAccTrans(){};
	static CAccTrans * getInstance() {return _pSelf;};
	void clear();
	int getCfgVerNo(int& cfgverno);
	int checkCfgUpdate();
	int loadCfg();
	int loadCfgFeeList();
	int loadCfgTransList();
	int loadCfgSplit();
	int initOperDtl(char *opercode);
	int addOperDtl(char *opercode=NULL);
	int doForegift(char *cardaccno,int foregiftamt);
	int updAcc(char *accno,char dbcrflag,T_t_cfgsplit& cfgsplit);
    int addAccDtl(char dbcrflag);
	int doSplitTrans();
	int doTransByTransType();
	int doFeeTrans();
	int doMainTrans();
	virtual int doAccTrans();
	int doReverseTrans(char *accdate,int termid,int termseqno);
	//int doReverseTrans(char *accdate,int termid,int termseqno);
};
#endif
