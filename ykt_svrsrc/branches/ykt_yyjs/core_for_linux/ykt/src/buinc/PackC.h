/********************************************************************
	created:	2004/10/12
	created:	12:10:2004   1:08
	filename: 	e:\proj\n_dce\xpack\packc.h
	file path:	e:\proj\n_dce\xpack
	file base:	packc
	file ext:	h
	author:		CHENYH
	
	purpose:	
      ģ��������޸�����Ϊ2005-3-25
   
      2005-6-3 11:06:02 ����ע��
      ��CPACK�ĵ���ģʽ���ݣ��滻ԭ����CPACK.Cģ�飩����֤ԭϵͳ��������ʹ�ã�
   ͬʱ�����˼����������Բ��ֺ������˹��ܵ���ǿ��
      ���ڲ��������XPACK�ṹ�����ļ���ʽ������ڲ������Ĵ���������ȫ�ı����

      Ϊ�˼���ԭCPACK���÷�ʽ��ģ���ڲ�������һ��ȫ�ֵ�CXPack���ʵ������Ϊ
      ȱʡʵ����

*********************************************************************/
#ifndef __PACKC_H_
#define __PACKC_H_

#ifdef PACKC_EXPORTS
#define PACKC_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define PACKC_API __declspec(dllimport)
#else
#define PACKC_API 
#endif
#endif

