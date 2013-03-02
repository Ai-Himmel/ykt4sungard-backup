/*: ����ȫ�ֲ�����                                       
  ����  : ����                                  
  ʱ��	��2004-08-18                          
*/ 

#ifndef  __GLOBALPARAMETER_H_
#define  __GLOBALPARAMETER_H_


#define GLOBE_FLAG_BALANCE		1	 //�����־ȫ�ֲ���
#define GLOBE_MAXCARDBALANCE		2	 //����ֵ���
#define GLOBE_MONTH_ACC_TIME		3	//�½�����
#define GLOBE_BLACKSHEETVER		5	 //�������汾
#define GLOBE_BLACKSHEETTIME		6	 //��������Ч��
#define GLOBE_TMPCARDVALIDDATE	7	 //������ʱ����Ч��
#define GLOBE_TRADESEIALDATE		8	 //Ĭ�������豸������ˮͬ�����
#define GLOBE_RENEWCARDDATE		9	 //Ĭ�Ϲ�ʧ������ʽ������
#define GLOBE_NO_NAME_TMPCARDVALIDDATE	10	 //�Ǽ�����ʱ����Ч��
#define GLOBE_MAX_CARDDB_NOBALANCE_TIMES	11	 //�����ⲻƽ�������壨������
#define GLOBE_MAX_CARDDB_NOBALANCE_MONEY	12	 //�����ⲻƽ�����
//#define GLOBE_FLAG_SYNCCUT					13	 //�ͻ�ͬ�������ʶ
#define GLOBE_FLAG_TEMPCARD_FEETYPE	13
#define GLOBE_FLAG_TEMPCARD_CUTTYPE  14
#define GLOBE_SCHOOL_NAME			15  //һ��ͨ�û���
#define GLOBAL_MAX_PER_SUBSIDY	    16 // ���ʲ��������




/*��ز��֣��豸���*/
#define GLOBE_DEV_BEATTIME	1000	 //�豸�������ʱ��
#define GLOBE_DEV_BEATCOUNT	1001	 //û���յ��豸����������ֵ
#define GLOBE_DEV_BSVER    		1002	 //�豸�������汾����ϵͳ��ǰ�汾�Ų�ֵ��ֵ       
#define GLOBE_DEV_STORGEP  	1003	 //Ӳ��Ӧ�ðٷֱȾ���ֵ                           
#define GLOBE_DEV_MEMORYP  	1004	 //�ڴ�Ӧ�ðٷֱȾ���ֵ                           
#define GLOBE_DEV_CPUP     		1005	 //CPUӦ�ðٷֱȾ���ֵ 
#define GLOBE_DEV_TIME     		1006	 //�豸ʱ�Ӳ�ͬ����ֵ
/*��ز��֣�Ӧ�ü��*/
#define GLOBE_APP_BEATTIME	1100	 //Ӧ���������ʱ��
#define GLOBE_MIF_SUMTIME		1101	 //Ĭ�Ͻ�������ʱ��
#define GLOBE_MIF_NOTIFTIME	1102	 //Ĭ�ϱ�������ʱ��ȫ�ֲ���(��λ��)

#define GLOBE_MIF_CARDOPERATETIMES	1103	 //��ض�ʱ���ڿ�������������ʱ��ȫ�ֲ���
#define GLOBE_MIF_CARDOPERATECOUNT	1104	 //��ض�ʱ���ڿ���������������������ȫ�ֲ���
#define GLOBE_MIF_CARDOPERATEMAXFEE	1105	 //���ο�����Ĭ������ȫ�ֲ���

#define GLOBE_DEV_DAY_TRADE_LIMIT 1106		// �ն��������޶�
#define GLOBE_DEV_ONCE_TRADE_LIMIT 1107		// �ն˵��������޶�

/*�������*/
#define GLOBE_999_SHUTTIMES	2005	 //����ʱ��
#define GLOBE_999_DEVAUTHKEY	2006	 //�豸��Ȩ��Կ
#define GLOBE_999_65CARDKEY	2007	 //65�࿨��Կ

/* �Ž����*/
#define GLOBE_DOOR_HOLIDAY_MAX 2008	//�Ž��ڼ���������
#define GLOBE_PURSE_TWO_CARDKEY  2009	 //СǮ����Կ
#define GLOBE_WATER_PURSE_NO  2010 //ˮ��Ǯ����

/*СǮ������, ��λΪԪ*/
#define GLB_PACKET_LIMITS     3001
//add by hhd
#define GLOBLE_SYSPARA_STATIC_KEY 	2006  /* ��Կ*/

#define GLOBAL_SCHOOL_CODE	2999  /* ѧУ��� */

// add by ���� 2008-1-11 , �����ļ���·��
#define GLOBAL_DOWNLOAD_PATH	2305
// �ϴ��ļ�·��
#define GLOBAL_UPLOAD_PATH		2306

//�����ļ���ִ�г�����·��
#define GOLBAL_EXC_ACC_CHK_PATH	2100

/* add by ���� 2008-1-11 , �ɽ���ѧ�ǹ��� ISBP �����ļ�ʹ�� */
// ��λί����
#define GLOBAL_ISBP_ENTRUST_CODE 4000
// ҵ�����
#define GLOBAL_ISBP_OPERATION_CODE 4001
// ί�е�λ�ʺ�
#define GLOBAL_ISBP_BANKCODE 4002
// ί�е�λ����
#define GLOBAL_ISBP_NAME 4003

#endif
