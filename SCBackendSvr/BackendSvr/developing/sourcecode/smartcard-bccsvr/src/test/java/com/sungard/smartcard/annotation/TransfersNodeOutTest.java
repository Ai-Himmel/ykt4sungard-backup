/*
 * TransfersNodeOutTest.java  v1.00  2011-12-31
 * Peoject	smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	TransfersNodeOutTest.java  v1.00 2011-12-31
 * Project	: 	smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.annotation;

import java.lang.reflect.Field;

import static junit.framework.Assert.*;

import org.junit.Test;

/**
 * test.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-31
 * 
 */
public class TransfersNodeOutTest {

    class TestOjbect {
        @TransfersNodeOut(value = TransfersNodeType.damt10, desc = "测试")
        private String xxx;
    }

    @Test
    public void testNodeOut() {
        Class<?> cc = TestOjbect.class;
        Field[] f = cc.getDeclaredFields();
        for (Field field : f) {
            if (field.isAnnotationPresent(TransfersNodeOut.class)) {
                TransfersNodeOut s = field.getAnnotation(TransfersNodeOut.class);
                TransfersNodeType n = s.value();
                System.out.println(s.desc() + "  " + n.getLength() + " " + n.getName() + "  " + n.getType() + "  "
                        + n.getOptMethodName());

                assertEquals("测试", s.desc());
                assertEquals(n.getName(), "damt10");
            }
        }

    }

    public static void main(String[] args) {

        Class<?> cc = TestOjbect.class;
        Field[] f = cc.getDeclaredFields();
        for (Field field : f) {
            if (field.isAnnotationPresent(TransfersNodeOut.class)) {
                TransfersNodeOut s = field.getAnnotation(TransfersNodeOut.class);
                TransfersNodeType n = s.value();
                System.out.println(s.desc() + "  " + n.getLength() + " " + n.getName() + "  " + n.getType() + "  "
                        + n.getOptMethodName());
            }
        }

    }

}
