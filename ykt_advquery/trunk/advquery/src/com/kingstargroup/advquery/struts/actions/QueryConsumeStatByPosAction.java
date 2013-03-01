/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.util.Collections;
import java.util.Iterator;
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
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

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
		//��ѯ����Ҫ����
		String posId = request.getParameter("posid");
		//��ʼ����
		String beginDate = request.getParameter("begindate");
		//��������
		String endDate = request.getParameter("enddate");
		StringBuffer dateRange = new StringBuffer(200);
		String statTypeShow = "";
		//���ز�ѯ���
		List weekResult = null;
		//ѡ���ͼ����ʾ����
		String showType = request.getParameter("showType");		
		String picType = "";
		//��λ
		int dataUnit = 0;
		//������ʾ��Ϣ
		String yLabel = "";
		//��ѯ���Ͳ����������ڷ�Χ��ѯ���·ݲ�ѯ��
		String statType = request.getParameter("statType");
		if (("".equals(beginDate))||("".equals(endDate))){
			request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		HttpSession session = request.getSession();
		session.setAttribute("posid",posId);
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
			endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
 			session.setAttribute("begindate32d",request.getParameter("begindate"));
			session.setAttribute("enddate32d",request.getParameter("enddate"));
			session.setAttribute("querytype32","0");
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonth(request.getParameter("begindate"));
			endDate = DateUtil.getMonth(request.getParameter("enddate"));
 			session.setAttribute("begindate32m",request.getParameter("begindate"));
			session.setAttribute("enddate32m",request.getParameter("enddate"));
			session.setAttribute("querytype32","1");
			statTypeShow = GetProperty.getProperties("title.month",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("byweek".equals(statType)){
			beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
			endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
 			session.setAttribute("begindate32w",request.getParameter("begindate"));
			session.setAttribute("enddate32w",request.getParameter("enddate"));
			session.setAttribute("querytype32","2");
			//beginWeek = DateUtilExtend.getWeek(beginDate);
			//endWeek = DateUtilExtend.getWeek(endDate);	
			statTypeShow = GetProperty.getProperties("title.week",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
			
		}
		
		if (DateUtil.getIntervalTime(endDate,beginDate)>Long.valueOf("7862400000").longValue()){
			request.setAttribute("errorcont",new String("��ѯ���ڼ�����ܴ��������£�������ָ����ѯ������"));
			return mapping.findForward("errortest");			
		}
		//���Ʊ����������
		String accType[] = {"POS����"};
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

		request.setAttribute("devname",getDevName(posId));
		List result = new TradeSerialDAO().getConsumeStatByPos(posId,
				beginDate, endDate,statType);
		if (result.isEmpty()){
			request.setAttribute("errorcont",getDevName(posId)+":"+new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		
		if (("bydate".equals(statType))||("bymonth".equals(statType))){
			request.setAttribute("result",result);
			yLabel = new GetListResultStat().getYLabelMoney(result,"tradefee",dataType);
			dataUnit = new GetListResultStat().getUnitValue(result,"tradefee",dataType);
			xData = "balance_date";
			request.setAttribute("ConsumeStatByPosChart",
					new DrawBarConfTypeMap(result,accType,xData,dataType,showColumn,dataUnit).getDataProducer());
			showTextAxis = new ErrorInfo().showTextAxis(result);
			
		}else if ("byweek".equals(statType)){
			weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
			Collections.sort(weekResult,new SortListByResult("balance_date"));
			yLabel = new GetListResultStat().getYLabelMoney(weekResult,"tradefee",dataType);
			dataUnit = new GetListResultStat().getUnitValue(weekResult,"tradefee",dataType);
			xData = "yearweek";
			request.setAttribute("result",weekResult);
			request.setAttribute("ConsumeStatByPosChart",
					new DrawBarConfTypeMap(weekResult,accType,xData,dataType,showColumn,dataUnit).getDataProducer());
			showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			
		}
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
		request.setAttribute("stattypeshow",statTypeShow);
		
		// �Զ���ͼ����ʾ
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		return mapping.findForward("consumestatbypos_queryresult");
	}
	
	private String getDevName(String posId){
		String devName = "";
		List list = new GetQueryConListDAO().getPosDeviceList(posId);
		Iterator iter = list.iterator();
		while (iter.hasNext()){
			Object row = (Object)iter.next();
			devName = row.toString();
		}
		return devName;
	}

	

}
