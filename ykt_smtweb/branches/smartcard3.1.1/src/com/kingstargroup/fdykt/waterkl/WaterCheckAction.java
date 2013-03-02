package com.kingstargroup.fdykt.waterkl;

import java.sql.SQLException;

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

public class WaterCheckAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(WaterCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = docheck(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward docheck(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = request.getParameter("cardphyid");
		String money = request.getParameter("money");
		String cardBala = request.getParameter("cardBala");
		String waterBala = request.getParameter("waterBala");
		String txCnt = request.getParameter("txCnt");
		String txCnt1 = request.getParameter("txCnt1");
		String sphone3 = request.getParameter("sphone3");
		String saddr = request.getParameter("saddr");
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("cardBala", cardBala);
		request.setAttribute("waterBala", waterBala);
		request.setAttribute("txCnt", txCnt);
		request.setAttribute("txCnt1", txCnt1);
		request.setAttribute("sphone3", sphone3);
		request.setAttribute("saddr", saddr);

		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			System.out.println("卡信息读取失败");
			request.setAttribute("errmsg", "卡信息读取失败!");
			return mapping.findForward("failure");
		}
 
		String reqip = request.getRemoteAddr();
//		reqip = "10.49.188.50";
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
				"logicfunc_water999_trans", 850010);// 后台业务功能号
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

				bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
						.getBytes(), String.valueOf(deviceid).getBytes());// 客户端id
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_auth"
						.getBytes(), DateUtil.getNow().getBytes());// 时间戳
				bcc.SetStringFieldByName(xpackhandle, 0, "sphone3".getBytes(),
						sphone3.getBytes());// 交易参考号
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(),
						saddr.getBytes());// 随机号
				bcc.SetStringFieldByName(xpackhandle, 0,
						"sstation1".getBytes(), cardphyid.getBytes());// 物理卡号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// 卡号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(cardBala));// 入卡值
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(txCnt));// 交易次数
				bcc.SetIntFieldByName(xpackhandle, 0, "lsafe_level".getBytes(),
						Integer.parseInt(waterBala));// 水控钱包余额
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
						Integer.parseInt(money) * 100);// 交易金额
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						Integer.parseInt("1000"));// 支付代码
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lbank_acc_type".getBytes(),1);// 钱包号

				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {

							int[] OutCardAmount = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol8"
									.getBytes(), OutCardAmount);
							int[] OutCardAmount1 = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lsafe_level"
									.getBytes(), OutCardAmount1);

							int[] TransAmount = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol5"
									.getBytes(), TransAmount);

							// 日期
							byte[] bytestr = new byte[10];
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate3"
									.getBytes(), bytestr, 10);

							String sdate3 = BccUtil.getStringFromByte(bytestr);
							bcc.GetStringFieldByName(xpackhandle, 0, "stime3"
									.getBytes(), bytestr, 10);
							String stime3 = BccUtil.getStringFromByte(bytestr);

							String out_card_amount = String
									.valueOf(OutCardAmount[0]);

							String out_card_amount1 = String
									.valueOf(OutCardAmount1[0]);

							request.setAttribute("outCardAmount",
									out_card_amount);
							request.setAttribute("outCardAmount1",
									out_card_amount1);

							request.setAttribute("sdate3", sdate3);
							request.setAttribute("stime3", stime3);
							return mapping.findForward("success");
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
