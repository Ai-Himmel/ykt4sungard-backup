package com.kingstargroup.fdykt.trade;

import java.math.BigDecimal;
import java.sql.SQLException;
import java.util.HashMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BccUtil;
import com.kingstargroup.fdykt.util.DateUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class GetSidyAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(GetSidyAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doGetSidy(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doGetSidy(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = request.getParameter("cardphyid");
		String card_bala = request.getParameter("cardBala");
		String dptCardCnt = request.getParameter("dptCardCnt");
		String payCardCnt = request.getParameter("payCardCnt");
		String cardsidyno = request.getParameter("sidyno");
		if (cardphyid == null || null == card_bala || "".equals(card_bala)
				|| "".equals(cardphyid) || null == dptCardCnt || "".equals(dptCardCnt) || null == payCardCnt || "".equals(payCardCnt)) {
			String xmlout = XMLGenerateUtil.XMLGenerate("7777", "重新登陆", null,
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		double CardBala = Double.parseDouble(card_bala);

		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			System.out.println("卡信息读取失败");
			String xmlout = XMLGenerateUtil.XMLGenerate("1002",
					"系统出现异常，请稍后重试！", null, null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		String reqip = request.getRemoteAddr();
//		reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				String xmlout = XMLGenerateUtil.XMLGenerate("1003",
						"设备未注册，不能使用此功能！", null, null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"设备未注册，不能使用此功能！", null, null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_sidy", 846318);// 后台业务功能号
//		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		String ipServer = KSConfiguration.getInstance().getProperty("drtpip1",
				"172.0.0.1");
		String drtpPort = KSConfiguration.getInstance().getProperty(
				"drtpport1", "4000");
		String svrFunc = KSConfiguration.getInstance().getProperty(
				"mainfunction1", "6000");
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			bcc.XPackInit(1);
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetStringFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						String.valueOf(card.getCardno()).getBytes());
				bcc.SetDoubleFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						CardBala);
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(dptCardCnt));
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
						Integer.parseInt(payCardCnt));
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol4".getBytes(),
						Integer.parseInt(cardsidyno));
				bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
						.getBytes(), String.valueOf(deviceid).getBytes());
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							// 补助金额
							double[] SidyAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
									.getBytes(), SidyAmount);
							// 交易后余额
							double[] OutCardAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "lvol8"
									.getBytes(), OutCardAmount);
							// 流水号
							byte[] SerialNo = new byte[26];
							bcc.GetStringFieldByName(xpackhandle, 0, "lserial1"
									.getBytes(), SerialNo, 26);
							// 补助批次号
							int[] sidyno = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol4"
									.getBytes(), sidyno);

							// 日期
							byte[] sdate3 = new byte[10];
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate3"
									.getBytes(), sdate3, 10);

							String serial_no = BccUtil
									.getStringFromByte(SerialNo);
							String datetime = BccUtil.getStringFromByte(sdate3);

							BigDecimal s = new BigDecimal(Double
									.toString(OutCardAmount[0]));
							BigDecimal c = new BigDecimal("1");
							BigDecimal one = new BigDecimal("1");
							BigDecimal f = s.divide(one, 2,
									BigDecimal.ROUND_HALF_UP);
							String cout_card_amount = String.valueOf(f
									.multiply(c).doubleValue());

							if (cout_card_amount.indexOf(".") > 0) {
								cout_card_amount = cout_card_amount.substring(
										0, cout_card_amount.indexOf("."));
							}


							String stime3 = DateUtil.getNow().substring(8);
							HashMap datamap = new HashMap();
							datamap.put("SidyAmount", String
									.valueOf(SidyAmount[0] * 100));
							datamap.put("OutCardAmount", cout_card_amount);
							datamap.put("SerialNo", serial_no);
							datamap.put("CardId", cardphyid);
							datamap.put("txCnt", String.valueOf(0));
							datamap.put("sidyno", String.valueOf(sidyno[0]));
							datamap.put("sdate3", datetime);
							datamap.put("stime3", stime3);
							datamap.put("ipServer", ipServer);
							datamap.put("drtpPort", drtpPort);
							datamap.put("svrFunc", svrFunc);

							String xmlout = XMLGenerateUtil.XMLGenerate("0000",
									"补助领取成功", datamap, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"无数据返回!", null, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							int i;

							String vs_mess = BccUtil.getStringFromByte(vsmess);

							String xmlout = XMLGenerateUtil.XMLGenerate("0002",
									vs_mess, null, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"无数据返回!", null, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					}

				} else {
					// 请求失败

					int i;
					for (i = 0; i < errmsg.length; i++) {
						if (errmsg[i] == 0) {
							break;
						}
					}
					String s = new String(errmsg, 0, i);
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					String xmlout = XMLGenerateUtil.XMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " + s, null, null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.XMLGenerate("1002",
					"系统出现异常，请稍后重试！", null, null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"系统出现异常，请稍后重试！", null, null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1004",
					"系统初始化异常，请稍后重试！", null, null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}
}
