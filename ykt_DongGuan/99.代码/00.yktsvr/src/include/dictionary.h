/*: ���������ֵ��
  ����  : ����
  ʱ��	��2004-08-12
*/

#ifndef  __DICTIONARY_H_
#define  __DICTIONARY_H_
#define SYSPARA_APPNAME				100		//Ӧ��ϵͳ����
#define SYSPARA_MAXBLACKCARDVERNO 	101		//���������汾��
#define SYSPARA_MAXCARDVERNO 		102		//��������汾��
#define SYSPARA_UPLOADDIR			103		//�ϴ��ļ�Ŀ¼
#define SYSPARA_MAXNUMCARDNO		104		//�������ɿ����������
#define CARDVERTYPE_CARDOPEN		1		//������
#define CARDVERTYPE_CARDCLOSE   		2		//������
#define CARDVERTYPE_CARDLOSS    		3		//����ʧ
#define CARDVERTYPE_CARDFROZE   		4		//���Ῠ
#define CARDVERTYPE_CARDINSTEADNEW 5		//����
#define CARDVERTYPE_CARDUNLOSS  	6		//�����
#define CARDVERTYPE_CARDUNFROZE 	7		//�ⶳ��
#define CARDVERTYPE_CARDINSTEADOLD 8		//�����ɿ�

#define MERCHSTATUS_NORNAL 			1		//����
#define MERCHSTATUS_CLOSE  			2		//����
#define MERCHSTATUS_FROZE  			3		//����

#define PAYTYPE_CASH				1		//�ֽ�
#define PAYTYPE_BILL					2		//֧Ʊ
#define PAYTYPE_OUTLAY				3		//���ѱ�	
#define PAYTYPE_ACC					4		//�����˻�

#define EXTTYPE_SUBSIDYNO			1		//�������κ�
#define EXTTYPE_BANKCARD			2		//���п���
#define EXTTYPE_MOBILE				3		//�ֻ���
#define EXTTYPE_OLDCARD				4		//�Ͽ�����
#define EXTTYPE_NEWCARD				5		//�¿�����
#define EXTTYPE_OPPACCNO			6		//�Է��˺�
#define EXTTYPE_OPPSNO				7		//�Է�ѧ��

#define SUBJMAPTYPE_CARDACCNO		1		//���˻�
#define SUBJMAPTYPE_CARDFOREGIFT	2		//��Ѻ���˻�

#define SUBJMAPTYPE_NETACCNO		8		//����Ǯ��

#define SUBJMAPTYPE_SHOPACCNO		9		//�̻��˻�


#define CARDPHYTYPE_CPU				10		//CPU
#define CARDPHYTYPE_CPUMF1			11		//CPU
#define CARDPHYTYPE_MF1				20		//MF1
#define CARDPHYTYPE_RFID			30		//RFID�ֻ���
#define CARDPHYTYPE_SAM				40		//SAM
#define CARDPHYTYPE_DEFAULT   		999//Ĭ�Ͽ���������

#define BWCS_SUCCESS   4  //д���ɹ�
#define BWCS_INIT     	     1  //δ����д��
#define BWCS_FAILD         2  //д��ʧ��
#define BWCS_UNDOUBT  3  //д��ʧ����;�ο�


#define BFS_INIT					'I' //��ʼ
#define BFS_CHKSUM					'M' //��֤�����Դ���
#define BFS_GETFILE 				'F'	//�����ļ���
#define BFS_CVT						'V'	//ת����
#define BFS_CHK						'C'	//������
#define BFS_SUCC					'S'	//���
#define BFS_CHKTAC					'T' //TAC��֤�ɹ�
#define BFS_TACERR					'U' //TAC��֤ʧ��
#define BFS_ERROR					'E' //�쳣״̬
#define BFS_INVALID					'D' //��Ч�ļ�

#define TS_TACOK					'T' //TAC��֤ͨ��
#define TS_TACERR					'U'	//TAC��֤ʧ��

#define CHKRESULT_INIT 		 		'I'	//�ȴ�����
#define CHKRESULT_OK 			 	'='	//��ȫһ��
#define CHKRESULT_DIFF	 	 	 	'X'	//���߲����
#define CHKRESULT_LOCAL_NOTEXIST 	'N'	//���ز�����
#define CHKRESULT_LOCAL_NOTACC   	'U'	//����δ����
#define CHKRESULT_BANK_NOTEXIST	 	'B'	//���в�����

#define MADESTATUS_WAITPAYFEE		1	//�ȴ��ɿ��ɱ���
#define MADESTATUS_WAITCHECK		2	//�ȴ���ݸ�����
#define MADESTATUS_WAITAPROVE		3	//�ȴ��ƿ����
#define MADESTATUS_WAITMAKECARD	4	//�ȴ������ƿ�
#define MADESTATUS_MAKECARDSTART	5	//������ʼ�ƿ�
#define MADESTATUS_MAKECARDEND	6	//�����ƿ�����
#define MADESTATUS_WAITISSUE		7	//�ȴ�����
#define MADESTATUS_ISSUED			8	//�ѷ���
//#define APPLYSTATUS_CANCEL			9     //�ѳ���

#define MERCHDEVSTATUS_NODEV		1	//δ����
#define MERCHDEVSTATUS_BINDDEV		2	//�ѷ���
#define MERCHDEVSTATUS_ENABLED		3	//����
#define MERCHDEVSTATUS_DISABLED	4     //ͣ��

#define POSSTATUS_AVAIL  	'A'
#define POSSTATUS_USED  	'U'
#define POSSTATUS_MAINTAIN  'M'
#define POSSTATUS_DISCARD   'D'

#define TRANSTATUS_INIT		1			//���׳�ʼ
#define TRANSTATUS_FAIL		2			//����ʧ��
#define TRANSTATUS_SUCC		3			//���׳ɹ�
#define TRANSTATUS_CANCEL	4			//����ȡ��
#define TRANSTATUS_EXCEPT	5			//�����쳣
#define TRANSTATUS_BREAK	6			//�����ж�
#define TRANSTATUS_ABORT	7			//������ֹ

