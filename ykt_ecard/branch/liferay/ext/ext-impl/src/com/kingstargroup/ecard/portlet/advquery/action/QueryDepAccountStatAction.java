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
 * ������λ��������䶯���
 * 
 * @author Administrator
 * 
 */
public class QueryDepAccountStatAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		// TODO ������λ��������䶯���excute
		QueryDepAccountStatActionExecution exec = new QueryDepAccountStatActionExecution();
		return exec.execute(mapping, form, request, response);
	}

	private class QueryDepAccountStatActionExecution {
		private String statType;
		private String deptCode;
		private String beginDate;
		private String endDate;
		private String statTypeShow = "";
		private StringBuffer dateRange = new StringBuffer(200);
		// ���ز�ѯ���
		private List weekResult = null;
		private String showType;
		private String picType = "";
		// ��λ
		private int dataUnit = 1;
		private int dateUnit = 1;
		// ������ʾ��Ϣ
		private String yLabel = "";
		// ����ͼ����������
		private String accType[] = { "���", "����", "Ѻ��", "�����" };
		private String xData = "";
		private String dataType = "float";
		private String columnTitle[] = { "saving", "consume", "deposit",
				"managefee" };

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

		ActionServlet servlet = QueryDepAccountStatAction.this.servlet;

		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			response.setCharacterEncoding("UTF-8");
			DynaActionForm deptaccountform = (DynaActionForm) form;
			List deptList = AdvqueryServiceUtil.getDeptList();
			request.setAttribute("deptList", deptList);
			String querytype = deptaccountform.getString("querytype");
			if(!"".equals(querytype)){
				deptaccountform.set("querytype", "");
				return mapping.findForward("errortest");	
			}
			
			// ��ѯ����
			statType = deptaccountform.getString("statType");
			deptCode = deptaccountform.getString("depno");
			// ��ʼ����
			beginDate = deptaccountform.getString("deptaccount_begindate");
			// ��������
			endDate = deptaccountform.getString("deptaccount_enddate");
			// ѡ���ͼ����ʾ����
			showType = deptaccountform.getString("showType");
			if("".equals(deptCode)){
				SessionErrors.add(request, EcardConstants.DEPTACCOUNT_ERROR_EXIST,"����ѡ����Ҫͳ�ƵĲ���");
				return mapping.findForward("errortest");
			}
			setInit(request);

			List result = AdvqueryServiceUtil.getDepAccountStat(deptCode,
					beginDate, endDate, statType);
			if (result.isEmpty()) {
				SessionErrors.add(request, EcardConstants.DEPTACCOUNT_ERROR_EXIST,
						getDeptNameByCode(deptCode)
						+ ":"
						+ ErrorInfo.getErrorTip(statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}
			// �ж��Ƿ�������ͼ��ʾ
			String errtip = ErrorInfo.DateRangeJudeg(showType, statType,
					beginDate, endDate, request);
			if (!"".equals(errtip)) {
				SessionErrors.add(request, EcardConstants.DEPTACCOUNT_ERROR_EXIST, errtip);
				return mapping.findForward("errortest");
			}

			dateUnit = result.size() / 2;
			statTypeReturn(request, result);

			// ����Ҫ��ʾ��ͼ��������ͼ��
			showTypeResult();

			request.setAttribute("ylabel", yLabel);
			request.setAttribute("pictype", picType);

			request.setAttribute("daterange", dateRange.toString());
			request.setAttribute("stattypeshow", statTypeShow);
			request.setAttribute("deptname", getDeptNameByCode(deptCode));
			drawPic(request);

			return mapping.findForward("deptaccount_queryresult");
		}

		private void setInit(HttpServletRequest request) {
			HttpSession session = request.getSession();
			session.setAttribute("deptcode", deptCode);
			if ("bydate".equals(statType)) {
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);
				statTypeShow = GetProperty.getProperties("title.date",
						this.servlet.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.date",
								this.servlet.getServletContext())).append(
						beginDate).append("-").append(endDate);
			} else if ("bymonth".equals(statType)) {
				beginDate = DateUtil.getMonth(beginDate);
				endDate = DateUtil.getMonth(endDate);
				statTypeShow = GetProperty.getProperties("title.month",
						this.servlet.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.month",
								this.servlet.getServletContext())).append(
						beginDate).append("-").append(endDate);
			} else if ("byweek".equals(statType)) {
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);
				statTypeShow = GetProperty.getProperties("title.week",
						this.servlet.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.week",
								this.servlet.getServletContext())).append(
						beginDate).append("-").append(endDate);
			}
		}

		private void statTypeReturn(HttpServletRequest request, List result) {
			if ("bydate".equals(statType)) {
				yLabel = new GetListResultStat().getYLabelMoney(result,
						"saving", dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,
						"saving", dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)) {
					request.setAttribute("deptAccountStatChart",
							new DrawTimeSeries(result, columnTitle, xData,
									dataType, accType, dataUnit)
									.getTimeSeriesProducer());
				} else {
					request.setAttribute("deptAccountStatChart",
							new DrawBarByTypeMap(result, accType, xData,
									dataType, columnTitle, dataUnit)
									.getDataProducer());
				}
			} else if ("bymonth".equals(statType)) {
				request.setAttribute("result", result);
				yLabel = new GetListResultStat().getYLabelMoney(result,
						"saving", dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,
						"saving", dataType);
				xData = "balance_date";
				// ������������ʧ���ջأ����쿨����ͼ�����ݼ�
				request.setAttribute("deptAccountStatChart",
						new DrawBarByTypeMap(result, accType, xData, dataType,
								columnTitle, dataUnit).getDataProducer());

				showTextAxis = ErrorInfo.showTextAxis(result);
			} else if ("byweek".equals(statType)) {
				weekResult = new GetListResultStat().getListByWeek(result,
						beginDate, endDate);
				Collections.sort(weekResult, new SortListByResult(
						"balance_date"));
				yLabel = new GetListResultStat().getYLabelMoney(weekResult,
						"saving", dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,
						"saving", dataType);
				xData = "yearweek";
				request.setAttribute("result", weekResult);
				// ������������ʧ���ջأ����쿨����ͼ�����ݼ�
				request.setAttribute("deptAccountStatChart",
						new DrawBarByTypeMap(weekResult, accType, xData,
								dataType, columnTitle, dataUnit)
								.getDataProducer());

				showTextAxis = ErrorInfo.showTextAxis(weekResult);
			}
		}

		private void showTypeResult() {
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)) {
					picType = GetProperty.getProperties("pic.timeseries",
							servlet.getServletContext());
				} else {
					picType = GetProperty.getProperties("pic.line", servlet
							.getServletContext());
				}
				showOutLine = false;
			} else if ("bar".equals(showType)) {
				picType = GetProperty.getProperties("pic.bar", this.servlet
						.getServletContext());
				showOutLine = true;
			} else if ("stack".equals(showType)) {
				picType = GetProperty.getProperties("pic.stack", this.servlet
						.getServletContext());
				showOutLine = true;
			}
		}

		private void drawPic(HttpServletRequest request) {
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)) {
					request.setAttribute("dataColor", new CustomerDrawChart(
							showBackgroundColor, showCustColor, dateUnit)
							.getTimeSeriesPostProcessor());
				} else {
					request.setAttribute("dataColor", new CustomerDrawChart(
							showCustColor, showTextAxis, showLabel,
							showBackgroundColor, showOutLine, showGrid)
							.getChartPostProcessor());
				}
			} else if ("bar".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(
						showCustColor, showTextAxis, showLabel,
						showBackgroundColor, showOutLine, showGrid)
						.getChartPostProcessor());
			} else if ("stack".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(
						showCustColor, showTextAxis, showLabel,
						showBackgroundColor, showOutLine, showGrid)
						.getChartPostProcessor());
			}
		}

	}

	private String getDeptNameByCode(String deptCode) {
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
