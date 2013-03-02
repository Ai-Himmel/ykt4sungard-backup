package org.king.check.dao.hibernate;

import org.king.check.dao.DepartmentTempDAO;
import org.king.check.domain.DepartmentTemp;
import org.king.framework.dao.BaseDAO;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-18
 */
public class DepartmentTempDAOHibernate implements DepartmentTempDAO {
    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public void save(DepartmentTemp transientInstance) {
        baseDAO.saveEntity(transientInstance);
    }
}
