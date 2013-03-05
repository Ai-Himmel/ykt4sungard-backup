#include "stdafx.h"
#include "Comm.h"

HANDLE  hCommDev = NULL;
int ErrorCode;
BYTE Dll_RetData[500];
int Dll_CommByte;
int Dll_bps = 19200;
BYTE Dll_MacNo;
COMMTIMEOUTS CommTimeOuts;
unsigned char subkey[17][49];
unsigned char IP_result[65];
unsigned char pc_1[57]={57,49,41,33,25,17,9,
                           1,58,50,42,34,26,18,
                           10,2,59,51,43,35,27,
                           19,11,3,60,52,44,36,
                           63,55,47,39,31,23,15,
                           7,62,54,46,38,30,22,
                           14,6,61,53,45,37,29,
                           21,13,5,28,20,12,4};
unsigned char pc_2[49]={14,17,11,24,1,5,
                           3,28,15,6,21,10,
                           23,19,12,4,26,8,
                           16,7,27,20,13,2,
                           41,52,31,37,47,55,
                           30,40,51,45,33,48,
                           44,49,39,56,34,53,
                           46,42,50,36,29,32};
unsigned char ls[17]={1,1,2,2,2,2,2,2,
                         1,2,2,2,2,2,2,1};
unsigned char IP1[65]={58,50,42,34,26,18,10,2,
                          60,52,44,36,28,20,12,4,
                          62,54,46,38,30,22,14,6,
                          64,56,48,40,32,24,16,8,
                          57,49,41,33,25,17,9,1,
                          59,51,43,35,27,19,11,3,
                          61,53,45,37,29,21,13,5,
                          63,55,47,39,31,23,15,7};
unsigned char IP_1[65]={40,8,48,16,56,24,64,32,
                           39,7,47,15,55,23,63,31,
                           38,6,46,14,54,22,62,30,
                           37,5,45,13,53,21,61,29,
                           36,4,44,12,52,20,60,28,
                           35,3,43,11,51,19,59,27,
                           34,2,42,10,50,18,58,26,
                           33,1,41, 9,49,17,57,25};

unsigned char enlage[49]={32, 1, 2, 3, 4, 5,
                              4, 5, 6, 7, 8, 9,
                              8, 9,10,11,12,13,
                             12,13,14,15,16,17,
                             16,17,18,19,20,21,
                             20,21,22,23,24,25,
                             24,25,26,27,28,29,
                             28,29,30,31,32,1};
unsigned char mselect[513]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
                              0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
                              4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
                              15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,
                              15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
                              3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
                              0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
                              13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,
                              10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
                              13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
                              13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
                              1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,
                              7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
                              13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
                              10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
                              3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,
                              2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
                              14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
                              4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
                              11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,
                              12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
                              10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
                              9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
                              4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,
                              4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
                              13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
                              1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
                              6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,
                              13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
                              1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
                              7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
                              2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};

unsigned char signal[33]={16,7,20,21,29,12,28,17,
                             1,15,23,26,5,18,31,10,
                             2,8,24,14,32,27,3,9,
                             19,13,30,6,22,11,4,25};


void des_code(unsigned char *dkey,unsigned char *jmdata,unsigned char *result,unsigned char k);
void sub_key(unsigned char *key);
void DECODE(unsigned char *IP_result);
void CODE(unsigned char *IP_result);
void IP_pro1(unsigned char *inword,unsigned char *result);
void IP_pro(unsigned char *inword,unsigned char *IP_result);
int en_key(unsigned char* mtext,unsigned char* text);



int en_key(unsigned char* mtext,unsigned char* text)
{

	//unsigned char M_Key[8]={0xf8,0x8c,0xfa,0xfB,0xfb,0xfa,0xf9,0x8c}; 
	unsigned char M_Key[8]="";
	unsigned char s_key[8]={0x32,0x30,0x30,0x35,0x30,0x31,0x33,0x31};
	int i;
	
	memcpy(M_Key,mtext,sizeof(M_Key));
	for(i=0;i<8;i++)
		M_Key[i] = M_Key[i]^s_key[i];
	for(i=0;i<8;i++)
		M_Key[i] =~M_Key[i];

	memcpy(text,M_Key,8);
	return 0;
}

