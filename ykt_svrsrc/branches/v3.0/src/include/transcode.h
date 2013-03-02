#ifndef TRANSCODE_H
#define TRANSCODE_H
#define CARDOPEN     1001


#define TCTYPE_ADD 1	//���
#define TCTYPE_DEL 2	//ɾ��
#define TCTYPE_UPD 3	//�޸�
#define TCTYPE_QRY 4	//��ѯ
#define TCTYPE_IMP 5	//����
#define TCTYPE_CHK 6	//���
#define TCTYPE_RESET 7	//����
#define TCTYPE_REVERSE 1 //����


#define MAKETRANSCODEADD(x) (x+TCTYPE_ADD)
#define MAKETRANSCODEDEL(x) (x+TCTYPE_DEL)
#define MAKETRANSCODEUPD(x) (x+TCTYPE_UPD)
#define MAKETRANSCODEQRY(x) (x+TCTYPE_QRY)
#define MAKETRANSCODEIMP(x) (x+TCTYPE_IMP)
//#define MAKETRANSCODECHK(x) (x+TCTYPE_CHK)
//#define MAKETRANSCODERESET(x) (x+TCTYPE_RESET)

#define MAKETRANSCODEREVERSE(x) (x+TCTYPE_REVERSE)


#define IS_TRANSCODEQRY(x) (x%10==TCTYPE_QRY)

//���������:��1Ϊ��ʾ���͵�2��3λ��ʾ��������4Ϊ���
//TCM_��־Ϊ�������
#define TCM_AREA	  		1000	//����
#define TCM_BRANCH 			1010	//����
#define TCM_SITE   			1020	//վ��
#define TCM_OPER   			1030	//����Ա
#define TC_OPERPWDUPD 		1040	//����Ա�����޸�
#define TC_OPERPWDRESET 	1041	//����Ա��������
#define TCM_OPERSITE 		1050	//����Ավ��
#define TCM_AUTHTPL  		1060	//Ȩ��ģ��
#define TCM_DEPT			1070	//����
#define TCM_SPECIALTY 		1080	//רҵ
#define TCM_SUBSYS			1090	//��ϵͳ
#define TCM_DEVICE			1100	//�豸
#define TCM_DICTIONARY		1120	//�����ֵ�
#define TCM_PARAM			1130	//ȫ�ֲ���
#define TCM_CARDTYPE 		1140	//�����
#define TCM_PURSE			1150	//Ǯ��
#define TCM_CUSTTYPE		1160  	//�ͻ����
#define TCM_FEETYPE			1170  	//�շ����
#define TCM_CFGFEE			1180  	//��������
#define TCM_TASK			1190	//�ƻ�����
#define TC_TASKLOGQRY		1200	//�ƻ�������־��ѯ
#define TCM_MQ				1210	//��Ϣ����
#define TCM_BANKCARD		1220  	//���п���
#define TCM_POSSHOP 		1230 	//POS�̻�
#define TCM_DEPOSITSHOPPOS 	1240 	//��ֵ�̻�POS
#define TCM_DEPOSITOPER 	1250    //��ֵ����Ա
#define TCM_DEPOSITOPERPOS 	1260 	//��ֵ����ԱPOS
#define TCM_MEAL			1270	//�ʹ�
#define TCM_SHOPMEAL		1280    //�̻��ʹ�
#define TCM_SHOPRAKEOFF  	1290    //�̻�Ӷ��
#define TCM_CUSTOMER 		1300	//�ͻ���Ϣ
#define TCM_CFGSHOPFEE 		1310	//�̻����ѷ���
#define TCM_CARDTYPERIGHT 	1320	//�����Ȩ��

#define TCM_DOORGROUP		1400   	//�Ž���

#define TC_CUSTOMERTMPIMP 	2001	//�ͻ���Ϣ����
#define TC_CUSTOMERTMPDEL 	2002	//�ͻ���Ϣ����ɾ��
#define TC_CUSTOMERTMPUPD 	2003	//�ͻ���Ϣ�����޸�
#define TC_CUSTOMERTMPQRY 	2004	//�ͻ���Ϣ�����ѯ
#define TC_CUSTOMERTMPCHK 	2005	//�ͻ���Ϣ�������


#define TC_DEVICETMPIMP  	2011  	//�豸�ļ�����
#define TC_DEVICETMPDEL  	2012  	//�豸�ļ�����ɾ��
#define TC_DEVICETMPUPD  	2013  	//�豸�ļ������޸�
#define TC_DEVICETMPQRY  	2014  	//�豸�ļ���ѯ
#define TC_DEVICETMPCHK  	2015  	//�豸�ļ����

#define TC_SHOPPOSTMPIMP  	2021  //�̻�POS�ļ�����
#define TC_SHOPPOSTMPDEL  	2022  //�̻�POS�ļ�����ɾ��
#define TC_SHOPPOSTMPUPD  	2023  //�̻�POS�ļ������޸�
#define TC_SHOPPOSTMPQRY  	2024  //�̻�POS�ļ������ѯ
#define TC_SHOPPOSTMPCHK  	2025  //�̻�POS�ļ��������

#define TC_POSDTLTMPIMP 	2030  //POS��ˮ����
#define TC_POSDTLTMPADD		2031  //POS��ˮ�ֹ�¼��
#define TC_POSDTLTMPDEL 	2032  //POS��ˮ����ɾ��
#define TC_POSDTLTMPUPD 	2033  //POS��ˮ�����޸�
#define TC_POSDTLTMPQRY 	2034  //POS��ˮ�����ѯ
#define TC_POSDTLTMPCHK 	2035  //POS��ˮ�������

