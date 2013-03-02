package org.king.checkinmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.checkinmanage.dao.StucheckininfoDAO;
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Stucheckininfo.
 * @see org.king.checkinmanage.dao.hibernate.Stucheckininfo
 * @author MyEclipse - Hibernate Tools
 */

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StucheckininfoDAOHibernate.java
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
public class StucheckininfoDAOHibernate implements StucheckininfoDAO{

    private static final Log log = LogFactory.getLog(StucheckininfoDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Stucheckininfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Stucheckininfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Stucheckininfo get(Serializable id) {
				log.debug("getting Stucheckininfo instance by id");
				return (Stucheckininfo)baseDAO.getEntity(Stucheckininfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Stucheckininfo all");
	      String allHql = "from Stucheckininfo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Stucheckininfo transientInstance) {
        log.debug("saving Stucheckininfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Stucheckininfo transientInstance){
	    	log.debug("updating Stucheckininfo instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Stucheckininfo persistentInstance) {
		    log.debug("deleting Stucheckininfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}