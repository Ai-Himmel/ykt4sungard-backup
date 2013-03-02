package com.kingstargroup.ecard.portlet.maintain.action;
      
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext; 

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.MaintainUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.ParamUtil;

public class ViewMaintainAction extends PortletAction{

	public ActionForward execute(    
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			/*int page = ParamUtil.get(req, "page", 0);
			String userId = (String)req.getSession().getAttribute(WebKeys.USER_ID);
			req.setAttribute("result", MaintainUtil.list(userId,page, EcardConstants.LIST_MORE_SIZE));*/
			return mapping.findForward("portlet.maintain.view");		
		} catch (Exception pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}
}



