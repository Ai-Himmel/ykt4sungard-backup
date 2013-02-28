// XPack.h: interface for the CXPack class.
//
//////////////////////////////////////////////////////////////////////

/***********************************************************************************
  ������־��¼
  ������: ������
  �������� 2004-10-10 15:07:25
  �汾: V1.00 
  ˵��: 
      ���������ϲ���ҵ����صģ������ṩ������CPACK�еĺ�����������Ȼ����C�������
  �Ա�ǰ̨VC���򷽱���ñ��๦�ܡ�ͬʱ����C���������ƣ�
  ������������ʵ���ֱ���CPACK���ݱ��ĺ�����PACK���ĸ�ʽ��ͨ���ϲ�������Э��ת������
  Ϊ�˼�������CPACK�ӿ�ģʽ���ڱ��๹�캯����ֱ��װ��CPACK.DAT�ļ�(��֤ȯCPACK�����ʽ)��
  ���û�и��ļ�����Ҳ����ʾ�����Ա�ֱ��ʹ���µĽṹ�����ļ���
      �ڱ�Э���У������˴��佻���Զ���ı��������ݽṹ����raw data block, ��λͼ����
  �������κ���Ч�ֶΣ�����������Ա����Զ��崫���ļ��������ݵ�Э�顣��ʱ�����ݰ��е�
  �����ֽ���Ͷ��붼�ύ��Э�����߿��ƣ�������ģ�鲻�����κο����ˡ�
      2004-10-14: CYH
      ע�⣺��RAWDATAģʽ�£�����ͽ���е����ݰ����У�ʹ��ST_SDPACK�ṹ����ST_SDPACK::data
  ����Ϊʵ�����ݣ������ֽ��򽻸��ϲ���ƣ�������Ϊ���ݳ��ȵ�ST_SDPACK::usDataLength���ֽ���
  ����Ȼ�ɱ������ת����ST_SDPACK::usDataLengthָ�ľ���ST_SDPACK::data�ĳ��ȣ�����������ĳ��ȣ�����
 ***********************************************************************************/


#if !defined(AFX_XPACK_H_)
#define AFX_XPACK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PackB.h"
#include "PackHandle.h"

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

//����λͼ�Ľ�����־
#define END_FIELDMARK  -1

class XPACK_API CXPack  
{
private:
   CPackHandle phandle;
   
public:
	bool IsValidField(ST_PACKHEAD *phead, char *fieldname);
	bool IsValidField(ST_PACKHEAD *phead, int fidx);

   // ������: HostByteOrder
   // ���  : ������ 2004-10-14 15:50:16
   // ����  : �õ���������е������ֽ���ת��
   // ����  : void 
   // ����  : void *data 
   // ����  : unsigned int datalength
	void HostByteOrder(void *data, unsigned int datalength);

   // ������: GetPackLength
   // ���  : ������ 2004-10-14 15:51:23
   // ����  : �õ�ST_PACK����������
   // ����  : int ����sizeof(ST_PACK)
	int GetPackLength();

   // ������: IsRawDataPack
   // ���  : ������ 2004-10-14 15:52:08
   // ����  : �ж��Ƿ�ΪRAW-DATA Mode
   // ����  : bool 
   // ����  : const ST_PACKHEAD *phead
	bool IsRawDataPack(const ST_PACKHEAD *phead);

   // ������: rev_data
   // ���  : ������ 2004-10-14 15:52:37
   // ����  : ���ݵ��ֽ���ת��
   // ����  : static void 
   // ����  : void *data
   // ����  : unsigned int datalen
	static void rev_data(void *data,unsigned int datalen);

   static char * LRTrim(char *str);

	static unsigned short xmk_crc16(const void *ptr, int count);