#define TRANSTYPE_DEPOSIT			10	//��ֵ
#define TRANSTYPE_DPSCASH			11   //�ֽ��ֵ
#define TRANSTYPE_DPSBANKCARD		12   //���п���ֵ
#define TRANSTYPE_DPSBILL			13   //֧Ʊ��ֵ
#define TRANSTYPE_PAYMENT			20	//����
#define TRANSTYPE_TRANSFEROUT		30	//ת��
#define TRANSTYPE_TRANSFERIN		32	//ת��
#define TRANSTYPE_COSTFEE			40	//�۷�
#define TRANSTYPE_FEE				50    //������
#define TRANSTYPE_OTHER				99    //����

#define RESOLVED_CLOSE				'C'	//�ر�
#define RESOLVED_EXCEPT				'E'	//�쳣
#define RESOLVED_ACC	 	 	 	'A'	//һ��ͨ�Ѽ���
#define RESOLVED_IGN	 	 	 	'I'	//����
#define RESOLVED_PAUSE				'P'	//�ݲ�����

#define RESOLVED_ACC	 	 	 	'A'	//һ��ͨ�Ѽ���
#define RESOLVED_IGN	 	 	 	'I'	//����


#define OPER_SYSTEM_KEY	"system"
#define DCFLAG_DEBIT				1     //�跽
#define DCFLAG_CREDIT				2     //����
// �û�Ĭ������,����Ϊ6���ַ�
#define DEFAULT_CUST_PWD	"666666"
#define TF_DPS				1		//��ֵ
#define TF_PAY				2		//����

#define POSDATATYPE_REALTIMESEND		1   //ʵʱ������ˮ
#define POSDATATYPE_AUTOSEND			2   //�ϴ��ѻ���ˮ(�Զ�)
#define POSDATATYPE_BYHANDSEND			3   //�ϴ��ѻ���ˮ(�ֶ�)
#define POSDATATYPE_COLLSEND			4   //�����ѻ���ˮ
#define POSDATATYPE_IMPORT				5   //�����ѻ���ˮ

#define BANKCODE            "00"


#define APPLYTYPE_OPENCARD				1
#define APPLYTYPE_CHANGECARD			2
#define APPLYTYPE_RENEWCARD			3
#define APPLYTYPE_LOSTCARD				4
#define APPLYTYPE_UNLOSTCARD			5
#define APPLYTYPE_CLOSECARD			6

#define APPLYSTATUS_ACCEPT				1
#define APPLYSTATUS_CANCEL				2
#define APPLYSTATUS_PROCESS			3
#define APPLYSTATUS_SUCC				4

#define CARDSTATUS_NORMAL				1	//��ʹ��(�ѷ���)
#define CARDSTATUS_NEW					2	//������
#define CARDSTATUS_APROVE				3	//�����
#define CARDSTATUS_MAKE					4	//���ƿ�
#define CARDSTATUS_MAKING				5	//�ƿ���
#define CARDSTATUS_MADE					6	//�ƿ����
#define CARDSTATUS_MAKE2				7      //�������ƿ�(���ź�ƽ)
#define CARDSTATUS_MAKEING2			8      //�����ƿ���(���ź�ƽ)
#define CARDSTATUS_ISSUE				9	//������
#define CARDSTATUS_CHANGE				10	//������
#define CARDSTATUS_RENEW				11	//������				
#define CARDSTATUS_LOSS					12	//����ʧ
#define CARDSTATUS_UNLOST				13	//�����
#define CARDSTATUS_CLOSE				14	//������
#define CARDSTATUS_LOST					15	//��ʧ
#define CARDSTATUS_LOCKED				16	//����(��ʧ)
#define CARDSTATUS_STOPPAY				17    //ֹ��
#define CARDSTATUS_CLOSED				99	//����

#define MADESTATUS_WAITPAYFEE		1	//�ȴ��ɿ��ɱ���
#define MADESTATUS_WAITCHECK		2	//�ȴ���ݸ�����
#define MADESTATUS_WAITAPROVE		3	//�ȴ��ƿ����
#define MADESTATUS_WAITMAKECARD	4	//�ȴ������ƿ�
#define MADESTATUS_MAKECARDSTART	5	//������ʼ�ƿ�
#define MADESTATUS_MAKECARDEND		6	//�����ƿ�����
#define MADESTATUS_WAITISSUE		7	//�ȴ�����
#define MADESTATUS_ISSUED			8	//�ѷ���

/*
	�ͻ����	1	 '�̻�'
	�ͻ����	10	'��ְ��ְ��'
	�ͻ����	11	'��ʿ��'
	�ͻ����	12	'����'
	�ͻ����	13	'����'
	�ͻ����	20	'����ҽԺ'
	�ͻ����	30	'��ʿ�о���'
	�ͻ����	31	'˶ʿ�о���'
	�ͻ����	32	'רҵѧλ�о���'
	�ͻ����	33	'��ѧ��'
	�ͻ����	40	'����'
	�ͻ����	41	'ר��'
	�ͻ����	42	'��ְ'
	�ͻ����	43	'����ѧԺ'
	�ͻ����	45	'��������ѧԺ'
	�ͻ����	46	'������ѧ��'
	�ͻ����	50	'����'
	�ͻ����	51	'У����Ա'
	�ͻ����	52	'��Ҫ����'
	�ͻ����	53	'����ѧ��'
*/
#define MEALTYPE_BREAKFAST		1
#define MEALTYPE_LUNCH			2
#define MEALTYPE_SUPPER			3
#define MEALTYPE_NIGHT			4

#define STATUS_NORMAL			'1'
#define STATUS_DELETE			'2'

#define OPERSTATUS_NORMAL		1
#define OPERSTATUS_CLOSE		2

#define TERMTYPE_OPER			'1'
#define TERMTYPE_DEV			'2'
#define TERMTYPE_ATM			'3'

