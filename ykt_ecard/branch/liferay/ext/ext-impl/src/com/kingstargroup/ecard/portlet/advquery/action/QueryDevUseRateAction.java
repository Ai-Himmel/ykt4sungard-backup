/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.hibernate.util.DeviceUtil;
import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawLineChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.liferay.util.servlet.SessionErrors;

/**
 * �ն��豸ʹ����
 * 
 * @author Administrator
 * 
 */
public class QueryDevUseRateAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		response.setCharacterEncoding("UTF-8");
		DynaActionForm devuserateform = (DynaActionForm) form;
		String querytype = devuserateform.getString("querytype");
		if(!"".equals(querytype)){
			devuserateform.set("querytype", "");
			return mapping.findForward("errortest");	
		}
		// ��ѯʱҪ����Ĳ���
		int seriType = Integer.parseInt(devuserateform.getString("seritype"));
		//��λ
		int dataUnit = 0;
		int dateUnit = 1;
		//������ʾ��Ϣ
		String yLabel = "";
		//�豸���ͣ����ݴ���Ľ��������ж�
		String devType = getDevType(seriType);
		//��ʼ����
		String beginDate = devuserateform.getString("devuserate_begindate");
		//��������
		String endDate = devuserateform.getString("devuserate_enddate");
		String dateRange = "";
		String statTypeShow = "";
		String statType = devuserateform.getString("statType");
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			SessionErrors.add(request, EcardConstants.DEVUSERATE_ERROR_EXIST, ErrorInfo
					.getErrorTip(statType, beginDate, endDate));
			return mapping.findForward("errortest");
		}
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTime(devuserateform.getString("devuserate_begindate"));
			endDate = DateUtil.reFormatTime(devuserateform.getString("devuserate_enddate"));

			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonth(devuserateform.getString("devuserate_begindate"));
			endDate = DateUtil.getMonth(devuserateform.getString("devuserate_enddate"));	
			statTypeShow = GetProperty.getProperties("title.month",this.servlet.getServletContext());
		}
		dateRange = ':'+beginDate +'-'+ endDate;
		// ����ͼƬҪ����Ĳ���
		String accType[] = { "�ն��豸ʹ����" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitle[] = {"rate"};
		String showColumn = "rate";

		// �Զ���ͼ����ʾҪ����Ĳ���
		// �������ߵ�͸����
		boolean showAlpha = true;

		// ��ʾͼ�α���ɫ
		boolean showBackGround = true;
		
		boolean showCustColor = true;

		// ����������ַ���
		boolean showTextAxis = true;

		// ��ʾ������
		boolean showGrid = true;

		List result = AdvqueryServiceUtil.getDeviceRate(seriType,beginDate,endDate,devType,statType);
		if (result.isEmpty()) {
			SessionErrors.add(request, EcardConstants.DEVUSERATE_ERROR_EXIST, ErrorInfo
					.getErrorTip(statType, beginDate, endDate));
			return mapping.findForward("errortest");
		}
		
		
		dateUnit = result.size();

		yLabel = new GetListResultStat().getYLabelRate(result,"rate",dataType);
		dataUnit = new GetListResultStat().getUnitValue(result,"rate",dataType);
		//showTextAxis = new ErrorInfo().showTextAxis(result);
		request.setAttribute("ylabel",yLabel);
		request.setAttribute("daterange",dateRange);
		request.setAttribute("result", result);
		request.setAttribute("devname",getDevName(seriType));
		request.setAttribute("stattypeshow",statTypeShow);
		
		if ("bydate".equals(statType)){
			request.setAttribute("pictype",GetProperty.getProperties("pic.timeseries",servlet.getServletContext()));
			request.setAttribute("dataColor", new CustomerDrawChart(showBackGround,showCustColor,dateUnit)
					.getTimeSeriesPostProcessor());
			
			request.setAttribute("devUseRateChart",
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
		}else if ("bymonth".equals(statType)){
			request.setAttribute("pictype",GetProperty.getProperties("pic.line",servlet.getServletContext()));
			request.setAttribute("dataColor", new CustomerDrawLineChart(
					showAlpha, showBackGround, showGrid, showTextAxis)
					.getChartPostProcessor());
			request.setAttribute("devUseRateChart", new DrawBarConfTypeMap(
					result, accType, xData, dataType, showColumn, dataUnit)
					.getDataProducer());
		}
		return mapping.findForward("devuserate_queryresult");
	}
	private String getDevName(int seriType){
		String devName = "";
		switch (seriType){
		case 240001 :devName = "Ȧ���";break;
		case 930034 :devName = "��ֵ��";break;
		case 930031 :devName = "���ѻ�";break;
		default :;
		}
		return devName;
	}
	private String getDevType(int seriType){
		String devType = "";
		switch (seriType){
		case 240001 :devType = "('0230')";break;
		case 930034 :devType = "('0201')";break;
		case 930031 :devType = "('0226','0244')";break;
		default :;
		}
		return devType;
	}

}
