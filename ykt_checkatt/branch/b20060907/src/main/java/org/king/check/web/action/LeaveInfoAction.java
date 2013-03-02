package org.king.check.web.action;

import java.net.URLDecoder;
import java.text.DateFormat;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.config.CommonConfig;
import org.king.check.domain.Leaveinfo;
import org.king.check.service.DepartmentService;
import org.king.check.service.LeaveInfoService;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class LeaveInfoAction extends BaseAction {
	 private static final Log log = LogFactory.getLog(LeaveInfoAction.class);
	 
	 private DepartmentService departmentService;
	 
	 private LeaveInfoService leaveInfoService;
	 
	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}
	
	public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
		this.leaveInfoService = leaveInfoService;
	}





		public ActionForward searchLeaveInfo(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			Map filterMap = WebUtils.getParametersStartingWith(request, "leave_");
			
			List departmentTree=departmentService.getDepartmentTree(0,null);
			List leaveInfoList=leaveInfoService.searchLeaveInfo(filterMap);
			
			log.debug("search");
			request.setAttribute("departmentTree",departmentTree);
			request.setAttribute("leaveInfoList",leaveInfoList);
			
			return mapping.findForward("success");
		}
	
	
		public ActionForward goStatic(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			log.debug("goStatic");
			List departmentTree=departmentService.getDepartmentTree(0,null);
			request.setAttribute("departmentTree",departmentTree);
			
			return mapping.findForward("goStatic");
		}
		public ActionForward staticLeaveInfo(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			
			Map filterMap = WebUtils.getParametersStartingWith(request, "leave_");
			
			log.debug("Static");
			
			List departmentTree=departmentService.getDepartmentTree(0,null);
			request.setAttribute("departmentTree",departmentTree);
			
			List staticInfoList=leaveInfoService.staticLeaveInfoByFilter(filterMap);
			request.setAttribute("staticInfoList",staticInfoList);
			
			request.setAttribute("endDate",filterMap.get("endDate"));
			
			return mapping.findForward("goStatic");
		}
		public ActionForward viewLeaveDetail(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			log.debug("viewDetail");
			
			String startDate=request.getParameter("startDate");
			String endDate=request.getParameter("endDate");
			Integer clerkId=new Integer(request.getParameter("clerkId"));
			
			Map filter=new HashMap();
			filter.put(CommonConfig.startDate,startDate);
			filter.put(CommonConfig.endDate,endDate);
			filter.put("clerkId",clerkId);

			List leaveDetailList=leaveInfoService.getLeaveInfoDetail(filter);
			
			request.setAttribute("leaveDetailList",leaveDetailList);
			
			return mapping.findForward("viewDetail");
		}
		public ActionForward delete(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			log.debug("delete");
			List departmentTree=departmentService.getDepartmentTree(0,null);
			request.setAttribute("departmentTree",departmentTree);
			
			String []leaveIds=request.getParameterValues("itemlist");
			
			leaveInfoService.deleteLeaveInfo(leaveIds);
			
			request.setAttribute("msg","成功删除"+leaveIds.length+"条请假信息");
			
			return mapping.findForward("deleteOk");
		}
		
		public ActionForward update(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			log.debug("update");
			List departmentTree=departmentService.getDepartmentTree(0,null);
			request.setAttribute("departmentTree",departmentTree);
			
			Map filterMap = WebUtils.getParametersStartingWith(request, "new_");

			leaveInfoService.updateLeaveInfo(filterMap);
			
			request.setAttribute("msg","修改成功");
			return mapping.findForward("updateOk");
		}
		public ActionForward preUpdate(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			log.debug("preupdate");
			Calendar startCal=Calendar.getInstance();
			Calendar endCal=Calendar.getInstance();
			String leaveInfoId=request.getParameter("pre_leaveinfoId");
			String clerkName=request.getParameter("pre_clerkName");
			clerkName=URLDecoder.decode(clerkName,"UTF-8");
			
			Leaveinfo leaveinfo=new Leaveinfo();
			
			if(leaveInfoId!=null)
				leaveinfo=leaveInfoService.getLeaveInfoById(leaveInfoId);
			
			startCal.setTime(leaveinfo.getStartdate());
			endCal.setTime(leaveinfo.getEnddate());
			
			String new_startDate=DateFormat.getDateInstance().format(leaveinfo.getStartdate());
			String new_endDate=DateFormat.getDateInstance().format(leaveinfo.getEnddate());
			
			
			request.setAttribute("leaveinfo",leaveinfo);
			request.setAttribute("clerkName",clerkName);
			request.setAttribute("new_startDate",new_startDate);
			request.setAttribute("new_endDate",new_endDate);
			request.setAttribute("new_startHour",new Integer(startCal.get(Calendar.HOUR_OF_DAY)));
			request.setAttribute("new_startMin",new Integer(startCal.get(Calendar.MINUTE)));
			request.setAttribute("new_endHour",new Integer(endCal.get(Calendar.HOUR_OF_DAY)));
			request.setAttribute("new_endMin",new Integer(endCal.get(Calendar.MINUTE)));
			request.setAttribute("new_description",leaveinfo.getDescription());
			
			
			return mapping.findForward("preupdate");
		}

}
