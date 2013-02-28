/********************************************************************
 created:	2006/05/31
 created:	31:5:2006   11:19
 filename: 	D:\proj\ksbass\bcclink\bccsvr\bccsvr.java
 file path:	D:\proj\ksbass\bcclink\bccsvr
 file base:	bccsvr
 file ext:	java
 author:		CHENYH

 purpose:	JAVA接口库，以服务方式通过业务通讯平台接收通知消息，
 同时也能接收请求，然后以服务方式返回请求的应答数据

 2006-11-27 10:39:32  将接口中的String参数，转换为byte[] 类型 － PeterX要求
 *********************************************************************/
package com.kingstar.bcc;

public class bccsvr {
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /// 下列函数与具体的数据无关，只是用于初试化XPACK，或对XPACK结构信息读取

    // 函数名: NewXpackHandle
    // 编程  : 陈永华 2006-11-14 17:57:39
    // 描述  : 构件一个用于XPack数据交换的数据区
    // 返回  : long : 返回该XPack数据区的句柄；==0(NULL): 失败
    // 参数  : byte[] XpackDescribleFile [IN]: XPack结构定义文件名，不能超过1024字节长，如: "/xpacks/cpack.dat"
    public native long NewXpackHandle(byte[] XpackDescribleFile);


    // 函数名: DeleteXpackHandle
    // 编程  : 陈永华 2006-11-14 18:08:08
    // 描述  : 将已经用NewXpackHandle得到的数据区释放(卸构)
    // 返回  : boolean
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native boolean DeleteXpackHandle(long Handle);

    // 函数名: GetMaxColumn
    // 编程  : 陈永华 2006-11-14 21:11:20
    // 描述  : 获取本格式的XPack中最大的有效字段索引值，与当时数据块不同
    // 返回  : int 返回ST_PACK中的最大有效字段索引值
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetMaxColumn(long Handle);

    // 函数名: GetFieldColumn
    // 编程  : 陈永华 2006-11-14 21:11:29
    // 描述  : 根据字段名称，获得字段索引号
    // 返回  : int >=0 为本XPACK中有效字段，返回的值即为索引号；<0为本XPACK中没有这个字段
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
    public native int GetFieldColumn(long Handle, byte[] FieldName);

    // 函数名: GetFieldInfo
    // 编程  : 陈永华 2006-11-17 15:11:24
    // 描述  : 读取指定字段的信息
    // 返回  : boolean : true-为有效字段
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : int Col [IN]: 指定的字段索引号
    // 参数  : byte[] FieldName [OUT]: 返回指定的字段名称, 给出64字节的空间
    // 参数  : int[] FieldType [OUT]: 指定的字段类型
    // 参数  : int[] FieldLength [OUT]: 指定的字段长度
    public native boolean GetFieldInfo(long Handle, int Col, byte[] FieldName, int[] FieldType, int[] FieldLength);

    // 函数名: GetFieldTypeByName
    // 编程  : 陈永华 2006-11-14 18:08:37
    // 描述  : 取得对应字段的类型(与NewXpackHandle中输入的结构定义文件相关)
    // 返回  : int  : 0 - 空字段; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double
    //                -1 字段索引不存在或Handle错误
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : byte[] FieldName [IN]: 指定的字段名称,如"vsmess"
    public native int GetFieldTypeByName(long Handle, byte[] FieldName);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// 下列接口则操作指定句柄缓存区的数据，与具体数据相关

    // 函数名: GetIntFieldByName
    // 编程  : 陈永华 2006-11-14 18:09:26
    // 描述  : 从数据区读取第Row条记录中的对应字段的值 (int)
    // 返回  : boolean
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数  : int[] Value [OUT]: 返回得到的值
    public native boolean GetIntFieldByName(long Handle, int Row, byte[] FieldName, int[] Value);

    // 函数名: GetDoubleFieldByName
    // 编程  : 陈永华 2006-11-14 18:09:31
    // 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
    // 返回  : boolean
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数  : double[] Value [OUT]: 返回得到的值
    public native boolean GetDoubleFieldByName(long Handle, int Row, byte[] FieldName, double[] Value);

    // 函数名: GetStringFieldByName
    // 编程  : 陈永华 2006-11-14 18:09:36
    // 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
    // 返回  : boolean
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数  : byte[] Value [OUT]: 返回得到的值，给出1024字节长度的空间
    // 参数  : int ValueBufferSize [IN]: Value缓存区的长度（即可以存放的最大长度）
    public native boolean GetStringFieldByName(long Handle, int Row, byte[] FieldName, byte[] Value, int ValueBufferSize);

    // 函数名: GetRecordCount
    // 编程  : 陈永华 2006-11-14 18:10:22
    // 描述  : 解包后读取本包中的记录数RecordCount
    // 返回  : int <0: 错误；>=0:成功返回当前接受到的数据记录数
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetRecordCount(long Handle);

    // 函数名: GetXPackType
    // 编程  : 陈永华 2006-11-14 21:11:05
    // 描述  : 查询当前数据块中数据记录类型
    // 返回  : int 返回数据记录类型 0-标准ST_PACK记录；1-ST_SDPACK的RawData记录; <0 － 错误的句柄
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetXPackType(long Handle);