unsigned int crctab[256]=
{
 0x0000,0x1021,0x2042,0x3063,0x4084,0x50A5,0x60C6,0x70E7,
 0x8108,0x9129,0xA14A,0xB16B,0xC18C,0xD1AD,0xE1CE,0xF1EF,
 0x1231,0x0210,0x3273,0x2252,0x52B5,0x4294,0x72F7,0x62D6,
 0x9339,0x8318,0xB37B,0xA35A,0xD3BD,0xC39C,0xF3FF,0xE3DE,
 0x2462,0x3443,0x0420,0x1401,0x64E6,0x74C7,0x44A4,0x5485,
 0xA56A,0xB54B,0x8528,0x9509,0xE5EE,0xF5CF,0xC5AC,0xD58D,
 0x3653,0x2672,0x1611,0x0630,0x76D7,0x66F6,0x5695,0x46B4,
 0xB75B,0xA77A,0x9719,0x8738,0xF7DF,0xE7FE,0xD79D,0xC7BC,
 0x48C4,0x58E5,0x6886,0x78A7,0x0840,0x1861,0x2802,0x3823,
 0xC9CC,0xD9ED,0xE98E,0xF9AF,0x8948,0x9969,0xA90A,0xB92B,
 0x5AF5,0x4AD4,0x7AB7,0x6A96,0x1A71,0x0A50,0x3A33,0x2A12,
 0xDBFD,0xCBDC,0xFBBF,0xEB9E,0x9B79,0x8B58,0xBB3B,0xAB1A,
 0x6CA6,0x7C87,0x4CE4,0x5CC5,0x2C22,0x3C03,0x0C60,0x1C41,
 0xEDAE,0xFD8F,0xCDEC,0xDDCD,0xAD2A,0xBD0B,0x8D68,0x9D49,
 0x7E97,0x6EB6,0x5ED5,0x4EF4,0x3E13,0x2E32,0x1E51,0x0E70,
 0xFF9F,0xEFBE,0xDFDD,0xCFFC,0xBF1B,0xAF3A,0x9F59,0x8F78,
 0x9188,0x81A9,0xB1CA,0xA1EB,0xD10C,0xC12D,0xF14E,0xE16F,
 0x1080,0x00A1,0x30C2,0x20E3,0x5004,0x4025,0x7046,0x6067,
 0x83B9,0x9398,0xA3FB,0xB3DA,0xC33D,0xD31C,0xE37F,0xF35E,
 0x02B1,0x1290,0x22F3,0x32D2,0x4235,0x5214,0x6277,0x7256,
 0xB5EA,0xA5CB,0x95A8,0x8589,0xF56E,0xE54F,0xD52C,0xC50D,
 0x34E2,0x24C3,0x14A0,0x0481,0x7466,0x6447,0x5424,0x4405,
 0xA7DB,0xB7FA,0x8799,0x97B8,0xE75F,0xF77E,0xC71D,0xD73C,
 0x26D3,0x36F2,0x0691,0x16B0,0x6657,0x7676,0x4615,0x5634,
 0xD94C,0xC96D,0xF90E,0xE92F,0x99C8,0x89E9,0xB98A,0xA9AB,
 0x5844,0x4865,0x7806,0x6827,0x18C0,0x08E1,0x3882,0x28A3,
 0xCB7D,0xDB5C,0xEB3F,0xFB1E,0x8BF9,0x9BD8,0xABBB,0xBB9A,
 0x4A75,0x5A54,0x6A37,0x7A16,0x0AF1,0x1AD0,0x2AB3,0x3A92,
 0xFD2E,0xED0F,0xDD6C,0xCD4D,0xBDAA,0xAD8B,0x9DE8,0x8DC9,
 0x7C26,0x6C07,0x5C64,0x4C45,0x3CA2,0x2C83,0x1CE0,0x0CC1,
 0xEF1F,0xFF3E,0xCF5D,0xDF7C,0xAF9B,0xBFBA,0x8FD9,0x9FF8,
 0x6E17,0x7E36,0x4E55,0x5E74,0x2E93,0x3EB2,0x0ED1,0x1EF0
}; 


