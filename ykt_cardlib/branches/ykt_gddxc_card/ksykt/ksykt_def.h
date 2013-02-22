#ifndef _KSYKT_DEF_H_
#define _KSYKT_DEF_H_
#pragma pack(1)
/*�������İ�*/
typedef struct
{
	unsigned int    AccountNo;         /*�ʺ�*/
	char            StudentNo[21];    /*ѧ��*/
	char            inqPassword[7];   /*��ѯ����*/
	char            Operator[3];         /*����Ա*/
	short           RetCode;             /*��̨������ֵ*/
} CardOperating;
/*��Ƭ��/�˷ѵİ�*/
typedef struct
{
	unsigned int    AccountNo;                /*�ʺ�*/
	unsigned int    CardNo;                   /*����*/
	char  FinancingType[3]; /*��������*/
	int	CardBalance;                     /*�����,��ȷ����*/
	int  TranAmt;                     /*���׶�,��ȷ����*/
	unsigned short  UseCardNum;             /*�ÿ�����������ǰ*/
	unsigned short  TerminalNo;                /*�ն˱��*/
	char   PassWord[7];              /*������*/
	char   Operator[3];                /*����Ա*/
	char   Abstract[129];             /*ժҪ*/
	unsigned int TranJnl;                       /*������ˮ��*/
	unsigned int BackJnl;                      /*��̨������ˮ��*/
	short    RetCode;                    /*��̨������ֵ*/
} CardConsume;


/*�ʻ���Ϣ��*/
typedef struct
{
	char		Name[21];           /*����*/
	char		SexNo[2];           /*�Ա�*/
	char		DeptCode[19];       /*���Ŵ���*/
	unsigned int	CardNo;         /*����*/
	unsigned int	AccountNo;      /*�ʺ�*/
	char	StudentCode[21];        /*ѧ��*/
	char	IDCard[21];             /*���֤��*/
	char	PID[3];                 /*��ݴ���*/
	char	IDNo[13];               /*������*/
	int	Balance;                    /*�����*/
	char	Password[7];            /*��������*/
	char	ExpireDate[7];          /*�˻���ֹ����*/
	unsigned short	SubSeq;         /*������*/
	char	IsOpenInSys;			/*�Ƿ��ڱ�ϵͳ�ڿ�ͨ*/
	short TerminalNo;				/*�ն˺���,��ȡ����ʱ��Ҫ��д*/
	short RetCode;					/*��̨������ֵ*/
	char Flag[16];					/*״̬(2004-08-26����)*/
	char Pad[84];					/*Ԥ���ֶ�*/
} AccountMsg;
/*
   ����Flag�����ֽڴ��������:
   flag[0]�������Ϣ�����־��0_û��� 1_�ѱ��
   flag[1]����״̬��0_���� 1_Ԥ���� 2_Ԥ���� 3_�����ʺ�
   flag[2]����ʧ��0_������ 1_��ʧ
   flag[3]�������־��0_���� 1_����
   flag[4]������־��0_���� 1_���ʲ�ƽ
   flag[5]��ת�ʱ�־��0_ֹͣ 1_���� 2_�Զ�
   flag[6]�����ѱ�־��0_���� 1_�Զ�
   flag[7]���������뿪�أ�0_��ʹ�������޶� 1_ʹ�������޶�
   flag[8]���Ƿ���������ת�ʣ�0_���� 1_����
   flag[9]���Ƿ�����ݹ����ܣ�0_�� 1_��
   flag[10]������ԭ��0_�˹����� 1_���ʲ�ƽ���������
   */
