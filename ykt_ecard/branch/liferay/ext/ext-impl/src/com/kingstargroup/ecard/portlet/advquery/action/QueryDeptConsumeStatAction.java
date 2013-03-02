/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

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
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.kingstargroup.ecard.util.SortListByResult;
import com.liferay.util.servlet.SessionErrors;

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
			response.setCharacterEncoding("UTF-8");
			DynaActionForm deptconsumeform = (DynaActionForm) form;
			List deptList = AdvqueryServiceUtil.getDeptList();
			request.setAttribute("deptList", deptList);
			String querytype = deptconsumeform.getString("querytype");
			if(!"".equals(querytype)){
				deptconsumeform.set("querytype", "");
				return mapping.findForward("errortest");	
			}
			//��ѯ��������
			statType = deptconsumeform.getString("statType");
			deptCode = deptconsumeform.getString("depno");
			//��ʼ����
			beginDate = deptconsumeform.getString("deptconsume_begindate");
			//��������
			endDate = deptconsumeform.getString("deptconsume_enddate");
			//ѡ���ͼ����ʾ����
			showType = deptconsumeform.getString("showType");		
			
			setInit(request);
			// �ж��Ƿ�������ͼ��ʾ
			String errtip = ErrorInfo.DateRangeJudeg(showType, statType,
					beginDate, endDate, request);
			if (!"".equals(errtip)) {
				SessionErrors.add(request, EcardConstants.DEPTCONSUME_ERROR_EXIST, errtip);
				return mapping.findForward("errortest");
			}
			
			List result = AdvqueryServiceUtil.getDeptConsumeStat(deptCode,beginDate,endDate,statType);
			if (result.isEmpty()){
				SessionErrors.add(request, EcardConstants.DEPTCONSUME_ERROR_EXIST, getDeptNameByCode(deptCode)+":"+ErrorInfo.getErrorTip(statType,beginDate,endDate));
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
			return mapping.findForward("deptconsume_queryresult");
			
		}
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			session.setAttribute("deptcode",deptCode);
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);	
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(beginDate);
				endDate = DateUtil.getMonth(endDate);
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);	
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
				showTextAxis = ErrorInfo.showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				yLabel = new GetListResultStat().getYLabelMoney(weekResult,"consumemoney",dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"consumemoney",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				request.setAttribute("DeptConsumeStatChart",
						new DrawBarByTypeMap(weekResult,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				showTextAxis = ErrorInfo.showTextAxis(weekResult);
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
		List deptName = AdvqueryServiceUtil.getDeptName(deptCode);
		if (deptName != null) {
			Iterator iter = deptName.iterator();
			while (iter.hasNext()) {
				TDept row = (TDept) iter.next();
				deptN = row.getDeptname();
			}
		}
		return deptN;
	}

}