/************ calc_crc16 快表法*************/

void crcupdata(unsigned char in,unsigned short *accum,unsigned int *crctab)
{
	*accum=(*accum<<8)^crctab[(*accum>>8)^in];
}
//验证时，返回0表示CRC正确,计算时将两位CRC也记入
bool Calc_crc16(int len,unsigned char *in,unsigned char *out)
{
	unsigned char i;
	unsigned short crc;	
	bool stat;
	stat=false;
	crc=0xc78c;
	for(i=0;i<len;in++,i++)
	{
		crcupdata(*in,&crc,crctab);
	}	
    out[0]=(unsigned char)(crc>>8);
	out[1]=(unsigned char)crc;
	// modify by 汤成
	// 39公司明确说明该CRC算法如果计算出来的 crc 为 0 也是正常的。
	// 因此注释掉判断条件
	//if(crc)
	stat=true;
	return(stat);
}	

/////////Compound function////////////////
int ExeCommand(unsigned char *Buffer,int Len)
{
	int i,retCode=0,Comm_Len;
	unsigned char Data[500];
    int MSec,L;
	unsigned char CRC[3];
	CString cs,cs1;
	
	if((Len<0)||(Len>256))
	{
		ErrorCode = 38;
		return (-1);
	}
	
	Data[0] = STX1;
	Data[1] = Dll_MacNo;
	Data[2] = Dll_CommByte;
	Data[3] = Len%256;

	for(i = 0; i<Len;i++)
		Data[4+i] = Buffer[i];

	Calc_crc16(Data[3]+4,Data,CRC);//CRC
	Data[Len+4] = CRC[0];
	Data[Len+5] = CRC[1];
	Data[Len+6] = ETX1;

	MSec = 1500;//1500接收超时;

	if(SendData(Data,Len+7))
	{
		return -1;
	}

	if(Dll_MacNo == 0)//广播
		return 0;

	for(i = 0;i<500;i++)
		Dll_RetData[i] = 0;

	//接收数据
	Comm_Len = ReceiveData(MSec,Dll_RetData);
		
	if(Comm_Len == -1)
	{
		return -1;
	}

    //检查收到数据的正确性
    retCode = -1;
    if (Comm_Len<7 )
	{
		ErrorCode = 43;
		return -1;
	}
	L = Dll_RetData[3];
        
    if (Comm_Len!=L+7)
	{
		ErrorCode = 43;
		return -1;
	}
	for(i = 0;i<3;i++)
		CRC[i] = 0;

	if(!Calc_crc16(L+4,Dll_RetData,CRC))
	{
		ErrorCode = 47;
		return (-1);
	}

    if (Dll_RetData[4+L]!=CRC[0])
	{
		ErrorCode = 46;
		return -1;
	}
    if (Dll_RetData[5+L]!=CRC[1])
	{
		ErrorCode = 46;
		return -1;
	}

	if(Dll_RetData[2]>0)
	{
		ErrorCode = Dll_RetData[2];
		return -1;
	}
        
	retCode = 0;
	return retCode;
}		

