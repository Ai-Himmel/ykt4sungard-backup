/*
 * CrudTypeTest.java  v1.00  2012-2-2
 * Peoject	smartcard-commons
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CrudTypeTest.java  v1.00 2012-2-2
 * Project	: 	smartcard-commons
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.annotation;

import org.junit.Test;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-2
 * 
 */
public class CrudTypeTest {

    @Test
    public void testValueOf() {

        for (CrudType crudType : CrudType.values()) {
            System.out.println(crudType.name());
        }

    }

}
