package org.king.dormitorymanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.dormitorymanage.domain.Feemodel;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: FeemodelDAO.java
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
public interface FeemodelDAO extends DAO {
	
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Feemodel get(Serializable id);
	
	public List getAll();
	
	public void save(Feemodel transientInstance);
	
    public void update(Feemodel transientInstance);
    
    public void delete(Feemodel persistentInstance);

}
