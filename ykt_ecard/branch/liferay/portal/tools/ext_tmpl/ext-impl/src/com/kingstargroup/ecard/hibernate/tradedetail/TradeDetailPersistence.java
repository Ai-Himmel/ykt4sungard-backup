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
 * �������� ������ ����ʱ�� ��������<br>
 * ===================================<br>
 * ���� Xiao Qi 2005-9-26 <br>
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
	 * Description:�����û�ѡ��Ŀ�ʼ���ںͽ������ڣ��Լ���Ӧ���ŵõ�����ڼ����ˮ��¼
	 * 
	 * @param cardId
	 *            ����
	 * @param beginDate
	 *            ��ʼ����
	 * @param endDate
	 *            ��������
	 * @param page
	 *            ��ѯ��ҳ��
	 * @param size
	 *            ҳ�а�����¼����С
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
