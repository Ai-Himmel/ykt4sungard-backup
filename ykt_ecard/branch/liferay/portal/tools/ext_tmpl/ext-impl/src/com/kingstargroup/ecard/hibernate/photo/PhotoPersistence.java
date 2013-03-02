/**
 * 
 */
package com.kingstargroup.ecard.hibernate.photo;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.service.persistence.BasePersistence;

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
public class PhotoPersistence extends BasePersistence {
	public TPhoto getPhoto(String stuempno) throws DBSystemException {
		TPhoto tcifphoto = null;
		Session s = null;
		try {
			s = openSession();
			StringBuffer hsql = new StringBuffer();
			hsql
					.append(
							"from com.kingstargroup.ecard.hibernate.photo.TPhoto photo where")
					.append(" photo.stuempno = ?");
			Query q = s.createQuery(hsql.toString());
			q.setString(0, stuempno);
			List list = q.list();
			if (list != null && list.size() > 0) {
				tcifphoto = (TPhoto) list.get(0);
			}
			return tcifphoto;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	private static final Log _log = LogFactory.getLog(PhotoPersistence.class);
}
