package com.kingstargroup.fdykt.ncbanktransfer;

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
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.trade.MobileCheckAction;
import com.kingstargroup.fdykt.util.ANSIX98FormatUtil;
import com.kingstargroup.fdykt.util.BccUtil;

public class NCCheckTransferAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(MobileCheckAction.class);

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
		String dptCardCnt = request.getParameter("dptCardCnt");
		String payCardCnt = request.getParameter("payCardCnt");
		String bankcardinfo = request.getParameter("bankcardinfo");
		String bankcardno = request.getParameter("bankcardno");
		String passwd = request.getParameter("password");
		
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("dptCardCnt", dptCardCnt);
		request.setAttribute("payCardCnt", payCardCnt);
		request.setAttribute("cardBala", card_bala);
		request.setAttribute("bankcardinfo", bankcardinfo);
		

		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
			if(card==null){
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
				"logicfunc_banktrans_check", 240020);// 后台业务功能号
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
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
						Integer.parseInt(money)*100);// 交易金额
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(card_bala));// 卡余额

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(dptCardCnt));// 充值次数
				
				
				byte[] enc_pwd = ANSIX98FormatUtil.process(passwd, bankcardno);
				
				String des_pwd = Util.ZHDesEnc(enc_pwd);
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sphone3".getBytes(), des_pwd.getBytes());//银行密码加密
				
				request.setAttribute("sbank", des_pwd);
				
				String bankcardcd2="";
				if(bankcardinfo.indexOf(";")>-1 && bankcardinfo.indexOf("?")>0){
					bankcardcd2=bankcardinfo.substring(bankcardinfo.indexOf(";")+1, bankcardinfo.indexOf("?"));
				}
				
				bcc.SetStringFieldByName(xpackhandle, 0, "vsvarstr0".getBytes(), bankcardcd2.getBytes());//银行卡2、3磁道信息
				
				String bankcardcd3="";
				if(bankcardinfo.indexOf("+")>-1 && bankcardinfo.lastIndexOf("?")>0){
					bankcardcd3=bankcardinfo.substring(bankcardinfo.indexOf("+")+1, bankcardinfo.lastIndexOf("?"));
				}
				
				bcc.SetStringFieldByName(xpackhandle, 0, "vsvarstr1".getBytes(), bankcardcd3.getBytes());
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_auth".getBytes(), bankcardno.getBytes());//银行卡号
				
				
				
				
				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							byte[] byteStr = new byte[21];
							bcc.GetStringFieldByName(xpackhandle, 0,
									"stx_pwd".getBytes(), byteStr, 9);
							String radomstr = BccUtil.getStringFromByte(byteStr);//随机数

							Arrays.fill(byteStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0,
									"sname2".getBytes(), byteStr, 21);
							String refno = BccUtil.getStringFromByte(byteStr);//交易参考号
							
							String showbankcardno = "";
							if(bankcardno.length()>8){
								showbankcardno = bankcardno.substring(0, 4)+"********"+bankcardno.substring(bankcardno.length()-4, bankcardno.length());
							}
							request.setAttribute("refno", refno);// 交易参考号
							request.setAttribute("bankcardno", bankcardno);
							request.setAttribute("showbankcardno", showbankcardno);
							request.setAttribute("radomstr", radomstr);//随机数
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
