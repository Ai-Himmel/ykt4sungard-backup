/********************************************************************
	created:	2004/09/23
	created:	23:9:2004   23:25
	filename: 	e:\proj\goldmem\ksbcc\packbase\packhandle.h
	file path:	e:\proj\goldmem\ksbcc\packbase
	file base:	packhandle
	file ext:	h
	author:		������
	
	purpose:	��������������CPACK��Ļ����������ͣ�
            ע�⣺iMode=0 Ϊ����ԭ����CPACK�����ʽ
                 ����Ϊ�µĴ����ʽ
*********************************************************************/
// PackHandle.h: interface for the CPackHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKHANDLE_H__5FABD1A8_F02E_485D_9CA8_7825CB168A2C__INCLUDED_)
#define AFX_PACKHANDLE_H__5FABD1A8_F02E_485D_9CA8_7825CB168A2C__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PackB.h"

#ifdef XPACK_INC
#define XPACK_API 
#else
#ifdef PACKC_EXPORTS
#define XPACK_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define XPACK_API __declspec(dllimport)
#else
#define XPACK_API 
#endif
#endif
#endif

 
class XPACK_API CPackHandle  
{
public:
   bool bReverse;                   // �Ƿ��ڴ������Ҫ��ת�ֽڣ��ڴ���а���BigEndian���򣨶�int/double��
   unsigned char iMode;             // 0: ֤ȯ���н��׵ı��뷽ʽ��1: �µı��뷽ʽ
   unsigned char iVersionID;        // ��������ڱȽ�
   char version[20];                // ���ڱ���汾������
   int  iLastPField;                // ���һ����Ч�ֶζ�����
   ST_PDATALIST pdlist[PARMBITS];   // ST_PACK �ṹ������
   int  nPackLength;                // ST_PACK ����һ����¼�ĳ���

public:
	void HostByteOrder(void *data, unsigned int datalength);

   // ������: GetPackLength
   // ���  : ������ 2004-10-11 16:58:55
   // ����  : ȡ������ST_PACK�ĳ���
   // ����  : int ST_PACK�ĳ��ȣ����� sizeof(ST_PACK)
	int GetPackLength();


   // ������: CheckValidField
   // ���  : ������ 2004-10-11 16:59:45
   // ����  : ��λͼ���м��ָ�����ֶα���Ƿ�Ϊ��Ч�ֶ�
   // ����  : bool 
   // ����  : const unsigned char *parmbits(IN): λͼ��
   // ����  : int fidx��IN����ָ���ֶα��
	bool CheckValidField(const unsigned char *parmbits, int fidx);

   // ������: GetPackDef
   // ���  : ������ 2004-10-10 22:53:58
   // ����  : �õ������������ݱ��Ľṹ����
   // ����  : const ST_PDATALIST *: ���ر��Ľṹ�������ݵ�λ��
   // ����  : int &ilastvfidx��OUT�������һ����Ч�ֶ�/��������ı��
	const ST_PDATALIST * GetPackDef(int &ilastvfidx);

   // ������: OverwritePack
   // ���  : ������ 2004-10-10 19:12:22
   // ����  : ��Ŀ�걨�����ݼ�¼�пյ����ݣ���Դ�����е���Ч������д��������ֻ�Ե���¼��Ч��
   //          ���Ŀ�걨���к�����Ч�����ݣ�����Դ���ĸ���
   // ����  : void 
   // ����  : unsigned char *dparmbits��OUT����Ŀ�걨�ĵ�λͼ��
   // ����  : void *dpack��OUT����Ŀ�걨�ļ�¼
   // ����  : const unsigned char *sparmbits��IN����Դ���ĵ�λͼ��
   // ����  : const void *spack��IN����Դ���ļ�¼
   void OverwritePack(unsigned char *dparmbits, void *dpack,const unsigned char *sparmbits,const void *spack);

