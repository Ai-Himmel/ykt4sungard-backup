package com.liferay.portal.term.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.hibernate.customer.TCifCustomer;
import com.kingstargroup.ecard.hibernate.util.CustomerUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;

public class TermRegisterAction  extends PortletAction {
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		
		HttpSession ses = req.getSession();
		String userId = ses.getAttribute(WebKeys.USER_ID).toString();
		TCifCustomer cust = CustomerUtil.getCustomerByStuempNo(userId);
		List result  = CustomerUtil.getTermRegister(cust.getCutId());
		req.setAttribute("cust",cust);
		req.setAttribute("result",result);
		return mapping.findForward("portlet.ecardtransaction.termregister");
		
		
	}

}
