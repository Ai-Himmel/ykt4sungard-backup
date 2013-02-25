/*
 * UserDaoHibernateTest.java  v1.00  2012-2-16
 * Peoject	sungard-commons-able
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	UserDaoHibernateTest.java  v1.00 2012-2-16
 * Project	: 	sungard-commons-able
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.common.dao.hibernate;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.AbstractTransactionalJUnit4SpringContextTests;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import static org.junit.Assert.*;

import com.sungard.common.domain.User;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-16
 * 
 */
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("/applicationContext-test.xml")
public class UserDaoHibernateTest extends AbstractTransactionalJUnit4SpringContextTests {

    private static Logger logger = LoggerFactory.getLogger(UserDaoHibernateTest.class);

    @Autowired
    private UserDaoHibernate userDaoHibernate;

    @Test
    public void testCrud() {
        User user = userDaoHibernate.get(1L);
        logger.info("---------------user is:{}, name={}", user, user.getName());
        assertEquals("un success", "admin", user.getLoginName());
    }

}