   // ������: GetValidFieldCount
   // ���  : ������ 2004-10-9 17:47:56
   // ����  : ����λͼ���õ���Ч��������/�ֶ���
   // ����  : int ��Ч��������
   // ����  : const unsigned char *parmbits������λͼ��
	int GetValidFieldCount(const unsigned char *parmbits);

   // ������: GetValidFieldInfo
   // ���  : ������ 2004-10-9 17:45:04
   // ����  : ���ݵ�ǰλͼ�õ���Ч��vfnumber�ֶεĶ�����Ϣ
   // ����  : const ST_PDATALIST *��������Ч�ֶεĶ�����Ϣ�� NULL - ʧ�ܣ�������Ч�ֶθ�����
   // ����  : const unsigned char *parmbits ��λͼ��
   // ����  : int vfnumber�� ��0��ʼ���ֶ���Ч�к�
	const ST_PDATALIST * GetValidFieldInfo(const unsigned char *parmbits,int vfnumber);

   // ������: ResetParmBits
   // ���  : ������ 2004-9-30 18:23:08
   // ����  : ����ָ����λͼ����ȫ�������λͼ
   // ����  : void 
   // ����  : unsigned char *parmbits(OUT): ��Ҫ����յ�λͼ��   
   void ResetParmBits(unsigned char *parmbits);

   // ������: xmk_crc16
   // ���  : ������ 2004-10-6 23:46:39
   // ����  : ͳ��һ���ڴ���crc16ֵ��ר�����ڸ������ݵ�������
   // ����  : unsigned short: �������õ�crc16
   // ����  : void *ptr: һ���ڴ��
   // ����  : int count: �ڴ����ֽ���
	static unsigned short xmk_crc16(const void *ptr, int count);

   // ������: SetPBIndex
   // ���  : ������ 2004-10-6 23:09:42
   // ����  : �����ֶ���ţ����û�������ݱ���λͼ����Ӧ���ֶ�λͼ
   // ����  : int �� �ɹ����򷵻�>=0��fidx���ֶ���ţ���ʧ�ܣ��򷵻�<0
   // ����  : unsigned char *parmbits(OUT): ���޸ĵ�λͼ��
   // ����  : int fidx��IN�������û�������ֶ����
   // ����  : bool bToSet��IN����true�����ã�false�����
	int SetPBIndex(unsigned char *parmbits,int fidx,bool bToSet=true);


   // ������: GetPrintFieldValue
   // ���  : ������ 2004-9-30 20:20:58
   // ����  : �����ݼ�¼prec�У����ָ���ֶ�pfd��ֵ������ʾ���ٸ�ʽ����
   // ����  : char * ���ظ�ʽ�����ֶ�ֵ��==NULL:�Ƿ��ֶ�
   //          ����PDL_UCHAR�������ֶΣ�����0xXX..XX���ַ����ͷ���
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : int fidx��IN�����ֶα��
   // ����  : char *pfv��OUT�������������
   //             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
   // ����  : int prec(IN): ����PDL_DOUBLE��Ч�����ڶ��巵�ص�С����λ����
   //          -1: ����%lf����
   char * GetPrintFieldValue(const void *prec, int fidx, char *pfv, int precision=-1);

   // ������: GetFieldValueD
   // ���  : ������ 2004-9-30 20:03:49
   // ����  : �����ݼ�¼�У���ȡ�ֶ���Ϊfieldname��ֵ����double��ʽ���أ�
   // ����  : double �����ֶε�doubleֵ
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : char *fieldname��IN�����ֶ�����
	double GetFieldValueD(const void *prec, const char *fieldname);

   // ������: GetFieldValueI
   // ���  : ������ 2004-9-30 20:02:56
   // ����  : �����ݼ�¼�У���ȡ�ֶ���Ϊfieldname��ֵ����int��ʽ���أ�
   // ����  : int �����ֶε�����ֵ
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : char *fieldname��IN�����ֶ�����
	int GetFieldValueI(const void *prec, const char *fieldname);

