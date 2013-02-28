package org.king.framework.common;

import org.apache.commons.beanutils.PropertyUtils;
import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Criteria;
import org.hibernate.criterion.MatchMode;
import org.hibernate.criterion.Order;
import org.hibernate.criterion.Projections;
import org.hibernate.criterion.Restrictions;
import org.king.framework.util.GenericsUtils;
import org.springframework.orm.ObjectRetrievalFailureException;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

import java.io.Serializable;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.StringTokenizer;

public abstract class AbstractHibernateDao extends HibernateDaoSupport {
    protected final Log logger = LogFactory.getLog(getClass());
    protected Class entityClass;

    protected Class getEntityClass() {
        return entityClass;
    }

    public AbstractHibernateDao() {
        entityClass = GenericsUtils.getGenericClass(getClass());
    }

    public Object get(Serializable id) {
        Object o = getHibernateTemplate().get(getEntityClass(), id);
        if (o == null)
            throw new ObjectRetrievalFailureException(getEntityClass(), id);
        return o;
    }

    public List getAll() {
        return getHibernateTemplate().loadAll(getEntityClass());
    }

    public void save(Object o) {
        getHibernateTemplate().saveOrUpdate(o);
    }

    public void remove(Serializable id) {
        remove(get(id));
    }

    public void remove(Object o) {
        getHibernateTemplate().delete(o);
    }

    public List find(String hsql) {
        return getHibernateTemplate().find(hsql);
    }

    public List find(String hsql, Object value) {
        return getHibernateTemplate().find(hsql, value);
    }

    public List find(String hsql, Object[] values) {
        return getHibernateTemplate().find(hsql, values);
    }

    public Object findBy(String name, Object value) {
        Criteria criteria = getSession().createCriteria(getEntityClass());
        criteria.add(Restrictions.eq(name, value));
        return criteria.uniqueResult();
    }

    public List findAllBy(String name, Object value) {
        Criteria criteria = getSession().createCriteria(getEntityClass());
        criteria.add(Restrictions.eq(name, value));
        return criteria.list();
    }

    public List findAllByLike(String name, String value) {
        Criteria criteria = getSession().createCriteria(getEntityClass());
        criteria.add(Restrictions.like(name, value, MatchMode.ANYWHERE));
        return criteria.list();
    }

    public List findAllBy(Map filter) {
        Criteria criteria = getSession().createCriteria(getEntityClass());
        filterCriteria(criteria, filter);
        return criteria.list();
    }

    protected void filterCriteria(Criteria criteria, Map filter) {
        if ((filter != null) && (!filter.isEmpty())) {
            Set keys = filter.keySet();

            Iterator iterator = keys.iterator();
            String key = null;
            String value = null;
            while (iterator.hasNext()) {
                key = (String) iterator.next();
                value = (String) filter.get(key);
                if (StringUtils.isNotBlank(value))
                    criteria.add(Restrictions.eq(key, value));
            }
        }
    }

    public boolean isNotUnique(Object entity, String names) {
        Criteria criteria = getSession().createCriteria(entity.getClass()).setProjection(Projections.rowCount());
        StringTokenizer namest = new StringTokenizer(names, ",");
        try {
            while (namest.hasMoreTokens()) {
                String name = namest.nextToken();
                criteria.add(Restrictions.eq(name, PropertyUtils.getProperty(entity, name)));
            }
            String keyName = getSessionFactory().getClassMetadata(entity.getClass()).getIdentifierPropertyName();
            if (keyName != null) {
                Object id = PropertyUtils.getProperty(entity, keyName);

                if (id != null)
                    criteria.add(Restrictions.not(Restrictions.eq(keyName, id)));
            }
        } catch (Exception e) {
            logger.error(e.getMessage());
        }
        return ((Integer) criteria.uniqueResult()).intValue() > 0;
    }

    protected void sortCriteria(Criteria criteria, Map sortMap, Object entity) {
        if (!sortMap.isEmpty()) {
            Set keys = sortMap.keySet();
            Iterator iterator = keys.iterator();
            String key = null;
            String value = null;
            while (iterator.hasNext()) {
                String fieldName = (String) iterator.next();
                String orderType = sortMap.get(fieldName).toString();

                if (fieldName.indexOf('.') != -1) {
                    String alias = StringUtils.substringBefore(fieldName, ".");
                    String aliasType = alias;
                    try {
                        aliasType = PropertyUtils.getProperty(entity, alias).getClass().getSimpleName();
                    } catch (Exception e) {
                        logger.warn("get propertity " + alias + " of entity error");
                    }
                    criteria.createAlias(aliasType, alias);
                }

                if ("asc".equalsIgnoreCase(orderType))
                    criteria.addOrder(Order.asc(fieldName));
                else
                    criteria.addOrder(Order.desc(fieldName));
            }
        }
    }
}