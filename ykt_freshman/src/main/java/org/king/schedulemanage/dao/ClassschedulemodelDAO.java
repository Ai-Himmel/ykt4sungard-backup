package org.king.schedulemanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.schedulemanage.domain.Classschedulemodel;
 
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassschedulemodelDAO.java
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
public interface ClassschedulemodelDAO extends DAO {
	
	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Classschedulemodel get(Serializable id);
	
	public List getAll();
	
	public void save(Classschedulemodel transientInstance);
	
    public void update(Classschedulemodel transientInstance);
    
    public void delete(Classschedulemodel persistentInstance);


}