   // ������: AddField
   // ���  : ������ 2004-10-11 13:19:51
   // ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ���������ͷphead!=NULL����ͬʱ���ñ�ͷ����Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : char *fieldname(IN): �ֶ�����
   // ����  : double dvalue(IN): �ֶε�ֵ
   // ����  : ST_PACKHEAD *phead(OUT): ��¼����ر���ͷ��
   //          �����ΪNULL����Դ˱�ͷ�е�λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, const char *fieldname, double dvalue, ST_PACKHEAD *phead=NULL);

   // ������: AddField
   // ���  : ������ 2004-10-11 13:21:58
   // ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ���������ͷphead!=NULL����ͬʱ���ñ�ͷ����Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : char *fieldname(IN): �ֶ�����
   // ����  : int ivalue(IN): �ֶε�ֵ
   // ����  : ST_PACKHEAD *phead(OUT): ��¼����ر���ͷ��
   //          �����ΪNULL����Դ˱�ͷ�е�λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, const char *fieldname, int ivalue, ST_PACKHEAD *phead=NULL);

   // ������: AddField
   // ���  : ������ 2004-10-11 13:23:05
   // ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ���������ͷphead!=NULL����ͬʱ���ñ�ͷ����Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : char *fieldname(IN): �ֶ�����
   // ����  : char *data(IN): �ֶε�ֵ�����ֶ�ΪPDL_UCHAR���ͣ�����Ϊ0x????���������ģ����ǽ������0x?????
   // ����  : ST_PACKHEAD *phead(OUT): ��¼����ر���ͷ��
   //          �����ΪNULL����Դ˱�ͷ�е�λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, const char *fieldname, const char *data, ST_PACKHEAD *phead=NULL);

   // ������: AddField
   // ���  : ������ 2004-10-11 13:23:15
   // ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ���������ͷphead!=NULL����ͬʱ���ñ�ͷ����Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : int fidx(IN): ��ֵ���ֶα��
   // ����  : double dvalue(IN): �ֶε�ֵ
   // ����  : ST_PACKHEAD *phead(OUT): ��¼����ر���ͷ��
   //          �����ΪNULL����Դ˱�ͷ�е�λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, int fidx, double dvalue, ST_PACKHEAD *phead=NULL);

   // ������: AddField
   // ���  : ������ 2004-10-11 13:23:26
   // ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ���������ͷphead!=NULL����ͬʱ���ñ�ͷ����Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : int fidx(IN): ��ֵ���ֶα��
   // ����  : int ivalue(IN): �ֶε�ֵ
   // ����  : ST_PACKHEAD *phead(OUT): ��¼����ر���ͷ��
   //          �����ΪNULL����Դ˱�ͷ�е�λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, int fidx, int ivalue, ST_PACKHEAD *phead=NULL);

   // ������: AddField
   // ���  : ������ 2004-10-11 13:23:38
   // ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ���������ͷphead!=NULL����ͬʱ���ñ�ͷ����Ӧ��λͼ
   // ����  : bool ��ֵ�ɹ����
   // ����  : void *prec (OUT): ���ݼ�¼
   // ����  : int fidx(IN): ��ֵ���ֶα��
   // ����  : char *data(IN): �ֶε�ֵ�����ֶ�ΪPDL_UCHAR���ͣ�����Ϊ0x????���������ģ����ǽ������0x?????
   // ����  : ST_PACKHEAD *phead(OUT): ��¼����ر���ͷ��
   //          �����ΪNULL����Դ˱�ͷ�е�λͼ����Ӧ������
   //          ���򣬽�����ֵ����
   bool AddField(void *prec, int fidx, const char *data, ST_PACKHEAD *phead=NULL);

   // ������: CheckValidField
   // ���  : ������ 2004-10-11 13:23:48
   // ����  : ��鱨��ͷ���ж��Ƿ�ָ�����ֶ�����Ϊ��Чֵ
   // ����  : bool ��true����Ч���ֶ����false����Ч���ֶ�����
   // ����  : const ST_PACKHEAD *phead(IN):��صı���ͷ
   // ����  : int fidx��IN����ָ���ֶ�����
	bool CheckValidField(const ST_PACKHEAD *phead, int fidx);

