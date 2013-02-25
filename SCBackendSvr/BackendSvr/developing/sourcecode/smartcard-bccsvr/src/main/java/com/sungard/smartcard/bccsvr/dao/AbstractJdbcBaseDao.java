/*
 * AbstractJdbcBaseDao.java  v1.00  2012-1-6
 * Peoject	smartcard-bccsvr
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	AbstractJdbcBaseDao.java  v1.00 2012-1-6
 * Project	: 	smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.dao;

import java.io.Serializable;
import java.sql.SQLException;
import java.util.List;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.ResultSetHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;

import com.sungard.common.dao.BaseDaoable;
import com.sungard.modules.utils.db.dao.DBSessionDao;

/**
 * 库基本操作jdbc抽像实现.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-1-6
 * 
 */
public abstract class AbstractJdbcBaseDao<T, PK extends Serializable> extends DBSessionDao implements
        BaseDaoable<T, PK> {

    private Class<T> persistentClass;

    public AbstractJdbcBaseDao(final Class<T> persistentClass) {
        this.persistentClass = persistentClass;
    }

    public abstract String getSelectAllSql();

    @Override
    public T get(PK id) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public List<T> getAll() {

        QueryRunner runner = new QueryRunner();
        ResultSetHandler<List<T>> rsh = new BeanListHandler<T>(persistentClass);
        try {
            return runner.query(getConnection(), getSelectAllSql(), rsh);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;
    }

    @Override
    public List<T> getAll(T object) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void remove(PK id) {
        // TODO Auto-generated method stub

    }

    @Override
    public T save(T object) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void saveOrUpdate(T object) {
        // TODO Auto-generated method stub

    }

    @Override
    public void update(T object) {
        // TODO Auto-generated method stub

    }

}
