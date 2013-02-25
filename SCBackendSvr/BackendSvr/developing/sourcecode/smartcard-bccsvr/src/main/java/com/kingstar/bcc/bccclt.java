/********************************************************************
	created:	2006/05/29
	created:	29:5:2006   16:56
	filename: 	D:\proj\ksbass\bcclink\bccclt\bccclt.java
	file path:	D:\proj\ksbass\bcclink\bccclt
	file base:	bccclt
	file ext:	java
	author:		CHENYH
	
	purpose:	JAVA接口库，以客户方式通过业务通讯平台调用BCC业务功能
 *********************************************************************/
package com.kingstar.bcc;

/**
 * 客户类本地方法.
 */
public class bccclt {
    // 函数名: SetDebugSwitch
    // 编程 : 陈永华 2006-8-24 10:26:51
    // 描述 : 设置是否打开调试跟踪文件
    // 返回 : void
    // 参数 : bool bDebug [IN]: 0(false) - off; 1(true) - on
    public native boolean SetDebugSwitch(boolean bDebug);

    // 函数名: XPackInit
    // 编程 : 陈永华 2005-11-15 11:18:52
    // 描述 : 预先设置本系统一共将有多少个XpackDescribleFile文件，相同的即使有多个XPack数据区句柄，仍然算一个
    // Notice: 一个系统只能调用设置一次
    // 返回 : boolean
    // 参数 : int maxXPackDefs [IN]: 设置的XpackDescribleFile文件数，参考NewXpackHandle()方法
    public native boolean XPackInit(int maxXPackDefs);

    // 函数名: NewXpackHandle
    // 编程 : 陈永华 2005-11-14 17:57:39
    // 描述 : 构件一个用于XPack数据交换的数据区
    // 返回 : long : 返回该XPack数据区的句柄；==0(NULL): 失败
    // 参数 : byte[] XpackDescribleFile [IN]: XPack结构定义文件名，不能超过1024字节长，如:
    // "/xpacks/cpack.dat"
    public native long NewXpackHandle(byte[] XpackDescribleFile);

    // 函数名: ResetPackHandle
    // 编程 : 陈永华 2005-11-14 18:01:30
    // 描述 : 重置数据区内容，主要用于准备首包请求时，填写具体请求数据字段之前调用
    // 返回 : boolean : false - 往往为错误的Handle(==NULL的时候)
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public native boolean ResetPackHandle(long Handle);

    // 函数名: CopyHandle
    // 编程 : 陈永华 2005-11-14 18:04:56
    // 描述 : 将SourceHandle中的状态、格式、数据等信息复制到DestHandle中
    // 返回 : boolean : false - 往往为错误的Handle(==NULL的时候)
    // 参数 : long SourceHandle [IN]: 被复制的原XPack数据区句柄
    // 参数 : long DestHandle [OUT]: 被复制的目标XPack数据区句柄，内部数据被覆盖，但不会新派生一个句柄
    public native boolean CopyHandle(long SourceHandle, long DestHandle);

    // 函数名: DeleteXpackHandle
    // 编程 : 陈永华 2005-11-14 18:08:08
    // 描述 : 将已经用NewXpackHandle得到的数据区释放(卸构)
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public native boolean DeleteXpackHandle(long Handle);

    // 函数名: GetFieldTypeByName
    // 编程 : 陈永华 2005-11-14 18:08:37
    // 描述 : 取得对应字段的类型(与NewXpackHandle中输入的结构定义文件相关)
    // 返回 : int : 0 - 空字段; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double
    // -1 字段索引不存在或Handle错误
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : byte[] FieldName [IN]: 指定的字段名称,如"vsmess"
    public native int GetFieldTypeByName(long Handle, byte[] FieldName);

    // 函数名: GetIntFieldByName
    // 编程 : 陈永华 2005-11-14 18:09:26
    // 描述 : 从数据区读取第Row条记录中的对应字段的值 (int)
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数 : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数 : int[] Value [OUT]: 返回得到的值
    public native boolean GetIntFieldByName(long Handle, int Row, byte[] FieldName, int[] Value);