   // ������: FindFieldIndex
   // ���  : ������ 2004-10-10 23:32:29
   // ����  : �����ֶ���Ϊfieldname���ֶα��
   // ����  : int >=0: �ɹ������ظ��ֶα�ţ�<0: �ڶ������û�и����Ƶ��ֶ�
   // ����  : char *fieldname��IN�����ֶ����ƣ�ע���Сд����
   int FindFieldIndex(char *fieldname);

   // ΪJNI�ӿ���string���͵���
	int FindCFieldIndex(const char *fieldname);

   // ������: GetPrintFieldValue
   // ���  : ������ 2004-10-10 23:28:59
   // ����  : �����ݼ�¼prec�У����ָ���ֶ�pfd��ֵ������ʾ���ٸ�ʽ����
   // ����  : char * ���ظ�ʽ�����ֶ�ֵ��==NULL:�Ƿ��ֶ�
   //          ����PDL_UCHAR�������ֶΣ�����0xXX..XX���ַ�������
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : int fidx��IN�����ֶα��
   // ����  : char *pfv��OUT�������������
   //             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
   // ����  : int prec(IN): ����PDL_DOUBLE��Ч�����ڶ��巵�ص�С����λ����
   //          -1: ����%lf����
   char * GetPrintFieldValue(const void *prec, int fidx, char *pfv, int precision=-1);


   // ������: GetFieldValueD
   // ���  : ������ 2004-10-11 14:55:09
   // ����  : �����ݼ�¼�У���ȡ�ֶ���Ϊfieldname��ֵ����double��ʽ���أ�
   // ����  : double �����ֶε�doubleֵ
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : char *fieldname��IN�����ֶ�����
   double GetFieldValueD(const void *prec, const char *fieldname);

   // ������: GetFieldValueD
   // ���  : ������ 2004-10-11 14:55:04
   // ����  : �����ݼ�¼�У���ȡ�ֶα��Ϊfidx��ֵ����double��ʽ���أ�
   // ����  : double �����ֶε�doubleֵ
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : int fidx��IN�����ֶα��
   double GetFieldValueD(const void *prec, int fidx);

   // ������: GetFieldValueI
   // ���  : ������ 2004-10-11 14:54:58
   // ����  : �����ݼ�¼�У���ȡ�ֶ���Ϊfieldname��ֵ����int��ʽ���أ�
   // ����  : int �����ֶε�����ֵ
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : char *fieldname��IN�����ֶ�����
   int GetFieldValueI(const void *prec, const char *fieldname);

   // ������: GetFieldValueI
   // ���  : ������ 2004-10-11 14:54:45
   // ����  : �����ݼ�¼�У���ȡ�ֶα��Ϊfidx��ֵ����int��ʽ���أ�
   // ����  : int �����ֶε�����ֵ
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : int fidx��IN�����ֶα��
   int GetFieldValueI(const void *prec, int fidx);
   
   
   // ������: GetFieldValue
   // ���  : ������ 2004-10-10 23:04:20
   // ����  : �����ݼ�¼�У���ȡ�ֶ���Ϊfieldname��ֵ�����ַ�����ʽ���أ�
   // ����  : char * �����ֶε�ֵ��==NULL:��ʾ��Ч���ֶ���
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : char *fieldname��IN�����ֶ�����
   // ����  : char *value��OUT�������ص��ֶ�ֵ�����ַ�����ʽ��ʾ��
   //             ���ΪPDL_UCHAR����Ϊ��BIN�ֶε�����ֵ��Ӧ����BIN�ֽ����ݣ�
   //                 ΪPDL_INT,��Ϊ%d��ʽ���أ�
   //                 ΪPDL_DOUBLE�ֶΣ���Ϊ%lf��ʽת��Ϊ�ַ�����
   //             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
   char * GetFieldValue(const void *prec, const char *fieldname, char *value);

