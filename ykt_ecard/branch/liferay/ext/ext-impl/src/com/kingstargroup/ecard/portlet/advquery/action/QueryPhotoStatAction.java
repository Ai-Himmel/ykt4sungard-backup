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

import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.liferay.util.servlet.SessionErrors;
/**
 * �������ͳ��
 * @author Administrator
 *
 */
public class QueryPhotoStatAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		response.setCharacterEncoding("UTF-8");
		DynaActionForm pohotform = (DynaActionForm) form;
		List typeList = AdvqueryServiceUtil.getEmpType();
		request.setAttribute("typeList", typeList);
		String querytype = pohotform.getString("querytype");
		if(!"".equals(querytype)){
			pohotform.set("querytype", "");
			return mapping.findForward("errortest");	
		}		
		String cutType = pohotform.getString("emptype");
		//��λ
		int dataUnit = 0;
		//������ʾ��Ϣ
		String yLabel = "";
		//��ʼ����
		String beginDate = pohotform.getString("photo_begindate");
		//��������
		String endDate = pohotform.getString("photo_enddate");
		String dateRange = "";
		String statTypeShow = "";
		List result = null;
		String statType = pohotform.getString("statType");
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			SessionErrors.add(request, EcardConstants.PHOTO_ERROR_EXIST, ErrorInfo
					.getErrorTip(statType, beginDate, endDate));
			return mapping.findForward("errortest");
		}
		HttpSession session = request.getSession();
		session.setAttribute("cuttype",cutType);
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTime(pohotform.getString("photo_begindate"));
			endDate = DateUtil.reFormatTime(pohotform.getString("photo_enddate"));	
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonth(pohotform.getString("photo_begindate"));
			endDate = DateUtil.getMonth(pohotform.getString("photo_enddate"));	
			statTypeShow = GetProperty.getProperties("title.month",this.servlet.getServletContext());
		}
		dateRange = ':'+beginDate+'-'+endDate;
		
		//����ͼ��Ҫ����Ĳ���
		String accType[] = {"�������ͳ��"};
		String xData = "photo_date";
		String showColumn = "photonum";
		String dataType = "integer";
		
		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		boolean showTextAxis ;
		// ��ʾBarͼ���ϵ�����
		boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		boolean showBackgroundColor = true;
		// ��ʾ������
		boolean showOutLine = true;
		// ��ʾ������
		boolean showGrid = true;
		if ("all".equals(cutType)){
			result = AdvqueryServiceUtil.getphotoNumAll(beginDate,endDate,statType);
			request.setAttribute("cuttype","������");
		}else{
			result = AdvqueryServiceUtil.getphotoNumByType(cutType,beginDate,endDate,statType);
			request.setAttribute("cuttype",cutType);
		}
		
		if (result.isEmpty()) {
			SessionErrors.add(request, EcardConstants.PHOTO_ERROR_EXIST, ErrorInfo
					.getErrorTip(statType, beginDate, endDate));
			return mapping.findForward("errortest");
		}
		showTextAxis = ErrorInfo.showTextAxis(result);
		request.setAttribute("daterange",dateRange);
		
		yLabel = new GetListResultStat().getYLabelManNum(result,"photonum",dataType);
		dataUnit = new GetListResultStat().getUnitValue(result,"photonum",dataType);
		request.setAttribute("result",result);
		request.setAttribute("ylabel",yLabel);
		request.setAttribute("stattypeshow",statTypeShow);
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		
		request.setAttribute("photoChart",
				new DrawBarConfTypeMap(result,accType,xData,dataType,showColumn,dataUnit).getDataProducer());
		return mapping.findForward("photo_queryresult");
	}

}
