#ifndef  __PUBDEF_H_
#define  __PUBDEF_H_
#include "dictionary.h"
//define db public error
#define SUCCESS   0
#define DB_SUCCESS 0
#define DB_NOTFOUND 100
#ifdef ESQL_DB2
#define DB_REPEAT 	    -803
#define DB_DISCONN	    -1024
#define DB_BADCONN     -900
#endif
#define DB_TIMESTAMP  -818
#define DB_DEADLOCK   -911
#define DB_EXIST 	1

#define CODE_SCHOOL  1000
#define MAX_RATIO	  0.5
#define SUBTYPE_FUND      1  //�ʲ���
#define SUBTYPE_DEBT      2  //��ծ��
#define SUBTYPE_RIGHT    3  //������Ȩ����
#define SUBTYPE_COST      4  //�ɱ���
#define SUBTYPE_INCDEC  5  //������
#define DBCR_DEBIT     1//��
#define DBCR_CREDIT   2 //��
#define DBCR_BOTH      3 //��ͬ

#define USE_CARD_TYPE_NULL		0  	//�޿�����
#define USE_CARD_TYPE_ONLINE	1  	//��������
#define USE_CARD_TYPE_OFFLINE	2  	//�ѻ�����

#define VALUE_NULL   -1 //��ֵ
#define STATE_VALID   1 //��Ч
#define STATE_INVALID   2 //��Ч

#define VOCTYPE_DEFALUT 100    	//����ƾ֤Ĭ������
/*������Կ*/
#define STATIC_SEED_KEY			"1234567890123456"	//���ݿ��д洢�������������Կ
#define WORKTIME_INTERVAL		600  		// ��

/* �豸�������� */
#define PHYTYPE_999_DEV	1000
#define PHYTYPE_HD_DEV		1001
#define PHYTYPE_HUNDURE_DEV 1002
// ���ڵ�ID
#define ROOT_DEVICE_ID	1