   // ������: GetFieldValue
   // ���  : ������ 2004-10-10 23:00:30
   // ����  : �����ݼ�¼�У���ȡ�ֶα��Ϊfidx��ֵ�����ַ�����ʽ���أ�
   // ����  : char * �����ֶε�ֵ��==NULL:��ʾ��Ч���ֶα��
   //          ע�⣺�����ֶ�ΪPDL_UCHAR���򷵻ص�������raw-data���Ʒ��ص�
   // ����  : void *prec��IN�������ݼ�¼
   // ����  : int fidx��IN�����ֶα��
   // ����  : char *value��OUT�������ص��ֶ�ֵ�����ַ�����ʽ��ʾ��
   //             ���ΪPDL_UCHAR����Ϊ��BIN�ֶε�����ֵ��Ӧ����BIN�ֽ�����
   //                 ΪPDL_INT,��Ϊ%d��ʽ���أ�
   //                 ΪPDL_DOUBLE�ֶΣ���Ϊ%lf��ʽת��Ϊ�ַ�����
   //             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
   char * GetFieldValue(const void *prec, int fidx, char *value);


   // ������: GetFieldValue
   // ���  : ������ 2004-10-10 23:04:20
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
   // ����  : char *value��OUT�������ص��ֶ�ֵ�����ַ�����ʽ��ʾ��
   //             ���ΪPDL_UCHAR����Ϊ��BIN�ֶε�����ֵ��Ӧ����BIN�ֽ����ݣ�
   //                 ΪPDL_INT,��Ϊ%d��ʽ���أ�
   //                 ΪPDL_DOUBLE�ֶΣ���Ϊ%lf��ʽת��Ϊ�ַ�����
   //             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
   int IGetFieldValue(const void *prec, const char *fieldname, char *value);

   // ������: GetFieldValue
   // ���  : ������ 2004-10-10 23:00:30
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
   // ����  : char *value��OUT�������ص��ֶ�ֵ�����ַ�����ʽ��ʾ��
   //             ���ΪPDL_UCHAR����Ϊ��BIN�ֶε�����ֵ��Ӧ����BIN�ֽ�����
   //                 ΪPDL_INT,��Ϊ%d��ʽ���أ�
   //                 ΪPDL_DOUBLE�ֶΣ���Ϊ%lf��ʽת��Ϊ�ַ�����
   //             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
   int IGetFieldValue(const void *prec, int fidx, char *value);
   
   // ������: GetPackDef
   // ���  : ������ 2004-10-10 22:53:58
   // ����  : �õ������������ݱ��Ľṹ����
   // ����  : const ST_PDATALIST *: ���ر��Ľṹ�������ݵ�λ��
   // ����  : int &ilastvfidx��OUT�������һ����Ч�ֶ�/��������ı��
   const ST_PDATALIST * GetPackDef(int &ilastvfidx);

   // ������: GetValidFieldCount
   // ���  : ������ 2004-10-10 22:47:49
   // ����  : �������ݱ���ͷ���õ���Ч��������/�ֶ���
   // ����  : int ��Ч��������
   // ����  : const ST_PACKHEAD *phead��IN�������ݱ���ͷ
	int GetValidFieldCount(const ST_PACKHEAD *phead);

   // ������: GetValidFieldInfo
   // ���  : ������ 2004-10-10 22:46:17
   // ����  : ���ݵ�ǰ���ݱ���ͷ�õ���Ч��vfnumber�ֶεĶ�����Ϣ
   // ����  : const ST_PDATALIST *��������Ч�ֶεĶ�����Ϣ�� NULL - ʧ�ܣ�������Ч�ֶθ�����
   // ����  : const ST_PACKHEAD *phead(IN): �����ͳ�Ƶ����ݱ���ͷ
   // ����  : int vfnumber(IN)�� ��0��ʼ���ֶ���Ч�к�
	const ST_PDATALIST * GetValidFieldInfo(const ST_PACKHEAD *phead,int vfnumber);

