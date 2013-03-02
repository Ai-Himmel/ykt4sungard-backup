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
 * <br>
 * ===================================<br>
 *     Xiao Qi  2005-9-26  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class QueryDetailResultAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			String beginDate = com.liferay.portal.kernel.util.StringUtil.replace(com.liferay.portal.kernel.util.ParamUtil.get(req, "beginDate", ""), '/', "");
			String endDate = com.liferay.portal.kernel.util.StringUtil.replace(com.liferay.portal.kernel.util.ParamUtil.get(req, "endDate", ""), '/', "");
			
			if("".equals(beginDate)||"".equals(endDate)){
				SessionErrors.add(req, EcardConstants.DATE_NOT_SELECTED);
				return mapping.findForward("portlet.ecardtransaction.querydetail");
			}
			
			int defDay= Integer.parseInt(KSConfiguration.getInstance().getProperty("def_days_num", "0"));
			if (DateUtil.diffDate(beginDate, endDate)>defDay){
				//req.setAttribute(PageContext.EXCEPTION, "流水查询最大期限为60天");
				SessionErrors.add(req, EcardConstants.DETAIL_QUERY_DAYS_NUM);
				return mapping.findForward("portlet.ecardtransaction.querydetail");
			}
			String serialType = ParamUtil.getString(req, "serialType");
			String cardId = ParamUtil.getString(req, "cardId");
			//1,消费流水，2考勤流水,3体锻流水
			if ("1".equals(serialType)){
				req.setAttribute("detailList", CardServiceUtil.getcomsumtradeSerial(beginDate, endDate, Integer.parseInt(cardId)));
				return mapping.findForward("portlet.ecardtransaction.querydetail");				
			}else if ("2".equals(serialType)){
				req.setAttribute("checkattDetailList", CardServiceUtil.getCheckAttSerial(beginDate, endDate, Integer.parseInt(cardId)));
				return mapping.findForward("portlet.ecardtransaction.querydetail");
			}else if ("3".equals(serialType)){
				req.setAttribute("checkatt_tdDetailList", CardServiceUtil.getCheckAttSerial_td(beginDate, endDate, Integer.parseInt(cardId)));
				return mapping.findForward("portlet.ecardtransaction.querydetail");
			}else{				
				SessionErrors.add(req, EcardConstants.DETAIL_QUERY_TYPE_SELECT);
				return mapping.findForward("portlet.ecardtransaction.querydetail");
			}
		} catch (PortalException pe) {
			SessionErrors.add(req,pe.getClass().getName(),pe);	
			return mapping.findForward("portlet.ecardtransaction.querydetail");
		}
	}
	
	protected boolean isCheckMethodOnProcessAction() {
		return _CHECK_METHOD_ON_PROCESS_ACTION;
		}

	private static final boolean _CHECK_METHOD_ON_PROCESS_ACTION = false;
}
