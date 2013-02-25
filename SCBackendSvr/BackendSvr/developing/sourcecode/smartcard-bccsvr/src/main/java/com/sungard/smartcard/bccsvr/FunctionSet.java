/*
 * FunctionSet.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	FunctionSet.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

import java.util.Set;

/**
 * 方法集合.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-19
 * 
 */
public class FunctionSet {

    private static Set<Class<? extends Object>> functionSet;

    public static Set<Class<? extends Object>> getFunctionSet() {
        return functionSet;
    }

    public static void setFunctionSet(Set<Class<? extends Object>> functionSet) {
        FunctionSet.functionSet = functionSet;
    }

}
