package com.kingstargroup.action.view;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.actions.DispatchAction;

import com.kingstargroup.business.util.DeviceStatusUtil;
import com.kingstargroup.business.util.ParaUtil;
import com.kingstargroup.form.MapParamTable;

public class DeviceStatusAction extends DispatchAction{
	
	 public   ActionForward    queryDeviceStatus(ActionMapping mapping, ActionForm form,
			    HttpServletRequest request, HttpServletResponse response)
	    throws Exception {
		    List result = new ArrayList();
		    String devstatus = request.getParameter("devstatus");
		    MapParamTable param = ParaUtil.getPara("TimeInterval"); 
		    double  timeInterval =param.getValue();
		    result = DeviceStatusUtil.getDeviceStatus(devstatus,String.valueOf(timeInterval));
		    request.setAttribute("result", result);
		    return mapping.findForward("deviceStatusList");
	 }
	 
	 public ActionForward  editDeviceStatus(ActionMapping mapping, ActionForm form,
			    HttpServletRequest request, HttpServletResponse response)
	    throws Exception {
		 
		 String status = request.getParameter("status");
		 String id = request.getParameter("id");
		 Map result = new HashMap();
		 if("1".equals(status)){//新增
			result = DeviceStatusUtil.getDeviceById(id);
			request.setAttribute("result", result);
		 }
		 return mapping.findForward("editDeviceStatus");
	 }
	 
	 public ActionForward  updateDeviceStatus(ActionMapping mapping, ActionForm form,
			    HttpServletRequest request, HttpServletResponse response)
	    throws Exception {
		 String  receive = request.getParameter("receive");
		 String  id = request.getParameter("id");
		 String deviceid = request.getParameter("deviceid");
		 if("1".equals(receive)){//接受
			 DeviceStatusUtil.updateDeviceStatus(id, 2);
			 
		 }else if("0".equals(receive)){//忽略
			 String canceltime = request.getParameter("canceltime");
			 String cancelreason = request.getParameter("cancelreason");
			 DeviceStatusUtil.updateDevice(canceltime, cancelreason,Long.parseLong(deviceid));	 
		 }
		 
		 return  mapping.findForward("deviceStatusList");
	 }
	 
}
