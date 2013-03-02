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

public class PosReportResultAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception {
		String deviceId = ParamUtil.getString(request, "reportDeviceId");
		String deviceName = ParamUtil.getString(request, "reportDeviceName");
		String beginDate = ParamUtil.getString(request, "reportBeginDate");
		String endDate = ParamUtil.getString(request, "reportEndDate");
		String beginTime = ParamUtil.getString(request, "reportBeginTime");
		String endTime = ParamUtil.getString(request, "reportEndTime");
		
		List result = null;
		try {
			result = PosServiceUtil.getPostReport(deviceId,deviceName,beginDate,endDate,beginTime,endTime);
		} catch (Exception e) {
			SessionErrors.add(request,e.getClass().getName(),e);	
			//e.printStackTrace();
		}
		request.setAttribute("reportList", result);
		
		return mapping.findForward("portlet.pos.report.view");
	}
}
