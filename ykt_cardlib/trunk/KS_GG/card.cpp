//
//卡操作模块
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "serial.h"

unsigned char Rsnr[5];          			//M1卡系列号
unsigned char readKey[32];      			 //验证密钥
char M1CardType;
int CheckSID=99;	//当前验密区号，每次验密前比对，如果当前已经对需验密扇区验密则省去验密过程
//有效块标志

/*int readcard(unsigned char *buf2,unsigned char *buf3)
{
	char	buffer[3];
	int	rc;
	unsigned char *p;
	unsigned char *q;
	p=buf2;
	q=buf3;
	
	//closenet();
restart:
   memset(buffer,0x20,sizeof(buffer));
   while(1){
	   rc=ser->RecvCom(2,buffer,1,2);
      if (rc<0){ //opennet(); 
      	return(0);}
      if(buffer[0]==0x1b) break;
   }
restart1:
	rc=ser->RecvCom(2,buffer,1,1);
   if (rc<0){ //opennet(); 
   	return(0);}
   if(buffer[0]==0x1b) goto restart1;
   if(buffer[0]!=0x73) goto restart;
	while(buffer[0]!=0x41){
		rc=ser->RecvCom(2,buffer,1,1);
      if(rc<0){ //opennet();
      	 return(0);}
		*p=buffer[0];
		p++;
	}
	p--;
	*p=0;
	while(buffer[0]!=0x3f){
		rc=ser->RecvCom(2,buffer,1,1);
      if(rc<0){ //opennet(); 
      	return(0); 
      	}
		*q=buffer[0];
		q++;
   }
	rc=ser->RecvCom(2,buffer,1,1);
   if((rc<0)||(buffer[0]!=0x1c)){ //opennet();
   	return(0);}
	q--;
	*q=0;
	//opennet();
	return(1);
}*/

//M1卡,CPU卡，SAM卡操作

/***********************************************************
珠海亿达crc8校验函数
parastr组成：首字节为参与crc长度，后面是内容。例：0x12+"123456789012"
*************************************************************/
char Wd_Crc8(  char *parastr)
{
    char recvstr[80],in_temp,m_temp1,m_temp2;
    char s_temp1,s_temp2,fix_m,crc8;
	short int m[9],n[9];
	int i,j,numm;
	     m[0]=0xff;
	     m[1]=0xfe;
		 m[2]=0xfd;
		 m[3]=0xfb;
		 m[4]=0xf7;
		 m[5]=0xef;
		 m[6]=0xdf;
		 m[7]=0xbf;
		 m[8]=0x7f;

	     n[0]=0x00;
	     n[1]=0x01;
		 n[2]=0x02;
		 n[3]=0x04;
		 n[4]=0x08;
		 n[5]=0x10;
		 n[6]=0x20;
		 n[7]=0x40;
		 n[8]=0x80;

	crc8=0;
	numm=*parastr;
	for (i=0;i<numm;i++)
		recvstr[i]=*(parastr+i+1);

	for (i=0;i<numm;i++)
	  { in_temp=recvstr[i];
		for (j=1;j<=8;j++)
		 { m_temp1=in_temp&n[j];		    // filter the BIT
		   m_temp1=m_temp1<<(8-j);			//the BIT to MSB
											// like ?0000000
		   m_temp2=crc8&n[1];
		   m_temp2=m_temp2<<7;				//?0000000
		   m_temp1=m_temp1^m_temp2;

		   fix_m=m_temp1;

		   // change crc8 BIT 5
		   m_temp1=fix_m;
		   m_temp2=m_temp1>>3;     
		   m_temp2=m_temp2&n[5];			//m.. 000?0000
		   s_temp1=crc8|m[5];				//s.. 111?1111
		   s_temp1=s_temp1^m_temp2;			//s.. 111?1111
		   s_temp2=crc8|n[5];				//s.. ???1????
		   crc8=s_temp1&s_temp2;			//s.. ????????

		   // change crc8 BIT 4
		   m_temp1=fix_m;
		   m_temp2=m_temp1>>4;     
		   m_temp2=m_temp2&n[4];			//m.. 0000?000
		   s_temp1=crc8|m[4];				//s.. 1111?111
		   s_temp1=s_temp1^m_temp2;			//s.. 1111?111
		   s_temp2=crc8|n[4];				//s.. ????1???
		   crc8=s_temp1&s_temp2;			//s.. ????????

		   //Begin right shift 1 bit
		   s_temp2=crc8>>1;
		   s_temp1=s_temp2&m[8];			//s.. 0???????
		   crc8=fix_m|s_temp1;				//s.. ????????
		};
		crc8=~crc8;
	};
	return crc8;
}

/**********************************
函数功能：赋值月到索引字段
双月(month)赋值到bb的低四位，单月赋值到高四位
返回赋值后的bb
当bb中已经包含该月，则返回值等于bb可以检测出是否已经购买该月月票
************************************/
char Put_month( int month,char bb )
{
    int i;    
    char a,b;
                   
    i=month%2;
    if( i == 0 ){
    	a = bb&0xf0;
    	a = a+month;
    }
    else{
    	a = bb&0x0f;
    	b = month;
    	b = b << 4;
    	a = a + b;
    }
    return a;          
}


// ASC扩展
//
void  Hex2Asc(unsigned char *sin, int len,   char *sout)
{
  int i;
  for( i=0; i<len; i++ )
     sprintf( sout+2*i, "%02X",sin[i] );
}

//IC卡座选择 (flag==1 >sam卡座;其他>IC卡座)
int select_Ic(CSerial *ser,int flag)
{
      unsigned char sBuff[64],tmpbuf[12];
    	int  i=0,rc;
    	unsigned char ch;
      unsigned long	t0,t1;

      //7E 49 30 31 ICC_NO(2 BYTES) LRC
    	memset(sBuff , 0 , sizeof( sBuff ) );
      if(flag==1){
        memcpy(sBuff , "\x7E\x49\x30\x31\x33\x31",6);
      }
      else if(flag==2){
      	memcpy(sBuff , "\x7E\x49\x30\x31\x33\x32",6);
      }
      else{
        memcpy(sBuff , "\x7E\x49\x30\x31\x33\x30",6);
      }
    	for(i =0;i<6;i++)
      sBuff[6]= sBuff[6] ^ sBuff[i];


//      while(getcom(port)>0);
    	ser->SendCom((char *)sBuff,7,3);

       ch=0x34;
      t0=GetTickCount();
	   while(1){
         rc=ser->RecvCom((char *)&ch,1,1);
		   if(rc==0){
		 	  if(ch==0x7E) 		break;
		   }
			t1=GetTickCount();
			if((t1-t0)<=5000) continue;
         goto opend;
      }
      memset(tmpbuf,0,sizeof(tmpbuf));
      if(ser->RecvCom((char *)tmpbuf,3,10)<0)  goto opend;

      if ( tmpbuf[0]!=0x30 ) goto opend;
      return 0;
opend:

      return -1;
}

//IC卡上电
int poweron_Ic(CSerial *ser)
{
      unsigned char sBuff[64],tmpbuf[12];
    	int  i=0,rc;
    	unsigned char ch;
      unsigned long	t0,t1;

    	memset(sBuff , 0 , sizeof( sBuff ) );
      memcpy(sBuff , "\x7E\x51\x30\x31\x30\x30",6);
    	for(i =0;i<6;i++)
      sBuff[6]= sBuff[6] ^ sBuff[i];

   //   while(getcom(port)>0);
    	ser->SendCom((char *)sBuff,7,3);


      t0=GetTickCount();
	   while(1){
         rc=ser->RecvCom((char *)&ch,1,1);
		   if(rc==0){
		 	  if(ch==0x7E) 		break;
		   }
			t1=GetTickCount();
			if((t1-t0)<=3000) continue;
         goto opend;
      }
      memset(tmpbuf,0,sizeof(tmpbuf));
      if(ser->RecvCom((char *)tmpbuf,1,3)<0)  goto opend;

      if ( tmpbuf[0]!=0x30 ) goto opend;
      return 0;
opend:

      return -1;
}

