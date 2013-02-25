/*
 * BccServerThread.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	BccServerThread.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.kingstar.bcc.bccsvr;

/**
 * 服务线程.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-19
 * 
 */
public class BccServerThread implements Runnable {

    private Logger logger = LoggerFactory.getLogger(BccServerThread.class);

    /*
     * 内部线程
     */
    private Thread reactor = null;
    private boolean flag = true;
    /*
     * 内部默认请求号，用于做缺省方法
     */
    final int _DEFAULT_FUNC = 999;
    final int _DEFAULT_NOTIFY1 = 998;
    final int _DEFAULT_NOTIFY0 = 997;
    /*
     * 资源对象，全局只有一个
     */
    private bccsvr resource = null;
    /*
     * 该资源的生成句柄
     */
    private long Handle = -1;
    /*
     * 被创建的内部服务号
     */
    private int svrID = -1;
    /*
     * 通讯的错误代码
     */
    private int errcode = 0;
    /*
     * 通讯的错误信息
     */
    private String errormessage = null;
    /**
     * 扩展接口，可以放置所有消息处理方法对象
     */
    private static HashMap processes = null;

    // ///////////////////////////////////////////////////////////

    /**
     * 构造方法
     */
    public BccServerThread(bccsvr res, long handle) {
        resource = res;
        Handle = handle;
        if (processes == null) {
            processes = new HashMap();
        }

        /*
         * 注册缺省方法对象
         */
        // RegisterFunction(new Function(1, _DEFAULT_NOTIFY0, new
        // DefaultNotifyService()));
        // RegisterFunction(new Function(2, _DEFAULT_NOTIFY1, new
        // DefaultNotifyService()));
        // RegisterFunction(new Function(3, _DEFAULT_FUNC, new
        // DefaultService()));
    }

    public void setFlag(boolean flag) {
        this.flag = flag;
    }

    public long getHandle() {
        return Handle;
    }

    /*
     * 释放句柄资源 (non-Javadoc)
     * 
     * @see java.lang.Object#finalize()
     */
    protected void finalize() {
        System.out.println("finalize:" + Handle);
        resource.DeleteXpackHandle(Handle);
    }

    public boolean Start(ThreadGroup tg, int svrID) {
        if (BindService(svrID) < 0) {
            System.out.println("Server BindService Fail..");
            return false;
        }
        // reactor = new Thread(this);
        reactor = new Thread(tg, this);
        reactor.start();
        System.out.println("Server Session Start..");
        return true;
    }

    /**
     * 启动会话线程，同时负责建立连接，注册/绑定服务
     * 
     * @param branchno
     * @param ip
     * @param port
     * @param funcno
     * @return
     */
    public boolean Start(int branchno, String ip, int port, int funcno) {

        svrID = AddService(branchno, ip, port, funcno, true);
        if (svrID < 0) {
            System.out.println("Server AddService Fail..");
            return false;
        }
        if (BindService(svrID) < 0) {
            System.out.println("Server BindService Fail..");
            return false;
        }
        reactor = new Thread(this);
        reactor.start();
        System.out.println("Server Session Start..");
        return true;
    }

    /**
     * 停止会话，清除服务
     * 
     * @return
     */
    public boolean Stop() {

        reactor.destroy();
        reactor = null;
        if (RemoveService(svrID) == false)
            return false;
        return true;
    }

    /**
     * 注册方法
     * 
     * @param func
     */
    public void RegisterFunction(Function func) {
        processes.put(new Integer(func.GetRequestType()), func);
    }

    public static boolean setProcesses(HashMap<Integer, Function> functonMap) {
        if (processes == null) {
            processes = new HashMap<Integer, Function>();
        }
        processes = functonMap;
        return true;
    }

    /**
     * 删除方法
     * 
     * @param func
     */
    public void RemoveFunction(Function func) {
        processes.remove(new Integer(func.GetRequestType()));
    }

    /**
     * 加载方法，至少会加载到一个默认方法
     * 
     * @param RequestType
     * @return
     * @throws Exception
     */
    private Function LoadFunction(int RequestType, int DefaultValue) throws Exception {

        logger.info("RequestType={}, DefaultValue={}", RequestType, DefaultValue);

        Function func = (Function) processes.get(new Integer(RequestType));
        if (null == func)
            func = (Function) processes.get(new Integer(DefaultValue));
        if (null == func) {
            throw new Exception("没有添加缺省方法");
        }
        return func;
    }

