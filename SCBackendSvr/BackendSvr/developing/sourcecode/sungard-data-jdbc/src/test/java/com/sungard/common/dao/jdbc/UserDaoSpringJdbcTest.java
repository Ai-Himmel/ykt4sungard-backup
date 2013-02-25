/*
 * UserDaoSpringJdbcTest.java  v1.00  2012-2-16
 * Peoject	sungard-data-jdbc
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	UserDaoSpringJdbcTest.java  v1.00 2012-2-16
 * Project	: 	sungard-data-jdbc
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.common.dao.jdbc;

import static org.junit.Assert.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.annotation.Rollback;

import com.sungard.common.domain.User;
import com.sungard.modules.test.spring.SpringTxTestCase;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-16
 * 
 */
public class UserDaoSpringJdbcTest extends SpringTxTestCase {

    private static Logger logger = LoggerFactory.getLogger(UserDaoSpringJdbcTest.class);

    @Autowired
    private UserDaoSpringJdbc userDaoSpringJdbc;

    // @Test
    public void testCrud() {

        List<User> list = userDaoSpringJdbc.getAll();
        for (User user : list) {
            logger.info(user.toString());
        }

        assertNotNull(list);

        User user = userDaoSpringJdbc.get(1L);
        logger.info("---------------user is:{}, name={}", user, user.getName());
        assertEquals("un success", "admin", user.getLoginName());

        userDaoSpringJdbc.remove(8L);

        //
        // User user2 = new User();
        // user2.setLoginName("------genliang.llsl");
        // userDaoSpringJdbc.update(user2);
        //
        // assertNull(user2.getId());

    }

    // @Test
    @Rollback(false)
    public void testInsert() {
        logger.info("---------------update test ------");
        User user2 = new User();
        user2.setLoginName(String.valueOf(Math.random()));
        user2 = userDaoSpringJdbc.save(user2);
        logger.info(user2.toString());

        assertNotNull(user2);
    }

    @Test
    @Rollback(false)
    public void testUpdate() {
        User user2 = new User();
        user2.setLoginName(String.valueOf(Math.random()));

        // filter_EQS_name filter_LIKES_name_OR_email
        Map<String, Object> parmMap = new HashMap<String, Object>();
        // parmMap.put("prop_EQS_LOGIN_NAME", "sdf_genliang.jiang");
        parmMap.put("prop_EQS_PASSWORD", "123456");
        userDaoSpringJdbc.setParmMap(parmMap);

        Map<String, Object> condMap = new HashMap<String, Object>();
        // condMap.put("cond_EQS_LOGIN_NAME", "admin");
        condMap.put("cond_LIKES_LOGIN_NAME", "d");
        userDaoSpringJdbc.setCondMap(condMap);

        userDaoSpringJdbc.update(user2);

        assertNotNull(user2);
    }

}
