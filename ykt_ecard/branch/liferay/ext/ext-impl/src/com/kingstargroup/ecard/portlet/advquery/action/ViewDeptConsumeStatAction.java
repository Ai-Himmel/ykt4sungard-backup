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
 * 单位所有持卡人消费情况统计
 * @author Administrator
 *
 */
public class ViewDeptConsumeStatAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		// TODO 单位所有持卡人消费情况统计excute
		DynaActionForm deptconsumeform = (DynaActionForm)form;
		deptconsumeform.set("statType", "".equals(deptconsumeform.getString("statType"))?"bydate":deptconsumeform.getString("statType"));
		deptconsumeform.set("querytype", "".equals(deptconsumeform.getString("querytype"))?"":deptconsumeform.getString("querytype"));
		deptconsumeform.set("showType", "".equals(deptconsumeform.getString("showType"))?"line":deptconsumeform.getString("showType"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		deptconsumeform.set("deptconsume_begindate", "".equals(deptconsumeform.getString("deptconsume_begindate"))?bgdate:deptconsumeform.getString("deptconsume_begindate"));
		deptconsumeform.set("deptconsume_enddate", "".equals(deptconsumeform.getString("deptconsume_enddate"))?eddate:deptconsumeform.getString("deptconsume_enddate"));
		List deptList = AdvqueryServiceUtil.getDeptList();
		request.setAttribute("deptList", deptList);
		return mapping.findForward("portlet.advquery.deptconsume.view");
	}
}