    // 函数名: GetDoubleFieldByName
    // 编程 : 陈永华 2005-11-14 18:09:31
    // 描述 : 从数据区读取第Row条记录中的对应字段的值 (double)
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数 : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数 : double[] Value [OUT]: 返回得到的值
    public native boolean GetDoubleFieldByName(long Handle, int Row, byte[] FieldName, double[] Value);

    // 函数名: GetStringFieldByName
    // 编程 : 陈永华 2005-11-14 18:09:36
    // 描述 : 从数据区读取第Row条记录中的对应字段的值 (double)
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数 : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数 : byte[] Value [OUT]: 返回得到的值
    // 参数 : int ValueBufferSize [IN]: Value缓存区的长度（即可以存放的最大长度） 一般可以为 <=256
    public native boolean GetStringFieldByName(long Handle, int Row, byte[] FieldName, byte[] Value, int ValueBufferSize);

    // 函数名: SetIntFieldByName
    // 编程 : 陈永华 2005-11-14 18:09:57
    // 描述 : 设置指定数据区中第Row条记录中的对应字段的值
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数 : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数 : int Value [IN]: 数据值
    public native boolean SetIntFieldByName(long Handle, int Row, byte[] FieldName, int Value);

    // 函数名: SetDoubleFieldByName
    // 编程 : 陈永华 2005-11-14 18:10:02
    // 描述 : 设置指定数据区中第Row条记录中的对应字段的值
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数 : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数 : double Value [IN]: 数据值
    public native boolean SetDoubleFieldByName(long Handle, int Row, byte[] FieldName, double Value);

    // 函数名: SetStringFieldByName
    // 编程 : 陈永华 2005-11-14 18:10:07
    // 描述 : 设置指定数据区中第Row条记录中的对应字段的值
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数 : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数 : byte[] Value [IN]: 数据值，不可以超过255长度
    public native boolean SetStringFieldByName(long Handle, int Row, byte[] FieldName, byte[] Value);

    // 函数名: SetRequestType
    // 编程 : 陈永华 2005-11-14 18:10:12
    // 描述 : 设置请求数据中的功能号 （在EncodeXpackForRequest之前一定要设置）
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int RequestType [IN]: 对应的业务功能号
    public native boolean SetRequestType(long Handle, int RequestType);

    // 函数名: IsEof
    // 编程 : 陈永华 2005-11-14 18:10:17
    // 描述 : 是否已经是最后一个应答包了，和HaveNextPack正好相反
    // 返回 : boolean : true - 表示已经没有后续应答数据包了；false - 要通过调用EncodeXpackForNext后续包
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public native boolean IsEof(long Handle);

    // 函数名: GetRecordCount
    // 编程 : 陈永华 2005-11-14 18:10:22
    // 描述 : 解包后读取本包中的记录数RecordCount
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int[] RecordCount [OUT]: 返回解包后的记录数
    public native boolean GetRecordCount(long Handle, int[] RecordCount);

    // 函数名: GetRetCode
    // 编程 : 陈永华 2005-11-14 18:10:28
    // 描述 : 解包后读取其返回码
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int[] RetCode [OUT]: 返回收到数据包中的返回码
    public native boolean GetRetCode(long Handle, int[] RetCode);

    // 函数名: GetPrivateFunctionForNext
    // 编程 : 陈永华 2005-11-14 21:10:48
    // 描述 : 根据收得解码后的数据，从中得到属于可以获取后续应答数据包的应用服务器专用通讯功能号
    // 详细技术请参考KSBCC使用说明书
    // 返回 : int : >0 - 可获取后续数据的专用通讯功能号；否则失败
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetPrivateFunctionForNext(long Handle);

    // 函数名: GetBranchNoForNext
    // 编程 : 陈永华 2005-11-14 21:10:52
    // 描述 : 根据收得解码后的数据，从中得到属于可以获取后续应答数据包的目标通讯平台节点编号
    // 详细技术请参考KSMBCC使用说明书
    // 返回 : int >0: 获取后续应答数据包的目标通讯平台节点编号; 否则还是用原来的节点编号
    // 当该功能是用Transfer实现的时候，需要这个可能被变更了的节点号
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetBranchNoForNext(long Handle);

