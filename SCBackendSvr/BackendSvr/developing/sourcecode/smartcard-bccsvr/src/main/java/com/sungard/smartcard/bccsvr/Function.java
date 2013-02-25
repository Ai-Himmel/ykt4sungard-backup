/*
 * Function.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	Function.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

/**
 * 方法类 用于设置保存各种处理方法
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-19
 * 
 */
public class Function {
    public static final int NOTIFY_0_INFO = 1; // 0类通知消息
    public static final int NOTIFY_1_INFO = 2; // 1类通知消息
    public static final int Q_A_INFO = 3; // 正常客户端请求数据，需要用PutRow/DataDone给出应答
    
    
    
    /*
     * 消息类型
     */
    private int InfoType = 0;
    /*
     * 消息号
     */
    private int RequestType = 0;
    /*
     * 主处理方法接口
     */
    private ServiceI service;
    /*
     * 事前处理接口
     */
    private ServiceI before = null;
    /*
     * 事后处理接口
     */
    private ServiceI after = null;
    /*
     * 错误号和错误消息
     */
    public int errorCode = 0;
    public String errorMsg = "";

    public Function(int it, int rt, ServiceI s) {
        InfoType = it;
        RequestType = rt;
        service = s;
    }

    public int GetInfoType() {
        return InfoType;
    }

    public void SetInfoType(int t) {
        InfoType = t;
    }

    public int GetRequestType() {
        return RequestType;
    }

    public void SetRequestType(int t) {
        RequestType = t;
    }

    public void SetBeforeService(ServiceI s) {
        before = s;
    }

    public void SetDoService(ServiceI s) {
        service = s;
    }

    public void SetAfterService(ServiceI s) {
        after = s;
    }

    /**
     * 消息处理过程
     * 
     * @param session
     * @return
     */
    public boolean doProcess(BccServerThread session) {
        boolean ret = true;

        if (before != null) {
            ret = before.doService(this, session);
        }
        if (false == ret)
            return ret;

        if (service != null) {
            ret = service.doService(this, session);
        }
        if (false == ret)
            return ret;

        if (after != null) {
            ret = after.doService(this, session);
        }

        return ret;
    }
}
