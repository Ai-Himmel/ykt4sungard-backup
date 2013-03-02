package org.king.classmanage.dao.hibernate;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassmodelDAOHibernate.java
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
import org.king.classmanage.dao.ClassmodelDAO;
import org.king.classmanage.domain.ClassDorm;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.MenuTime;
import org.king.classmanage.domain.NHeaderSessionModel;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.utils.DateUtil;

/**
 * Data access object (DAO) for domain model class Classmodel.
 * 
 * @see org.king.classmanage.dao.hibernate.Classmodel
 * @author MyEclipse - Hibernate Tools
 */

public class ClassmodelDAOHibernate implements ClassmodelDAO {

	private static final Log log = LogFactory
			.getLog(ClassmodelDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding Classmodel instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding Classmodel instance by query");
		return baseDAO.findEntity(query);
	}

	public Classmodel get(Serializable id) {
		log.debug("getting Classmodel instance by id");
		return (Classmodel) baseDAO.getEntity(Classmodel.class, id);
	}

	public List getAll() {
		log.debug("getting Classmodel all");
		String allHql = "from Classmodel order by classNo";
		return baseDAO.findEntity(allHql);
	}

	public void save(Classmodel transientInstance) {
		log.debug("saving Classmodel instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(Classmodel transientInstance) {
		log.debug("updating Classmodel instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(Classmodel persistentInstance) {
		log.debug("deleting Classmodel instance");
		baseDAO.removeEntity(persistentInstance);
	}
	
	public void saveClassDorm(ClassDorm classdorm){
		log.debug("saving ClassDorm instance");
		baseDAO.saveEntity(classdorm);		
	}
	
	public void updateClassDorm(ClassDorm classdorm){
		log.debug("saving ClassDorm instance");
		baseDAO.updateEntity(classdorm);		
	}
	
	public void deleteClassDorm(ClassDorm classdorm) {
		log.debug("deleting ClassDorm instance");
		baseDAO.removeEntity(classdorm);		
	}
	
	public void saveMenuTime(MenuTime menuTime){
		log.debug("saving MenuTime instance");
		baseDAO.saveEntity(menuTime);		
	}
	
	public void updateMenuTime(MenuTime menuTime){
		log.debug("saving MenuTime instance");
		baseDAO.updateEntity(menuTime);		
	}
	
	public void deleteMenuTime(MenuTime menuTime){
		log.debug("deleting MenuTime instance");
		baseDAO.removeEntity(menuTime);		
	}
	
    public void saveUserSession(NHeaderSessionModel transientInstance){
    	log.debug("saving NHeaderSessionModel");
    	baseDAO.saveEntity(transientInstance);
    }
    
    public void updateUserSession(NHeaderSessionModel transientInstance){
    	log.debug("saving NHeaderSessionModel");
		baseDAO.updateEntity(transientInstance);	
    }

}