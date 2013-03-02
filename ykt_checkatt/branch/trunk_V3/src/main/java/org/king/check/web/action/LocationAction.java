package org.king.check.web.action;

import java.io.PrintWriter;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.domain.TCheckDeviceLocation;
import org.king.check.domain.TCheckDeviceLocationId;
import org.king.check.domain.TCheckLocation;
import org.king.check.service.CheckInfoService;
import org.king.framework.web.action.BaseAction;

public class LocationAction extends BaseAction {
	private static final Log log = LogFactory.getLog(LocationAction.class);
	
	private CheckInfoService checkInfoService;

	public void setCheckInfoService(CheckInfoService checkInfoService) {
		this.checkInfoService = checkInfoService;
	}
	
	public ActionForward listLocation(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		List locations = checkInfoService.findAllLocation();
		request.setAttribute("locations", locations);
		return mapping.findForward("locationList");
	}
	
	public ActionForward viewLocation(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		String locationId = request.getParameter("locationId");
		TCheckLocation checkLocation;
		if (StringUtils.isNotBlank(locationId)) {
			checkLocation = checkInfoService.getCheckLocation(locationId);
			List deviceLocations = checkInfoService.findCheckDeviceLocation(locationId);
			request.setAttribute("deviceLocations", deviceLocations);
		} else {
			checkLocation = new TCheckLocation();
		}
		((DynaActionForm) form).set("checkLocation", checkLocation);
		return mapping.findForward("viewLocation");
	}
	
	public ActionForward saveLocation(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		TCheckLocation checkLocation = (TCheckLocation) ((DynaActionForm) form).get("checkLocation");
		if(StringUtils.isNotBlank(checkLocation.getId())){
			checkInfoService.updateCheckLocation(checkLocation);
		} else {
			checkInfoService.saveCheckLocation(checkLocation);
		}
		return mapping.findForward("list");
	}
	
	public ActionForward deleteLocation(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		String[] locationIds = request.getParameterValues("itemlist");
		checkInfoService.deleteCheckLocations(locationIds);
		return mapping.findForward("list");
	}
	
	public ActionForward selectDevice(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		String locationId = request.getParameter("locationId");
		List deviceList = checkInfoService.findDevice();
		request.setAttribute("deviceList", deviceList);
		request.setAttribute("locationId", locationId);
		return mapping.findForward("selectDevice");
	}
	
	public ActionForward saveDeviceLocation(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		response.setCharacterEncoding("UTF-8");
		PrintWriter writer = response.getWriter();
		
		String deviceId = request.getParameter("deviceId");
		String deviceType = request.getParameter("deviceType");
		String locationId = request.getParameter("locationId");
		String message = "";
		try {
			TCheckDeviceLocation checkDeviceLocation = new TCheckDeviceLocation();
			TCheckDeviceLocationId checkDeviceLocationId = new TCheckDeviceLocationId();
			checkDeviceLocationId.setDeviceId(Integer.valueOf(deviceId));
			checkDeviceLocationId.setLocationId(locationId);
			checkDeviceLocation.setCheckType(deviceType);
			checkDeviceLocation.setId(checkDeviceLocationId);
			checkInfoService.saveCheckDeviceLocation(checkDeviceLocation);
		} catch (Exception e) {
			message = "保存设备失败："+e.getMessage();
			log.error(message);
		}
		writer.write(message);
		return null;
	}
	
	public ActionForward deleteDeviceLocation(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		response.setCharacterEncoding("UTF-8");
		PrintWriter writer = response.getWriter();
		String deviceId = request.getParameter("deviceId");
		String message = "";
		try {
			checkInfoService.deleteCheckDeviceLocation(deviceId);
		} catch (Exception e) {
			message = "删除设备失败："+e.getMessage();
			log.error(message);
		}
		writer.write(message);
		return null;
	}
}
