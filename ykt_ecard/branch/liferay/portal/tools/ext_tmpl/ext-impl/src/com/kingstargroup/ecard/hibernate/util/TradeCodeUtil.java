/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.tradecode.TPifTradecode;
import com.kingstargroup.ecard.hibernate.tradecode.TTranscode;
import com.kingstargroup.ecard.hibernate.tradecode.TradeCodePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: TradeCodeUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class TradeCodeUtil {
	/**
	 * Description:���ݽ��״���õ�����������Ϣ
	 * @param code
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TTranscode getTradeCodeById(String code) throws PortalException {
			return getPersistence().getTradeCodeById(code);

	}
	
	public static TradeCodePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(TradeCodePersistence persistence) {
		_persistence = persistence;
	}

	private static TradeCodeUtil _getUtil() {
		if (_util == null) {
			_util = (TradeCodeUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = TradeCodeUtil.class.getName();
	private static TradeCodeUtil _util;
	private TradeCodePersistence _persistence;
}
