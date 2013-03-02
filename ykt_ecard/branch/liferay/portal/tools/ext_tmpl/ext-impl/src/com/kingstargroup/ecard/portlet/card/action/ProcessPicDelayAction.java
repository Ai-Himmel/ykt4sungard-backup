/**
 * 
 */
package com.kingstargroup.ecard.portlet.card.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.PicDelayUtil;
import com.kingstargroup.ecard.portlet.card.service.PicDelayServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PicDelayUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-28  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ProcessPicDelayAction extends PortletAction {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {						
			String redirectURL = com.liferay.portal.kernel.util.ParamUtil.getString(req, "redirecturl");
			if (isTokenValid(req)) {				
				
				PicDelayServiceUtil.updateDelays();
				resetToken(req);
			}
			res.sendRedirect(redirectURL);
			//ServletResponseUtil.sendFile(res, format.format(new Date()) + ".txt", bytes);			
			return mapping.findForward(ActionConstants.COMMON_NULL);
		} catch (PortalException pe) {			
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

}
