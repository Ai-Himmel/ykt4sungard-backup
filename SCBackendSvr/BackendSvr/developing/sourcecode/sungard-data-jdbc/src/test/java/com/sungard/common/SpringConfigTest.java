/*
 * SpringConfigTest.java  v1.00  2012-2-16
 * Peoject	sungard-commons-able
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	SpringConfigTest.java  v1.00 2012-2-16
 * Project	: 	sungard-commons-able
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.common;

import static org.junit.Assert.assertNotNull;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationContext;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

/**
 * spring context load test.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-16
 * 
 */
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("/applicationContext-test.xml")
public class SpringConfigTest {// extends
                               // AbstractTransactionalJUnit4SpringContextTests
                               // {

    private static Logger logger = LoggerFactory.getLogger(SpringConfigTest.class);

    @Autowired
    private ApplicationContext applicationContext;

    @Before
    public void setUp() {

    }

    @Test
    public void testGetApplicationContext() {
        logger.info("--------applicationContext-->>---:{}", applicationContext);
        assertNotNull(applicationContext);
    }
}
