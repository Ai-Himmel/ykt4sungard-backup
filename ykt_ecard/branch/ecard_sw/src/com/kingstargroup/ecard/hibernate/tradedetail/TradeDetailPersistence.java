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
public class TradeDetailPersistence extends BasicPersistence {

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
	public ResultPage getTradeDetailsByDate(String cardId, String beginDate,
			String endDate, String sysDate, int page, int size)
			throws DBSystemException {
		Session s = getSession();
		try {
			// accId = "1000000000326835";
			Query query = null;
			Query countQuery = null;
			/*
			 * 如果查询的开始日期大于当前数据库时间，只查当日流水表
			 */
			if (beginDate.compareTo(sysDate) >= 0) {
				query = s.getNamedQuery("TodayTradelogSQL");
				countQuery = s.getNamedQuery("TodayTradelogCountSQL");
			} else {
				/*
				 * 否则两张流水表都要查询
				 */
				query = s.getNamedQuery("TradelogSQL");
				countQuery = s.getNamedQuery("TradelogCountSQL");
			}
			query.setInteger("cardId", Integer.parseInt(cardId));
			query.setString("startDate", beginDate);
			query.setString("endDate", endDate);

			countQuery.setInteger("cardId", Integer.parseInt(cardId));
			countQuery.setString("startDate", beginDate);
			countQuery.setString("endDate", endDate);
			
			_log.debug("TradelogCountSQL=" + countQuery.getQueryString());
			_log.debug("TradelogSQL=" + query.getQueryString());
			_log.debug("cardId=" + Integer.parseInt(cardId));
			_log.debug("startDate=" + beginDate);
			_log.debug("endDate=" + endDate);
			
			ResultPage result = new ResultPage(query, page, size);
			int totalRecords = ((Integer) countQuery.uniqueResult()).intValue();
			System.out.println("totalRecords=" + totalRecords);
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
	
	public ResultPage getTradeDetailsBy6(String cardId,  int page, int size)
			throws DBSystemException {
		Session s = getSession();
		try {
			// accId = "1000000000326835";
			Query query = null;	
				/*
				 * 两张流水表都要查询
				 */
			query = s.getNamedQuery("TradelogSQL_6");
			
			
			query.setInteger("cardId", Integer.parseInt(cardId));
				
			ResultPage result = new ResultPage(query, page, size);
			int totalRecords = 6; //((Integer) countQuery.uniqueResult()).intValue();
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
	

	private static final Log _log = LogFactory
			.getLog(TradeDetailPersistence.class);
}
