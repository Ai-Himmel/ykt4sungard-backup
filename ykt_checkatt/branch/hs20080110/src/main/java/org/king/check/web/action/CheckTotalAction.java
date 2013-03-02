/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.web.CheckTotalAction.java
 * 创建日期： 2006-6-13 13:48:18
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-13 13:48:18      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.check.web.action;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.domain.TMakereportrecord;
import org.king.check.domain.TMakereportrecordId;
import org.king.check.service.ClerkService;
import org.king.check.service.SysService;
import org.king.check.service.WorkInfoService;
import org.king.check.util.DateUtilExtend;
import org.king.framework.util.MyUtils;
import org.king.framework.web.action.BaseAction;

public class CheckTotalAction extends BaseAction {
	private SysService sysService;
	private WorkInfoService workInfoService;

	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	private ClerkService clerkService;
	
	public void setClerkService(ClerkService clerkService){
		this.clerkService = clerkService;
	}
	public void setWorkInfoService(WorkInfoService workInfoService) {
		this.workInfoService = workInfoService;
	}

	/**
	 * 
	 * 装载个人出席情况统计
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goPersonCheckStatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String endDate = DateUtilExtend.getNowDate();
		String startDate = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-30);
		request.setAttribute("startDate",DateUtilExtend.formatDate3(startDate));
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goPersonCheckStatic");
	}

	/**
	 * 个人出席情况统计报表
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getPersonCheckStatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String startDate = request.getParameter("cs_startDate");
		String endDate = request.getParameter("cs_endDate");
		String stuempNo = request.getParameter("cs_stuNo");
		Map filter = new HashMap();
		filter.put("stuempNo",stuempNo);
		//统计结果信息
		List custList = sysService.getCustInfo(filter);
		if (custList.size()>0){
			Map custMap = (Map)custList.get(0);
			request.setAttribute("clerkName",custMap.get("CUT_NAME"));
			request.setAttribute("stuempNo",custMap.get("STUEMP_NO"));
			request.setAttribute("deptName",custMap.get("DEPT_NAME"));
		}
		int custId = sysService.getCustIdByStuempNo(stuempNo);
		List checkDetail = null;
		Map clerkReport = null;
		if (custId != 0){
			checkDetail = workInfoService.getOneCheckDetail(custId,DateUtilExtend.formatDate2(startDate),
					DateUtilExtend.formatDate2(endDate));
			clerkReport = clerkService.getCheckReportByStuempNo(custId,DateUtilExtend.formatDate2(startDate),
					DateUtilExtend.formatDate2(endDate));
			request.setAttribute("ifOffice",sysService.getIfOffice(custId));
			request.setAttribute("checkDetail",checkDetail);
			
			request.setAttribute("factWorkValue",clerkReport.get("factWorkValue"));
			request.setAttribute("workValue",clerkReport.get("workValue"));
			request.setAttribute("overValue",clerkReport.get("overValue"));
			request.setAttribute("twoRestValue",clerkReport.get("twoRestValue"));
			request.setAttribute("holidayValue",clerkReport.get("holidayValue"));
			request.setAttribute("delayValue",clerkReport.get("delayValue"));
			request.setAttribute("leaveEarlyValue",clerkReport.get("leaveEarlyValue"));
			request.setAttribute("leaveTimeValue",clerkReport.get("leaveTimeValue"));
			request.setAttribute("leaveValue",clerkReport.get("leaveValue"));
		}
		request.setAttribute("startDate",startDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goPersonCheckStatic");
	}
	
	public ActionForward load4clerkQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		return mapping.findForward("input");
	}
	
	public ActionForward clerkQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		return mapping.findForward("success");
	}
	
	/**
	 * 打开生成考勤日志报表页面,载入默认日期和所属周
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goMakeCheckReport(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		String statDate = DateUtilExtend.getNowDate().substring(0,7);
		request.setAttribute("statDate",statDate);
		List ss = sysService.getWeekByDate(statDate);
		request.setAttribute("dayNum",new Integer(DateUtilExtend.getDaysByMonth(statDate)));
		request.setAttribute("ss",ss);
		//如果该操作员拥有的部门权限数量等于部门数量，该操作员为超级管理员，可以操作所有的部门出勤报表
		int deptCount = sysService.getDeptCount();
		int accountDeptCount = sysService.getDeptCountByAccount(accountId);
		if (deptCount==accountDeptCount){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}
		return mapping.findForward("goMakeCheckReport");
	}
	
	/**
	 * 打开生成考勤日志报表页面,载入默认日期和所属周
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goMakeCheckReportFinance(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		String statDate = DateUtilExtend.getNowDate().substring(0,7);
		request.setAttribute("statDate",statDate);
		List ss = sysService.getWeekByDate(statDate);
		request.setAttribute("dayNum",new Integer(DateUtilExtend.getDaysByMonth(statDate)));
		request.setAttribute("ss",ss);
		//如果该操作员拥有的部门权限数量等于部门数量，该操作员为超级管理员，可以操作所有的部门出勤报表
		
		int deptCount = sysService.getDeptCount();
		int accountDeptCount = sysService.getDeptCountByAccount(accountId);
		if (deptCount==accountDeptCount){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}
		
		return mapping.findForward("goMakeCheckReportFinance");
	}
	
	public ActionForward  getMakeCheckReport(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		//System.out.println("test kq begin");
		HttpSession  session = request.getSession();
		String realPath = request.getRealPath("");
		String accountId =(String)session.getAttribute("account");
		
		String deptId = request.getParameter("deptId");
		
		List  deptList = sysService.getDeptList(accountId);
		
		request.setAttribute("departmentTree", deptList);
		
	
		
		String statDate = request.getParameter("statDate");  
		
		List ss = sysService.getWeekByDate(statDate);
		String statMonth = statDate.substring(0,4)+statDate.substring(5,7);
		request.setAttribute("ss",ss);
		request.setAttribute("statDate",statDate.substring(0,7));
		request.setAttribute("dayNum",new Integer(DateUtilExtend.getDaysByMonth(statDate)));
		
		
        List checkReportList = workInfoService.getCheckReportByMonth(deptId,deptList,statDate);
		
		request.setAttribute("checkReportList", checkReportList);
		//判断是否为财务人员
		String finance = request.getParameter("finance").toString();
		if(checkReportList != null && checkReportList.size()>0){
		 
			sysService.importReportToExcel(realPath,deptId,statDate,checkReportList,accountId,finance);
		 
		}
		if ("1".equals(finance)){
        	//	System.out.println("goMakeCheckReportFinance kq begin");

			return mapping.findForward("goMakeCheckReportFinance");
		}else{
        	//	System.out.println("goMakeCheckReport kq begin");

			return mapping.findForward("goMakeCheckReport");
		}
	}
	
	
	
	
	/**
	 * 生成考勤日期报表
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	/*public ActionForward getMakeCheckReport(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		//如果该操作员拥有的部门权限数量等于部门数量，该操作员为超级管理员，可以操作所有的部门出勤报表
		
		int deptCount = sysService.getDeptCount();
		int accountDeptCount = sysService.getDeptCountByAccount(accountId);
		if (deptCount<=accountDeptCount){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		String statDate = request.getParameter("statDate");  
		String deptId = request.getParameter("deptId");
		
		List ss = sysService.getWeekByDate(statDate);
		String statMonth = statDate.substring(0,4)+statDate.substring(5,7);
		request.setAttribute("ss",ss);
		request.setAttribute("statDate",statDate.substring(0,7));
		request.setAttribute("dayNum",new Integer(DateUtilExtend.getDaysByMonth(statDate)));
		
		//判断是否为财务人员
		String finance = request.getParameter("finance").toString();
		
		
		 * 如果选择所有，则认为是列表中所有的部门
		 * hanjiwei add it 20080520******************************************
		 
		StringBuffer deptStr = new StringBuffer(512);
		if ("".equals(deptId)){
			//Iterator deptIter = deptList.iterator();
			//while (deptIter.hasNext()){
			for (int i=0;i<deptList.size();i++){
				Map deptMap = (Map)deptList.get(i);
				String dep = deptMap.get("deptId").toString();
				if(deptList.size()==1){
					deptStr.append(dep);
				}else{
				if (i==0){
					deptStr.append(dep).append("',");
				}else if (i==deptList.size()-1){
					deptStr.append("'").append(dep);
				}else{
					deptStr.append("'").append(dep).append("',");
				}
				}
				
			}
		}else{
			deptStr.append(deptId);
		}
		//********************************************************************
		
		hanjiwei delete it 20080520*********************
		if ("".equals(deptId)){
			tmpDeptId = "0";
		}else{
			tmpDeptId = deptId;
		}
		**************************************************
		
		
		String tmpDeptId = MyUtils.toMD5(deptStr.toString());
		
		String makeSign = request.getParameter("makeSign").toString();
		String status = "0";
		if ("0".equals(makeSign)){
			status = sysService.getReportRecord(tmpDeptId,statMonth);
		}
		
		if ("1".equals(finance)&&"2".equals(status)){
			request.setAttribute("msg", "该月份的人事考勤报表已经生成,请直接点击另存为Excel,也可以点击“重新生成报表”重新生成。");
			return mapping.findForward("goMakeCheckReportFinance");
		}else if ("0".equals(finance)&&"1".equals(status)){
			request.setAttribute("msg", "该月份的部门考勤报表已经生成,请直接点击另存为Excel,也可以点击“重新生成报表”重新生成。");
			return mapping.findForward("goMakeCheckReport");
		}
		
		//1为部门报表已经生成，2为人事报表已经生成，3为人事、部门报表都已经生成
		if ("3".equals(status)){
			request.setAttribute("msg", "该月份的考勤报表已经生成,请直接点击另存为Excel,也可以点击“重新生成报表”重新生成。");
			if ("1".equals(finance)){
				return mapping.findForward("goMakeCheckReportFinance");
			}else{
				return mapping.findForward("goMakeCheckReport");
			}
		}else{
			List checkReportList = workInfoService.makeCheckReport(statDate,deptStr.toString());
			String realPath = request.getRealPath("");
			TMakereportrecord reportRecord = new TMakereportrecord();
			TMakereportrecordId reportId = new TMakereportrecordId();
			//if ("".equals(deptId)){
				//reportId.setDeptId("0");
			//}else{
			reportId.setDeptId(tmpDeptId);
			//}
			reportId.setReportMonth(statMonth);
			reportRecord.setReportDate(DateUtilExtend.getNowDate2());
			if ("1".equals(status)){
				if ("1".equals(finance)){
					reportRecord.setStatus("3");
				}else{
					reportRecord.setStatus("1");
				}
			}else if (("2".equals(status))){
				if ("1".equals(finance)){
					reportRecord.setStatus("2");
				}else{
					reportRecord.setStatus("3");
				}
			}else if (("0".equals(status))){
				if ("1".equals(finance)){
					reportRecord.setStatus("2");
				}else{
					reportRecord.setStatus("1");
				}
			}
			
			reportRecord.setId(reportId);
			clerkService.makeReportRecord(reportRecord);
			
			//生成excel文件,保存到服务器指定位置,当点击保存excel时直接下载生成的文件
			if ("".equals(deptId)){
				sysService.importReportToExcel(realPath,tmpDeptId,statDate,checkReportList,accountId,finance);
			}else{
				sysService.importReportToExcel(realPath,deptStr.toString(),statDate,checkReportList,accountId,finance);
			}
			request.setAttribute("checkReportList",checkReportList);
			
			if ("1".equals(finance)){
				return mapping.findForward("goMakeCheckReportFinance");
			}else{
				return mapping.findForward("goMakeCheckReport");
			}
		}
	}*/
	
	public ActionForward downLoadFileAction(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		sysService.downLoadFile(request,response);
		return null;
	}

}
