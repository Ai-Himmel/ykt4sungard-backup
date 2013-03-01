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
import com.kingstargroup.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

/**
 * ƶ��������
 * 
 * @author Administrator
 * 
 */
public class QuerySpecialListAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		// ��ʼ����
		String beginDate = request.getParameter("begindate").toString();
		// ��������
		String endDate = request.getParameter("enddate").toString();
		// ���ڲ���Ϊ��
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		
		int datenum = (int)DateUtilExtend.diffDate(DateUtil.reFormatTime(beginDate),DateUtil.reFormatTime(endDate));
		
		
		
		if ("".equals(request.getParameter("per"))
				||(Integer.parseInt(request.getParameter("per").toString()))>datenum) {
			request.setAttribute("errorcont", new String(
					"����Ƶ�Ȳ���Ϊ���Ҳ��ܴ������ڲ���������룡"));
			return mapping.findForward("errortest");
		}
		
		String meal = nullToString(request.getParameter("meal"));
		//String bDate = beginDate;//nullToString(request.getParameter("begindate"));
		//String eDate = nullToString(request.getParameter("enddate"));
		String deptNo = nullToString(request.getParameter("deptNo"));
		String specNo = nullToString(request.getParameter("specNo"));
		String classNo = nullToString(request.getParameter("classNo"));
		int custType = Integer.parseInt(nullToString(request.getParameter("custType")));
		int feeType = Integer.parseInt(nullToString(request.getParameter("feeType")));
		String bStuempNo = nullToString(request.getParameter("bStuempNo"));
		String eStuempNo = nullToString(request.getParameter("eStuempNo"));
		int per = Integer.parseInt(nullToString(request.getParameter("per").toString()));
		String selPer = request.getParameter("selPer").toString();
		int perRange = 0;
		float bavgRange = 0;
		float eavgRange = 0;
		if (!"".equals(request.getParameter("bavgRange").toString())) {
			bavgRange = Float.parseFloat(request.getParameter("bavgRange").toString());
		}
		if (!"".equals(request.getParameter("eavgRange").toString())) {
			eavgRange = Float.parseFloat(request.getParameter("eavgRange").toString());
		}
		
		if (!"".equals(selPer)){
			if ("".equals(request.getParameter("perRange"))){
				request.setAttribute("errorcont", new String(
				"ѡ����ƽ��ֵ������������ĸ�����Χֵ����ȷ�����������룡"));
				return mapping.findForward("errortest");
				
			}else{
				perRange = Integer.parseInt(request.getParameter("perRange").toString());
			}
		}
		//�����ʼֵ�����㣬���ҿ�ʼֵ���ڽ���ֵ����ʾ������Ϣ
		if (bavgRange>0){
			if (bavgRange>eavgRange){
				request.setAttribute("errorcont", new String(
				"ƽ��ֵ��Χ��ʼֵ���ܴ��ڽ���ֵ��Ϊ����ʹ��ƽ��ֵ���˲�ѯ��������������룡"));
				return mapping.findForward("errortest");
				
			}
		}
		
		HttpSession session = request.getSession();
		session.setAttribute("meal",String.valueOf(meal));
		session.setAttribute("begindate27d",String.valueOf(beginDate));
		session.setAttribute("enddate27d",String.valueOf(endDate));
		session.setAttribute("deptNo",String.valueOf(deptNo));
		session.setAttribute("specNo",String.valueOf(specNo));
		session.setAttribute("classNo",String.valueOf(classNo));
		session.setAttribute("custType",String.valueOf(custType));
		session.setAttribute("feeType",String.valueOf(feeType));
		session.setAttribute("bStuempNo",String.valueOf(bStuempNo));
		session.setAttribute("eStuempNo",String.valueOf(eStuempNo));
		session.setAttribute("per",String.valueOf(per));
		session.setAttribute("bavgRange",String.valueOf(bavgRange));
		session.setAttribute("eavgRange",String.valueOf(eavgRange));
		session.setAttribute("selPer",String.valueOf(selPer));
		session.setAttribute("perRange",String.valueOf(perRange));
		
		beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
		endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
		List resultList = new TradeSerialDAO().getSpecialList(beginDate,endDate,deptNo,specNo,classNo,custType,
				feeType,bStuempNo,eStuempNo,per,meal,bavgRange,eavgRange,selPer,perRange);
		List resultAvg = new TradeSerialDAO().getSpecStat(meal);
		List result3 = new TradeSerialDAO().getConsemeAvg(meal,beginDate,endDate);
		if (null==resultList){
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		String specStatTip = "���"+mealTrans(meal)+"�����ѽ��(Ԫ)";
		String dateRange = ":"+beginDate+"-"+endDate+"(��"+datenum+"��)";
		request.setAttribute("daterange",dateRange);
		request.setAttribute("resultAvg",resultAvg);
		request.setAttribute("result3",result3);
		request.setAttribute("resultList",resultList);
		request.setAttribute("specStatTip",specStatTip);
		request.setAttribute("ylabel","��λ:��");
		request.setAttribute("mealStr",mealTrans(meal));
		
		//����ͼ��
		// ��������ͼ��ʾʱ�������
		String fillData = "amavg";
		String xData = "amavg";
		String yData = "num";
		String barDataType = "integer";
		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		boolean showTextAxis = false;
		// ��ʾBarͼ���ϵ�����
		boolean showLabel = true;
		// ��ʾ�Զ���ͼ������ɫ
		boolean showBackgroundColor = true;
		// ��ʾ������
		boolean showOutLine = false;
		// ��ʾ������
		boolean showGrid = true;
		
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());

		// �������������ռ����ͼ�����ݼ�
		request.setAttribute(
				"consAvgData",
				new DrawBarSingleMap(result3, fillData, xData, yData,barDataType)
						.getDatasetProducer());				
		//����ͼ����ʾ����
		return mapping.findForward("speciallist_queryresult");
	}
	
	private String mealTrans(String in){
		if ("bk".equals(in.trim())){
			return "���";
		}else if ("lun".equals(in.trim())){
			return "���";
		}else if ("sup".equals(in.trim())){
			return "���";
		}else{
			return "ȫ��";
		}
	}

	private String nullToString(Object o){
		if (o==null){
			return "";
		}else{
			return o.toString();
		}
	}
}
