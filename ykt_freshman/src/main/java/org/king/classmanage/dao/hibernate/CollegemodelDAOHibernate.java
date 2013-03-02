package org.king.classmanage.dao.hibernate;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegemodelDAOHibernate.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-24     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.classmanage.dao.CollegemodelDAO;
import org.king.classmanage.domain.Collegemodel;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Collegemodel.
 * @see org.king.classmanage.dao.hibernate.Collegemodel
 * @author MyEclipse - Hibernate Tools
 */
 
public class CollegemodelDAOHibernate implements CollegemodelDAO{

    private static final Log log = LogFactory.getLog(CollegemodelDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Collegemodel instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Collegemodel instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Collegemodel get(Serializable id) {
				log.debug("getting Collegemodel instance by id");
				return (Collegemodel)baseDAO.getEntity(Collegemodel.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Collegemodel all");
	      String allHql = "from Collegemodel order by collegeNo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Collegemodel transientInstance) {
        log.debug("saving Collegemodel instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Collegemodel transientInstance){
	    	log.debug("updating Collegemodel instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Collegemodel persistentInstance) {
		    log.debug("deleting Collegemodel instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}