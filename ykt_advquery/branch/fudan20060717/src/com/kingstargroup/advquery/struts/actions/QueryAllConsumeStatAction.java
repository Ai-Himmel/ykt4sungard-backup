/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.util.Collections;
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
import com.kingstargroup.advquery.hibernate.util.ReportShopBalanceUtil;

/**
 * �����������ͳ��
 * 
 * @author Administrator
 * 
 */
public class QueryAllConsumeStatAction extends Action {
	/**
	 * Logger for this class
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		QueryAllConsumeStatActionExecution exec = new QueryAllConsumeStatActionExecution();
		ActionForward returnActionForward = exec.execute(mapping, form,
				request, response);
		return returnActionForward;
	}

	private class QueryAllConsumeStatActionExecution {

		//��ʼ���ڣ��·ݣ��ܣ�
		private String beginDate;
		//�������ڣ��·ݣ��ܣ�
		private String endDate;
		
		//����ͷ��ʾ�����ڣ��·ݣ����ڵȣ�
		private String statTypeShow = "";
		//���ڷ�Χ��ʾ
		private StringBuffer dateRange = new StringBuffer("");
		//ͳ������
		private String statType;
		// ������ʾ��Ϣ
		private String yLabel = "";
		private String yLabel2 = "";
		//��λ
		private int dataUnit = 1;
		private int dataUnit2 = 1;
		//X�����ڿ̶�
		private int dateUnit = 1;
		//���ز�ѯ���
		private List weekResult = null;
		private String xData = "";
		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		private boolean showCustColor = false;
		// ��ʾ���������ֵ���ת����
		private boolean showTextAxis = true;
		// ��ʾBarͼ���ϵ�����
		private boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		private boolean showBackgroundColor = true;
		// ��ʾ������
		private boolean showOutLine = true;
		// ��ʾ������
		private boolean showGrid = true;
		
		private String showType;//ѡ���ͼ����ʾ����
		private String picType = "";
		
		// ����ͼ��Ҫ����Ĳ���
		String accType[] = { "���ѽ��", "����ѽ��" };			
		String accType2[] = { "����ѽ��(�Ŵ�)" };			
		String dataType = "float";
		String columnTitle[] = { "tradeamt", "mngamt" };
		String columnTitle2[] = { "mngamt" };
		ActionServlet servlet = QueryAllConsumeStatAction.this.servlet;
		
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			
			// ��ʼ����
			beginDate = request.getParameter("begindate");
			// ��������
			endDate = request.getParameter("enddate");		
			// ͳ������Ҫ����Ĳ����������ڻ��·�ͳ�ƣ�
			statType = request.getParameter("statType");			
			// ѡ���ͼ����ʾ����
			showType = request.getParameter("showType");

			if (("".equals(beginDate)) || ("".equals(endDate))) {
				request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
						statType, beginDate, endDate));
				ActionForward returnActionForward = mapping
						.findForward("errortest");
				return returnActionForward;
			}

			setInit(request);
			
			List result = ReportShopBalanceUtil.getAllConsumeStat(beginDate,
					endDate, statType);
			if (result.isEmpty()) {
				request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
						statType, beginDate, endDate));
				ActionForward returnActionForward = mapping
						.findForward("errortest");
				return returnActionForward;
			}
			Collections.sort(result, new SortListByResult("balance_date"));
			//�ж��Ƿ�������ͼ��ʾ
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			
			dateUnit = result.size()/8;
			statTypeReturn(request,result);
			
			// ����Ҫ��ʾ��ͼ��������ͼ��
			showTypeResult();
			
			request.setAttribute("pictype", picType);
			request.setAttribute("ylabel", yLabel);
			request.setAttribute("ylabel2",yLabel2);
			request.setAttribute("stattype",statType);
			request.setAttribute("pictype",picType);
			request.setAttribute("daterange", dateRange.toString());
			request.setAttribute("stattypeshow", statTypeShow);
			drawPic(request);
			ActionForward returnActionForward = mapping
					.findForward("allconsumestat_queryresult");
			return returnActionForward;
		}
		
		private void setInit(HttpServletRequest request){

			HttpSession session = request.getSession();
			if ("bydate".equals(statType)) {
				beginDate = DateUtil
						.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
				session.setAttribute("begindate45d", request
						.getParameter("begindate"));
				session.setAttribute("enddate45d", request.getParameter("enddate"));
				session.setAttribute("querytype45", "0");
				statTypeShow = GetProperty.getProperties("title.date", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.date", servlet.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("bymonth".equals(statType)) {
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
				session.setAttribute("begindate45m", request
						.getParameter("begindate"));
				session.setAttribute("enddate45m", request.getParameter("enddate"));
				session.setAttribute("querytype45", "1");
				statTypeShow = GetProperty.getProperties("title.month",
						this.servlet.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.month", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("byweek".equals(statType)) {
				beginDate = DateUtil
						.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
				session.setAttribute("begindate45w", request
						.getParameter("begindate"));
				session.setAttribute("enddate45w", request.getParameter("enddate"));
				session.setAttribute("querytype45", "2");
				// beginWeek = DateUtilExtend.getWeek(beginDate);
				// endWeek = DateUtilExtend.getWeek(endDate);
				statTypeShow = GetProperty.getProperties("title.week", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.week", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			}

		}
		
		/**
		 * ����ѡ���ͳ�����ͻ���ͼ��
		 * @param request
		 * @param result
		 */
		private void statTypeReturn(HttpServletRequest request,List result){

			if ("bydate".equals(statType)){
				yLabel = new GetListResultStat().getYLabelMoney(result, "tradeamt",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "tradeamt",dataType);
				yLabel2 = new GetListResultStat().getYLabelMoney(result, "mngamt",dataType);
				dataUnit2 = new GetListResultStat().getUnitValue(result, "mngamt",dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute("allConsumeStatChart",
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
					
					request.setAttribute("allConsumeStatChart2",
							new DrawTimeSeries(result, columnTitle2, xData,
									dataType, accType2, dataUnit2)
									.getTimeSeriesProducer());
					
				}else{
					request.setAttribute("allConsumeStatChart",
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit)
							.getDataProducer());
				}
			}else if ("bymonth".equals(statType)) {
				yLabel = new GetListResultStat().getYLabelMoney(result, "tradeamt",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "tradeamt",dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				request.setAttribute("allConsumeStatChart",
						new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());

				showTextAxis = new ErrorInfo().showTextAxis(result);
			} else if ("byweek".equals(statType)) {
				weekResult = new GetListResultStat().getListByWeek(result,
						beginDate, endDate);
				Collections.sort(weekResult, new SortListByResult("balance_date"));
				xData = "yearweek";
				yLabel = new GetListResultStat().getYLabelMoney(weekResult,
						"tradeamt", dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,
						"tradeamt", dataType);
				request.setAttribute("result", weekResult);
				request.setAttribute("allConsumeStatChart",
						new DrawBarByTypeMap(weekResult, accType, xData, dataType,
								columnTitle, dataUnit).getDataProducer());

				showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			}
	

		}
		
		/**
		 * ����ѡ���ͼ����������ͼ������
		 *
		 */
		private void showTypeResult(){
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)){
					picType = GetProperty.getProperties("pic.timeseries",servlet.getServletContext());
				}else{
					picType = GetProperty.getProperties("pic.line",servlet.getServletContext());
				}
				showOutLine = false;
			} else if ("bar".equals(showType)) {
				picType = GetProperty.getProperties("pic.bar", servlet
						.getServletContext());
				showOutLine = true;
			} else if ("stack".equals(showType)) {
				picType = GetProperty.getProperties("pic.stack",servlet
						.getServletContext());
				showOutLine = true;
			}

		}
		
		private void drawPic(HttpServletRequest request){
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)){
					request.setAttribute("dataColor", new CustomerDrawChart(showBackgroundColor,showCustColor,dateUnit)
							.getTimeSeriesPostProcessor());
				}else{
					request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
							showTextAxis, showLabel, showBackgroundColor, showOutLine,
							showGrid).getChartPostProcessor());
				}
			}else if ("bar".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
						showTextAxis, showLabel, showBackgroundColor, showOutLine,
						showGrid).getChartPostProcessor());
			}else if ("stack".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
						showTextAxis, showLabel, showBackgroundColor, showOutLine,
						showGrid).getChartPostProcessor());
			}

		}
		
	}
}
