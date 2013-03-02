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
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawPie;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.servlet.SessionErrors;


/**
 * ��Ƭʹ�����
 * 
 * @author Administrator
 * 
 */
public class QueryCardUseAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		response.setCharacterEncoding("UTF-8");
		// ��ѯʱ�������ڲ���
		DynaActionForm   carduseform = (DynaActionForm)form;
		
		String enddate = carduseform.getString("carduse_enddate");
		
		enddate = DateUtil.reFormatTime(enddate);
		
		// ��������ͼ��ʾʱ�������
		String fillData = "typename";
		String xData = "typename";
		String yData = "cardnum";
		String barDataType = "integer";
		
		String dataPie = "rate";
		String dataType = "float";

		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		boolean showTextAxis = false;
		// ��ʾBarͼ���ϵ�����
		boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		boolean showBackgroundColor = true;
		// ��ʾ������
		boolean showOutLine = true;
		// ��ʾ������
		boolean showGrid = true;
		HttpSession session = request.getSession();
		
		List result = AdvqueryServiceUtil.getCardUse(enddate);
		if (result.isEmpty()){
			SessionErrors.add(request, EcardConstants.CARDUSE_ERROR_EXIST,"û����Ҫ��ѯ�����ݣ�������ָ����ѯ������");
			return mapping.findForward("errortest");			
		}
		request.setAttribute("result", result);

		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());

		// �������������ռ����ͼ�����ݼ�
		request.setAttribute(
				"cardUseVBarData",
				new DrawBarSingleMap(result, fillData, xData, yData,barDataType)
						.getDatasetProducer());
		// �������������ռ�ٷֱ�ͼ�����ݼ�
		request.setAttribute(
				"cardUsePieData",
				new DrawPie(result, xData, dataPie, dataType)
						.getDatasetProducer());
		// �Զ����ͼ��ʾ
		request.setAttribute("dataColorPie", new CustomerDrawChart(showBackgroundColor).getPiePostProcessor());

		return mapping.findForward("carduse_queryresult");
	}

}
