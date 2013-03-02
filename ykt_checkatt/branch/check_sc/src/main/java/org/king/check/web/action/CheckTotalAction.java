/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.check.web.CheckTotalAction.java
 * �������ڣ� 2006-6-13 13:48:18
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-13 13:48:18      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.check.web.action;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.config.CommonConfig;
import org.king.check.domain.TMakereportrecord;
import org.king.check.domain.TMakereportrecordId;
import org.king.check.service.ClerkService;
import org.king.check.service.SysService;
import org.king.check.service.WorkInfoService;
import org.king.check.util.DateUtilExtend;
import org.king.check.util.MailSender;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

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
	 * װ�ظ��˳�ϯ���ͳ��
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goCheckStatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String endDate = DateUtilExtend.getNowDate();
		String startDate = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-30);
		request.setAttribute("startDate",DateUtilExtend.formatDate3(startDate));
		request.setAttribute("endDate",endDate);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		return mapping.findForward("goCheckStatic");
	}

	/**
	 * ���˳�ϯ���ͳ�Ʊ���
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getCheckStatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String startDate = request.getParameter("cs_startDate");
		String endDate = request.getParameter("cs_endDate");
		String stuempNo = "";
		String deptId = request.getParameter("deptId");
		if (request.getParameter("cs_stuNo")!=null){
			stuempNo = request.getParameter("cs_stuNo");
		}
		List checkStaticStat = clerkService.getCheckReportStat(stuempNo,DateUtilExtend.formatDate2(startDate),DateUtilExtend.formatDate2(endDate),deptId);
		
		request.setAttribute("checkStaticStat",checkStaticStat);
		request.setAttribute("startDate",startDate);
		request.setAttribute("endDate",endDate);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		return mapping.findForward("goCheckStatic");
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
	 * �����ɿ�����־����ҳ��,����Ĭ�����ں�������
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
		
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}

		
		return mapping.findForward("goMakeCheckReport");
	}
	
	/**
	 * �����ɿ�����־����ҳ��,����Ĭ�����ں�������
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
		String startDate = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-30);
		String endDate = DateUtilExtend.getNowDate();
		request.setAttribute("startDate",DateUtilExtend.formatDate3(startDate));
		request.setAttribute("endDate",endDate);
		
		
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}
		return mapping.findForward("goMakeCheckReportFinance");
	}
	
	/**
	 * ���ɿ������ڱ���
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getMakeCheckReportFinance(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		String cmd = request.getParameter("cmd");
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		String startDate = request.getParameter("startDate");
		String endDate = request.getParameter("endDate");
		
		String deptId = request.getParameter("deptId");
		
		request.setAttribute("startDate",startDate);
		request.setAttribute("endDate",endDate);
		
		
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}

		List checkReportList = workInfoService.makeCheckReportFinance(startDate,endDate,deptId);
		if(checkReportList.isEmpty()){
			request.setAttribute("msg", "δ�鵽�����ڷ�Χ������Ϣ");
			return mapping.findForward("goMakeCheckReportFinance");
		}
		/*	if("print".equals(cmd)){
				request.setAttribute("syear",statDate.substring(0,4)); 
				request.setAttribute("smonth",statDate.substring(5,7));
				request.setAttribute("checkReportList",checkReportList);
				return mapping.findForward("CheckReportPrint");
			}*/
			String realPath = request.getRealPath("");

			
			//����excel�ļ�,���浽������ָ��λ��,���������excelʱֱ���������ɵ��ļ�
			sysService.importReportToExcelFinance(realPath,deptId,startDate,endDate,checkReportList,accountId);
			request.setAttribute("checkReportList",checkReportList);
			//��ɺ����ʼ������������
			if ("".equals(deptId)){
				deptId = "0";
			}
	
			String fileAddr = realPath+"/downloadfile/"+deptId+startDate+"--"+endDate+"checkRecordReport.xls";
			//String fileAddr = realPath+"\\downloadfile\\"+deptId+startDate+"--"+endDate+"checkRecordReport.xls";
			//MailSender.mailsSender(mailStr.toString(),fileAddr,statMonth+"�·ݿ���ϵͳ����");
			
			return mapping.findForward("goMakeCheckReportFinance");
		//}
	}
	
	/**
	 * ���ɿ������ڱ���
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getMakeCheckReport(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		String cmd = request.getParameter("cmd");
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		String statDate = request.getParameter("statDate");
		String deptId = request.getParameter("deptId");
		List ss = sysService.getWeekByDate(statDate);
		String statMonth = statDate.substring(0,4)+statDate.substring(5,7);
		request.setAttribute("ss",ss);
		request.setAttribute("statDate",statDate.substring(0,7));
		
		request.setAttribute("dayNum",new Integer(DateUtilExtend.getDaysByMonth(statDate)));
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}

	/*	if (sysService.getReportRecord(deptId,statMonth)>0){
			request.setAttribute("msg", "���·ݵĿ��ڱ����Ѿ�����,��ֱ�ӵ�����ΪExcel����!");
			return mapping.findForward("goMakeCheckReport");
		}else{*/
			List checkReportList = workInfoService.makeCheckReport(statDate,deptId);
			if("print".equals(cmd)){
				request.setAttribute("syear",statDate.substring(0,4)); 
				request.setAttribute("smonth",statDate.substring(5,7));
				request.setAttribute("checkReportList",checkReportList);
				return mapping.findForward("CheckReportPrint");
			}
			String realPath = request.getRealPath("");
			TMakereportrecord reportRecord = new TMakereportrecord();
			TMakereportrecordId reportId = new TMakereportrecordId();
			if ("".equals(deptId)){
				reportId.setDeptId("0");
			}else{
				reportId.setDeptId(deptId);
			}
			reportId.setReportMonth(statMonth);
			reportRecord.setReportDate(DateUtilExtend.getNowDate2());
			reportRecord.setStatus("1");
			reportRecord.setId(reportId);
			clerkService.makeReportRecord(reportRecord);
			
			//����excel�ļ�,���浽������ָ��λ��,���������excelʱֱ���������ɵ��ļ�
			sysService.importReportToExcel(realPath,deptId,statDate,checkReportList,accountId);
			request.setAttribute("checkReportList",checkReportList);
			//��ɺ����ʼ������������
			if ("".equals(deptId)){
				deptId = "0";
			}
			/*List mailList = sysService.getEmailList();
			StringBuffer mailStr = new StringBuffer(512);
			if (mailList.size()>0){
				for (int i=0;i<mailList.size();i++){
					Map mailMap = (Map)mailList.get(i);
					if (i==mailList.size()-1){
						mailStr.append(mailMap.get("email").toString());
					}else{
						mailStr.append(mailMap.get("email").toString()).append(";");
					}				
				}
			}*/
			String fileAddr = realPath+"/downloadfile/"+deptId+statMonth+"checkRecordReport.xls";
			//String fileAddr = realPath+"\\downloadfile\\"+deptId+statMonth+"checkRecordReport.xls";
			//MailSender.mailsSender(mailStr.toString(),fileAddr,statMonth+"�·ݿ���ϵͳ����");
			
			return mapping.findForward("goMakeCheckReport");
		//}
	}
	
	public ActionForward downLoadFileFinanceAction(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		sysService.downLoadFileFinance(request,response);
		return null;
	}
	
	public ActionForward downLoadFileAction(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		sysService.downLoadFile(request,response);
		return null;
	}
	
	/**
	 * hanjiwei add it 20061107
	 * ���˿��������ϸ
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goCheckDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		String endDate = DateUtilExtend.getNowDate();
		String startDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.formatDate2(endDate),-6));
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		
		
		request.setAttribute(CommonConfig.startDate, startDate);
		request.setAttribute(CommonConfig.endDate, endDate);
		return mapping.findForward("queryCheckDetail");
	}
	
	/**
	 * hanjiwei add it 20061107
	 * ���˿��������ѯ
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getCheckDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Map filterMap = WebUtils.getParametersStartingWith(request, "dutyInfo_");

		request.setAttribute("startDate", (String) filterMap.get(CommonConfig.startDate));
		request.setAttribute("endDate", (String) filterMap.get(CommonConfig.endDate));
		
		String beginDate = DateUtilExtend.formatDate2((String) filterMap.get("startDate"));
		String endDate = DateUtilExtend.formatDate2((String) filterMap.get("endDate"));
		String deptId = (String) filterMap.get("deptId");
		String stuempNo = "";
		if ((String) filterMap.get("stuempNo")!=null){
			stuempNo = (String) filterMap.get("stuempNo");
		}
		List checkDetail = clerkService.getCheckDetail(stuempNo,beginDate,endDate,deptId);
		
		request.setAttribute("checkDetail",checkDetail);
		
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		return mapping.findForward("queryCheckDetail");
	}
	
	/**
	 * ������Ա������ˮ
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goCheckSerial(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		String endDate = DateUtilExtend.getNowDate();
		String startDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.formatDate2(endDate),-6));
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		
		
		request.setAttribute(CommonConfig.startDate, startDate);
		request.setAttribute(CommonConfig.endDate, endDate);
		return mapping.findForward("queryCheckSerial");
	}

	/**
	 * ������Ա������ˮ��ѯ
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getCheckSerial(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Map filterMap = WebUtils.getParametersStartingWith(request, "dutyInfo_");

		request.setAttribute("startDate", (String) filterMap.get(CommonConfig.startDate));
		request.setAttribute("endDate", (String) filterMap.get(CommonConfig.endDate));
		
		String beginDate = DateUtilExtend.formatDate2((String) filterMap.get("startDate"));
		String endDate = DateUtilExtend.formatDate2((String) filterMap.get("endDate"));
		String deptId = (String) filterMap.get("deptId");
		String stuempNo = "";
		if ((String) filterMap.get("stuempNo")!=null){
			stuempNo = (String) filterMap.get("stuempNo");
		}
		List checkSerial = clerkService.getCheckSerial(stuempNo,beginDate,endDate,deptId);
		
		request.setAttribute("checkSerial",checkSerial);
		
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		return mapping.findForward("queryCheckSerial");
	}
	
	/**
	 * �����ɿ�����־����ҳ��,����Ĭ�����ں�������
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goMakeCheckReportStu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		String beginDate = DateUtilExtend.getNowDate2();
		String endDate = DateUtilExtend.addDate2(beginDate,6);	
		request.setAttribute("endDate",endDate);
		request.setAttribute("beginDate1",beginDate);
		request.setAttribute("beginDate",DateUtilExtend.formatDate3(beginDate));
		
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}		
		return mapping.findForward("goMakeCheckReportStu");
	}

	/**
	 * ����ѧ���������ڱ���
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getMakeCheckReportStu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		String beginDate = DateUtilExtend.formatDate2(request.getParameter("beginDate"));
		
		String endDate = DateUtilExtend.addDate2(beginDate,6);	
		String deptId = request.getParameter("deptId");
		request.setAttribute("beginDate1",beginDate);
		request.setAttribute("beginDate",DateUtilExtend.formatDate3(beginDate));
		request.setAttribute("endDate",endDate);
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}
		String statDeptId = "0";
		if (!"".equals(deptId)){
			statDeptId = deptId;
		}
		if (sysService.getReportRecord(statDeptId,beginDate)>0){
			request.setAttribute("msg", "��ʱ���ѧ�����ڱ����Ѿ�����,��ֱ�ӵ�����ΪExcel����!");
			return mapping.findForward("goMakeCheckReportStu");
		}else{
			List checkReportList = workInfoService.makeStuCheckReport(beginDate,endDate,deptId);
			String realPath = request.getRealPath("");
			TMakereportrecord reportRecord = new TMakereportrecord();
			TMakereportrecordId reportId = new TMakereportrecordId();
			if ("".equals(deptId)){
				reportId.setDeptId("0");
			}else{
				reportId.setDeptId(deptId);
			}
			reportId.setReportMonth(beginDate);
			reportRecord.setReportDate(DateUtilExtend.getNowDate2());
			reportRecord.setStatus("1");
			reportRecord.setId(reportId);
			clerkService.makeReportRecord(reportRecord);
			
			//����excel�ļ�,���浽������ָ��λ��,���������excelʱֱ���������ɵ��ļ�
			sysService.importReportToExcelStu(realPath,deptId,beginDate,endDate,checkReportList,accountId);
			request.setAttribute("checkReportList",checkReportList);
			//��ɺ����ʼ������������
			if ("".equals(deptId)){
				deptId = "0";
			}
			List mailList = sysService.getEmailList();
			StringBuffer mailStr = new StringBuffer(512);
			if (mailList.size()>0){
				for (int i=0;i<mailList.size();i++){
					Map mailMap = (Map)mailList.get(i);
					if (i==mailList.size()-1){
						mailStr.append(mailMap.get("email").toString());
					}else{
						mailStr.append(mailMap.get("email").toString()).append(";");
					}				
				}
			}
			String fileAddr = realPath+"/downloadfile/"+deptId+beginDate+"checkRecordReport.xls";
			MailSender.mailsSender(mailStr.toString(),fileAddr,beginDate+"�·ݿ���ϵͳ����");
			
			return mapping.findForward("goMakeCheckReportStu");
		}
	}

}
