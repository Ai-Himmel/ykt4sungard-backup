/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.util.DateUtil;
import com.liferay.portal.struts.PortletAction;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:ViewSavingSortStatAction.java
 * Description: 
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建               2009-10-21  何林青    
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class ViewTotleSavingStatAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		DynaActionForm totsavingform = (DynaActionForm)form;
		totsavingform.set("statType", "".equals(totsavingform.getString("statType"))?"bydate":totsavingform.getString("statType"));
		totsavingform.set("querytype", "".equals(totsavingform.getString("querytype"))?"":totsavingform.getString("querytype"));
		totsavingform.set("showType", "".equals(totsavingform.getString("showType"))?"line":totsavingform.getString("showType"));
		totsavingform.set("moneyornum", "".equals(totsavingform.getString("moneyornum"))?"money":totsavingform.getString("moneyornum"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		totsavingform.set("totlesaving_begindate", "".equals(totsavingform.getString("totlesaving_begindate"))?bgdate:totsavingform.getString("totlesaving_begindate"));
		totsavingform.set("totlesaving_enddate", "".equals(totsavingform.getString("totlesaving_enddate"))?eddate:totsavingform.getString("totlesaving_enddate"));
		
		return mapping.findForward("portlet.advquery.totlesaving.view");
	}
}
