package org.king.dormitorymanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: DormitorymodelDAO.java
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
public interface DormitorymodelDAO extends DAO {
	
	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Dormitorymodel get(Serializable id);
	
	public List getAll();
	
	public void save(Dormitorymodel transientInstance);
	
    public void update(Dormitorymodel transientInstance);
    
    public void delete(Dormitorymodel persistentInstance);
    
    public List getRoomByDorm(String buildingId);

}
