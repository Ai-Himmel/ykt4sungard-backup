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
 * �̻������
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
		//��ѯ�����ڷ�Χ
		private StringBuffer dateRange = new StringBuffer(200);
		private String statType;
		private String beginDate;
		private String endDate;
		private String level;
		
		//�̻�
		private String storeLimitString = "";
		private String operCode;
		
		ActionServlet servlet = QueryShopReportAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//ͳ�����ͣ��£��죬����
			statType = request.getParameter("statType");
			//��ʼ����
			beginDate = request.getParameter("begindate");
			//��������
			endDate = request.getParameter("enddate");
			operCode = request.getParameter("operCode");
			level = request.getParameter("level");
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			setInit(request);

			if (("".equals(ParamUtil.getString(request, "storeLimitString"))||(null==ParamUtil.getString(request, "storeLimitString")))){
				request.setAttribute("errorcont",new String("��ѡ���̻���"));
				return mapping.findForward("errortest");
			}
			if (new GetQueryConListDAO().isShopOwner(operCode)){
				storeLimitString = '('+ParamUtil.getString(request, "storeLimitString")+')';
			}else{
				try {
					storeLimitString = '('+new GetQueryConListDAO().getCompareShopList(ParamUtil.getString(request, "storeLimitString"),operCode)+')';				
				} catch (Exception e) {
					e.printStackTrace();
					request.setAttribute("errorcont",new String("��ѡ������в���Ȩ�޵��̻���"));
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
