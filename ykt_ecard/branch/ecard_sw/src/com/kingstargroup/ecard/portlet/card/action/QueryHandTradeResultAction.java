package com.kingstargroup.ecard.portlet.card.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.HandTradeUtil;
import com.kingstargroup.ecard.hibernate.util.TradeDetailUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringUtil;

public class QueryHandTradeResultAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		
		try {
			
			String beginDate = StringUtil.replace(ParamUtil.get(req, "beginDate", ""), '/', "");
			String endDate = StringUtil.replace(ParamUtil.get(req, "endDate", ""), '/', "");
			String cardId = ParamUtil.getString(req, "cardId");
			int page = ParamUtil.get(req, "page", 0);		
				
			//req.setAttribute("result", TradeDetailUtil.getTradeDetail(cardId, beginDate, endDate, page));//参照这个交易流水做

		    req.setAttribute("result", HandTradeUtil.getHandTrade(cardId, beginDate, endDate));
					
			return mapping.findForward("portlet.ecardtransaction.queryhandtrade_result");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}
