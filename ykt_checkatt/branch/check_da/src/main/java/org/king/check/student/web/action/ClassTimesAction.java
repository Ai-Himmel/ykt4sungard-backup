package org.king.check.student.web.action;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.domain.TTime;
import org.king.check.service.TimeService;
import org.king.framework.web.action.BaseAction;

public class ClassTimesAction  extends BaseAction {
	
	private TimeService timeService;

	public void setTimeService(TimeService timeService) {
		this.timeService = timeService;
	}
	
	 public ActionForward search(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
		throws Exception {
		     
		       List timeList = timeService.findClassTimes();
		       
		       request.setAttribute("timeList",timeList);
		       
		       return mapping.findForward("list");
	     
	 }
	 
	 public ActionForward editTime(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
		throws Exception {
		     
		       String   classNum = request.getParameter("classNum");
		       TTime time  =  timeService.getTime(Integer.parseInt(classNum));
		       return mapping.findForward("editTime");
	 } 
	 
	 public ActionForward  addClasssTimes(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
		throws Exception {
		       return mapping.findForward("add");
	 } 
	 
	 public ActionForward  update_step1(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
		throws Exception {
		       DynaActionForm  dform = (DynaActionForm)form;
		       String classNum = request.getParameter("classNum");
		       Map time1 = timeService.getTimeByClass(classNum.toString());
		       BeanUtils.copyProperties(dform,time1); 
		       
		       return mapping.findForward("edit");
	 } 
	 
	 
	 
	 public ActionForward  saveClasssTimes(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
		throws Exception {
		       DynaActionForm  dform = (DynaActionForm)form;
		       String beginTime = dform.getString("beginTime").toString();
		       String endTime =dform.getString("endTime").toString();
		       
		       String classNum =dform.getString("classNum").toString();
		       if(beginTime==null||beginTime.equals("")||endTime==null||endTime.equals("")||classNum==null||classNum.equals("")){
		    	   request.setAttribute("result", "输入项不能为空");
		    	   return mapping.findForward("add");
		       }
		       TTime time1 = timeService.getTime(Integer.valueOf(classNum.toString()));
		       if(time1!=null){
		    	   request.setAttribute("result", "课次已存在");
		    	   return mapping.findForward("add");
		       }
		       
		       TTime  time = new TTime();
		       time.setClassNum(Integer.valueOf(classNum.toString()));
		       time.setBeginTime(beginTime);
		       time.setEndTime(endTime);
		       timeService.saveClassTimes(time);
		       return search(mapping,form,request,response);
	 } 
	 
	 public ActionForward  updateClasssTimes(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
		throws Exception {
		       DynaActionForm  dform = (DynaActionForm)form;
		       TTime  time = timeService.getTime(Integer.parseInt(dform.getString("classNum")));
		       BeanUtils.copyProperties(time,dform); 
		       
		       timeService.updateClassTime(time);
		       return search(mapping,form,request,response);
	 } 
	 

}
