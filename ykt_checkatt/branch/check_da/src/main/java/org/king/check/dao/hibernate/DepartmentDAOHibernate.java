package org.king.check.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.dao.DepartmentDAO;
import org.king.check.domain.Department;
import org.king.check.util.PageLimitUtil;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class Department.
 *
 * @author MyEclipse - Hibernate Tools
 */
public class DepartmentDAOHibernate implements DepartmentDAO {

    private static final Log log = LogFactory.getLog(DepartmentDAOHibernate.class);

    protected void initDao() {
        //do nothing
    }

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding Department instance by myQuery");

        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding Department instance by query");
        return baseDAO.findEntity(query);
    }

    public Department get(Serializable id) {
        log.debug("getting Department instance by id");
        return (Department) baseDAO.getEntity(Department.class, id);
    }

    public void findDepartmentsByPage(DBPageLimit page, MyQuery myQuery) {
        PageLimitUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    public Department findDepartment(String deptId) {
        String hql = "from Department t where t.id='" + deptId + "'";
        List list = baseDAO.findEntity(hql);
        if (list != null && list.size() > 0) {
            return (Department) list.get(0);
        }
        return null;
    }

    public List getAll() {
        log.debug("getting Department all");
        String allHql = "from Department";
        return baseDAO.findEntity(allHql);
    }

    public void save(Department transientInstance) {
        log.debug("saving Department instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(Department transientInstance) {
        log.debug("updating Department instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(Department persistentInstance) {
        log.debug("deleting Department instance");

        /*Department parent = persistentInstance.getParent();

        if (parent != null) {
            parent.getChildren().remove(persistentInstance);
            baseDAO.updateEntity(parent);
            baseDAO.removeEntity(persistentInstance);
        } else {
            baseDAO.removeEntity(persistentInstance);
        }*/
        baseDAO.removeEntity(persistentInstance);
    }


}