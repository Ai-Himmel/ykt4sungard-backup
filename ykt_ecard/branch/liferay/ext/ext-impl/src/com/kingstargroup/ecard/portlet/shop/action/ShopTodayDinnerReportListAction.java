package com.kingstargroup.ecard.portlet.shop.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil;
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
public class ShopTodayDinnerReportListAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		String shopid = ParamUtil.getString(req, "shopid");
		String shoplevel = ParamUtil.getString(req, "shoplevel");
		req.setAttribute("shopid", shopid);
		req.setAttribute("shoplevel", shoplevel);
		if("".equals(shopid)){
			SessionErrors.add(req, EcardConstants.SHOPID_NOT_SELECTED);
			return mapping.findForward("portlet.shoptodayreport.view");
		}

		int intshopid = Integer.parseInt(shopid);
		int intshoplevel = Integer.parseInt(shoplevel);
		List result = null;
		try {
			result = ShopServiceUtil.getShopTodayDinnerReportList(intshopid,intshoplevel);
		} catch (Exception e) {
			SessionErrors.add(req, EcardConstants.ERROR_EXIST,e);		
			e.printStackTrace();
		}
		
		req.setAttribute("shoptodaydinnerresult", result);
		return mapping.findForward("portlet.shoptodayreport.view");
	
	}
}
