#ifndef _KSG_TASKCODE_H_
#define _KSG_TASKCODE_H_

#ifdef _MSC_VER
#pragma once
#endif

#define TK_CODE_BASE	930300

//<! ����ǰ�û�����
#define TK_RESTART_GATEWAY	999999
//<! �����ɼ�����
#define TK_HEARTBEAT_TASK	TK_CODE_BASE + 1
#define TK_COLLSERIAL_TASK	TK_CODE_BASE + 2
//<! �´��豸ʱ��
#define TK_DL_TIMER				930001
//<! �ϴ��豸ʱ��				
#define TK_UL_TIMER				930002
//<! �´�������
#define TK_ADD_BLACKCARD		930003
//<! ɾ��������
#define TK_DEL_BLACKCARD		930004
//<! �豸��Ȩ�޷���				
#define TK_SET_CARD_PRIVILEGE	950040
//<! ���ù���ѱ���
#define TK_SET_FEE_RATE			950041
//<! �ɼ���ʷ������ˮ
#define TK_COLL_HIS_SERIAL		930016
//<! �´��Ž�ʱ���
#define TK_DOOR_DL_TIME_SECT	930107
//<! �´��Ž���
#define TK_DOOR_DL_WEEK		930105
//<! �ϴ��Ž���
#define TK_DOOR_UL_WEEK		930106
//<! �´��Ž��ڼ���
#define TK_DOOR_DL_HOLIDAY	930109
//<! �ϴ��Ž��ڼ���
#define TK_DOOR_UL_HOLIDAY  930110
//<! �´��Ž���Ա����
#define TK_DOOR_DL_CARD		930117

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
#define XML_KEY_CARDPHY			"PHYNO"			//������
#define XML_KEY_SEQNO			"SEQ"			//���

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
#define XML_KEY_HOLIDAY		"HOLIDAY"		//�Ž��Ž��ڼ���
#define XML_KEY_WORKMODE		"WORKMODE"		//����ģʽ
#define XML_KEY_LOCK1_TIME		"LOCK1"			//��1����ʱ��
#define XML_KEY_LOCK2_TIME		"LOCK2"			//��2����ʱ��
#define XML_KEY_IS_ALLEYWAY	"ALLEYWAY"		//�Ƿ�ͨ��
#define XML_KEY_IS_SAVE		"SAVE"			//�Ƿ񱣴�򿨼�¼
#define XML_KEY_IS_LCD			"LCD"			//�Ƿ�Һ����ʾ
#define XML_KEY_CUSTID			"CUSTID"		//�ͻ���

#define KEY_TASK_ERR_MSG		"TK_ERR_MSG"		//���ش�����Ϣ

#define E_999_BLKCARD                  0x00	//�ڿ�����
#define E_999_INVCARD                  0x01	//�Ƿ���
#define E_999_UNCONFIRM                0x02	//��;�ο�
#define E_999_PURE_ERR                 0x03	//Ǯ����ʽ��
#define E_999_WRITE_ERR                0x05	//�޷�д��
#define E_999_PSWD_ERR                 0x10	//�������
#define E_999_SUCCESS				   0x99 // ��ȷ
#define E_999_OUT_TIME                 0xA0 //����ʱ����ڴ�
#define E_999_EXCEED                   0xA1	//��������
#define E_999_INTERVAL_ERR             0xA2	//ʱ��������
#define E_999_ADD_MENOY                0xFA	//��ֵ����
#define E_999_CANCEL                   0xFE	//��������
#define E_999_FAILED				   0xFF	//���ײ��ɹ�


#endif // _KSG_TASKCODE_H_
