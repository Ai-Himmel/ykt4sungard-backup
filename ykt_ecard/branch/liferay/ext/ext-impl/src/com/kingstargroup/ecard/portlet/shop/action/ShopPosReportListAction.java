package com.kingstargroup.ecard.portlet.shop.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.BccBgInfoException;
import com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

public class ShopPosReportListAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		String shopid = ParamUtil.getString(req, "shopid");
		String begindate = ParamUtil.getString(req, "shopad_begindate");
		String enddate = ParamUtil.getString(req, "shopad_enddate");
		String devphyId = ParamUtil.getString(req, "devphyId");
		
		req.setAttribute("shopid", shopid);
		req.setAttribute("shopad_begindate", begindate);
		req.setAttribute("shopad_enddate", enddate);
		req.setAttribute("devphyId", devphyId);
		if("".equals(shopid)){
			SessionErrors.add(req, EcardConstants.SHOPID_NOT_SELECTED);
			return mapping.findForward("portlet.shopposreport.view");
		}
		if(begindate.length()==0||enddate.length()==0){
			SessionErrors.add(req, EcardConstants.DATE_NOT_SELECTED);
			return mapping.findForward("portlet.shopposreport.view");
		}
		
		
		int intshopid = Integer.parseInt(shopid);
		begindate = begindate.substring(0,4)+begindate.substring(5,7)+begindate.substring(8,10);
		enddate = enddate.substring(0,4)+enddate.substring(5,7)+enddate.substring(8,10);
		if(DateUtil.checkIntervalTime(begindate+"000000", enddate+"000000", 5184000)<0){
			//³¬¹ý
			SessionErrors.add(req, EcardConstants.TIME_PERIOD_TOO_LONG);
			return mapping.findForward("portlet.shopposreport.view");
		}
		List result = null;
		try {
			result = ShopServiceUtil.getShopPosDetailList(intshopid, begindate, enddate, devphyId);
		}catch (BccBgInfoException e) {
			SessionErrors.add(req,e.getClass().getName(),e);
		}
		catch (Exception e) {
			SessionErrors.add(req,e.getClass().getName(),e);		
			//e.printStackTrace();
		}
		req.setAttribute("result", result);
		return mapping.findForward("portlet.shopposreport.view");
	
	}
}
