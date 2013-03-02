package com.kingstargroup.ecard.portlet.card.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.card.TCard;
import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.hibernate.device.TDevice;
import com.kingstargroup.ecard.hibernate.photo.TPhoto;
import com.kingstargroup.ecard.hibernate.tradecode.TTranscode;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;

public class CardServiceUtil {

	/**
	 * Description:
	 * 
	 * @param customerId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static List getAvailableCards(String customerId)
			throws PortalException {
		CardService cardService = CardServiceFactory.getService();
		return cardService.getAvailableCards(customerId);
	}

	public static List getAllCards(String customerId)
	throws PortalException {
		CardService cardService = CardServiceFactory.getService();
		return cardService.getAllCards(customerId);
	}
	public static TDept getDept(String deptNo) throws PortalException {
		CardService cardService = CardServiceFactory.getService();
		return cardService.getDept(deptNo);
	}

	public static TCard getCardById(Long cardno) throws PortalException {
		CardService cardService = CardServiceFactory.getService();
		return cardService.getCardByno(cardno);
	}

	/**
	 * Description:
	 * 
	 * @param customerId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static TCard getCurrentCard(String custid)
			throws PortalException {
		CardService cardService = CardServiceFactory.getService();
		return cardService.getCurrentCard(custid);
	}

	/**
	 * Description:
	 * 
	 * @param customerId
	 * @param state
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static int getCardStatus(String custid, String state)
			throws PortalException {

		CardService cardService = CardServiceFactory.getService();
		return cardService.getCardStatus(custid, state);
	}

	/**
	 * Description:根据用户的学/工号挂失对应的卡
	 * 
	 * @param custid
	 *            Modify History:
	 */
	public static void processLostCard(String stuempNo, String cardId)
			throws PortalException {

		CardService cardService = CardServiceFactory.getService();
		cardService.processLostCard(stuempNo, cardId);

	}

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
		CardService cardService = CardServiceFactory.getService();
		return cardService.getTradeDetail(cardId, beginDate, endDate, page,
				size);

	}

	public static TTranscode getTradeCodeById(String code)
			throws PortalException {
		CardService cardService = CardServiceFactory.getService();
		return cardService.getTradeCodeById(code);

	}
	public static String getSysDate(int day) throws PortalException {
		CardService cardService = CardServiceFactory.getService();
		return cardService.getSysDate(day);

	}
	
	public static TDevice getDeviceById(String deviceid) throws PortalException {
		CardService cardService = CardServiceFactory.getService();
		return cardService.getDeviceById(deviceid);
	}
	
	
	
	//
	public static TPhoto getPhoto(String stuempno) throws PortalException {
		CardService cardService = CardServiceFactory.getService();
		return cardService.getPhoto(stuempno);
}
	
	//GateHisTradeDetail partition
	

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
		CardService cardService = CardServiceFactory.getService();
		return cardService.getGateHisTradeDetail(cardId, beginDate, endDate);
	}
	
	
	
	public static ResultPage getCKHisTradeDetail(String stuempNo, String beginDate, String endDate, int page, int size) throws PortalException {			
		CardService cardService = CardServiceFactory.getService();
		return cardService.getCKHisTradeDetail(stuempNo, beginDate, endDate, page);
	}
	
	public static int getCKHisTradeDetailSize(String stuempNo, String beginDate, String endDate) throws PortalException {			
		CardService cardService = CardServiceFactory.getService();
		return cardService.getCKHisTradeDetailSize(stuempNo, beginDate, endDate);
	}
	
	public static List getcomsumtradeSerial(String beginDate,String endDate,int cardid) throws PortalException{
		CardService cardService = CardServiceFactory.getService();
		return cardService.getcomsumtradeSerial(beginDate, endDate, cardid);
	
	}
	
	
	public static List getCheckAttSerial(String beginDate,String endDate,int cardid) throws PortalException{
		CardService cardService = CardServiceFactory.getService();
		return cardService.getCheckAttSerial(beginDate, endDate, cardid);
	
	}
	
	public static List getCheckAttSerial_td(String beginDate,String endDate,int cardid) throws PortalException{
		CardService cardService = CardServiceFactory.getService();
		return cardService.getCheckAttSerial_td(beginDate, endDate, cardid);
	
	}
	
	public static List getTdquerystat(String begindate,String enddate,String classno,String stuempno,String custname) throws PortalException{
		CardService cardService = CardServiceFactory.getService();
		return cardService.getTdquerystat(begindate, enddate, classno,stuempno,custname);
	
	}
	
	//end of 
}
