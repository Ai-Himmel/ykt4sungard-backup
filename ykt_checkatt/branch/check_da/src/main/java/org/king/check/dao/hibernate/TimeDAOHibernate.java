package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.check.dao.TimeDAO;
import org.king.check.domain.TTime;
import org.king.framework.dao.BaseDAO;

public class TimeDAOHibernate implements TimeDAO{
	private BaseDAO baseDAO;
	
	 public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public  List findClassTimes(String query){
		 return  baseDAO.findEntity(query);
	}

	public void deleClassTime(TTime time) {
		baseDAO.removeEntity(time);
		
	}

	public void saveClassTimes(TTime time) {
		baseDAO.saveEntity(time);
		
	}

	public void updateClassTime(TTime time) {
		baseDAO.updateEntity(time);
	}

	public TTime getTime(Serializable id) {
	   return (TTime)baseDAO.getEntity(TTime.class, id);
	}
	
	
}
