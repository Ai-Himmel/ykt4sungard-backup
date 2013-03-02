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
import com.kingstargroup.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.photo.PhotoDAO;
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
		String cutType = request.getParameter("emptype");
		//��λ
		int dataUnit = 0;
		//������ʾ��Ϣ
		String yLabel = "";
		//��ʼ����
		String beginDate = request.getParameter("begindate");
		//��������
		String endDate = request.getParameter("enddate");
		String dateRange = "";
		String statTypeShow = "";
		List result = null;
		String statType = request.getParameter("statType");
		if (("".equals(beginDate))||("".equals(endDate))){
			request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		HttpSession session = request.getSession();
		session.setAttribute("cuttype",cutType);
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTimeOther(request.getParameter("begindate"));
			endDate = DateUtil.reFormatTimeOther(request.getParameter("enddate"));	
 			session.setAttribute("begindate51d",request.getParameter("begindate"));
			session.setAttribute("enddate51d",request.getParameter("enddate"));
			session.setAttribute("querytype51","0");
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonthOther(request.getParameter("begindate"));
			endDate = DateUtil.getMonthOther(request.getParameter("enddate"));	
 			session.setAttribute("begindate51m",request.getParameter("begindate"));
			session.setAttribute("enddate51m",request.getParameter("enddate"));
			session.setAttribute("querytype51","1");
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
			result = new PhotoDAO().getphotoNumAll(beginDate,endDate,statType);
			request.setAttribute("cuttype","������");
		}else{
			result = new PhotoDAO().getphotoNumByType(cutType,beginDate,endDate,statType);
			request.setAttribute("cuttype",cutType);
		}
		
		if (result.isEmpty()){
			request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		showTextAxis = new ErrorInfo().showTextAxis(result);
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
