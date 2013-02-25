/*
 * BccServerHandleTest.java  v1.00  2011-12-28
 * Peoject	smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	BccServerHandleTest.java  v1.00 2011-12-28
 * Project	: 	smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

import java.util.List;

import static junit.framework.Assert.*;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-28
 * 
 */
public class BccServerHandleTest {

    private static final Logger logger = LoggerFactory.getLogger(BccServerHandleTest.class);

    @Test
    public void testCreateHandle() {
        BccServer bccServer = new BccServer();
        BccServerHandle bccServerHandle = new BccServerHandle(bccServer);
        bccServerHandle.setXpackFile(bccServer.GetXpackFileName());
        long hand = bccServerHandle.createHandle();
        System.out.println(hand);
        BccServerThread session = bccServer.CreateSession();
        logger.info("GetMaxColumn={}", session.GetMaxColumn());
        logger.info("GetXPackType={}", session.GetXPackType(session.getHandle()));
        List list = session.XpackFieldDefine(session.GetMaxColumn());
        for (Object object : list) {
            logger.info("" + object);
        }

        assertNotSame(0, hand);
    }

}
