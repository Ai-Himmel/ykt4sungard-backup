package org.king.checkinmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.checkinmanage.domain.Uploadfile;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: UploadfileDAO.java
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
public interface UploadfileDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public Uploadfile get(Serializable id);

	public List getAll();

	public void save(Uploadfile transientInstance);

	public void update(Uploadfile transientInstance);

	public void delete(Uploadfile persistentInstance);

}
