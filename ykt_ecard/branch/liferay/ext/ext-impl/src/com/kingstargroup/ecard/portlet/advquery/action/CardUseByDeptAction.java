package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.liferay.util.servlet.SessionErrors;

public class CardUseByDeptAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		//ͳ��ʱҪ����Ĳ���
		String deptcode = request.getParameter("deptcode");
		String code = "";
		//����ͼ��ʱҪ����Ĳ���
		String fillData = "cardtypename";
		String yData = "cardtypename";
		String xData = "cardnum";
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
			
		List result = AdvqueryServiceUtil.getCardUseByDept(deptcode);
		
		List deptList = AdvqueryServiceUtil.getDeptList();
		request.setAttribute("deptList", deptList);
		
		if (result==null || result.isEmpty()){
			SessionErrors.add(request, EcardConstants.CARDUSEBYDEPT_ERROR_EXIST,"û����Ҫ��ѯ�����ݣ�������ָ����ѯ������");
			return mapping.findForward("errortest");			
		}
		showTextAxis =  ErrorInfo.showTextAxis(result);
		request.setAttribute("result",result);
		request.setAttribute("deptname", getDeptNameByCode(deptcode));
		// �Զ���ͼ����ʾ
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		
		request.setAttribute("cardUseStatByDept",
				new DrawBarSingleMap(result,fillData,yData,xData,dataType).getDatasetProducer());
		
		return mapping.findForward("cardusebydept_queryresult");
	}
	private String getDeptNameByCode(String deptCode) {
		String deptN = "";
		List deptName = AdvqueryServiceUtil.getDeptName(deptCode);
		if (deptName != null) {
			Iterator iter = deptName.iterator();
			while (iter.hasNext()) {
				TDept row = (TDept) iter.next();
				deptN = row.getDeptname();
			}
		}
		return deptN;
	}

}