#define NEWCARDSTATUS_INIT				1				//��ʼ״̬
#define NEWCARDSTATUS_UPDOLDCARDFAIL	2				//�ɿ���Ϣ���ʧ��
#define NEWCARDSTATUS_UPDNEWCARDFAIL	3				//�¿���Ϣд��ʧ��
#define NEWCARDSTATUS_SUCCESS			4				//�����ɹ�


#define DTLSTATUS_INIT			'1'
#define DTLSTATUS_FAIL			'2'				//ʧ����ˮ
#define DTLSTATUS_SUCCESS		'3'				//����ɹ���ˮ
#define DTLSTATUS_EXCEPT		'4'				//�쳣��ˮ
#define DTLSTATUS_INVALID		'5'				//��Ч��ˮ
#define DTLSTATUS_REPEAT		'6'				//�ظ���ˮ
#define DTLSTATUS_CANCEL		'7'				//��;�ο���ˮ


#define CARDUSETYPE_GET			1			//����
#define CARDUSETYPE_REUSE		2			//����
#define CARDUSETYPE_USE			3			//����
#define CARDUSETYPE_DISABLE		4			//����
#define CARDUSETYPE_PUT			5			//�Ͻ�
#define CARDUSETYPE_DISABLEREV	6			//��������

#define CARDUSESTATUS_UNUSED	1			//δʹ��
#define CARDUSESTATUS_USED		2			//��ʹ��
#define CARDUSESTATUS_DISABLE	3			//����


#define BANKCARDTMPSTATUS_INVALID 	1		//��Ч
#define BANKCARDTMPSTATUS_ACCEPT	2		//�ѽ��յȴ�����
#define BANKCARDTMPSTATUS_FAIL		3		//����ʧ��
#define BANKCARDTMPSTATUS_SUCC		4		//����ɹ�

#define CARDTYPE_TEMP			99			//������ʱ��
//#define CARDTYPE_ANONYMOUS      2			//������

#define CARDBADFLAG_MANMADE			'1'			//��Ϊ��
#define CARDBADFLAG_QUALITY			'2'			//������
#define CARDBADFLAG_ACCBAL			'3'			//��������
#define CARDBADFLAG_CARDBAL			'4'			//��������

/***************************************************
 * �ƻ�����״̬˵��
 * PUSHTASK_NEW
 */
#define PUSHTASK_NEW		1
#define PUSHTASK_RUN		2
#define PUSHTASK_FAILED		3
#define PUSHTASK_ERROR		4
#define PUSHTASK_EXPIRED	5
#define PUSHTASK_SUCCESS	6

/*
		ϵͳ״̬	1	��ˮ����״̬
		ϵͳ״̬	2	����״̬	��ˮ������״̬
		ϵͳ״̬	3	���㳬ʱ״̬
*/

#define SYSSTATE_INACT						1
#define SYSSTATE_NOTINACT					2
#define SYSSTATE_SUMOUTTIME				3

/*
		�Ƿ����	1	��
		�Ƿ����	2	��
*/
#define IS_YES					1
#define IS_NO 					2
#define TYPE_YES				"1"     //��
#define TYPE_NO 					"2"     //��


#define STATE_TRUE				'1'     	//��
#define STATE_FALSE 			'0'     	//��

//����֧��
#define  INOUTFLAG_IN				1		//����
#define  INOUTFLAG_OUT				2       //֧��
/*
	����Ϣ��غ궨��
*/
#define PURSE_NO_ONE 0					//ǮһǮ����
#define PURSE_NO_TWO 1					//�ڶ�Ǯ����
#define PURSE_NO_THREE 2				//������Ǯ��
#define PURSE_NO_FOUR	3				//���ĸ�Ǯ��

#define IS_MAIN_TRUE "T"					//�Ƿ�Ϊ����
#define AUTO_TRAN_FALSE "F"				//�Ƿ��Զ�ת��
#define ACCOUNT_COUNT_ONE 1			//����Ӧ�ʻ�����
#define PHYTYPE_NO_ONE 1				//�豸�����ͺ�
#define LOSS_TYPE_INFORMAL 1			//��ʧ����
#define ADD_BLACKLIST 0					//���Ӻ�������־
#define DELETE_BLACKLIST 1				//ɾ����������־
#define CANCEL_BLACKLIST		2			// ע��������
#define CHCARD_BLACKLIST          9			// ��������
#define VALIDDATE	"501230121212"		//��������Ч��

/*
	��ˮ״̬	1	����δ����
	��ˮ״̬	2	������
	��ˮ״̬	3	�ѽ������
	��ˮ״̬	4	�ѳ���
	��ˮ״̬	5	����ʱ�βɼ�δ����״̬
	��ˮ״̬	6	�ظ��ϴ��쳣״̬:������վ�ظ��ϴ�ʱ��ϵͳ��¼�����жϣ������ظ����ø�״̬
	��ˮ״̬	7	�ѹ鵵
	��ˮ״̬	8	�����쳣
	��ˮ״̬	9	���𣨲�������ҵ��
*/
#define SERISTAT_NODEBT 		1			//����δ����
#define SERISTAT_DEBT 			2              	//������
#define SERISTAT_GATHER		3             	//�ѽ������
#define SERISTAT_RUSH 			4              	//�ѳ���
#define SERISTAT_BNODEBT 		5              	//����ʱ�βɼ�δ����״̬
#define SERISTAT_ECHO 			6              	//�ظ��ϴ��쳣״̬:������վ�ظ��ϴ�ʱ��ϵͳ��¼�����жϣ������ظ����ø�״̬
#define SERISTAT_ARCHIVE 		7              	//�ѹ鵵
#define SERISTAT_DEBTEXC 		8              	//�����쳣
#define SERISTAT_NONEEDDEBT	9               	//���𣨲�������ҵ��
#define SERISTAT_INVALID		10               	//�ϴ���ˮ���ݴ���


