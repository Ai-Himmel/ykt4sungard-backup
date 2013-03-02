package org.king.dormitorymanage.web.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.king.classmanage.service.ClassService;
import org.king.dormitorymanage.exception.DormitoryNotEnoughException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.dormitorymanage.service.DormitoryService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;

public class GzDormitoryDistrAction extends BaseAction {
	private DormitoryService dormitoryService;

	private ClassService classService;

	public void setDormitoryService(DormitoryService dormitoryService) {
		this.dormitoryService = dormitoryService;
	}

	public void setClassService(ClassService classService) {
		this.classService = classService;
	}

	public ActionForward dormDistributionStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		HttpSession session = request.getSession();
		ActionMessages messages = new ActionMessages();
		Account account = null;
		if (session.getAttribute("accountPerson") != null) {
			String schoolId = "0002";
			List collegeclassList = classService.getGzClassList(schoolId);

			request.setAttribute("collegeclassList", collegeclassList);

			account = (Account) session.getAttribute("accountPerson");
			String stuemp_no = account.getPerson().getPersonCode();
			List ClassStudentCount = dormitoryService.getGzClassStudentCount();
			request.setAttribute("ClassStudentCount", ClassStudentCount);

			List ClassDormitoryStatistic = dormitoryService
					.getGzClassDormitoryStatistic(stuemp_no);
			request.setAttribute("ClassDormitoryStatistic",
					ClassDormitoryStatistic);

		} else {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.loginFirstornotass"));
			saveErrors(request, messages);
			return mapping.findForward("dormDistributionStatistic");
		}

		return mapping.findForward("dormDistributionStatistic");
	}

	public ActionForward dormDistribution(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		ActionMessages messages = new ActionMessages();
		try {
			HttpSession session = request.getSession();
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String stuemp_no = account.getPerson().getPersonCode();
				dormitoryService.saveGzDormDistribution(stuemp_no);
				// Ñ§Éú·Ö°à
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormDistribution.rss", "1"));
				saveErrors(request, messages);
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"classAlert.loginFirstornotass"));
				saveErrors(request, messages);
				return dormDistributionStatistic(mapping, form, request,
						response);
			}

		} catch (StudentAlreadyInDormException e) {
			// e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.studentalreadyindorm"));
			saveErrors(request, messages);
			return dormDistributionStatistic(mapping, form, request, response);
		} catch (DormitoryNotEnoughException e) {
			// e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.dormitorynotenough"));
			saveErrors(request, messages);
			return dormDistributionStatistic(mapping, form, request, response);
		} catch (Exception e) {
			// e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.error"));
			saveErrors(request, messages);
			e.printStackTrace();
			return dormDistributionStatistic(mapping, form, request, response);

		}
		return mapping.findForward("dormDistributionSuccess");

	}

}
