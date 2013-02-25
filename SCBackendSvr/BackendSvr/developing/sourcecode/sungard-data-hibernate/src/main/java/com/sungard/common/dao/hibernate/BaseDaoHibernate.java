/*
 * BaseDaoHibernate.java  v1.00  2011-12-13
 * Peoject	sungard-common-able
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	BaseDaoHibernate.java  v1.00 2011-12-13
 * Project	: 	sungard-common-able
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.common.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.hibernate.SessionFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

import com.sungard.common.dao.BaseDaoable;

/**
 * BaseDao hibernate实现.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-13
 * 
 */
public abstract class BaseDaoHibernate<T, PK extends Serializable> extends HibernateDaoSupport implements
        BaseDaoable<T, PK> {

    private Class<T> persistentClass;

    public BaseDaoHibernate(final Class<T> persistentClass) {
        this.persistentClass = persistentClass;
    }

    @Autowired
    public void setSessionFactory0(final SessionFactory sessionFactory) {
        super.setSessionFactory(sessionFactory);
    }

    @Override
    public T get(PK id) {
        return (T) getHibernateTemplate().get(this.persistentClass, id);
    }

    @Override
    public List<T> getAll() {
        return getHibernateTemplate().loadAll(this.persistentClass);
    }

    @Override
    public void remove(PK id) {
        getHibernateTemplate().delete(get(id));
    }

    @SuppressWarnings("unchecked")
    @Override
    public T save(T object) {
        return (T) getHibernateTemplate().save(object);
    }

    @Override
    public void saveOrUpdate(T object) {
        getHibernateTemplate().saveOrUpdate(object);
    }

    @Override
    public void update(T object) {
        getHibernateTemplate().saveOrUpdate(object);
    }

    @SuppressWarnings("unchecked")
    @Override
    public List<T> getAll(T object) {
        return getHibernateTemplate().findByExample(object);
    }

}
