/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: DictionaryDAO.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-5-30     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.Dictionary;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface DictionaryDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public Dictionary get(Serializable id);

	public List getAll();

	public void save(Dictionary transientInstance);

	public void update(Dictionary transientInstance);

	public void delete(Dictionary persistentInstance);

}
