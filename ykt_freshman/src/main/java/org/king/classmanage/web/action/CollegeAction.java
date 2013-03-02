/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegeAction.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-25     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.action;

import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.CollegemanagerId;
import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.Schoolmodel;
import org.king.classmanage.service.ClassService;
import org.king.classmanage.service.CollegeService;
import org.king.classmanage.service.ManagerService;
import org.king.classmanage.web.help.CollegeWithLeader;
import org.king.framework.web.action.BaseAction;

public class CollegeAction extends BaseAction {

	private CollegeService collegeService;

	private ManagerService managerService;
	
	private ClassService ClassService;

	/**
	 * @param classService The classService to set.
	 */
	public void setClassService(ClassService classService) {
		ClassService = classService;
	}

	/**
	 * @param collegeService
	 *            The collegeService to set.
	 */
	public void setCollegeService(CollegeService collegeService) {
		this.collegeService = collegeService;
	}

	/**
	 * @param managerService
	 *            The managerService to set.
	 */
	public void setManagerService(ManagerService managerService) {
		this.managerService = managerService;
	}

	/**
	 * Description: �����ѯ����
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return Modify History: 2006-4-25 jackey create
	 */
	public ActionForward load4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		List retcollege_leader = new ArrayList();

		List colleges = collegeService.getAllCollegeByfdxy();
		for (int i = 0; i < colleges.size(); i++) {
			Collegemodel collegemodel = (Collegemodel) colleges.get(i);
			CollegeWithLeader collegewithleader = new CollegeWithLeader();
			try {
				BeanUtils.copyProperties(collegewithleader, collegemodel);
			} catch (IllegalAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InvocationTargetException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			Managermodel managermodel = null;
			List leaderList = managerService.getCollegeManager(collegemodel
					.getCollegeId());
			if (leaderList.size() > 0) {
				managermodel = (Managermodel) leaderList.get(0);
				collegewithleader.setManagerId(managermodel.getManagerId());
				collegewithleader.setManagerName(managermodel.getManagerName());
			} else {
				collegewithleader.setManagerId("");
				collegewithleader.setManagerName("");
			}
			retcollege_leader.add(collegewithleader);
		}
		request.setAttribute("collegeleaders", retcollege_leader);
		return mapping.findForward("list");
	}

	/**
	 * Description: ������ӽ���
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return Modify History: 2006-4-25 jackey create
	 */
	public ActionForward load4Add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		List list = managerService.getCollegeManager();
		request.setAttribute("managermodel", list);
		request.setAttribute("actionFlag", "Add");
		return mapping.findForward("add");
	}

	/**
	 * Description: �����޸Ľ���
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return Modify History: 2006-4-25 jackey create
	 */
	public ActionForward load4Edit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm collegeForm = (DynaActionForm) form;
		String collegeId = request.getParameter("collegeId");
		if (null != collegeId) {
			Collegemodel collegemodel = collegeService.getCollege(collegeId);
			if (null == collegemodel) {
				load4List(mapping, form, request, response);
			}
			List leaderList = managerService.getCollegeManager(collegemodel
					.getCollegeId());
			if (leaderList.size() > 0) {
				Managermodel managermodel = (Managermodel) leaderList.get(0);
				collegeForm.set("collegeleader", managermodel.getManagerId());
			}

			List list = managerService.getCollegeManager();
			request.setAttribute("managermodel", list);
			collegeForm.set("collegemodel", collegemodel);

		}
		request.setAttribute("actionFlag", "Modify");
		return mapping.findForward("edit");
	}

	/**
	 * Description: TODO
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return Modify History: 2006-4-25 jackey create
	 */
	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		DynaActionForm collegeForm = (DynaActionForm) form;
		Schoolmodel schoolmodel = new Schoolmodel();
		schoolmodel.setSchoolId("0001");
		Collegemodel collegemodel = (Collegemodel) collegeForm
				.get("collegemodel");
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();

		if ("".equals(collegemodel.getCollegeId())) {
			try {
				// ����
				collegemodel.setYxSchool(schoolmodel);
				String collegeleader = collegeForm.getString("collegeleader");
				List list_no = collegeService.getCollegebyNo(collegemodel.getCollegeNo());
				List list_name = collegeService.getCollegebyName(collegemodel.getCollegeName());
				if (list_no.size()> 0) {
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("college.thesamecollegeno"));
					saveErrors(request, messages);
					return load4Add(mapping, form, request, response);
				}else if(list_name.size()>0){
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("college.thesamecollegename"));
					saveErrors(request, messages);
					return load4Add(mapping, form, request, response);
				}else {
					Collegemanager collegemanager = new Collegemanager();
					collegeService.saveCollegeAndLeader(collegemodel,
							collegeleader, collegemanager);
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("college.added", collegemodel
									.getCollegeName()));
					saveErrors(request, messages);
				}

			} catch (Exception e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"college.notadded", collegemodel.getCollegeName()));
				saveErrors(request, messages);
				return load4Add(mapping, form, request, response);
			}
		} else {
			try {
				// �޸�
				collegemodel.setYxSchool(schoolmodel);
				String collegeleader = collegeForm.getString("collegeleader");
				Collegemanager collegemanager = null;
				if (!"".equals(collegeleader)) {
					collegemanager = new Collegemanager();
					CollegemanagerId managerId = new CollegemanagerId();
					managerId.setCollegeId(collegemodel.getCollegeId());
					managerId.setManagerId(collegeleader);
					collegemanager.setId(managerId);
				}

				collegeService.updateCollegeAndLeader(collegemodel,
						collegeleader, collegemanager);
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"college.modified", collegemodel.getCollegeName()));
				saveErrors(request, messages);
			} catch (Exception e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"college.notmodified", collegemodel.getCollegeName()));
				saveErrors(request, messages);
				return load4Add(mapping, form, request, response);
			}
		}

		return load4List(mapping, form, request, response);

	}

	/**
	 * Description: ɾ����Ժ��Ϣ
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return Modify History: 2006-4-25 jackey create
	 */
public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm collegeForm = (DynaActionForm) form;
		Collegemodel collegemodel = (Collegemodel) collegeForm
				.get("collegemodel");
//		 Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		if(ClassService.getClassbyCollegeId(collegemodel.getCollegeId()).size()>0){
			// �а༶����
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("college.cannotbedelete",
							collegemodel.getCollegeName()));
			saveErrors(request, messages);
			return load4Add(mapping, form, request, response);
			
		}else{
			// ����ɾ��
			collegeService.deleteCollege(collegemodel.getCollegeId());
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("college.deleted",
							collegemodel.getCollegeName()));
			saveErrors(request, messages);
		}
		
		return load4List(mapping, form, request, response);
	}}
