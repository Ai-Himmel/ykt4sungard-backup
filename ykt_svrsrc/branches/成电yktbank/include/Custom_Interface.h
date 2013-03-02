/***************************************************************/
/* �Զ�����������ӿ�ͷ�ļ�                                    */
/*                                                             */
/* �ļ���:      Custom_Interface.h                             */
/*                                                             */
/* ����Ա:      ���ٽ�                                         */
/*                                                             */
/* ��������:    2005.04.19                                     */
/***************************************************************/


#define  _OS_LINUX_

#ifndef _CUSTOM_INTERFACE_H_
#define _CUSTOM_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined _OS_WIN32_
#define  FUNCTION_DECLARE(returnType)  extern __declspec(dllimport) returnType
#endif

#if defined _OS_LINUX_
#define FUNCTION_DECLARE(returnType)   extern returnType
#endif
//#define  FUNCTION_DECLARE(returnType)  extern __declspec(dllimport) returnType


/*********************�������Ͷ���*********************/
//��������ֵ
typedef  unsigned int   CI_RV;


/***************************�ӿڶ���*********************************************************/


/*������ӿڶ��忪ʼ*/

/********************************************************************************************/
/*�� �� ����    CI_SymEncrypt                                                               */
/*����������    �ԳƼ���                                                                    */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_SymEncrypt(
              int           nFunction,      //��������ҵ�����ݣ�һ��ҵ�����ݶ�Ӧһ���Գ���Կ��
              unsigned char  *pEntity,       //�Է�ʵ��ı�ţ������Ľ����ĸ�ʵ�干��
              unsigned char  *pPlainData,
              unsigned int  nPlainLength,
              unsigned char  *pCipherData,
              unsigned int  *pnCipherLength
              )  ;

/********************************************************************************************/
/*�� �� ����    CI_SymDecrypt                                                               */
/*����������    �Գƽ���                                                                    */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_SymDecrypt(
              int           nFunction,      //��������ҵ�����ݣ�һ��ҵ�����ݶ�Ӧһ���Գ���Կ��
              unsigned char  *pEntity,       //�Է�ʵ��ı�ţ������������ĸ�ʵ�壩
              unsigned char  *pCipherData,
              unsigned int  nCipherLength,
              unsigned char  *pPlainData,
              unsigned int  *pnPlainLength
              ) ;

/********************************************************************************************/
/*�� �� ����    CI_RSAPubKeyEncrypt                                                         */
/*����������    RSA��Կ����                                                                 */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAPubKeyEncrypt(
              unsigned char  *pEntity,       //ʹ���ĸ�ʵ��Ĺ�Կ����
              unsigned char  *pPlainData,
              unsigned int  nPlainLength,
              unsigned char  *pCipherData,
              unsigned int  *pnCipherLength
              ) ;


/********************************************************************************************/
/*�� �� ����    CI_RSAPriKeyDecrypt                                                         */
/*����������    RSA˽Կ����                                                                 */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAPriKeyDecrypt(
              unsigned char  *pEntity,      //ʹ���ĸ�ʵ���˽Կ����
              unsigned char  *pCipherData,
              unsigned int  nCipherLength,
              unsigned char  *pPlainData,
              unsigned int  *pnPlainLength
              ) ;

/********************************************************************************************/
/*�� �� ����    CI_RSAPriKeyEncrypt                                                         */
/*����������    RSA˽Կ����                                                                 */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAPriKeyEncrypt(
              unsigned char  *pEntity,      //ʹ���ĸ�ʵ���˽Կ����
              unsigned char  *pPlainData,
              unsigned int  nPlainLength,
              unsigned char  *pCipherData,
              unsigned int  *pnCipherLength
              ) ;

/********************************************************************************************/
/*�� �� ����    CI_RSAPubKeyDecrypt                                                         */
/*����������    RSA��Կ����                                                                 */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAPubKeyDecrypt(
              unsigned char  *pEntity,       //ʹ���ĸ�ʵ��Ĺ�Կ����
              unsigned char  *pCipherData,
              unsigned int  nCipherLength,
              unsigned char  *pPlainData,
              unsigned int  *pnPlainLength
              ) ;

/********************************************************************************************/
/*�� �� ����    CI_RSASign                                                                  */
/*����������    ��������ǩ��                                                                */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSASign(
              unsigned char  *pEntity,      //ʹ���ĸ�ʵ���˽Կǩ�����������ĸ�ʵ���ǩ��
              unsigned char  *pInData,
              unsigned int  nInDataLength,
              unsigned char  *pSignature,
              unsigned int  *pnSignatureLength
          ) ;