//ϵͳ��������
#define KEYTYPE_ACT  			"T_AIF_ACCOUNT"				//�˺�
#define KEYTYPE_CARD_ID  		"T_PIF_CARD"					//����
#define KEYTYPE_CARD_STRU		"T_PIF_CARDSTRUT"			//���ṹ
#define KEYTYPE_CUSTOMER  		"T_CIF_CUSTOMER"			//�ͻ���
#define KEYTYPE_SHOP  			"T_CIF_SHOP"					//�̻���
#define KEYTYPE_SUBSYSTEM 	 	"T_PIF_SUBSYSTEM"			//��ϵͳע���
#define KEYTYPE_DEVICE  			"T_PIF_DEVICE"				//�豸��
#define KEYTYPE_PHYDEVICE  		"T_PIF_PHYDEVICE"				//�豸����ṹ��Ϣ
#define KEYTYPE_DEVTIME  		"T_PIF_DEVTIME"				//�豸����ʱ�������
#define KEYTYPE_DEVASSET  		"T_PIF_DEVASSET"				//�豸�ʲ���
#define KEYTYPE_AREA	 		"T_PIF_AREA"					//�����
#define KEYTYPE_POS_ID  		"T_CIF_SHOP_POS"			//�豸�̻����
#define KEYTYPE_COSHIS		 	"T_TIF_COSUME_HIS"			//������ʷ��
#define KEYTYPE_CHECKOUT	 	"T_TIF_CHECKOUT_HIS"		//������ʷ��
#define KEYTYPE_CHECKOUT_CUR	 "T_TIF_CHECKOUT_CUR"		//��ǰ������ˮ��
#define KEYTYPE_TRADESERIAL	 "T_TIF_TRADESERIAL"			//������ˮ��
#define KEYTYPE_WRITEFAILED    "T_TIF_WRITEFAILED"        //д��ʧ�ܱ�
#define KEYTYPE_DEVICE_COLLECT "T_TIF_DEVICE_COLLECT_LOG" //�豸�ɼ���ʾ��
#define KEYTYPE_MESLIST 		"T_TIF_MESLIST"				//��Ϣ����
#define KEYTYPE_DEVMONITOR  			"T_MIF_DEVMONITOR"			//����豸��
#define KEYTYPE_MIF_CONSUME			"T_MIF_CONSUME"            		//����쳣������ˮ
#define KEYTYPE_MIF_TRAN				"T_MIF_TRAN"             			//����쳣ת����ˮ
#define KEYTYPE_MIF_CARDOPERATE		"T_MIF_CARDOPERATE"           	//����쳣��������ˮ
#define KEYTYPE_MIF_CARDDBINCON		"T_MIF_CARDDBINCON"            	//��ؿ��ⲻƽ�쳣��
#define KEYTYPE_MIF_SYSSTATE			"T_MIF_SYSSTATE"            		//���ϵͳ״̬�쳣��
#define KEYTYPE_MIF_ALARMOP			"T_MIF_ALARMOP"            		//���������¼��
#define KEYTYPE_MIF_TRADESERIALERRORERROR		"T_MIF_TRADESERIALERROR"            		//��ؽ�����ˮ�쳣��
#define KEYTYPE_MIF_TRADESERIALERROR				"T_MIF_TRADESERIAL"            		//������ˮ��
#define KEYTYPE_TMPPERSON		"TMP_PERSON_ID"						//��ʱ ��ԱID
#define KEYTYPE_CUT_INFO_UPD	"T_TIF_CUT_INFO_UPDATE"				// �ͻ���Ϣ���±�ID
#define KEYTYPE_DOOR_CARDLIST	"T_DOOR_CARDLIST"			// ��Ա�����汾
#define KEYTYPE_DOOR_DEVICE_WORKTIME		"T_DOOR_DEVICE_WORKTIME" 	// �Ž��豸����ʱ��α�
#define KEYTYPE_DOOR_HOLIDAY				"T_DOOR_HOLIDAY"			//�Ž��ڼ���
#define KEYTYPE_DOOR_DEV_HLD				"T_DOOR_DEVICE_HOLIDAY_VER"	//�Ž����ڼ��հ汾							//
#define KEYTYPE_MEAL_TYPE					"T_PIF_MEAL_TYPE"	//�̻��ʹζ���
#define KEYTYPE_DOOR_TIMESECT				"T_DOOR_TIME_SECT"  //�Ž�ʱ���
#define KEYTYPE_DOOR_WEEKS				"T_DOOR_WEEKS" //�Ž�ʱ�����
#define KEYTYPE_DOOR_GROUP				"T_DOOR_GROUP" //�Ž���
#define KEYTYPE_DOOR_TIME_GROUP			"T_DOOR_TIMES_GROUP" //�Ž�ʱ�����
#define KEYTYPE_PIF_SUB_UPDATE			"T_PIF_SUB_UPDATE" //��ϵͳ����������


//���㲿��
#define REPORT_SERI_TYPE	1	// ���㲿�� ����������ܱ���� �ֵ����Ϊ 1 Dean 2004-8-17 11:43
#define CUSTSTAT_NORMAL    	0	//�ͻ�״̬--����

//�ڲ��ʺŵĶ���꣬һ�㲻��ı��
#define INNER_ACCOUNT_CASH				"1011"	//�ֽ��ʺ�
#define INNER_ACCOUNT_BANKDEPOSIT      		"1021"	//���д���ʺ�

#define INNER_ACCOUNT_BANKTRANSFER   		"2031"	//���л����ʺ�
#define INNER_ACCOUNT_FINANCETRANSER      	"2041"	//���񻮲��ʺ�


/* ���״���궨��
 *	��ӣ�������
 *	ʱ�䣺2004-11-06
 *	�������TXCODE_ + ʵ���������,��ע:�Ž�ͳһ�涨��
 */
#define TXCODE_BANK_SCHOOL			240001	//Ȧ��ת��
#define TXCODE_BANK_ELEC			242001	//Ȧ��ת�ʵ�����Ǯ��
#define TXCODE_BANK_YCT				242002	//Ȧ��ת�ʵ����ͨ
#define TXCODE_BANK_DETRANS			241011	//Ȧ�����
#define TXCODE_INNERTRANS				240155	//�ڲ��ʺ�ת��
#define TXCODE_WITHDRAWMNGFEE		240156	//�˹����
#define TXCODE_MAKEUPSERIAL			240157	//������ˮ
#define TXCODE_GET_SUBSIDY				240104	//��ȡ����

/* ���״���궨��
 *	��ӣ���Ҷ��
 *	ʱ�䣺2004-09-21
 *	�������TXCODE_ + ʵ���������,��ע:�Ž�ͳһ�涨��
 */