/*�ʻ���Ϣ��չ��*/
typedef struct
{
	char                      Name[21];                         /*����*/
	char                      SexNo[2];                          /*�Ա�*/
	char                      DeptCode[19];                   /*���Ŵ���*/
	unsigned int           CardNo;                            /*����*/
	unsigned int           AccountNo;                       /*�ʺ�*/
	char                      StudentCode[21];               /*ѧ��*/
	char                      IDCard[21];                       /*���֤��*/
	char                      PID[3];                              /*��ݴ���*/
	char                      IDNo[13];                          /*������*/
	int                         Balance;                             /*�����*/
	char                      Password[7];                      /*��������*/
	char                      ExpireDate[7];                    /*�˻���ֹ����*/
	unsigned short       SubSeq;                             /*������*/
	char                      IsOpenInSys;                     /*�Ƿ��ڱ�ϵͳ�ڿ�ͨ*/
	short                     TerminalNo;                       /*�ն˺���,��ȡ����ʱ��Ҫ��д*/
	short                     RetCode;                           /*��̨������ֵ*/
	char                      TechTitle[4];                       /*����ְ��*/
	long                      EducTime;                          /*ѧ��*/
	char                      InDate[9];                          /*��У����*/
	char                     Flag[16];                            /*״̬(2004-08-26����)*/
	char                      Pad[71];                      /*Ԥ���ֶ�*/
} AccountMsgEx;
/*��ѯ������ˮ�����ݰ�*/
typedef struct
{
	char               InqType;              /*��ѯ����,0-��ѯ������ˮ;1-��ʷ��ˮ*/
	unsigned int    Account;              /*�ֿ����ʺ�*/
	unsigned int    MercAcc;             /*�̻��ʺ�*/
	short              TerminalNo;         /*�ն˺���*/
	char               StartTime[15];      /*��ʼʱ��,YYYYMMDDHHMMSS*/
	char               EndTime[15];       /*����ʱ��,YYYYMMDDHHMMSS*/
	char               FileName[64];      /*���յ����ļ�����*/
	int                  RecNum;              /*��ѯ���ļ�¼��Ŀ*/
}InqTranFlow;
/*��ѯ��ͨ��ˮ*/
typedef struct
{
	unsigned int Account;          /*�ֿ����ʺ�*/
	char FileName[64];                   /*���յ����ļ�����*/
	int RecNum;                              /*��ѯ���ļ�¼��Ŀ*/
}InqOpenFlow;
#pragma pack(1)
/*ģ����ѯ�ʻ���Ϣ��*/
typedef struct
{
	char Name[31];  /*����*/
	char SexNo[2]; /*�Ա�*/
	char DeptCode[19]; /*���Ŵ���*/
	unsigned int CardNo;  /*����*/
	unsigned int AccountNo;  /*�ʺ�*/
	char StudentCode[21];  /*ѧ��*/
	char IDCard[21]; /*���֤��*/
	char PID[3];	 /*��ݴ���*/
	char IDNo[13];	/*������*/
	int Balance;        /*�����*/
	char ExpireDate[7];  /*�˻���ֹ����*/
	unsigned int SubSeq; /*������*/
	char Flag[16];		/*״̬(2004-08-26����)*/
}HazyInqAccMsg;

/*ģ����ѯ�ʻ���Ϣ��չ��*/
typedef struct
{
	char Name[31];    /*����*/
	char SexNo[2];   /*�Ա�*/
	char DeptCode[19];   /*���Ŵ���*/
	unsigned int CardNo;    /*����*/
	unsigned int AccountNo;   /*�ʺ�*/
	char StudentCode[21];  /*ѧ��*/
	char IDCard[21];   /*���֤��*/
	char PID[3];     /*��ݴ���*/
	char IDNo[13];    /*������*/
	int Balance;     /*�����*/
	char ExpireDate[7];  /*�˻���ֹ����*/
	unsigned int SubSeq;    /*������*/
	char Flag[16];       /*״̬(2004-08-26����)*/
	char TechTitle[4];     /*����ְ��*/
	long EducTime;      /*ѧ��*/
	char InDate[9];      /*��У����*/
}HazyInqAccMsgEx;

/*��ˮ�ļ��ṹ*/
typedef struct
{
	long                        Account;                                /*�ʺ�*/
	long                        BackJnl;                                                /*��̨��ˮ��*/
	long                        MercAccount;                        /*�̻��ʺ�*/
	long                        TerminalNo;                                          /*�ն˱��*/
	char                        OperCode[4];                        /*����Ա���*/
	char                        TranCode[3];                         /*�¼�����*/
	char                        JnlStatus[2];                                          /*��ˮ״̬*/
	char                        JnDateTime[15];                    /*��ˮ��������ʱ��YYYYMMDDHH24MISS*/
	char                        EffectDate [9];                       /*��ˮ��Ч����YYYYMMDD*/
	long                        Balance;                                                /*���*/
	long                        TranAmt;                               /*���׶�*/
	char                        ConsumeType[4];   /*��������*/
	char                        Resume[129];                        /*��ע*/
}TrjnFlowFile;
/*ģ����ѯʱ���صĿ�ͨ��ˮ���ļ��ṹ*/
typedef struct
{
	long                        Account;                 /*�ʺ�*/
	long                        SysCode;                               /*��ͨϵͳϵͳ����*/
	char                       SysName[41];        /*��ͨϵͳϵͳ����*/
	char                        OpenDate[15];       /*��ͨ����YYYYMMDDHH24MISS*/
}OpenFlowFile;
	/*�����ǿ����ļ��Ľṹ*/
	/*ǰ8+30 * sizeof (struct tabCtrlHead)Ϊ�ļ�ͷ*/
	/* ǰ8�ֽ�ΪSYNTONG */
	/*��˳�����£�*/
	/*ID_CONTROL.BIN �ļ�ͷ
	  λ�� ͷ�ṹ ��Ӧ���ݱ�����
	  ================================================*/