/*****************
CPU卡操作
*****************/
//IC初始化
int init_Ic(CSerial *ser){
    int st,i;

    st=select_Ic(ser,0);
    if(st<0) return (-1);

    for( i=0;i<3;i++ ){
  		st=poweron_Ic(ser);
  		if( st>=0 )	break;
    }
    if(st<0) return -1;
    return (0);
}

//IC卡下电
int powerdown_Ic(CSerial *ser)
{
      unsigned char sBuff[64],tmpbuf[12];
    	int  i=0,rc;
    	unsigned char ch;
      unsigned long	t0,t1;

    	memset(sBuff , 0 , sizeof( sBuff ) );
      memcpy(sBuff , "\x7e\x5a\x30\x30",4);
    	for(i =0;i<4;i++)
      sBuff[4]= sBuff[4] ^ sBuff[i];

//      while(getcom(port)>0);
    	ser->SendCom((char *)sBuff,5,3);


      t0=GetTickCount();
	   while(1){
         rc=ser->RecvCom((char *)&ch,1,1);
		   if(rc==0){
		 	  if(ch==0x7E) 		break;
		   }
			t1=GetTickCount();
			if((t1-t0)<=5000) continue;
         goto opend;
      }
      memset(tmpbuf,0,sizeof(tmpbuf));
      if(ser->RecvCom((char *)tmpbuf,3,3)<0)  goto opend;

      if ( tmpbuf[0]!=0x30 ) goto opend;
      return 0;
opend:

      return -1;
}

//循卡命令交换
int CommModu_anticoll(CSerial *ser,unsigned char *szSendBuff,unsigned char *szRecBuff)
{
	int i,j,len,iLrc=0,rc;
	unsigned char szBuff[256];
	unsigned char szTmpBuf[256],szTmpBuf1[256];
	//初始化变量
	memset(szBuff, 0,sizeof(szBuff));
	memset(szTmpBuf,0,sizeof(szTmpBuf));
	memset(szTmpBuf1,0,sizeof(szTmpBuf1));

	szBuff[0]=0x02;			//0x02为起始符，不需拆分
	szBuff[1]=szSendBuff[0];	//命令字，不需拆分
	len=szSendBuff[1];
	//长度需拆分
	szBuff[2]=((szSendBuff[1]>>4)&0x0f)|0x30;
	szBuff[3]=(szSendBuff[1]&0x0f)|0x30;
	//命令需拆分
	for(i=0;i<len;i++)
	{
		szBuff[i*2+4]=((szSendBuff[i+2]>>4)&0x0f)|0x30;
		szBuff[i*2+5]=(szSendBuff[i+2]&0x0f)|0x30;
	}

	szBuff[i*2+4]=0x03;		//0x03为结束符，不需拆分

	//计算异或校验值
	for(j=0;j<len+1;j++)
	{
		iLrc=iLrc^szSendBuff[j+1];
	}
	iLrc=iLrc^0x03;

	szBuff[i*2+5]=((iLrc>>4)&0x0f)|0x30;	//校验值需拆分
	szBuff[i*2+6]=(iLrc&0x0f)|0x30;

	//发送命令
  // while(getcom(Devfd)>0);
	rc = ser->SendCom((char *)szBuff,len*2+7,3);
	if(rc)	return(-2);

	iLrc=0;

	//接收响应起始符
   if(ser->RecvCom((char *)szTmpBuf,1,3)<0)
		return(-2);
	if(szTmpBuf[0]!=0x02)
		return(-2);

	memset(szTmpBuf,0,sizeof(szTmpBuf));

	//接收长度
   if(ser->RecvCom((char *)szTmpBuf,2,3)<0)
		return(-2);

	//计算长度
	len=((szTmpBuf[0]<<4)&0xf0)|(szTmpBuf[1]&0x0f);
   if(len<=0) return (-2);

	iLrc=iLrc^len;

	memset(szTmpBuf,0,sizeof(szTmpBuf));

	//接受剩余信息
   if(ser->RecvCom((char *)szTmpBuf,len*2+3,3)<0)
		return(-2);

	//合并响应代码和数据
	for(i=0;i<len;i++)
		szTmpBuf1[i]=((szTmpBuf[i*2]<<4)&0xf0)|(szTmpBuf[i*2+1]&0x0f);

	//判断结束符
	if(szTmpBuf[i*2]!=0x03)
		return(-2);

	//求校验值
	for(j=0;j<len;j++)
		iLrc=iLrc^szTmpBuf1[j];

	iLrc=iLrc^0x03;

	//判断校验值
	if((((szTmpBuf[i*2+1]<<4)&0xf0)|(szTmpBuf[i*2+2]&0x0f))!=iLrc)
		return(-2);

	//判断响应代码
	if(szTmpBuf1[0]!=0x30)
		return -(szTmpBuf1[0]&0x0f);

	memcpy(szRecBuff,szTmpBuf1+1,len-1);
	return(len-1);
}

//M1卡拆分.合并命令发送与接收
int CommModu_Rc(CSerial *ser,unsigned char *szSendBuff,unsigned char *szRecBuff)
{
	int i,j,len,iLrc=0;
	unsigned char szBuff[256];
	unsigned char szTmpBuf[256],szTmpBuf1[256];
	//初始化变量
	memset(szBuff, 0,sizeof(szBuff));
	memset(szTmpBuf,0,sizeof(szTmpBuf));
	memset(szTmpBuf1,0,sizeof(szTmpBuf1));


	szBuff[0]=0x02;			//0x02为起始符，不需拆分
	szBuff[1]=szSendBuff[0];	//命令字，不需拆分
	len=szSendBuff[1];
	//长度需拆分
	szBuff[2]=((szSendBuff[1]>>4)&0x0f)|0x30;
	szBuff[3]=(szSendBuff[1]&0x0f)|0x30;
	//命令需拆分
	for(i=0;i<len;i++)
	{
		szBuff[i*2+4]=((szSendBuff[i+2]>>4)&0x0f)|0x30;
		szBuff[i*2+5]=(szSendBuff[i+2]&0x0f)|0x30;
	}

	szBuff[i*2+4]=0x03;		//0x03为结束符，不需拆分

	//计算异或校验值
	for(j=0;j<len+1;j++)
	{
		iLrc=iLrc^szSendBuff[j+1];
	}
	iLrc=iLrc^0x03;

	szBuff[i*2+5]=((iLrc>>4)&0x0f)|0x30;	//校验值需拆分
	szBuff[i*2+6]=(iLrc&0x0f)|0x30;

	//发送命令
//   while(getcom(ser)>0);
	if(ser->SendCom((char *)szBuff,len*2+7,3))
		return(-2);

	iLrc=0;

	//接收响应起始符
   if(ser->RecvCom((char *)szTmpBuf,1,3)<0)
		return(-2);
	if(szTmpBuf[0]!=0x02) 
		return(-2);

	memset(szTmpBuf,0,sizeof(szTmpBuf));

	//接收长度
   if(ser->RecvCom((char *)szTmpBuf,2,3)<0)
		return(-2);

	//计算长度
	len=((szTmpBuf[0]<<4)&0xf0)|(szTmpBuf[1]&0x0f);
   if(len<=0) return (-2);
   
	iLrc=iLrc^len;

	memset(szTmpBuf,0,sizeof(szTmpBuf));

	//接受剩余信息
   if(ser->RecvCom((char *)szTmpBuf,len*2+3,3)<0)
		return(-2);

	//合并响应代码和数据
	for(i=0;i<len;i++)
		szTmpBuf1[i]=((szTmpBuf[i*2]<<4)&0xf0)|(szTmpBuf[i*2+1]&0x0f);

	//判断结束符
	if(szTmpBuf[i*2]!=0x03)
		return(-2);

	//求校验值
	for(j=0;j<len;j++)
		iLrc=iLrc^szTmpBuf1[j];
		
	iLrc=iLrc^0x03;
	
	//判断校验值
	if((((szTmpBuf[i*2+1]<<4)&0xf0)|(szTmpBuf[i*2+2]&0x0f))!=iLrc)
		return(-2);

   
	//判断响应代码
	if(szTmpBuf1[0]!=0x30)
		return -(szTmpBuf1[0]&0x0f);
	
	memcpy(szRecBuff,szTmpBuf1+1,len-1);	
	if(len>=1 ) 	return(len-1);	
	else return 0;
}

