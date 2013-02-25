/*
 * TransfersNodeIn.java  v1.00  2011-12-31
 * Peoject	smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	TransfersNodeIn.java  v1.00 2011-12-31
 * Project	: 	smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * 获取(接收)节点.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-31
 * 
 */
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.FIELD)
public @interface TransfersNodeIn {
    TransfersNodeType value();

    String desc() default "";
}
