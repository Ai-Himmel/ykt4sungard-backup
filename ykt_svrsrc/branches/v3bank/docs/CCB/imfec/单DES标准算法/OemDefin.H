///////////////////////////////////////////////////////////////////////////////////////
//OemDefin.H内定义了公用部分接口                                                     //
//供圈存机1.50和2.00及后续版本使用,由于07卡标准不兼容以往版本,因此部分函数分版本号   //
//简略词NCBS=>NewCapecBaseServer;NCMi=>NewCapecMiFare                                //
//新开普电子金融组                      2007-08-09首次正式定义                   //
//新开普电子金融组 当前版本最后一次修改 2007-08-13                               //
///////////////////////////////////////////////////////////////////////////////////////
#ifndef         _NewCapec_OEM_DEFINE_BY_YUCH_20070809_2D0_H
#define         _NewCapec_OEM_DEFINE_BY_YUCH_20070809_2D0_H

//////////////////////////////签约前定义的版本号2.00Ver///////////////////////////////
#ifndef         NewCapec_OEM_Ver2D0
#define         NewCapec_OEM_Ver2D0    200
#endif

////////////////数据基本类型///////////////////
#ifndef         ULONG
#define			ULONG	unsigned long
#endif
#ifndef         UINT
#define			UINT	unsigned int
#endif
#ifndef         BYTE
#define			BYTE	unsigned char
#endif
#ifndef         DWORD
#define			DWORD	unsigned long
#endif
#ifndef         WORD
#define			WORD	unsigned short
#endif
#ifndef         UINT32
#define			UINT32	unsigned long
#endif
#ifndef         UINT16
#define			UINT16	unsigned short
#endif
#ifndef         UINT8
#define			UINT8	unsigned char
#endif

////////////////函数基本返回值类型///////////////////
#define         NC_True            1        //是,真   
#define         NC_False           0        //否,假




////////////////其它相关的函数/////////////////////

/////Ascii("0-F")到Bcd码,pAcsBuf数据串,ascLen长度,pBcd转换后的数据,
//如果ascLen%2!=0则需要启用填充功能,rightFill0[NC_True右填充0,NC_False左填充0],
int  NCBS_Asc0_FToBcd(BYTE *pAscBuf,int ascLen,BYTE *pBcdBuf,BYTE rightFill0);
/////Bcd码到Ascii("0-F"),pBcd数据串,bcdLen长度,pAcsii转换后的数据,acsiiLen要转换的长度要求bcdLen*2-1<acsiiLen<=bcdLen*2,
//左取LeftFirst[NC_True左取,NC_False右取]
int  NCBS_BcdToAsc0_F(BYTE *pBcdBuf,int bcdLen,BYTE *pAscBuf,int ascLen,BYTE LeftFirst);

////////////////和加密相关的函数///////////////////
//单DES8个字节64BIT加密 pKey08为8位的密钥,pBufS08为8位数据源,pBufD08为8位加密结果  
int  NCBS_Des08_Encrypt(BYTE *pKey08,BYTE *pBufS08,BYTE *pBufD08);
//单DES8个字节64BIT解密 pKey08为8位的密钥,pBufS08为8位数据源,pBufD08为8位解密结果  
int  NCBS_Des08_Decryptor(BYTE *pKey08,BYTE *pBufS08,BYTE *pBufD08);

//Ansi98(单DES8个字节64BIT)加密 pKey08为8位的密钥,pBankCardNo20为前16位必须有效不足右补空格的20位卡号,
// bankCardLen为银行卡的实际长度16<=bankCardLen<=19
// pBufS08为6位有效密码右补2位空格的源密码,pBankPass08为前6位有效的8位密码,pBufD08为8位加密结果
int  NCBS_Des08_Ansi98Encrypt(BYTE *pKey08,BYTE *pBankCardNo20,int bankCardLen,BYTE *pBankPass08,BYTE *pBufD08);
//Ansi98(单DES8个字节64BIT)解密 pKey08为8位的密钥,pBankCardNo20为前16位必须有效不足右补空格的20位卡号,
// bankCardLen为银行卡的实际长度16<=bankCardLen<=19
// pBufS08为6位有效密码右补2位空格的源密码,pBufS08为8位数据源,pBufS08为需要解密的数据源,pBankPass08为前6位有效的8位密码结果
int  NCBS_Des08_Ansi98Decryptor(BYTE *pKey08,BYTE *pBankCardNo20,int bankCardLen,BYTE *pBufS08,BYTE *pBankPass08);

//Ansi98(单DES8个字节64BIT)Mac计算 pKey08为8位的密钥,pBufS数据源缓冲区,
// begin为从第几位开始计算len长度,pMacD08为8位计算结果
int  NCBS_Des08_Ansi99New(BYTE *pKey08,BYTE *pBufS,int begin,int len,BYTE *pMacD08);
//Ansi98(单DES8个字节64BIT)Mac计算 pKey08为8位的密钥,pBufS数据源缓冲区,
// begin为从第几位开始计算len长度,pMacS08为8位原Mac,pMacD08为本次生成的8位计算结果
int  NCBS_Des08_Ansi99Check(BYTE *pKey08,BYTE *pBufS,int begin,int len,BYTE *pMacS08,BYTE *pMacD08);

#endif  //#ifndef _NewCapec_OEM_DEFINE_BY_YUCH_20070809_2D0_H
