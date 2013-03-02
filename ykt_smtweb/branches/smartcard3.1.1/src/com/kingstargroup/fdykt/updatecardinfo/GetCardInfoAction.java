package com.kingstargroup.fdykt.updatecardinfo;

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
import com.kingstargroup.fdykt.dto.UpdateInfoDTO;

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

public class GetCardInfoAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(GetCardInfoAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		ActionForward forward = mapping.findForward("logon");
		if (session.getAttribute("cardno") == null){
			session.setAttribute("REQ_URL", request.getRequestURL());
			return forward;
		}
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
		HttpSession session = request.getSession();
		String CardPhyId = session.getAttribute("cardphyid").toString(); // 物理卡号
		DB2AccountDAO accdao = new DB2AccountDAO();
		ActionErrors errors = new ActionErrors();

		int deviceid = -2;
		try {
			String reqip = request.getRemoteAddr();
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

		
		//
		UpdateInfoDTO updateinfo = null;
		try {
			DB2AccountDAO accountdao = new DB2AccountDAO();
			updateinfo = accountdao.getUpdateInfoByCardphyid(CardPhyId);
			if (updateinfo == null) {
				return (mapping.findForward("isnull"));
			}
		} catch (Exception e) {
			logger.error("查询客户信息失败");
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error","查询客户信息失败"));
			saveErrors(request, errors);
			return (mapping.findForward("failure"));
		}
		
		request.setAttribute("CardPhyId", CardPhyId);
		request.setAttribute("UpdateInfoDTO", updateinfo);
		return (mapping.findForward("success"));

	}
}
