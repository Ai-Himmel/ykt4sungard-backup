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

import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.TradeDetailUtil;
import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: QueryDetailResultAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½   ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½   ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½     ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½<br>
 * ===================================<br>
 *  ï¿½ï¿½ï¿½ï¿½    Xiao Qi  2005-9-26  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CheckAttSerialQViewAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		/*
		try {
			String beginDate = com.liferay.portal.kernel.util.StringUtil.replace(com.liferay.portal.kernel.util.ParamUtil.get(req, "beginDate", ""), '/', "");
			String endDate = com.liferay.portal.kernel.util.StringUtil.replace(com.liferay.portal.kernel.util.ParamUtil.get(req, "endDate", ""), '/', "");
			int defDay= Integer.parseInt(KSConfiguration.getInstance().getProperty("def_days_num", "0"));
			if (DateUtil.diffDate(beginDate, endDate)>defDay){
				//req.setAttribute(PageContext.EXCEPTION, "Á÷Ë®²éÑ¯×î´óÆÚÏÞÎª60Ìì");
				SessionErrors.add(req, EcardConstants.DETAIL_QUERY_DAYS_NUM);
				return mapping.findForward("portlet.ecardtransaction.querydetail_max");
			}
			String cardId = ParamUtil.getString(req, "cardId");
			int page = ParamUtil.get(req, "page", 0);			
			req.setAttribute("result", CardServiceUtil.getTradeDetail(cardId, beginDate, endDate, page));
			return mapping.findForward("portlet.checkattquery.query.view");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
		*/
		return mapping.findForward("portlet.checkattquery.query.view");
	}
}
