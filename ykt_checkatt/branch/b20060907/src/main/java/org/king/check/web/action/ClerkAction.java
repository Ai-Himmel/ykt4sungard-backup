/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.check.web.ClerkAction.java
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

import java.util.ArrayList;
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
import org.king.check.Constants;
import org.king.check.domain.Clerk;
import org.king.check.domain.Clerkinfo;
import org.king.check.domain.Department;
import org.king.check.domain.Workconf;
import org.king.check.domain.Workconfmap;
import org.king.check.domain.Worktimeconf;
import org.king.check.service.ClerkService;
import org.king.check.service.DepartConfService;
import org.king.check.service.DepartmentService;
import org.king.check.service.SysService;
import org.king.check.service.WorkConfMapService;
import org.king.check.service.WorkConfService;
import org.king.check.service.WorkTimeConfService;
import org.king.framework.web.action.BaseAction;
import org.king.security.service.DictionaryService;
import org.springframework.web.util.WebUtils;

/**
 * <p>
 * CheckAction.java
 * </p>
 * <p>
 * {����˵��}
 * </p>
 * 
 * <p>
 * <a href="ClerkAction.java.html"><i>�鿴Դ����</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-13
 * 
 * 
 */
public class ClerkAction extends BaseAction {
	
	private static final Log log = LogFactory.getLog(ClerkAction.class);
	//private static final int defaultPageSize = 3;