//IC卡命令发送与接收
int CommModu_c(CSerial *ser,unsigned char *szSendBuff,unsigned char *szRecBuff)
{
	int i,len,rc,iLrc=0;
	unsigned char szBuff[256];
	unsigned char szTmpBuf[256],szTmpBuf1[256];
   unsigned long	t0,t1;

	//初始化变量
	memset(szBuff, 0,sizeof(szBuff));
	memset(szTmpBuf,0,sizeof(szTmpBuf));
	memset(szTmpBuf1,0,sizeof(szTmpBuf1));

   len=szSendBuff[1];
   /*memset(_str,0,sizeof(_str));
   Hex2Asc(szSendBuff,len+2,_str);*/

	szBuff[0]=0x7E;				//7E为起始符，不需拆分
	szBuff[1]=szSendBuff[0];	//命令字，不需拆分
	//长度需拆分
	szBuff[2]=((szSendBuff[1]>>4)&0x0f)|0x30;
	szBuff[3]=(szSendBuff[1]&0x0f)|0x30;
	len=szSendBuff[1];
	//命令需拆分
	for(i=0;i<len;i++)
	{
		szBuff[i*2+4]=((szSendBuff[i+2]>>4)&0x0f)|0x30;
		szBuff[i*2+5]=(szSendBuff[i+2]&0x0f)|0x30;
	}

	//计算异或校验值
	for(i=0;i<len*2+4;i++){
		iLrc=iLrc^szBuff[i];
	}
	szBuff[len*2+4]=iLrc;

	//发送命令
  // while(getcom(port)>0);
   ser->SendCom((char *)szBuff,len*2+5,3);

   //接收响应起始符
	iLrc=0;
   memset(szTmpBuf,0,sizeof(szTmpBuf));
   t0 = GetTickCount();
   while(1){
         rc=ser->RecvCom((char *)szTmpBuf,1,1);
		   if(rc==0){
		 	  if(szTmpBuf[0]==0x7E) 		break;
		   }

			t1=GetTickCount();
			if((t1-t0)<=5000) continue;

         return -1;
   }

	iLrc=iLrc^szTmpBuf[0];

	//接收响应代码及长度
   memset(szTmpBuf,0,sizeof(szTmpBuf));
   if(ser->RecvCom((char *)szTmpBuf,3,3)<0)  return (-2);


	//判断是否错误响应
	if(szTmpBuf[1]==0x00 && szTmpBuf[2]==(iLrc^szTmpBuf[0]^szTmpBuf[1])){
		//判断响应合法性
		if((szTmpBuf[0]&0xf0)!=0x30) return(-2);
		//返回错误代码
		return -(szTmpBuf[0]&0x0f);
	}

	iLrc=iLrc^szTmpBuf[0]^szTmpBuf[1]^szTmpBuf[2];

	//计算长度
	len=((szTmpBuf[1]<<4)&0xf0)|(szTmpBuf[2]&0x0f);
   if(len<=0) return (-2);

	//接受剩余信息
   if(ser->RecvCom((char *)szTmpBuf1,len*2+1,3)<0)   return (-2);

	//计算异或校验值
	for(i=0;i<len*2;i++)
		iLrc=iLrc^szTmpBuf1[i];

	if(szTmpBuf1[i]==iLrc)
	{
		if(szTmpBuf[0]!=0x30)
		{
			return -(szTmpBuf[0]&0x0f);
		}
		else if(szBuff[1]==0x46)
		{
			memcpy(szRecBuff,szTmpBuf1,len);
		}
		else
		{
			for(i=0;i<len;i++)
			szRecBuff[i]=((szTmpBuf1[i*2]<<4)&0xf0)|(szTmpBuf1[i*2+1]&0x0f);
		}
		return(len);
	}
	else
	{
		return(-2);
	}
}

int IccComm(CSerial *ser,unsigned char Mhead,unsigned char Cla,unsigned char Ins,
        unsigned char p1,unsigned char p2,
		  unsigned char Lc,unsigned char *data,
		  unsigned char Le,unsigned char *resp){
        int i=0,m,rc,len;
        unsigned char temp[12];
        unsigned char TmpStr[256];
        unsigned char TmpStr1[256];
        unsigned char RecvCmd[256];

        memset(TmpStr,0,sizeof(TmpStr));
        memset(RecvCmd,0,sizeof(RecvCmd));
        memset(TmpStr1,0,sizeof(TmpStr1));
        memset(temp,0,sizeof(temp));

        TmpStr[i++] = Cla;
        TmpStr[i++] = Ins;
        TmpStr[i++] = p1;
        TmpStr[i++] = p2;
        TmpStr[i++] = Lc;
        
        if (Lc>0){
        		for (m=0;m<(int)Lc;m++)
           		TmpStr[i++] = data[m];
        		len=Lc+5;
        }else len=5;

        i=0;
        TmpStr1[i++] = Mhead ;
        TmpStr1[1]=len;
        memcpy(TmpStr1+2,TmpStr,len);

        rc=CommModu_c(ser,TmpStr1,RecvCmd);

        if(rc<2) return (-1);

        if(RecvCmd[rc-2]!=0x90&&RecvCmd[rc-1]!=0x00) return (-1);
        memcpy(resp,RecvCmd,rc);
        return (rc);
}

/*
 功能描述： DES 初始化
 返回： 0:成功
		<0 失败
*/
int SamDesInit(CSerial *ser)
{
	int st;
	unsigned char sRcvData[128],sSendData[128];
	
	
       //	memcpy(sSendData,pData,nSendLen);
	st=IccComm(ser,0x52,0x80,0x1a,0x28,0x01,0x08,(unsigned char *)"\x07\x56\x71\x68\x90\x72\x89\x68",-1,sRcvData);
   if ( st < 0 ) return -1;
	return 0;
}

/*
 功能描述： DES 加密
 返回： 0:成功
		<0 失败
*/
int SamDes(CSerial *ser,unsigned char *Cardid,char *pDest)
{
	int st;
	unsigned char sRcvData[128],sSendData[128];

	//DES加密
	memset(sSendData,0,sizeof(sSendData));
   memset(sRcvData,0,sizeof(sRcvData));
	memcpy(sSendData+4,"\x05\x51\x0b\x00\xff\xff\xff\xff\x05\x51\x0b\x01\x07\x56\x08\x56\x05\x51\x07\x73",20);
  memcpy( sSendData,Cardid,4 );
  memcpy( sSendData+8,Cardid,4 );
  
  
	st=IccComm(ser,0x52,0x80,0xfa,0x00,0x00,0x18,sSendData,-1,sRcvData);
   if ( st < 0 ) return -1;
   memset(pDest,0,sizeof(pDest));
   memcpy(pDest,sRcvData,24);
	return 0;
}

