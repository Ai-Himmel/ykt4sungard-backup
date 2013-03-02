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
import org.apache.struts.action.ActionServlet;

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.reportshopbalance.ReportShopBalanceDAO;
import com.kingstargroup.advquery.util.ParamUtil;

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
			//ͳ�����ͣ��£��գ���
			statType = request.getParameter("statType");
			//��ʼ����
			beginDate = request.getParameter("begindate");
			//��������
			endDate = request.getParameter("enddate");
			showType = request.getParameter("showType");		
			operCode = request.getParameter("operCode");
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			setInit(request);
			//�ж��Ƿ�������ͼ��ʾ
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			

			if (("".equals(ParamUtil.getString(request, "storeLimitString"))||(null==ParamUtil.getString(request, "storeLimitString")))){
				request.setAttribute("errorcont",new String("��ѡ��Ҫ�Աȵ��̻���"));
				return mapping.findForward("errortest");
			}
			if (new GetQueryConListDAO().isShopOwner(operCode)){
				storeLimitString = '('+ParamUtil.getString(request, "storeLimitString")+')';
			}else{
				try {
					storeLimitString = '('+new GetQueryConListDAO().getCompareShopList(ParamUtil.getString(request, "storeLimitString"),operCode)+')';				
				} catch (Exception e) {
					e.printStackTrace();
					request.setAttribute("errorcont",new String("��ѡ��Ҫ����в���Ȩ�޵��̻����жԱȣ�"));
					return mapping.findForward("errortest");
				}
			}
			List result = new ReportShopBalanceDAO().getShopAccountCompare(storeLimitString,beginDate,endDate,statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			request.setAttribute("result",result);
			yLabel = new GetListResultStat().getYLabelMoney(result,"tradeamt",dataType);
			dataUnit = new GetListResultStat().getUnitValue(result,"tradeamt",dataType);
			// ������������ʧ���ջأ����쿨����ͼ�����ݼ�
			request.setAttribute("shopCompareData", new DrawBarByTypeMap(
					result, accType, xData, dataType, columnTitle,dataUnit)
					.getDataProducerDouble());
			//showTextAxis = new ErrorInfo().showTextAxis(result);
			
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
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
	 			session.setAttribute("begindate35d",request.getParameter("begindate"));
				session.setAttribute("enddate35d",request.getParameter("enddate"));
				dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
					.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));	
	 			session.setAttribute("begindate35m",request.getParameter("begindate"));
				session.setAttribute("enddate35m",request.getParameter("enddate"));
				dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate35w",request.getParameter("begindate"));
				session.setAttribute("enddate35w",request.getParameter("enddate"));
				dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
		}
	}
}
