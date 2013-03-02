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
import org.apache.struts.action.ActionServlet;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.util.servlet.SessionErrors;

/**
 * ���̻�Ӫҵ����Ա�
 * @author Administrator
 *
 */
public class QueryShopCompareAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
				ActionForm form, 
				HttpServletRequest request, 
				HttpServletResponse response) throws Exception {
		QueryShopCompareActionExecution exec = new QueryShopCompareActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryShopCompareActionExecution {
		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		private boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		private boolean showTextAxis = false;
		// ��ʾBarͼ���ϵ�����
		private boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		private boolean showBackgroundColor = true;
		// ��ʾ������
		private boolean showOutLine = true;
		// ��ʾ������
		private boolean showGrid = true;
		//��ѯ�����ڷ�Χ
		private StringBuffer dateRange = new StringBuffer(200);
		private String statType;
		private String beginDate;
		private String endDate;
		//��λ
		private int dataUnit = 0;
		//������ʾ��Ϣ
		private String yLabel = "";
		//Ҫ�Աȵ��̻�
		private String storeLimitString = "";
		private String showType;
		private String picType = "";
		private String operCode;
		// ����ͼ��ʱ����Ĳ���
		private String accType[] = {"���׶�","�����"};
		private String xData = "shopid";
		private String dataType = "float";
		private String columnTitle[] = {"tradeamt","mngamt"};
		ActionServlet servlet = QueryShopCompareAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			response.setCharacterEncoding("UTF-8");
			DynaActionForm shopcompareform = (DynaActionForm) form;
			
			String querytype = shopcompareform.getString("querytype");
			if(!"".equals(querytype)){
				shopcompareform.set("querytype", "");
				return mapping.findForward("errortest");	
			}
			//ͳ�����ͣ��£��գ���
			statType = shopcompareform.getString("statType");
			//��ʼ����
			beginDate = shopcompareform.getString("shopcompare_begindate");
			//��������
			endDate = shopcompareform.getString("shopcompare_enddate");
			showType = shopcompareform.getString("showType");		
//			operCode = shopcompareform.getString("operCode");
			if (("".equals(beginDate)) || ("".equals(endDate))) {
				SessionErrors.add(request, EcardConstants.SHOPCOMPARE_ERROR_EXIST,
						ErrorInfo.getErrorTip(statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}
			
			setInit(request);
			//�ж��Ƿ�������ͼ��ʾ
			String errtip = ErrorInfo.DateRangeJudeg(showType, statType,
					beginDate, endDate, request);
			if (!"".equals(errtip)) {
				SessionErrors.add(request, EcardConstants.SHOPCOMPARE_ERROR_EXIST, errtip);
				return mapping.findForward("errortest");
			}
			storeLimitString = ParamUtil.getString(request, "storeLimitString");

			if ((null==storeLimitString)||"".equals(storeLimitString)){
				SessionErrors.add(request, EcardConstants.SHOPCOMPARE_ERROR_EXIST, "��ѡ��Ҫ�Աȵ��̻���");
				return mapping.findForward("errortest");
			}
//			if (new GetQueryConListDAO().isShopOwner(operCode)){
//				storeLimitString = '('+ParamUtil.getString(request, "storeLimitString")+')';
//			}else{
//				try {
//					storeLimitString = '('+new GetQueryConListDAO().getCompareShopList(ParamUtil.getString(request, "storeLimitString"),operCode)+')';				
//				} catch (Exception e) {
//					e.printStackTrace();
//					SessionErrors.add(request, EcardConstants.SHOPCOMPARE_ERROR_EXIST, "��ѡ��Ҫ����в���Ȩ�޵��̻����жԱȣ�");
//					return mapping.findForward("errortest");
//				}
//			}
			List result = AdvqueryServiceUtil.getShopAccountCompare(storeLimitString,beginDate,endDate,statType);
			if (result.isEmpty()){
				SessionErrors.add(request, EcardConstants.SHOPCOMPARE_ERROR_EXIST, ErrorInfo.getErrorTip(statType, beginDate,
										endDate));
				return mapping.findForward("errortest");			
			}
			request.setAttribute("storeLimitString", storeLimitString);
			request.setAttribute("result",result);
			yLabel = new GetListResultStat().getYLabelMoney(result,"tradeamt",dataType);
			dataUnit = new GetListResultStat().getUnitValue(result,"tradeamt",dataType);
			// ������������ʧ���ջأ����쿨����ͼ�����ݼ�
			request.setAttribute("shopCompareData", new DrawBarByTypeMap(
					result, accType, xData, dataType, columnTitle,dataUnit)
					.getDataProducerDouble());
			//showTextAxis = ErrorInfo.showTextAxis(result);
			
			//����Ҫ��ʾ��ͼ��������ͼ��
			if ("line".equals(showType)){
				picType = GetProperty.getProperties("pic.line",this.servlet.getServletContext());
				showOutLine = false;
			}else if ("bar".equals(showType)){
				picType = GetProperty.getProperties("pic.bar",this.servlet.getServletContext());
				showOutLine = true;
			}else if ("stack".equals(showType)){
				picType = GetProperty.getProperties("pic.stack",this.servlet.getServletContext());
				showOutLine = true;
			}
			
			request.setAttribute("ylabel",yLabel);
			request.setAttribute("pictype",picType);

			request.setAttribute("daterange",dateRange.toString());
			// �Զ���ͼ����ʾ
			request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
					showTextAxis, showLabel, showBackgroundColor, showOutLine,
					showGrid).getChartPostProcessor());

			return mapping.findForward("shopcompare_queryresult");
			
		}
		private void setInit(HttpServletRequest request){
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);
				dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
					.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(beginDate);
				endDate = DateUtil.getMonth(endDate);	
				dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);	
				dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
		}
	}
}
