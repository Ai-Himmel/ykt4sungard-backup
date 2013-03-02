package org.king.checkinmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.checkinmanage.dao.StuFeeInfoDAO;
import org.king.checkinmanage.domain.StuFeeInfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class StuFeeInfo.
 * @see org.king.checkinmanage.dao.hibernate.StuFeeInfo
 * @author MyEclipse - Hibernate Tools
 */
public class StuFeeInfoDAOHibernate implements StuFeeInfoDAO{

    private static final Log log = LogFactory.getLog(StuFeeInfoDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding StuFeeInfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding StuFeeInfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public StuFeeInfo get(Serializable id) {
				log.debug("getting StuFeeInfo instance by id");
				return (StuFeeInfo)baseDAO.getEntity(StuFeeInfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting StuFeeInfo all");
	      String allHql = "from StuFeeInfo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(StuFeeInfo transientInstance) {
        log.debug("saving StuFeeInfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(StuFeeInfo transientInstance){
    	log.debug("updating StuFeeInfo instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(StuFeeInfo persistentInstance) {
		    log.debug("deleting StuFeeInfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}