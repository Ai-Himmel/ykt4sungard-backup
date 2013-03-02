package com.kingstargroup.ecard.portlet.card.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.ecard.BccctlInit;
import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.exceptions.ProcessCardLossException;
import com.kingstargroup.ecard.hibernate.area.TArea;
import com.kingstargroup.ecard.hibernate.card.TCard;
import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.hibernate.device.TDevice;
import com.kingstargroup.ecard.hibernate.device.VTerm;
import com.kingstargroup.ecard.hibernate.photo.TPhoto;
import com.kingstargroup.ecard.hibernate.tradecode.TTranscode;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.portlet.distribution.service.CustomerLocalServiceUtil;
import com.kingstargroup.ecard.util.BccUtil;
import com.kingstargroup.ecard.util.DateFormatUtil;
import com.kingstargroup.ecard.util.EcardConstants;

public class CardServiceImpl extends CardServiceBase {

	/**
	 * Description:
	 * 
	 * @param customerId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public List getAvailableCards(String custid) throws PortalException {
		return cardPersistence.getAvailableCards(custid);
	}
	public List getAllCards(String custid) throws PortalException {
		return cardPersistence.getAllCards(custid);
	}

	public TDept getDept(String deptcode) throws PortalException {
		return cardPersistence.getDept(deptcode);
	}

	public TCard getCardByno(Long cardno) throws PortalException {
		return cardPersistence.getCardByno(cardno);
	}

	/**
	 * Description:
	 * 
	 * @param customerId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public TCard getCurrentCard(String custid) throws PortalException {
		return cardPersistence.getCurrentValidCard(custid);
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
	public int getCardStatus(String custid, String state)
			throws PortalException {

		int status = 0;

		TCard card = cardPersistence.getCardByCustidAndState(custid,
				state);
		if (card != null) { 
			long type = card.getCardtype().longValue();
			if (type == 1) {
				status = 100559;// 该客户正式卡未挂失,不能办临时卡
			} else {
				status = 100560;// 该客户有一张临时卡可正常使用,不能再办临时卡
			}
		}
		return status;
	}

	/**
	 * Description:根据用户的学/工号挂失对应的卡
	 * 
	 * @param customerId
	 *            Modify History:
	 */
	public void processLostCard(String stuempno, String cardno)
			throws PortalException {
		//TCustomer customer = CustomerLocalServiceUtil.getCustomerByStuempno(stuempno);
		try {
			//if (customer != null) {
			long xpackhandle = 0;
			int drtpno = 0;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// 后台drtp功能号
			int mainfunction = KSConfiguration.getInstance()
					.getPropertyAsInt("mainfunction", 9000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"logicfunc_card_loss", 846801);// 后台业务功能号
			int tries = KSConfiguration.getInstance().getPropertyAsInt(
					"tries", 3);// 默认重试次数
			int[] RetCode = new int[1];
			int[] RecordCount = new int[1];
			bccclt bcc = null;
			try {
				bcc = BccctlInit.getBccctlInstance();
				xpackhandle = bcc.NewXpackHandle(KSConfiguration
						.getInstance().getProperty("cpackfile",
								"/opt/cpack.dat").getBytes());
				if (0 != xpackhandle) {
					bcc.SetRequestType(xpackhandle, func);
//						bcc.SetIntFieldByName(xpackhandle, 0, "lvol0"
//								.getBytes(), Integer.parseInt(customer
//								.getCustid().toString()));// 客户号
//						bcc.SetIntFieldByName(xpackhandle, 0, "lvol1"
//								.getBytes(), Integer.parseInt("0"));// 交易卡号
//						bcc.SetIntFieldByName(xpackhandle, 0, "lvol2"
//								.getBytes(), Integer.parseInt("0"));// 交易卡号
//						bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd"
//								.getBytes(), "1".getBytes());// 密码
//						bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0"
//								.getBytes(), "0".getBytes());// 校验密码
//						bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
//								.getBytes(), "web".getBytes());// 操作员						
					bcc.SetRequestType(xpackhandle, func);
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
							Integer.parseInt(cardno));// 卡号
					bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
							.getBytes(), "".getBytes());// 密码
					bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
							.getBytes(), "1".getBytes());//终端号
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus1"
							.getBytes(), "1".getBytes());//挂失解挂标识

