package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;

public class ViewCardUseByDeptAction  extends Action{
	

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res) 
		throws Exception {		
		 
		DynaActionForm  cardusebydeptform = (DynaActionForm)form;
		
		cardusebydeptform.set("deptcode", "".equals(cardusebydeptform.getString("deptcode"))?"line":cardusebydeptform.getString("deptcode"));
		List deptList = AdvqueryServiceUtil.getDeptList();
		req.setAttribute("deptList", deptList);
		return mapping.findForward("portlet.advquery.cardusebydept.view");
	}

}
