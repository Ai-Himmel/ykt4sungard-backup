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
import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
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
			Long realUserId = (Long) req.getSession().getAttribute(
					WebKeys.USER_ID);
			User myuser = UserLocalServiceUtil.getUserById(realUserId);
			String stuempNo = myuser.getScreenName();
			String cardId = com.liferay.portal.kernel.util.ParamUtil.getString(req, "cardId");
			CardServiceUtil.processLostCard(stuempNo, cardId);
			
			//根据卡号取得是否有遗失卡信息
		} catch (PortalException pe) {
			SessionErrors.add(req, pe.getClass().getName());
		}
		return mapping.findForward("portlet.ecardtransaction.view_info");
	}

}