    /**
     * 内部运行线程
     */
    public void run() {
        try {
            do {
                // System.out.println("run() RecvMsg");
                int ret = ReceiveMsg();
                System.out.println("RecvMsg : " + ret);
                /*
                 * 返回 :1－0类通知消息； 2－1类通知消息； 3－正常客户端请求数据，需要用PutRow/DataDone给出应答 0:
                 * 一个后续数据返回处理完成，同-1一样继续处理； -1: 表示本次扫描各个Bind的Service都没有收到新的消息或请求
                 * （注意这种情况下不要狂扫描，本线程中加入少许等待） -2:
                 * 表示绑定的svrID连接出现问题了，errormessage中将会给出具体信息 <-2:
                 * 属于错误，参考errormessage信息 -3: 解码错误
                 */
                if (ret < -2) {
                    System.out.println("RecvMsg Error : " + this.GetErrorMessage());
                    continue;
                }
                if (ret == -2) {
                    System.out.println("RecvMsg Error : " + this.GetErrorMessage());
                    continue;
                }
                if (ret == -1) {
                    System.out.println("RecvMsg Warnning : 表示本次扫描各个Bind的Service都没有收到新的消息或请求");
                    Thread.sleep(1000);
                    continue;
                }
                if (ret == 1) {// 0类通知消息；
                    Function func = LoadFunction(GetRequestType(), _DEFAULT_NOTIFY0);
                    if (false == func.doProcess(this)) {
                        System.out.println(func.errorMsg);
                    }
                    continue;
                }
                if (ret == 2) {// 1类通知消息；
                    Function func = LoadFunction(GetRequestType(), _DEFAULT_NOTIFY1);
                    if (false == func.doProcess(this)) {
                        System.out.println(func.errorMsg);
                    }
                    continue;
                }
                if (ret == 3) {// 正常客户端请求数据，默认已用DataDone给出应答
                    System.out.println("  RequestType =" + GetRequestType() + "  Handle=" + Handle);
                    Function func = LoadFunction(GetRequestType(), _DEFAULT_FUNC);
                    if (false == func.doProcess(this)) {
                        System.out.println(func.errorMsg);
                    }
                    continue;
                }
                if (ret == 0) {
                    System.out.println("RecvMsg Return : 一个后续数据返回处理完成");
                    continue;
                }
            } while (flag);
            // } while (reactor != null);
            logger.info("---stop thread {}", reactor.getName());
        } catch (Exception ex) {

        }

    }

    /**
     * 返回错误代码
     * 
     * @return
     */
    public int GetErrCode() {
        return errcode;
    }

    /**
     * 返回错误信息
     * 
     * @return
     */
    public String GetErrorMessage() {
        return errormessage;
    }

    /**
     * 取得对应字段的类型(与NewXpackHandle中输入的结构定义文件相关) int : 0 - 空字段; 1-char; 2-vs_char;
     * 3-unsigned char; 4-int; 5-double -1 字段索引不存在或Handle错误
     * 
     * @param FieldName
     * @return
     */
    public int GetFieldTypeByName(String FieldName) {
        return resource.GetFieldTypeByName(Handle, FieldName.getBytes());
    }

    // 函数名: GetFieldInfo
    // 编程 : 陈永华 2005-11-17 15:11:24
    // 描述 : 读取指定字段的信息
    // 返回 : boolean : true-为有效字段
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Col [IN]: 指定的字段索引号
    // 参数 : byte[] FieldName [OUT]: 返回指定的字段名称
    // 参数 : int[] FieldType [OUT]: 指定的字段类型
    // 参数 : int[] FieldLength [OUT]: 指定的字段长度
    public XPackField GetFieldInfo(int Col) {
        byte[] FieldName = new byte[256];
        int[] FieldType = new int[2];
        int[] FieldLength = new int[2];

        if (false == resource.GetFieldInfo(Handle, Col, FieldName, FieldType, FieldLength)) {
            return null;
        }
        return new XPackField(Col, Convert4Bytes(FieldName), FieldType[0], FieldLength[0]);
    }

