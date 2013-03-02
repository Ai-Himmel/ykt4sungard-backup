/**
 * 
 */
package com.kingstargroup.ecard.portlet.card.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.CardUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.GetterUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ProcessCardLostAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-8  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ProcessCardLostAction extends PortletAction {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			String cutId = GetterUtil.get((String)req.getSession().getAttribute(WebKeys.USER_ID), StringPool.BLANK);
			String cardId = ParamUtil.getString(req, "cardId");
			CardUtil.processLostCard(cutId, cardId);
		} catch (PortalException pe) {
			SessionErrors.add(req, pe.getClass().getName());
		}
		return mapping.findForward("portlet.ecardtransaction.view_info");
	}

}
