/*
 * TransfersElement.java  v1.00  2011-12-11
 * Peoject	smartcard-simple
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	TransfersElement.java  v1.00 2011-12-11
 * Project	: 	smartcard-simple
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * 传输对象.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-11
 * 
 */
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface TransfersElement {
	String value() default "";
}
