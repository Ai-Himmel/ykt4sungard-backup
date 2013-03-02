package com.kingstargroup.ecard.portlet.losecard.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.losecard.service.LoseCardServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.SessionErrors;

public class QueryResultAction extends Action {

	/**
	 * “≈ ßø®π‹¿Ì
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm lossgetform = (DynaActionForm)form;
		String beginDate = lossgetform.getString("beginDate");
		String endDate = lossgetform.getString("endDate");
		String custName = lossgetform.getString("custName");
		String stuempNO = lossgetform.getString("stuempNO");
		String lossCardStatus11 = lossgetform.getString("lossCardStatus");
		String cardShowNo = lossgetform.getString("cardShowNo");
		
		List lossCardStatus = LoseCardServiceUtil.getDictListBy(160);
		request.setAttribute("lossCardStatus", lossCardStatus);
		request.setAttribute("beginDate", beginDate);
		request.setAttribute("endDate", endDate);
		request.setAttribute("custName", custName);
		request.setAttribute("stuempNO", stuempNO);
		//request.setAttribute("lossCardStatus", lossCardStatus);
		request.setAttribute("cardShowNo", cardShowNo);
		if ((DateUtil.formatStr2Date(endDate)!=0)||(DateUtil.formatStr2Date(beginDate)!=0)){
			SessionErrors.add(request, EcardConstants.LOSECARD_DATAFORMATERROR);	
			return mapping.findForward("portlet.losecard.query.queryresult");
		}
		
		if (DateUtil.dateCompare(beginDate,endDate)!=0){
			SessionErrors.add(request, EcardConstants.LOSECARD_DATACOMERROR);
			return mapping.findForward("portlet.losecard.query.queryresult");
		}
		
		String shopCode = null;
		try{
			long userId = PortalUtil.getUserId(request);
			if (userId==0){
				SessionErrors.add(request, EcardConstants.LOSECARD_NOLOGIN);
				return mapping.findForward("portlet.losecard.shop.view");
			}
			
			User user = null;
			user = UserServiceUtil.getUserById(userId);
			shopCode = user.getScreenName();
		}catch (Exception e){
			throw new PortalException(e);
		}
		
		List result = LoseCardServiceUtil.getLossCardInfo(shopCode, beginDate, endDate, 0, cardShowNo, stuempNO, custName,lossCardStatus11);
		request.setAttribute("result", result);
		return mapping.findForward("portlet.losecard.query.queryresult");
	}

}
