package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.check.dao.CourseDAO;
import org.king.check.domain.TCourse;
import org.king.framework.dao.BaseDAO;

public class CourseDAOHibernate implements CourseDAO{

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}


	public void delte(TCourse course) {
		baseDAO.removeEntity(course);
		
	}

	public List find(String query) {
	    return 	baseDAO.findEntity(query);
	}

	
	public TCourse get(Serializable id) {
		return (TCourse)baseDAO.getEntity(TCourse.class, id);
	}
	
	public void save(TCourse course) {
		baseDAO.saveEntity(course);
	}

	
	public void update(TCourse course) {
		baseDAO.updateEntity(course);
	}

}
