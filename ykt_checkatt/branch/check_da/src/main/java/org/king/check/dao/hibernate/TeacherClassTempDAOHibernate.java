package org.king.check.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.TeacherClassTempDAO;
import org.king.check.domain.TTeacherClassTemp;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-16
 */
public class TeacherClassTempDAOHibernate implements TeacherClassTempDAO {
    private static final Log log = LogFactory.getLog(TeacherClassTempDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public void save(TTeacherClassTemp transientInstance) {
        log.debug("saving TTeacherClassTemp instance");
        baseDAO.saveEntity(transientInstance);
    }

    public List find(MyQuery myQuery) {
        log.debug("finding TTeacherClassTemp instance by myQuery");

        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding TTeacherClassTemp instance by query");
        return baseDAO.findEntity(query);
    }

    public List getAll() {
        log.debug("getting TTeacherClassTemp all");
        String allHql = "from TTeacherClassTemp";
        return baseDAO.findEntity(allHql);
    }

    public void update(TTeacherClassTemp transientInstance) {
        log.debug("updating TTeacherClassTemp instance");
        baseDAO.updateEntity(transientInstance);
    }

    public void delete(TTeacherClassTemp persistentInstance) {
        log.debug("deleting TTeacherClassTemp instance");
        baseDAO.removeEntity(persistentInstance);
    }
}
