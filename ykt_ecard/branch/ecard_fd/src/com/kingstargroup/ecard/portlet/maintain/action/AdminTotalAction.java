package com.kingstargroup.ecard.portlet.maintain.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.MaintainUtil;
import com.kingstargroup.ecard.util.DateFormatUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;

public class AdminTotalAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {

	 try{
		 String beginDate = req.getParameter("beginDate");
		 String endDate = req.getParameter("endDate");
		 if(endDate ==null || "".equals(endDate)){
			 endDate = DateFormatUtil.getNowDate();
		 }
		 List result = MaintainUtil.adminTotal(beginDate, endDate);
		 req.setAttribute("beginDate", beginDate);
		 req.setAttribute("endDate", endDate);
		 req.setAttribute("result", result);
		 return mapping.findForward("portlet.maintain.total");
	 }catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}
