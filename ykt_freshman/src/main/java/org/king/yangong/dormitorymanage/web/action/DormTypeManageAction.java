package org.king.yangong.dormitorymanage.web.action;

import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;
import org.king.yangong.dormitorymanage.domain.GraduateType;
import org.king.yangong.dormitorymanage.service.DormTypeManageService;

public class DormTypeManageAction extends BaseAction{
	
	DormTypeManageService dormTypeManageService;
	
	
	public ActionForward loadDormTypeList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm graduateTypeSearchForm = (DynaActionForm) form;
		String type = request.getParameter("graduateTypeSearch");
		List li = dormTypeManageService.getDormTypeList(type);
		request.setAttribute("graduateTypeList", li);
		return mapping.findForward("graduateTypeList");
	}
	
	public ActionForward loadGraduateTypeInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		Map map = new HashMap();
		
		DynaActionForm graduateTypeForm = (DynaActionForm) form;
		String itemList = request.getParameter("itemList");
		if(itemList!=null&&!itemList.equals("")){
			GraduateType graduateType = (GraduateType)dormTypeManageService.getDormTypeInfo(itemList);
			graduateTypeForm.set("id", graduateType.getId());
			graduateTypeForm.set("graduateType", graduateType.getGraduateType());
		}else{
			graduateTypeForm.set("id", "");
			graduateTypeForm.set("graduateType", "");
		}
		
		return mapping.findForward("graduateTypeInfo");
	}
	
	public ActionForward saveGraduateTypeInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		DynaActionForm graduateTypeForm = (DynaActionForm) form;
		ActionMessages messages = new ActionMessages();
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		String id = request.getParameter("id");
		GraduateType graduateType = new GraduateType();
		if(id!=null&&!id.equals("")){
			graduateType.setId(graduateTypeForm.getString("id"));
			graduateType.setGraduateType(graduateTypeForm.getString("graduateType"));
			graduateType.setUpdator(operator);
			graduateType.setIfdeleted("1");
			graduateType.setUpdateTime(DateUtil.getNow("yyyy-MM-dd"));
			dormTypeManageService.updateDormTypeInfo(graduateType);
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("updateGraduateInfo.success"));
			saveErrors(request, messages);
		}else{
			graduateType.setGraduateType(graduateTypeForm.getString("graduateType"));
			graduateType.setUpdator(operator);
			graduateType.setIfdeleted("1");
			graduateType.setUpdateTime(DateUtil.getNow("yyyy-MM-dd"));
			dormTypeManageService.saveDormTypeInfo(graduateType);
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("saveGraduateInfo.success"));
			saveErrors(request, messages);
		}
		
		return mapping.findForward("graduateTypeSaveSuccess");
	}
	
	public ActionForward deleteDormTypeInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionMessages messages = new ActionMessages();
		String[] itemLists = request.getParameterValues("itemList");
//		for(int i=0;i<itemLists.length;i++){
//			List li = dormTypeManageService.findGraduateByGT(itemLists[i]);
//			if(li!=null&&li.size()!=0){
//				messages.add(ActionMessages.GLOBAL_MESSAGE,
//						new ActionMessage("ifdelete.ifdelete"));
//				saveErrors(request, messages);
//				return mapping.findForward("graduateTypeDeletenoSuccess");
//			}
//		}
		dormTypeManageService.deleteDormTypeInfo(itemLists);
		messages.add(ActionMessages.GLOBAL_MESSAGE,
				new ActionMessage("deleteInfo.success"));
		saveErrors(request, messages);
		return mapping.findForward("graduateTypeDeleteSuccess");
	}
	
	public void setDormTypeManageService(DormTypeManageService dormTypeManageService) {
		this.dormTypeManageService = dormTypeManageService;
	}
}
