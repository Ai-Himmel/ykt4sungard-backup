package com.kingstargroup.fdykt.netcomputebindopenacc;

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
import com.kingstargroup.fdykt.dto.AccountDTO;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BccUtil;

public class NetComputeCheckAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(NetComputeCheckAction.class);

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
		String card_bala = request.getParameter("cardBala");
		String txCnt = request.getParameter("txCnt");
//		String room = request.getParameter("room");
		
		String ipServer = KSConfiguration.getInstance().getProperty("drtpip1",
		"172.0.0.1");
		String drtpPort = KSConfiguration.getInstance().getProperty(
				"drtpport1", "4000");
		String svrFunc = KSConfiguration.getInstance().getProperty(
				"mainfunction1", "6000");

//		request.setAttribute("room", room);
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("txCnt", txCnt);
		request.setAttribute("ipServer", ipServer);
		request.setAttribute("drtpPort", drtpPort);
		request.setAttribute("svrFunc", svrFunc);
		
		String stuempno = "";
		CardDTO card = new CardDTO();
		AccountDTO acc = new AccountDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
			if(card==null){
				request.setAttribute("errmsg", "卡信息异常，请检查是否正常卡!");
				return mapping.findForward("failure");
			}
			acc = accdao.getAccountInfoByCardno(String.valueOf(card.getCardno()));
			if(acc.getStuempno()==null){
				request.setAttribute("errmsg", "学工号信息有误，暂时不能使用此功能!");
				return mapping.findForward("failure");
			}
			stuempno=acc.getStuempno();
		} catch (Exception e) {
			// TODO: handle exception
			request.setAttribute("errmsg", "账户信息读取失败!");
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
				"logicfunc_thirdpay", 850005);// 后台业务功能号
		String net_computer_pay_code = KSConfiguration.getInstance().getProperty("net_computer_pay_code", "4201");//支付代码
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
						.getBytes(), 1);// 交易标志
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// 卡号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(txCnt));// 交易次数
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(card_bala));// 卡交易前余额(分)
				bcc.SetStringFieldByName(xpackhandle, 0,
						"sstation1".getBytes(), cardphyid.getBytes());// 物理卡号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(money)*100);// 转账金额(分)		
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sbank_acc".getBytes(),
						stuempno.getBytes());// 对方账号				
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						Integer.parseInt(net_computer_pay_code));// 支付代码
				
				bcc.SetStringFieldByName(xpackhandle, 0, "vsvarstr0".getBytes(),
						"1003".getBytes());// 开户请求标识		
				


			boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							
							byte[] inStr = new byte[300];
							int[] intRec = new int[1];
							Arrays.fill(inStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sphone3"
									.getBytes(), inStr, 300);
							String sphone3 = BccUtil.getStringFromByte(inStr);
							
							Arrays.fill(inStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "saddr"
									.getBytes(), inStr, 300);
							String saddr = BccUtil.getStringFromByte(inStr);
							
							Arrays.fill(inStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate3"
									.getBytes(), inStr, 300);
							String sdate3 = BccUtil.getStringFromByte(inStr);
							
							Arrays.fill(inStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "stime3"
									.getBytes(), inStr, 300);
							String stime3 = BccUtil.getStringFromByte(inStr);
							
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol8"
									.getBytes(), intRec);// 余额（分）
							String out_card_amount = String.valueOf(intRec[0]);
							
							request.setAttribute("stuempno", stuempno);
							request.setAttribute("sphone3", sphone3);
							request.setAttribute("saddr", saddr);
							request.setAttribute("sdate3", sdate3);
							request.setAttribute("stime3", stime3);
							request.setAttribute("outCardAmount",out_card_amount);
						
							return mapping.findForward("success");
						} else {
							request.setAttribute("errmsg", "后台处理失败");
							return mapping.findForward("failure");
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							Arrays.fill(vsmess, (byte) 0);
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
