/********************************************************************
	created:	2004/10/12
	created:	12:10:2004   1:08
	filename: 	e:\proj\n_dce\xpack\packc.h
	file path:	e:\proj\n_dce\xpack
	file base:	packc
	file ext:	h
	author:		CHENYH

	purpose:
      模块最后功能修改日期为2005-3-25

      2005-6-3 11:06:02 增加注释
      与CPACK的调用模式兼容（替换原来的CPACK.C模块），保证原系统按照正常使用，
   同时新增了几个函数，对部分函数作了功能的增强。
      由于采用了外挂XPACK结构定义文件方式，因此内部大量的处理作了完全的变更。

      为了兼容原CPACK调用方式，模块内部定义了一个全局的CXPack类的实例，作为
      缺省实例。

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
// 以下为C/C++都能调用的一些基本函数：

// 函数名: LoadPackDefFile
// 编程  : 陈永华 2005-6-3 11:10:04
//         新增函数 New
// 描述  : 用于装载XPACK结构定义文件。
//         如果系统直接使用当前目录下的cpack.dat作为XPACK结构定义文件，
//         则可以不调用本函数。
// 返回  : PACKC_API int
//           >=0  - 成功 返回最后一个有效字段号；
//            -1  - 包格式文件不能打开；
//            -2  - 指定文件格式错误；不能被本版本所辨别
// 参数  : char *szPackDefFile：XPACK格式定义文件名
    PACKC_API int LoadPackDefFile(char *szPackDefFile);


// 函数名: GetDefaultXPack
// 编程  : 陈永华 2005-6-3 11:19:05
//         新增函数 New
// 描述  : 得到内部缺省的XPack定义实例
// 返回  : PACKC_API void *：用这种类型返回是为了对原来的程序不需要再增加XPack.h等头文件
//         当程序包含了XPack.h文件，并且希望使用强大的CXPack内的方法，
//         对于返回值，可以强制为CXPack *，即可以如下调用：
//         CXPack *pXPack = (CXPack *)GetDefaultXPack(); 即可
    PACKC_API void * GetDefaultXPack();


// 函数名: Reverse
// 编程  : 陈永华 2005-6-3 11:25:33
//         原有函数 Old
// 描述  : 对buf的数据进行XPACK/CPACK内部定义的字节序转换
//         即程序运行的机器如果属于Little-Endian类型的，则作转换；
//         若为Big-Endian类型的，则不作字节序转换。
//         对其真实含义不是完全了解，
// 返回  : PACKC_API void
// 参数  : void *buf 需要转换的数据位置
// 参数  : int len   数据的字节数
    PACKC_API void Reverse(void *buf,int len);


// 函数名: Reserve
// 编程  : 陈永华 2005-6-3 11:31:36
//         原有函数 Old
// 描述  : 本函数不建议使用，仅仅是为了兼容CPACK的定义函数。
//          实际功能和Reverse相同。
// 返回  : PACKC_API void
// 参数  : void *buf
// 参数  : int len
    PACKC_API void Reserve(void *buf,int len);


// 函数名: DecodeHead
// 编程  : 陈永华 2005-6-3 11:33:21
//         原有函数 Old
// 描述  : 对打包编码（从网络上收到的XPACK数据）进行XPACK头部数据的解码
// 返回  : PACKC_API int ：sizeof(ST_PACKHEAD) ；<0 失败 缓冲区长度太小
// 参数  : void *buf [IN] : 编码缓冲区 （应该为接收到的数据开始位置）
// 参数  : int len [IN] : 编码数据长度（即接收到的数据长度）
// 参数  : ST_PACKHEAD *pHead [OUT]: 包头指针
// 参数  : char *eMsg：返回失败时候，存放失败信息
    PACKC_API int DecodeHead(unsigned char *buf,int len,ST_PACKHEAD *pHead,char *eMsg);


// 函数名: DecodeBufHead
// 编程  : 陈永华 2005-6-3 13:03:49
//         原有函数 Old
// 描述  : 实际就是DecodeHead,仅仅更改了调用参数。
//         将数据中的XPACK/CPACK的包头数据解码到pPack中的包头
// 返回  : PACKC_API int：sizeof(ST_PACKHEAD) ；<0 失败 缓冲区长度太小
// 参数  : void *buf [IN] : 编码缓冲区 （应该为接收到的数据开始位置）
// 参数  : int len [IN] : 编码数据长度（即接收到的数据长度）
// 参数  : ST_CPACK *pPack [OUT]: ST_CPACK包指针，解码数据存放的目标
// 参数  : char *eMsg [OUT]: 返回失败时候，存放失败信息
    PACKC_API int DecodeBufHead(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg);


// 函数名: DecodeAPack
// 编程  : 陈永华 2005-6-3 13:09:49
//         原有函数 Old
// 描述  : 将打包数据中的包体部分逐条记录解码
// 返回  : PACKC_API int
    /*
          >=0:成功，返回编码占用的长度；
          <0:解码失败
             -1: 编码位图有误(有未定义的位图设置);
             -2: 编码中字段数据超出定义;
             -10: 缓冲区长度不足
    *******************************************************/
