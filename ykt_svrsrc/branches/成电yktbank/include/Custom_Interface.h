/***************************************************************/
/* 自定义密码运算接口头文件                                    */
/*                                                             */
/* 文件名:      Custom_Interface.h                             */
/*                                                             */
/* 程序员:      燕召将                                         */
/*                                                             */
/* 编码日期:    2005.04.19                                     */
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


/*********************数据类型定义*********************/
//函数返回值
typedef  unsigned int   CI_RV;


/***************************接口定义*********************************************************/


/*报文类接口定义开始*/

/********************************************************************************************/
/*接 口 名：    CI_SymEncrypt                                                               */
/*功能描述：    对称加密                                                                    */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_SymEncrypt(
              int           nFunction,      //加密哪种业务数据（一种业务数据对应一个对称密钥）
              unsigned char  *pEntity,       //对方实体的编号（该密文将和哪个实体共享）
              unsigned char  *pPlainData,
              unsigned int  nPlainLength,
              unsigned char  *pCipherData,
              unsigned int  *pnCipherLength
              )  ;

/********************************************************************************************/
/*接 口 名：    CI_SymDecrypt                                                               */
/*功能描述：    对称解密                                                                    */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_SymDecrypt(
              int           nFunction,      //解密哪种业务数据（一种业务数据对应一个对称密钥）
              unsigned char  *pEntity,       //对方实体的编号（该密文来自哪个实体）
              unsigned char  *pCipherData,
              unsigned int  nCipherLength,
              unsigned char  *pPlainData,
              unsigned int  *pnPlainLength
              ) ;

/********************************************************************************************/
/*接 口 名：    CI_RSAPubKeyEncrypt                                                         */
/*功能描述：    RSA公钥加密                                                                 */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAPubKeyEncrypt(
              unsigned char  *pEntity,       //使用哪个实体的公钥加密
              unsigned char  *pPlainData,
              unsigned int  nPlainLength,
              unsigned char  *pCipherData,
              unsigned int  *pnCipherLength
              ) ;


/********************************************************************************************/
/*接 口 名：    CI_RSAPriKeyDecrypt                                                         */
/*功能描述：    RSA私钥解密                                                                 */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAPriKeyDecrypt(
              unsigned char  *pEntity,      //使用哪个实体的私钥解密
              unsigned char  *pCipherData,
              unsigned int  nCipherLength,
              unsigned char  *pPlainData,
              unsigned int  *pnPlainLength
              ) ;

/********************************************************************************************/
/*接 口 名：    CI_RSAPriKeyEncrypt                                                         */
/*功能描述：    RSA私钥加密                                                                 */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAPriKeyEncrypt(
              unsigned char  *pEntity,      //使用哪个实体的私钥加密
              unsigned char  *pPlainData,
              unsigned int  nPlainLength,
              unsigned char  *pCipherData,
              unsigned int  *pnCipherLength
              ) ;

/********************************************************************************************/
/*接 口 名：    CI_RSAPubKeyDecrypt                                                         */
/*功能描述：    RSA公钥解密                                                                 */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAPubKeyDecrypt(
              unsigned char  *pEntity,       //使用哪个实体的公钥解密
              unsigned char  *pCipherData,
              unsigned int  nCipherLength,
              unsigned char  *pPlainData,
              unsigned int  *pnPlainLength
              ) ;

/********************************************************************************************/
/*接 口 名：    CI_RSASign                                                                  */
/*功能描述：    产生数字签名                                                                */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSASign(
              unsigned char  *pEntity,      //使用哪个实体的私钥签名，即产生哪个实体的签名
              unsigned char  *pInData,
              unsigned int  nInDataLength,
              unsigned char  *pSignature,
              unsigned int  *pnSignatureLength
          ) ;

/********************************************************************************************/
/*接 口 名：    CI_RSAVerify                                                                */
/*功能描述：    验证签名的合法性                                                            */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSAVerify(
              unsigned char  *pEntity,       //使用哪个实体的公钥验签，即验证哪个实体的签名
              unsigned char  *pInData,
              unsigned int  nInDataLength,
              unsigned char  *pSignature,
              unsigned int  nSignatureLength
              )  ;

/********************************************************************************************/
/*接 口 名：    CI_MAC                                                                      */
/*功能描述：    计算Mac值                                                                   */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_MAC(
              int           nFunction,      //计算哪种业务数据的Mac（一种业务数据对应一个对称密钥）
              unsigned char  *pEntity,       //对方实体的编号（该Mac将由哪个实体验证）
              unsigned char  *pInData,
              unsigned int  nInLength,
              unsigned char  *pMAC,
              unsigned int  *pnMACLength
              )  ;

/********************************************************************************************/
/*接 口 名：    CI_MACVerify                                                                */
/*功能描述：    验证Mac的正确性                                                             */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_MACVerify(
              int           nFunction,      //验证哪种业务数据的Mac（一种业务数据对应一个对称密钥）
              unsigned char  *pEntity,       //对方实体的编号（该Mac来自哪个实体）
              unsigned char  *pInData,
              unsigned int  nInLength,
              unsigned char  *pMAC,
              unsigned int  nMACLength
              ) ;

