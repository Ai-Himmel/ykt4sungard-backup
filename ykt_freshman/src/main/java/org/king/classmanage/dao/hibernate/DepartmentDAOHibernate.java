package org.king.classmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.classmanage.dao.DepartmentDAO;
import org.king.classmanage.domain.Department;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Department.
 * @see org.king.classmanage.dao.hibernate.Department
 * @author MyEclipse - Hibernate Tools
 */
public class DepartmentDAOHibernate implements DepartmentDAO{

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
				return (Department)baseDAO.getEntity(Department.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Department all");
	      String allHql = "from Department order by deptCode";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Department transientInstance) {
        log.debug("saving Department instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Department transientInstance){
    	log.debug("updating Department instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Department persistentInstance) {
		    log.debug("deleting Department instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}