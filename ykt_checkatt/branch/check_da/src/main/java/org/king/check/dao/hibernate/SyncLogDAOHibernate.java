package org.king.check.dao.hibernate;

import org.king.check.dao.SyncLogDAO;
import org.king.check.domain.TSyncLog;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-4
 */
public class SyncLogDAOHibernate implements SyncLogDAO {
    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public void save(TSyncLog entity) {
        baseDAO.saveEntity(entity);
    }

    public void update(TSyncLog entity) {
        baseDAO.updateEntity(entity);
    }

    public TSyncLog get(Serializable id) {
        return (TSyncLog) baseDAO.getEntity(TSyncLog.class, id);
    }

    public List find(String query) {
        return baseDAO.findEntity(query);
    }

    public List find(MyQuery myQuery) {
        return baseDAO.findEntity(myQuery);
    }

    public void delete(TSyncLog entity) {
        baseDAO.removeEntity(entity);
    }
}