   // ������: GetFieldValue
   // ���  : ������ 2004-9-30 20:01:12
   // ����  : �����ݼ�¼�У���ȡ�ֶ���Ϊfieldname��ֵ�����ַ�����ʽ���أ�
   // 2006-6-1 9:47:08 Ϊ����ߴ���Ч�ʣ��ܹ�ͬʱ���ظ��ֶε����͸��ϲ�
   // ���� : int �ֶ����ͣ�
   //          PDL_CHAR=1,          ��ͨ�ַ���ģʽ��Լ�����ȣ��������255
   //          PDL_VCHAR=2,         �䳤�ַ����������255
   //          PDL_UCHAR=3,         ���ڴ�Ŷ��������ݵ��ֶΣ�����Ȩ�޵�
   //          PDL_INT=4,           �����ֶΣ���������64λ���У�long����64λ������32λ������Ϊ32λ������int���ǹ̶��ģ���˱�Э���в��ٲ���long��
   //          PDL_DOUBLE=5         double�����ֶ�
   ////         // ����  : char * �����ֶε�ֵ��==NULL:��ʾ��Ч���ֶ���
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : char *fieldname��IN�����ֶ�����
   // ����  : char *value��OUT�������ص��ֶ�ֵ�����ַ�����ʽ��ʾ�����ΪPDL_UCHAR����Ϊ��BIN�ֶε�����ֵ��Ӧ����BIN�ֽ�����
   //             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
   int GetFieldValue(const void *prec, const char *fieldname, char *value);

   // ������: GetFieldValueD
   // ���  : ������ 2004-9-30 20:00:26
   // ����  : �����ݼ�¼�У���ȡ�ֶα��Ϊfidx��ֵ����double��ʽ���أ�
   // ����  : double �����ֶε�doubleֵ
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : int fidx��IN�����ֶα��
	double GetFieldValueD(const void *prec, int fidx);

   // ������: GetFieldValueI
   // ���  : ������ 2004-9-30 19:59:19
   // ����  : �����ݼ�¼�У���ȡ�ֶα��Ϊfidx��ֵ����int��ʽ���أ�
   // ����  : int �����ֶε�����ֵ
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : int fidx��IN�����ֶα��
	int GetFieldValueI(const void *prec, int fidx);

   // ������: GetFieldValue
   // ���  : ������ 2004-9-30 19:45:03
   // ����  : �����ݼ�¼�У���ȡ�ֶα��Ϊfidx��ֵ�����ַ�����ʽ���أ�
   // 2006-6-1 9:47:08 Ϊ����ߴ���Ч�ʣ��ܹ�ͬʱ���ظ��ֶε����͸��ϲ�
   // ���� : int �ֶ����ͣ�
   //          PDL_CHAR=1,          ��ͨ�ַ���ģʽ��Լ�����ȣ��������255
   //          PDL_VCHAR=2,         �䳤�ַ����������255
   //          PDL_UCHAR=3,         ���ڴ�Ŷ��������ݵ��ֶΣ�����Ȩ�޵�
   //          PDL_INT=4,           �����ֶΣ���������64λ���У�long����64λ������32λ������Ϊ32λ������int���ǹ̶��ģ���˱�Э���в��ٲ���long��
   //          PDL_DOUBLE=5         double�����ֶ�
   ////         // ����  : char * �����ֶε�ֵ��==NULL:��ʾ��Ч���ֶ���
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : int fidx��IN�����ֶα��
   // ����  : char *value��OUT�������ص��ֶ�ֵ�����ַ�����ʽ��ʾ�����ΪPDL_UCHAR����Ϊ��BIN�ֶε�����ֵ��Ӧ����BIN�ֽ�����
   //             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
	int GetFieldValue(const void *prec, int fidx, char *value);

