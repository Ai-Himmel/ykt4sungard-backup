/**
 * 
 */
package com.kingstargroup.ecard.portlet.lostfound.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.liferay.portal.struts.PortletAction;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: RenderAddLostFoundAction<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-10-27 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class RenderAddLostFoundAction extends PortletAction {
	/*
	 * (non-Javadoc)
	 * 
	 * @seeorg.apache.struts.action.Action#execute(org.apache.struts.action.
	 * ActionMapping, org.apache.struts.action.ActionForm,
	 * javax.servlet.http.HttpServletRequest,
	 * javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form, HttpServletRequest req, HttpServletResponse res) throws Exception {
		saveToken(req);
		System.out.println(req.getSession().getAttribute(Globals.TRANSACTION_TOKEN_KEY));
		return mapping.findForward("portlet.lostfound.add");
	}
}
