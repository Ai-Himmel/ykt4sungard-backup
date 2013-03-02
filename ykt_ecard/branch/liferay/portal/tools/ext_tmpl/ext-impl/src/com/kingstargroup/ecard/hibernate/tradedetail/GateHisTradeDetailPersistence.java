/**
 * 
 */
package com.kingstargroup.ecard.hibernate.tradedetail;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * @author hjw
 * 
 */
public class GateHisTradeDetailPersistence extends BasePersistence {

	/**
	 * Description
	 * 
	 * @param cardId
	 * @param beginDate
	 * @param endDate
	 * @param page
	 * @param size
	 * @return
	 * @throws DBSystemException
	 */
	public ResultPage getGateHisTradeDetailsByDate(
			String cardId, 
			String beginDate,
			String endDate, 
			int page, 
			int size)
			throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			// accId = "1000000000326835";
			Query query = null;
			Query countQuery = null;
			/*
			 * 
			 */
			query = s.getNamedQuery("GateHisTradelogSQL");
			countQuery = s.getNamedQuery("GateHisTradelogCountSQL");
			query.setInteger("cardNo", Integer.parseInt(cardId));
			query.setString("startDate", beginDate);
			query.setString("endDate", endDate);

			countQuery.setInteger("cardNo", Integer.parseInt(cardId));
			countQuery.setString("startDate", beginDate);
			countQuery.setString("endDate", endDate);
			ResultPage result = new ResultPage(query, page, size);
			int totalRecords = ((Integer) countQuery.uniqueResult()).intValue();
			int quotient = totalRecords / size;
			int remainder = totalRecords % size;
			if (remainder == 0 && quotient != 0) {
				result.setTotalPage(quotient);
			} else {
				result.setTotalPage(quotient + 1);
			}
			return result;
			// return new ResultPage(query, page, size);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}finally{
			closeSession(s);
		}
	}

	/**
	 * Method name: getCKHisTradeDetailsByDate<br>
	 * Description: 海事考勤<br>
	 * Return: ResultPage<br>
	 * Args:
	 * 
	 * @param stuempNo
	 *            Args:
	 * @param beginDate
	 *            Args:
	 * @param endDate
	 *            Args:
	 * @param page
	 *            Args:
	 * @param size
	 *            Args:
	 * @return Args:
	 * @throws DBSystemException
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 Mar 12, 2008 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public ResultPage getCKHisTradeDetailsByDate(String stuempNo,
			String beginDate, String endDate, int page, int size)
			throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			// accId = "1000000000326835";
			Query query = null;
			Query countQuery = null;
			/*
			 * 
			 */
			query = s.getNamedQuery("CheckTTLogSQL");
			countQuery = s.getNamedQuery("CheckTTLogCountSQL");
			query.setString("stuempNo", stuempNo);
			query.setString("startDate", beginDate);
			query.setString("endDate", endDate);

			countQuery.setString("stuempNo", stuempNo);
			countQuery.setString("startDate", beginDate);
			countQuery.setString("endDate", endDate);
			ResultPage result = new ResultPage(query, page, size);
			int totalRecords = ((Integer) countQuery.uniqueResult()).intValue();
			int quotient = totalRecords / size;
			int remainder = totalRecords % size;
			if (remainder == 0 && quotient != 0) {
				result.setTotalPage(quotient);
			} else {
				result.setTotalPage(quotient + 1);
			}
			return result;
			// return new ResultPage(query, page, size);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	public int getCKHisTradeDetailsSizeByDate(String stuempNo,
			String beginDate, String endDate) throws DBSystemException {
		Session s = null;
		try {
			// accId = "1000000000326835";
			s = openSession();
			Query countQuery = null;

			countQuery = s.getNamedQuery("CheckTTLogCountSQL");
			countQuery.setString("stuempNo", stuempNo);
			countQuery.setString("startDate", beginDate);
			countQuery.setString("endDate", endDate);
			int totalRecords = ((Integer) countQuery.uniqueResult()).intValue();

			return totalRecords;
			// return new ResultPage(query, page, size);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	private static final Log _log = LogFactory
			.getLog(GateHisTradeDetailPersistence.class);
}
