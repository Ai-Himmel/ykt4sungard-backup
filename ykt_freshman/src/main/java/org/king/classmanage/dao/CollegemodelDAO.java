package org.king.classmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.Collegemodel;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegemodelDAO.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-24     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
public interface CollegemodelDAO extends DAO {

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Collegemodel get(Serializable id);
	
	public List getAll();
	
	public void save(Collegemodel transientInstance);
	
    public void update(Collegemodel transientInstance);
    
    public void delete(Collegemodel persistentInstance);
}
