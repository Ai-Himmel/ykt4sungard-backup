package org.king.classmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.StuAdddelhis;
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
public interface StuAdddelhisDAO extends DAO {
	
	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public StuAdddelhis get(Serializable id);
	
	public List getAll();
	
	public void save(StuAdddelhis transientInstance);
	
    public void update(StuAdddelhis transientInstance);
    
    public void delete(StuAdddelhis persistentInstance);

}