    public Object GetFieldByName(int Row, String FieldName) {
        int FieldType = GetFieldTypeByName(FieldName);
        // 0 - 空字段; 1-char; 2-vs_char;
        // 3-unsigned char; 4-int; 5-double
        // -1 字段索引不存在或Handle错误
        switch (FieldType) {
        case 0:
            return null;
        case 1:
            // return GetByteFieldByName(Row, FieldName);
            return GetStringFieldByName(Row, FieldName);
        case 2:
            return GetStringFieldByName(Row, FieldName);
        case 3:
            return GetStringFieldByName(Row, FieldName);
        case 4:
            return GetIntFieldByName(Row, FieldName);
        case 5:
            return GetDoubleFieldByName(Row, FieldName);
        case -1:
            return null;
        default:
            return null;
        }
    }

    /**
     * 从数据区读取第Row条记录中的对应字段的值 (int)
     * 
     * @param Row
     *            本包中指定的记录号 [0..RecordCount-1]
     * @param FieldName
     *            字段名称 如"vsmess"
     * @return 返回得到的值
     */
    public Integer GetIntFieldByName(int Row, String FieldName) {
        int[] Value = new int[2];
        if (false == resource.GetIntFieldByName(Handle, Row, FieldName.getBytes(), Value)) {
            return null;
        }
        return new Integer(Value[0]);
    }

    /**
     * 从数据区读取第Row条记录中的对应字段的值 (double)
     * 
     * @param Row
     *            本包中指定的记录号 [0..RecordCount-1]
     * @param FieldName
     *            字段名称 如"vsmess"
     * @return 返回得到的值
     */
    public Double GetDoubleFieldByName(int Row, String FieldName) {
        double[] Value = new double[2];
        if (false == resource.GetDoubleFieldByName(Handle, Row, FieldName.getBytes(), Value)) {
            return null;
        }
        return new Double(Value[0]);
    }

    public byte GetByteFieldByName(int Row, String FieldName) {

        byte[] Value = new byte[1];
        if (false == resource.GetStringFieldByName(Handle, Row, FieldName.getBytes(), Value, Value.length)) {
            return (Byte) null;
        }
        return new Byte(Value[0]);
    }

    /**
     * 从数据区读取第Row条记录中的对应字段的值 (double)
     * 
     * @param Row
     *            本包中指定的记录号 [0..RecordCount-1]
     * @param FieldName
     *            字段名称 如"vsmess"
     * @return 返回缓存区的长度（即可以存放的最大长度） 一般可以为 <=256
     */
    public String GetStringFieldByName(int Row, String FieldName) {
        byte[] Value = new byte[1024];
        if (false == resource.GetStringFieldByName(Handle, Row, FieldName.getBytes(), Value, Value.length)) {
            return null;
        }
        return Convert4Bytes(Value);
    }

    /**
     * 输出Xpack包协议字段的定义 方便二次开发和调试
     * 
     * @return
     */
    public List XpackFieldDefine(int colNum) {
        List Defines = new ArrayList();
        /**
         * 默认一个协议中的定义字段数量不会超过4096个 因为包文原则上不会超过4K
         */
        for (int Col = 0; Col <= colNum; Col++) {
            // for (int Col = 0; Col < 4096; Col++) {
            XPackField field = GetFieldInfo(Col);
            if (field != null) {
                switch (field.GetType()) {
                case 0:
                    break;
                case -1:
                    return Defines;
                default:
                    Defines.add(field);
                }
            } else {
                Defines.add(null);
            }
        }
        return Defines;
    }

    /**
     * 给一套更加简易的赋值方法,采用Map结构来表示字段数值
     * 
     * @return
     */
    public boolean SetFieldByNames(Vector fields) {
        for (int i = 0; i < fields.size(); i++) {
            Map obj = (Map) fields.get(i);
            if (!SetFieldByName((String) obj.get("name"), obj.get("value"))) {
                return false;
            }
        }
        return true;
    }

    /**
     * 按照字段名称来设置数据
     * 
     * @param Row
     * @param FieldName
     * @param Value
     * @return
     */
    public boolean SetFieldByName(String FieldName, Object Value) {
        if (Value instanceof Integer)
            return SetIntFieldByName(FieldName, ((Integer) Value).intValue());
        if (Value instanceof Double)
            return SetDoubleFieldByName(FieldName, ((Double) Value).doubleValue());
        if (Value instanceof String)
            return SetStringFieldByName(FieldName, (String) Value);

        return true;
    }

    /**
     * 设置指定数据区中第Row条记录中的对应字段的值
     * 
     * @param Row
     *            本包中指定的记录号 [0..RecordCount-1]
     * @param FieldName
     *            字段名称 如"vsmess"
     * @param Value
     *            数据值
     * @return
     */
    public boolean SetIntFieldByName(String FieldName, int Value) {
        return resource.SetIntFieldByName(Handle, FieldName.getBytes(), Value);
    }