#define TXCODE_AMBIGUITY 				0	 	//����ȷ�Ľ���
#define TXCODE_COSUME_LOG 				930031	//������ˮ
#define TXCODE_SUBSIDY_LOG 			930033	//������ˮ
#define TXCODE_DEPOSIT_LOG  			930034	//��ֵ��ˮ
#define TXCODE_DRAW_DEPOSIT_LOG  		847107	//�ֽ�֧ȡ
#define TXCODE_WITHDRAW_LOG			847107	//ȡ����ˮ
#define TXCODE_CHECKOUT_CUR  			930035	//������ˮ
#define TXCODE_DEPOSITMANAGE_LOG  	930036	//��ֵ������ˮ
#define TXCODE_CARD_LOSS  				930001	//����ʧ��ˮ
#define TXCODE_CARD_COMEBACK_LOSS	930002	//�������ˮ
#define TXCODE_MODIFICATIONPW			930003	//���Ŀ�������ˮ
#define TXCODE_WRITE_ERROR			847108	//��дʧ�ܸ��¿�״̬
#define TXCODE_CARD_OPEN_CASH		847101 	//������ʽ(�ֽ�)
#define TXCODE_CARD_OPEN_BILL			8471012	//������ʽ��(֧Ʊ)
#define TXCODE_CARD_OPEN_FUNDBOOK	8471013 	//������ʽ��(���ѱ�)
#define TXCODE_CARD_OPEN_OTHER		8471014 	//������ʽ��(����)
#define TXCODE_CARD_OPEN_TMP_CASH		847124 	//���м�����ʱ��(�ֽ�)
#define TXCODE_CARD_OPEN_TMP_BILL		8471242	//���м�����ʱ��(֧Ʊ)
#define TXCODE_CARD_OPEN_TMP_FUNDBOOK	8471243 	//���м�����ʱ��(���ѱ�)
#define TXCODE_CARD_OPEN_TMP_OTHER		8471244 	//���м�����ʱ��(����)

#define TXCODE_TEMPCARD_OPEN			847116 	//������ʱ��
#define TXCODE_CALLBACK_CARD			847105	//�ջؿ�
#define TXCODE_SAVING_CASH			847106	//�ֽ��ֵ
#define TXCODE_SAVING_BILL				8471062	//֧Ʊ��ֵ
#define TXCODE_SAVING_FUNDBOOK		8471063	//���ѱ���ֵ
#define TXCODE_SAVING_OTHER			8471064	//������ֵ
#define TXCODE_CASH_DEPOSIT			847107	//�ֽ�֧ȡ
#define TXCODE_TMPCARD_OPEN			847116	//���й�����ʱ��
#define TXCODE_FREEZE_CARD			847117	//���Ῠ
#define TXCODE_UNFREEZE_CARD			847118	//�ⶳ��
#define TXCODE_REWRITE_CARD			847119	//��д��
#define TXCODE_CHANGE_CARD			8471040	//���쿨
#define TXCODE_LOSTNOMALCARD_LOGOUT	8471041	//��ʧ��ʽ��ע��
#define TXCODE_LOSTTMPCARD_LOGOUT	8471042	//��ʧ��ʱ��ע��ת��
#define TXCODE_UNLOSTTMPCARD_LOGOUT	8471043	//�ǹ�ʧ��ʱ��ע��ת��
#define TXCODE_CARD_OPEN_FOR_TEMP	847125 	//���зǼ�����ʱ��
#define TXCODE_CARD_OPEN_VIP_CASH	847126 	//���й����ʱ��(�ֽ�)
#define TXCODE_CARD_OPEN_VIP_BILL		8471262 	//���й����ʱ��(֧Ʊ)
#define TXCODE_CARD_OPEN_VIP_FUNDBOOK	8471263 	//���й����ʱ��(���ѱ�)
#define TXCODE_CARD_OPEN_VIP_OTHER	8471264 	//���й����ʱ��(����)
#define TXCODE_CARD_DBCR				847127 	//�ֹ����
#define TXCODE_SHOP_OPEN				843335 	//�̻�����
#define TXCODE_SHOP_LOGOUT			843336 	//�̻�ע��
#define TXCODE_TX_REVEAL				847183	//���׳���
#define TXCODE_SET_SUBSIDY				847132	//�·�����

// �ϴ�������
#define TXCODE_FAN_PAY_MONEY			847220	//��ֵ���
#define TXCODE_FAN_RUSH_PAY			847221	//������ֵ���

//ˮ��ת��
#define TXCODE_CONSUME              847301   //��Ǯ��תСǮ���ۿ�
#define TXCODE_SAVING_SMALL_PACKET    847300   //СǮ����ֵ
//#define TXCODE_REWRITE_CARD_PACKET   847303    //ˮ�ش�Ǯ����д��
#define TXCODE_RESET_DEVICE  847303             //���������豸
#define TXCODE_COLLECT_IN_ACCOUNT    847306    //�ɼ��ܶ�����

#define TXCODE_FAN_BALANCE			847222	//�̻����ѽ���
#define TXCODE_FAN_RUSH_BALANCE		847223	//�����̻����ѽ���

// ����Ա��Ȩ������
#define TXCODE_ISSUE_AUTHCARD			847226   //������Ȩ��
#define TXCODE_CANCEL_AUTHCARD		847227	//������Ȩ��
#define TXCODE_MODIFY_AUTHCARD		847228	//������Ȩ��
#define TXCODE_LOSS_AUTHCARD			847229	//��ʧ��Ȩ��
#define TXCODE_UNLOSS_AUTHCARD		847230   //�����Ȩ��




/* ���״���궨��
 *	��ӣ�����
 *	ʱ�䣺2004-09-23
 *	�������TXCODE_ + ʵ���������,��ע:�Ž�ͳһ�涨��
 */
#define TXCODE_DEVLOGIN  930054		//�豸ǩ��
#define TXCODE_DEVLOGOUT  930055	//�豸ǩ��
#define TXCODE_OPERLOGIN  820351	//����Ա��½
#define TXCODE_OPERLOGOUT  820352	//����Ա�ǳ�
#define TXCODE_SYSLOGIN  930052	//ǰ�û�ǩ��
#define TXCODE_SYSLOGOUT  930053	//ǰ�û�ǩ��

/*
	XML ��ֵ����
*/
#define XML_KEY_CARDID			 "CARDID"		//����
#define XML_KEY_CLOCK 			 "CLOCK"			//ʱ��(�ϴ����´�)
#define XML_KEY_VERNUM 	 	 "VERNUM"		//�������汾��
#define XML_KEY_NOTVALIDITY	 "NOTVALIDITY"	//��������Ч��
#define XML_KEY_ADDDELSIGN	 "ADDDELSIGN"	//��ɾ��־
#define XML_KEY_CARDTYPE		 "CARDTYPE"		//�����
#define XML_KEY_FEE				 "FEE"			//����
#define XML_KEY_BTTIME			 "BTTIME"	       //�豸�������ʱ����
#define XML_KEY_NAME			"NAME"			//����
#define XML_KEY_AMT			"AMT"			//���
#define XML_KEY_DATE			"DATE"			//����
#define XML_KEY_TIME			"TIME"			//ʱ��
#define XML_KEY_DORM_NO		"DORM_NO"		//�����
#define XML_KEY_DORM_NAME		"DORM_NAME"	//������
#define XML_KEY_CUSTID			"CUSTID"		//�ͻ���
#define XML_KEY_ELEC			"ELEC"			//����
#define XML_KEY_CARDPHY		"PHYNO"			//������
#define XML_KEY_MAJOR_DEV		"MJID"			//���豸��
#define XML_KEY_MINOR_DEV		"MNID"			//���豸��


//�´��豸������
#define XML_KEY_DEVPHY999_NO	"DEVPHY999_ID"		//�ն��豸id
#define XML_KEY_DEV999_NO		"DEV999_NO"		//����
#define XML_KEY_DEV999_ID 		"DEV999_ID"		//ע���
#define XML_KEY_BAUDRATE 		"BAUDRATE"		//������
#define XML_KEY_SYSPWD 		"SYSPWD"		//ϵͳԱ����
#define XML_KEY_ADMPWD		"ADMPWD"		//����Ա����
#define XML_KEY_PWDONOFF 		"PWDONOFF"		//���뿪��
#define XML_KEY_CARDSTR 		"CARDSTR"		//��Ƭ�ṹ
#define XML_KEY_CARDUSENUM 	"CARDUSENUM"	//�������ʹ�ô���\����������Ѵ���
#define XML_KEY_MAXDEPOSIT	"MAXDEPOSIT"	//Ǯ����ߴ���޶�
#define XML_KEY_MINDEPOSIT 	"MINDEPOSIT"	//Ǯ�����ʣ����޶�
#define XML_KEY_RATION			"RATION"			//��ֵ�շѷ�ʽʹ�õĶ�ֵ��\��ֵ���
#define XML_KEY_PUSERNO 		"PUSERNO"		//Ǯ������\Ǯ����
#define XML_KEY_MAXTRADE		"MAXTRADE"		//ÿ�ν�����߶�\��������޶�
#define XML_KEY_VCARDSET 		"VCARDSET"		//�ն˻������û������\����(������128�࿨)
#define XML_KEY_FUNONOFF		"FUNONOFF"		//�շѻ���ǿ���ܿ���


//���ò�������
#define XML_KEY_SUBSIDYONOFF	"SUBSIDYONOFF"	//��������

//�������ѱ�ż��汾
#define XML_KEY_CONCODEVER	"CONCODEVER"	//���ѱ�Ű汾
#define XML_KEY_CONCODE		"CONCODE"		//���ѱ��

//�������ѿ�ݱ��
#define XML_KEY_CONKEYCODE	"CONKEYCODE"	//���ѿ�ݱ��

//��������ʱ��β���
#define XML_KEY_CONCODEVER	"CONCODEVER"	//���ѱ�Ű汾
#define XML_KEY_CONCODE		"CONCODE"		//���ѱ��

//�������ѿ�ݱ��
#define XML_KEY_CONKEYCODE	"CONKEYCODE"	//���ѿ�ݱ��

//��������ʱ��β���
#define XML_KEY_STARTDT		"STARTDT"		//��ʼʱ��
#define XML_KEY_ENDDT			"ENDDT"			//����ʱ��

//�������״̬����
#define XML_KEY_FTFLAG			"FTFLAG"			//�������ñ�־

//�豸����
#define XML_KEY_CONTROLONOFF	"CONTROLONOFF"	//��������ֵ

//�ɼ�������ˮ
#define XML_KEY_FEETYPE		"FEETYPE"		//��������
#define XML_KEY_STARTNUM		"STARTNUM"		//������ʼ��ˮ��
#define XML_KEY_ENDNUM			"ENDNUM"		//����������ˮ��

//�´�������������
#define XML_KEY_SUBSIDYFEE		"SUBSIDYFEE"		//�������
#define XML_KEY_OUTNUM			"OUTNUM"		//��������
#define XML_KEY_SUBSIDYTYPE	"SBSTYPE"		//��������
#define XML_KEY_SUBSIDYFLAG	"SBSFLAG"		//������־

//�´��豸������Ϣ
#define XML_KEY_DEVTYPE		"DEVTYPE"		//���ʹ���
#define XML_KEY_DEVVERSION		"DEVVERSION"	//�豸�汾��
#define XML_KEY_PORTCOUNT		"PORTCOUNT"		//�������˿�����
#define XML_KEY_FDEVPHY_ID		"FDEVPHY_ID"		//�ϼ��豸����ID
#define XML_KEY_PORTNO			"PORTNO"		//�������˿ں�
#define XML_KEY_STATE_ID		"STATE_ID"		//�豸״̬
#define XML_KEY_JOINMODE		"JOINMODE"		//��·ģʽ
#define XML_KEY_COMADD			"COMADD"		//ͨ�ŵ�ַ
#define XML_KEY_PORT			"PORT"			//ͨѶ�˿�
#define XML_KEY_COMTYPE		"COMTYPE"		//����ͨѶ��ʽ
#define XML_KEY_LASTSHUTSERNO	"LASTSHUTSERNO"	//�ն�������ˮ����ĩֵ
#define XML_KEY_LASTSHUTDATE	"LASTSHUTDATE"	//�ն�����ʱ����ĩֵ
#define XML_KEY_LASTTRASERNO	"LASTTRASERNO"	//�ն˽�����ˮ����ĩֵ
#define XML_KEY_LASTTRADATE	"LASTTRADATE"	//�ն˽���ʱ����ĩֵ