/********************************************************************************************/
/*接 口 名：    CI_HMAC                                                                      */
/*功能描述：    计算HMac值                                                                   */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_HMAC(
              int           nFunction,      //计算哪种业务数据的HMac（一种业务数据对应一个对称密钥）
              unsigned char  *pEntity,       //对方实体的编号（该HMac将由哪个实体验证）
              unsigned char  *pInData,
              unsigned int  nInLength,
              unsigned char  *pHMAC,
              unsigned int  *pnHMACLength
       ) ;

/********************************************************************************************/
/*接 口 名：    CI_HMACVerify                                                                */
/*功能描述：    验证HMac的正确性                                                             */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_HMACVerify(
             int           nFunction,      //验证哪种业务数据的HMac（一种业务数据对应一个对称密钥）
             unsigned char  *pEntity,       //对方实体的编号（该HMac来自哪个实体）
             unsigned char  *pInData,
             unsigned int  nInLength,
             unsigned char  *pHMAC,
             unsigned int  nHMACLength
             )  ;

/********************************************************************************************/
/*接 口 名：    CI_Digest                                                                   */
/*功能描述：    产生消息摘要                                                                */
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
/*程 序 名：    CI_Envelop                                                                  */
/*功能描述：    产生报文数字信封                                                            */
/*              对称算法采用DES_AES_PAD                                                     */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_Envelop(
            unsigned char  *pEntity,           //该数字信封将由哪个实体打开（发送给哪个实体）
            unsigned char  *pInData,
            unsigned int  nInLength,
            unsigned char  *pEnvelope,
            unsigned int  *pnEnvelopeLen
          );
/********************************************************************************************/
/*程 序 名：    CI_UnEnvelop                                                                */
/*功能描述：    解开报文数字信封                                                            */
/*              对称算法采用DES_AES_PAD                                                     */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_UnEnvelop(
              unsigned char  *pEntity,        //当前实体的编号，其他实体的信封不允许当前实体打开
              unsigned char  *pEnvelope,
              unsigned int  nEnvelopeLen,
              unsigned char  *pOutData,
              unsigned int  *pnOutLen
            ) ;
/********************************************************************************************/
/*接 口 名：    CI_RSASignEncrypt                                                           */
/*功能描述：    对同一个明文输入数据,即计算签名又加密                                       */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_RSASignSymEncrypt(
              int           nFunction,          //用于对称加密的密钥号
              unsigned char  *pCipherEntity,     //该运算输出密文的接收实体，签名实体默认为当前实体

              unsigned char  *pInData,          //要计算签名和加密的数据
              unsigned int  nInDataLength,     //数据长度

              unsigned char  *pSignature,        //签名输出缓冲区
              unsigned int  *pnSignatureLength, //签名长度
              unsigned char  *pCipherData,       //密文输出缓冲区
              unsigned int  *pnCipherLength     //密文长度
              ) ;


/********************************************************************************************/
/*接 口 名：    CI_SymDecryptRSAVerify                                                      */
/*功能描述：    对密文解密，并验证其明文的签名                                              */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_SymDecryptRSAVerify(
							int           nFunction,          //用于对称解密的密钥号
              unsigned char  *pSignCipherEntity, //签名及密文来源实体

              unsigned char  *pCipherData,        //要解密的数据
              unsigned int  nCipherLength,       //密文长度
              unsigned char  *pSignature,         //要验证的签名，该密文对应的明文的签名
              unsigned int  nSignatureLength,    //签名长度

              unsigned char  *pPlainData,         //明文的输出缓冲区
              unsigned int  *pnPlainLength       //明文长度
              ) ;

/*报文类接口定义结束*/
/*文件类接口定义开始*/

/********************************************************************************************/
/*接 口 名：    CI_FileRSASign                                                              */
/*功能描述：    对文件产生数字签名                                                          */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileRSASign(
              unsigned char  *pEntity,      //使用哪个实体的私钥签名，即产生哪个实体的签名
              unsigned char  *pInFile,
              unsigned char  *pSignature,
              unsigned int  *pnSignatureLength
              )  ;

/********************************************************************************************/
/*接 口 名：    CI_FileRSAVerify                                                            */
/*功能描述：    验证签名的合法性                                                            */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileRSAVerify(
              unsigned char  *pEntity,       //使用哪个实体的公钥验签，即验证哪个实体的签名
              unsigned char  *pInFile,
              unsigned char  *pSignature,
              unsigned int  nSignatureLength
              ) ;

/********************************************************************************************/
/*接 口 名：    CI_FileMAC                                                                  */
/*功能描述：    计算文件Mac值                                                               */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileMAC(
              int           nFunction,      //第几个密钥
              unsigned char  *pEntity,       //对方实体的编号
              unsigned char  *pInFile,
              unsigned char  *pMAC,
              unsigned int  *pnMACLength
              )  ;

/********************************************************************************************/
/*接 口 名：    CI_FileMACVerify                                                            */
/*功能描述：    验证文件Mac的正确性                                                         */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileMACVerify(
              int           nFunction,      //第几个密钥
              unsigned char  *pEntity,       //对方实体的编号
              unsigned char  *pInFile,
              unsigned char  *pMAC,
              unsigned int  nMACLength
              ) ;
