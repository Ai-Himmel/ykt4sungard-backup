package com.kingstargroup.ecard.portlet.bank.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.hibernate.customer.TCifCustomer;
import com.kingstargroup.ecard.hibernate.util.BankServiceUtil;
import com.kingstargroup.ecard.hibernate.util.CustomerUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.ParamUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

public class EditBankBindAction extends PortletAction {
	/*
	 * (non-Javadoc)
	 * 
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping,
	 *      org.apache.struts.action.ActionForm,
	 *      javax.servlet.http.HttpServletRequest,
	 *      javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		String cmd = ParamUtil.get(req, "cmd", "");
		String stuempno = ParamUtil.get(req, "stuempno", "");
		String bankacc = ParamUtil.get(req, "bankacc", "");
		try {			
			if (isTokenValid(req)) {	
				TCifCustomer tcustomer = CustomerUtil.getCustomerByStuempNo(stuempno);
				if ("update".equals(cmd)) {
					BankServiceUtil.linkBindingOper(tcustomer.getStuempNo(), bankacc, "A");
					req.setAttribute("stuempno", stuempno);
					req.setAttribute("bankacc", bankacc);
					System.out.println("------------"+stuempno);
					System.out.println("------------"+bankacc);
					SessionErrors.add(req, EcardConstants.EDIT_INFO_SUCCESS);
				} else if ("delete".equals(cmd)) {
					BankServiceUtil.linkBindingOper(tcustomer.getStuempNo(), bankacc, "D");
					req.setAttribute("stuempno", stuempno);
					req.setAttribute("bankacc", "");
					SessionErrors.add(req, EcardConstants.DELETE_INFO_FAILED);
				}
			}else{
				req.setAttribute("stuempno", stuempno);
				req.setAttribute("bankacc", bankacc);
			}
			saveToken(req);
			return mapping.findForward("portlet.bankbind.edit");
		}catch (Exception e) {
			e.printStackTrace();
			SessionErrors.add(req,Exception.class.getName(),e.getMessage());		
		} 
		req.setAttribute("stuempno", stuempno);
		req.setAttribute("bankacc", bankacc);
		saveToken(req);
		return mapping.findForward("portlet.bankbind.edit");
	}
}
