package com.kingstargroup.fdykt.trade;

import java.io.IOException;
import java.sql.SQLException;
import java.util.Arrays;

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

public class GetOnlineCheckAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(GetOnlineCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = doOnlineCheck(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}

		if (forward.equals(mapping.findForward("none"))) {
			if (request.getSession().getAttribute("REQ_URL") != null) {
				try {
					response.sendRedirect(request.getSession().getAttribute(
							"REQ_URL").toString()+"&onlinecheck=checked");
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				return null;
			} else {
				return forward;
			}

		} else {
			return forward;
		}
	}

	private ActionForward doOnlineCheck(ActionMapping mapping,
			HttpServletRequest request) {
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = request.getParameter("cardphyid"); // 物理卡号
		String dptCardCnt = request.getParameter("dptCardCnt");// 充值次数
		String payCardCnt = request.getParameter("payCardCnt");// 消费次数
		String cardBala = request.getParameter("cardBala");// 卡余额
		String tradetype = request.getParameter("tradetype");// 交易类型
		
		

		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
			if (card == null) {
				request.setAttribute("errmsg", "卡信息异常，请检查是否正常卡!");
				return mapping.findForward("failure");
			}
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			request.setAttribute("errmsg", "卡信息读取失败");
			return mapping.findForward("failure");
		}

		String reqip = request.getRemoteAddr();
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				request.setAttribute("errmsg", "设备未注册，不能使用此功能！");
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			request.setAttribute("errmsg", "设备未注册，不能使用此功能！");
			return mapping.findForward("failure");
		}

		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_online_check", 200001);// 后台业务功能号
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

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// 卡号

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(cardBala));// 卡余额

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
						Integer.parseInt(dptCardCnt));// 充值次数
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(payCardCnt));// 消费次数
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(),
						tradetype.getBytes());

				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {

							int[] intRec = new int[1];
							double[] doubleRec = new double[1];

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol1"
									.getBytes(), intRec);// 是否需要补写
							String lvol1 = String.valueOf(intRec[0]);

							if ("1".equals(lvol1)) {

								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, 0, "lvol8"
										.getBytes(), intRec);// 出卡值（分）
								String lvol8 = String.valueOf(intRec[0]);
								
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, 0, "lvol7"
										.getBytes(), intRec);// 交易前值（分）
								String lvol7 = String.valueOf(intRec[0]);

								Arrays.fill(intRec, 0);
								bcc.GetDoubleFieldByName(xpackhandle, 0,
										"damt0".getBytes(), doubleRec);
								String damt0 = String.valueOf(doubleRec[0]);

								byte[] byteStr = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"sdate0".getBytes(), byteStr, 300);
								String sdate0 = BccUtil
										.getStringFromByte(byteStr);// 上次交易日期

								Arrays.fill(byteStr, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, 0,
										"stime0".getBytes(), byteStr, 300);
								String stime0 = BccUtil
										.getStringFromByte(byteStr);// 上次交易时间

								Arrays.fill(byteStr, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, 0,
										"lcert_code".getBytes(), byteStr, 300);
								String lcert_code = BccUtil
										.getStringFromByte(byteStr);// 上次交易代码

								Arrays.fill(byteStr, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, 0,
										"snote".getBytes(), byteStr, 300);
								String snote = BccUtil
										.getStringFromByte(byteStr);// 上次交易名称

								Arrays.fill(byteStr, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), byteStr, 300);
								String vsmess = BccUtil
										.getStringFromByte(byteStr);// 备注信息
								String ipServer = KSConfiguration.getInstance().getProperty("drtpip1",
								"172.0.0.1");
								String drtpPort = KSConfiguration.getInstance().getProperty(
										"drtpport1", "4000");
								String svrFunc = KSConfiguration.getInstance().getProperty(
										"mainfunction1", "6000");
								
								request.setAttribute("ipServer", ipServer);
								request.setAttribute("drtpPort", drtpPort);
								request.setAttribute("svrFunc", svrFunc);	
								request.setAttribute("cardphyid", cardphyid);
								request.setAttribute("lvol7", lvol7);
								request.setAttribute("lvol8", lvol8);
								request.setAttribute("damt0", damt0);
								request.setAttribute("sdate0", sdate0);
								request.setAttribute("stime0", stime0);
								request.setAttribute("lcert_code", lcert_code);
								request.setAttribute("snote", snote);
								request.setAttribute("vsmess", vsmess);

								return mapping.findForward("success");

							} else {
								request.setAttribute("errmsg", "没有需要补写信息");
								return mapping.findForward("none");
							}

						} else {
							request.setAttribute("errmsg", "后台处理失败");
							return mapping.findForward("failure");
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							request.setAttribute("errmsg", vs_mess);
							return mapping.findForward("failure");
						} else {
							request.setAttribute("errmsg", "后台处理失败");
							return mapping.findForward("failure");
						}

					}

				} else {
					// 请求失败
					String s = BccUtil.getStringFromByte(errmsg);
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					request.setAttribute("errmsg", "后台通讯暂时不可用，请稍后重试！ " + s);
					return mapping.findForward("failure");
				}
			}

			request.setAttribute("errmsg", "系统出现异常，请稍后重试！");
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！");
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统初始化异常，请稍后重试！");
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
