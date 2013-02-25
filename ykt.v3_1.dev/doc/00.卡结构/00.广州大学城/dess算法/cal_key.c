
void des_code(unsigned char *dkey,unsigned char *jmdata,unsigned char *result,unsigned char k);
void Cal_Key(unsigned char *sourcedata,unsigned char *KEY);
void TriDes(unsigned char *dkey, unsigned char *jmdata, unsigned char *result, unsigned char k);

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
unsigned char select[513]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
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
        four[j]=select[((j-1)*4+k)*16+h];
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
        four[j]=select[((j-1)*4+k)*16+h];
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

/////////////////////////////////////////////////////////////////////////////////////////////
/*
void CalOffset(unsigned char *sourcedata,unsigned char *KEY)
{
	int i,iTemp;
	unsigned char ucdata[16];
	memcpy(ucdata,sourcedata,8);
	memcpy(ucdata+8,sourcedata,8);
	iTemp = 0;
	for(i=0;i<8;i++)
		iTemp += sourcedata[i]*i;
	i = iTemp %10;
	memcpy(KEY,ucdata+i,6);
	return;
}
*/

void CalOffset(unsigned char *SOURCEDATA,unsigned char *KEY)
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

/////////////////////////////////////////////////////////////////////////////////////////////
void CalKeyA(unsigned char *ucSerialNo,unsigned char *ucWorkKey,unsigned char *ucKeyA)
{
	unsigned char ucRawData[256];
	unsigned char ucDesData[256];
	int i;
	memcpy(ucRawData,ucSerialNo,4);
	for(i=0;i<4;i++)
		ucRawData[i+4] = ~ucRawData[i];
	des_code(ucWorkKey,ucRawData,ucDesData,'0');
	CalOffset(ucDesData,ucKeyA);
	return ;
}