    /**
     * 设置指定数据区中第Row条记录中的对应字段的值
     * 
     * @param Row
     *            本包中指定的记录号 [0..RecordCount-1]
     * @param FieldName
     *            字段名称 如"vsmess"
     * @param Value
     *            数据值
     * @return
     */
    public boolean SetDoubleFieldByName(String FieldName, double Value) {
        return resource.SetDoubleFieldByName(Handle, FieldName.getBytes(), Value);
    }

    /**
     * 设置指定数据区中第Row条记录中的对应字段的值
     * 
     * @param Row
     *            本包中指定的记录号 [0..RecordCount-1]
     * @param FieldName
     *            字段名称 如"vsmess"
     * @param Value
     *            数据值，不可以超过255长度
     * @return
     */
    public boolean SetStringFieldByName(String FieldName, String Value) {
        return resource.SetStringFieldByName(Handle, FieldName.getBytes(), Value.getBytes());
    }

    // / 对XPACK中RawData的读写操作：
    // 函数名: SetRawRecord
    // 编程 : 陈永华 2005-11-14 21:11:11
    // 描述 : 设置指定记录为指定的RawData记录
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : byte[] RawData [IN]: 要设置数据块
    // 参数 : int RawDataLength [IN]: 要设置数据块长度
    public boolean SetRawRecord(byte[] RawData, int RawDataLength) {
        return resource.SetRawRecord(Handle, RawData, RawDataLength);
    }

    // 函数名: GetRawRecord
    // 编程 : 陈永华 2005-11-14 21:11:15
    // 描述 : 当用GetXPackType返回为1即ST_SDPACK类的记录，则可以用本函数获取各个有效记录中的RawData记录
    // 返回 : int : >=0 - 成功返回RawData的数据长度(字节数)
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int Row [IN]: 指定的记录号 [0..RecordCount-1]
    // 参数 : byte[] RawData [OUT]: 存放读取的RawData数据块，在不定的情况下需分配8K字节的缓存
    // 参数 : int RawDataSize [IN]: RawData数据块的可存放的最长长度
    public int GetRawRecord(int Row, byte[] RawData, int RawDataSize) {
        return resource.GetRawRecord(Handle, Row, RawData, RawDataSize);
    }

    /**
     * 获取本格式的XPack中最大的有效字段索引值，与当时数据块不同
     * 
     * @return 返回ST_PACK中的最大有效字段索引值
     */
    public int GetMaxColumn() {
        return resource.GetMaxColumn(Handle);
    }

    /**
     * 根据字段名称，获得字段索引号
     * 
     * @param FieldName
     *            字段名称 如"vsmess"
     * @return int >=0 为本XPACK中有效字段，返回的值即为索引号；<0为本XPACK中没有这个字段
     */
    public int GetFieldColumn(String FieldName) {
        return resource.GetFieldColumn(Handle, FieldName.getBytes());
    }

    /**
     * 内部byte[]转为String的静态方法 不能直接用new String(byte[])来产生String对象
     * 因为byte[]是定长，不是实际长度
     * 
     * @param bytes
     * @return
     */
    private static String Convert4Bytes(byte[] bytes) {
        // System.out.println("Convert4Bytes");

        for (int length = 0; length < bytes.length; length++) {
            if ('\0' == bytes[length]) {
                return new String(bytes, 0, length);
            }
        }
        return null;
    }

    // 函数名: GetRecordCount
    // 编程 : 陈永华 2005-11-14 18:10:22
    // 描述 : 解包后读取本包中的记录数RecordCount
    // 返回 : int <0: 错误；>=0:成功返回当前接受到的数据记录数
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public int GetRecordCount() {
        return resource.GetRecordCount(Handle);
    }

    // 函数名: GetXPackType
    // 编程 : 陈永华 2005-11-14 21:11:05
    // 描述 : 查询当前数据块中数据记录类型
    // 返回 : int 返回数据记录类型 0-标准ST_PACK记录；1-ST_SDPACK的RawData记录; <0 － 错误的句柄
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public int GetXPackType(long Handle) {
        return resource.GetXPackType(Handle);
    }

