/***************************************************************/
/* 通用密码运算接口的数据类型定义头文件                    */
/*                                                             */
/* 文件名:      CI_Datatype.h                                  */
/*                                                             */
/* 程序员:      燕召将                                         */
/*                                                             */
/* 编码日期:    2005.04.19                                     */
/***************************************************************/




#ifndef _CI_DATATYPE_H_
#define _CI_DATATYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************常量定义*************************/
//函数成功的返回值
#define CI_OK                     0

//错误码
#define CI_ERR_BASE                 0X02240000

#define CI_ERR_GENERAL              CI_ERR_BASE+0X0001
#define CI_ERR_RSA_DATA_LEN         CI_ERR_BASE+0X0002   //进行RSA运算处理的输入数据长度不合法
#define CI_ERR_BUFFER_TOO_SMALL     CI_ERR_BASE+0X0003   //输出缓冲区太小，不足以存放结果
#define CI_ERR_ARG_NULL             CI_ERR_BASE+0X0005   //指针参数为NULL
#define CI_ERR_RSA_PAD              CI_ERR_BASE+0X0006   //RSA解密出来的Pad错误
#define CI_ERR_MALLOC_MEMORY        CI_ERR_BASE+0X0007   //申请内存错误
#define CI_ERR_INVALID_SIGNATURE    CI_ERR_BASE+0X0008   //签名不合法
#define CI_ERR_ARG_OUTOF_RANGE      CI_ERR_BASE+0X0009   //数值参数小于最小值或大于最大值
#define CI_ERR_RSA_MODULUS_LEN      CI_ERR_BASE+0X000a   //RSA公钥/私钥模长不合法
#define CI_ERR_KEYTYPE              CI_ERR_BASE+0X000b   //密钥类型错误，无此密钥类型或者和算法类型不匹配
#define CI_ERR_ALGTYPE              CI_ERR_BASE+0X000c   //算法类型错误，无此算法类型或者和接口不匹配
#define CI_ERR_SYM_PAD              CI_ERR_BASE+0X000d   //对称解密出来的Pad错误
#define CI_ERR_SYM_DATA_LEN         CI_ERR_BASE+0X000e   //进行对称加解密、MAC计算/验证、hash计算的输入数据长度不合法
#define CI_ERR_SIGNATURE_LEN        CI_ERR_BASE+0X000f   //签名长度错误

#define CI_ERR_IV_LEN               CI_ERR_BASE+0X0022   //初始化向量长度和算法不匹配
#define CI_ERR_KEY_LEN              CI_ERR_BASE+0X0032   //密钥长度不符合要求

#define CI_ERR_HMAC_LEN             CI_ERR_BASE+0X0040   //HMAC验证中发现HMAC长度错误
#define CI_ERR_HMAC                 CI_ERR_BASE+0X0041   //HMAC验证中发现HMAC值不匹配
#define CI_ERR_MAC_LEN              CI_ERR_BASE+0X0042   //MAC验证中发现MAC长度错误
#define CI_ERR_MAC                  CI_ERR_BASE+0X0043   //MAC验证中发现MAC值不匹配

#define CI_ERR_FILE_OPEN            CI_ERR_BASE+0X0050   //打开文件错误
#define CI_ERR_FILE_CREATE          CI_ERR_BASE+0X0051   //创建输出文件错误
#define CI_ERR_FILE_EXIST           CI_ERR_BASE+0X0052   //输出文件已经存在
#define CI_ERR_FILE_READ            CI_ERR_BASE+0X0053   //读文件错误
#define CI_ERR_FILE_WRITE           CI_ERR_BASE+0X0054   //写文件错误
#define CI_ERR_KEY_OR_MAC_OR_HMAC   CI_ERR_BASE+0X0060

#define CI_ERR_MYID_NOT_SATISFY     CI_ERR_BASE+0X0070   //协商软件配置的实体编号和老的版本不兼容
#define CI_ERR_BASE64CIPHER_FORMAT  CI_ERR_BASE+0X0071   //base64编码后的密文格式不正确
#define CI_ERR_BASE64DATA_LEN       CI_ERR_BASE+0X0072   //base64编码长度不正确，必须是4的整数倍
//缓冲区大小
#define CI_MAX_DATA_LEN            16384 //16*1024
#define CI_MAX_RANDOM_LEN          4096
#define CI_MAX_RSA_MODULUS_LEN     256
#define CI_MAX_RSA_PRIME_LEN       CI_MAX_RSA_MODULUS_LEN/2

