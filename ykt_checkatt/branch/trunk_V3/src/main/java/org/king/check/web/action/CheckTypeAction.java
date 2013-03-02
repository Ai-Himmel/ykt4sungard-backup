package org.king.check.web.action;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.domain.TChecktype;
import org.king.check.service.CheckTypeService;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class CheckTypeAction extends BaseAction {
	private static final Log log = LogFactory.getLog(CheckTypeAction.class);

	private CheckTypeService checkTypeService;

	public void setCheckTypeService(CheckTypeService checkTypeService) {
		this.checkTypeService = checkTypeService;
	}

	public ActionForward goCheckType(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		return mapping.findForward("goCheckType");
	}

	public ActionForward addCheckType_step1(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		return mapping.findForward("add_step1");
	}

	public ActionForward addCheckType(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");

		TChecktype checkType = new TChecktype();

		checkType.setTypeName((String) filterMap.get("typeName"));
		checkTypeService.saveCheckType(checkType);

		searchWorkConfList(request);
		return mapping.findForward("searchRes");
	}

	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		searchWorkConfList(request);
		return mapping.findForward("searchRes");
	}

	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String workIds[] = request.getParameterValues("itemlist");
		StringBuffer tempIds = new StringBuffer(128);
		for (int i=0;i<workIds.length;i++){
			if (i==workIds.length-1){
				tempIds.append("'").append(workIds[i]).append("'");
			}else{
				tempIds.append("'").append(workIds[i]).append("'").append(",");
			}
		}
		List usedWork = checkTypeService.getUsedCheckType(tempIds.toString());
		if (usedWork.size()>0){
			request.setAttribute("msg","要删除的班次信息中有已经被引用的项，不能删除！");
		}else{
			for (int i = 0; i < workIds.length; i++) {
				checkTypeService.deleteCheckType(workIds[i]);
			}
			request.setAttribute("msg", "班次信息删除成功");
		}		

		searchWorkConfList(request);
		return mapping.findForward("searchRes");
	}

	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//HttpSession session = request.getSession();
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");

		TChecktype checkType = checkTypeService.getCheckType((String) filterMap.get("typeId"));

		checkType.setTypeName((String) filterMap.get("typeName"));

		checkTypeService.updateCheckType(checkType);

		request.setAttribute("msg", "班次信息修改成功");
		searchWorkConfList(request);
		return mapping.findForward("searchRes");
	}

	public ActionForward update_step1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("update_step1");

		String typeId = request.getParameter("typeId");

		TChecktype checkType = checkTypeService.getCheckType(typeId);

		request.setAttribute("checkType", checkType);

		return mapping.findForward("update_step1");
	}
	
	private void searchWorkConfList(HttpServletRequest request)throws Exception{
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");

		List checkTypeList = checkTypeService.search(filterMap);
		request.setAttribute("checkTypeList", checkTypeList);

	}
}
