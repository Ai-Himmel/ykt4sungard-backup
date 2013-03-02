/**
 * 
 */
package com.kingstargroup.ecard.hibernate.postpone;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Criteria;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.criterion.Expression;
import org.hibernate.criterion.Projections;
import org.hibernate.criterion.Property;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PostponePersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-28  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class PostponePersistence extends BasicPersistence {
	/**
	 * Description:根据客户ID得到对应的卡延期申请信息
	 * @param stuempNo
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public EcardPostponeApply getPostponeByStuempNo(String stuempNo) throws DBSystemException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from EcardPostponeApply as apply where apply.stuempno = :stuempNo order by id desc");
			q.setString("stuempNo", stuempNo);
			List result = q.list();
			if (result.size() == 0) {
				return null;
			} else {
				return (EcardPostponeApply) result.get(0);
			}			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public EcardPostponeApply getPostpone(String id) throws DBSystemException {
		Session s = getSession();
		try {
			return (EcardPostponeApply) s.get(EcardPostponeApply.class, new Integer(id));
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:
	 * @param applyId
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void delete(String applyId) throws DBSystemException {
		Session s = getSession();
		try {
			EcardPostponeApply apply = (EcardPostponeApply) s.get(EcardPostponeApply.class, new Integer(applyId));
			if (apply != null) {
				s.delete(apply);
			}
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
			
		}
	}
	
	/**
	 * Description:
	 * @param apply
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void saveOrUpdate(EcardPostponeApply apply) throws DBSystemException {
		Session s = getSession();
		try {
			s.saveOrUpdate(apply);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:
	 * @param status
	 * @param page
	 * @param size
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public ResultPage search(String status, int page, int size) throws DBSystemException { 
		Session s = getSession();
		try {
			/**Criteria criteria = s.createCriteria(EcardPostponeApply.class);	
			criteria.add(Expression.eq("status", status));
			criteria.setProjection(Projections.alias(Projections.rowCount(), "countRecords"));			
			int totalRecords = ((Integer) criteria.uniqueResult()).intValue();
			criteria.setProjection(null);
			criteria.addOrder(Property.forName("id").desc());**/
			//Query query = s.createQuery(" from EcardPostponeApply where status='"+status+"' order by id desc");
			//query.set
			//int totalRecords =  query.list().size();
			//ResultPage result = new ResultPage(criteria, page, size);
			
			//ResultPage result = new ResultPage(query, page, size);
			int totalRecords = 1;
			ResultPage result = new ResultPage( page, size);
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
			throw new DBSystemException("kao----------------------------------" + ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(PostponePersistence.class);
}
