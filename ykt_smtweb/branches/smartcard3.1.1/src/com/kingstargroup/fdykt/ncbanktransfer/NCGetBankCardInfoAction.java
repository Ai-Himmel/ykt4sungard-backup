package com.kingstargroup.fdykt.ncbanktransfer;

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
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.ANSIX98FormatUtil;
import com.kingstargroup.fdykt.util.BccUtil;

public class NCGetBankCardInfoAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(NCGetBankCardInfoAction.class);

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
		

		DB2AccountDAO accdao = new DB2AccountDAO();
		String bankcardinfo = request.getParameter("bankcardinfo");
		String bankcardno = request.getParameter("bankcardno");
		String passwd = request.getParameter("password");
		

		System.out.println("bankcardinfo="+bankcardinfo);
		
		System.out.println("bankcardno="+bankcardno);
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
				"logicfunc_bankcard_info", 240024);// 后台业务功能号
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
				
				
				byte[] enc_pwd = ANSIX98FormatUtil.process(passwd, bankcardno);
				
				String des_pwd = Util.ZHDesEnc(enc_pwd);
				
				System.out.println("*************************");
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sphone3".getBytes(), des_pwd.getBytes());//银行密码加密
				
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

							double[] bankmoney = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
									.getBytes(), bankmoney);
							String cardmoney = String.valueOf(bankmoney[0]);//卡余额
							request.setAttribute("bankcardno", bankcardno);
							request.setAttribute("cardmoney", cardmoney);
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
