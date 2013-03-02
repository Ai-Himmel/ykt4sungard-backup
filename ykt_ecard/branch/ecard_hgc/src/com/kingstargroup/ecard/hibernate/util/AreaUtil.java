/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import org.apache.log4j.Logger;
import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.area.AreaPersistence;
import com.kingstargroup.ecard.hibernate.area.TPifArea;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AreaUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AreaUtil extends BasicUtil {
	
	private static final Logger logger = Logger.getLogger(AreaUtil.class);

	/**
	 * Description:���ݵ���ID�õ��������
	 * @param areaId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public static TPifArea getAreaById(String areaId) throws PortalException {
		AreaPersistence persistence = (AreaPersistence) getPersistence(AreaPersistence.class.getName());
		Transaction t = beginTransaction();
		TPifArea area = null;
		try {
			//logger.info("----------getAreaById------------");
			area = persistence.getAreaById(areaId);
			
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return area;
	}

}