/*
	д��״̬	1	����δд�������
	д��״̬	2	д�������
	д��״̬	3	��д��
*/

#define WCARDSTAT_LAUNCH 		1
#define WCARDSTAT_WHITE 		2
#define WCARDSTAT_WCARD 		3

/*
	�豸״̬	1	δǩ��
	�豸״̬	2	ǩ��������
	�豸״̬	3	ǩ�����ѻ�
	�豸״̬	4	ǩ��
*/
#define DEVRUNSTATUS_REGIST 		'1'
#define DEVRUNSTATUS_ONLINE 		'2'
#define DEVRUNSTATUS_OFFLINE 		'3'
#define DEVRUNSTATUS_SIGNOUT 		'4'

/*
 * PSAM��״̬ 1 ����
 * PSAM��״̬ 2 ע�� 
 */
#define DEVPSAM_REGISTER '1'
#define DEVPSAM_SIGNOUT '1'

/*
	�豸����	1	��ͨ�������豸
	�豸����	2	��̫���������豸
	�豸����	3	ˮ���������豸
	�豸����	4	����������豸
	�豸����	5	��֤���豸
	�豸����	6	����Ȧ���
	�豸����	7	������ֵ��
	�豸����	8	����վ(LPort��
	�豸����	9	����վ(PC��

#define DEVITYPE_CONSUME 		1
#define DEVITYPE_ETHERNET 		2
#define DEVITYPE_WATER			3
#define DEVITYPE_ELECTR			4
#define DEVITYPE_ATTEST			5
#define DEVITYPE_KEEP			6
#define DEVITYPE_CHARGE			7
#define DEVITYPE_LPORT			8
#define DEVITYPE_PC			9
*/
/*
	���Ż��ʹ���	0001	���˴�ǰ�û�
	���Ż��ʹ���	0226	�����շѻ�
*/
#define DEVITYPE_SUBSYSTEM 		"0001"
#define DEVITYPE_CONSUME			"0226"
#define DEVITYPE_LPORT				"5301"
#define DEVITYPE_JLPORT				"5302"
#define DEVITYPE_JSB				"0121"
#define DEVITYPE_MOBILE_TERM		"1055"
#define DEVITYPE_CONSUME_TERM		"8999"
#define DEVITYPE_DOOR				"9000"
#define DEVITYPE_ADDPOS		 	"0201" // ��ֵ��

//���ǻ��ʹ���
#define DEVITYPE_AR716E			"8001"

#define DEV_CONN_COM 1       	// COM ����
#define DEv_CONN_MODEM   	 // MODEM ���� 
#define DEV_CONN_TCP  3		// TCP/IP ����
#define DEV_CONN_SUBLEVEL 9 // �¼��豸

// �豸��;
// ��ʱ��
#define DU_JSB_NORMAL				1001    //�Ž�
#define DU_JSB_MEDICAL				1002   // ҽ����֤
#define DU_JSB_CONFRENCE			1003    // ����ǩ��
#define DU_JSB_ATTENDANCE			1004    // ����

#define DU_POS_NORMAL				2001   // ���� POS ��

/*
	��ϵͳ״̬0	δ����
	��ϵͳ״̬1	ǩ��������	
	��ϵͳ״̬2	ǩ�����ѻ�
	��ϵͳ״̬3	ǩ��
*/

#define SUBSYSRUNSTAT_DEACTIVE		'1'
#define SUBSYSRUNSTAT_ONLINE		'2'
#define SUBSYSRUNSTAT_OFFLINE		'3'
#define SUBSYSRUNSTAT_LOGOUT		'4'

/*
	��ϵͳ����	1	Ȧ����
	��ϵͳ����	2	ʳ���̵�������
	��ϵͳ����	3	ͼ���������
	��ϵͳ����	4	ҽԺ������
	��ϵͳ����	5	���������
	��ϵͳ����	6	ˮ��������
	��ϵͳ����	7	����������
	��ϵͳ����	8	ͼ�����֤��
	��ϵͳ����	9	�Ž���֤��
	��ϵͳ����	10	������֤��
	��ϵͳ����	11	�Խ���
	��ϵͳ����	12	����ǰ�û�
	��ϵͳ����	13  �����ϵͳ
*/
#define SUBSYSTYPE_KEEP			1
#define SUBSYSTYPE_REST			2
#define SUBSYSTYPE_LIB			3
#define SUBSYSTYPE_HOSPIT		4
#define SUBSYSTYPE_ELECTR		5
#define SUBSYSTYPE_WATER		6
#define SUBSYSTYPE_COMPUT		7
#define SUBSYSTYPE_LIBCERT		8
#define SUBSYSTYPE_DOORCERT		9
#define SUBSYSTYPE_CHECK		10
#define SUBSYSTYPE_INTERFACE		11
#define SUBSYSTYPE_999				12
#define SUBSYSTYPE_THIRDPARY		14
#define SUBSYSTYPE_YKT_GW			15
#define SUBSYSTYPE_XSQ				17	

/*
	ѧ��״̬	1	ע��
	ѧ��״̬	2	��ѧ
	ѧ��״̬	3	��ҵע��
	ѧ��״̬	4	��ѧע��
*/
#define STUSTAT_REGIST			1
#define STUSTAT_TEMPOFF			2
#define STUSTAT_GRADUATE		3
#define STUSTAT_GIVEUP			4

/*
   ��ϵͳ��������    1    ��ʧ���ע������
   ��ϵͳ��������	 9    ����
   ��ϵͳ��������    2    ע��
   ��ϵͳ��������    4    �û���Ϣ���
 */
#define SUB_UPDATE_BLK 1
#define SUB_UPDATE_CHUSERINFO 2



