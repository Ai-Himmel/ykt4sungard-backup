/*
 * UserService.java  v1.00  2012-2-23
 * Peoject	sungard-data-hibernate
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	UserService.java  v1.00 2012-2-23
 * Project	: 	sungard-data-hibernate
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.common.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.sungard.common.dao.BaseDaoable;
import com.sungard.common.dao.hibernate.UserDaoHibernate;
import com.sungard.common.domain.User;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-23
 * 
 */
@Service
public class UserService extends BaseService<User, Long> {

    @Autowired
    private UserDaoHibernate userDaoHibernate;

    public void setUserDaoHibernate(UserDaoHibernate userDaoHibernate) {
        this.userDaoHibernate = userDaoHibernate;
    }

    @Override
    protected BaseDaoable<User, Long> getBaseDao() {
        return userDaoHibernate;
    }

}
