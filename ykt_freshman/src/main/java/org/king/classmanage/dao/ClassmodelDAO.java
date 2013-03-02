package org.king.classmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.ClassDorm;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.MenuTime;
import org.king.classmanage.domain.NHeaderSessionModel;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassmodelDAO.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-25     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
public interface ClassmodelDAO extends DAO {
	
	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Classmodel get(Serializable id);
	
	public List getAll();
	
	public void save(Classmodel transientInstance);
	
    public void update(Classmodel transientInstance);
    
    public void delete(Classmodel persistentInstance);
    
    public void deleteClassDorm(ClassDorm classdorm);
    
    public void saveClassDorm(ClassDorm classdorm);
    
    public void updateClassDorm(ClassDorm classdorm);
    
    public void saveMenuTime(MenuTime menuTime);
    
    public void updateMenuTime(MenuTime menuTime);
    
    public void deleteMenuTime(MenuTime menuTime);
    
    public void saveUserSession(NHeaderSessionModel transientInstance);
    
    public void updateUserSession(NHeaderSessionModel transientInstance);

}
