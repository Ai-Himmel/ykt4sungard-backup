/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StuFeeInfoDAO.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-5-26     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
package org.king.checkinmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.checkinmanage.domain.StuFeeInfo;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface StuFeeInfoDAO extends DAO {
	
	public List find(MyQuery myQuery);

	public List find(String query);

	public StuFeeInfo get(Serializable id);

	public List getAll();

	public void save(StuFeeInfo transientInstance);

	public void update(StuFeeInfo transientInstance);

	public void delete(StuFeeInfo persistentInstance);

}
