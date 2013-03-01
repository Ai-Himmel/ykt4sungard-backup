/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionServlet;

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.customer.TCifCustomer;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.hibernate.util.AccountUtil;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

/**
 * ��������䶯����������ѣ�Ѻ��
 * 
 * @author Administrator
 * 
 */
public class QueryAccountStatByCustIdAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		QueryAccountStatByCustIdActionExecution exec = new QueryAccountStatByCustIdActionExecution();
		return exec.execute(mapping,form,request,response);

	}
	private class QueryAccountStatByCustIdActionExecution {
		private String stuempno;
		//ѧ����
		private String custId;
		//��ʼ����
		private String beginDate;
		//��������
		private String endDate ;
		//��ʾ���ڷ�Χ
		private StringBuffer dateRange = new StringBuffer(200);
		//��ѯ����
		private String statType;
		//��ʾͳ��ʱ�ǰ��·�ͳ�ƣ��������ڣ���ͳ��
		private String statTypeShow = "";
		//������ʾ��Ϣ
		private String errorTip = "";
		
		// ��ʾ�Զ�����ɫ
		private boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		private boolean showTextAxis = true;
		// ��ʾBarͼ���ϵ�����
		private boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		private boolean showBackgroundColor = true;
		// ��ʾ������
		private boolean showOutLine = true;
		//��ʾ������
		private boolean showGrid = true;
		
		//����ͼ���������
		private String accType[] = {"���","����","Ѻ��"};
		private String xData = "";
		private String dataType = "float";
		private String columnTitle[] = {"saving","consume","ensure"};
		
		//���ز�ѯ���
		private List weekResult = null;
		//��λ
		private int dataUnit = 1;
		private int dateUnit11 = 9;
		//������ʾ��Ϣ
		private String yLabel = "";
		//ѡ���ͼ����ʾ����
		private String showType;
		//ͼ��Ҫ��ʾ������
		private String picType = "";

		ActionServlet servlet = QueryAccountStatByCustIdAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//ѧ����
			custId = request.getParameter("empno");
			stuempno = request.getParameter("stuempno");
			//��ʼ����
			beginDate = request.getParameter("begindate");
			//��������
			endDate = request.getParameter("enddate");
			//ѡ���ͼ����ʾ����
			showType = request.getParameter("showType");
			//��ѯ����
			statType = request.getParameter("statType");
			
			setInit(request);
			
		
			if ("".equals(custId)&& "".equals(stuempno)){
				request.setAttribute("errorcont",new String("������Ҫ��ѯ�Ŀͻ��Ż�ѧ���ţ�"));
				return mapping.findForward("errortest");
			}
			if(!"".equals(stuempno)){
	          String 	temp_custId =   getCustId(stuempno);
	          if((!"".equals(custId))&&!temp_custId.equals(custId)){
	        	  request.setAttribute("errorcont",new String("�ͻ������ڣ����������룡"));
					return mapping.findForward("errortest");
	          }else{
	        	  custId = temp_custId;
	          }
			}
			/*if (("".equals(getCustName(custId))) || null==(getCustName(custId))) {
				request.setAttribute("errorcont",new String("�ͻ��ţ�"+custId+"�����ڣ����������룡"));
				return mapping.findForward("errortest");			
			}*/
			request.setAttribute("custname",getCustName(custId));
			
			List result = new TradeSerialDAO().getAllAccountChangeStatByCustId(
					custId, beginDate, endDate,statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",errorTip);
				return mapping.findForward("errortest");			
			}
			//�ж��Ƿ�������ͼ��ʾ
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			
			dateUnit11 = result.size()/8;
			//����ͳ�������ж�Ҫ���
			statTypeReturn(request,result);
			
			//����Ҫ��ʾ��ͼ��������ͼ��
			showTypeResult();
			
			request.setAttribute("ylabel",yLabel);
			request.setAttribute("pictype",picType);
			request.setAttribute("daterange",dateRange.toString());
			request.setAttribute("stattypeshow",statTypeShow);
			
			drawPic(request);
			
			return mapping.findForward("oneaccountstat_queryresult");

		}
		
		/**
		 * ��ʼ��ϵ�в���
		 * @param request
		 */
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			session.setAttribute("custid",custId);
			session.setAttribute("stuempno",stuempno);
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate42d",request.getParameter("begindate"));
				session.setAttribute("enddate42d",request.getParameter("enddate"));
				session.setAttribute("querytype42","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
	 			session.setAttribute("begindate42m",request.getParameter("begindate"));
				session.setAttribute("enddate42m",request.getParameter("enddate"));
				session.setAttribute("querytype42","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate42w",request.getParameter("begindate"));
				session.setAttribute("enddate42w",request.getParameter("enddate"));
				session.setAttribute("querytype42","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",this.servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
			
			if ("bydate".equals(statType)){
				errorTip = "���ڷ�ΧΪ��"+dateRange+"--û����Ҫ��ѯ�����ݣ�������ָ����ѯ������";		
			}else if ("bymonth".equals(statType)){
				errorTip = "�·ݷ�ΧΪ��"+dateRange+"--û����Ҫ��ѯ�����ݣ�������ָ����ѯ������";			
			}
			
		}
		
		/**
		 * ����ѡ���ͳ�����ͻ���ͼ��
		 * @param request
		 * @param result
		 */
		private void statTypeReturn(HttpServletRequest request,List result){
			if ("bydate".equals(statType)){
				request.setAttribute("result",result);
				yLabel = new GetListResultStat().getYLabelMoney(result,"consume",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"consume",dataType);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute("OneAccountStatChart",
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
				}else{
					request.setAttribute("OneAccountStatChart",
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				}
			}else if ("bymonth".equals(statType)){
				request.setAttribute("result",result);
				yLabel = new GetListResultStat().getYLabelMoney(result,"consume",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"consume",dataType);
				xData = "balance_date";
				request.setAttribute("OneAccountStatChart",
						new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				yLabel = new GetListResultStat().getYLabelMoney(weekResult,"consume",dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"consume",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				request.setAttribute("OneAccountStatChart",
						new DrawBarByTypeMap(weekResult,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			}
		}
		private void showTypeResult(){
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)){
					picType = GetProperty.getProperties("pic.timeseries",servlet.getServletContext());
				}else{
					picType = GetProperty.getProperties("pic.line",servlet.getServletContext());
				}
				showOutLine = false;
			}else if ("bar".equals(showType)){
				picType = GetProperty.getProperties("pic.bar",servlet.getServletContext());
				showOutLine = true;
			}else if ("stack".equals(showType)){
				picType = GetProperty.getProperties("pic.stack",servlet.getServletContext());
				showOutLine = true;
			}

		}
		private void drawPic(HttpServletRequest request){
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)){
					request.setAttribute("dataColor", new CustomerDrawChart(showBackgroundColor,
							showCustColor,dateUnit11)
							.getTimeSeriesPostProcessor());
				}else{
					request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
							showTextAxis, showLabel, showBackgroundColor, showOutLine,
							showGrid).getChartPostProcessor());
				}
			}else if ("bar".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid).getChartPostProcessor());
			}else if ("stack".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
						showTextAxis, showLabel, showBackgroundColor, showOutLine,
						showGrid).getChartPostProcessor());
			}
		}

	}
	/**
	 * ����ѧ���ŵõ�����
	 * @param custId
	 * @return
	 */
	private String getCustName(String custId){
		String custName = "";
		List list = new GetQueryConListDAO().getCustNameByID(custId);
		Iterator iter = list.iterator();
		while (iter.hasNext()){
			TCifCustomer row = (TCifCustomer)iter.next();
			custName = row.getCutName().toString();
		}
		return custName;
	}
	
	private String getCustId(String stuempNo){
		String custId ="";
		custId =  AccountUtil.getCustIdBystuempNo(stuempNo);
	    return custId;
	}

}
