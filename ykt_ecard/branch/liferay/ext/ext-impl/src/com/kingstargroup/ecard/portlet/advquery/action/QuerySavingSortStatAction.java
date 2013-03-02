/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.liferay.util.servlet.SessionErrors;


/**
 * ����������ͳ��
 * 
 * @author Administrator
 * 
 */
public class QuerySavingSortStatAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		response.setCharacterEncoding("UTF-8");
		DynaActionForm savingsortform = (DynaActionForm)form;
		
		String querytype = savingsortform.getString("querytype");
		if(!"".equals(querytype)){
			savingsortform.set("querytype", "");
			return mapping.findForward("errortest");	
		}
		// ��ѯʱҪ����Ĳ���
		String seriType = savingsortform.getString("seritype");
		//��ʼ����
		String beginDate = savingsortform.getString("savingsort_begindate");
		//��������
		String endDate = savingsortform.getString("savingsort_enddate");
		StringBuffer dateRange = new StringBuffer(200);
		String statTypeShow = "";
		//���ز�ѯ���
		List weekResult = null;
		//��ʼ��
		//String beginWeek = "";
		//������
		//String endWeek = "";
		String statType = savingsortform.getString("statType");
		if (("".equals(beginDate))||("".equals(endDate))){
			SessionErrors.add(request, EcardConstants.SAVINGSORT_ERROR_EXIST,ErrorInfo.getErrorTip(statType,beginDate,endDate));	
			return mapping.findForward("errortest");			
		}
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTime(savingsortform.getString("savingsort_begindate"));
			endDate = DateUtil.reFormatTime(savingsortform.getString("savingsort_enddate"));
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonth(savingsortform.getString("savingsort_begindate"));
			endDate = DateUtil.getMonth(savingsortform.getString("savingsort_enddate"));	
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("byweek".equals(statType)){
			beginDate = DateUtil.reFormatTime(savingsortform.getString("savingsort_begindate"));
			endDate = DateUtil.reFormatTime(savingsortform.getString("savingsort_enddate"));	
			statTypeShow = GetProperty.getProperties("title.week",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}
		// ��������ͼ��ʾʱ�������
		String fillData = "devid";
		String xData = "devid";
		String yNumData = "num";
		String yNumDataType="integer";
		String yMoneyDataType="float";
		String yMoneyData = "money";

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
		boolean showGrid = false;

		request.setAttribute("devname",getDevName(Integer.parseInt(seriType)));
		List result = AdvqueryServiceUtil.getSavingSortStat(seriType,beginDate, endDate,statType);
		if (result.isEmpty()){
			SessionErrors.add(request, EcardConstants.SAVINGSORT_ERROR_EXIST,
					getDevName(Integer.parseInt(seriType))+"��"+ErrorInfo.getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");		
		}
		
		if (("bydate".equals(statType))||("bymonth".equals(statType))){
			request.setAttribute("result",result);
			// ��ʾ����������ͼ
			try {
				
				request.setAttribute(
						"savingSortNumChart",
						new DrawBarSingleMap(result, fillData, xData, yNumData,yNumDataType)
								.getDatasetProducer());
							
			} catch (NullPointerException e) {
				_log.error(e);
				return null;
			}

			// ��ʾ���������ͼ
			
			try {			
				request.setAttribute(
						"savingSortMoneyChart",
						new DrawBarSingleMap(result, fillData, xData, yMoneyData,yMoneyDataType)
								.getDatasetProducer());
				
			} catch (NullPointerException e) {
				_log.error(e);
				return null;
			}
			showTextAxis = ErrorInfo.showTextAxis(result);

		}else if ("byweek".equals(statType)){
			weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
			//Collections.sort(weekResult,new SortListByResult("balance_date"));
			request.setAttribute("result",weekResult);
			// ��ʾ����������ͼ
			try {
				
				request.setAttribute(
						"savingSortNumChart",
						new DrawBarSingleMap(weekResult, fillData, xData, yNumData,yNumDataType)
								.getDatasetProducer());
							
			} catch (NullPointerException e) {
				_log.error(e);
				return null;
			}

			// ��ʾ���������ͼ
			
			try {			
				request.setAttribute(
						"savingSortMoneyChart",
						new DrawBarSingleMap(weekResult, fillData, xData, yMoneyData,yMoneyDataType)
								.getDatasetProducer());
				
			} catch (NullPointerException e) {
				_log.error(e);
				return null;
			}
			showTextAxis = ErrorInfo.showTextAxis(weekResult);
			
		}

		request.setAttribute("daterange",dateRange);
		request.setAttribute("stattypeshow",statTypeShow);

		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		
		return mapping.findForward("savingsort_result");
	}
	private String getDevName(int seriType){
		String devName = "";
		switch (seriType){
		case 204 :devName = "Ȧ��ת��";break;
		case 202 :devName = "POS��ֵ";break;
		case 201 :devName = "�ֽ��ֵ";break;
		default :;
		}
		return devName;
	}
	
	private Log _log = LogFactory.getLog(QuerySavingSortStatAction.class);

}