/*
功能描述： 读入SAM卡的终端号
*/
int SamReadId(CSerial *ser,unsigned char *pSamId)
{
	int st;
   unsigned char sRcvData[128],sSendData[128];

	//选择根文件
	memset(sSendData,0,sizeof(sSendData));
   memset(sRcvData,0,sizeof(sRcvData));
	memcpy(sSendData,"\x3f\x00",2);

	st=IccComm(ser,0x52,0x00,0xa4,0x00,0x00,0x02,sSendData,-1,sRcvData);
   if ( st <0 ) return -1;

	//读终端号文件
	memset(sSendData,0,sizeof(sSendData));
	//memcpy(sSendData,"\x3f\x00",2);
   memset(sRcvData,0,sizeof(sRcvData));
   
	st=IccComm(ser,0x52,0x00,0xb0,0x96,0x00,0x00,sSendData,0x00,sRcvData);
   if ( st < 0 ) return -1;

   memset(pSamId,0,sizeof(pSamId));
   memcpy(pSamId,sRcvData,6);//读取SAM卡卡号
	return 0;
}


//
// ASC还原到HEX
//
int  Asc2Hex(char *sin, char *sout, int sout_len)
{
        int nlen, st, i;
        char stmp[1024], ch;

        nlen = strlen(sin);
        st = nlen /2;
        if(st >= sout_len) st=sout_len;
        memset(stmp, 0, sizeof(stmp));
        for (i=0;i<st;i++)
        {
                ch= sin[2*i];
                if( ch <0x30 || ( ch >0x39 && ch <0x41) || (ch >0x46 && ch <0x61)
                        || ch >0x66 )   return -1;
                if(ch>0x39)
                        stmp[i]=((ch-0x37)&0x0f)<<4;
                else
                        stmp[i]=((ch-0x30)&0x0f)<<4;

                ch=sin[2*i+1];
                if( ch <0x30 || ( ch >0x39 && ch <0x41) || (ch >0x46 && ch <0x61)
                        || ch >0x66 )
                                return -1;

                if(ch>0x39)
                        stmp[i]=stmp[i]+((ch-0x37)&0x0f);
                else
                        stmp[i]=stmp[i]+((ch-0x30)&0x0f);
        }
        memcpy(sout,stmp,st);
        return st;
}

int get_len(char *p,int n)
{	int i,j=0;
	for(i=0;i<n;i++){
		if(*p!=0x20)	j++;		
		p++;
	}
	return(j);
}

void change_buf(char *p,int n)
{
	int i;
	char buf[128];
	i=get_len(p,n);
		if(i==n)	return;
	memset(buf,0x30,n-i);
	//ltrim(p);
	memcpy(buf+n-i,p,i);
	memcpy(p,buf,n);
}

void strtobcdstr(  char *pin,int n, char *pout)
{
	int i;
	char *p,*p2,buffer[256];
	memset(buffer,0,sizeof(buffer));
	memcpy(buffer,pin,n);
	change_buf(buffer,n);
	p=pout;
	p2=buffer;	
	for(i=0;i<n/2;i++){
		*p=((*p2-0x30)<<4);
		p2++;
		*p+=(*p2-0x30);
		p2++;
		p++;
	}
}

//密码加密算法
void str_cryptUN(unsigned char * buf, int  len, unsigned char *key )
{
  int    salt_ptr = 0;
  int    salt_len = strlen((char *)key);
  unsigned char salt[65];

  strncpy( (char *)salt, (char *)key, 64 );
  salt[64] = '\0';

  for( ; len>0; len--, buf++ ) {
    buf[0] ^= salt[salt_ptr] ^ (salt[0] * salt_ptr);
    salt[salt_ptr] += ((salt_ptr<(salt_len-1))? salt[salt_ptr+1] : salt[0]);
    if( !salt[salt_ptr] )  salt[salt_ptr]++;
    if( ++salt_ptr >= salt_len )  salt_ptr = 0;
  }
}

//循卡
int  Rc_anticoll( CSerial *ser,int ActiveMode,unsigned char *CardId)
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];

	//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	//组织命令
	memcpy(szSendBuf,"\x32\x01",2);

	switch(ActiveMode)
	{
	case 0:		memcpy(szSendBuf+2,"\x52",1);
				break;
	case 1:		memcpy(szSendBuf+2,"\x26",1);
				break;
	default:	memcpy(szSendBuf+2,"\x52",1);
				break;
	}

	//命令交换
        iRet = 2;
        iRet = CommModu_anticoll(ser,szSendBuf,szRecBuf);

	if(iRet<0){
                return(iRet);
        }

	memcpy(CardId,szRecBuf,iRet);
	return(0);
}


/*
  M1卡寻卡,失败返回-1，成功返回1
*/
int mif_anticoll( CSerial *ser,unsigned char *cardno ){
    int i,st;

    
    for(i=0;i<3;i++){

	   st=Rc_anticoll(ser,2,cardno);
     if(st==0){
     	CheckSID=99;
     	  return 1;
     	}
    }
    return -1;
}

/*
  挂起卡片
*/
int  Rc_CloseCard( CSerial *ser )
{
	int iRet;
	unsigned char szSendBuf[128];
	unsigned char szRecBuf[128];

	//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	//组织命令
	memcpy(szSendBuf,"\x40\x0",2);

	//命令交换

	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){
		return(iRet);
   }
	return(iRet);
}

/*
  认证块密码
*/
int  Rc_ConfirmPwd( CSerial *ser,int BlockID,int PwdMode,unsigned char *CardId)
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];

	//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	//组织命令
	memcpy(szSendBuf,"\x33\x06",2);
	szSendBuf[2]=BlockID;
	switch(PwdMode)
	{
	case 0:		memcpy(szSendBuf+3,"\x60",1);
				break;
	case 1:		memcpy(szSendBuf+3,"\x61",1);
				break;
	default:	memcpy(szSendBuf+3,"\x60",1);
				break;
	}
	memcpy(szSendBuf+4,CardId,4);

	//命令交换
	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){
		return(iRet);
   }
	return(iRet);
}

/*
  读块数据(16字节)
*/

int  Rc_ReadData( CSerial *ser,int BlockID,unsigned char *Data)
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];

	//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	//组织命令
	memcpy(szSendBuf,"\x34\x01",2);
	szSendBuf[2]=BlockID;

	//命令交换

	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){
		return(iRet);
   }
	memcpy(Data,szRecBuf,iRet);
	return(iRet);
}

/*
  写卡
*/
int  Rc_WriteData( CSerial *ser,int BlockID,unsigned char *Data)
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];

	//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	//组织命令
	memcpy(szSendBuf,"\x35\x11",2);
	szSendBuf[2]=BlockID;
	memcpy(szSendBuf+3,Data,16);

	//命令交换
	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){
		return(iRet);
   }
	return(iRet);
}

