package org.king.checkinmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.checkinmanage.dao.UploadfileDAO;
import org.king.checkinmanage.domain.Uploadfile;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Uploadfile.
 * @see org.king.checkinmanage.dao.hibernate.Uploadfile
 * @author MyEclipse - Hibernate Tools
 */

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: UploadfileDAOHibernate.java
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
public class UploadfileDAOHibernate implements UploadfileDAO{

    private static final Log log = LogFactory.getLog(UploadfileDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Uploadfile instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Uploadfile instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Uploadfile get(Serializable id) {
				log.debug("getting Uploadfile instance by id");
				return (Uploadfile)baseDAO.getEntity(Uploadfile.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Uploadfile all");
	      String allHql = "from Uploadfile";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Uploadfile transientInstance) {
        log.debug("saving Uploadfile instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Uploadfile transientInstance){
	    	log.debug("updating Uploadfile instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Uploadfile persistentInstance) {
		    log.debug("deleting Uploadfile instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}