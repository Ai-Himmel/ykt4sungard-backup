/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StuFeeInfoDAO.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-5-26     何林青             
 * <p>
 *
 * @author      何林青
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
