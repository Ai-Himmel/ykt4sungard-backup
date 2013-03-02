/**
 * 
 */
package com.kingstargroup.ecard.portlet.bank.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.BccBgInfoException;
import com.kingstargroup.ecard.exceptions.BccException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.portlet.bank.service.BankServiceUtil;
import com.kingstargroup.ecard.portlet.distribution.service.CustomerLocalServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: EditPostponeResultAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-9-28 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class EditAuthBankBindAction extends PortletAction {
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
		String authcode = ParamUtil.get(req, "authcode", "");
		try {			
			if (isTokenValid(req)) {	
				TCustomer tcustomer = CustomerLocalServiceUtil
						.getCustomerByStuempno(stuempno);
				if ("update".equals(cmd)) {
					BankServiceUtil.linkBindingOperWithAuth(tcustomer.getStuempno(), bankacc,authcode, "A");
					req.setAttribute("stuempno", stuempno);
					req.setAttribute("bankacc", bankacc);
					SessionErrors.add(req, EcardConstants.EDIT_INFO_SUCCESS);
				} else if ("delete".equals(cmd)) {
					BankServiceUtil.linkBindingOperWithAuth(tcustomer.getStuempno(), bankacc,authcode, "D");
					req.setAttribute("stuempno", stuempno);
					req.setAttribute("bankacc", "");
					SessionErrors.add(req, EcardConstants.DELETE_INFO_FAILED);
				} else if ("reset".equals(cmd)) {
					BankServiceUtil.linkBindingOperWithAuth(tcustomer.getStuempno(), bankacc,authcode, "R");
					req.setAttribute("stuempno", stuempno);
					req.setAttribute("bankacc", bankacc);
					SessionErrors.add(req, EcardConstants.RESET_INFO_FAILED);
				} 
			}else{
				req.setAttribute("stuempno", stuempno);
				req.setAttribute("bankacc", bankacc);
			}
			saveToken(req);
			return mapping.findForward("portlet.bankbind.edit");
		}catch (BccBgInfoException e) {
			SessionErrors.add(req,e.getClass().getName(),e);
		}catch (BccException e) {
			SessionErrors.add(req,e.getClass().getName(),e);		
		}catch (Exception e) {
			SessionErrors.add(req,e.getClass().getName(),e);		
		} 
		req.setAttribute("stuempno", stuempno);
		req.setAttribute("bankacc", bankacc);
		saveToken(req);
		return mapping.findForward("portlet.bankbind.edit");
	}
}
