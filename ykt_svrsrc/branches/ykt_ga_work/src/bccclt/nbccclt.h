/********************************************************************
	created:	2006/08/23
	created:	23:8:2006   9:41
	filename: 	D:\proj\ksbass\bcclink\bccclt\bccclt.h
	file path:	D:\proj\ksbass\bcclink\bccclt
	file base:	bccclt
	file ext:	h
	author:		CHENYH
	
	purpose:	这个头文件目的是为了能够生成可以让C、C++也能调用的接口
*********************************************************************/
#ifndef NBCCCLT_H
#define NBCCCLT_H
#ifdef BCCCLT_EXPORTS
#include "XPData.h"
#ifdef _WINDOWS
#define BCCCLT_API __declspec(dllexport)
#else
#define BCCCLT_API 
#endif
#else
typedef void * BCHANDLE;
#ifdef _WINDOWS
#define BCCCLT_API __declspec(dllimport)
#else
#define BCCCLT_API 
#endif
#endif

#ifdef __cplusplus
extern "C" {
#else
   typedef unsigned char bool;
/* ****** Updated by CHENYH at 2006-7-12 11:04:58 ****** 
   #define true 1
   #define false 0
*******************************************************/
#endif

   // 描述  : 初试化本系统将直接连接多少个业务通讯平台节点个数
   //		Notice: 系统只能调用一次
   // 返回  : bool 
   // 参数  : int maxnodes=1 [IN]: 设置最多会有多少个连接节点
   BCCCLT_API  bool BCCCLTInit(int maxnodes);
   
   // 描述  : 增加一个要直接连接的业务通讯平台节点
   //       作为系统初试化部分，建议在调用BCCCLTInit后，在统一一个线程里一次性的设置完毕，供整个环境使用
   // 返回  : int  增加的业务通讯平台节点编号 >=0:成功；否则，可能没有正确调用BCCCLTInit()
   // 参数  : char * ip [IN]: 该业务通讯平台的IP地址
   // 参数  : int port [IN]: 该业务通讯平台提供的端口号port
   BCCCLT_API  int BCAddDrtpNode(char * ip,int port);


   // 描述  : 构件一个用于XPack数据交换的数据区
   // 返回  : BCHANDLE : 返回该XPack数据区的句柄；==0(NULL): 失败
   // 参数  : const char * XpackDescribleFile [IN]: XPack结构定义文件名，不能超过1024字节长，如: "/xpacks/cpack.dat"
	BCCCLT_API  BCHANDLE BCNewHandle(const char * XpackDescribleFile);
   
   // 描述  : 将已经用BCNewHandle得到的数据区释放(卸构)
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   BCCCLT_API  bool BCDeleteHandle(BCHANDLE Handle);

   // 描述  : 重置数据区内容，主要用于准备首包请求时，填写具体请求数据字段之前调用
   // 返回  : bool : false - 往往为错误的Handle(==NULL的时候)
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
	BCCCLT_API  bool BCResetHandle(BCHANDLE Handle);

   // 描述  : 将SourceHandle中的状态、格式、数据等信息复制到DestHandle中
   // 返回  : bool : false - 往往为错误的Handle(==NULL的时候)
   // 参数  : BCHANDLE SourceHandle [IN]: 被复制的原XPack数据区句柄
   // 参数  : BCHANDLE DestHandle   [OUT]: 被复制的目标XPack数据区句柄，内部数据被覆盖，但不会新派生一个句柄
	BCCCLT_API  bool BCCopyHandle(BCHANDLE SourceHandle,BCHANDLE DestHandle);
//--------------------------------------------------------------------------------------------------
   //////////////////////////////////////////////////////////////////////////
   // 在通过BCNewHandle得到句柄后，就可以设置请求字段数据了：

   // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : int Value [IN]: 数据值
   BCCCLT_API  bool BCSetIntFieldByName(BCHANDLE Handle,int Row,char * FieldName,int Value);
   
   // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : double Value [IN]: 数据值
   BCCCLT_API  bool BCSetDoubleFieldByName(BCHANDLE Handle,int Row,char * FieldName,double Value);
   
   // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : char * Value [IN]: 数据值，不可以超过255长度
   BCCCLT_API  bool BCSetStringFieldByName(BCHANDLE Handle,int Row,char * FieldName,char * Value);
      
   
   // 描述  : 设置指定记录为指定的RawData记录
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 指定设置的记录号 [0..RecordCount-1]
   // 参数  : char * RawData [IN]: 要设置数据块
   // 参数  : int RawDataLength [IN]: 要设置数据块长度
   BCCCLT_API  bool BCSetRawRecord(BCHANDLE Handle, int Row, char * RawData, int RawDataLength);


   // 描述  : 设置请求数据中的功能号 （在EncodeXpackForRequest之前一定要设置）
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int RequestType [IN]: 对应的业务功能号
   BCCCLT_API  bool BCSetRequestType(BCHANDLE Handle,int RequestType);

   
   // 描述  : 对于BCC类的服务器，客户端可以设置应答包每次返回的最多记录数
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int MaxRetCount [IN]: 指定的最多记录数，0则由应用服务器端 [0..100]; 
   BCCCLT_API  bool BCSetMaxRetCount(BCHANDLE Handle,int MaxRetCount);
   

   //////////////////////////////////////////////////////////////////////////
   // 在设置了请求数据和请求功能号，接下来就可以用下列函数向服务器发请求了：

   // 描述  : 将前面设置好XPack请求数据打包发送给指定的通讯平台和应用服务器
   // 返回  : bool : true 成功发送，并且接收解码了应答数据；false 操作失败，具体错误，参见错误码
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int drtpno [IN]: 从那个直联的业务通讯平台节点发送和接收数据，参见BCAddDrtpNode()的返回值
   // 参数  : int branchno [IN]: 目标应用服务器连接的业务通讯平台节点编号（参见业务通讯平台的配置参数表）
   // 参数  : int function [IN]: 目标应用服务器注册在业务通讯平台的功能号 (参见BCC配置文件中的BASEFUNCNO)
   // 参数  : int timeout [IN]: 发送接收数据的超时时间，以毫秒计
   // 参数  : int* errcode [OUT]: 返回的错误码
   // 参数  : char * errormessage [OUT]: 返回的错误信息
   BCCCLT_API  bool BCCallRequest(BCHANDLE Handle, int drtpno, int branchno,int function, int timeout, int *errcode,char * errormessage);
   
   
   //////////////////////////////////////////////////////////////////////////
   //在调用了BCCallRequest后，就要检查返回的数据内容，
   
   // 描述  : 在调用BCCallRequest后读取其返回码
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int* RetCode [OUT]: 返回收到数据包中的返回码
   BCCCLT_API  bool BCGetRetCode(BCHANDLE Handle,int * RetCode);

   // 描述  : 在调用BCCallRequest/BCCallNext后读取本包中的记录数RecordCount
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int * RecordCount [OUT]: 返回解包后的记录数
   BCCCLT_API  bool BCGetRecordCount(BCHANDLE Handle,int * RecordCount);   
   
   // 描述  : 根据收得解码后的数据，从中得到属于可以获取后续应答数据包的应用服务器专用通讯功能号
   //          详细技术请参考KSBCC使用说明书
   // 返回  : int : >0 - 可获取后续数据的专用通讯功能号；否则失败
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   BCCCLT_API  int BCGetPrivateFunctionForNext(BCHANDLE Handle);
   
   // 描述  : 根据收得解码后的数据，从中得到属于可以获取后续应答数据包的目标通讯平台节点编号
   //          详细技术请参考KSMBCC使用说明书
   // 返回  : int >0: 获取后续应答数据包的目标通讯平台节点编号; 否则还是用原来的节点编号
   //                当该功能是用Transfer实现的时候，需要这个可能被变更了的节点号
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   BCCCLT_API  int BCGetBranchNoForNext(BCHANDLE Handle);
   
   // 编程  : 陈永华 2005-11-14 22:01:15
   // 描述  : 当解码后，通过本函数判断是否还有后续应答包
   // 返回  : bool : true-表示还有后续应答包；false－无后续包
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   BCCCLT_API  bool BCHaveNextPack(BCHANDLE Handle);

   // 描述  : 取下一个后续应答包
   //          在成功调用BCCallRequest后，如果检查到BCHaveNextPack()后，则用本功能获取下一个后续应答包
   // 返回  : bool ：true 成功发送，并且接收解码了应答数据；false 操作失败，具体错误，参见错误码
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int timeout [IN]: 发送接收数据的超时时间，以毫秒计
   // 参数  : int* errcode [OUT]: 返回的错误码
   // 参数  : char * errormessage [OUT]: 返回的错误信息
   BCCCLT_API  bool BCCallNext(BCHANDLE Handle, int timeout, int* errcode,char * errormessage);
      
   // 描述  : 查询当前数据块中数据记录类型
   // 返回  : int 返回数据记录类型 0-标准ST_PACK记录；1-ST_SDPACK的RawData记录
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   BCCCLT_API  int BCGetXPackType(BCHANDLE Handle); 
   
   // 描述  : 当用BCGetXPackType返回为1即ST_SDPACK类的记录，则可以用本函数获取各个有效记录中的RawData记录
   // 返回  : int : >=0 - 成功返回RawData的数据长度(字节数); -1:RawData Size过小; -2: 非ST_SDPACK类记录或记录不存在; -3: 无效句柄Handle
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 指定的记录号 [0..RecordCount-1]
   // 参数  : char * RawData [OUT]: 存放读取的RawData数据块 
   // 参数  : int RawDataSize [IN]: RawData数据块的可存放的最长长度
   BCCCLT_API  int BCGetRawRecord(BCHANDLE Handle, int Row, char * RawData, int RawDataSize);

   // 描述  : 检查应答数据中，是否有指定字段的值
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 指定的记录号 [0..RecordCount-1]
   // 参数  : char *FieldName [IN]: 字段名称 如"vsmess"
   BCCCLT_API  bool BCIsValidField(BCHANDLE Handle, int Row, char *FieldName);

   //////////////////////////////////////////////////////////////////////////
   // 获取应答包中各条记录中的字段值

   // 描述  : 从数据区读取第Row条记录中的对应字段的值 (int)
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : int* Value [OUT]: 返回得到的值
	BCCCLT_API  bool BCGetIntFieldByName(BCHANDLE Handle,int Row,char * FieldName,int * Value);

   // 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : double* Value [OUT]: 返回得到的值
	BCCCLT_API  bool BCGetDoubleFieldByName(BCHANDLE Handle,int Row,char * FieldName,double * Value);

   // 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : char * Value [OUT]: 返回得到的值
   // 参数  : int ValueBufferSize [IN]: Value缓存区的长度（即可以存放的最大长度） 一般可以为 <=256
	BCCCLT_API  bool BCGetStringFieldByName(BCHANDLE Handle,int Row,char * FieldName,char * Value,int ValueBufferSize);

   //////////////////////////////////////////////////////////////////////////
   // 

   // 描述  : 获取本格式的XPack中最大的有效字段索引值
   // 返回  : int 返回ST_PACK中的最大有效字段索引值
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
	BCCCLT_API  int BCGetMaxColumn(BCHANDLE Handle);

   // 描述  : 根据字段名称，获得字段索引号
   // 返回  : int >=0 为本XPACK中有效字段，返回的值即为索引号；-1为本XPACK中没有这个字段; -2: 无效句柄
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
	BCCCLT_API  int BCGetFieldColumn(BCHANDLE Handle, char * FieldName);
   
   // 描述  : 取得对应字段的类型(与BCNewHandle中输入的结构定义文件相关)
   // 返回  : int  : 0 - 空字段; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
   //                -1 字段索引不存在或Handle错误
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : char * FieldName [IN]: 指定的字段名称,如"vsmess"
   BCCCLT_API  int BCGetFieldTypeByName(BCHANDLE Handle,char * FieldName);

   // 描述  : 读取指定字段的信息
   // 返回  : bool : true-为有效字段
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Col [IN]: 指定的字段索引号
   // 参数  : char * FieldName [OUT]: 返回指定的字段名称
   // 参数  : int* FieldType [OUT]: 指定的字段类型
   // 参数  : int* FieldLength [OUT]: 指定的字段长度
	BCCCLT_API  bool BCGetFieldInfo(BCHANDLE Handle,int Col, char * FieldName, int * FieldType, int * FieldLength);

   // 描述  : 当需要在一次请求的时候，请求数据需要发送多记录的时候，为了获得一次能够发送多少记录，
   //         需要在第一条记录用SetxxxxFieldByName完整后，才可调用本函数。
   //          注意：所有记录使用的字段必须相同，即就是第一条记录设置的那些字段
   // 返回  : int ：返回最大可设置多少条记录
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   BCCCLT_API  int BCEmulateMaxRows(BCHANDLE Handle);

   // 描述  : 设置是否打开调试跟踪文件
   // 返回  : void 
   // 参数  : bool bDebug [IN]: 0(false) - off; 1(true) - on
   BCCCLT_API  void BCSetDebugSwitch(bool bDebug);

   // 描述  : 将前面设置好XPack请求数据向所有符合条件的服务端(destno:funcno)广播
   //          注意:由于接收端可能许多，这种模式如同BCC架构中的推送消息0模式处理
   //                接收端不要发送应答或确认消息；本端也不要接收
   //                本功能只能在DRTP4版本上实现；DRTP3一概返回false
   // 返回  : bool 
   // 参数  : BCHANDLE Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int drtpno [IN]: 从那个直联的业务通讯平台节点广播数据，参见BCAddDrtpNode()的返回值
   // 参数  : int branchno [IN]: 目标应用服务连接的业务通讯平台节点编号 >=0;  =0: 则全网广播,否则就在指定节点上的广播
   // 参数  : int function [IN]: 目标应用服务注册在业务通讯平台的用于接收广播的功能号（常常为通用功能号或专门接收广播的功能号）
   // 参数  : int* errcode [OUT]: 返回的错误码
   // 参数  : char *errmsg [OUT]: 需要512字节空间，返回错误信息
   BCCCLT_API bool BCBroad(BCHANDLE Handle, int drtpno, int destno, int funcno, int *errcode, char *errmsg);
   

#ifdef __cplusplus
}
#endif

#undef BCCCLT_API
   

#endif
