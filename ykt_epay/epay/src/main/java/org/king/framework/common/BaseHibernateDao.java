package org.king.framework.common;

import org.hibernate.Criteria;
import org.hibernate.Query;
import org.hibernate.criterion.CriteriaSpecification;
import org.king.framework.common.support.CriteriaPage;
import org.king.framework.common.support.HqlPage;
import org.king.framework.common.support.Page;

import java.util.Map;

public abstract class BaseHibernateDao extends AbstractHibernateDao {
    public Page pagedQuery(String hql, int pageNo, int pageSize) {
        return pagedQuery(hql, pageNo, pageSize, true);
    }

    public Page pagedQuery(String hql, int pageNo, int pageSize, boolean isScroll) {
        return pagedQuery(hql, null, pageNo, pageSize, isScroll);
    }

    public Page pagedQuery(String hql, Object[] args, int pageNo, int pageSize) {
        return pagedQuery(hql, args, pageNo, pageSize, true);
    }

    public Page pagedQuery(String hql, Object[] args, int pageNo, int pageSize, boolean isScroll) {
        if (hql == null) {
            throw new IllegalArgumentException("NULL is not a valid HQL string");
        }
        Query query = getSession().createQuery(hql);
        if (args != null) {
            for (int i = 0; i < args.length; i++) {
                query.setParameter(i, args[i]);
            }
        }
        return HqlPage.getHibernatePageInstance(query, pageNo, pageSize, isScroll);
    }

    public Page pagedQuery(Criteria criteria, int pageNo, int pageSize) {
        return pagedQuery(criteria, pageNo, pageSize, true);
    }

    public Page pagedQuery(Criteria criteria, int pageNo, int pageSize, boolean isScroll) {
        return CriteriaPage.getHibernatePageInstance(criteria, pageNo, pageSize, isScroll);
    }

    public Page findAllBy(Map filterMap, Map sortMap, int pageNo, int pageSize) {
        Criteria criteria = getSession().createCriteria(getEntityClass());

        filterCriteria(criteria, filterMap);
        sortCriteria(criteria, sortMap, null);
        criteria.setResultTransformer(CriteriaSpecification.ROOT_ENTITY);

        return pagedQuery(criteria, pageNo, pageSize);
    }
}