    // 函数名: SetRecordCount
    // 编程 : 陈永华 2005-11-14 21:10:56
    // 描述 : 预设置请求数据中的记录数
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int RecordCount [IN]: 设置的记录数
    public native boolean SetRecordCount(long Handle, int RecordCount);

    // 函数名: SetMaxRetCount
    // 编程 : 陈永华 2005-11-14 21:11:00
    // 描述 : 设置应答包每次返回的最多记录数
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int MaxRetCount [IN]: 指定的最多记录数，0则由应用服务器端 [0..100];
    public native boolean SetMaxRetCount(long Handle, int MaxRetCount);

    // 函数名: GetXPackType
    // 编程 : 陈永华 2005-11-14 21:11:05
    // 描述 : 查询当前数据块中数据记录类型
    // 返回 : int 返回数据记录类型 0-标准ST_PACK记录；1-ST_SDPACK的RawData记录
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetXPackType(long Handle);

    // 函数名: SetRawRecord
    // 编程 : 陈永华 2005-11-14 21:11:11
    // 描述 : 设置指定记录为指定的RawData记录
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Row [IN]: 指定设置的记录号 [0..RecordCount-1]
    // 参数 : byte[] RawData [IN]: 要设置数据块
    // 参数 : int RawDataLength [IN]: 要设置数据块长度
    public native boolean SetRawRecord(long Handle, int Row, byte[] RawData, int RawDataLength);

    // 函数名: GetRawRecord
    // 编程 : 陈永华 2005-11-14 21:11:15
    // 描述 : 当用GetXPackType返回为1即ST_SDPACK类的记录，则可以用本函数获取各个有效记录中的RawData记录
    // 返回 : int : >=0 - 成功返回RawData的数据长度(字节数)
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Row [IN]: 指定的记录号 [0..RecordCount-1]
    // 参数 : byte[] RawData [OUT]: 存放读取的RawData数据块
    // 参数 : int RawDataSize [IN]: RawData数据块的可存放的最长长度
    public native int GetRawRecord(long Handle, int Row, byte[] RawData, int RawDataSize);

    // 函数名: GetMaxColumn
    // 编程 : 陈永华 2005-11-14 21:11:20
    // 描述 : 获取本格式的XPack中最大的有效字段索引值，与当时数据块不同
    // 返回 : int 返回ST_PACK中的最大有效字段索引值
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetMaxColumn(long Handle);

    // 函数名: GetFieldColumn
    // 编程 : 陈永华 2005-11-14 21:11:29
    // 描述 : 根据字段名称，获得字段索引号
    // 返回 : int >=0 为本XPACK中有效字段，返回的值即为索引号；<0为本XPACK中没有这个字段
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : byte[] FieldName [IN]: 字段名称 如"vsmess"
    public native int GetFieldColumn(long Handle, byte[] FieldName);

    // 函数名: GetFieldInfo
    // 编程 : 陈永华 2005-11-17 15:11:24
    // 描述 : 读取指定字段的信息
    // 返回 : boolean : true-为有效字段
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Col [IN]: 指定的字段索引号
    // 参数 : byte[] FieldName [OUT]: 返回指定的字段名称
    // 参数 : int[] FieldType [OUT]: 指定的字段类型
    // 参数 : int[] FieldLength [OUT]: 指定的字段长度
    public native boolean GetFieldInfo(long Handle, int Col, byte[] FieldName, int[] FieldType, int[] FieldLength);

    // 函数名: HaveNextPack
    // 编程 : 陈永华 2005-11-14 22:01:15
    // 描述 : 当解码后，通过本函数判断是否还有后续应答包
    // 返回 : boolean : true-表示还有后续应答包；false－无后续包
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public native boolean HaveNextPack(long Handle);

    // /////////////////////////////////////////////////////////////////////////////////////
    // 与业务通讯平台相关的函数：

    // 函数名: BCCCLTInit
    // 编程 : 陈永华 2005-11-15 11:22:35
    // 描述 : 初试化本系统将直接连接多少个业务通讯平台节点个数
    // Notice: 系统只能调用一次
    // 返回 : boolean
    // 参数 : int maxnodes=1 [IN]: 设置最多会有多少个连接节点
    public native boolean BCCCLTInit(int maxnodes);

