package org.king.classmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.ClassAlertHis;
import org.king.classmanage.domain.GzStuTemp;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StudentmodelDAO.java
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
public interface StudentmodelDAO extends DAO {
	
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Studentmodel get(Serializable id);
	
	public List getAll();
	
	public void save(Studentmodel transientInstance);
	
    public void update(Studentmodel transientInstance);
    
    public void delete(Studentmodel persistentInstance);
    
	public void saveGzStuTemp(GzStuTemp transientInstance);
	
    public void updateGzStuTemp(GzStuTemp transientInstance);
    
    public void deleteGzStuTemp(GzStuTemp persistentInstance);

    public void saveAlertHis(ClassAlertHis transientInstance);
    
    public Studentmodel findbyStuId(String id);
}
