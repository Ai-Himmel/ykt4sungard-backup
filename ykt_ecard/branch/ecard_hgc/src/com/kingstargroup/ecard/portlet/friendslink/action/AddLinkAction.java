package com.kingstargroup.ecard.portlet.friendslink.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.FriendsLinkUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringPool;
import com.liferay.util.servlet.SessionErrors;

public class AddLinkAction extends PortletAction {
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			String linkname = req.getParameter("linkname");
			String linkurl = req.getParameter("linkurl");
			String cmd = req.getParameter("cmd");		
			String creater = GetterUtil.get((String)req.getSession().getAttribute(WebKeys.USER_ID), StringPool.BLANK);
			
			if (isTokenValid(req)) {
				FriendsLinkUtil.add(linkname, linkurl,  creater);
				resetToken(req);
			}
			//如果操作类型为保存并添加下一个，就需要清除对应的Form对象
			if (cmd.equals("saveandnext")) {
				if (mapping.getAttribute() != null) {
					if ("request".equals(mapping.getScope())) {					
						req.removeAttribute(mapping.getAttribute());					
					} else {
						req.getSession().removeAttribute(mapping.getAttribute());
					}
				}
				saveToken(req);
				SessionErrors.add(req, EcardConstants.ADD_INFO_SUCCEED);				
				return mapping.findForward("portlet.ecardlink.add");
			}
			return mapping.findForward("portlet.ecardlink.admin");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}


}
