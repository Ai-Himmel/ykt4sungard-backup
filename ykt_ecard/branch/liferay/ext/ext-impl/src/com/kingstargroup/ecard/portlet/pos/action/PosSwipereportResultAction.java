package com.kingstargroup.ecard.portlet.pos.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.portlet.pos.service.PosServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

public class PosSwipereportResultAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception {
		String type = ParamUtil.getString(request, "swipereportType");
		String custNo = ParamUtil.getString(request, "swipereportCustNo");
		String custName = ParamUtil.getString(request, "swipereportCustName");
		String departmentName = ParamUtil.getString(request, "swipereportDepartment");
		String beginDate = ParamUtil.getString(request, "swipereportBeginMonth");
		String endDate = ParamUtil.getString(request, "swipereportEndMonth");
		
		List result = null;
		List departments = PosServiceUtil.getDepartments();
		try {
			result = PosServiceUtil.getPosSwipeReport(type,custNo,custName,departmentName,beginDate,endDate);
		} catch (Exception e) {
			SessionErrors.add(request,e.getClass().getName(),e);
			//e.printStackTrace();
		}
		request.setAttribute("departments", departments);
		request.setAttribute("swipereportList", result);
		
		return mapping.findForward("portlet.pos.swipereport.view");
	}
}
