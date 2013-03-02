package com.kingstargroup.ecard.portlet.advquery.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.util.DateUtil;

public class ViewTransferRateAction extends Action {

	/**
	 * È¦´æ³É¹¦ÂÊ
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm transferform = (DynaActionForm)form;
		transferform.set("statType", "".equals(transferform.getString("statType"))?"bydate":transferform.getString("statType"));
		transferform.set("querytype", "".equals(transferform.getString("querytype"))?"":transferform.getString("querytype"));
		transferform.set("showType", "".equals(transferform.getString("showType"))?"line":transferform.getString("showType"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		transferform.set("transfer_begindate", "".equals(transferform.getString("transfer_begindate"))?bgdate:transferform.getString("transfer_begindate"));
		transferform.set("transfer_enddate", "".equals(transferform.getString("transfer_enddate"))?eddate:transferform.getString("transfer_enddate"));
		
		return mapping.findForward("portlet.advquery.transfer.view");
	}

}
