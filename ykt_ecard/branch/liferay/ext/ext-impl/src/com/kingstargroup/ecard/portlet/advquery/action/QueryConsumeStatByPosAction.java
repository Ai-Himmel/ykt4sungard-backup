/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.kingstargroup.ecard.util.SortListByResult;
import com.liferay.util.servlet.SessionErrors;

/**
 * ĳһ̨POS�����������ͳ��
 * 
 * @author Administrator
 * 
 */
public class QueryConsumeStatByPosAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		response.setCharacterEncoding("UTF-8");
		DynaActionForm consumebyposform = (DynaActionForm) form;
		String querytype = consumebyposform.getString("querytype");
		if(!"".equals(querytype)){
			consumebyposform.set("querytype", "");
			return mapping.findForward("errortest");	
		}
		// ��ѯ����Ҫ����
		String posId = consumebyposform.getString("posid");
		// ��ʼ����
		String beginDate = consumebyposform
				.getString("consumestatbypos_begindate");
		// ��������
		String endDate = consumebyposform.getString("consumestatbypos_enddate");

		StringBuffer dateRange = new StringBuffer(200);
		String statTypeShow = "";
		// ���ز�ѯ���
		List weekResult = null;
		// ѡ���ͼ����ʾ����
		String showType = consumebyposform.getString("showType");
		String picType = "";
		// ��λ
		int dataUnit = 0;
		// ������ʾ��Ϣ
		String yLabel = "";
		// ��ѯ���Ͳ����������ڷ�Χ��ѯ���·ݲ�ѯ��
		String statType = consumebyposform.getString("statType");
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			SessionErrors.add(request, EcardConstants.CONSUMEBYPOS_ERROR_EXIST, ErrorInfo
					.getErrorTip(statType, beginDate, endDate));
			return mapping.findForward("errortest");
		}
		if("".equals(posId)){
			SessionErrors.add(request, EcardConstants.CONSUMEBYPOS_ERROR_EXIST, "����д���ѻ��ź��ٲ�ѯ");
			return mapping.findForward("errortest");
		}
		if ("bydate".equals(statType)) {
			beginDate = DateUtil
					.reFormatTime(beginDate);
			endDate = DateUtil.reFormatTime(endDate);
			statTypeShow = GetProperty.getProperties("title.date", this.servlet
					.getServletContext());
			dateRange.append(
					GetProperty.getProperties("query.show.date", this.servlet
							.getServletContext())).append(beginDate)
					.append("-").append(endDate);
		} else if ("bymonth".equals(statType)) {
			beginDate = DateUtil.getMonth(beginDate);
			endDate = DateUtil.getMonth(endDate);
			statTypeShow = GetProperty.getProperties("title.month",
					this.servlet.getServletContext());
			dateRange.append(
					GetProperty.getProperties("query.show.month", this.servlet
							.getServletContext())).append(beginDate)
					.append("-").append(endDate);
		} else if ("byweek".equals(statType)) {
			beginDate = DateUtil
					.reFormatTime(beginDate);
			endDate = DateUtil.reFormatTime(endDate);
			statTypeShow = GetProperty.getProperties("title.week", this.servlet
					.getServletContext());
			dateRange.append(
					GetProperty.getProperties("query.show.week", this.servlet
							.getServletContext())).append(beginDate)
					.append("-").append(endDate);

		}

		if (DateUtil.getIntervalTime(endDate, beginDate) > Long.valueOf(
				"7862400000").longValue()) {
			SessionErrors.add(request, EcardConstants.CONSUMEBYPOS_ERROR_EXIST,
					"��ѯ���ڼ�����ܴ��������£�������ָ����ѯ������");
			return mapping.findForward("errortest");
		}
		// ���Ʊ����������
		String accType[] = { "POS����" };
		String xData = "";
		String showColumn = "tradefee";
		String dataType = "float";

		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		boolean showTextAxis = true;
		// ��ʾBarͼ���ϵ�����
		boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		boolean showBackgroundColor = true;
		// ��ʾ������
		boolean showOutLine = true;
		// ��ʾ������
		boolean showGrid = true;

		request.setAttribute("devname", getDevName(posId));
		List result = AdvqueryServiceUtil.getConsumeStatByPos(posId, beginDate,
				endDate, statType);
		if (result.isEmpty()) {
			SessionErrors.add(request, EcardConstants.CONSUMEBYPOS_ERROR_EXIST,
					getDevName(posId)
							+ ":"
							+ ErrorInfo.getErrorTip(statType, beginDate,
									endDate));
			return mapping.findForward("errortest");
		}

		if (("bydate".equals(statType)) || ("bymonth".equals(statType))) {
			request.setAttribute("result", result);
			yLabel = new GetListResultStat().getYLabelMoney(result, "tradefee",
					dataType);
			dataUnit = new GetListResultStat().getUnitValue(result, "tradefee",
					dataType);
			xData = "balance_date";
			request.setAttribute("ConsumeStatByPosChart",
					new DrawBarConfTypeMap(result, accType, xData, dataType,
							showColumn, dataUnit).getDataProducer());
			showTextAxis = ErrorInfo.showTextAxis(result);

		} else if ("byweek".equals(statType)) {
			weekResult = new GetListResultStat().getListByWeek(result,
					beginDate, endDate);
			Collections.sort(weekResult, new SortListByResult("balance_date"));
			yLabel = new GetListResultStat().getYLabelMoney(weekResult,
					"tradefee", dataType);
			dataUnit = new GetListResultStat().getUnitValue(weekResult,
					"tradefee", dataType);
			xData = "yearweek";
			request.setAttribute("result", weekResult);
			request.setAttribute("ConsumeStatByPosChart",
					new DrawBarConfTypeMap(weekResult, accType, xData,
							dataType, showColumn, dataUnit).getDataProducer());
			showTextAxis = ErrorInfo.showTextAxis(weekResult);

		}
		// ����Ҫ��ʾ��ͼ��������ͼ��
		if ("line".equals(showType)) {
			picType = GetProperty.getProperties("pic.line", this.servlet
					.getServletContext());
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

		request.setAttribute("ylabel", yLabel);
		request.setAttribute("pictype", picType);

		request.setAttribute("daterange", dateRange.toString());
		request.setAttribute("stattypeshow", statTypeShow);

		// �Զ���ͼ����ʾ
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,
				showGrid).getChartPostProcessor());
		return mapping.findForward("consumestatbypos_queryresult");
	}

	private String getDevName(String posId) {
		String devName = "";
		List list = AdvqueryServiceUtil.getPosDeviceList(posId);
		if (list != null) {
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				Object row = (Object) iter.next();
				devName = row.toString();
			}
		}
		return devName;
	}

}