/********************************************************************************************/
/*接 口 名：    CI_FileHMAC                                                                 */
/*功能描述：    计算文件的HMac值                                                            */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileHMAC(
       int           nFunction,      //第几个密钥
       unsigned char  *pEntity,       //对方实体的编号
       unsigned char  *pInFile,
       unsigned char  *pHMAC,
       unsigned int  *pnHMACLength
       ) ;

/********************************************************************************************/
/*接 口 名：    CI_FileHMACVerify                                                           */
/*功能描述：    验证文件HMac的正确性                                                        */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileHMACVerify(
             int           nFunction,      //第几个密钥
             unsigned char  *pEntity,       //对方实体的编号
             unsigned char  *pInFile,
             unsigned char  *pHMAC,
             unsigned int  nHMACLength
             )  ;

/********************************************************************************************/
/*接 口 名：    CI_FileDigest                                                               */
/*功能描述：    产生文件的摘要                                                              */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileDigest(
              unsigned int  nAlgType,
              unsigned char  *pInFile,
              unsigned char  *pHASH,
              unsigned int  *pnHASHLength
              )  ;



/********************************************************************************************/
/*程 序 名：    CI_Envelop                                                                  */
/*功能描述：    产生报文数字信封                                                            */
/*              对称算法采用DES_AES_PAD                                                     */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileEnvelop(
            unsigned char  *pEntity,           //该数字信封将由哪个实体打开（发送给哪个实体）
            unsigned char  *pInFile,
            unsigned char  *pEnvelopeFile
          ) ;

/********************************************************************************************/
/*程 序 名：    CI_UnEnvelop                                                                */
/*功能描述：    解开报文数字信封                                                            */
/*              对称算法采用DES_AES_PAD                                                     */
/********************************************************************************************/
FUNCTION_DECLARE(CI_RV)
CI_FileUnEnvelop(
              unsigned char  *pEntity,        //当前实体的编号，其他实体的信封不允许当前实体打开
              unsigned char  *pEnvelopeFile,
              unsigned char  *pOutFile
            ) ;

/*文件类接口定义结束*/
/*密钥管理类定义开始*/
/********************************************************************************************/
/*接 口 名：    CI_SymDecrypt                                                               */
/*功能描述：    产生真随机数，最大长度为300字节                                             */
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
/*base64编码*/
FUNCTION_DECLARE(CI_RV)
CI_base64_encode(
              unsigned char * bin_data,
              unsigned int   bin_size,
			        char          * base64_data
			        ) ;

/*base64解码*/
FUNCTION_DECLARE(CI_RV)
CI_base64_decode(
              char          * base64_data,
			        unsigned char * bin_data,
			        unsigned int * bin_size
			        ) ;


/*密钥类接口定义结束*/



/*与“北京接口”兼容的接口开始*/
/********************************************************/
/*程 序 名：    CI_PinEncrypt                           */
/*功能描述：    PinKey 加密                             */
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
/*程 序 名：    CI_PinDecrypt                           */
/*功能描述：    PinKey 解密                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_PinDecrypt(
		unsigned char * pEncryptedData,
		unsigned int   ulEncryptedDataLen,
		unsigned char * pData,
		unsigned int * pulDataLen
    ) ;

/********************************************************/
/*程 序 名：    CI_PkgEncrypt                           */
/*功能描述：    PkgKey 加密                             */
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
/*程 序 名：    CI_PkgDecrypt                           */
/*功能描述：    PkgKey 解密                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_PkgDecrypt(
		unsigned char * pEncryptedData,
		unsigned int   ulEncryptedDataLen,
		unsigned char * pData,
		unsigned int * pulDataLen
    ) ;

/********************************************************/
/*程 序 名：    CI_GenerateMac                          */
/*功能描述：    MacKey 加密                             */
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
/*程 序 名：    CI_VerifyMac                            */
/*功能描述：    MacKey 验证                             */
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
/*程 序 名：    CI_Base64_PinEncrypt                    */
/*功能描述：    PinKey 加密                             */
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
/*程 序 名：    CI_Base64_PinDecrypt                    */
/*功能描述：    PinKey 解密                             */
/********************************************************/
FUNCTION_DECLARE(CI_RV)
CI_Base64_PinDecrypt(
		unsigned char *	pEncryptedData,
		unsigned int   ulEncryptedDataLen,
		unsigned char * pData,
		unsigned int * pulDataLen
    ) ;

/********************************************************************************************/
/*接 口 名：    CI_DeviceInit                                                               */
/*功能描述：    初始化设备                                                      */
/********************************************************************************************/ 
FUNCTION_DECLARE(CI_RV)						
CI_DeviceInit();
/********************************************************************************************/
/*接 口 名：    CI_DeviceFinal                                                               */
/*功能描述：    关闭设备                                                      */
/********************************************************************************************/ 
FUNCTION_DECLARE(CI_RV)						
CI_DeviceFinal();

/*与“北京接口”兼容的接口结束*/


#ifdef __cplusplus
}
#endif

#endif
