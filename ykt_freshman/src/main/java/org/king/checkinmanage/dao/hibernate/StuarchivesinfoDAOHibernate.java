package org.king.checkinmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.checkinmanage.dao.StuarchivesinfoDAO;
import org.king.checkinmanage.domain.Stuarchivesinfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Stuarchivesinfo.
 * @see org.king.checkinmanage.dao.hibernate.Stuarchivesinfo
 * @author MyEclipse - Hibernate Tools
 */

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StuarchivesinfoDAOHibernate.java
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
public class StuarchivesinfoDAOHibernate implements StuarchivesinfoDAO{

    private static final Log log = LogFactory.getLog(StuarchivesinfoDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Stuarchivesinfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Stuarchivesinfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Stuarchivesinfo get(Serializable id) {
				log.debug("getting Stuarchivesinfo instance by id");
				return (Stuarchivesinfo)baseDAO.getEntity(Stuarchivesinfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Stuarchivesinfo all");
	      String allHql = "from Stuarchivesinfo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Stuarchivesinfo transientInstance) {
        log.debug("saving Stuarchivesinfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Stuarchivesinfo transientInstance){
	    	log.debug("updating Stuarchivesinfo instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Stuarchivesinfo persistentInstance) {
		    log.debug("deleting Stuarchivesinfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}