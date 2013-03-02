package com.kingstargroup.ecard.portlet.card.action;


import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.log4j.Logger;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import com.kingstar.bcc.bccclt;
import com.kingstargroup.ecard.BccctlInit;
import com.kingstargroup.ecard.KSConfiguration;
import com.liferay.portal.struts.PortletAction;


public class RemainElecResultAction extends  PortletAction {

	/** 
	 * Logger for this class 
	 */
	private static final Logger logger = Logger
			.getLogger(RemainElecResultAction.class);
 
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String room = request.getParameter("room");

		request.setAttribute("room", room);

		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_elect_check", 847319);// 后台业务功能号
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
						Integer.parseInt("240204"));// 请求号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol10".getBytes(),
						Integer.parseInt(room));// 房间号
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						"ecard".getBytes());// 操作员

				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							
							
							double[] remainElec = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt1"
									.getBytes(), remainElec);
							
							double[] OutCardAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
									.getBytes(), OutCardAmount);
							int[] SerialNo = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol0"
									.getBytes(), SerialNo);
							
							double[] ElecPrice = new double[1];//电价(分)
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt2"
									.getBytes(), ElecPrice);
							
							byte[] sbankname = new byte[81];
							bcc.GetStringFieldByName(xpackhandle, 0,
									"sbankname".getBytes(), sbankname, 81);

							
							String serial_no = String.valueOf(SerialNo[0]);

						
							String elect_price = String.valueOf(ElecPrice[0]);
							int i = 0;
							for (i = 0; i < sbankname.length; i++) {
								if (0 == sbankname[i]) {
									break;
								}
							}

							String sbankname_s = new String(sbankname, 0, i);
							request.setAttribute("serialNo", serial_no);
						
							request.setAttribute("ElecPrice", elect_price);
							request.setAttribute("sbankname", sbankname_s);
							request.setAttribute("remainElec",String.valueOf(remainElec[0]));
							return mapping.findForward("portlet.ecardtransaction.querydetail_result");
						} else {
							request.setAttribute("errmsg", "后台处理失败");
							return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
						}

					} else {
						
						logger.error("后台返回错误码RetCode[0]="+RetCode[0]);
						// 失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							int i;
							for (i = 0; i < vsmess.length; i++) {
								if (vsmess[i] == 0) {
									break;
								}
							}
							String vs_mess = new String(vsmess, 0, i);
							request.setAttribute("errmsg", vs_mess);
							return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
						} else {
							request.setAttribute("errmsg", "后台处理失败,错误码"+RetCode[0]);
							return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
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
					
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					request.setAttribute("errmsg", "后台通讯暂时不可用，请稍后重试！ " + RetCode[0]);
					return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
				}
			}

			request.setAttribute("errmsg", "系统出现异常，请稍后重试!"+RetCode[0]);
			return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！"+RetCode[0]);
			return mapping.getInputForward();
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统初始化异常，请稍后重试！"+RetCode[0]);
			return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}


		

