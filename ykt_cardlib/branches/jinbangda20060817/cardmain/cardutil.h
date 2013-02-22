#ifndef CARDUTIL_H
#define CARDUTIL_H

#define SELECTSMARTCARDTYPE 0x18

// 
#ifdef __cplusplus
extern "C" {
#endif

	//���п��ṹ����
#pragma pack(1)
	
	typedef struct               
	{
		unsigned char ShowCardNo[11];			//�û�����ʾ����
		unsigned char CardNo[8];				//�û������׿���
		unsigned char DeadLineDate[9];			//�û���ʹ�ý�ֹ����
		int CardRightType;						//�û���ʹ��Ȩ�����ͣ�1--254��
		unsigned char ucName[9];				//����
		unsigned char ucDutyNo[9];				//ְ�����
		unsigned char ucCertificateNo[21];		//֤������
		unsigned char ucDepartmentNo[11];		//���ű��
		unsigned char ucIdentifyNo[5];			//��ݴ���
		unsigned char ucSexNo[2];				//�Ա����
		unsigned char ucCardNo[21];				//���ţ����Ż�ѧ�ţ�
		unsigned char ucPwd[6];					//������
		unsigned char ucLibraryNo[21];			//ͼ��֤��
		int Money;								//���֣�
		unsigned char isFormat;					//�Ƿ��ʽ����һ����
	}TPublishCard;
	
	typedef struct
	{
		DWORD RemainMoney;			// ����Ǯ�����
		WORD DealTimes;				// �û���������ˮ��
		BYTE DealYear;				// ��������
		BYTE DealMonth; 
		BYTE DealDay;
		BYTE DealHour;
		BYTE DealMin;
		BYTE DealTimes_CurTime;		// �ۼƽ��״���(��ǰʱ�����)
		BYTE DealTimes_CurDay;		// �ۼƽ��״���(������)
	} LOOPPURSEINFO ,*LPLOOPPURSEINFO;
	
#pragma pack()

#define CARDUTIL_API __declspec(dllimport) 

#ifdef __cplusplus
}
#endif

#endif