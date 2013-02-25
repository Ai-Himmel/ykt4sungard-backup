/****************************************************************************
*
*�ļ�(File):         WiFi.c
*
*�޸�(Modify):       2011-10-28 8:59:04
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
| V1.00  2011-10-28 8:59:04           Rain 
----------------------------------------------------------------------------
****************************************************************************/

#include <API.h>
#include "MyDefine.c" 
#include "WiFi/WiFi.h"
#include "WiFi/NaNoWiFiConst.h"
#include "WiFi/WiFiPubFuncs.h"
#include <unistd.h>
#include "ExternParameter.h" 


extern uint	Cal_CRC_Sub(uchar * Datas, uint nBytes) ;
extern void WaringFdivBeep(uchar f_div,uchar Beep_count);
extern void WaringBeep(uchar Beep_count);
extern long Inputdate(char *str,char alpla,char *pstr,char pwchar,int maxnum,int minvalue,int maxvalue);
extern int WriteParameter(ushort Addr,uchar *Wrdate,char len);
extern int SetInputDate(char * str,char alpla,char * pstr,char pwchar,int maxnum,int minvalue,int maxvalue,long *val,int qx,int qy);
static void Wifi_GetSoftwareVer();

static int Wifi_OpenModel(char bbit);
static int Wifi_InitModel(char bbit);//��ʼ��ģ��
static int Wifi_SetPowerModel(char bbit,uchar WaitInterval,uchar ScanCyc,uint NoConScanTime);//��Դ��������
static int Wifi_SetChangle(char bbit,uchar ChID);//ͨ���ŵ�����
static int Wifi_SetTransRate(char bbit,uchar TransRate);//ͨѶ��������
static int Wifi_SetSsid(char bbit,char *SSID);//·����SSID����
static int Wifi_SetPsk(char bbit,char *PSK);//PSK��������
static int Wifi_SetIp(char bbit,char *IP);//IP��ַ����
static void Wifi_GetIp();//��ȡIP��ַ
static int Wifi_SetGateway(char bbit,char *GateWay);//��������
static void Wifi_GetGateway();//�������
static int Wifi_SetNetMask(char bbit,char *NetMask);//������������
static void Wifi_GetNetMask();//��ȡ��������
static void Wifi_GetNicMac();//��ȡMAC��ַ
int Wifi_Connect(char bbit,u16 *Handle,char *HostIpAddr,char *HostPort,char ConnectType);//�׽�������
int Wifi_GetSocketStatus(char bbit,uint HandleID);//�鿴�׽�������״̬;
static int Wifi_CloseSocket(char bbit,uint HandleID);//�Ͽ��׽�������
static int Wifi_CloseModel(char bbit);//�ر�ģ��
static void Wifi_SetParameter();
static void Wifi_GetServer();


int Open_WifiModel();
int UdpReceiceDateDiag();
int Wifi_WriteDate(char bbit,u16 HandleID);
int Wifi_ReadDate(char bbit,u16 HandleID);



