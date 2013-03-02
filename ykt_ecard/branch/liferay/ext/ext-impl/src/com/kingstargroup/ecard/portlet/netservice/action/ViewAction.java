/**
 * 
 */
package com.kingstargroup.ecard.portlet.netservice.action;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.util.SimpleEncoding;
import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. File name:ViewAction.java
 * Description: Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述 创建
 * 2009-8-25 何林青
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class ViewAction extends PortletAction {
	public ActionForward render(ActionMapping mapping, ActionForm form,
			PortletConfig config, RenderRequest req, RenderResponse res)
			throws Exception {
		User user = null;
		user = PortalUtil.getSelectedUser(req);
		String stuempno = user.getScreenName();
		stuempno = SimpleEncoding.encode(stuempno.getBytes(), "kingstar".getBytes()).toString();
		req.setAttribute("stuempno", stuempno);
		return mapping.findForward("extportlet.netservice.view");

	}

}
