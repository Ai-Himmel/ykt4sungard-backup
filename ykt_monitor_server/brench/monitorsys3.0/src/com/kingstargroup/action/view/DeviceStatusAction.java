package com.kingstargroup.action.view;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.actions.DispatchAction;

import com.kingstargroup.business.util.DeviceStatusUtil;
import com.kingstargroup.business.util.ParaUtil;
import com.kingstargroup.form.DeviceStatusResult;
import com.kingstargroup.form.Deviceservice;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.utils.DateUtil;

public class DeviceStatusAction extends DispatchAction{
	
	 public ActionForward queryDeviceStatus(ActionMapping mapping, ActionForm form,
			    HttpServletRequest request, HttpServletResponse response)
	    throws Exception {
		    List result = new ArrayList();
		    HttpSession session= request.getSession();
			 if(session.getAttribute("loginUserName")==null){
				return mapping.findForward("gindex");
			 }
		    DynaActionForm tfrom = (DynaActionForm)form;
		    String devstatus = tfrom.getString("devstatus");
		    String devicename = tfrom.getString("devicename");
		    String errreason =  tfrom.getString("errreason");
		    MapParamTable param = ParaUtil.getPara("HeartLostTime"); 
		    double  timeInterval =param.getValue();
		    result = DeviceStatusUtil.getDeviceStatus(devicename,errreason,devstatus,String.valueOf(timeInterval*60));
		    request.setAttribute("result", result);
		    List list  = DeviceStatusUtil.stateDictList();
			request.setAttribute("stateDict", list);
		    return mapping.findForward("deviceStatusList");
	 }
	 
	 public ActionForward  editDeviceStatus(ActionMapping mapping, ActionForm form,
			    HttpServletRequest request, HttpServletResponse response)
	    throws Exception {
		 DynaActionForm tfrom = (DynaActionForm)form;
		 HttpSession session= request.getSession();
		 if(session.getAttribute("loginUserName")==null){
			return mapping.findForward("gindex");
		 }
		 String status = request.getParameter("status");
		 String id = request.getParameter("id");
		 DeviceStatusResult result = null;
		 List serviceList = null;
		 if("1".equals(status)){//新增
			tfrom.set("receive", "2");
			result = DeviceStatusUtil.getDeviceById(id);
			request.setAttribute("result", result);
			return mapping.findForward("editservice_newadd");
		 }else  if("2".equals(status)){//维修中
			 tfrom.set("receive", "3");
			serviceList =  DeviceStatusUtil.getServiceList(id);
			request.setAttribute("serviceList", serviceList);
			result = DeviceStatusUtil.getDeviceById(id);
			request.setAttribute("result", result);
			return mapping.findForward("editservice_service");
		 }else{
			serviceList =  DeviceStatusUtil.getServiceList(id);
			request.setAttribute("serviceList", serviceList);
			result = DeviceStatusUtil.getDeviceById(id);
			request.setAttribute("result", result);
			return mapping.findForward("editservice_status");
		 }
		 
	 }
	 
	 public ActionForward  updateDeviceStatus(ActionMapping mapping, ActionForm form,
			    HttpServletRequest request, HttpServletResponse response)
	    throws Exception {
		 DynaActionForm tfrom = (DynaActionForm)form;
		 HttpSession session= request.getSession();
		 if(session.getAttribute("loginUserName")==null){
			return mapping.findForward("gindex");
		 }
		 String loginUserName = (String)session.getAttribute("loginUserName");
		 String  receive = tfrom.getString("receive");
		 String  id = request.getParameter("id");
		 String deviceid = request.getParameter("deviceid");
		 String dealmark = tfrom.getString("dealmark");
		 if("2".equals(receive)){//接受
			 DeviceStatusUtil.updateDeviceStatus(id, Long.parseLong(receive),"");
			 Deviceservice deviceservice = new Deviceservice();
			 deviceservice.setDevicestatusid(id);
			 deviceservice.setRcvman(loginUserName);
			 deviceservice.setRcvtime(DateUtil.getNow());
			 deviceservice.setDealstatus(1);
			 deviceservice.setDealmark(dealmark);
			 DeviceStatusUtil.saveDeviceService(deviceservice);
		 }else if("5".equals(receive)){//忽略
			 DeviceStatusUtil.updateDeviceStatus(id,  Long.parseLong(receive),"");
			 String canceltime = tfrom.getString("canceltime");
			 String cancelreason = tfrom.getString("cancelreason");
			 DeviceStatusUtil.saveDeviceFilter(loginUserName,canceltime, cancelreason,Long.parseLong(deviceid));	 
		 }else if("3".equals(receive)){//已修复
			 DeviceStatusUtil.updateDeviceStatus(id,  Long.parseLong(receive),DateUtil.getNow());			 
			 Deviceservice deviceservice = new Deviceservice();
			 deviceservice.setDevicestatusid(id);
			 deviceservice.setRcvman(loginUserName);
			 deviceservice.setRcvtime(DateUtil.getNow());
			 deviceservice.setDealstatus(2);
			 deviceservice.setDealmark(dealmark);
			 DeviceStatusUtil.saveDeviceService(deviceservice);
		 }else if("6".equals(receive)){//已报废
			 DeviceStatusUtil.updateDeviceStatus(id,Long.parseLong(receive),"");			 
			 DeviceStatusUtil.saveDeviceFilter(loginUserName,"99999999999999", "设备报废",Long.parseLong(deviceid));	 
		 }
		 return queryDeviceStatus(mapping,form,request,response);
	 }
	 
}
