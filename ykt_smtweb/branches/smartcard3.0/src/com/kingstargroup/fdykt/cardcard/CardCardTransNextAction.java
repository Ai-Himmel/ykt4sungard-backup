package com.kingstargroup.fdykt.cardcard;

import org.apache.log4j.Logger;

import java.sql.SQLException;
import java.util.Arrays;
import java.util.HashMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

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

public class CardCardTransNextAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CardCardTransNextAction.class);

	/**
	 * Logger for this class
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			e.printStackTrace();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		if (logger.isDebugEnabled()) {
			logger
					.debug("doPutin(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();

		String money = request.getParameter("money");
		String cardphyno = request.getParameter("cardphyno");
		String cardbalance = request.getParameter("cardbalance");
		String cardcnt = request.getParameter("cardcnt");
		String outcardphyno = request.getParameter("outcardphyno");
		String outcardbalance = request.getParameter("outcardbalance");
		String outcardcnt = request.getParameter("outcardcnt");
		String serialNo = request.getParameter("serialNo");
		String sphone3 = request.getParameter("sphone3");
		String saddr = request.getParameter("saddr");

		request.setAttribute("money", money);
		request.setAttribute("cardphyno", cardphyno);
		request.setAttribute("cardbalance", cardbalance);
		request.setAttribute("cardcnt", cardcnt);
		request.setAttribute("outcardphyno", outcardphyno);
		request.setAttribute("outcardbalance", outcardbalance);
		request.setAttribute("outcardcnt", outcardcnt);

		String hexcardno = Integer.toHexString(Integer.parseInt(cardphyno))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}

		String outhexcardno = Integer.toHexString(
				Integer.parseInt(outcardphyno)).toUpperCase();
		for (int i = outhexcardno.length(); i < 8; i++) {
			outhexcardno = "0" + outhexcardno;// pad left
		}

		ActionErrors errors = new ActionErrors();
		CardDTO card = new CardDTO();
		CardDTO outcard = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
			outcard = carddao.getCardInfoById(outhexcardno);
		} catch (Exception e) {
			// TODO: handle exception
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "卡信息读取失败"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		String reqip = request.getRemoteAddr();
		// reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"deviceid.notregister"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"deviceid.notregister"));
			saveErrors(request, errors);
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
				"logicfunc_cardcard_check", 846328);// 后台业务功能号
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
						.getBytes(), String.valueOf(deviceid).getBytes());// 终端号
				bcc.SetIntFieldByName(xpackhandle, 0, "lbank_acc_type"
						.getBytes(), 2);// 交易标志

				bcc.SetIntFieldByName(xpackhandle, 0, "lserial1".getBytes(),
						Integer.parseInt(serialNo));// 流水号

				bcc.SetStringFieldByName(xpackhandle, 0, "sphone3".getBytes(),
						sphone3.getBytes());// 日期

				bcc.SetStringFieldByName(xpackhandle, 0, "saddr"
						.getBytes(), saddr.getBytes());// 随机数MAC

				bcc.SetStringFieldByName(xpackhandle, 0,
						"sstation1".getBytes(), hexcardno.getBytes());// 物理卡号

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// 卡号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(cardcnt));// 交易次数
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(cardbalance));// 卡交易前余额(分)
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol2".getBytes(),
						Integer.parseInt(String.valueOf(outcard.getCardno())));// 卡号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						Integer.parseInt(outcardcnt));// 交易次数
				bcc.SetIntFieldByName(xpackhandle, 0, "lsafe_level".getBytes(),
						Integer.parseInt(outcardbalance));// 卡交易前余额(分)

				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						(int)(Double.parseDouble(money)*100));// 转账金额(分)

				boolean bccret = false;

				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							byte[] inStr = new byte[300];
							int[] intRec = new int[1];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lserial1"
									.getBytes(), intRec);// 流水号
							String serial_no = String.valueOf(intRec[0]);

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol8"
									.getBytes(), intRec);// 余额（分）
							String card_amount = String.valueOf(intRec[0]);
							
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lsafe_level2"
									.getBytes(), intRec);// 余额（分）
							String out_card_amount = String.valueOf(intRec[0]);

							Arrays.fill(inStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sphone3"
									.getBytes(), inStr, 300);
							sphone3 = BccUtil.getStringFromByte(inStr);
							
							Arrays.fill(inStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "saddr"
									.getBytes(), inStr, 300);
							saddr = BccUtil.getStringFromByte(inStr);

							request.setAttribute("serialNo", serial_no);
							request.setAttribute("sphone3", sphone3);
							request.setAttribute("saddr", saddr);
							request.setAttribute("cardAmount",card_amount);
							request.setAttribute("outCardAmount",
									out_card_amount);

							logger.info("卡卡转账正式入账成功,物理卡号：" + hexcardno
									+ ",入账日期：" + sphone3 + "，流水号：" + serial_no
									+ ",出卡值：" + out_card_amount + "分");
							return mapping.findForward("success");
						} else {
							logger.info("卡卡转账正式入账失败,后台处理失败,物理卡号：" + hexcardno);
							errors.add(ActionMessages.GLOBAL_MESSAGE,
									new ActionError("back.error", "后台处理失败"));
							saveErrors(request, errors);
							return mapping.findForward("failure");
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							errors.add(ActionMessages.GLOBAL_MESSAGE,
									new ActionError("back.error", vs_mess));
							saveErrors(request, errors);

							logger.info("卡卡转账正式入账失败,后台处理失败,物理卡号：" + hexcardno
									+ "，返回错误信息：" + vs_mess);
							return mapping.findForward("failure");
						} else {

							errors.add(ActionMessages.GLOBAL_MESSAGE,
									new ActionError("back.error", "后台处理失败"));
							saveErrors(request, errors);
							logger.info("卡卡转账正式入账失败,后台处理失败,物理卡号：" + hexcardno
									+ "，返回错误信息：无");
							return mapping.findForward("failure");
						}

					}

				} else {
					// 请求失败

					String err_msg = BccUtil.getStringFromByte(errmsg);
					logger.info("卡卡转账正式入账失败,后台处理失败,物理卡号：" + hexcardno
							+ ",connect:errcode=" + errcode[0] + "msg="
							+ err_msg);
					errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
							"back.error", "后台通讯暂时不可用，请稍后重试！ " + err_msg));
					saveErrors(request, errors);
					return mapping.findForward("failure");
				}
			}
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "系统出现异常，请稍后重试！"));
			saveErrors(request, errors);
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "系统出现异常，请稍后重试！"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "系统出现异常，请稍后重试！"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}
}
