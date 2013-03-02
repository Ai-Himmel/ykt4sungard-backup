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
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: TradeDetailPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-9-26 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
/**
 * @author hjw
 * 
 */
public class TradeDetailPersistence extends BasePersistence {

	/**
	 * Description:根据用户选择的开始日期和结束日期，以及对应卡号得到这段期间的流水记录
	 * 
	 * @param cardId
	 *            卡号
	 * @param beginDate
	 *            开始日期
	 * @param endDate
	 *            结束日期
	 * @param page
	 *            查询的页码
	 * @param size
	 *            页中包含记录数大小
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public ResultPage getTradeDetailsByDate(String cardno, String beginDate,
			String endDate, String sysDate, int page, int size)
			throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			// accId = "1000000000326835";
			Query query = null;
			Query countQuery = null;

			query = s.getNamedQuery("TradelogSQL");
			countQuery = s.getNamedQuery("TradelogCountSQL");
			query.setLong("cardno", Long.parseLong(cardno));
			query.setString("startDate", beginDate);
			query.setString("endDate", endDate);

			countQuery.setLong("cardno", Long.parseLong(cardno));
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

	private static final Log _log = LogFactory
			.getLog(TradeDetailPersistence.class);
}
