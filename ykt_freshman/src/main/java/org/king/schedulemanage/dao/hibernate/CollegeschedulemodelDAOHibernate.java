package org.king.schedulemanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.schedulemanage.dao.CollegeschedulemodelDAO;
import org.king.schedulemanage.domain.Collegeschedulemodel;

/**
 * Data access object (DAO) for domain model class Collegeschedulemodel.
 * @see org.king.schedulemanage.dao.hibernate.Collegeschedulemodel
 * @author MyEclipse - Hibernate Tools
 */
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegeschedulemodelDAOHibernate.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-25     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
public class CollegeschedulemodelDAOHibernate implements CollegeschedulemodelDAO{

    private static final Log log = LogFactory.getLog(CollegeschedulemodelDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Collegeschedulemodel instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Collegeschedulemodel instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Collegeschedulemodel get(Serializable id) {
				log.debug("getting Collegeschedulemodel instance by id");
				return (Collegeschedulemodel)baseDAO.getEntity(Collegeschedulemodel.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Collegeschedulemodel all");
	      String allHql = "from Collegeschedulemodel";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Collegeschedulemodel transientInstance) {
        log.debug("saving Collegeschedulemodel instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Collegeschedulemodel transientInstance){
	    	log.debug("updating Collegeschedulemodel instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Collegeschedulemodel persistentInstance) {
		    log.debug("deleting Collegeschedulemodel instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}