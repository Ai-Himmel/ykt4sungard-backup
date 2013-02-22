#ifndef _YUCHUANDEF_H_
#define _YUCHUANDEF_H_


#pragma pack(1)
typedef struct 	
{	
	unsigned char Start_Time; 				// �Ƿ���ʱ��		
	unsigned char Use_Uint;   				// �Ʒѵ�λ		
	unsigned char Time_Money; 				// �շѽ��		
}One_Rate;

typedef struct 
{	
	unsigned char fee_count; 				// ���ʸ���		
	One_Rate  N_Rate[3]; 				// ��������� ,Ŀǰ��Ч3��
}Multilevel_Rate;
	
typedef struct 
{
	unsigned char  System_Flag;				//ϵͳ����ģʽ��ʵʱ0x11/����0x22/ά��0x33��
	unsigned char  Use_Mode;				//�۷ѹ���ģʽ������0x44/��ʱ0x55��
	unsigned char  PassWordRead[8];				//�û�������1
	unsigned char  PassWordWrite[8];			//�û�������2
	unsigned char  Use_Sector;				//�û���ʹ�õ�Ǯ��
	unsigned char  En_Card_Type[4];				//����ʹ�õĿ���	
	Multilevel_Rate Rate[20];            		//���ζ�׷���ģʽ��Ŀǰ֧��20�ࣩ
}JS_FEE_RATE;

typedef struct                                  		//��¼ָ��ṹ��
{
	unsigned  char  Record_Flag ;				//�洢״̬������0x00/��0x33��
	unsigned  long 	Record_All_Number ;			//�豸�ܴ洢����
	unsigned  long  Record_Get_Number ;			//�Ѳɼ�������
	unsigned  long  Record_Save_Number ;			//�Ѽ�¼������
	unsigned  char  Reserved;				//������0x00��
}JS_REC_INFO;

typedef struct                                  		//���Ѽ�¼�ṹ��
{
	unsigned long Record_Number;				//��¼��
	unsigned long User_NO;					//�û�����ˮ��
	unsigned long User_Card_Value;				//�û��������
	unsigned long User_Used_Value;				//�û������Ѷ�
	unsigned long Used_Address;				//�û��������豸��
	unsigned long Used_Times;				//�û������״���
	unsigned char Used_purse;				//�û���Ǯ����
	unsigned char Used_Time[6];				//����ʱ��
	unsigned char DEV_UID[4];				//�豸������ID��ȫ��Ψһ��
	unsigned char Used_Flag;				//��¼״̬�֣�������¼0x00��
}JS_RECORD;

#pragma pack()

#define DCLR_DLLFUNC(r,n,p) typedef r (__stdcall *LP##n) p; \
	extern LP##n n

#define DEF_DLLFUNC(n) LP##n n=NULL

#define LOAD_DLLFUNC_RET(h,n,r) do { n = (LP##n)GetProcAddress(h,#n); \
	if(n == NULL) return r; } while(0)

#define LOAD_DLLFUNC(h,n) LOAD_DLLFUNC_RET(h,n,-1)



DCLR_DLLFUNC(HANDLE,OpenCommAuto,(int CommPort,int BaudVal));
DCLR_DLLFUNC(int,CloseComm,(HANDLE icdev));
DCLR_DLLFUNC(int,JS_GET_RECORD,(HANDLE icdev,int Node_Addr,unsigned long REC_Number,unsigned long Device_UID,unsigned char *Woke_Flag,JS_RECORD &Record,int COM_time));
DCLR_DLLFUNC(int,JS_GET_APPOINTED_RECORD,(HANDLE icdev,int Node_Addr,unsigned long REC_Number,unsigned long Device_UID,JS_RECORD &Record,int COM_time));
DCLR_DLLFUNC(int,JS_SET_Black_Version,(HANDLE icdev,int Node_Addr,unsigned char *ver_data,unsigned long Device_UID,int COM_Time));
DCLR_DLLFUNC(int,JS_GET_Black_Version,(HANDLE icdev,int Node_Addr,unsigned char *ver_data,unsigned long Device_UID,int COM_Time));
DCLR_DLLFUNC(int,JS_SET_Black,(HANDLE icdev,int Node_Addr,unsigned long Device_UID,unsigned char *Black_Data,int COM_Time));
DCLR_DLLFUNC(int,JS_GetNodeTime,(HANDLE icdev,int Node_Addr,unsigned char *datetime,int COM_Times));
DCLR_DLLFUNC(int,JS_SetNodeTime,(HANDLE icdev,int Node_Addr,unsigned char *datetime,int COM_Times));
DCLR_DLLFUNC(int,JS_SET_ONE_Black,(HANDLE icdev,int Node_Addr,unsigned long Black_Card_Number,unsigned long Device_UID,unsigned char *Black_Data,int COM_Time));
DCLR_DLLFUNC(int,JS_GET_SYSTEM_INFO,(HANDLE icdev,int Node_Addr,JS_FEE_RATE&fee_rate,int COM_Times));
DCLR_DLLFUNC(int,JS_SET_SYSTEM_INFO,(HANDLE icdev,int Node_Addr,JS_FEE_RATE&fee_rate,int COM_Times));
DCLR_DLLFUNC(int,JS_SET_Address,(HANDLE icdev,int Node_Addr,int Address_Data,int COM_Times));
DCLR_DLLFUNC(int,JS_UID_SET_Address,(HANDLE icdev,int Node_Addr,unsigned int Address_Date,unsigned long Device_UID, int COM_Times));
DCLR_DLLFUNC(int,JS_ShakeHand,(HANDLE icdev,int Node_Addr,unsigned char *Password, LPSTR IAP_VER,LPSTR MCU_TYPE,unsigned char *Device_UID,  int COM_Times));

#define DAS_OK				 0					//���ݽ�������
#define write_PASS			 0					//���س���ɹ�
#define Comm_Init_Err		-1					//���ڳ�ʼ������
#define CommPort_Err		-2					//�˿ڴ���
#define Chksum_Err			-3					//ͨѶ����Ч�����
#define Rev_Data_Err		-4					//��������ʧ��
#define TIME_OUT_Err		-5					//ͨѶ��ʱ����
#define Para_Err			-6					//��������
#define Send_Data_Err		-7					//��������ʧ��
#define Get_status_Err		-9					//����״̬λ����
#define No_Data_Return		-11					//û�����ݷ���
#define No_BIN_Files		-21					//û�����ݷ���
#define Read_Files_ERR		-22					//û�����ݷ���
#define CRC_ERR				-26					//CRCЧ�����
#define Rev_LEN_Err			-27					//���ճ������
#define Password_Err		-28					//��Ȩ�������
#define Password_Para_Err   -29					//�����ʽ����
#define Encrypt_Err			-30					//���ݼ��ܴ���
#define Wrong_DEV_Err		9					//�豸����ID�Ų���
#define No_Record_Err		0x11				//û����ˮ

extern HANDLE g_comhandle;

#define TEST_COM_OPEN_RET(r) do {if(g_comhandle==NULL) return r;} while (0)
#define TEST_COM_OPEN_NORET do {if(g_comhandle==NULL) {WriteLog(100,"����û�д򿪣�");return;}} while (0)

#endif //_YUCHUANDEF_H_
