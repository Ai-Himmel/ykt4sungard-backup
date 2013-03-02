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
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AddMsgAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-11  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AddMsgAction extends PortletAction {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			if (isTokenValid(req)) {
				
				String title = ParamUtil.getString(req, "title");
				String content = ParamUtil.getString(req, "content");
				String creater = GetterUtil.get((String)req.getSession().getAttribute("j_username"), StringPool.BLANK);
//				String creater = GetterUtil.get((String)req.getSession().getAttribute(WebKeys.USER_ID), StringPool.BLANK);
				MsgBoardServiceUtil.addMsg(title, content, creater);
				resetToken(req);
			}
			return mapping.findForward("portlet.ecardmsgboard.view");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}		
	}

}
