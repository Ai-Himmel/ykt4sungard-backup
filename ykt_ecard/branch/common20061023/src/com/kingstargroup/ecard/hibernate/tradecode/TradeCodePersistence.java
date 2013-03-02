/**
 * 
 */
package com.kingstargroup.ecard.hibernate.tradecode;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.tradedetail.TradeDetailPersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: TradeCodePersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class TradeCodePersistence extends BasicPersistence {
	
	/**
	 * Description:根据交易代码得到交易信息对象
	 * @param code 
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TPifTradecode getTradeCodeById(String code) throws DBSystemException {
		Session s = getSession();
		try {
			return (TPifTradecode) s.get(TPifTradecode.class, Integer.valueOf(code));
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(TradeCodePersistence.class);
}
