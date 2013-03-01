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
import com.kingstargroup.advquery.dept.TCifDept;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.reportdepttrade.ReportDeptTradeDAO;

/**
 * ��λ���гֿ����������ͳ��
 * @author Administrator
 *
 */
public class QueryDeptConsumeStatAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		// TODO ��λ���гֿ����������ͳ��excute
		QueryDeptConsumeStatActionExecution exec = new QueryDeptConsumeStatActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryDeptConsumeStatActionExecution {
		private String statType;
		private String deptCode;
		private String beginDate;
		private String endDate;
		private String statTypeShow = "";
		private StringBuffer dateRange = new StringBuffer(200);
		private String picType = "";

		//���ز�ѯ���
		private List weekResult = null;
		//��λ
		private int dataUnit = 1;
		private int dateUnit = 1;
		//������ʾ��Ϣ
		private String yLabel = "";
		private String showType;
		//����ͼ����������
		private String accType[] = {"���ѽ��"};
		private String xData = "";
		private String dataType = "float";
		private String columnTitle[] = {"consumemoney"};//,"avgmoney"
		
		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		private boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		private boolean showTextAxis =true;
		// ��ʾBarͼ���ϵ�����
		private boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		private boolean showBackgroundColor = true;
		// ��ʾ������
		private boolean showOutLine = true;
		// ��ʾ������
		private boolean showGrid = true;

		ActionServlet servlet = QueryDeptConsumeStatAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//��ѯ��������
			statType = request.getParameter("statType");
			deptCode = request.getParameter("depno");
			//��ʼ����
			beginDate = request.getParameter("begindate");
			//��������
			endDate = request.getParameter("enddate");
			//ѡ���ͼ����ʾ����
			showType = request.getParameter("showType");		
			
			setInit(request);
			List result = new ReportDeptTradeDAO().getDeptConsumeStat(deptCode,beginDate,endDate,statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",getDeptNameByCode(deptCode)+":"+new ErrorInfo().getErrorTip(statType,beginDate,endDate));
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
			request.setAttribute("pictype",picType);

			request.setAttribute("ylabel",yLabel);
			request.setAttribute("daterange",dateRange.toString());
			request.setAttribute("stattypeshow",statTypeShow);
			request.setAttribute("deptname",getDeptNameByCode(deptCode));
			drawPic(request);
			return mapping.findForward("deptconsumestat_queryresult");
			
		}
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			session.setAttribute("deptcode",deptCode);
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate44d",request.getParameter("begindate"));
				session.setAttribute("enddate44d",request.getParameter("enddate"));
				session.setAttribute("querytype44","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
	 			session.setAttribute("begindate44m",request.getParameter("begindate"));
				session.setAttribute("enddate44m",request.getParameter("enddate"));
				session.setAttribute("querytype44","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate44w",request.getParameter("begindate"));
				session.setAttribute("enddate44w",request.getParameter("enddate"));
				session.setAttribute("querytype44","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
		}
		private void statTypeReturn(HttpServletRequest request,List result){
			if ("bydate".equals(statType)){
				yLabel = new GetListResultStat().getYLabelMoney(result, "consumemoney",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "consumemoney",dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute("DeptConsumeStatChart",
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
				}else{
					request.setAttribute("DeptConsumeStatChart",
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit)
							.getDataProducer());
				}
			
			}else if ("bymonth".equals(statType)){
				request.setAttribute("result",result);
				yLabel = new GetListResultStat().getYLabelMoney(result,"consumemoney",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"consumemoney",dataType);
				xData = "balance_date";
				request.setAttribute("DeptConsumeStatChart",
						new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				yLabel = new GetListResultStat().getYLabelMoney(weekResult,"consumemoney",dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"consumemoney",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				request.setAttribute("DeptConsumeStatChart",
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
	private String getDeptNameByCode(String deptCode){
		String deptN = "";
		List deptName = new GetQueryConListDAO().getDeptName(deptCode);
		Iterator iter = deptName.iterator();
		while (iter.hasNext()){
			TCifDept row = (TCifDept)iter.next(); 
			deptN = row.getDeptName();
		}
		return deptN;
	}

}
