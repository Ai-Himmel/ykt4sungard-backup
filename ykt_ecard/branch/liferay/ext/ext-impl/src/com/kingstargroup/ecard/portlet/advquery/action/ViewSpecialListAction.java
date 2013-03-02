/**
 * 
 */
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
import com.kingstargroup.ecard.util.DateUtil;

/**
 * Æ¶À§Éú·ÖÎö
 * 
 * @author Administrator
 * 
 */
public class ViewSpecialListAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		DynaActionForm speciallistform = (DynaActionForm)form;

		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		speciallistform.set("speciallist_begindate", "".equals(speciallistform.getString("speciallist_begindate"))?bgdate:speciallistform.getString("speciallist_begindate"));
		speciallistform.set("speciallist_enddate", "".equals(speciallistform.getString("speciallist_enddate"))?eddate:speciallistform.getString("speciallist_enddate"));
		speciallistform.set("per", "".equals(speciallistform.getString("per"))?"20":speciallistform.getString("per"));
		speciallistform.set("bavgRange", "".equals(speciallistform.getString("bavgRange"))?"0":speciallistform.getString("bavgRange"));
		speciallistform.set("eavgRange", "".equals(speciallistform.getString("eavgRange"))?"0":speciallistform.getString("eavgRange"));
		speciallistform.set("perRange", "".equals(speciallistform.getString("perRange"))?"0":speciallistform.getString("perRange"));
		List detpList = AdvqueryServiceUtil.getDeptList();
		request.setAttribute("deptList", detpList);
		List specList = AdvqueryServiceUtil.getSpecialityList();
		request.setAttribute("specList", specList);
		List custtypeList = AdvqueryServiceUtil.getCusttypeList();
		request.setAttribute("custtypeList", custtypeList);
		List feetypeList = AdvqueryServiceUtil.getFeeTypeList();
		request.setAttribute("feetypeList", feetypeList);
		return mapping.findForward("portlet.advquery.speciallist.view");
	}
}