//对称密钥长度
#define CI_MAX_HMAC_KEY_LEN       256
#define CI_MAX_SYMMETRIC_KEY_LEN  32
#define CI_DES_KEY_LEN            8
#define CI_3DES112_KEY_LEN        16
#define CI_3DES168_KEY_LEN        24
#define CI_IDEA_KEY_LEN           16
#define CI_SSF33_KEY_LEN          16
#define CI_AES128_KEY_LEN         16

//对称算法分组长度长度
#define CI_DES_BLOCK_LEN          8
#define CI_3DES_BLOCK_LEN         8
#define CI_IDEA_BLOCK_LEN         8
#define CI_SSF33_BLOCK_LEN        16
#define CI_AES128_BLOCK_LEN       16

/**密钥类型定义，需和libCSSP.h中定义的值一致**/   /**注释掉的密钥类型定义来自libCSSP.h**/

#define CI_KEY_BASE         0X0000D000      //#define CSSPK_BASE            0X0000D000

#define CI_SYMMETRIC_KEY    CI_KEY_BASE+0   //#define CSSPK_SYMMETRIC_KEY   CSSPK_BASE+0
#define CI_PUBLIC_KEY       CI_KEY_BASE+1   //#define CSSPK_PUBLIC_KEY      CSSPK_BASE+1

#define CI_DES_KEY          CI_KEY_BASE+10  //#define CSSPK_DES_KEY         CSSPK_BASE+10
#define CI_3DES112_KEY      CI_KEY_BASE+11  //#define CSSPK_DES2_KEY        CSSPK_BASE+11
#define CI_3DES168_KEY      CI_KEY_BASE+12  //#define CSSPK_DES3_KEY        CSSPK_BASE+12
#define CI_IDEA_KEY         CI_KEY_BASE+13  //#define CSSPK_IDEA_KEY        CSSPK_BASE+13
#define CI_AES128_KEY       CI_KEY_BASE+14  //#define CSSPK_AES128_KEY      CSSPK_BASE+14
#define CI_SSF33_KEY        CI_KEY_BASE+17  //#define CSSPK_SSF33_KEY       CSSPK_BASE+17

#define CI_RSA_PUBLIC_KEY   CI_KEY_BASE+32  //#define CSSPK_RSA_PUBLIC_KEY_RAW  CSSPK_BASE+32
#define CI_RSA_PRIVATE_KEY  CI_KEY_BASE+33  //#define CSSPK_RSA_PRIVATE_KEY_RAW CSSPK_BASE+33

#define CI_MAC_MD5_KEY      CI_KEY_BASE+36  //#define CSSPK_MAC_MD5_KEY         CSSPK_BASE+36
#define CI_MAC_SHA1_KEY     CI_KEY_BASE+37  //#define CSSPK_MAC_SHA1_KEY        CSSPK_BASE+37


/********************算法类型（机制）定义*****/
//对称算法
enum
{
    CI_ALGO_DES_ECB       = 0x00000001,
    CI_ALGO_DES_CBC       = 0x00000002,
    CI_ALGO_3DES_ECB      = 0x00000010,
    CI_ALGO_3DES_CBC      = 0x00000020,
    CI_ALGO_AES_ECB       = 0x00000100,
    CI_ALGO_AES_CBC       = 0x00000200,
    CI_ALGO_SSF33_ECB     = 0x00001000,
    CI_ALGO_SSF33_CBC     = 0x00002000,
    CI_ALGO_IDEA_ECB      = 0x00010000,
    CI_ALGO_IDEA_CBC      = 0x00020000,
    CI_ALGO_DES_ECB_PAD   = 0x10000001,
    CI_ALGO_DES_CBC_PAD   = 0x10000002,
    CI_ALGO_3DES_ECB_PAD  = 0x10000010,
    CI_ALGO_3DES_CBC_PAD  = 0x10000020,
    CI_ALGO_AES_ECB_PAD   = 0x10000100,
    CI_ALGO_AES_CBC_PAD   = 0x10000200,
    CI_ALGO_SSF33_ECB_PAD    = 0x10001000,
    CI_ALGO_SSF33_CBC_PAD    = 0x10002000,
    CI_ALGO_IDEA_ECB_PAD     = 0x10010000,
    CI_ALGO_IDEA_CBC_PAD     = 0x10020000
};

