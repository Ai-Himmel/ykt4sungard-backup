package org.king.check.dao.hibernate;

import org.king.check.dao.CourseplanTempDAO;
import org.king.check.domain.TCourseplanTemp;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-4
 */
public class CourseplanTempDAOHibernate implements CourseplanTempDAO {
    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public void save(TCourseplanTemp entity) {
        baseDAO.saveEntity(entity);
    }

    public void update(TCourseplanTemp entity) {
        baseDAO.updateEntity(entity);
    }

    public TCourseplanTemp get(Serializable id) {
        return (TCourseplanTemp) baseDAO.getEntity(TCourseplanTemp.class, id);
    }

    public List find(String query) {
        return baseDAO.findEntity(query);
    }

    public List find(MyQuery myQuery) {
        return baseDAO.findEntity(myQuery);
    }

    public void delete(TCourseplanTemp entity) {
        baseDAO.removeEntity(entity);
    }
}
