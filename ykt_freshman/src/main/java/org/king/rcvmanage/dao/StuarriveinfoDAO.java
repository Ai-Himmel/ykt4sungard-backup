package org.king.rcvmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.rcvmanage.domain.Stuarriveinfo;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StuarriveinfoDAO.java
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
public interface StuarriveinfoDAO extends DAO {
	
	public List find(MyQuery myQuery);

	public List find(String query);

	public Stuarriveinfo get(Serializable id);

	public List getAll();

	public void save(Stuarriveinfo transientInstance);

	public void update(Stuarriveinfo transientInstance);

	public void delete(Stuarriveinfo persistentInstance);

     //	自定义方法
	  
	public List getAllwith();
	
	public Stuarriveinfo findbyId(String id);
}
