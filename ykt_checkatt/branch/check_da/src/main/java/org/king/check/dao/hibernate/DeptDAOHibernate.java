package org.king.check.dao.hibernate;

import java.util.List;

import org.king.check.dao.DeptDAO;
import org.king.framework.dao.BaseDAO;

public class DeptDAOHibernate implements DeptDAO{
	
	private BaseDAO baseDAO;

	public List findDept(String query) {
		return baseDAO.findEntity(query);
	}

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

}
