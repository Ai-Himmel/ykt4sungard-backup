package com.kingstargroup.ecard.portlet.maintain.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.hibernate.util.MaintainUtil;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.ParamUtil;

public class AdminQryResultAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		try{
	    String  status =   req.getParameter("status");
		String  type  = req.getParameter("type");
		String  userId = (String)req.getSession().getAttribute(WebKeys.USER_ID);
		String  appBeginDate = req.getParameter("appBeginDate");
		String  appEndDate = req.getParameter("appEndDate");
		String  asrBeginDate = req.getParameter("asrBeginDate");
		String  asrEndDate = req.getParameter("asrEndDate");
		int page = req.getParameter("page")==null?0:Integer.parseInt(req.getParameter("page"));
		
		ResultPage curpage = 
		     MaintainUtil.adminQry(userId,status,type,appBeginDate,appEndDate,asrBeginDate,asrEndDate,page, EcardConstants.LIST_MORE_SIZE);
		
		req.setAttribute("status", status);
		req.setAttribute("type", type);
		req.setAttribute("curpage", curpage);
		req.setAttribute("page", new Integer(page));
		req.setAttribute("appBeginDate", appBeginDate);
		req.setAttribute("appEndDate", appEndDate);
		req.setAttribute("asrBeginDate", asrBeginDate);
		req.setAttribute("asrEndDate", asrEndDate);
		
		return mapping.findForward("portlet.maintain.admin");
		}catch (Exception pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	
	}

	

}
