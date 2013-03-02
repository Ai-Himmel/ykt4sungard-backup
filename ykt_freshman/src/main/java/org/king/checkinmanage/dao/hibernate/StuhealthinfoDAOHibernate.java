package org.king.checkinmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.checkinmanage.dao.StuhealthinfoDAO;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Stuhealthinfo.
 * @see org.king.checkinmanage.dao.hibernate.Stuhealthinfo
 * @author MyEclipse - Hibernate Tools
 */

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StuhealthinfoDAOHibernate.java
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
public class StuhealthinfoDAOHibernate implements StuhealthinfoDAO{

    private static final Log log = LogFactory.getLog(StuhealthinfoDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Stuhealthinfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Stuhealthinfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Stuhealthinfo get(Serializable id) {
				log.debug("getting Stuhealthinfo instance by id");
				return (Stuhealthinfo)baseDAO.getEntity(Stuhealthinfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Stuhealthinfo all");
	      String allHql = "from Stuhealthinfo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Stuhealthinfo transientInstance) {
        log.debug("saving Stuhealthinfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Stuhealthinfo transientInstance){
	    	log.debug("updating Stuhealthinfo instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Stuhealthinfo persistentInstance) {
		    log.debug("deleting Stuhealthinfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}