#define TCM_POSDTL 			2040  //POS�쳣��ˮ
#define TC_CARDGET			2100 //��Ƭ����
#define TC_CARDPUT			2110 //��Ƭ�Ͻ�
#define TC_CARDDISABLE		2120 //��Ƭ����
#define TC_CARDCHANGE   	2130 //��Ƭ����
#define TCM_CARDBAD			2140 //�����Ǽ�
#define TC_CARDQRY   		2154 //��Ƭ��ѯ

#define TC_AUTHCARDOPEN		2200 //��Ȩ������
#define TC_AUTHCARDCLOSE	2210 //��Ȩ������
#define TC_AUTHCARDLOSS		2220 //��Ȩ����ʧ
#define TC_AUTHCARDUNLOSS	2230 //��Ȩ�����
#define TC_AUTHCARDUPD		2240 //��Ȩ������
#define TC_AUTHCARDQRY		2254 //��Ȩ����ѯ

#define TC_CARDOPEN			3000  //��Ƭ����
#define TC_CARDOPENREV		3001  //��Ƭ��������
#define TC_CARDCLOSE		3010  //��Ƭ����
#define TC_CARDRENEW		3020  //������
#define TC_CARDRETURN		3030  //������
#define TC_CARDLOSS			3040  //����ʧ
#define TC_CARDUNLOSS   	3050  //�����
#define TC_CARDFROZE		3060  //������
#define TC_CARDUNFROZE  	3070  //���ⶳ
#define TC_CARDUPDBASEINFO	3080  //���¿�������Ϣ
#define TC_CARDUPDEXPIREDATE 3081  //���¿���Ч��
#define TC_CARDUPDBADCARD	3082 //�����޸�
#define TC_CARDREWRITE		3083 //��д����Ϣ
#define TC_CARDCLEAR 		3084 // ��տ���Ϣ
#define TC_CARDSAVEINFO		3090 //�������濨��Ϣ
#define TC_CARDINSTEAD		3091 //����
#define TC_CARDINSTEADREV	3092 //��������

#define TC_CARDDEPOSIT  	3100  //����ֵ
#define TC_CARDDEPOSITREV 	3101 //����ֵ����
#define TC_CARDDRAW  		3110  //��֧ȡ
#define TC_SUBSIDYIMP		3121  //��������
#define TC_SUBSIDYDEL		3122  //����ɾ��
#define TC_SUBSIDYUPD		3123  //�����޸�
#define TC_SUBSIDYQRY		3124  //������ѯ
#define TC_SUBSIDYPUT		3130  //�����·�
#define TC_POSDEPOSIT 		3140  //POS��ֵ
#define TC_POSDEPOSITREV 	3141  //POS��ֵ����
#define TC_SHOPPOSDEPOSIT  	3150  //��ֵ�̻�POS��ֵ
#define TC_SHOPPOSDEPOSITREV  3151  //��ֵ�̻�POS��ֵ����
#define TC_POSDRAW  		3160  //POS����
#define TC_POSDRAWREV  		3161  //POS���ѳ���
#define TC_BANKTRANS		3170  //Ȧ��ת��
#define TC_CARDPAYMENT		3180  //��֧������
#define TC_CARDPWDUPD		3200  //�������޸�
#define TC_CARDPWDRESET		3210  //����������
#define TC_SUBSIDYGET		3220  //������ȡ
#define TC_CARD2CARTRANS	3230  //����ת��(�ɿ����¿�)
#define TC_CARDBALMOD		3240  //��������

#define TC_TRANSREV			4000  	//���˽���
#define TC_CARDACCDIFF		4001  	//���ⲻƽ

#define TC_SHOPOPEN			5001	//�̻�����
#define TC_SHOPCLOSE		5002	//�̻�����
#define TC_SHOPUPD			5003	//�̻���Ϣ�޸�
#define TC_SHOPQRY      	5004	//�̻���Ϣ��ѯ
#define TC_SHOPSAVING 		5010    //�̻����

#define TC_EACCOPEN			6000  	//����Ǯ������
#define TC_EACCCLOSE		6010  	//����Ǯ������
#define TC_EACCDEPOSIT		6020  	//����Ǯ����ֵ
#define TC_EACCDRAW			6030  	//����Ǯ��ȡ��
#define TC_CARD2EACC		6040	//��������Ǯ��ת��
#define TC_EACC2CARD		6050	//����Ǯ������ת��
#define TC_BANK2EACC		6060	//���п�������Ǯ��ת��
#define TC_EACCSTOPPAY		6070  	//����Ǯ��ֹ��
#define TC_EACCUNSTOPPAY 	6080  	//����Ǯ���⸶
#define TC_EACCQRY		 	6094	//����Ǯ����Ϣ��ѯ
#define TC_EACCPWDUPD 	 	6100  	//����Ǯ�������޸�
#define TC_EACCPWDRESET  	6110  	//����Ǯ����������
#define TC_EACCLOGIN		6200	//����Ǯ��֧��ϵͳǩ��
#define TC_EACCQRYBAL		6210	//����Ǯ������ѯ
#define TC_EACCFROZE		6220	//����Ǯ������
#define TC_EACC2SHOP		6230	//����Ǯ��֧��
#define TC_EACC2SHOPREV		6240	//����Ǯ��֧������
#define TC_MANUALDRCR	 	7000  	//�ֹ����
#define TC_SHOPPAYMENT   	8000   	//�̻����

#endif /* TRANSCODE_H */