/*
  从SAM卡里读扇区的密钥
*/
int LoadSectorKey(CSerial *ser,unsigned char *cardid,unsigned char *_Key){

  unsigned char send_buf1[12],send_buf2[12];
  unsigned char file_tag[16],respone[128];
  int st,i;



  st=select_Ic(ser,1);
  if(st<0) return (-1);

  for( i=0;i<3;i++ ){
  		st=poweron_Ic(ser);
  		if( st>=0 )	break;
  }

  for(i=0;i<10;i++){
  		//选择金融应用目录
  		memset(file_tag,0,sizeof(file_tag));
  		memcpy(file_tag,"\xa2\x00\x00\x57\x64\x62\x69\x61\x6f",9);
  		memset(respone,0x00,128);
                Sleep(100);
  		st = IccComm(ser,0x52,0x00,0xa4,0x04,0x00,0x09,file_tag,0,respone);
   	if(st>=0) break;

  }
  if ( st < 0 ) return -1;

  st=SamDesInit(ser);

  if ( st < 0 ) return -1;

  st=SamDes(ser, cardid,(char *)send_buf2 );

  if ( st < 0 ) return -1;

  // 复制扇区密钥
  memset(_Key,0,sizeof(_Key));
  memcpy(_Key, send_buf2, 18);

  powerdown_Ic(ser);

  return 0;
}

/*
  激活卡片，返回四字节卡号
*/
int  Rc_ActiveCard( CSerial *ser,int ActiveMode,unsigned char *CardId)
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];

	//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	//组织命令
	memcpy(szSendBuf,"\x32\x01",2);

	switch(ActiveMode)
	{
	case 0:		memcpy(szSendBuf+2,"\x52",1);
				break;
	case 1:		memcpy(szSendBuf+2,"\x26",1);
				break;
	default:	memcpy(szSendBuf+2,"\x52",1);
				break;
	}

	//命令交换

	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){

		return(iRet);
   }

	memcpy(CardId,szRecBuf,iRet);
	return(iRet);
}

/*
  下装密码
*/
int  Rc_LoadPwd( CSerial *ser,int PwdMode,int SectorID,unsigned char *Pwd)
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];


	//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	//组织命令
	memcpy(szSendBuf,"\x31\x08",2);

	switch(PwdMode)
	{
	case 0:		memcpy(szSendBuf+2,"\x60",1);
				break;
	case 1:		memcpy(szSendBuf+2,"\x61",1);
				break;
	default:	memcpy(szSendBuf+2,"\x60",1);
				break;
	}

	szSendBuf[3]=SectorID;
	switch( SectorID ){
		case 0:
		case 2:
			memcpy(szSendBuf+4,Pwd,6);
			break;
		case 1:
		case 3:
			memcpy(szSendBuf+4,Pwd+6,6);
			break;
		default:
			memcpy(szSendBuf+4,Pwd+12,6);
			break;
	}
	

	//命令交换

	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){

		return(iRet);
   }

	return(iRet);

}

/*
	认证密码
  返回：0-成功 其他-失败
*/
int KeyVerify(CSerial *ser,CSerial *seric,unsigned char *cardid,int SectorID){
  	int st,i;
	 unsigned char data[32];
   unsigned long snr;

if( CheckSID == SectorID ){	//当前扇区已验密
   	return 0;
  }
   for(i=0;i<3;i++){
     st=Rc_CloseCard(ser);
     if(st==0) break;
   }
   if(st<0) return -1;

   memset(Rsnr,0,sizeof(Rsnr));
   st=Rc_ActiveCard(ser,0x52,Rsnr);
   if(st<0) return -1;

   memset(readKey,0,sizeof(readKey));
   st=LoadSectorKey(seric,cardid,readKey);
   if(st<0){
    	Rc_CloseCard(ser);
     	return -1;
   }
   readKey[18]='\0';

   /*memset(_str,0,sizeof(_str));
   Hex2Asc(readKey,6,_str);*/

   st=Rc_LoadPwd( ser,1,SectorID,readKey);
   if(st<0){
    	Rc_CloseCard(ser);
     	return -1;
   }

   st=Rc_ConfirmPwd( ser,SectorID*4,1,Rsnr);
   if(st<0){
    	Rc_CloseCard(ser);
     	return -1;
   }
   CheckSID = SectorID;
   return 0;
}


//-----------------------------------------------------------------------------

//Memory卡选卡座
//0:IC卡座，1：SAM1卡座 2：SAM2卡座
int select_Memory(CSerial *ser,int flag)
{
		int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];
	
		//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	szSendBuf[0]=0x47;	//命令字
	szSendBuf[1]=0x01;	//数据包长度
	switch( flag ){
		case 0:
			szSendBuf[2]=0x30;	//选择IC卡座
			break;
		case 1:
			szSendBuf[2]=0x31;	//选择SAM1卡座
			break;
		case 2:
			szSendBuf[2]=0x32;	//选择SAM2卡座
			break;
		default:
			szSendBuf[2]=0x30;	//选择IC卡座
			break;
	}	
	iRet=CommModu_Rc(ser,szSendBuf,szRecBuf);
	return(iRet);
}


//Memory卡选择卡型
int selecttp_Memory(CSerial *ser)
{
		int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];
	
		//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	szSendBuf[0]=0x48;	//命令字
	szSendBuf[1]=0x01;	//数据包长度
	szSendBuf[2]=0x10;	//选择卡型 AT88SC102 

	iRet=CommModu_Rc(ser,szSendBuf,szRecBuf);
	return(iRet);
}

//Memory卡上电
int poweron_Memory(CSerial *ser)
{
		int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];
	
		//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	szSendBuf[0]=0x49;	//命令字
	szSendBuf[1]=0x01;	//数据包长度
  szSendBuf[2]=0x02;	//等待插卡时间,循环检测,单次时间不宜过长
			
	iRet=CommModu_Rc(ser,szSendBuf,szRecBuf);
	return(iRet);
}


/*****************
CPU卡操作
*****************/
//IC初始化，不带上电
int init_Memory(CSerial *ser){
    int st,i;

    st=select_Memory(ser,0);
    if(st<0) return (-1);
    st=selecttp_Memory(ser);
    if(st<0) return (-2);
    return (0);
}

//IC卡下电
int powerdown_Memory(CSerial *ser)
{
		int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];
	
		//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));

	szSendBuf[0]=0x46;	//命令字
	szSendBuf[1]=0x00;	//数据包长度
	iRet=CommModu_Rc(ser,szSendBuf,szRecBuf);
	return(iRet);
}
//
//	读IC卡数据
//
int Memory_ReadData( CSerial *ser,unsigned char *Head,int num,unsigned char *Data )
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];
	
		//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));
	
	szSendBuf[0]=0x43;	//命令字
	szSendBuf[1]=0x03;	//数据包长度
	memcpy( szSendBuf+2,Head,2 );	//起始位置
	szSendBuf[4]=num;	//读数据长度
	
	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){
		return(iRet);
   }
	memcpy(Data,szRecBuf,iRet);
	return(iRet);
}

//
//	擦除IC卡数据
//
int Memory_CData( CSerial *ser,unsigned char *Head,int num )
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];
	
		//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));
	
	szSendBuf[0]=0x4c;	//命令字
	szSendBuf[1]=0x03;	//数据包长度
	memcpy( szSendBuf+2,Head,2 );	//起始位置
	szSendBuf[4]=num;	//擦数据长度
	
	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){
		return(iRet);
   }
	return(iRet);
}
//
//	写IC卡数据
//
int Memory_WriteData( CSerial *ser,unsigned char *Head,int num,unsigned char *Data )
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];
	
		//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));
	
	szSendBuf[0]=0x44;	//命令字
	szSendBuf[1]=num+2;	//数据包长度+2
	memcpy( szSendBuf+2,Head,2 );	//起始位置
	memcpy( szSendBuf+4,Data,num );	//写入数据
	
	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){
		return(iRet);
   }
	//memcpy(Data,szRecBuf,iRet);
	return(iRet);
}

