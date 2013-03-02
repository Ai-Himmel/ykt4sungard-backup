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
import com.kingstargroup.advquery.cewolf.DrawPieCust;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.reportactive.ReportActiveDAO;
/**
 * @author Administrator
 * 
 */
public class QueryCardOpenLoseBackAction extends Action {

	/**
	 * ĳ��ʱ���ڿ�������ʧ�����գ����쿨����ͳ��
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		QueryCardOpenLoseBackActionExecution exec = new QueryCardOpenLoseBackActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryCardOpenLoseBackActionExecution {
		private String beginDate;
		private String endDate;
		//��ѯ�����ڷ�Χ
		private StringBuffer dateRange = new StringBuffer(200);
		//��ѯ�������ʾ����
		private String statTypeShow = "";
		//��λ
		private int dataUnit = 1;
		private int dateUnit = 1;
		//������ʾ��Ϣ
		private String yLabel = "";
		private String showType;
		private String picType = "";
		private List weekResult = null;
		private String statType;
		// ����ͼ��ʱ����Ĳ���
		private String accType[] = { "���п�", "��ʧ��", "�ջؿ�", "���쿨" };
		private String xData = "";
		private String dataType = "integer";
		private String columnTitle[] = {"opencard", "lose", "receive","repair" };

		// �Զ���ͼ����ʾҪ����Ĳ���
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
		// ��ʾ������
		private boolean showGrid = true;
		ActionServlet servlet = QueryCardOpenLoseBackAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//��ʼ����
			beginDate = request.getParameter("begindate");
			//��������
			endDate = request.getParameter("enddate");
			//ѡ���ͼ����ʾ����
			showType = request.getParameter("showType");		
			// ͳ�����Ͳ���
			statType = request.getParameter("statType");
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			setInit(request);
			List result = new ReportActiveDAO().getCardOpenLoseBackStat(beginDate,
					endDate, statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			//�ж��Ƿ�������ͼ��ʾ
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			

			dateUnit = result.size()/9;
			//�ж��ǰ��ܲ�ѯ���£������ղ�ѯ
			statTypeResult(request,result);
			//����Ҫ��ʾ��ͼ��������ͼ��
			showTypeResult();
			request.setAttribute("pictype",picType);

			int[] resultPie = new GetListResultStat().getListResultStat(result,
					columnTitle);

			request.setAttribute("ylabel",yLabel);
			request.setAttribute("daterange",dateRange.toString());
			//request.setAttribute("result", result);
			request.setAttribute("stattypeshow",statTypeShow);
			// �Զ���ͼ����ʾ
			drawPic(request);

			// ���Ʊ�ͼ
			request
					.setAttribute("cardOpenLoseBackPieData", new DrawPieCust(
							resultPie, accType, dataType, columnTitle)
							.getDatasetProducerTotle());

			// �Զ����ͼ��ʾ
			request.setAttribute("dataColorPie", new CustomerDrawChart(showBackgroundColor).getPiePostProcessor());

			return mapping.findForward("cardopenloseback_queryresult");
			
		}
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
	 			session.setAttribute("begindate22d",request.getParameter("begindate"));
				session.setAttribute("enddate22d",request.getParameter("enddate"));
				session.setAttribute("querytype22","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
					.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));	
	 			session.setAttribute("begindate22m",request.getParameter("begindate"));
				session.setAttribute("enddate22m",request.getParameter("enddate"));
				session.setAttribute("querytype22","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate22w",request.getParameter("begindate"));
				session.setAttribute("enddate22w",request.getParameter("enddate"));
				session.setAttribute("querytype22","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
				
			}
		}
		private void statTypeResult(HttpServletRequest request,List result){
			if ("bydate".equals(statType)){
				yLabel = new GetListResultStat().getYLabelCard(result, "opencard",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "opencard",dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute("cardOpenLoseBackBarData",
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
				}else{
					request.setAttribute("cardOpenLoseBackBarData",
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit)
							.getDataProducer());
				}
			}else if ("bymonth".equals(statType)){
				request.setAttribute("result",result);
				yLabel = new GetListResultStat().getYLabelCard(result,"opencard",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"opencard",dataType);
				xData = "balance_date";
				// ������������ʧ���ջأ����쿨����ͼ�����ݼ�
				request.setAttribute("cardOpenLoseBackBarData", new DrawBarByTypeMap(
						result, accType, xData, dataType, columnTitle,dataUnit)
						.getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				yLabel = new GetListResultStat().getYLabelCard(weekResult,"opencard",dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"opencard",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				// ������������ʧ���ջأ����쿨����ͼ�����ݼ�
				request.setAttribute("cardOpenLoseBackBarData", new DrawBarByTypeMap(
						weekResult, accType, xData, dataType, columnTitle,dataUnit)
						.getDataProducer());
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
