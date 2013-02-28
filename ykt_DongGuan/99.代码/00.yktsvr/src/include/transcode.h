#ifndef TRANSCODE_H
#define TRANSCODE_H

#define TC_DICTADD			1000	//�����ֵ�����
#define TC_DICTDEL			1010	//�����ֵ�ɾ��
#define TC_DICTUPD			1020	//�����ֵ��޸�

#define TC_PARAMADD			1030	//ȫ�ֲ������
#define TC_PARAMDEL			1040	//ȫ�ֲ���ɾ��
#define TC_PARAMUPD			1050	//ȫ�ֲ����޸�

#define TC_CARDTYPEADD 		1090	//��������
#define TC_CARDTYPEDEL 		1100	//�����ɾ��
#define TC_CARDTYPEUPD 		1110	//������޸�

#define TC_AUTHTPLADD  		1120	//Ȩ��ģ�����
#define TC_AUTHTPLDEL  		1130	//Ȩ��ģ��ɾ��
#define TC_AUTHTPLUPD  		1140	//Ȩ��ģ���޸�

#define TC_BRANCHADD		1150	//����ע��
#define TC_BRANCHDEL		1160	//����ע��
#define TC_BRANCHUPD		1170	//�����޸�

#define TC_SITEADD			1180	//վ��ע��
#define TC_SITEDEL			1190	//վ��ע��
#define TC_SITEUPD			1200	//վ���޸�

#define TC_SUBSYSADD		1210	//��ϵͳע��
#define TC_SUBSYSDEL		1220	//��ϵͳע��
#define TC_SUBSYSUPD		1230	//��ϵͳ�޸�

#define TC_DEVICEADD			1240	//�豸���
#define TC_DEVICEDEL			1250	//�豸ɾ��
#define TC_DEVICEUPD			1260	//�豸�޸�

#define TC_DEVMAIN			1270	//�豸ά��
#define TC_DEVDISCARD		1280	//�豸����
#define TC_DEVREUSE			1290	//�豸����


#define TC_OPERADD			1300	//����Աע��
#define TC_OPERDEL			1310	//����Աע��
#define TC_OPERUPD			1320	//����Ա�޸�

#define TC_OPERPWDUPD 		1330	//����Ա�����޸�
#define TC_OPERPWDRESET 	1340	//����Ա��������

#define TC_OPERSITEADD		1350	//����Ավ�����
#define TC_OPERSITEDEL		1360	//����Ավ��ɾ��
#define TC_OPERSITEUPD		1370	//����Ավ���޸�

#define TC_OPERAUTHADD		1400	//����ԱȨ������
#define TC_OPERAUTHDEL		1410	//����ԱȨ��ɾ��

#define TC_CUSTAPPLYADD		2000	//��ݸ����Ϣ¼��
#define TC_CUSTAPPLYDEL		2010	//��ݸ����Ϣɾ��
#define TC_CUSTAPPLYUPD		2020	//��ݸ����Ϣ�޸�
#define TC_CARDNOGEN		2030	//��ʵ����������
#define TC_MAKECARDAPROVE	2040	//�ƿ��������
#define TC_IMPMAKECARDDATA	2050	//�����ƿ�����
#define TC_PRINTCARDAPROVE	2060	//�����ƿ��������
#define TC_IMPMOBILE			2070	//�����ֻ���
#define TC_CARDINFOUPD		2080 //����Ϣ�޸�

#define TC_OPENCARDAPPLY	2100	//�쿨����
#define TC_CHANGECARDAPPLY	2110	//��������
#define TC_RENEWCARDAPPLY	2120	//��������
#define TC_CLOSECARDAPPLY	2130	//��������
#define TC_APPLYCANCEL		2140	//���볷��

#define TC_CARDOPEN			2200  //������
#define TC_CARDINSTEAD		2210  //����
#define TC_CARDRENEW		2220  //����
#define TC_CARDCLOSE		2230  //����
#define TC_CARDLOSS			2240  //����ʧ
#define TC_CARDUNLOSS   		2250  //�����
#define TC_CARDFROZE		2260  //������
#define TC_CARDUNFROZE  		2270  //���ⶳ

#define TC_CARDPWDUPD		2300  //�������޸�
#define TC_CARDPWDRESET		2310  //����������
#define TC_CARDBALMOD		2320  //��������
#define TC_CARDBALUPD		2330  //���������


#define TC_SELLCARD			3000	//���۷�ʵ����
#define TC_ISSUECARD			3010	//����ʵ����
#define TC_PREPAID			3020	//�տ��ɱ���
#define TC_ISSUEDPS			3030	//������ֵ

//#define TC_CARDDPSATM  		3100  //�����ֽ��ֵ/����
#define TC_CARDDPSCASH  		3100  //�ֽ��ֵ/����
#define TC_CARDDPSBANK  		3110  //���п���ֵ/����
#define TC_CARDDPSBILL		3120  //֧Ʊ��ֵ/����
#define TC_BANKTRANS		3200  //Ȧ��ת��

#define TC_CARDPAYMENT		3300  //��֧������

#define TC_POSPAY  			3400  //POS����/����
#define TC_ONLINEPAY		3410	//��������
#define TC_LOSTPAY			3500	//��ʧ����
#define TC_CLOSEPAY			3510	//ע������
#define TC_PAYREPEAT        		3520	//�ѻ��ظ�����

#define TC_POSLOCKCARD		3600	//POS����
#define TC_CONSUMEFAIL		3700	//����ʧ��
#define TC_CARD2CARD		3800 //���ת��
#define TC_TRANSREV			3900	 //���׳���
#define TC_MERCHOPEN		4000	//�̻�����
#define TC_MERCHCLOSE		4010	//�̻�����
#define TC_MERCHUPD			4020	//�̻���Ϣ�޸�

#define TC_MERCHDEVADD		4100	//�̻��豸���
#define TC_MERCHDEVUPD		4120	//�̻��豸�޸�
#define TC_MERCHDEVDEL		4130	//�̻��豸ɾ��


#define TC_SHOPSAVING 		4200    //�̻����
#define TC_SHOPPOSDEPOSIT  	4210  //��ֵ�̻�POS��ֵ/����


#define TC_PKGDEL			4310 //ɾ��������
#define TC_PKGUPD			4320 //�޸İ�����

#define TC_PKGFILEDEL		4410 //ɾ�������ļ�
#define TC_PKGFILEUPD		4420 //�޸İ����ļ�


#define TC_SUBJADD			5000	//��Ŀ���
#define TC_SUBJDEL			5010	//��Ŀɾ��
#define TC_SUBJUPD			5020	//��Ŀ�޸�


#define TC_VOUCHERMAKE		6000	//ƾ֤¼��
#define TC_VOUCHERUPD		6010	//ƾ֤�޸�
#define TC_VOUCHERDEL		6020	//ƾ֤ɾ��
#define TC_VOUCHERSIGN		6030	//ƾ֤ǩ��
#define TC_VOUCHERCHECK		6040	//ƾ֤����
#define TC_VOUCHERCHECKREV	6050	//ƾ֤����ȡ��
#define TC_VOUCHERBOOK		6060	//ƾ֤����
#define TC_VOUCHERBOOKREV	6070	//ƾ֤����

#define TC_DAYEND			7000	//���ս���
#define TC_MONTHEND			7010	//��ĩ��ת
#define TC_YEAREND			7020	//���ս�ת

#endif /* TRANSCODE_H */
