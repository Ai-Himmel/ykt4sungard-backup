/**
 * 
 */
package com.kingstargroup.ecard.hibernate.hitinfo;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.util.lang.FastStringBuffer;

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
public class HitInfoPersistence extends BasicPersistence {	
	
	public void delete(String hitInfoIds[]) throws DBSystemException {
		Session s = getSession();
		try {
			for (int i = 0; i < hitInfoIds.length; i++) {
				EcardHitInfo info = (EcardHitInfo) s.get(EcardHitInfo.class, Integer.valueOf(hitInfoIds[i]));
				if (info != null) {
					s.delete(info);
				}
			}
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
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
		Session s = getSession();
		try {
			FastStringBuffer buff = new FastStringBuffer();
			buff.append("select count(*) from EcardHitInfo as hit, EcardInformation as info")
				.append(" where hit.infoId = info.id");
			if (title != null && !title.equals("")) {
				buff.append(" and hit.title like :title");
			}			
			Query q = s.createQuery(buff.toString());
			if (title != null && !title.equals("")) {
				q.setString("title", "%" + title + "%");
			}
			int totalRecords = ((Integer) q.uniqueResult()).intValue();
			buff = new FastStringBuffer();
			buff.append("select new Map(info.createDate as createDate, info.infoType as infoType, info.attachments as attachments,")
				.append("hit.id as id, hit.infoId as infoId, hit.title as title, info.infoTitle as infoTitle)")
				.append(" from EcardHitInfo as hit, EcardInformation as info")
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
		}
	}
	
	Log _log = LogFactory.getLog(HitInfoPersistence.class.getClass());
}
