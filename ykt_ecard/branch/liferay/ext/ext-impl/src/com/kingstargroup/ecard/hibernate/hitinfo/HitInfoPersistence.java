/**
 * 
 */
package com.kingstargroup.ecard.hibernate.hitinfo;

import java.io.Serializable;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: HitInfoPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-17  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class HitInfoPersistence extends BasePersistence {	
	
	public void delete(String hitInfoIds[]) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			for (int i = 0; i < hitInfoIds.length; i++) {
				EcardHitInfo info = (EcardHitInfo) s.get(EcardHitInfo.class, Integer.valueOf(hitInfoIds[i]));
				if (info != null) {
					s.delete(info);
				}
			}
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally{
			closeSession(s);
		}
	}

	
	/**
	 * Description:
	 * @param title
	 * @param page 当前查询页
	 * @param size
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public ResultPage search(String title, int page, int size) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			StringBuffer buff = new StringBuffer();
			buff.append("select count(*) from EcardHitInfo hit, EcardInformation info")
				.append(" where hit.infoId = info.id");
			if (title != null && !title.equals("")) {
				buff.append(" and hit.title like :title");
			}			
			Query q = s.createQuery(buff.toString());
			if (title != null && !title.equals("")) {
				q.setString("title", "%" + title + "%");
			}
			int totalRecords = Integer.parseInt(String.valueOf(q.uniqueResult()));
			buff = new StringBuffer();
			buff.append("select new com.kingstargroup.ecard.hibernate.hitinfo.HitInfoResult(hit.id,hit.title,hit.infoId,")
			.append("info.infoType,info.infoTitle,info.attachments,info.createDate)")
			.append(" FROM EcardHitInfo hit,EcardInformation info")
				.append(" where hit.infoId = info.id");
			if (title != null && !title.equals("")) {
				buff.append(" and hit.title like :title");
			}
			buff.append(" order by info.createDate desc");
			Query resultQ = s.createQuery(buff.toString());
			if (title != null && !title.equals("")) {
				resultQ.setString("title", "%" + title + "%");
			}
			ResultPage result = new ResultPage(resultQ, page, size);
			int quotient = totalRecords / size;
			int remainder = totalRecords % size;
			if (remainder == 0 && quotient != 0) {
				result.setTotalPage(quotient);
			} else {
				result.setTotalPage(quotient + 1);
			}
			return result;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		} finally{
			closeSession(s);
		}
	}
	
	Log _log = LogFactory.getLog(HitInfoPersistence.class.getClass());
}
