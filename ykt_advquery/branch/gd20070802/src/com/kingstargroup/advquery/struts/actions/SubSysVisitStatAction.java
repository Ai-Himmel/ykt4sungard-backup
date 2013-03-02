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
import com.kingstargroup.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.advquery.cewolf.CustomerDrawLineChart;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.hibernate.util.SubSysUtil;
import com.kingstargroup.advquery.util.ParamUtil;

public class SubSysVisitStatAction extends Action {

	/**
	 * Ȧ��ɹ���
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		QuerySubSysActionExecution exec = new QuerySubSysActionExecution();
		return exec.execute(mapping, form, request, response);
	}

	private class QuerySubSysActionExecution {
		private String beginDate;

		private String endDate;
		
		private int sysid = 0;

		private StringBuffer dateRange = new StringBuffer(200);

		private String statTypeShow = "";
		private String picType = "";
		// ���ز�ѯ���
		private List weekResult = null;

		// ��λ
		private int dataUnit = 1;

		private int dateUnit = 1;

		// ������ʾ��Ϣ
		private String yLabel = "";

		private String statType;

		// ����ͼƬҪ����Ĳ���
		private String accType[] = { "������" };

		private String xData = "";

		private String dataType = "integer";

		private String showColumn = "numb";
		private String columnTitle[] = {"numb"};

		// �Զ���ͼ����ʾҪ����Ĳ���
		// �������ߵ�͸����
		private boolean showAlpha = true;

		// ��ʾͼ�α���ɫ
		private boolean showBackGround = true;
		
		private boolean showCustColor = true;

		// ����������ַ���
		private boolean showTextAxis = true;

		// ��ʾ������
		private boolean showGrid = true;

		ActionServlet servlet = SubSysVisitStatAction.this.servlet;

		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			// ��ʼ����
			beginDate = request.getParameter("begindate");
			// ��������
			endDate = request.getParameter("enddate");
			statType = request.getParameter("statType");
			if (("".equals(beginDate)) || ("".equals(endDate))) {
				request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
						statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}

			setInit(request);

			List result = SubSysUtil.getgetSubSysVisitList(
					sysid,beginDate, endDate, statType);
			if ((result.isEmpty()) || (result == null)) {
				request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
						statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}

			dateUnit = result.size()/3;
			statTypeResult(request, result);
			showTypeResult();
			request.setAttribute("ylabel", yLabel);
			request.setAttribute("pictype",picType);
			
			//������ϵͳ����
			request.setAttribute("syssubtitle", SubSysUtil.getSubSysName((new Integer(sysid)).toString())+"����ͳ��"+dateRange.toString());
			request.setAttribute("stattypeshow", statTypeShow);

			drawPic(request);
			return mapping.findForward("subsys_queryresult");

		}

		private void setInit(HttpServletRequest request) {
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)) {
				beginDate = DateUtil.reFormatTime(request
						.getParameter("begindate"));
				endDate = DateUtil
						.reFormatTime(request.getParameter("enddate"));
				
				sysid = ParamUtil.getInteger(request,"subsystype");
				session.setAttribute("begindate54d", request
						.getParameter("begindate"));
				session.setAttribute("enddate54d", request
						.getParameter("enddate"));
				session.setAttribute("querytype54", "0");
				session.setAttribute("subsystype",new Integer(sysid));
				statTypeShow = GetProperty.getProperties("title.date", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.date", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("bymonth".equals(statType)) {
				beginDate = DateUtil
						.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
				sysid = ParamUtil.getInteger(request,"subsystype");
				session.setAttribute("begindate54m", request
						.getParameter("begindate"));
				session.setAttribute("enddate54m", request
						.getParameter("enddate"));
				session.setAttribute("querytype54", "1");
				session.setAttribute("subsystype",new Integer(sysid));
				statTypeShow = GetProperty.getProperties("title.month", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.month", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("byweek".equals(statType)) {
				beginDate = DateUtil.reFormatTime(request
						.getParameter("begindate"));
				endDate = DateUtil
						.reFormatTime(request.getParameter("enddate"));
				sysid = ParamUtil.getInteger(request,"subsystype");
				session.setAttribute("begindate54w", request
						.getParameter("begindate"));
				session.setAttribute("enddate54w", request
						.getParameter("enddate"));
				session.setAttribute("subsystype",new Integer(sysid));
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

		private void statTypeResult(HttpServletRequest request, List result) {
			if ("bydate".equals(statType)) {
				request.setAttribute("result", result);
				xData = "log_date";
				yLabel = new GetListResultStat().getYLabelVisitNum(result, "numb",
						dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "numb",
						dataType);
				request.setAttribute("subsysChart",
						new DrawTimeSeries(result, columnTitle, xData,
								dataType, accType, dataUnit)
								.getTimeSeriesProducer());

				showTextAxis = new ErrorInfo().showTextAxis(result);
			} else if ("bymonth".equals(statType)) {
				request.setAttribute("result", result);
				xData = "log_date";
				yLabel = new GetListResultStat().getYLabelVisitNum(result, "numb",
						dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "numb",
						dataType);
				request.setAttribute("subsysChart", new DrawBarConfTypeMap(
						result, accType, xData, dataType, showColumn, dataUnit)
						.getDataProducer());

				showTextAxis = new ErrorInfo().showTextAxis(result);
			} else if ("byweek".equals(statType)) {
				weekResult = new GetListResultStat().getListByWeek(result,
						beginDate, endDate);
				Collections.sort(weekResult, new SortListByResult(
						"log_date"));
				yLabel = new GetListResultStat().getYLabelVisitNum(weekResult,
						"numb", dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,
						"numb", dataType);
				xData = "yearweek";
				request.setAttribute("result", weekResult);
				request.setAttribute("subsysChart", new DrawBarConfTypeMap(
						weekResult, accType, xData, dataType, showColumn,
						dataUnit).getDataProducer());

				showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			}
		}
		private void showTypeResult(){
			if ("bydate".equals(statType)){
				picType = GetProperty.getProperties("pic.timeseries",servlet.getServletContext());
			}else{
				picType = GetProperty.getProperties("pic.line",servlet.getServletContext());
			}
		}
		private void drawPic(HttpServletRequest request){
			if ("bydate".equals(statType)){
				request.setAttribute("dataColor", new CustomerDrawChart(showBackGround,showCustColor,dateUnit)
						.getTimeSeriesPostProcessor());
			}else{
				request.setAttribute("dataColor", new CustomerDrawLineChart(
						showAlpha, showBackGround, showGrid, showTextAxis)
						.getChartPostProcessor());
			}
		}

	}
}