//*******************************************
int	ReceiveData(int _WaitTime,unsigned char *RecBuffer)
{

	DWORD	StartTime;
	DWORD	EndTime;
	int	    WaitTime;
	BYTE	*buffer;
	int     WaitForSTX2Time=600;
    int		pack_len,PacketLen;
	DWORD	BytesRead=0,nToRead=0;
	BOOL	bReturn;
    //  receive text 
	StartTime = GetTickCount();
	buffer = RecBuffer;
    buffer++;
	//  wait for start of text flag -- STX 
	do{
		*RecBuffer = (char)NULL;
		bReturn = ReadFile(hCommDev,RecBuffer,1,&BytesRead,NULL);
		if (bReturn == FALSE)
		{			
			ErrorCode = 44;
			return(-1);
		}
		EndTime=GetTickCount();
		WaitTime = EndTime - StartTime;
		if(WaitTime > WaitForSTX2Time) 
		{	
			ErrorCode = 42;
			return(-1);
		}
	}while(*RecBuffer!=STX2);   	

    StartTime = GetTickCount();
    pack_len = 3;		
    while (pack_len>0)
	{
		bReturn = ReadFile(hCommDev,buffer,pack_len,&BytesRead,NULL);
		if(bReturn == FALSE)
		{		
			ErrorCode = 44;
			return(-1);
		}
   		buffer += BytesRead;
    	pack_len -= BytesRead;
  		EndTime=GetTickCount();
		WaitTime = EndTime - StartTime;
		if(WaitTime > _WaitTime) 
		{			
			ErrorCode = 42;
			return(-1);
		}
	}
	buffer--;
    pack_len = *buffer;		
    buffer ++;
        /*  Add CRC1,CRC2 and ETX2 */
    pack_len += 3;
	StartTime = GetTickCount();
    while (pack_len>0)
	{
        bReturn = ReadFile(hCommDev,buffer,pack_len,&BytesRead,NULL);
		if(bReturn == FALSE)
		{
			ErrorCode = 44;
			return(-1);
		}
		buffer += BytesRead;
	    pack_len -= BytesRead;
	    EndTime=GetTickCount();
	    WaitTime = EndTime - StartTime;
	    if(WaitTime > _WaitTime) 
		{	
			ErrorCode = 42;
			return(-1);
		}
	}
    *buffer-- = (char)NULL;
    if (*buffer!=ETX2)
	{		
		ErrorCode = 46;
		return -1;
	}
	buffer++;   
	PacketLen = buffer-RecBuffer;	 
	
	return(PacketLen);
	///modified by liyongdong
}

//***********************************************
int	SendData(unsigned char *PacketBuffer,int PacketLen)
{
	DWORD	BytesWritten=0;
	DWORD	WrittingLen,total_write_len;
	BOOL	bReturn;
//	char temp[256];
//	int i;

	unsigned char	*buffer;

		/*  Send text  */

	PurgeComm(hCommDev,PURGE_TXCLEAR);
	PurgeComm(hCommDev,PURGE_RXCLEAR);

	buffer = PacketBuffer;
	WrittingLen = PacketLen;
	total_write_len=0;
	do{
		BytesWritten=0;
		bReturn=WriteFile(hCommDev,buffer,WrittingLen, &BytesWritten,NULL);
		
		if (!bReturn)
		{
			ErrorCode = 45;
			return(-1);
		}
		else{
			total_write_len += BytesWritten;
			buffer += BytesWritten;
			WrittingLen -= BytesWritten;
		}
	} while (total_write_len<(DWORD)PacketLen);

	return(0);
}

//*******************************************
int CommIntilialize(char* ComStr,int BaudRate)
{
	DCB		dcb;
	char	InitTemp[80];
	char	CommName[10];
	
	strcpy(CommName,ComStr);

	hCommDev = CreateFile 
	(
		CommName,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, //0,
		NULL
	);
	
	if (hCommDev == (HANDLE)-1 )
	{
		ErrorCode = 40;
		DWORD err = GetLastError();
		if(err==5)
			ErrorCode = 48;
		return (-1);
	}

	memset(&dcb,0,sizeof(DCB));
	GetCommState(hCommDev,&dcb);
	sprintf(InitTemp,"baud=%d parity=N data=8 stop=1 ",BaudRate);
	BuildCommDCB(InitTemp,&dcb);
	SetCommState(hCommDev,&dcb);

	SetupComm(hCommDev,1024,1024);

	COMMTIMEOUTS CommTimeOuts;
	memset(&CommTimeOuts,0,sizeof(CommTimeOuts));
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
//	CommTimeOuts.WriteTotalTimeoutMultiplier = 5;
//	CommTimeOuts.WriteTotalTimeoutConstant = 50;	  
	SetCommTimeouts(hCommDev,&CommTimeOuts);
	PurgeComm(hCommDev,PURGE_TXCLEAR);
	PurgeComm(hCommDev,PURGE_RXCLEAR);
	return 0;
}		

