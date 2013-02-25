/*
 * AppContextTest.java  v1.00  2012-2-21
 * Peoject	smartcard-commons
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	AppContextTest.java  v1.00 2012-2-21
 * Project	: 	smartcard-commons
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import static org.junit.Assert.assertNotNull;

/**
 * test class.
 *
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-21
 */
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("/applicationContext-test.xml")
public class AppContextTest {

    private Logger logger = LoggerFactory.getLogger(AppContextTest.class);

    @Autowired
    private AppContext appContext;

    @Test
    public void testInitMessageCode() {

        logger.info("100003={}", appContext.getRetMsg(100003));

        assertNotNull(appContext);
    }
}