#define XML_KEY_OPERATEDATE	"OPERATE_DATE"	//��������
#define XML_KEY_SERIALNO		"SERIAL_NO"		//������ˮ��
#define XML_KEY_TRADECODE		"TRADE_CODE"	//������

#define XML_KEY_WEEKNO			"WEEKNO"		 //����1-8
#define XML_KEY_CARDRIGHTTYPE	"CARDRIGHTTYPE"	 //��Ȩ������
#define XML_KEY_DOORTIME1		"T1"				 //�Ž�ʱ���1
#define XML_KEY_DOORTIME2		"T2"		 		//�Ž�ʱ���2
#define XML_KEY_DOORTIME3		"T3"		 		//�Ž�ʱ���3
#define XML_KEY_DOORTIME4		"T4"		 		//�Ž�ʱ���4
#define XML_KEY_DOORTIME5		"T5"		 		//�Ž�ʱ���5
#define XML_KEY_DOORTIME6		"T6"		 		//�Ž�ʱ���6
#define XML_KEY_DOORTIME7		"T7"		 		//�Ž�ʱ���7
#define XML_KEY_DOORTIME8		"T8"		 		//�Ž�ʱ���8
#define XML_KEY_WEEK_DAY1		"WD1"			//����1
#define XML_KEY_WEEK_DAY2		"WD2"			//����2
#define XML_KEY_WEEK_DAY3		"WD3"			//����3
#define XML_KEY_WEEK_DAY4		"WD4"			//����4
#define XML_KEY_WEEK_DAY5		"WD5"			//����5
#define XML_KEY_WEEK_DAY6		"WD6"			//����6
#define XML_KEY_WEEK_DAY7		"WD7"			//����7
#define XML_KEY_SEQNO			"SEQ"			//���
#define XML_KEY_HOLIDAY		"HOLIDAY"		//�Ž��Ž��ڼ���
#define XML_KEY_WORKMODE		"WORKMODE"		//����ģʽ
#define XML_KEY_LOCK1_TIME		"LOCK1"			//��1����ʱ��
#define XML_KEY_LOCK2_TIME		"LOCK2"			//��2����ʱ��
#define XML_KEY_IS_ALLEYWAY	"ALLEYWAY"		//�Ƿ�ͨ��
#define XML_KEY_IS_SAVE		"SAVE"			//�Ƿ񱣴�򿨼�¼
#define XML_KEY_IS_LCD			"LCD"			//�Ƿ�Һ����ʾ

// д��ʧ�ܱ�־
#define CARDWFAIL_NORMAL		'N'	//��ͨ

// д��ʧ�ܱ�־��¼�ǻ��߷�, ����д��ʧ�ܱ�
#define CARDWFAIL_PACKET_DEAL_FLAG_Y     'Y' // д��Ǯ��ʧ�ܱ��
#define CARDWFAIL_PACKET_DEAL_FLAG_N     'N'

/* 	��ӣ�hanhaidong
 *	ʱ�䣺2004-09-27
 *	�������
 */
 //wen jian add
#define FEETYPE_CASH			'C'				//�շѷ�ʽ--�ֽ�
#define FEETYPE_ACCOUNT		'M'				//�շѷ�ʽ--���������ʻ�
// wenjian add end
#ifndef	SEGSIZE
	#define 	SEGSIZE		1024		//�����ڴ��С
#endif
//#define	SCHOOL_CODE				"XYK00008"		//ԺУ���룭�����ж����
#define	STATIC_KEY					"87906576"		//���нӿڵľ�̬��Կ���������ṩ��


//�������Ͷ���
#define TXTYPE_SAVING_CASH			1	//�ֽ��ֵ
#define TXTYPE_SAVING_BILL			2	//֧Ʊ��ֵ
#define TXTYPE_SAVING_FUNDBOOK	3	//���ѱ���ֵ
#define TXTYPE_SAVING_OTHER		4	//������ֵ

#define TXTYPE_DRAW_CASH			5	//�ֽ�֧ȡ
#define TXTYPE_DRAW_BILL			6	//֧Ʊ֧ȡ
#define TXTYPE_DRAW_FUNDBOOK		7	//���ѱ�֧ȡ
#define TXTYPE_DRAW_OTHER			8	//����֧ȡ

