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
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.hibernate.util.TradeDetailUtil;
import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.kingstargroup.ecard.portlet.distribution.service.CustomerLocalServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.SessionErrors;

public class CheckAttQueryResultAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			String beginDate = com.liferay.portal.kernel.util.StringUtil.replace(com.liferay.portal.kernel.util.ParamUtil.get(req, "gbeginDate", ""), '/', "");
			String endDate = com.liferay.portal.kernel.util.StringUtil.replace(com.liferay.portal.kernel.util.ParamUtil.get(req, "gendDate", ""), '/', "");
			int defDay= Integer.parseInt(KSConfiguration.getInstance().getProperty("def_days_num", "0"));
			if (DateUtil.diffDate(beginDate, endDate)>defDay){
				//req.setAttribute(PageContext.EXCEPTION, "流水查询最大期限为60天");
				SessionErrors.add(req, EcardConstants.DETAIL_QUERY_DAYS_NUM);
				return mapping.findForward("portlet.checkattquery.query.result");
			}
			long userId = PortalUtil.getUserId(req);
			User user = null;
			user = UserServiceUtil.getUserById(userId);
		    String stuempNo = user.getScreenName();
		    
		    TCustomer tcustomer = CustomerLocalServiceUtil.getCustomerByStuempno(stuempNo);
		    int custId = Integer.parseInt(tcustomer.getCustid().toString());
			//int page = ParamUtil.get(req, "page", 0);			
			req.setAttribute("result", CardServiceUtil.getCheckAttSerial(beginDate, endDate, custId));
			return mapping.findForward("portlet.checkattquery.query.result");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}
}
