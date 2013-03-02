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
 * 个商户营业情况对比
 * @author Administrator
 *
 */
public class ViewShopCompareAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
				ActionForm form, 
				HttpServletRequest request, 
				HttpServletResponse response) throws Exception {
		DynaActionForm shopcompareform = (DynaActionForm)form;
		shopcompareform.set("statType", "".equals(shopcompareform.getString("statType"))?"bydate":shopcompareform.getString("statType"));
		shopcompareform.set("querytype", "".equals(shopcompareform.getString("querytype"))?"":shopcompareform.getString("querytype"));
		shopcompareform.set("showType", "".equals(shopcompareform.getString("showType"))?"bar":shopcompareform.getString("showType"));
		
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		shopcompareform.set("shopcompare_begindate", "".equals(shopcompareform.getString("shopcompare_begindate"))?bgdate:shopcompareform.getString("shopcompare_begindate"));
		shopcompareform.set("shopcompare_enddate", "".equals(shopcompareform.getString("shopcompare_enddate"))?eddate:shopcompareform.getString("shopcompare_enddate"));
		
		return mapping.findForward("portlet.advquery.shopcompare.view");
	}
}
