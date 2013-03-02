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
 * 某一台POS机的消费情况统计
 * 
 * @author Administrator
 * 
 */
public class ViewConsumeStatByPosAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
	
		DynaActionForm consumebyposform = (DynaActionForm)form;
		consumebyposform.set("statType", "".equals(consumebyposform.getString("statType"))?"bydate":consumebyposform.getString("statType"));
		consumebyposform.set("querytype", "".equals(consumebyposform.getString("querytype"))?"":consumebyposform.getString("querytype"));
		consumebyposform.set("showType", "".equals(consumebyposform.getString("showType"))?"line":consumebyposform.getString("showType"));
		consumebyposform.set("posid", "".equals(consumebyposform.getString("posid"))?"":consumebyposform.getString("posid"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		consumebyposform.set("consumestatbypos_begindate", "".equals(consumebyposform.getString("consumestatbypos_begindate"))?bgdate:consumebyposform.getString("consumestatbypos_begindate"));
		consumebyposform.set("consumestatbypos_enddate", "".equals(consumebyposform.getString("consumestatbypos_enddate"))?eddate:consumebyposform.getString("consumestatbypos_enddate"));
		
		return mapping.findForward("portlet.advquery.consumestatbypos.view");
	}

}