int Memory_CheckPassword( CSerial *ser,unsigned char key1,unsigned char key2 )
{
	int iRet;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];
	unsigned char k1,k2;
	
		//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));
	
	szSendBuf[0]=0x6a;	//命令字
	szSendBuf[1]=4;	//密码长度+2
	szSendBuf[2]=0x00;
	szSendBuf[3]=0x0a;
	k1 = (key1&0x0f)*0x10;
	k2 = key1>>4;
	szSendBuf[4]=k1+k2;
	szSendBuf[5]=key2;
	
	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){
		return(iRet);
   }
	//memcpy(Data,szRecBuf,iRet);
	return(iRet);
}

//读一个块
//读卡地址计算方法为：扇区号＊4＋块号
//Sec为扇区号，Block为块号
//返回 0-成功 -1-验密失败 -2-读卡失败
int ReadBlock( CSerial *ser,CSerial *seric,unsigned char *cardid,int Sec, int Block, unsigned char *OutData )
{
  int rc;

  rc = KeyVerify( ser, seric,cardid,Sec );
  if( rc != 0 ){
    return -1;
  }

  //读射频卡，读addr个块的数据(addr=SerNum*4+Block)
  rc = Rc_ReadData( ser,Sec*4+Block,OutData );
  if( rc <= 0 ){
    return -2;
  }
  return 0;
}


/************************************************************
函数功能：读取电子钱包余额,当两块同时有效且值不等时取其大并且重写小的那块
返回值：成功：数值大的块号，失败：-1验密失败 -2读值失败
输出参数：balance-余额
************************************************************/
int GetM1Balance( CSerial *ser,CSerial *seric,unsigned char *cardid,int Block,unsigned long *balance )
{
	int iRet,rc;
	unsigned long amt1,amt2;
	unsigned char tmp[4],buf[17],tmp1[17];

  iRet = KeyVerify( ser, seric,cardid,Block/4 );
  if( iRet != 0 ){ 
    return -1;
  }	
  
  /**********************
  取S2B0
  ***********************/
  rc = Rc_ReadData( ser,Block,buf );
  if( rc <= 0 ){
    return -2;
  }
  memcpy( tmp1,buf,16 );
	memcpy( (unsigned char*)&amt1,buf,4 );
	//*balance = amt1/100;

/**********************
  取S2B1
  ***********************/
  rc = Rc_ReadData( ser,Block+1,buf );
  if( rc <= 0 ){
    return -2;
  }
	memcpy( (unsigned char*)&amt2,buf,4 );
	//*balance = amt2/100;
  
  if( amt1 >= amt2 ){	
  	*balance = amt1; 
  	if( amt1 != amt2 )
  	rc = Rc_WriteData(ser,Block+1,tmp1);
  	return 0; 
  }
  else{
  	*balance = amt2; 
  	rc = Rc_WriteData(ser,Block,buf);
  	return 0;
	}
}

/************************************************************
函数功能：电子钱包加值
balance以分为单位
************************************************************/
int AddM1Balance( CSerial *ser,CSerial *seric,unsigned char *cardid,unsigned long balance )
{
	int rc;
	int iRet;
	unsigned long amt;
	unsigned char szSendBuf[256];
	unsigned char szRecBuf[256];
	unsigned char buf1[4],buf2[4];
  unsigned char tmp1[17];

  rc = KeyVerify( ser, seric,cardid,2 );
  if( rc != 0 ){ 
    return -1;
  }	
		//初始化变量
	memset(szSendBuf,0,sizeof(szSendBuf));
	memset(szRecBuf,0,sizeof(szRecBuf));
	
	szSendBuf[0]=0x38;	//命令字
	szSendBuf[1]=0x05;	//数据包长度
	szSendBuf[2]=8;	//块号
	amt = balance;	//以分为单位
	memcpy( buf1,(unsigned char *)&amt,4 );
	buf2[0]=buf1[3];buf2[1]=buf1[2];buf2[2]=buf1[1];buf2[3]=buf1[0];
	memcpy( szSendBuf+3,buf2, 4 );
	
	if((iRet=CommModu_Rc(ser,szSendBuf,szRecBuf))<0){
		return(iRet);
   }
   
	rc = Rc_ReadData( ser,8,tmp1 );
  if( rc <= 0 ){
    return -2;
  }
  rc = Rc_WriteData(ser,9,tmp1);
  if( rc ){
    	return -3;
  }
	
	
  return 0;

}

/****************************************************************************
读最近三次充值信息
函数名：GetTradeInfo
****************************************************************************/
int GetTradeInfo( CSerial *ser,CSerial *seric,char *cardid,char *out1,char *out2,char *out3 )
{
	int rc;
	unsigned char tmp1[18];
	unsigned char tmp2[16];
  unsigned long amt;
  float a1,a2,a3;

  rc = KeyVerify( ser, seric,(unsigned char *)cardid,3 );
  if( rc != 0 ){
    return -1;
  }
  
  memset( tmp1,0,sizeof(tmp1) );
  rc = Rc_ReadData( ser,12,tmp1 );
  if( rc <= 0 ){
    return -2;
  }
  memcpy( tmp2,tmp1+14,4 ); //tmp2[3]=0x00;
  memcpy( (unsigned char *)&amt ,tmp2,4 );
  sprintf( out1,"%02x年%02x月%02x日   %02x:%02x    充值金额： %ld.00 元",tmp1[5],tmp1[6],tmp1[7],tmp1[8],tmp1[9],amt/100 );
  
  memset( tmp1,0,sizeof(tmp1) );
  rc = Rc_ReadData( ser,13,tmp1 );
  if( rc <= 0 ){
    return -2;
  }
  memcpy( tmp2,tmp1+14,4 ); // tmp2[3]=0x00;
  memcpy( (unsigned char *)&amt ,tmp2,4 );
  sprintf( out2,"%02x年%02x月%02x日   %02x:%02x    充值金额： %ld.00 元",tmp1[5],tmp1[6],tmp1[7],tmp1[8],tmp1[9],amt/100 );

  memset( tmp1,0,sizeof(tmp1) );
  rc = Rc_ReadData( ser,14,tmp1 );
  if( rc <= 0 ){
    return -2;
  }
  memcpy( tmp2,tmp1+14,4 ); //tmp2[3]=0x00;
  memcpy( (unsigned char *)&amt ,tmp2,4 );
  sprintf( out3,"%02x年%02x月%02x日   %02x:%02x    充值金额： %ld.00 元",tmp1[5],tmp1[6],tmp1[7],tmp1[8],tmp1[9],amt/100 );

  return 0;
}

/***********************************************************
写最近充值信息
覆盖最早一条记录

***********************************************************/
int WriteTradeInfo( CSerial *ser,CSerial *seric,char *cardid,unsigned char *buf )
{
	int rc,n1,n2,m1,m2,wBlock;
	unsigned char tmp1[16];
  unsigned long amt;

  rc = KeyVerify( ser, seric,(unsigned char *)cardid,3 );
  if( rc != 0 ){
    return -1;
  }

  rc = Rc_ReadData( ser,12,tmp1 );
  if( rc <= 0 ){
    return -2;
  }
  wBlock = 12;
  n1 = tmp1[4]*30*12+tmp1[5]*30+tmp1[6];
  m1 = tmp1[7]*24+tmp1[8];
  
  rc = Rc_ReadData( ser,13,tmp1 );
  if( rc <= 0 ){
    return -2;
  }
  n2 = tmp1[4]*30*12+tmp1[5]*30+tmp1[6];
  m2 = tmp1[7]*24+tmp1[8];
  if( (n1 > n2)||((n1==n2)&&(m1>m2) ) ){  //该记录更早
  	n1 = n2;m1=m2;
  	wBlock = 13;
  }

  rc = Rc_ReadData( ser,14,tmp1 );
  if( rc <= 0 ){
    return -2;
  }
  n2 = tmp1[4]*30*12+tmp1[5]*30+tmp1[6];
  m2 = tmp1[7]*24+tmp1[8];
  if( (n1 > n2)||((n1==n2)&&(m1>m2) ) ){  //该记录更早
  	//num = tmp1[4]*30*12+tmp2[5]*30+tmp3[6];
  	wBlock = 14;
  }
  
  rc = Rc_WriteData( ser,wBlock,buf);
  
  return rc;
}

