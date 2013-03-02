package com.kingstargroup.fdykt.trade;

import java.net.InetAddress;
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

/**
 * <p>
 * Title:Test
 * </p>
 * <p>
 * Description:
 * </p>
 * <p>
 * Copyright: Copyright (c) 2004
 * </p>
 * <p>
 * Company: kingstargroup
 * </p>
 * 
 * @author
 * @version 1.0
 */

public class ConsumerLimitAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ConsumerLimitAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		ActionForward forward = mapping.findForward("logon");
		if (session.getAttribute("cardno") == null)
			return forward;
		KSDaoSessionFactory.createSession();
		forward = doGetConsumerLimit(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doGetConsumerLimit(ActionMapping mapping,
			HttpServletRequest request) {
		String CardPhyId = request.getParameter("CardPhyId"); // 物理卡号
		String maxpercount = request.getParameter("maxpercount");
		String maxperday = request.getParameter("maxperday");
		DB2AccountDAO accdao = new DB2AccountDAO();
		ActionErrors errors = new ActionErrors();

		int deviceid = -2;
		try {
			String reqip = request.getRemoteAddr();
			System.out.print("ip请求"+reqip);
//			InetAddress addr = InetAddress.getLocalHost();
//			String reqip = addr.getHostAddress();// 获得本机IP
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

		request.setAttribute("CardPhyId", CardPhyId);
		request.setAttribute("maxpercount", maxpercount);
		request.setAttribute("maxperday", maxperday);
		return (mapping.findForward("success"));

	}
}