//***********************************************
void sub_key(unsigned char *key)
{
   int  i,j,k;
   unsigned char c[31]={""};
   unsigned char d[31]={""};
   unsigned char kz[65]={""};
   for(i=1;i<65;i++){
       k=(i-1)/8;
       j=(i-1)-k*8;
       kz[i]=(key[k]>>(7-j))&1;
   }

   for(i=1;i<57;i++){
      k=pc_1[i-1];
      if(i<29)  c[i]=kz[k];
      else   d[i-28]=kz[k];
   }
   for(i=1;i<17;i++){
       k=ls[i-1];
       c[29]=c[1];
       c[30]=c[2];
       d[29]=d[1];
       d[30]=d[2];
       for(j=1;j<29;j++){
         c[j]=c[j+k];
         d[j]=d[j+k];
       }
       for(j=1;j<57;j++){
         if(j<29) kz[j]=c[j];
         else kz[j]=d[j-28];
       }
       for(j=1;j<49;j++){
         k=pc_2[j-1];
         subkey[i][j]=kz[k];
       }
   }
}

//***********************************************
void des_code(unsigned char *dkey,unsigned char *jmdata,unsigned char *result,unsigned char k)
{
    sub_key(dkey);
    IP_pro(jmdata,IP_result);
    if(k==0x30)  CODE(IP_result);
    else if(k==0x31) DECODE(IP_result);
    IP_pro1(IP_result,result);
}

void TriDes(unsigned char *dkey, unsigned char *jmdata, unsigned char *result, unsigned char k)
{
	unsigned char Src0[8],Key0[8];//,Res[8];
	int i;
	for(i=0;i<8;i++)
	{
		Src0[i] = jmdata[i];
		Key0[i] = dkey[i];
	}
	des_code(Key0,Src0,result,k);
	for(i=0;i<8;i++)
	{
		Src0[i] = result[i];
		Key0[i] = dkey[i+8];
	}
	if(k == 0x30) 
		des_code(Key0,Src0,result,0x31);
	else
		des_code(Key0,Src0,result,0x30);
	
	for(i=0;i<8;i++)
	{
		Src0[i] = result[i];
		Key0[i] = dkey[i];
	}
	des_code(Key0,Src0,result,k);
}


//***********************************************
void IP_pro(unsigned char *inword,unsigned char *IP_result)
{
   int i,j,k,h;
   for(i=1;i<65;i++){
       h=IP1[i-1];
       j=(h-1)/8;
       k=h-1-j*8;
       IP_result[i]=(inword[j]>>(7-k))&1;
   }
}

//***********************************************
void IP_pro1(unsigned char *inword,unsigned char *result)
{
   int i,j;
   for(i=0;i<8;i++){ result[i]=0;}
   for(i=1;i<65;i++){
       j=IP_1[i-1];
       result[(i-1)/8]+=inword[j]<<(8-i+(i-1)/8*8);
   }
}

