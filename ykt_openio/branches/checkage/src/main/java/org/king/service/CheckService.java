package org.king.service;

import org.king.dao.JdbcDao;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public interface CheckService {
    public void setJdbcDao(JdbcDao jdbcDao);

    public void checkRecord();
}