    // 函数名: GetRawRecord
    // 编程  : 陈永华 2006-11-14 21:11:15
    // 描述  : 当用GetXPackType返回为1即ST_SDPACK类的记录，则可以用本函数获取各个有效记录中的RawData记录
    // 返回  : int : >=0 - 成功返回RawData的数据长度(字节数)
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : int Row [IN]: 指定的记录号 [0..RecordCount-1]
    // 参数  : byte[] RawData [OUT]: 存放读取的RawData数据块，在不定的情况下需分配8K字节的缓存
    // 参数  : int RawDataSize [IN]: RawData数据块的可存放的最长长度
    public native int GetRawRecord(long Handle, int Row, byte[] RawData, int RawDataSize);

    // 函数名: GetRequestType
    // 编程  : 陈永华 2006-7-11 14:06:12
    // 描述  : 取ReceiveMsg后得到数据的请求功能号
    // 返回  : int 请求功能号
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetRequestType(long Handle);

    // 描述  : 取ReceiveMsg后得到数据的RetCode值
    // 返回  : int 消息或请求数据中的RetCode值
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetRetCode(long Handle);

    // 描述  : 取ReceiveMsg后>0的得到数据是从哪个SvrID中取得的
    // 返回  : int 消息或请求数据是从哪个SvrID中取得的
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetSvrID(long Handle);

    // 描述  : 用于0、1类消息，取消息编号，消息编号在XPACK协议中，是用Number*100+Day(两位日期)组成的
    // 返回  : int 返回消息编号即XPACK头中的hook.UserID
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetMsgID(long Handle);

    // 描述  : 用于0、1类消息，取消息的来源ID
    // 返回  : int 返回消息来源ID即XPACK头中的hook.queuetype
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetMsgSource(long Handle);

    // 描述  : 用于0、1类消息，取消息的批次号
    // 返回  : int 返回消息批次号即XPACK头中的userdata
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    public native int GetMsgBatchNo(long Handle);

    //////////////////////////////////////////////////////////////////////////
    // 设置应答包数据部分的函数：
    ///////////////////////////////////////////////
    // 函数名: SetIntFieldByName
    // 编程  : 陈永华 2006-11-14 18:09:57
    // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
    // 返回  : boolean
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数  : int Value [IN]: 数据值
    public native boolean SetIntFieldByName(long Handle, byte[] FieldName, int Value);

    // 函数名: SetDoubleFieldByName
    // 编程  : 陈永华 2006-11-14 18:10:02
    // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
    // 返回  : boolean
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数  : double Value [IN]: 数据值
    public native boolean SetDoubleFieldByName(long Handle, byte[] FieldName, double Value);

    // 函数名: SetStringFieldByName
    // 编程  : 陈永华 2006-11-14 18:10:07
    // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
    // 返回  : boolean
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
    // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
    // 参数  : byte[] Value [IN]: 数据值，一般不可以超过255长度，除非该字段为binary类型，用0xXXXXXX...表示的数据值
    public native boolean SetStringFieldByName(long Handle, byte[] FieldName, byte[] Value);

    // 函数名: SetAPackMaxRows
    // 编程  : 陈永华 2006-11-14 21:11:00
    // 描述  : 设置应答包每次返回的最多记录数
    // 返回  : boolean
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : int MaxRetCount [IN]: 指定的最多记录数，0则由自动控制 [0..100];
    public native boolean SetAPackMaxRows(long Handle, int MaxRows);

    /// 对XPACK中RawData的读写操作：
    // 函数名: SetRawRecord
    // 编程  : 陈永华 2006-11-14 21:11:11
    // 描述  : 设置指定记录为指定的RawData记录
    // 返回  : boolean
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : byte[] RawData [IN]: 要设置数据块
    // 参数  : int RawDataLength [IN]: 要设置数据块长度
    public native boolean SetRawRecord(long Handle, byte[] RawData, int RawDataLength);

    ///////////////////////////////////////////////////////////////////////////////////////
    // 与业务通讯平台相关的函数：

    // 函数名: AddService
    // 编程  : 陈永华 2006-6-15 11:24:25
    // 描述  : 增加一个通讯服务，包括连接的业务通讯平台节点参数，和为了接收消息或请求需要的通讯功能号，
    //          注意：basefno和privfno两者其中至少必须一个是有效的。
    // 返回  : int 返回业务通讯平台服务ID号；<0: 失败
    // 参数  : byte[] ip [IN]: 该业务通讯平台的IP地址
    // 参数  : int port [IN]: 该业务通讯平台提供的端口号port
    // 参数  : int[] funlist [IN]: 在业务通讯平台上注册的功能号列表，其中其中第一个必须为私有功能号
    // 参数  : int funcount [IN]: 在业务通讯平台上注册的功能号个数，必须是>0
    // 参数  : boolean bretry [IN]: 是否当断开连接后，继续retry连接。
    //                           1(true), 则当接收错误连接断开的时候，会重新不停连接，恢复接收，但ReceiveMsg不出现-2信息
    //                           0(false)，则当连接断开时候，相关的ReceiveMsg过程中会接收到-2的信息，退出服务。
    public native int AddService(int branchno, byte[] ip, int port, int[] funlist, int funcount, boolean bretry);