   // ������: AddField
   // ���  : ������ 2004-9-30 18:03:15
   // ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : char *fieldname(IN): �ֶ�����
   // ����  : double dvalue(IN): �ֶε�ֵ
   // ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
   //          �����ΪNULL����Դ˱��λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, const char *fieldname, double dvalue, unsigned char *parmbits=NULL);
   // ������: AddField
   // ���  : ������ 2004-9-30 18:07:30
   // ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : char *fieldname(IN): �ֶ�����
   // ����  : int ivalue(IN): �ֶε�ֵ
   // ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
   //          �����ΪNULL����Դ˱��λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, const char *fieldname, int ivalue, unsigned char *parmbits=NULL);
   // ������: AddField
   // ���  : ������ 2004-9-30 18:08:26
   // ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : char *fieldname(IN): �ֶ�����
   // ����  : char *data(IN): �ֶε�ֵ�����ֶ�ΪPDL_UCHAR���ͣ�����Ϊ0x????���������ģ����ǽ������0x?????
   // ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
   //          �����ΪNULL����Դ˱��λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, const char *fieldname, const char *data, unsigned char *parmbits=NULL);


   // ������: AddField
   // ���  : ������ 2004-9-30 18:09:32
   // ����  : �Լ�¼prec�еı��Ϊfidx���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : int fidx(IN): ��ֵ���ֶα��
   // ����  : double dvalue(IN): �ֶε�ֵ
   // ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
   //          �����ΪNULL����Դ˱��λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, int fidx, double dvalue, unsigned char *parmbits=NULL);
   // ������: AddField
   // ���  : ������ 2004-9-30 18:11:45
   // ����  : �Լ�¼prec�еı��Ϊfidx���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : int fidx(IN): ��ֵ���ֶα��
   // ����  : int ivalue(IN): �ֶε�ֵ
   // ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
   //          �����ΪNULL����Դ˱��λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, int fidx, int ivalue, unsigned char *parmbits=NULL);
   // ������: AddField
   // ���  : ������ 2004-9-30 18:12:29
   // ����  : �Լ�¼prec�еı��Ϊfidx���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : int fidx(IN): ��ֵ���ֶα��
   // ����  : char *data(IN): �ֶε�ֵ�����ֶ�ΪPDL_UCHAR���ͣ�����Ϊ0x????���������ģ����ǽ������0x?????
   // ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
   //          �����ΪNULL����Դ˱��λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, int fidx, const char *data, unsigned char *parmbits=NULL);


   // ������: EmulateEncodeLength
   // ���  : ������ 2004-9-30 18:13:31
   // ����  : �����Ѿ����õ�λͼ������һ����¼���ռ�õı��뻺�����ĳ���
   // ����  : int �����ر�����Ҫ���Ļ���������
   // ����  : unsigned char *parmbits��IN�����Ѿ����õ����ݼ�¼λͼ��
	int EmulateEncodeLength(const unsigned char *parmbits);


   // ������: ClearParmBitByFIndex
   // ���  : ������ 2004-9-30 18:16:02
   // ����  : ���ñ��fidxָ�����ֶε���Ӧλͼ�������
   // ����  : int <0: ʧ�ܣ��Ƿ��ֶ�λͼ���룻>=0: �ɹ�����Ϊ���ֶα��
   // ����  : unsigned char *parmbits��IN/OUT����λͼ��
   // ����  : int fidx��IN���� �ֶα��
	int ClearParmBitByFIndex(unsigned char *parmbits, int fidx);
   // ������: ClearParmBit
   // ���  : ������ 2004-9-30 18:18:33
   // ����  : ����λͼ�����ʾ���ֶε���Ӧλͼ�������
   // ����  : int <0: ʧ�ܣ��Ƿ��ֶ�λͼ���룻>=0: �ɹ�����Ϊ���ֶα��
   // ����  : unsigned char parmbits��IN/OUT����λͼ��
   // ����  : int fpb��IN���� �ֶ�λͼ����
	int ClearParmBit(unsigned char *parmbits, int fpb);


