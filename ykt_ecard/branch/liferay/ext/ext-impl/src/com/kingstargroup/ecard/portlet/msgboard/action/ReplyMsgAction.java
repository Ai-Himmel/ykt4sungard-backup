/**
 * 
 */
package com.kingstargroup.ecard.portlet.msgboard.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.msgboard.service.MsgBoardServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ReplyMsgAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-10-11  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ReplyMsgAction extends PortletAction {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			if (isTokenValid(req)) {
				
				int id = ParamUtil.getInteger(req, "id");
				String content = ParamUtil.getString(req, "replyContent");
				String replyer = GetterUtil.get((String)req.getSession().getAttribute("j_username"), StringPool.BLANK);
				MsgBoardServiceUtil.replyMsg(id, content, replyer);
				resetToken(req);
			}
			SessionErrors.add(req, EcardConstants.REPLY_MSG_SUCCESS);
			return mapping.findForward("portlet.ecardmsgboard.view");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}		
	}

}
