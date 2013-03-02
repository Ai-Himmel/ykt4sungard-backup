/* message size */
#define  STAND    0   
//#define	 MAXMSGSIZE  2560
/* transaction type */
#define  BANK_QUERY_REQ            0
#define  BANK_QUERY_RSP           (BANK_QUERY_REQ + 1)
#define  BANK_TRANS_REQ            2
#define  BANK_TRANS_RSP           (BANK_TRANS_REQ + 1)
#define  BANK_DETRANS_REQ        4
#define  BANK_DETRANS_RSP       (BANK_DETRANS_REQ + 1)

#define  TRANS_TYPE 8
#define  transTypeSize 4
#define  SHM_TXNDSC_IDX 0x00
#define  MAXBUFSIZE 2500
//#define  8583_

#ifdef WIN32
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
//#pragma pack(push,1)
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif

typedef struct
{
	char length[4];
    char pkgtyp[1];         //报文种类 0为8583包，1为非8583包
    char msgtyp[4];	    // 
    char prccde[6];	    		//	880108  488833 488833
    char acqInstID[8];      //4446301 收单机构号统一定为8位,不足后补空格
    char termID[8];	    //	COLLEGE2
    char trcno[6];          //我的流水号   不足6位前补0
    char custyp[2];         //OV 帐户种类
    char cusidt[25];        //校园卡卡号   不足后补空格
    char apcode[2];         //01       01_RB,03_AC
    char srvuID[8];	    //44630021	公司代码
    char rspcde[2];	    //	00
    char pkgseq[2];         //01      报文序号 
    char filler[6];         //null    附加域  
    char msgLen[4];         //包长度  不足4位前补0
    char msg[MAXBUFSIZE];   //包体    数据区
}H_MSG8583;


#ifdef WIN32
#pragma pack(pop)
#else
#ifdef __GNUC__
//#pragma pack(pop)
#else
#pragma options align=reset
#endif
#endif
#undef __PACKED__





/*******************************************************************/


