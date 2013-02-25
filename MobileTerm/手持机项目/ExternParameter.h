/****************************************************************************
*
*�ļ�(File):         ExternParameter.h
*
*�޸�(Modify):       2011-10-28 9:05:16
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
| V1.00  2011-10-28 9:05:16          Rain 
----------------------------------------------------------------------------
****************************************************************************/
#include <API.h>
 #include "WiFi/WiFi.h"


 extern u16 G_HandleID;//���Ӿ��
 extern char G_AddrIP[16]; 	 //����IP
 extern char RBackInfo[32];	 // �ص�����������Ϣ  ����
 extern char G_ServerIp[16];	 //������IP
 extern char G_ServerPort[5];	 //�������˿�
 extern char G_Ssid[16];		 //·����SSID
 extern char G_Psk[16];		 //·����PSK
 
 //uchar G_Chid;		   //ͨѶ�ŵ�
 extern char G_GateWay[16];	 //����
 extern char G_NetMask[16];	 //��������
 extern char G_Hostport[5];	 //�����˿ں�
 extern uint G_BackColor;		 //������ɫ
 extern uint G_FontColor;		 //ǰ����ɫ
 extern uint G_ThemeColor; 	 //������ɫ
 extern uint G_AutoSleep;		 //�Զ��ػ�ʱ��
 extern uint G_AutoElClose;	 //�����Զ��ر�ʱ��
 extern char G_KeySound;		 //�������Ƿ���
 
 extern uchar G_Changle; 	 //�ŵ�ѡ��
 extern uchar G_TransRate;	 //ͨѶ����
 
 extern uchar G_AddrIPLen;	 //ip��ַ����
 extern uchar G_SsidLen; 	 //SSID����
 extern uchar G_ServerIpLen; //������IP����
 extern uchar G_NetMaskLen;  //�������볤��
 extern uchar G_GateWayLen;  //���س���
 extern uchar G_PskLen; 	 //·�������볤��
 extern uchar G_ServerPortLen;//�������˿ڳ���
 extern uchar G_LocalSite;
 
 extern uchar G_PassWord[16];	   //��������
 extern uchar G_PassWordStatus;
 extern uchar G_PassWordLen;
 extern uchar G_WifiPowerTime;

 
 extern uchar Receive_Ip[16];//����ԭIP��˿�
 extern uchar Receive_Port[5];
 extern uchar ReceiveMaincode;//վ��
 extern u16 SerialReceiveLen;
 extern uchar Check_CardOk;
 
 
 //union	 sDatasUnion  xdata SerialUnion;
 //uchar	 SerialReceiveLen;
 
 
 extern uchar UID[4];
 

