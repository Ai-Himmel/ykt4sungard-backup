package org.king.check.dao.hibernate;

import org.king.check.dao.CustomerDAO;
import org.king.check.domain.TCourse;
import org.king.check.domain.TCustomer;
import org.king.framework.dao.BaseDAO;

import java.io.Serializable;
import java.util.List;

public class CustomerDAOHibernate implements CustomerDAO {

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public void delte(TCourse course) {
        baseDAO.removeEntity(course);
    }

    public TCustomer getCustomer(Serializable id) {
        return (TCustomer) baseDAO.getEntity(TCustomer.class, id);
    }

    public List find(String query) {
        return baseDAO.findEntity(query);
    }

    public TCustomer getCustomerByStuempno(String stuempno) {
        String hql = "from TCustomer c where c.stuempno='" + stuempno + "'";
        List list = baseDAO.findEntity(hql);
        if (list != null && list.size() > 0) {
            return (TCustomer) list.get(0);
        }
        return null;
    }
}
