package org.king.checkinmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StuhealthinfoDAO.java
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
public interface StuhealthinfoDAO extends DAO {
	
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Stuhealthinfo get(Serializable id);
	
	public List getAll();
	
	public void save(Stuhealthinfo transientInstance);
	
    public void update(Stuhealthinfo transientInstance);
    
    public void delete(Stuhealthinfo persistentInstance);

}
