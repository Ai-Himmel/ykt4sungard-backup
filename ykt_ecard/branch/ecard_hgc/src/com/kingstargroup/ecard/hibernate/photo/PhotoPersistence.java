/**
 * 
 */
package com.kingstargroup.ecard.hibernate.photo;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PhotoPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-10-19 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class PhotoPersistence extends BasicPersistence {
	public TCifPhoto getPhoto(String stuempNo) throws DBSystemException {
		TCifPhoto tcifphoto = null;
		Session s = getSession();
		try {
			
			StringBuffer hsql = new StringBuffer();
			hsql
					.append(
							"from com.kingstargroup.ecard.hibernate.photo.TCifPhoto as photo where")
					.append(" photo.stuempNo = ?");
			Query q = s.createQuery(hsql.toString());
			q.setString(0, stuempNo);
			java.util.List list = q.list();
			if (list != null && list.size() > 0) {
				tcifphoto = (TCifPhoto) list.get(0);
				System.out.println("************"+tcifphoto.getCutId()+"*************");
			}
			System.out.println("************"+list.size()+"*************");
			return tcifphoto;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}

	private static final Log _log = LogFactory.getLog(PhotoPersistence.class);
}
