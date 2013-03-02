/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.check.web.action.DepartmentAction.java
 * �������ڣ� 2006-6-16 10:55:44
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-16 10:55:44      ljf        �����ļ���ʵ�ֻ�������
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


import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;


import org.king.check.config.ClerkConfig;
import org.king.check.config.CommonConfig;
import org.king.check.domain.Departconf;
import org.king.check.domain.Department;
import org.king.check.domain.Workconf;
import org.king.check.domain.Worktimeconf;
import org.king.check.exception.DepartmentAlreadyExistException;
import org.king.check.service.DepartConfService;
import org.king.check.service.DepartmentService;
import org.king.check.service.WorkConfService;
import org.king.check.service.WorkTimeConfService;
import org.king.framework.exception.BusinessException;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;



/**
 * <p> DepartmentAction.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="DepartmentAction.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-16
 * 
 *
 */
public class DepartmentAction extends BaseAction {
	private static final Log log = LogFactory.getLog(DepartmentAction.class);
	private DepartmentService departmentService;
	private WorkTimeConfService workTimeConfService;
	private WorkConfService workConfService;
	private DepartConfService departConfService;
	
	
	public void setWorkConfService(WorkConfService workConfService) {
		this.workConfService = workConfService;
	}

	public void setWorkTimeConfService(WorkTimeConfService workTimeConfService) {
		this.workTimeConfService = workTimeConfService;
	}

	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}
	
	public void setDepartConfService(DepartConfService departConfService) {
		this.departConfService = departConfService;
	}

	public  ActionForward load4add( ActionMapping mapping,
			 ActionForm form, HttpServletRequest request,
			 HttpServletResponse response) throws Exception{
		ActionMessages errors = new ActionMessages();
        //List departmentTree;
		// Remove the obsolete form bean
		//removeAttribute(mapping, request);
		
        //departmentTree = departmentService.getDepartmentTree(0,null);
        
        //request.setAttribute("departmenttree", departmentTree);

		
		DynaActionForm departmentForm = (DynaActionForm) form;
		Department dept = new Department();
		String pid = (String) request.getParameter("pid");
		if(pid!=null){
			Department entity = departmentService.getDepartment(pid);
			dept.setParent(entity);
		}

		departmentForm.set("department",dept);
		departmentForm.set("methodToCall", "add");
		
		saveToken(request);
		
		return (mapping.findForward("input"));
	}
	
	/**
	 * 
	 * ��������
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 */
	public  ActionForward create( ActionMapping mapping,
			 ActionForm form, HttpServletRequest request,
			 HttpServletResponse response) throws Exception{
		ActionMessages errors = new ActionMessages();
		 // Was this transaction cancelled?
        if (isCancelled(request)) {
            removeAttribute(mapping, request);

            return (mapping.findForward("cancel"));
        }

        //check token
        if (!isTokenValid(request)) {
            errors.add(ActionMessages.GLOBAL_MESSAGE,
                new ActionMessage("errors.TokenError"));
            resetToken(request);
            saveErrors(request, errors);

            return (mapping.getInputForward());
        }

		Department department = (Department) ((DynaActionForm) form)
				.get("department");
		department.setId(null);

		try {
			departmentService.saveDepartment(department);
		}catch (BusinessException be){
			errors
			.add("create error", new ActionMessage(
					"errors.UnKnowError"));
		}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);
			saveToken(request);

			return (mapping.getInputForward());
		} else {
			// Remove the obsolete form bean
			removeAttribute(mapping, request);

			return (mapping.findForward("success"));
		}
	}

	/**
	 * װ��Ϊ���޸�
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 */
	public final ActionForward load4edit( ActionMapping mapping,
			 ActionForm form,  HttpServletRequest request,
			 HttpServletResponse response) throws Exception{
		ActionMessages errors = new ActionMessages();
        //List departmentTree;
		
		// Remove the obsolete form bean
		//removeAttribute(mapping, request);
		
        //departmentTree = departmentService.getDepartmentTree(0,null);
        
        //request.setAttribute("departmenttree", departmentTree);

		DynaActionForm departmentForm = (DynaActionForm) form;
		String deptId = (String) request.getParameter("id");
		Department dept = null;
		if(deptId!=null){
		    dept = departmentService.getDepartment(deptId);
		}

		departmentForm.set("department",dept);
		departmentForm.set("methodToCall", "edit");
		
        
        saveToken(request);
		return (mapping.findForward("edit"));
	}


	public final ActionForward update( ActionMapping mapping,
			 ActionForm form,  HttpServletRequest request,
			 HttpServletResponse response) throws Exception{
		ActionMessages errors = new ActionMessages();
		Department department = (Department) ((DynaActionForm) form)
				.get("department");

		try {
			departmentService.updateDepartment(department);
		} catch (BusinessException e) {
			errors
					.add("update error", new ActionMessage(
							"errors.UnKnowError"));
		}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);
			saveToken(request);

			return (mapping.getInputForward());
		} else {
			// Remove the obsolete form bean
			removeAttribute(mapping, request);

			return (mapping.findForward("success"));
		}
	}



	/**
	 * ɾ��Ŀ¼
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 */
	public final ActionForward remove(final ActionMapping mapping,
			final ActionForm form, final HttpServletRequest request,
			final HttpServletResponse response) throws Exception{
		ActionMessages errors = new ActionMessages();
		ActionMessages messages = new ActionMessages();
		String id = request.getParameter("id");
		if(id==null){
			errors
			.add("remove error", new ActionMessage(
					"errors.UnKnowError"));
		}
		try {
		   departmentService.deleteDepartment(id);
		}catch (BusinessException be){
			errors
			.add("remove error", new ActionMessage(
					"errors.UnKnowError"));
		}
		
		if (!errors.isEmpty()) {
			saveErrors(request, errors);
			saveToken(request);
			return (mapping.getInputForward());
		}
		
		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"success.delete", "1"));

		saveMessages(request, messages);
		// Remove the obsolete form bean
		removeAttribute(mapping, request);

		return (mapping.findForward("success"));
	}

	/**
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getDepartmentXMLTree(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'getXMLMenu' method");
		}

		String deptTree = departmentService.getDepartmentXmlTree();

		request.setAttribute("menuTree", deptTree);

		return mapping.findForward("success");
	}
	
	/**
	 * ���벿���б�
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4list(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		
		return mapping.findForward("list");
	}
	
	
	/**
	 * ȡ��
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward cancel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		
		return mapping.findForward("success");
	}
	
	/**
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward loadDepartmentTree(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		
		return mapping.findForward("selectTree");
	}
	public ActionForward goDeptConf(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goDeptConf");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		
		request.setAttribute("departmentTree",departmentTree);
		return mapping.findForward("goDeptConf");
	}
	/*
	 * ��Ӳ�������ѡ����
	 */
	public ActionForward addConfSltDpt(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addConfSltDpt");
		
		
		request.getSession().removeAttribute("dptConfList");
		request.getSession().removeAttribute("new_department");
		request.getSession().removeAttribute("dptName");
		request.getSession().removeAttribute("dptConfList");
		return mapping.findForward("addConfSltDpt");
	}
	/*
	 * ���в�������
	 */
	public ActionForward addConfStep1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addConfStep1");
		String dept_id=request.getParameter("new_department");
		
		Department dpt=departmentService.getDepartment(dept_id);
		
		List workConfList=workConfService.getAll();
		List workTimeConfList=workTimeConfService.getAll();
		List dptConfList=departConfService.getDepartConfByDptId(dept_id);
		
		
		request.getSession().setAttribute("dptConfList",dptConfList);
		request.getSession().setAttribute("workConfList",workConfList);
		request.getSession().setAttribute("workTimeConfList",workTimeConfList);
		request.getSession().setAttribute("new_department",dept_id);
		request.setAttribute("display","block");
		request.getSession().setAttribute("dptName",dpt.getName());
    	//request.getSession().setAttribute("recentDate",recentDate);
		
		return mapping.findForward("addConfStep1");
	}
	/*
	 * �õ��ƶ���Ϣ
	 */
	public ActionForward getConfDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		String workConfId=request.getParameter("new_clerkRule");//��ӹ����ƶ�ϸ��
		if(StringUtils.isNotEmpty(workConfId))
			{
			  Workconf workconf=workConfService.getWorkConf(workConfId);
			  String workconfDetail="";
			  workconfDetail+="��������:"+workconf.getPreearly()+"���� ";
			  workconfDetail+="����ٵ�:"+workconf.getPermitlatetime()+"���� ";
			  workconfDetail+="�ϰ���ǰ�򿨲�������:"+workconf.getOndutyad()+"���� ";
			  workconfDetail+="�°�������ͺ�:"+workconf.getOffdutyovertime()+"���� ";
			  request.setAttribute("workconfDetail",workconfDetail);
			}
		
		String workTimeConfId=request.getParameter("new_cherkTimeRule");//��ӹ���ʱ��ϸ��
		if(StringUtils.isNotEmpty(workTimeConfId))
		{
			Worktimeconf worktimeconf=workTimeConfService.getWorkTimeConf(workTimeConfId);
			String timeDetail="";
			int token=1;
			String ondutytime,offdutytime;
			if(StringUtils.isNotEmpty(worktimeconf.getOndutytime1())||StringUtils.isNotEmpty(worktimeconf.getOffdutytime1()))
			{
				ondutytime=worktimeconf.getOndutytime1();
				offdutytime=worktimeconf.getOffdutytime1();
				timeDetail+=StringUtils.isNotEmpty(ondutytime)?"�ϰ�ʱ��"+token+": "+ondutytime.substring(0,2)+"��"+ondutytime.substring(2)+"�� ":"";
				timeDetail+=StringUtils.isNotEmpty(offdutytime)?"�°�ʱ��"+token+": "+offdutytime.substring(0,2)+"��"+offdutytime.substring(2)+"�� ":"";
				token++;
			}
			if(StringUtils.isNotEmpty(worktimeconf.getOndutytime2())||StringUtils.isNotEmpty(worktimeconf.getOffdutytime2()))
			{
				ondutytime=worktimeconf.getOndutytime2();
				offdutytime=worktimeconf.getOffdutytime2();
				timeDetail+=StringUtils.isNotEmpty(ondutytime)?"�ϰ�ʱ��"+token+": "+ondutytime.substring(0,2)+"��"+ondutytime.substring(2)+"�� ":"";
				timeDetail+=StringUtils.isNotEmpty(offdutytime)?"�°�ʱ��"+token+": "+offdutytime.substring(0,2)+"��"+offdutytime.substring(2)+"�� ":"";
				token++;
			}
			if(StringUtils.isNotEmpty(worktimeconf.getOndutytime3())||StringUtils.isNotEmpty(worktimeconf.getOffdutytime3()))
			{
				ondutytime=worktimeconf.getOndutytime3();
				offdutytime=worktimeconf.getOffdutytime3();
				timeDetail+=StringUtils.isNotEmpty(ondutytime)?"�ϰ�ʱ��"+token+": "+ondutytime.substring(0,2)+"��"+ondutytime.substring(2)+"�� ":"";
				timeDetail+=StringUtils.isNotEmpty(offdutytime)?"�°�ʱ��"+token+": "+offdutytime.substring(0,2)+"��"+offdutytime.substring(2)+"�� ":"";
				token++;
			}
			if(StringUtils.isNotEmpty(worktimeconf.getOndutytime4())||StringUtils.isNotEmpty(worktimeconf.getOffdutytime4()))
			{
				ondutytime=worktimeconf.getOndutytime4();
				offdutytime=worktimeconf.getOffdutytime4();
				timeDetail+=StringUtils.isNotEmpty(ondutytime)?"�ϰ�ʱ��"+token+": "+ondutytime.substring(0,2)+"��"+ondutytime.substring(2)+"�� ":"";
				timeDetail+=StringUtils.isNotEmpty(offdutytime)?"�°�ʱ��"+token+": "+offdutytime.substring(0,2)+"��"+offdutytime.substring(2)+"�� ":"";
				token++;
			}	
			request.setAttribute("timeDetail",timeDetail);
		}
		
		List workConfList=workConfService.getAll();
		List workTimeConfList=workTimeConfService.getAll();
		List departmentTree = departmentService.getDepartmentTree(0, null);
		
		request.setAttribute("workConfList",workConfList);
		request.setAttribute("workTimeConfList",workTimeConfList);
		request.setAttribute("departments",departmentTree);
		
		return mapping.findForward("addConfStep1");
	}
	/*
	 * ��ӿ����ƶ�
	 */
	public ActionForward addConf(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addConf");
		Map filterMap = WebUtils.getParametersStartingWith(request, "new_");
		String startDate=(String)filterMap.get("startDate");
		String endDate=(String)filterMap.get("endDate");
		
		Departconf departconf=new Departconf();
		departconf.setStartdate(startDate.substring(0,4)+startDate.substring(5,7)+startDate.substring(8));
		departconf.setEnddate(endDate.substring(0,4)+endDate.substring(5,7)+endDate.substring(8));
		departconf.setIsseat((String)filterMap.get("isSeat"));
		if((String)filterMap.get("restinwkd")!=null&&((String)filterMap.get("restinwkd")).equals(CommonConfig.restInWKD))
			departconf.setRestinwkd(CommonConfig.restInWKD);
		else departconf.setRestinwkd(CommonConfig.workInWKD);
		
		Map paraMap=new HashMap();
		paraMap.put("startDate",departconf.getStartdate());
		paraMap.put("endDate",departconf.getEnddate());
		paraMap.put("dptId",(String)filterMap.get("department"));
		List  existList=departConfService.isExist(paraMap);//����Ű�ƻ��Ƿ��Ѿ�����
		if(!existList.isEmpty())
		{
			String msg="ʱ����Ѵ���,������.";
			String buttonInfo="����";
			String actionUrl="history.back();";
			request.setAttribute("msg",msg);//��ʾ��Ϣ
			request.setAttribute("btnInfo",buttonInfo);//��ť��Ϣ
			request.setAttribute("actionUrl",actionUrl);//������Ϣ
			request.setAttribute("startDate",startDate);
			request.setAttribute("endDate",endDate);
			request.setAttribute("display","block");
			request.setAttribute("existList",existList);
			request.setAttribute("timeDetail",(String)filterMap.get("timeDetail"));
			request.setAttribute("workconfDetail",(String)filterMap.get("workconfDetail"));
			if(((String)filterMap.get("isSeat")).equals(Integer.toString(ClerkConfig.isSeat)))
			{
				request.setAttribute("isSeat","����");
			}
			else
			{
				request.setAttribute("isSeat","������");
			}
			return mapping.findForward("finish");
		}
		
		Department dpt=departmentService.getDepartment((String)filterMap.get("department"));
		departconf.setDepartment(dpt);
		
		if((String)filterMap.get("isSeat")!=null&&((String)filterMap.get("isSeat")).equals(Integer.toString(ClerkConfig.isSeat)))
		{
			Worktimeconf worktimeconf=workTimeConfService.getWorkTimeConf((String)filterMap.get("cherkTimeRule"));
			Workconf workconf=workConfService.getWorkConf((String)filterMap.get("clerkRule"));
			departconf.setWorkconf(workconf);
			departconf.setWorktimeconf(worktimeconf);
		}
		
		departConfService.save(departconf);		
		
		String msg="���óɹ�,�����Լ�������";
		String buttonInfo="��������";
		String actionUrl="window.location.href='department.do?method=addConfSltDpt';";//������Ϣ
		request.setAttribute("btnInfo",buttonInfo);//��ť��Ϣ
		request.setAttribute("actionUrl",actionUrl);
		request.setAttribute("msg",msg);//��ʾ��Ϣ
		request.setAttribute("startDate",startDate);
		request.setAttribute("endDate",endDate);
		request.setAttribute("display","none");
		request.setAttribute("timeDetail",(String)filterMap.get("timeDetail"));
		request.setAttribute("workconfDetail",(String)filterMap.get("workconfDetail"));
		if(((String)filterMap.get("isSeat")).equals(Integer.toString(ClerkConfig.isSeat)))
		{
			request.setAttribute("isSeat","����");
		}
		else
		{
			request.setAttribute("isSeat","������");
		}
		
		return mapping.findForward("finish");
	}
	
	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("search");
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		List dptConfList=departConfService.search(filterMap);
        List departmentTree=departmentService.getDepartmentTree(0,null);
		
		request.setAttribute("departmentTree",departmentTree);
		request.setAttribute("dpConfList",dptConfList);
		request.setAttribute("startDate",(String)filterMap.get("startDate"));
		request.setAttribute("endDate",(String)filterMap.get("endDate"));
		return mapping.findForward("goDeptConf");
	}
	
}