   // ������: OverwritePack
   // ���  : ������ 2004-10-10 22:39:12
   // ���  : ������ 2004-10-10 19:12:22
   // ����  : ��Ŀ�걨�����ݼ�¼�пյ����ݣ���Դ�����е���Ч������д��������ֻ�Ե���¼��Ч��
   //          ���Ŀ�걨���к�����Ч�����ݣ�����Դ���ĸ���
   // ����  : void 
   // ����  : ST_PACKHEAD *dhead(OUT): Ŀ�걨��ͷ
   // ����  : void *dpack��OUT����Ŀ�걨�ļ�¼
   // ����  : const ST_PACKHEAD *shead(IN): Դ����ͷ
   // ����  : const void *spack��IN����Դ���ļ�¼
	void OverwritePack(ST_PACKHEAD *dhead, void *dpack, const ST_PACKHEAD *shead,const void *spack);

   // ������: ClearParmBit
   // ���  : ������ 2004-10-10 22:34:22
   // ����  : ���ñ��fidxָ�����ֶε���Ӧλͼ�������
   // ����  : int <0: ʧ�ܣ��Ƿ��ֶ�λͼ���룻>=0: �ɹ�����Ϊ���ֶα��
   // ����  : ST_PACKHEAD *phead (OUT): �����õ����ݱ���ͷ
   // ����  : int fidx��IN������ָ��Ҫ������ֶΣ��������
	int ClearParmBit(ST_PACKHEAD *phead,int fidx);

   // ������: SetParmBit
   // ���  : ������ 2004-10-10 22:31:12
   // ����  : ���ñ��fidxָ�����ֶε���Ӧλͼ��������
   // ����  : int <0: ʧ�ܣ��Ƿ��ֶ�λͼ���룻>=0: �ɹ�����Ϊ���ֶα��
   // ����  : ST_PACKHEAD *phead (OUT): �����õ����ݱ���ͷ
   // ����  : int fidx��IN������ָ�����ֶΣ��������
	int SetParmBit(ST_PACKHEAD *phead,int fidx);

   // ������: EmulateEncodeLength
   // ���  : ������ 2004-10-10 22:26:51
   // ����  : �����Ѿ����õ�λͼ������һ����¼�������ݿ飩���ռ�õı��뻺�����ĳ���
   // ����  : int �����ر�����Ҫ���Ļ���������
   // ����  : const ST_PACKHEAD *phead(IN): �Ѿ�����λͼ������ݱ���ͷ
	int EmulateEncodeLength(const ST_PACKHEAD *phead);

   // ������: DecodeRow
   // ���  : ������ 2004-10-10 22:21:37
   // ����  : ���ݱ���ͷphead�����뻺����ebuf���н��룬���뵽������pdata��
   // ����  : int
   /* 
         >=0:�ɹ������ر���ռ�õĳ��ȣ�
         <0:����ʧ�� 
            -1: ����λͼ����(��δ�����λͼ����); 
            -2: �������ֶ����ݳ�������;
            -10: ���������Ȳ���
   */
   // ����  : ST_PACKHEAD *phead (IN): �����λͼ��
   // ����  : void *ebuf��IN�������뻺����
   // ����  : int eblen��IN�������뻺�����ĳ���
   // ����  : void *pdata��OUT�������ڴ�Ž��������
	int DecodeRow(const ST_PACKHEAD *phead, const void *ebuf, int eblen, void *pdata);

   // ������: DecodeHead
   // ���  : ������ 2004-10-10 22:10:29
   // ����  : �����뻺�����н��뵽��ͷ��
   // ����  : int >0:����ɹ������ر��볤�� ��<0 - ����������̫С
   // ����  : void *buf [IN] : ���뻺���� 
   // ����  : int blen [IN] : ���뻺��������
   // ����  : ST_PACKHEAD *pHead [OUT]: ��ͷָ��
	int DecodeHead(const void *buf, int blen, ST_PACKHEAD *pHead);