	private ClerkService clerkService;
	private DepartmentService departmentService;
	private DictionaryService dictionaryService;
	private SysService sysService;
	private WorkTimeConfService workTimeConfService;
	private WorkConfService workConfService;
	private WorkConfMapService workConfMapService;
	private DepartConfService  departConfService;
	
	
	public void setClerkService(ClerkService clerkService) {
		this.clerkService = clerkService;
	}

	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}

	public void setDictionaryService(DictionaryService dictionaryService) {
		this.dictionaryService = dictionaryService;
	}


	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}


	public void setWorkTimeConfService(WorkTimeConfService workTimeConfService) {
		this.workTimeConfService = workTimeConfService;
	}


	public void setWorkConfService(WorkConfService workConfService) {
		this.workConfService = workConfService;
	}

	public void setWorkConfMapService(WorkConfMapService workConfMapService) {
		this.workConfMapService = workConfMapService;
	}

	public void setDepartConfService(DepartConfService departConfService) {
		this.departConfService = departConfService;
	}

	/**
	 * װ�ؿ�����Ա��Ϣ
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4queryClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		//request.setAttribute("departments",departmentTree);
		//����ȡ�����еĲ����б�
		List deptList=sysService.getDeptList();
		request.setAttribute("departments",deptList);
		
		//��Ա����
		//List dictionarys = dictionaryService.findDictionaryByNo("1001");
		//request.setAttribute("dictionarys",dictionarys);
		return mapping.findForward("query");
	}
	
	/**
	 * ��ѯ������Ա
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward queryClerkInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		List clerkList = clerkService.queryClerk(filterMap);
		List deptList=sysService.getDeptList();
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		//��Ա����
		//List dictionarys = dictionaryService.findDictionaryByNo("1001");
		//request.setAttribute("dictionarys",dictionarys);
		
		request.setAttribute("clerks",clerkList);
		request.setAttribute("departments",deptList);
		
		return mapping.findForward("success");
	}
	
	
	/**
	 * װ�ؿ����õ���Ա
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4queryAvailableClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		
		List departmentTree = departmentService.getDepartmentTree(0, null);
		request.setAttribute("departments",departmentTree);
		
		//��Ա����
		List dictionarys = dictionaryService.findDictionaryByNo("1001");
		request.setAttribute("dictionarys",dictionarys);
		
		//��״̬
		//List cardStatusList=sysService.getCardStatus();
		//request.setAttribute("cardStatusList",cardStatusList);
		
		//��Ա����
	    List personTypeList=sysService.getPersonType();
	    request.setAttribute("personTypeList",personTypeList);
	    
	    //�����
	    List cardTypeList=sysService.getCardType();
	    request.setAttribute("cardTypeList",cardTypeList);
	    
	    //�����б�
	    List departList=sysService.getDepartList();
	    request.setAttribute("departList",departList);
	    
	    
		return mapping.findForward("queryPerson");
	}
	
	
	/**
	 * ��ѯ�����õ���Ա
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward QueryAvailablePerson(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		//��״̬
		//List cardStatusList=sysService.getCardStatus();
		//request.setAttribute("cardStatusList",cardStatusList);
		
		//��Ա����
	    List personTypeList=sysService.getPersonType();
	    request.setAttribute("personTypeList",personTypeList);
	    
	    //�����
	    List cardTypeList=sysService.getCardType();
	    request.setAttribute("cardTypeList",cardTypeList);
	    
	    //�����б�
	    List departList=sysService.getDepartList();
	    request.setAttribute("departList",departList);
	    
	    List searchRes=sysService.search(filterMap);
	    request.setAttribute("searchRes",searchRes);
		/*List clerkList = clerkService.queryAvailableClerk(filterMap);
		List departmentTree = departmentService.getDepartmentTree(0, null);
//		��Ա����
		List dictionarys = dictionaryService.findDictionaryByNo("1001");
		request.setAttribute("dictionarys",dictionarys);
		
		request.setAttribute("clerks",clerkList);
		request.setAttribute("departments",departmentTree);*/
		
		return mapping.findForward("queryPerson");

	}
	
	/**
	 * װ�ؿ�����Ա����
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4setupClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		String[] ids = request.getParameterValues("itemlist");
		request.getSession().setAttribute(Constants.SELECTED_PERSON,ids);
		
		//hanjiweiע����20060830��
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		
		//List workConfList=workConfService.getAll();
		//List workTimeConfList=workTimeConfService.getAll();
		
		//request.setAttribute("workConfList",workConfList);
		//request.setAttribute("workTimeConfList",workTimeConfList);
		//request.setAttribute("departments",departmentTree);
		//����ȡ�����еĲ����б�
		List deptList=sysService.getDeptList();
		request.setAttribute("deptList",deptList);
		return mapping.findForward("setup");
	}
	
	/**
	 * ���ÿ�����Ա��Ϣ
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward setupClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		ActionMessages messages = new ActionMessages();
		
		String [] ids = (String [])request.getSession().getAttribute(Constants.SELECTED_PERSON);
		String deptId = request.getParameter("department");
		String isSeat = request.getParameter("isSeat");
		/**String department = request.getParameter("department");
		List confList=departConfService.getDepartConfByDptId(department);
		Departconf departconf=new Departconf();
		if(!confList.isEmpty())
		{
			departconf=(Departconf)confList.get(0);
		}
		Department entity = departmentService.getDepartment(department);**/
		
		List idList = new ArrayList();
		for(int i=0;i<ids.length;i++){
			if(!idList.contains(ids[i])){
				idList.add(ids[i]);
			}
		}
		
		List clerkList = new ArrayList();
		if(ids != null){
			for(int i=0;i<idList.size();i++){
				Clerkinfo clerk = new Clerkinfo();
				clerk.setCustId(Integer.valueOf((String)idList.get(i)));
				clerk.setDeptId(deptId);
				clerk.setIfoffice(isSeat);
				//clerk.setClerkid(Integer.valueOf((String)idList.get(i)));
				//clerk.setIsseat(departconf.getIsseat());
				//clerk.setDepartment(entity);
				//clerk.setIsirregularrest(ClerkConfig.isNoIrregularRest);
				clerkList.add(clerk);
			}
			
			int count = clerkService.setupClerk(clerkList);
			messages.add(ActionMessages.GLOBAL_MESSAGE,new ActionMessage("success.setup",String.valueOf(count)));
			saveMessages(request, messages);
		}
		return mapping.findForward("success");
	}
	
	
	public ActionForward deleteClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		ActionMessages messages = new ActionMessages();
		int count = 0;
		String [] ids = request.getParameterValues("itemlist");
		if(ids!=null){
			for(int i=0;i<ids.length;i++){
				clerkService.deleteClerk(ids[i]);
				count++;
			}
			
			messages.add(ActionMessages.GLOBAL_MESSAGE,new ActionMessage("success.delete",String.valueOf(count)));
			saveMessages(request, messages);
			
		}
		return mapping.findForward("success");
	}
	public ActionForward setupSeatClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
        ActionMessages messages = new ActionMessages();
		
		String [] ids = (String [])request.getSession().getAttribute(Constants.SELECTED_PERSON);
		String department = request.getParameter("department");
		String isSeat = request.getParameter("isSeat");
		String workTimeConfId=request.getParameter("cherkTimeRule");
		String workConfId=request.getParameter("clerkRule");
		
		Department entity = departmentService.getDepartment(department);
		
		List idList = new ArrayList();
		for(int i=0;i<ids.length;i++){
			if(!idList.contains(ids[i])){
				idList.add(ids[i]);
			}
			
		}
		
		List clerkList = new ArrayList();
		if(ids != null){
			for(int i=0;i<idList.size();i++){
				Clerk clerk = new Clerk();
				clerk.setClerkid(Integer.valueOf((String)idList.get(i)));
				clerk.setIsseat(isSeat);
				clerk.setDepartment(entity);
				clerk.setWorktimeconfid(workTimeConfId);
				clerkList.add(clerk);
				
				Workconfmap workconfmap=workConfMapService.getWorkconfmapByClerkId(Integer.valueOf((String)idList.get(i)));
				
				if(workconfmap==null)
				{
					workconfmap=new Workconfmap();
				    workconfmap.setClerkid(Integer.valueOf((String)idList.get(i)));
				    workconfmap.setWorkconfid(workConfId);
				
				    workConfMapService.save(workconfmap);
				}
				else
				{
					workconfmap.setWorkconfid(workConfId);
					workConfMapService.update(workconfmap);
				}
			}
			
			int count = clerkService.setupClerk(clerkList);
			messages.add(ActionMessages.GLOBAL_MESSAGE,new ActionMessage("success.setup",String.valueOf(count)));
			saveMessages(request, messages);
			
		}
		
		
		return mapping.findForward("success");
	}
	public ActionForward getConfDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		String workConfId=request.getParameter("clerkRule");//��ӹ����ƶ�ϸ��
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
		
		String workTimeConfId=request.getParameter("cherkTimeRule");//��ӹ���ʱ��ϸ��
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
		
		return mapping.findForward("setup");
	}
	public ActionForward viewClerkDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		log.debug("viewClerkDetail");
		String clerkId=request.getParameter("clerkId");
		
		Map clerkInfo=clerkService.getClerkDetailByClerkId(clerkId);
		
		request.setAttribute("clerkInfo",clerkInfo);
		
		return mapping.findForward("showDetail");		
	}
}