   // ������: SetParmBitByFIndex
   // ���  : ������ 2004-9-30 18:15:44
   // ����  : ���ñ��fidxָ�����ֶε���Ӧλͼ��������
   // ����  : int <0: ʧ�ܣ��Ƿ��ֶ�λͼ���룻>=0: �ɹ�����Ϊ���ֶα��
   // ����  : unsigned char *parmbits��IN/OUT����λͼ��
   // ����  : int fidx��IN���� �ֶα��
	int SetParmBitByFIndex(unsigned char *parmbits,int fidx);
   // ������: SetParmBit
   // ���  : ������ 2004-9-30 18:22:17
   // ����  : ����λͼ�����ʾ���ֶε���Ӧλͼ��������
   // ����  : int <0: ʧ�ܣ��Ƿ��ֶ�λͼ���룻>=0: �ɹ�����Ϊ���ֶα��
   // ����  : unsigned char *parmbits��IN/OUT����λͼ��
   // ����  : int fpb��IN���� �ֶ�λͼ����
	int SetParmBit(unsigned char *parmbits,int fparmbit);



   // ������: FindFieldIndex
   // ���  : ������ 2004-9-30 18:24:18
   // ����  : �����ֶ���Ϊfieldname���ֶα��
   // ����  : int >=0: �ɹ������ظ��ֶα�ţ�<0: �ڶ������û�и����Ƶ��ֶ�
   // ����  : char *fieldname��IN�����ֶ�����
	int FindFieldIndex(const char *fieldname);


   // ������: DecodeRow
   // ���  : ������ 2004-9-30 18:25:48
   // ����  : ����λͼ��parmbits�����뻺����ebuf���н��룬���뵽�����ݼ�¼prec��
   // ����  : int
   /* 
         >=0:�ɹ������ر���ռ�õĳ��ȣ�
         <0:����ʧ�� 
            -1: ����λͼ����(��δ�����λͼ����); 
            -2: �������ֶ����ݳ�������;
            -10: ���������Ȳ���
   */
   // ����  : unsigned char *parmbits(IN): �����λͼ��
   // ����  : void *ebuf��IN�������뻺����
   // ����  : int eblen��IN�������뻺�����ĳ���
   // ����  : void *prec��OUT�������ڴ�Ž�������ݼ�¼
	int DecodeRow(const unsigned char *parmbits, const void *ebuf, int eblen, void *prec);

   // ������: EncodeRow
   // ���  : ������ 2004-9-30 18:27:08
   // ����  : ����λͼ��parmbits�����ݼ�¼prec���б��룬����ṹ��ŵ����뻺����ebuf
   // ����  : int 
   /* 
         >=0:�ɹ������ر���ռ�õĳ��ȣ�
         <0:����ʧ�� 
            -1: ����λͼ����(��δ�����λͼ����); 
            -10: ���������Ȳ���
   */
   // ����  : unsigned char *parmbits(IN): �����λͼ��
   // ����  : void *prec��IN��������������ݼ�¼
   // ����  : void *ebuf��OUT�������ڴ�ű������Ļ�����
   // ����  : int ebsize��IN�������뻺��������󳤶�
	int EncodeRow(const unsigned char *parmbits, const void *prec, void *ebuf,int ebsize);


   // ������: DecodeHead
   // ���  : ������ 2004-9-24 16:32:51
   // ����  : �����뻺�����н��뵽��ͷ��
   // ����  : int >0:����ɹ������ر��볤�� ��<0 - ����������̫С
   // ����  : void *buf [IN] : ���뻺���� 
   // ����  : int blen [IN] : ���뻺��������
   // ����  : ST_PACKHEAD *pHead [OUT]: ��ͷָ��
	int DecodeHead(const void *buf, int blen, ST_PACKHEAD *pHead);
   // ������: EncodeHead
   // ���  : ������ 2004-9-24 16:30:57
   // ����  : ����ͷ���ݱ��뵽ָ���Ļ�����
   // ����  : int >0:����ɹ������ر����ʹ�ñ��뻺�����ĳ���
   // ����  : ST_PACKHEAD *pHead ��IN�� ��ͷ����
   // ����  : void *buf ��OUT����ű���Ļ�����
	int EncodeHead(const ST_PACKHEAD *pHead, void *buf);


