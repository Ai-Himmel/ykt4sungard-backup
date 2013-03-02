/**

 * 
 */
package com.kingstargroup.ecard.hibernate.util;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.device.TDevice;
import com.kingstargroup.ecard.hibernate.tradedetail.GateHisTradeDetailPersistence;
import com.kingstargroup.ecard.util.DateFormatUtil;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * @author hjw
 *
 */
public class GateHisTradeDetailUtil {

	public static ResultPage getGateHisTradeDetail(String cardId, String beginDate, String endDate) throws PortalException {
		return getGateHisTradeDetail(cardId, beginDate, endDate, 0);
	}
	
	public static ResultPage getGateHisTradeDetail(String cardId, String beginDate, String endDate, int page) throws PortalException {
		return getGateHisTradeDetail(cardId, beginDate, endDate, page, EcardConstants.LIST_MORE_SIZE);
	}
	
	public static ResultPage getCKHisTradeDetail(String stuempNo, String beginDate, String endDate, int page) throws PortalException {
		return getCKHisTradeDetail(stuempNo, beginDate, endDate, page, EcardConstants.LIST_MORE_SIZE);
	}
	
	public static int getCKHisTradeDetailSize(String stuempNo, String beginDate, String endDate, int page) throws PortalException {
		return getCKHisTradeDetailSize(stuempNo, beginDate, endDate);
	}
	
	
	
	
	/**
	 * Description:
	 * @param cardId
	 * @param beginDate
	 * @param endDate
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static ResultPage getGateHisTradeDetail(String cardId, String beginDate, String endDate, int page, int size) throws PortalException {			
		//SysDatePersistence sysPersistence = (SysDatePersistence) getPersistence(SysDatePersistence.class.getName());
		ResultPage result = getPersistence().getGateHisTradeDetailsByDate(cardId, beginDate, endDate, page, size);

		List detailList = result.getFullList();
		List tableList = new ArrayList();
		for (int i = 0; i < detailList.size(); i++) {
			 Object[] objects = (Object[]) detailList.get(i);
			 /*
			  * index:
			  * 
			  */
			 HashMap detailMap = new HashMap();
			 TDevice device = DeviceUtil.getDeviceById(objects[0].toString());
			 if (device == null) {
				 detailMap.put("tradePlace", "Unkown Device");
			 } else {
				 detailMap.put("tradePlace", AreaUtil.getAreaBycode(device.getAreacode()).getAreaname());//交易地点
			 }
			 detailMap.put("devicename",(String) objects[1]);
			 detailMap.put("tradeTime", DateFormatUtil.format((String) objects[2] + (String) objects[3]));//发生日期时间
			 detailMap.put("mark", ErrorMsgUtil.getErrorMsg(Integer.parseInt(String.valueOf(objects[5]))));//交易状�?
			 //errcode.getErrMsg(addZero(String.valueOf(objects[4]))));
			 tableList.add(detailMap);			
		}
		result.setList(tableList);
		return result;
	}
	
	
	
	public static ResultPage getCKHisTradeDetail(String stuempNo, String beginDate, String endDate, int page, int size) throws PortalException {			
		ResultPage result = getPersistence().getCKHisTradeDetailsByDate(stuempNo, beginDate, endDate, page, size);

		List detailList = result.getFullList();
		List tableList = new ArrayList();
		for (int i = 0; i < detailList.size(); i++) {
			 Object[] objects = (Object[]) detailList.get(i);
	
			 HashMap detailMap = new HashMap();
			 detailMap.put("custId",(Integer) objects[0]);
			 detailMap.put("cutName",(String) objects[1]);
			 detailMap.put("stuempNo",(String) objects[2]);
			 detailMap.put("attDate",(String) objects[3]);
			 detailMap.put("attnum",(Integer) objects[4]);			
			 tableList.add(detailMap);			
		}
		result.setList(tableList);
		return result;
	}
	
	public static int getCKHisTradeDetailSize(String stuempNo, String beginDate, String endDate) throws PortalException {			
		return getPersistence().getCKHisTradeDetailsSizeByDate(stuempNo, beginDate, endDate);
	}
	
	
	public static GateHisTradeDetailPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(GateHisTradeDetailPersistence persistence) {
		_persistence = persistence;
	}

	private static GateHisTradeDetailUtil _getUtil() {
		if (_util == null) {
			_util = (GateHisTradeDetailUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = GateHisTradeDetailUtil.class.getName();
	private static GateHisTradeDetailUtil _util;
	private GateHisTradeDetailPersistence _persistence;
}
