/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.tradecode.TPifTradecode;
import com.kingstargroup.ecard.hibernate.tradecode.TradeCodePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: TradeCodeUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class TradeCodeUtil extends BasicUtil {
	/**
	 * Description:根据交易代码得到交易描述信息
	 * @param code
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TPifTradecode getTradeCodeById(String code) throws PortalException {
		TradeCodePersistence persistence = (TradeCodePersistence) getPersistence(TradeCodePersistence.class.getName());
		Transaction t = beginTransaction();
		TPifTradecode tradeCode = null;
		try {
			tradeCode = persistence.getTradeCodeById(code);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return tradeCode;
	}
}
