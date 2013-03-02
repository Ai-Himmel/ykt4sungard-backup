package org.king.schedulemanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.schedulemanage.domain.Collegeschedulemodel;
 
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegeschedulemodelDAO.java
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
public interface CollegeschedulemodelDAO extends DAO {
	
	public List find(String query);
	 
	public Collegeschedulemodel get(Serializable id);
	
	public List getAll();
	
	public void save(Collegeschedulemodel transientInstance);
	
    public void update(Collegeschedulemodel transientInstance);
    
    public void delete(Collegeschedulemodel persistentInstance);

	

}
