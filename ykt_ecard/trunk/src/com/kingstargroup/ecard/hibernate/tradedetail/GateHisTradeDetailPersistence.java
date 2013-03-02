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
	 * Description���������ʷ���Ž�ҽԺ���?
	 * Coder: ����ΰ
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
			 * ����ѯ�Ŀ�ʼ���ڴ��ڵ�ǰ��ݿ�ʱ�䣬ֻ�鵱����ˮ��?
			 */
			query = s.getNamedQuery("GateHisTradelogSQL");
			countQuery = s.getNamedQuery("GateHisTradelogCountSQL");
			query.setString("cardNo", cardId);
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

	
	private static final Log _log = LogFactory
			.getLog(GateHisTradeDetailPersistence.class);
}
