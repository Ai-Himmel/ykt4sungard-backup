/*
 * OperatorDbutilsServiceTest.java  v1.00  2011-12-26
 * Peoject	smartcard-operator
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	OperatorDbutilsServiceTest.java  v1.00 2011-12-26
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.service;

import org.junit.BeforeClass;
import org.junit.Test;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-26
 * 
 */
public class OperatorDbutilsServiceTest {

    private static OperatorDbutilsService operatorDbutilsService;

    @BeforeClass
    public static void setUp() {
        operatorDbutilsService = new OperatorDbutilsService();
    }

    @Test
    public void testDoService() {

        // operatorDbutilsService.doService(func, session);
        operatorDbutilsService.doService(null, null);
    }

}
