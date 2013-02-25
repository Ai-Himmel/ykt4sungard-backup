/*
 * InfoType.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	InfoType.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.annotation;

/**
 * 消息类型. <br/>
 * <br/>
 * NOTIFY_0_INFO = 1; // 0类通知消息<br/>
 * NOTIFY_1_INFO = 2; // 1类通知消息<br/>
 * Q_A_INFO = 3; // 正常客户端请求数据，需要用PutRow/DataDone给出应答<br/>
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-19
 * 
 */
public enum InfoType {

    NOTIFY_0_INFO, NOTIFY_1_INFO, Q_A_INFO

}
