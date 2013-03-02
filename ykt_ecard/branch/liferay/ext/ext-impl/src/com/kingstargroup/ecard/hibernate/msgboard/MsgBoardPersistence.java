/**
 * 
 */
package com.kingstargroup.ecard.hibernate.msgboard;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Criteria;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.criterion.Expression;
import org.hibernate.criterion.Projections;
import org.hibernate.criterion.Property;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: MsgBoardPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-10-11 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class MsgBoardPersistence extends BasePersistence {


	/**
	 * Description:根据指定查询条件得到符合关键字的留言
	 * 
	 * @param title
	 * @param content
	 * @param page
	 * @param size
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public ResultPage search(String title, String content, int page, int size)
			throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Criteria criteria = s.createCriteria(EcardMsgboard.class);
			if (title != null && !title.equals("")) {
				criteria.add(Expression.like("msgTitle", "%" + title + "%"));
			}
			if (content != null && !content.equals("")) {
				// criteria.add(Expression.like("postContent", "%" + content +
				// "%"));
				criteria.add(Expression.or(Expression.or(Expression.like(
						"postContent", "%" + content + "%"), Expression.like(
						"postContent", "" + content + "")), Expression.or(
						Expression.like("replyContent", "%" + content + "%"),
						Expression.like("replyContent", "" + content + ""))));
			}
			criteria.setProjection(Projections.alias(Projections.rowCount(),
					"countRecords"));
			int totalRecords = ((Integer) criteria.uniqueResult()).intValue();
			criteria.setProjection(null);
			criteria.addOrder(Property.forName("id").desc());
			ResultPage result = new ResultPage(criteria, page, size);
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
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:删除ids数组中包含的留言
	 * 
	 * @param ids
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public void deleteMsgs(int ids[]) throws DBSystemException {
		Session s = null;
		try {

			s = openSession();
			for (int i = 0; i < ids.length; i++) {
				s.delete(s.get(EcardMsgboard.class, new Integer(ids[i])));
			}
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:根据留言ID得到对应的留言
	 * 
	 * @param id
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public EcardMsgboard getMsg(int id) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			return (EcardMsgboard) s.get(EcardMsgboard.class, new Integer(id));
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	private static final Log _log = LogFactory
			.getLog(MsgBoardPersistence.class);

}
