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

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

/**
 * �Ž���Ϣͳ�Ʒ���
 * 
 * @author Administrator
 * 
 */
public class EntranceGuardAnalyseAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String groupedlist = request.getParameter("groupedlist");
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
		
		String deptNo = nullToString(request.getParameter("deptNo"));
		String specNo = nullToString(request.getParameter("specNo"));
		String classNo = nullToString(request.getParameter("classNo"));
		int custType = Integer.parseInt(nullToString(request.getParameter("custType")));
		int cardType = Integer.parseInt(nullToString(request.getParameter("cardType")));
		String devUse = nullToString(request.getParameter("devUse"));
		String bStuempNo = nullToString(request.getParameter("bStuempNo"));
		String eStuempNo = nullToString(request.getParameter("eStuempNo"));
		
		
		HttpSession session = request.getSession();
		session.setAttribute("bdate71",String.valueOf(beginDate));
		session.setAttribute("edate71",String.valueOf(endDate));
		session.setAttribute("deptNo",String.valueOf(deptNo));
		session.setAttribute("specNo",String.valueOf(specNo));
		session.setAttribute("classNo",String.valueOf(classNo));
		session.setAttribute("custType",String.valueOf(custType));
		session.setAttribute("devUse",String.valueOf(devUse));
		session.setAttribute("eStuempNo",String.valueOf(eStuempNo));
		session.setAttribute("bStuempNo",String.valueOf(bStuempNo));
		session.setAttribute("eStuempNo",String.valueOf(eStuempNo));
		session.setAttribute("egroupedlist",String.valueOf(groupedlist));
		
		
		beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
		endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
		
		List resultList = new TradeSerialDAO().entranceAnalyse(beginDate,endDate,deptNo,specNo,classNo,custType,
				cardType,devUse,bStuempNo,eStuempNo,groupedlist);
		if (null==resultList){
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		request.setAttribute("resultList",resultList);
		request.setAttribute("egroupedlist",String.valueOf(groupedlist));
		request.setAttribute("specStatTip","��֤��Ϣͳ�Ʒ���(���һ��Ϊ�ϼ�ֵ)");
		return mapping.findForward("entranceanalyse_queryresult");
		/*
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
		 * 
		 */
	}
	/*
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
	*/
	private String nullToString(Object o){
		if (o==null){
			return "";
		}else{
			return o.toString();
		}
	}
	
	/*
	private String nullToInt(Object o){
		if (o==null){
			return "0";
		}else{
			return o.toString();
		}
	}
	*/
}