   // ������: P_Index
   // ���  : ������ 2004-9-30 18:43:59
   // ����  : �ֶ�λͼ����ת��Ϊ�ֶα��
   // ����  : int >=0���Ϸ����ֶΣ������ֶα�ţ�<0:�Ƿ����ֶ�λͼ����
   // ����  : int parmbit���ֶ�λͼ����
	int P_Index(int parmbit);

   // ������: Initialize
   // ���  : ������ 2004-9-30 18:39:25
   // ����  : ��ʼ�������ݰ������װ�����ݰ��ṹ�����ļ�
   // ����  : int 
   //           >=0  - �ɹ� ���ذ汾�ţ�
   //            -1  - ����ʽ�ļ����ܴ򿪣�
   //            -2  - ָ���ļ���ʽ���󣻲��ܱ����汾����� 
   // ����  : char *szPackDefFile������ʽ�ļ�����
   /* ****** designed by CHENYH at 2004-9-23 23:48:16 ****** 
   ����ʽ�ļ��ĸ�ʽ���壺
      int i1;  ���ļ����ɵĻ���������1�ı�ʾֵ�����Ȿ�ļ�����ʹ�õĻ��������ɵĻ��������ʽ�Ĳ�ͬ���½ṹ����
      int iMode;
      char version[20];
      int iVersionID;
      int iLastPField;
      ST_PDATALIST pdlist[255];
   */
	int Initialize(const char *szPackDefFile="pack.dat");

	CPackHandle();
	virtual ~CPackHandle();

   static void rev_data(void *data,unsigned int datalen);
	static void Hex2Buffer(unsigned char *buf,int len,char *hex);
	static char * LRTrim(char *str);

private:
   
   // ������: GetPrintFieldValue
   // ���  : ������ 2004-9-30 20:18:02
   // ����  : �����ݼ�¼prec�У����ָ���ֶ�pfd��ֵ������ʾ���ٸ�ʽ����
   // ����  : char * ���ظ�ʽ�����ֶ�ֵ��==NULL:�Ƿ��ֶ�
   //          ����PDL_UCHAR�������ֶΣ�����0xXX..XX���ַ����ͷ���
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : ST_PDATALIST *pfd��IN����ָ�����ֶζ���
   // ����  : char *pfv��OUT�������������
   // ����  : int precision(IN): ����PDL_DOUBLE��Ч�����ڶ��巵�ص�С����λ����
   //          -1: ����%lf����
   char * GetPrintFieldValue(const void *prec, const ST_PDATALIST *pfd, char *pfv,int precision);
   int GetFieldValue(const void *prec, const ST_PDATALIST *pfd, char *value);
	bool SetFieldValue(void *prec, int fidx, char *data);

	bool SetFieldValue(void *prec, const ST_PDATALIST *pfd, double dvalue);
	bool SetFieldValue(void *prec, const ST_PDATALIST *pfd, int ivalue);
	bool SetFieldValue(void *prec, const ST_PDATALIST *pfd, char *data);

	int GetEncodeFieldLength(const ST_PDATALIST *pfd);
	int DecodeSingleField(const ST_PDATALIST *pfd, const void *pbuf, void *pdata);
	int EncodeSingleField(const ST_PDATALIST *pfd, const void *pdata, void *pbuf);
};

#undef XPACK_API

#endif // !defined(AFX_PACKHANDLE_H__5FABD1A8_F02E_485D_9CA8_7825CB168A2C__INCLUDED_)
