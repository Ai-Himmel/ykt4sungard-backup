/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.CustomerDrawLineChart;
import com.kingstargroup.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.hibernate.util.DeviceUtil;

/**
 * �ն��豸ʹ����
 * 
 * @author Administrator
 * 
 */
public class QueryDevUseRate extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		// ��ѯʱҪ����Ĳ���
		int seriType = Integer.parseInt(request.getParameter("seritype"));
		//��λ
		int dataUnit = 0;
		int dateUnit = 1;
		//������ʾ��Ϣ
		String yLabel = "";
		//�豸���ͣ����ݴ���Ľ��������ж�
		String devType = getDevType(seriType);
		//��ʼ����
		String beginDate = request.getParameter("begindate");
		//��������
		String endDate = request.getParameter("enddate");
		String dateRange = "";
		String statTypeShow = "";
		String statType = request.getParameter("statType");
		if (("".equals(beginDate))||("".equals(endDate))){
			request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		HttpSession session = request.getSession();
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
			endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
 			session.setAttribute("begindate52d",request.getParameter("begindate"));
			session.setAttribute("enddate52d",request.getParameter("enddate"));
			session.setAttribute("querytype52","0");
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonth(request.getParameter("begindate"));
			endDate = DateUtil.getMonth(request.getParameter("enddate"));	
			session.setAttribute("querytype52","1");
 			session.setAttribute("begindate52m",request.getParameter("begindate"));
			session.setAttribute("enddate52m",request.getParameter("enddate"));
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

		List result = DeviceUtil.getDeviceRate(seriType,beginDate,endDate,devType,statType);
		if (result.isEmpty()){
			request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
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
		case 240001 :devType = "0230";break;
		case 930034 :devType = "0201";break;
		case 930031 :devType = "0226";break;
		default :;
		}
		return devType;
	}

}
