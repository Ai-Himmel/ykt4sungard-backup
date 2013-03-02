package org.king.check.dao.hibernate;

import org.king.check.common.ec.DBPageLimit;
import org.king.check.dao.CheckrecordDAO;
import org.king.check.util.PageLimitUtil;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;

import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-9-26
 */
public class CheckrecordDAOHibernate implements CheckrecordDAO{
    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

    public void findDeviceCheckByPage(DBPageLimit page, MyQuery myQuery) {
        PageLimitUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    public void findCheckDetailByPage(DBPageLimit page, MyQuery myQuery) {
        PageLimitUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    public List findCheckDetail(String query) {
        return baseDAO.findEntity(query);
    }
}
