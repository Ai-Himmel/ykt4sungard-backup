package org.king.rcvmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.rcvmanage.domain.Stuarriveinfo;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StuarriveinfoDAO.java
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
public interface StuarriveinfoDAO extends DAO {
	
	public List find(MyQuery myQuery);

	public List find(String query);

	public Stuarriveinfo get(Serializable id);

	public List getAll();

	public void save(Stuarriveinfo transientInstance);

	public void update(Stuarriveinfo transientInstance);

	public void delete(Stuarriveinfo persistentInstance);

     //	�Զ��巽��
	  
	public List getAllwith();
	
	public Stuarriveinfo findbyId(String id);
}
