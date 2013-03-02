/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.util.DateUtil;

/**
 * 商户整体账户变动情况，营业额，管理费金额
 * 
 * @author Administrator
 * 
 */
public class ViewAllShopAccountStatAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		DynaActionForm allshopaccountform = (DynaActionForm)form;
		allshopaccountform.set("statType", "".equals(allshopaccountform.getString("statType"))?"bydate":allshopaccountform.getString("statType"));
		allshopaccountform.set("querytype", "".equals(allshopaccountform.getString("querytype"))?"":allshopaccountform.getString("querytype"));
		allshopaccountform.set("showType", "".equals(allshopaccountform.getString("showType"))?"line":allshopaccountform.getString("showType"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		allshopaccountform.set("allshopaccount_begindate", "".equals(allshopaccountform.getString("allshopaccount_begindate"))?bgdate:allshopaccountform.getString("allshopaccount_begindate"));
		allshopaccountform.set("allshopaccount_enddate", "".equals(allshopaccountform.getString("allshopaccount_enddate"))?eddate:allshopaccountform.getString("allshopaccount_enddate"));
		
		return mapping.findForward("portlet.advquery.allshopaccount.view");
	}
	
}
