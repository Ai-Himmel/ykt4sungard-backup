package com.kingstargroup.conference.action.sign;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.ajaxanywhere.AAUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.GetDictionary;

/**
 * ÎÞ¿¨Ç©µ½
 * 
 * @author hlq
 * 
 */
public class ReplaceByHandQueryBAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm from,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		int confid = ParamUtil.getInteger(request, "confidB");
		String custno = ParamUtil.getString(request, "custnoB");
		String custname = ParamUtil.getString(request, "custnameB");
		String deptcode = ParamUtil.getString(request, "deptcodeB");
		String duty = ParamUtil.getString(request, "dutyB");
		String username = GetterUtil.get((String) request.getSession()
				.getAttribute("username"), "");		
		List confList = GetDictionary.getConfList(username);
		List deptList = GetDictionary.getDeptList();
		request.setAttribute("confList", confList);
		request.setAttribute("deptList", deptList);
		request.setAttribute("resultB", AttendeeUtil.getCustListMaphandB(
				confid, custno, custname, duty, deptcode));
		if (AAUtils.isAjaxRequest(request)) {
			AAUtils.addZonesToRefresh(request, "blist");
		}
		return mapping.findForward("success");
	}
}
