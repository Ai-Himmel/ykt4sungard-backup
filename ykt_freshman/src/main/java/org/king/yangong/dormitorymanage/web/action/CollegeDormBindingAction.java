package org.king.yangong.dormitorymanage.web.action;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.dormitorymanage.service.DormitoryService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.StringUtil;
import org.king.yangong.dormitorymanage.service.DormTypeManageService;
import org.king.yangong.dormitorymanage.service.YxGraduateService;

public class CollegeDormBindingAction extends BaseAction {
	private YxGraduateService yxGraduateService;
	private DormitoryService dormitoryService;
	public void setYxGraduateService(YxGraduateService yxGraduateService) {
		this.yxGraduateService = yxGraduateService;
	}
	public void setDormitoryService(DormitoryService dormitoryService) {
		this.dormitoryService = dormitoryService;
	}
	private DormTypeManageService dormTypeManageService;

	public void setDormTypeManageService(DormTypeManageService dormTypeManageService) {
		this.dormTypeManageService = dormTypeManageService;
	}

	public ActionForward load4Search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		ActionMessages messages = new ActionMessages();

		Account account = null;
		if (session.getAttribute("accountPerson") != null) {
			account = (Account) session.getAttribute("accountPerson");
			String stuemp_no = account.getPerson().getPersonCode();
			// 性别
			List sexList = yxGraduateService.getSexList();
			request.setAttribute("sexList", sexList);
			// 学生类别
			List studentTypeList = yxGraduateService.getStudentTypeList();
			request.setAttribute("studentTypeList", studentTypeList);
			// 录取院系
			List collegeList = yxGraduateService
					.getCollegeListFromGraduateTableLimit(stuemp_no);
			request.setAttribute("collegeList", collegeList);

//			List sectionList = yxGraduateService.getSectionList();
//			request.setAttribute("sectionList", sectionList);
//			List districtionList = yxGraduateService.getDistrictionList();
//			request.setAttribute("districtionList", districtionList);
//			List buildingList = yxGraduateService.getBuildingList();
//			request.setAttribute("buildingList", buildingList);
//			List layerList = yxGraduateService.getLayerList();
//			request.setAttribute("layerList", layerList);
//			List cellList = yxGraduateService.getCellList();
//			request.setAttribute("cellList", cellList);
			
			DynaActionForm adjustForm = (DynaActionForm)form; 
			dormitoryService.initForm(request);	
			List areali = (List)request.getAttribute("sectionList");
			if(areali!=null&&areali.size()>0){
				adjustForm.set("section",((Map)areali.get(0)).get("dictValue"));
				request.setAttribute("section", ((Map)areali.get(0)).get("dictValue"));
				List localli = (List)request.getAttribute("districtionList");
				if(localli!=null&&localli.size()>0){
					for(int i=0;i<localli.size();i++){
						if(((Map)localli.get(i)).get("dictParent").equals(((Map)areali.get(0)).get("dictValue"))){
							adjustForm.set("distriction",((Map)localli.get(i)).get("dictValue"));
							request.setAttribute("distriction", ((Map)localli.get(i)).get("dictValue"));
							List dormli = (List)request.getAttribute("dormitoryList");
							for(int j=0;j<dormli.size();j++){
								if(((Map)dormli.get(i)).get("dictParent").equals(((Map)localli.get(0)).get("dictValue"))){
									adjustForm.set("building",((Map)dormli.get(i)).get("dictValue"));
									request.setAttribute("building", ((Map)dormli.get(i)).get("dictValue"));
									break;
								}
							}
							break;
						}
					}
				}
			}
			List collegebindingList = yxGraduateService
					.getCollegeBindingList(stuemp_no);

			request.setAttribute("collegebindingList", collegebindingList);
			List unbinddormitoryList = yxGraduateService
					.getDormitoryList(stuemp_no);
			request.setAttribute("unbinddormitoryList", unbinddormitoryList);
			List binddormList = yxGraduateService
					.getBindedDormitoryList(stuemp_no);
			request.setAttribute("binddormList", binddormList);

		} else {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.loginFirstornotass"));
			saveErrors(request, messages);
			return mapping.findForward("load4Search");
		}

		return mapping.findForward("load4Search");
	}

	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm graduateForm = (DynaActionForm) form;
		HttpSession session = request.getSession();
		String binddormitorys = graduateForm.getString("binddormitorys");
		String unbinddormitorys = graduateForm.getString("unbinddormitorys");
		String[] temp = StringUtil.split(binddormitorys, ",");
		String[] untemp = StringUtil.split(unbinddormitorys, ",");
		ActionMessages messages = new ActionMessages();
		Account account = null;
		 if (request.getSession().getAttribute("accountPerson") != null) {
			 account = (Account) session.getAttribute("accountPerson");
			String stuemp_no = account.getPerson().getPersonCode();
			try {
				yxGraduateService.updateDormitory(temp, untemp,stuemp_no);
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"collegeBinding.success"));
				saveErrors(request, messages);
			} catch (DormitoryHasStuException e) {
				String dormerrmesg = e.getMessage();
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"collegeBinding.studenthasindorm", dormerrmesg));
				saveErrors(request, messages);
			} catch (Exception e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"collegeBinding.error"));
				saveErrors(request, messages);
				e.printStackTrace();
			}
			
		 } else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"classAlert.loginFirstornotass"));
			saveErrors(request, messages);
			return mapping.findForward("load4Search");
		}
	
		
		return load4Search(mapping, form, request, response);
	}

	public ActionForward dormDistributionStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		HttpSession session = request.getSession();
		ActionMessages messages = new ActionMessages();
		Account account = null;
		if (session.getAttribute("accountPerson") != null) {
			account = (Account) session.getAttribute("accountPerson");
			String stuemp_no = account.getPerson().getPersonCode();
			List collegeList = yxGraduateService
					.getCollegeListFromGraduateTableLimit(stuemp_no);
			request.setAttribute("collegeList", collegeList);
			
			List dormList=dormTypeManageService
					.getDormListFromGraduateTableLimit(stuemp_no);
			request.setAttribute("dormList", dormList);
			
			//List CollegeStudentCount = yxGraduateService
			//		.getCollegeStudentCount(stuemp_no);
			//request.setAttribute("CollegeStudentCount", CollegeStudentCount);

			//List CollegeDormitoryStatistic = yxGraduateService
			//		.getCollegeDormitoryStatistic(stuemp_no);
			//request.setAttribute("CollegeDormitoryStatistic",
			//		CollegeDormitoryStatistic);
			
			List CollegeStudentCount=dormTypeManageService.getDormStatbyCollege(stuemp_no);
			request.setAttribute("CollegeStudentCount", CollegeStudentCount);

			List CollegeDormitoryStatistic = dormTypeManageService.getDormStatbyDorm(stuemp_no);
			request.setAttribute("DormitoryStatistic",
					CollegeDormitoryStatistic);

		} else {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.loginFirstornotass"));
			saveErrors(request, messages);
			return mapping.findForward("dormbindresult");
		}

		return mapping.findForward("dormbindresult");
	}
}