#ifdef __cplusplus
extern "C" {
#else
   typedef unsigned char bool;
   #define true 1
   #define false 0
#endif
// ����ΪC/C++���ܵ��õ�һЩ����������

// ������: LoadPackDefFile
// ���  : ������ 2005-6-3 11:10:04
//         �������� New
// ����  : ����װ��XPACK�ṹ�����ļ���
//         ���ϵͳֱ��ʹ�õ�ǰĿ¼�µ�cpack.dat��ΪXPACK�ṹ�����ļ���
//         ����Բ����ñ������� 
// ����  : PACKC_API int 
//           >=0  - �ɹ� �������һ����Ч�ֶκţ�
//            -1  - ����ʽ�ļ����ܴ򿪣�
//            -2  - ָ���ļ���ʽ���󣻲��ܱ����汾����� 
// ����  : char *szPackDefFile��XPACK��ʽ�����ļ���
PACKC_API int LoadPackDefFile(char *szPackDefFile);


// ������: GetDefaultXPack
// ���  : ������ 2005-6-3 11:19:05
//         �������� New
// ����  : �õ��ڲ�ȱʡ��XPack����ʵ��
// ����  : PACKC_API void *�����������ͷ�����Ϊ�˶�ԭ���ĳ�����Ҫ������XPack.h��ͷ�ļ�
//         �����������XPack.h�ļ�������ϣ��ʹ��ǿ���CXPack�ڵķ�����
//         ���ڷ���ֵ������ǿ��ΪCXPack *�����������µ��ã�
//         CXPack *pXPack = (CXPack *)GetDefaultXPack(); ����
PACKC_API void * GetDefaultXPack();


// ������: Reverse
// ���  : ������ 2005-6-3 11:25:33
//         ԭ�к��� Old
// ����  : ��buf�����ݽ���XPACK/CPACK�ڲ�������ֽ���ת��
//         ���������еĻ����������Little-Endian���͵ģ�����ת����
//         ��ΪBig-Endian���͵ģ������ֽ���ת����
//         ������ʵ���岻����ȫ�˽⣬
// ����  : PACKC_API void 
// ����  : void *buf ��Ҫת��������λ��
// ����  : int len   ���ݵ��ֽ���
PACKC_API void Reverse(void *buf,int len);


// ������: Reserve
// ���  : ������ 2005-6-3 11:31:36
//         ԭ�к��� Old
// ����  : ������������ʹ�ã�������Ϊ�˼���CPACK�Ķ��庯����
//          ʵ�ʹ��ܺ�Reverse��ͬ��
// ����  : PACKC_API void 
// ����  : void *buf
// ����  : int len
PACKC_API void Reserve(void *buf,int len);


// ������: DecodeHead
// ���  : ������ 2005-6-3 11:33:21
//         ԭ�к��� Old
// ����  : �Դ�����루���������յ���XPACK���ݣ�����XPACKͷ�����ݵĽ���
// ����  : PACKC_API int ��sizeof(ST_PACKHEAD) ��<0 ʧ�� ����������̫С
// ����  : void *buf [IN] : ���뻺���� ��Ӧ��Ϊ���յ������ݿ�ʼλ�ã�
// ����  : int len [IN] : �������ݳ��ȣ������յ������ݳ��ȣ�
// ����  : ST_PACKHEAD *pHead [OUT]: ��ͷָ��
// ����  : char *eMsg������ʧ��ʱ�򣬴��ʧ����Ϣ
PACKC_API int DecodeHead(unsigned char *buf,int len,ST_PACKHEAD *pHead,char *eMsg);


// ������: DecodeBufHead
// ���  : ������ 2005-6-3 13:03:49
//         ԭ�к��� Old
// ����  : ʵ�ʾ���DecodeHead,���������˵��ò�����
//         �������е�XPACK/CPACK�İ�ͷ���ݽ��뵽pPack�еİ�ͷ
// ����  : PACKC_API int��sizeof(ST_PACKHEAD) ��<0 ʧ�� ����������̫С
// ����  : void *buf [IN] : ���뻺���� ��Ӧ��Ϊ���յ������ݿ�ʼλ�ã�
// ����  : int len [IN] : �������ݳ��ȣ������յ������ݳ��ȣ�
// ����  : ST_CPACK *pPack [OUT]: ST_CPACK��ָ�룬�������ݴ�ŵ�Ŀ�� 
// ����  : char *eMsg [OUT]: ����ʧ��ʱ�򣬴��ʧ����Ϣ
PACKC_API int DecodeBufHead(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg);


// ������: DecodeAPack
// ���  : ������ 2005-6-3 13:09:49
//         ԭ�к��� Old
// ����  : ����������еİ��岿��������¼����
// ����  : PACKC_API int 
/*  
      >=0:�ɹ������ر���ռ�õĳ��ȣ�
      <0:����ʧ�� 
         -1: ����λͼ����(��δ�����λͼ����); 
         -2: �������ֶ����ݳ�������;
         -10: ���������Ȳ���
*******************************************************/
// ����  : char *buf [IN]: ����������ݿ飨ע�������ݵ�ƫ��λ�ã�
// ����  : int len [IN]: δ��������ݿ鳤�� ��ע��۳�֮ǰ�Ѿ�����ռ�õ����ݿ鳤�ȣ�
// ����  : ST_PACKHEAD *phead [IN]: �Ѿ�����������İ�ͷ
// ����  : ST_PACK *pack [OUT]: ��Ž�������ļ�¼���壬������֧�ֶ�ST_SDPACK�Ľ��룩
// ����  : char *eMsg [OUT]: ����ʧ��ʱ�򣬴��ʧ����Ϣ
PACKC_API int DecodeAPack(char *buf,int len,ST_PACKHEAD *phead,ST_PACK *pack,char *eMsg);


// ������: DecodeBuf
// ���  : ������ 2005-6-3 13:17:36
//         ԭ�к��� Old
// ����  : �����DecodeHead��DecodeAPack����������ݿ���뵽ST_CPACK�У�����ͷ�Ͱ����׼�¼��
// ����  : PACKC_API int 
/*
         >0: ����ռ�ã�����ɣ��ı���鳤��
         =0: �������
*/
// ����  : char *buf [IN]: ������ģ������룩���ݿ飨�����ǰ�����ͷ����˾��ǽ��յ������ݿ���ʼλ�ã�
// ����  : int len [IN] : �������ݳ��ȣ������յ������ݳ��ȣ�
// ����  : ST_CPACK *pPack [OUT]: ���������ST_CPACK����
// ����  : char *eMsg [OUT]: ����ʧ��ʱ�򣬴��ʧ����Ϣ
PACKC_API int DecodeBuf(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg);


// ������: DecodeBufWithArray
// ���  : ������ 2005-6-3 13:41:07
//         ԭ�к��� Old
// ����  : �����������������뵽һ��ST_CPACK��ST_PACK��¼���У�����еĻ���
// ����  : PACKC_API int 
/*
         >0: ����ռ�ã�����ɣ��ı���鳤��
         =0: �������
*/
// ����  : char *buf [IN]: ������ģ������룩���ݿ飨�����ǰ�����ͷ����˾��ǽ��յ������ݿ���ʼλ�ã�
// ����  : int len [IN] : �������ݳ��ȣ������յ������ݳ��ȣ�
// ����  : ST_CPACK *pPack [OUT]: ���������ST_CPACK����
// ����  : ST_PACK *packArray [OUT]: ��������ĺ��¼���ݻ��壬��ΪNULLʱ���򲻽���ڶ�����ʼ�ļ�¼
// ����  : int *recCount [OUT]: ���ؽ�������ļ�¼��
// ����  : char *eMsg [OUT]: ����ʧ��ʱ�򣬴��ʧ����Ϣ
PACKC_API int DecodeBufWithArray(unsigned char *buf,int len,ST_CPACK *pPack,ST_PACK *packArray,int *recCount,char *eMsg);


// ������: EmulateEncodeLen
// ���  : ������ 2005-6-3 13:50:30
//         �������� New
// ����  : ���ݰ�ͷphead�е�λͼ������һ�����ݼ�¼������Ҫ��Ļ���ռ䳤��
// ����  : PACKC_API int ��Ҫ���һ����¼�ı������ݵĻ���ռ䳤�ȣ���������ͷ���ֵĳ��ȣ�
// ����  : ST_PACKHEAD *phead [IN]: ��������İ�ͷ
PACKC_API int EmulateEncodeLen(ST_PACKHEAD *phead);


// ������: ModifyHead
// ���  : ������ 2005-6-3 13:55:31
//         ԭ�к��� Old
// ����  : ����ͷ���ֱ��뵽���뻺����
// ����  : int �� sizeof(ST_PACKHEAD)
// ����  : ST_PACKHEAD *pHead ��IN�� ��ͷ����
// ����  : unsigned char *buf ��OUT����ű���Ļ�����
PACKC_API int ModifyHead(ST_PACKHEAD *phead,unsigned char *buf);


// ������: EncodeRow
// ���  : ������ 2005-6-3 13:58:55
//         ԭ�к��� Old
// ����  : ��һ�����ݼ�¼pRowPack���루����������뻺����
// ����  : PACKC_API int 
/* ****** Updated by CHENYH at 2005-6-3 14:01:08 ****** 
            >0: ���ظü�¼�������ռ�õı��뻺�泤�ȣ�
            ��0: ����ʧ�ܣ�����buf==NULL �� pHead->recCount<=0
                 ������Ϊ���볤��>8K
*******************************************************/
// ����  : ST_PACKHEAD *pHead [IN]: ���ڱ���İ�ͷ
// ����  : ST_PACK *pRowPack [IN]: һ�����ݼ�¼ (֧�ֶ�ST_SDPACK�ı���)
// ����  : unsigned char *buf [OUT]: ���뻺��
// ����  : int *len [OUT]: ���볤��
// ����  : char *eMsg  --- û����
PACKC_API int EncodeRow(ST_PACKHEAD *pHead,ST_PACK *pRowPack,unsigned char *buf,int *len,char *eMsg);


// ������: EncodeBuf
// ���  : ������ 2005-6-3 14:13:52
// ����  : ��һ��ST_CPACK�����������뻺����
// ����  : PACKC_API int �����ر����ĳ��ȣ������뻺����ռ�õĿռ䣩
// ����  : ST_CPACK *pPack [IN]: һ���������ST_CPACK
// ����  : unsigned char *buf [OUT]:  ���뻺��
// ����  : int *len [OUT]: ���ر����ĳ���
// ����  : char *eMsg --- û����
PACKC_API int EncodeBuf(ST_CPACK *pPack,unsigned char *buf,int *len,char *eMsg);


// ������: EncodeBufArray
// ���  : ������ 2005-6-3 14:44:19
// ����  : һ���ԶԵ���¼����¼���ݵı��뺯��
// ����  : PACKC_API int�� ���ر����ĳ��ȣ������뻺����ռ�õĿռ䣩
// ����  : ST_CPACK *pPack [IN]: �������ST_CPACK
// ����  : ST_PACK *pArray [IN]: �������ST_PACK���飬����ΪNULL����ST_CPACK�б�ǿ�и�Ϊ����¼���޼�¼��
//         ע�⣺��ΪST_SDPACK��ļ�¼����ôҲ������ST_PACK���ȶ��루������ΪST_PACK��������Ϊ���棩
// ����  : unsigned char *buf [OUT]:  ���뻺��
// ����  : int *len [OUT]: ���ر����ĳ���
// ����  : char *eMsg --- û����
PACKC_API int EncodeBufArray(ST_CPACK *pPack,ST_PACK *pArray,unsigned char *buf,int *len,char *eMsg);


// ������: SetParmBit
// ���  : ������ 2005-6-3 14:53:47
// ����  : �ڰ�ͷ������ָ���ֶε�λͼ
// ����  : PACKC_API int  0: ����ȷ���ֶκţ����ʼ���ı��ĸ�ʽ������1:�ɹ�
// ����  : ST_PACKHEAD *ph [OUT]: �����õİ�ͷ���ڲ���λͼ��
// ����  : int fidx [IN]: �ֶε�F_  ֵ ���μ�cpack.h�еĶ��壩
PACKC_API int SetParmBit(ST_PACKHEAD *ph,int fidx);


// ������: ClearParmBit
// ���  : ������ 2005-6-3 14:56:31
// ����  : �ڰ�ͷ�����ָ���ֶε�λͼ
// ����  : PACKC_API int  0: ����ȷ���ֶκţ����ʼ���ı��ĸ�ʽ������1:�ɹ�
// ����  : ST_PACKHEAD *ph[OUT]: �����õİ�ͷ���ڲ���λͼ��
// ����  : int fidx [IN]: �ֶε�F_  ֵ ���μ�cpack.h�еĶ��壩
PACKC_API int ClearParmBit(ST_PACKHEAD *ph,int fidx);


// ������: SetErrorPack
// ���  : ������ 2005-6-3 14:58:57
// ����  : ���ô��󷵻����ݰ���������inPack���ð�ͷ
//          ͬʱ��outPack��ͷ�е�
//             firstflag=1;  ��ʾΪ�װ�����
//             nextflag=0;   ��ʾ�޺�����
//             recCount=1; ����¼���ݰ�
//          ���⽫�׼�¼�е�vsmess�ֶ��м��������Ϣ�������ö�Ӧ��λͼ
// ����  : PACKC_API int :1
// ����  : ST_CPACK *inPack [IN]: ��inPack�İ�ͷ�е�userdata,hook,addr,RequestType,firstflag���Ƶ�outPack��
// ����  : ST_CPACK *outPack [OUT]: �����õķ��ذ�����
// ����  : char *emsg [IN]: ������Ϣ�ַ���
// ����  : int eCode [IN]: ������ ��ֵ��outPack�İ�ͷ�е�retCode��
PACKC_API int SetErrorPack(ST_CPACK *inPack,ST_CPACK *outPack,char *emsg,int eCode);


// ������: SetErrorPack2
// ���  : ������ 2005-6-3 14:59:05
// ����  : ���ô��󷵻����ݰ����������ݰ�ͷ
//          ͬʱ��outPack��ͷ�е�
//             firstflag=1;  ��ʾΪ�װ�����
//             nextflag=0;   ��ʾ�޺�����
//             recCount=1; ����¼���ݰ�
//          ���⽫�׼�¼�е�vsmess�ֶ��м��������Ϣ�������ö�Ӧ��λͼ
// ����  : PACKC_API int ��1
// ����  : ST_CPACK *outPack [OUT]: �����õķ��ذ�����
// ����  : char *emsg [IN]: ������Ϣ�ַ���
// ����  : int eCode [IN]: ������ ��ֵ��outPack�İ�ͷ�е�retCode��
PACKC_API int SetErrorPack2(ST_CPACK *outPack,char *emsg,int eCode);


// ������: SetNormalPack
// ���  : ������ 2005-6-3 14:59:12
// ����  : ���������inPack�����������ķ��ذ�outPack
//          ͬʱ��outPack��ͷ�е�
//             firstflag��inPack�е�firstflag��ͬ
// ����  : PACKC_API int :1
// ����  : ST_CPACK *inPack [IN]: ��inPack�İ�ͷ�е�userdata,hook,addr,RequestType,firstflag���Ƶ�outPack��
// ����  : ST_CPACK *outPack [OUT]: �����õķ��ذ�����
// ����  : int nextflag [IN]: �Ƿ��к�����. 0-�ޣ�������
// ����  : int recCount [IN]: �����ݰ������ж������ݼ�¼��
PACKC_API int SetNormalPack(ST_CPACK *inPack,ST_CPACK *outPack,int nextflag,int recCount);


// ������: SetNormalPack2
// ���  : ������ 2005-6-3 14:59:18
// ����  : �����������ݰ�outPack ����հ�ͷ�е�userdata,hook�ȣ�
//          ͬʱ��outPack��ͷ�е�
//             firstflag=1;  ��ʾΪ�װ�����
//             nextflag=0;   ��ʾ�޺�����
// ����  : PACKC_API int ��1
// ����  : ST_CPACK *outPack [OUT]: �����õ����ݰ�
// ����  : unsigned int reqtype [IN]: ���������ܺ�
// ����  : int recCount [IN]: �����ݰ������ж������ݼ�¼��
PACKC_API int SetNormalPack2(ST_CPACK *outPack,unsigned int reqtype,int recCount);  // update reqtype (unsigned char ) with (unsigned int) 20050325


// ������: ShowPackHead
// ���  : ������ 2005-6-3 15:43:09
// ����  : ��buf�������ͷ�еĲ��������ڵ���
// ����  : PACKC_API int ��1
// ����  : char *buf [OUT]: ������д�ɴ�ӡ�İ�ͷ�еĲ�����ע��Ҫ�����㹻�Ŀռ�
// ����  : ST_PACKHEAD *phead [IN]: �����Եİ�ͷ
PACKC_API int ShowPackHead(char *buf,ST_PACKHEAD *phead);


// ������: AddFieldValue
// ���  : ������ 2005-6-3 15:46:12
//         �������� New
// ����  : ��ST_CPACK�е������ַ���ָ���ֶν��и�ֵ����������λͼ��
// ����  : PACKC_API bool ���������Ϊfalse��˵��û���ҵ�ָ�����ֶ�
// ����  : ST_CPACK *pack [OUT]: ����ֵST_CPACK
// ����  : const char *fieldname [IN]: �ֶε�����
// ����  : const char *fieldvalue [IN]: ���ַ�����ʾ���ֶ�ֵ ע�������unsigned char ���ֶΣ��������0x��ʼ��ʾ��ֵ������ͱ�ֱ�Ӹ���
PACKC_API bool AddFieldValue(ST_CPACK *pack,const char *fieldname,const char *fieldvalue);


// ������: AddFieldValueD
// ���  : ������ 2005-6-3 15:55:40
//         �������� New
// ����  : ��ST_CPACK�е������ַ���ָ���ֶν��и�ֵ����������λͼ��
// ����  : PACKC_API bool ���������Ϊfalse��˵��û���ҵ�ָ�����ֶ�
// ����  : ST_CPACK *pack [OUT]: ����ֵST_CPACK
// ����  : const char *fieldname [IN]: �ֶε�����
// ����  : const double dfvalue [IN]: �ø����ʾ���ֶ�ֵ��������ֶβ���double�ͣ��򾭹�ת����������Ӧ������
PACKC_API bool AddFieldValueD(ST_CPACK *pack,const char *fieldname,const double dfvalue);


// ������: AddFieldValueI
// ���  : ������ 2005-6-3 15:56:20
//         �������� New
// ����  : ��ST_CPACK�е������ַ���ָ���ֶν��и�ֵ����������λͼ��
// ����  : PACKC_API bool ���������Ϊfalse��˵��û���ҵ�ָ�����ֶ�
// ����  : ST_CPACK *pack [OUT]: ����ֵST_CPACK
// ����  : const char *fieldname [IN]: �ֶε�����
// ����  : const int ifvalue [IN]: ��������ʾ���ֶ�ֵ��������ֶβ���int�ͣ��򾭹�ת����������Ӧ������
PACKC_API bool AddFieldValueI(ST_CPACK *pack,const char *fieldname,const int ifvalue);


// ������: FindFieldIndex
// ���  : ������ 2005-8-2 22:13:11
// ����  : �����ֶ����õ���ǰ���Ľṹ�У��Ը��ֶε��ֶα�ż�F_ ֵ
// ����  : int >=0: �ɹ������ظ��ֶα�ţ�<0: �ڶ������û�и����Ƶ��ֶ�
// ����  : const char *fieldname [IN]: �ֶ�����ע���Сд����
PACKC_API int FindFieldIndex(const char *fieldname);

#ifdef __cplusplus
}
#endif

#undef PACKC_API 

#endif

