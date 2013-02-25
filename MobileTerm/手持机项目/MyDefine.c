/****************************************************************************
*
*�ļ�(File):         MyDefine.c
*
*�޸�(Modify):       2011-10-28 9:04:26
*
*����(Author):       Rain
*
*����(Compile):      ����ƽ̨(Smart Platform)
*
*����(Description):
*
*e-mail          :  rain_mcu@163.com
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011-10-28 9:04:26           Rain 
----------------------------------------------------------------------------
****************************************************************************/


//#define OPEN_WARNING_BEEP 

#define uchar unsigned char 
#define uint unsigned int 
#define ushort unsigned short

#define E_IpAddr                 0      //ip��ַ����ʼ��ַ��16�ֽ�
#define E_SsidAddr               16     //Ԥ��16�ֽ� 
#define E_PskAddr                32     //Ԥ��16�ֽ�
#define E_ChidAddr               48     //ͨ���ŵ� 1�ֽ�
#define E_GateWayAddr            49     //���� 16�ֽ�
#define E_NetMaskAddr            65     //��������16�ֽ�
#define E_PortAddr               81     //�˿ں�5�ֽ�  int��
#define E_TransRateAddr          86     //ͨѶ����1�ֽ�
#define E_BackColorAddr          87     //������ɫ2�ֽ�
#define E_FontColorAddr          89     //ǰ����ɫ2�ֽ�
#define E_ThemeColorAddr         142       //2�ֽ�
#define E_LocalSiteAddr          144    //����վ��1�ֽ�
#define E_AutoSleepAddr          150     //�Զ��ػ�ʱ��2�ֽ�
#define E_AutoElCloseAddr        92     //�����Զ��ر�ʱ��1�ֽ�
#define E_KeySondAddr            93     //��������1�ֽ�

#define E_ServerIpAddr           94     //������IP16�ֽ�
#define E_ServerPortAddr         110    //�������˿�5�ֽ�

#define E_SsidLenAddr            115    //SSID����1�ֽ�
#define E_PskLenAddr             116    //PSK���� 1�ֽ�
#define E_IpLenAddr              117    //IP���� 1�ֽ�
//#define E_PortLenAddr                    118   
#define E_ServerIpLenAddr        119    //������IP��ַ
#define E_ServerPortLenAddr      120    //�������˿ڳ��ȵ�ַ
#define E_GateWayLenAddr         121	   //���س��ȵ�ַ
#define E_NetMaskLenAddr         123    //�������볤�ȵ�ַ
#define E_PassWordAddr           124    //���������ַ 16�ֽ�
#define E_PassWordLenAddr        140    //�������볤�ȵ�ַ1�ֽ�
#define E_PassWordStatusAddr     141    //��������״̬
#define E_WifiPowerModleAddr     145    //wifi��������ʱ��



#define DISP_STATUS_INF           0     //�Ƿ���ʾ������Ϣ
#define DISP_OK_DELAY_TIME        2		//���óɹ���ʾ����ʱ��
#define DISP_ESC_DELAY_TIME       1		//ȡ��������ʾ����ʱ��
#define DISP_CHECK_DELAY_TIME     4

#define STX                       2		//Start 
#define ETX                       3		//End  

#define SendDateLen               4
#ifdef  OPEN_WARNING_BEEP 
#define OK_WARNING_BEEP           1
#define ERR_WARNING_BEEP          3
#else
#define OK_WARNING_BEEP           0
#define ERR_WARNING_BEEP          0
#endif
#define RECEIVE_DATE_ERR          -1
#define CRC_CHECK_ERR             -2
#define UID_CHECK_ERR             -3
#define SITE_CHECK_ERR            -4
#define CARD_CHECK_ERR            -5
#define READ_NET_ERR              -6
#define RECEIVE_DATE_OK            0

#define CZ_COMMAND_WORD_H          0x02   //�����ָߵ�ַ
#define CZ_COMMAND_WORD_L          0x12   //�����ֵ͵�ַ

//extern u16 G_HandleID;//���Ӿ��
  /*
struct	sDatasStruct//ͨѶ���ݸ�ʽ
{
	uchar	AddrH;//��ַ��
	uchar	AddrL;//��ַ��
	uchar	DatasLen;//���ݳ���
	uchar	Datas[1021];//���ݰ�
};
union	sDatasUnion
{
	uchar	S_DatasBuffer[1024];
	struct	sDatasStruct	S_DatasStruct;
};

      */




