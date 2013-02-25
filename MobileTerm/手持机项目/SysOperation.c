/****************************************************************************
*
*�ļ�(File):         SysOperation.c
*
*�޸�(Modify):       2011-10-28 9:01:19
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
| V1.00  2011-10-28 9:01:19           Rain 
----------------------------------------------------------------------------
****************************************************************************/

#include <API.h>
#include "MyDefine.c"
#include "ExternParameter.h"


extern void Wifi_SetDemo();
extern    void Wifi_GetDemo();
extern int WriteParameter(ushort Addr,uchar *Wrdate,char len);

static void SetTime();
static void SetDisp();
static void SetKeyBoard();
static void AutoPowerDown();
static void SetElAutoTime();
static void SetPassword();
static void SetLocalSite();
static void ResetPlant();

static void GetTime();
static void GetDisp();
static void GetAutoSleep();
static void GetAutoEl();
static void GetPasswordStatus();
static void GetLocalSite();
static long Inputime(char *str,int maxnum,int minvalue,int maxvalue);
static void SetPassWordStatus();
static void ChangePassWord();
static void OpenPassWord();
static void ClosePassWord();



int SetInputDate(char * str,char alpla,char * pstr,char pwchar,int maxnum,int minvalue,int maxvalue,long *val,int qx,int qy);
long Inputdate(char *str,char alpla,char *pstr,char pwchar,int maxnum,int minvalue,int maxvalue);
void WaringBeep(uchar Beep_count);
void WaringFdivBeep(uchar f_div,uchar Beep_count);


 void SetSysParameter()
 {
	 BROWINFO setpar_menu;
	 char parameter_str[]=" 1.ʱ������    "
					      " 2.��ʾ����    "
					 " 3.��������    "
					 " 4.�Զ��ػ�ʱ��"
					 " 5.����ʱ������"
					 " 6.������������"
					 " 7.WIFI��������"
					 " 8.WIFI�����ѯ"
					 " 9.����վ������"
					 " 10.�ָ���������";
	 
	 int select;
	 setpar_menu.iStr=parameter_str;//����ַ���
	 setpar_menu.lPtr = 0;//��ʼ��ʾ��
	 setpar_menu.cPtr = 0;//��ʼѡ����
	 while(1)
	 {
		DispStr_CE(0,1,"ϵͳ���ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		setpar_menu.mInt=10;//��ʾ������
		setpar_menu.lineMax=15;//ÿ����ʾ����ַ��� 
		setpar_menu.startLine=3;//��ʼ�� 
		setpar_menu.dispLines=10;//
		setpar_menu.sFont=0;  //0 -������
		setpar_menu.numEnable=1;//�Ƿ�������̷���� 1-����
		setpar_menu.qEvent=(EXIT_KEY_F1);
		setpar_menu.autoexit =120;
		select=EXT_Brow_Select(&setpar_menu);
		switch(select)
		{
			 case 0:
				 SetTime();
				 break;
			 case 1:
				 SetDisp();
				 break;
			 case 2:
				 SetKeyBoard();
				 break;
			 case 3:
				 AutoPowerDown();
				 break;
			 case 4:
				 SetElAutoTime();
				 break;
			 case 5:
				 SetPassword();
				 break;
			 case 6:
				 Wifi_SetDemo();
				 break;
			 case 7:
			 	Wifi_GetDemo();
				break;
			 case 8:
				 SetLocalSite();
				 break;
			 case 9:
				 ResetPlant();
				 break;
			 default:
				 return;
				 //break;
		 }
	 }
 }

 
 void GetSysParameter()
  {
	  BROWINFO getpar_menu;
	  char parameter_str[]=" 1.ʱ���ѯ    "
					       " 2.��ʾ��ѯ    "
					  " 3.�ػ�ʱ���ѯ"
					  " 4.����ʱ���ѯ"
					  " 5.����״̬��ѯ"
					  " 6.����վ���ѯ";
					  
	  
	  int select;
	  getpar_menu.iStr=parameter_str;//����ַ���
	  getpar_menu.lPtr = 0;//��ʼ��ʾ��
	  getpar_menu.cPtr = 0;//��ʼѡ����
	  while(1)
	  {
		 DispStr_CE(0,1,"��ѯϵͳ�˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		 getpar_menu.mInt=6;//��ʾ������
		 getpar_menu.lineMax=15;//ÿ����ʾ����ַ��� 
		 getpar_menu.startLine=3;//��ʼ�� 
		 getpar_menu.dispLines=6;//
		 getpar_menu.sFont=0;  //0 -������
		 getpar_menu.numEnable=1;//�Ƿ�������̷���� 1-����
		 getpar_menu.qEvent=(EXIT_KEY_F1);
		 getpar_menu.autoexit =120;
		 select=EXT_Brow_Select(&getpar_menu);
		 switch(select)
		 {
			  case 0:
				  GetTime();
				  break;
			  case 1:
				  GetDisp();
				  break;
			  case 2:
				  GetAutoSleep();
				  break;
			  case 3:
				  GetAutoEl();
				  break;
			  case 4:
				  GetPasswordStatus();
				  break;
			  case 5:
				  GetLocalSite();
				  break;
			  default:
				  return;
				  //break;
		  }
	  }
  }


static void GetLocalSite()
{
	char Local_str[20];
	sprintf(Local_str,"����վ���Ϊ:%d",G_LocalSite);
	DispStr_CE(0,12,Local_str,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_ALL,120);
	return;
}

static void SetLocalSite()
{
	char site_str[]=" ";
	char site_pstr[10];
	int ret;
	char tempstr[16];
	GETSTR_PARAM g_Site;
	g_Site.qx=100;//��ʾ���x����
     g_Site.qy=12;//��ʾ���y����
     g_Site.pPrompt=site_str;//��ʾ��仺������ָ��
     g_Site.sFont=0;//0��ʹ��7x9�Ĵ�����
     g_Site.alpha=0;//0��������������ĸ������
     g_Site.nullEnable=0;//0�������������밴Enter����
     g_Site.pStr=site_pstr;//����ʱ��ų�ʼĬ���ַ����������˳��Ǵ�ż�����ַ�����
     g_Site.csChar='_';//�����ʾ�ַ�
     g_Site.pwChar=0;//������ʾ�ַ���Ϊ0����Ч
     g_Site.minNum=0; //���ٽ��յ��ַ�����
     g_Site.spChar='.';//���ַָ���
     g_Site.maxNum=3;
     g_Site.minValue=-1;
     g_Site.maxValue=255;
     g_Site.retNum=strlen(site_pstr);
     g_Site.qEvent=EXIT_KEY_F1;
	 DispStr_CE(0,8,"�����뱾��վ���(0~255)",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
     if(GetStr_E(&g_Site))
     {
     	DispStr_CE(0,12,"ȡ������!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(ERR_WARNING_BEEP);
		return;
	 }
	ret=WriteParameter(E_LocalSiteAddr,(uchar*)&g_Site.retValue,1);
	if(!ret)
	{
		G_LocalSite=(uchar)g_Site.retValue;
		sprintf(tempstr,"����վ������ó�%d",G_LocalSite);
		DispStr_CE(0,12,tempstr,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(OK_WARNING_BEEP);
		
	}
	else
	{
		DispStr_CE(0,12,"����վ�������ʧ��!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(ERR_WARNING_BEEP);
	}
	return;
}




 static void AutoPowerDown()
{
	long set_date;
	char set_buf[16];
	 uchar temp;
	Disp_Clear();
	set_date=Inputdate("�������Զ��ػ�ʱ��(��) ",0,set_buf,0,3,-1,-1);
	
	if(set_date!=-1)
	{
	    temp=*((uchar*)&set_date+1);          
		WriteParameter(E_AutoSleepAddr,&temp,1);
		temp=*((uchar*)&set_date);
		WriteParameter(E_AutoSleepAddr+1,&temp,1);
		memset(set_buf,0x00,16);
		memset(set_buf,0x00,16);
		sprintf(set_buf,"�Զ��ػ�ʱ��Ϊ%d��",set_date);
		DispStr_CE(0,4,set_buf,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(OK_WARNING_BEEP);
		Sys_Auto_Poweroff_Set((ushort)temp);
	}
	else
	{
		DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		WaringBeep(ERR_WARNING_BEEP);
		delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
	}
	return ;
	
}
static void SetPassword()
{
	BROWINFO pass_menu;
	char pass_str[]=" 1.��������״̬"
					" 2.���Ŀ�������";
					
	
	int select;
    pass_menu.iStr=pass_str;//����ַ���
    pass_menu.lPtr = 0;//��ʼ��ʾ��
    pass_menu.cPtr = 0;//��ʼѡ����
	while(1)
	{
	   DispStr_CE(0,1,"�����������ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	   pass_menu.mInt=2;//��ʾ������
	   pass_menu.lineMax=15;//ÿ����ʾ����ַ��� 
	   pass_menu.startLine=3;//��ʼ�� 
	   pass_menu.dispLines=2;//
	   pass_menu.sFont=0;  //0 -������
	   pass_menu.numEnable=1;//�Ƿ�������̷���� 1-����
	   pass_menu.qEvent=(EXIT_KEY_F1);
	   pass_menu.autoexit =120;
	   select=EXT_Brow_Select(&pass_menu);
	   switch(select)
	   {
			case 0:
				SetPassWordStatus();//
				break;
			case 1:
				ChangePassWord();//
				break;
			default:
				return;
	
	   }
	}
	return ;
	
}
 

 


long Inputdate(char *str,char alpla,char *pstr,char pwchar,int maxnum,int minvalue,int maxvalue)
{

	GETSTR_PARAM g_time;
	g_time.qx=0;//��ʾ���x����
     g_time.qy=0;//��ʾ���y����
     g_time.pPrompt=str;//��ʾ��仺������ָ��
     g_time.sFont=0;//0��ʹ��7x9�Ĵ�����
     g_time.alpha=alpla;//0��������������ĸ������
     g_time.nullEnable=0;//0�������������밴Enter����
     g_time.pStr=pstr;//����ʱ��ų�ʼĬ���ַ����������˳��Ǵ�ż�����ַ�����
     g_time.csChar='_';//�����ʾ�ַ�
     g_time.pwChar=pwchar;//������ʾ�ַ���Ϊ0����Ч
     g_time.minNum=0; //���ٽ��յ��ַ�����
     g_time.spChar='.';//���ַָ���
     g_time.maxNum=maxnum;
     g_time.minValue=minvalue;
     g_time.maxValue=maxvalue;
     g_time.retNum=strlen(pstr);
     g_time.qEvent=EXIT_KEY_F1;
     if(!GetStr_E(&g_time))
     {
		return (g_time.retValue);
	 }
	 return -1;
}
int SetInputDate(char * str,char alpla,char * pstr,char pwchar,int maxnum,int minvalue,int maxvalue,long *val,int qx,int qy)
{

	GETSTR_PARAM g_time;
	g_time.qx=qx;//��ʾ���x����
     g_time.qy=qy;//��ʾ���y����
     g_time.pPrompt=str;//��ʾ��仺������ָ��
     g_time.sFont=0;//0��ʹ��7x9�Ĵ�����
     g_time.alpha=alpla;//0��������������ĸ������
     g_time.nullEnable=0;//0�������������밴Enter����
     g_time.pStr=pstr;//����ʱ��ų�ʼĬ���ַ����������˳��Ǵ�ż�����ַ�����
     g_time.csChar='_';//�����ʾ�ַ�
     g_time.pwChar=pwchar;//������ʾ�ַ���Ϊ0����Ч
     g_time.minNum=0; //���ٽ��յ��ַ�����
     g_time.spChar='.';//���ַָ���
     g_time.maxNum=maxnum;
     g_time.minValue=minvalue;
     g_time.maxValue=maxvalue;
     g_time.retNum=strlen(pstr);
     g_time.qEvent=EXIT_KEY_F1;
     if(!GetStr_E(&g_time))
     {
     	*val=g_time.retValue;
		return 0;
	 }
	 return -1;
}



void WaringBeep(uchar Beep_count)
{
	uchar i;
	for(i=0;i<Beep_count;i++)
	{
		Beep_Sound(BEEP_ON,8,50);
		Sys_Delay_MS(200);
		Beep_Sound(BEEP_OFF,8,50);
		Sys_Delay_MS(50);
	}
	return;
}
void WaringFdivBeep(uchar f_div,uchar Beep_count)
{
	uchar i;
	for(i=0;i<Beep_count;i++)
	{
		Beep_Sound(BEEP_ON,f_div,50);
		Sys_Delay_MS(200);
		Beep_Sound(BEEP_OFF,f_div,50);
		Sys_Delay_MS(50);
	}
	return;
}


static void SetPassWordStatus()
{
	BROWINFO passstatus_menu;
	char pass_str[]=" 1.������������"
					" 2.������ֹ����";
					
	
	int select;
    passstatus_menu.iStr=pass_str;//����ַ���
    passstatus_menu.lPtr = 0;//��ʼ��ʾ��
    passstatus_menu.cPtr = 0;//��ʼѡ����
	while(1)
	{
	   DispStr_CE(0,1,"��������״̬���ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	   passstatus_menu.mInt=2;//��ʾ������
	   passstatus_menu.lineMax=15;//ÿ����ʾ����ַ��� 
	   passstatus_menu.startLine=3;//��ʼ�� 
	   passstatus_menu.dispLines=2;//
	   passstatus_menu.sFont=0;  //0 -������
	   passstatus_menu.numEnable=1;//�Ƿ�������̷���� 1-����
	   passstatus_menu.qEvent=(EXIT_KEY_F1);
	   passstatus_menu.autoexit =120;
	   select=EXT_Brow_Select(&passstatus_menu);
	   switch(select)
	   {
			case 0:
				OpenPassWord();
				break;
			case 1:
				ClosePassWord();
				break;
			default:
				return;
				
	   }
	}
	return ;
}

void RunPassWord()
{
	char input_date[16];
	long templong=0;
restart:

	SetInputDate("�����뿪������: ",0,input_date,'*',8,-1,-1,&templong,10,8);
	if(!memcmp(G_PassWord,(uchar*)input_date,G_PassWordLen))
	{
		DispStr_CE(0,4,"����������ȷ ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (1,EXIT_KEY_F1,120);
		return;
	}
	else
	{	DispStr_CE(0,4,"�����������",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		DispStr_CE(0,10,"��������������!",DISP_CENTER|DISP_NORMAL);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		Disp_Clear();
		goto  restart;
	}
}


static void ChangePassWord()
{
	long rett;
	int ret;
	char set_buf[16];
	uchar passwordbuf;
	uchar OldPassWordBak[16];
	Disp_Clear();
	memset(set_buf,0x00,16);
	memset(OldPassWordBak,0x00,16);
	memcpy(OldPassWordBak,G_PassWord,strlen((char*)G_PassWord));
	rett=Inputdate("�����뿪��ԭ����  ",0,set_buf,1,8,-1,-1);
	if(rett!=-1)
	{
		
		if(!memcmp(G_PassWord,set_buf,G_PassWordLen))
		{
			memset(set_buf,0x00,16);
			Disp_Clear();
			rett=Inputdate("�����뿪�������� ",0,set_buf,1,8,-1,-1);
			if(rett!=-1)
			{
				ret=WriteParameter(E_PassWordAddr,(uchar*)set_buf,strlen(set_buf));
				if(!ret)
				{
					passwordbuf=strlen(set_buf);
					ret=WriteParameter(E_PassWordLenAddr,&passwordbuf,1);
					if(!ret)
					{
						DispStr_CE(0,4,"�������óɹ� ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
						memcpy(G_PassWord,set_buf,passwordbuf);
						G_PassWordLen=passwordbuf;
						delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
						WaringBeep(OK_WARNING_BEEP);
						return;
					}
					else
					{
						WriteParameter(E_PassWordAddr,OldPassWordBak,strlen((char*)OldPassWordBak));
						DispStr_CE(0,4,"����д��ʧ�� ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
						WaringBeep(ERR_WARNING_BEEP);
						delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
						return;
					}
				}
				else
				{
					DispStr_CE(0,4,"����д��ʧ�� ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					WaringBeep(ERR_WARNING_BEEP);	
					delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
					return;
				}
			}
			else
			{
				DispStr_CE(0,4,"��ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
				WaringBeep(ERR_WARNING_BEEP);
				delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
				return;
			}
		}
		else
		{
			DispStr_CE(0,4,"�������ԭ��������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(ERR_WARNING_BEEP);
			delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			return;
		}
	}
	else 
	{
		DispStr_CE(0,4,"��ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		WaringBeep(ERR_WARNING_BEEP);
		delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
	}
	return;
}
static void OpenPassWord()
{
	int ret;
	uchar status;
	status=1;
	ret=WriteParameter(E_PassWordStatusAddr,&status,1);
	if(!ret)
	{
		G_PassWordStatus=1;
		DispStr_CE(0,4,"���������ѿ���",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(OK_WARNING_BEEP);
	}
	return;
}
static void ClosePassWord()
{
	int ret;
	uchar status;
	status=0;
	ret=WriteParameter(E_PassWordStatusAddr,&status,1);
	if(!ret)
	{
		G_PassWordStatus=0;
		DispStr_CE(0,4,"���������ѽ�ֹ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(OK_WARNING_BEEP);
	}
	return;
}
static void SetElAutoTime()
{
	long set_date;
	char set_buf[16];
	uchar temp;
	Disp_Clear();
	set_date=Inputdate("�����뱳�����ʱ��(��) ",0,set_buf,0,2,-1,-1);
	
	if(set_date!=-1)
	{
	    temp=(uchar)set_date;          
		WriteParameter(E_AutoElCloseAddr,&temp,1);
		memset(set_buf,0x00,16);
		sprintf(set_buf,"�������ʱ��Ϊ%d��",set_date);
		DispStr_CE(0,4,set_buf,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(OK_WARNING_BEEP);
		EL_Set_Timeout((ushort)temp);
	}
	else
	{
		DispStr_CE(0,4,"ȡ������! ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		WaringBeep(ERR_WARNING_BEEP);
		delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
	}
	
	return ;
}


static void setThemecolor()
{
	char  str[]=" 1.������ɫΪ��ɫ  "
                " 2.������ɫΪ��ɫ  "
                " 3.������ɫΪ��ɫ  "
                " 4.������ɫΪ��ɫ  "
                " 5.������ɫΪ��ɫ  "
                " 6.�ֶ�����������  ";
     uint color;
     int ret;
	 long temp_buf;
	 char set_buf[16];
	 uchar colordate[2];
	 BROWINFO bi;
	 bi.lPtr = 0;
	 bi.cPtr = 0;
	 while(1)
	 {
     DispStr_CE(0,1,"������ɫ���ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
     bi.iStr=str;
	   bi.mInt=6;
	   bi.lineMax=19;//ÿ����ʾ����ַ��� 
	   bi.startLine=3;//��ʼ�� 
	   bi.dispLines=6;//
	   bi.sFont=0;
	   bi.numEnable=1;
	   bi.qEvent=(EXIT_KEY_F1); 
	   ret=EXT_Brow_Select(&bi);
      switch(ret)
       {
          case 0:
                color=0x001f;
               // Disp_Set_Color(SET_BACK_COLOR,color);
               break;
          case 1:
               color=0x0040;
               //Disp_Set_Color(SET_BACK_COLOR,color);
               break;
          case 2:
               color=0xffe0;
              // Disp_Set_Color(SET_BACK_COLOR,color);
               break;
          case 3:
               color=0xf800;
               break;
          case 4:
               color=0xffff;
               break; 
		  case 5:
		  		Disp_Clear();
		  		temp_buf=Inputdate("����������16λ��ɫֵ:",0,set_buf,0,5,-1,65535);
				if(temp_buf!=-1)
				{
					color=(uint)temp_buf;
				}
			  	else
			  	{
					DispStr_CE(0,4,"��ȡ������ɫ����!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					WaringBeep(ERR_WARNING_BEEP);
					delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
					return;
				}
			    break;
          default :
		  	   DispStr_CE(0,4,"��ȡ������!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			   WaringBeep(ERR_WARNING_BEEP);
			   delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
			   return; //���� 
               break;            
       }
	  colordate[0]=*((char *)&color+1);
	  colordate[1]=*((char *)&color);
	  ret=WriteParameter(E_ThemeColorAddr,colordate,2);
	  if(!ret)
	  {
	  	DispStr_CE(0,4,"������ɫ���óɹ� ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (1,EXIT_KEY_F1,120);
		Disp_Set_Color(SET_SELECT_COLOR,color);
		//DispStr_CE(0,4,"�ػ���������Ч!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		//delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(OK_WARNING_BEEP);
	  }
      return ;
    }   
}

 static void setclearcolor()
{
    char  str[]=" 1.ǰ�����ó���ɫ  "
               " 2.ǰ�����ó���ɫ  "
               " 3.ǰ�����óɻ�ɫ  "
               " 4.ǰ�����óɺ�ɫ  "
               " 5.ǰ�����óɰ�ɫ  "
               " 6.�ֶ�����ǰ����ɫ";
     uint color;
     int ret;
	 long temp_buf;
	 char set_buf[16];
	 uchar colordate[2];
	 BROWINFO bi;
	 bi.lPtr = 0;
	 bi.cPtr = 0;
	 while(1)
	 {
     DispStr_CE(0,1,"ǰ����ɫ���ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
     bi.iStr=str;
	   bi.mInt=6;
	   bi.lineMax=19;//ÿ����ʾ����ַ��� 
	   bi.startLine=3;//��ʼ�� 
	   bi.dispLines=6;//
	   bi.sFont=0;
	   bi.numEnable=1;
	   bi.qEvent=(EXIT_KEY_F1); 
	   ret=EXT_Brow_Select(&bi);
      switch(ret)
       {
          case 0:
                color=0x001f;
               // Disp_Set_Color(SET_BACK_COLOR,color);
               break;
          case 1:
               color=0x0040;
               //Disp_Set_Color(SET_BACK_COLOR,color);
               break;
          case 2:
               color=0xffe0;
              // Disp_Set_Color(SET_BACK_COLOR,color);
               break;
          case 3:
               color=0xf800;
               break;
          case 4:
               color=0xffff;
               break; 
		  case 5:
		  		Disp_Clear();
		  		temp_buf=Inputdate("������ǰ��16λ��ɫֵ:",0,set_buf,0,5,-1,65535);
				if(temp_buf!=-1)
				{
					color=(uint)temp_buf;
				}
			  	else
			  	{
					DispStr_CE(0,4,"��ȡ��ǰ����ɫ����!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					WaringBeep(ERR_WARNING_BEEP);
					delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
					return;
				}
			    break;
          default :
		  	   DispStr_CE(0,4,"��ȡ������!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			   WaringBeep(ERR_WARNING_BEEP);
			   delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
			   return; //���� 
               break;            
       }
	  colordate[0]=*((char *)&color+1);
	  colordate[1]=*((char *)&color);
	  ret=WriteParameter(E_FontColorAddr,colordate,2);
	  if(!ret)
	  {
	  	DispStr_CE(0,4,"ǰ����ɫ���óɹ� ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (1,EXIT_KEY_F1,120);
		DispStr_CE(0,4,"�ػ���������Ч!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(OK_WARNING_BEEP);
	  }
      return ;
    }    
} 


static void setbackcolor()
{
   char  str[]=" 1.�������ó���ɫ  "
               " 2.�������ó���ɫ  "
               " 3.�������óɻ�ɫ  "
               " 4.�������óɺ�ɫ  "
               " 5.�������óɰ�ɫ  "
               " 6.�ֶ����ñ�����ɫ";
     uint color;
     int ret;
	 long temp_buf;
	 char set_buf[16]; 
	 uchar colordate[2];
	 BROWINFO bi;
	 bi.lPtr = 0;
	 bi.cPtr = 0;
	 while(1)
	 {
     DispStr_CE(0,1,"������ɫ���ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
     bi.iStr=str;

	   bi.mInt=6;
	   bi.lineMax=19;//ÿ����ʾ����ַ��� 
	   bi.startLine=3;//��ʼ�� 
	   bi.dispLines=6;//
	   bi.sFont=0;
	   bi.numEnable=1;
	   bi.qEvent=(EXIT_KEY_F1); 
	   ret=EXT_Brow_Select(&bi);
      switch(ret)
       {
          case 0:
                color=0x001f;
               // Disp_Set_Color(SET_BACK_COLOR,color);
               break;
          case 1:
               color=0x0400;
               //Disp_Set_Color(SET_BACK_COLOR,color);
               break;
          case 2:
               color=0xffe0;
              // Disp_Set_Color(SET_BACK_COLOR,color);
               break;
          case 3:
               color=0xf800;
               break;
          case 4:
               color=0xffff;
               break; 
		  case 5:
		  		Disp_Clear();
		  		temp_buf=Inputdate("�����뱳��16λ��ɫֵ:",0,set_buf,0,5,-1,65535);
				if(temp_buf!=-1)
				{
					color=(uint)temp_buf;
				}
			  	else
			  	{
					DispStr_CE(0,4,"��ȡ��������ɫ����!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
					WaringBeep(ERR_WARNING_BEEP);
					delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
					return;
				}
			
		  		break;
          default :
		  	   DispStr_CE(0,4,"ȡ������!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			   WaringBeep(ERR_WARNING_BEEP);
			   delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
               return; //����             
       }
	  colordate[0]=*((char *)&color+1);
	  colordate[1]=*((char *)&color);
	  ret=WriteParameter(E_BackColorAddr,colordate,2);
	  if(!ret)
	  {
	  	DispStr_CE(0,4,"������ɫ���óɹ� ",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (1,EXIT_KEY_F1,120);
		DispStr_CE(0,4,"�ػ���������Ч!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(OK_WARNING_BEEP);
	  }
      return ;
    }   
         
}


static void SetTime()
{
	char str1[]="��������:";
	char str2[]="�������·�:";
	char str3[]="����������:";
	char str4[]="������ʱ:";
	char str5[]="�������:";
	char str6[]="��������:";
	char str7[]="�����������"; 
	char str8[]="ȡ������!"; 
	char timedatestr[32];
	Disp_Clear();
	typ_DATE_TIME  s_time;//��ʾʱ��
	typ_DATE_TIME  i_time;//����ʱ��
	RTC_Get_DateTime(&s_time);
	sprintf(timedatestr,"��ǰʱ��: %d-%d-%d %d:%d:%d",s_time.year,s_time.month,s_time.day,s_time.hour,s_time.min,s_time.sec);
	DispStr_CE(0,8,timedatestr,DISP_CENTER|DISP_CLRSCR);//��ʾ���õ�ʱ��
	i_time.year=(uint)Inputime(str1,4,2000,2099);//��
	Disp_Clear() ;
	if(i_time.year==255)
	goto escset;
	sprintf(timedatestr,"��ǰʱ��: %d-%d-%d %d:%d:%d",i_time.year,s_time.month,s_time.day,s_time.hour,s_time.min,s_time.sec);
	DispStr_CE(0,8,timedatestr,DISP_CENTER|DISP_CLRSCR);//��ʾ���õ�ʱ��
	i_time.month=(uchar)Inputime(str2,2,1,12);//
	Disp_Clear() ;
	if(i_time.month==255)
   goto escset;
	sprintf(timedatestr,"��ǰʱ��: %d-%d-%d %d:%d:%d",i_time.year,i_time.month,s_time.day,s_time.hour,s_time.min,s_time.sec);
	DispStr_CE(0,8,timedatestr,DISP_CENTER|DISP_CLRSCR);//��ʾ���õ�ʱ��
	i_time.day=(uchar)Inputime(str3,2,1,31);
	Disp_Clear() ;
	if(i_time.day==255)
   goto escset;
	sprintf(timedatestr,"��ǰʱ��: %d-%d-%d %d:%d:%d",i_time.year,i_time.month,i_time.day,s_time.hour,s_time.min,s_time.sec);
	DispStr_CE(0,8,timedatestr,DISP_CENTER|DISP_CLRSCR);//��ʾ���õ�ʱ��
	i_time.hour=(uchar)Inputime(str4,2,0,23);
	Disp_Clear() ;
	if(i_time.hour==255)
   goto escset;
	sprintf(timedatestr,"��ǰʱ��: %d-%d-%d %d:%d:%d",i_time.year,i_time.month,i_time.day,i_time.hour,s_time.min,s_time.sec);
	DispStr_CE(0,8,timedatestr,DISP_CENTER|DISP_CLRSCR);//��ʾ���õ�ʱ��
	i_time.min=(uchar)Inputime(str5,2,0,59);
	Disp_Clear() ;
	if(i_time.min==255)
   goto escset;
	sprintf(timedatestr,"��ǰʱ��: %d-%d-%d %d:%d:%d",i_time.year,i_time.month,i_time.day,i_time.hour,i_time.min,s_time.sec);
	DispStr_CE(0,8,timedatestr,DISP_CENTER|DISP_CLRSCR);//��ʾ���õ�ʱ��
	i_time.sec=(uchar)Inputime(str6,2,0,59);
	i_time.week=(uchar)RTC_get_week((int)i_time.year,(int)i_time.month,(int)i_time.day);
	
	  Disp_Clear() ;
	  if(i_time.sec==255)
	 goto escset;
	RTC_Set_DateTime(&i_time);
	  DispStr_CE(0,8,str7,DISP_CENTER|DISP_CLRSCR);
	  delay_and_wait_key(DISP_OK_DELAY_TIME, EXIT_KEY_F1,120 ); 
	  WaringBeep(OK_WARNING_BEEP);
	return;
escset:
	DispStr_CE(0,8,str8,DISP_CENTER|DISP_CLRSCR);
	WaringBeep(ERR_WARNING_BEEP);
	delay_and_wait_key(DISP_ESC_DELAY_TIME, EXIT_KEY_F1,120 );
	return ;
}


static void SetDisp()
{
   char str[]=" 1.������ɫ����"
			  " 2.ǰ����ɫ����"
			  " 3.������ɫ����";
	int select;
	BROWINFO bi;
	bi.lPtr = 0;
	bi.cPtr = 0;
	bi.iStr = str;
	while(1)
	{
	   DispStr_CE(0,1,"��ʾ���ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	   bi.mInt=3;//��ʾ������
	   bi.lineMax=15;//ÿ����ʾ����ַ��� 
	   bi.startLine=3;//��ʼ�� 
	   bi.dispLines=3;//
	   bi.sFont=0;	//0 -������
	   bi.numEnable=1;//�Ƿ�������̷���� 1-����
	   bi.qEvent=(EXIT_KEY_F1);
	   bi.autoexit =120;
		 
	   select=EXT_Brow_Select(&bi);
	   switch(select)
	   {
		  case 0:
			   setbackcolor();
			   break;
		  case 1:
			   setclearcolor();
			   break;
		  case 2:
			   setThemecolor();
			   break;
		  default :
			   return;
	   }
	 }
}

static void SetKeyBoard()
{
	char str[]=" 1.����������"
			  " 2.�������ر�";
	int select;
	uchar DateBuf;
	BROWINFO bi;
	bi.lPtr = 0;
	bi.cPtr = 0;
	bi.iStr = str;
	while(1)
	{
	   DispStr_CE(0,1,"���������ò˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	   bi.mInt=2;//��ʾ������
	   bi.lineMax=13;//ÿ����ʾ����ַ��� 
	   bi.startLine=3;//��ʼ�� 
	   bi.dispLines=2;//
	   bi.sFont=0;	//0 -������
	   bi.numEnable=1;//�Ƿ�������̷���� 1-����
	   bi.qEvent=(EXIT_KEY_F1);
	   bi.autoexit =120;
		 
	   select=EXT_Brow_Select(&bi);
	   switch(select)
	   {
		  case 0:
				DateBuf=1;
			   G_KeySound=1;
			   KEY_Init(KEY_BEEP_KEY|KEY_AUTO_EL_ON);
			   WriteParameter(E_KeySondAddr,&DateBuf,1);
			   DispStr_CE(0,4,"�������ѿ���",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			   delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			   WaringBeep(OK_WARNING_BEEP);
			   break;
		  case 1:
			   DateBuf=0;
			   G_KeySound=0;
			   KEY_Init(KEY_AUTO_EL_ON);
			   WriteParameter(E_KeySondAddr,&DateBuf,1);
			   DispStr_CE(0,4,"�������ѹر�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			   delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
			   WaringBeep(OK_WARNING_BEEP);
			   break;
		  default :
			   return;
	   }
	 }
}



static void GetTime()
{
	char time_str[32];
	char week_str[]="����һ"
					"���ڶ�"
					"������"
					"������"
					"������"
					"������"
					"������";
	
	char g_weekstr[7];
	typ_DATE_TIME  g_time;
	memset(g_weekstr,0x00,7);
	DispStr_CE(0,10,"����ʱ��:",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	RTC_Get_DateTime(&g_time);
	memcpy(g_weekstr,week_str+(g_time.week-1)*6,6);
	DispStr_CE(0,22,g_weekstr,DISP_CENTER|DISP_NORMAL|DISP_CLRLINE);
	while(1)
	{
		RTC_Get_DateTime(&g_time);
		//memset(time_str,0x00,20);
		sprintf(time_str,"   %d-%d-%d  %02d:%02d:%02d   ",g_time.year,g_time.month,g_time.day,g_time.hour,g_time.min,g_time.sec);
		DispStr_CE(0,16,time_str,DISP_CENTER|DISP_NORMAL);
		
		if(KEY_Read()==KEY_F1)
		{
				return ;
		}
	}
}
static void GetDisp()
{

}

static void GetAutoSleep()
{
	ushort auto_time;
	char auto_time_str[32];
    auto_time=Sys_Auto_Poweroff_Read();
	sprintf(auto_time_str,"ϵͳ�Զ��ػ�ʱ��Ϊ%d��",auto_time);
	DispStr_CE(0,12,auto_time_str,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_ALL,120);
	return;
}
static void GetAutoEl()
{
	ushort EL_time;
	char EL_time_str[32];
	EL_time=EL_Get_Timeout();
	memset(EL_time_str,0x00,32);
	sprintf(EL_time_str,"�������ʱ��Ϊ%d��",EL_time);
	DispStr_CE(0,12,EL_time_str,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_ALL,120);
	return;
}
static void GetPasswordStatus()
{
	if(G_PassWordStatus)
	{
		DispStr_CE(0,16,"��������״̬Ϊ����",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	else
	{
		DispStr_CE(0,16,"��������״̬Ϊ�ر�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_ALL,120);
	return;
}


static long Inputime(char *str,int maxnum,int minvalue,int maxvalue)
{

	GETSTR_PARAM g_time;
	g_time.qx=0;
     g_time.qy=0;
     g_time.pPrompt=str;
     g_time.sFont=0;
     g_time.alpha=0;
     g_time.nullEnable=0;
     g_time.pStr="0";
     g_time.csChar='_';
     g_time.pwChar=0;
     g_time.minNum=0;
     g_time.maxNum=maxnum;
     g_time.minValue=minvalue;
     g_time.maxValue=maxvalue;
     g_time.retNum=2;
     g_time.qEvent=EXIT_KEY_F1;
     if(!GetStr_E(&g_time))
     {
		return (g_time.retValue);
	 }
	 return 255;
}


static void ResetPlant()
{
	uchar tempstruchar[16];
	uchar tempuchar;
	int ret;
	int tempret;
	typ_DATE_TIME  time;
	DispStr_CE(0,8,"ȷ��Ҫ�ָ�����������?",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	Sys_Delay_MS(300);
	DispStr_CE(0,12,"ȷ���밴�س�  ȡ���밴F1",DISP_CENTER|DISP_NORMAL);
	Sys_Delay_MS(300);
	DispStr_CE(0,16,"(ע��:�ָ��������ú�",DISP_CENTER|DISP_NORMAL);
	DispStr_CE(0,18,"�������ݽ���ʧ!)",DISP_CENTER|DISP_NORMAL);
	while(1)
	{
		if(KEY_Read()==KEY_F1)
		{
			DispStr_CE(0,12,"��ȡ���ָ���������!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
			WaringBeep(ERR_WARNING_BEEP);
			delay_and_wait_key (DISP_ESC_DELAY_TIME,EXIT_KEY_F1,120);
			return;
		}
		if(KEY_Read()==KEY_ENTER)
		{
			break;
		}
	}	
/****************************************************/
	memset(tempstruchar,0x00,16); 
	ret=WriteParameter(E_FontColorAddr,tempstruchar,2);//ǰ����ɫΪ��ɫ
	memset(tempstruchar,0xff,2);
	ret|=WriteParameter(E_BackColorAddr,tempstruchar,2);//������ɫΪ��ɫ
	tempstruchar[0]=0x04;
	tempstruchar[1]=0x00;
	ret|=WriteParameter(E_ThemeColorAddr,tempstruchar,2);
/*****************************************************/
	tempuchar=0;
	ret|=WriteParameter(E_LocalSiteAddr,&tempuchar,1);
/*****************************************************/
	time.year=2000;
	time.month=1;
	time.day=1;
	time.hour=0;
	time.min=0;
	time.sec=0;
	time.week=(uchar)RTC_get_week(2000,1,1);
	RTC_Set_DateTime(&time);
/******************************************************/
	tempuchar=0;
	ret|=WriteParameter(E_AutoSleepAddr,&tempuchar,1);
	tempuchar=60;
	Sys_Auto_Poweroff_Set((ushort)tempuchar);
	ret|=WriteParameter(E_AutoSleepAddr+1,&tempuchar,1);
/******************************************************/
	tempuchar=10;
	EL_Set_Timeout((ushort)tempuchar);
	ret|=WriteParameter(E_AutoElCloseAddr,&tempuchar,1);
/******************************************************/
	tempuchar=0;
	tempret=WriteParameter(E_PassWordStatusAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_PassWordStatus=tempuchar;
	}
/******************************************************/ 
	tempuchar=3;
	tempret=WriteParameter(E_PassWordLenAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)

	{
		G_PassWordLen=tempuchar;
	}
/******************************************************/
	memcpy(tempstruchar,"123",3);
	tempret=WriteParameter(E_PassWordAddr,tempstruchar,3);
	ret|=tempret;
	if(!tempret)
	{
		memcpy(G_PassWord,tempstruchar,3);
	}
/******************************************************/
	memcpy(tempstruchar,"521",3);
	tempuchar=3;
	tempret=WriteParameter(E_SsidAddr,tempstruchar,3);
	ret|=tempret;
	if(!tempret)
	{
		memcpy(G_Ssid,tempstruchar,3);
	}
	tempret=WriteParameter(E_SsidLenAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_SsidLen=3;
	}
/*****************************************************/
	memcpy(tempstruchar,"12345678",8);
	tempuchar=8;
	tempret=WriteParameter(E_PskAddr,tempstruchar,8);
	ret|=tempret;
	if(!tempret)
	{
		memcpy(G_Psk,tempstruchar,8);
	}
	tempret=WriteParameter(E_PskLenAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_PskLen=8;
	}
/******************************************************/
	tempuchar=0;
	tempret=WriteParameter(E_ChidAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_Changle=0;
	}
/******************************************************/
	tempuchar=13;
	tempret=WriteParameter(E_TransRateAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_TransRate=13;
	}
/******************************************************/
	memcpy(tempstruchar,"192.168.1.125",13);
	tempuchar=13;
	tempret=WriteParameter(E_IpAddr,tempstruchar,13);
	ret|=tempret;
	if(!tempret)
	{
		memcpy(G_AddrIP,tempstruchar,13);
	}
	tempret=WriteParameter(E_IpLenAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_AddrIPLen=13;
	}
/******************************************************/
	memcpy(tempstruchar,"192.168.1.1",11);
	tempuchar=11;
	tempret=WriteParameter(E_GateWayAddr,tempstruchar,11);
	ret|=tempret;
	if(!tempret)
	{
		memcpy(G_GateWay,tempstruchar,11);
	}
	tempret=WriteParameter(E_GateWayLenAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_GateWayLen=11;
	}
/******************************************************/
	memcpy(tempstruchar,"255.255.255.0",13);
	tempuchar=13;
	tempret=WriteParameter(E_NetMaskAddr,tempstruchar,13);
	ret|=tempret;
	if(!tempret)
	{
		memcpy(G_NetMask,tempstruchar,13);
	}
	tempret=WriteParameter(E_NetMaskLenAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_NetMaskLen=13;
	}
/******************************************************/
	memcpy(tempstruchar,"192.168.1.100",13);
	tempuchar=13;
	tempret=WriteParameter(E_ServerIpAddr,tempstruchar,13);
	ret|=tempret;
	if(!tempret)
	{
		memcpy(G_ServerIp,tempstruchar,13);
	}
	tempret=WriteParameter(E_ServerIpLenAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_ServerIpLen=13;
	}
/******************************************************/
	memcpy(tempstruchar,"9000",4);
	tempuchar=4;
	tempret=WriteParameter(E_ServerPortAddr,tempstruchar,4);
	ret|=tempret;
	if(!tempret)
	{
		memcpy(G_ServerPort,tempstruchar,4);
	}
	tempret=WriteParameter(E_ServerPortLenAddr,&tempuchar,1);
	ret|=tempret;
	if(!tempret)
	{
		G_ServerPortLen=4;
	}
	if(ret)
	{
		DispStr_CE(0,10,"�ָ���������ʱ���ִ���",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		WaringBeep(ERR_WARNING_BEEP);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
	}
	else
	{
		DispStr_CE(0,10,"�ָ��������óɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (DISP_OK_DELAY_TIME,EXIT_KEY_F1,120);
		WaringBeep(OK_WARNING_BEEP);
	}
	return ;
/*****************************************************/
}


