package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.VacationDao;
import org.king.check.domain.Vacation;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

public class VacationDAOHibernate implements VacationDao{
	 private static final Log log = LogFactory.getLog(VacationDAOHibernate.class);

		protected void initDao() {
			//do nothing
		}
	    
	    private BaseDAO baseDAO;
	    
	    public void setBaseDAO(BaseDAO baseDAO) {
			    this.baseDAO = baseDAO;
		  }
public List find(MyQuery myQuery)
{
	return baseDAO.findEntity(myQuery);
}
	
	public List find(String query)
	{
		return baseDAO.findEntity(query);
	}
	 
	public Vacation get(Serializable id)
	{
		return (Vacation)baseDAO.getEntity(Vacation.class,id);
	}
	
	public List getAll()
	{
		String allHql = "from Vacation";
	      return baseDAO.findEntity(allHql);
		
	}
	
	public void save(Vacation transientInstance)
	{
		baseDAO.saveEntity(transientInstance);
	}
	
 public void update(Vacation transientInstance)
 {
	 baseDAO.updateEntity(transientInstance);
 }
 
 public void delete(Vacation persistentInstance)
 {
	 baseDAO.removeEntity(persistentInstance);
 }

}
