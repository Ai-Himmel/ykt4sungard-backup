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
public class ShopBrasDetailListAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		String begindate = ParamUtil.getString(req, "bras_begindate");
		String enddate = ParamUtil.getString(req, "bras_enddate");
		String refno = ParamUtil.getString(req, "refno");
		String stuempno = ParamUtil.getString(req, "stuempno");	
		String custname = ParamUtil.getString(req, "custname");		
		String opaccno =  ParamUtil.getString(req, "oppaccno");
		String opaccname =  ParamUtil.getString(req, "oppaccname");
		String status = ParamUtil.getString(req, "status");
		String brastype =  ParamUtil.getString(req, "brastype");


		if(begindate.length()!=10||enddate.length()!=10){
			SessionErrors.add(req, EcardConstants.DATE_NOT_SELECTED);
			return mapping.findForward("portlet.shopbrasdetail.view");
		}
		
		
		begindate = begindate.substring(0,4)+begindate.substring(5,7)+begindate.substring(8,10);
		enddate = enddate.substring(0,4)+enddate.substring(5,7)+enddate.substring(8,10);

		List result = null;
		try {
			result = ShopServiceUtil.getShopBrasDetailList(begindate, enddate,refno,stuempno,custname, opaccno, opaccname,status,brastype);
		}catch (BccBgInfoException e) {
			SessionErrors.add(req,e.getClass().getName(),e);
		}
		catch (Exception e) {
			SessionErrors.add(req,e.getClass().getName(),e);		
			e.printStackTrace();
		}
		req.setAttribute("shopbrasresult", result);
		return mapping.findForward("portlet.shopbrasdetail.view");
	
	}
}
