/**
 * 
 */
package com.kingstargroup.ecard.portlet.card.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.util.PermissionUtil;
import com.liferay.portal.struts.PortletAction;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ViewQueryUIAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-26  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class GateHisViewQueryUIAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {		
		if (PermissionUtil.hasCardTransactionAdmin(req)) {
			return mapping.findForward("portlet.ecardtransaction.postpone_admin");			
		}
		return mapping.findForward("portlet.ecardtransaction.gatehisquerydetail_max");
	}
}
