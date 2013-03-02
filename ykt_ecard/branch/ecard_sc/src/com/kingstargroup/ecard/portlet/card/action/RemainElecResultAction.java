package com.kingstargroup.ecard.portlet.card.action;


import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.ecard.BccctlInit;
import com.kingstargroup.ecard.KSConfiguration;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;


public class RemainElecResultAction extends  PortletAction {

	/** 
	 * Logger for this class 
	 */
	private static final Logger logger = Logger
			.getLogger(RemainElecResultAction.class);
 
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
	    HttpSession session = request.getSession(true);
		String stuempno = session.getAttribute(WebKeys.USER_ID).toString();
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
				"elecquery", 847323);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			logger.info("-------mainfunction--------"+mainfunction);
			logger.info("-------func--------"+func);
			
			bcc = BccctlInit.getBccctlInstance();
			
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						Integer.parseInt("240203"));// 请求号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						stuempno.getBytes());// 客户id
				
				bcc.SetIntFieldByName(xpackhandle, 0, "saddr".getBytes(),
						Integer.parseInt(room));// 房间号
				
				
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				logger.info("-------bccret--------"+bccret);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							double[] remainElec = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
									.getBytes(), remainElec);
						
							//logger.info("-------remainElec--------"+String.valueOf(remainElec[0]));
							
							request.setAttribute("remainElec",String.valueOf(remainElec[0]));
							//logger.info("-------success--------");
							return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
						} else {
						//	logger.info("-------后台处理失败--------"+RetCode[0]);
							request.setAttribute("errmsg", "后台处理失败"+RetCode[0]);
							return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {
							request.setAttribute("errmsg", "后台处理失败"+RetCode[0]);
							return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
						} else {
							request.setAttribute("errmsg", "后台处理失败"+RetCode[0]);
							return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
						}
					}

				} else {
					// 请求失败
					request.setAttribute("errmsg", "后台通讯暂时不可用，请稍后重试！ " );
					return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
				}
			}

			request.setAttribute("errmsg", "没有找到cpackfile");
			return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");

		} catch ( UnsatisfiedLinkError  e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！UnsatisfiedLinkError");
			return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
		} catch (Exception e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统初始化异常，请稍后重试！Exception");
			return mapping.findForward("portlet.ecardtransaction.elecquerydetail_max");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}


		

