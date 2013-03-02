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

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.service.ClerkService;
import org.king.check.service.SysService;
import org.king.check.service.WorkInfoService;
import org.king.check.util.DateUtilExtend;
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
	
}
