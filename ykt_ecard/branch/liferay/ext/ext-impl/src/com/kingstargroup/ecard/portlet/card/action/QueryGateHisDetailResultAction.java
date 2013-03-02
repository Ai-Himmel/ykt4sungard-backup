/**
 * 
 */
package com.kingstargroup.ecard.portlet.card.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: QueryDetailResultAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-26  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class QueryGateHisDetailResultAction extends PortletAction {
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
			
			String beginDate = StringUtil.replace(ParamUtil.get(req, "gbeginDate", ""), '/', "");
			String endDate = StringUtil.replace(ParamUtil.get(req, "gendDate", ""), '/', "");
//			String cardId = ParamUtil.getString(req, "cardId");

//			String stuempNo = (String)req.getSession().getAttribute(WebKeys.USER_ID);
//			TCifCustomer cust = AccountUtil.getCifCustomerbyStuempNo(stuempNo);
//			String cardNos = "0";
//			if(cust!=null){
//				cardNos = AccountUtil.cardNoString(cust.getCutId().intValue());
//			}
			int page = ParamUtil.get(req, "page", 0);			
			req.setAttribute("result", CardServiceUtil.getCKHisTradeDetail(stuempNo, beginDate, endDate, page));
			req.setAttribute("resultsize", String.valueOf(CardServiceUtil.getCKHisTradeDetailSize(stuempNo, beginDate, endDate, page)));
			return mapping.findForward("portlet.ecardtransaction.gatehisquerydetail_result");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}
}
