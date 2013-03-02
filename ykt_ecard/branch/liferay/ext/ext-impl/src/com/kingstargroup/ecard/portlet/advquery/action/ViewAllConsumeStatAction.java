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
 * 消费情况总体统计
 * 
 * @author Administrator
 * 
 */
public class ViewAllConsumeStatAction extends Action {
	/**
	 * Logger for this class
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm allconsumeform = (DynaActionForm)form;
		allconsumeform.set("statType", "".equals(allconsumeform.getString("statType"))?"bydate":allconsumeform.getString("statType"));
		allconsumeform.set("querytype", "".equals(allconsumeform.getString("querytype"))?"":allconsumeform.getString("querytype"));
		allconsumeform.set("showType", "".equals(allconsumeform.getString("showType"))?"line":allconsumeform.getString("showType"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		allconsumeform.set("allconsume_begindate", "".equals(allconsumeform.getString("allconsume_begindate"))?bgdate:allconsumeform.getString("allconsume_begindate"));
		allconsumeform.set("allconsume_enddate", "".equals(allconsumeform.getString("allconsume_enddate"))?eddate:allconsumeform.getString("allconsume_enddate"));
		
		return mapping.findForward("portlet.advquery.allconsume.view");
	}
}