    // 函数名: GetRequestType
    // 编程 : 陈永华 2006-7-11 14:06:12
    // 描述 : 取ReceiveMsg后得到数据的请求功能号
    // 返回 : int 请求功能号
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public int GetRequestType() {
        return resource.GetRequestType(Handle);
    }

    // 描述 : 取ReceiveMsg后得到数据的RetCode值
    // 返回 : int 消息或请求数据中的RetCode值
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public int GetRetCode() {
        return resource.GetRetCode(Handle);
    }

    // 描述 : 取ReceiveMsg后>0的得到数据是从哪个SvrID中取得的
    // 返回 : int 消息或请求数据是从哪个SvrID中取得的
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public int GetSvrID() {
        return resource.GetSvrID(Handle);
    }

    // 描述 : 用于0、1类消息，取消息编号，消息编号在XPACK协议中，是用Number*100+Day(两位日期)组成的
    // 返回 : int 返回消息编号即XPACK头中的hook.UserID
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public int GetMsgID() {
        return resource.GetMsgID(Handle);
    }

    // 描述 : 用于0、1类消息，取消息的来源ID
    // 返回 : int 返回消息来源ID即XPACK头中的hook.queuetype
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public int GetMsgSource() {
        return resource.GetMsgSource(Handle);
    }

    // 描述 : 用于0、1类消息，取消息的批次号
    // 返回 : int 返回消息批次号即XPACK头中的userdata
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    public int GetMsgBatchNo() {
        return resource.GetMsgBatchNo(Handle);
    }

    // 函数名: SetAPackMaxRows
    // 编程 : 陈永华 2005-11-14 21:11:00
    // 描述 : 设置应答包每次返回的最多记录数
    // 返回 : boolean
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int MaxRetCount [IN]: 指定的最多记录数，0则由自动控制 [0..100];
    public boolean SetAPackMaxRows(int MaxRows) {
        return resource.SetAPackMaxRows(Handle, MaxRows);
    }

    // /////////////////////////////////////////////////////////////////////////////////////
    // 与业务通讯平台相关的函数：

    // 函数名: AddService
    // 编程 : 陈永华 2006-6-15 11:24:25
    // 描述 : 增加一个通讯服务，包括连接的业务通讯平台节点参数，和为了接收消息或请求需要的通讯功能号，
    // 注意：basefno和privfno两者其中至少必须一个是有效的。
    // 返回 : int 返回业务通讯平台服务ID号；<0: 失败
    // 参数 : String ip [IN]: 该业务通讯平台的IP地址
    // 参数 : int port [IN]: 该业务通讯平台提供的端口号port
    // 参数 : int[] funlist [IN]: 在业务通讯平台上注册的功能号列表，其中其中第一个必须为私有功能号
    // 参数 : int funcount [IN]: 在业务通讯平台上注册的功能号个数，必须是>0
    // 参数 : boolean bretry [IN]: 是否当断开连接后，继续retry连接。
    // 1(true), 则当接收错误连接断开的时候，会重新不停连接，恢复接收，但ReceiveMsg不出现-2信息
    // 0(false)，则当连接断开时候，相关的ReceiveMsg过程中会接收到-2的信息，退出服务。
    public int AddService(int branchno, String ip, int port, int funcno, boolean bretry) {
        // Object[] FuncList = processes.keySet().toArray();

        int[] funclist = new int[3];
        funclist[0] = funcno + 1;
        funclist[1] = funcno;
        return resource.AddService(branchno, ip.getBytes(), port, funclist, 2, bretry);
    }

    // 函数名: RemoveService
    // 编程 : 陈永华 2006-8-25 16:38:58
    // 描述 : 中断服务连接
    // 返回 : boolean : 当服务连接编号错误，即svrID<0 或 svrID>=10 返回为false
    // 参数 : int svrID [IN]: 用AddService函数返回的通讯平台服务连接编号
    public boolean RemoveService(int svrID) {
        return resource.RemoveService(svrID);
    }

    // 函数名: BindService
    // 编程 : 陈永华 2006-6-15 11:24:25
    // 描述 : 将XPack数据处理句柄绑定通讯服务ID
    // 返回 : int 返回业务通讯平台服务ID号；<0: 失败
    // 参数 : long Handle [IN]: 指定的XPack数据区句柄
    // 参数 : int svrID [IN]: 通讯服务ID，即AddService(...)返回的ID
    public int BindService(int svrID) {
        return resource.BindService(Handle, svrID);
    }

