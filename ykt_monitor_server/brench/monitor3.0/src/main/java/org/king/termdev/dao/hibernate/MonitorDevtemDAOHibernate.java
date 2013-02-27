package org.king.termdev.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Criteria;
import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.termdev.dao.MonitorDevtemDAO;
import org.king.termdev.domain.MonitorDevtem;
import org.king.utils.PaginationUtil;
import org.springframework.orm.hibernate3.HibernateCallback;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-2
 */
public class MonitorDevtemDAOHibernate implements MonitorDevtemDAO {
    private static final Log log = LogFactory.getLog(MonitorDevtemDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorDevtem instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorDevtem instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorDevtem get(Serializable id) {
        log.debug("getting MonitorDevtem instance by id");
        return (MonitorDevtem) baseDAO.getEntity(MonitorDevtem.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorDevtem all");
        String allHql = "from MonitorDevtem";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorDevtem transientInstance) {
        log.debug("saving MonitorDevtem instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorDevtem transientInstance) {
        log.debug("updating MonitorDevtem instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorDevtem persistentInstance) {
        log.debug("deleting MonitorDevtem instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findTDeviceByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据设备id查找该设备是否关联模板
     *
     * @param deviceid .
     * @return .
     */
    public boolean isExistMonitorDevtem(Integer deviceid) {
        String hql = "from MonitorDevtem t where t.deviceid=" + deviceid;
        List result = baseDAO.findEntity(hql);
        return result != null && result.size() > 0;
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
