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
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.DateUtilExtend;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.liferay.util.servlet.SessionErrors;

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
		
		response.setCharacterEncoding("UTF-8");
		DynaActionForm speciallistform = (DynaActionForm) form;
		
		List detpList = AdvqueryServiceUtil.getDeptList();
		request.setAttribute("deptList", detpList);
		List specList = AdvqueryServiceUtil.getSpecialityList();
		request.setAttribute("specList", specList);
		List custtypeList = AdvqueryServiceUtil.getCusttypeList();
		request.setAttribute("custtypeList", custtypeList);
		List feetypeList = AdvqueryServiceUtil.getFeeTypeList();
		request.setAttribute("feetypeList", feetypeList);
		
		// ��ʼ����
		String beginDate = speciallistform.getString("speciallist_begindate");
		// ��������
		String endDate = speciallistform.getString("speciallist_enddate");
		// ���ڲ���Ϊ��
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, ErrorInfo
					.getErrorTip("bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}

		int datenum = (int)DateUtilExtend.diffDate(DateUtil.reFormatTime(beginDate),DateUtil.reFormatTime(endDate));
		
		
		
		if ("".equals(speciallistform.getString("per"))
				||(Integer.parseInt(speciallistform.getString("per").toString()))>datenum) {
			SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, "����Ƶ�Ȳ���Ϊ���Ҳ��ܴ������ڲ���������룡");
			return mapping.findForward("errortest");
		}
		
		String meal = nullToString(speciallistform.getString("meal"));
		String deptNo = nullToString(speciallistform.getString("deptNo"));
		String specNo = nullToString(speciallistform.getString("specNo"));
		String classNo = nullToString(speciallistform.getString("classNo"));
		int custType = Integer.parseInt(nullToInt(speciallistform.getString("custType")));
		int feeType = Integer.parseInt(nullToInt(speciallistform.getString("feeType")));
		String bStuempNo = nullToString(speciallistform.getString("bStuempNo"));
		String eStuempNo = nullToString(speciallistform.getString("eStuempNo"));
		int per = Integer.parseInt(nullToInt(speciallistform.getString("per")));
		String selPer = speciallistform.getString("selPer");
		int perRange = 0;
		float bavgRange = 0;
		float eavgRange = 0;
		if (!"".equals(speciallistform.getString("bavgRange"))) {
			bavgRange = Float.parseFloat(speciallistform.getString("bavgRange"));
		}
		if (!"".equals(speciallistform.getString("eavgRange"))) {
			eavgRange = Float.parseFloat(speciallistform.getString("eavgRange"));
		}
		
		if (!"".equals(selPer)){
			if ("".equals(speciallistform.getString("perRange"))){
				SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, "ѡ����ƽ��ֵ������������ĸ�����Χֵ����ȷ�����������룡");
				return mapping.findForward("errortest");
				
			}else{
				perRange = Integer.parseInt(speciallistform.getString("perRange"));
			}
		}
		
		if(bavgRange<0 || eavgRange<0){
			SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, "ƽ��ֵ��Χ����Ϊ��ֵ�����������룡");
			return mapping.findForward("errortest");
			
		}
		
		//�����ʼֵ�����㣬���ҿ�ʼֵ���ڽ���ֵ����ʾ������Ϣ
		if (bavgRange>=0){
			if (bavgRange>eavgRange){
				SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, "ƽ��ֵ��Χ��ʼֵ���ܴ��ڽ���ֵ��Ϊ����ʹ��ƽ��ֵ���˲�ѯ��������������룡");
				return mapping.findForward("errortest");
				
			}
		}
		
		
		beginDate = DateUtil.reFormatTime(beginDate);
		endDate = DateUtil.reFormatTime(endDate);
//		List resultList = null;
		List resultList = AdvqueryServiceUtil.getSpecialList(beginDate,endDate,deptNo,specNo,classNo,custType,
				feeType,bStuempNo,eStuempNo,per,meal,bavgRange,eavgRange,selPer,perRange);
		List resultAvg = AdvqueryServiceUtil.getSpecStat(beginDate,endDate,deptNo,specNo,classNo,custType,
				feeType,bStuempNo,eStuempNo,per,meal,bavgRange,eavgRange,selPer,perRange);
		List result3 = AdvqueryServiceUtil.getConsemeAvg(beginDate,endDate,deptNo,specNo,classNo,custType,
				feeType,bStuempNo,eStuempNo,per,meal,bavgRange,eavgRange,selPer,perRange);
		if (resultList.isEmpty()||resultList.size()==0) {
			SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST,ErrorInfo.getErrorTip(
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
	private String nullToInt(Object o){		
		if (o==null||"".equals(o)){
			return "0";
		}else{
			return o.toString();
		}
	}
}
