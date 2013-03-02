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
import com.kingstargroup.advquery.reportactive.ReportActiveDAO;

/**
 * @author Administrator
 *
 */
public class QueryCardOpenDestroyStatAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		QueryCardOpenDestroyStatActionExecution exec = new QueryCardOpenDestroyStatActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryCardOpenDestroyStatActionExecution {
		private String beginDate;
		private String endDate;
		//��ѯ���ڷ�Χ
		private StringBuffer dateRange = new StringBuffer(200);
		//������ʾ����
		private String statTypeShow = "";
		//���ز�ѯ���
		private List weekResult = null;
		private String showType ;
		private String picType = "";
		
		//��λ
		private int dataUnit = 1;
		//���ڿ̶�
		private int dateUnit = 1;
		//������ʾ��Ϣ
		private String yLabel = "";
		private String statType;
		//����ͼ��ʱҪ����Ĳ���
		private String accType[] = {"��������","��������"};
		private String xData = "";
		private String dataType = "integer";
		private String columnTitle[] = {"opencard","destorycard"};
		
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
		ActionServlet servlet = QueryCardOpenDestroyStatAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//��ʼ����
			beginDate = request.getParameter("begindate");
			//��������
			endDate = request.getParameter("enddate");
			//ѡ���ͼ����ʾ����
			showType = request.getParameter("showType");		
			//ͳ���������������ڻ��·ݣ�
			statType = request.getParameter("statType");
			
			//��ʼ���ڻ��������û�����룬��ʾ������Ϣ
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			setInit(request);

			List result = new ReportActiveDAO().getCardOpenDestroyStat(beginDate,endDate,statType);
			
			if ((result.isEmpty())||(null == result)){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			//�ж��Ƿ�������ͼ��ʾ
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			

			dateUnit = result.size()/10;
			statTypeReturn(request,result);
			
			//����Ҫ��ʾ��ͼ��������ͼ��
			showTypeResult();
			
			request.setAttribute("ylabel",yLabel);
			request.setAttribute("pictype",picType);

			request.setAttribute("daterange",dateRange.toString());
			
			request.setAttribute("stattypeshow",statTypeShow);
			
			//����ͼ��
			drawPic(request);
			return mapping.findForward("cardopendestory_queryresult");
			
		}
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
				session.setAttribute("begindate25d",request.getParameter("begindate"));
				session.setAttribute("enddate25d",request.getParameter("enddate"));
				session.setAttribute("querytype25","0");
				statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));	
				session.setAttribute("begindate25m",request.getParameter("begindate"));
				session.setAttribute("enddate25m",request.getParameter("enddate"));
				session.setAttribute("querytype25","1");
				statTypeShow = GetProperty.getProperties("title.month",this.servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
				session.setAttribute("begindate25w",request.getParameter("begindate"));
				session.setAttribute("enddate25w",request.getParameter("enddate"));
				session.setAttribute("querytype25","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",this.servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
		}
		
		/**
		 * ����ѡ���ͳ�����ͻ���ͼ��
		 * @param request
		 * @param result
		 */
		private void statTypeReturn(HttpServletRequest request,List result){
			if ("bydate".equals(statType)){
				yLabel = new GetListResultStat().getYLabelManNum(result, "opencard",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "opencard",dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute("cardOpenDestoryBarChart",
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
				}else{
					request.setAttribute("cardOpenDestoryBarChart",
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit)
							.getDataProducer());
				}
			}else if ("bymonth".equals(statType)){
				request.setAttribute("result",result);
				yLabel = new GetListResultStat().getYLabelManNum(result,"opencard",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"opencard",dataType);
				xData = "balance_date";
				request.setAttribute("cardOpenDestoryBarChart",
						new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				yLabel = new GetListResultStat().getYLabelManNum(weekResult,"opencard",dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"opencard",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				request.setAttribute("cardOpenDestoryBarChart",
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
				picType = GetProperty.getProperties("pic.bar",this.servlet.getServletContext());
				showOutLine = true;
			}else if ("stack".equals(showType)){
				picType = GetProperty.getProperties("pic.stack",this.servlet.getServletContext());
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
