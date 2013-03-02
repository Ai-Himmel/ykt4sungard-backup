package com.kingstargroup.advquery.struts.actions;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.hibernate.util.ReportShopBalanceUtil;
import com.kingstargroup.advquery.hibernate.util.UserUtil;


public class ShopAccountQueryResultAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		    ActionForward forward = doQueryResult(mapping,form,request,response);
			return forward;
	}
	
	private ActionForward doQueryResult(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response){
		HttpSession sess=request.getSession();
		String username =(String)sess.getAttribute("username");
        //开始日期
		String beginDate = request.getParameter("begindate");
		//结束日期
		String endDate = request.getParameter("enddate");
		beginDate = DateUtilExtend.formatDate2(beginDate);
		endDate = DateUtilExtend.formatDate2(endDate);
		
		String shopid="";
		shopid = UserUtil.getStoreLimitString(username);
		StringBuffer dateRange= new StringBuffer(200);
		dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
		.append(beginDate).append("-").append(endDate);
		
		List result = ReportShopBalanceUtil.getShopAccountQueryResult(beginDate,endDate,shopid);
		request.setAttribute("dateRange", dateRange.toString());
		request.setAttribute("result", result);
	    return (mapping.findForward("shopaccount_queryresult"));
	}

	

}
