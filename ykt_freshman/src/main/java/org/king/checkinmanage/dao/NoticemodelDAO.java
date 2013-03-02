package org.king.checkinmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.checkinmanage.domain.Noticemodel;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: NoticemodelDAO.java
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
public interface NoticemodelDAO extends DAO {
	
	public List find(MyQuery myQuery);

	public List find(String query);

	public Noticemodel get(Serializable id);

	public List getAll();

	public void save(Noticemodel transientInstance);

	public void update(Noticemodel transientInstance);

	public void delete(Noticemodel persistentInstance);

	public Noticemodel findbyId(String id);

}
