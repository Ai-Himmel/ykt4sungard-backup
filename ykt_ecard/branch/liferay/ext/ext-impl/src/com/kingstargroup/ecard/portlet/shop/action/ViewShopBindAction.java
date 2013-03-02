package com.kingstargroup.ecard.portlet.shop.action;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ViewRuleAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-21  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ViewShopBindAction extends PortletAction {
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		User user = null;
		user = PortalUtil.getSelectedUser(req);
		long userid = user.getUserId();
		
		req.setAttribute("userid", String.valueOf(userid));
		req.setAttribute("storeLimitString", ShopServiceUtil.getStoreLimitString(userid));
		
		return mapping.findForward("portlet.shop_admin.edit");
	
	}
}