/*
	ѧ������	1	��ͨ��ʽר��
	ѧ������	2	��ͨ��ʽ����
	ѧ������	3	��ͨ��ʽ˶ʿ
	ѧ������	4	��ͨ��ʽ��ʿ
	ѧ������	5	��ͨ��ʽ��ʿ��
	ѧ������	6	��ͨ�Կ�ר��
	ѧ������	7	��ͨ�Կ�����
	ѧ������	8	��ͨ����ר��
	ѧ������	9	��ͨ���˱���
*/
#define STUTYPE_OFFIZHUAN		1
#define STUTYPE_OFFISCHOLAR  		2
#define STUTYPE_OFFIMASTER		3

/*
	Ա��״̬	1	ע��
	Ա��״̬	2	ע��
*/
#define EMPLSTAT_REGIST			1
#define EMPLSTAT_LOGOUT			2

/*
	Ա������	1	����
	Ա������	1	����
	Ա������	1	��ʦ
*/
#define EMPLTYPE_LOGI  			1
#define EMPLTYPE_DEPART			2
#define EMPLTYPE_TEACH			3

/*
	�̻�״̬	1	ע��
	�̻�״̬	2	ע��
*/
#define SHOPSTAT_REGIST			1
#define SHOPSTAT_LOGOUT			2

/*
	�̻�����	1	��������ӯ����
	�̻�����	2	�Ƕ�������ӯ����
	�̻�����	3	ѧУ������
*/
#define SHOPTYPE_ABSOLUTE		1
#define SHOPTYPE_NOABSOLUTE		2
#define SHOPTYPE_PUBLIC			3
#define SHOPTYPE_GROUP			0
#define SHOPTYPE_COSUMESHOP		1
#define SHOPTYPE_DEPOSITSHOP	2

/*
	�̻�����״̬	1	ע��
   	�̻�����״̬	2	ע��
*/
#define DEPARTSTAT_REGIST		1
#define DEPARTSTAT_LOGOUT		2


/*
	�̻���������	1	��������ӯ����
	�̻���������	2	�Ƕ�������ӯ����
	�̻���������	3	ѧУ������
*/
#define DEPARTTYPE_ABSOLUTE		1
#define DEPARTTYPE_NOABSOLUTE		2
#define DEPARTTYPE_PUBLIC		3

/*
	�ͻ�״̬	1	ע��
   	�ͻ�״̬	2	ע��
*/
#define CUSTSTAT_REGIST			1
#define CUSTSTAT_LOGOUT			2

/*
	�ͻ�����	1	ѧ��
	�ͻ�����	2	��ְԱ��
	�ͻ�����	3	�̻�
	�ͻ�����	4	��ʱ��Ա
*/
#define CUSTTYPE_SHOP			1
#define CUSTTYPE_TEACH			2
#define CUSTTYPE_STU			3
#define CUSTTYPE_TEMP 			4

/*
	��״̬	1	����
	��״̬	2	ע��
	��״̬	3	�绰��ʧ
	��״̬	4	WEB��ʧ
	��״̬	5	����Ա��ʧ
	��״̬	6	��������ʧ
	��״̬	7	ע��Ӧ��
	��״̬	8	����
	��״̬	9	����д��ʧ��״̬

#define  CARDSTAT_NORMAL		1
#define  CARDSTAT_LOGOUT		2
#define  CARDSTAT_PLOST			3
#define  CARDSTAT_WLOST		4
#define  CARDSTAT_OLOST		5
#define  CARDSTAT_ALOST		6
#define  CARDSTAT_STOPUSE		7
#define  CARDSTAT_DESTROY		8
#define  CARDSTAT_WRITEFAIL	9
*/

//Changed by hhd at 2004-11-3 14:11
//8      7       6      5      4      3      2       1
//0000 0000 0000 0000 0000 0000 0001 0000
//	1  normal
//	2-5  lost

//#define  IDX_CARDSTAT_NORMAL 	0     	//��״̬:0 -����1-ע��
#define CARDSTAT_REG				"0000000000"     //ע��
#define CARDSTAT_LOGOUT 			"1000000000"     //ע��
//#define CARDSTAT_CHANGECARD		"3000"     //����
#define CARDSTAT_LOST				"0100000000"     //��ʧ
#define CARDSTAT_FREEZE				"0010000000"     //����
#define CARDSTAT_WFAIL				"0001000000"     //д��ʧ��
#define CARDSTAT_LOSTFREEZE			"0110000000"     //��ʧ����

#define  CARDSTAT_TYPE_REG	 		0
#define  CARDSTAT_TYPE_LOST	 		1     	//��״̬:��ʧ0-����1-��ʧ
#define  CARDSTAT_TYPE_FREEZE		2     	//��״̬ ����0-����1-����
#define  CARDSTAT_TYPE_WFAIL 		3  	    //��״̬:���ṹ��
#define  CARDSTAT_TYPE_BAD     		4       //��״̬:����-����0-1��Ϊ�𻵿�

/*
#define CARDSTATUS_NORMAL			0		//������
#define CARDSTATUS_LOCK				1		//������
#define CARDSTATUS_FROZE			2		//���Ῠ
#define CARDSTATUS_LOST				3		//��ʧ��
#define CARDSTATUS_CLOSE			4		//ע����
#define CARDSTATUS_EXPIRE			5		//���ڿ�
#define CARDSTATUS_EXCEPT			9		//�쳣��

#define CARDSTATUS_ISSUE			6		//������
#define CARDSTATUS_ISSUED			7		//�ѷ���
*/


/*
	������		1	ѧ����ʽ��
	������		2	�̹���ʽ��
	������		3	ѧ���ƿ���ʱ��	��ʽ��δ�������ǰʹ��
	������		4	�̹��ƿ���ʱ��	��ʽ��δ�������ǰʹ��
	������		5	ѧ��������ʱ��	��ʧ����ʱʹ��
	������		6	�̹�������ʱ��	��ʧ����ʱʹ��
	������		7	�����	����Ƭ
	������		8	��ʱ��Ա��	����Ƭ
*/
/*
	������		1	��ʽ��
	������		2	������ʱ��
	������		3	��������ʱ��
	������		4	VIP������ʱ��
	������		5	������ʱ��
*/
#define CT_NORMAL			1
#define CT_TEMP				2
#define CT_TEMP_NONAME	3
#define CT_VIP				4
#define CT_TEMP_NAME		5

