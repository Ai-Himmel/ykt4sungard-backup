package org.king.check.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.dao.TeacherClassDAO;
import org.king.check.domain.TTeacherClass;
import org.king.check.util.PageLimitUtil;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-17
 */
public class TeacherClassDAOHibernate implements TeacherClassDAO {
    private static final Log log = LogFactory.getLog(TeacherClassDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public void save(TTeacherClass transientInstance) {
        log.debug("saving TTeacherClass instance");
        baseDAO.saveEntity(transientInstance);
    }

    public TTeacherClass get(Integer custid, String deptId) {
        String query = "from TTeacherClass t where t.custid=" + custid + " and t.deptId='" + deptId + "'";
        List list = baseDAO.findEntity(query);
        if (list != null && list.size() > 0) {
            return (TTeacherClass) list.get(0);
        }
        return null;
    }

    public TTeacherClass get(String stuempno, String deptId) {
        String query = "from TTeacherClass t where t.stuempno=" + stuempno + " and t.deptId='" + deptId + "'";
        List list = baseDAO.findEntity(query);
        if (list != null && list.size() > 0) {
            return (TTeacherClass) list.get(0);
        }
        return null;
    }

    public TTeacherClass get(Serializable id) {
        return (TTeacherClass) baseDAO.getEntity(TTeacherClass.class, id);
    }

    public void findTeacherClassByPage(DBPageLimit page, MyQuery myQuery) {
        PageLimitUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    public List find(MyQuery myQuery) {
        log.debug("finding TTeacherClass instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding TTeacherClass instance by query");
        return baseDAO.findEntity(query);
    }

    public List getAll() {
        log.debug("getting TTeacherClass all");
        String allHql = "from TTeacherClass";
        return baseDAO.findEntity(allHql);
    }

    public void update(TTeacherClass transientInstance) {
        log.debug("updating TTeacherClass instance");
        baseDAO.updateEntity(transientInstance);
    }

    public void delete(TTeacherClass persistentInstance) {
        log.debug("deleting TTeacherClass instance");
        baseDAO.removeEntity(persistentInstance);
    }
}
