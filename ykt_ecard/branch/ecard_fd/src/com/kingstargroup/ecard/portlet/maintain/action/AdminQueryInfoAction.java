package com.kingstargroup.ecard.portlet.maintain.action;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.MaintainUtil;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.ParamUtil;

public class AdminQueryInfoAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		try {

			String status = "0";
			String type = "";
			List statusList = new ArrayList();

			statusList = MaintainUtil.getMaintainType("002");

			List MaintainType = new ArrayList();

			MaintainType = MaintainUtil.getMaintainType("001");

			String userId = (String) req.getSession().getAttribute(
					WebKeys.USER_ID);
			
			int page = ParamUtil.get(req, "page", 0);
			/*ResultPage curpage = MaintainUtil.adminQry(userId, status, type,
					page, EcardConstants.LIST_MORE_SIZE);*/
			
			req.setAttribute("statusList", statusList);
			req.setAttribute("MaintainType", MaintainType);
			/*req.setAttribute("curpage", curpage);*/
			
			return mapping.findForward("portlet.maintain.admin");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}
}
