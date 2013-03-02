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

public class PosDetailResultAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest req, HttpServletResponse res) throws Exception {
		String deviceId = ParamUtil.getString(req, "detailDeviceId");
		String deviceName = ParamUtil.getString(req, "detailDeviceName");
		String beginDate = ParamUtil.getString(req, "detailBeginDate");
		String endDate = ParamUtil.getString(req, "detailEndDate");
		String beginTime = ParamUtil.getString(req, "detailBeginTime");
		String endTime = ParamUtil.getString(req, "detailEndTime");
		
		List result = null;
		try {
			result = PosServiceUtil.getPosDetail(deviceId,deviceName,beginDate,endDate,beginTime,endTime);
		} catch (Exception e) {
			SessionErrors.add(req,e.getClass().getName(),e);
			//e.printStackTrace();
		}
		req.setAttribute("detailList", result);
		
		return mapping.findForward("portlet.pos.detail.view");
	}
}