#define CONTROL_STR "SYNTONG"              /* �����ļ���ʶ */
#define OFFSET_T_DEPARTMENT 0               /* ������֯�� */
#define OFFSET_T_PID 1                                   /* ��ݴ���� */
#define OFFSET_T_IDTYPE 2                           /* ֤�����ͱ� */
#define OFFSET_T_PEOPLE 3                           /* ����� */
#define OFFSET_T_NATION 4                          /* ������ */
#define OFFSET_T_ZZMM 5                                             /* ������ò */
#define OFFSET_T_AREA 6                                              /* У/��������� */
#define OFFSET_T_SS_YUAN 7                       /* ���ᣨԷ/�� */
#define OFFSET_T_WHCD 8                                            /* �Ļ��̶� */
#define OFFSET_T_CARDTYPE 9     /* ��������� */
#define OFFSET_T_JSZC 10                                             /* ����ְ�� */
#define OFFSET_T_XZZW 11                            /* ����ְ�� */
#define OFFSET_SCHOOLCODE 12 /* 0:ѧУ����SchoolCode*/
#define OFFSET_SUBJECT 13                           /* 1:�ձ��ֵ�Subject*/
#define OFFSET_FEE 14                                                    /* 2:���������趨��fee*/
#define OFFSET_CONFIGINFO 15   /* 3:���ִ����ֵ�ConfigInfo*/
#define OFFSET_BRANCH 16                           /* 4:�̻����ű�branch*/
#define OFFSET_CSZD 17                                 /* 5:ϵͳ����cszd*/
#define OFFSET_TRCD 18                                 /* 6:�¼������trcd*/
#define OFFSET_MESSAGE 19                         /* 7:ϵͳ��Ϣ��message*/