/********************************************************************************************/
/*�� �� ����    CI_RSAVerify                                                                */
/*����������    ��֤ǩ���ĺϷ���                                                            */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAVerify(
              unsigned char  *pEntity,       //ʹ���ĸ�ʵ��Ĺ�Կ��ǩ������֤�ĸ�ʵ���ǩ��
              unsigned char  *pInData,
              unsigned int  nInDataLength,
              unsigned char  *pSignature,
              unsigned int  nSignatureLength
              )  ;

/********************************************************************************************/
/*�� �� ����    CI_MAC                                                                      */
/*����������    ����Macֵ                                                                   */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_MAC(
              int           nFunction,      //��������ҵ�����ݵ�Mac��һ��ҵ�����ݶ�Ӧһ���Գ���Կ��
              unsigned char  *pEntity,       //�Է�ʵ��ı�ţ���Mac�����ĸ�ʵ����֤��
              unsigned char  *pInData,
              unsigned int  nInLength,
              unsigned char  *pMAC,
              unsigned int  *pnMACLength
              )  ;

/********************************************************************************************/
/*�� �� ����    CI_MACVerify                                                                */
/*����������    ��֤Mac����ȷ��                                                             */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_MACVerify(
              int           nFunction,      //��֤����ҵ�����ݵ�Mac��һ��ҵ�����ݶ�Ӧһ���Գ���Կ��
              unsigned char  *pEntity,       //�Է�ʵ��ı�ţ���Mac�����ĸ�ʵ�壩
              unsigned char  *pInData,
              unsigned int  nInLength,
              unsigned char  *pMAC,
              unsigned int  nMACLength
              ) ;

/********************************************************************************************/
/*�� �� ����    CI_HMAC                                                                      */
/*����������    ����HMacֵ                                                                   */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_HMAC(
              int           nFunction,      //��������ҵ�����ݵ�HMac��һ��ҵ�����ݶ�Ӧһ���Գ���Կ��
              unsigned char  *pEntity,       //�Է�ʵ��ı�ţ���HMac�����ĸ�ʵ����֤��
              unsigned char  *pInData,
              unsigned int  nInLength,
              unsigned char  *pHMAC,
              unsigned int  *pnHMACLength
       ) ;

/********************************************************************************************/
/*�� �� ����    CI_HMACVerify                                                                */
/*����������    ��֤HMac����ȷ��                                                             */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_HMACVerify(
             int           nFunction,      //��֤����ҵ�����ݵ�HMac��һ��ҵ�����ݶ�Ӧһ���Գ���Կ��
             unsigned char  *pEntity,       //�Է�ʵ��ı�ţ���HMac�����ĸ�ʵ�壩
             unsigned char  *pInData,
             unsigned int  nInLength,
             unsigned char  *pHMAC,
             unsigned int  nHMACLength
             )  ;

/********************************************************************************************/
/*�� �� ����    CI_Digest                                                                   */
/*����������    ������ϢժҪ                                                                */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_Digest(
        unsigned int  nAlgType,
        unsigned char  *pInData,
        unsigned int  nInLength,
        unsigned char  *pHASH,
        unsigned int  *pnHASHLength
        )  ;


/********************************************************************************************/
/*�� �� ����    CI_Envelop                                                                  */
/*����������    �������������ŷ�                                                            */
/*              �Գ��㷨����DES_AES_PAD                                                     */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_Envelop(
            unsigned char  *pEntity,           //�������ŷ⽫���ĸ�ʵ��򿪣����͸��ĸ�ʵ�壩
            unsigned char  *pInData,
            unsigned int  nInLength,
            unsigned char  *pEnvelope,
            unsigned int  *pnEnvelopeLen
          );
/********************************************************************************************/
/*�� �� ����    CI_UnEnvelop                                                                */
/*����������    �⿪���������ŷ�                                                            */
/*              �Գ��㷨����DES_AES_PAD                                                     */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_UnEnvelop(
              unsigned char  *pEntity,        //��ǰʵ��ı�ţ�����ʵ����ŷⲻ����ǰʵ���
              unsigned char  *pEnvelope,
              unsigned int  nEnvelopeLen,
              unsigned char  *pOutData,
              unsigned int  *pnOutLen
            ) ;
/********************************************************************************************/
/*�� �� ����    CI_RSASignEncrypt                                                           */
/*����������    ��ͬһ��������������,������ǩ���ּ���                                       */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSASignSymEncrypt(
              int           nFunction,          //���ڶԳƼ��ܵ���Կ��
              unsigned char  *pCipherEntity,     //������������ĵĽ���ʵ�壬ǩ��ʵ��Ĭ��Ϊ��ǰʵ��

              unsigned char  *pInData,          //Ҫ����ǩ���ͼ��ܵ�����
              unsigned int  nInDataLength,     //���ݳ���

              unsigned char  *pSignature,        //ǩ�����������
              unsigned int  *pnSignatureLength, //ǩ������
              unsigned char  *pCipherData,       //�������������
              unsigned int  *pnCipherLength     //���ĳ���
              ) ;