    // 函数名: RemoveService
    // 编程  : 陈永华 2006-8-25 16:38:58
    // 描述  : 中断服务连接
    // 返回  : boolean : 当服务连接编号错误，即svrID<0 或 svrID>=10 返回为false
    // 参数  : int svrID [IN]: 用AddService函数返回的通讯平台服务连接编号
    public native boolean RemoveService(int svrID);

    // 函数名: BindService
    // 编程  : 陈永华 2006-6-15 11:24:25
    // 描述  : 将XPack数据处理句柄绑定通讯服务ID
    // 返回  : int 返回业务通讯平台服务ID号；<0: 失败
    // 参数  : long Handle [IN]: 指定的XPack数据区句柄
    // 参数  : int svrID [IN]: 通讯服务ID，即AddService(...)返回的ID
    public native int BindService(long Handle, int svrID);

    // 函数名: ReceiveMsg
    // 编程  : 陈永华 2006-6-31 21:42:08
    // 描述  : 作为服务，以被设置的通讯功能号，扫描接收消息或请求数据
    // 返回  : int    1－0类通知消息；2－1类通知消息；3－正常客户端请求数据，需要用PutRow/DataDone给出应答
    //                0: 一个后续数据返回处理完成，同-1一样继续处理；
    //                -1: 表示本次扫描各个Bind的Service都没有收到新的消息或请求（注意这种情况下不要狂扫描，本线程中加入少许等待）
    //                -2: 表示绑定的svrID连接出现问题了，errormessage中将会给出具体信息
    //                <-2: 属于错误，参考errormessage信息 -3: 解码错误
    // 参数  : long Handle [IN] : 等待接收的XPACK数据缓存句柄
    // 参数  : byte[] errormessage [OUT] : 当返回码为<0的时候的错误信息
    public native int ReceiveMsg(long Handle, byte[] errormessage, int emlen);


    // 函数名: PutRow
    // 编程  : 陈永华 2006-6-31 21:46:30
    // 描述  : 将当前缓存中的已经设置的数据(Row=0的)作为一条记录，准备完毕，可以提交给对方
    //          注意：在XPACK、CPACK协议中，该记录不会即时发送给对方，除非成为一个完整的包
    //             （属于挤压出去的模式），每次都要用PutRow表示一条记录准备完毕，最后，
    //             通过调用DataDone，表示本次请求处理结束，没有更多的数据要给请求方。
    // 返回  : int : 返回成功>=0 或失败<0
    // 参数  : long Handle [IN] : 被操作的XPACK数据缓存句柄
    // 参数  : int retCode [IN] : 当前的返回码，一般在XPACK协议中0表示成功
    public native int PutRow(long Handle, int retCode);


    // 函数名: DataDone
    // 编程  : 陈永华 2006-6-22 11:53:00
    // 描述  : 本次对请求数据处理结束，不再有信息返回给请求方
    // 返回  : int : 返回成功>=0 或失败<0
    // 参数  : long Handle [IN] : 被操作的XPACK数据缓存句柄
    // 参数  : int retCode [IN] : 当前的返回码，一般在XPACK协议中0表示成功
    public native int DataDone(long Handle, int retCode);


    // 描述  : 清除此前通过SetXXXXFieldByName或SetRawData的数据，或更改返回记录的内容的字段项
    //          这个时候就会将前面的PutRow结果提交给请求方的。
    // 返回  : int >=0: 成功；<0: 失败
    // 参数  : long Handle [IN] : 被操作的XPACK数据缓存句柄
    public native int ClearRow(long Handle);

    ////////////////////////////////////////////////////////////////////////////////////
    /// 下面用于调试开发的时候，将所有进出的数据信息记录到KLG日志文件中
    /// 在开发阶段可以通过OpenKLGFile，则会将所有与本接口相关的重要的信息记录到KLG日志中
    //////////////////////////////////////////////////////////////////////////
    // 函数名: KLGOpen
    // 编程  : 陈永华 2006-6-2 15:42:08
    // 描述  : 通过调用本函数，打开KLG日志文件，用于调试跟踪使用，
    //       注意：在release版本中，建议不要调用它，这会导致因为记录KLG日志而导致效率降低
    // 返回  : boolean
    // 参数  : byte[] klgpath [IN]: KLG日志文件存放路径, 长度不要1K
    public native boolean KLGOpen(byte[] klgpath);

    // 当调用KLGOpen后，可以调用本函数将（调试）信息记录到KLG文件中，其他相关函数只在接口内部使用
    // message的长度<1000
    public native boolean KLGMsg(byte[] message);

    // 删除过期文件
    // path_mark：删除的文件路径，不包括文件本身。必须加上相应的路径分割符如WINDOWS下的'\\'或UNIX下的'/'
    // ext：删除的文件扩展名，必须加上'.'
    public native int RemoveOverdueFile(byte[] path_mark, byte[] ext, int overdue);

    static {
        System.loadLibrary("bccsvr");
    }
}
