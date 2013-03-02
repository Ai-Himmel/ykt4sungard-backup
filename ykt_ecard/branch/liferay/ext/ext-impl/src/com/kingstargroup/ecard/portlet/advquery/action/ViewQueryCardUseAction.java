package com.kingstargroup.ecard.portlet.advquery.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.util.DateUtil;
import com.liferay.portal.struts.PortletAction;

public class ViewQueryCardUseAction extends PortletAction {
	
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		DynaActionForm  carduseform =(DynaActionForm)form;
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		carduseform.set("carduse_enddate", "".equals(carduseform.getString("carduse_enddate"))?eddate:carduseform.getString("carduse_enddate"));
	    return mapping.findForward("portlet.advquery.carduse.view");
	}
}
