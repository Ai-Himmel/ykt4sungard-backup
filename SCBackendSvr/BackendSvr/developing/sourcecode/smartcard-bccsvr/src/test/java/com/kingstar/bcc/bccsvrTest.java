/*
 * bccsvrTest.java  v1.00  2011-12-16
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	bccsvrTest.java  v1.00 2011-12-16
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.kingstar.bcc;

import static org.junit.Assert.*;

import java.util.Properties;
import java.util.Set;

import org.apache.commons.lang.StringUtils;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * test Class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-16
 * 
 */
public class bccsvrTest {

    private Logger logger = LoggerFactory.getLogger(bccsvrTest.class);

    @Test
    public void testbccsvr() {

        Properties p = System.getProperties();
        Set<Object> set = p.keySet();
        for (Object object : set) {
            String valueString = (String) p.get(object);
            logger.info("{}={}", object, valueString);
            String[] split = StringUtils.split(valueString, ";");
            for (String string : split) {
                logger.info("\t{}", string);
            }
        }
        // logger.info("{}",p);

        bccsvr bccsvr = new bccsvr();
        logger.info("bccsvr={}", bccsvr);
        assertNotNull("not null", bccsvr);
    }
}
