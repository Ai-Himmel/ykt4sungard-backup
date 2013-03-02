package org.king.classmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.ClassAlertHis;
import org.king.classmanage.domain.Department;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StudentmodelDAO.java
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
public interface DepartmentDAO extends DAO {
	
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Department get(Serializable id);
	
	public List getAll();
	
	public void save(Department transientInstance);
	
    public void update(Department transientInstance);
    
    public void delete(Department persistentInstance);
}
