/*
 * UserServiceTest.java  v1.00  2012-2-23
 * Peoject	sungard-data-hibernate
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	UserServiceTest.java  v1.00 2012-2-23
 * Project	: 	sungard-data-hibernate
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.common.service;

import java.util.List;

import static org.junit.Assert.*;

import org.junit.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.annotation.Rollback;

import com.sungard.common.domain.User;
import com.sungard.modules.test.spring.SpringTxTestCase;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-23
 * 
 */
public class UserServiceTest extends SpringTxTestCase {

    @Autowired
    private UserService userService;

    @Test
    public void testService() {
        List<User> list = userService.getAll();
        for (User user : list) {
            logger.info(user.toString());
        }

        assertNotNull(list);
        
        User u = userService.get(10L);
        logger.info("u={}",u);

//        User user = new User();
//        user.setLoginName("=====");
//        userService.save(user);
//        assertNotNull(user.getId());

    }

}