//非对称算法
enum
{
    CI_ALGO_RSA_PUBLIC_KEY_RAW  = 0x00000001,
    CI_ALGO_RSA_PRIVATE_KEY_RAW = 0x00000002,

    CI_ALGO_RSA_PUBLIC_KEY_ENC_PKCS1  = 0x00000010,
    CI_ALGO_RSA_PUBLIC_KEY_DEC_PKCS1  = 0x00000020,
    CI_ALGO_RSA_PRIVATE_KEY_ENC_PKCS1 = 0x00000040,
    CI_ALGO_RSA_PRIVATE_KEY_DEC_PKCS1 = 0x00000080,

    CI_ALGO_RSA_PRIVATE_KEY_SIGN_WITH_MD5   = 0x00000100,
    CI_ALGO_RSA_PRIVATE_KEY_SIGN_WITH_SHA1  = 0x00000200,
    CI_ALGO_RSA_PUBLIC_KEY_VERIFY_WITH_MD5  = 0x00000400,
    CI_ALGO_RSA_PUBLIC_KEY_VERIFY_WITH_SHA1 = 0x00000800
};

//消息摘要
enum
{
    CI_ALGO_HASH_MD5  = 0x00000001,
    CI_ALGO_HASH_SHA1 = 0x00000002
};

//消息鉴别码
enum
{
    CI_ALGO_MAC_MD5    = 0x00000001,
    CI_ALGO_MAC_SHA1   = 0x00000002,
    CI_ALGO_MAC_DES_CBC   = 0x00000004,
    CI_ALGO_MAC_3DES_CBC  = 0x00000008,
    CI_ALGO_MAC_AES_CBC   = 0x00000010,
    CI_ALGO_MAC_SSF33_CBC = 0x00000020,
    CI_ALGO_MAC_IDEA_CBC  = 0x00000040
};

/*********************数据类型定义*********************/



typedef struct{
  unsigned int  nKeyLength;
  unsigned int  nKeyType;
  unsigned char pbKeyBuffer[CI_MAX_SYMMETRIC_KEY_LEN];
}SYMMETRIC_KEY;//对称密钥结构,必须和libCSSP.h中对称密钥结构一模一样

typedef struct{
   unsigned int    modulusLength;
   unsigned char   modulus[CI_MAX_RSA_MODULUS_LEN];
   unsigned char   publicExponent[CI_MAX_RSA_MODULUS_LEN];
}RSA_PUBLIC_KEY;//公钥结构,必须和libCSSP.h中公钥结构一模一样

typedef struct{
   unsigned int   modulusLength ;
   unsigned char  modulus[CI_MAX_RSA_MODULUS_LEN];
   unsigned char  publicExponent[CI_MAX_RSA_MODULUS_LEN];
   unsigned char  privateExponent[CI_MAX_RSA_MODULUS_LEN];
   unsigned char  prime[2][CI_MAX_RSA_PRIME_LEN];
   unsigned char  primeExponent[2][CI_MAX_RSA_PRIME_LEN];
   unsigned char  crtCoefficient[CI_MAX_RSA_PRIME_LEN];
}RSA_PRIVATE_KEY;//私钥结构,必须和libCSSP.h中私钥结构一模一样


typedef struct{
    unsigned int    nAlgType;       //对称算法（包括MAC算法）类型（机制）
    SYMMETRIC_KEY    SymKey;         //对称密钥结构
    unsigned char    IV[24];         //初始化向量
    unsigned int    nIVLen;         //初始化向量长度
}SYM_CONTEX;         //对称运算（对称加解密、MAC计算及验证）上下文

typedef struct{
    unsigned int    nAlgType;       //HMAC算法类型（机制）
    unsigned int    nKeyLength;     //计算HMAC的密钥长度
    unsigned char    pbKeyBuffer[CI_MAX_HMAC_KEY_LEN];   //HMAC密钥
}HMAC_CONTEX;        //HMAC计算及验证的上下文

typedef struct{
    unsigned int    nAlgType;       //非对称算法类型（机制）
    RSA_PUBLIC_KEY   PubKey;     //公钥结构
}PUB_CONTEX;         //非对称公钥运算（非对称加解密、验证签名）上下文

typedef struct{
    unsigned int     nAlgType;       //非对称算法类型（机制）
    RSA_PRIVATE_KEY   PriKey;         //私钥结构
}PRI_CONTEX;         //非对称私钥运算（非对称加解密、计算签名）上下文



#ifdef __cplusplus
}
#endif

#endif