int hextobcd ( int data )
{
  int result;
//  int mid;
  int bal;
  bal = data %1000;
  result = (data/1000)<<12;
  result += (bal/100)<<8;
  bal = bal%100;
  result += (bal/10)<<4;
  bal = bal%10;
  result += bal;
  return result;
}

/***************************************************************
// 读索引块S1B1
// 返回值0表示可以充值，1不可以
******************************************************************/
int read_index( CSerial *ser,CSerial *seric,char *cardid, int year, int month)
{
    int rc,flag2;
    unsigned char buf[17];
    int y,m;

    rc = KeyVerify( ser, seric,(unsigned char *)cardid,1 );
  	if( rc != 0 ){
    	return -1;
  	}
  	
		memset( buf,0,sizeof(buf) );
    rc = Rc_ReadData( ser,5,buf );
	  if( rc <= 0 ){
	    return -2;
	  }
    

   	flag2 = month%4;

    y = hextobcd(year);
    switch( flag2 ){
    	case 0:
    		m = Put_month( month,buf[5] );
    		if( (buf[4] == y)&&(buf[5] == m ) )
    		return(1);
    		break;
    	case 3:
    		m = Put_month( month,buf[5] );
    		if( (buf[3] == y)&&(buf[5] == m ) )
    		return(1);
    		break;
    	case 1:
    		m = Put_month( month,buf[2] );
    		if( (buf[0] == y)&&(buf[2] == m ) )
    		return(1);
    		break;
    	case 2:
    		m = Put_month( month,buf[2] );
    		if( (buf[1] == y)&&(buf[2] == m ) )
    		return(1);
    		break;
    	default:
    		break;
    }
    return(0);
}

/******************************************************
函数功能：写卡验证
解释：S1B2中第14存放有S1B1的crc
*******************************************************/
int set_s1b2( CSerial *ser,CSerial *seric,char *cardid,char a ){
    int rc;
    unsigned char buf[17],bufcrc[17];
    
    rc = KeyVerify( ser, seric,(unsigned char *)cardid,1 );
  	if( rc != 0 ){
    	return -1;
  	}
    memset( buf,0,sizeof(buf) );
    rc = Rc_ReadData( ser,6,buf );
	  if( rc <= 0 ){
	    return -2;
	  }

    buf[14] = a;
    memset( bufcrc,0,sizeof(bufcrc) );
    bufcrc[0]=0x0f;
    memcpy( bufcrc+1,buf,15 );
    buf[15] = Wd_Crc8( (char *)bufcrc );
    rc = Rc_WriteData(ser,6,buf);
    return rc;
}

/*****************************************************************************************
函数功能：月票卡写入数据区
返回值：0成功 -1验密失败
*******************************************************************************************/
int add_remain( CSerial *ser,CSerial *seric,char *cardid,int year,int month,unsigned long balance )
{
  int rc,sec,succ=2;
  unsigned long num;
  unsigned char HLdata[17];

  num = balance;
  sec = month%4;
  if( sec == 0) sec=4;

  rc = KeyVerify( ser, seric,(unsigned char *)cardid,sec+3 );
  if( rc != 0 ){
    return -1;
  }

  memcpy( HLdata,(char *)&num,4 );
  HLdata[4]=~HLdata[0];
  HLdata[5]=~HLdata[1];
  HLdata[6]=~HLdata[2];
  HLdata[7]=~HLdata[3];
  HLdata[8]=HLdata[0];
  HLdata[9]=HLdata[1];
  HLdata[10]=HLdata[2];
  HLdata[11]=HLdata[3];
  HLdata[12]=month;
  HLdata[13]=~HLdata[12];
  HLdata[14]=month;
  HLdata[15]=~HLdata[14];
  
  rc = Rc_WriteData(ser,4*(sec+3),HLdata);
    if( rc ){
    	succ--;
   }
   rc = Rc_WriteData(ser,4*(sec+3)+1,HLdata);
    if( rc ){
    	succ--;
   }
   if( succ == 0 ) return -3;

  return rc;
}

/**************************************************************
	写索引块S1B1
	0-成功 -1-写卡验证出错 -2-读块 3-写块出错 -4写s1b2出错
******************************************************************/
int add_index( CSerial *ser,CSerial *seric,char *cardid, int year, int month )
{
    int rc,flag1,flag2,i;
    unsigned char buf[17];
    char bufcrc[17],crc;

    rc = KeyVerify( ser, seric,(unsigned char *)cardid,1 );
  	if( rc != 0 ){
    	return -1;
  	}

    rc = Rc_ReadData( ser,5,buf );
	  if( rc <= 0 ){
	    return -2;
	  }
    flag1 = month%2;
    	buf[9]=0x01;		//票制:月票
    	flag2 = month%4;
    switch( flag2 ){
    	case 0:
    		buf[4]=hextobcd(year);
    		buf[5]=Put_month( month,buf[5] );
    		break;
    	case 3:
    		buf[3]=hextobcd(year);
    		buf[5]=Put_month( month,buf[5] );
    		break;
    	case 1:
    		buf[0]=hextobcd(year);
    		buf[2]=Put_month( month,buf[2] );
    		break;
    	case 2:
    		buf[1]=hextobcd(year);
    		buf[2]=Put_month( month,buf[2] );
    		break;
    	default:
    		break;
    }
    if( flag1 == 0 ){		//写6、7、8字节
    	buf[7]=hextobcd(year);
    	buf[8]=Put_month( month,buf[8] );
    }
    else{
    	buf[6]=hextobcd(year);
    	buf[8]=Put_month( month,buf[8] );
    }
    memset( bufcrc,0,sizeof(buf) );
    bufcrc[0] = 0x0f;
    memcpy( bufcrc+1,buf,15 );    
    buf[15] = Wd_Crc8( bufcrc );	//crc8 验证
    
    rc = Rc_WriteData(ser,5,buf);
    if( rc ){
    	return -3;
    }
    //	写卡验证
    memset( bufcrc,0,sizeof(buf) );
    bufcrc[0] = 0x0b;
    memcpy( bufcrc+1,buf,11 );
    crc = Wd_Crc8( bufcrc );	
    rc = set_s1b2( ser,seric,cardid,crc );
    if( rc ){
    	return -4;
    }
    return rc;
}

