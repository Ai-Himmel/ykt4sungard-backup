package org.king.check.web.action;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.config.CommonConfig;
import org.king.check.service.DepartmentService;
import org.king.check.service.DutyTimeService;
import org.king.check.service.WorkInfoService;
import org.king.check.service.WorkStaticService;
import org.king.check.util.DutyTimeUtil;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;
import org.apache.commons.lang.builder.CompareToBuilder;

public class WorkStaticAction  extends BaseAction {
	
	 private static final Log log = LogFactory.getLog(WorkInfoAction.class);
	 	 
	 private WorkStaticService workStaticService;
	 
	 private DepartmentService departmentService;
	 	
	public void setWorkStaticService(WorkStaticService workStaticService) {
		this.workStaticService = workStaticService;
	}

	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}
	
	public ActionForward goclerkstatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goclerkstatic");
		//List departmentTree=departmentService.getDepartmentTree(0,null);
		//request.setAttribute("departmentTree",departmentTree);
		
		return mapping.findForward("goclerkstatic");
	}
	
	public ActionForward gochecklog(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("gochecklog");
		//List departmentTree=departmentService.getDepartmentTree(0,null);
		//request.setAttribute("departmentTree",departmentTree);
		
		return mapping.findForward("gochecklog");
	}
	
	public ActionForward godeptstatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goclerkstatic");
		List departmentTree = departmentService.getDepartmentTree(0, null);
		if(departmentTree!=null&&departmentTree.size()>0)
		    request.setAttribute("departments",departmentTree);
		return mapping.findForward("godeptstatic");
	}
	
	public ActionForward checklog(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "log_");
		
		 if(StringUtils.isNotEmpty((String)filterMap.get(CommonConfig.startDate)))
			  request.setAttribute("startDate",(String)filterMap.get(CommonConfig.startDate));
		 if(StringUtils.isNotEmpty((String)filterMap.get(CommonConfig.endDate)))
			 request.setAttribute("endDate",(String)filterMap.get(CommonConfig.endDate));
		 
		 log.debug("Static");
		 
		 List staticInfoList=new ArrayList();
		 
		 if(workStaticService!=null){ 		
			   
			 staticInfoList=workStaticService.checklogByFilter(filterMap);
			    
			 if(staticInfoList!=null&&staticInfoList.size()>0)
			       request.setAttribute("staticInfoList",staticInfoList);
			    
		}
	
		 return mapping.findForward("checklog");
	}

	public ActionForward clerkstatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "cs_");
		
		 if(StringUtils.isNotEmpty((String)filterMap.get(CommonConfig.startDate)))
			  request.setAttribute("startDate",(String)filterMap.get(CommonConfig.startDate));
		 if(StringUtils.isNotEmpty((String)filterMap.get(CommonConfig.endDate)))
			 request.setAttribute("endDate",(String)filterMap.get(CommonConfig.endDate));
		 
		String stuNo=(String)filterMap.get("stuNo");
		
		String clerkid="";
		
		if(workStaticService!=null){ 
			clerkid=workStaticService.getclerkId(stuNo);
			filterMap.put("personCode",clerkid);//从学工号得到clerkId
		}
		log.debug("Static");
		
		//List departmentTree=departmentService.getDepartmentTree(0,null);
		//request.setAttribute("departmentTree",departmentTree);
		List staticInfoList=new ArrayList();
		List clerkInfoList=new ArrayList();
		Map sumInfoList=new HashMap();
		
		if(workStaticService!=null&&clerkid!=null){ 		
		    staticInfoList=workStaticService.clerkstaticByFilter(filterMap);
		    clerkInfoList=workStaticService.getclerkInfo((String)filterMap.get("personCode"));
		    sumInfoList=workStaticService.sumstaticByFilter(filterMap);
		    
		    if(staticInfoList!=null&&staticInfoList.size()>0)
		       request.setAttribute("staticInfoList",staticInfoList);
		    
		    if(clerkInfoList!=null&&clerkInfoList.size()>0){
		    	Map clerkInfo=new HashMap();
		    	clerkInfo=(Map)clerkInfoList.get(0);
		    	request.setAttribute("clerkName",clerkInfo.get("clerkName"));
		    	request.setAttribute("cardId",clerkInfo.get("cardId"));
		    	request.setAttribute("deptName",clerkInfo.get("deptName"));
		    	
		    }
		    
		    if(sumInfoList!=null&&sumInfoList.size()>0){
		    	request.setAttribute("workNum",sumInfoList.get("workNum"));
		    	request.setAttribute("notworkNum",sumInfoList.get("notworkNum"));
		    	request.setAttribute("extraNum",sumInfoList.get("extraNum"));
		    	request.setAttribute("irregularNum",sumInfoList.get("irregularNum"));
		    	request.setAttribute("leaveNum",sumInfoList.get("leaveNum"));
		    	request.setAttribute("outNum",sumInfoList.get("outNum"));
		    	
		    }
		}
		
		return mapping.findForward("clerkstatic");
	}
	
	public ActionForward viewDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		String checkDate=request.getParameter("checkDate");
		String clerkId=request.getParameter("clerkId");
		String flag=request.getParameter("flag");
		
		log.debug("ViewDetail");
		
		//List departmentTree=departmentService.getDepartmentTree(0,null);
		//request.setAttribute("departmentTree",departmentTree);
		List staticInfoList=new ArrayList();
		List clerkInfoList=new ArrayList();
		
		if(workStaticService!=null){ 		
		    staticInfoList=workStaticService.clerkstaticDetail(checkDate,clerkId,flag);
		    clerkInfoList=workStaticService.getclerkInfo(clerkId);
		    
		    if(staticInfoList!=null&&staticInfoList.size()>0)
		       request.setAttribute("staticInfoList",staticInfoList);
		    
		    if(clerkInfoList!=null&&clerkInfoList.size()>0){
		    	Map clerkInfo=new HashMap();
		    	clerkInfo=(Map)clerkInfoList.get(0);
		    	request.setAttribute("clerkName",clerkInfo.get("clerkName"));
		    	request.setAttribute("cardId",clerkInfo.get("cardId"));
		    	request.setAttribute("deptName",clerkInfo.get("deptName"));
		    	
		    }
		}
		
		return mapping.findForward("clerkstaticdetail");
	}
   
	public ActionForward deptstatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		List departmentTree = departmentService.getDepartmentTree(0, null);
		if(departmentTree!=null&&departmentTree.size()>0)
		    request.setAttribute("departments",departmentTree);
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "ds_");
		
		if(StringUtils.isNotEmpty((String)filterMap.get(CommonConfig.startDate)))
			  request.setAttribute("startDate",(String)filterMap.get(CommonConfig.startDate));
		if(StringUtils.isNotEmpty((String)filterMap.get(CommonConfig.endDate)))
			 request.setAttribute("endDate",(String)filterMap.get(CommonConfig.endDate));
		if(StringUtils.isNotEmpty((String)filterMap.get("deptId")))
			 request.setAttribute("deptId",(String)filterMap.get("deptId"));
		
		List staticInfoList=new ArrayList();
		List deptInfoList=new ArrayList();
		
        log.debug("Static");
		
		if(workStaticService!=null){ 		
		    staticInfoList=workStaticService.deptstaticByFilter(filterMap);
		    deptInfoList=workStaticService.getdeptInfo((String)filterMap.get("deptId"));
		    
		    if(staticInfoList!=null&&staticInfoList.size()>0)
		       request.setAttribute("staticInfoList",staticInfoList);
		    
		    if(deptInfoList!=null&&deptInfoList.size()>0){
		    	Map deptInfo=new HashMap();
		    	deptInfo=(Map)deptInfoList.get(0);		    	
		    	request.setAttribute("deptName",deptInfo.get("deptName"));
		    	
		    }
		
	    }
		return mapping.findForward("deptstatic");
	}
	
	/*
	public ActionForward searchNoSeatWorkInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm noSeatParaForm = (DynaActionForm) form;
		String  startDate= (String)noSeatParaForm.get(CommonConfig.startDate);
	    String endDate=(String)noSeatParaForm.get(CommonConfig.endDate);
	    String departId=(String)noSeatParaForm.get(CommonConfig.deptId);

	    if(StringUtils.isNotEmpty(startDate)&&StringUtils.isNotEmpty(endDate))
		{	    	
	    	startDate=startDate+" 00:00:00";
	    	endDate=endDate+" 23:59:59";
	    	
	    	log.debug(startDate+endDate);
		}
	
		HashMap paraMap=new HashMap();
		paraMap.put(CommonConfig.startDate,startDate);
		paraMap.put(CommonConfig.endDate,endDate);
		paraMap.put(CommonConfig.deptId,departId);
		
		List noSeatWorkInfoList=dutyTimeService.searchInfo(paraMap);
		List departmentTree=departmentService.getDepartmentTree(0,null);

		request.getSession().setAttribute("noSeatWorkInfoList",noSeatWorkInfoList);
		request.setAttribute("departmentTree",departmentTree);
		request.setAttribute(CommonConfig.startDate,(String)noSeatParaForm.get(CommonConfig.startDate));
		request.setAttribute(CommonConfig.endDate,(String)noSeatParaForm.get(CommonConfig.endDate));
						
		return mapping.findForward("success");
	}

	public ActionForward noSeatWorkInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		DynaActionForm noSeatParaForm = (DynaActionForm) form;
		if(!StringUtils.isNotEmpty((String)noSeatParaForm.get(CommonConfig.startDate)))
			log.debug("test out ");
		List noSeatWorkInfoList=new ArrayList();
		request.getSession().setAttribute("noSeatWorkInfoList",noSeatWorkInfoList);
		return mapping.findForward("success");
	}
	public ActionForward dealWithNoSeatClerkInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		workInfoService.dealWithNoSeatClerk();
		return mapping.findForward("success");
	}
	public ActionForward getNewFormatDutyTimeInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String msg;
		Map filterMap = WebUtils.getParametersStartingWith(request, "dutyInfo_");
		
		request.setAttribute(CommonConfig.startDate,(String)filterMap.get(CommonConfig.startDate));
		request.setAttribute(CommonConfig.endDate,(String)filterMap.get(CommonConfig.endDate));
				
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		msg=DutyTimeUtil.validate(filterMap);
		if(msg!=null)
		{
			request.setAttribute("msg",msg);
			return mapping.findForward("newformat");
		}
        
        Map newFormatM=dutyTimeService.searchForNewFormat(filterMap);
		
        log.debug("action over");
        
		request.setAttribute("newFormatL",(List)newFormatM.get(CommonConfig.dutyStrs));
		request.setAttribute("titleStr",(String)newFormatM.get(CommonConfig.titleStr));
		
		return mapping.findForward("newformat");
	}
	public ActionForward goNewFormat(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String startDate,endDate;
		List departmentTree=departmentService.getDepartmentTree(0,null);
		Date curDate=new Date();
		int offSet=6;
				
		endDate=DutyTimeUtil.getLastDate(curDate,0);
		startDate=DutyTimeUtil.getLastDate(curDate,offSet);
		
		String titleStr="<td width='100' align='center'  bgcolor='#A8D1E6'>部门</td>  <td><table border='1'  cellpadding='1'" +
		"  cellspacing='2' > <tr>" ;
		titleStr+="<td  width='50' align='center' class='tdHeader1'>姓名</td>";
		titleStr+="<td width='95' class='tableHeader6' align='center'>"+startDate+"</td>";
		titleStr+="<td width='95' class='tableHeader6' align='center'>"+endDate+"</td>";
		titleStr+="</tr></table></td>";
		
		
		request.setAttribute("titleStr",titleStr);
		request.setAttribute(CommonConfig.startDate,startDate);
		request.setAttribute(CommonConfig.endDate,endDate);
		request.setAttribute("departmentTree",departmentTree);
		return mapping.findForward("gonewformat");
	} 
	public ActionForward goMenualRegister(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goMenualRegister");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		
		return mapping.findForward("goMenualRegister");
	}
	public ActionForward searchClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("searchClerk");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		
		
		List clerkList=workInfoService.searchClerkForReg(filterMap);
		
		if(!clerkList.isEmpty())
		{
			request.setAttribute("show","block");
		}
		
		request.setAttribute("clerkList",clerkList);
		
		return mapping.findForward("goMenualRegister");
	}
	//手工打卡
	public ActionForward manualRegister(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("manualRegister");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		String  ids[]=request.getParameterValues("itemlist");
		filterMap.put("ids",ids);
		String card_number[];
		
		if((card_number=workInfoService.judgeIsOwnValidCardByClerkId(ids))==null)
		{
			request.setAttribute("msg","卡号无效,请检查!");
			
			return mapping.findForward("goMenualRegister");
		}
		
		filterMap.put("card_number",card_number);

		workInfoService.manualRegister(filterMap);
	
		request.setAttribute("msg","打卡成功"+ids.length+"条数据");
		return mapping.findForward("goMenualRegister");
	}
	*/
}
