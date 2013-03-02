package com.kingstargroup.ecard.portlet.losecard.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.losecard.service.LoseCardServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.SessionErrors;

public class StatResultAction extends Action {

	/**
	 * 遗失卡管理,统计信息
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm lossgetform = (DynaActionForm)form;
		String shopCode = null;
		//String shopName = null;
		try{
			long userId = PortalUtil.getUserId(request);
			if (userId==0){
				SessionErrors.add(request, EcardConstants.LOSECARD_NOLOGIN);
				return mapping.findForward("portlet.losecard.reg");
			}
			
			User user = null;
			user = UserServiceUtil.getUserById(userId);
			shopCode = user.getScreenName();
		}catch (Exception e){
			request.setAttribute(PageContext.EXCEPTION, e);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
		String beginDate = lossgetform.getString("beginDate");
		String endDate = lossgetform.getString("endDate");
		
		request.setAttribute("beginDate", beginDate);
		request.setAttribute("endDate", endDate);
		if ((DateUtil.formatStr2Date(endDate)!=0)||(DateUtil.formatStr2Date(beginDate)!=0)){
			SessionErrors.add(request, EcardConstants.LOSECARD_DATAFORMATERROR);	
			return mapping.findForward("portlet.losecard.stat.statresult");
		}
		
		if (DateUtil.dateCompare(beginDate,endDate)!=0){
			SessionErrors.add(request, EcardConstants.LOSECARD_DATACOMERROR);
			return mapping.findForward("portlet.losecard.stat.statresult");
		}
		/*
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
		*/
		List result = null;
		if ("admin".equals(shopCode.toLowerCase())){
			result = LoseCardServiceUtil.getLossStatList(beginDate, endDate, "");
		}else{
			result = LoseCardServiceUtil.getLossStatList(beginDate, endDate, shopCode);
		}
		
		request.setAttribute("result", result);
		return mapping.findForward("portlet.losecard.stat.statresult");
	}

}
