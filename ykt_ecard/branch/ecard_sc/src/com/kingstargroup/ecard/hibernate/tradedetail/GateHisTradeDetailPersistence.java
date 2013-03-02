/**
 * 
 */
package com.kingstargroup.ecard.hibernate.tradedetail;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

/**
 * @author hjw
 *
 */
public class GateHisTradeDetailPersistence extends BasicPersistence {

	/**
	 * Descriptionï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½Å½ï¿½Ò½Ôºï¿½ï¿½Ë?
	 * Coder: ï¿½ï¿½ï¿½ï¿½Î°
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
		Session s = getSession();
		try {
			// accId = "1000000000326835";
			Query query = null;
			Query countQuery = null;
			/*
			 * ï¿½ï¿½ï¿½ï¿½Ñ¯ï¿½Ä¿ï¿½Ê¼ï¿½ï¿½ï¿½Ú´ï¿½ï¿½Úµï¿½Ç°ï¿½ï¿½Ý¿ï¿½Ê±ï¿½ä£¬Ö»ï¿½éµ±ï¿½ï¿½ï¿½ï¿½Ë®ï¿½ï¿?
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
		}
	}
	
	
	/**
			* Method name: getCKHisTradeDetailsByDate<br>
			* Description: º£ÊÂ¿¼ÇÚ<br>
			* Return: ResultPage<br>
			* Args: @param stuempNo
			* Args: @param beginDate
			* Args: @param endDate
			* Args: @param page
			* Args: @param size
			* Args: @return
			* Args: @throws DBSystemException
			* Modify History: <br>
			* ²Ù×÷ÀàÐÍ    ²Ù×÷ÈË     ²Ù×÷Ê±¼ä       ²Ù×÷ÄÚÈÝ<br>
			* ======================================<br>
			*  ´´½¨      ºÎÁÖÇà    Mar 12, 2008  <br>
			* @author   ºÎÁÖÇà
			* @version 
			* @since 1.0
			*/
	public ResultPage getCKHisTradeDetailsByDate(
			String stuempNo, 
			String beginDate,
			String endDate, 
			int page, 
			int size)
			throws DBSystemException {
		Session s = getSession();
		try {
			// accId = "1000000000326835";
			Query query = null;
			Query countQuery = null;
			/*
			 * ï¿½ï¿½ï¿½ï¿½Ñ¯ï¿½Ä¿ï¿½Ê¼ï¿½ï¿½ï¿½Ú´ï¿½ï¿½Úµï¿½Ç°ï¿½ï¿½Ý¿ï¿½Ê±ï¿½ä£¬Ö»ï¿½éµ±ï¿½ï¿½ï¿½ï¿½Ë®ï¿½ï¿?
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
		}
	}
	
	public int getCKHisTradeDetailsSizeByDate(
			String stuempNo, 
			String beginDate,
			String endDate)
			throws DBSystemException {
		Session s = getSession();
		try {
			// accId = "1000000000326835";

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
		}
	}

	
	private static final Log _log = LogFactory
			.getLog(GateHisTradeDetailPersistence.class);
}
