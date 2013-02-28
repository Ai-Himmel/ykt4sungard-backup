#ifndef _BUBANK_BANKERR_H_
#define _BUBANK_BANKERR_H_

#define EB_SUCCESS        0 //�ɹ�
#define EB_SYSTEM         1 //ϵͳ����
#define EB_NETWORK        2 //�������

///////////////////////////////////////////////////////////////////////////////
#define EB_AUTHENTICATION 11 //��֤����,��Կ�����κŲ���ȷ
#define EB_LOGIN          12 //ǩ������
#define EB_OUTSERVICE     13 //���ڷ���ʱ��
#define EB_BANKLINK       14 //�����������
#define EB_TERMSEQERR     15 //�ն���ˮ���ظ�
#define EB_DTLNOTEXITS    16 //��ˮ������
#define EB_SYS_CUTON      17 //ϵͳ������

///////////////////////////////////////////////////////////////////////////////
#define EB_CARDLOST       21 //���ѹ�ʧ
#define EB_CARDFROZEN     22 //���Ѷ���
#define EB_CARDCANCEL     23 //����ע��
#define EB_CARDNOTEXIST   24 //��������
#define EB_CARDEXPIRED    25 //���ѹ���
#define EB_CARDDPSCNTERR  26 //����ֵ�����쳣
#define EB_CARDBAL_ABNORMAL 27 //������쳣���뵽�������Ĵ���

///////////////////////////////////////////////////////////////////////////////
#define EB_BANKNOTSUPPORT 30 //�����в�֧��
#define EB_BANKCARDNOTSUPPORT 31 //�����п�������Ȧ��
#define EB_DTLHASDEAL     32  //��ˮ�Ѵ���
#define EB_DTLERROR       33  //��ˮ״̬�쳣
///////////////////////////////////////////////////////////////////////////////
#define EB_QUERYCOND      41 //��ѯ��������

//////////////////////////////////////////////////////////////////////////////
#define EB_UNKNOWN        99 //��������


#endif