// 参数  : char *buf [IN]: 被解码的数据块（注意打包数据的偏移位置）
// 参数  : int len [IN]: 未解码的数据块长度 （注意扣除之前已经解码占用的数据块长度）
// 参数  : ST_PACKHEAD *phead [IN]: 已经被解码出来的包头
// 参数  : ST_PACK *pack [OUT]: 存放解码出来的记录缓冲，（新增支持对ST_SDPACK的解码）
// 参数  : char *eMsg [OUT]: 返回失败时候，存放失败信息
    PACKC_API int DecodeAPack(char *buf,int len,ST_PACKHEAD *phead,ST_PACK *pack,char *eMsg);


// 函数名: DecodeBuf
// 编程  : 陈永华 2005-6-3 13:17:36
//         原有函数 Old
// 描述  : 结合了DecodeHead和DecodeAPack，将打包数据块解码到ST_CPACK中（即包头和包体首记录）
// 返回  : PACKC_API int
    /*
             >0: 解码占用（即完成）的编码块长度
             =0: 解码错误
    */
// 参数  : char *buf [IN]: 被解码的（即编码）数据块（由于是包括包头，因此就是接收到的数据块起始位置）
// 参数  : int len [IN] : 编码数据长度（即接收到的数据长度）
// 参数  : ST_CPACK *pPack [OUT]: 解码出来的ST_CPACK缓存
// 参数  : char *eMsg [OUT]: 返回失败时候，存放失败信息
    PACKC_API int DecodeBuf(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg);


// 函数名: DecodeBufWithArray
// 编程  : 陈永华 2005-6-3 13:41:07
//         原有函数 Old
// 描述  : 将编码数据完整解码到一个ST_CPACK和ST_PACK记录组中（如果有的话）
// 返回  : PACKC_API int
    /*
             >0: 解码占用（即完成）的编码块长度
             =0: 解码错误
    */
// 参数  : char *buf [IN]: 被解码的（即编码）数据块（由于是包括包头，因此就是接收到的数据块起始位置）
// 参数  : int len [IN] : 编码数据长度（即接收到的数据长度）
// 参数  : ST_CPACK *pPack [OUT]: 解码出来的ST_CPACK缓存
// 参数  : ST_PACK *packArray [OUT]: 解码出来的后记录数据缓冲，当为NULL时候，则不解码第二条开始的记录
// 参数  : int *recCount [OUT]: 返回解码出来的记录数
// 参数  : char *eMsg [OUT]: 返回失败时候，存放失败信息
    PACKC_API int DecodeBufWithArray(unsigned char *buf,int len,ST_CPACK *pPack,ST_PACK *packArray,int *recCount,char *eMsg);


// 函数名: EmulateEncodeLen
// 编程  : 陈永华 2005-6-3 13:50:30
//         新增函数 New
// 描述  : 根据包头phead中的位图，推算一个数据记录编码需要最长的缓冲空间长度
// 返回  : PACKC_API int 需要存放一条记录的编码数据的缓冲空间长度（不包括包头部分的长度）
// 参数  : ST_PACKHEAD *phead [IN]: 用于推算的包头
    PACKC_API int EmulateEncodeLen(ST_PACKHEAD *phead);


// 函数名: ModifyHead
// 编程  : 陈永华 2005-6-3 13:55:31
//         原有函数 Old
// 描述  : 将包头部分编码到编码缓存中
// 返回  : int ： sizeof(ST_PACKHEAD)
// 参数  : ST_PACKHEAD *pHead 〔IN〕 包头数据
// 参数  : unsigned char *buf 〔OUT〕存放编码的缓冲区
    PACKC_API int ModifyHead(ST_PACKHEAD *phead,unsigned char *buf);


// 函数名: EncodeRow
// 编程  : 陈永华 2005-6-3 13:58:55
//         原有函数 Old
// 描述  : 将一条数据记录pRowPack编码（打包）到编码缓存中
// 返回  : PACKC_API int
    /* ****** Updated by CHENYH at 2005-6-3 14:01:08 ******
                >0: 返回该记录被编码后占用的编码缓存长度；
                ＝0: 编码失败，包括buf==NULL 或 pHead->recCount<=0
                     或者因为编码长度>8K
    *******************************************************/