void Wifi_SetDemo()
{
	   char set_str[]= " 1.��ģ��  "
					   " 2.��ʼ��ģ��"
					   " 3.��������  "
					   " 4.���Ͳ���  "
					   " 5.��������  "
					   " 6.���ܲ���  "
					   " 7.�Ͽ�����  "
					   " 8.�ر�ģ��  ";
	   int select;
	   BROWINFO set_menu;
	   set_menu.iStr=set_str;//����ַ���
	   set_menu.lPtr = 0;//��ʼ��ʾ��
	   set_menu.cPtr = 0;//��ʼѡ����
	   while(1)
	   {
		  DispStr_CE(0,1,"ϵͳ���ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		  set_menu.mInt=8;//��ʾ������
		  set_menu.lineMax=13;//ÿ����ʾ����ַ��� 
		  set_menu.startLine=3;//��ʼ�� 
		  set_menu.dispLines=8;//��ʾ������
		  set_menu.sFont=0;  //0 -������
		  set_menu.numEnable=1;//�Ƿ�������̷���� 1-����
		  set_menu.qEvent=(EXIT_KEY_F1);
		  set_menu.autoexit =120;
		  select=EXT_Brow_Select(&set_menu);
		  switch(select)
		  {
			   case 0:
				   Wifi_OpenModel(1);//��ģ��
				   Wifi_SetPowerModel(0,0,2,120);//���õ�Դ����ģ��
				   break;
			   case 1:
				   Wifi_InitModel(1);//��ʼ��ģ��
				   break;
			   case 2:
				   Wifi_Connect(1,&G_HandleID,G_ServerIp,G_ServerPort,1);//�����׽���
				   break;
			   case 3:
				   Wifi_WriteDate(1,G_HandleID);
				   break;
			   case 4:
				   Wifi_SetParameter();//���ò���
				   break;
			   case 5:
			   		Wifi_ReadDate(1,G_HandleID);
				   break;
			   case 6:
				   Wifi_CloseSocket(1,G_HandleID);//�ο�����
				   break;
			   case 7:
				   Wifi_CloseModel(1);//�ر�ģ��
				   break;
			   default:
				   return;
				   //break;
		  }
	   }
	   return ;
}
   
   


   void Wifi_GetDemo()
  {
	  char get_str[]=" 1.��ȡIP��ַ  "
					 " 2.��ȡ����    "
					 " 3.��ȡ��������"
					 " 4.��ȡMAC��ַ "
					 " 5.�鿴����״̬"
					 " 6.��ȡ������  "
					 " 7.��ȡ����汾";
	  int select;
	  BROWINFO get_menu;
	  get_menu.iStr=get_str;//����ַ���
	  get_menu.lPtr = 0;//��ʼ��ʾ��
	  get_menu.cPtr = 0;//��ʼѡ����
	  while(1)
	  {
		 DispStr_CE(0,1,"WIFI�����ѯ�˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR); 
		 get_menu.mInt=7;//��ʾ������
		 get_menu.lineMax=15;//ÿ����ʾ����ַ��� 
		 get_menu.startLine=3;//��ʼ�� 
		 get_menu.dispLines=7;//��ʾ������
		 get_menu.sFont=0;	//0 -������
		 get_menu.numEnable=1;//�Ƿ�������̷���� 1-����
		 get_menu.qEvent=(EXIT_KEY_F1);
		 get_menu.autoexit =120;
		 select=EXT_Brow_Select(&get_menu);
		 switch(select)
		 {
			  case 0:
				  Wifi_GetIp();
				  break;
			  case 1:
				  Wifi_GetGateway();
				  break;
			  case 2:
				  Wifi_GetNetMask();
				  break;
			  case 3:
				  Wifi_GetNicMac();
				  break;
			  case 4:
				  Wifi_GetSocketStatus(1,G_HandleID);
				  break;
			  case 5:
				  Wifi_GetServer();
				  break;
			  case 6:
				  Wifi_GetSoftwareVer();
				  break;
			  default :
				  return;
		 }
	  }
	  
	 return ;			
  }
 static void Wifi_GetServer()
  {
	  u32  pHostPort[1]  = {0};
	  char pHostAddr[20] = {0x00};
	  char dispstr[16];
	  char dis_pstr1[16];
	  if(WiFi_OK == CWiFi_GetHostInfo(G_HandleID,pHostAddr,pHostPort))
	  {
		  memset(dis_pstr1,0x00,16);
		  sprintf(dis_pstr1,"�������˿ں�:%d ",pHostPort[0]);
		  DispStr_CE(0,6,dis_pstr1,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		  memset(dispstr,0x00,16);
		  sprintf(dispstr,"��������ַ:%s",pHostAddr);
		  DispStr_CE(0,4,dispstr,DISP_CENTER|DISP_NORMAL);
		  
	  }
	  else 
	  {
		  DispStr_CE(0,4,"��ȡʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	  }
	  delay_and_wait_key(DISP_OK_DELAY_TIME,EXIT_KEY_F1,120); 
  }
  
  

  static void Wifi_GetSoftwareVer()
  {
	  char pVerNum[16];
	  char pVerTime[16];
	  int ret;
	  memset(pVerNum,0x00,16);
	  ret=CWiFi_GetSoftwareVer(pVerNum,pVerTime);
	  if(!ret)
	  {
		  DispStr_CE(0,14,"VER ",DISP_CENTER|DISP_CLRSCR);//��ʾ���õ�ʱ��
		  DispStr_CE(50,14,pVerNum,DISP_CENTER);//��ʾ���õ�ʱ��
		  DispStr_CE(0,16,pVerTime,DISP_CENTER);//��ʾ���õ�ʱ��
	  }
	  else
	  {
		  DispStr_CE(0,14,"��ȡ����汾ʧ��!",DISP_CENTER|DISP_CLRSCR);//��ʾ���õ�ʱ��
	  }
	  delay_and_wait_key(DISP_OK_DELAY_TIME, EXIT_KEY_F1,120 );
	  return;
  }
  


  static int Wifi_OpenModel(char bbit)
  {
	  int ret;
	  ret=CWiFi_OpenMould();
	  if(bbit)
	  {
		  if(!ret)
		  {
			  //Disp_Clear();
			  DispStr_CE(0,4,"WIFI�򿪳ɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFI��ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
			  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
		  }
		  
	  }
	  return ret;
  }
  

  static int Wifi_InitModel(char bbit)
  {
	  int ret;
	  ret=CWiFi_InitModule(0,0);
	  if(bbit)
	  {
		  if(!ret)
		  {
			  DispStr_CE(0,4,"WIFI��ʼ���ɹ� ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFI��ʼ��ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
			  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
		  }
		  
	  }
	  return ret;
  }
  


  static int Wifi_SetPowerModel(char bbit,uchar WaitInterval,uchar ScanCyc,uint NoConScanTime)
  {
	  int ret;
	  ret=CWiFi_SetPowerMode(WaitInterval,ScanCyc,NoConScanTime);
	  if(bbit)
	  {
		  if(!ret)
		  {
			 DispStr_CE(0,4,"WIFI��Դ�������óɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		  }
		  else
		  {
			 DispStr_CE(0,4,"WIFI��Դ��������ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		  }
		  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	  }
	  return ret;
  }
	 

  static int Wifi_SetChangle(char bbit,uchar ChID)
  {
	  int ret;
	  char str[20];
	  sprintf(str,"WIFIͨ���ŵ�����%d",ChID);
	  ret=CWiFi_SetWiFiChanle( ChID);
	  if(bbit)
	  {
		  if(!ret)
		  {
			  DispStr_CE(0,4,str,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFIͨ���ŵ�����ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
		  }
		  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	  }
	  return ret;
  }

  static int Wifi_SetTransRate(char bbit,uchar TransRate)
  {
	  int ret;
	  char str[20];
	  sprintf(str,"WIFIͨ����������%d",TransRate);
	  ret=CWiFi_SetWiFiTransRate(TransRate);
	  if(bbit)
	  {
		  if(!ret)
		  {
			  DispStr_CE(0,4,str,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFIͨ����������ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
		  }
		  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	  }
	  return ret;
  }

  static int Wifi_SetSsid(char bbit,char *SSID)
  {
	  int ret;
	  
	  ret=CWiFi_SetRouteSSID(SSID);
	  if(bbit)
	  {
		  if(!ret)
		  {
			  DispStr_CE(0,4,"WIFI SSID���óɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFI SSID����ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
		  }
		  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	  }
	  return ret;
  }  //

  static int Wifi_SetPsk(char bbit,char *PSK)
  {
	  int ret;
	  ret=CWiFi_SetRoutePSK(PSK);
	  if(bbit)
	  {
		  if(!ret)
		  {
			  DispStr_CE(0,4,"WIFI PSK���óɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFI PSK����ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
		  }
		  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	  }
	  return ret;
  }


  static int Wifi_SetIp(char bbit,char *IP)
  {
	  int ret;
	  ret=CWiFi_SetLocalAddress(IP);
	  if(bbit)
	  {
		  if(!ret)
		  {
			  DispStr_CE(0,4,"WIFI IP���óɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFI IP����ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
		  }
		  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	  }
	  return ret;
  }
  



  static void Wifi_SetParameter()
  {
	  char parameter_str[]= " 1.SSID����     "
							" 2.PSK����      "
							" 3.ͨѶ�ŵ����� "
							" 4.ͨѶ�������� "
							" 5.IP��ַ����   "
							" 6.��������     "
							" 7.������������ "
							" 8.���÷�����IP "
							" 9.���ö˿�     "
							"10.ģ���Դ���� ";
	  int select;
	  char set_buf[16];
	  int ret;
	  long rett;
	  uchar setval;
	  BROWINFO parameter_menu;
	  memset(set_buf,0x00,16);
	  parameter_menu.iStr=parameter_str;//����ַ���
	  parameter_menu.lPtr = 0;//��ʼ��ʾ��
	  parameter_menu.cPtr = 0;//��ʼѡ����
	  while(1)
	  {
		 DispStr_CE(0,1,"WIFI�������ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		 parameter_menu.mInt=10;//��ʾ������
		 parameter_menu.lineMax=16;//ÿ����ʾ����ַ��� 
		 parameter_menu.startLine=3;//��ʼ�� 
		 parameter_menu.dispLines=10;//��ʾ������
		 parameter_menu.sFont=0;  //0 -������
		 parameter_menu.numEnable=1;//�Ƿ�������̷���� 1-����
		 parameter_menu.qEvent=(EXIT_KEY_F1);
		 parameter_menu.autoexit =120;
		 select=EXT_Brow_Select(&parameter_menu);
		 switch(select)
		 {
			  case 0:
				   Disp_Clear();
				  rett=Inputdate("������SSID  ",1,set_buf,0,-1,-1,-1);
				  if(rett!=-1)
				  {
					  ret=Wifi_SetSsid(1,set_buf);
					  if(!ret)
					  {
						  memcpy(G_Ssid,set_buf,strlen(set_buf));
						  WriteParameter(E_SsidAddr,(uchar*)set_buf,strlen(set_buf));
						  setval=strlen(set_buf);
						  WriteParameter(E_SsidLenAddr,&setval,1);//����ssid�ַ�������
						  WaringBeep(OK_WARNING_BEEP);
					  //  EEPROM_Write_Byte(E_SsidAddr+strlen(set_buf),&ss);
					  }
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }
				  break;
			  case 1:
				   Disp_Clear();
				  rett=Inputdate("����������  ",1,set_buf,0,-1,-1,-1);
				  if(rett!=-1)
				  {
					  ret=Wifi_SetPsk(1,set_buf);
					  if(!ret)
					  {
						  memcpy(G_Psk,set_buf,strlen(set_buf));
						  WriteParameter(E_PskAddr,(uchar*)set_buf,strlen(set_buf));
						  setval=strlen(set_buf);
						  WriteParameter(E_PskLenAddr,&setval,1);
						  WaringBeep(OK_WARNING_BEEP);
					  }
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }
				  break;
			  case 2:
				   Disp_Clear();
				  rett=Inputdate("�������ŵ�  ",0,set_buf,0,-1,-1,-1);
				  if(rett!=-1)
				  {
					  ret=Wifi_SetChangle(1,(uchar)rett);
					  if(!ret)
					  {
						  G_Changle=setval;
						  WriteParameter(E_ChidAddr,&setval,1);
						  WaringBeep(OK_WARNING_BEEP);
					  }
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }
				  break;
			  case 3:
				   Disp_Clear();
				  rett=Inputdate("����������  ",0,set_buf,0,-1,-1,-1);
				  if(rett!=-1)
				  {
					  ret=Wifi_SetTransRate(1,(uchar)rett);
					  if(!ret)
					  {
						  G_TransRate=setval;
						  WriteParameter(E_TransRateAddr,&setval,1);
						  WaringBeep(OK_WARNING_BEEP);
					  }
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }
				  break;
			  case 4:
				   Disp_Clear();
				  rett=Inputdate("������IP  ",0,set_buf,0,-1,-1,-1);
				  if(rett!=-1)
				  {
					  ret=Wifi_SetIp(1,set_buf);
					  if(!ret)
					  {
						  memcpy(G_AddrIP,set_buf,strlen(set_buf));
						  WriteParameter(E_IpAddr,(uchar*)set_buf,strlen(set_buf));
						  setval=strlen(set_buf);
						  WriteParameter(E_IpLenAddr,&setval,1);
						  WaringBeep(OK_WARNING_BEEP);
					  }
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }
				  break;
			  case 5:
				   Disp_Clear();
				  rett=Inputdate("����������  ",0,set_buf,0,-1,-1,-1);
				  if(rett!=-1)
				  {
					  ret=Wifi_SetGateway(1,set_buf);
					  if(!ret)
					  {
						  memcpy(G_GateWay,set_buf,strlen(set_buf));
						  WriteParameter(E_GateWayAddr,(uchar*)set_buf,strlen(set_buf));
						  setval=strlen(set_buf);
						  WriteParameter(E_GateWayLenAddr,&setval,1);
						  WaringBeep(OK_WARNING_BEEP);
					  }
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }
				  break;
			  case 6:
				   Disp_Clear();
				  rett=Inputdate("����������  ",0,set_buf,0,-1,-1,-1);
				  if(rett!=-1)
				  {
					  ret=Wifi_SetNetMask(1,set_buf);
					  if(!ret)
					  {
						  memcpy(G_NetMask,set_buf,strlen(set_buf));
						  WriteParameter(E_NetMaskAddr,(uchar*)set_buf,strlen(set_buf));
						  setval=strlen(set_buf);
						  WriteParameter(E_NetMaskLenAddr,&setval,1);
						  WaringBeep(OK_WARNING_BEEP);
					  }
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }
				  break;
			  case 7:
				  Disp_Clear();
				  rett=Inputdate("�����������IP ",0,set_buf,0,-1,-1,-1);
				  if(rett!=-1)
				  {
					  memcpy(G_ServerIp,set_buf,strlen(set_buf));//���÷�����IP��ַ
					  WriteParameter(E_ServerIpAddr,(uchar*)G_ServerIp,strlen(G_ServerIp));
					  setval=strlen(set_buf);
					  WriteParameter(E_ServerIpLenAddr,&setval,1);
					  WaringBeep(OK_WARNING_BEEP);
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }
				  break;
			  case 8:
				  Disp_Clear();
				  rett=Inputdate("������������˿�  ",0,set_buf,0,-1,-1,-1);
				  if(rett!=-1)
				  {
					  memcpy(G_ServerPort,set_buf,strlen(set_buf));//���÷�����IP��ַ
					  WriteParameter(E_ServerPortAddr,(uchar*)G_ServerPort,strlen(G_ServerPort));
					  setval=strlen(set_buf) ;
					  WriteParameter(E_ServerPortLenAddr,&setval,1);  
					  WaringBeep(OK_WARNING_BEEP);
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }
				  break;
			case 9:
				 Disp_Clear();
				 DispStr_CE(0,8,"������ģ���������ʱ��(0~255)",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
				 ret=SetInputDate(" ",0,set_buf,0,-1,-1,-1,&rett,120,12);
				  if(!ret)
				  {
					 ret=Wifi_SetPowerModel(1,(uchar)rett,2,120);
					 if(!ret)
					 {
						WriteParameter(E_WifiPowerModleAddr,(uchar *)&rett,1);
					 }
				  }
				  else
				  {
					  DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					  WaringBeep(ERR_WARNING_BEEP);
					  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				  }	
				break;
			  default :
				  return; 
		 }
	  }
	  return;
  }
  


  static int Wifi_SetGateway(char bbit,char *GateWay)
  {
	  int ret;
	  ret=CWiFi_SetGatewayAddress(GateWay);
	  if(bbit)
	  {
		  if(!ret)
		  {
			  DispStr_CE(0,4,"WIFI �������óɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFI ��������ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
		  }
		  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	  }
	  return ret;
  }


  static int Wifi_SetNetMask(char bbit,char *NetMask)
  {
	  int ret;
	  ret=CWiFi_SetLocalNetMask(NetMask);
	  if(bbit)
	  {
		  if(!ret)
		  {
			  DispStr_CE(0,4,"WIFI �����������óɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFI ������������ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
		  }
		  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	  }
	  return ret;
  }
  


 int Wifi_Connect(char bbit,u16 *Handle,char *HostIpAddr,char *HostPort,char ConnectType)
  {
	  int ret;
	  ret=CWiFi_Connect(Handle,HostIpAddr,HostPort,ConnectType);
	  if(bbit)
	  {
		  if(!ret)
		  {
			  DispStr_CE(0,4,"WIFI �׽������ӳɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			  WaringBeep(OK_WARNING_BEEP);
		  }
		  else
		  {
			  DispStr_CE(0,4,"WIFI �׽�������ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			  WaringBeep(ERR_WARNING_BEEP);
			  delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
		  }
		  
	  }
	  return ret;
  }


  static int Wifi_CloseSocket(char bbit,uint HandleID)
{
	int ret;
	ret=CWiFi_Disconnect(HandleID);
	if(bbit)
	{
		if(!ret)
		{
			DispStr_CE(0,4,"WIFI �׽��ֹرճɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			WaringBeep(OK_WARNING_BEEP);
		}
		else
		{
			DispStr_CE(0,4,"WIFI �׽��ֹر�ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(ERR_WARNING_BEEP);
			delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
		}
		
	}
	return ret;
}

static int Wifi_CloseModel(char bbit)
{
	int ret;
	ret=CWiFi_CloseMould();
	if(bbit)
	{
		if(!ret)
		{
			DispStr_CE(0,4,"WIFI ģ��ճɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			WaringBeep(OK_WARNING_BEEP);
		}
		else
		{
			DispStr_CE(0,4,"WIFI ģ��ر�ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(ERR_WARNING_BEEP);
			delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
		}
		
	}
	return ret;
}

static void Wifi_GetIp()
{
	int ret;
	char GetIP[16];
	memset(GetIP,0x00,16);
	ret=CWiFi_GetLocalAddress(GetIP);
	if(!ret)
	{
		DispStr_CE(0,4,"WIFI IP��ȡ�ɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		DispStr_CE(0,6,GetIP,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	else
	{
		DispStr_CE(0,4,"WIFI IP��ȡʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	delay_and_wait_key (DISP_CHECK_DELAY_TIME,EXIT_KEY_ALL,120);
	
}


static void Wifi_GetGateway()
{
	int ret;
	char Getway[16];
	memset(Getway,0x00,16);
	ret=CWiFi_GetGatewayAddress(Getway);
	if(!ret)
	{
		
		DispStr_CE(0,4,"WIFI ���ػ�ȡ�ɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		DispStr_CE(0,6,Getway,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	else
	{
		DispStr_CE(0,4,"WIFI ���ػ�ȡʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	delay_and_wait_key (DISP_CHECK_DELAY_TIME,EXIT_KEY_ALL,120);
}



static void Wifi_GetNetMask()
{
	int ret;
	char NetMask[16];
	memset(NetMask,0x00,16);
	ret=CWiFi_GetLocalNetMask(NetMask);
	if(!ret)
	{
		DispStr_CE(0,4,"WIFI ���������ȡ�ɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		DispStr_CE(0,6,NetMask,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	else
	{
		DispStr_CE(0,4,"WIFI ���������ȡʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	delay_and_wait_key (DISP_CHECK_DELAY_TIME,EXIT_KEY_ALL,120);
}




static void Wifi_GetNicMac()
{
	int ret;
	char NicMac[16];
	char Disp_buf[17];
	memset(NicMac,0x00,16);
	ret=CWiFi_GetNicMac(NicMac);
	if(!ret)
	{
		memset(Disp_buf,0x00,17);
		sprintf(Disp_buf,"%c%c %c%c %c%c ",NicMac[0],NicMac[1],NicMac[2],NicMac[3],NicMac[4],NicMac[5]);
		sprintf(Disp_buf+9,"%c%c %c%c %c%c",NicMac[6],NicMac[7],NicMac[8],NicMac[9],NicMac[10],NicMac[11]);
		DispStr_CE(0,4,"WIFI MAC��ַ��ȡ�ɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		DispStr_CE(0,6,Disp_buf,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		//delay_and_wait_key (DISP_CHECK_DELAY_TIME,EXIT_KEY_ALL,120);
	}
	else
	{
		DispStr_CE(0,4,"WIFI MAC��ַ��ȡʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	delay_and_wait_key (DISP_CHECK_DELAY_TIME,EXIT_KEY_ALL,120);
}


 int Wifi_GetSocketStatus(char bbit,uint HandleID)//�鿴�׽�������״̬
{
	int ret;
	ret=CWiFi_GetSocketStatus(HandleID);
	if(bbit)
	{
		if(!ret)
		{
			DispStr_CE(0,4,"WIFI �׽�����������",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		}
		else
		{
			DispStr_CE(0,4,"WIFI �׽�����������",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		}
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	}
	return ret;
}



unsigned long WiFi_MsgDisplay(char *WiFiMsg,
                              u16   WiFiMsgID,
                              u8    WiFiMsgType)
{
    memset(RBackInfo,0x00,32);
    sprintf(&RBackInfo[0], " MID:%d,TID:%d,%s\n", WiFiMsgID,WiFiMsgType,WiFiMsg);
    sprintf(&RBackInfo[0], "%s",WiFiMsg);
    return 0;
}

int Wifi_WriteDate(char bbit,u16 HandleID)
{
	int ret;
	char Pbuf[]="��ð�" ;
	Pbuf[0]=0x25;
	Pbuf[1]=0x35;
	
	ret=CWiFi_Write(HandleID,Pbuf,8);
	if(bbit)
	{
		if(!ret)
		{
			DispStr_CE(0,4,"���ͳɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			WaringBeep(OK_WARNING_BEEP);
		}
		else
		{
			DispStr_CE(0,4,"����ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(ERR_WARNING_BEEP);
			delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
		}
		
	}
	return ret;
}


int Wifi_ReadDate(char bbit,u16 HandleID)
{
	int ret;
	char Receive_Buf[20];
	u16 Len;
	ret=CWiFi_Read(HandleID,Receive_Buf,&Len);
	if(bbit)
	{
		if(!ret)
		{
			DispStr_CE(0,4,"���ճɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(ERR_WARNING_BEEP);
			delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
		
		}
		else
		{
			DispStr_CE(0,4,"����ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(ERR_WARNING_BEEP);
			delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
		}
		
	}
	return ret;
}
int Open_WifiModel()
{
	int ret;
	DispStr_CE(0,4,"ϵͳ���ڳ�ʼ��...",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	DispStr_CE(0,8,"���Ժ�...",DISP_CENTER|DISP_NORMAL);
	ret=Wifi_InitModel(DISP_STATUS_INF);//��ʼ��ģ��
	if(ret)
	{
		goto end;
	}
	ret=Wifi_OpenModel(DISP_STATUS_INF); //��ģ�� 
	if(ret)
	{
		goto end;
	}
	
	ret=Wifi_SetPowerModel(DISP_STATUS_INF,G_WifiPowerTime,2,120);//���õ�Դ����
	if(ret)
	{
		goto end;	
	}
	ret=Wifi_SetChangle(DISP_STATUS_INF,G_Changle);//�����ŵ�
	if(ret)
	{
		goto end;
	}
	ret=Wifi_SetTransRate(DISP_STATUS_INF,G_TransRate);//����ͨѶ����
	if(ret)
	{
		goto end;
	}
	ret=Wifi_SetSsid(DISP_STATUS_INF,G_Ssid);//����SSID
	if(ret)
	{
		goto end;
	}
	ret=Wifi_SetPsk(DISP_STATUS_INF,G_Psk);
	if(ret)
	{
		goto end;
	}
	ret=Wifi_SetIp(DISP_STATUS_INF,G_AddrIP);//���ñ���IP;
	if(ret)
	{
		goto end;
	}
	ret=Wifi_SetGateway(DISP_STATUS_INF,G_GateWay);
	if(ret)
	{
		goto end;
	}
	ret=Wifi_SetNetMask(DISP_STATUS_INF,G_NetMask);
	if(ret)
	{
		goto end;
	}
	ret=Wifi_Connect(DISP_STATUS_INF,&G_HandleID,G_ServerIp,G_ServerPort,1);//��������
	if(ret)
	{
		goto end;
	}
	DispStr_CE(0,14,"ϵͳ��ʼ���ɹ�...",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	WaringBeep(1);
	delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	return 0;
end:
	DispStr_CE(0,14,"WIFI���������ж�!!!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	DispStr_CE(0,18,"���ֶ���������...",DISP_CENTER|DISP_NORMAL);
	WaringBeep(3);
	delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	return -1;
}


void UdpSendDate()
{
	uchar DateBuf[16];
	char SendBuf[60];
	uchar i,j;
	uint CRC_Buf;
	uchar temp;
	uchar CRC_Temp;
	int ret;
	char st_data;
	uchar read_count=0;
	uchar write_count=0;
	memset(DateBuf,0x00,16);
	DateBuf[0]=0;
	DateBuf[1]=G_LocalSite;
	DateBuf[2]=0;
	DateBuf[3]=0;
	DateBuf[4]=CZ_COMMAND_WORD_H;
	DateBuf[5]=CZ_COMMAND_WORD_L;
	DateBuf[6]=0;
	DateBuf[7]=0;
	DateBuf[8]=0;
	DateBuf[9]=1;
	DateBuf[10]=0x04;//���͵����ݳ��� 4�ֽ�
	memcpy(DateBuf+11,UID,4);
	
	SendBuf[0]=STX;//STX
	j=1;
	for(i=0;i<15;i++)
	{
		st_data=DateBuf[i];
		temp=(st_data>>4)&0x0f;
		if(temp>9)
			SendBuf[j++]=temp+0x37;
		else
			SendBuf[j++]=temp+0x30;

		temp=st_data&0x0f;
		if(temp>9)
			SendBuf[j++]=temp+0x37;
		else
			SendBuf[j++]=temp+0x30;
	}
	SendBuf[j++]=ETX;//ETX
	CRC_Buf=Cal_CRC_Sub((uchar*)&DateBuf,i);
	CRC_Temp=(*((uchar*)&CRC_Buf+1)>>4)&0x0f;
	if(CRC_Temp>9)
	SendBuf[j++]=0x37+CRC_Temp;
	else
	SendBuf[j++]=0x30+CRC_Temp;
	CRC_Temp=*((uchar*)&CRC_Buf+1)&0x0f;
	if(CRC_Temp>9)
	SendBuf[j++]=0x37+CRC_Temp;
	else
	SendBuf[j++]=0x30+CRC_Temp;
	
	CRC_Temp=(*((uchar*)&CRC_Buf)>>4)&0x0f;
	if(CRC_Temp>9)
	SendBuf[j++]=0x37+CRC_Temp;
	else
	SendBuf[j++]=0x30+CRC_Temp;
	CRC_Temp=*((uchar*)&CRC_Buf)&0x0f;
	if(CRC_Temp>9)
	SendBuf[j++]=0x37+CRC_Temp;
	else
	SendBuf[j++]=0x30+CRC_Temp;		
WRITE_START:
	ret=CWiFi_Write(G_HandleID,SendBuf,11*2+2+4+8+1);
	if(!ret)
	{
READD_START:
		ret=UdpReceiceDateDiag();
		if(ret==CRC_CHECK_ERR)
		{
			write_count++;
			if(read_count==4)
			{
			write_count=0;
			DispStr_CE(0,14,"CRCУ��ʧ�ܣ�������ˢ��!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(3);
			delay_and_wait_key (2,EXIT_KEY_F1,120);
			}
			else
			{
				goto WRITE_START;
			}
		}
		else if(ret==UID_CHECK_ERR)
		{
			DispStr_CE(0,14,"����У��ʧ�ܣ�������ˢ��!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(3);
			delay_and_wait_key (2,EXIT_KEY_F1,120);	
		}
		else if(ret==CARD_CHECK_ERR)
		{
			DispStr_CE(0,14,"�˿����Ϸ�!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(3);
			delay_and_wait_key (2,EXIT_KEY_F1,120);
		}
		else if(ret==RECEIVE_DATE_ERR)
		{
			DispStr_CE(0,14,"��������ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(3);
			delay_and_wait_key (2,EXIT_KEY_F1,120);
		}
		else if(ret==SITE_CHECK_ERR)
		{
			DispStr_CE(0,14,"վ���У��ʧ�ܣ�������ˢ��!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(3);
			delay_and_wait_key (2,EXIT_KEY_F1,120);
		}
		else if(ret==RECEIVE_DATE_OK)
		{
			DispStr_CE(0,14,"�Ϸ���",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		}
		if(ret==READ_NET_ERR)
		{
			write_count++;
			if(write_count==3)
			{
				DispStr_CE(0,14,"�����������Ӵ���!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
				WaringBeep(3);
				delay_and_wait_key (2,EXIT_KEY_F1,120);
				return ;
			}
			else
			{
				goto WRITE_START;
			}
			
		}
		if(ret==0xff)
		{
			read_count++;
			if(read_count==4)
			{
			DispStr_CE(0,14,"����ʧ��!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(3);
			delay_and_wait_key (2,EXIT_KEY_F1,120);
			}
			else
			{
				goto READD_START;
			}
		}
	}
	else
	{
		ret=Wifi_Connect(0,&G_HandleID,G_ServerIp,G_ServerPort,1);
		if(ret)
		{
			DispStr_CE(0,12,"�������Ӵ���!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			DispStr_CE(0,16,"������������...",DISP_CENTER|DISP_NORMAL);
			WaringBeep(3);
			delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			return;
		}
		goto WRITE_START;	
	}
	
}


int UdpReceiceDateDiag()
{
	int ret;
	u16 Len;

	uint i;
	uchar st_data;
	uchar ReceiveLen=0;
	char Receive_Buf[256];
	uint CRC_Temp;
	uchar SerialReCase=0;
	uchar bitEven=0;
	uchar rChar=0;
	uchar j=0;
	uchar UID_Buf[4];
	uint SerialReCheckSum;
	uchar SerialReCheckSumCount=1;
	uchar bitSerial_ReceiveEnd=0;
	uchar Site_TempH=0;
	uchar Site_TempL=0;
	uchar PacketLen=0;
	uchar UIDLen=0;
	char Disp_str[20];
	uchar CheckCardBuf=0;
	uchar StringLen=0;
	uchar Read_CMDH=0;
	uchar Read_CMDL=0;
	memset(Disp_str,0x00,20);
	ret=CWiFi_Read(G_HandleID,Receive_Buf,&Len);
	if(ret==MEM_OVER)
	{
		DispStr_CE(0,14,"�������",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		WaringBeep(3);
		delay_and_wait_key (2,EXIT_KEY_F1,120);
	}
	if(ret)
	{
		return READ_NET_ERR;
	}
	for(i=0;i<Len;i++)
	{
		st_data=Receive_Buf[i];
		if(!SerialReCase)
		{
			if(st_data==STX)
			{
				bitEven=0;
				SerialReCase=1;
			}
		}
		else if(SerialReCase==1)
		{
			
			if (st_data<0x3a && st_data>0x2f)
				j=st_data-0x30;
			else if (st_data>0x40 && st_data<0x47)
				j=st_data-0x37;
			else if (st_data==ETX)
			{
				SerialReCase=2;
				bitEven=0;
			}
			else
			{
				return	0xff;
			}
			if (SerialReCase==1)
			{
				if (!bitEven)
				{
					rChar=j<<4;
					bitEven=1;
				}
				else
				{
					bitEven=0;
					rChar+=j;
					Receive_Buf[ReceiveLen++]=rChar;
					
					if(ReceiveLen==3)
					{
						Site_TempH=rChar;
					}
					if(ReceiveLen==4)
					{
						Site_TempL=rChar;
						
					}
					if(ReceiveLen==5)
					{
						Read_CMDH=rChar;
					}
					if(ReceiveLen==6)
					{
						Read_CMDL=rChar;
					}
					if(ReceiveLen==11)
					{
						PacketLen=rChar;
					}
					if((11<ReceiveLen)&&(ReceiveLen<16))
					{
						UID_Buf[UIDLen++]=rChar;
					}
					if(ReceiveLen==16)
					{
						CheckCardBuf=rChar;
					}
					
					if(ReceiveLen>16)
					{
						Disp_str[StringLen++]=rChar;
					}
					
				}
			}		
		}
		else if(SerialReCase==2)
		{
			if((st_data>0x2f)&&(st_data<0x3a))
			{
				j=st_data-0x30;
			}
			else if((st_data<0x47)&&(st_data>0x40))
			{
				j=st_data-0x37;
			}
			else
			{
				return	0xff;
			}		
			if (!bitEven)
			{
				rChar=j<<4;
				bitEven=1;
			}
			else
			{
				bitEven=0;
				rChar+=j;
				* (SerialReCheckSumCount+(uchar *)&SerialReCheckSum)=rChar;	
				if (SerialReCheckSumCount==0)
				{//CRCУ��ͱȽ�
					bitSerial_ReceiveEnd=1;
					break;
				}				 
				SerialReCheckSumCount--;	
			}
		}
	
	}
	if((Read_CMDH!=CZ_COMMAND_WORD_H)||(Read_CMDL!=CZ_COMMAND_WORD_L))
	{
		return 0xff;
	}
	if(!bitSerial_ReceiveEnd)
	{
		return RECEIVE_DATE_ERR;
	}
	if(CheckCardBuf!=0xaa)
	{
		return CARD_CHECK_ERR;
	}
	if((UID_Buf[0]!=UID[0])||(UID_Buf[1]!=UID[1])||(UID_Buf[2]!=UID[2])||(UID_Buf[3]!=UID[3]))
	{
		return UID_CHECK_ERR;
	}
	if(Site_TempL!=G_LocalSite)
	{
		return SITE_CHECK_ERR;
	}
	CRC_Temp=Cal_CRC_Sub((uchar*)Receive_Buf,PacketLen+11);
	if((*((uchar*)&CRC_Temp)!=*((uchar*)&SerialReCheckSum))||(*((uchar*)&CRC_Temp+1)!=*((uchar*)&SerialReCheckSum+1)))
	{
		return CRC_CHECK_ERR;	
	}
	DispStr_CE(0,12,Disp_str,DISP_CENTER|DISP_NORMAL);
	WaringFdivBeep(8,1);
	delay_and_wait_key (2,EXIT_KEY_F1,120);
	return RECEIVE_DATE_OK;
}