    // 函数名: AddDrtpNode
    // 编程 : 陈永华 2005-11-15 11:24:25
    // 描述 : 增加一个要直接连接的业务通讯平台节点
    // 作为系统初试化部分，建议在调用BCCCLTInit后，在统一一个线程里一次性的设置完毕，供整个环境使用
    // 返回 : int 增加的业务通讯平台节点编号 >=0:成功；否则，可能没有正确调用BCCCLTInit()
    // 参数 : byte[] ip [IN]: 该业务通讯平台的IP地址
    // 参数 : int port [IN]: 该业务通讯平台提供的端口号port
    public native int AddDrtpNode(byte[] ip, int port);

    // 函数名: CallRequest
    // 编程 : 陈永华 2005-11-15 11:27:07
    // 描述 : 将前面设置好XPack请求数据打包发送给指定的通讯平台和应用服务器
    // 返回 : boolean : true 成功发送，并且接收解码了应答数据；false 操作失败，具体错误，参见错误码
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int drtpno [IN]: 从那个直联的业务通讯平台节点发送和接收数据，参见AddDrtpNode()的返回值
    // 参数 : int branchno [IN]: 目标应用服务器连接的业务通讯平台节点编号（参见业务通讯平台的配置参数表）
    // 参数 : int function [IN]: 目标应用服务器注册在业务通讯平台的功能号 (参见BCC配置文件中的BASEFUNCNO)
    // 参数 : int timeout [IN]: 发送接收数据的超时时间，以毫秒计
    // 参数 : int[] errcode [OUT]: 返回的错误码
    // 参数 : byte[] errormessage [OUT]: 返回的错误信息
    public native boolean CallRequest(long Handle, int drtpno, int branchno, int function, int timeout, int[] errcode,
            byte[] errormessage);

    // 函数名: CallNext
    // 编程 : 陈永华 2005-11-15 11:30:38
    // 描述 : 取下一个后续应答包
    // 在成功调用CallRequest后，如果检查到HaveNextPack()后，则用本功能获取下一个后续应答包
    // 返回 : boolean ：true 成功发送，并且接收解码了应答数据；false 操作失败，具体错误，参见错误码
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int timeout [IN]: 发送接收数据的超时时间，以毫秒计
    // 参数 : int[] errcode [OUT]: 返回的错误码
    // 参数 : byte[] errormessage [OUT]: 返回的错误信息
    public native boolean CallNext(long Handle, int timeout, int[] errcode, byte[] errormessage);

    // 函数名: EmulateMaxRows
    // 编程 : 陈永华 2006-8-23 9:53:42
    // 描述 : 当需要在一次请求的时候，请求数据需要发送多记录的时候，为了获得一次能够发送多少记录，
    // 需要在第一条记录用SetxxxxFieldByName完整后，才可调用本函数。
    // 注意：所有记录使用的字段必须相同，即就是第一条记录设置的那些字段
    // 返回 : int ：返回最大可设置多少条记录
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public native int EmulateMaxRows(long Handle);

    // 函数名: Broad
    // 编程 : 陈永华 2006-8-25 18:41:34
    // 描述 : 将前面设置好XPack请求数据向所有符合条件的服务端(destno:funcno)广播
    // 注意:由于接收端可能许多，这种模式如同BCC架构中的推送消息0模式处理
    // 接收端不要发送应答或确认消息；本端也不要接收
    // 本功能只能在DRTP4版本上实现；DRTP3一概返回false
    // 返回 : boolean:
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int drtpno [IN]: 从那个直联的业务通讯平台节点广播数据，参见AddDrtpNode()的返回值
    // 参数 : int branchno [IN]: 目标应用服务连接的业务通讯平台节点编号 >=0; =0: 则全网广播,否则就在指定节点上的广播
    // 参数 : int funcno [IN]: 目标应用服务注册在业务通讯平台的用于接收广播的功能号（常常为通用功能号或专门接收广播的功能号）
    // 参数 : int* errcode [OUT]: 返回的错误码
    // 参数 : char *errmsg [OUT]: 需要512字节空间，返回错误信息
    public native boolean Broad(long Handle, int drtpno, int destno, int funcno, int[] errcode, byte[] errmsg);

    static {
        System.loadLibrary("bccclt");
    }
}