// 参数  : ST_PACKHEAD *pHead [IN]: 用于编码的包头
// 参数  : ST_PACK *pRowPack [IN]: 一条数据记录 (支持对ST_SDPACK的编码)
// 参数  : unsigned char *buf [OUT]: 编码缓存
// 参数  : int *len [OUT]: 编码长度
// 参数  : char *eMsg  --- 没有用
    PACKC_API int EncodeRow(ST_PACKHEAD *pHead,ST_PACK *pRowPack,unsigned char *buf,int *len,char *eMsg);


// 函数名: EncodeBuf
// 编程  : 陈永华 2005-6-3 14:13:52
// 描述  : 将一个ST_CPACK编码打包到编码缓存中
// 返回  : PACKC_API int ：返回编码后的长度（即编码缓存中占用的空间）
// 参数  : ST_CPACK *pPack [IN]: 一个被编码的ST_CPACK
// 参数  : unsigned char *buf [OUT]:  编码缓存
// 参数  : int *len [OUT]: 返回编码后的长度
// 参数  : char *eMsg --- 没有用
    PACKC_API int EncodeBuf(ST_CPACK *pPack,unsigned char *buf,int *len,char *eMsg);


// 函数名: EncodeBufArray
// 编程  : 陈永华 2005-6-3 14:44:19
// 描述  : 一次性对单记录或多记录数据的编码函数
// 返回  : PACKC_API int： 返回编码后的长度（即编码缓存中占用的空间）
// 参数  : ST_CPACK *pPack [IN]: 被编码的ST_CPACK
// 参数  : ST_PACK *pArray [IN]: 被编码的ST_PACK数组，可以为NULL，则ST_CPACK中被强行改为单记录或无记录的
//         注意：当为ST_SDPACK类的记录，那么也必须以ST_PACK长度对齐（或者作为ST_PACK的数组作为缓存）
// 参数  : unsigned char *buf [OUT]:  编码缓存
// 参数  : int *len [OUT]: 返回编码后的长度
// 参数  : char *eMsg --- 没有用
    PACKC_API int EncodeBufArray(ST_CPACK *pPack,ST_PACK *pArray,unsigned char *buf,int *len,char *eMsg);


// 函数名: SetParmBit
// 编程  : 陈永华 2005-6-3 14:53:47
// 描述  : 在包头中设置指定字段的位图
// 返回  : PACKC_API int  0: 不正确的字段号（与初始化的报文格式不符）1:成功
// 参数  : ST_PACKHEAD *ph [OUT]: 被设置的包头（内部的位图表）
// 参数  : int fidx [IN]: 字段的F_  值 （参见cpack.h中的定义）
    PACKC_API int SetParmBit(ST_PACKHEAD *ph,int fidx);


// 函数名: ClearParmBit
// 编程  : 陈永华 2005-6-3 14:56:31
// 描述  : 在包头中清除指定字段的位图
// 返回  : PACKC_API int  0: 不正确的字段号（与初始化的报文格式不符）1:成功
// 参数  : ST_PACKHEAD *ph[OUT]: 被设置的包头（内部的位图表）
// 参数  : int fidx [IN]: 字段的F_  值 （参见cpack.h中的定义）
    PACKC_API int ClearParmBit(ST_PACKHEAD *ph,int fidx);


// 函数名: SetErrorPack
// 编程  : 陈永华 2005-6-3 14:58:57
// 描述  : 设置错误返回数据包，并根据inPack设置包头
//          同时将outPack包头中的
//             firstflag=1;  表示为首包数据
//             nextflag=0;   表示无后续包
//             recCount=1; 单记录数据包
//          另外将首记录中的vsmess字段中加入错误信息，并设置对应的位图
// 返回  : PACKC_API int :1
// 参数  : ST_CPACK *inPack [IN]: 将inPack的包头中的userdata,hook,addr,RequestType,firstflag复制到outPack中
// 参数  : ST_CPACK *outPack [OUT]: 被设置的返回包数据
// 参数  : char *emsg [IN]: 错误信息字符串
// 参数  : int eCode [IN]: 错误码 赋值到outPack的包头中的retCode中
    PACKC_API int SetErrorPack(ST_CPACK *inPack,ST_CPACK *outPack,char *emsg,int eCode);


// 函数名: SetErrorPack2
// 编程  : 陈永华 2005-6-3 14:59:05
// 描述  : 设置错误返回数据包，重置数据包头
//          同时将outPack包头中的
//             firstflag=1;  表示为首包数据
//             nextflag=0;   表示无后续包
//             recCount=1; 单记录数据包
//          另外将首记录中的vsmess字段中加入错误信息，并设置对应的位图
// 返回  : PACKC_API int ：1
// 参数  : ST_CPACK *outPack [OUT]: 被设置的返回包数据
// 参数  : char *emsg [IN]: 错误信息字符串
// 参数  : int eCode [IN]: 错误码 赋值到outPack的包头中的retCode中
    PACKC_API int SetErrorPack2(ST_CPACK *outPack,char *emsg,int eCode);


