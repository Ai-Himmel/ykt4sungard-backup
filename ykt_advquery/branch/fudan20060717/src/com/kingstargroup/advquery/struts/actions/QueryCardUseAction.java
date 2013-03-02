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

import com.kingstargroup.advquery.card.CardDAO;
import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.advquery.cewolf.DrawPie;
import com.kingstargroup.advquery.common.DateUtil;
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
		// ��ѯʱ�������ڲ���
		String beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
		// ��������ͼ��ʾʱ�������
		String fillData = "dict_caption";
		String xData = "dict_caption";
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
		session.setAttribute("begindate21d",request.getParameter("begindate"));
		List result = new CardDAO().getCardUseStatistics(beginDate);
		if (result.isEmpty()){
			request.setAttribute("errorcont",new String("û����Ҫ��ѯ�����ݣ�������ָ����ѯ������"));
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