//�ļ�ͷ
struct tabCtrlHead
{
	unsigned short structlength; /*ÿ����¼����*/
	unsigned short count; /*��¼����*/
	long offset; /*���ļ�ͷ��ʼ���ñ��һ����¼ƫ����*/
};
//������֯�ṹ
struct t_department{
	char dept_code[15+1];                          //���Ŵ���
	char dept_name[40+1];                         //��������
	char area_code[3+1];                                           //����У/����
	char dept_level;                                                    //���ż���
	char dept_easycode[10+1];   //������
	char dept_type;                                                     //��������
	char dept_flag;                                                      //����״̬
	char dept_desc[20+1];                          //������Ϣ
	char dept_opercode[3+1];    //����Ա����
};
//�������
struct t_pid{
	char pid_code[2+1];                                             //��ݴ���
	char class_code;                                                   //�ֿ������ͣ�1ѧ����2�̹���3У����Ա��
	char area_code[3+1];                                           //У/��������
	char pid_name[40+1];                                          //�������
	char pid_easycode[10+1];      //������
	char pid_flag;                                                        //����״̬
	char pid_opercode[3+1];       //����Ա����
	char pid_cardtypeno[3+1];    //����ʽ��
	int pid_zkl;                                                                           //�ۿ���
};
//֤�����ͱ�
struct t_idtype{
	char idtype_code[3+1];
	char idtype_name[16+1];
	char idtype_easycode[10+1];
};
//�����
struct t_people{
	char people_code[2+1];
	char people_name[10+1];
	char people_easycode[10+1];
	char people_flag;
};
//������
struct t_nation{
	char nation_code[2+1];
	char nation_name[24+1];
	char nation_easycode[10+1];
	char nation_flag;
};
//������ò
struct t_zzmm{
	char zzmm_code[2+1];
	char zzmm_name[30+1];
	char zzmm_easycode[10+1];
	char zzmm_flag;
};
//У/���������
struct t_area{
	char area_code[3+1];
	char area_name[40+1];
	char area_easycode[10+1];
};
/* 2003/08/06 add */
//���ᣨԷ/����
struct t_ss_yuan {
	char code[3+1];                                                    //����
	char name[20+1];                                                 //����
	char easycode[10+1];                                           //������
	char type;                                                                             //����
};
//�Ļ��̶�
struct t_whcd {
	char code[2+1];
	char name[20+1];
	char easycode[10+1];
	char useflag;
};
//����ʽ����
struct t_cardtype {
	char cardtypeno[2+1];
	char cardtypename[20+1];
	char cardcontent[100+1];
	char useflag;
};
//����ְ��
struct t_jszc {
	char code[3+1];
	char name[30+1];
	char easycode[10+1];
	char useflag;
};
//����ְ��
struct t_xzzw {
	char code[3+1];
	char name[30+1];
	char easycode[10+1];
	char useflag;
};
/* add end */
//ѧУ����
struct t_schcode{
	char SchCode[2+1];
	char Name[40+1];
	char EnglishName[81];
	char Address[81];
	char Remark[41];
};
//�ձ��ֵ�
struct t_subject{
	char SubjectCode[8+1];
	char SubjectName[18+1];
	char ShortName[12+1];
	char SuperSubject[8+1];
	int Sequence;
	char flag[11];
};
//���������趨��
struct t_fee{
	char FeeCode[3+1];
	char FeeName[20+1];
	char SchCode[2+1];
	char TranCode[2+1];
	char PID[2+1];
	int FeeAmt;
	int FeeAmtRate;
	char FeeFlag[3];
};
//���ִ����ֵ�
struct t_configinfo{
	char Code[3+1];
	char Name[41];
	char AssistantCode[10+1];
	char Type[3];
};
//�̻����ű�
struct t_branch{
	char DeptCode[4];
	char AssistantCode[10+1];
	char Name[31];
	char SuDeptCode[4];
	char DeptLevel;
	char DeptType;
};
//ϵͳ����
struct t_cszd{
	char Code[4];
	char Name[21];
	char Value[21];
	char Remark[41];
	char Flag[3];
};
//�¼������
struct t_trcd{
	char TranCode[2+1];
	char TranName[40+1];
	char Flag[11];
};
//ϵͳ��Ϣ��
struct t_message{
	short MsgCode;
	char Describe[251];
};
#pragma pack()

#define ERR_EXCEPTION   -9999	//�ػ��쳣
#define ERR_OK			0		//���׳ɹ�
#define ERR_VER			-1		//�汾����
#define ERR_RETCODE		-2		//�����벻��
#define ERR_LENGTH		-3		//���ݳ��Ȳ���
#define ERR_FILENAME	-4		//�ļ����Ƿ�
#define ERR_FILESTAT	-5		//�ļ�����״̬�Ƿ�
#define ERR_FAIL		-6		//����ʧ��

/*sios error : ERR_SIOS_ */
#define ERR_SIOS_NOREC		-100	//ָ���ļ�¼������
#define ERR_SIOS_DOWNLOAD   -101	//�����ļ�ʧ��


/*net error : ERR_NET_ */
#define ERR_NET_CONNECT		-200  //�������Ӳ�ͨ
#define ERR_NET_SEND		-201    //���ݷ��ͳ���
#define ERR_NET_RECV		-202    //���ݽ��ճ���
#define ERR_NET_RECVFILE	-203  //�����ļ�����
#define ERR_NET_SENDFILE	-204  //�����ļ�����

/*trans errot : ERR_TRN_ */
#define ERR_TRN_SUBCODE    -300   //��Ч����ϵͳ����
#define ERR_TRN_STATION    -301   //��Ч��վ���


/*EN_CARD error : ERR_ENCARD_ */
#define ERR_ENCARD_RHEAD    -500  //�����ܿ�ͷ��
#define ERR_ENCARD_CONFIG   -501   //������������
#define ERR_ENCARD_RKEY     -502     //����Կ��
#define ERR_ENCARD_OPEN     -503   //�򿪼��ܿ�ʧ��
#define ERR_PSAM_INIT       -504     //psam����ʼ��ʧ��
#define ERR_PSAM_FACTORY    -505  //��������Ϣʧ��
#define ERR_PSAM_LOCAL      -506   //������������Ϣʧ��
#define ERR_PSAM_SERVER     -507    //��������������Ϣʧ��
#define ERR_PSAM_KEY        -508   //����Կ������Ϣʧ��
#define ERR_PSAM_AUTH		-509   //��������Ȩ��Ϣʧ��
#define ERR_PSAM_SAUTH		-510   //����ϵͳ��Ȩ��Ϣʧ��


/*DLL error : ERR_DLL_ from -1000 */
#define ERR_DLL_SIOS	-1001                     //SIOSû����������
#define ERR_DLL_DSQL	-1002                     //DSQL��������
#define ERR_DLL_BUF_MIN -1003                     //����Ļ�����̫С�����ܿ���
#define ERR_DLL_UNPACK  -1004                     //�������
#define ERR_DLL_REDO    -1005                     //����ҵ��2003-09-05
#define ERR_DLL_NOPHOTO -1006                     //û����Ƭ�ļ�
#define ERR_DLL_NOFILE  -1007                     //ָ���ļ�������

/*������������ֵ from 1100*/
#define    ERR_FILEEXIST  -1100            //�ļ��Ѿ�����
#define    ERR_REFUSE     -1101            //�������ܾ�
#define    ERR_NO_FILE    -1102            //û���ļ�
#define    ERR_DEL_FAIL   -1103            //ɾ���ļ�ʧ��
#define    ERR_COMM_FAIL  -1104            //ͨѶʧ��


/*����������ֵ���� from 1200*/
#define ERR_TA_TRANAMT		-1200                     //���׶����
#define ERR_TA_NOT_INIT		-1201                     //������APIû�г�ʼ��
#define ERR_TA_CARDREADER   -1202                     //����������
#define ERR_TA_READCARD     -1203                     //����ʧ��
#define ERR_TA_WRITECARD    -1204                     //д��ʧ��
#define ERR_TA_LIMIT_FUNC   -1205                     //�������ù�������
#define ERR_TA_CARDTYPE     -1206                     //�������ѿ�
#define ERR_TA_SNO			-1207                     //�Ǳ�ԺУ��
#define ERR_TA_EXPIRECARD   -1208                     //���ڿ�
#define ERR_TA_FAIL_CHGUT   -1209                     //�޸��ÿ�����ʧ��
#define ERR_TA_NOT_SAMECARD -1210                     //д��ʱ���Ų���
#define ERR_TA_WRONG_PWD    -1211                     //������ʱ�����������
#define ERR_TA_LOW_BALAN    -1212                     //��������
#define ERR_TA_EXCEED_QUOTA -1213                     //���������޶�
#define ERR_TA_LOST_CARD    -1214                     //��ʧ��
#define ERR_TA_FREEZE_CARD  -1215                     //���Ῠ
#define ERR_TA_CARDNO       -1216                     //�����ʺŲ���
#define ERR_TA_ID_CLOSE     -1217                     //��ݹر�
#define ERR_TA_CR_DLL		-1218                     //���ض�������̬���ӿ�ʧ��
#define ERR_TA_CR_INIT		-1219                     //��������ʼ��ʧ��
#define ERR_TA_PARA			-1220                     //��������
#define ERR_TA_NOREC		-1221                     //û������ʻ�
#define ERR_TA_SUB_SUCC		-1222                     //�����ɹ�,Ҳ����ȷ�ķ�����Ϣ
#define ERR_TA_SUB_FAIL		-1223                     //����ʧ��,Ҳ����ȷ�ķ�����Ϣ
#define ERR_TA_INITED		-1224                     //�������Ѿ���ʼ������ر�
#define ERR_TA_UP_DLL		-1225                     //����UpdateAPI.dll��̬��ʧ��
#define ERR_TA_LOCAL_DATE	-1300					  //����������ϵͳ���ڲ�һ��

// kingstar define error code
#define ERR_READ_AUTH_CARD -2000		// ��ȡ��Ȩ��ʧ��
#define ERR_AUTHCARD_RIGHT  -2001		// ��Ȩ������Ȩ��
#define ERR_AUTH_FAILED		-2002		// ��Ȩʧ��
#define ERR_ENCRYPT_ERR		-2003		// ���ܴ���
#define ERR_DECRYPT_ERR		-2004		// ���ܴ���
#define ERR_SERIAL_CRC		-2005		// ��ˮ�ãңô���
#define ERR_READ_EOF		-2006		// ��ȡ�ļ�����β

#endif //
