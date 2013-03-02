package com.kingstargroup.ecard.portlet.shop.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.BccBgInfoException;
import com.kingstargroup.ecard.exceptions.BccException;
import com.kingstargroup.ecard.exceptions.BccResultToomuchException;
import com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ViewRuleAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-21  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ShopAccountDetailListAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		String shopid = ParamUtil.getString(req, "shopid");
		String begindate = ParamUtil.getString(req, "shopad_begindate");
		String enddate = ParamUtil.getString(req, "shopad_enddate");
		String deviceid = ParamUtil.getString(req, "deviceid");
		if("".equals(deviceid)){
			deviceid="0";
		}
		req.setAttribute("shopid", shopid);
		req.setAttribute("shopad_begindate", begindate);
		req.setAttribute("shopad_enddate", enddate);
		req.setAttribute("deviceid", deviceid);
		if("".equals(shopid)){
			SessionErrors.add(req, EcardConstants.SHOPID_NOT_SELECTED);
			return mapping.findForward("portlet.shopaccountdetail.view");
		}
		if(begindate.length()==0||enddate.length()==0){
			SessionErrors.add(req, EcardConstants.DATE_NOT_SELECTED);
			return mapping.findForward("portlet.shopaccountdetail.view");
		}
		
		
		int intshopid = Integer.parseInt(shopid);
		begindate = begindate.substring(0,4)+begindate.substring(5,7)+begindate.substring(8,10);
		enddate = enddate.substring(0,4)+enddate.substring(5,7)+enddate.substring(8,10);
		if(DateUtil.checkIntervalTime(begindate+"000000", enddate+"000000", 5184000)<0){
			//超过
			SessionErrors.add(req, EcardConstants.TIME_PERIOD_TOO_LONG);
			return mapping.findForward("portlet.shopaccountdetail.view");
		}
		int termid = Integer.parseInt(deviceid);
		List result = null;
		try {
			result = ShopServiceUtil.getShopAccountDetailList(intshopid, begindate, enddate, termid);
		}catch (BccBgInfoException e) {
			SessionErrors.add(req,e.getClass().getName(),e);
		}
		catch (Exception e) {
			SessionErrors.add(req,e.getClass().getName(),e);		
			//e.printStackTrace();
		}
		req.setAttribute("shopadresult", result);
		return mapping.findForward("portlet.shopaccountdetail.view");
	
	}
}
