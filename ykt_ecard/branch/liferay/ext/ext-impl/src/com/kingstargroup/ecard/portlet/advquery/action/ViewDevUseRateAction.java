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
 * 终端设备使用率
 * 
 * @author Administrator
 * 
 */
public class ViewDevUseRateAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm devuserateform = (DynaActionForm)form;
		devuserateform.set("statType", "".equals(devuserateform.getString("statType"))?"bydate":devuserateform.getString("statType"));
		devuserateform.set("querytype", "".equals(devuserateform.getString("querytype"))?"":devuserateform.getString("querytype"));
		devuserateform.set("showType", "".equals(devuserateform.getString("showType"))?"line":devuserateform.getString("showType"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		devuserateform.set("devuserate_begindate", "".equals(devuserateform.getString("devuserate_begindate"))?bgdate:devuserateform.getString("devuserate_begindate"));
		devuserateform.set("devuserate_enddate", "".equals(devuserateform.getString("devuserate_enddate"))?eddate:devuserateform.getString("devuserate_enddate"));
		
		return mapping.findForward("portlet.advquery.devuserate.view");
	}

}