//***********************************************
void CODE(unsigned char *IP_result)
{
   unsigned char r[33];
   unsigned char  l[33];
   unsigned char t[33];
   unsigned char six_bit[9][7];
   unsigned char four[9];
   int i,j,k,h;

   for(i=1;i<65;i++){
       if(i<33) l[i]=IP_result[i];
       else r[i-32]=IP_result[i];
   }
   for(i=1;i<17;i++){

      for(j=1;j<49;j++){
        k=enlage[j-1];
        IP_result[j]=r[k];
      }
      for(j=1;j<49;j++){
        IP_result[j]=IP_result[j]^subkey[i][j];
        six_bit[(j-1)/6+1][j-(j-1)/6*6]=IP_result[j];
      }
      for(j=1;j<9;j++){
        k=six_bit[j][1]*2+six_bit[j][6];
        h=six_bit[j][2]*8+six_bit[j][3]*4+six_bit[j][4]*2+six_bit[j][5];
        four[j]=mselect[((j-1)*4+k)*16+h];
      }
      for(j=1;j<33;j++){
        k=(j-1)/4;
        h=4-(j-k*4);
        k++;
        t[j]=(four[k]>>h)&1;
      }
      for(j=1;j<33;j++){
        k=signal[j-1];
        IP_result[j]=t[k]^l[j];
        l[j]=r[j];
        r[j]=IP_result[j];
      }
   }
   for(i=1;i<65;i++){
       if(i<33) IP_result[i]=r[i];
       else IP_result[i]=l[i-32];
   }
}

//***********************************************
void DECODE(unsigned char *IP_result)
{
   unsigned char  r[33];
   unsigned char l[33];
   unsigned char t[33];
   unsigned char six_bit[9][7];
   unsigned char four[9];
   unsigned int i,j,k,h;

   for(i=1;i<65;i++){
       if(i<33) r[i]=IP_result[i];
       else l[i-32]=IP_result[i];
   }
   for(i=16;i>0;i--){
      for(j=1;j<49;j++){
        k=enlage[j-1];
        IP_result[j]=l[k]^subkey[i][j];
        six_bit[(j-1)/6+1][j-(j-1)/6*6]=IP_result[j];
      }
      for(j=1;j<9;j++){
        k=six_bit[j][1]*2+six_bit[j][6];
        h=six_bit[j][2]*8+six_bit[j][3]*4+six_bit[j][4]*2+six_bit[j][5];
        four[j]=mselect[((j-1)*4+k)*16+h];
      }
      for(j=1;j<33;j++){
        k=(j-1)/4;
        h=4-(j-k*4);
        k++;
        t[j]=(four[k]>>h)&1;
      }
      for(j=1;j<33;j++){
        k=signal[j-1];
        IP_result[j]=t[k]^r[j];
        r[j]=l[j];
        l[j]=IP_result[j];
      }
   }
   for(i=1;i<65;i++){
       if(i<33) IP_result[i]=l[i];
       else IP_result[i]=r[i-32];
   }
}

//计算KEYA或KEYB
void Cal_Key(unsigned char *SOURCEDATA,unsigned char *KEY)
{
	int i,iTemp;
	unsigned char ucdata[16];
	memcpy(ucdata,SOURCEDATA,8);
	memcpy(ucdata+8,SOURCEDATA,8);
	iTemp = 0;
	for(i=0;i<8;i++)
		iTemp += SOURCEDATA[i];
	i = iTemp % 7;
	memcpy(KEY,ucdata + i,6);
	return;
}

//////////////////////////////////////////////////////////////////////////
// 新加的算KeyA的偏移算法, 将SmartCom411DXQ里面所有的Cal_Key改成Cal_KeyA
void Cal_KeyA(unsigned char *SOURCEDATA, unsigned char *KEY)
{
	int i, iTemp;
	unsigned char ucdata[16];
	memcpy(ucdata, SOURCEDATA, 8);
	memcpy(ucdata + 8, SOURCEDATA, 8);
	iTemp = 0;
	for(i = 0;i < 8; i++)
		iTemp += SOURCEDATA[i] * i;
	i = iTemp % 10;
	memcpy(KEY, ucdata + i, 6);
	return;	
}
//////////////////////////////////////////////////////////////////////////
