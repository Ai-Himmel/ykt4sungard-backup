

/***********************************************************************************
  ������־��¼
  ������: ������
  �������� 2003-1-20 15:18:06
  �汾: V2.00 - CT�汾 
  ˵��: ���汾�Ǵ��н���ϵͳ�ϵ�CTPACK
 ***********************************************************************************/


#ifndef __CTPACK_H
#define __CTPACK_H

#include "cpack.h"

#ifdef CTPACK_EXPORTS
#define CTPACK_API __declspec(dllexport)
#else
#define CTPACK_API __declspec(dllimport)
#endif

#define CTPACKVER  231      // 2xxΪ���а汾����
#define CTPACKDATE 20021129

   /* ���´����������ֽڶ���ʹ�õ� */
#ifndef WIN32
#ifndef __GNUC__
#define __PACKED__
#pragma options align=packed
#else
#define __PACKED__	__attribute__ ((packed))
#pragma pack(push,1)
#endif
#else
#define __PACKED__ 
#pragma pack(push,1)
#endif


typedef struct st_hookc
{
    unsigned int	UserID;					/* �����ߵ�ID����*/
	char hostname[33];						/* ������ */
	char queuename[33];						/* ������ */
	unsigned int	queuetype;				/* �������� */
}__PACKED__ ST_HOOKC;

/* 
	��ͷ�ṹ
*/
typedef struct st_packheadc
{
	unsigned int	RequestType;
	unsigned char	firstflag;				/* �Ƿ��һ�������װ�����*/
	unsigned char	nextflag;					/* �Ƿ����������*/
	unsigned int	recCount;					/* �����ļ�¼��*/
	unsigned int	retCode;					/* ���ش���*/
	
	ST_ADDR			addr;						/* �����ŵĵ�ַ��6���ӽڣ�*/
	ST_HOOKC       hook;	                    /*                    */
	unsigned int   userdata;					/*					*/

	unsigned char ParmBits[32];
}__PACKED__ ST_PACKHEADC;


typedef struct st_ctpack
{
   ST_PACKHEADC head;
   ST_PACKDATA	pack;
}__PACKED__ ST_CPACKC;


#ifdef __cplusplus
extern "C" {
#endif

#ifndef WIN32
#ifndef __GNUC__
#pragma options align=reset
#else
#pragma pack(pop)
#endif
#else
#pragma pack(pop)
#endif

CTPACK_API int  CTPackDllDate(int dversion=CTPACKVER);


//���ĳ���ֶε�λͼ, 
// ��ʵ��ʹ�����ƺ�û���ô�
//��ڲ�����head����ͷ
//          fieldParam����Ҫ������ֶε�λͼ
//����ֵ���ɹ���TRUE
//        ʧ�ܣ�FALSE
CTPACK_API bool ClearParmBitC(ST_PACKHEADC *head, int fieldid);

//����ĳ���ֶε�λͼ
//��ڲ�����head����ͷ
//          fieldid����Ҫ���õ��ֶε�λͼ
//����ֵ���ɹ���TRUE
//        ʧ�ܣ�FALSE
CTPACK_API bool SetParmBitC(ST_PACKHEADC *head, int fieldid);

CTPACK_API BOOL DecodeBufC(unsigned char *buf,int len,ST_CPACKC *pPack,char *eMsg);
CTPACK_API BOOL DecodeBufWithArrayC(unsigned char *buf,int len,ST_CPACKC *pPack,ST_PACKDATA *packArray,
                        int *recCount,char *eMsg);
CTPACK_API BOOL EncodeBufC(ST_CPACKC *pPack,unsigned char *buf,int *len,char *eMsg);
CTPACK_API BOOL EncodeBufArrayC(ST_CPACKC *pPack,ST_PACKDATA *pArray,unsigned char *buf,int *len,char *eMsg);

#ifdef __cplusplus
}
#endif

#endif