// 函数名: SetNormalPack
// 编程  : 陈永华 2005-6-3 14:59:12
// 描述  : 根据输入包inPack，设置正常的返回包outPack
//          同时将outPack包头中的
//             firstflag与inPack中的firstflag相同
// 返回  : PACKC_API int :1
// 参数  : ST_CPACK *inPack [IN]: 将inPack的包头中的userdata,hook,addr,RequestType,firstflag复制到outPack中
// 参数  : ST_CPACK *outPack [OUT]: 被设置的返回包数据
// 参数  : int nextflag [IN]: 是否有后续包. 0-无，否则有
// 参数  : int recCount [IN]: 本数据包包含有多少数据记录数
    PACKC_API int SetNormalPack(ST_CPACK *inPack,ST_CPACK *outPack,int nextflag,int recCount);


// 函数名: SetNormalPack2
// 编程  : 陈永华 2005-6-3 14:59:18
// 描述  : 设置正常数据包outPack （清空包头中的userdata,hook等）
//          同时将outPack包头中的
//             firstflag=1;  表示为首包数据
//             nextflag=0;   表示无后续包
// 返回  : PACKC_API int ：1
// 参数  : ST_CPACK *outPack [OUT]: 被设置的数据包
// 参数  : unsigned int reqtype [IN]: 包的请求功能号
// 参数  : int recCount [IN]: 本数据包包含有多少数据记录数
    PACKC_API int SetNormalPack2(ST_CPACK *outPack,unsigned int reqtype,int recCount);  // update reqtype (unsigned char ) with (unsigned int) 20050325


// 函数名: ShowPackHead
// 编程  : 陈永华 2005-6-3 15:43:09
// 描述  : 在buf中输出包头中的参数，用于调试
// 返回  : PACKC_API int ：1
// 参数  : char *buf [OUT]: 用于填写可打印的包头中的参数，注意要留出足够的空间
// 参数  : ST_PACKHEAD *phead [IN]: 被调试的包头
    PACKC_API int ShowPackHead(char *buf,ST_PACKHEAD *phead);


// 函数名: AddFieldValue
// 编程  : 陈永华 2005-6-3 15:46:12
//         新增函数 New
// 描述  : 对ST_CPACK中的名称字符串指定字段进行赋值（包括设置位图）
// 返回  : PACKC_API bool ：如果返回为false，说明没有找到指定的字段
// 参数  : ST_CPACK *pack [OUT]: 被赋值ST_CPACK
// 参数  : const char *fieldname [IN]: 字段的名称
// 参数  : const char *fieldvalue [IN]: 用字符串表示的字段值 注意对属于unsigned char 的字段，建议采用0x开始表示的值，否则就被直接复制
    PACKC_API bool AddFieldValue(ST_CPACK *pack,const char *fieldname,const char *fieldvalue);


// 函数名: AddFieldValueD
// 编程  : 陈永华 2005-6-3 15:55:40
//         新增函数 New
// 描述  : 对ST_CPACK中的名称字符串指定字段进行赋值（包括设置位图）
// 返回  : PACKC_API bool ：如果返回为false，说明没有找到指定的字段
// 参数  : ST_CPACK *pack [OUT]: 被赋值ST_CPACK
// 参数  : const char *fieldname [IN]: 字段的名称
// 参数  : const double dfvalue [IN]: 用浮点表示的字段值，如果该字段不是double型，则经过转换后设置相应的类型
    PACKC_API bool AddFieldValueD(ST_CPACK *pack,const char *fieldname,const double dfvalue);


// 函数名: AddFieldValueI
// 编程  : 陈永华 2005-6-3 15:56:20
//         新增函数 New
// 描述  : 对ST_CPACK中的名称字符串指定字段进行赋值（包括设置位图）
// 返回  : PACKC_API bool ：如果返回为false，说明没有找到指定的字段
// 参数  : ST_CPACK *pack [OUT]: 被赋值ST_CPACK
// 参数  : const char *fieldname [IN]: 字段的名称
// 参数  : const int ifvalue [IN]: 用整数表示的字段值，如果该字段不是int型，则经过转换后设置相应的类型
    PACKC_API bool AddFieldValueI(ST_CPACK *pack,const char *fieldname,const int ifvalue);


// 函数名: FindFieldIndex
// 编程  : 陈永华 2005-8-2 22:13:11
// 描述  : 根据字段名得到当前报文结构中，对该字段的字段编号即F_ 值
// 返回  : int >=0: 成功，返回该字段编号；<0: 在定义表中没有该名称的字段
// 参数  : const char *fieldname [IN]: 字段名，注意大小写敏感
    PACKC_API int FindFieldIndex(const char *fieldname);

#ifdef __cplusplus
}
#endif

#undef PACKC_API

#endif

