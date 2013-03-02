package com.kingstargroup.ecard.portlet.advquery.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import com.kingstargroup.ecard.util.DateUtil;


public class ViewQueryAccountDtlByCustIdAction extends Action{
	
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res) 
		throws Exception {		
		 
		DynaActionForm  queryaccountdtlform = (DynaActionForm)form;
		String queryaccountdtl_enddate = DateUtil.getNow("yyyy-MM-dd");
		String queryaccountdtl_begindate = DateUtil.getNewTimes(queryaccountdtl_enddate, -2592000, "yyyy-MM-dd");
		queryaccountdtlform.set("queryaccountdtl_begindate", "".equals(queryaccountdtlform.getString("queryaccountdtl_begindate"))?queryaccountdtl_begindate:queryaccountdtlform.get("queryaccountdtl_begindate"));
		queryaccountdtlform.set("queryaccountdtl_enddate", "".equals(queryaccountdtlform.getString("queryaccountdtl_enddate"))?queryaccountdtl_enddate:queryaccountdtlform.get("queryaccountdtl_enddate"));
		queryaccountdtlform.set("custId", "".equals(queryaccountdtlform.getString("custId"))?"":queryaccountdtlform.get("custId"));
		queryaccountdtlform.set("stuempno", "".equals(queryaccountdtlform.getString("stuempno"))?"":queryaccountdtlform.get("stuempno"));
        return mapping.findForward("portlet.advquery.accounttransdtl.view");

	}

}
