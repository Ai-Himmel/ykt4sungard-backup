/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.device.TDevice;
import com.kingstargroup.ecard.hibernate.tradedetail.TradeDetailPersistence;
import com.kingstargroup.ecard.util.DateFormatUtil;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: TradeDetailUtil.java<br>
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
/**
 * @author hjw
 * 
 */
public class TradeDetailUtil {

	public static ResultPage getTradeDetail(String cardId, String beginDate,
			String endDate) throws PortalException {
		return getTradeDetail(cardId, beginDate, endDate, 0);
	}

	public static ResultPage getTradeDetail(String cardId, String beginDate,
			String endDate, int page) throws PortalException {
		return getTradeDetail(cardId, beginDate, endDate, page,
				EcardConstants.LIST_MORE_SIZE);
	}

	/**
	 * Description:
	 * 
	 * @param cardId
	 * @param beginDate
	 * @param endDate
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static ResultPage getTradeDetail(String cardId, String beginDate,
			String endDate, int page, int size) throws PortalException {

		ResultPage result = null;
		String nowDate = SysDateUtil.getSysDate(0).substring(0, 8);
		result = getPersistence().getTradeDetailsByDate(cardId, beginDate,
				endDate, nowDate, page, size);
		List detailList = result.getFullList();
		List tableList = new ArrayList();
		for (int i = 0; i < detailList.size(); i++) {
			Object[] objects = (Object[]) detailList.get(i);
			/*
			 * index: 0-���״���,1-�豸ID,2-��������,3-����ʱ��,4-���׷�����,5-���º��ʻ����
			 */
			HashMap detailMap = new HashMap();
			detailMap.put("tradeName", TradeCodeUtil.getTradeCodeById(
					objects[0].toString()).getTransname());// ��������
			TDevice device = DeviceUtil.getDeviceById(objects[1].toString());
			if (device == null) {
				detailMap.put("tradePlace", "Unkown Device");
			} else {
//				if (device.getAreacode() != null) {
//					detailMap.put("tradePlace", AreaUtil.getAreaBycode(
//							device.getAreacode()).getAreaname());// ���׵ص�
//				} else {
//					detailMap.put("tradePlace", "Unkown Device");
//				}
				detailMap.put("tradePlace", device.getDevicename());
			}
			detailMap.put("tradeTime", DateFormatUtil
					.format((String) objects[2] + (String) objects[3]));// ��������ʱ��
			detailMap.put("tradeAmount", padAmount(((Double) objects[4])
					.toString()));// ���׽��
			detailMap.put("balance", padAmount(String.valueOf(objects[5])));// �ʻ����
			tableList.add(detailMap);
		}
		result.setList(tableList);
		return result;
	}

	private static String padAmount(String amount) {
		int dotPosition = amount.indexOf(".");
		if (dotPosition != -1) {
			if (amount.substring(dotPosition + 1).length() == 1) {
				amount = amount + "0";
			}
		}
		return amount;
	}

	public static TradeDetailPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(TradeDetailPersistence persistence) {
		_persistence = persistence;
	}

	private static TradeDetailUtil _getUtil() {
		if (_util == null) {
			_util = (TradeDetailUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = TradeDetailUtil.class.getName();
	private static TradeDetailUtil _util;
	private TradeDetailPersistence _persistence;

}
