/**

 * 
 */
package com.kingstargroup.ecard.hibernate.util;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.device.TPifDevice;
import com.kingstargroup.ecard.hibernate.tradedetail.GateHisTradeDetailPersistence;
import com.kingstargroup.ecard.hibernate.tradedetail.GetErrorMsg;
import com.kingstargroup.ecard.util.DateFormatUtil;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * @author hjw
 *
 */
public class GateHisTradeDetailUtil extends BasicUtil {

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
		GateHisTradeDetailPersistence persistence = (GateHisTradeDetailPersistence) getPersistence(GateHisTradeDetailPersistence.class.getName());
		//SysDatePersistence sysPersistence = (SysDatePersistence) getPersistence(SysDatePersistence.class.getName());
		Transaction t = beginTransaction();
		ResultPage result = null;
		
		try {
			//String nowDate = sysPersistence.getSysDate(0).substring(0, 8);
			result = persistence.getGateHisTradeDetailsByDate(cardId, beginDate, endDate, page, size);
			
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
		List detailList = result.getFullList();
		List tableList = new ArrayList();
		for (int i = 0; i < detailList.size(); i++) {
			 Object[] objects = (Object[]) detailList.get(i);
			 /*
			  * index:
			  * 0-设备ID,1-发生日期,2-发生时间,4-交易状�?
			  */
			 HashMap detailMap = new HashMap();
			 TPifDevice device = DeviceUtil.getDeviceById(objects[0].toString());
			 if (device == null) {
				 detailMap.put("tradePlace", "Unkown Device");
			 } else {
				 detailMap.put("tradePlace", AreaUtil.getAreaById(device.getArea().toString()).getAreaName());//交易地点
			 }
			 detailMap.put("devicename",(String) objects[1]);
			 detailMap.put("tradeTime", DateFormatUtil.format((String) objects[2] + (String) objects[3]));//发生日期时间
			 detailMap.put("mark", getErrorMsg(Integer.parseInt(String.valueOf(objects[5]))));//交易状�?
			 //errcode.getErrMsg(addZero(String.valueOf(objects[4]))));
			 tableList.add(detailMap);			
		}
		result.setList(tableList);
		return result;
	}
	
	
	
	public static ResultPage getCKHisTradeDetail(String stuempNo, String beginDate, String endDate, int page, int size) throws PortalException {			
		GateHisTradeDetailPersistence persistence = (GateHisTradeDetailPersistence) getPersistence(GateHisTradeDetailPersistence.class.getName());
		//SysDatePersistence sysPersistence = (SysDatePersistence) getPersistence(SysDatePersistence.class.getName());
		Transaction t = beginTransaction();
		ResultPage result = null;
		
		try {
			//String nowDate = sysPersistence.getSysDate(0).substring(0, 8);
			result = persistence.getCKHisTradeDetailsByDate(stuempNo, beginDate, endDate, page, size);
			
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
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
		GateHisTradeDetailPersistence persistence = (GateHisTradeDetailPersistence) getPersistence(GateHisTradeDetailPersistence.class.getName());
		//SysDatePersistence sysPersistence = (SysDatePersistence) getPersistence(SysDatePersistence.class.getName());
		Transaction t = beginTransaction();
		int result = 0;
		
		try {
			//String nowDate = sysPersistence.getSysDate(0).substring(0, 8);
			result = persistence.getCKHisTradeDetailsSizeByDate(stuempNo, beginDate, endDate);
			
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
		
		return result;
	}
	
	public static String getErrorMsg(int code) throws PortalException {
		GetErrorMsg error = (GetErrorMsg) getPersistence(GetErrorMsg.class.getName());
		try {
			return error.getErrorMsgByCode(code);
		} catch  (DBSystemException dbse)  {
			throw dbse;
		} finally {
			closeSession();
		}
	}
}
