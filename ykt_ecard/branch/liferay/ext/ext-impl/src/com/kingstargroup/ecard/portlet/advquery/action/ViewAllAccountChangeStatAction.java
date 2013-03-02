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
 * @author Administrator
 *
 */
public class ViewAllAccountChangeStatAction extends Action{

	/**
	 * 整体帐务情况变化统计：充值，消费，押金
	 */
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		DynaActionForm allaccountform = (DynaActionForm)form;
		allaccountform.set("statType", "".equals(allaccountform.getString("statType"))?"bydate":allaccountform.getString("statType"));
		allaccountform.set("querytype", "".equals(allaccountform.getString("querytype"))?"":allaccountform.getString("querytype"));
		allaccountform.set("showType", "".equals(allaccountform.getString("showType"))?"line":allaccountform.getString("showType"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		allaccountform.set("allaccount_begindate", "".equals(allaccountform.getString("allaccount_begindate"))?bgdate:allaccountform.getString("allaccount_begindate"));
		allaccountform.set("allaccount_enddate", "".equals(allaccountform.getString("allaccount_enddate"))?eddate:allaccountform.getString("allaccount_enddate"));
		
		return mapping.findForward("portlet.advquery.allaccount.view");
	}
	
}

