package org.king.dormitorymanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.dormitorymanage.dao.DormitorymodelDAO;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Dormitorymodel.
 * @see org.king.dormitorymanage.dao.hibernate.Dormitorymodel
 * @author MyEclipse - Hibernate Tools
 */

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: DormitorymodelDAOHibernate.java
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
public class DormitorymodelDAOHibernate implements DormitorymodelDAO{

    private static final Log log = LogFactory.getLog(DormitorymodelDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Dormitorymodel instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Dormitorymodel instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Dormitorymodel get(Serializable id) {
				log.debug("getting Dormitorymodel instance by id");
				return (Dormitorymodel)baseDAO.getEntity(Dormitorymodel.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Dormitorymodel all");
	      String allHql = "from Dormitorymodel";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Dormitorymodel transientInstance) {
        log.debug("saving Dormitorymodel instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Dormitorymodel transientInstance){
	    	log.debug("updating Dormitorymodel instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Dormitorymodel persistentInstance) {
		    log.debug("deleting Dormitorymodel instance");
        baseDAO.removeEntity(persistentInstance);
	  }    
        public List getRoomByDorm(String dormitory){
        	 return baseDAO.findEntity("from Dormitorymodel a where a.dormitory = '"+dormitory+"'");
        	 
      }
}