   // ������: EncodeRow
   // ���  : ������ 2004-10-10 21:49:11
   // ����  : �������ݱ���ͷ��������pdata���б��룬����������ŵ�ebuf�С�
   //          ��������ͷ�е�λͼ��������Чλͼ�������������Ķ�����ֶ����ݱ��룻
   //          ���������Чλͼ��Ϊ�գ������raw-data���룬��֧��raw-dataЭ�飨�Զ�������Э�飩
   // ����  : int >0�������ɹ�������ʵ�ʱ���ʹ�õĳ��ȣ�
   //             <=0, ����ʧ�ܣ�
   //                  0: phead->recCount<=0��pdata==NULL
   //                 -1: ����λͼ����(��δ�����λͼ����); 
   //                 -10: ��ͨ����µĻ���������
   //                 -11: �Զ���������µĻ��������Ȳ���
   // ����  : const ST_PACKHEAD *phead��IN��������ʹ�õ����ݱ���ͷ
   // ����  : const void *pdata��IN�������������������
   // ����  : void *ebuf��OUT�������ڴ�ű������Ļ�����
   // ����  : int ebsize��IN�������뻺��������󳤶�
   int EncodeRow(const ST_PACKHEAD *phead, const void *pdata, void *ebuf, int ebsize);

   // ������: EncodeHead
   // ���  : ������ 2004-10-10 21:38:51
   // ����  : ����ͷ���ݱ��뵽ָ���Ļ�����
   // ����  : int >0:����ɹ������ر����ʹ�ñ��뻺�����ĳ���
   // ����  : ST_PACKHEAD *pHead ��IN�� ������İ�ͷ����
   // ����  : void *buf ��OUT����ű���Ļ�����
	int EncodeHead(const ST_PACKHEAD *pHead, void *buf);

   // ������: ResetPackHead
   // ���  : ������ 2004-10-10 21:01:05
   // ����  : ���ݱ����Ļ���Լ���������ݱ���ͷ������
   //          ����вο�����ͷ������������Ҫ�󣬶Զ�ȡ�����������ݵ�ʱ��
   //          ��Ҫ���ϴ��յ���Ӧ����ͷ�е�hook���Ƶ����Ա���ͷ�У�
   //          ������Ӧ����ͷ����������ͷ��Ϊ�ο�����ͷ����Ҫ���ͻ��������userdata��
   //          ���Ƶ���Ӧ������ñ���ͷ�У�
   //          ���������������������ϲ������ƣ����ﶼһ����Ϊ0������λͼ��
   // ����  : void 
   // ����  : ST_PACKHEAD *phead
   // ����  : const ST_PACKHEAD *refphead=NULL
	void ResetPackHead(ST_PACKHEAD *phead, const ST_PACKHEAD *refphead=NULL);

   // ������: Initialize
   // ���  : ������ 2004-10-10 19:04:25
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
	int Initialize(const char *szPackDefFile="cpack.dat");

	explicit CXPack(const char *szPackDefFile="cpack.dat");  // ȱʡװ��"cpack.dat"

	virtual ~CXPack();


   // ������: SetPackHead
   // ���  : ������ 2005-9-20 10:52:45
   // ����  : ͨ�������ܣ�����һ��XPack��ͷ����Ҫ������������Ч�ֶ�λͼ��ͬʱfirstflag=1;nextflag=0; ����������Ϊ0
   // ����  : int : 0 
   // ����  : ST_PACKHEAD *head[OUT]: �����õİ�ͷ
   // ����  : int recCount[IN]: ��¼����
   // ����  : int retCode[IN]: ������
   // ����  : ... [IN]: ��F_xxxxxָ����Ч�ֶ�λͼ(���)����END_FIELDMARK(-1)����
	int SetPackHead(ST_PACKHEAD *head,int recCount,int retCode,...);

};

#undef XPACK_API

#endif // !defined(AFX_XPACK_H__5F12942D_DCBC_4055_A561_7031DBD4BCB8__INCLUDED_)
