/*
 * UserTest.java  v1.00  2012-2-24
 * Peoject	sungard-data-jdbc
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	UserTest.java  v1.00 2012-2-24
 * Project	: 	sungard-data-jdbc
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.common.domain;

import java.lang.reflect.Field;

import org.apache.commons.lang.reflect.FieldUtils;
import org.junit.Test;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-24
 * 
 */
public class UserTest {

    @Test
    public void testUsers() {

        Field field = FieldUtils.getDeclaredField(User.class, "id", true);
        System.out.println(field);

        Field[] fields = User.class.getDeclaredFields();
        for (Field fiel : fields) {
            System.out.println(fiel.getName());
        }

    }

}
