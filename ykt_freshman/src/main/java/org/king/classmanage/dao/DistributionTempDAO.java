package org.king.classmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.domain.DistributionTemp;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegemodelDAO.java
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
public interface DistributionTempDAO extends DAO {

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public DistributionTemp get(Serializable id);
	
	public List getAll();
	
	public void save(DistributionTemp transientInstance);
	
    public void update(DistributionTemp transientInstance);
    
    public void delete(DistributionTemp persistentInstance);
}
