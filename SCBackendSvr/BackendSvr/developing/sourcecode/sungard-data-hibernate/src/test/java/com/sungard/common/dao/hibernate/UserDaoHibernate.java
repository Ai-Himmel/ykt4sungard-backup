/*
 * UserDaoHibernate.java  v1.00  2012-2-16
 * Peoject	sungard-commons-able
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	UserDaoHibernate.java  v1.00 2012-2-16
 * Project	: 	sungard-commons-able
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.common.dao.hibernate;

import org.springframework.stereotype.Repository;

import com.sungard.common.domain.User;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-16
 * 
 */
@Repository
public class UserDaoHibernate extends BaseDaoHibernate<User, Long> {

    public UserDaoHibernate() {
        super(User.class);
    }

    // public UserDaoHibernate(Class<User> persistentClass) {
    // super(User.class);
    // }

}
