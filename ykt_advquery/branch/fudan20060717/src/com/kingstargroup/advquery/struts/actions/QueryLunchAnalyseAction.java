package com.kingstargroup.advquery.struts.actions;

import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionServlet;

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.hibernate.util.LunchUtil;

/**
 * 就餐人员分析
 * @author Administrator
 *
 */
public class QueryLunchAnalyseAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
				ActionForm form, 
				HttpServletRequest request, 
				HttpServletResponse response) throws Exception {
		QueryLunchAnalyseActionExecution exec = new QueryLunchAnalyseActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryLunchAnalyseActionExecution {
		//查询的日期范围
		private StringBuffer dateRange = new StringBuffer(200);
		private String statType;
		private String beginDate;
		private String endDate;
		
		private String operCode;
		
		ActionServlet servlet = QueryLunchAnalyseAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//统计类型，时间段，月
			statType = request.getParameter("statType");
			beginDate = request.getParameter("begindate");
			endDate = request.getParameter("enddate");
			
			operCode = request.getParameter("operCode");
			
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			Map params = setInit(request);
			List result = LunchUtil.getLunchPerson(params);
			/*if (result.isEmpty()){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}*/
			
			request.setAttribute("result",result);
			request.setAttribute("daterange",dateRange.toString());
			
			return mapping.findForward("lunchanalyse_queryresult");
		}
		private Map setInit(HttpServletRequest request){
			Map params = new HashMap();
			params.put("statType", request.getParameter("statType"));
			params.put("dayLimit", request.getParameter("dayLimit"));
			params.put("day", request.getParameter("day"));
			params.put("mealLimit", request.getParameter("mealLimit"));
			params.put("meal", request.getParameter("meal"));
			params.put("moneyLimit", request.getParameter("moneyLimit"));
			params.put("money", request.getParameter("money"));
			params.put("stuempNo", request.getParameter("stuempno"));
			String custName = request.getParameter("custname");
			if(StringUtils.isNotBlank(custName)){
				try {
					custName = URLDecoder.decode(custName,"GBK");
					request.setAttribute("custname", custName);
				} catch (UnsupportedEncodingException e) {
					e.printStackTrace();
				}
	        }
			params.put("custName", custName);
			params.put("cutType", request.getParameter("cuttype"));
			params.put("feeType", request.getParameter("feetype"));
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
	 			session.setAttribute("begindate35d",request.getParameter("begindate"));
				session.setAttribute("enddate35d",request.getParameter("enddate"));
				dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext())).append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));	
	 			session.setAttribute("begindate35m",request.getParameter("begindate"));
				session.setAttribute("enddate35m",request.getParameter("enddate"));
				dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext())).append(beginDate).append("-").append(endDate);
			}
			params.put("beginDate", beginDate);
			params.put("endDate", endDate);
			return params;
		}
	}
}
