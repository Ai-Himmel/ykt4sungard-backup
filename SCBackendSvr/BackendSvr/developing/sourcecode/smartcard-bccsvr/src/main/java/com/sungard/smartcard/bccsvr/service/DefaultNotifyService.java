/*
 * DefaultNotifyService.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	DefaultNotifyService.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.service;

import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;

/**
 * 缺省0类消息处理方法类.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-19
 * 
 */
@SmartCardFunction(infotype = 0, funcnum = 997, name = "Notify0")
public class DefaultNotifyService implements ServiceI {

    public DefaultNotifyService() {
        super();
    }

    public boolean doService(Function func, BccServerThread session) {
        switch (func.GetInfoType()) {
        case Function.NOTIFY_0_INFO:
            System.out.println("通知0");
            break;
        case Function.NOTIFY_1_INFO:
            System.out.println("通知1");
            break;
        }

        return true;
    }
}