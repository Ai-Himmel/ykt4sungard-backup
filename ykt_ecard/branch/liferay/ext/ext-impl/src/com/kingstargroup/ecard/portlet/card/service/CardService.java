package com.kingstargroup.ecard.portlet.card.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.area.TArea;
import com.kingstargroup.ecard.hibernate.card.TCard;
import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.hibernate.device.TDevice;
import com.kingstargroup.ecard.hibernate.photo.TPhoto;
import com.kingstargroup.ecard.hibernate.tradecode.TTranscode;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public interface CardService {

	public List getAvailableCards(String custid) throws PortalException;
	public List getAllCards(String custid) throws PortalException;

	public TDept getDept(String deptcode) throws PortalException;

	public TCard getCardByno(Long cardno) throws PortalException;

	/**
	 * Description:
	 * 
	 * @param custid
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public TCard getCurrentCard(String custid) throws PortalException;

	/**
	 * Description:
	 * 
	 * @param custid
	 * @param state
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public int getCardStatus(String custid, String state)
			throws PortalException;

	/**
	 * Description:根据用户的学/工号挂失对应的卡
	 * 
	 * @param custid
	 *            Modify History:
	 */
	public void processLostCard(String stuempno, String cardno)
			throws PortalException;

	public ResultPage getTradeDetail(String cardno, String beginDate,
			String endDate) throws PortalException;

	public ResultPage getTradeDetail(String cardno, String beginDate,
			String endDate, int page) throws PortalException;

	public ResultPage getTradeDetail(String cardno, String beginDate,
			String endDate, int page, int size) throws PortalException;

	/**
	 * Description:根据交易代码得到交易描述信息
	 * 
	 * @param code
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public TTranscode getTradeCodeById(String code) throws PortalException;

	public String getSysDate(int day) throws PortalException;

	public TDevice getDeviceById(String deviceid) throws PortalException;

	
	//photopersistence
	public TPhoto getPhoto(String stuempno) throws PortalException;

	//gateHistradedetailpersistence

	public ResultPage getGateHisTradeDetail(String cardno, String beginDate,
			String endDate) throws PortalException;

	public ResultPage getGateHisTradeDetail(String cardno, String beginDate,
			String endDate, int page) throws PortalException;

	public ResultPage getCKHisTradeDetail(String stuempno, String beginDate,
			String endDate, int page) throws PortalException;

	public int getCKHisTradeDetailSize(String stuempno, String beginDate,
			String endDate, int page) throws PortalException;

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
	public ResultPage getGateHisTradeDetail(String cardno, String beginDate,
			String endDate, int page, int size) throws PortalException;

	public ResultPage getCKHisTradeDetail(String stuempno, String beginDate,
			String endDate, int page, int size) throws PortalException;

	public int getCKHisTradeDetailSize(String stuempno, String beginDate,
			String endDate) throws PortalException;
	
	public TArea getAreaById(String areaId) throws PortalException ;
	
	public  String getErrorMsg(int code) throws PortalException ;
	//消费流水
	public List getcomsumtradeSerial(String beginDate,String endDate,int cardid) throws PortalException;
	//考勤流水
	public List getCheckAttSerial(String beginDate,String endDate,int cardid) throws PortalException;
	//体锻流水
	public List getCheckAttSerial_td(String beginDate,String endDate,int cardid) throws PortalException;
	//体锻统计查询
	public List getTdquerystat(String begindate,String enddate,String classno,String stuempno,String custname) throws PortalException;
}