/*
	ҽԺ�������	1	�Һŷ�
	ҽԺ�������	2	ҩ��
*/
#define HOSCONTYPE_REGIST		1
#define HOSCONTYPE_MEDI			2

/*
	�����ʽ����	1	ʳ�á��̵�������
	�����ʽ����	2	������
	�����ʽ����	3	Ѻ��
	�����ʽ����	4	��ֵ��
	�����ʽ����	5	�˻ؽ�
	�����ʽ����	6	�����
	�����ʽ����	7	����
	�����ʽ����	8	ת��

*/
#define FUNDTYPE_COMSUME		1
#define FUNDTYPE_HANDING		2
#define FUNDTYPE_DEPOSIT		3
#define FUNDTYPE_FILL			4
#define FUNDTYPE_BACK			5
#define FUNDTYPE_MANAGE		6
#define FUNDTYPE_BOARD			7
#define FUNDTYPE_TRAN			8

/*
	��ʱ����ִ�����	1	����һ��
	��ʱ����ִ�����	2	�ظ�����
*/
#define MASKTYPE_ONCE			1
#define MASKTYPE_REPEAT			2

/*
	ʱ������λ		����
	ʱ������λ		Сʱ
	ʱ������λ		��
	ʱ������λ		��
	ʱ������λ		��
	ʱ������λ		��
*/
#define INTERVAL_MIN			1
#define INTERVAL_HOUR			2
#define INTERVAL_DAY			3
#define INTERVAL_WEEK			4
#define INTERVAL_MONTH			5
#define INTERVAL_YEAR			6

/*
	�鵵����	1	��ˮ������ǩ����־��
	�鵵����	2	���ܡ������
	�鵵����	3	��ˮ�����ܡ������
*/
#define SORTCONT_GLIDE			1
#define SORTCONT_SUM			2
#define SORTCONT_ALL			3

/*
	��ʧ�������	1	�����ӳ�
	��ʧ�������	2	�û�ָ��
*/
#define LIMITTYPE_FOREVER		1
#define LIMITTYPE_SPECIFY		2

/*
	�����ʶ	1	�跽
	�����ʶ	2	����
*/
#define DEBITCREBIT_DEBIT		1
#define DEBITCRRBIT_CREBIT		2

/*
	�跽��־	1	��Ĭ��
	�跽��־	2	������
	�跽��־	3	������
*/
#define DEBITSYMBOL_READ		1
#define DEBITSYMBOL_RINPUT		2
#define DEBITSYMBOL_RCONFIG		3

/*
	ƾ֤���	1	�տ�ƾ֤
	ƾ֤���	2	����ƾ֤
	ƾ֤���	3	ת��ƾ֤
*/
#define PAPERTYPE_IN			1
#define PAPERTYPE_OUT			2
#define PAPERTYPE_TURN			3

/*
	��Ŀ���	1	�ʲ�
	��Ŀ���	2	��ծ
	��Ŀ���	3	��ͬ��
	��Ŀ���	4	������Ȩ��	
	��Ŀ���	5	�ɱ�
	��Ŀ���	6	����
*/
#define SUBJTYPE_FUND			'1'
#define SUBJTYPE_DEBT			'2'
#define SUBJTYPE_OWNER			'3'
#define SUBJTYPE_RIGHT			'4'
#define SUBJTYPE_COST			'5'
#define SBUJTYPE_PROFIT			'6'

#define SUBJCLASS_FUND			1		//�ʲ�
#define SUBJCLASS_DEBT			2		//��ծ
#define SUBJCLASS_RIGHT			3		//������Ȩ��
#define SUBJCLASS_COST			4		//���óɱ�
#define SBUJCLASS_INCOMING		5		//������

/*
	��Ŀ����	1	��
	��Ŀ����	2	��
	��Ŀ����	3	��ͬ
*/
#define BALANCEDIR_DEBIT		1
#define BALANCEDIR_CREBIT		2
#define BALANCEDIR_BOTH			3

/*
	��Ŀ����	1	�ֽ�
	��Ŀ����	2	����
	��Ŀ����	3	����
	��Ŀ����	4	����
	��Ŀ����	5	����
	��Ŀ����	6	����
	��Ŀ����	7	����
	��Ŀ����	8	��Ŀ
	��Ŀ����	9	����
	��Ŀ����	10	ת��
*/
#define SUBJCHAR_CASH			1
#define SUBJCHAR_BANK			2
#define SUBJCHAR_ROTA			3
#define SUBJCHAR_FEE			4
#define SUBJCHAR_QUAN			5
#define SUBJCHAR_DEPART		6
#define SUBJCHAR_PERSON		7
#define SUBJCHAR_PROJ			8
#define SUBJCHAR_CHECK			9
#define SUBJCHAR_TRANS			10

/*
	��Ŀ��Ϣ��
	101		�ֽ�
	102		��������
	103		Ӧ���ݸ�
	201		���˴��
	202		�̻����
	203		Ӧ������
	301		�����
	10101	�ֽ��ֵ
	10201	����ת��
	20301	Ѻ��
	20302	Ԥ������
	30101	һ��ͨ�����
	30102	�̻�������
*/

/*
	ĩ����־	1	��
	ĩ����־	2	��
*/
#define FINALSYMBOL_YES			1
#define FINALSYMBOL_NO			2

/*
	������ò	1
*/


/*
	�������	1
*/

/*
	ְ�ƴ���	1	��
*/

/*
	����������	1	������
	����������	2	΢��
*/
#define CARDCORP_PHILIP			1
#define CARDCORP_MICROSTAR		2

