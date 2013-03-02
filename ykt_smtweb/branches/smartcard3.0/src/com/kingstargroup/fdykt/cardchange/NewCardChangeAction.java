package com.kingstargroup.fdykt.cardchange;

import java.sql.SQLException;
import java.util.Arrays;
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
import com.kingstargroup.fdykt.trade.MobileCheckAction;
import com.kingstargroup.fdykt.util.BccUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class NewCardChangeAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(MobileCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = saveinfo(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward saveinfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		saveToken(request);

		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = request.getParameter("cardphyid");
		String cardsubsidyno = request.getParameter("cardsubsidyno");
		String card_bala = request.getParameter("cardBala");
		String txCnt = request.getParameter("txCnt");
		String showcardno = request.getParameter("showcardno");
		String newcardphyid = request.getParameter("newcardphyid");

//		request.setAttribute("cardphyid", cardphyid);
//		request.setAttribute("cardsubsidyno", cardsubsidyno);
//		request.setAttribute("txCnt", txCnt);
//		request.setAttribute("cardBala", card_bala);
//		request.setAttribute("showcardno", showcardno);
//		request.setAttribute("newcardphyid", newcardphyid);

		String hexcardno = Integer.toHexString(Integer.parseInt(cardphyid))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}
		String newhexcardno = Integer.toHexString(Integer.parseInt(newcardphyid)).toUpperCase();
		for (int i = newhexcardno.length(); i < 8; i++) {
			newhexcardno = "0" + newhexcardno;// pad left
		}

		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			String xmlout = XMLGenerateUtil.XMLGenerate("8888", "卡信息读取错误",
					"", "", "", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		String reqip = request.getRemoteAddr();
		// reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				String xmlout = XMLGenerateUtil.XMLGenerate("9999", "设备未注册，不能使用此功能！",
						"", "", "", "", "", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			String xmlout = XMLGenerateUtil.XMLGenerate("9999", "设备未注册，不能使用此功能！",
					"", "", "", "", "", "", "", "", null);
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
				"logicfunc_changecard_oldcard", 846327);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						deviceid);// 客户端id
				// bcc.SetStringFieldByName(xpackhandle, 0, "semp".getBytes(),
				// "2000".getBytes());
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(),
						"C".getBytes());
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// 卡号

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol4".getBytes(),
						Integer.parseInt(cardsubsidyno));// 补助批次号

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
						Integer.parseInt(txCnt));// 交易次数(充值

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(txCnt));// 交易次数(消费

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(card_bala));// 卡余额

				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						hexcardno.getBytes());// 物理卡号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no2".getBytes(),
						newhexcardno.getBytes());//新卡物理卡号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder0".getBytes(),
						showcardno.getBytes());//显示卡号

				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							// double[] doubleRec = new double[1];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lserial1"
									.getBytes(), intRec);
							int lserial1 = intRec[0];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0,
									"lwithdraw_flag".getBytes(), intRec);
							int lwithdraw_flag = intRec[0];
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate3"
									.getBytes(), byteStrRec, 9);
							String sdate3 = BccUtil
									.getStringFromByte(byteStrRec);
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol0"
									.getBytes(), intRec);
							int lvol0 = intRec[0];
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sorder0"
									.getBytes(), byteStrRec, 11);
							String sorder0 = BccUtil
									.getStringFromByte(byteStrRec);
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol1"
									.getBytes(), intRec);
							int lvol1 = intRec[0];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0,
									"lsafe_level2".getBytes(), intRec);
							int lsafe_level2 = intRec[0];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol5"
									.getBytes(), intRec);
							int lvol5 = intRec[0];
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0,
									"sall_name".getBytes(), byteStrRec, 81);
							String sall_name = BccUtil
									.getStringFromByte(byteStrRec);
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "spager"
									.getBytes(), byteStrRec, 31);
							String spager = BccUtil
									.getStringFromByte(byteStrRec);
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "scert_no"
									.getBytes(), byteStrRec, 51);
							String scert_no = BccUtil
									.getStringFromByte(byteStrRec);
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "semail2"
									.getBytes(), byteStrRec, 61);
							String semail2 = BccUtil
									.getStringFromByte(byteStrRec);
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0,
									"smarket_code".getBytes(), byteStrRec, 2);
							String smarket_code = BccUtil
									.getStringFromByte(byteStrRec);
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate0"
									.getBytes(), byteStrRec, 9);
							String sdate0 = BccUtil
									.getStringFromByte(byteStrRec);
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol8"
									.getBytes(), intRec);
							int lvol8 = intRec[0];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol6"
									.getBytes(), intRec);
							int lvol6 = intRec[0];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol4"
									.getBytes(), intRec);
							int lvol4 = intRec[0];
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "stx_pwd"
									.getBytes(), byteStrRec, 9);
							String stx_pwd = BccUtil
									.getStringFromByte(byteStrRec);
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol11"
									.getBytes(), intRec);
							int lvol11 = intRec[0];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol12"
									.getBytes(), intRec);
							int lvol12 = intRec[0];

							HashMap result = new HashMap();

							result.put("lserial1", String.valueOf(lserial1));
							result.put("lwithdraw_flag", String
									.valueOf(lwithdraw_flag));
							result.put("sdate3", String.valueOf(sdate3));
							result.put("lvol0", String.valueOf(lvol0));

							result.put("sorder0", String.valueOf(sorder0));
							result.put("lvol1", String.valueOf(lvol1));
							result.put("lsafe_level2", String
									.valueOf(lsafe_level2));
							result.put("lvol5", String.valueOf(lvol5));

							result.put("sall_name", String.valueOf(sall_name));
							result.put("spager", String.valueOf(spager));
							result.put("scert_no", String.valueOf(scert_no));
							result.put("semail2", String.valueOf(semail2));

							result.put("smarket_code", String
									.valueOf(smarket_code));
							result.put("sdate0", String.valueOf(sdate0));
							result.put("lvol8", String.valueOf(lvol8));
							result.put("lvol6", String.valueOf(lvol6));
							result.put("lvol4", String.valueOf(lvol4));
							result.put("stx_pwd", String.valueOf(stx_pwd));
							result.put("lvol11", String.valueOf(lvol11));
							result.put("lvol12", String.valueOf(lvol12));
							String xmlout = XMLGenerateUtil.MapXMLGenerate(
									"0000", "新生换卡成功", result);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							System.out.println(xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.MapXMLGenerate(
									"0001", "无数据返回!", null);
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

							String vs_mess = BccUtil.getStringFromByte(vsmess);

							String xmlout = XMLGenerateUtil.MapXMLGenerate(
									"0002", vs_mess, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.MapXMLGenerate(
									"0001", "无数据返回!", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}
					}

				} else {
					// 请求失败
					String s = BccUtil.getStringFromByte(errmsg);
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					String xmlout = XMLGenerateUtil.MapXMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " + s, null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.MapXMLGenerate("1002",
					"系统出现异常，请稍后重试！", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.MapXMLGenerate("1003",
					"系统出现异常，请稍后重试！", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.MapXMLGenerate("1004",
					"系统初始化异常，请稍后重试！", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
