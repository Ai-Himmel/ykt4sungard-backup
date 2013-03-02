/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.liferay.portal.util.WebKeys;

/**
 * 各商户营业情况统计
 * 
 * @author Administrator
 * 
 */
public class ViewOneShopAccountStatAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		DynaActionForm oneshopaccountform = (DynaActionForm)form;
		oneshopaccountform.set("statType", "".equals(oneshopaccountform.getString("statType"))?"bydate":oneshopaccountform.getString("statType"));
		oneshopaccountform.set("querytype", "".equals(oneshopaccountform.getString("querytype"))?"":oneshopaccountform.getString("querytype"));
		oneshopaccountform.set("showType", "".equals(oneshopaccountform.getString("showType"))?"line":oneshopaccountform.getString("showType"));
		oneshopaccountform.set("shopid", "".equals(oneshopaccountform.getString("shopid"))?"":oneshopaccountform.getString("shopid"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		oneshopaccountform.set("oneshopaccount_begindate", "".equals(oneshopaccountform.getString("oneshopaccount_begindate"))?bgdate:oneshopaccountform.getString("oneshopaccount_begindate"));
		oneshopaccountform.set("oneshopaccount_enddate", "".equals(oneshopaccountform.getString("oneshopaccount_enddate"))?eddate:oneshopaccountform.getString("oneshopaccount_enddate"));
		Long realUserId = (Long) request.getSession().getAttribute(
				WebKeys.USER_ID);
		List shoplist = ShopServiceUtil.getShopList(realUserId);
		request.setAttribute("shopList", shoplist);
		return mapping.findForward("portlet.advquery.oneshopaccount.view");
	}

}
