package org.king.check.dao.hibernate;

import org.king.check.dao.UnplanStudentDAO;
import org.king.check.domain.TUnplanstudent;
import org.king.framework.dao.BaseDAO;

public class UnplanStuDAOHibernate implements UnplanStudentDAO{
	
	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	

	public void update(TUnplanstudent unplanstudent) {
		baseDAO.updateEntity(unplanstudent);
	}

}