    // 函数名: ReceiveMsg
    // 编程 : 陈永华 2006-6-31 21:42:08
    // 描述 : 作为服务，以被设置的通讯功能号，扫描接收消息或请求数据
    // 返回 : int 1－0类通知消息；2－1类通知消息；3－正常客户端请求数据，需要用PutRow/DataDone给出应答
    // 0: 一个后续数据返回处理完成，同-1一样继续处理；
    // -1: 表示本次扫描各个Bind的Service都没有收到新的消息或请求（注意这种情况下不要狂扫描，本线程中加入少许等待）
    // -2: 表示绑定的svrID连接出现问题了，errormessage中将会给出具体信息
    // <-2: 属于错误，参考errormessage信息 -3: 解码错误
    // 参数 : long Handle [IN] : 等待接收的XPACK数据缓存句柄
    // 参数 : byte[] errormessage [OUT] : 当返回码为<0的时候的错误信息
    public int ReceiveMsg() {
        byte[] Value = new byte[1024];
        int ret = resource.ReceiveMsg(Handle, Value, Value.length);

        errormessage = Convert4Bytes(Value);

        return ret;
    }

    // 函数名: PutRow
    // 编程 : 陈永华 2006-6-31 21:46:30
    // 描述 : 将当前缓存中的已经设置的数据(Row=0的)作为一条记录，准备完毕，可以提交给对方
    // 注意：在XPACK、CPACK协议中，该记录不会即时发送给对方，除非成为一个完整的包
    // （属于挤压出去的模式），每次都要用PutRow表示一条记录准备完毕，最后，
    // 通过调用DataDone，表示本次请求处理结束，没有更多的数据要给请求方。
    // 返回 : int : 返回成功>=0 或失败<0
    // 参数 : long Handle [IN] : 被操作的XPACK数据缓存句柄
    // 参数 : int retCode [IN] : 当前的返回码，一般在XPACK协议中0表示成功
    public int PutRow(int retCode) {
        return resource.PutRow(Handle, retCode);
    }

    // 函数名: DataDone
    // 编程 : 陈永华 2006-6-22 11:53:00
    // 描述 : 本次对请求数据处理结束，不再有信息返回给请求方
    // 返回 : int : 返回成功>=0 或失败<0
    // 参数 : long Handle [IN] : 被操作的XPACK数据缓存句柄
    // 参数 : int retCode [IN] : 当前的返回码，一般在XPACK协议中0表示成功
    public int DataDone(int retCode) {
        return resource.DataDone(Handle, retCode);
    }

    // 描述 : 清除此前通过SetXXXXFieldByName或SetRawData的数据，或更改返回记录的内容的字段项
    // 这个时候就会将前面的PutRow结果提交给请求方的。
    // 返回 : int >=0: 成功；<0: 失败
    // 参数 : long Handle [IN] : 被操作的XPACK数据缓存句柄
    public int ClearRow() {
        return resource.ClearRow(Handle);
    }

    // //////////////////////////////////////////////////////////////////////////////////
    // / 下面用于调试开发的时候，将所有进出的数据信息记录到KLG日志文件中
    // / 在开发阶段可以通过OpenKLGFile，则会将所有与本接口相关的重要的信息记录到KLG日志中
    // ////////////////////////////////////////////////////////////////////////
    // 函数名: KLGOpen
    // 编程 : 陈永华 2006-6-2 15:42:08
    // 描述 : 通过调用本函数，打开KLG日志文件，用于调试跟踪使用，
    // 注意：在release版本中，建议不要调用它，这会导致因为记录KLG日志而导致效率降低
    // 返回 : boolean
    // 参数 : String klgpath [IN]: KLG日志文件存放路径, 长度不要1K
    public boolean KLGOpen(String klgpath) {
        return resource.KLGOpen(klgpath.getBytes());
    }

    // 当调用KLGOpen后，可以调用本函数将（调试）信息记录到KLG文件中，其他相关函数只在接口内部使用
    // message的长度<1000
    public boolean KLGMsg(String message) {
        return resource.KLGMsg(message.getBytes());
    }

    // 删除过期文件
    // path_mark：删除的文件路径，不包括文件本身。必须加上相应的路径分割符如WINDOWS下的'\\'或UNIX下的'/'
    // ext：删除的文件扩展名，必须加上'.'
    public int RemoveOverdueFile(String path_mark, String ext, int overdue) {
        return resource.RemoveOverdueFile(path_mark.getBytes(), ext.getBytes(), overdue);
    }

}
