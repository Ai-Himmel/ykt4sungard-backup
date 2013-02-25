/*
 * StartFuncsHolderTest.java  v1.00  2012-2-17
 * Peoject	smartcard-commons
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	StartFuncsHolderTest.java  v1.00 2012-2-17
 * Project	: 	smartcard-commons
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.util.holder;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import static org.junit.Assert.*;

import com.sungard.smartcard.bccsvr.FunctionInfo;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-17
 * 
 */
public class StartFuncsHolderTest {

    private Logger logger = LoggerFactory.getLogger(StartFuncsHolderTest.class);

    @Test
    public void testAddFunc() {
        FunctionInfo funInfo = new FunctionInfo(1000, "genliang", "", String.class);
        StartFuncsHolder.addFunc(funInfo);
        logger.info("FunctionInfo={}", StartFuncsHolder.getFunc(1000));
        assertEquals("ture", StartFuncsHolder.getFunc(1000), funInfo);
    }

}