#define TXTYPE_PRE_TOLL_BOARD		9	//Ԥ�մ���
#define TXTYPE_TOLL_BOARD			10	//�̻��մ���
#define TXTYPE_TOLL_CARDCOST		11	//�տ��ɱ���
#define TXTYPE_TOLL_CHARGE			12	//��������
#define TXTYPE_TOLL_DEPOSIT		13	//��Ѻ��
#define TXTYPE_TOLL_DEPRECIATION	14	//ѧУ�մ���
#define TXTYPE_TOLL_MESS_CONSUME	15	//ʳ������

#define TXTYPE_RETURN_DEPOSIT		16	//��Ѻ��
#define TXTYPE_RETURN_BOARD		17	//�˴���

#define TXTYPE_DEDUCT_BALANCE		18	//�ۿ����
#define TXTYPE_DEDUCT_BOARD		19	//�۴���
#define TXTYPE_DEDUCT_DEPOSIT		20	//��Ѻ��

#define TXTYPE_BANK_TRANSFER		21	//����ת��
#define TXTYPE_BANK_PRE_TOLL_BOARD	22	//����ת��Ԥ�մ���
#define TXTYPE_SUBSIDY_CASH			23	//�·�����(�ֽ�)
#define TXTYPE_GET_SUBSIDY				24	//��ȡ����
#define TXTYPE_PRE_TOLL_BOARD_BILL	25	//Ԥ�մ���(֧Ʊ)
#define TXTYPE_PRE_TOLL_BOARD_FUNDBOOK	26	//Ԥ�մ���(���ѱ�)
#define TXTYPE_TOLL_CHARGE_BILL			27	//��������(֧Ʊ)
#define TXTYPE_TOLL_CHARGE_FUNDBOOK		28	//��������(���ѱ�)
#define TXTYPE_TOLL_CARDCOST_BILL			29	//�տ��ɱ���(֧Ʊ)
#define TXTYPE_TOLL_CARDCOST_FUNDBOOK	30	//�տ��ɱ���(���ѱ�)
#define TXTYPE_TOLL_DEPOSIT_BILL			31	//��Ѻ��(֧Ʊ)
#define TXTYPE_TOLL_DEPOSIT_FUNDBOOK		32	//��Ѻ��(���ѱ�)
#define TXTYPE_TOLL_DEPRECIATION_BILL		33	//�տ��۾ɷ�(֧Ʊ)'
#define TXTYPE_TOLL_DEPRECIATION_FUNDBOOK	34	//�տ��۾ɷ�(���ѱ�)
#define TXTYPE_RETURN_DEPOSIT_BILL 			35	//��Ѻ��(֧Ʊ)
#define TXTYPE_RETURN_DEPOSIT_FUNDBOOK 		36	//��Ѻ��(���ѱ�)
#define TXTYPE_RETURN_BOARD_BILL 				37	//�˴���(֧Ʊ)
#define TXTYPE_RETURN_BOARD_FUNDBOOK 		38	//�˴���(���ѱ�)
#define TXTYPE_SUBSIDY_BILL					49	//�·�����(֧Ʊ)
#define TXTYPE_SUBSIDY_FUNDBOOK				50	//�·�����(���ѱ�)
#define TXTYPE_SUBSIDY_PRE_TOLL_BOARD_CASH			51	//����Ԥ�մ���(�ֽ�)
#define TXTYPE_SUBSIDY_PRE_TOLL_BOARD_BILL			52	//����Ԥ�մ���(֧Ʊ)
#define TXTYPE_SUBSIDY_PRE_TOLL_BOARD_FUNDBOOK		53	//����Ԥ�մ���(���ѱ�)

#define DOOR_DEV_WORKTIME_UNUSE_VOL "000000000000"	// �Ž�ʱ���δʹ�õİ汾��־

//add by hhd
#define GLOBLE_SYSPARA_STATIC_KEY 	2006

#define	AUTO_TRANS		1			//�Զ�ת��
#define	SELF_TRANS			2			//����ת��
#define	AUTH_MODE_BANKPWD		1	//ת���������п�����
#define 	AUTH_MODE_SCHOOLPWD		2	//ת������У԰�����룬�ж϶�Ӧ��ϵ
#define 	LOGIN_MODE_STUEMP_NO		1	//��ʧ��½��ʽ����ѧ����
#define	LOGIN_MODE_CUT_NO			2	//��ʧ��½��ʽ����ͻ���	

#endif