					boolean bccret = false;
					while (--tries >= 0) {
						bccret = bcc.CallRequest(xpackhandle, drtpno,
								branchno, mainfunction, 2000, errcode,
								errmsg);
						if (bccret) {
							break;
						}
					}
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 != RetCode[0]) {
							// 失败
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);
								String vs_mess = BccUtil.getStringFromByte(vsmess);
								throw new ProcessCardLossException(vs_mess);
							} else {
								throw new ProcessCardLossException("后台处理失败");
							}

						}

					} else {
						// 请求失败
						throw new ProcessCardLossException("请求失败");

					}
					}

				} catch (Exception e) {
					// TODO: handle exception
					e.printStackTrace();
					throw new ProcessCardLossException("系统出现异常，请稍后重试！");
				} catch (UnsatisfiedLinkError e) {
					e.printStackTrace();
					throw new ProcessCardLossException("动态库加载失败，请稍后重试！");
				} finally {
					if (xpackhandle != 0) {
						bcc.DeleteXpackHandle(xpackhandle);
					}
			}
			//} else {
				//throw new ProcessCardLossException("系统可能超时或发生异常，请重新登录后重试！");
			//}
		} catch (PortalException e) {
			e.printStackTrace();
			throw e;
		} catch (Exception he) {
			he.printStackTrace();
			throw new DBSystemException(he);
		}
	}

	public ResultPage getTradeDetail(String cardId, String beginDate,
			String endDate) throws PortalException {
		return getTradeDetail(cardId, beginDate, endDate, 0);
	}

	public ResultPage getTradeDetail(String cardId, String beginDate,
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
	public ResultPage getTradeDetail(String cardno, String beginDate,
			String endDate, int page, int size) throws PortalException {

		ResultPage result = null;
		String nowDate = getSysDate(0).substring(0, 8);
		result = tradeDetailPersistence.getTradeDetailsByDate(cardno,
				beginDate, endDate, nowDate, page, size);
		List detailList = result.getFullList();
		List tableList = new ArrayList();
		for (int i = 0; i < detailList.size(); i++) {
			Object[] objects = (Object[]) detailList.get(i);
			/*
			 * index: 0-交易代码,1-设备ID,2-发生日期,3-发生时间,4-交易发生额,5-更新后帐户余额
			 */
			HashMap detailMap = new HashMap();
			detailMap.put("tradeName", getTradeCodeById(objects[0].toString())
					.getTransname());// 交易名称
			VTerm term = getVtembyId(objects[1].toString());
			if (term == null) {
				detailMap.put("tradePlace", "Unkown Device");
			} else {
//				if (device.getAreacode() != null) {
//					detailMap.put("tradePlace", AreaUtil.getAreaBycode(
//							device.getAreacode()).getAreaname());// 交易地点
//				} else {
//					detailMap.put("tradePlace", "Unkown Device");
//				}
				detailMap.put("tradePlace", term.getTermname());
			}
			detailMap.put("tradeTime", DateFormatUtil
					.format((String) objects[2] + (String) objects[3]));// 发生日期时间
			detailMap.put("tradeAmount", padAmount(((Double) objects[4])
					.toString()));// 交易金额
			detailMap.put("balance", padAmount(String.valueOf(objects[5])));// 帐户余额
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

	/**
	 * Description:根据交易代码得到交易描述信息
	 * 
	 * @param code
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public TTranscode getTradeCodeById(String code) throws PortalException {
		return tradeCodePersistence.getTradeCodeById(code);

	}

	public String getSysDate(int day) throws PortalException {
		return sysDatePersistence.getSysDate(day);

	}

	public TDevice getDeviceById(String deviceid) throws PortalException {
		TDevice device = null;
		try {
			device = devicePersistence.getDeviceById(deviceid);
		} catch (DBSystemException e) {
			throw e;
		}
		return device;
	}
	
	public VTerm getVtembyId(String termid)throws PortalException {
		VTerm vterm = null;
		try {
			vterm = devicePersistence.getVTermById(termid);
		} catch (DBSystemException e) {
			throw e;
		}
		return vterm;
	}
//photo
	public TPhoto getPhoto(String stuempno) throws PortalException {
		return  photoPersistence.getPhoto(stuempno);
}
	
	//gatehis
	

	public  ResultPage getGateHisTradeDetail(String cardId, String beginDate, String endDate) throws PortalException {
		return getGateHisTradeDetail(cardId, beginDate, endDate, 0);
	}
	
	public  ResultPage getGateHisTradeDetail(String cardId, String beginDate, String endDate, int page) throws PortalException {
		return getGateHisTradeDetail(cardId, beginDate, endDate, page, EcardConstants.LIST_MORE_SIZE);
	}
	
	public  ResultPage getCKHisTradeDetail(String stuempNo, String beginDate, String endDate, int page) throws PortalException {
		return getCKHisTradeDetail(stuempNo, beginDate, endDate, page, EcardConstants.LIST_MORE_SIZE);
	}
	
	public  int getCKHisTradeDetailSize(String stuempNo, String beginDate, String endDate, int page) throws PortalException {
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
	public  ResultPage getGateHisTradeDetail(String cardId, String beginDate, String endDate, int page, int size) throws PortalException {			
		ResultPage result = gateHisTradeDetailPersistence.getGateHisTradeDetailsByDate(cardId, beginDate, endDate, page, size);

		List detailList = result.getFullList();
		List tableList = new ArrayList();
		for (int i = 0; i < detailList.size(); i++) {
			 Object[] objects = (Object[]) detailList.get(i);
			 /*
			  * index:
			  * 
			  */
			 HashMap detailMap = new HashMap();
			 TDevice device = getDeviceById(objects[0].toString());
			 if (device == null) {
				 detailMap.put("tradePlace", "Unkown Device");
			 } else {
				 detailMap.put("tradePlace", getAreaById(device.getAreacode()).getAreaname());
			 }
			 detailMap.put("devicename",(String) objects[1]);
			 detailMap.put("tradeTime", DateFormatUtil.format((String) objects[2] + (String) objects[3]));
			 detailMap.put("mark", getErrorMsg(Integer.parseInt(String.valueOf(objects[5]))));
			 tableList.add(detailMap);			
		}
		result.setList(tableList);
		return result;
	}
	
	
	
	public  ResultPage getCKHisTradeDetail(String stuempNo, String beginDate, String endDate, int page, int size) throws PortalException {			
		ResultPage result = gateHisTradeDetailPersistence.getCKHisTradeDetailsByDate(stuempNo, beginDate, endDate, page, size);

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
	
	public  int getCKHisTradeDetailSize(String stuempNo, String beginDate, String endDate) throws PortalException {			
		return gateHisTradeDetailPersistence.getCKHisTradeDetailsSizeByDate(stuempNo, beginDate, endDate);
	}
	
	public List getcomsumtradeSerial(String beginDate,String endDate,int cardid) throws PortalException {

		List detailList = tradeDetailPersistence.getcomsumtradeSerial(beginDate, endDate, cardid);
		List tableList = new ArrayList();
		for (int i = 0; i < detailList.size(); i++) {
			Object[] objects = (Object[]) detailList.get(i);
			/*
			 * index: 0-交易代码,1-设备ID,2-发生日期,3-发生时间,4-交易发生额,5-更新后帐户余额
			 */
			HashMap detailMap = new HashMap();
			detailMap.put("tradeName", getTradeCodeById(objects[0].toString())
					.getTransname());// 交易名称
			VTerm term = getVtembyId(objects[1].toString());
			if (term == null) {
				detailMap.put("tradePlace", "");
			} else {
				detailMap.put("tradePlace", term.getTermname());
			}
			detailMap.put("tradeTime", DateFormatUtil
					.format((String) objects[2] + (String) objects[3]));// 发生日期时间
			detailMap.put("tradeAmount", padAmount(((Double) objects[4])
					.toString()));// 交易金额
			detailMap.put("balance", padAmount(String.valueOf(objects[5])));// 帐户余额
			tableList.add(detailMap);
		}
		return tableList;
	}
	
	public List getCheckAttSerial(String beginDate,String endDate,int cardid) throws PortalException {
		return gateHisTradeDetailPersistence.getCheckAttSerial(beginDate, endDate, cardid);
	}
	
	public List getCheckAttSerial_td(String beginDate,String endDate,int cardid) throws PortalException {
		return gateHisTradeDetailPersistence.getCheckAttSerial_td(beginDate, endDate, cardid);
	}
	
	public  List getTdquerystat(String begindate,String enddate,String classno,String stuempno,String custname) throws PortalException{
		return gateHisTradeDetailPersistence.getTdquerystat(begindate, enddate, classno,stuempno,custname);
	}
	
	//area
	
	public TArea getAreaById(String areacode) throws PortalException {
		return areaPersistence.getAreaBycode(areacode);
	}
	
	public String getErrorMsg(int code) throws PortalException {
		return errorMsgPersistence.getErrorMsgByCode(code);
}
}