/*
	���򼶱�	1	��
	���򼶱�	2	У��
	���򼶱�	3	¥
	���򼶱�	4	¥��
	���򼶱�	5	����
*/
#define AREALEVEL_ROOT			1
#define AREALEVEL_SCHOOL			2
#define AREALEVEL_BUILD			3
#define AREALEVEL_FLOOR			4
#define AREALEVEL_WINDOW			5
/*
	�ʺ����	1	�������˺�
	�ʺ����	2	�̻����˺�
	�ʺ����	3	���˸��˺�
	�ʺ����	4	�̻����˺�
	�ʺ����	5	ѧУ�����˺ţ���ѧУ������
	�ʺ����	6	ѧУ�����˺ţ������н�����
	�ʺ����	7	ѧУ�����˺ţ����ֽ𽻻���
	�ʺ����	8	ѧУ�����˺ţ�����񽻻���
*/
#define ACCTYPE_PERMAIN			1
#define ACCTYPE_SHOPMAIN		2
#define ACCTYPE_PEROTHER		3
#define ACCTYPE_SHOPOTHER		4
#define ACCTYPE_SCHSCH			5
#define ACCTYPE_SCHBANK			6
#define ACCTYPE_SCHCASH			7
#define ACCTYPE_SCHFINA			8
/*
	��Ȩ��״̬	1	ע��
	��Ȩ��״̬	2	ע��
*/
#define AuthCardS_LOGON			1
#define AuthCardS_LOGOUT		2
/*
	��Ȩ�����	1	��Ȩĸ��
	��Ȩ�����	2	������Կ��
	��Ȩ�����	3	��ֵ��Կ��
*/
#define AuthCardT_MOTHER		1
#define AuthCardT_COUSME		2
#define AuthCardT_DEPOSIT		3
/*
	�ⲿϵͳ��ʶ	1	ũ��1
	�ⲿϵͳ��ʶ	2	ũ��2
*/
#define OUTSYS_BANKONE			1
#define OUTSYS_BANKTWO		2

/*
	��Ϣ״̬1: �ȴ���������
	��Ϣ״̬2: �ѷ�������
	��Ϣ״̬3: ִ�гɹ�
	��Ϣ״̬4: ִ��ʧ��
	��Ϣ״̬5: 999������Ϣ����
	��Ϣ״̬6: ���뷵�ؽ��
	��Ϣ״̬7: �����������ݼ�
*/
#define MESLISTSTATE_SUCCEED		1
#define MESLISTSTATE_ERROR			2
#define MESLISTSTATE_WAIT			3
#define MESLISTSTATE_RETERROR		5
#define MESLISTSTATE_START			4
#define MESLISTSTATE_NOTRET			6
#define MESLISTSTATE_CONTINUUM		7
#define MESLISTSTATE_HUNG			9

#define MESLIST_TYPE_NORMAL		0
#define MESLIST_TYPE_ORDER			1
// ����
#define MESLIST_PRIORITY_NORMAL	1
// ʵʱ
#define MESLIST_PRIORITY_REALTIME  2
// ��ռ
#define MESLIST_PRIORITY_PREEMPT	3

/*
	��Ϣ����Ĭ��ʧ�ܺ��ʹ���
*/
#define MESLIST_SENDCOUNT		3

/*
	��������ɾ��־
	0		���
	1		ɾ��
*/
#define BLACK_SHEET_ISADD		0
#define BLACK_SHEET_ISDEL		1
#define BLACK_SHEET_CANCEL		2
#define BLACK_SHEET_CHCARD          9


/*	----------------������Ĳ���------------------------------	*/
/*
	�豸����״̬	1	����
	�豸����״̬	2	�ѻ�
*/
#define DEVBEATSTATE_ON			1
#define DEVBEATSTATE_OFF			2

/* �豸ģʽ*/
/*
   1    ��������ʹ�õ��豸
   2    �����ѻ�ʹ�õ��豸
   4    ��������Ҳ��������ʹ�õ��豸
*/
#define DEV_MODE_ONLINE     '1'
#define DEV_MODE_OFFLINE   '2'
#define DEV_MODE_BOTH		'4'

/*
	�쳣��ˮ״̬	1	����
	�쳣��ˮ״̬	2	��֪ͨ
	�쳣��ˮ״̬	3	�Ѵ���
*/
#define ERRSERIALSTATE_BEGIN			1
#define ERRSERIALSTATE_NOTIF			2
#define ERRSERIALSTATE_DEAL			3

/*
	������ˮ״̬	1	�ѱ���
	������ˮ״̬	2	�Ѵ������
	������ˮ״̬	3	����δ���
*/
#define NOTIFSERIALSTATE_NOTIF			1
#define NOTIFSERIALSTATE_END				2
#define NOTIFSERIALSTATE_OVERTIME		3
/*
	����Ա״̬	1	ע��
	����Ա״̬	2	δע���ע��
	����Ա״̬	3	��½
	����Ա״̬	4	�ǳ�
*/
#define OPERATOR_REG			"1"
#define OPERATOR_UNREG			"2"
#define OPERATOR_LOGON			"3"
#define OPERATOR_LOGOUT		"4"

#define TYPE_CASH			1		//�ֽ��ֵ
#define TYPE_BILL			2		//֧Ʊ��ֵ
#define TYPE_FUNDBOOK		3		//���ѱ���ֵ
#define TYPE_OTHER			4		//������ʽ��ֵ

#define CUTUPD_UPDATE		 0	// ����һ���ͻ���Ϣ���µļ�¼
#define CUTUPD_CANCEL		 1	// ����һ��ע���ͻ���Ϣ�ļ�¼
#define CUTUPD_ADD			 2	// ����һ�������ͻ���Ϣ�ļ�¼
#define CUTUPD_CH_OLDCARD  3     // ����һ�������ɿ��ļ�¼
#define CUTUPD_CH_NEWCARD 4    // ����һ�������¿��ļ�¼

#define FEE_CODE_DEFAULT	0  // ��ʹ�ÿ�Ŀ�շ�
#define FEE_CODE_MAX		99 // ����Ŀ��

/*
 * ��ϵͳ��Ӧ�Ĺ��ܺ��б�
*/
#define SUBSYSTEM_BLKCARD_FUNC	400000	 	// ��ʧ���ע������
#define SUBSYSTEM_NEWCARD_FUNC	400002		// ���¿�����

////////////////////////////////////////////////
/// һ��ͨ��ϵͳ
#define YKT_SYS_PHONE			1000
#define YKT_SYS_ATM				1001
#define YKT_SYS_WEB			2000
#define YKT_SYS_ADVQUREY		2001
#define YKT_SYS_MM				2002
#define YKT_SYS_MONITOR		2003


#define CUT_RELATION_TYPE_BANK	1
#define CARDINF_NEW_STATE		2
#define CARDINF_AGAIN_STATE	1

// ��ֵƽ̨,����״̬����
// ���¿�
#define UNI_CARD_NEW_CARD		1
// ������ʽ��
#define UNI_CARD_REISSUE_CARD 2
// ��д����Ϣ
#define UNI_CARD_REWRITE_CARD 3
// ��ʧ
#define UNI_CARD_LOSS			4
// ����
#define UNI_CARD_FROZEN		5
// ��ֵ
#define UNI_CARD_ADD_MONEY	6
// ע��
#define UNI_CARD_CANCEL		7

// ����Ա��Ȩ��״̬
// ����
#define AUTHCARD_STATUS_NORMAL	1
// ��ʧ
#define AUTHCARD_STATUS_LOSS		2
// ע��
#define AUTHCARD_STATUS_CANCEL	4

// ����״̬
// δ�·�
#define SUBSIDY_STATUS_INIT	'1'
// δ��ȡ
#define SUBSIDY_STATUS_PUT  '2'
// ����ȡ
#define SUBSIDY_STATUS_GET  '3'
#define SUBSIDY_STATUS_INVALID	'4'
#define SUBSIDY_STATUS_REV	'5'
//���״̬
// δ���
#define SUBSIDY_CHECKFLAG_INIT	0
// ���ͨ��
#define SUBSIDY_CHECKFLAG_OK  1
// ��˲�ͨ��
#define SUBSIDY_CHECKFLAG_REJECT  2
// ��������
#define SUBSIDY_TYPE_BANK	'1'		//�����·�����

/*************************************************
 * ��Ȩ��Ȩ��λ
 * **********************************************/
#define AUTHCARD_PRV_POS		1  // �շ��ն�
#define AUTHCARD_PRV_CENTER		2  // ��������
#define AUTHCARD_PRV_ADDPOS		4  // ��ֵ�ն�
#define AUTHCARD_PRV_DOOR		8  // �Ž��ն�
#define AUTHCARD_PRV_ID			16 // ��֤�ն�
#define	AUTHCARD_PRV_AREA		32 // �������

/*************************************************
 �Ž�ϵͳ״̬��������
*/
//#define DOOR_ADDFLAG_UNDOWNLOAD 1			//��������־-δ�´�
//#define DOOR_FLAG_NORMAL  2				//���������´�
//#define DOOR_DELFLAG_UNDOWNLOAD 7			//������ɾ��-δ�´�
//#define DOOR_FLAG_WAITING_DEL 8			//�������ȴ�ɾ��
//#define DOOR_FLAG_DELETE     9			//��������ɾ��-���´�
#define DOOR_ADDFLAG_UNDOWNLOAD 	1	//��������־-δ�´�
#define DOOR_ADDFLAG_DOWNLOAD  		2	//���������´�
#define DOOR_DELFLAG_UNDOWNLOAD 	7	//������ɾ��-δ�´�
#define DOOR_DELFLAG_WAITDOWNLOAD 	8	//�������ȴ�ɾ��
#define DOOR_DELFLAG_DOWNDOWNLOAD   9	//��������ɾ��-���´�

#define ADDDELFLAG_ADD				1 	//���
#define ADDDELFLAG_DEL				2	//ɾ��

#define DOWNSTATUS_INIT				1     //δ�´�
#define DOWNSTATUS_SUCCESS		2	  //�´��ɹ�
/* �Ž����ڶ���*/
#define DOOR_WEEK_MON	1
#define DOOR_WEEK_TUE   2
#define DOOR_WEEK_WEN 	3
#define DOOR_WEEK_THU  	4
#define DOOR_WEEK_FRI	5
#define DOOR_WEEK_SAT  	6
#define DOOR_WEEK_SUN 	7

#define DOOR_BEGIN_TIME   "00000000000000"
#define DOOR_END_TIME     "99999999999999"

/**************************************************
 �����Ž��豸����
***************************************************/
#define HNDR_RAC2000P "9001"
#define HNDR_RAC2000G "9002"
#define HNDR_GCU3	     "9003"
#define HNDR_NCU3         "9004"
#define HNDR_BF430        "9005"

/**************************************************
 �ⲿ���д���
***************************************************/
#define NONGYE_BANK 		1
#define GONGSHANG_BANK	2
#define JIANSHE_BANK		3
#define ZHONGGUO_BANK		4  


//�������
#define BANK_ACCCHK_TYPE   1
#define MOBILE_ACCCHK_TYPE 2

//////////////////////////////////////////////////////////
// TRANSPACK ״̬
/*
 N δ����
 S �ɹ�
 R ���
 F ʧ��
 D ����
 C ����
 B ��Ʊ
 V �ܾ�
 W д��ʧ��
*/
#define TRANSPACKSTATE_NODEAL 'N'
#define TRANSPACKSTATE_SUCCESS 'S'
#define TRANSPACKSTATE_REJECT 'R'
#define TRANSPACKSTATE_FAILD 'F'
#define TRANSPACKSTATE_EXPIRD 'D'
#define TRANSPACKSTATE_CANCEL 'C'
#define TRANSPACKSTATE_RETURN 'B'
#define TRANSPACKSTATE_DENY 'V'
#define TRANSPACKSTATE_WRITEFAILD 'W'
#endif
