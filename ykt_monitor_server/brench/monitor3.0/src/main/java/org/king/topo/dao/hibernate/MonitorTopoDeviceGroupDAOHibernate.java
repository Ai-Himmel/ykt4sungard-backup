package org.king.topo.dao.hibernate;

import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.topo.dao.MonitorTopoDeviceGroupDAO;
import org.king.topo.domain.MonitorTopoDeviceGroup;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateCallback;

import java.io.Serializable;
import java.util.List;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorTopoDeviceGroup entities. Transaction control of the save(), update()
 * and delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 *
 * @author MyEclipse Persistence Tools
 * @see org.king.topo.domain.MonitorTopoDeviceGroup
 */

public class MonitorTopoDeviceGroupDAOHibernate implements
        MonitorTopoDeviceGroupDAO {
    private static final Logger log = LoggerFactory
            .getLogger(MonitorTopoDeviceGroupDAOHibernate.class);

    private BaseDAO baseDAO;

    /*
      * (non-Javadoc)
      *
      * @see
      * org.king.topo.dao.hibernate.MonitorTopoDeviceGroupDAO#setBaseDAO(org.
      * king.framework.dao.BaseDAO)
      */

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    /*
      * (non-Javadoc)
      *
      * @see
      * org.king.topo.dao.hibernate.MonitorTopoDeviceGroupDAO#find(org.king.framework
      * .dao.MyQuery)
      */

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTopoDeviceGroup instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    /*
      * (non-Javadoc)
      *
      * @see
      * org.king.topo.dao.hibernate.MonitorTopoDeviceGroupDAO#find(java.lang.
      * String)
      */

    public List find(String query) {
        log.debug("finding MonitorTopoDeviceGroup instance by query");
        return baseDAO.findEntity(query);
    }

    /*
      * (non-Javadoc)
      *
      * @seeorg.king.topo.dao.hibernate.MonitorTopoDeviceGroupDAO#get(java.io.
      * Serializable)
      */

    public MonitorTopoDeviceGroup get(Serializable id) {
        log.debug("getting MonitorTopoDeviceGroup instance by id");
        return (MonitorTopoDeviceGroup) baseDAO.getEntity(
                MonitorTopoDeviceGroup.class, id);
    }

    /*
      * (non-Javadoc)
      *
      * @see org.king.topo.dao.hibernate.MonitorTopoDeviceGroupDAO#getAll()
      */

    public List getAll() {
        log.debug("getting MonitorTopoDeviceGroup all");
        String allHql = "from MonitorTopoDeviceGroup";
        return baseDAO.findEntity(allHql);
    }

    /*
      * (non-Javadoc)
      *
      * @see
      * org.king.topo.dao.hibernate.MonitorTopoDeviceGroupDAO#save(org.king.topo
      * .domain.MonitorTopoDeviceGroup)
      */

    public void save(MonitorTopoDeviceGroup transientInstance) {
        log.debug("saving MonitorTopoDeviceGroup instance");
        baseDAO.saveEntity(transientInstance);
    }

    /*
      * (non-Javadoc)
      *
      * @see
      * org.king.topo.dao.hibernate.MonitorTopoDeviceGroupDAO#update(org.king
      * .topo.domain.MonitorTopoDeviceGroup)
      */

    public void update(MonitorTopoDeviceGroup transientInstance) {
        log.debug("updating MonitorTopoDeviceGroup instance");
        baseDAO.updateEntity(transientInstance);
    }

    /*
      * (non-Javadoc)
      *
      * @see
      * org.king.topo.dao.hibernate.MonitorTopoDeviceGroupDAO#delete(org.king
      * .topo.domain.MonitorTopoDeviceGroup)
      */

    public void delete(MonitorTopoDeviceGroup persistentInstance) {
        log.debug("deleting MonitorTopoDeviceGroup instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public List findBySql(final String sql) {
        SQLQuery sqlQuery = (SQLQuery) ((BaseDAOHibernate) baseDAO).getHibernateTemplate().execute(new HibernateCallback() {
            public Object doInHibernate(Session session) throws HibernateException {
                return session.createSQLQuery(sql);
            }
        });
        return sqlQuery.list();
    }
}