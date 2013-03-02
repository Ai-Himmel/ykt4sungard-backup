package org.king.checkinmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.checkinmanage.dao.StuCardfeeInfoDAO;
import org.king.checkinmanage.domain.StuCardfeeInfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class StuCardfeeInfo.
 * @see org.king.checkinmanage.dao.hibernate.StuCardfeeInfo
 * @author MyEclipse - Hibernate Tools
 */
public class StuCardfeeInfoDAOHibernate implements StuCardfeeInfoDAO{

    private static final Log log = LogFactory.getLog(StuCardfeeInfoDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding StuCardfeeInfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding StuCardfeeInfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public StuCardfeeInfo get(Serializable id) {
				log.debug("getting StuCardfeeInfo instance by id");
				return (StuCardfeeInfo)baseDAO.getEntity(StuCardfeeInfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting StuCardfeeInfo all");
	      String allHql = "from StuCardfeeInfo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(StuCardfeeInfo transientInstance) {
        log.debug("saving StuCardfeeInfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(StuCardfeeInfo transientInstance){
    	log.debug("updating StuCardfeeInfo instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(StuCardfeeInfo persistentInstance) {
		    log.debug("deleting StuCardfeeInfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}