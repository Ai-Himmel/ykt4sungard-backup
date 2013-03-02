package com.kingstargroup.ecard.portlet.advquery.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.util.DateUtil;

public class ViewQueryCardOpenLoseBackAction extends Action {
	
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {		
	DynaActionForm     cardopenlosebackform =  (DynaActionForm)form;
	String enddate = DateUtil.getNow("yyyy-MM-dd");
	String begindate = DateUtil.getNewTimes(enddate, -2592000, "yyyy-MM-dd");
	cardopenlosebackform.set("openloseback_begindate", "".equals(cardopenlosebackform.getString("openloseback_begindate"))?begindate:cardopenlosebackform.get("openloseback_begindate"));
	cardopenlosebackform.set("openloseback_enddate", "".equals(cardopenlosebackform.getString("openloseback_enddate"))?enddate:cardopenlosebackform.get("openloseback_enddate"));
	cardopenlosebackform.set("querytype", "".equals(cardopenlosebackform.getString("querytype"))?"":cardopenlosebackform.getString("querytype"));
	cardopenlosebackform.set("showType", "".equals(cardopenlosebackform.getString("showType"))?"line":cardopenlosebackform.getString("showType"));
	cardopenlosebackform.set("statType", "".equals(cardopenlosebackform.getString("statType"))?"bydate":cardopenlosebackform.getString("statType"));
	return mapping.findForward("portlet.advquery.cardopenloseback.view");
	}

}
