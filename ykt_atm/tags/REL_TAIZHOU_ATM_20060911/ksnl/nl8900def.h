#ifndef NL8900_DEF_H
#define NL8900_DEF_H

#define rsSuccess	 1			// �ɹ�
#define rsTimeOut	-1			// ���ʱ
#define rsUnknowCmd	-2			// δ֪����
#define rsTransErr	-3			// �������
#define rsUnknowResp -4			// δ֪��Ӧ
#define rsEscExit	-5			// ��ESC�˳�

#define rrERR_FORMAT	-4001		// ���ò�����
#define rrERR_DATAFORMAT	-4002	// ���ݸ�ʽ��
#define rrERR_LENGTH	-4003		// ���ճ��ȴ�
#define rrERR_READ	-4004			// ����
#define rrERR_WRITE	-4005			// д��
#define rrERR_LESS	-4006			// ERR_LESS
#define RrERR_BCC	-4007			// У���
#define RrERR_CardData	-4008		// �����ݴ�
#define RrERR_OpenCom	-4009		// �򿪴��ڴ�
#define rrNotag	-4012				// �ڲ�����ַû����Ƶ��
#define rrCrc	-4013				// ����CRC����
#define rrEmpty	-4014				// ֵ���
#define rrAuth	-4015				// ��֤����
#define rrParity	-4016			// ��żУ�����
#define rrCode	-4017				// ��RF���е�ͨѶ����
#define rrKey	-4018				// ��֤��Կ����
#define rrBitcount		-4019		// ���ձ���������
#define rrBytecount	-4021			// �����ֽ�������
#define rrTrans	-4022				// ����Transferִ�д���
#define rrWrite	-4023				// ����Writeִ�д���
#define rrIncr	-4024				// ����Incrementִ�д���
#define rrDecr	-4025				// ����Decrementִ�д���
#define rrRead	-4026				// ����Readִ�д���
#define rrOvfl	-4027				// ֵ�������
#define rrFraming		-4028		// ֡����
#define rrUnknowncommand	-4029	// ��Ч����
#define rrColl	-4030				// ��ͻ����
#define rrInit		-4031			// ��ʼ������
#define rrInterface	-4032			// �ӿڴ���
#define rrAccesstimeout	-4033		// ���ʳ�ʱ
#define rrNobit		-4034			// ����ͻ�����е�TagType�����
#define rrQuit	-4035				// ����ж��˳�
#define rrRevbufoverflow	-4036	// ���ջ��������
#define rrSenbufoverflow	-4037	// ���ͻ��������
#define rrPara	-4038				// ��������
#define RrNoloadkey	-4039			// ûװ��Կ����


#define DCLR_NLFUNC(r,name,arg) \
	typedef r (* LP##name) arg; \
	extern LP##name name;

#define DEF_NLFUNC(name) \
	LP##name name = NULL;	\
	
#define LOAD_NLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if( NULL == name) \
		return -1;

//////////////////////////////////////////////////////////////////////////
// �ӿں�������

DCLR_NLFUNC(int,Mag_ReadCard,(char *tk2,char *tk3, int wTime,int tkNum))
DCLR_NLFUNC(int,IC_SelectCard,(char *str))
DCLR_NLFUNC(int,IC_Powerup,(char *str, unsigned char* rcvData))
DCLR_NLFUNC(int,IC_Powerdown,(char *str))
DCLR_NLFUNC(int,IC_IcCRW,(int len ,char sendcmdbuf[200], char rcvbuf[200]))
DCLR_NLFUNC(BOOL,ICMag_ComInit,(char *_ComType, int _Syn))
DCLR_NLFUNC(int,ICMag_OpenCom,(void))
DCLR_NLFUNC(int,ICMag_CloseCom,(void))
DCLR_NLFUNC(int,IC_ReadState,(unsigned char *Resp))
DCLR_NLFUNC(int,ICMag_ReadEdition,(unsigned char *Resp))
DCLR_NLFUNC(int,IC_StopOper,(void))
DCLR_NLFUNC(int,IC_SoftRest,(void))
DCLR_NLFUNC(void,IC_getReceData,(char cpto[200]))
DCLR_NLFUNC(int,IC_getReceLen,(void))
DCLR_NLFUNC(int,IC_SelectIcCardType,(int cardtype_num))
DCLR_NLFUNC(void,ICMag_GetErrMsg,(char *ErrMsg,int ErrCode))

DCLR_NLFUNC(int,Rf_GetStatus,(unsigned char *_Status))
DCLR_NLFUNC(int,Rf_StoreKey,(unsigned char _Mode,unsigned char _SecNr,
			unsigned char *_Nkey))
DCLR_NLFUNC(int,Rf_LoadKey,(unsigned char _Mode,unsigned char _SecNr,
			unsigned char _AuthSector))
DCLR_NLFUNC(int,Rf_HL_Read,(unsigned char _Mode,unsigned char _BlockAddr,
			unsigned long _Snr,
			unsigned char *_Data,
			unsigned long *_NSnr))
DCLR_NLFUNC(int,Rf_HL_Write,(unsigned char _Mode,unsigned char _BlockAddr,
			unsigned long *_Snr,
			unsigned char *_Data))
DCLR_NLFUNC(int,Rf_HL_Initval,(unsigned char _Mode,unsigned char _BlockAddr,
			unsigned long _Value,
			unsigned long *_Snr))
			
DCLR_NLFUNC(int,Rf_ComInit,(char *_ComType,int _Syn))
DCLR_NLFUNC(BOOL,Rf_GetSerial,(unsigned char *_serial))
DCLR_NLFUNC(BOOL,Rf_ComClose,())

#endif