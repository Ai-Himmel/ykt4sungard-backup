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

import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;

/**
 * 整个单位卡户帐务变动情况
 * @author Administrator
 *
 */
public class ViewDepAccountStatAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		// TODO 整个单位卡户帐务变动情况excute
		DynaActionForm deptaccountform = (DynaActionForm)form;
		deptaccountform.set("statType", "".equals(deptaccountform.getString("statType"))?"bydate":deptaccountform.getString("statType"));
		deptaccountform.set("querytype", "".equals(deptaccountform.getString("querytype"))?"":deptaccountform.getString("querytype"));
		deptaccountform.set("showType", "".equals(deptaccountform.getString("showType"))?"line":deptaccountform.getString("showType"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		deptaccountform.set("deptaccount_begindate", "".equals(deptaccountform.getString("deptaccount_begindate"))?bgdate:deptaccountform.getString("deptaccount_begindate"));
		deptaccountform.set("deptaccount_enddate", "".equals(deptaccountform.getString("deptaccount_enddate"))?eddate:deptaccountform.getString("deptaccount_enddate"));
		List deptList = AdvqueryServiceUtil.getDeptList();
		request.setAttribute("deptList", deptList);
		return mapping.findForward("portlet.advquery.deptaccount.view");
	}
}
