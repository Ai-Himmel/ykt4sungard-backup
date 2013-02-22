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
    char pkgtyp[1];         //�������� 0Ϊ8583����1Ϊ��8583��
    char msgtyp[4];	    // 
    char prccde[6];	    		//	880108  488833 488833
    char acqInstID[8];      //4446301 �յ�������ͳһ��Ϊ8λ,����󲹿ո�
    char termID[8];	    //	COLLEGE2
    char trcno[6];          //�ҵ���ˮ��   ����6λǰ��0
    char custyp[2];         //OV �ʻ�����
    char cusidt[25];        //У԰������   ����󲹿ո�
    char apcode[2];         //01       01_RB,03_AC
    char srvuID[8];	    //44630021	��˾����
    char rspcde[2];	    //	00
    char pkgseq[2];         //01      ������� 
    char filler[6];         //null    ������  
    char msgLen[4];         //������  ����4λǰ��0
    char msg[MAXBUFSIZE];   //����    ������
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


