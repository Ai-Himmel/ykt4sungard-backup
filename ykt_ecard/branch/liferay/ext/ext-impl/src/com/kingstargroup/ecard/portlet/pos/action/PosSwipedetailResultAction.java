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

public class PosSwipedetailResultAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception {
		String custNo = ParamUtil.getString(request, "swipedetailCustNo");
		String custName = ParamUtil.getString(request, "swipedetailCustName");
		String departmentName = ParamUtil.getString(request, "swipedetailDepartment");
		String beginDate = ParamUtil.getString(request, "swipedetailBeginDate");
		String endDate = ParamUtil.getString(request, "swipedetailEndDate");
		String beginTime = ParamUtil.getString(request, "swipedetailBeginTime");
		String endTime = ParamUtil.getString(request, "swipedetailEndTime");
		
		List result = null;
		List departments = PosServiceUtil.getDepartments();
		try {
			result = PosServiceUtil.getPosSwipeDetail(custNo,custName,departmentName,beginDate,endDate,beginTime,endTime);
		} catch (Exception e) {
			SessionErrors.add(request,e.getClass().getName(),e);	
			//e.printStackTrace();
		}
		request.setAttribute("departments", departments);
		request.setAttribute("swipedetailList", result);
		
		return mapping.findForward("portlet.pos.swipedetail.view");
	}
}
