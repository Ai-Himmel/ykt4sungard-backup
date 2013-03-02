package com.kingstargroup.ecard.portlet.cardlist.action;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.CardListUtil;
import com.kingstargroup.ecard.hibernate.util.InformationUtil;
import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.kingstargroup.ecard.portlet.cardlist.service.CardListServiceUtil;
import com.kingstargroup.ecard.portlet.information.service.EcardInformationServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ViewRuleAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-21  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ViewListAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {
		String id = req.getParameter("id");
		int page = ParamUtil.get(req, "page", 0);
		try {
			if (!req.getWindowState().equals(WindowState.MAXIMIZED)) {
				req.setAttribute("result", EcardInformationServiceUtil.list(0, EcardConstants.INFORMATION_CARDLIST_TYPE, EcardConstants.DEFAULT_RESULT_SIZE));
				return mapping.findForward("portlet.ecardlist.view");
			} else {
				if (id == null) {
					req.setAttribute("result", EcardInformationServiceUtil.list(page, EcardConstants.INFORMATION_CARDLIST_TYPE, EcardConstants.LIST_MORE_SIZE));
					return mapping.findForward("portlet.ecardlist.viewMore");
				}
				else {
					req.setAttribute("result", CardListServiceUtil.getInfoById(id));
					return mapping.findForward("portlet.ecardlist.viewlist");
				}
			}
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}
}