/********************************************************************************************/
/*�� �� ����    CI_SymDecryptRSAVerify                                                      */
/*����������    �����Ľ��ܣ�����֤�����ĵ�ǩ��                                              */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_SymDecryptRSAVerify(
							int           nFunction,          //���ڶԳƽ��ܵ���Կ��
              unsigned char  *pSignCipherEntity, //ǩ����������Դʵ��

              unsigned char  *pCipherData,        //Ҫ���ܵ�����
              unsigned int  nCipherLength,       //���ĳ���
              unsigned char  *pSignature,         //Ҫ��֤��ǩ���������Ķ�Ӧ�����ĵ�ǩ��
              unsigned int  nSignatureLength,    //ǩ������

              unsigned char  *pPlainData,         //���ĵ����������
              unsigned int  *pnPlainLength       //���ĳ���
              ) ;

/*������ӿڶ������*/
/*�ļ���ӿڶ��忪ʼ*/

/********************************************************************************************/
/*�� �� ����    CI_FileRSASign                                                              */
/*����������    ���ļ���������ǩ��                                                          */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileRSASign(
              unsigned char  *pEntity,      //ʹ���ĸ�ʵ���˽Կǩ�����������ĸ�ʵ���ǩ��
              unsigned char  *pInFile,
              unsigned char  *pSignature,
              unsigned int  *pnSignatureLength
              )  ;

/********************************************************************************************/
/*�� �� ����    CI_FileRSAVerify                                                            */
/*����������    ��֤ǩ���ĺϷ���                                                            */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileRSAVerify(
              unsigned char  *pEntity,       //ʹ���ĸ�ʵ��Ĺ�Կ��ǩ������֤�ĸ�ʵ���ǩ��
              unsigned char  *pInFile,
              unsigned char  *pSignature,
              unsigned int  nSignatureLength
              ) ;

/********************************************************************************************/
/*�� �� ����    CI_FileMAC                                                                  */
/*����������    �����ļ�Macֵ                                                               */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileMAC(
              int           nFunction,      //�ڼ�����Կ
              unsigned char  *pEntity,       //�Է�ʵ��ı��
              unsigned char  *pInFile,
              unsigned char  *pMAC,
              unsigned int  *pnMACLength
              )  ;

/********************************************************************************************/
/*�� �� ����    CI_FileMACVerify                                                            */
/*����������    ��֤�ļ�Mac����ȷ��                                                         */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileMACVerify(
              int           nFunction,      //�ڼ�����Կ
              unsigned char  *pEntity,       //�Է�ʵ��ı��
              unsigned char  *pInFile,
              unsigned char  *pMAC,
              unsigned int  nMACLength
              ) ;
/********************************************************************************************/
/*�� �� ����    CI_FileHMAC                                                                 */
/*����������    �����ļ���HMacֵ                                                            */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileHMAC(
       int           nFunction,      //�ڼ�����Կ
       unsigned char  *pEntity,       //�Է�ʵ��ı��
       unsigned char  *pInFile,
       unsigned char  *pHMAC,
       unsigned int  *pnHMACLength
       ) ;

/********************************************************************************************/
/*�� �� ����    CI_FileHMACVerify                                                           */
/*����������    ��֤�ļ�HMac����ȷ��                                                        */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileHMACVerify(
             int           nFunction,      //�ڼ�����Կ
             unsigned char  *pEntity,       //�Է�ʵ��ı��
             unsigned char  *pInFile,
             unsigned char  *pHMAC,
             unsigned int  nHMACLength
             )  ;

/********************************************************************************************/
/*�� �� ����    CI_FileDigest                                                               */
/*����������    �����ļ���ժҪ                                                              */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileDigest(
              unsigned int  nAlgType,
              unsigned char  *pInFile,
              unsigned char  *pHASH,
              unsigned int  *pnHASHLength
              )  ;



/********************************************************************************************/
/*�� �� ����    CI_Envelop                                                                  */
/*����������    �������������ŷ�                                                            */
/*              �Գ��㷨����DES_AES_PAD                                                     */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileEnvelop(
            unsigned char  *pEntity,           //�������ŷ⽫���ĸ�ʵ��򿪣����͸��ĸ�ʵ�壩
            unsigned char  *pInFile,
            unsigned char  *pEnvelopeFile
          ) ;

