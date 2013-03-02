package com.kingstargroup.advquery.struts.actions;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionServlet;

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.reportshopbalance.ReportShopBalanceDAO;
import com.kingstargroup.advquery.util.ParamUtil;

/**
 * 商户结算表
 * @author Administrator
 *
 */
public class QueryShopReportAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
				ActionForm form, 
				HttpServletRequest request, 
				HttpServletResponse response) throws Exception {
		QueryShopReportActionExecution exec = new QueryShopReportActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryShopReportActionExecution {
		//查询的日期范围
		private StringBuffer dateRange = new StringBuffer(200);
		private String statType;
		private String beginDate;
		private String endDate;
		private String level;
		
		//商户
		private String storeLimitString = "";
		private String operCode;
		
		ActionServlet servlet = QueryShopReportAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//统计类型，月，天，区间
			statType = request.getParameter("statType");
			//开始日期
			beginDate = request.getParameter("begindate");
			//结束日期
			endDate = request.getParameter("enddate");
			operCode = request.getParameter("operCode");
			level = request.getParameter("level");
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			setInit(request);

			if (("".equals(ParamUtil.getString(request, "storeLimitString"))||(null==ParamUtil.getString(request, "storeLimitString")))){
				request.setAttribute("errorcont",new String("请选择商户！"));
				return mapping.findForward("errortest");
			}
			if (new GetQueryConListDAO().isShopOwner(operCode)){
				storeLimitString = '('+ParamUtil.getString(request, "storeLimitString")+')';
			}else{
				try {
					storeLimitString = '('+new GetQueryConListDAO().getCompareShopList(ParamUtil.getString(request, "storeLimitString"),operCode)+')';				
				} catch (Exception e) {
					e.printStackTrace();
					request.setAttribute("errorcont",new String("请选择你具有操作权限的商户！"));
					return mapping.findForward("errortest");
				}
			}
			List result = new ReportShopBalanceDAO().getShopAccountReport(storeLimitString,beginDate,endDate,statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			request.setAttribute("result",result);
			request.setAttribute("daterange",dateRange.toString());
			
			return mapping.findForward("shopreport_queryresult");
		}
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
	 			session.setAttribute("begindate35d",request.getParameter("begindate"));
				session.setAttribute("enddate35d",request.getParameter("enddate"));
				dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
					.append(beginDate).append("-").append(endDate);
				session.setAttribute("level", request.getParameter("level"));
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));	
	 			session.setAttribute("begindate35m",request.getParameter("begindate"));
				session.setAttribute("enddate35m",request.getParameter("enddate"));
				dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
				session.setAttribute("level", request.getParameter("level"));
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate35w",request.getParameter("begindate"));
				session.setAttribute("enddate35w",request.getParameter("enddate"));
				dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
				session.setAttribute("level", request.getParameter("level"));
			} else if ("byday".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
	 			session.setAttribute("begindate35d",request.getParameter("begindate"));
				session.setAttribute("enddate35d",request.getParameter("enddate"));
				dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
					.append(beginDate).append("-").append(endDate);
				session.setAttribute("level", request.getParameter("level"));
			}
		}
	}
}