/********************************************************
函数功能：取月票信息
返回值：该月月票次数，-1验密失败 -2未购买该月
********************************************************/
int GetMonthInfo( CSerial *ser,CSerial *seric,char *cardid,int year,int month )
{
	int rc;
  unsigned long num;
	
	/*rc = KeyVerify( ser, seric,cardid,1 );
  if( rc != 0 ){
    return -1;
  }*/
  rc = read_index( ser, seric,cardid,year,month );
  if( rc == 0 ){	//可以充值，表示未购买
    return -2;
  }
  switch( month%4 ){
  	case 0:	//s7b0,s7b1 - 4，8，12月
  		rc = GetM1Balance( ser,seric,(unsigned char *)cardid,28,&num );
  		break;
  	case 1: //s4b0,s4b1 - 1，5，9月
  		GetM1Balance( ser,seric,(unsigned char *)cardid,16,&num );
  		break;
  	case 2: //s5b0,s5b1 - 2，6，10月
  		GetM1Balance( ser,seric,(unsigned char *)cardid,20,&num );
  		break;
  	case 3: //s6b0,s6b1 - 3，7，11月
  		GetM1Balance( ser,seric,(unsigned char *)cardid,24,&num );
  		break;
  	default:
  		num = 0;
  		break;
  }
  if( rc < 0 ) return rc;
  rc = num;
  return rc;
}
/*********************************************************
检查是否换卡
函数名：CheckCard1
输入参数： ser 串口
输出参数：cardno-卡号
返回值： 1非原卡 0原卡
*********************************************************/
int CheckCard1( CSerial *ser,CSerial *seric,char *cardid,char *cardno)
{
	int rc;
	unsigned char buf[17];
	unsigned char c_cardid[16],c_cardno[16];
  int t_m0,t_m1;
  
  while(1){
    rc = mif_anticoll( ser,c_cardid );
    if(rc==1) break;
    t_m1 =  GetTickCount() - t_m0;
    if( t_m1 > 3000 ){
    	 return 1;
    }
  }
  
rc = ReadBlock( ser,seric,c_cardid,1,0,buf );
	if( rc != 0 ) return rc;
	
	//拷贝卡编号
	Hex2Asc( buf+2,4,(char *)c_cardno );
	if( strncmp((char *)c_cardno,cardno,8)!=0) return 1;		
	return 0;
}

/***********************************88
  将0x11-->11
**************************************/
int GetInt( unsigned char h )
{
	int i;
	
	i = 10*(h/16) + h%16 ;
	
	return i;
}

/*************************************************************************
函数功能：检查年审
输入参数：
返回值：0成功 2验密失败 
*************************************************************************/
int CheckCard2( CSerial *ser,CSerial *seric,unsigned char *cardid,unsigned char cardtype )
{
	int rc;
	int c_month,k_year,k_month,k_day;
	unsigned char buf[16];
	time_t timer;
  struct tm *tblock;
	
	/* gets time of day */
   timer = time(NULL);
  /* converts date/time to a structure */
  tblock = localtime(&timer);
   
	rc = ReadBlock( ser,seric,cardid,1,0,buf );
	if( rc != 0 ) return rc;
		
	if( (cardtype == 'C')||(cardtype == 'E') )	c_month = 8;
	else if( cardtype == 'D' ) c_month = 11;
	else return 0;
  if( tblock->tm_mon+1 > c_month-1 ){
  	/**********************************
  	  检查年审信息
  	***********************************/
  	k_year = GetInt( buf[0] );
  	k_month = GetInt( buf[1] );
  	k_day = GetInt( buf[2] );
  	if( k_year < tblock->tm_year - 100 )	return 2;
  	if( k_month < 8 ) return 2;
	}
	
	return 0;
}

/*********************************************************
读公交卡信息
函数名：GetCardInfo
输入参数： ser 串口
输出参数：cardno-卡号 cardtype-卡类型 acbl-电子钱包余额 buf1、buf2、buf3三个月票余额
返回值： -3新卡，不能充值,1售卡押金为0不能充值
*********************************************************/
int GetCardInfo( CSerial *ser,CSerial *seric,char *cardid,char *cardno, char *cardtype,unsigned long *acbl,char *buf1,char *buf2,char *buf3)
{
	int rc,ret;
	unsigned char buf[17];
	time_t timer;
	int t_month,t_year;
  struct tm *tblock;
  int m1,m2,m3,y1,y2,y3;
  unsigned long num1,num2,num3;
  
//  /* gets time of day */
//   timer = time(NULL);
//   /* converts date/time to a structure */
//   tblock = localtime(&timer);
//   /* 得到当前系统日期  */
//   t_month = tblock->tm_mon+1;
//   t_year = tblock->tm_year-100;
//   /* 得到需显示的三个月份 */
//   m1 = t_month;y1 = t_year;
//   if( m1 != 12 ){ m2=m1+1; y2=y1; }
//   	else{m2=1;y2=y1+1; }
//   if( m2 != 12 ){ m3=m2+1; y3=y2; }
//   	else{m3=1;y3=y2+1; }

	rc = ReadBlock( ser,seric,(unsigned char *)cardid,1,0,buf );
	if( rc != 0 ) return rc;
	
	//判断主子卡类型
	switch( buf[1] ){
		case 0x01:
			strcpy( cardtype,"电子钱包卡(A卡)" );
			M1CardType = 'A'; //交易中标识卡类型用
			break;	
		case 0xA3:
			strcpy( cardtype,"成人优惠卡(B卡)" );
			M1CardType = 'B'; //交易中标识卡类型用
			break;
		case 0xA4:
			strcpy( cardtype,"学生优惠卡(C卡)" );
			M1CardType = 'C'; //交易中标识卡类型用
			break;
		default:
			strcpy( cardtype,"本系统不支持该卡" );
			M1CardType = 'X'; //交易中标识卡类型用
			break;
	}
	if( buf[14] == 0xAA ) return -3;
	if( buf[13] == 0 ){	//售卡押金为0，不能充值
		rc = 1;
	}
	else rc=0;
	//拷贝卡编号
	Hex2Asc( buf+2,4,cardno );
	
	//取电子钱包余额
	GetM1Balance( ser,seric,(unsigned char *)cardid,8,acbl );
	
	GetTradeInfo( ser,seric,cardid,buf1,buf2,buf3 );
	
	ret = CheckCard2( ser,seric,(unsigned char *)cardid,M1CardType );
	if( ret != 0 ) rc = ret;
/*	月票作废，仅考虑电子钱包
	//取最近三个月月票信息
	num1 = GetMonthInfo( ser,seric,cardid,y1,m1 );
	if( num1 == -2 ){
		sprintf( buf1,"%02d年%02d月 未购买",y1,m1 );
	}
	else
		sprintf( buf1,"%02d年%02d月 (%d次)",y1,m1,num1 );
	num2 = GetMonthInfo( ser,seric,cardid,y2,m2 );
	if( num2 == -2 ){
		sprintf( buf2,"%02d年%02d月 未购买",y2,m2 );
	}
	else
		sprintf( buf2,"%02d年%02d月 (%d次)",y2,m2,num2 );
	num3 = GetMonthInfo( ser,seric,cardid,y3,m3 );
	if( num3 == -2 ){
		sprintf( buf3,"%02d年%02d月 未购买",y3,m3 );
	}
	else
		sprintf( buf3,"%02d年%02d月 (%d次)",y3,m3,num3 );*/
		
	return rc;
}




/*************************************************************************
函数功能：对指定月进行充值
输入参数：balance - 充值的次数
返回值：0成功 -1验密失败 -2已充值 -3写块失败 -4写索引失败
*************************************************************************/
int AddMonthBalance( CSerial *ser,CSerial *seric,unsigned char *cardid,int year,int month, unsigned long balance )
{
	int rc;
	
	rc = read_index( ser, seric,(char *)cardid,year,month);
	if( rc != 0 ) return -2;
	
	rc = add_remain( ser, seric,(char *)cardid,year,month,balance );
	if( rc != 0 ) return -3;
	
	rc = add_index( ser, seric,(char *)cardid,year,month );
	if( rc !=0 ) return -4;
		
	return 0;
}