/********************************************************************************************/
/*�� �� ����    CI_UnEnvelop                                                                */
/*����������    �⿪���������ŷ�                                                            */
/*              �Գ��㷨����DES_AES_PAD                                                     */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileUnEnvelop(
              unsigned char  *pEntity,        //��ǰʵ��ı�ţ�����ʵ����ŷⲻ����ǰʵ���
              unsigned char  *pEnvelopeFile,
              unsigned char  *pOutFile
            ) ;

/*�ļ���ӿڶ������*/
/*��Կ�����ඨ�忪ʼ*/
/********************************************************************************************/
/*�� �� ����    CI_SymDecrypt                                                               */
/*����������    ���������������󳤶�Ϊ300�ֽ�                                             */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_GenTrueRandom(
              unsigned int  nSize,
              unsigned char  *pRandData
              ) ;
FUNCTION_DECLARE(CI_RV)
CI_GetMyID(
            unsigned char *CurrentEntityCode
          );
/*base64����*/
FUNCTION_DECLARE(CI_RV)
CI_base64_encode(
              unsigned char * bin_data,
              unsigned int   bin_size,
			        char          * base64_data
			        ) ;

/*base64����*/
FUNCTION_DECLARE(CI_RV)
CI_base64_decode(
              char          * base64_data,
			        unsigned char * bin_data,
			        unsigned int * bin_size
			        ) ;


/*��Կ��ӿڶ������*/



/*�롰�����ӿڡ����ݵĽӿڿ�ʼ*/
/********************************************************/
/*�� �� ����    CI_PinEncrypt                           */
/*����������    PinKey ����                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_PinEncrypt(
		unsigned char *	pEntity,
		unsigned char *	pData,
		unsigned int	  ulDataLen ,
		unsigned char *	pEncryptedData,
		unsigned int *	pulEncryptedDataLen
    ) ;

/********************************************************/
/*�� �� ����    CI_PinDecrypt                           */
/*����������    PinKey ����                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_PinDecrypt(
		unsigned char * pEncryptedData,
		unsigned int   ulEncryptedDataLen,
		unsigned char * pData,
		unsigned int * pulDataLen
    ) ;

/********************************************************/
/*�� �� ����    CI_PkgEncrypt                           */
/*����������    PkgKey ����                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_PkgEncrypt(
		unsigned char *	pEntity,
		unsigned char *	pData,
		unsigned int	  ulDataLen ,
		unsigned char *	pEncryptedData,
		unsigned int *	pulEncryptedDataLen
    ) ;

/********************************************************/
/*�� �� ����    CI_PkgDecrypt                           */
/*����������    PkgKey ����                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_PkgDecrypt(
		unsigned char * pEncryptedData,
		unsigned int   ulEncryptedDataLen,
		unsigned char * pData,
		unsigned int * pulDataLen
    ) ;

/********************************************************/
/*�� �� ����    CI_GenerateMac                          */
/*����������    MacKey ����                             */
/********************************************************/

FUNCTION_DECLARE(CI_RV)
CI_GenerateMac(
		unsigned char *	pEntity,
		unsigned char * pData,
		unsigned int   ulDataLen,
		unsigned char * pMac,
		unsigned int * pulMacLen
    ) ;

/********************************************************/
/*�� �� ����    CI_VerifyMac                            */
/*����������    MacKey ��֤                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_VerifyMac(
		unsigned char *	pEntity,
		unsigned char * pData,
		unsigned int   ulDataLen,
		unsigned char * pMac,
		unsigned int   ulMacLen
    ) ;



/********************************************************/
/*�� �� ����    CI_Base64_PinEncrypt                    */
/*����������    PinKey ����                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_Base64_PinEncrypt(
		unsigned char *	pEntity,
		unsigned char *	pData,
		unsigned int	  ulDataLen ,
		unsigned char *	pEncryptedData,
		unsigned int *	pulEncryptedDataLen
    ) ;

/********************************************************/
/*�� �� ����    CI_Base64_PinDecrypt                    */
/*����������    PinKey ����                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_Base64_PinDecrypt(
		unsigned char *	pEncryptedData,
		unsigned int   ulEncryptedDataLen,
		unsigned char * pData,
		unsigned int * pulDataLen
    ) ;

/********************************************************************************************/
/*�� �� ����    CI_DeviceInit                                                               */
/*����������    ��ʼ���豸                                                      */
/********************************************************************************************/ 
FUNCTION_DECLARE(CI_RV)						
CI_DeviceInit();
/********************************************************************************************/
/*�� �� ����    CI_DeviceFinal                                                               */
/*����������    �ر��豸                                                      */
/********************************************************************************************/ 
FUNCTION_DECLARE(CI_RV)						
CI_DeviceFinal();

/*�롰�����ӿڡ����ݵĽӿڽ���*/


#ifdef __cplusplus
}
#endif

#endif
