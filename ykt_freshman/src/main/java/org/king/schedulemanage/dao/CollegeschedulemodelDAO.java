package org.king.schedulemanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.schedulemanage.domain.Collegeschedulemodel;
 
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegeschedulemodelDAO.java
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
public interface CollegeschedulemodelDAO extends DAO {
	
	public List find(String query);
	 
	public Collegeschedulemodel get(Serializable id);
	
	public List getAll();
	
	public void save(Collegeschedulemodel transientInstance);
	
    public void update(Collegeschedulemodel transientInstance);
    
    public void delete(Collegeschedulemodel persistentInstance);

	

}
