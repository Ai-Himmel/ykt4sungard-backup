package org.king.schedulemanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.schedulemanage.dao.ClassschedulemodelDAO;
import org.king.schedulemanage.domain.Classschedulemodel;

/** 
 * Data access object (DAO) for domain model class Classschedulemodel.
 * @see org.king.schedulemanage.dao.hibernate.Classschedulemodel
 * @author MyEclipse - Hibernate Tools
 */
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassschedulemodelDAOHibernate.java
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
public class ClassschedulemodelDAOHibernate implements ClassschedulemodelDAO{

    private static final Log log = LogFactory.getLog(ClassschedulemodelDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Classschedulemodel instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Classschedulemodel instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Classschedulemodel get(Serializable id) {
				log.debug("getting Classschedulemodel instance by id");
				return (Classschedulemodel)baseDAO.getEntity(Classschedulemodel.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Classschedulemodel all");
	      String allHql = "from Classschedulemodel";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Classschedulemodel transientInstance) {
        log.debug("saving Classschedulemodel instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Classschedulemodel transientInstance){
	    	log.debug("updating Classschedulemodel instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Classschedulemodel persistentInstance) {
		    log.debug("deleting Classschedulemodel instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}